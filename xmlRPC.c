/*
 *  xmlRPC.c
 *      xmlRPC.dll のメインエントリポイント
 *
 * History:
 * $Log: /comm/xmlRPC/xmlRPC.c $
 * 
 * 2     09/06/02 2:49 tsupo
 * 1.268版
 * 
 * 36    09/06/01 16:21 Tsujimura543
 * amazonAccessKeyID と amazonAccessKeySecret を追加
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 35    09/03/30 19:48 Tsujimura543
 * OAuth 対応
 * 
 * 34    08/09/10 23:52 Tsujimura543
 * ソースを整理 (コメントアウトしてあったコードを削除)
 * 
 * 33    08/09/09 21:23 Tsujimura543
 * 不要になった機能を削除 (その3)
 * 
 * 32    08/09/09 17:52 Tsujimura543
 * 不要になった機能を削除
 * 
 * 31    08/05/15 23:23 Tsujimura543
 * 外部公開用関数として getStatusCode() を追加
 * 
 * 30    08/01/29 17:25 Tsujimura543
 * bk1ブリーダー関連のコードを削除
 * (すでにbk1ブリーダー制度は廃止されている)
 * 
 * 29    07/12/20 15:20 Tsujimura543
 * Visual Studio 2005 によるコンパイルチェック結果を反映
 * 
 * 28    07/12/19 20:55 Tsujimura543
 * startup を追加 (for connectHTTP)
 * 
 * 27    07/09/10 19:05 Tsujimura543
 * 各種Webサービス関連で使用していないものをオプション化(実質、廃止)
 * 
 * 26    07/09/04 20:21 Tsujimura543
 * verboseFp を追加
 * 
 * 25    07/09/04 20:09 Tsujimura543
 * dumpFp を追加
 * 
 * 24    07/08/24 18:38 Tsujimura543
 * setReferer() を追加
 * 
 * 23    07/04/09 17:36 Tsujimura543
 * rurl.org API 関連処理を追加
 * 
 * 22    07/03/09 21:13 Tsujimura543
 * isNecessaryToCheckProxyInfo() を追加、およびそれに伴う修正を実施
 * 
 * 21    07/03/09 16:59 Tsujimura543
 * XMLRPC構造体に confirmProxyInfo を追加
 * 
 * 20    07/03/06 23:33 Tsujimura543
 * typo 修正
 * 
 * 19    07/03/02 11:42 Tsujimura543
 * じゃらんWebサービスAPIキー 対応
 * 
 * 18    07/01/17 19:26 Tsujimura543
 * 楽天デベロッパーID 対応
 * 
 * 17    07/01/17 16:54 Tsujimura543
 * Windows の「言語」の取得、設定用の関数を追加
 * 
 * 16    06/12/23 0:09 Tsujimura543
 * proxy 使用時の https 接続のときのヘッダ部分が http でなければいけない
 * サーバ、https でなければいけないサーバ、どちらでもいいサーバのどの
 * パターンにも対応するため、フラグを1個追加し、対応した 
 * 
 * 15    06/10/07 1:34 Tsujimura543
 * http(応答受信待ち)タイムアウト時間を設定変更できるようにした
 * 
 * 14    06/09/15 14:42 Tsujimura543
 * バリューコマース関連の記憶領域を廃止
 * 
 * 13    06/09/11 12:05 Tsujimura543
 * コメントを追加
 * 
 * 12a   06/09/10 5:48 tsupo
 * resetDaylightSaving() を導入した
 * (Visual Studio 2005 の C++ ランタイム使用時に、日本時間なのに夏時間と
 * 判定されてしまう件の対策)
 * 
 * 12    06/09/02 1:12 Tsujimura543
 * http通信実行中かどうかをチェックできる関数を追加した
 * 
 * 11    06/01/13 16:03 Tsujimura543
 * dwsEmail, dwsHID を追加
 * 
 * 10    06/01/10 15:12 Tsujimura543
 * userAgent / setUserAgent() を追加
 * 
 * 9     05/12/14 13:37 Tsujimura543
 * Yahoo! Japan 検索WebサービスAPI対応準備
 * 
 * 8     05/11/17 21:31 Tsujimura543
 * http による送信可能な電文サイズの上限をメモリの許す限りどこまでも
 * 大きくできるようにした (初期サイズは従来の値)
 * 
 * 7     05/09/02 14:38 Tsujimura543
 * affiriate → affiliate に修正 (綴り間違い)
 * 
 * 6     05/05/19 13:36 Tsujimura543
 * vcPublicID03 と vcPublicID04 の初期化を追加
 * 
 * 5     04/11/19 14:51 Tsujimura543
 * SSL 関連メンバの初期化を追加
 * 
 * 4     04/11/04 15:53 Tsujimura543
 * Amazon E-Commerce Service 4.0 対応準備
 * 
 * 3     04/10/08 15:08 Tsujimura543
 * vcPublicID02 の初期化を追加
 * 
 * 2     04/07/07 11:53 Tsujimura543
 *
 */

#include "xmlRPC.h"
#include <time.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/xmlRPC.c 2     09/06/02 2:49 tsupo $";
#endif


XMLRPC_t    xmlrpc_p = NULL;


#pragma warning( disable : 4100 )

/*
 *  DLL エントリポイント
 */

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch ( ul_reason_for_call ) {
    case DLL_PROCESS_ATTACH:
        xmlrpc_p = (XMLRPC_t)malloc( sizeof ( XMLRPC ) );
        if ( xmlrpc_p ) {
            memset( xmlrpc_p, 0x00, sizeof ( XMLRPC ) );
            xmlrpc_p->scdHTTP = (DWORD)-1;
            xmlrpc_p->rcvHTTPbufferSize  = RCV_BUFFER_SIZE;
            xmlrpc_p->sndHTTPmessageSize = 0;
            xmlrpc_p->rcvHTTPmessageSize = 0;
            xmlrpc_p->proxyPort   = 0;
            xmlrpc_p->blogKind    = BLOGKIND_UNKNOWN;
            xmlrpc_p->useSSL      = FALSE;
            xmlrpc_p->recoverySSL = FALSE;
            xmlrpc_p->useProxy    = FALSE;
            xmlrpc_p->verbose     = FALSE;
            xmlrpc_p->verboseFp   = stderr;
#if defined (_DEBUG) || defined (CHECK_DETAIL)
            xmlrpc_p->dump        = FALSE;
            xmlrpc_p->dumpFp      = NULL;
#endif
            xmlrpc_p->active      = FALSE;
            xmlrpc_p->workArea1   = NULL;
            xmlrpc_p->workArea2   = NULL;
            xmlrpc_p->initialized = initializeSocket();
            strcpy( xmlrpc_p->dataDir, "./" );
            strcpy( xmlrpc_p->keywordList, "keyword.lst" );
            strcpy( xmlrpc_p->bulkfeedsAPIkey,       BULKFEEDS_API_KEY );
            strcpy( xmlrpc_p->amazonAssociateID,     AMAZON_ASSOCIATE_ID );
            strcpy( xmlrpc_p->amazonSubscriptionID,  AMAZON_SUBSCRIPTION_ID );
            strcpy( xmlrpc_p->amazonAccessKeyID,     AMAZON_ASSOCIATE_ID );
            strcpy( xmlrpc_p->amazonAccessKeySecret, AMAZON_SUBSCRIPTION_ID );
            strcpy( xmlrpc_p->rakutenDeveloperID,    RAKUTEN_DEVELOPER_ID );
            strcpy( xmlrpc_p->rakutenAffiliateID,    RAKUTEN_AFFILIATE_ID );
            strcpy( xmlrpc_p->rakutenAffiliateID2,   RAKUTEN_AFFILIATE_ID2 );
            xmlrpc_p->userAgent[0] = NUL;
            xmlrpc_p->referer[0]   = NUL;

            xmlrpc_p->sndHTTP = (char *)malloc( SND_BUFFER_SIZE );
            if ( xmlrpc_p->sndHTTP == NULL )
                return ( FALSE );
            memset( xmlrpc_p->sndHTTP, 0x00, SND_BUFFER_SIZE );
            xmlrpc_p->sndHTTPBufferSize = SND_BUFFER_SIZE;
            xmlrpc_p->timedoutTime = DEFAULT_HTTP_TIMEOUT;
            xmlrpc_p->languageCode = GetThreadLocale();
            xmlrpc_p->confirmProxyInfo     = NULL;
            xmlrpc_p->needToCheckProxyInfo = FALSE;
            xmlrpc_p->startup = (long) time( NULL );
            xmlrpc_p->statusCode = 0;
#ifdef  USE_AUTHORIZATION_OAUTH
            xmlrpc_p->oauth_header[0] = NUL;
#endif

            InitializeCriticalSection( &xmlrpc_p->critic );
#if (WINVER >= 0x0500)
#ifdef  _MSC_VER
            resetDaylightSaving();
#endif
#endif
        }
        break;

    case DLL_THREAD_ATTACH:
        if ( !xmlrpc_p || !(xmlrpc_p->initialized) )
            return ( FALSE );
        break;

    case DLL_PROCESS_DETACH:
        if ( xmlrpc_p ) {
            if ( xmlrpc_p->initialized ) {
                finalizeSocket();
                xmlrpc_p->initialized = 0;
            }
            if ( xmlrpc_p->sndHTTP ) {
                free( xmlrpc_p->sndHTTP );
                xmlrpc_p->sndHTTP = NULL;
                xmlrpc_p->sndHTTPBufferSize = 0;
            }
            DeleteCriticalSection( &xmlrpc_p->critic );
            free( (char *)xmlrpc_p );
            xmlrpc_p = NULL;
        }
        break;

    case DLL_THREAD_DETACH:
        break;

    default:
        break;
    }

    return ( TRUE );
}

#pragma warning( default : 4100 )
