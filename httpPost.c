/*
 *  httpPost
 *      XML-RPC client (send request and receive result via http)
 *        Copyright (c) 2003, 2004 by Hiroshi Tsujimura (tsupo@na.rim.or.jp)
 *        All Right Reserved.
 *
 *      02 Nov 2003
 *
 * History:
 * $Log: /comm/xmlRPC/httpPost.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 27    08/01/23 16:40 Tsujimura543
 * http_postW, http_putW を追加
 * 
 * 26    05/10/18 18:44 Tsujimura543
 * _httpExecute() の引数追加に伴う各種変更を実施
 * 
 * 25    05/06/28 22:06 Tsujimura543
 * httpPutBASIC() に引数 mimeType を追加
 * 
 * 24    05/06/28 15:23 Tsujimura543
 * httpPostBASIC() と httpPutBASIC() を追加
 * 
 * 23    05/05/31 22:51 Tsujimura543
 * httpPutEx() を追加
 * 
 * 22    04/11/24 15:46 Tsujimura543
 * _http_post() を http.c へ移動
 * 
 * 21    04/11/24 15:37 Tsujimura543
 * connectHTTP(), disconnectHTTP(), sendHTTP(), recvHTTP() を http.c へ移動
 * 
 * 20    04/11/19 22:11 Tsujimura543
 * _httpPost() の本体を _httpExecute() に統合
 * 
 * 19    04/11/19 21:05 Tsujimura543
 * https 対応 (暫定) -- とりあえず、従来の http がデグレードしていない
 * ことを確認
 * 
 * 18    04/11/17 13:24 Tsujimura543
 * Amazon Web Services 対策として、connectHTTP() で設定する flag の値で
 * 処理を分岐する流れを復活させる
 * 
 * 17    04/11/05 15:29 Tsujimura543
 * 調査用コード組込み (受信側)
 * 
 * 16    04/11/01 21:02 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 15    04/10/12 13:46 Tsujimura543
 * (1) 調査用コード組込み
 * (2) HTTPリクエストヘッダに Connection: close を追加
 * 
 * 14    04/10/08 12:20 Tsujimura543
 * 302 で Location 移動が発生する場合、HTTP POST ではなく HTTP GET で
 * 移動するように修正 (無限にリダイレクトされ続けるのを避けるため)
 * 
 * 13    04/10/05 16:10 Tsujimura543
 * 302 Moved Temporarily 検出時のみ Location: で指定された URL に移動する
 * はずが、それ以外のときも Location: 指定されている場合に移動してしまって
 * いたのを修正
 * 
 * 12    04/10/05 13:40 Tsujimura543
 * 念のために Cache-Control: no-cache を付加するようにしてみた。
 * 
 * 11    04/09/02 20:40 Tsujimura543
 * getCookie() を cookie.c に移動
 * 
 * 10    04/09/01 22:12 Tsujimura543
 * マイプロフィール対応 (暫定)
 * 
 * 9     04/09/01 16:22 Tsujimura543
 * Location: の先頭が / で始まっている場合の処理を追加
 * 
 * 8     04/08/27 16:13 Tsujimura543
 * Loaction: の URL の後ろにコメントが付いている場合に対処
 * 
 * 7     04/08/27 9:03 Tsujimura543
 * cookie 関係の処理を整理した
 * 
 * 6     04/08/26 22:20 Tsujimura543
 * exciteブログに投稿できることを確認
 * 
 * 5     04/08/25 16:58 Tsujimura543
 * cookie の送受信を伴う post メソッドに対応
 * 
 * 4     04/07/09 14:36 Tsujimura543
 * コメントを修正
 *
 * 1     04/07/07 11:24 Tsujimura543
 * RCS による版数管理から VSS による版数管理に移行
 *
 * Revision 1.1  2003/11/02 15:04:46  tsupo
 * Initial revision
 *
 */

#include "xmlRPC.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/httpPost.c 1     09/05/14 3:46 tsupo $";
#endif


/*
 *  HTTPリクエストのPOSTメソッド関連処理群
 */

/*
 *  httpPost() --- post a XML-RPC request via httpd process
 *      arguments: 
 *          char *webServer;   web server which has target web page
 *          char *webPage;     target web page
 *      return: if get OK, returns 0; else returns non 0 value
 *              (if detected disconnection before receiving target web page,
 *               returns -2)
 */

int
httpPost( const char *webServer, const char *webPage,
          const char *mimeType,
          const char *request, char *response )
{
    return ( _httpPost( webServer, webPage,
                        NULL, NULL,
                        mimeType,
                        request, response, NULL, NULL,
                        NULL, NULL ) );
}


int
httpPostEx2( const char *webServer, const char *webPage,
             const char *request,   char *response,
             const char *wsse )
{
    return ( _httpPost( webServer, webPage,
                        NULL, NULL,
                        NULL,
                        request, response, wsse, NULL,
                        NULL, NULL ) );
}

int
httpPostWithSession( const char *webServer, const char *webPage,
                     const char *mimeType,
                     const char *sndBody, char *rcvBody, char *cookie,
                     char *webServerRedirected, char *cookieRedirected )
{
    return ( _httpPost( webServer, webPage,
                        NULL, NULL,
                        mimeType,
                        sndBody, rcvBody, NULL, cookie,
                        webServerRedirected, cookieRedirected ) );
}

/* for blogger.com Atom API -- http POST メソッド実行(BASIC認証対応版 -- */
int
httpPostBASIC( const char *webServer, const char *webPage,
               const char *userName,  const char *password,
               const char *mimeType,
               const char *request,   char *response )
{
    return ( _httpPost( webServer, webPage,
                        userName, password,
                        mimeType,
                        request, response, NULL, NULL,
                        NULL, NULL ) );
}


/*
 *  HTTPリクエストのPUTメソッド関連処理群
 */

int
httpPutEx( const char *webServer, const char *webPage,
           const char *request,   char *response,
           const char *wsse )
{
    return ( httpPutBASIC( webServer, webPage,
                           NULL, NULL,
                           NULL,
                           request, response,
                           wsse ) );
}

/* for blogger.com Atom API -- http PUT メソッド実行(BASIC認証対応版 -- */
int
httpPutBASIC( const char *webServer, const char *webPage,
              const char *userName,  const char *password,
              const char *mimeType,
              const char *request,   char *response,
              const char *wsse )
{
    int stackCount = 0;
    int ret;

    ret = _httpExecute( "PUT",
                        webServer, webPage,
                        mimeType, request,
                        userName, password,
                        response, NULL, FALSE,
                        wsse, NULL, NULL,
                        NULL, NULL,
                        stackCount );

    return ( ret );
}



// for Atom PP

char    *
http_postW( const char *url, const char *wsse,
            const char *userName, const char *password,
            const char *request, char *response )
{
    setTargetURL( url );
    _httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
               userName, password,
               NULL,
               request, response, wsse, NULL,
               NULL, NULL );

    return ( response );
}

char    *
http_putW( const char *url, const char *wsse,
           const char *userName, const char *password,
           const char *request, char *response )
{
    setTargetURL( url );
    httpPutBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  userName, password,
                  NULL,
                  request, response,
                  wsse );

    return ( response );
}
