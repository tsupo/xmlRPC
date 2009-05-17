/*
 *  http.c
 *      http サポートモジュール
 *
 * History:
 * $Log: /comm/xmlRPC/http.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 110   09/03/30 19:48 Tsujimura543
 * OAuth 対応
 * 
 * 109   08/12/02 21:07 Tsujimura543
 * コメント中の綴りミスを発見、修正
 * 
 * 108   08/11/21 15:10 Tsujimura543
 * restructCookie() に対して Wassr (sledge) 向け暫定対策を実施
 * 
 * 107   08/11/17 10:07 Tsujimura543
 * connectHTTP() の「サーバが見つからない」ときの MessageBox() 実行
 * 条件を変更 (verbose が指定されているときのみ実行する)
 * 
 * 106   08/08/01 2:44 Tsujimura543
 * XXX-Location: (XXX は任意の文字列) が http レスポンスヘッダに
 * 含まれる場合、そちらで指示されている URL にリダイレクトしてしまう
 * 不具合に対処
 * 
 * 105   08/05/15 23:23 Tsujimura543
 * 外部公開用関数として getStatusCode() を追加
 * 
 * 104   07/12/19 20:54 Tsujimura543
 * tinyurl のみの特別な対策は廃止。汎用的な対策に移行
 * 
 * 103   07/12/13 22:23 Tsujimura543
 * 暫定的に tinyurl 対策を入れてみた (connectHTTP)
 * 
 * 102   07/12/06 1:16 Tsujimura543
 * _httpExecute() でバイナリファイルの送信に対応するための修正を実施
 * 
 * 101   07/11/26 19:31 Tsujimura543
 * connect() 時に WSAETIMEDOUT が発生した場合は、すぐエラーリターンする
 * ようにした
 * 
 * 100   07/10/10 2:02 Tsujimura543
 * http_postEx() 内のデバッグ情報出力部分を修正 (長い文字列を出力しようと
 * して落ちることがある不具合に対処するための修正)
 * 
 * 99    07/10/09 20:15 Tsujimura543
 * dputs(), dprintf() を導入
 * 
 * 98    07/10/02 18:20 Tsujimura543
 * 「レスポンスヘッダ部をファイルに出力する機能」を呼び出す箇所を変更
 * 
 * 97    07/10/01 20:44 Tsujimura543
 * レスポンスヘッダ部をファイルに出力する機能を追加 (出力されない場合も
 * あるので、あとで見直す)
 * 
 * 96    07/09/20 20:43 Tsujimura543
 * リダイレクト発生時の Referer: の付け替えをする/しない関連の修正
 * 
 * 95    07/09/19 21:40 Tsujimura543
 * BBAuth 対応作業中 (あとでソースの整理を実施する)
 * 
 * 94    07/09/14 23:17 Tsujimura543
 * リダイレクト発生時、Referer: を設定するようにした
 * 
 * 93    07/09/07 20:52 Tsujimura543
 * http通信のスレッド間排他制御対応
 * 
 * 92    07/09/05 0:26 Tsujimura543
 * Release ビルド版は verbose が TRUE なら、recv() したデータの中身を
 * dump するようにしてみた
 * 
 * 91    07/09/04 22:26 Tsujimura543
 * verboseFp を導入。詳細なログを残せるようにした
 * 
 * 90    07/08/29 16:07 Tsujimura543
 * http_headBASIC() を追加
 * 
 * 89    07/08/22 22:17 Tsujimura543
 * ステータスコード 303 に対応 (Jaiku 向け)
 * 
 * 88    07/08/10 23:18 Tsujimura543
 * http_getBASICEx() を追加
 * 
 * 87    07/07/02 17:48 Tsujimura543
 * _httpRedirect() を再修正 (nullポインタ参照エラーで落ちることがある)
 * 
 * 86    07/06/29 22:02 Tsujimura543
 * TypeKey 認証に失敗するようになってしまったため、対策を実施
 * (いつから失敗するようになったのかは不明)
 * 
 * 85    07/06/04 19:33 Tsujimura543
 * connectHTTP() を修正、「確認してください」ダイアログを表示する
 * 条件を変更した
 * 
 * 84    07/05/25 17:37 Tsujimura543
 * statusCode == 407 時の retry 処理を追加
 * 
 * 83    07/05/23 19:47 Tsujimura543
 * リファクタリング
 * 
 * 82    07/05/23 17:46 Tsujimura543
 * recvHTTP() の返す受信データが細切れになる場合にレスポンス本体を
 * _httpExecute() の呼び出し元にきちんと返せないことがある不具合に対処
 * 
 * 81    07/05/22 22:36 Tsujimura543
 * デグレード箇所を修正 [バイナリファイル受信関連]
 * 
 * 80    07/05/22 19:35 Tsujimura543
 * デグレード箇所を修正(つづき) [fix]
 * 
 * 79    07/05/22 19:02 Tsujimura543
 * デグレード箇所を修正(つづき)
 * 
 * 78    07/05/22 18:01 Tsujimura543
 * ユーザ名とパスワードが必要な proxyサーバを使う場合の処理の実装時に
 * デグレードしてしまった箇所の修正を実施
 * 
 * 77    07/05/22 0:27 Tsujimura543
 * ユーザ名とパスワードが必要な proxyサーバを使っての https 通信に
 * 対応 (メモリ破壊発生箇所を特定。修正済み)
 * 
 * 76    07/05/21 19:56 Tsujimura543
 * ユーザ名とパスワードが必要な proxyサーバを使っての https 通信に
 * 対応 (どこかでメモリ破壊が起きている可能性あり。調査中)
 * 
 * 75    07/05/21 13:58 Tsujimura543
 * ユーザ名とパスワードが必要な proxyサーバを使っての Web アクセスに
 * 対応する処理全般を書き直し。動作確認済み
 * 
 * 74    07/04/11 21:57 Tsujimura543
 * さらに application/json 対策を追加
 * 
 * 73    07/04/11 21:54 Tsujimura543
 * application/html 対策を追加
 * 
 * 72    07/04/11 21:50 Tsujimura543
 * Content-type: が application/xml や application/rss+xml のような場合に
 * バイナリデータを受信したと誤判定してしまう不具合に対処
 * 
 * 71    07/03/26 16:05 Tsujimura543
 * (1) http関連関数群をバイナリファイルの受信にも対応させた
 * (2) getBinSize() を追加した
 * 
 * 70    07/03/16 18:31 Tsujimura543
 * http_postBASIC() を追加
 * 
 * 69    07/03/16 1:02 Tsujimura543
 * コメントを修正
 * 
 * 68    07/03/16 1:02 Tsujimura543
 * proxyサーバ経由でないとインターネットアクセスできないのに、proxyサーバ
 * を使わない設定になっている場合の対策を追加
 * 
 * 67    07/03/14 23:30 Tsujimura543
 * いったん proxy サーバが見つからない状態になっても、その後、再び
 * proxy サーバが見えるようになったら needToCheckProxyInfo の値を
 * 元に戻すように修正
 * 
 * 66    07/03/10 6:15 Tsujimura543
 * proxy関連の処理を修正
 * 
 * 65    07/03/10 4:58 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応
 * 
 * 64    07/03/09 21:14 Tsujimura543
 * isNecessaryToCheckProxyInfo() を追加、およびそれに伴う修正を実施
 * 
 * 63    07/01/24 12:34 Tsujimura543
 * スタックオーバーフロー防止の仕組みを見直し
 * 
 * 62    06/12/23 0:09 Tsujimura543
 * proxy 使用時の https 接続のときのヘッダ部分が http でなければいけない
 * サーバ、https でなければいけないサーバ、どちらでもいいサーバのどの
 * パターンにも対応するため、フラグを1個追加し、対応した 
 * 
 * 61    06/11/16 19:36 Tsujimura543
 * 実行する必要のない memset() を削除
 * 
 * 60    06/11/16 19:33 Tsujimura543
 * (verbose モードが on の場合など)stdout への出力が発生する場合、その時
 * 点の stdout がコンソールなのかどうか確認してから出力するようにした
 * 
 * 59    06/10/23 19:39 Tsujimura543
 * 送信バッファサイズより大きな電文を送信しようとしたときは、送信バッファ
 * を改めて確保し直すようにしてみた
 * 
 * 58    06/10/07 1:34 Tsujimura543
 * http(応答受信待ち)タイムアウト時間を設定変更できるようにした
 * 
 * 57    06/09/28 16:23 Tsujimura543
 * '\0' → NUL に置換
 * 
 * 56    06/09/28 16:06 Tsujimura543
 * _httpRedirect() と restructCookie() の引数 saveCookie の型を char *
 * から char ** に変更(修正) [malloc し直しでアドレスが変わるため]
 * 
 * 55    06/09/26 19:42 Tsujimura543
 * _httpExecute() をさらにリファクタリング
 * 
 * 54    06/09/26 18:52 Tsujimura543
 * (1) MAX_URLLENGTH_MAX の定義を http.c から http.h へ移す
 * (2) 大きくなりすぎた _httpExecute() を複数の関数に分割
 * 
 * 53    06/09/26 16:22 Tsujimura543
 * _httpExecute() で rcvBody が NULL の場合の考慮が抜けていたため、修正
 * 
 * 52    06/09/25 15:13 Tsujimura543
 * http_headEx() を追加
 * 
 * 51    06/09/20 11:02 Tsujimura543
 * http のレスポンスが 302 の場合の Location: が location: のように、
 * 先頭の L が小文字の l になっている場合がある(例えば、Echoo!)
 * ことが判明。大文字でも小文字でも通るように変更した 
 * 
 * 50    06/09/06 15:10 Tsujimura543
 * X-WSSE: 送出時、Host: 行の末尾の改行が \n のみだったのを、\r\n に修正
 * 
 * 49    06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 48c   06/09/03 15:52 tsupo
 * cookie 格納領域のオーバーランを防止するコードを追加
 * 
 * 48b   06/09/03 7:03 tsupo
 * Sleep(5) ではまだ受信サイズ 0 と誤認してしまうことがあるため、
 * Sleep(10)とする
 * 
 * 48a   06/09/03 7:01 tsupo
 * 実際にはデータを受信している(snifferで確認)にも関わらず、recv() が受
 * 信サイズ 0 と認識してしまう件に対し、Sleep() を入れることで対処した
 * 
 * 48    06/09/02 1:12 Tsujimura543
 * http通信実行中かどうかをチェックできる関数を追加した
 * 
 * 47    06/08/26 0:04 Tsujimura543
 * '<' が含まれる場合の修正が不十分だったことが判明。修正し直した
 * 
 * 46    06/08/24 21:22 Tsujimura543
 * html でも xml でもない形式のデータの受信時、最初の recvHTTP() で
 * 受信した電文中に '<' が含まれる場合、'<' より前の文字を捨ててしまって
 * いた(html もしくは xml だと誤判定してしまっていた)のを、捨てないように
 * 修正
 * 
 * 45    06/08/24 20:13 Tsujimura543
 * html でも xml でもない形式のデータの受信時、複数回の recvHTTP() で電文
 * 全体を受信する必要がある場合に、最初の1回分しかバッファにコピーしていな
 * かった不具合に対処
 * 
 * 44    06/07/25 18:15 Tsujimura543
 * ドリコムアカウント(2006年7月25日稼動開始)対応のため、https 関連の
 * 処理を見直した
 * 
 * 43    06/07/24 19:24 Tsujimura543
 * _httpExecute() のバッファオーバーラン防止対策関連の仕組みを修正
 * 
 * 42    06/07/24 14:09 Tsujimura543
 * _httpExecute() 内でバッファオーバーランが発生するのを防止する機能
 * として、あらかじめ rcvBody のサイズを指定しておけるようにした
 * (指定しなかった場合は、従来通りの動作を行なう)
 * 
 * 41    06/07/11 17:23 Tsujimura543
 * URL に # が含まれる場合の対策、動作確認実施。問題なし
 * 
 * 40    06/07/11 17:22 Tsujimura543
 * URL に # が含まれる場合、GET しようとすると 404 Not Found を返すサーバが
 * あることが判明したため、その対策を実施してみた
 * 
 * 39    06/06/13 22:13 Tsujimura543
 * リダイレクト先の URL が 384バイトより長いとメモリ破壊が起きる不具合に対処
 * 
 * 38    06/03/10 22:37 Tsujimura543
 * いったん、フィックス
 * 
 * 37    06/03/10 15:14 Tsujimura543
 * makeRSS.c から新たな「ゴミ掃除処理」を取り込む
 * (ただし、#if 0 ～ #endif にて囲むことで機能自体は働かないようにしてある)
 * 
 * 36    06/03/10 10:50 Tsujimura543
 * 非コンソールAP から getAuth() が呼び出された場合の暫定対処を追加
 * 
 * 35    06/03/07 23:07 Tsujimura543
 * ゴミ掃除処理を強化
 * 
 * 34    06/02/21 1:30 Tsujimura543
 * 301/302 リダイレクト時の Location: がルートからの相対パスの場合にも対応
 * 
 * 33    06/02/06 15:03 Tsujimura543
 * 301/302 のリダイレクトで指示される Location: が相対パス表記の場合
 * (があることを考慮していなかった)にも正しくリダイレクトできるようにした
 * 
 * 32    06/01/31 20:05 Tsujimura543
 * connectHTTP() を修正。メモリ領域が破壊される現象に対処
 * 
 * 31    06/01/31 13:35 Tsujimura543
 * もはや不要になったコメントを削除
 * 
 * 30    06/01/31 13:30 Tsujimura543
 * connectHTTP() を修正。Web サーバの見かけ上のホスト名が違ってもIPアドレ
 * スは同一の場合に別ホストと判断してしまう不具合に対処した
 * 
 * 29    06/01/27 0:10 Tsujimura543
 * デバッグ文を削除
 * 
 * 28    06/01/26 18:10 Tsujimura543
 * cookie 周りの処理を見直した
 * 
 * 27    06/01/20 14:49 Tsujimura543
 * 301 Moved Permanently に対応
 * 
 * 26    06/01/10 15:16 Tsujimura543
 * User-Agent を任意の文字列に変更できるようにした
 * 
 * 25    06/01/10 14:55 Tsujimura543
 * IIS6.0 向け「ゴミ掃除」処理を追加
 * 
 * 24    05/12/01 15:07 Tsujimura543
 * html や xml 以外のものを受信した場合(通常のテキストファイル)、受信電文
 * 格納領域に何も文字が格納されないことがある不具合に対処
 * 
 * 23    05/10/19 16:59 Tsujimura543
 * _httpExecute() にクッキー切り替え機能を追加実装 (動作確認済み)
 * 
 * 22    05/10/18 18:45 Tsujimura543
 * (1) _httpExecute() の引数追加に伴う各種変更を実施
 * (2) http_getEx2() と http_postEx2() を追加
 * 
 * 21    05/10/15 0:42 Tsujimura543
 * BASIC 認証まわりを修正
 * 
 * 20    05/06/28 15:22 Tsujimura543
 * _httpPost() を BASIC認証対応化
 * 
 * 19    05/05/31 22:49 Tsujimura543
 * 関数仕様の不整合を防ぐため、http.h を #include するようにした
 * 
 * 18    05/05/24 17:43 Tsujimura543
 * getAuth() に引数 prompt を追加
 * 
 * 17    05/05/24 15:53 Tsujimura543
 * BASIC認証要求時のユーザ名、パスワード入力処理を追加
 * 
 * 16    05/05/24 14:43 Tsujimura543
 * BASIC認証に対応
 * 
 * 15    05/04/05 21:39 Tsujimura543
 * 無限に 302 Moved Temporarily を返し続けるパターンに遭遇すると、スタック
 * オーバーフローで落ちてしまうことが判明。対策を実施(10回連続で 302 が来
 * たら、Web ページの get を打ち切るようにした)
 * 
 * 14    05/04/01 18:29 Tsujimura543
 * _httpExecute() での cookie 復元条件を修正
 * 
 * 13    05/03/30 10:13 Tsujimura543
 * 受信電文サイズが 0 のときは、ゴミ掃除処理を実行しないように修正
 * 
 * 12    05/03/25 19:15 Tsujimura543
 * 「ゴミ掃除」するタイミングを電文全体受信後に変更
 * 
 * 11    05/02/25 15:52 Tsujimura543
 * verbose モード時、受信電文内に EUC-JP もしくは UTF-8 文字列があれば
 * Shift_JIS 文字列に変換してから表示するようにした (WIN32 環境の場合)
 * 
 * 10    05/02/23 10:43 Tsujimura543
 * recvHTTP() の「ゴミ掃除」処理に4桁パターンを追加
 * 
 * 9     05/02/14 15:33 Tsujimura543
 * WIN32 の場合は、close() ではなく closesocket() を使うように修正
 * 
 * 8     05/02/14 14:37 Tsujimura543
 * recvHTTP() 内の「ゴミ掃除」処理を https の場合だけではなく、http の場合
 * も適用するように変更
 * 
 * 7     05/01/18 11:08 Tsujimura543
 * http_getEx() と http_postEx() を追加
 * 
 * 6     04/11/29 14:49 Tsujimura543
 * https のレスポンス中に含まれるゴミ(パケットサイズ?)を取り除く処理を追加
 * 
 * 5     04/11/26 14:00 Tsujimura543
 * SSL 接続失敗時のリトライ処理を追加
 * 
 * 4     04/11/25 10:07 Tsujimura543
 * Location: で示される URL が / で始まっている場合の処理を修正
 * 
 * 3     04/11/24 15:51 Tsujimura543
 * httpGet.c と httpPost.c から http 関連共通を抽出し、http.c へ移動
 * 
 * 2     04/11/24 15:12 Tsujimura543
 * http_get() と http_head() の動作を確認
 * 
 * 1     04/11/24 15:08 Tsujimura543
 * HTTPリクエストの主要なメソッドを直接実行するAPIを外部に見せるようにする
 */

#include "xmlRPC.h"
#include "http.h"
#include <time.h>
#include <sys/stat.h>
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/http.c 1     09/05/14 3:46 tsupo $";
#endif

void
confirmProxyInfo(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword );

/*
 *  HTTPリクエスト実行処理 共通部
 */

char    *getCookie( char *cookie );
char    *joinCookie( char *cookieNew, const char *cookieOld );
void    disconnectHTTP( void );

/*
 *  BASIC認証用ユーザ名、パスワード入力処理
 */
char    *
getAuth( const char *prompt, char *username, char *password )
{
    int  ch = 0, pos = 0;
    char *p;

    if ( !isatty( fileno( stdin  ) ) ||
         !isatty( fileno( stderr ) )    ) {
        /* 標準入力がリダイレクトされている場合、もしくは非コンソールアプ  */
        /* リケーションから呼び出されている場合                            */
        /*** 暫定対処 (本来は、login 用のダイアログのようなものを表示し  ***/
        /***           て、ユーザ名とパスワードの入力を促すようにすべき) ***/
        if ( username )
            *username = NUL;
        if ( password )
            *password = NUL;
        return ( "" );
    }

    fprintf( stderr, "=== %s ===\n", prompt );
    do {
        fputs( "ユーザ名: ", stderr );
        p = fgets( username, MAX_NAMELEN, stdin );
        if ( !p ) {
            clearerr( stdin );
            username[0] = NUL;
        }
        while ( username[strlen(username) - 1] == '\n' ) {
            username[strlen(username) - 1] = NUL;
            if ( username[0] == NUL )
                break;
        }
    } while ( username[0] == NUL );

    do {
        pos = 0;
        fputs( "パスワード: ", stderr );
#ifdef  WIN32
        do {
            ch = _getch();
            if ( (ch > ' ') && (ch < 0x7F) ) {
                password[pos] = (char)(ch & 0x7F);
                pos++;
                fputc( 'X', stderr );
            }
        } while( (ch != 0x0c) && (ch != 0x0d) );
        password[pos] = NUL;
#else
        p = fgets( password, MAX_NAMELEN, stdin );
        if ( !p ) {
            clearerr( stdin );
            password[0] = NUL;
        }
        while ( (password[strlen(password) - 1] == '\n') ||
                (password[strlen(password) - 1] == '\r')    ) {
            password[strlen(password) - 1] = NUL;
            if ( password[0] == NUL )
                break;
        }
#endif
    } while ( password[0] == NUL );

    return ( username );
}


struct hostent*
copyHostent( struct hostent **dst, const struct hostent *src )
{
    char    **s;
    int     nameLen       = 0;
    int     numOfAliases  = 0;
    int     numOfAddrList = 0;
    int     i;

    *dst = (struct hostent *)malloc( sizeof ( struct hostent ) );
    if ( *dst ) {
        if ( src->h_name && src->h_name[0] )
            nameLen = strlen( src->h_name ) + 1;

        s = src->h_aliases;
        while ( *s ) {
            s++;
            numOfAliases++;
        }

        s = src->h_addr_list;
        while ( *s ) {
            s++;
            numOfAddrList++;
        }

        if ( nameLen > 0 ) {
            (*dst)->h_name = (char *)malloc( nameLen );
            if ( (*dst)->h_name )
                strcpy( (*dst)->h_name, src->h_name );
        }
        else
            (*dst)->h_name = NULL;

        if ( numOfAliases > 0 ) {
            int     len;

            (*dst)->h_aliases = 
                (char **)malloc( sizeof ( char * ) * (numOfAliases + 1) );
            if ( (*dst)->h_aliases ) {
                for ( i = 0; i < numOfAliases; i++ ) {
                    len = strlen( src->h_aliases[i] ) + 1;
                    (*dst)->h_aliases[i] = (char *)malloc( len );
                    if ( (*dst)->h_aliases[i] )
                        strcpy( (*dst)->h_aliases[i], src->h_aliases[i] );
                    else
                        (*dst)->h_aliases[i] = NULL;
                }
                (*dst)->h_aliases[i] = NULL;
            }
        }
        else
            (*dst)->h_aliases = NULL;

        if ( numOfAddrList > 0 ) {
            int     len;

            (*dst)->h_addr_list =
                (char **)malloc( sizeof ( char * ) * (numOfAddrList + 1) );
            if ( (*dst)->h_addr_list ) {
                for ( i = 0; i < numOfAddrList; i++ ) {
                    len = strlen( src->h_addr_list[i] ) + 1;
                    (*dst)->h_addr_list[i] = (char *)malloc( len );
                    if ( (*dst)->h_addr_list[i] )
                        strcpy( (*dst)->h_addr_list[i], src->h_addr_list[i] );
                    else
                        (*dst)->h_addr_list[i] = NULL;
                }
                (*dst)->h_addr_list[i] = NULL;
            }
        }
        else
            (*dst)->h_addr_list = NULL;

        (*dst)->h_addrtype = src->h_addrtype;
        (*dst)->h_length   = src->h_length;
    }

    return ( *dst );
}

void
freeHostent( struct hostent *p )
{
    if ( p ) {
        char    **s;
        int     numOfAliases  = 0;
        int     numOfAddrList = 0;
        int     i;

        if ( p->h_addr_list ) {
            s = p->h_addr_list;
            while ( *s ) {
                s++;
                numOfAddrList++;
            }
            for ( i = numOfAddrList; i > 0; i-- )
                if ( p->h_addr_list[i - 1] )
                    free( p->h_addr_list[i - 1] );
            free( p->h_addr_list );
        }

        if ( p->h_aliases ) {
            s = p->h_aliases;
            while ( *s ) {
                s++;
                numOfAliases++;
            }
            for ( i = numOfAliases; i > 0; i-- )
                if ( p->h_aliases[i - 1] )
                    free( p->h_aliases[i - 1] );
            free( p->h_aliases );
        }

        if ( p->h_name )
            free( p->h_name );

        free( p );
    }
}


/*
 *  connectHTTP() --- connect to httpd process on web/proxy server
 *      argument: web server name (or IP address)
 *      return:   if connect OK, returns 0; else returns non 0 value
 */

int
connectHTTP( const char *webServer, int *flag, int *retryConnect )
{
    int             ret = 1, retryCnt = 0;
    long            len;
    struct protoent *p, pe;
    struct servent  *q, se;
    struct hostent  *rp;
    unsigned long   inaddrRemote;
    unsigned short  port = 0;
    const char      *server;
    char            proxyServerWithUserNameAndPassword[MAX_URLLENGTH];

    proxyServerWithUserNameAndPassword[0] = NUL;
    if ( xmlrpc_p->useProxy ) {
#if 0
        if ( xmlrpc_p->proxyUserName[0] ) {
            if ( xmlrpc_p->proxyPassword[0] )
                sprintf( proxyServerWithUserNameAndPassword,
                         "%s:%s@%s",
                         xmlrpc_p->proxyUserName,
                         xmlrpc_p->proxyPassword,
                         xmlrpc_p->proxyServer );
            else
                sprintf( proxyServerWithUserNameAndPassword,
                         "%s@%s",
                         xmlrpc_p->proxyUserName,
                         xmlrpc_p->proxyServer );

            server = proxyServerWithUserNameAndPassword;
        }
        else
#endif
            server = xmlrpc_p->proxyServer;
        port = htons( xmlrpc_p->proxyPort );
    }
    else {
        char *s;
        if ( (s = strrchr( webServer, ':' )) != NULL ) {
            /* In case of 'http://server:port/' */
            *s++ = NUL;
            if ( (*s >= '0') && (*s <= '9') ) {
                port = (unsigned short)(atol( s ) & 0xFFFF);
                port = htons( port );
            }
        }
        server = webServer;
    }

    /*
     *  create a socket
     */
    p = getprotobyname( "tcp" );
    memcpy( (char *)&pe, (char *)p, sizeof ( struct protoent ) );
    p = &pe;
    xmlrpc_p->scdHTTP = socket( PF_INET, SOCK_STREAM, p->p_proto );
    if ( (long)(xmlrpc_p->scdHTTP) < 0 )
        return ( ret );
#ifdef  WIN32
    if ( (xmlrpc_p->scdHTTP) == INVALID_SOCKET )
        return ( ret );
#endif

    /*
     *  set a port
     */
    if ( port == 0 ) {
        if ( xmlrpc_p->useSSL == FALSE )
            q = getservbyname( "http", "tcp" );
        else
            q = getservbyname( "https", "tcp" );
        if ( !q ) {
            unsigned short  defaultPort;
            
            if ( xmlrpc_p->useSSL == FALSE )
                defaultPort = (unsigned short)DEFAULT_HTTP_PORT;
            else
                defaultPort = (unsigned short)DEFAULT_HTTPS_PORT;

            if ( xmlrpc_p->verbose )
                dprintf( "\texpected http port is %d\n", defaultPort );
            port = htons( defaultPort );
        }
        else {
            memcpy( (char *)&se, (char *)q, sizeof ( struct servent ) );
            q = &se;
            port = q->s_port;
            if ( xmlrpc_p->verbose )
                dprintf( "\tprotocol #%d, port #%d\n",
                         p->p_proto, ntohs( q->s_port ) );
        }
    }

    rp = gethostbyname( server );
    if ( !rp ) {
        if ( (server[0] >= '0') && (server[0] <= '9') &&
             (strchr( server, '.' ) != NULL)             ) {
            const char  *p, *q, *r, *s;

            p = server;
            q = strchr( server, '.' );
            if ( !q )
                return ( ret );
            r = strchr( q + 1, '.' );
            if ( !r )
                return ( ret );
            s = strchr( r + 1, '.' );
            if ( !s )
                return ( ret );
            q++, r++, s++;
            if ( (*p < '0') || (*p > '9') ||
                 (*q < '0') || (*q > '9') ||
                 (*r < '0') || (*r > '9') ||
                 (*s < '0') || (*s > '9')    )
                return ( ret );
            xmlrpc_p->saddrHTTPremote.sin_addr.s_addr =
                    ((atol( p ) & 0xFF) << 24) | ((atol( q ) & 0xFF) << 16) |
                        ((atol( r ) & 0xFF) <<  8) |  (atol( s ) & 0xFF);
#ifndef  SUNOS
            xmlrpc_p->saddrHTTPremote.sin_addr.s_addr =
                    htonl( xmlrpc_p->saddrHTTPremote.sin_addr.s_addr );
#endif
            if ( xmlrpc_p->verbose )
                dprintf( "\tremote address = %d:%d:%d:%d\n",
                         atol( p ) & 0xff, atol( q ) & 0xff,
                         atol( r ) & 0xff, atol( s ) & 0xff  );
        }
        else {
            if ( isatty( fileno( stderr ) ) )
                dprintf( "\t%s: not found.\n", server );
            else if ( xmlrpc_p->useProxy ) {
                LCID    l = getLanguageCode();
                char    temp[BUFSIZ];

                sprintf( temp,
                         l == 0x0411
                            ? "proxyサーバ '%s' が見つかりません。    "
                            : "proxy server '%s': not found.  ",
                         xmlrpc_p->proxyServer );

                xmlrpc_p->needToCheckProxyInfo = TRUE;
                if ( xmlrpc_p->confirmProxyInfo                      &&
                     (xmlrpc_p->confirmProxyInfo != (CONF_FUNC)(-1))    ) {
                    strcat( temp,
                            l == 0x0411
                                ? "\nproxyサーバに関する設定が間違っていない"
                                  "か、確認してください。    "
                                : "\nCheck configuration setting of proxy "
                                  "server.    " );
                    MessageBox( NULL,
                                temp,
                                l == 0x0411
                                    ? "proxyサーバが見つかりません"
                                    : "proxy server is not found",
                                MB_OK|MB_ICONWARNING );
                }
                else
                    MessageBox( NULL,
                                temp,
                                l == 0x0411
                                    ? "proxyサーバが見つかりません"
                                    : "proxy server is not found",
                                MB_OK|MB_ICONWARNING );
            }
            return ( ret );
        }
    }
    else {
        struct hostent  *rp2 = NULL, *rS, *rH;

        copyHostent( &rS, rp );
        if ( xmlrpc_p->verbose ) {
            dprintf( "\tremote name    = %s\n", rS->h_name );
            dprintf( "\tremote address = %d:%d:%d:%d\n",
                     (rS->h_addr[0]) & 0xff, (rS->h_addr[1]) & 0xff,
                     (rS->h_addr[2]) & 0xff, (rS->h_addr[3]) & 0xff  );
        }

        rH = rS;
        if ( strcmp( webServer, rS->h_name ) != 0 ) {
            rp2 = gethostbyname( webServer );
            if ( rp2 )
                copyHostent( &rH, rp2 );
            rp = gethostbyname( server ); // 取得し直しておく
        }

        if ( ((rS->h_addr[0] & 0xff) != (rH->h_addr[0] & 0xff)) &&
             ((rS->h_addr[1] & 0xff) != (rH->h_addr[1] & 0xff)) &&
             ((rS->h_addr[2] & 0xff) != (rH->h_addr[2] & 0xff)) &&
             ((rS->h_addr[3] & 0xff) != (rH->h_addr[3] & 0xff))    )
            *flag = FALSE;
        else if ( strstr( webServer, "bulknews" ) != NULL )
            *flag = FALSE;
        else
            *flag = TRUE;
#ifdef  SUNOS
        xmlrpc_p->saddrHTTPremote.sin_addr.s_addr =
                ((rS->h_addr[0] & 0xFF) << 24) |
                ((rS->h_addr[1] & 0xFF) << 16) |
                ((rS->h_addr[2] & 0xFF) <<  8) |
                 (rS->h_addr[3] & 0xFF);
#else
        if ( !(rS->h_addr_list)    ||
             !(rS->h_addr_list[0])    ) {
            if ( rp2 )
                freeHostent( rH );
            freeHostent( rS );
            return ( ret );
        }
        inaddrRemote = *(unsigned long *)(rp->h_addr_list[0]);
                                            /* 注意: rS ではなく rp を使う */
        xmlrpc_p->saddrHTTPremote.sin_addr = *(struct in_addr *)&inaddrRemote;
        memset( xmlrpc_p->saddrHTTPremote.sin_zero, 0x00, 8 );
#endif
        if ( rp2 )
            freeHostent( rH );
        freeHostent( rS );
    }
    xmlrpc_p->saddrHTTPremote.sin_family = AF_INET;
    xmlrpc_p->saddrHTTPremote.sin_port   = port;
    len = sizeof (struct sockaddr_in);

    /*
     *  connect to web server (or proxy server)
     */
    if ( xmlrpc_p->verbose )
        dprintf( "\tConnecting to HTTP server on %s...", server );
    do {
        ret = connect( xmlrpc_p->scdHTTP,
                       (struct sockaddr *)&xmlrpc_p->saddrHTTPremote,
                       len );
        if ( ret < 0 ) {
#ifdef  WIN32
            int err = GetLastError();   /* @@ */
            if ( err == WSAETIMEDOUT )  /* @@ */
                retryCnt = 5;           /* @@ */
            putchar( '.' );
#else
            perror( "\nconnect" );
#endif
            retryCnt++;
#ifdef  WIN32
            closesocket( xmlrpc_p->scdHTTP );
#else
            close( xmlrpc_p->scdHTTP );
#endif
            xmlrpc_p->scdHTTP = (unsigned long)(-1);
            if ( (xmlrpc_p->needToCheckProxyInfo == FALSE) &&
                 (retryCnt < 5)                               ) {
                sleep( 10 );
                xmlrpc_p->scdHTTP = socket( PF_INET, SOCK_STREAM,
                                            p->p_proto );
                if ( (long)(xmlrpc_p->scdHTTP) < 0 )
                    return ( ret );
#ifdef  WIN32
                if ( xmlrpc_p->scdHTTP == INVALID_SOCKET ) {
                    return ( ret );
                }
#endif
            }
            else {
#ifdef  WIN32
                putchar( '\n' );
#endif
                xmlrpc_p->needToCheckProxyInfo = TRUE;
                if ( xmlrpc_p->confirmProxyInfo                      &&
                     (xmlrpc_p->confirmProxyInfo != (CONF_FUNC)(-1))    ) {
                    if ( xmlrpc_p->verbose ) {
                        time_t  t = time( NULL );
                        if ( t - xmlrpc_p->startup < 300 ) {
                            LCID    l = getLanguageCode();
                            char    temp[BUFSIZ];

                            sprintf(
                                temp,
                                l == 0x0411
                                    ? "サーバ '%s' が見つかりません。    "
                                    : "server '%s': not found.  ",
                                server );
                            strcat(
                                temp,
                                l == 0x0411
                                    ? "\n設定が間違っていないか、確認して"
                                      "ください。    "
                                    : "\nCheck configuration setting.    " );
                            MessageBox(
                                NULL,
                                temp,
                                l == 0x0411
                                    ? "サーバが見つかりません"
                                    : "server is not found",
                                MB_OK|MB_ICONWARNING );
                        }
                    }
                }

                goto EXIT;
            }
        }
    } while ( ret < 0 );

    if ( xmlrpc_p->useSSL == FALSE )
        ret = 0;
    else {
        ret = openHTTPS();  /* SSL 開始 */
        if ( ret != 0 ) {
            /* リトライ */
            if ( *retryConnect <= 5 ) {
                disconnectHTTP();
                (*retryConnect)++;
                ret = connectHTTP( webServer, flag, retryConnect );
            }
        }
    }
    xmlrpc_p->needToCheckProxyInfo = FALSE;

 EXIT:
    return ( ret );
}


/*
 *  disconnectHTTP() --- disconnect from httpd process on web/proxy server
 *      arguments: none
 *      return:    none (void)
 */

void
disconnectHTTP()
{
    if ( xmlrpc_p->useSSL == FALSE ) {
#ifdef  WIN32
        closesocket( xmlrpc_p->scdHTTP );
#else
        close( xmlrpc_p->scdHTTP );
#endif
    }
    else
        closeHTTPS();   /* SSL 終了 */

    xmlrpc_p->scdHTTP = (unsigned long)(-1);
    if ( xmlrpc_p->verbose )
        dputs( "\n\tConnection closed\n" );
}


/*
 *  sendHTTP() --- send a HTTP/POST request to httpd process
 *      argument: none
 *      return: if send OK, returns 0; else returns non 0 value
 *              (if detected disconnection, returns -2)
 */

int
sendHTTP()
{
    int     ret = 1;

    /*
     *  send a request via socket
     */
    if ( xmlrpc_p->useSSL == FALSE )
        ret = send( xmlrpc_p->scdHTTP, xmlrpc_p->sndHTTP,
                    xmlrpc_p->sndHTTPmessageSize, 0 );
    else
        ret = sendHTTPS( xmlrpc_p->sndHTTP, xmlrpc_p->sndHTTPmessageSize );

    if ( ret <= 0 ) {
#ifdef  WIN32
        int e = WSAGetLastError();
        dprintf( "error code = %d\n", e );
        if ( h_errno == WSAECONNRESET ) {
            dputs( "\n\tConnection is lost.\n" );
            return ( -2 );
        }
#else
        perror( "send" );
#endif
        return ( -1 );
    }

#ifdef  _DEBUG
    dprintf( "send %dbytes to HTTP server\n", ret );
#endif

    return ( 0 );
}


/*
 *  recvHTTP() --- receive a response from httpd process
 *      argument: none
 *      return:   byte length of received data
 *                  if receive OK, then returns received-data-length;
 *                  else returns negative integer value
 *                  (if detected disconnection, returns -2)  
 */

int     timedout     = 0;
int     timedoutTime = DEFAULT_HTTP_TIMEOUT;

int
recvHTTP()
{
    int             ret = 1;
    fd_set          rfds[1];
    struct timeval  t;

    FD_ZERO( rfds );
    t.tv_sec  = (xmlrpc_p->timedoutTime < DEFAULT_HTTP_TIMEOUT)
                    ? timedoutTime
                    : xmlrpc_p->timedoutTime;
    t.tv_usec = 0;
    timedout  = 0;

    /*
     *  receive data via socket
     */
    xmlrpc_p->rcvHTTPbufferSize = RCV_BUFFER_SIZE;
    memset( xmlrpc_p->rcvHTTP, 0, xmlrpc_p->rcvHTTPbufferSize );
#ifdef  _MSC_VER
#pragma warning (disable: 4127)
#endif
    FD_SET( xmlrpc_p->scdHTTP, rfds );
    ret = select( FD_SETSIZE, rfds, NULL, NULL, &t );
    FD_CLR( xmlrpc_p->scdHTTP, rfds );
#ifdef  _MSC_VER
#pragma warning (default: 4127)
#endif
    if ( ret <= 0 ) {
        dputs( "\trecv: timed out\n" );
        timedout = 1;
        return ( -1 );
    }
#ifdef  WIN32
    Sleep(10);  /* {@@} */
#endif
    if ( xmlrpc_p->useSSL == FALSE )
        ret = recv( xmlrpc_p->scdHTTP, xmlrpc_p->rcvHTTP,
                    xmlrpc_p->rcvHTTPbufferSize, 0 );
    else
        ret = recvHTTPS( xmlrpc_p->rcvHTTP, xmlrpc_p->rcvHTTPbufferSize );

    if( ret < 0 ) {
#ifdef  WIN32
        if ( h_errno == WSAECONNRESET ) {
            dputs( "\n\tConnection is lost.\n" );
            return ( -2 );
        }
#else
        perror( "recv" );
#endif
        return ( -1 );
    }

    xmlrpc_p->rcvHTTPmessageSize = ret;
    if ( xmlrpc_p->verbose )
        dprintf( "\treceived %dbytes from HTTP server\n", ret );
    if ( ret == 0 ) {
        if ( xmlrpc_p->verbose )
            dputs( "\tConnection closed by server.\n" );
        return ( -2 );
    }

    if ( xmlrpc_p->verbose ) {
        int             i, c;
        unsigned char   buf[80];

        for ( i = 0; i < ret; i++ ) {
            if ( (i != 0) && (i % 16 == 0) ) {
                buf[16] = NUL;
                dprintf( "    %s\n", buf );
            }
            if ( i % 16 == 0 )
                dprintf( "%08x:", &xmlrpc_p->rcvHTTP[i] );
            c = xmlrpc_p->rcvHTTP[i] & 0xFF;
            if ( (c >= ' ') && (c <= 0x7E) )
                buf[i % 16] = (unsigned char)c;
            else
                buf[i % 16] = '.';
            dprintf( " %02x", c & 0xFF );
        }
        if ( i % 16 == 0 )
            buf[16] = NUL;
        else {
            buf[i % 16] = NUL;
            for ( i = i % 16; i < 16; i++ )
                dputs( "   " );
        }
        dprintf( "    %s\n", buf );
    }

    return ( 0 );
}


char    *
deleteChunkedData( char *rcvBody )
{
    char    *p = rcvBody;
    char    *q;

    while ( *p ) {
        /* 2桁 #1 */
        if ( (*p       == 0x0d) &&
             (*(p + 1) == 0x0a) &&
             (*(p + 2) == 0x0d) &&
             (*(p + 3) == 0x0a) &&
             ( ((*(p + 4) >= '0') && (*(p + 4) <= '9')) ||
               ((*(p + 4) >= 'A') && (*(p + 4) <= 'F')) ||
               ((*(p + 4) >= 'a') && (*(p + 4) <= 'f'))    ) &&
             ( ((*(p + 5) >= '0') && (*(p + 5) <= '9')) ||
               ((*(p + 5) >= 'A') && (*(p + 5) <= 'F')) ||
               ((*(p + 5) >= 'a') && (*(p + 5) <= 'f'))    ) &&
             (*(p + 6) == 0x0d) &&
             (*(p + 7) == 0x0a) &&
             (*(p + 8) == 0x0d) &&
             (*(p + 9) == 0x0a)    ) {
            /* ゴミ発見 */
            strcpy( p, p + 10 );
        }
        else
        /* 2桁 #2 */
        if ( (*p       == 0x0d) &&
             (*(p + 1) == 0x0a) &&
             ( ((*(p + 2) >= '0') && (*(p + 2) <= '9')) ||
               ((*(p + 2) >= 'A') && (*(p + 2) <= 'F')) ||
               ((*(p + 2) >= 'a') && (*(p + 2) <= 'f'))    ) &&
             ( ((*(p + 3) >= '0') && (*(p + 3) <= '9')) ||
               ((*(p + 3) >= 'A') && (*(p + 3) <= 'F')) ||
               ((*(p + 3) >= 'a') && (*(p + 3) <= 'f'))    ) &&
             (*(p + 4) == 0x0d) &&
             (*(p + 5) == 0x0a) ) {
            /* ゴミ発見 */
            strcpy( p, p + 6 );
        }
        else
        /* 3桁 #1 */
        if ( (*p       == 0x0d) &&
             (*(p + 1) == 0x0a) &&
             (*(p + 2) == 0x0d) &&
             (*(p + 3) == 0x0a) &&
             ( ((*(p + 4) >= '0') && (*(p + 4) <= '9')) ||
               ((*(p + 4) >= 'A') && (*(p + 4) <= 'F')) ||
               ((*(p + 4) >= 'a') && (*(p + 4) <= 'f'))    ) &&
             ( ((*(p + 5) >= '0') && (*(p + 5) <= '9')) ||
               ((*(p + 5) >= 'A') && (*(p + 5) <= 'F')) ||
               ((*(p + 5) >= 'a') && (*(p + 5) <= 'f')) ||
               (*(p + 5) == ' ') /* ← 3桁の場合のみ考慮 */) &&
             ( ((*(p + 6) >= '0') && (*(p + 6) <= '9')) ||
               ((*(p + 6) >= 'A') && (*(p + 6) <= 'F')) ||
               ((*(p + 6) >= 'a') && (*(p + 6) <= 'f')) ||
               (*(p + 6) == ' ') /* ← 3桁の場合のみ考慮 */) &&
             (*(p +  7) == 0x0d) &&
             (*(p +  8) == 0x0a) &&
             (*(p +  9) == 0x0d) &&
             (*(p + 10) == 0x0a)    ) {
            /* ゴミ発見 */
            strcpy( p, p + 11 );
        }
        else
        /* 3桁 #2 */
        if ( (*p       == 0x0d) &&
             (*(p + 1) == 0x0a) &&
             ( ((*(p + 2) >= '0') && (*(p + 2) <= '9')) ||
               ((*(p + 2) >= 'A') && (*(p + 2) <= 'F')) ||
               ((*(p + 2) >= 'a') && (*(p + 2) <= 'f'))    ) &&
             ( ((*(p + 3) >= '0') && (*(p + 3) <= '9')) ||
               ((*(p + 3) >= 'A') && (*(p + 3) <= 'F')) ||
               ((*(p + 3) >= 'a') && (*(p + 3) <= 'f')) ||
               (*(p + 3) == ' ') /* ← 3桁の場合のみ考慮 */) &&
             ( ((*(p + 4) >= '0') && (*(p + 4) <= '9')) ||
               ((*(p + 4) >= 'A') && (*(p + 4) <= 'F')) ||
               ((*(p + 4) >= 'a') && (*(p + 4) <= 'f')) ||
               (*(p + 4) == ' ') /* ← 3桁の場合のみ考慮 */) &&
             (*(p + 5) == 0x0d) &&
             (*(p + 6) == 0x0a) ) {
            /* ゴミ発見 */
            strcpy( p, p + 7 );
        }
        else
        /* 4桁 #1 */
        if ( (*p       == 0x0d) &&
             (*(p + 1) == 0x0a) &&
             (*(p + 2) == 0x0d) &&
             (*(p + 3) == 0x0a) &&
             ( ((*(p + 4) >= '0') && (*(p + 4) <= '9')) ||
               ((*(p + 4) >= 'A') && (*(p + 4) <= 'F')) ||
               ((*(p + 4) >= 'a') && (*(p + 4) <= 'f'))    ) &&
             ( ((*(p + 5) >= '0') && (*(p + 5) <= '9')) ||
               ((*(p + 5) >= 'A') && (*(p + 5) <= 'F')) ||
               ((*(p + 5) >= 'a') && (*(p + 5) <= 'f'))    ) &&
             ( ((*(p + 6) >= '0') && (*(p + 6) <= '9')) ||
               ((*(p + 6) >= 'A') && (*(p + 6) <= 'F')) ||
               ((*(p + 6) >= 'a') && (*(p + 6) <= 'f'))    ) &&
             ( ((*(p + 7) >= '0') && (*(p + 7) <= '9')) ||
               ((*(p + 7) >= 'A') && (*(p + 7) <= 'F')) ||
               ((*(p + 7) >= 'a') && (*(p + 7) <= 'f'))    ) &&
             (*(p +  8) == 0x0d) &&
             (*(p +  9) == 0x0a) &&
             (*(p + 10) == 0x0d) &&
             (*(p + 11) == 0x0a)    ) {
            /* ゴミ発見 */
            strcpy( p, p + 12 );
        }
        else
        /* 4桁 #2 */
        if ( (*p       == 0x0d) &&
             (*(p + 1) == 0x0a) &&
             ( ((*(p + 2) >= '0') && (*(p + 2) <= '9')) ||
               ((*(p + 2) >= 'A') && (*(p + 2) <= 'F')) ||
               ((*(p + 2) >= 'a') && (*(p + 2) <= 'f'))    ) &&
             ( ((*(p + 3) >= '0') && (*(p + 3) <= '9')) ||
               ((*(p + 3) >= 'A') && (*(p + 3) <= 'F')) ||
               ((*(p + 3) >= 'a') && (*(p + 3) <= 'f'))    ) &&
             ( ((*(p + 4) >= '0') && (*(p + 4) <= '9')) ||
               ((*(p + 4) >= 'A') && (*(p + 4) <= 'F')) ||
               ((*(p + 4) >= 'a') && (*(p + 4) <= 'f'))    ) &&
             ( ((*(p + 5) >= '0') && (*(p + 5) <= '9')) ||
               ((*(p + 5) >= 'A') && (*(p + 5) <= 'F')) ||
               ((*(p + 5) >= 'a') && (*(p + 5) <= 'f'))    ) &&
             (*(p + 6) == 0x0d) &&
             (*(p + 7) == 0x0a) ) {
            /* ゴミ発見 */
            strcpy( p, p + 8 );
        }
        else
        /* 1桁 */
        if ( (*p       == 0x0d) &&
             (*(p + 1) == 0x0a) &&
             (*(p + 2) == 0x0d) &&
             (*(p + 3) == 0x0a) &&
             ( ((*(p + 4) >= '0') && (*(p + 4) <= '9')) ||
               ((*(p + 4) >= 'A') && (*(p + 4) <= 'F')) ||
               ((*(p + 4) >= 'a') && (*(p + 4) <= 'f'))    ) &&
             (*(p + 5) == 0x0d) &&
             (*(p + 6) == 0x0a) &&
             (*(p + 7) == 0x0d) &&
             (*(p + 8) == 0x0a)    ) {
            /* ゴミ発見 */
            strcpy( p, p + 9 );
        }
        p++;
    }

    /* 上記ではじけなかったゴミをはじく (for IIS6.0) */
    p = rcvBody;
    while ( *p ) {
        if ( (*p == '\r') || (*p == '\n' ) ) {
            q = p++;
            while ( (*p == '\r') || (*p == '\n' ) )
                p++;
            if ( !(*p) )
                break;
            if ( ((*p >= '0') && (*p <= '9')) ||
                 ((*p >= 'a') && (*p <= 'f'))    ) {
                if ( ((*(p + 1) >= '0') && (*(p + 1) <= '9')) ||
                     ((*(p + 1) >= 'a') && (*(p + 1) <= 'f'))    ) {
                    if ( ((*(p + 2) >= '0') && (*(p + 2) <= '9')) ||
                         ((*(p + 2) >= 'a') && (*(p + 2) <= 'f'))    ) {
                        if ( ((*(p + 3) >= '0') && (*(p + 3) <= '9')) ||
                             ((*(p + 3) >= 'a') && (*(p + 3) <= 'f'))    ) {
                            if ( *(p + 4) == '\n' ) {
                                strcpy( q, p + 4 );
                                p = q;
                                continue;
                            }
                            else if ( (*(p + 4) == '\r') &&
                                      (*(p + 5) == '\n')    ) {
                                strcpy( q, p + 6 );
                                p = q;
                                continue;
                            }
                        }
                        else if ( *(p + 3) == '\n' ) {
                            strcpy( q, p + 4 );
                            p = q;
                            continue;
                        }
                        else if ( (*(p + 3) == '\r') &&
                                  (*(p + 4) == '\n')    ) {
                            strcpy( q, p + 5 );
                            p = q;
                            continue;
                        }
                    }
                    else if ( *(p + 2) == '\n' ) {
                        strcpy( q, p + 3 );
                        p = q;
                        continue;
                    }
                    else if ( (*(p + 2) == '\r') &&
                              (*(p + 3) == '\n')    ) {
                        strcpy( q, p + 4 );
                        p = q;
                        continue;
                    }
                }
                else if ( *(p + 1) == '\n' ) {
                    strcpy( q, p + 2 );
                    p = q;
                    continue;
                }
                else if ( (*(p + 1) == '\r') &&
                          (*(p + 2) == '\n')    ) {
                    strcpy( q, p + 3 );
                    p = q;
                    continue;
                }
            }
        }

        p++;
    }

#if 0
    /* 上記ではじけなかったゴミをはじく (for @niftyの掲示板) */
    p = rcvBody;
    while ( *p ) {
        q = strchr( p, '\n' );
        if ( q ) {
            if ( *(q - 1) == '\r' )
               q--;
        }
        else
            q = strchr( p, '\r' );
        if ( !q )
            break;
        p = q;
        q++;
        while ( (*q == '\n') || (*q == '\r') )
           q++;
        if ( ((*q >= '0') && (*q <= '9')) ||
             ((*q >= 'a') && (*q <= 'f'))    ) {
            if ( (*(q + 1) == '\n') || (*(q + 1) == '\r') ) {
                q++;
                while ( (*q == '\n') || (*q == '\r') )
                    q++;
                strcpy( p, q );
                continue;
            }

            q++;
            if ( ((*q >= '0') && (*q <= '9')) ||
                 ((*q >= 'a') && (*q <= 'f'))    ) {
                if ( (*(q + 1) == '\n') || (*(q + 1) == '\r') ) {
                    q++;
                    while ( (*q == '\n') || (*q == '\r') )
                        q++;
                    strcpy( p, q );
                    continue;
                }

                q++;
                if ( ((*q >= '0') && (*q <= '9')) ||
                     ((*q >= 'a') && (*q <= 'f'))    ) {
                    if ( (*(q + 1) == '\n') || (*(q + 1) == '\r') ) {
                        q++;
                        while ( (*q == '\n') || (*q == '\r') )
                            q++;
                        strcpy( p, q );
                        continue;
                    }

                    q++;
                    if ( ((*q >= '0') && (*q <= '9')) ||
                         ((*q >= 'a') && (*q <= 'f'))    ) {
                        if ( (*(q + 1) == '\n') || (*(q + 1) == '\r') ) {
                            q++;
                            while ( (*q == '\n') || (*q == '\r') )
                                q++;
                            strcpy( p, q );
                            continue;
                        }
                    }
                }
            }
        }
        p = q + 1;
    }

    /* 余分な ctrl+M (\r) を除去する     */
    /*   例えば、                        */
    /*       \r\r\n → \r\n              */
    /*       ABC\rDEF\r\n → ABCDEF\r\n  */
    /*   に置換する                      */
    p = rcvBody;
    while ( *p ) {
        if ( *p == '\r' ) {
            if ( (*(p + 1) != NUL) && (*(p + 1) != '\n') ) {
                strcpy( p, p + 1 );
                continue;
            }
            else if ( *(p + 1) == NUL ) {
                *p = NUL;
                break;
            }
        }
        else
        if ( *p == '\n' ) {
            if ( *(p + 1) == '\n' ) {
                strcpy( p, p + 1 );
                continue;
            }
        }

        p++;
    }
#endif

    return ( rcvBody );
}

char    *
makeRequestHeader(
        const char *method,
        const char *webServer, const char *webPage,
        const char *mimeType,/* ← 必要なのは POST, PUT のみ */
        const char *sndBody, /* ← 必要なのは POST, PUT のみ */
        const char *userName,/* ← 必要なのは BASIC認証使用時のみ */
        const char *password,/* ← 必要なのは BASIC認証使用時のみ */
        const char *wsse,
        const char *cookie,
        size_t     sndLength,
        int        flag,
        size_t     *sndSize,
        const char *newSndBody )
{
    if ( (size_t)(xmlrpc_p->sndHTTPBufferSize) <= sndLength ) {
        char    *newBuffer = (char *)malloc( sndLength * 2 );

        if ( newBuffer == NULL ) {
            dputs( "makeRequestHeader: memory exhausted.\n" );
            return ( xmlrpc_p->sndHTTP );
        }
        free( xmlrpc_p->sndHTTP );

        xmlrpc_p->sndHTTP    = newBuffer;
        xmlrpc_p->sndHTTP[0] = NUL;
        xmlrpc_p->sndHTTPBufferSize = sndLength * 2;
    }

    if ( xmlrpc_p->useProxy ) {
        if ( (webPage[0] == NUL) || !strcmp( webPage, "/" ) ) {
            if ( xmlrpc_p->useSSL == FALSE )
                sprintf( xmlrpc_p->sndHTTP, "%s http://%s/",
                         method, webServer );
            else
                sprintf( xmlrpc_p->sndHTTP, "%s %s",
                         method, webServer );
        }
        else {
            if ( xmlrpc_p->useSSL && xmlrpc_p->recoverySSL ) {
                /* 解説: 本来、https 通信時も GET/POST するのは http:// で  */
                /*       いいはずであるが、なぜか、ドリコムアカウントのサー */
                /*       バは https:// を指定しないとエラーを返すので       */
                /*       https:// を使うようにした。ちなみに、他のサーバは、*/
                /*       一般的に http:// でも https:// でもどちらでも通る  */
                /*       ようなので、https:// で行くことにする              */
                /*       (2006年12月22日 追記)                              */
                /*         http:// でないと 500 Internal Server Error を返  */
                /*         すサーバが存在することが判明                     */
                sprintf( xmlrpc_p->sndHTTP, "%s https://%s%s",
                         method,
                         webServer, webPage );
            }
            else
                sprintf( xmlrpc_p->sndHTTP, "%s http://%s%s",
                         method,
                         webServer, webPage );
        }
    }
    else if ( (flag == FALSE) /*&& (xmlrpc_p->useSSL == FALSE)*/ )
        sprintf( xmlrpc_p->sndHTTP, "%s http://%s%s",
                 method, webServer, webPage );                  /* (a) */
    else
        sprintf( xmlrpc_p->sndHTTP, "%s %s", method, webPage ); /* (b) */
    /* (1) proxy を通す場合は http:// を含めてフルURLで指定する必要がある */
    /* (2) proxy を通さない場合は、通常、フルURLから http://サーバ名 を取 */
    /*     り除いた文字列を指定する(b) が、サーバによっては 404 Not Found */
    /*     になってしまう。そのようなサーバでは、(a) のように  http:// を */
    /*     含めたフルURL を指定することで、正常にアクセスできる。たいてい */
    /*     のサーバでは (a) でも (b) でも正常にアクセスできるが、(a) でな */
    /*     いと正しくアクセスできないサーバ、 逆に (b) でないと正常にアク */
    /*     セスできないサーバがあるので注意                               */

    if ( xmlrpc_p->recoverySSL )
        if ( xmlrpc_p->useProxy )
            if ( xmlrpc_p->useSSL == FALSE )
                xmlrpc_p->recoverySSL = FALSE;

    if ( !strcmp( method, "GET" ) ) {
        // url に # が含まれる場合、GET しようとすると、404 Not Found を返
        // してくるサーバがあることが判明。対策として、# 以降を切り捨てるよ
        // うにしてみた(= Internet Explorer 6.0 の挙動に合わせた)
        char   *p;

        p = strrchr( xmlrpc_p->sndHTTP, '#' );
        if ( p )
            *p = NUL;
    }

    if ( wsse ) {
        strcat( xmlrpc_p->sndHTTP, " HTTP/1.1\r\n" ); /* HTTP 1.1 */
        sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                 "User-Agent: %s\r\n",
                 xmlrpc_p->userAgent[0]
                    ? xmlrpc_p->userAgent
                    : "httpWsse/1.0 (written by H.Tsujimura)" );
        sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                 "Host: %s\r\n", webServer );
        if ( cookie && *cookie )
            strcat( xmlrpc_p->sndHTTP, cookie );
        strcat( xmlrpc_p->sndHTTP, "X-WSSE: " );
        strcat( xmlrpc_p->sndHTTP, wsse );
        strcat( xmlrpc_p->sndHTTP, "\r\n" );
    }
    else {
#ifdef  SIMPLE_HEADER
        strcat( xmlrpc_p->sndHTTP, " HTTP/1.0\r\n\r\n" );
#else
        strcat( xmlrpc_p->sndHTTP, " HTTP/1.1\r\n" );
        strcat( xmlrpc_p->sndHTTP, "Accept: */*\r\n" );
        sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                 "User-Agent: %s\r\n",
                 xmlrpc_p->userAgent[0]
                    ? xmlrpc_p->userAgent
                    : "httpRead/1.0 (written by H.Tsujimura)" );
        sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                 "Host: %s\r\n", webServer );
        if ( cookie && *cookie ) {
         // if ( cookie[strlen(cookie) - 3] != ';' ) 
         //     strcpy( (char *)&(cookie[strlen(cookie) - 3]), ";\r\n" );
            strcat( xmlrpc_p->sndHTTP, cookie );
        }
#endif
    }

    if ( xmlrpc_p->referer[0] ) {
        sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                 "Referer: %s\r\n", xmlrpc_p->referer );
        if ( xmlrpc_p->userAgent[0]                     &&
             !strstr( xmlrpc_p->userAgent, "Firefox/" )    )
            xmlrpc_p->referer[0] = NUL;
    }

    if ( (xmlrpc_p->proxyUserName[0]) /*&& (xmlrpc_p->useSSL == FALSE)*/ ) {
        char   auth[128];
        char   *p;

        if ( !(xmlrpc_p->proxyPassword[0]) )
            sprintf( auth, "%s", xmlrpc_p->proxyUserName );
        else
            sprintf( auth, "%s:%s",
                     xmlrpc_p->proxyUserName, xmlrpc_p->proxyPassword );
        p = base64( (unsigned char *)auth, strlen( auth ) );
        if ( p )
            sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                     "Proxy-Authorization: Basic %s\r\n", p );
    }
    if ( userName && *userName && password && *password ) {
        char   auth[64];
        char   *p;

        sprintf( auth, "%s:%s", userName, password );
        p = base64( (unsigned char *)auth, strlen( auth ) );
        if ( p ) {
            sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                     "Authorization: Basic %s\r\n", p );
            if ( xmlrpc_p->proxyCookie[0] )
                sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                         "Cookie: %s\r\n",
                         xmlrpc_p->proxyCookie );
        }
    }

#ifdef  USE_AUTHORIZATION_OAUTH
    if ( xmlrpc_p->oauth_header[0] ) {
        sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                 "Authorization: OAuth %s\r\n", xmlrpc_p->oauth_header );
        xmlrpc_p->oauth_header[0] = NUL;
    }
#endif

    strcat( xmlrpc_p->sndHTTP, "Connection: close\r\n" );
 /* strcat( xmlrpc_p->sndHTTP, "Keep-Alive: 300\r\n" );        */
 /* strcat( xmlrpc_p->sndHTTP, "Connection: keep-alive\r\n" ); */
    strcat( xmlrpc_p->sndHTTP, "Cache-Control: no-cache\r\n" );

    if ( sndBody ) {
        if ( !mimeType || !(*mimeType) )
            strcat( xmlrpc_p->sndHTTP, "Content-Type: text/xml\r\n" );
        else {
            sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                     "Content-Type: %s\r\n",
                     mimeType );
        }
        if ( *sndSize > 0 ) {
            // バイナリファイル送信用
            size_t  baseSize = 0;
            sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                     "Content-Length: %d\r\n\r\n",
                     *sndSize );
            baseSize = strlen(xmlrpc_p->sndHTTP);
            memcpy( xmlrpc_p->sndHTTP + baseSize,
                    newSndBody, *sndSize );
            *sndSize += baseSize; 
        }
        else {
            sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                     "Content-Length: %d\r\n\r\n",
                     sndLength );
            strcat( xmlrpc_p->sndHTTP, sndBody );
        }
    }
    else
        strcat( xmlrpc_p->sndHTTP, "\r\n" );

    if ( xmlrpc_p->verbose )
        dprintf( "\t%s\n", xmlrpc_p->sndHTTP );

    return ( xmlrpc_p->sndHTTP );
}

char    *
restructCookie( char *cookie, char **saveCookie )
{
    getCookie( cookie );
    if ( !(*cookie) ) {
        if ( *saveCookie && **saveCookie )
            strcpy( cookie, *saveCookie );
    }
    else {
        if ( *saveCookie ) {
            if ( **saveCookie &&
                 (strcmp( *saveCookie, cookie ) != 0) ) {
                if ( strstr( cookie,      "sledge_sid" ) != NULL &&
                     strstr( *saveCookie, "sledge_sid" ) != NULL    )
                    ;   /* wassr [暫定対策] */
                else
                    joinCookie( cookie, *saveCookie );  /* 2つのクッキーを合体 */
            }
            free( *saveCookie );
        }
        *saveCookie = (char *)malloc( strlen( cookie ) + 1 );
        if ( *saveCookie )
            strcpy( *saveCookie, cookie );
    }

    return ( cookie );
}

int
_httpExecuteBASIC(
        const char *method,
        const char *mimeType,
        const char *sndBody,
        const char *userName, const char *password,
        char       *rcvBody, FILE *output, int printHead,
        const char *wsse, char *p3p, char *cookie,
        char       *webServerRedirected, char *cookieRedirected,
        int        stackCount,
        const char *basic,
        size_t     rcvLength )
{
    int     ret;
    char    _userName[MAX_NAMELEN + 1];
    char    _password[MAX_NAMELEN + 1];

    if ( userName && userName[0] && password && password[0] ) {
        strcpy( _userName, userName );
        strcpy( _password, password );
    }
    else
        getAuth( basic, _userName, _password );
    if ( rcvBody ) {
        if ( rcvLength > 0 ) {
            setUpReceiveBuffer( rcvBody, rcvLength );
        }
        else
            *(size_t *)rcvBody = 0;
    }
    ret = _httpExecute( method,
                        xmlrpc_p->webServer, xmlrpc_p->webPage,
                        mimeType, sndBody,
                        _userName, _password,
                        rcvBody, output, printHead,
                        wsse, p3p, cookie,
                        webServerRedirected, cookieRedirected,
                        stackCount + 1 );

    return ( ret );
}


int
_httpRedirect(
        const char *method,
        const char *webServer,
        const char *mimeType,
        const char *sndBody,
        const char *userName, const char *password,
        char       *rcvBody, FILE *output, int printHead,
        const char *wsse, char *p3p,
        char       *cookie, char **saveCookie,
        char       *webServerRedirected, char *cookieRedirected,
        int        stackCount,
        char       *location,
        int        statusCode,
        size_t     rcvLength )
{
    int ret;

    /* クッキー復元 (必要がある場合のみ) */
    if ( cookie && !(*cookie) && *saveCookie && **saveCookie )
        strcpy( cookie, *saveCookie );

    /* クッキー切替 (必要がある場合のみ) */
    if ( webServerRedirected && webServerRedirected[0]     &&
         cookieRedirected    && cookieRedirected[0]        &&
         (strncmp( webServer, webServerRedirected,
                   strlen(webServerRedirected)     ) != 0)    )
        strcpy( cookie, cookieRedirected );

    /* Location: で指定された url へ飛ぶ */
    if ( (strncmp( location, "http://",  7 ) != 0) &&
         (strncmp( location, "https://", 8 ) != 0)    ) {
        char    temp[MAX_URLLENGTH_MAX];

        /* 相対パス → 絶対パス 変換 */
        if ( location[0] == '/' ) {
            sprintf( temp, "%s%s",
                     xmlrpc_p->webServer, location );
            strcpy( location, temp );
        }
        else if ( (strncmp( location, xmlrpc_p->webServer,
                            strlen(xmlrpc_p->webServer) ) != 0) &&
                  (strncmp( location,
                            xmlrpc_p->webServer,
                            strlen(location) ) != 0)               ) {
            char    *p;

            sprintf( temp, "%s%s",
                     xmlrpc_p->webServer, xmlrpc_p->webPage );
            p = strrchr( temp, '/' );
            if ( p ) {
                strcpy( p + 1, location );
                strcpy( location, temp );
            }
        }
    }
    setTargetURL( location );
    if ( xmlrpc_p->verbose )
        dprintf( ">>> Location: %s\n", location );
    if ( rcvBody ) {
        if ( rcvLength > 0 ) {                          /* {@@} */
            setUpReceiveBuffer( rcvBody, rcvLength );   /* {@@} */
        }                                               /* {@@} */
        else                                            /* {@@} */
            *(size_t *)rcvBody = 0;                     /* {@@} */
    }
    if ( ((statusCode == 302) || (statusCode == 303)) &&
         (strcmp( method, "GET" ) != 0)                  ) {
        if ( webServerRedirected && *webServerRedirected ) {
            char    *p = strstr( location, "://" );
            char    *q = strstr( webServerRedirected, "://" );
            if ( p && q ) {
                p = p + 3;
                q = q + 3;
                if ( strncmp( p, q, strlen(q) ) != 0 )
                    statusCode = 301; /* @@ */
            }
        }
    }
    if ( ((statusCode == 300) || (statusCode == 301)) &&
         (strcmp( method, "GET" ) != 0) )
        ret = _httpExecute( method,
                            xmlrpc_p->webServer, xmlrpc_p->webPage,
                            mimeType, sndBody,
                            userName, password,
                            rcvBody, output, printHead,
                            wsse, p3p, cookie,
                            webServerRedirected, cookieRedirected,
                            stackCount + 1 );
    else
        ret = _httpExecute( "GET",
                            xmlrpc_p->webServer, xmlrpc_p->webPage,
                            NULL, NULL,
                            userName, password,
                            rcvBody, output, printHead,
                            wsse, p3p, cookie,
                            webServerRedirected, cookieRedirected,
                            stackCount + 1 );
    if ( cookie ) {
        if ( !(*cookie) ) {
            if ( *saveCookie && **saveCookie )
                strcpy( cookie, *saveCookie );
        }
        else if ( !(*saveCookie) || !(**saveCookie)    ||
                  (strcmp( cookie, *saveCookie ) != 0)    ) {
            if ( *saveCookie )
                free( *saveCookie );
            *saveCookie = (char *)malloc( strlen( cookie ) + 1 );
            if ( *saveCookie )
                strcpy( *saveCookie, cookie );
        }
    }

    return ( ret );
}

int
_getStatusCode( const char *rcvData,
                char       *referer,
                char       *location,
                char       *basic )
{
    const char  *p = rcvData;
    const char  *q;
    const char  *r;
    int         statusCode;

    statusCode = atol( p );
    xmlrpc_p->statusCode = (unsigned short)(statusCode & 0xFFFF);
    switch ( statusCode ) {
    case 300: /* Multiple Choices */
    case 301: /* Moved Permanently */
    case 302: /* Moved Temporarily */
    case 303: /* See Other */
        if ( !strncmp( xmlrpc_p->webServer, "http", 4 ) )
            sprintf( referer, "%s%s",
                     xmlrpc_p->webServer,
                     xmlrpc_p->webPage );
        else
            sprintf( referer, "%s://%s%s",
                     xmlrpc_p->useSSL == FALSE
                        ? "http"
                        : "https",
                     xmlrpc_p->webServer,
                     xmlrpc_p->webPage );

        do {
            r = strstr( p, "-Location: " );
            q = strstr( p, "Location: " );
            if ( !q )
                q = strstr( p, "location: " ); // Echoo!

            if ( r && (r + 2 == q + 1) )
                p = r + 2;  // Wassr
        } while ( r && q );

        if ( q ) {
            const char  *r, *s, *t;
            char        *u;

            q += 10;
            r = strchr( q, '\r' );
            s = strchr( q, '\n' );
            t = (r && s) ? ((r < s) ? r : s)
                         : (r       ? r : s);
            if ( t ) {
                if ( *q == '/' ) {
                    int len;
                    sprintf( location, "%s",
                             xmlrpc_p->webServer );
                    len = strlen( location );
                    strncat( location, q, t - q );
                    location[len + (t - q)] = NUL;
                }
                else {
                    strncpy( location, q, t - q );
                    location[t - q] = NUL;
                }

                u = strchr( location, ';' );
                if ( u )
                    *u = NUL;

                r = strchr( location, '?' );
                if ( r ) {
                    // for BBAuth
                    r++;
                    while ( *r ) {
                        s = strchr( r, '=' );
                        if ( !s )
                            break;
                        r = s + 1;
                        s = strchr( r, '&' );
                        if ( !s )
                            s = r + (strlen(r) - 1);
                        while ( r < s ) {
                            switch ( *r ) {
                            case '%':
                                if ( !strncmp( r + 1, "3a", 2 ) ||
                                     !strncmp( r + 1, "3f", 2 )    ) {
                                    r += 2;
                                    u  = (char *)r;
                                    *u = (char)(*u - 'a' + 'A');
                                }
                                break;
                            case '=':
                                u = (char *)(r + strlen(r));
                                while ( u > r ) {
                                    *(u + 2) = *u;
                                    u--;
                                }
                                u = (char *)r;
                                *u++ = '%';
                                *u++ = '3';
                                *u++ = 'D';
                                r += 2;
                                s += 2;
                                break;
                            case ':':
                                u = (char *)(r + strlen(r));
                                while ( u > r ) {
                                    *(u + 2) = *u;
                                    u--;
                                }
                                u = (char *)r;
                                *u++ = '%';
                                *u++ = '3';
                                *u++ = 'A';
                                r += 2;
                                s += 2;
                                break;
                            case '/':
                                u = (char *)(r + strlen(r));
                                while ( u > r ) {
                                    *(u + 2) = *u;
                                    u--;
                                }
                                u = (char *)r;
                                *u++ = '%';
                                *u++ = '2';
                                *u++ = 'F';
                                r += 2;
                                s += 2;
                                break;
                            case '.':
                                if ( strncmp( r - 3, "%26", 3 ) != 0 ) {
                                    u = (char *)(r + strlen(r));
                                    while ( u > r ) {
                                        *(u + 2) = *u;
                                        u--;
                                    }
                                    u = (char *)r;
                                    *u++ = '%';
                                    *u++ = '2';
                                    *u++ = 'E';
                                    r += 2;
                                    s += 2;
                                }
                                break;
                            }

                            r++;
                        }
                    }
                }
            }
        }
        break;

    case 401: /* Authorization Required */
        q = strstr( p, "WWW-Authenticate: Basic" );
        if ( q ) {
            /* BASIC 認証の場合 */
            const char  *r, *s;

            strcpy( basic, "BASIC認証" );
            r = strstr( q + 23, "realm=\"" );
            if ( r ) {
                r += 7;
                s = strchr( r, '"' );
                if ( s ) {
                    strncpy( basic, r, s - r );
                    basic[s - r] = NUL;
                }
            }
        }
     /* else {
      *     // それ以外の認証の場合
      *     //  -- 未対応
      *  }
      */
        break;

    case 407: /* Proxy Authentication Required */
        q = strstr( p, "Proxy-Authenticate: Basic" );
        if ( !q )
            q = strstr( p, "Proxy-Authenticate: BASIC" );
        if ( q ) {
            /* BASIC 認証の場合 */
            const char  *r, *s;

            strcpy( basic, "BASIC認証" );
            r = strstr( q + 25, "realm=\"" );
            if ( r ) {
                r += 7;
                s = strchr( r, '"' );
                if ( s ) {
                    strncpy( basic, r, s - r );
                    basic[s - r] = NUL;
                }
            }
        }
        break;

    case 500:
    case 503:
        if ( xmlrpc_p->useProxy )
            if ( xmlrpc_p->useSSL )
                xmlrpc_p->recoverySSL = TRUE;
        break;

    default:
        break;
    }

    if ( (statusCode >= 400) && (statusCode <= 499) ) {
        const char  *r, *s;

        s = strstr( p, "Set-Cookie: BCSI-" );
        if ( s ) {
            s += 12;
            r = strchr( s, ';' );
            if ( !r )
                r = strchr( s, '\r' );
            if ( !r )
                r = strchr( s, '\n' );
            if ( r ) {
                strncpy( xmlrpc_p->proxyCookie, s, r - s );
                xmlrpc_p->proxyCookie[r - s] = NUL;
            }
        }
    }

    return ( statusCode );
}

char    *
getP3P( const char *rcvData,
        char       *p3p )
{
    const char  *p = rcvData;
    const char  *q, *r, *s;

    q = strchr( p, '\r' );
    r = strchr( p, '\n' );
    s = (q && r) ? ((q < r) ? q : r)
                 : (q       ? q : r);
    if ( s ) {
        strncpy( p3p, p, s - p );
        p3p[s - p] = NUL;
    }

    return ( p3p );
}

void
copyResponseBody(
        const char *buffer,
        size_t     bufferSz,
        char       *rcvBody,
        size_t     rcvLength,
        size_t     *binSize,
        BOOL       binary,
        int        *count
    )
{
    const char  *p, *q;
    size_t      sz = (bufferSz > 0)
                        ? bufferSz
                        : xmlrpc_p->rcvHTTPmessageSize;

    p = (bufferSz > 0) ? buffer : xmlrpc_p->rcvHTTP;
    q = strstr( p, "\r\n\r\n" );
    if ( q ) {
        *binSize = 0;
        q += 4;
        if ( binary ) {
            if ( rcvLength > 0 ) {
                size_t blen = sz - (q - p);
                if ( blen <= sz ) {
                    if ( blen < rcvLength ) {
                        memcpy( rcvBody, q, blen );
                        *binSize += blen;
                    }
                }
            }
        }
        else {
            if ( rcvLength > 0 ) {
                strncpy( rcvBody, q, rcvLength );
                rcvBody[rcvLength] = NUL;
            }
            else
                strcpy( rcvBody, q );
        }

        if ( *rcvBody )
            (*count)++;
    }
}

void
copyResponseBody2(
        const char *current,
        size_t     currentSz,
        char       *rcvBody,
        size_t     rcvLength,
        size_t     *binSize,
        BOOL       binary
    )
{
    if ( binary ) {
        if ( rcvLength > 0 ) {
            size_t blen = currentSz;
            if ( *binSize + blen < rcvLength )
                memcpy( rcvBody + *binSize, current, blen );
            *binSize += blen;
        }
    }
    else {
        if ( rcvLength > 0 ) {
            size_t  len = *rcvBody ? strlen( rcvBody ) : 0;
            strncat( rcvBody, current, rcvLength - len );
            rcvBody[rcvLength] = NUL;
        }
        else
            strcat( rcvBody, current );
    }
}

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
              int stackCount )
{
    int         ret   = -1;
    int         flag  = TRUE;
    int         count = 0, retryConnect = 0;
    char        *p, *q;
    const char  *newSndBody = sndBody;
    char        location[MAX_URLLENGTH_MAX];
    char        basic[128];
    char        *saveCookie = NULL;
    size_t      sndLength   = sndBody ? strlen( sndBody ) : 0;
    size_t      rcvLength   = 0;
    size_t      sndSize     = 0;
    size_t      binSize     = 0;
    BOOL        binary      = FALSE;
    int         statusCode;
    char        referer[MAX_URLLENGTH_MAX];

    if ( stackCount >= 12 ) {
        // スタックオーバーフロー防止
        return ( ret );
    }

    if ( rcvBody && (*(size_t *)rcvBody > 0) ) {
        /* 解説: rcvBody の先頭に rcvBody の示すメモリ領域のサイズをあらか */
        /*       じめ格納しておくことで、_httpExecute() にサイズを教えるこ */
        /*       とができる。 このサイズより大きな電文を受信した場合、サイ */
        /*       ズを超えた部分は捨てられる。なお、サイズを指定しないで    */
        /*       _httpExecute() を呼び出した場合、rcvBody の示す領域のサイ */
        /*       ズが  _httpExecute() にはわからないので、バッファオーバー */
        /*       ランが発生する可能性がある                                */
        getReceiveBufferSize( rcvBody, rcvLength );
    }
    if ( sndBody && (*(size_t *)sndBody > 0) ) {
        getSendBufferSize( sndBody, sndSize, newSndBody );
    }
    referer[0] = NUL;

    while ( isActive() ) {
        count++;
        if ( count > MAX_NUMBER_OF_ACTIVITY_CHECK )
            break;
        Sleep( PERIOD_OF_ACTIVITY_CHECK );
    }
    if ( count > MAX_NUMBER_OF_ACTIVITY_CHECK )
        return ( ret );
    count = 0;

    setActive( TRUE );

    if ( connectHTTP( xmlrpc_p->webServer, &flag, &retryConnect ) ) {
        setActive( FALSE );
        dputs( "\tconnect failed!\n" );
        return ( ret );
    }
    if ( xmlrpc_p->verbose )
        dputs( "\tconnected!\n" );

    if ( cookie && *cookie ) {
        saveCookie = (char *)malloc( strlen( cookie ) + 1 );
        if ( saveCookie )
            strcpy( saveCookie, cookie );   /* クッキー保存 */
    }

    makeRequestHeader( method,
                       webServer, webPage,
                       mimeType, sndBody,
                       userName, password, wsse, cookie,
                       sndLength, flag,
                       &sndSize, newSndBody );

    if ( sndSize > 0 )
        xmlrpc_p->sndHTTPmessageSize = sndSize;
    else
        xmlrpc_p->sndHTTPmessageSize = strlen( xmlrpc_p->sndHTTP );
    location[0] = NUL;
    basic[0]    = NUL;
    statusCode  = 200;

    ret = sendHTTP();
    if ( !ret ) {
#define MAX_TEMP_BUFSIZ 65536
        int     charSet = 0;
        char    *temp2  = (char *)malloc( MAX_TEMP_BUFSIZ + 1 );
        size_t  temp2Sz = 0;
        char    *pp;

#define CS_EUC  1
#define CS_UTF8 2

        if ( temp2 )
            memset( temp2, 0x00, MAX_TEMP_BUFSIZ + 1 );
        if ( cookie )
            *cookie = NUL;
        do {
            ret = recvHTTP();
            if ( xmlrpc_p->rcvHTTPmessageSize > 0 ) {
                p = xmlrpc_p->rcvHTTP;

                if ( temp2 && (temp2Sz < (MAX_TEMP_BUFSIZ / 2)) ) {
                    size_t  org = temp2Sz;
                    size_t  len = org + xmlrpc_p->rcvHTTPmessageSize;
                    if ( len < MAX_TEMP_BUFSIZ ) {
                        memcpy(temp2 + org, p, xmlrpc_p->rcvHTTPmessageSize);
                        temp2Sz += xmlrpc_p->rcvHTTPmessageSize;
                    }
                }

                if ( count == 0 ) {
                    pp = temp2 ? temp2 : xmlrpc_p->rcvHTTP;
                    if ( !strncmp( pp, "HTTP/1.", 7 ) ) {
                        char    *q = strchr( pp, ' ' );
                        if ( q )
                            statusCode = _getStatusCode( q + 1,
                                                         referer, location,
                                                         basic );
                        q = strstr( pp, "Content-Type:" );
                        if ( !q )
                            q = strstr( pp, "Content-type:" );
                        if ( q ) {
                            char    *r;

                            q += 13;
                            r = strstr( q, "text/" );
                            if ( !r )
                                r = strstr( q, "/xml" );
                            if ( !r )
                                r = strstr( q, "+xml" );
                            if ( !r )
                                r = strstr( q, "application/html" );
                            if ( !r )
                                r = strstr( q, "/json" );
                            if ( !r )
                                binary = TRUE;
                        }
                    }

                    if ( *p != '<' ) {
                        if ( p3p ) {
                            char    *q = strstr( p, "P3P: " );
                            if ( q )
                                getP3P( q, p3p );
                        }

                        if ( printHead ) {
                            if ( output )
                                fputs( p, output );
                            if ( xmlrpc_p->verbose ) {
                                dputs( p );
                                if ( (output != stdout)     &&
                                     isatty(fileno(stdout))    )
                                    fputs( p, stdout );
                            }
                            if ( rcvBody ) {
                                if ( rcvLength > 0 ) {  /* ↓ {@@} */
                                    size_t  len = *rcvBody ? strlen( rcvBody )
                                                           : 0;
                                    strncat( rcvBody, p, rcvLength - len );
                                    rcvBody[rcvLength] = NUL;
                                }                       /* ↑ {@@} */
                                else
                                    strcat( rcvBody, p );
                            }
                        }

                        if ( (( q = strchr( p, '<' ) ) != NULL) &&
                             ((unsigned char)(*(q - 1)) < ' ')     ) {/*{@@}*/
                            if ( cookie ) {
                                int     l = *cookie ? strlen( cookie ) : 0;
                                if ( l + (q - p) < MAX_COOKIE_LEN ) {
                                    strncat( cookie, p, q - p );
                                    cookie[l + (q - p)] = NUL;
                                }
                            }
                            p = q;
                        }
                        else {
                            pp = temp2 ? temp2 : p;
                            q  = strstr( pp, "\r\n\r\n" );
                            if ( pp == temp2 ) {
                                if ( cookie )
                                    *cookie  = NUL;
                                if ( rcvBody )
                                    *rcvBody = NUL;
                                p = pp;
                            }
                            if ( cookie ) {
                                size_t  len  = strlen( cookie );
                                char    *ppp = p;
                                if ( pp == temp2 ) {
                                    ppp = strstr( pp, "Set-Cookie: " );
                                    if ( !ppp || (ppp > q) )
                                        ppp = p;
                                }
                                if (q && (len + (q - ppp) < MAX_COOKIE_LEN)) {
                                    strncat( cookie, ppp, q - ppp );
                                    cookie[len + (q - ppp)] = NUL;
                                }
                                else
                                if ( len + strlen( ppp ) >= MAX_COOKIE_LEN ) {
                                    strncat( cookie, ppp,
                                             MAX_COOKIE_LEN - len - 1 );
                                    cookie[MAX_COOKIE_LEN - 1] = NUL;
                                }
                                else
                                    strcat( cookie, ppp );
                            }

                            if ( rcvBody && !(*rcvBody) )
                                copyResponseBody( temp2, temp2Sz,
                                                  rcvBody, rcvLength,
                                                  &binSize, binary,
                                                  &count );
                            continue;
                        }
                    }
                }

                if ( output )
                    fputs( p, output );
                if ( xmlrpc_p->verbose      &&
                     (output != stdout)     &&
                     isatty(fileno(stdout))    ) {
#ifdef  WIN32
                    char    *q;

                    if ( !strncmp( p, "<?xml", 5 ) ) {
                        if ( (q = strstr( p, "encoding=\"" )) != NULL ) {
                            q += 10;
                            if ( !strncmpi( q, "EUC-JP", 6 ) )
                                charSet = CS_EUC;
                            else if ( !strncmpi( q, "UTF-8", 5 ) )
                                charSet = CS_UTF8;
                        }
                    }

                    q = NULL;
                    if ( charSet == CS_EUC )
                        q = euc2sjis( p );
                    else if ( charSet == CS_UTF8 )
                        q = utf2sjis( p );
                    fputs( q ? q : p, stdout );
#else
                    fputs( p, stdout );
#endif
                }

                if ( rcvBody )
                    copyResponseBody2( p, xmlrpc_p->rcvHTTPmessageSize,
                                       rcvBody, rcvLength,
                                       &binSize, binary );
            }
            else if ( xmlrpc_p->verbose ) {
                const char  *ppp = temp2;
                const char  *qqq = strstr( ppp, "\r\n\r\n" );

                if ( qqq ) {
                    const char  *r;

                    dputs( "\r\n>>\r\n" );
                    for ( r = ppp; r < qqq + 2; r++ )
                        dputc( *r );
                    dputs( "<<\r\n" );
                }
            }

            count++;
#ifdef  DEBUG
            dprintf( "\tcount = %d\n", count );
#endif
        } while ( !ret );

        if ( temp2 ) {
            if ( rcvBody && !(*rcvBody) )
                copyResponseBody( temp2, temp2Sz,
                                  rcvBody, rcvLength,
                                  &binSize, binary,
                                  &count );
            free( temp2 );
        }
    }
    else
        dputs( "\tsendHTTP(): failed\n" );

    disconnectHTTP();

    setActive( FALSE );

    if ( cookie && *cookie )
        restructCookie( cookie, &saveCookie );  /* クッキー再構築 */

    if ( location[0] ) {
        char    redirectOK = TRUE;
        char    *p = strstr( location, "://" );
        if ( p ) {
            p += 3;
            if ( !strncmp( p, webServer, strlen(webServer) ) ) {
                p += strlen(webServer);
                if ( !strcmp( p, webPage ) ) {
                    // redirct 先の URL とカレント URL が一致
                    if ( xmlrpc_p->recoverySSL )
                        redirectOK = FALSE; // 無限に redirct し続けるのを防ぐ
                    else
                        xmlrpc_p->recoverySSL = TRUE;
                }
            }
#if 0
            if ( (xmlrpc_p->useSSL == FALSE)         &&
                 !strncmp( location, "https://", 8 )    ) {
                redirectOK = FALSE;
                /* http から https に切り替わったときは redirect は保留 */
            }
#endif
        }

        if ( redirectOK ) {
            /* Location: で指定された url へアクセス */
            if ( xmlrpc_p->userAgent[0]                     &&
                 !strstr( xmlrpc_p->userAgent, "Firefox/" )    )
                if ( referer[0] )
                    setReferer( referer );
            ret = _httpRedirect( method, webServer,
                                 mimeType, sndBody,
                                 userName, password,
                                 rcvBody, output, printHead,
                                 wsse, p3p, cookie, &saveCookie,
                                 webServerRedirected, cookieRedirected,
                                 stackCount + 1,
                                 location, statusCode,
                                 rcvLength );
            location[0] = NUL;
        }
    }
    else  if ( basic[0] ) {
        if ( statusCode == 407 ) {
            if ( xmlrpc_p->proxyUserName[0] == NUL ) {
                // proxy サーバ情報設定し直し
                BOOL    useProxy = FALSE;
                if ( xmlrpc_p->confirmProxyInfo ) {
                    if ( xmlrpc_p->confirmProxyInfo != (CONF_FUNC)(-1) )
                        xmlrpc_p->confirmProxyInfo( &useProxy,
                                                    xmlrpc_p->proxyServer,
                                                    &(xmlrpc_p->proxyPort),
                                                    xmlrpc_p->proxyUserName,
                                                    xmlrpc_p->proxyPassword );
                }
                else
                    confirmProxyInfo( &useProxy,
                                      xmlrpc_p->proxyServer,
                                      &(xmlrpc_p->proxyPort),
                                      xmlrpc_p->proxyUserName,
                                      xmlrpc_p->proxyPassword );
            }
            else if ( xmlrpc_p->proxyCookie[0] ) {
                // retry
                if ( rcvLength > 0 )
                    setUpReceiveBuffer( rcvBody, rcvLength );
                ret = _httpExecute( method,
                                    webServer, webPage,
                                    mimeType,  sndBody,
                                    userName,  password,
                                    rcvBody,   output, printHead,
                                    wsse,      p3p,    cookie,
                                    webServerRedirected, cookieRedirected,
                                    stackCount + 1 );
                }
        }
        else {
            /* BASIC認証に切り替えてアクセスし直し */
            ret = _httpExecuteBASIC( method,
                                     mimeType, sndBody,
                                     userName, password,
                                     rcvBody, output, printHead,
                                     wsse, p3p, cookie,
                                     webServerRedirected, cookieRedirected,
                                     stackCount + 1,
                                     basic,
                                     rcvLength );
        }
    }

    if ( xmlrpc_p->recoverySSL ) {
        if ( (statusCode == 500) || (statusCode == 503) ) {
            if ( rcvLength > 0 ) {
                setUpReceiveBuffer( rcvBody, rcvLength );
            }
            ret = _httpExecute( method,
                                webServer, webPage,
                                mimeType,  sndBody,
                                userName,  password,
                                rcvBody,   output, printHead,
                                wsse,      p3p,    cookie,
                                webServerRedirected, cookieRedirected,
                                stackCount + 1 );
        }
    }

    /* ゴミ掃除 */
    if ( rcvBody && *rcvBody && !binary )
        deleteChunkedData( rcvBody );

    if ( saveCookie ) {
        /* クッキー復元 (必要がある場合のみ) */
        if ( cookie && *saveCookie &&
             (!(*cookie) || (strcmp(cookie, saveCookie) != 0)) ) {
            strcpy( cookie, saveCookie );
        }
        free( saveCookie );
        saveCookie = NULL;
    }

    xmlrpc_p->binSize = binSize;

    return ( ret );
}



/*
 *  _httpGet() --- get a web page via httpd process
 *      arguments: 
 *          char *webServer;   web server which has target web page
 *          char *webPage;     target web page
 *      return: if get OK, returns 0; else returns non 0 value
 *              (if detected disconnection before receiving target web page,
 *               returns -2)
 */

int
_httpGet( const char *webServer, const char *webPage,
          const char *userName,  const char *password,
          char *rcvBody, FILE *output, int printHead,
          const char *wsse, char *p3p, char *cookie,
          char *webServerRedirected, char *cookieRedirected )
{
    int stackCount = 0;

    return ( _httpExecute( "GET", webServer, webPage,
                           NULL, NULL,
                           userName, password,
                           rcvBody, output, printHead, wsse, p3p, cookie,
                           webServerRedirected, cookieRedirected,
                           stackCount ) );
}

/*
 *  _httpDelete() --- delete a web page via httpd process
 *      arguments: 
 *          char *webServer;   web server which has target web page
 *          char *webPage;     target web page
 *      return: if get OK, returns 0; else returns non 0 value
 *              (if detected disconnection before receiving a response from
 *               target web page, returns -2)
 */

int
_httpDelete( const char *webServer, const char *webPage,
             const char *userName,  const char *password,
             char *rcvBody, FILE *output, int printHead,
             const char *wsse )
{
    int stackCount = 0;

    return ( _httpExecute( "DELETE", webServer, webPage,
                           NULL, NULL,
                           userName, password,
                           rcvBody, output, printHead, wsse, NULL, NULL,
                           NULL, NULL,
                           stackCount ) );
}

/*
 *  _httpPost() --- post a request via httpd process
 *      arguments: 
 *          char *webServer;   web server which has target web page
 *          char *webPage;     target web page
 *      return: if get OK, returns 0; else returns non 0 value
 *              (if detected disconnection before receiving a response,
 *               returns -2)
 */

int
_httpPost( const char *webServer, const char *webPage,
           const char *userName,  const char *password,
           const char *mimeType,
           const char *request, char *response,
           const char *wsse,    char *cookie,
           char *webServerRedirected, char *cookieRedirected )
{
    int stackCount = 0;

    return ( _httpExecute( "POST", webServer, webPage,
                           mimeType, request,
                           userName, password,
                           response, NULL,
                           FALSE,
                           wsse, NULL, cookie,
                           webServerRedirected, cookieRedirected,
                           stackCount ) );
}


/*
 *  HTTPリクエスト主要メソッド個別処理関数群
 */

/* HTTP GET メソッドを実行 */
char    *
http_get( const char *url,
          char *response )
{
    int ret = httpGetBuffer( url, response, FALSE );

    return ( ret == -1 ? NULL : response );
}

char    *
http_getEx( const char *url,
            char *response, char *cookie )
{
    int ret;
#ifdef  _DEBUG
    if ( xmlrpc_p->verbose ) {
        dprintf( "http_getEx():\n"
                 "    url    = %s\n"
                 "    cookie = %s\n",
                 url, cookie && *cookie ? cookie : " " );
    }
#endif
    ret = httpGetBufferWithSession( url,
                                    response, FALSE,
                                    NULL, NULL, cookie,
                                    NULL, NULL );
#ifdef  _DEBUG
    if ( xmlrpc_p->verbose ) {
        dprintf( "--- cookie = %s\n",
                 cookie && *cookie ? cookie : " " );
    }
#endif

    return ( ret == -1 ? NULL : response );
}

char    *
http_getEx2( const char *url,
             char *response, char *cookie,
             char *webServerRedirected, char *cookieRedirected )
{
    int ret = httpGetBufferWithSession( url,
                                        response, FALSE,
                                        NULL, NULL, cookie,
                                        webServerRedirected, cookieRedirected );

    return ( ret == -1 ? NULL : response );
}

char    *
http_getBASIC( const char *url,
               const char *userName, const char *password,
               char *response )
{
    /* http_get() の BASIC認証対応版 */
    int ret = httpGetBufferBASIC( url, userName, password, response, FALSE );

    return ( ret == -1 ? NULL : response );
}

char    *
http_getBASICEx( const char *url,
                 const char *userName, const char *password,
                 char *response, char *cookie )
{
    int ret;

    /* http_getEx() の BASIC認証対応版 */
    setTargetURL( url );
    ret = httpGetBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        userName, password,
                        response, NULL, FALSE, NULL, NULL,
                        cookie,
                        NULL, NULL );

    return ( ret == -1 ? NULL : response );
}


/* HTTP HEAD メソッドを実行 */
char    *
http_head( const char *url, char *response )
{
    int ret;
    int stackCount = 0;
    
    setTargetURL( url );
    ret = _httpExecute( "HEAD", xmlrpc_p->webServer, xmlrpc_p->webPage,
                        NULL, NULL,
                        NULL, NULL,
                        response, NULL, TRUE,
                        NULL, NULL, NULL,
                        NULL, NULL,
                        stackCount );

    return ( ret == -1 ? NULL : response );
}

char    *
http_headEx( const char *url, char *response, char *cookie )
{
    int ret;
    int stackCount = 0;
    
    setTargetURL( url );
    ret = _httpExecute( "HEAD", xmlrpc_p->webServer, xmlrpc_p->webPage,
                        NULL, NULL,
                        NULL, NULL,
                        response, NULL, TRUE,
                        NULL, NULL, cookie,
                        NULL, NULL,
                        stackCount );

    return ( ret == -1 ? NULL : response );
}

char    *
http_headBASIC( const char *url,
                const char *userName, const char *password,
                char *response )
{
    int ret;
    int stackCount = 0;
    
    setTargetURL( url );
    ret = _httpExecute( "HEAD", xmlrpc_p->webServer, xmlrpc_p->webPage,
                        NULL, NULL,
                        userName, password,
                        response, NULL, TRUE,
                        NULL, NULL, NULL,
                        NULL, NULL,
                        stackCount );

    return ( ret == -1 ? NULL : response );
}


/* HTTP DELETE メソッドを実行 */
char    *
http_delete( const char *url, char *response )
{
    int ret;
    
    setTargetURL( url );
    ret = _httpDelete( xmlrpc_p->webServer, xmlrpc_p->webPage,
                       NULL, NULL,
                       response, NULL, FALSE, NULL );

    return ( ret == -1 ? NULL : response );
}


/* HTTP POST メソッドを実行 */
char    *
http_post( const char *url, const char *mimeType, const char *request,
           char *response )
{
    int ret;

    setTargetURL( url );
    ret = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    mimeType, request, response );

    return ( ret == -1 ? NULL : response );
}

char    *
http_postEx( const char *url, const char *mimeType, const char *request,
             char *response, char *cookie )
{
    int ret;

#ifdef  _DEBUG
    if ( xmlrpc_p->verbose ) {
        dprintf( "http_postEx():\n"
                 "    url      = %s\n"
                 "    mimeType = %s\n"
                 "    request  = %s\n"
                 "    cookie   = %s\n",
                 url,
                 mimeType,
                 request && *request &&
                    (strlen(request) < MAX_DESCRIPTION_LEN)
                                                ? request : "(略)",
                 cookie && *cookie ? cookie : " " );
    }
#endif
    setTargetURL( url );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               mimeType, request, response, cookie,
                               NULL, NULL );
#ifdef  _DEBUG
    if ( xmlrpc_p->verbose ) {
        dprintf( "--- cookie = %s\n",
                 cookie && *cookie ? cookie : " " );
    }
#endif

    return ( ret == -1 ? NULL : response );
}

char    *
http_postEx2( const char *url, const char *mimeType, const char *request,
              char *response, char *cookie,
              char *webServerRedirected, char *cookieRedirected )
{
    int ret;

    setTargetURL( url );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               mimeType, request, response, cookie,
                               webServerRedirected, cookieRedirected );

    return ( ret == -1 ? NULL : response );
}

char    *
http_postBASIC( const char *url,
                const char *userName, const char *password,
                const char *mimeType, const char *request,
                char *response )
{
    int ret;

    setTargetURL( url );
    ret = httpPostBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                         userName, password,
                         mimeType,
                         request, response );

    return ( ret == -1 ? NULL : response );
}

/* HTTP PUT メソッドを実行 */
char    *
http_put( const char *url, const char *mimeType, const char *filename,
          char *response )
{
    int         ret, sz, remain;
    char        *buf, *p;
    struct stat s;
    FILE        *fp;
    BOOL        done = FALSE;
    int         stackCount = 0;

    if ( ( fp = fopen( filename, "r" ) ) == NULL ) {
        dprintf( "ファイル %s が見つかりません\n", filename );
        return ( NULL );
    }
    fclose( fp );

    if ( stat( filename, &s ) != 0 ) {
        dprintf( "ファイル %s の状態が取得できません\n", filename );
        return ( NULL );
    }

    buf = (char *)malloc( s.st_size * sizeof ( char ) );
    if ( !buf ) {
        dputs( "メモリが足りません\n" );
        return ( NULL );
    }

    p = buf;
    remain = s.st_size;
    fp = fopen( filename, "rb" );
    do {
        sz = fread( p, sizeof ( char ), remain, fp );
        if ( sz <= 0 )
            done = TRUE;
        else {
            remain -= sz;
            if ( remain <= 0 )
                break;
            p += sz;
        }
    } while ( done != TRUE );
    fclose( fp );

    if ( !mimeType || !strcmp( mimeType, "text/plain" ) )
        p = buf;
    else
        p = base64( (unsigned char *)buf, s.st_size );

    setTargetURL( url );
    ret = _httpExecute( "PUT", xmlrpc_p->webServer, xmlrpc_p->webPage,
                        mimeType, p,
                        NULL, NULL,
                        response, NULL, FALSE,
                        NULL, NULL, NULL,
                        NULL, NULL,
                        stackCount );
    free( buf );

    return ( ret == -1 ? NULL : response );
}


size_t  getBinSize()
{
    return ( xmlrpc_p->binSize );
}

unsigned short  getStatusCode()
{
    return ( xmlrpc_p->statusCode );
}
