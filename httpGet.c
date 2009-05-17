/*
 *  httpGet
 *      get a file via http
 *        Copyright (c) 2003 by Hiroshi Tsujimura (tsujimura543@oki.com)
 *        All Right Reserved.
 *
 *      28 July 2003
 *
 * History:
 * $Log: /comm/xmlRPC/httpGet.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 32    08/07/25 23:34 Tsujimura543
 * http_deleteBASIC() を追加
 * 
 * 31    08/01/23 16:41 Tsujimura543
 * http_getW, http_deleteW を追加
 * 
 * 30    07/05/22 0:24 Tsujimura543
 * BASIC認証 + cookie 同時使用対応準備
 * 
 * 29    06/03/10 14:36 Tsujimura543
 * httpGetFileBASIC() 内で使う fopen() のモードを w から wb に変更
 * 
 * 28    06/03/03 16:21 Tsujimura543
 * httpGetFileBASIC() の引数の順序を変更
 * 
 * 27    05/10/18 18:44 Tsujimura543
 * _httpExecute() の引数追加に伴う各種変更を実施
 * 
 * 26    05/06/28 21:29 Tsujimura543
 * httpDeleteBASIC() を修正
 * 
 * 25    05/06/28 15:27 Tsujimura543
 * httpDeleteBASIC() を追加
 * 
 * 24    05/05/24 14:44 Tsujimura543
 * BASIC認証に対応
 * 
 * 23    04/11/24 15:44 Tsujimura543
 * _httpGet() と _httpDelete() を http.c へ移動
 * 
 * 22    04/11/24 15:32 Tsujimura543
 * _httpExecute() を http.c へ移動
 * 
 * 21    04/11/24 15:14 Tsujimura543
 * https://www2.ggn.net/cgi-bin/ssl を GET できることを確認
 * 
 * 20    04/11/19 22:10 Tsujimura543
 * _httpExecute() による POST メソッドの動作の確認終了
 * 
 * 19    04/11/19 21:44 Tsujimura543
 * _httpExecute() を POST メソッドにも対応できるように修正
 * 
 * 18    04/11/19 21:06 Tsujimura543
 * https 対応 (暫定) -- とりあえず、従来の http がデグレードしていない
 * ことを確認
 * 
 * 17    04/11/19 20:45 Tsujimura543
 * https 対応 (暫定)
 * 
 * 16    04/11/17 13:24 Tsujimura543
 * Amazon Web Services 対策として、connectHTTP() で設定する flag の値で
 * 処理を分岐する流れを復活させる
 * 
 * 15    04/11/16 15:20 Tsujimura543
 * 常に HTTP 1.1 にしてみる (Amazon Web Services 3.x 対策)
 * 
 * 14    04/11/05 15:29 Tsujimura543
 * 調査用コード組込み (受信側)
 * 
 * 13    04/10/12 13:46 Tsujimura543
 * (1) 調査用コード組込み
 * (2) HTTPリクエストヘッダに Connection: close を追加
 * 
 * 12    04/10/08 12:18 Tsujimura543
 * httpGetBufferWithSession() の引数追加
 * 
 * 11    04/10/05 16:12 Tsujimura543
 * コメントを整理
 * 
 * 10    04/10/05 16:09 Tsujimura543
 * 302 Moved Temporarily 検出時のみ Location: で指定された URL に移動する
 * はずが、それ以外のときも Location: 指定されている場合に移動してしまって
 * いたのを修正
 * 
 * 9     04/10/05 13:39 Tsujimura543
 * 特定の場合しか Cache-Control: no-cache を付けてなかったのを、
 * 常に付けるようにした (主として livedoor Blog 対策)
 * 
 * 8     04/09/01 16:22 Tsujimura543
 * Location: の先頭が / で始まっている場合の処理を追加
 * 
 * 7     04/08/27 16:13 Tsujimura543
 * Loaction: の URL の後ろにコメントが付いている場合に対処
 * 
 * 6     04/08/27 9:03 Tsujimura543
 * cookie 関係の処理を整理した
 * 
 * 5     04/08/26 22:21 Tsujimura543
 * exciteブログに投稿できることを確認
 * 
 * 4     04/07/14 9:15 Tsujimura543
 * X-WSSE: 付加時以外も Host: を付加するようにした
 * 
 * 3     04/07/09 14:37 Tsujimura543
 * コメントを修正
 *
 * 1     04/07/07 11:24 Tsujimura543
 * RCS による版数管理から VSS による版数管理に移行
 *
 * Revision 1.6  2003/12/25  03:22:36  tsujimura543
 * HTTP responseヘッダ 表示機能を付加 (-hオプション)
 *
 * Revision 1.5  2003/09/26  05:04:23  tsujimura543
 * コメントの一部の漢字コードが ISO-2022-JP になっていたのを Shift_JIS に変更
 * (コメントのみの変更)
 *
 * Revision 1.4  2003/09/26  00:21:33  tsujimura543
 * HTTP リクエストヘッダに User-Agent: を含めるようにした。
 *
 * Revision 1.3  2003/09/16  06:56:49  tsujimura543
 * Windows 環境の場合、proxy.txt が存在しなければ、レジストリからproxy情報を
 * 取得するようにした。
 *
 * Revision 1.2  2003/09/02  04:47:31  tsujimura543
 * When -p specified, if not found 'proxy.txt', then finish the process.
 *
 * Revision 1.1  2003/09/02  04:41:52  tsujimura543
 * Initial revision
 *
 */

#include "xmlRPC.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/httpGet.c 1     09/05/14 3:46 tsupo $";
#endif


/*
 *  HTTPリクエストのGETメソッド関連処理群
 */


/*
 *  httpGet() --- get a web page
 *      arguments: 
 *          char *webServer;   web server which has target web page
 *          char *webPage;     target web page
 *          FILE *output;      stream for writing as target web page
 *      return: if get OK, returns TRUE; else returns FALSE
 */

int
httpGet( const char *webServer, const char *webPage,
         char *rcvBody, FILE *output, int printHead,
         const char *wsse,
         char *p3p, char *cookie,
         char *webServerRedirected, char *cookieRedirected )
{
    return ( _httpGet( webServer, webPage,
                       NULL, NULL,
                       rcvBody, output, printHead, wsse,
                       p3p, cookie,
                       webServerRedirected, cookieRedirected ) );
}

int
httpGetBASIC( const char *webServer, const char *webPage,
              const char *userName,  const char *password,
              char *rcvBody, FILE *output, int printHead,
              const char *wsse,
              char *p3p, char *cookie,
              char *webServerRedirected, char *cookieRedirected )
{
    return ( _httpGet( webServer, webPage,
                       userName, password,
                       rcvBody, output, printHead, wsse,
                       p3p, cookie,
                       webServerRedirected, cookieRedirected ) );
}


/* for Atom API */
int
httpGetEx( const char *webServer, const char *webPage,
           char *rcvBody, FILE *output, int printHead,
           const char *wsse )
{
    return ( _httpGet( webServer, webPage,
                       NULL, NULL,
                       rcvBody, output, printHead, wsse,
                       NULL, NULL,
                       NULL, NULL ) );
}

int
httpDeleteEx( const char *webServer, const char *webPage,
              char *rcvBody, FILE *output, int printHead,
              const char *wsse )
{
    return ( _httpDelete( webServer, webPage,
                          NULL, NULL,
                          rcvBody, output, printHead, wsse ) );
}


int
httpGetFile( const char *uri, const char *filename,
             int printHead )
{
    return ( httpGetFileBASIC( uri, filename, NULL, NULL, printHead ) );
}

int
httpGetFileBASIC( const char *uri, const char *filename,
                  const char *userName, const char *password,
                  int printHead )
{
    int     ret = 0;
    FILE    *fp;

    setTargetURL( uri );
    if ( ( fp = fopen( filename, "wb" ) ) != NULL ) {
        ret = httpGetBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                            userName, password,
                            NULL, fp, printHead, NULL, NULL, NULL,
                            NULL, NULL );
        fclose( fp );
    }

    return ( ret );
}


int
httpGetBuffer( const char *uri,
               char *rcvBuf, int printHead )
{
    return ( httpGetBufferBASIC( uri, NULL, NULL, rcvBuf, printHead ) );
}

int
httpGetBufferBASIC( const char *uri,
                    const char *userName, const char *password,
                    char *rcvBuf, int printHead )
{
    int     ret     = 0;
    char    *cookie = NULL;

#if 0
    if ( xmlrpc_p->proxyUserName[0] ) {
        cookie = (char *)malloc( MAX_COOKIE_LEN );
        if ( cookie )
            memset( cookie, 0x00, MAX_COOKIE_LEN );
    }
#endif

    setTargetURL( uri );
    ret = httpGetBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        userName, password,
                        rcvBuf, NULL, printHead, NULL, NULL,
                        cookie,
                        NULL, NULL );

#if 0
    if ( cookie )
        free( cookie );
#endif

    return ( ret );
}


int
httpGetBufferWithSession( const char *uri,
                          char       *rcvBuf,
                          int        printHead,
                          const char *wsse,
                          char       *p3p,
                          char       *cookie,
                          char       *webServerRedirected,
                          char       *cookieRedirected )
{
    int     ret = 0;

    setTargetURL( uri );
    ret = httpGet( xmlrpc_p->webServer, xmlrpc_p->webPage,
                   rcvBuf, NULL, printHead, wsse, p3p, cookie,
                   webServerRedirected, cookieRedirected );

    return ( ret );
}


/* for blogger.com Atom API -- http DELETE メソッド実行(BASIC認証対応版 -- */
int
httpDeleteBASIC( const char *webServer, const char *webPage,
                 const char *userName,  const char *password,
                 char *response, FILE *output, int printHead,
                 const char *wsse )
{
    return ( _httpDelete( webServer, webPage,
                          userName, password,
                          response, output, printHead, wsse ) );
}


// for Atom PP
char    *
http_getW( const char *url, const char *wsse,
           const char *userName, const char *password,
           char *response )
{
    setTargetURL( url );
    httpGetBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  userName, password,
                  response, NULL, FALSE,
                  wsse,
                  NULL, NULL,
                  NULL, NULL );

    return ( response );
}

char    *
http_deleteW( const char *url, const char *wsse,
              const char *userName, const char *password,
              char *response )
{
    setTargetURL( url );
    httpDeleteBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     userName, password,
                     response, NULL, FALSE,
                     wsse );

    return ( response );
}


// for RESTful API (cf. Diigo)
char    *
http_deleteBASIC( const char *url,
                  const char *userName, const char *password,
                  const char *mimeType, const char *request,
                  char *response )
{
    int stackCount = 0;

    setTargetURL( url );

    _httpExecute( "DELETE",
                  xmlrpc_p->webServer, xmlrpc_p->webPage,
                  mimeType, request,
                  userName, password,
                  response, NULL, FALSE,
                  NULL, NULL, NULL,
                  NULL, NULL, stackCount );

    return ( response );
}
