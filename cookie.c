/*
 *  cookie.c
 *      cookie 関連関数群
 *
 * History:
 * $Log: /comm/xmlRPC/cookie.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 23    08/11/17 21:56 Tsujimura543
 * static → Thread static に変更
 * 
 * 22    07/09/26 13:51 Tsujimura543
 * CV_t を導入し、ソースを整理
 * 
 * 21    07/09/26 13:46 Tsujimura543
 * 「livedoor Blog 向け暫定処理」を livedoor Blog 以外にも適用する
 * ようにした
 * 
 * 20    06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 19a   06/09/03 15:51 tsupo
 * assert を入れてみた
 * 
 * 19    06/03/10 18:18 Tsujimura543
 * joinCookie() を修正 (cookieNew と cookieOld の両方に同じ名前の
 * パラメータがある場合、新しい方の値を古い方の値で上書きしていた
 * のを、古い方の値を新しい方の値で上書きするように修正した)
 * 
 * 18    06/03/07 23:06 Tsujimura543
 * path と domain は完全に削除するようにしてみた
 * 
 * 17    06/02/21 21:48 Tsujimura543
 * [メモ] path は完全に削除してしまっても構わない?
 * 
 * 16    06/02/21 21:42 Tsujimura543
 * Cookie が無限に長くなっていくのを防ぐため、 path=/; を削除するようにした
 * 
 * 15    06/02/21 1:41 Tsujimura543
 * 一部のサイトに関して暫定的に cookie 回りの特別な処理を入れていたのを
 * 完全に廃止
 * 
 * 14    06/02/21 1:32 Tsujimura543
 * Expire の西暦年が2桁表記である場合にも正しく処理できるようにした
 * 
 * 13    06/02/06 12:10 Tsujimura543
 * joinCookie() を修正 (編集後の cookie を反映せずに捨ててしまっていた)
 * 
 * 12    06/01/27 0:09 Tsujimura543
 * joinCookie() を修正 (Cookie 文字列が際限なく長くなっていく不具合を修正)
 * 
 * 11    06/01/26 17:10 Tsujimura543
 * 2つの cookie を合体させる関数を追加
 * 
 * 10    06/01/25 21:28 Tsujimura543
 * (1) expires をチェックするようにした
 * (2) livedoor Blog 向け暫定処理を追加
 * 
 * 9     05/04/21 15:09 Tsujimura543
 * 楽天広場に対応できるように、saveCookie() を中心に修正を実施
 * 
 * 8     04/11/26 20:52 Tsujimura543
 * ウェブリブログ対応
 * 
 * 7     04/11/25 10:07 Tsujimura543
 * エコログ対応
 * 
 * 6     04/10/08 20:29 Tsujimura543
 * キヌガサ内日記対応
 * 
 * 5     04/10/08 12:18 Tsujimura543
 * exciteブログにも適用するようにした
 * 
 * 4     04/09/28 13:54 Tsujimura543
 * アメーバブログ対応
 * 
 * 3     04/09/02 20:40 Tsujimura543
 * getCookie() を httpPost.c から移動
 * 
 * 2     04/09/02 15:44 Tsujimura543
 * リファクタリングを実施
 * 
 * 1     04/09/02 15:41 Tsujimura543
 * 新規作成
 */

#include "xmlRPC.h"
#include <time.h>
#include <assert.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/cookie.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

typedef struct cookieValuable   CV_t;

#define COOKIE_UNIT 80

/* cookie情報格納領域の確保 */
COOKIE_INFO *
createCookie()
{
    COOKIE_INFO *p;

    p = (COOKIE_INFO *)malloc( sizeof ( COOKIE_INFO ) );
    if ( !p )
        return ( NULL );

    p->valuable = (CV_t *)malloc( sizeof ( CV_t ) * COOKIE_UNIT );
    if ( !(p->valuable) ) {
        free( (void *)p );
        return ( NULL );
    }

    p->maxNumOfValuables = COOKIE_UNIT;
    p->numOfValuables    = 0;

    memset( p->valuable, 0x00, sizeof ( CV_t ) * COOKIE_UNIT );

    return ( p );
}


/* cookie情報格納領域の拡張 */
COOKIE_INFO *
reallocCookie( COOKIE_INFO *p )
{
    CV_t    *vp;

    if ( !p )
        return ( NULL );
    p->maxNumOfValuables += COOKIE_UNIT;
    vp = (CV_t *)malloc( sizeof ( CV_t ) * p->maxNumOfValuables );
    if ( vp ) {
        memcpy( vp, p->valuable,
                sizeof ( CV_t ) * (p->maxNumOfValuables - COOKIE_UNIT) );
        free( (void *)(p->valuable) );
        p->valuable = vp;
    }

    return ( p );
}


/* cookie情報格納領域の解放 */
void
destroyCookie( COOKIE_INFO *p )
{
    if ( !p )
        return;

    if ( p->valuable )
        free( (void *)(p->valuable) );
    free( (void *)p );
}


/* cookie の保存 */
char    *
saveCookie( COOKIE_INFO *cp, const char *cookie )
{
    Thread static char  newCookie[10240];
    const char          *p, *q, *r;
    CV_t                tmp;
    int                 found, done, i;

    if ( !cp )
        return ( NULL );

    p = strstr( cookie, ": " );
    if ( p )
        p += 2;
    else
        p = cookie;

    do {
        found = FALSE;
        done  = FALSE;
        q = strchr( p, ';' );
        if ( q ) {
            r = strchr( p, '=' );
            if ( r && (r < q ) ) {
                char    *s = strstr( q + 1, "secure;" );
                if ( s )
                    q = s + 6; /* "secure"(6バイト)分加算 */

                strncpy( tmp.name,  p, r - p );
                tmp.name[r - p] = NUL;
                r++;
                strncpy( tmp.value, r, q - r );
                tmp.value[q - r] = NUL;
                found = TRUE;
            }
            p = q + 1;
            while ( *p == ' ' )
                p++;
        }
        else {
            done = TRUE;
            r = strchr( p, '=' );
            if ( r ) {
                strncpy( tmp.name,  p, r - p );
                tmp.name[r - p] = NUL;
                r++;
                while ( (*(r + (strlen( r ) - 1)) == '\r') ||
                        (*(r + (strlen( r ) - 1)) == '\n')    ) {
                    *(char *)(r + (strlen( r ) - 1)) = NUL;
                }
                strcpy( tmp.value, r );
                found = TRUE;

                p = r + strlen( r );
            }
        }

        if ( found ) {
            if ( (stricmp( tmp.name, "path"   ) != 0) &&
                 (stricmp( tmp.name, "domain" ) != 0)    ) {
                /* path と domain 以外に関しては、重複するものがある場合、 */
                /* 後から出現した方で上書きする                            */
                int rewritten = FALSE;

                for ( i = 0; i < cp->numOfValuables; i++ ) {
                    if ( !strcmp( cp->valuable[i].name, tmp.name ) ) {
                        strcpy( cp->valuable[i].value, tmp.value );
                        rewritten = TRUE;
                        break;
                    }
                }

                if ( !rewritten ) {
                    if ( cp->numOfValuables == cp->maxNumOfValuables )
                        cp = reallocCookie( cp );
                    strcpy(cp->valuable[cp->numOfValuables].name,  tmp.name );
                    strcpy(cp->valuable[cp->numOfValuables].value, tmp.value);
                    (cp->numOfValuables)++;
                }
            }
            /*
            else {
                if ( cp->numOfValuables == cp->maxNumOfValuables )
                    cp = reallocCookie( cp );
                strcpy(cp->valuable[cp->numOfValuables].name,  tmp.name );
                strcpy(cp->valuable[cp->numOfValuables].value, tmp.value);
                (cp->numOfValuables)++;
            }
            */
        }
    } while ( *p && !done );

    return ( loadCookie( cp ) );
}


/* cookie の取得 */
char    *
loadCookie( const COOKIE_INFO *cp )
{
    Thread static char  newCookie[10240];
    int                 i;

    strcpy( newCookie, "Cookie: " );
    for ( i = 0; i < cp->numOfValuables; i++ ) {
        if ( i > 0 )
            strcat( newCookie, "; " );
        sprintf( newCookie + strlen( newCookie ),
                 "%s=%s",
                 cp->valuable[i].name, cp->valuable[i].value );
    }
    strcat( newCookie, "\r\n" );

    assert( strlen(newCookie) < MAX_COOKIE_LEN );

    return ( newCookie );
}


static BOOL
checkExpire( const char *p )
{
    /* 期限切れかどうかのチェック */
    const char  *q = strstr( p, "\r\n" );
    const char  *r;
    time_t      t;
    struct tm   *tm;
    int         yyyyC, mmC, ddC, HHC, MMC, SSC;
    int         yyyyE, mmE, ddE, HHE, MME, SSE;

    if ( !q )
        q = strchr( p, '\n' );
    if ( !q )
        q = strchr( p, '\r' );
    if ( !q )
        return ( FALSE );
    r = strstr( p, "expires=" );
    if ( !r )
        r = strstr( p, "Expires=" );
    if ( !r || (r > q) )
        return ( FALSE );

    /* expires=Thu, 23-Feb-2006 05:16:29 GMT */
    p = r + 8;
    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    ddE = atol( p );

    while ( ((*p < 'A') || (*p > 'S')) && (p < q) )
        p++;
    if ( !strncmp( p, "Jan", 3 ) )
        mmE = 1;
    else if ( !strncmp( p, "Feb", 3 ) )
        mmE = 2;
    else if ( !strncmp( p, "Mar", 3 ) )
        mmE = 3;
    else if ( !strncmp( p, "Apr", 3 ) )
        mmE = 4;
    else if ( !strncmp( p, "May", 3 ) )
        mmE = 5;
    else if ( !strncmp( p, "Jun", 3 ) )
        mmE = 6;
    else if ( !strncmp( p, "Jul", 3 ) )
        mmE = 7;
    else if ( !strncmp( p, "Aug", 3 ) )
        mmE = 8;
    else if ( !strncmp( p, "Sep", 3 ) )
        mmE = 9;
    else if ( !strncmp( p, "Oct", 3 ) )
        mmE = 10;
    else if ( !strncmp( p, "Nov", 3 ) )
        mmE = 11;
    else if ( !strncmp( p, "Dec", 3 ) )
        mmE = 12;
    else
        return ( FALSE );

    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    yyyyE = atol( p );
    if ( yyyyE < 100 )
        yyyyE += 2000;

    while ( ((*p >= '0') && (*p <= '9')) && (p < q) )
        p++;
    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    HHE = atol( p );

    while ( ((*p >= '0') && (*p <= '9')) && (p < q) )
        p++;
    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    MME = atol( p );

    while ( ((*p >= '0') && (*p <= '9')) && (p < q) )
        p++;
    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    SSE = atol( p );

    /* 現在時刻を取得 */
    t  = time( NULL );
    tm = gmtime( &t );  /* GMT */
    yyyyC = tm->tm_year + 1900;
    mmC   = tm->tm_mon + 1;
    ddC   = tm->tm_mday;
    HHC   = tm->tm_hour;
    MMC   = tm->tm_min;
    SSC   = tm->tm_sec;

    /* 現在時刻と expire 日時を比較 */
    if ( yyyyE < yyyyC )
        return ( TRUE );    /* 期限切れ */
    if ( yyyyE > yyyyC )
        return ( FALSE );

    if ( mmE < mmC )
        return ( TRUE );    /* 期限切れ */
    if ( mmE > mmC )
        return ( FALSE );

    if ( ddE < ddC )
        return ( TRUE );    /* 期限切れ */
    if ( ddE > ddC )
        return ( FALSE );

    if ( HHE < HHC )
        return ( TRUE );    /* 期限切れ */
    if ( HHE > HHC )
        return ( FALSE );

    if ( MME < MMC )
        return ( TRUE );    /* 期限切れ */
    if ( MME > MMC )
        return ( FALSE );

    if ( SSE < SSC )
        return ( TRUE );    /* 期限切れ */
    if ( SSE > SSC )
        return ( FALSE );

    return ( TRUE );        /* 期限切れ */
}

/*
 *  Webサーバから受け取った http 応答電文から cookie を取り出す
 */

char    *
getCookie( char *cookie )
{
    char    *p = cookie, *q, *r;
    char    *temp = (char *)malloc( strlen( p ) );
    BOOL    skip  = FALSE;
    BOOL    first = TRUE;

    if ( !temp )
        return ( NULL );

    r = temp;
    while ( ( q = strstr( p, "Set-Cookie: " ) ) != NULL ) {
        if ( checkExpire( q + 12 ) ) {
            /* 期限切れの場合 */
            p = q + 12;
            continue;   /* 無視する */
        }
        skip = FALSE;
        if ( first ) {
            q += 4; /* "Set-" 部分を捨てる */
            first = FALSE;
        }
        else {
            *r++ = ';';
            *r++ = ' ';
            q += 12;/* "Set-Cookie: " 部分を捨てる */
        }
        while ( *q && (*q != '\n') && (*q != '\r') ) {
            if ( !skip && (*q == ';') ) {
                /* "; expire=XXXX" 部分を捨てる */
                if ( !strncmpi( q + 1, " expires=", 9 ) ) {
                    skip = TRUE;
                    q += 9;
                }
                else if ( !strncmpi( q + 1, " domain=", 7 ) ) {
                    /* "; domain=XXXX" 部分を捨てる */
                    skip = TRUE;
                    q += 7;
                }
                else if ( !strncmpi( q + 1, " path=", 5 ) ) {
                    /* "; path=XXXX" 部分を捨てる */
                    skip = TRUE;
                    q += 5;
                }
            }
            if ( !skip )
                *r++ = *q;
            q++;
        }
        p = q;
    }
    if ( !first ) {
        *r++ = '\r';
        *r++ = '\n';
    }
    *r = '\0';

    p = temp;
    while ( ( q = strstr( p, "path=/; " ) ) != NULL )
        strcpy( q, q + 8 );

    strcpy( cookie, temp );
    free( temp );

    return ( cookie );
}

char    *
joinCookie( char *cookieNew, const char *cookieOld )
{
    COOKIE_INFO *cp;
    char        *p, *q, *r;
    int         cnt = 0;
    size_t      len = strlen( cookieNew ) + strlen( cookieOld );

    assert( len < MAX_COOKIE_LEN );

    r = (char *)malloc( len + 1 );
    if ( r ) {
        /* cookieNew := cookieOld + cookieNew */
        strcpy( r, cookieOld );
        p = &(r[strlen(r) - 2]);
        q = strstr( cookieNew, ": " );
        if ( p && q ) {
            *p++ = ';';
            *p++ = ' ';
            *p   = NUL;
            q += 2;
            strcpy( p, q );
            strcpy( cookieNew, r );
            free( r );
        }
    }
    else {
#if 0
        /* cookieNew := cookieNew + cookieOld */
        p = &(cookieNew[strlen(cookieNew) - 2]);
        q = strstr( cookieOld, ": " );
        if ( p && q ) {
            *p++ = ';';
            *p++ = ' ';
            *p   = NUL;
            q += 2;
            strcpy( p, q );
        }
#else
        return ( cookieNew );
#endif
    }

    p = cookieNew;
    r = p + (strlen( p ) - 1);
    while ( ( q = strchr( p, ';' ) ) != NULL ) {
        cnt++;
        p = q + 1;
        if ( p >= r )
            break;
    }

    if ( cnt > 1 ) {
        cp = (COOKIE_INFO *)createCookie();
        p = saveCookie( cp, cookieNew );
        if ( p )
            strcpy( cookieNew, p );
        destroyCookie( cp );
    }

    return ( cookieNew );
}
