/*
 *  atom API
 *
 * History:
 * $Log: /comm/xmlRPC/atomApi.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 51    09/03/30 22:54 Tsujimura543
 * getNonce() を追加
 * 
 * 50    09/03/20 22:25 Tsujimura543
 * 「はてなダイアリー」の Atom API に対応
 * 
 * 49    08/11/17 21:37 Tsujimura543
 * static char → Thread static char に変更
 * 
 * 48    08/11/17 21:29 Tsujimura543
 * バッファオーバーフロー対策を強化
 * 
 * 47    07/12/05 23:19 Tsujimura543
 * unbase64() の引数追加に伴う修正を実施
 * 
 * 46    07/03/06 0:33 Tsujimura543
 * バッファオーバーラン対策を実施
 * 
 * 45    07/03/03 15:29 Tsujimura543
 * utf2sjis() が NULL を返す場合の対策を実施
 * 
 * 44    06/09/14 19:34 Tsujimura543
 * Vox の「blog一覧取得」、「記事の投稿」に対応した
 * (Atom API による カテゴリ一覧の取得、記事一覧の取得、記事の編集、
 *  記事の削除はまだ実装されてない模様)
 * 
 * 43    06/09/11 11:52 Tsujimura543
 * ソースコードを整理
 * 
 * 42a   06/09/10 5:46 tsupo
 * Visual Studio 2005 でビルドしたときに出る warning に基づいた修正を実施
 * 
 * 42    06/09/07 23:59 Tsujimura543
 * コメントを追加
 * 
 * 41    06/09/07 23:55 Tsujimura543
 * editEntryOnAtomAPI() にも postEntryOnAtomAPI() 同様の修正を実施
 * 
 * 40    06/09/07 23:51 Tsujimura543
 * postEntryOnAtomAPI() を修正。再び、blogger.com に投稿できるようになった
 * ことを確認。
 * 
 * 39    06/09/07 15:06 Tsujimura543
 * postEntryOnAtomAPI() は、blogger への GData API 導入後、blogger への
 * 投稿ができなくなっている。GData API 対応の処理を別途作成する必要あり
 * → GData API 対応(は、将来行なうとして)をしなくても、
 *      (1) entry 要素の属性の追加、
 *      (2) genarator 要素の属性の変更、
 *      (3) blogger:draft 要素の app:draft 要素への変更
 *    にて、再び投稿できるようになった (revision 40, 41 での修正)
 * 
 * 38    06/09/06 17:04 Tsujimura543
 * getContentInfo() を修正し、アメーバブログの記事IDも取れるようにした
 * 
 * 37    06/07/24 20:10 Tsujimura543
 * _httpExecute() のバッファオーバーラン防止機能を利用するようにした
 * 
 * 36    06/01/26 14:51 Tsujimura543
 * アメーバブログの Atom API に暫定対応
 * 
 * 35    06/01/23 14:41 Tsujimura543
 * listPostsOnAtomAPI() で convertLineBreaks の値を取得できるようにした
 * 
 * 34    05/11/17 21:31 Tsujimura543
 * http による送信可能な電文サイズの上限をメモリの許す限りどこまでも
 * 大きくできるようにした (初期サイズは従来の値)
 * 
 * 33    05/10/18 17:48 Tsujimura543
 * httpGetBASIC() の引数追加に伴う修正を実施
 * 
 * 32    05/08/17 15:10 Tsujimura543
 * postEntryOnAtomAPI() と editEntryOnAtomAPI() に引数を追加し、
 * 下書き投稿可能とした (対象は blogger.com のみ)
 * 
 * 31    05/07/19 19:02 Tsujimura543
 * listCategoriesOnAtomAPI() を So-net blog 向けに fix
 * 
 * 30    05/07/19 14:52 Tsujimura543
 * So-net 特有の諸々に対応 (動作確認完了)
 * 
 * 29    05/07/19 11:17 Tsujimura543
 * So-net blog 対応
 * 
 * 28    05/06/29 9:48 Tsujimura543
 * getBlogIDsOnAtomAPI() を blogger.com にも対応するよう修正
 * 
 * 27    05/06/28 22:16 Tsujimura543
 * editEntryOnAtomAPI() を追加、動作確認済み
 * 
 * 26    05/06/28 21:47 Tsujimura543
 * postEntryOnAtomAPI() の blogger.com に対する動作確認完了
 * 
 * 25    05/06/28 21:32 Tsujimura543
 * deletePostOnAtomAPI() の blogger.com に対する動作確認完了
 * 
 * 24    05/06/28 20:21 Tsujimura543
 * postEntryOnAtomAPI() と detelePostOnAtomAPI() を bloggers.com 対応化
 * (動作確認中)
 * 
 * 23    05/06/28 17:05 Tsujimura543
 * listPostsOnAtomAPI() と getContentInfo() を bloggers.com にも対応させた
 * 
 * 22    05/06/28 15:56 Tsujimura543
 * listWeblogsOnAtomAPI() を blogger.com の BASIC認証 + SSL に対応させて
 * みた(動作確認 OK)
 * 
 * 21    05/06/21 13:29 Tsujimura543
 * listWeblogsOnAtomAPI() 内で使用する受信電文格納領域のサイズを
 * 増やしてみる (将来に備える)
 * 
 * 20    05/06/20 20:36 Tsujimura543
 * ココログで、過去記事の取得、新規記事の投稿、過去記事の削除、カテゴリ一覧
 * の取得などの動作を確認した (TypePad 1.5 関連)
 * 
 * 19    05/06/20 20:30 Tsujimura543
 * getContentInfo() で処理中の content が base64 エンコードされている場合は、
 * デコードするようにした
 * 
 * 18    05/06/20 20:10 Tsujimura543
 * getContentInfo() を TypePad 1.5 でも問題なく動くように修正
 * 
 * 17    05/06/20 15:44 Tsujimura543
 * TypePad 1.5 が livedoor Blog と同じ WSSE 生成方式にも対応したことを確認
 * 
 * 16    05/05/30 20:32 Tsujimura543
 * はてなブックマーク対応
 * 
 * 15    04/11/01 21:01 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 14    04/10/15 13:36 Tsujimura543
 * (1) getEndpointURLbyAutoDiscoveryOnAtomAPI() を追加
 * (2) getBlogIDsOnAtomAPI() を修正
 * 
 * 13    04/10/05 16:13 Tsujimura543
 * postEntryOnAtomAPI() に mode="base64" での投稿処理を追加 
 * 
 * 12    04/08/20 19:05 Tsujimura543
 * バッファオーバラン対策を実施
 * 
 * 11    04/08/19 16:23 Tsujimura543
 * サーバから取得した XML データを無条件で標準出力に吐き出していたのを抑止
 * (verbose モードのときのみ出力するようにした)
 * 
 * 10    04/08/19 9:05 Tsujimura543
 * LOVELOG 対応
 * 
 * 9     04/08/13 15:02 Tsujimura543
 * getRecentPostTitlesOnAtomAPI() を追加
 * 
 * 8     04/08/12 21:17 Tsujimura543
 * getBlogIDsOnAtomAPI() を追加
 * 
 * 7     04/07/16 19:55 Tsujimura543
 * Nonce の生成パターンをより複雑化した
 * 
 * 6     04/07/16 19:19 Tsujimura543
 * postEntryOnAtomAPI() に引数を追加し、概要を指定できるようにした
 * 
 * 5     04/07/16 17:22 Tsujimura543
 * escaped モードでの投稿に対応
 * 
 * 4     04/07/16 13:57 Tsujimura543
 * Atom API 関連、全面見直し。XML-RPC API 関連関数との整合を図る。
 * 
 * 3     04/07/09 20:30 Tsujimura543
 * livedoor Blog の Atom API 対応
 * 
 * 2     04/07/07 11:58 Tsujimura543
 * RCS による版数管理から VSS による版数管理に移行
 */

#include "xmlRPC.h"
#include "atomApi.h"
#include "md5.h"
#include <time.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/atomApi.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char    *
makeCreated( time_t t )
{
    Thread static char  buf[64];
    struct tm           *tm;
    
    if ( t == 0 ) {
        time_t  tt = time( NULL );
        tm = gmtime( &tt );
    }
    else
        tm = gmtime( &t );  /* GMT */

    sprintf( buf, "%04d-%02d-%02dT%02d:%02d:%02dZ",
             tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
             tm->tm_hour, tm->tm_min, tm->tm_sec );

    return ( buf );
}

char    *
makeNonce( const char *preNonce, int blogKind )
{
    static unsigned long    ll = 20040426;
    static unsigned long    mm = 3784786237;
    Thread static char      buf[48] = { 0x00, };
    Thread static char      pre[48];
    time_t                  t = time( NULL );
    int                     r1, r2, r3, r4, r5;

    if ( preNonce )
        strcpy( pre, preNonce );
    else
        strcpy( pre, buf );

    if ( buf[0] == 0x00 )
        srand( (unsigned int)t );
    do {
        r1 = rand();
        r2 = rand();
        r3 = rand();
        r4 = rand();
        r5 = rand();

        switch ( blogKind ) {
        case BLOGKIND_MOVABLETYPE:      /* Movable Type   */
        case BLOGKIND_TYPEPAD:          /* TypePad        */
        case BLOGKIND_COCOLOG:          /* ココログ       */
        case BLOGKIND_BLOGZINE:         /* BLOGZINE       */
        case BLOGKIND_TYPEPADJAPAN:     /* TypePad Japan  */
        case BLOGKIND_TYPEPADFRANCE:    /* TypePad France */
#if 0   /* MovableType 3.16 および TypePad 1.5 では livedoor Blog と同じ */
        /* WSSE 生成方式でも通るようになった                             */
            sprintf( buf, "%04x%02x%08x%04x%02x%02x%08x%04x%04x%02x",
                     r4 % (128 * 256),
                     t % 256,
                     ll,
                     r1 % (128 * 256),
                     (t / 256) % 256,
                     r3 % 256,
                     mm,
                     r2 % (128 * 256),
                     r5 % (128 * 256),
                     (r3 / 256) % 256 );
            break;
#endif
        case BLOGKIND_BLOGGER:          /* Blogger                */
        case BLOGKIND_LIVEDOOR:         /* livedoor Blog          */
        case BLOGKIND_LOVELOG:          /* LOVELOG                */
        case BLOGKIND_SONET:            /* So-net blog            */
        case BLOGKIND_AMEBLO:           /* アメーバブログ         */
        case BLOGKIND_ATOMAPI:          /* Atom API サポート blog */
        case BLOGKIND_HATENA:   /* はてなブックマーク または はてなFOTOLIFE */
        default:
            switch ( r4 % 3 ) {
            case 0:
                sprintf( buf, "%04x%02x%08x%04x%02x",
                         r4 % (128 * 256),
                         t % 256,
                         ll,
                         r1 % (128 * 256),
                         (t / 256) % 256 );
                break;
            case 1:
                sprintf( buf, "%04x%08x%02x%04x%02x",
                         r5 % (128 * 256),
                         r2,
                         t % 256,
                         r4 % (128 * 256),
                         (r3 / 256) % 256 );
                break;
            case 2:
                sprintf( buf, "%04x%02x%02x%04x%02x%06x",
                         r3 % (128 * 256),
                         r1 % 256,
                         (r4 / 256) % 256,
                         r2 % (128 * 256),
                         t % 256,
                         r5 % 0x00FFFFFF );
                break;
            }
            break;
        }

        if ( ll == (unsigned long)0xFFFF )
            ll = 0;
        else
            ll++;

        if ( mm == (unsigned long)0xFFFF )
            mm = 0;
        else
            mm++;
    } while ( !strcmp( pre, buf ) );

    return ( buf );
}

char    *
getNonce( const char *preNonce )
{
    return ( makeNonce( preNonce, BLOGKIND_UNKNOWN ) );
}

char    *
makePasswordDigest(
        const char *nonce,
        const char *created,
        const char *password,
        int        blogKind )
{
    const char  *p, *q, *r;
    char        *s, *t;
    char        buf[BUFSIZ];

    p = nonce;
    if ( !nonce )
        p = makeNonce( NULL, blogKind );

    q = created;
    if ( !created ) {
        time_t  t = time( NULL );
        q = makeCreated( t );
    }

    r = password;
    if ( !password ) {
        if ( xmlrpc_p )
            xmlrpc_p->password;
        else
            return ( NULL );
    }

    if ( blogKind == BLOGKIND_AMEBLO ) {
        /* アメーバブログの場合 */
        strcpy( buf, nonce );
        strcat( buf, created );
        strcat( buf, MD5(password) );
    }
    else {
        strcpy( buf, nonce );
        strcat( buf, created );
        strcat( buf, password );
    }
    s = (char *)sha1( (unsigned char *)buf );
    if ( s )
        t = base64( (unsigned char *)s, 20 );
    else
        t = NULL;

    return ( t );
}

char    *
makeWSSE( const char *username, const char *password, char *buffer,
          int blogKind )
{
    char    *nonce;
    char    *created;
    char    *passwordDigest;
    char    buf[BUFSIZ];

    if ( !username )
        username = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    /*
     * TypePad での例
     *  X-WSSE: UsernameToken Username="Melody",
     *  PasswordDigest="VfJavTaTy3BhKkeY/WVu9L6cdVA=",
     *  Created="2004-01-20T01:09:39Z",
     *  Nonce="7c19aeed85b93d35ba42e357f10ca19bf314d622"
     *
     * livedoor Blog での例
     *  X-WSSE: UsernameToken Username="tsupo",
     *  PasswordDigest="hXtbxblQ1fcH+ZRkNew0awHD8WM=",
     *  Nonce="Cc9EjFjsp7s1UPn+l2sMZeRtjHY=",
     *  Created="2004-07-08T02:04:10Z"
     *
     */

    nonce   = makeNonce( NULL, blogKind );
    created = makeCreated( 0L );
    passwordDigest = makePasswordDigest( nonce, created, password, blogKind );

    switch ( blogKind ) {
    case BLOGKIND_MOVABLETYPE:      /* Movable Type    */
    case BLOGKIND_TYPEPAD:          /* TypePad         */
    case BLOGKIND_COCOLOG:          /* ココログ        */
    case BLOGKIND_BLOGZINE:         /* BLOGZINE        */
    case BLOGKIND_TYPEPADJAPAN:     /* TypePad Japan   */
    case BLOGKIND_TYPEPADFRANCE:    /* TypePad France  */
    case BLOGKIND_TYPEPADGERMANY:   /* TypePad Germany */
#if 0   /* MovableType 3.16 および TypePad 1.5 では livedoor Blog と同じ */
        /* WSSE 生成方式でも通るようになった                             */
	    sprintf( buffer,
                 "UsernameToken Username=\"%s\", PasswordDigest=\"%s\", "
                 "Created=\"%s\", Nonce=\"%s\"",
		         username, passwordDigest, created, nonce );
        break;
#endif
    case BLOGKIND_BLOGGER:          /* Blogger                */
    case BLOGKIND_LIVEDOOR:         /* livedoor Blog          */
    case BLOGKIND_LOVELOG:          /* LOVELOG                */
    case BLOGKIND_SONET:            /* So-net blog            */
    case BLOGKIND_AMEBLO:           /* アメーバブログ         */
    case BLOGKIND_ATOMAPI:          /* Atom API サポート blog */
    case BLOGKIND_HATENA:   /* はてなブックマーク または はてなFOTOLIFE */
    case BLOGKIND_HATENADIARY:      /* はてなダイアリー       */
    default:
        strcpy( buf, passwordDigest );
	    sprintf( buffer,
                 "UsernameToken Username=\"%s\", PasswordDigest=\"%s\", "
                 "Nonce=\"%s\", Created=\"%s\"",
		         username, buf,
                 base64( (unsigned char *)nonce, strlen(nonce) ),
                 created );
        break;
    }

    return ( buffer );
}


/* 記事情報の抽出 */
int
getContentInfo( char         **p,
                CONTENTINFEX *contentInfo,
                CATLISTINFEX *categoryInfo,
                long         numOfPosts,
                long         *numOfCats )
{
    char    *q, *r;
    char    *s;
    int     ret = 1; /* 0: fall into, 1: continue, 2: break */
    char    category[MAX_CATNAMELENGTH];

    if ( !strncmp( *p, "<title>", 7 ) ||
         !strncmp( *p, "<title ", 7 )    ) {
        q = strchr( *p, '>' );
        if ( q )
            *p = q + 1;
        if ( ( q = strstr( *p, "</title>" ) ) != NULL ) {
            size_t  len = min( q - *p, MAX_LOGICALLINELEN - 1 );
            strncpy( contentInfo[numOfPosts].title, *p, len );
            contentInfo[numOfPosts].title[len] = NUL;
            (*p) = q + 8;
            return ( ret ); /* continue */
        }
    }

    q = NULL;
    if ( (contentInfo[numOfPosts].link[0] == NUL) &&
         (!strncmp(*p,
                   "<link rel=\"alternate\" type=\"text/html\" href=\"",
                   45 )                                                 ||
          (!strncmp( *p, "<link ", 6 )                               &&
           ((q = strstr(*p + 6, " rel=\"alternate\"")) != NULL)&&
           (((r = strstr(*p + 6," rel=\"service.edit\"")) == NULL)||
            (q < r)                                                 )  )  )) {
        s = *p;
        if ( q )
            (*p)  = (q + 23);
        else
            (*p) += 45;
        q = strstr( s, "href=\"" );
        if ( q ) {
            q += 6;
            r = strchr( q, '"' );
            if ( r ) {
                size_t  len = min( r - q, MAX_URLLENGTH - 1 );
                strncpy( contentInfo[numOfPosts].link, q, len );
                contentInfo[numOfPosts].link[len] = NUL;
                strcpy( contentInfo[numOfPosts].permaLink,
                        contentInfo[numOfPosts].link );
                (*p) = r + 1;
                return ( ret ); /* continue */
            }
        }
    }

    q = NULL;
    if ( !strncmp( *p, "<link rel=\"service.edit\"", 24 )               ||
         (!strncmp( *p, "<link ", 6 )                               &&
          ((q = strstr( *p + 6, " rel=\"service.edit\"" )) != NULL)    )   ) {
        s = *p;
        if ( q )
            (*p)  = (q + 19);
        else
            (*p) += 24;
        if ( ( q = strstr( *p, "entry_id=" ) ) != NULL ) {
            q += 9;
            r = strchr( q, '"' );
            if ( r ) {
                size_t  len = min( r - q, MAX_POSTIDLENGTH - 1 );
                strncpy( contentInfo[numOfPosts].postid, q, len );
                contentInfo[numOfPosts].postid[len] = NUL;
                (*p) = r + 1;
                return ( ret ); /* continue */
            }
        }
        else {
            /* for Blogger.com */
            q = strstr( s, "href=\"https://www.blogger.com/atom/" );
            if ( q )
                q += 35;
            else {
                /* for So-net blog, アメーバブログ */
                q = strstr( s, "/_atom/blog/" );
                if ( q )
                    q += 12;
            }
            if ( q ) {
                r = strchr( q, '/' );
                if ( r ) {
                    r++;
                    q = strchr( r, '"' );
                    if ( q ) {
                        size_t  len = min( q - r, MAX_POSTIDLENGTH - 1 );
                        strncpy( contentInfo[numOfPosts].postid, r, len );
                        contentInfo[numOfPosts].postid[len] = NUL;
                        (*p) = q + 1;
                        return ( ret ); /* continue */
                    }
                }
            }
        }
    }
    if ( !strncmp( *p, "<id ", 3 ) &&
         ((q = strstr( *p, "tag:vox.com," )) != NULL) ) {
        /* for Vox */
        (*p) = q + 12;
        q = strstr( *p, ":asset-" );
        if ( q ) {
            q += 7;
            r = strstr( q, "</id>" );
            if ( r ) {
                size_t  len = min( r - q, MAX_POSTIDLENGTH - 1 );
                strncpy( contentInfo[numOfPosts].postid, q, len );
                contentInfo[numOfPosts].postid[len] = NUL;
                (*p) = r + 5;
                return ( ret ); /* continue */
            }
        }
    }
    if ( !strncmp( *p, "<id>", 3 ) &&
         ((q = strstr( *p, "tag:d.hatena.ne.jp," )) != NULL) ) {
        /* for はてなダイアリー */
        (*p) = q + 19;
        q = strstr( *p, ":diary-" );
        if ( q ) {
            char    date[MAX_POSTIDLENGTH];
            char    entryID[MAX_POSTIDLENGTH];

            q += 7;
            r = strchr( q, '-' );
            if ( r ) {
                q = r + 1;
                r = strchr( q, '-' );
                if ( r ) {
                    strncpy( date, q, r - q );
                    date[r - q] = NUL;

                    q = r + 1;
                    r = strstr( q, "</id>" );
                    if ( r ) {
                        strncpy( entryID, q, r - q );
                        entryID[r - q] = NUL;
                        sprintf( contentInfo[numOfPosts].postid, "%s/%s", date, entryID );

                        (*p) = r + 5;
                        return ( ret ); /* continue */
                    }
                }
            }
        }
    }

    if ( !strncmp( *p, "<dc:subject>", 12 ) ) {
        (*p) += 12;
        if ( ( q = strstr( *p, "</dc:subject>" ) ) != NULL ) {
            if ( *numOfCats < MAX_CATEGORIES ) {
                size_t  len;

                r = categoryInfo[numOfPosts].categoryName[*numOfCats];
                len = min( q - *p, MAX_CATNAMELENGTH - 1);
                strncpy( r, *p, len );
                r[len] = NUL;
                (*numOfCats)++;
                categoryInfo[numOfPosts].numberOfCategories = *numOfCats;
            }
            else {
                r = utf2sjis( category );
                fprintf( stderr, "category: %s\n",
                         r ? r : category );
            }
            (*p) = q + 13;
            return ( ret ); /* continue */
        }
    }

    if ( !strncmp( *p, "<summary ", 9 ) ) {
        (*p) += 9;
        q = strchr( *p, '>' );
        if ( q && *q ) {
            q++;
            if ( ( r = strstr( q, "</summary>" ) ) != NULL ) {
                size_t  len = min( r - q, MAX_CONTENT_SIZE - 1 );
                strncpy( contentInfo[numOfPosts].mt_excerpt, q, len );
                contentInfo[numOfPosts].mt_excerpt[len] = NUL;
                (*p) = r + 10;
                return ( ret ); /* continue */
            }
        }
    }

    if ( !strncmp( *p, "<content ", 9 ) ) {
        (*p) += 9;
        q = strchr( *p, '>' );
        r = strstr( *p, "mode=\"base64\"" );
        if ( q && *q ) {
            int base64Mode = FALSE;
            if ( r && ( r < q ) )
                base64Mode = TRUE;
            q++;
            if ( ( r = strstr( q, "</content>" ) ) != NULL ) {
                char    *s = strstr( q, "<![CDATA[" );

                if ( !s ) {
                    size_t  len = min( r - q, MAX_CONTENT_SIZE - 1 );

                    if ( base64Mode == FALSE ) {
                        strncpy( contentInfo[numOfPosts].description,
                                 q, len );
                        contentInfo[numOfPosts].description[len] = NUL;
                    }
                    else {
                        char    tmp[MAX_CONTENT_SIZE];
                        size_t  sz = 0;

                        strncpy( tmp, q, len );
                        tmp[len] = NUL;
                        unbase64( (unsigned char *)tmp,
                                  (unsigned char *)
                                      (contentInfo[numOfPosts].description),
                                  &sz );
                    }
                }
                else {
                    size_t  len;
                    char    *t = strstr( s, "]]>" );

                    s += 9;
                    while( (*s == '\r') || (*s == '\n') )
                        s++;
                    len = min( t - s, MAX_CONTENT_SIZE - 1 );
                    strncpy( contentInfo[numOfPosts].description,
                             s, len );
                    contentInfo[numOfPosts].description[len] = NUL;
                }
                (*p) = r + 10;
                return ( ret ); /* continue */
            }
        }
    }

    if ( !strncmp( *p, "<issued>", 8 ) ||
         !strncmp( *p, "<issued ", 8 )    ) {
        int yy, mm, dd, HH, MM, SS;

        q = strchr( *p, '>' );
        if ( q )
            *p = q + 1;
        yy = ((((*p)[0] - '0')  * 10 +
               ((*p)[1] - '0')) * 10 +
               ((*p)[2] - '0')) * 10 +
               ((*p)[3] - '0');
        (*p) += 4;
        if ( *(*p) == '-' )
            (*p)++;
        mm = ((*p)[0] - '0') * 10 + ((*p)[1] - '0');
        (*p) += 2;
        if ( *(*p) == '-' )
            (*p)++;
        dd = ((*p)[0] - '0') * 10 + ((*p)[1] - '0');
        (*p) += 2;
        while ( *(*p) && ((*(*p) < '0') || (*(*p) > '9')) )
            (*p)++;
        HH = ((*p)[0] - '0') * 10 + ((*p)[1] - '0');
        (*p) += 2;
        if ( *(*p) == ':' )
            (*p)++;
        MM = ((*p)[0] - '0') * 10 + ((*p)[1] - '0');
        (*p) += 2;
        if ( *(*p) == ':' )
            (*p)++;
        SS = ((*p)[0] - '0') * 10 + ((*p)[1] - '0');
        q = strstr( *p, "</issued>" );
        if ( q )
            (*p) = q + 9;
        else
            (*p) += 2;

        contentInfo[numOfPosts].yy = yy;
        contentInfo[numOfPosts].mm = mm;
        contentInfo[numOfPosts].dd = dd;
        contentInfo[numOfPosts].HH = HH;
        contentInfo[numOfPosts].MM = MM;
        contentInfo[numOfPosts].SS = SS;

        return ( ret ); /* continue */
    }

    ret = 0;
    return ( ret ); /* fall into ... */
}


/* Listing the User's Weblogs */
int     
listWeblogsOnAtomAPI( const char      *username,    // (I) ユーザ名
                      const char      *password,    // (I) パスワード
                      long            *numOfUrls,   // (I) 取得するURL情報数
                                                    // (O) 取得したURL情報数
                      ATOM_URL_INFO_t urlInfo       // (O) 取得したURL情報
                    )
{
    int     ret = FALSE;
    char    buffer[BUFSIZ];
    char    *response;
    long    num = 0;
    char    *p, *q;
    size_t  sz;

    if ( !numOfUrls || (*numOfUrls <= 0) || !urlInfo )
        return ( num );

    sz = (*numOfUrls * BUFSIZ) + BUFSIZ * 2;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    memset( buffer, NUL, BUFSIZ );
    setUpReceiveBuffer( response, sz );

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_BLOGGER:  /* Blogger      */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        ret = httpGetBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                            username, password,
                            response, NULL, FALSE,
                            NULL, NULL, NULL,
                            NULL, NULL );
        break;

    default:                /* Blogger 以外 */
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        ret = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                         response, NULL, FALSE,
                         buffer );
        break;
    }

    if ( response[0] != NUL ) {
        p = response;
        while ( *p ) {
            if ( num >= *numOfUrls )
                break;

            if ( xmlrpc_p->blogKind == BLOGKIND_HATENADIARY ) {
                // はてなダイアリーだけ特別扱い
                while ( (*p == ' ')  || (*p == '\t') ||
                        (*p == '\r') || (*p == '\n')    )
                    p++;

                if ( !strncmp( p, "<title>", 7 ) ) {
                    p += 7;
                    q = strstr( p, "</title>" );
                    if ( q ) {
                        strncpy( urlInfo[num].title, p, q - p );
                        urlInfo[num].title[q - p] = NUL;
                        sprintf( urlInfo[num].url,
                                 "http://d.hatena.ne.jp/%s/",
                                 username );
                        strcpy( urlInfo[num].urlType, "feed" );
                        num++;
                    }
                    break;
                }
                
                p++;
                continue;
            }

            if ( !strncmp( p, "<link ", 6 ) ) {
                p += 6;
                while ( *p ) {
                    if ( !strncmp( p, "rel=\"", 5 ) ) {
                        p += 5;
                        q = strchr( p, '"' );
                        if ( q ) {
                            size_t  len = min( q - p, MAX_TYPELENGTH - 1 );
                            strncpy( urlInfo[num].urlType, p, len );
                            urlInfo[num].urlType[len] = NUL;
                            p = q + 1;
                            continue;
                        }
                    }

                    if ( !strncmp( p, "href=\"", 6 ) ) {
                        p += 6;
                        q = strchr( p, '"' );
                        if ( q ) {
                            size_t  len = min( q - p, MAX_URLLENGTH - 1 );
                            strncpy( urlInfo[num].url, p, len );
                            urlInfo[num].url[len] = NUL;
                            p = q + 1;
                            continue;
                        }
                    }

                    if ( !strncmp( p, "type=\"", 6 ) ) {
                        p += 6;
                        q = strchr( p, '"' );
                        if ( q ) {
                            size_t  len = min( q - p, MAX_TYPELENGTH - 1 );
                            strncpy( urlInfo[num].mimeType, p, len );
                            urlInfo[num].mimeType[len] = NUL;
                            p = q + 1;
                            continue;
                        }
                    }

                    if ( !strncmp( p, "title=\"", 7 ) ) {
                        p += 7;
                        q = strchr( p, '"' );
                        if ( q ) {
                            size_t  len = min(q - p, MAX_LOGICALLINELEN - 1);
                            strncpy( urlInfo[num].title, p, len );
                            urlInfo[num].title[len] = NUL;
                            p = q + 1;
                            continue;
                        }
                    }

                    if ( *p == '>' ) {
                        num++;
                        break;
                    }
                    p++;
                }
            }
            p++;
        }
    }

    free( response );
    *numOfUrls = num;

    return ( num );
}


/* Listing the Posts in a Weblog */
int     
listPostsOnAtomAPI(
        const char   *username,             // (I) ユーザ名
        const char   *password,             // (I) パスワード
        const char   *blogID,               // (I) blog ID
        int          *numOfRecentEntries,   // (I) 取得する記事情報数
                                            // (O) 取得した記事情報数
        CONTENTINFEX *contentInfo,          // (O) 取得した記事情報
        CATLISTINFEX *categoryInfo          // (O) 取得したカテゴリ情報
    )
{
    int     ret = FALSE, r;
    char    buffer[BUFSIZ];
    char    *response;
    char    target[BUFSIZ];
    char    *p, *q;
    long    numOfPosts = 0;
    long    numOfCats  = 0;
    int     first = 1;
    BOOL    convertLineBreaks = TRUE; /* とりあえず、default は TRUE とする */
    size_t  sz;

    if ( !blogID                              ||
         !(*blogID)                           ||
         (strlen(blogID) >= MAX_BLOGIDLENGTH) ||
         !numOfRecentEntries                  ||
         (*numOfRecentEntries <= 0)           ||
         !contentInfo                         ||
         !categoryInfo                           )
        return ( numOfPosts );

    sz = *numOfRecentEntries * 128 * 1024;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfPosts );

    memset( buffer, NUL, BUFSIZ );
    setUpReceiveBuffer( response, sz );

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_BLOGGER:  /* Blogger      */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        sprintf( target, "%s/%s", xmlrpc_p->webPage, blogID );
        ret = httpGetBASIC( xmlrpc_p->webServer, target,
                            username, password,
                            response, NULL, FALSE,
                            NULL, NULL, NULL,
                            NULL, NULL );
        break;

    case BLOGKIND_SONET:    /* So-net         */
    case BLOGKIND_AMEBLO:   /* アメーバブログ */
        sprintf( target, "%s/%s", xmlrpc_p->webPage, blogID );
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        ret = httpGetEx( xmlrpc_p->webServer, target,
                         response, NULL, FALSE,
                         buffer );
        break;

    case BLOGKIND_VOX:      /* Vox */
        sprintf( target, "%s/svc=post/collection_id=%s",
                 xmlrpc_p->webPage, blogID );
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        ret = httpGetEx( xmlrpc_p->webServer, target,
                         response, NULL, FALSE,
                         buffer );
        break;  /* 2006年89月14日現在、501 Not Implrmented が返ってくる */

    case BLOGKIND_HATENADIARY:  /* はてなダイアリー */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        sprintf( target, "/%s/atom/blog", username );
        ret = httpGetEx( xmlrpc_p->webServer, target,
                         response, NULL, FALSE,
                         buffer );
        break;

    default:                /* 上記以外     */
        sprintf( target, "%s/blog_id=%s", xmlrpc_p->webPage, blogID );
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        ret = httpGetEx( xmlrpc_p->webServer, target,
                         response, NULL, FALSE,
                         buffer );
        break;
    }

    if ( response[0] != NUL ) {
        p = response;
        while ( *p ) {
            if ( first ) {
                if ( !strncmp( p, "<title", 6 ) ) {
                    /* for So-net blog */
                    q = strstr( p, "</title>" );
                    if ( q )
                        p = q + 1;
                    else
                        p += 6;
                    continue;
                }

                if ( !strncmp( p, "<convertLineBreaks ", 19 ) ) {
                    /* for Bloggers.com */
                    q = strchr( p, '>' );
                    if ( q ) {
                        char    *r;

                        p = q + 1;
                        q = strchr( p, '<' );
                        if ( q ) {
                            r = p;
                            while ( *r && (r < q) ) {
                                if ( !strncmp( r, "true", 4 ) ) {
                                    convertLineBreaks = TRUE;
                                    break;
                                }
                                if ( !strncmp( r, "false", 5 ) ) {
                                    convertLineBreaks = FALSE;
                                    break;
                                }
                                r++;
                            }
                            p = q - 1;
                        }
                    }
                }

                if ( !strncmp( p, "<entry>", 7 ) ||
                     !strncmp( p, "<entry ", 7 )    ) {
                    first = 0;
                    contentInfo[numOfPosts].description[0] = NUL;
                    contentInfo[numOfPosts].title[0]       = NUL;
                    contentInfo[numOfPosts].postid[0]      = NUL;
                    contentInfo[numOfPosts].link[0]        = NUL;
                    contentInfo[numOfPosts].permaLink[0]   = NUL;
                    contentInfo[numOfPosts].mt_excerpt[0]  = NUL;
                    strcpy( contentInfo[numOfPosts].mt_convert_breaks,
                            (convertLineBreaks == TRUE) ? "1" : "0" );
                }
                p++;
                if ( *p ) {
                    q = strchr( p, '<' );
                    if ( q )
                        p = q;
                }
                continue;
            }

            r = getContentInfo( &p, contentInfo, categoryInfo,
                                numOfPosts, &numOfCats );
            if ( r == 1 )
                continue;

            if ( !strncmp( p, "</entry>", 8 ) ) {
                p += 8;
                numOfPosts++;
                if ( numOfPosts >= *numOfRecentEntries )
                    break;
                numOfCats = 0;
                continue;
            }

            p++;
            if ( *p ) {
                q = strchr( p, '<' );
                if ( q )
                    p = q;
            }
        }
    }

    free( response );
    *numOfRecentEntries = numOfPosts;

    return ( numOfPosts );
}


/* Retrieving a list of categories */
int
listCategoriesOnAtomAPI(
        const char   *username,         // (I) ユーザ名
        const char   *password,         // (I) パスワード
        const char   *blogID,           // (I) blog ID
        long         *numOfCategories,  // (I) 取得するカテゴリの数
                                        // (O) 取得したカテゴリの数
        CATLISTINF_t categories         // (O) 取得したカテゴリ情報
    )
{
    int     ret = FALSE;
    char    buffer[BUFSIZ];
    char    *response;
    char    target[BUFSIZ];
    long    num = 0;
    char    *p, *q;
    size_t  sz;

    if ( !blogID                                ||
         !(*blogID)                             ||
         (strlen( blogID ) >= MAX_BLOGIDLENGTH) ||
         !numOfCategories                       ||
         (*numOfCategories <= 0)                ||
         !categories                               )
        return ( num );

    if ( (xmlrpc_p->blogKind == BLOGKIND_BLOGGER) ||
         (xmlrpc_p->blogKind == BLOGKIND_SONET)   ||
         (xmlrpc_p->blogKind == BLOGKIND_AMEBLO)  ||
         (xmlrpc_p->blogKind == BLOGKIND_VOX )       )
        return ( num ); /* Blogger.com には「カテゴリ」の概念がない */
        /* アメーバブログでカテゴリを取得しようとすると、期待しているものと */
        /* は別のものが返ってくるので、とりあえず当分の間、何もせずに即座に */
        /* リターンするようにしておく。                                     */
    sz = (*numOfCategories * BUFSIZ) / 4 + BUFSIZ * 2 + MAX_CONTENT_SIZE;
    response = (char *)malloc( sz);
    if ( !response )
        return ( num );

    memset( buffer, NUL, BUFSIZ );
    makeWSSE( username, password, buffer, xmlrpc_p->blogKind );

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_SONET:    /* So-net         */
    case BLOGKIND_AMEBLO:   /* アメーバブログ */
        sprintf( target, "%s/%s/svc=categories",
                 xmlrpc_p->webPage, blogID );
        break;  /* 2005年7月19日現在、So-net では「カテゴリ」関連の API は */
                /* 未サポート   (2006年9月11日時点でも未サポートのまま。ア */
                /* メーバブログでも「カテゴリ」の取得・登録はできない)     */
    case BLOGKIND_VOX:      /* Vox */
        sprintf( target, "%s/svc=categories/collection_id=%s",
                 xmlrpc_p->webPage, blogID );
        break;  /* Vox もカテゴリの設定・取得は未対応の模様(記事の投稿時は */
                /* デフォルト[=moblog投稿時]のカテゴリ(タグ)が設定される)  */
    default:                /* それ以外 */
        sprintf( target, "%s/blog_id=%s/svc=categories",
                 xmlrpc_p->webPage, blogID );
        break;
    }

    setUpReceiveBuffer( response, sz );
    ret = httpGetEx( xmlrpc_p->webServer, target,
                     response, NULL, FALSE,
                     buffer );

    if ( response[0] != NUL ) {
        p = response;
        while ( *p ) {
            if ( num >= *numOfCategories )
                break;
            if ( !strncmp( p, "<subject", 8 ) ) {
                p = strchr( p + 8, '>' );
                if ( p && (*++p) ) {
                    q = strchr( p, '<' );
                    if ( q ) {
                        size_t  len = min( q - p, MAX_CATNAMELENGTH - 1 );
                        strncpy( categories[num].categoryName, p, len );
                        categories[num].categoryName[len] = NUL;
                        num++;
                        p = q + 1;
                    }
                }
            }
            p++;
        }
    }

    free( response );
    *numOfCategories = num;

    return ( num );
}


/* Retrieving a Post */
BOOL
getRecentPostOnAtomAPI(
        const char   *username,     // (I) ユーザ名
        const char   *password,     // (I) パスワード
        const char   *blogID,       // (I) blog ID
        const char   *entryID,      // (I) 記事ID
        CONTENTINFEX *contentInfo,  // (O) 取得した記事情報
        CATLISTINFEX *categoryInfo  // (O) 取得したカテゴリ情報
    )
{
    int     ret = FALSE, r;
    char    buffer[BUFSIZ];
    char    *response;
    char    target[BUFSIZ];
    char    *p, *q;
    long    numOfPosts = 0;
    long    numOfCats  = 0;
    int     first      = 1;
    size_t  sz;

    if ( !blogID                               ||
         !(*blogID)                            ||
         (strlen(blogID) >= MAX_BLOGIDLENGTH)  ||
         !entryID                              ||
         !(*entryID)                           ||
         (strlen(entryID) >= MAX_POSTIDLENGTH) ||
         !contentInfo                          ||
         !categoryInfo                            )
        return ( ret );

    sz = 128 * 1024;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    memset( buffer, NUL, BUFSIZ );
    setUpReceiveBuffer( response, sz );

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_BLOGGER:  /* Blogger      */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        sprintf( target, "%s/%s/%s", xmlrpc_p->webPage, blogID, entryID );
        r = httpGetBASIC( xmlrpc_p->webServer, target,
                          username, password,
                          response, NULL, FALSE,
                          NULL, NULL, NULL,
                          NULL, NULL );
        break;

    case BLOGKIND_SONET:    /* So-net         */
    case BLOGKIND_AMEBLO:   /* アメーバブログ */
#if 0
        /* So-net blog は entryID を指定しての記事取得は未サポート */
        sprintf( target, "%s/%s/%s",
                 xmlrpc_p->webPage, blogID, entryID );
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        r = httpGetEx( xmlrpc_p->webServer, target,
                       response, NULL, FALSE,
                       buffer );
#else
        /* 記事を20個づつ取得して、その中から entryID に一致する記事を */
        /* 拾い出す                                                    */
        {
            long    numOfContent = 20;
            int     j = 0;

            do {
                sprintf( target, "%s/%s/offset=%d",
                         xmlrpc_p->webPage, blogID, j );
                makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
                setUpReceiveBuffer( response, sz );
                r = httpGetEx( xmlrpc_p->webServer, target,
                               response, NULL, FALSE,
                               buffer );
                if ( *response ) {
                    if ( ( p = strstr( response, entryID ) ) != NULL ) {
                        if ( *(p - 1) == '/' ) {
                            while ( *p > *response ) {
                                if ( !strncmp( p, "<entry>", 7 ) )
                                    break;
                                p--;
                            }
                            if ( !strncmp( p, "<entry>", 7 ) )
                                strcpy( response, p );
                            break;
                        }
                    }
                }
                j += numOfContent;
            } while ( *response && strstr( response, "<entry>" ) );
        }
#endif
        break;

    case BLOGKIND_VOX:      /* Vox */
        sprintf( target, "%s/collection_id=%s/post_id=%s",
                 xmlrpc_p->webPage, blogID, entryID );
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        r = httpGetEx( xmlrpc_p->webServer, target,
                       response, NULL, FALSE,
                       buffer );
        break;

    case BLOGKIND_HATENADIARY:  /* はてなダイアリー */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        sprintf( target, "/%s/atom/blog/%s", username, entryID );
        // http://d.hatena.ne.jp/{はてなID}/atom/blog/{date}/{entry_id}
        // entryID := {date}/{entry_id}
        r = httpGetEx( xmlrpc_p->webServer, target,
                       response, NULL, FALSE,
                       buffer );
        break;

    default:                /* 上記以外     */
        sprintf( target, "%s/blog_id=%s/entry_id=%s",
                 xmlrpc_p->webPage, blogID, entryID );
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        r = httpGetEx( xmlrpc_p->webServer, target,
                       response, NULL, FALSE,
                       buffer );
        break;
    }

    if ( response[0] != NUL ) {
        p = response;
        while ( *p ) {
            if ( first ) {
                if ( !strncmp( p, "<entry>", 7 ) ||
                     !strncmp( p, "<entry ", 7 )    ) {
                    first = 0;
                    contentInfo[numOfPosts].description[0] = NUL;
                    contentInfo[numOfPosts].title[0]       = NUL;
                    contentInfo[numOfPosts].postid[0]      = NUL;
                    contentInfo[numOfPosts].link[0]        = NUL;
                    contentInfo[numOfPosts].permaLink[0]   = NUL;
                    contentInfo[numOfPosts].mt_excerpt[0]  = NUL;
                }
                p++;
                if ( *p ) {
                    q = strchr( p, '<' );
                    if ( q )
                        p = q;
                }
                continue;
            }

            r = getContentInfo( &p, contentInfo, categoryInfo,
                                numOfPosts, &numOfCats );
            if ( r == 1 )
                continue;

            if ( !strncmp( p, "</entry>", 8 ) )
                break;

            p++;
            if ( *p ) {
                q = strchr( p, '<' );
                if ( q )
                    p = q;
            }
        }

        ret = TRUE;
    }

    free( response );

    return ( ret );
}


/* Deleting a Post */
BOOL
deletePostOnAtomAPI( const char *username,  // (I) ユーザ名
                     const char *password,  // (I) パスワード
                     const char *blogID,    // (I) blog ID
                     const char *entryID )  // (I) 記事ID
{
    int     ret = FALSE;
    char    buffer[BUFSIZ];
    char    *response;
    char    target[BUFSIZ];
    size_t  sz;

    if ( !blogID                               ||
         !(*blogID)                            ||
         (strlen(blogID) >= MAX_BLOGIDLENGTH)  ||
         !entryID                              ||
         !(*entryID)                           ||
         (strlen(entryID) >= MAX_POSTIDLENGTH)    )
        return ( ret );

    memset( buffer, NUL, BUFSIZ );

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    setUpReceiveBuffer( response, sz );

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_BLOGGER:  /* Blogger */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        sprintf( target, "%s/%s/%s", xmlrpc_p->webPage, blogID, entryID );
        ret = httpDeleteBASIC( xmlrpc_p->webServer, target,
                               username, password,
                               response, NULL, FALSE,
                               NULL );
        break;

    case BLOGKIND_SONET:    /* So-net         */
    case BLOGKIND_AMEBLO:   /* アメーバブログ */
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        sprintf( target, "%s/%s/%s",
                 xmlrpc_p->webPage, blogID, entryID );
        ret = httpDeleteEx( xmlrpc_p->webServer, target,
                            response, NULL, FALSE,
                            buffer );
        break;

    case BLOGKIND_VOX:      /* Vox */
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        sprintf( target,
                 "%s/svc=post/collection_id=%s/entry_id=%s",
              // "%s/svc=post/collection_id=%s/post_id=%s",
                 xmlrpc_p->webPage, blogID, entryID );
        ret = httpDeleteEx( xmlrpc_p->webServer, target,
                            response, NULL, FALSE,
                            buffer );
        break;/* 2006年9月14日現在、「削除」はまだサポートされていない模様 */

    case BLOGKIND_HATENADIARY:  /* はてなダイアリー */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        sprintf( target, "/%s/atom/blog/%s", username, entryID );
        // http://d.hatena.ne.jp/{はてなID}/atom/blog/{date}/{entry_id}
        // entryID := {date}/{entry_id}
        ret = httpDeleteEx( xmlrpc_p->webServer, target,
                            response, NULL, FALSE,
                            buffer );
        break;

    default:                /* 上記以外 */
        makeWSSE( username, password, buffer, xmlrpc_p->blogKind );
        sprintf( target, "%s/blog_id=%s/entry_id=%s",
                 xmlrpc_p->webPage, blogID, entryID );
        ret = httpDeleteEx( xmlrpc_p->webServer, target,
                            response, NULL, FALSE,
                            buffer );
        break;
    }

    if ( response[0] != NUL ) {
        ret = TRUE;
    }
    free( response );

    return ( ret );
}



/* Posting an entry */
int
postEntryOnAtomAPI(
        const char         *username,       // (I) ユーザID
        const char         *password,       // (I) パスワード
        const char         *blogID,         // (I) blog ID
        const char         *title,          // (I) 題名
        const char         *summary,        // (I) 概要
        const char         *content,        // (I) 本文
        const CATLISTINFEX *categoryInfo,   // (I) 設定するカテゴリ
        BOOL               publish,// (I) 投稿状態 (FALSE: 下書き, TRUE: 公開)
                                   //  -- 現時点では、blogger.com でのみ有効
        char               *postID          // (O) 投稿後の記事ID
    )
{
    int     ret = FALSE, i, r;
    char    wsse[BUFSIZ];
    char    *request;
    char    *response;
    char    *tmp;
    char    target[BUFSIZ];
    int     len;
    char    *mode;
    size_t  sz;

    if ( !blogID                                                ||
         !(*blogID)                                             ||
         (strlen(blogID) >= MAX_BLOGIDLENGTH)                   ||
         !title                                                 ||
         !(*title)                                              ||
         (strlen(title) >= MAX_LOGICALLINELEN)                  ||
         !content                                               ||
         !(*content)                                            ||
         (strlen(content) >=
                (size_t)(xmlrpc_p->sndHTTPBufferSize - BUFSIZ)) ||
         !categoryInfo                                          ||
         !postID                                                   )
        return ( ret );

    len = strlen( content ) * 16 + 1 +
              ( categoryInfo->numberOfCategories * BUFSIZ ) / 4 + BUFSIZ * 2;
    if ( summary && *summary )
        len += (strlen( summary ) * 5);

    request  = (char *)malloc( len );
    if ( !request )
        return ( ret );

    sz = MAX_CONTENT_SIZE * 4;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    tmp = (char *)malloc( strlen( content ) * 16 + 1 );
    if ( !tmp )
        return ( ret );
    if ( strstr( content, "<p>" ) != NULL ) {
        if ( xmlrpc_p->blogKind == BLOGKIND_LIVEDOOR ) {
            /* http://blog.livedoor.com/spec_atom_api.html に書いてあること */
            /* に準拠するため、base64 を使うようにする (escaped や xml でも */
            /* 投稿できることは確認してある)                                */
            sprintf( tmp, "%s",
                     base64( (unsigned char *)content, strlen(content) ) );
            mode = "base64";
        }
        else if ( xmlrpc_p->blogKind == BLOGKIND_BLOGGER ) {
            /* Blogger.com の場合 */
            sprintf( tmp,
                     "<div xmlns=\"http://www.w3.org/1999/xhtml\">%s</div>",
                     content );
            mode = "xml";
        }
        else {
            sprintf( tmp, "<![CDATA[\n%s]]>", content );
            mode = "escaped";
        }
    }
    else if ( (xmlrpc_p->blogKind == BLOGKIND_SONET)  ||
              (xmlrpc_p->blogKind == BLOGKIND_AMEBLO)    ) {
        /* So-net blog の場合 */
        encodeString( content, tmp );
        mode = "escaped";
    }
    else {
        strcpy( tmp, "<div xmlns=\"http://www.w3.org/1999/xhtml\">" );
        encodeString( content, tmp + strlen(tmp) );
        strcat( tmp, "</div>" );
        mode = "xml";
    }
    if ( strlen( tmp ) >= (size_t)(xmlrpc_p->sndHTTPBufferSize - BUFSIZ) ) {
        free( tmp );
        free( request );
        free( response );
        return ( ret );
    }

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_BLOGGER:  /* Blogger      */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        sprintf( request,
          "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\r\n"
#if 0
          "<entry xmlns=\"http://purl.org/atom/ns#\">\r\n"
#else
          "<entry xmlns=\"http://purl.org/atom/ns#\" "
          "xmlns:app=\"http://purl.org/atom/app#\">\r\n"
          "<generator version=\"1.0\" uri=\"http://www.na.rim.or.jp/"
          "~tsupo/makeRSS\">tsupo client</generator>\r\n"
#endif
               );
        sprintf( request + strlen(request),
                 "<title mode=\"escaped\" type=\"text/plain\">%s</title>\r\n",
                 title );
        // <issued>2004-04-12T06:07:20Z</issued>
        // ↑ issued は必須ではない (省略可)

     /* 以下は、将来対応とする
        sprintf( request + strlen(request),
            "<convertLineBreaks xmlns=\"http://www.blogger.com/atom/ns#\">%s"
            "</convertLineBreaks>\n",
            convertLineBreaks == TRUE ? "true" : "false" );
      */

#if 0
        sprintf( request + strlen(request),
                 "<content type=\"application/xhtml+xml\">\r\n"
                 "%s\r\n"
                 "</content>\r\n"
                 "<blogger:draft>%s</blogger:draft>\r\n"
                 "</entry>\r\n",// ← blogegr.com では、最後の改行は必須!!
                 tmp,           //   (改行がないと Mulformed xml エラーになる)
                 publish == TRUE ? "false" /* 下書き */
                                 : "true"  /* 公開   */ );
#else
        sprintf( request + strlen(request),
                 "<content type=\"application/xhtml+xml\">\r\n"
                 "%s\r\n"
                 "</content>\r\n"
                 "<app:control>\r\n"
                 "<app:draft>%s</app:draft>\r\n"
                 "</app:control>\r\n"
                 "</entry>\r\n",// ← blogegr.com では、最後の改行は必須!!
                 tmp,           //   (改行がないと Mulformed xml エラーになる)
                 publish == TRUE ? "no"  /* 下書き */
                                 : "yes" /* 公開   */
               );
#endif
        break;

    default:                /* Blogger 以外 */
        sprintf( request,
		         XML_STATEMENT
                 "<entry xmlns=\"http://purl.org/atom/ns#\" "
                 "xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n"
                 "<title>%s</title>\n",
                 title );

        /* 注意: Blogger.com には「カテゴリ」の概念がない */
        for ( i = 0; i < categoryInfo->numberOfCategories; i++ ) {
            sprintf( request + strlen(request),
                     "<dc:subject>%s</dc:subject>\n",
                     categoryInfo->categoryName[i] );
        }

        if ( summary && *summary )
            sprintf( request + strlen(request),
                     "<summary type=\"text/plain\">%s</summary>\n",
                     summary );
        sprintf( request + strlen(request),
                 "<content type=\"application/xhtml+xml\" mode=\"%s\">"
                 "%s"
                 "</content>\n"
                 "</entry>\n",
                 mode, tmp );
        break;
    }

    free( tmp );
    tmp = NULL;

    setUpReceiveBuffer( response, sz );

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_BLOGGER:  /* Blogger */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        sprintf( target, "%s/%s", xmlrpc_p->webPage, blogID );
        r = httpPostBASIC( xmlrpc_p->webServer, target,
                           username, password,
                           "application/atom+xml",
                           request, response );
        break;

    case BLOGKIND_SONET:    /* So-net         */
    case BLOGKIND_AMEBLO:   /* アメーバブログ */
        makeWSSE( username, password, wsse, xmlrpc_p->blogKind );
        sprintf( target, "%s/%s",
                 xmlrpc_p->webPage, blogID );
        r = httpPostEx2( xmlrpc_p->webServer, target,
                         request, response,
                         wsse );
        break;

    case BLOGKIND_VOX:      /* Vox */
        makeWSSE( username, password, wsse, xmlrpc_p->blogKind );
        sprintf( target, "%s/svc=post/collection_id=%s",
                 xmlrpc_p->webPage, blogID );
        r = httpPostEx2( xmlrpc_p->webServer, target,
                         request, response,
                         wsse );
        break;

    case BLOGKIND_HATENADIARY:  /* はてなダイアリー */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        makeWSSE( username, password, wsse, xmlrpc_p->blogKind );
        sprintf( target, "/%s/atom/blog", username );
        r = httpPostEx2( xmlrpc_p->webServer, target,
                         request, response,
                         wsse );
        break;

    default:                /* 上記以外 */
        makeWSSE( username, password, wsse, xmlrpc_p->blogKind );
        sprintf( target, "%s/blog_id=%s",
                 xmlrpc_p->webPage, blogID );
        r = httpPostEx2( xmlrpc_p->webServer, target,
                         request, response,
                         wsse );
        break;
    }

    if ( response[0] != NUL ) {
        CONTENTINFEX    *contentInf;
        CATLISTINFEX    *categoryInf;
        char            *p, *q;
        int             r;
        long            numOfPosts = 0;
        long            numOfCats  = 0;
        int             first = 1;

        contentInf  = (CONTENTINFEX *)malloc( sizeof ( CONTENTINFEX ) );
        if ( !contentInf ) {
            free( request );
            free( response );
            return ( ret );
        }

        categoryInf = (CATLISTINFEX *)malloc( sizeof ( CATLISTINFEX ) );
        if ( !categoryInf ) {
            free( contentInf );
            free( request );
            free( response );
            return ( ret );
        }

        contentInf->postid[0] = NUL;
        categoryInf->numberOfCategories = categoryInfo->numberOfCategories;

        p = response;
        while ( *p ) {
            if ( first ) {
                if ( !strncmp( p, "<entry>", 7 ) ||
                     !strncmp( p, "<entry ", 7 )    ) {
                    first = 0;
                    contentInf[numOfPosts].description[0] = NUL;
                    contentInf[numOfPosts].title[0]       = NUL;
                    contentInf[numOfPosts].postid[0]      = NUL;
                    contentInf[numOfPosts].link[0]        = NUL;
                    contentInf[numOfPosts].permaLink[0]   = NUL;
                    contentInf[numOfPosts].mt_excerpt[0]  = NUL;
                }
                p++;
                if ( *p && (*p != '<') ) {
                    q = strchr( p, '<' );
                    if ( q )
                        p = q;
                }
                continue;
            }

            r = getContentInfo( &p, contentInf, categoryInf,
                                numOfPosts, &numOfCats );
            if ( r == 1 )
                continue;

            if ( !strncmp( p, "</entry>", 8 ) )
                break;

            p++;
            if ( *p && (*p != '<') ) {
                q = strchr( p, '<' );
                if ( q )
                    p = q;
            }
        }

        if ( contentInf->postid[0] ) {
            strcpy( postID, contentInf->postid );
            ret = TRUE;
        }

        free( categoryInf );
        free( contentInf );
    }

    free( response );
    free( request );

    return ( ret );
}


/* Editing an entry */
int
editEntryOnAtomAPI(
        const char         *username,       // (I) ユーザID
        const char         *password,       // (I) パスワード
        const char         *blogID,         // (I) blog ID
        const char         *title,          // (I) 題名
        const char         *summary,        // (I) 概要
        const char         *content,        // (I) 本文
        const CATLISTINFEX *categoryInfo,   // (I) 設定するカテゴリ
        BOOL               publish,// (I) 投稿状態 (FALSE: 下書き, TRUE: 公開)
                                   //  -- 現時点では、blogger.com でのみ有効
        const char         *postID          // (I) 編集対象の記事ID
    )
{
    int     ret = FALSE, i, r;
    char    wsse[BUFSIZ];
    char    *request;
    char    *response;
    char    *tmp;
    char    target[BUFSIZ];
    int     len;
    char    *mode;

    if ( !blogID                                                ||
         !(*blogID)                                             ||
         (strlen(blogID) >= MAX_BLOGIDLENGTH)                   ||
         !title                                                 ||
         !(*title)                                              ||
         (strlen(title) >= MAX_LOGICALLINELEN)                  ||
         !content                                               ||
         !(*content)                                            ||
         (strlen(content) >=
                (size_t)(xmlrpc_p->sndHTTPBufferSize - BUFSIZ)) ||
         !categoryInfo                                          ||
         !postID                                                   )
        return ( ret );

    len = strlen( content ) * 5 + 1 +
              ( categoryInfo->numberOfCategories * BUFSIZ ) / 4 + BUFSIZ * 2;
    if ( summary && *summary )
        len += (strlen( summary ) * 5);

    request  = (char *)malloc( len );
    if ( !request )
        return ( ret );

    response = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !response )
        return ( ret );

    tmp = (char *)malloc( strlen( content ) * 5 + 1 );
    if ( !tmp )
        return ( ret );
    if ( strstr( content, "<p>" ) != NULL ) {
        if ( xmlrpc_p->blogKind == BLOGKIND_LIVEDOOR ) {
            /* http://blog.livedoor.com/spec_atom_api.html に書いてあること */
            /* に準拠するため、base64 を使うようにする (escaped や xml でも */
            /* 投稿できることは確認してある)                                */
            sprintf( tmp, "%s",
                     base64( (unsigned char *)content, strlen(content) ) );
            mode = "base64";
        }
        else if ( xmlrpc_p->blogKind == BLOGKIND_BLOGGER ) {
            /* Blogger.com の場合 */
            sprintf( tmp,
                     "<div xmlns=\"http://www.w3.org/1999/xhtml\">%s</div>",
                     content );
            mode = "xml";
        }
        else {
            sprintf( tmp, "<![CDATA[\n%s]]>", content );
            mode = "escaped";
        }
    }
    else if ( (xmlrpc_p->blogKind == BLOGKIND_SONET)  ||
              (xmlrpc_p->blogKind == BLOGKIND_AMEBLO)    ) {
        /* So-net blog の場合 */
        encodeString( content, tmp );
        mode = "escaped";
    }
    else {
        strcpy( tmp, "<div xmlns=\"http://www.w3.org/1999/xhtml\">" );
        encodeString( content, tmp + strlen(tmp) );
        strcat( tmp, "</div>" );
        mode = "xml";
    }
    if ( strlen( tmp ) >= (size_t)(xmlrpc_p->sndHTTPBufferSize - BUFSIZ) ) {
        free( tmp );
        free( request );
        free( response );
        return ( ret );
    }

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_BLOGGER:  /* Blogger      */
        sprintf( request,
          "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\r\n"
#if 0
          "<entry xmlns=\"http://purl.org/atom/ns#\">\r\n"
#else
          "<entry xmlns=\"http://purl.org/atom/ns#\" "
          "xmlns:app=\"http://purl.org/atom/app#\">\r\n"
          "<generator version=\"1.0\" uri=\"http://www.na.rim.or.jp/"
          "~tsupo/makeRSS\">tsupo client</generator>\r\n"
#endif
               );
        sprintf( request + strlen(request),
                 "<title mode=\"escaped\" type=\"text/plain\">%s</title>\r\n",
                 title );

        // <issued>2004-04-12T06:07:20Z</issued>
        // ↑ issued は必須ではない (省略可)

     /* 以下は、将来対応とする
        sprintf( request + strlen(request),
            "<convertLineBreaks xmlns=\"http://www.blogger.com/atom/ns#\">%s"
            "</convertLineBreaks>\n",
            convertLineBreaks == TRUE ? "true" : "false" );
      */
#if 0
        sprintf( request + strlen(request),
                 "<content type=\"application/xhtml+xml\">\n"
                 "%s\n"
                 "</content>\n"
                 "<blogger:draft>%s</blogger:draft>\n"
                 "</entry>\n",  // ← blogegr.com では、最後の改行は必須!!
                 tmp,           //   (改行がないと Mulformed xml エラーになる)
                 publish == TRUE ? "false" /* 下書き */
                                 : "true"  /* 公開   */ );
#else
        sprintf( request + strlen(request),
                 "<content type=\"application/xhtml+xml\">\r\n"
                 "%s\r\n"
                 "</content>\r\n"
                 "<app:control>\r\n"
                 "<app:draft>%s</app:draft>\r\n"
                 "</app:control>\r\n"
                 "</entry>\r\n",// ← blogegr.com では、最後の改行は必須!!
                 tmp,           //   (改行がないと Mulformed xml エラーになる)
                 publish == TRUE ? "no"  /* 下書き */
                                 : "yes" /* 公開   */
               );
#endif
        break;

    default:                /* Blogger 以外 */
        sprintf( request,
		         XML_STATEMENT
                 "<entry xmlns=\"http://purl.org/atom/ns#\" "
                 "xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n"
                 "<title>%s</title>\n",
                 title );

        /* 注意: Blogger.com には「カテゴリ」の概念がない */
        for ( i = 0; i < categoryInfo->numberOfCategories; i++ ) {
            sprintf( request + strlen(request),
                     "<dc:subject>%s</dc:subject>\n",
                     categoryInfo->categoryName[i] );
        }

        if ( summary && *summary )
            sprintf( request + strlen(request),
                     "<summary type=\"text/plain\">%s</summary>\n",
                     summary );
        sprintf( request + strlen(request),
                 "<content type=\"application/xhtml+xml\" mode=\"%s\">"
                 "%s"
                 "</content>\n"
                 "</entry>\n",
                 mode, tmp );
        break;
    }

    free( tmp );
    tmp = NULL;

    response[0] = NUL;

    switch ( xmlrpc_p->blogKind ) {
    case BLOGKIND_BLOGGER:  /* Blogger      */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        sprintf( target, "%s/%s/%s", xmlrpc_p->webPage, blogID, postID );
        r = httpPutBASIC( xmlrpc_p->webServer, target,
                          username, password,
                          "application/xml",
                          request, response,
                          NULL );
        break;

    case BLOGKIND_SONET:    /* So-net         */
    case BLOGKIND_AMEBLO:   /* アメーバブログ */
        makeWSSE( username, password, wsse, xmlrpc_p->blogKind );
        sprintf( target, "%s/%s/%s",
                 xmlrpc_p->webPage, blogID, postID );
        r = httpPutEx( xmlrpc_p->webServer, target,
                       request, response,
                       wsse );
        break;

    case BLOGKIND_VOX:      /* Vox */
        makeWSSE( username, password, wsse, xmlrpc_p->blogKind );
        sprintf( target,
              // "%s/svc=post/collection_id=%s/entry_id=%s",
              // "%s/svc=post/collection_id=%s/post_id=%s",
              // "%s/svc=edit/collection_id=%s/entry_id=%s",
                 "%s/svc=edit/collection_id=%s/post_id=%s",
                 xmlrpc_p->webPage, blogID, postID );
        r = httpPutEx( xmlrpc_p->webServer, target,
                       request, response,
                       wsse );  /* 2006年9月14日現在、Vox では Atom API に */
        break;                  /* よる「編集」は、 まだサポートされていな */
                                /* い模様                                  */

    case BLOGKIND_HATENADIARY:  /* はてなダイアリー */
        if ( !username )
            username = xmlrpc_p->userName;
        if ( !password )
            password = xmlrpc_p->password;
        makeWSSE( username, password, wsse, xmlrpc_p->blogKind );
        sprintf( target, "/%s/atom/blog/%s", username, postID );
        // http://d.hatena.ne.jp/{はてなID}/atom/blog/{date}/{entry_id}
        // postID := {date}/{entry_id}
        r = httpPutEx( xmlrpc_p->webServer, target,
                       request, response,
                       wsse );
        break;

    default:                /* 上記以外     */
        makeWSSE( username, password, wsse, xmlrpc_p->blogKind );
        sprintf( target, "%s/blog_id=%s/entry_id=%s",
                 xmlrpc_p->webPage, blogID, postID );
        r = httpPutEx( xmlrpc_p->webServer, target,
                       request, response,
                       wsse );
        break;
    }

    if ( response[0] != NUL ) {
        CONTENTINFEX    *contentInf;
        CATLISTINFEX    *categoryInf;
        char            *p, *q;
        int             r;
        long            numOfPosts = 0;
        long            numOfCats  = 0;
        int             first = 1;

        contentInf  = (CONTENTINFEX *)malloc( sizeof ( CONTENTINFEX ) );
        if ( !contentInf ) {
            free( request );
            free( response );
            return ( ret );
        }

        categoryInf = (CATLISTINFEX *)malloc( sizeof ( CATLISTINFEX ) );
        if ( !categoryInf ) {
            free( contentInf );
            free( request );
            free( response );
            return ( ret );
        }

        contentInf->postid[0] = NUL;
        categoryInf->numberOfCategories = categoryInfo->numberOfCategories;

        p = response;
        while ( *p ) {
            if ( first ) {
                if ( !strncmp( p, "<entry>", 7 ) ||
                     !strncmp( p, "<entry ", 7 )    ) {
                    first = 0;
                    contentInf[numOfPosts].description[0] = NUL;
                    contentInf[numOfPosts].title[0]       = NUL;
                    contentInf[numOfPosts].postid[0]      = NUL;
                    contentInf[numOfPosts].link[0]        = NUL;
                    contentInf[numOfPosts].permaLink[0]   = NUL;
                    contentInf[numOfPosts].mt_excerpt[0]  = NUL;
                }
                p++;
                if ( *p && (*p != '<') ) {
                    q = strchr( p, '<' );
                    if ( q )
                        p = q;
                }
                continue;
            }

            r = getContentInfo( &p, contentInf, categoryInf,
                                numOfPosts, &numOfCats );
            if ( r == 1 )
                continue;

            if ( !strncmp( p, "</entry>", 8 ) )
                break;

            p++;
            if ( *p && (*p != '<') ) {
                q = strchr( p, '<' );
                if ( q )
                    p = q;
            }
        }

        if ( contentInf->postid[0] ) {
         // strcpy( postID, contentInf->postid );
            ret = TRUE;
        }

        free( categoryInf );
        free( contentInf );
    }

    free( response );
    free( request );

    return ( ret );
}



/*
 *  ユーティリティ関数群
 */

/*
 * blog ID の取得
 *    引数:   ユーザ名, パスワード, 取得した blog 情報格納場所
 *    戻り値: システム内に存在する blog の数
 */

int
getBlogIDsOnAtomAPI(
        const char *userName,       // (I) ユーザ名
        const char *password,       // (I) パスワード
        int        *numberOfBlogs,  // (I/O) blog 情報数
        BLOGINF    *blogInfo        // (O) blog 情報
    )
{
    long            numOfInfo  = *numberOfBlogs;
    int             numOfBlogs = 0;
    ATOM_URL_INFO_t urlInfo;
    char            blogIDstr[MAX_BLOGIDLENGTH];
    int             i;

    if ( !numberOfBlogs        ||
         (*numberOfBlogs <= 0) ||
         !blogInfo                )
        return ( numOfBlogs );

    blogIDstr[0] = '\0';
    urlInfo =
        (ATOM_URL_INFO_t)malloc( sizeof ( ATOM_URL_INFO ) * *numberOfBlogs );
    if ( urlInfo ) {
        memset( urlInfo, 0x00, sizeof ( ATOM_URL_INFO ) * *numberOfBlogs );
        listWeblogsOnAtomAPI( userName, password, &numOfInfo, urlInfo );
        for ( i = 0; i < numOfInfo; i++ ) {
            if ( !strcmp( urlInfo[i].urlType, "service.post" ) ) {
                char  *p = strstr( urlInfo[i].url, "blog_id=" );
                if ( !p )
                    p = strstr( urlInfo[i].url, "collection_id=" );
                if ( p ) {
                 // p += 8;
                    p = strchr( p, '=' ) + 1;
                    strcpy( blogIDstr, p );
                }
                else {
                    /* for Blogger.com */
                    p = strrchr( urlInfo[i].url, '/' );
                    if ( p )
                        strcpy( blogIDstr, p + 1 );
                }
                strcpy( blogInfo[numOfBlogs].url, urlInfo[i].url );
                strcpy( blogInfo[numOfBlogs].blogID, blogIDstr );
                strcpy( blogInfo[numOfBlogs].blogName, urlInfo[i].title );
                numOfBlogs++;
            }
            else if ( !strcmp( urlInfo[i].urlType, "alternate" ) ) {
                int j;
                for ( j = 0; j < numOfBlogs; j++ ) {
                    if ( !strcmp( urlInfo[i].title, blogInfo[j].blogName ) ) {
                        strcpy( blogInfo[j].url, urlInfo[i].url );
                        break;
                    }
                }
            }
            else if ( !strcmp( urlInfo[i].urlType, "feed" ) ) {
                /* はてなダイアリー */
                strcpy( blogInfo[numOfBlogs].url, urlInfo[i].url );
                sprintf( blogInfo[numOfBlogs].blogID, "diary-%s", userName );
                strcpy( blogInfo[numOfBlogs].blogName, urlInfo[i].title );
                numOfBlogs++;
            }
        }
        free( (char *)urlInfo );
    }

    *numberOfBlogs = numOfBlogs;
    return ( numOfBlogs );
}


/*
 * 指定件数分の記事情報の取得
 *    引数:   blog ID, ユーザ名, パスワード, 取得する記事情報数,
 *            取得した記事情報格納場所
 *    戻り値: 取得した記事情報数
 *    備考:   getRecentPostTitles() の Atom API バージョン
 */
int
getRecentPostTitlesOnAtomAPI(
        const char *blogID,         // (I) blog ID
        const char *userName,       // (I) ユーザ名
        const char *password,       // (I) パスワード
        int        *numberOfPosts,  // (I/O) 記事情報数
        POSTINF    *postinf         // (O 記事情報
    )
{
    int             i;
    int             numOfPosts = 0;
    CONTENTINFEX    *contentInfo;
    CATLISTINFEX    *categoryInfo;

    if ( !blogID                                ||
         !(blogID[0])                           ||
         (strlen( blogID ) >= MAX_BLOGIDLENGTH) ||
         !numberOfPosts                         ||
         (*numberOfPosts <= 0)                  ||
         !postinf                                  )
        return ( numOfPosts );

    numOfPosts   = *numberOfPosts;
    contentInfo  =
        (CONTENTINFEX *)malloc( sizeof ( CONTENTINFEX ) * numOfPosts );
    if ( !contentInfo )
        return ( 0 );
    categoryInfo =
        (CATLISTINFEX *)malloc( sizeof ( CATLISTINFEX ) * numOfPosts );
    if ( !categoryInfo ) {
        free( (char *)contentInfo );
        return ( 0 );
    }

    listPostsOnAtomAPI( userName, password, blogID,
                        &numOfPosts, contentInfo, categoryInfo );

    for ( i = 0; i < numOfPosts; i++ ) {
        strcpy( postinf[i].postid, contentInfo[i].postid );
        strcpy( postinf[i].userid, contentInfo[i].userid );
        strcpy( postinf[i].title,  contentInfo[i].title );
        postinf[i].yy = contentInfo[i].yy;
        postinf[i].mm = contentInfo[i].mm;
        postinf[i].dd = contentInfo[i].dd;
        postinf[i].HH = contentInfo[i].HH;
        postinf[i].MM = contentInfo[i].MM;
        postinf[i].SS = contentInfo[i].SS;
    }

    free( (char *)categoryInfo );
    free( (char *)contentInfo );
    *numberOfPosts = numOfPosts;

    return ( numOfPosts );
}


/*
 * エンドポイントURLの取得
 *    引数:   トップページURL, 取得した blog ID の格納場所
 *    戻り値: 取得したエンドポイントURL
 *    備考:   getEndpointURLbyAutoDiscovery() の Atom API バージョン
 *            トップページの html head 部分に
 *               <link rel="alternate" type="application/atom+xml" ……
 *            という行があれば、当該行で指定されている Atom Feed ファイルを
 *            元に、エンドポイントURLを求める。
 *            当該行が存在しない場合は、トップページ直下に atom.xml という
 *            Atom Feed ファイルが存在するものと仮定し、atom.xml ファイル
 *            から、エンドポイントURLを求める。
 *            ただし、 Atom Feed ファイル中に
 *                <link rel="service.post" type="application/x.atom+xml" ……
 *            という行が存在しない場合は、エンドポイントURLの取得はできない。
 */
char    *
getEndpointURLbyAutoDiscoveryOnAtomAPI(
        const char *topPageURL, // (I) トップページ URL
        char       *blogID      // (O) blog ID
    )
{
    char                *buffer, *p, *q;
    int                 ret;
    Thread static char  endPointURL[MAX_URLLENGTH + 1];
    char                atomFeedURL[MAX_URLLENGTH + 1];
    size_t              sz;

    if ( !topPageURL || !(*topPageURL) )
        return ( NULL );

    memset( endPointURL, 0x00, MAX_URLLENGTH + 1 );
    memset( atomFeedURL, 0x00, MAX_URLLENGTH + 1 );

    sz = RCV_BUFFER_SIZE * 4;
    buffer = (char *)malloc( sz );
    if ( !buffer )
        return ( NULL );

    /* トップページを取得 */
    setUpReceiveBuffer( buffer, sz );
    ret = httpGetBuffer( topPageURL, buffer, FALSE );
    if ( (ret != -1) && (buffer[0] != NUL) ) {
        /* トップページから                                     */
        /*    <link rel="alternate" type="application/atom+xml" */
        /* な行を抜き出す                                       */
        p = strstr( buffer,
                    "<link rel=\"alternate\" type=\"application/atom+xml\"" );
        if ( p && ( ( q = strstr( p + 49, "href=\"" ) ) != NULL ) ) {
            /* Atom Feed の URL を取得 */
            p = q + 6;
            q = strchr( p, '"' );

            if ( q ) {
                size_t  len = min( q - p, MAX_URLLENGTH );
                strncpy( atomFeedURL, p, len );
                atomFeedURL[len] = NUL;
            }
        }

        if ( atomFeedURL[0] == NUL ) {
            /* Atom Feed の URL を トップページURL/atom.xml と仮定 */
            sprintf( atomFeedURL, "%s/atom.xml", topPageURL );
        }

        /* Atom Feed ファイルを取得 */
        setUpReceiveBuffer( buffer, sz );
        ret = httpGetBuffer( atomFeedURL, buffer, FALSE );
        if ( (ret != -1) && (buffer[0] != NUL) ) {
            /* Atom Feed ファイルから エンドポイントURL を抜き出す */
            p = strstr( buffer,
               "<link rel=\"service.post\" type=\"application/x.atom+xml\"" );
            if ( !p )
                p = strstr( buffer,
                  "<link rel=\"service.post\" type=\"application/atom+xml\"");
            if ( p && ( (q = strstr( p + /*54*/50, "href=\"") ) != NULL ) ) {
                /* エンドポイントURL を取得 */
                p = q + 6;
                q = strstr( p, "/blog_id=" );
                if ( !q )
                    q = strstr( p, "/collection_id=" );

                if ( q ) {
                    size_t  len = min( q - p, MAX_URLLENGTH );
                    strncpy( endPointURL, p, len );
                    endPointURL[len] = NUL;
                    p = strstr( endPointURL, "/svc=post" );
                    if ( p )
                        *p = NUL;

                    if ( blogID ) {
                        /* blog ID を取得 */
                     // p = q + 9;
                        p = strchr( q, '=' ) + 1;
                        if ( ( q = strchr( p, '"' ) ) != NULL ) {
                            strncpy( blogID, p, q - p );
                            blogID[q - p] = NUL;
                        }
                    }
                }
            }
        }
    }

    free( buffer );

    return ( endPointURL );
}
