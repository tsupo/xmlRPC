/*
 *  bulkfeed.c
 *
 * History:
 * $Log: /comm/xmlRPC/bulkfeed.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 22    08/11/17 21:42 Tsujimura543
 * static char → Thread static char に変更
 * 
 * 21    08/09/09 17:33 Tsujimura543
 * searchEntryOnFeedback() を廃止
 * 
 * 20    07/03/03 14:59 Tsujimura543
 * FeedBack に関するコメントを追加
 * 
 * 19    07/03/03 14:59 Tsujimura543
 * utf2sjis(), sjis2utf() が NULL を返す場合に以降の処理で落ちる不具合に対処
 * 
 * 18    06/11/20 18:48 Tsujimura543
 * ↓ とかやっても埒があかないので、最初に実測しておいて、その値を使って
 *     メモリを確保するようにしてみた(ら、今までと実測値が全然違う。何か別
 *     の潜在バグがあるのかも?)
 * 
 * 17    06/11/20 18:32 Tsujimura543
 * extractAnalyseOnBulkfeeds() 内で malloc() する request のサイズがまだ
 * 足りないことがあるようなので、実際の計測値を参考に大き目の値を設定して
 * みた
 * 
 * 16    06/11/16 19:42 Tsujimura543
 * 実行する必要のない memset() を削除
 * 
 * 15    06/11/16 19:37 Tsujimura543
 * extractAnalyseOnBulkfeeds() 内で malloc() する request のサイズをさらに
 * 増やした
 * 
 * 14    06/07/24 20:10 Tsujimura543
 * _httpExecute() のバッファオーバーラン防止機能を利用するようにした
 * 
 * 13    06/02/09 16:37 Tsujimura543
 * extractAnalyseOnBulkfeeds() 内の受信バッファサイズを増量
 * 
 * 12    06/02/02 22:11 Tsujimura543
 * getTerms() を修正
 * 
 * 11    06/02/02 15:31 Tsujimura543
 * extractAnalyseOnBulkfeeds() を修正 (API の URL が間違っていた)
 * 
 * 10    05/05/18 16:36 Tsujimura543
 * searchEntryOnFeedback() を追加
 * 
 * 9     05/05/18 16:29 Tsujimura543
 * searchRssOnBulkfeeds() の処理を若干修正。暫定仕様であることを明記。
 * 
 * 8     05/05/18 14:25 Tsujimura543
 * extractFeatureWordsOnBulkfeeds() と extractAnalyseOnBulkfeeds() の
 * 引数を2個追加
 * 
 * 7     05/05/17 18:58 Tsujimura543
 * getRssUrlOnBulkfeeds() の返す文字列を RSS の URL そのものに変更
 * 
 * 6     05/04/28 11:25 Tsujimura543
 * updateRssOnBulkfeeds() の戻り値の型を int から BOOL に変更
 * 
 * 5     04/11/15 17:06 Tsujimura543
 * encodeURL() 内で確保した領域の解放処理を追加
 * 
 * 4     04/11/11 11:26 Tsujimura543
 * searchSimilarityOnBulkfeeds() の引数を変更
 * 
 * 3     04/10/27 15:02 Tsujimura543
 * searchEntryOnBulkfeeds() の仕様を変更。キーワード検索した結果(記事一覧)
 * を返すようにした
 * 
 * 2     04/07/07 11:58 Tsujimura543
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/bulkfeed.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/*
 *  Bulkfeeds API
 */

static int
getTerms( const char *buf, int numOfTerms, BF_TERM *terms )
{
    char    *p   = strstr( buf, "<terms about=\"" );
    int     num  = 0;
    int     skip = 14;

    if ( !p ) {
        p = strstr( buf, "<terms>" );
        skip = 7;
    }
    if ( p ) {
        char    *q = strstr( p + skip, "<term>" );
        char    *r = strstr( p + skip, "</terms>" );

        while ( q && (q < r) ) {
            p = q + 6;
            q = strstr( p, "</term>" );
            if ( !q )
                break;

            strncpy( terms[num].term, p, q - p );
            terms[num].term[q - p] = NUL;

            if ( ++num >= numOfTerms )
                break;

            q = strstr( p, "<term>" );
        }
    }

    return ( num );
}


/* Bulkfeeds API Key 設定 */
void
setApiKeyOnBulkfeeds( const char *apiKey )
{
    if ( xmlrpc_p && apiKey && *apiKey )
        strcpy( xmlrpc_p->bulkfeedsAPIkey, apiKey );
}

/* RSS 登録/更新  → weblogUpdates.ping を使用 */

/* RSS/OPML直接指定による登録/更新                               */
/*   GET http://bulkfeeds.net/app/add.xml?url=登録したいRSS/OPML */
BOOL
updateRssOnBulkfeeds( const char *url )
{
    int     res;
    BOOL    ret = FALSE;
    char    rcvBuf[BUFSIZ * 2];
    char    addr[BUFSIZ];
    size_t  sz  = BUFSIZ * 2;

    sprintf( addr, "http://bulkfeeds.net/app/add.xml?url=%s", url );

    setUpReceiveBuffer( rcvBuf, sz );
    res = httpGetBuffer( addr, rcvBuf, FALSE );
    if ( (res != -1) && rcvBuf[0] )
        ret = TRUE;

    return ( ret );
}


/* RSS Feed 検索                                                          */
/*   GET http://bulkfeeds.net/app/search.opml?q=キーワード;field=検索対象 */
/*   GET http://bulkfeeds.net/app/search.rdf?q=キーワード;field=検索対象  */
/*             キーワードは UTF-8 の文字列を URL エンコードしたもの       */
/*             検索対象 は title | description | link のいずれか          */

#define BUFFER_SIZE 2048
#define RCV_BUF_SIZ 102400

int
searchRssOnBulkfeeds( const char *keyword, const char *field, int outputType )
{
    int     ret = 0;
    char    *rcvBuf;
    char    addr[BUFSIZ];
    char    *pp;
    size_t  sz;

    sz = RCV_BUF_SIZ;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( ret );

    pp = sjis2utf( keyword );
    if ( outputType == OUTPUT_RSS )
        sprintf( addr, "http://bulkfeeds.net/app/search.rdf?q=%s&field=%s",
                 encodeURL( pp ? pp : keyword ), field );
    else
        sprintf( addr, "http://bulkfeeds.net/app/search.opml?q=%s&field=%s",
                 encodeURL( pp ? pp : keyword ), field );

    setUpReceiveBuffer( rcvBuf, sz );
    ret = httpGetBuffer( addr, rcvBuf, FALSE );
    if ( (ret != -1) && (rcvBuf[0]) ) {
        /* 注意: 本来は取得した文字列を標準出力に表示するのではなく、 */
        /*       API の呼び出し元に渡すべきであるが、2005年5月18日現  */
        /*       在、blukfeeds の当該 API が機能停止中のため、暫定的  */
        /*       に、標準出力に表示する仕様としている                 */
        if ( strlen( rcvBuf ) < BUFFER_SIZE ) {
            pp = utf2sjis( rcvBuf );
            fputs( pp ? pp : rcvBuf, stdout );
        }
        else {
            char    buf[BUFFER_SIZE];
            char    *p;
            char    *q;

            p = rcvBuf;
            do {
                q = strchr( p, '\n' );
                if ( !q )
                    q = p + strlen( p ) - 1;
                strncpy( buf, p, q - p + 1 );
                buf[q - p + 1] = '\0';
                pp = utf2sjis( buf );
                    fputs( p ? p : buf, stdout );
                p = q + 1;
            } while ( strlen( p ) >= BUFFER_SIZE );
            if ( p && *p ) {
                pp = utf2sjis( p );
                fputs( pp ? pp : p, stdout );
            }
        }
    }

    encodeURL( NULL );
    free( rcvBuf );

    return ( ret );
}

/* RSS Item 全文検索 */
/*   GET http://bulkfeeds.net/app/search2.rdf?q=キーワード                */

int
searchEntryOnBulkfeeds(
        const char *keyword,        // (I) キーワード
        int        *numberOfPosts,  // (I) 取得する記事情報の数
                                    // (O) 実際に取得した記事情報の数
        POSTINF    *postinf         // (O) 取得した記事情報
    )
{
    int     ret = 0;
    char    addr[BUFSIZ];

    sprintf( addr, "http://bulkfeeds.net/app/search2.rdf?q=%s",
             encodeURL( sjis2utf( keyword ) ) );
    ret = getRecentPostTitlesFromRSS( addr, numberOfPosts, postinf );
    encodeURL( NULL );

    return ( ret );
}

/* RSS Similarity Search                                                  */
/*   GET http://bulkfeeds.net/app/similar.rdf?url=アドレス&apikey=APIキー */

int
searchSimilarityOnBulkfeeds(
        const char *url,            // (I) 類似記事を検索したい記事のURL
        const char *apiKey,         // (I) APIキー
        int        *numberOfPosts,  // (I) 取得する記事情報の数
                                    // (O) 実際に取得した記事情報の数
        POSTINF    *postinf         // (O) 取得した記事情報
    )
{
    int         ret = 0;
    const char  *key;
    char        addr[BUFSIZ];

    if ( !apiKey )
        key = xmlrpc_p->bulkfeedsAPIkey;
    else
        key = apiKey;

    sprintf( addr, "http://bulkfeeds.net/app/similar.rdf?url=%s&apikey=%s",
             url, key );
    ret = getRecentPostTitlesFromRSS( addr, numberOfPosts, postinf );

    return ( ret );
}

/* 特徴語上位10語取得                                                         */
/*   GET http://bulkfeeds.net/app/similar.xml?url=アドレス&apikey=APIキー     */
/*    返り値(XML) の例                                                        */
/*      <?xml version="1.0" encoding="utf-8" ?>                               */
/*      <terms about="http://watcher.moe-nifty.com/memo/2004/04/post_1.html"> */
/*      <term>優子</term>                                                     */
/*      <term>小倉</term>                                                     */
/*      <term>BLOODY</term>                                                   */
/*      <term>トレカ</term>                                                   */
/*      <term>種類</term>                                                     */
/*      <term>獣</term>                                                       */
/*      <term>計画</term>                                                     */
/*      <term>付い</term>                                                     */
/*      <term>化</term>                                                       */
/*      <term>“</term>                                                       */
/*      </terms>                                                              */

int
extractFeatureWordsOnBulkfeeds(
        const char *url,        // (I) 特徴語を抽出したい記事のURL
        const char *apiKey,     // (I) APIキー
        int        *numOfTerms, // (I) 取得する特徴語の数 (最大 10個)
                                // (O) 実際に取得した特徴語の数
        BF_TERM    *terms       // (O) 取得した特徴語
    )
{
    int         ret = 0, r;
    const char  *key;
    char        *rcvBuf;
    char        addr[BUFSIZ];
    size_t      sz;

    if ( !url || !(url[0]) || !numOfTerms || !terms )
        return ( ret );

    sz = RCV_BUF_SIZ;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( ret );

    if ( *numOfTerms > 10 )
        *numOfTerms = 10;

    if ( !apiKey )
        key = xmlrpc_p->bulkfeedsAPIkey;
    else
        key = apiKey;

    sprintf( addr, "http://bulkfeeds.net/app/similar.xml?url=%s&apikey=%s",
             encodeURL(url), key );

    setUpReceiveBuffer( rcvBuf, sz );
    r = httpGetBuffer( addr, rcvBuf, FALSE );
    if ( rcvBuf[0] )
        ret = *numOfTerms = getTerms( rcvBuf, *numOfTerms, terms );

    free( rcvBuf );

    return ( ret );
}

/* 形態素解析 + 特徴語抽出                                                        */
/*   GET http://bulkfeeds.net/app/terms.xml?content=解析対象文字列&apikey=APIキー */

int
extractAnalyseOnBulkfeeds(
        const char *content,    // (I) 形態素解析(特徴語抽出)対象の文字列
        const char *apiKey,     // (I) APIキー
        int        *numOfTerms, // (I) 取得する特徴語の数
                                // (O) 実際に取得した特徴語の数
        BF_TERM    *terms       // (O) 取得した特徴語
    )
{
    int         ret = 0;
    const char  *key;
    char        *rcvBuf;
    char        url[MAX_URLLENGTH];
    char        *request;
    char        *p;
    size_t      sz, szTarget;

    if ( !content || !(content[0]) || !numOfTerms || !terms )
        return ( ret );

    sz = MAX_CONTENT_SIZE;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( ret );

    if ( !apiKey )
        key = xmlrpc_p->bulkfeedsAPIkey;
    else
        key = apiKey;

    p = sjis2utf(content);
    if ( p )
        szTarget = strlen(encodeURL(p));
    else
        szTarget = strlen(content) * 18;

    request = (char *)malloc( szTarget + strlen(key) + BUFSIZ );
    if ( !request ) {
        free( rcvBuf );
        return ( ret );
    }

    strcpy( url, "http://bulkfeeds.net/app/terms.xml" );
    sprintf( request, "content=%s&apikey=%s",
             encodeURL( p ? p : content ), key );
    setTargetURL( url );

    setUpReceiveBuffer( rcvBuf, sz );
    http_post( url, "application/x-www-form-urlencoded", request, rcvBuf );
    if ( rcvBuf[0] )
        ret = *numOfTerms = getTerms( rcvBuf, *numOfTerms, terms );
    encodeURL( NULL );

    free( request );
    free( rcvBuf );

    return ( ret );
}

/* RSS Auto Discovery                                                      */
/*   GET http://bulkfeeds.net/app/discover.xml?url=アドレス&apikey=APIキー */
/*    返り値(XML) の例                                                     */
/*      <?xml version="1.0" encoding="UTF-8" ?>                            */
/*      <result about="http://watcher.moe-nifty.com/memo/">                */
/*      <success>http://watcher.moe-nifty.com/memo/index.rdf</success>     */
/*      </result>                                                          */

char    *
getRssUrlOnBulkfeeds( const char *blogUrl, const char *apiKey )
{
    int                 ret = 0;
    const char          *key;
    char                addr[BUFSIZ];
    Thread static char  buf[BUFFER_SIZE];
    size_t              sz  = BUFFER_SIZE;

    if ( !apiKey )
        key = xmlrpc_p->bulkfeedsAPIkey;
    else
        key = apiKey;

    sprintf( addr, "http://bulkfeeds.net/app/discover.xml?url=%s&apikey=%s",
             blogUrl, key );

    setUpReceiveBuffer( buf, sz );
    ret = httpGetBuffer( addr, buf, FALSE );
    if ( buf[0] ) {
        char    *p = strstr( buf, "<success>" ), *q;
        if ( p ) {
            p += 9;
            q = strstr( p, "</success>" );
            if ( q )
                *q = NUL;
            strcpy( buf, p );
        }
        else
            buf[0] = NUL;
    }

    return ( buf );
}


#if 0
/*
 *  FeedBack API
 */

/* RSS Item 全文検索 */
/*   GET http://naoya.dyndns.org/feedback/app/rss?keyword=キーワード */
/*   現在、FeedBack は運用停止中 (再開する予定はない?)               */

int
searchEntryOnFeedback(
        const char *keyword,        // (I) キーワード
        int        *numberOfPosts,  // (I) 取得する記事情報の数
                                    // (O) 実際に取得した記事情報の数
        POSTINF    *postinf         // (O) 取得した記事情報
    )
{
    int     ret = 0;
    char    *p;
    char    addr[BUFSIZ];

    p = sjis2utf( keyword );
    sprintf( addr, "http://naoya.dyndns.org/feedback/app/rss?keyword=%s",
             encodeURL( p ? p : keyword ) );
    ret = getRecentPostTitlesFromRSS( addr, numberOfPosts, postinf );
    encodeURL( NULL );

    return ( ret );
}
#endif
