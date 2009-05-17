/*
 *  bludot.c
 *
 * History:
 * $Log: /comm/xmlRPC/bluedot.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/02/25 16:22 Tsujimura543
 * bluedot.us → faves.com への移行に伴う修正を実施
 * 
 * 3     07/01/29 20:11 Tsujimura543
 * getNumberOfTagsOnBlueDot() を追加
 * 
 * 2     07/01/11 19:39 Tsujimura543
 * Blue Dot の html の書き方が微妙に変わったため、getNumberOfBookmarksOnBl
 * ueDot() を修正
 * 
 * 1     06/10/06 21:56 Tsujimura543
 * 新規作成 (del.icio.us 互換 API)
 */

#include "xmlRPC.h"
#include "delicious.h"
#include "bluedot.h"
#include "deliciousApi.h"
#include <time.h>
#include <math.h>

#define isWhiteSpace(c) \
    (((c) == ' ') || ((c) == '\t') || ((c) == '\r') || ((c) == '\n'))

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/bluedot.c 1     09/05/14 3:46 tsupo $";
#endif

/*
 *  Blue Dot: del.icio.us API
 */

/* 日付別投稿数の一覧の取得 */

long
getListOfDatesOnBlueDot(
        const char      *userName,      /* (I) ユーザ名       */
        const char      *password,      /* (I) パスワード     */
        char            *tag,           /* (I) タグ           */
        long            *numOfDates,    /* (I) 取得する情報数 */
                                        /* (O) 取得した情報数 */
        DELICIOUS_DATES *dates          /* (O) 取得した情報   */
    )
{
    return ( getListOfDatesOnDeliciousAPI( DAPI_BLUEDOT,
                                           userName, password,
                                           tag, numOfDates, dates ) );
}


/* 使っているタグの一覧の取得 */

long
getListOfTagsOnBlueDot(
        const char     *userName,   /* (I) ユーザ名       */
        const char     *password,   /* (I) パスワード     */
        long           *numOfTags,  /* (I) 取得する情報数 */
                                    /* (O) 取得した情報数 */
        DELICIOUS_TAGS *tags        /* (O) 取得した情報   */
    )
{
    return ( getListOfTagsOnDeliciousAPI( DAPI_BLUEDOT,
                                          userName, password,
                                          numOfTags, tags ) );
}


/* 指定した日付に投稿したエントリの一覧の取得 */

long
getListOfPostsOnBlueDot(
        const char      *userName,  /* (I) ユーザ名                         */
        const char      *password,  /* (I) パスワード                       */
        const char      *tag,       /* (I) 検索条件 (タグ)                  */
        const char      *dateTime,  /* (I) 検索条件 (投稿日時)
                                                   yyyy-mm-ddThh:mm:ssZ形式 */
        const char      *targetUrl, /* (I) 検索条件 (URL)                   */
        long            *numOfPosts,/* (I) 取得する情報数                   */
                                    /* (O) 取得した情報数                   */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報                     */
    )
{
    return ( getListOfPostsOnDeliciousAPI( DAPI_BLUEDOT,
                                           userName, password,
                                           tag, dateTime, targetUrl,
                                           numOfPosts, posts ) );
}


/* 最近のエントリ一覧の取得 */

long
getRecentPostsOnBlueDot(
        const char      *userName,  /* (I) ユーザ名        */
        const char      *password,  /* (I) パスワード      */
        const char      *tag,       /* (I) 検索条件 (タグ) */
        long            *numOfPosts,/* (I) 取得する情報数  */
                                    /* (O) 取得した情報数  */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報    */
    )
{
    return ( getRecentPostsOnDeliciousAPI( DAPI_BLUEDOT,
                                           userName, password,
                                           tag, numOfPosts, posts ) );
}


/* 全エントリの取得 */

long
getAllPostsOnBlueDot(
        const char      *userName,  /* (I) ユーザ名        */
        const char      *password,  /* (I) パスワード      */
        const char      *tag,       /* (I) 検索条件 (タグ) */
        long            *numOfPosts,/* (I) 取得する情報数  */
                                    /* (O) 取得した情報数  */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報    */
    )
{
    return ( getAllPostsOnDeliciousAPI( DAPI_BLUEDOT,
                                        userName, password,
                                        tag, numOfPosts, posts ) );
}


/* 最終更新日時の取得 */

long
getLastUpdateOnBlueDot(
        const char *userName,   /* (I) ユーザ名     */
        const char *password,   /* (I) パスワード   */
        char       *dateTime    /* (O) 取得した情報 */
    )
{
    return ( getLastUpdateOnDeliciousAPI( DAPI_BLUEDOT,
                                          userName, password,
                                          dateTime ) );
}


/* エントリの投稿(ブックマークの追加登録) */

BOOL
postEntryOnBlueDot(
    const char      *userName,      /* (I) ユーザ名               */
    const char      *password,      /* (I) パスワード             */
    DELICIOUS_ENTRY *entry     )    /* (I) 登録する情報(投稿内容) */
{
    return ( postEntryOnDeliciousAPI( DAPI_BLUEDOT,
                                      userName, password, entry ) );
}


/* エントリの削除 */

BOOL
deleteEntryOnBlueDot(
        const char *userName,   /* (I) ユーザ名                    */
        const char *password,   /* (I) パスワード                  */
        const char *url         /* (I) 削除するエントリの URL 要素 */
    )
{
    return ( deleteEntryOnDeliciousAPI( DAPI_BLUEDOT,
                                        userName, password, url ) );
}


/* タグの変更 */

BOOL
renameTagOnBlueDot(
        const char *userName,   /* (I) ユーザ名   */
        const char *password,   /* (I) パスワード */
        const char *oldTag,     /* (I) 古いタグ   */
        const char *newTag      /* (I) 新しいタグ */
    )
{
    return ( renameTagOnDeliciousAPI( DAPI_BLUEDOT,
                                      userName, password,
                                      oldTag, newTag ) );
}


/*
 *  追加機能
 */

/* 総ブックマーク数の取得 */

long
getNumberOfBookmarksOnBlueDot(
        const char *userName,   /* (I) ユーザ名   */
        const char *password    /* (I) パスワード */
    )
{
    long    num = 0;
    char    url[BUFSIZ];
    char    *response;
    size_t  sz;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE * 16;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

 // sprintf( url, "http://bluedot.us/users/%s", userName );
    sprintf( url, "http://faves.com/users/%s", userName );

    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( response[0] ) {
        char    *p = strstr( response, "Faves<img" );
        if ( p ) {
            char    *q = p;
            char    *r;
            char    buf[BUFSIZ];
            int     i = 0;

            while ( (p > response) && (*(p - 1) != '>') )
                p--;
            r = strstr( p, "of" );
            if ( r )
                p = r + 2;

            while ( *p && (p < q) ) {
                if ( (*p >= '0') && (*p <= '9') )
                    buf[i++] = *p;
                p++;
            }
            buf[i] = NUL;
            num = atol( buf );
        }
    }
    free( response );

    return ( num );
}


/* 総タグ数の取得 */
long
getNumberOfTagsOnBlueDot(
        const char *userName,   /* (I) ユーザ名   */
        const char *password    /* (I) パスワード */
    )
{
    long    num = 0;
    char    url[MAX_URLLENGTH];
    char    cookie[MAX_COOKIE_LEN];
    char    *response;
    size_t  sz;
    int     r;

    cookie[0] = NUL;
    sz = MAX_CONTENT_SIZE * 16;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    r = loginBlueDot( userName, password, cookie );
    if ( r || *cookie ) {
     // sprintf( url, "http://bluedot.us/users/%s/tag", userName );
        sprintf( url, "http://faves.com/users/%s/tag", userName );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "var tagExplorerMax =" );

            if ( p ) {
                p += 20;
                while ( isWhiteSpace( *p ) )
                    p++;
                num = atol( p );
            }

            if ( num == 0 ) {
                p = strstr( response, "<span>1 - 20</span> of " );
                if ( p ) {
                    int     n = 0;
                    char    *q;

                    p += 23;
                    q = strstr( p, "</div>" );
                    do {
                        while ( (*(q - 1) >= '0') && (*(q - 1) <= '9') )
                            q--;
                        num += (int)(atol( q ) * pow( 1000.0, (double)n ));
                        n++;
                    } while ( *--q == ',' );
                }
            }
        }
    }

    free( response );

    return ( num );
}


/* Blue Dot へ login */
int
loginBlueDot(
        const char *userName,   /* (I)   ユーザ名   */
        const char *password,   /* (I)   パスワード */
        char       *cookie      /* (I/O) クッキー   */
    )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !cookie )
         return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

 // strcpy( url, "https://secure.bluedot.us/signIn" );
    strcpy( url, "https://secure.faves.com/signIn" );
    setTargetURL( url );
    sprintf( request,
             "rUsername=%s&"
             "rPassword=%s&"
             "rememberMe=1&"
             "action=Sign+In",
             userName, password );
    setUpReceiveBuffer( response, sz );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               "application/x-www-form-urlencoded",
                               request, response, cookie,
                               NULL, NULL );

    if ( ret == -1 )
        ret = 0;        /* サーバとの通信失敗 */
    else if ( *response ) {
     // if ( strstr( response, "https://secure.bluedot.us/signOut" ) != NULL )
        if ( strstr( response, "https://secure.faves.com/signOut" ) != NULL )
            ret = 1;    /* ログイン成功 */
        else
            ret = 0;    /* ログイン失敗 */
    }

    free( response );
    free( request  );

    return ( ret );
}

