/*
 *  cousagi.c
 *
 * History:
 * $Log: /comm/xmlRPC/cousagi.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 11    06/09/15 16:38 Tsujimura543
 * ソースコードを整理
 * 
 * 10    06/08/29 21:20 Tsujimura543
 * 新しい URL で提供されることになった「記事投稿」APIの動作確認用に
 * コードを修正
 * 
 * 9     06/08/18 11:03 Tsujimura543
 * 新APIテスト版
 * 
 * 8     05/02/18 16:10 Tsujimura543
 * cousagi.yomiusa..net を www.blogpet.net に文字列置換するようにした
 * 
 * 7     05/02/18 15:39 Tsujimura543
 * 「こうさぎ」が「BlogPet」へ移行したのに伴う修正
 * 
 * 6     04/11/04 16:18 Tsujimura543
 * setRequestForCousagi() を追加し、要求電文組み立て処理を共通化
 * 
 * 5     04/11/04 16:10 Tsujimura543
 * getNewWhisperOnCousagi() を追加
 * 
 * 4     04/08/31 15:57 Tsujimura543
 * http POST で使う電文格納領域を動的に確保するように変更
 * 
 * 3     04/07/16 14:09 Tsujimura543
 * こうさぎ API 関連を整理
 * 
 * 2     04/07/07 11:57 Tsujimura543
 * RCS による版数管理から VSS による版数管理に移行
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/cousagi.c 1     09/05/14 3:46 tsupo $";
#endif


char    *regulerizeString( char *src );

/*
 * cousagi XML-RPC API
 *
 *  cousagi.getNewEntry 
 *    説明 
 *      こうさぎに新しく記事を書かせます 
 *    引数 
 *      String  username, // こうさぎ のユーザ名(アカウント)
 *      String  password  // 上記ユーザの login 用パスワード
 *
 *  cousagi.getNewPhrase 
 *    説明 
 *      こうさぎに新しく発言させます 
 *    引数 
 *      String  username, // こうさぎ のユーザ名(アカウント)
 *      String  password  // 上記ユーザの login 用パスワード
 *
 *  cousagi.getNewHaiku 
 *    説明 
 *      こうさぎに新しく俳句を詠ませます 
 *    引数 
 *      String  username, // こうさぎ のユーザ名(アカウント)
 *      String  password  // 上記ユーザの login 用パスワード
 *
 *  cousagi.getNewWhisper 
 *    説明 
 *      こうさぎに新しく寝言をつぶやかせます 
 *    引数 
 *      String  username, // こうさぎ のユーザ名(アカウント)
 *      String  password  // 上記ユーザの login 用パスワード
 *
 *
 *  blogpet.getEntry
 *    説明 
 *      BlogPet に新しく記事を書かせます 
 *    引数 
 *      String ログインID
 *      String ログインパス
 */

/* 要求電文の組み立て */
char    *
setRequestForCousagi( const char *userName,     // (I) ユーザ名
                      const char *password,     // (I) パスワード
                      const char *serviceName,  // (I) 要求電文名
                      char       *request       // (O) 生成した要求電文 (XML)
                    )
{
	sprintf( request,
             XML_STATEMENT
             "<methodCall>\n<methodName>%s</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             serviceName,
             userName, password );

    return ( request );
}


/* 記事の生成 */
int
getNewEntryOnCousagi( const char *userName, // (I) ユーザ名
                      const char *password, // (I) パスワード
                      char       *title,    // (O) 生成した記事の題名
                      char       *body )    // (O) 生成した記事の本文
{
    int     ret = 0, res;
    char    *buffer;
    char    *result;
    char    petName[BUFSIZ];
    char    profile[BUFSIZ];

    petName[0] = NUL;
    profile[0] = NUL;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( BUFSIZ * 2 );
    if ( !buffer )
        return ( ret );
    result = (char *)malloc( MAX_CONTENT_SIZE * 2 );
    if ( !result ) {
        free( buffer );
        return ( ret );
    }
    memset( buffer, 0x00, BUFSIZ * 2 );
    memset( result, 0x00, MAX_CONTENT_SIZE * 2 );

#ifdef  OLD_FASHIONED
    setTargetURL( APIURL_COUSAGI );
    setRequestForCousagi( userName, password, "cousagi.getNewEntry", buffer );
#else
    setTargetURL( "http://api.blogpet.net/api/api.php" );
    setRequestForCousagi( userName, password, "blogpet.getEntry", buffer );
#endif

    res = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, result );

    if ( (res == 0) || (result[0] != NUL) ) {
        /*
         * String   title
         * String   body
         */
        char    *p = result;
        char    *q = strstr( p, "<struct>" );
        char    *r, *s, *t;
        int     cnt = 0;

        if ( q ) {
            q += 8;
            while ( *q ) {
                r = strstr( q, "<name>Title</name>" );
                if ( !r )
                    r = strstr( q, "<name>title</name>" );
                if ( r ) {
                    s = strstr( r + 18, "<string>" );
                    if ( s ) {
                        s += 8;
                        t = strstr( s, "</string>" );
                        strncpy( title, s, t - s );
                        title[t - s] = NUL;
                        q = t + 9;
                        cnt++;
#ifdef  OLD_FASHIONED
                        if ( cnt >= 2 )
#else
                        if ( cnt >= 4 )
#endif
                            break;
                        continue;
                    }
                }

                r = strstr( q, "<name>Body</name>" );
                if ( !r )
                    r = strstr( q, "<name>body</name>" );
                if ( r ) {
                    s = strstr( r + 17, "<string>" );
                    if ( s ) {
                        s += 8;
                        t = strstr( s, "</string>" );

                        /* なぜか title に本文、body に題名が入っている    */
                        /* (2006年8月29日現在)ため、以下の暫定対処を入れる */
                        if ( !strstr( title, "(BlogPet)" ) ) {
                            strcpy( body, title );

                            strncpy( title, s, t - s );
                            title[t - s] = NUL;
                        }
                        else {
                            strncpy( body, s, t - s );
                            body[t - s] = NUL;
                        }
                        decodeString( body );
                        regulerizeString( body );
                        q = t + 9;
                        cnt++;
#ifdef  OLD_FASHIONED
                        if ( cnt >= 2 )
#else
                        if ( cnt >= 4 )
#endif
                            break;
                        continue;
                    }
                }

#ifndef OLD_FASHIONED
                r = strstr( q, "<name>petname</name>" );
                if ( r ) {
                    s = strstr( r + 20, "<string>" );
                    if ( s ) {
                        s += 8;
                        t = strstr( s, "</string>" );
                        strncpy( petName, s, t - s );
                        petName[t - s] = NUL;
                     // decodeString( petName );
                        q = t + 9;
                        cnt++;
                        if ( cnt >= 4 )
                            break;
                        continue;
                    }
                }

                r = strstr( q, "<name>profile</name>" );
                if ( r ) {
                    s = strstr( r + 20, "<string>" );
                    if ( s ) {
                        s += 8;
                        t = strstr( s, "</string>" );
                        strncpy( profile, s, t - s );
                        profile[t - s] = NUL;
                     // decodeString( profile );
                        q = t + 9;
                        cnt++;
                        if ( cnt >= 4 )
                            break;
                        continue;
                    }
                }
#endif
                q++;
            }
        }

        ret = 1;
    }


    if ( body[0] && petName[0] && profile[0] ) {
        sprintf( body + strlen( body ),
                 "<p>%s ",
                 sjis2utf( "*このエントリは" ) );
        sprintf( body + strlen( body ),
                 "<a href=\"http://www.blogpet.net/\">BlogPet</a>"
                 " %s <a href=\"%s\">%s</a> ",
                 sjis2utf( "の" ), profile, petName );
        sprintf( body + strlen( body ),
                 "%s</p>",
                 sjis2utf( "が書きました。" ) );
    }

    free( result );
    free( buffer );

    return ( ret );
}


/* 発言の生成 */
int
getNewPhraseOnCousagi( const char *userName,    // (I) ユーザ名
                       const char *password,    // (I) パスワード
                       char       *response )   // (O) 生成した発言
{
    int     ret = 0, res;
    char    *buffer;
    char    *result;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( BUFSIZ * 2 );
    if ( !buffer )
        return ( ret );
    result = (char *)malloc( BUFSIZ * 2 );
    if ( !result ) {
        free( buffer );
        return ( ret );
    }
    memset( buffer, 0x00, BUFSIZ * 2 );
    memset( result, 0x00, BUFSIZ * 2 );

    setTargetURL( APIURL_COUSAGI );
    setRequestForCousagi( userName, password, "cousagi.getNewPhrase", buffer);

    res = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, result );

    if ( (res == 0) || (result[0] != NUL) ) {
        /*
         * String   phrase
         */
        getSingleString( result, response );
        ret = 1;
    }

    free( result );
    free( buffer );

    return ( ret );
}


/* 俳句の詠唱 */
int
getNewHaikuOnCousagi( const char *userName, // (I) ユーザ名
                      const char *password, // (I) パスワード
                      char       *response )// (O) 生成した俳句
{
    int     ret = 0, res;
    char    *buffer;
    char    *result;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( BUFSIZ * 2 );
    if ( !buffer )
        return ( ret );
    result = (char *)malloc( BUFSIZ * 2 );
    if ( !result ) {
        free( buffer );
        return ( ret );
    }
    memset( buffer, 0x00, BUFSIZ * 2 );
    memset( result, 0x00, BUFSIZ * 2 );

    setTargetURL( APIURL_COUSAGI );
    setRequestForCousagi( userName, password, "cousagi.getNewHaiku", buffer );

    res = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, result );

    if ( (res == 0) || (result[0] != NUL) ) {
        /*
         * String   haiku
         */
        getSingleString( result, response );
        ret = 1;
    }

    free( result );
    free( buffer );

    return ( ret );
}


/* 寝言の生成 */
int
getNewWhisperOnCousagi( const char *userName,
                        const char *password,
                        char       *response )
{
    int     ret = 0, res;
    char    *buffer;
    char    *result;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( BUFSIZ * 2 );
    if ( !buffer )
        return ( ret );
    result = (char *)malloc( BUFSIZ * 2 );
    if ( !result ) {
        free( buffer );
        return ( ret );
    }
    memset( buffer, 0x00, BUFSIZ * 2 );
    memset( result, 0x00, BUFSIZ * 2 );

    setTargetURL( APIURL_COUSAGI );
    setRequestForCousagi( userName, password, "cousagi.getNewWhisper",buffer);

    res = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, result );

    if ( (res == 0) || (result[0] != NUL) ) {
        /*
         * String   whisper
         */
        getSingleString( result, response );
        ret = 1;
    }

    free( result );
    free( buffer );

    return ( ret );
}


/* XHTML valid な形式になるようタグを付加 */
char    *
regulerizeString( char *src )   // (I/O) 正規化したい文字列/正規化済みの文字列
{
    char    *tmp1;
    char    *tmp2;
    char    *p, *q;

    tmp1 = (char *)malloc( MAX_CONTENT_SIZE * 2 );
    if ( !tmp1 )
        return ( NULL );
    tmp2 = (char *)malloc( MAX_CONTENT_SIZE * 2 );
    if ( !tmp2 ) {
        free( tmp1 );
        return ( NULL );
    }
    memset( tmp1, 0x00, MAX_CONTENT_SIZE * 2 );
    memset( tmp2, 0x00, MAX_CONTENT_SIZE * 2 );

    sprintf( tmp1, "<p>%s</p>", src );

    p = tmp1;
    while ( ( ( q = strstr( p, "<blockquote>" ) ) != NULL ) ||
            ( ( q = strstr( p, "<BLOCKQUOTE>" ) ) != NULL )    ) {
        p = q;
        sprintf( tmp2, "</p><blockquote><p>%s", q + 12 );
        strcpy( q, tmp2 );
        p += 19;
        if ( ( ( q = strstr( p, "</blockquote>" ) ) != NULL ) ||
             ( ( q = strstr( p, "</BLOCKQUOTE>" ) ) != NULL )    ) {
            p = q;
            sprintf( tmp2, "</p></blockquote><p>%s", q + 13 );
            strcpy( q, tmp2 );
            p += 20;
        }
    }

    p = tmp1;
    while ( *p ) {
        if ( (*p == '\r') && (*(p + 1) == '\n') ) {
            sprintf( tmp2, "<br />%s", p + 2 );
            strcpy( p, tmp2 );
            p += 5;
        }
        else if ( (*p == '\r') || (*p == '\n') ) {
            sprintf( tmp2, "<br />%s", p + 1 );
            strcpy( p, tmp2 );
        }
        p++;
    }

    strcpy( src, tmp1 );

    free( tmp2 );
    free( tmp1 );

    return ( src );
}


/* 生成した記事に俳句を埋め込む (おまけAPI) */
char    *
insertHaikuIntoEntry( char       *body,         // (I/O) 記事本文
                      const char *haiku,        // (I) 俳句
                      const char *cousagiName,  // (I) BlogPet の名前
                      int        blogPetType )  // (I) BlogPet の種別
{
    char    *tmp;
    char    *p, *q, *r;
    int     len = strlen( body ) + 
                    ((haiku && *haiku) ? strlen( haiku ) : 0) +
                    BUFSIZ;
    const char  *target1 =
    "*このエントリは、<a href=\"http://cousagi.yomiusa.net/\">こうさぎ</a>の";
    const char  *target2 =
      "*このエントリは、<a href=\"http://www.blogpet.net/\">BlogPet</a>の";

    tmp = (char *)malloc( len );
    if ( tmp ) {
        p = strstr( body, target1 );
        if ( !p )
            p = strstr( body, target2 );
        if ( p ) {
            if ( haiku && *haiku ) {
                memset( tmp, 0x00, len );
                strncpy( tmp, body, p - body );
                tmp[p - body] = '\0';
                sprintf( tmp + strlen( tmp ),
                         "</p><p>ここで一句、</p>"
                         "<blockquote><p>「%s」</p>"
                         "<cite>― %s %s、心の俳句</cite>"
                         "</blockquote><p>%s",
                         haiku, 
                         blogPetTypeString( blogPetType ),
                         cousagiName, p );
                strcpy( body, tmp );
                p = strstr( body, target1 );
                if ( !p )
                    p = strstr( body, target2 );
            }
        }

        if ( p && !strncmp( p, target1, strlen( target1 ) ) ) {
            q = strchr( p, '"' );
            r = strchr( q + 1, '"' );
            strcpy( q + 1, "http://www.blogpet.net/" );
            strcat( q + 1, r );
            p = strstr( body, "*このエントリは、" );
        }

        if ( p ) {
            q = strchr( p, '>' );
            r = strstr( p, "「" );

            if ( q ) {
                q++;
                memset( tmp, 0x00, len );
                strncpy( tmp, body, q - body );
                tmp[q - body] = '\0';
                strcat( tmp, blogPetTypeString( blogPetType ) );

                q = strchr( q, '<' );
                if ( q && r && ( q < r ) ) {
                    r += 2;
                    len = strlen( tmp );
                    strncat( tmp, q, r - q );
                    tmp[len + (r - q)] = NUL;

                    strcat( tmp, cousagiName );

                    r = strstr( r, "」" );
                    if ( r )
                        strcat( tmp, r );
                }
                else if ( q )
                    strcat( tmp, q );

                strcpy( body, tmp );
            }
        }

        free( tmp );
    }

    return ( body );
}


/*
 * Blog Pet 種別を文字列で返す
 */
char    *
blogPetTypeString( int blogPetType )
{
    char    *p;

    switch ( blogPetType ) {
    case BPTYPE_COUSAGI:
        p = "こうさぎ";
        break;
    case BPTYPE_CONEKO:
        p = "こねこ";
        break;
    case BPTYPE_COINU:
        p = "こいぬ";
        break;
    case BPTYPE_COPANDA:
        p = "こぱんだ";
        break;
    case BPTYPE_CONEZUMI:
        p = "こねずみ";
        break;
    case BPTYPE_UNKNOWN:
    default:
        p = "Blog Pet";
        break;
    }

    return ( p );
}
