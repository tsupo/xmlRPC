/*
 *  xmlRPCutil.c
 *      ユーティリティ関数群
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2008, 2009 by H.Tsujimura
 *      written by H.Tsujimura      17 March 2004
 *
 * History:
 * $Log: /comm/xmlRPC/xmlRPCutil.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 37    09/03/23 16:01 Tsujimura543
 * getString() の修正ミスを修正
 * 
 * 36    09/03/20 17:45 Tsujimura543
 * ウェブリブログの XML-RPC API 経由での投稿、動作確認終了
 * 
 * 35    09/03/17 22:42 Tsujimura543
 * Windows Live Spaces (およびウェブリブログ) 向けの処理を追加
 * 
 * 34    08/11/17 22:41 Tsujimura543
 * バッファオーバーフロー対策を強化
 * 
 * 33    08/11/17 22:17 Tsujimura543
 * static char → Thread static char に変更
 * 
 * 32    08/09/10 23:52 Tsujimura543
 * ソースを整理 (コメントアウトしてあったコードを削除)
 * 
 * 31    08/09/10 22:47 Tsujimura543
 * getCategoryName***, getCategoryID*** 系の関数を削除
 * (xmlRPC.dll 外へ移動)
 * 
 * 30    07/10/29 17:48 Tsujimura543
 * getString() を修正、シャープエンコードされた文字列が含まれる場合は
 * デコードするようにした
 * 
 * 29    07/03/03 15:40 Tsujimura543
 * カテゴリ関連の処理(文字コード変換失敗時に落ちる可能性がある箇所)を修正
 * 
 * 28    07/01/23 15:32 Tsujimura543
 * getCategoryIDs() を修正 (楽天ブログ対策)
 * 
 * 27    06/09/05 13:44 Tsujimura543
 * exciteブログのカテゴリ名が数値参照で表現されるようになったのに対処する
 * ため、カテゴリ関連の処理を数値参照対応にした
 * 
 * 26    06/07/24 20:10 Tsujimura543
 * _httpExecute() のバッファオーバーラン防止機能を利用するようにした
 * 
 * 25    06/02/28 14:17 Tsujimura543
 * getSingleString() を MSN Spaces の返してくる XML にも対応させた
 * 
 * 24    06/02/28 13:46 Tsujimura543
 * getString() を MSN Spaces の返してくる XML にも対応させた
 * 
 * 23    05/08/11 17:51 Tsujimura543
 * getCategoryIDbyName() と getCategoryID() を2005年8月リニューアル後の
 * JUGEM でも使えるように修正
 * 
 * 22    05/05/18 20:54 Tsujimura543
 * getListFromXML() を修正 (不正ポインタ参照が発生する可能性があった)
 * 
 * 21    05/04/18 16:03 Tsujimura543
 * getResultFromXML() など XML 関連ユーティリティ関数を amazon.c
 * から移管
 * 
 * 20    05/04/01 16:26 Tsujimura543
 * バッファオーバーラン対策
 * 
 * 19    05/03/28 17:42 Tsujimura543
 * もはや使用していない変数を削除
 * 
 * 18    05/03/25 18:34 Tsujimura543
 * getCategoryIDbyName() を追加
 * 
 * 17    05/03/23 19:37 Tsujimura543
 * getCategoryIDs() を追加
 * 
 * 16    04/11/25 12:04 Tsujimura543
 * getCategoryNameFromStdin() をエコログ向けに微調整
 * 
 * 15    04/11/01 21:02 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 14    04/10/15 12:14 Tsujimura543
 * getEndpointURLbyAutoDiscovery() にRSDファイル取得失敗時の対処を追加
 * 
 * 13    04/10/14 23:20 Tsujimura543
 * getEndpointURLbyAutoDiscovery() で blogID も取得するように変更
 * 
 * 12    04/10/14 21:56 Tsujimura543
 * getEndpointURLbyAutoDiscovery() を追加
 * 
 * 11    04/09/29 13:34 Tsujimura543
 * 管理画面と対話する方式で投稿する場合のカテゴリ選択関連のバグ修正
 * 
 * 10    04/09/29 12:44 Tsujimura543
 * exciteブログでカテゴリ選択が意図通りにできない不具合に対処
 * 
 * 9     04/09/28 13:57 Tsujimura543
 * アメーバブログ対応
 * 
 * 8     04/09/17 15:34 Tsujimura543
 * getCategoryID() と getCategoryIDwithName() の共通部分を括りだし、
 * 新たに getCategoryIDfromStdin() を作成
 * 
 * 7     04/09/17 14:06 Tsujimura543
 * getCategoryIDwithName() を exciteBlog.c から取出し、共通関数化した
 * 
 * 6     04/09/17 13:32 Tsujimura543
 * getCategoryID() を修正 (minimumID が 1 以外のときの選択肢表示が
 * おかしかった)
 * 
 * 5     04/09/16 16:14 Tsujimura543
 * getCategoryID() を jugem.c, myprofile.c, yaplog.c から取り出し、
 * 共通関数化した
 * 
 * 4     04/08/31 12:06 Tsujimura543
 * getStringFromItem()、getDateTimeFromItem() を xmlRPCapic から移動
 * 
 * 3     04/07/14 18:49 Tsujimura543
 * Movable Type API 関連の関数の仕様見直し
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/xmlRPCutil.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/* Unicode(UCS-2BE) (%uXXXX or &#XXXXX;) → UTF-8 (xxyyzz) 変換 */
char    *
convUnicode( unsigned long code )
{
    unsigned short      a, b, c, d;
    Thread static char  codeStr[6];

    if ( code < 0x0080 ) {
        a = (unsigned short)code;
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = NUL;
    }
    else if ( code < 0x0800 ) {
        a = (unsigned short)(((code & 0x07C0) >> 6) | 0xC0);
        b = (unsigned short)(( code & 0x003F)       | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = NUL;
    }
    else if ( code < 0x010000 ) {
        a = (unsigned short)(((code & 0xF000) >> 12) | 0xE0);
        b = (unsigned short)(((code & 0x0FC0) >>  6) | 0x80);
        c = (unsigned short)(( code & 0x003F)        | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = (char)(c & 0xFF);
        codeStr[3] = NUL;
    }
    else {
        a = (unsigned short)(((code & 0x001C0000) >> 18) | 0xF0);
        b = (unsigned short)(((code & 0x0003F000) >> 12) | 0x80);
        c = (unsigned short)(((code & 0x00000FC0) >>  6) | 0x80);
        d = (unsigned short)(( code & 0x0000003F)        | 0x80);
        codeStr[0] = (char)(a & 0xFF);
        codeStr[1] = (char)(b & 0xFF);
        codeStr[2] = (char)(c & 0xFF);
        codeStr[3] = (char)(d & 0xFF);
        codeStr[4] = NUL;
    }

    return ( codeStr );
}

char    *
decodeNumericReference( char *src )
{
    char    *p    = src;
    char    *temp = (char *)malloc( strlen( src ) + 1 );

    if ( temp ) {
        unsigned long   l;

        temp[0] = NUL;
        while ( *p ) {
            if ( (*p == '&') && (*(p + 1) == '#') ) {
                l = atol( p + 2 );
                strcat( temp, convUnicode( l ) );
                p = strchr( p + 2, ';' ) + 1;
            }
            else {
                l = temp[0] ? strlen( temp ) : 0;
                temp[l]     = *p;
                temp[l + 1] = NUL;
                p++;
            }
        }
        strcpy( src, temp );

        free( temp );
    }

    return ( src );
}

int
getDateCreated( char **input,
                int *yy, int *mm, int *dd, int *HH, int *MM, int *SS,
                int *cnt, int cntMax,
                int *numOfInfo )
{
#define MAX_DATECREATED_LENGTH  60
    char    *p, *q, *r, *s;
    char    dateCreated[MAX_DATECREATED_LENGTH];
    /* パターン1 => 19980717T14:08:55    */
    /* パターン2 => 2004-03-16T18:00:06Z */

    p = strstr( *input, "<name>dateCreated</name>" );
    q = strstr( *input, "<name>" );
    if ( p && (p == q) ) {
        r = strstr( p + 24, "<dateTime.iso8601>" );
        if ( r ) {
            s = strstr( r + 18, "</dateTime.iso8601>" );
            if ( s ) {
                size_t  len = min( s - (r + 18), MAX_DATECREATED_LENGTH - 1 );
                strncpy( dateCreated,
                         r + 18,
                         len );
                dateCreated[len] = NUL;

                if ( strchr( dateCreated, '-' ) == NULL ) {
                    /* パターン1 の場合 */
                    *dd = atol( dateCreated + 6 );
                    dateCreated[6] = NUL;
                    *mm = atol( dateCreated + 4 );
                    dateCreated[4] = NUL;
                    *yy = atol( dateCreated );
                    *HH = atol( dateCreated +  9 );
                    *MM = atol( dateCreated + 11 );
                    *SS = atol( dateCreated + 13 );
                }
                else {
                    /* パターン2 の場合 */
                    *yy = atol( dateCreated );
                    *mm = atol( dateCreated +  5 );
                    *dd = atol( dateCreated +  8 );
                    *HH = atol( dateCreated + 11 );
                    *MM = atol( dateCreated + 14 );
                    *SS = atol( dateCreated + 17 );
                }
                (*cnt)++;
                if ( *cnt == cntMax ) {
                    (*numOfInfo)++;
                    *input = strstr( s, "</struct>" );
                }
            }
        }
    }

    return ( *cnt );
}


int
getString( char       **input,
           char       *string,
           const char *paramName,
           int        *cnt,
           int        cntMax,
           int        *numOfInfo )
{
#define MAX_TARGETSTRING_LENGTH 128
    const char  *p, *q, *r, *s = NULL;
    char        target[MAX_TARGETSTRING_LENGTH];
    size_t      l = strlen( paramName );
    int         checked = FALSE;

    sprintf( target, "<name>%s</name>", paramName );
    p = strstr( *input, target );
    q = strstr( *input, "</struct>" );
    if ( p && (p < q) ) {
        q = strstr( p + l, "<string/>" );
        r = strstr( p + l, "<string />" );
        s = strstr( p + 1, "</member>" );
        if ( (q && (q < s)) || (r && (r < s)) ) {
            string[0] = NUL;
            checked = TRUE;
            s = q ? q + 9 : r + 10;
        }
        else {
            const char  *t = "</string>";
            int         skip = 8;

            r = strstr( p + l, "<string>" );
            if ( !r ) {
                /* for MSN Spaces */
                r = strstr( p + l, "<value>" );
                t = "</value>";
                skip = 7;
            }

            if ( r ) {
                s = strstr( r + skip, t );
                if ( s ) {
                    size_t  len = min( s - (r + skip),
                                       MAX_TARGETSTRING_LENGTH - 1 );
                    strncpy( string, r + skip, len );
                    string[len] = NUL;

                    // &#xxxx; な文字列があれば、デコードする
                    if ( strstr( string, "&#" ) )
                        decodeNumericReference( string );

                    checked = TRUE;
                }
            }
        }
    }

    if ( checked && s ) {
        (*cnt)++;
        if ( *cnt == cntMax ) {
            (*numOfInfo)++;
            *input = strstr( s, "</struct>" );
        }
    }

    return ( *cnt );
}


int
getInteger( char       **input,
            int        *integer,
            const char *paramName,
            int        *cnt,
            int        cntMax,
            int        *numOfInfo )
{
    char    *p, *q, *r, *s, *t;
    char    target[MAX_TARGETSTRING_LENGTH];
    size_t  l = strlen( paramName );
    char    string[BUFSIZ];

    sprintf( target, "<name>%s</name>", paramName );
    p = strstr( *input, target );
    q = strstr( *input, "<name>" );
    if ( p && (p == q) ) {
        q = strstr( p + l, "<i4>" );
        r = strstr( p + l, "<int>" );
        if ( q || r ) {
            if ( q ) {
                t = q + strlen("<i4>");
                s = strstr( t, "</i4>" );
            }
            else {
                t = r + strlen("<int>");
                s = strstr( t, "</int>" );
            }
            if ( s ) {
                size_t  len = min( s - t, MAX_TARGETSTRING_LENGTH - 1 );
                strncpy( string, t, len );
                string[len] = NUL;
                *integer = atol( string );
                (*cnt)++;
                if ( *cnt == cntMax ) {
                    (*numOfInfo)++;
                    *input = strstr( s, "</struct>" );
                }
            }
        }
    }

    return ( *cnt );
}


int
getBoolean( char       **input,
            int        *boolean,
            const char *paramName,
            int        *cnt,
            int        cntMax,
            int        *numOfInfo )
{
    char    *p, *q, *s, *t;
    char    target[MAX_TARGETSTRING_LENGTH];
    size_t  l = strlen( paramName );
    char    string[BUFSIZ];

    sprintf( target, "<name>%s</name>", paramName );
    p = strstr( *input, target );
    q = strstr( *input, "<name>" );
    if ( p && (p == q) ) {
        q = strstr( p + l, "<boolean>" );
        if ( q ) {
            t = q + strlen("<boolean>");
            s = strstr( t, "</boolean>" );
            if ( s ) {
                size_t  len = min( s - t, MAX_TARGETSTRING_LENGTH - 1 );
                strncpy( string, t, len );
                string[len] = NUL;
                *boolean = atol( string );
                (*cnt)++;
                if ( *cnt == cntMax ) {
                    (*numOfInfo)++;
                    *input = strstr( s, "</struct>" );
                }
            }
        }
    }

    return ( *cnt );
}



int
getUserid( char **input,
           char *userid,
           int *cnt, int cntMax,
           int *numOfInfo )
{
    return ( getString( input, userid, "userid", cnt, cntMax, numOfInfo ) );
}


int
getPostid( char **input,
           char *postid,
           int *cnt, int cntMax,
           int *numOfInfo )
{
    return ( getString( input, postid, "postid", cnt, cntMax, numOfInfo ) );
}


int
getContent( char **input,
            char *content,
            int *cnt, int cntMax,
            int *numOfInfo )
{
    return ( getString( input, content, "content", cnt, cntMax, numOfInfo ) );
}


int
getTitle( char **input,
          char *title,
          int *cnt, int cntMax,
          int *numOfInfo )
{
    return ( getString( input, title, "title", cnt, cntMax, numOfInfo ) );
}


int
getPingUrl( char **input,
            char *pingURL,
            int *cnt, int cntMax,
            int *numOfInfo )
{
    return ( getString( input, pingURL, "pingURL", cnt, cntMax, numOfInfo ) );
}


int
getPingTitle( char **input,
              char *pingTitle,
              int *cnt, int cntMax,
              int *numOfInfo )
{
    return ( getString( input, pingTitle, "pingTitle",
                        cnt, cntMax, numOfInfo ) );
}


int
getPingIP( char **input,
           char *pingIP,
           int *cnt, int cntMax,
           int *numOfInfo )
{
    return ( getString( input, pingIP, "pingIP", cnt, cntMax, numOfInfo ) );
}


int
getUrl( char **input,
        char *url,
        int *cnt, int cntMax,
        int *numOfInfo )
{
    return ( getString( input, url, "url", cnt, cntMax, numOfInfo ) );
}


int
getBlogid( char **input,
           char *blogid,
           int *cnt, int cntMax,
           int *numOfInfo )
{
    return ( getString( input, blogid, "blogid", cnt, cntMax, numOfInfo ) );
}


int
getBlogName( char **input,
             char *blogName,
             int *cnt, int cntMax,
             int *numOfInfo )
{
    return ( getString( input, blogName, "blogName", cnt, cntMax, numOfInfo ) );
}


int
getFirstname( char **input,
             char *firstname,
             int *cnt, int cntMax,
             int *numOfInfo )
{
    return ( getString( input, firstname, "firstname",
                        cnt, cntMax, numOfInfo ) );
}

int
getLastname( char **input,
             char *lastname,
             int *cnt, int cntMax,
             int *numOfInfo )
{
    return (getString( input, lastname, "lastname", cnt, cntMax, numOfInfo ));
}

int
getNickname( char **input,
             char *nickname,
             int *cnt, int cntMax,
             int *numOfInfo )
{
    return (getString( input, nickname, "nickname", cnt, cntMax, numOfInfo ));
}

int
getEmail( char **input,
          char *email,
          int *cnt, int cntMax,
          int *numOfInfo )
{
    return ( getString( input, email, "email", cnt, cntMax, numOfInfo ) );
}

int
getDescription( char **input,
                char *description,
                int *cnt, int cntMax,
                int *numOfInfo )
{
    return ( getString( input, description, "description",
                        cnt, cntMax, numOfInfo ) );
}

int
getLink( char **input,
         char *link,
         int *cnt, int cntMax,
         int *numOfInfo )
{
    return ( getString( input, link, "link",
                        cnt, cntMax, numOfInfo ) );
}

int
getPermaLink( char **input,
              char *permaLink,
              int *cnt, int cntMax,
              int *numOfInfo )
{
    return ( getString( input, permaLink, "permaLink",
                        cnt, cntMax, numOfInfo ) );
}


/* 以下、Movable Type 拡張 metaWeblog API 用ユーティリティ関数群 */

int
getStringEx( char       **input,
             char       *string,
             const char *paramName,
             int        *cnt,
             int        cntMax,
             int        *numOfInfo )
{
    int     ret = 0;
    char    *p, *q;

    p = strstr( *input, paramName );
    q = strstr( *input, "</struct>" );
    if ( p && q && (p < q) )
        ret = getString( input, string, paramName,
                         cnt, cntMax, numOfInfo ) ;
    else {
        string[0] = NUL;
        ret = ++(*cnt);
        if ( *cnt == cntMax ) {
            (*numOfInfo)++;
            *input = strstr( *input, "</struct>" );
        }
    }

    return ( ret );
}

int
getIntegerEx( char       **input,
              int        *integer,
              const char *paramName,
              int        *cnt,
              int        cntMax,
              int        *numOfInfo )
{
    int     ret = 0;
    char    *p, *q;

    p = strstr( *input, paramName );
    q = strstr( *input, "</struct>" );
    if ( p && q && (p < q) )
        ret = getInteger( input, integer, paramName,
                          cnt, cntMax, numOfInfo ) ;
    else {
        *integer = -1;
        ret = ++(*cnt);
        if ( *cnt == cntMax ) {
            (*numOfInfo)++;
            *input = strstr( *input, "</struct>" );
        }
    }

    return ( ret );
}


int
getExcerpt( char **input,
            char *excerpt,
            int *cnt, int cntMax,
            int *numOfInfo )
{
    return ( getStringEx( input, excerpt, "mt_excerpt",
                          cnt, cntMax, numOfInfo ) );
}

int
getExtended( char **input,
             char *excerpt,
             int *cnt, int cntMax,
             int *numOfInfo )
{
    return ( getStringEx( input, excerpt, "mt_text_more",
                          cnt, cntMax, numOfInfo ) );
}

int
getAllowComments( char **input,
                  int *allowComments,
                  int *cnt, int cntMax,
                  int *numOfInfo )
{
    return ( getIntegerEx( input, allowComments, "mt_allow_comments",
                           cnt, cntMax, numOfInfo ) );
}

int
getAllowPings( char **input,
               int *allowPings,
               int *cnt, int cntMax,
               int *numOfInfo )
{
    return ( getIntegerEx( input, allowPings, "mt_allow_pings",
                           cnt, cntMax, numOfInfo ) );
}

int
getConvertLineBreaks( char **input,
                      char *convertLineBreaks,
                      int *cnt, int cntMax,
                      int *numOfInfo )
{
    return ( getStringEx( input, convertLineBreaks, "mt_convert_breaks",
                          cnt, cntMax, numOfInfo ) );
}

int
getKeywords( char **input,
             char *keywords,
             int *cnt, int cntMax,
             int *numOfInfo )
{
    return ( getStringEx( input, keywords, "mt_keywords",
                          cnt, cntMax, numOfInfo ) );
}


/* Movable Type API 専用 */
int
getCategoryId( char **input,
               char *categoryId,
               int *cnt, int cntMax,
               int *numOfInfo )
{
    return ( getString( input, categoryId, "categoryId",
                        cnt, cntMax, numOfInfo ) );
}

int
getCategoryName( char **input,
                 char *categoryName,
                 int *cnt, int cntMax,
                 int *numOfInfo )
{
    return ( getString( input, categoryName, "categoryName",
                        cnt, cntMax, numOfInfo ) );
}

int
getIsPrimary( char **input,
              int *isPrimary,
              int *cnt, int cntMax,
              int *numOfInfo )
{
    return ( getBoolean( input, isPrimary, "isPrimary",
                         cnt, cntMax, numOfInfo ) );
}

int
getKey( char **input,
        char *key,
        int *cnt, int cntMax,
        int *numOfInfo )
{
    return ( getString( input, key, "key",
                        cnt, cntMax, numOfInfo ) );
}

int
getLabel( char **input,
          char *label,
          int *cnt, int cntMax,
          int *numOfInfo )
{
    return ( getString( input, label, "label",
                        cnt, cntMax, numOfInfo ) );
}


char    *
getSingleString( const char *src, char *dst )
{
    const char  *p = strstr( src, "<string>" );
    const char  *q;
    const char  *r = "</string>";
    int         skip = 8;

    if ( !p ) {
        /* for MSN Spaces */
        p = strstr( src, "<value>" );
        r = "</value>";
        skip = 7;
    }

    if ( p ) {
        p += skip;
        q = strstr( p, r );
        if ( q ) {
            strncpy( dst, p, q - p );
            dst[q - p] = NUL;
        }
    }

    return ( dst );
}


/* RSSファイル解析用 */
BOOL
getStringFromItem( const char *spec,
                   const char *in[],
                   char       *out,
                   int        size,
                   int        *cnt )
{
    BOOL        cont = FALSE;
    const char  *p, *q, *r;
    int         l;
    int         len = strlen( spec );

    p = *in;
    if ( (*p == '<')                  &&
         !strncmp( p + 1, spec, len ) &&
         (*(p + 1 + len) == '>')         ) {
        q = (p += (1 + len + 1));
        if ( !strncmp( p, "<![CDATA[", 9 ) )
            q = (p += 9);

        if ( ( ( r = strstr( p, "</" ) ) != NULL ) &&
             !strncmp( r + 2, spec, len ) &&
             (*(r + 2 + len) == '>')                   ) {
            p = r + 8;
            if ( !strncmp( r - 3, "]]>", 3 ) )
                r -= 3;

            l = r - q;
            if ( l >= size )
                l = size - 1;
            strncpy( out, q, l );
            out[l] = NUL;
            (*cnt)++;
        }
        else
            cont = TRUE;
    }
    *in = p;

    return ( cont );
}

BOOL
getDateTimeFromItem( const char *spec,
                     const char *in[],
                     POSTINF    *out,
                     int        *cnt )
{
    BOOL    cont = FALSE;
    char    dateTime[MAX_DATELENGTH];

    dateTime[0] = NUL;
    if ( getStringFromItem( spec, in,
                            dateTime,
                            MAX_DATELENGTH, cnt ) ) {
        cont = TRUE;
    }
    else if ( dateTime[0] != NUL ) {
        int     d;
        char    *r = dateTime;

        d = (*r++ - '0');
        d = d * 10 + (*r++ - '0');
        d = d * 10 + (*r++ - '0');
        d = d * 10 + (*r++ - '0');
        out->yy = d;

        if ( *r == '-' )
            r++;
        d = (*r++ - '0');
        d = d * 10 + (*r++ - '0');
        out->mm = d;

        if ( *r == '-' )
            r++;
        d = (*r++ - '0');
        d = d * 10 + (*r++ - '0');
        out->dd = d;

        if ( *r == 'T' )
            r++;
        d = (*r++ - '0');
        d = d * 10 + (*r++ - '0');
        out->HH = d;

        if ( *r == ':' )
            r++;
        d = (*r++ - '0');
        d = d * 10 + (*r++ - '0');
        out->MM = d;

        if ( *r == ':' )
            r++;
        d = (*r++ - '0');
        d = d * 10 + (*r++ - '0');
        out->SS = d;
    }

    return ( cont );
}


/* エンドポイントURL取得 */
char    *
getEndpointURLbyAutoDiscovery( const char *topPageURL, char *blogID )
{
    char                *buffer, *p, *q;
    int                 ret;
    size_t              sz;
    Thread static char  endPointURL[MAX_URLLENGTH + 1];

    if ( !topPageURL || !(*topPageURL) )
        return ( NULL );

    memset( endPointURL, 0x00, MAX_URLLENGTH + 1 );

    sz = RCV_BUFFER_SIZE * 4;
    buffer = (char *)malloc( sz );
    if ( !buffer )
        return ( NULL );

    /* トップページを取得 */
    setUpReceiveBuffer( buffer, sz );
    ret = httpGetBuffer( topPageURL, buffer, FALSE );
    if ( (ret != -1) && (buffer[0] != NUL) ) {
        /* トップページから <link rel="EditURI" な行を抜き出す */
        p = strstr( buffer, "<link rel=\"EditURI\"" );
        if ( p && ( ( q = strstr( p + 19, "href=\"" ) ) != NULL ) ) {
            /* RSD の URL を取得 */
            char rsdURL[MAX_URLLENGTH + 1];

            p = q + 6;
            q = strchr( p, '"' );

            if ( q ) {
                size_t  len = min( q - p, MAX_URLLENGTH );
                strncpy( rsdURL, p, len );
                rsdURL[len] = NUL;

                /* RSD ファイルを取得 */
                setUpReceiveBuffer( buffer, sz );
                ret = httpGetBuffer( rsdURL, buffer, FALSE );
                if ( (ret != -1) && (buffer[0] != NUL) ) {
                    /* RSD ファイルから エンドポイントURL を抜き出す */
                    p = strstr( buffer, "apiLink=\"" );
                    if ( p && ( ( q = strchr( p + 9, '"' ) ) != NULL ) ) {
                        p += 9;
                        len = min( q - p, MAX_URLLENGTH );
                        strncpy( endPointURL, p, len );
                        endPointURL[len] = NUL;

                        if ( blogID ) {
                            /* blog ID を取得 */
                            p = strstr( q + 1, "blogID=\"" );
                            if ( p &&
                                 ( ( q = strchr( p + 8, '"' ) ) != NULL ) ) {
                                p += 8;
                                strncpy( blogID, p, q - p );
                                blogID[q - p] = NUL;
                            }
                        }
                    }
                }
            }
        }
    }

    free( buffer );

    return ( endPointURL );
}


/*
 *  XMLからデータを取り出すためのユーティリティ関数
 */

char    *
getResultFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *sectionEnd,
        char       *result
    )
{
    const char  *p = xmlSrc, *q, *r;
    char        targetTag[MAX_NAMELEN];
    int         len;

    sprintf( targetTag, "<%s>", tagName );
    len = strlen( targetTag );

    q = strstr( p, targetTag );
    r = strstr( p, sectionEnd );
    if ( q && r ) {
        if ( q < r ) {
            q += len;
            r = strchr( q, '<' );
            if ( r ) {
                strncpy( result, q, r - q );
                result[r - q] = NUL;
                p = r + (len + 1);
            }
            else
                p = q + 1;
        }
    }

    return ( (char *)p );
}

char    *
getIntegerFromXML(
        const char    *xmlSrc,
        const char    *tagName,
        const char    *sectionEnd,
        unsigned long *result
    )
{
    char    temp[16];
    char    *p = getResultFromXML( xmlSrc, tagName, sectionEnd, temp );
    char    *q = temp;

    if ( (*q > '0') && (*q <= '9') ) {
        char    *r = q;
        while ( *r ) {
            if ( *r == ',' )
                strcpy( r, r + 1 );
            r++;
        }
        *result = (unsigned long)atol( q );
    }

    return ( p );
}

char    *
getFloatFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *sectionEnd,
        double     *result
    )
{
    char    temp[16];
    char    *p = getResultFromXML( xmlSrc, tagName, sectionEnd, temp );
    char    *q = temp;

    if ( (*q > '0') && (*q < '9') ) {
        char    *r = q;
        while ( *r ) {
            if ( *r == ',' )
                strcpy( r, r + 1 );
            r++;
        }
        *result = atof( q );
    }

    return ( p );
}

char    *
getListFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *subTagName,
        const char *sectionEnd,
        char       *result,
        size_t     areaSizeOfResult
    )
{
    const char  *p = xmlSrc, *q, *r;
    char        targetTag[MAX_NAMELEN];
    char        targetEnd[MAX_NAMELEN];
    char        subTag[MAX_NAMELEN];
    int         taglen, sublen;

    sprintf( targetTag, "<%s>",  tagName );
    sprintf( targetEnd, "</%s>", tagName );
    sprintf( subTag,    "<%s>",  subTagName );
    taglen = strlen( targetTag );
    sublen = strlen( subTag );

    q = strstr( p, targetTag );
    r = strstr( p, sectionEnd );
    if ( q && r ) {
        if ( q < r ) {
            size_t  len = 0;
            char    *s = strstr( q + taglen, targetEnd );

            if ( s ) {
                result[0] = NUL;

                q += taglen;
                r = strchr( q, '<' );
                while ( r && !strncmp( r, subTag, sublen ) ) {
                    q = r + sublen;
                    r = strchr( q, '<' );

                    if ( r ) {
                        if ( len > 0 ) {
                            strcat( result, ", " );
                            len += 2;
                        }
                        strncat( result, q, r - q );
                        result[len + (r - q)] = NUL;
                        len += (r - q);
                        q = r + (sublen + 1);
                    }

                    r = strchr( q, '<' );
                    if ( r && (r == s) )
                        break;
                    if ( len >= areaSizeOfResult )
                        break;
                }

                p = q + 1;
            }
        }
    }

    return ( (char *)p );
}


/*
 * for Windows Live Spaces
 */

int
getPublish( char **input,
            int *publish,
            int *cnt, int cntMax,
            int *numOfInfo )
{
    return ( getBoolean( input, publish, "publish",
                         cnt, cntMax, numOfInfo ) );
}

int
getArrayCategories( char **input,
                    char *categories[MAX_CATEGORIES],
                    int  *numOfCategories )
{
    char    *p, *q, *r, *s, *t, *u;
    int     num = 0;
    size_t  len;

    p = strstr( *input, "<name>categories</name>" );
    q = strstr( *input, "<name>" );
    if ( p && (p == q) ) {
        p += 23;
        q = strstr( p, "<array>" );
        r = strstr( p, "</member>" );
        if ( q && r && (q < r) ) {
            q += 7;
            while ( *q ) {
                s = strstr( q, "<data>" );
                if ( !s || (s > r) )
                    break;

                s += 6;
                t = strstr( s, "<value>" );
                if ( !t || (t > r) )
                    break;

                t += 7;
                u = strstr( s, "</value>" );
                if ( !u || (u > r) )
                    break;

                len = min( u - t, MAX_CATNAMELENGTH - 1 );
                strncpy( categories[num], t, len );
                categories[num][len] = NUL;
                num++;
                if ( num >= MAX_CATEGORIES )
                    break;

                q = u + 8;
            }

            *numOfCategories = num;
            *input = r + 9;
        }
        else if ( r )
            *input = r + 9;
        else
            *input = p;
    }

    return ( *numOfCategories );
}

