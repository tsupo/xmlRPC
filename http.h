/*
 *  http.h
 *
 * History:
 * $Log: /comm/xmlRPC/http.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     08/12/02 21:07 Tsujimura543
 * コメント中の綴りミスを発見、修正
 * 
 * 8     07/09/14 22:39 Tsujimura543
 * MAX_URLLENGTH_MAX の定義を xmlRPC.h に移動
 * 
 * 7     06/09/26 18:50 Tsujimura543
 * MAX_URLLENGTH_MAX の定義を http.c から http.h へ移す
 * 
 * 6     05/10/18 18:46 Tsujimura543
 * _httpExecute() の引数追加に伴う各種変更を実施
 * 
 * 5     05/06/28 15:22 Tsujimura543
 * _httpPost() を BASIC認証対応化
 * 
 * 4     05/05/31 22:50 Tsujimura543
 * _httpExecute() のプロトタイプ宣言を修正
 * 
 * 3     05/05/24 14:43 Tsujimura543
 * BASIC認証に対応
 * 
 * 2     04/11/24 15:48 Tsujimura543
 * http 関連共通関数を整理
 * 
 * 1     04/11/24 15:29 Tsujimura543
 * _httpExecute() のプロトタイプ宣言をヘッダファイルに移動
 */

#ifndef __HTTP_H__
#define __HTTP_H__

/* HTTPリクエスト実行処理本体 */
int
_httpExecute( const char *method,
              const char *webServer, const char *webPage,
              const char *mimeType,/* ← 必要なのは POST, PUT のみ */
              const char *sndBody, /* ← 必要なのは POST, PUT のみ */
              const char *userName,/* ← 必要なのは BASIC認証使用時のみ */
              const char *password,/* ← 必要なのは BASIC認証使用時のみ */
              char *rcvBody, FILE *output, int printHead,
              const char *wsse, char *p3p, char *cookie,
              char *webServerRedirected,    /* for TypeKey */
              char *cookieRedirected,       /* for TypeKey */
              int stackCount );

int
_httpGet( const char *webServer, const char *webPage,
          const char *userName,/* ← 必要なのは BASIC認証使用時のみ */
          const char *password,/* ← 必要なのは BASIC認証使用時のみ */
          char *rcvBody, FILE *output, int printHead,
          const char *wsse, char *p3p, char *cookie,
          char *webServerRedirected, char *cookieRedirected );

int
_httpDelete( const char *webServer, const char *webPage,
             const char *userName,/* ← 必要なのは BASIC認証使用時のみ */
             const char *password,/* ← 必要なのは BASIC認証使用時のみ */
             char *rcvBody, FILE *output, int printHead,
             const char *wsse );

int
_httpPost( const char *webServer, const char *webPage,
           const char *userName,/* ← 必要なのは BASIC認証使用時のみ */
           const char *password,/* ← 必要なのは BASIC認証使用時のみ */
           const char *mimeType,
           const char *sndBody, char *rcvBody,
           const char *wsse,    char *cookie,
           char *webServerRedirected, char *cookieRedirected );

#endif  /* __HTTP_H__ */
