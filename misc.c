/*
 *  misc.c
 *      ユーティリティ関数群
 *
 * History:
 * $Log: /comm/xmlRPC/misc.c $
 * 
 * 2     09/05/27 2:56 tsupo
 * ./noproxy.txt ファイルがあれば、「proxyを使わない」と判断するようにした
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 92    09/03/30 19:48 Tsujimura543
 * OAuth 対応
 * 
 * 91    09/03/20 22:25 Tsujimura543
 * 「はてなダイアリー」の Atom API に対応
 * 
 * 90    08/11/17 22:10 Tsujimura543
 * static char → Thread static char に変更
 * 
 * 89    08/02/07 19:03 Tsujimura543
 * isUsedProxy() / getProxyInfo() が何回も繰り返し呼び出されてしまう
 * ことがある現象に対処
 * 
 * 88    07/12/06 1:15 Tsujimura543
 * unbase64() の引数を追加
 * 
 * 87    07/10/16 22:50 Tsujimura543
 * __argv[0] にディレクトリ名が含まれない場合にも対応
 * 
 * 86    07/10/10 2:03 Tsujimura543
 * dprintf() 内の作業用バッファサイズを固定に戻す
 * 
 * 85    07/10/09 21:26 Tsujimura543
 * dprintf() 内で使用するバッファのサイズ計算式を修正
 * 
 * 84    07/10/09 20:08 Tsujimura543
 * dputc() を追加
 * 
 * 83    07/10/09 19:36 Tsujimura543
 * dprintf() 内の作業用バッファサイズを可変にする
 * 
 * 82    07/10/09 19:32 Tsujimura543
 * dputs() と dprintf() を追加
 * 
 * 81    07/09/28 19:18 Tsujimura543
 * XMLRPC_ERROR_CHANGED_PROXYINFO を導入
 * 
 * 80    07/09/28 18:42 Tsujimura543
 * confirmProxyInfo() で表示するダイアログ(MessageBox)の文言を修正
 * 
 * 79    07/09/14 22:41 Tsujimura543
 * setReferer() を修正 (referer の最大長を変更)
 * 
 * 78    07/09/10 19:04 Tsujimura543
 * makeRurl() を廃止
 * 
 * 77    07/09/04 20:21 Tsujimura543
 * verboseFp を追加し、setVerbos() の第2引数で値を変更できるようにした
 * 
 * 76    07/09/04 20:10 Tsujimura543
 * dumpFp を追加し、setDump() の第2引数で値を変更できるようにした
 * 
 * 75    07/08/24 18:38 Tsujimura543
 * setReferer() を追加
 * 
 * 74    07/07/03 14:39 Tsujimura543
 * decodeString() に &dquot; に関する処理を追加
 * 
 * 73    07/06/04 14:33 Tsujimura543
 * getProxyInfo() を修正 (__argv が取れないときに落ちる不具合に対処)
 * 
 * 72    07/05/21 19:53 Tsujimura543
 * getProxyInfo() の proxy.txt を読む部分を修正
 * 
 * 71    07/04/10 23:12 Tsujimura543
 * リファクタリング
 * 
 * 70    07/04/09 19:10 Tsujimura543
 * makeRurl() を修正
 * 
 * 69    07/04/09 17:36 Tsujimura543
 * rurl.org API 関連処理を追加
 * 
 * 68    07/04/09 16:34 Tsujimura543
 * setProxyInfo() を変更、いったん初期化してから設定が必要なメンバのみ
 * いじるようにした
 * 
 * 67    07/04/09 16:26 Tsujimura543
 * getProxyInfo() を修正、無限に「proxy情報問い合わせ」メッセージボックス
 * が出続ける現象に対処 [対症療法] (想定しているレジストリ構成ではない場
 * 合に発生?)
 * 
 * 66    07/03/13 19:54 Tsujimura543
 * useProxy が TRUE のとき、setTargetURL() 内で毎回 getproxyInfo() する
 * ようになっていたのをやめる
 * 
 * 65    07/03/13 19:18 Tsujimura543
 * setProxy() → setProxyInfo() に名称変更
 * 
 * 64    07/03/13 19:16 Tsujimura543
 * setProxy() を追加
 * 
 * 63    07/03/10 6:15 Tsujimura543
 * proxy関連の処理を修正
 * 
 * 62    07/03/10 5:05 Tsujimura543
 * confirmProxyInfo() の引数を2個追加
 * 
 * 61    07/03/10 4:58 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応
 * 
 * 60    07/03/09 21:13 Tsujimura543
 * isNecessaryToCheckProxyInfo() を追加、およびそれに伴う修正を実施
 * 
 * 59    07/03/09 17:26 Tsujimura543
 * (1) getProxyInfo() を修正 (proxy情報の自動取得に失敗した場合の処理
 *     を追加)
 * (2) setConfirmProxyInfoFunc() を追加
 * 
 * 58    07/03/03 15:21 Tsujimura543
 * sjis2utf() が NULL を返す場合の対策を実施
 * 
 * 57    07/02/14 22:10 Tsujimura543
 * getProxyInfoViaOpera() は現在のコードのままいじらなくてもいいことを確認
 * 
 * 56    07/02/13 12:04 Tsujimura543
 * getProxyInfoViaInternetExplorer() と getProxyInfoViaFirefox() を
 * 修正。proxyサーバの設定は残ったままであるが、proxyサーバは使わな
 * い設定に変更しているといった状況にも対応
 * 
 * 55    07/01/17 16:54 Tsujimura543
 * Windows の「言語」の取得、設定用の関数を追加
 * 
 * 54    06/10/27 1:54 Tsujimura543
 * getProxyInfo() 関連の改修を実施し、Firefox 2 に対応した
 * 
 * 53    06/10/19 22:58 Tsujimura543
 * 今までライブラリ外には 非公開だった getProxyInfo() を公開することにした
 * 
 * 52    06/09/19 17:01 Tsujimura543
 * (1) 不要になったコードの削除
 * (2) Opera 9 に関する処理の説明(コメント)を追加
 * 
 * 51    06/09/19 16:17 Tsujimura543
 * getProxyInfo() 関連の改修を実施
 *   (1) 「通常使用するブラウザ」の設定を優先的に取得するようにした
 *   (2) Opera 9 に対応した (従来の Opera 対応処理は Opera 8 までにしか
 *       対応しきれていなかった)
 * 
 * 50    06/09/11 12:05 Tsujimura543
 * コメントを追加
 * 
 * 49a   06/09/10 5:48 tsupo
 * resetDaylightSaving() を導入した
 * (Visual Studio 2005 の C++ ランタイム使用時に、日本時間なのに夏時間と
 * 判定されてしまう件の対策)
 * 
 * 49    06/07/24 20:10 Tsujimura543
 * _httpExecute() のバッファオーバーラン防止機能を利用するようにした
 * 
 * 48    06/06/01 14:33 Tsujimura543
 * getTrackbackURL() を楽天広場の「暗号化されたトラックバックURL」に対応
 * 
 * 47    06/03/13 16:49 Tsujimura543
 * getCurrentLocation() を追加
 * 
 * 46    06/03/09 14:37 Tsujimura543
 * unbase64() をより厳密な処理を行なうように書き直した
 *  (処理結果自体は今までと同じ)
 * 
 * 45    06/01/26 18:09 Tsujimura543
 * バッファオーバーラン対策を実施
 * 
 * 44    06/01/25 19:18 Tsujimura543
 * 修正後の setTargetURL() の動作を確認。問題なし
 * 
 * 43    06/01/25 19:14 Tsujimura543
 * setTargetURL() を修正 (ルートディレクトリを示す URL の場合、末尾の / が抜け
 * ていたら補完するようにした  [例えば、http://aaa.bbb → http://aaa.bbb/ のよ
 * うに / を付加してから、処理を行なうようにした])
 * 
 * 42    06/01/10 15:26 Tsujimura543
 * setUserAgent() を修正し、一度設定した User-Agent をデフォルト値に戻せる
 * ようにした
 * 
 * 41    06/01/10 15:12 Tsujimura543
 * userAgent / setUserAgent() を追加
 * 
 * 40    05/10/31 13:49 Tsujimura543
 * getProxyInfoViaFirefox() を修正し、設定ファイルをデフォルトの場所以外に
 * 変更している場合にも対応できるようにした
 * 
 * 39    05/10/18 18:08 Tsujimura543
 * httpGet() の引数追加に伴う修正を実施
 * 
 * 38    05/10/04 15:07 Tsujimura543
 * Opera の設定情報から proxy 関連情報を読み取る処理を追加
 * 
 * 37    05/10/04 14:01 Tsujimura543
 * Firefox の設定情報から proxy 関連情報を読み取る処理を追加
 * 
 * 36    05/03/25 17:03 Tsujimura543
 * isDecString() を追加
 * 
 * 35    05/03/25 16:49 Tsujimura543
 * isHexString() を webry.c から移動
 * 
 * 34    05/03/22 15:00 Tsujimura543
 * isUsedProxy() を追加
 * 
 * 33    05/02/23 10:59 Tsujimura543
 * getTrackbackURL() 内に「ゴミ掃除」処理を追加
 * 
 * 32    05/02/21 10:27 Tsujimura543
 * getTrackbackURL() を修正 (同一Webページ内にレントラを複数設置している
 * 場合の対策)
 * 
 * 31    05/02/17 12:06 Tsujimura543
 * レントラ関連処理を修正
 * 
 * 30    05/02/15 19:53 Tsujimura543
 * sendTrackbackPing() 内の str[3] のバッファサイズが不足して領域破壊が
 * 発生していたのを修正
 * 
 * 29    05/02/14 19:16 Tsujimura543
 * トラックバック関連処理をいったん Fix
 * 
 * 28    05/02/14 19:13 Tsujimura543
 * normalizeString() を追加、トラックバック送信処理を normalizeString()
 * を使って書き直し
 * 
 * 27    05/02/14 18:37 Tsujimura543
 * getTrackbackURL() で取得した URL の末尾にゴミがつくことがある不具合
 * に対処
 * 
 * 26    05/02/09 18:12 Tsujimura543
 * getTrackbackURL() を XOOPS に対応
 * 
 * 25    05/02/09 18:03 Tsujimura543
 * getTrackbackURL() を teeter totter に対応
 * 
 * 24    05/02/09 13:43 Tsujimura543
 * 「取得したURLが相対パス表記であれば絶対パス表記に変換する処理」を追加
 * 
 * 23    05/02/08 19:05 Tsujimura543
 * getTrackbackURL() を HaloScan を使っている Web ページにも対応させた
 * 
 * 22    05/02/08 15:38 Tsujimura543
 * getTrackbackURL() を MSN Spaces に対応
 * 
 * 21    05/02/07 13:59 Tsujimura543
 * getTrackbackURL() を NAVERブログ と BLOGari にも対応
 * 
 * 20    05/02/07 11:24 Tsujimura543
 * getTrackbackURL() を「関西どっとコム」にも対応
 * 
 * 19    05/02/05 19:38 Tsujimura543
 * getTrackbackURL() を更に修正 (楽天広場関連処理) → 動作確認完了
 * 
 * 18    05/02/05 19:09 Tsujimura543
 * getTrackbackURL() を更に修正 (楽天広場関連処理)
 * 
 * 17    05/02/05 18:24 Tsujimura543
 * getTrackbackURL() を修正 (レントラ, 楽天広場 関連処理の各バグFix)
 * 
 * 16    05/02/03 14:06 Tsujimura543
 * getTrackbackURL() を「マイぷれす」にも対応させた
 * 
 * 15    05/02/02 20:45 Tsujimura543
 * トラックバック送信時に error 応答が返ってきたかどうかチェックするよう
 * にした
 * 
 * 14    05/02/02 13:13 Tsujimura543
 * memla! blog 対策 (トラックバック送信に対する応答受信用バッファサイズを
 * 増やす)
 * 
 * 13    05/01/28 14:56 Tsujimura543
 * FC2BLOG の3つのサーバのうち blog2.fc2.com にある blog のみ、trackback
 * auto-discovery がうまく働かない(テンプレートのバグだそうです)現象に、本
 * ライブラリ側で暫定的に対処
 * 
 * 12    05/01/26 22:01 Tsujimura543
 * レントラを使っているWebページのトラックバック送信用URLも取得できるよう
 * にした
 * 
 * 11    05/01/26 20:21 Tsujimura543
 * getTrackbackURL() を追加
 * 
 * 10    04/11/25 10:06 Tsujimura543
 * setTargetURL() を修正。冒頭で必ず useSSL をクリアする(FALSEにする)
 * ようにした。
 * 
 * 9     04/11/19 14:55 Tsujimura543
 * https 対応
 * 
 * 8     04/11/15 17:06 Tsujimura543
 * encodeURL() 内で確保した領域の解放処理を追加
 * 
 * 7     04/11/12 15:45 Tsujimura543
 * unbase64() を追加 (動作確認済み)
 * 
 * 6     04/11/01 21:02 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 5     04/09/03 15:25 Tsujimura543
 * マイプロフィール対応 [暫定]
 * 
 * 4     04/08/31 15:57 Tsujimura543
 * decodeString() での &amp; 絡みの処理を修正
 * 
 * 3     04/07/08 16:33 Tsujimura543
 * 関数 setTargetURL() に blog 種別設定機能を付加。
 * 
 * 2     04/07/07 11:55 Tsujimura543
 */

#include "xmlRPC.h"
#include <sys/stat.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/misc.c 2     09/05/27 2:56 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/*
 *  外部非公開 ユーティリティ関数
 */

/*
 *  漢字を含む文字列(Shift_JIS)を指定した長さに切り詰める
 */

#ifndef	iskanji1
#define	iskanji1(s) \
    (((((short)s & 0xFF)>=0x81) && (((short)s & 0xFF)<=0x9f)) || \
     ((((short)s & 0xFF)>=0xe0) && (((short)s & 0xFF)<=0xfc)))
#endif
#ifndef	iskanji2
#define	iskanji2(s) \
    (((((short)s & 0xFF)>=0x40) && (((short)s & 0xFF)<=0x7e)) || \
     ((((short)s & 0xFF)>=0x80) && (((short)s & 0xFF)<=0xfc)))
#endif

char    *
normalizeString( char *dst, const char *src, size_t len )
{
    /* 漢字の1バイト目で終了するのを避ける */
    char        *p = dst;
    const char  *q = src;
    int         flag = 0;

    if ( !p || !q )
        return ( p );

    if ( *q && (strlen( q ) > len) ) {
        strncpy( p, q, len );
        p[len] = NUL;
    }
    else
        strcpy( p, q );

    while ( *q ) {
        if ( (flag == 0) && iskanji1( *q ) ) {
            flag = 1;
        }
        else if ( (flag == 1) && iskanji2( *q ) ) {
            flag = 0;
        }
        q++;
    }

    if ( flag )
        p[len - 1] = NUL;

    return ( p );
}


/*
 *  proxy サーバ名 と proxy ポート番号の取得
 *    ・proxy.txt というファイルが存在する場合、当該ファイルから情報を読み取る
 *    ・proxy.txt というファイルが存在しない場合、Win32 環境であれば、Internet
 *      Explorer の proxy 関連情報を読み取る(Internet Explorer の proxy 関連情
 *      報が読み取れなかった場合は、Firefox の proxy 関連情報を読み取る。 さら
 *      に Firefox の情報も取れなかった場合は、Opera の情報を取る)
 *   なお、proxy に関する「情報」のフォーマットは  サーバ名:ポート番号 という
 *   形式とする
 */

#define BR_UNKNOWN      0   /* 不明    */
#define BR_IEXPLORER    1   /* IE      */
#define BR_FIREFOX      2   /* Firefox */
#define BR_OPERA        3   /* Opera   */
#define BR_EXTRA        4   /* その他  */

static int
getDefaultBrowser( void )
{
    int     ret = BR_UNKNOWN;
    long    r;
    HKEY    hk;
    long    type;
    char    buf[BUFSIZ];
    long    sz = BUFSIZ - 1;

#if 0
    r = RegOpenKeyEx( HKEY_CLASSES_ROOT,
                      "htmlfile\\shell\\open\\command",
                      0,
                      KEY_READ,
                      &hk );
#else
    r = RegOpenKeyEx( HKEY_CLASSES_ROOT,
                      "http\\shell\\open\\ddeexec\\Application",
                      0,
                      KEY_READ,
                      &hk );
#endif
    if ( r == ERROR_SUCCESS ) {
        r = RegQueryValueEx( hk,
                             "",
                             NULL,
                             (unsigned long *)&type,
                             (unsigned char *)buf,
                             (unsigned long *)&sz );
        if ( r == ERROR_SUCCESS ) {
            if ( type == REG_SZ ) {
                if ( strstr( buf, "iexplore" ) ||
                     strstr( buf, "IExplore" )    )
                    ret = BR_IEXPLORER;
                else if ( strstr( buf, "firefox" ) ||
                          strstr( buf, "Firefox" )    )
                    ret = BR_FIREFOX;
                else if ( strstr( buf, "opera" ) ||
                          strstr( buf, "Opera" )    )
                    ret = BR_OPERA;
                else
                    ret = BR_EXTRA;
            }
        }
        RegCloseKey( hk );
    }

    return ( ret );
}

static BOOL
getProxyInfoViaInternetExplorer(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword
    )
{
    /*
     *  Internet Explorer の設定を調べる
     */

    /* 以下のレジストリから proxy 関連情報を取得する                   */
    /*   HKEY_CURRENT_USER                                             */
    /*     Software\Microsoft\Windows\CurrentVersion\Internet Settings */
    /*       ProxyServer                                               */

    long    ret;
    HKEY    hk;
    long    type;
    char    buf[BUFSIZ], *p;
    long    sz = BUFSIZ - 1;
    BOOL    isInternetExplorerActive = FALSE;

    ret = RegOpenKeyEx( HKEY_CURRENT_USER,
            "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
                        0,
                        KEY_READ,
                        &hk );
    if ( ret == ERROR_SUCCESS ) {
        isInternetExplorerActive = TRUE;
                            /* Internet Explorer インストール済み */
        ret = RegQueryValueEx( hk,
                               "ProxyEnable",
                               NULL,
                               (unsigned long *)&type,
                               (unsigned char *)buf,
                               (unsigned long *)&sz );
        if ( ret == ERROR_SUCCESS ) {
            BOOL    proxyEnable = FALSE;
            if ( type == REG_DWORD )
                proxyEnable = ((unsigned long *)buf) ? TRUE : FALSE;
            else if ( type == REG_BINARY )
                proxyEnable = buf[0] ? TRUE : FALSE;

            if ( proxyEnable ) {
                sz = BUFSIZ - 1;
                ret = RegQueryValueEx( hk,
                                       "ProxyServer",
                                       NULL,
                                       (unsigned long *)&type,
                                       (unsigned char *)buf,
                                       (unsigned long *)&sz );
                if ( ret == ERROR_SUCCESS ) {
                    if ( type == REG_SZ ) {
                        char    *q;

                        p = buf;
                        q = strchr( buf, ':' );
                        if ( q ) {
                            char    *r;
                            r = strchr( buf, '@' );
                            if ( r ) {
                                *r++ = NUL;
                                if ( r > q ) {
                                    *q++ = NUL;
                                    if ( proxyUserName )
                                        strcpy( proxyUserName, p );
                                    if ( proxyPassword )
                                        strcpy( proxyPassword, q );

                                    q = strchr( r, ':' );
                                }
                                else {
                                    if ( proxyUserName )
                                        strcpy( proxyUserName, p );
                                }

                                p = r;
                            }

                            if ( q )
                                *q = NUL;
                            strcpy( proxyServer, p );
                            if ( q )
                                *proxyPort =
                                    (unsigned short)(atol( q + 1 ) & 0xFFFF);
                            if ( (*proxyPort > 0)        &&
                                 (proxyServer[0] != NUL)    ) {
                                if ( xmlrpc_p->verbose )
                                    if ( isatty( fileno( stderr ) ) )
                                        fprintf( stderr, "\tproxy = %s:%d\n",
                                                 proxyServer, *proxyPort );
                                *useProxy = TRUE;
                            }
                        }
                    }
                }
            }
        }
        RegCloseKey( hk );
    }

    return ( isInternetExplorerActive );
}

static BOOL
getProxyInfoViaFirefox(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword
    )
{
    /*
     *  Firefox の設定を調べる
     */

    /* 手順                                                              */
    /*  (1) レジストリ                                                   */
    /*        HKEY_CURRENT_USER\Software\Mozilla\Mozilla Firefox         */
    /*      が存在すれば、Firefox インストール済み                       */
    /*  (2) 環境変数 USERPROFILE の指すディレクトリ以下のファイルを探索  */
    /*  (3) Application Data/Mozilla/Firefox/profiles.ini というファイル */
    /*      から                                                         */
    /*        Path=Profiles/*.default                                    */
    /*      という行を取得する (* 部分は環境によって変わる)              */
    /*  (4) Application Data/Mozilla/Firefox/Profiles/*.default/prefs.js */
    /*      (ただし、設定ファイルを置く場所を(Profiles/*.default以外の)  */
    /*       別のところに変更している場合も考慮して Path  の示すディレク */
    /*      トリ直下から prefs.js を探した方がいい)                      */
    /*      というファイルの中に                                         */
    /*        user_pref("network.proxy.http", "proxyサーバ名");          */
    /*        user_pref("network.proxy.http_port", ポート番号);          */
    /*      という記述があれば、proxy を使用する                         */
    /* 注意: 用途に合わせて profile を複数用意し使い分けているような場合 */
    /*       は、この手順で proxy の設定を取得できるとは限らない         */

#if 0
    long    ret;
    HKEY    hk;
    long    type;
    long    sz = BUFSIZ - 1;
#endif
    char    buf[BUFSIZ];
    BOOL    isFirefoxActive = FALSE;

#if 0
    ret = RegOpenKeyEx( HKEY_CURRENT_USER,
                        "Software\\Mozilla\\Mozilla Firefox",
                        0,
                        KEY_READ,
                        &hk );
    if ( ret == ERROR_SUCCESS ) {
        // Firefox 2.x では、このレジストリを使用しなくなった
        // (Firefox 1.x のときのみ有効)
        ret = RegQueryValueEx( hk,
                               "CurrentVersion",
                               NULL,
                               (unsigned long *)&type,
                               (unsigned char *)buf,
                               (unsigned long *)&sz );
        if ( ret == ERROR_SUCCESS ) {
            /* Firefox インストール済みであると判断 */
            isFirefoxActive = TRUE;
        }
        RegCloseKey( hk );
    }

    if ( isFirefoxActive == TRUE ) {
#endif
        char    *p = getenv("USERPROFILE");

        if ( p && *p ) {
            char    targetDir[MAX_PATH];
            char    filename[MAX_PATH];
            char    path[MAX_PATH];
            FILE    *fp;
            BOOL    isRelative = TRUE;

            sprintf( targetDir,
                     "%s\\Application Data\\Mozilla\\Firefox\\", p );
            sprintf( filename, "%sprofiles.ini", targetDir );
            path[0] = NUL;

            if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
                char    *p;

                isFirefoxActive = TRUE;
                while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
                    if ( !strncmp( p, "IsRelative=", 11 ) ) {
                        p += 11;
                        isRelative = (atol( p ) == 0) ? FALSE : TRUE;
                        continue;
                    }
                    if ( !strncmp( p, "Path=", 5 ) ) {
                        p += 5;
                        strcpy( path, p );
                        while ( (path[strlen(p) - 1] == '\n') ||
                                (path[strlen(p) - 1] == '\r') ||
                                (path[strlen(p) - 1] == ' ' ) ||
                                (path[strlen(p) - 1] == '/' ) ||
                                (path[strlen(p) - 1] == '\\')    )
                            path[strlen(p) - 1] = NUL;
                        break;
                    }
                }
                fclose( fp );

                if ( path[0] ) {
                    if ( isRelative )
                        sprintf( filename, "%s%s\\prefs.js",
                                 targetDir, path );
                    else
                        sprintf( filename, "%s\\prefs.js", path );

                    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
                        BOOL    enableProxy = FALSE;

                        while ( (p = fgets( buf, BUFSIZ - 1, fp )) != NULL ) {
                            if ( !strncmp( p,
                                           "user_pref(\"network.proxy.http\"",
                                           30 ) ) {
                                char    *q;

                                p += 30;
                                q = strchr( p, '"' );
                                if ( q ) {
                                    q++;
                                    p = strchr( q, '"' );
                                    if ( p ) {
                                        char    *r;

                                        *p = NUL;

                                        r = strchr( q, '@' );
                                        if ( r ) {
                                            char    *s;

                                            *r++ = NUL;
                                            s = strchr( q, ':' );
                                            if ( s ) {
                                                *s++ = NUL;
                                                if ( proxyUserName )
                                                    strcpy(proxyUserName, q);
                                                if ( proxyPassword )
                                                    strcpy(proxyPassword, s);
                                            }
                                            else {
                                                if ( proxyUserName )
                                                    strcpy(proxyUserName, q);
                                            }

                                            q = r;
                                        }

                                        strcpy( proxyServer, q );
                                        enableProxy = TRUE;
                                        *proxyPort  = DEFAULT_HTTP_PORT;
                                            /* とりあえず、デフォルト値を */
                                            /* 入れておく                 */
                                    }
                                }
                            }
                            else if ( !strncmp( p,
                                      "user_pref(\"network.proxy.http_port\"",
                                                35 ) ) {
                                p += 35;
                                while ( *p && ((*p < '0') || (*p > '9')) )
                                    p++;
                                if ( *p ) {
                                    *proxyPort =
                                        (unsigned short)(atol( p ) & 0xFFFF);
                                    enableProxy = TRUE;
                                }
                            }
                            else if ( !strncmp( p,
                                      "user_pref(\"network.proxy.type\"",
                                                30 ) ) {
                                int type = 0;
                                p += 30;
                                while ( *p && ((*p < '0') || (*p > '9')) )
                                    p++;
                                if ( *p ) {
                                    type = atol( p );
                                            /* 1: 手動でプロキシを設定する */
                                            /* 2: 自動プロキシ設定スクリプ */
                                            /*    トURL                    */
                                            /* 4: このネットワークのプロキ */
                                            /*    シ設定を自動検出する     */
                                }
                                if ( enableProxy || (type >= 1) ) {
                                    *useProxy = TRUE;
                                    if ( type != 1 )                /* @@ */
                                        isFirefoxActive = FALSE;    /* @@ */
                                    break;
                                }
                            }
                        }
                        fclose( fp );
                    }
                }
            }
        }
#if 0
    }
#endif

    return ( isFirefoxActive );
}


static BOOL
readProxySettingFromOperaIni(
        const char     *filename,
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword 
    )
{
    BOOL    found = FALSE;
    char    buf[BUFSIZ];
    char    *p;
    FILE    *fp;

    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            if ( !strncmpi( p, "HTTP Server=",  12 ) ||
                 !strncmpi( p, "HTTPS Server=", 13 )    ) {
                    /* Opera 8 までは Server,                     */
                    /* Opera 9 は     server [s が小文字になった] */
                char    *q;
                char    *r;

                found = TRUE;
                p = strchr( p + 11, '=' ) + 1;
                q = strchr( p, ':' );
                r = strchr( p, '@' );
                if ( r ) {
                    if ( q && (q < r) ) {
                        *q++ = NUL;
                        if ( proxyUserName )
                            strcpy( proxyUserName, p );
                        *r = NUL;
                        if ( proxyPassword )
                            strcpy( proxyPassword, q );
                    }
                    else {
                        *r = NUL;
                        if ( proxyUserName )
                            strcpy( proxyUserName, p );
                    }

                    p = r + 1;
                    q = strchr( p, ':' );
                }

                if ( !q ) {
                    q = p + (strlen(p) - 1);
                    while ( (q > p) && (*q == '\n') || (*q == '\r') )
                        *q-- = NUL;
                    strcpy( proxyServer, p );
                    *proxyPort = DEFAULT_HTTP_PORT;
                                        /* とりあえず、デフォルト値を */
                                        /* 入れておく                 */
                }
                else {
                    *q++ = NUL;
                    strcpy( proxyServer, p );
                    *proxyPort = (unsigned short)(atol( q ) & 0xFFFF);
                }
                *useProxy = TRUE;

                break;
            }
        }
        fclose( fp );
    }

    return ( found );
}

static BOOL
getProxyInfoViaOpera(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword
    )
{
    /*
     *  Opera の設定を調べる
     */

    /* 手順                                                               */
    /*  (1) レジストリ                                                    */
    /*        HKEY_CURRENT_USER\Software\Opera Software                   */
    /*      が存在すれば、Opera インストール済み                          */
    /*  (2) 上記レジストリから キー                                       */
    /*        Last Directory2                                             */
    /*      の値を取得 (Last Directory2 の値が取れなかった場合は          */
    /*      Last Directory3 の値を取得)                                   */
    /*  (3) Last Directory2 も Last Directory3 も取れなかった場合は       */
    /*        Plugin Path                                                 */
    /*      の値を取得                                                    */
    /*  (4) 上記 (2) または (3) で得た情報から Opera のインストール先ディ */
    /*      レクトリがどこか判断                                          */
    /*  (5) Opera のインストール先ディレクトリにある OperaDef6.ini という */
    /*      ファイルの中に                                                */
    /*         HTTP Server=proxyサーバ名:ポート番号                       */
    /*      という記述があれば、proxy を使用する (Opera 6 ～ 8)           */
    /*  (6) 環境変数 USERPROFILE の指すディレクトリ以下の                 */
    /*      Application Data/Opera/Opera/profile/opera6.ini というファイ  */
    /*      ルの中に                                                      */
    /*         HTTP server=proxyサーバ名:ポート番号                       */
    /*      という記述があれば、proxy を使用する (Opera 9)                */

    long    ret;
    HKEY    hk;
    long    type;
    long    sz = BUFSIZ - 1;
    char    buf[BUFSIZ];
    char    *p;
    BOOL    isOperaActive = FALSE;

    ret = RegOpenKeyEx( HKEY_CURRENT_USER,
                        "Software\\Opera Software",
                        0,
                        KEY_READ,
                        &hk );
    if ( ret == ERROR_SUCCESS ) {
        ret = RegQueryValueEx( hk,
                               "Last Directory2",
                               NULL,
                               (unsigned long *)&type,
                               (unsigned char *)buf,
                               (unsigned long *)&sz );
        if ( ret != ERROR_SUCCESS )
            ret = RegQueryValueEx( hk,
                                   "Last Directory3",
                                   NULL,
                                   (unsigned long *)&type,
                                   (unsigned char *)buf,
                                   (unsigned long *)&sz );
                        // ↑↑↑ 通常はこれが hit する (Opera 6 以降) ↑↑↑
        if ( ret != ERROR_SUCCESS ) {
            ret = RegQueryValueEx( hk,
                                   "Plugin Path",
                                   NULL,
                                   (unsigned long *)&type,
                                   (unsigned char *)buf,
                                   (unsigned long *)&sz );
            if ( ret == ERROR_SUCCESS ) {
                p = strstr( buf, "\\\\Program\\\\Plugins" );
                if ( p && *p )
                    *p = NUL;
            }
        }
        if ( ret != ERROR_SUCCESS ) {
            // for Opera 9
            ret = RegQueryValueEx( hk,
                                   "Last CommandLine v2",
                                   NULL,
                                   (unsigned long *)&type,
                                   (unsigned char *)buf,
                                   (unsigned long *)&sz );
            if ( ret == ERROR_SUCCESS ) {
                p = strstr( buf, "\\\\Opera.exe" );
                if ( p && *p )
                    *p = NUL;
            }
        }
        if ( ret == ERROR_SUCCESS ) {
            /* Opera インストール済みであると判断 */
            isOperaActive = TRUE;
        }
        RegCloseKey( hk );
    }

    if ( isOperaActive == TRUE ) {
        BOOL    found = FALSE;
        char    filename[MAX_PATH];

        sprintf( filename, "%s\\OperaDef6.ini", buf );

        found = readProxySettingFromOperaIni( filename,
                                              useProxy,
                                              proxyServer, proxyPort,
                                              proxyUserName, proxyPassword );
        if ( found == FALSE ) {
            // for Opera 9
            char    *p = getenv("USERPROFILE");

            if ( p && *p ) {
                char    targetDir[MAX_PATH];

                sprintf( targetDir,
                         "%s\\Application Data\\Opera\\Opera\\profile\\", p );
                sprintf( filename, "%sopera6.ini", targetDir );
                found = readProxySettingFromOperaIni(
                                                filename,
                                                useProxy,
                                                proxyServer, proxyPort,
                                                proxyUserName, proxyPassword);
            }
        }
    }

    return ( isOperaActive );
}

void
confirmProxyInfo(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword )
{
    LCID    l = getLanguageCode();

    SetLastError( ERROR_SUCCESS );
    if ( isatty( fileno( stdin ) ) && isatty( fileno( stderr ) ) ) {
        int     yesNo;
        FILE    *fp;

        inputYesNo( &yesNo,
                    l == 0x0411
                        ? "インターネットへの接続に proxy サーバを"
                          "利用していますか?"
                        : "Do you access the Internet via a proxy "
                          "server ?" );
        if ( yesNo == TRUE ) {
            char    *p, *q;
            char    buf1[BUFSIZ];
            char    buf2[BUFSIZ];
            char    buf3[BUFSIZ];
            char    buf4[BUFSIZ];

            inputString( buf1,
                         l == 0x0411
                            ? "proxyサーバのURL(またはIPアドレス): "
                            : "proxy server's URL (or IP address): ",
                            FALSE );
            inputString( buf2,
                         l == 0x0411
                            ? "proxyサーバのポート番号: "
                            : "proxy port number: ",
                            FALSE );

            buf3[0] = NUL;
            buf4[0] = NUL;
            inputYesNo( &yesNo,
                        l == 0x0411
                            ? "その proxy サーバを利用するのにユーザ名が"
                              "必要ですか?"
                            : "Do you use this proxy server with "
                              "username ?" );
            if ( yesNo == TRUE ) {
                inputString( buf3,
                             l == 0x0411
                                ? "proxyサーバのユーザ名: "
                                : "proxy username: ",
                                FALSE );

                inputYesNo( &yesNo,
                            l == 0x0411
                                ? "その proxy サーバを利用するのに"
                                  "パスワードが必要ですか?"
                                : "Do you use this proxy server with "
                                  "password ?" );
                if ( yesNo == TRUE ) {
                    inputString( buf4,
                                 l == 0x0411
                                    ? "proxyサーバのパスワード: "
                                    : "proxy password: ",
                                    TRUE );
                }
            }

            if ( ( fp = fopen( "proxy.txt", "w" ) ) != NULL ) {
                p = buf1;
                while ( (*p == ' ') || (*p == '\t') )
                    p++;
                if ( *p                                     &&
                     (((q = strchr( p, '.' )) != NULL) ||
                      (*p < '0') || (*p > '9')            )    ) {
                    strcpy( proxyServer, p );
                    fprintf( fp, "%s\n", proxyServer );
                }

                p = buf2;
                while ( (*p == ' ') || (*p == '\t') )
                    p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *proxyPort = (unsigned short)((atol( p ) & 0xFFFF));
                    fprintf( fp, "%d\n", *proxyPort );

                    if ( buf3[0] ) {
                        fprintf( fp, "%s\n", buf3 );
                        if ( proxyUserName )
                            strcpy( proxyUserName, buf3 );
                        if ( buf4[0] ) {
                            fprintf( fp, "%s\n", buf4 );
                            if ( proxyPassword )
                                strcpy( proxyPassword, buf4 );
                        }
                    }
                }

                fclose( fp );

                if ( (*proxyPort > 0) && (proxyServer[0] != NUL) ) {
                    if ( xmlrpc_p->verbose && isatty( fileno( stderr ) ) )
                        fprintf( stderr, "\tproxy = %s:%d\n",
                                 proxyServer, *proxyPort );
                    *useProxy = TRUE;
                }
            }
        }
    }
    else {
        int ret = MessageBox( NULL,
                              l == 0x0411
                                ? "proxyサーバ経由でインターネットを"
                                  "利用していますか?"
                                : "Do you access the Internet via a "
                                  "proxy server ?",
                              l == 0x0411
                                ? "インターネット利用形態確認"
                                : "Confirmation of proxy server",
                            MB_YESNO|MB_ICONQUESTION );
        if ( ret == IDYES ) {
            MessageBox( NULL,
                        l == 0x0411
                          ?
    "お手数をおかけしますが、proxyサーバの情報を書いたファイルを用意して"
    "ください。\n\n"
    "    ファイル名: proxy.txt\n"
    "    ファイルの中身: \n"
    "      以下の2行からなるテキストファイル\n"
    "         proxy サーバ名(または IPアドレス)\n"
    "         ポート番号\n\n"
    "      または、以下の4行からなるテキストファイル\n"
    "         proxy サーバ名(または IPアドレス)\n"
    "         ポート番号\n"
    "         proxy サーバにアクセスするためのユーザ名\n"
    "         proxy サーバにアクセスするためのパスワード\n\n"
    "上記のファイルをアプリケーション(*.exe)のあるフォルダに置いてくださ"
    "い。\n\n\n"
    "ファイルの用意が終わりましたら、OK ボタンを押してください。"
                                  :
    "Make an information file for proxy server.\n\n"
    "    Filename: proxy.txt\n"
    "    Contents of file: \n"
    "      Text file that consists of the following two lines\n"
    "        proxy server's URL (or IP address)\n"
    "        proxy port number\n\n"
    "      Or, Text file that consists of the following four lines\n"
    "        proxy server's URL (or IP address)\n"
    "        proxy port number\n"
    "        username for proxy server\n"
    "        password for proxy server\n\n"
    "Put this file on the folder with the application (that is *.exe).\n\n\n"
    "When you make and put this file, and push the OK button." ,
                        l == 0x0411
                          ? "設定ファイル作成要請"
                          : "Make information file for proxy server",
                        MB_OK|MB_ICONQUESTION );

            getProxyInfo( useProxy, proxyServer, proxyPort,
                          proxyUserName, proxyPassword );
        }
        else
            *useProxy = FALSE;

        SetLastError( XMLRPC_ERROR_CHANGED_PROXYINFO );
    }
}

void
getProxyInfo(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword
    )
{
    FILE        *fp;
    BOOL        isActive = FALSE;
    char        filename[MAX_PATH];
    struct stat s;

    if ( !useProxy || !proxyServer || !proxyPort )
        return;

    if ( stat( "./noproxy.txt", &s ) == 0 ) {
        *useProxy = FALSE;
        return;
    }

#ifdef  WIN32
    if ( __argv && __argv[0] && __argv[0][0] ) {
        char    *p;

        strcpy( filename, __argv[0] );
        p = strrchr( filename, '\\' );
        if ( p )
            *p = NUL;
        else {
            p = strrchr( filename, '/' );
            if ( p )
                *p = NUL;
            else
                strcpy( filename, "." );
        }
        strcat( filename, "/proxy.txt" );
    }
    else
        strcpy( filename, "./proxy.txt" );
#else
    strcpy( filename, "./proxy.txt" );
#endif
    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        char    *p, *q;
        char    buf[BUFSIZ];
        int     lineCnt     = 0;
        BOOL    useUserName = FALSE;

        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            if ( p[strlen(p) - 1] == '\n' )
                p[strlen(p) - 1] = NUL;
            if ( ((q = strchr( p, '.' )) != NULL) ||
                 (*p < '0') || (*p > '9') ) {
                if ( lineCnt == 0 )
                    strcpy( proxyServer, p );
                else if ( useUserName == FALSE ) {
                    if ( proxyUserName )
                        strcpy( proxyUserName, p );
                    useUserName = TRUE;
                }
                else if ( useUserName == TRUE ) {
                    if ( proxyPassword )
                        strcpy( proxyPassword, p );
                    break;  /* 残りの行は読まない */
                }
                lineCnt++;
            }
            else if ( (*p >= '0') && (*p <= '9') ) {
                *proxyPort = (unsigned short)((atol( p ) & 0xFFFF));
                lineCnt++;
            }
        }
        fclose( fp );

        if ( (*proxyPort > 0) && (proxyServer[0] != NUL) ) {
            if ( xmlrpc_p->verbose && isatty( fileno( stderr ) ) ) {
                if ( proxyUserName && *proxyUserName ) {
                    if ( proxyPassword && *proxyPassword )
                        fprintf( stderr, "\tproxy = %s:%s@%s:%d\n",
                                 proxyUserName, proxyPassword,
                                 proxyServer, *proxyPort );
                    else
                        fprintf( stderr, "\tproxy = %s@%s:%d\n",
                                 proxyUserName,
                                 proxyServer, *proxyPort );
                }
                else
                    fprintf( stderr, "\tproxy = %s:%d\n",
                             proxyServer, *proxyPort );
            }
            *useProxy = TRUE;
            isActive  = TRUE;
        }
    }

#ifdef  WIN32
    if ( *useProxy == FALSE ) {
        int     browser = getDefaultBrowser();

        switch ( browser ) {
        case BR_FIREFOX:
            isActive = getProxyInfoViaFirefox( useProxy,
                                               proxyServer, proxyPort,
                                               proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaInternetExplorer(
                                        useProxy, proxyServer, proxyPort,
                                        proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaOpera(useProxy,
                                                proxyServer, proxyPort,
                                                proxyUserName, proxyPassword);
            break;

        case BR_OPERA:
            isActive = getProxyInfoViaOpera( useProxy, proxyServer, proxyPort,
                                             proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaInternetExplorer(
                                        useProxy, proxyServer, proxyPort,
                                        proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaFirefox( useProxy,
                                               proxyServer, proxyPort,
                                               proxyUserName, proxyPassword );
            break;

        case BR_IEXPLORER:
        default:
            isActive = getProxyInfoViaInternetExplorer(
                                            useProxy, proxyServer, proxyPort,
                                            proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaFirefox( useProxy,
                                               proxyServer, proxyPort,
                                               proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaOpera( useProxy,
                                               proxyServer, proxyPort,
                                               proxyUserName, proxyPassword );
            break;
        }
    }
#endif  /* WIN32 */

    if ( isActive == FALSE ) {
        if ( xmlrpc_p->confirmProxyInfo ) {
            if ( xmlrpc_p->confirmProxyInfo != (CONF_FUNC)(-1) )
                isActive = xmlrpc_p->confirmProxyInfo(
                                        useProxy,
                                        proxyServer, proxyPort,
                                        proxyUserName, proxyPassword );
        }
        else
            confirmProxyInfo( useProxy,
                              proxyServer, proxyPort,
                              proxyUserName, proxyPassword );
    }
}

int
isUsedProxy()
{
    int             useProxy = FALSE;
    char            server[MAX_PATH];
    unsigned short  proxyPort = 0;
    char            proxyUserName[MAX_NAMELEN + 1];
    char            proxyPassword[MAX_NAMELEN + 1];

    server[0]        = NUL;
    proxyUserName[0] = NUL;
    proxyPassword[0] = NUL;
    getProxyInfo( &useProxy, server, &proxyPort,
                  proxyUserName, proxyPassword );

    return ( useProxy );
}

void    setConfirmProxyInfoFunc( CONF_FUNC confirmProxyInfo )
{
    if ( confirmProxyInfo )
        xmlrpc_p->confirmProxyInfo = confirmProxyInfo;
    else
        xmlrpc_p->confirmProxyInfo = NULL;
}

BOOL    isNecessaryToCheckProxyInfo()
{
    return ( xmlrpc_p->needToCheckProxyInfo );
}

void    setProxyInfo( const char *proxyServer, unsigned short proxyPort,
                      const char *proxyUsername, const char *proxyPassword )
{
    xmlrpc_p->proxyServer[0]   = NUL;
    xmlrpc_p->proxyPort        = 0;
    xmlrpc_p->proxyUserName[0] = NUL;
    xmlrpc_p->proxyPassword[0] = NUL;

    if ( proxyServer && *proxyServer ) {
        strcpy( xmlrpc_p->proxyServer, proxyServer );
        xmlrpc_p->proxyPort = proxyPort;
        if ( proxyUsername && *proxyUsername ) {
            strcpy( xmlrpc_p->proxyUserName, proxyUsername );
            if ( proxyPassword && *proxyPassword )
                strcpy( xmlrpc_p->proxyPassword, proxyPassword );
        }
    }
}

int
httpPostEx( char *request, char *response )
{
    int ret   = 0;
    int done  = FALSE;
    int count = 0;

    do {
        ret = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        NULL,
                        request, response );

        done = TRUE;
        if ( (ret == 0) || (response[0] != NUL) ) {
            char    *p = strstr( response, "<struct>" );
            if ( p ) {
                char    *q = strchr( p, 0xC3 );
                if ( q ) {
#ifndef _DEBUG
                    if ( xmlrpc_p->verbose )
#endif
                        if ( isatty( fileno( stderr ) ) )
                            fprintf( stderr, "文字化け検出!!\n" );
                    done = FALSE;
                }
            }
        }
        count++;
        if ( count > 16 )
            break;
    } while ( !done );

    return ( ret );
}


/*
 *  外部公開用 ユーティリティ関数
 */

/* verbose モード切替 */
void    setVerbose( int verbose, FILE *fp )
{
    if ( xmlrpc_p ) {
        xmlrpc_p->verbose = verbose;
        if ( verbose )
            xmlrpc_p->verboseFp = fp;
        else
            xmlrpc_p->verboseFp = stderr;
    }
}


/* dump モード切替 */
#if !defined (_DEBUG) && !defined (CHECK_DETAIL)
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
#endif
void    setDump( int dump, FILE *dumpFp )
{
#if defined (_DEBUG) || defined (CHECK_DETAIL)
    if ( xmlrpc_p ) {
        xmlrpc_p->dump = dump;
        if ( dump )
            xmlrpc_p->dumpFp = dumpFp;
        else
            xmlrpc_p->dumpFp = NULL;
    }
#endif
}
#if !defined (_DEBUG) && !defined (CHECK_DETAIL)
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif
#endif


/* proxy モード切替 */
void    setUseProxy( int useProxy )
{
    if ( xmlrpc_p )
        xmlrpc_p->useProxy = useProxy;
}


/* User-Agent 設定変更 */
void    setUserAgent( const char *userAgent )
{
    if ( xmlrpc_p ) {
        memset( xmlrpc_p->userAgent, NUL, MAX_LOGICALLINELEN );
        if ( userAgent && userAgent[0] )
            strncpy( xmlrpc_p->userAgent, userAgent, MAX_LOGICALLINELEN - 2 );
    }
}

/* Referer 設定変更 */
void    setReferer( const char *referer )
{
    if ( xmlrpc_p ) {
        memset( xmlrpc_p->referer, NUL, MAX_URLLENGTH_MAX );
        if ( referer && referer[0] )
            strncpy( xmlrpc_p->referer, referer, MAX_URLLENGTH_MAX - 2 );
    }
}

/* for OAuth */
#if !defined(USE_AUTHORIZATION_OAUTH)
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
#endif
void    setOAuthHeader( const char *header )
{
#ifdef  USE_AUTHORIZATION_OAUTH
    if ( xmlrpc_p ) {
        memset( xmlrpc_p->oauth_header, NUL, MAX_OAUTH_HEADER_LEN );
        if ( header && header[0] )
            strncpy( xmlrpc_p->oauth_header, header, MAX_OAUTH_HEADER_LEN - 2 );
    }
#endif
    return;
}
#if !defined(USE_AUTHORIZATION_OAUTH)
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif
#endif

/* ユーザ情報設定 */
void    setUserInfo( const char *userName, const char *password )
{
    if ( xmlrpc_p ) {
        strcpy( xmlrpc_p->userName, userName );
        strcpy( xmlrpc_p->password, password );
    }
}


/* webServer, webPage 設定 */
void    setTargetURL( const char *targetURL )
{
    const char  *p, *q;
    const char  *hStr = "http://";
    const char  *sStr = "https://";
    char        *url;
    int         len   = strlen( hStr );
    BLOGINFOTBL *pp;

    url = (char *)malloc( strlen(targetURL) + 16 );
    if ( !url )
        return;

    strcpy( url, targetURL );
    p = strstr( url, "://" );
    if ( p ) {
        p += 3;
        q = strchr( p, '/' );
        if ( !q )
            strcat( url, "/" );
    }

    p = url;
    xmlrpc_p->useSSL = FALSE;
    if ( !strncmp( p, hStr, len ) ) {
        p += len;
        xmlrpc_p->useSSL = FALSE;
    }
    else {
        len   = strlen( sStr );
        if ( !strncmp( p, sStr, len ) ) {
            p += len;
            xmlrpc_p->useSSL = TRUE;
        }
    }
    if ( ( q = strchr( p, '/' ) ) != NULL ) {
        strncpy( xmlrpc_p->webServer, p, q - p );
        xmlrpc_p->webServer[q - p] = NUL;
        strcpy( xmlrpc_p->webPage, q );
    }

    if ( xmlrpc_p->useProxy ) {
        if ( !(xmlrpc_p->proxyServer[0]) ) {
            xmlrpc_p->useProxy = FALSE;
            getProxyInfo( &xmlrpc_p->useProxy,
                          xmlrpc_p->proxyServer,
                          &xmlrpc_p->proxyPort,
                          xmlrpc_p->proxyUserName,
                          xmlrpc_p->proxyPassword );
            if ( xmlrpc_p->useProxy == FALSE )
                if ( isatty( fileno( stderr ) ) )
                    fprintf( stderr, "\tNot specified proxy server\n" );
        }
    }

    for ( pp = &(blogInfoTbl[0]); pp->blogType != -1; pp++ ) {
        if ( pp->xmlEndpoint && *(pp->xmlEndpoint) &&
             !strcmp( targetURL, pp->xmlEndpoint ) ) {
            xmlrpc_p->blogKind = pp->blogType;
            break;
        }
        if ( pp->atomEndpoint && *(pp->atomEndpoint) ) {
            if ( !strcmp( targetURL, pp->atomEndpoint ) ) {
                xmlrpc_p->blogKind = pp->blogType;
                break;
            }
            
            p = strchr( pp->atomEndpoint, '{' );
            if ( p ) {
                size_t  len = p - pp->atomEndpoint;
                if ( !strncmp( targetURL, pp->atomEndpoint, len ) ) {
                    xmlrpc_p->blogKind = pp->blogType;
                    break;
                }
            }
        }
    }

    free( url );
}


/* blog 種別設定 */
void    setBlogKind( int blogKind )
{
    if ( xmlrpc_p )
        xmlrpc_p->blogKind = blogKind;
}


/* データファイル格納先ディレクトリ名設定 */
void    setDataDir( const char *dirname )
{
    if ( xmlrpc_p ) {
        strcpy( xmlrpc_p->dataDir, dirname );
    }
}

/* はてなダイアリーキーワードリストファイル名設定 */
void    setKeywordList( const char *filename )
{
    if ( xmlrpc_p ) {
        strcpy( xmlrpc_p->keywordList, filename );
    }
}



/* base64 エンコーダ */
static char b[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  /* 0000000000111111111122222222223333333333444444444455555555556666 */
  /* 0123456789012345678901234567890123456789012345678901234567890123 */
char    *
base64( const unsigned char *src, size_t sz )
{
    unsigned char               *pp, *p, *q;
    Thread static unsigned char *qq = NULL;
    size_t                      i, safe = sz;

    if ( qq ) {
        free( qq );
        qq = NULL;
    }
    if ( !src || (sz == 0) )
        return ( NULL );

    if ( (sz % 3) == 1 ) {
        p = (unsigned char *)malloc( sz + 2 );
        if ( !p )
            return ( NULL );
        memcpy( p, src, sz );
        p[sz] = p[sz + 1] = '=';
        sz += 2;
    }
    else if ( (sz % 3) == 2 ) {
        p = (unsigned char *)malloc( sz + 1 );
        if ( !p )
            return ( NULL );
        memcpy( p, src, sz );
        p[sz] = '=';
        sz++;
    }
    else
        p = (unsigned char *)src;

    q = (unsigned char *)malloc( (sz / 3) * 4 + 2 );
    if ( !q ) {
        if ( p != src )
            free( p );
        return ( NULL );
    }

    pp = p;
    qq = q;
    for ( i = 0; i < sz; i += 3 ) {
        q[0] = b[(p[0] & 0xFC) >> 2];
        q[1] = b[((p[0] & 0x03) << 4) | ((p[1] & 0xF0) >> 4)];
        q[2] = b[((p[1] & 0x0F) << 2) | ((p[2] & 0xC0) >> 6)];
        q[3] = b[p[2] & 0x3F];
        p += 3;
        q += 4;
    }
    *q = NUL;
    if ( (safe % 3) == 1 ) {
        *(q - 1) = '=';
        *(q - 2) = '=';
    }
    if ( (safe % 3) == 2 )
        *(q - 1) = '=';

    if ( pp != src )
        free( pp );
    return ( (char *)qq );
}

/* base64デコーダ */
static int
code( int c )
{
    int ret = -1, i;

    for ( i = 0; i < 64; i++ ) {
        if ( c == b[i] ) {
            ret = i;
            break;
        }
    }

    return ( ret );
}

char   *
unbase64( const unsigned char *src, unsigned char *dst, size_t *sz )
{
    const char      *p;
    unsigned char   *q;
    int             i, j, k, l;

    if ( src && *src && dst ) {
        p = (char *)src;
        q = dst;

        while ( *p ) {
            i = code( *p++ );
            j = code( *p++ );
            k = code( *p++ );
            l = code( *p++ );

            *q++ = (unsigned char)(((i & 0x3F) << 2) | ((j & 0x30) >> 4));

            if ( k == -1 ) {
                *q++ = NUL;
                break;
            }
            else
                *q++ = (unsigned char)(((j & 0x0F) << 4) | ((k & 0x3C) >> 2));

            if ( l == -1 ) {
                *q++ = NUL;
                break;
            }
            else
                *q++ = (unsigned char)(((k & 0x03) << 6) | (l & 0x3F));
        }

        *q = NUL;
        if ( sz )
            *sz = q - dst;
    }

    return ( dst ? (char *)dst : (char *)src );
}


/*
 *  トラックバック送信
 *      blogName, articleURL, targetURL のみ必須
 */
int
sendTrackbackPing( const char *blogName,
                   const char *articleTitle,
                   const char *articleURL,
                   const char *articleExcerpt,
                   const char *targetURL )
{
    int     ret = -1;
    char    str[3][1024];
    char    request[2048];
    char    *response;
    char    *p, *q;
    size_t  sz;

    if ( !blogName     || !(*blogName)     ||
         !articleURL   || !(*articleURL)   ||
         !targetURL    || !(*targetURL)       )
        return ( ret );

    // 80バイト以下になるように切り詰める
    normalizeString( str[0], blogName, 80 );
    q = sjis2utf(str[0]);
    p = encodeURL( q ? q : str[0] );
    strcpy( str[0], p ); // blogName

    if ( articleTitle && *articleTitle ) {
        // 160バイト以下になるように切り詰める
        normalizeString( str[1], articleTitle, 160 );
        q = sjis2utf(str[1]);
        p = encodeURL( q ? q : str[1] );
        strcpy( str[1], p ); // articleTitle

        if ( articleExcerpt && *articleExcerpt ) {
            // 160バイト以下になるように切り詰める
            normalizeString( str[2], articleExcerpt, 160 );
            q = sjis2utf(str[2]);
            p = encodeURL( q ? q : str[2] );
            strcpy( str[2], p ); // articleExcerpt
	        sprintf( request,
                     "title=%s"
                     "&url=%s"
                     "&excerpt=%s"
                     "&blog_name=%s"
                     "&charset=UTF-8", // 注意: charset 指定は日本の blog 界
                                       //       (の一部)で提唱されたものであ
                                       //       る(文字コード絡みの問題を解決
                                       //       するため)
                                       //       したがって、どの blog もサポー
                                       //       トしているとは限らない(サポー
                                       //       トしていない場合は、charset引
                                       //       数は単に無視されるだけ)
                     str[1],    // articleTitle
                     articleURL,// articleURL
                     str[2],    // articleExcerpt
		             str[0] );  // blogName
        }
        else {
	        sprintf( request,
                     "title=%s"
                     "&url=%s"
                     "&blog_name=%s"
                     "&charset=UTF-8",
                     str[1],    // articleTitle
                     articleURL,// articleURL
		             str[0] );  // blogName
        }
    }
    else {
        if ( articleExcerpt && *articleExcerpt ) {
            // 160バイト以下になるように切り詰める
            normalizeString( str[1], articleExcerpt, 160 );
            q = sjis2utf(str[1]);
            p = encodeURL( q ? q : str[1] );
            strcpy( str[1], p ); // articleExcerpt
	        sprintf( request,
                     "url=%s"
                     "&excerpt=%s"
                     "&blog_name=%s"
                     "&charset=UTF-8",
                     articleURL,
                     str[1],    // articleExcerpt
		             str[0] );  // blogName
        }
        else {
	        sprintf( request,
                     "url=%s"
                     "&blog_name=%s"
                     "&charset=UTF-8",
                     articleURL,
		             str[0] );  // blogName
        }
    }

    sz = MAX_CONTENT_SIZE * 64;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    if ( xmlrpc_p ) {
        /* GET メソッドによるトラックバック送信は 2003年2月末 まで有効、そ */
        /* れ以降は POST メソッドのみ有効ということになっているが、実際に  */
        /* は、MovableType 2.6x 等、現在でも GET, POST のどちらでも受け付  */
        /* けるものが多い                                                  */
#ifdef  USE_HTTPGET_VERSION_TRACKBACK
        char    action[2048];

        sprintf( action, "%s?%s", targetURL, request );
        setTargetURL( action );
        setUpReceiveBuffer( response, sz );
        ret = httpGet( xmlrpc_p->webServer, xmlrpc_p->webPage,
                       response, stderr, 0 );
#else   /* USE_HTTPPOST_VERSION_TRACKBACK */
        setTargetURL( targetURL );
        setUpReceiveBuffer( response, sz );
        ret = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        "application/x-www-form-urlencoded",
                        request, response );
#endif  /* USE_HTTPPOST_VERSION_TRACKBACK */

        // response の中身を吟味して、トラックバック送信成功/失敗を判断
        if ( strstr( response, "<error>1</error>" ) )
            ret = -1;
    }

    /* 領域解放 */
    free( response );
    encodeURL( NULL );

    return ( ret ); // ret: 0 のとき正常終了、-1 のときエラー、-2 のとき通信
                    //      途中で回線切断検出(正常終了とみなす)
}

char    *
decodeEncyptedTrackbackURL( const char *encyptedTrackbackURL )
{
    /* 暗号化されているトラックバックURLを復号する (for 楽天広場) */
    Thread static char  trackbackURL[MAX_URLLENGTH];
    const char          *p = encyptedTrackbackURL;
    char                *q = trackbackURL;

    trackbackURL[0] = NUL;
    while ( *p )
        *q++ = (char)(*p++ ^ 0x04);
    *q = NUL;

    return ( trackbackURL );
}

/*
 *  指定記事のトラックバック送信用URLの取得
 *      (1) 原則として trackback Auto-discovery 機能を使って取得
 *      (2) ただし、trackback Auto-discovery 未対応なところでも、
 *          記事の URL を元に、一定の法則でトラックバック送信用
 *          URL を求めることができる場合は、その URL を返す
 */
char    *
getTrackbackURL( const char *articleURL )
{
    Thread static char  trackbackURL[MAX_URLLENGTH];
    char                jsURL[MAX_URLLENGTH];
    char                *response;
    const char          *p, *q;
    int                 ret;
    size_t              sz;

    memset( trackbackURL, NUL, MAX_URLLENGTH );

    /* 指定 Web ページを取得 */
    sz = MAX_CONTENT_SIZE * 64; /* 念のために大きめに確保 */
    response = (char *)malloc( sz );
    if ( !response )
        return ( NULL );

    setTargetURL( articleURL );
    setUpReceiveBuffer( response, sz );
    ret = httpGet( xmlrpc_p->webServer, xmlrpc_p->webPage,
                   response, NULL, FALSE,
                   NULL, NULL, NULL, NULL, NULL );
    if ( response[0] == NUL  ) {
        free( response );
        return ( NULL );
    }

    /* レントラを使用しているかどうかのチェック */
    jsURL[0] = NUL;
    if ( ( p = strstr( response,
                  "=\"http://rentra.zansin.jp/pl/gate.tb/" ) ) != NULL ) {

        // レントラを使っている場合
        p += 2;
        q = strstr( p, "\">" );
        if ( q ) {
            char    dummy[BUFSIZ];
            char    *r;
            int     l;

            r = strstr( p, "gate.tb/" );
            if ( !(((*(r + 8) >= '0') && (*(r + 8) <= '9')) ||
                   ((*(r + 8) >= 'A') && (*(r + 8) <= 'Z')) ||
                   ((*(r + 8) >= 'a') && (*(r + 8) <= 'z'))   ) ) {
                free( response );
                return ( NULL );
            }

            strncpy( jsURL, p, r - p );
            jsURL[r - p] = NUL;
            strcat( jsURL, "normal.tb/" );

            l = strlen( jsURL );
            r += 8;
            strncat( jsURL, r, q - r);
            jsURL[l + (q - r)] = NUL;

            sprintf( dummy, "Referer: %s\r\n", articleURL );
                /* -- Referer: の指定がないと警告メッセージが返ってくる */

            /* JavaScript を取得 */
            setTargetURL( jsURL );
            setUpReceiveBuffer( response, sz );
            ret = httpGet( xmlrpc_p->webServer, xmlrpc_p->webPage,
                           response, NULL, FALSE,
                           NULL, NULL, dummy, NULL, NULL );
            if ( response[0] == NUL  ) {
                free( response );
                return ( NULL );
            }

            p = strstr( response, "http://rentra.zansin.jp/pl/tb_show.cgi/" );
            if ( p ) {
                q = strchr( p, '\'' );
                if ( !q )
                    q = strchr( p, '"' );
                if ( q ) {
                    strncpy( jsURL, p, q - p );
                    jsURL[q - p] = NUL;
                }
            }
        }
    }

    /* trackback auto-discovery を試みる */
    /* (1) head 部分に df:Description がある場合 (MovableType など) */
    /* (2) body 部分に df:Description がある場合 (本来の trackback  */
    /*     auto-discovery)                                          */
    p = strstr( response, "rdf:Description" );
    if ( !p )
        p = strstr( response, "RDF:DESCRIPTION" );
    if ( p ) {
        p += 15;
        q = strstr( p, "trackback:ping=\"=\"" );
        if ( q )
            q += 2; // blog2.fc2.com のバグに対応
        else
            q = strstr( p, "trackback:ping=\"" );
        if ( q ) {
            p = q + 16;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( trackbackURL, p, q - p );
                trackbackURL[q - p] = NUL;
            }
        }
    }

    /* (3) その他、特定の blog/CMSツール 対応処理 */
    if ( trackbackURL[0] == NUL ) {
        if ((p=strstr(response,"=\"http://www.haloscan.com/load/")) != NULL) {
            // HaloScan を使っている場合
            char    userID[MAX_URLLENGTH];
            char    tbID[32];

            p += strlen( "=\"http://www.haloscan.com/load/" );
            q = strchr( p, '"');
            if ( !q )
                q = strchr( p, '>' );
            if ( q ) {
                strncpy( userID, p, q - p );
                userID[q - p] = NUL;

                if ( ( p = strstr( q + 1, ":HaloScanTB(" ) ) != NULL ) {
                    p += strlen( ":HaloScanTB(" );
                    while ( *p && ((*p < '0') || (*p > '9')) )
                        p++;
                    if ( *p ) {
                        q = p + 1;
                        while ( (*q >= '0') && (*q <= '9') )
                            q++;
                        strncpy( tbID, p, q - p );
                        tbID[q - p] = NUL;

                        sprintf( trackbackURL,
                                 "http://www.haloscan.com/tb/%s/%s",
                                 userID, tbID );
                    }
                }
            }
        }
        else if ( !strncmp(articleURL, "http://plaza.rakuten.co.jp/", 27) ) {
            /* 楽天広場の場合 */
            p = strstr( response, "<span class=\"jscrypt\"" );
            if ( p ) {
                /* トラックバックURLが暗号化されている場合 (2006年5月29日以降) */
                p += 21;
                q = strstr( p, "title=\"" );
                if ( q ) {
                    p = q + 7;
                    q = strchr( p, '"' );
                    if ( q ) {
                        char    encryptedTbID[80];
                        strncpy( encryptedTbID, p, q - p );
                        encryptedTbID[q - p] = NUL;
                        q = decodeString( encryptedTbID );
                        if ( q )
                            strcpy( encryptedTbID, q );
                        q = decodeEncyptedTrackbackURL( encryptedTbID );
                        if ( q )
                            strcpy( trackbackURL, q );
                    }
                }
            }
            else {
                /* 従来の楽天広場の場合 (2006年5月29日以前) */
                p = strstr( response, "&tbUrl=http://tb.plaza.rakuten.co.jp/" );
                q = NULL;
                if ( p ) {
                    p += 7;
                    q = strchr( p, '"' );
                }
                else {
                    p = strstr( response, "http://tb.plaza.rakuten.co.jp/" );
                    if ( p ) {
                        q = strchr( p, '\n' );
                        if ( !q )
                            q = strchr( p, '\r' );
                        if ( !q )
                            q = strchr( p, ' ' );
                    }
                }
                if ( p && q ) {
                    strncpy( trackbackURL, p, q - p );
                    trackbackURL[q - p] = NUL;
                }
                if ( trackbackURL[0] == NUL )  {
                    sprintf( trackbackURL, "http://tb.plaza.rakuten.co.jp/%s",
                             articleURL + 27 );
                }
            }
        }
        else if ( !strncmp( articleURL, "http://blog.melma.com", 21 ) ||
                  ( strstr( articleURL, "ap.teacup.com/" ) != NULL )     ) {
            /* melma! blog または AutoPage の場合 */
            if ( ( p = strchr( articleURL, '#' ) ) != NULL ) {
                strncpy( trackbackURL, articleURL, p - articleURL );
                trackbackURL[p - articleURL] = NUL;
            }
            else
                strcpy( trackbackURL, articleURL );

            /* AutoPage の場合 */
            if ( strstr( articleURL,"ap.teacup.com/" ) != NULL ) {
                if ( ( p = strstr( articleURL, ".html") ) != NULL ) {
                    strncpy( trackbackURL, articleURL, p - articleURL );
                    trackbackURL[p - articleURL] = NUL;
                }

                if ( !strstr( trackbackURL, "applet" ) ) {
                    char    temp[MAX_URLLENGTH];

                    p = strstr( trackbackURL, "teacup.com/" ) + 11;
                    strncpy( temp, trackbackURL, p - trackbackURL );
                    temp[p - trackbackURL] = NUL;
                    strcat( temp, "applet/" );
                    strcat( temp, p );
                    strcpy( trackbackURL, temp );
                }
            }

            /* 以下、melma! blog, AutoPage 共通処理 */
            if ( trackbackURL[strlen(trackbackURL) - 1] != '/' )
                strcat( trackbackURL, "/" );
            strcat( trackbackURL, "trackback" );
        }
        else if ( strstr( articleURL, "http://yaplog.jp/"      ) ||
                  strstr( articleURL, "http://blog.drecom.jp/" )    ) {
            // ヤプログ! または ドリコムブログ の場合
            //  例) http://yaplog.jp/cocousagi/archive/50
            //          → http://yaplog.jp/cocousagi/tb_ping/50
            char    temp[MAX_URLLENGTH];

            p = strstr( articleURL, "archive/" );
            q = strrchr( articleURL, '/' );
            if ( p && q ) {
                strncpy( temp, articleURL, p - articleURL );
                temp[p - articleURL] = NUL;
                strcat( temp, "tb_ping" );
                strcat( temp, q );
                strcpy( trackbackURL, temp );
            }
        }
        else if (strstr(articleURL,"http://carlife.carview.co.jp/User.asp")) {
            // みんカラの場合
            //  例) http://carlife.carview.co.jp/User.asp?UserDiaryID=78139
            //          → http://feed.carview.co.jp/tb.aspx?t=blog&i=78139
            p = strrchr( articleURL, '=' );
            if ( p ) {
                p++;
                sprintf( trackbackURL,
                         "http://feed.carview.co.jp/tb.aspx?t=blog&i=%s", p );
            }
        }
        else if ( !strncmp( articleURL, "http://www.mypress.jp/", 22 ) &&
                  ( ( p = strstr( articleURL, "?story_id=" ) ) != NULL ) ) {
            // マイぷれす の場合
            //  例) http://www.mypress.jp/v2_writers/tenmonbu/story/?story_id=895426
            //          → http://www.mypress.jp/trackback/tb_popup.php?tb_id=895426
            p += 10;
            sprintf( trackbackURL,
                     "http://www.mypress.jp/trackback/tb_popup.php?tb_id=%s",
                     p );
        }
        else if ( !strncmp( articleURL, "http://blog.kansai.com/", 23 ) ) {
            // 関西どっとコム の場合
            //  例) http://blog.kansai.com/ukiyo/1
            //          → http://blog.kansai.com/tb/ukiyo/1
            p = articleURL;
            p += 23;
            sprintf( trackbackURL,
                     "http://blog.kansai.com/tb/%s", p );
        }
        else if ( !strncmp( articleURL, "http://blog.zaq.ne.jp/", 22 ) ) {
            // BLOGari の場合
            //  例) http://blog.zaq.ne.jp/unplugged/article/232/
            //         → http://blog.zaq.ne.jp/unplugged/trackback/232/ 
            char    temp[MAX_URLLENGTH];

            p = strstr( articleURL, "article/" );
            q = strrchr( articleURL, '/' );
            if ( p && q ) {
                strncpy( temp, articleURL, p - articleURL );
                temp[p - articleURL] = NUL;
                strcat( temp, "trackback" );
                strcat( temp, q );
                strcpy( trackbackURL, temp );
            }
        }
        else if ( !strncmp( articleURL, "http://blog.naver.co.jp/", 24 ) ) {
            // NAVERブログ の場合
            //  例) http://blog.naver.co.jp/yahoo__bb/50000981932
            //      http://blog.naver.co.jp/yahoo__bb.do?Redirect=Dlog&Qs=/yahoo__bb/50000981932
            //      http://blog.naver.co.jp/post/postView.jsp?blogId=yahoo__bb&logNo=50000981932
            //         → http://blog.naver.co.jp/tb/yahoo__bb/50000981932
            char    *r, *s;
            char    userName[MAX_URLLENGTH];

            userName[0] = NUL;
            p = articleURL;
            p += 24;
            q = p + strlen( p );
            while ( (*(q - 1) >= '0') && (*(q - 1) <= '9') )
                q--;
            if ( !strncmp( p, "post/", 5 ) ) {
                p += 5;
                r = strstr( p, "blogId=" );
                if ( r ) {
                    r += 7;
                    s = strchr( r, '&' );
                    if ( !s )
                        s = r + strlen( r );
                    strncpy( userName, r, s - r );
                    userName[s - r] = NUL;
                }
            }
            else {
                r = strstr( p, ".do?" );
                if ( !r )
                    r = strchr( p, '/' );
                if ( r ) {
                    strncpy( userName, p, r - p );
                    userName[r - p] = NUL;
                }
            }

            if ( userName[0] && (q > p) )
                sprintf( trackbackURL,
                         "http://blog.naver.co.jp/tb/%s/%s",
                         userName, q );
        }
        else if ( !strncmp( articleURL,
                            "http://spaces.msn.com/members/", 30 ) ) {
            // msn Spaces の場合
            //  例) http://spaces.msn.com/members/kazumao/Blog/cns!1pmDEFJ6LYrvL9rl0_HcQKfw!210.entry
            //         → http://spaces.msn.com/members/kazumao/blog/cns!1pmDEFJ6LYrvL9rl0_HcQKfw!210.trak
            //           (http://spaces.msn.com/members/kazumao/Blog/cns!1pmDEFJ6LYrvL9rl0_HcQKfw!210.trak)
            if ( ( p = strstr( articleURL, ".entry" ) ) != NULL ) {
                strcpy( trackbackURL, articleURL );
                strcpy( trackbackURL + (p - articleURL), ".trak" );
            }
        }
        else if ( jsURL[0] ||
                  strstr( articleURL,
                          "http://rentra.zansin.jp/pl/tb_show.cgi/" ) ) {
            // レントラの場合
            if ( jsURL[0] == NUL )
                strcpy( jsURL, articleURL );
            p = strstr( jsURL, "tb_show.cgi/" );
            if ( p ) {
                q = p + 12;
                strncpy( trackbackURL, jsURL, p - jsURL );
                trackbackURL[p - jsURL] = NUL;
                strcat( trackbackURL, "get.tb/" );
                strcat( trackbackURL, q );
            }
        }
        else {
            // それ以外
            // “id="trackback"”なタグ近辺からそれっぽい URL を拾い出す
            if ( ((p = strstr(response, "id=\"trackback\""  )) != NULL) ||
                 ((p = strstr(response, "name=\"trackback\"")) != NULL)    ) {
                if ( ( q = strstr( p + 14, "http://" ) ) != NULL ) {
                    if ( ( ( p = strchr( q, '"' ) ) != NULL ) ||
                         ( ( p = strchr( q, ' ' ) ) != NULL ) ||
                         ( ( p = strchr( q, '>' ) ) != NULL ) ||
                         ( ( p = strchr( q, '<' ) ) != NULL )    ) {
                        char    *r = strchr( q + 7, '/' );
                        if ( r && !strncmp( q, articleURL, r - q ) ) {
                            strncpy( trackbackURL, q, p - q );
                            trackbackURL[p - q] = NUL;
                            if ( ( r = strchr( trackbackURL, '<' ) ) != NULL )
                                *r = NUL;
                            if ( ( r = strchr( trackbackURL, '>' ) ) != NULL )
                                *r = NUL;
                            if ( ( r = strchr( trackbackURL, ' ' ) ) != NULL )
                                *r = NUL;
                            if ( ( r = strchr( trackbackURL, '"' ) ) != NULL )
                                *r = NUL;
                        }
                    }
                }
            }

            if ( trackbackURL[0] == NUL ) {
                // trackback.php とか trackback.cgi とかを拾ってみる
                //   (Nucleus はこの方法で対応できる)
                if ( !p )
                    p = response;
                q = strstr( p, "trackback.php?" );
                if ( !q )
                    q = strstr( p, "trackback.cgi?" );
                if ( !q )
                    q = strstr( p, "trackback.pl?" );
                if ( !q )
                    q = strstr( p, "trackback.asp?" );
                if ( !q )
                    q = strstr( p, "trackback.jsp?" );
                if ( !q )
                    q = strstr( p, "action.php?" );
                if ( !q )
                    q = strstr( p, "/tt_tb.cgi/" ); /* teeter totter */
                if ( !q )
                    q = strstr( p, "/tb.php/" );    /* XOOPS */

                if ( q ) {
                    p = q;
                    while ( (p > response) &&
                            (*p != '"')    &&
                            (*p != '\'')   &&
                            (*p != '>')    &&
                            (*p != '=')    &&
                            (*p != '\t')   &&
                            (*p != ' ')       )
                        p--;
                    while ( *q             &&
                            (*q != '"')    &&
                            (*q != '\'')   &&
                            (*q != '<')    &&
                            (*q != '\t')   &&
                            (*q != ' ')       )
                        q++;
                    if ( p && ((*p == '"')  ||
                               (*p == '\'') ||  
                               (*p == '>')  ||
                               (*p == '=')  ||
                               (*p == '\t') ||
                               (*p == ' ')    ) &&
                         q && ((*q == '"')  ||
                               (*q == '\'') ||
                               (*q == '<')  ||
                               (*q == '\t') ||
                               (*q == ' ')    )    ) {
                        p++;
                        strncpy( trackbackURL, p, q - p );
                        trackbackURL[p - q] = NUL;
                    }
                }
            }
        }
    }

    free( response );

    if ( trackbackURL[0] ) {
        char    *p, *q;

        /* ゴミ掃除 (主として JUGEM 対策)                                */
        /*  -- recvHTTP() 内の「ゴミ掃除」で掃除し切れなかったゴミの掃除 */
        while ( ( ( p = strchr( trackbackURL, '\r' ) ) != NULL ) ||
                ( ( p = strchr( trackbackURL, '\n' ) ) != NULL )    ) {
            if ( *p == '\r' ) {
                q = strchr( p + 1, '\r' );
                if ( *(p - 1) == '\n' )
                    p--;
            }
            else
                q = strchr( p + 1, '\n' );
            if ( q ) {
                if ( ( *(q + 1) == '\n' ) || ( *(q + 1) == '\r' ) )
                    q++;
                strcpy( p, q + 1 );
            }
            else
                strcpy( p, p + 1 );
        }

        /* "&amp;" → "&" の置換 */
        while ( ( p = strstr( trackbackURL, "&amp;" ) ) != NULL )
            strcpy( p + 1, p + 5 );

        /* トラックバックURLの正規化 */
        if ( trackbackURL[0] == '/' ) {
            char    temp[MAX_URLLENGTH];

            if ( ((p = strchr( articleURL, '~' ))   != NULL) ||
                 ((p = strstr( articleURL, "%7E" )) != NULL) ||
                 ((p = strstr( articleURL, "%7e" )) != NULL)    ) {
                p = strchr( p + 1, '/' );
            }
            else {
                p = strstr( articleURL, "://" );
                if ( p )
                    p = strchr( p + 3, '/' );
            }

            /* 相対パス → 絶対パス */
            if ( p ) {
                strncpy( temp, articleURL, p - articleURL );
                temp[p - articleURL] = NUL;
                strcat( temp, trackbackURL );
                strcpy( trackbackURL, temp );
            }
        }
    }

    return ( trackbackURL );
}


/*
 * 実体参照のデコード
 */

char    *
decodeString( char *src )
{
    char    *p = src, *q;

    while ( ( q = strstr( p, "&lt;" ) ) != NULL ) {
        *q = '<';
        strcpy( q + 1, q + 4 );
    }
    while ( ( q = strstr( p, "&gt;" ) ) != NULL ) {
        *q = '>';
        strcpy( q + 1, q + 4 );
    }
    while ( ( q = strstr( p, "&quot;" ) ) != NULL ) {
        *q = '"';
        strcpy( q + 1, q + 6 );
    }
    while ( ( q = strstr( p, "&amp;" ) ) != NULL ) {
        *q = '&';
        strcpy( q + 1, q + 5 );
    }

    while ( ( q = strstr( p, "&dquot;" ) ) != NULL ) {
        *q = '"';
        strcpy( q + 1, q + 7 );
    }

    return ( src );
}


/*
 * 実体参照へのエンコード
 */

char    *
encodeString( const char *src, char *dst )
{
    const char  *p = src;
    char        *q = dst;

    while ( *p ) {
        if ( *p == '<' ) {
            *q++ = '&';
            *q++ = 'l';
            *q++ = 't';
            *q++ = ';';
        }
        else if ( *p == '>' ) {
            *q++ = '&';
            *q++ = 'g';
            *q++ = 't';
            *q++ = ';';
        }
        else if ( *p == '"' ) {
            *q++ = '&';
            *q++ = 'q';
            *q++ = 'u';
            *q++ = 'o';
            *q++ = 't';
            *q++ = ';';
        }
        else if ( *p == '&' ) {
            *q++ = '&';
            *q++ = 'a';
            *q++ = 'm';
            *q++ = 'p';
            *q++ = ';';
        }
        else
            *q++ = *p;

        p++;
    }
    *q = NUL;

    return ( dst );
}


/* 指定文字列は16進文字列か否か */
int
isHexString( const char *p )
{
    int ret = 1;

    while ( *p ) {
        if ( ((*p >= '0') && (*p <= '9')) ||
             ((*p >= 'a') && (*p <= 'f')) ||
             ((*p >= 'A') && (*p <= 'F'))    ) {
            p++;
            continue;
        }

        ret = 0;
        break;
    }

    return ( ret );
}

/* 指定文字列は10進文字列か否か */
int
isDecString( const char *p )
{
    int ret = 1;

    while ( *p ) {
        if ( (*p >= '0') && (*p <= '9') ) {
            p++;
            continue;
        }

        ret = 0;
        break;
    }

    return ( ret );
}

/* 直前に参照した URL を返す */
char    *
getCurrentLocation( char *url )
{
    if ( xmlrpc_p && url ) {
        if ( xmlrpc_p->webServer[0] && xmlrpc_p->webPage[0] )
            sprintf( url, "%s://%s%s",
                     xmlrpc_p->useSSL ? "https" : "http",
                     xmlrpc_p->webServer,
                     xmlrpc_p->webPage );
    }

    return ( url );
}

/* Windows の言語を取得 (例えば、日本語版: 1041, 英語(USA)版: 1033) */
DWORD
getLanguageCode( void )
{
    return ( xmlrpc_p ? xmlrpc_p->languageCode : GetThreadLocale() );
}

/* 言語を強制切り替え */
void
setLanguageCode( DWORD languageCode )
{
    if ( xmlrpc_p )
        xmlrpc_p->languageCode = languageCode;
    SetThreadLocale( languageCode );
}


#if (WINVER >= 0x0500)
#ifdef  _MSC_VER
#include <time.h>

/* 日本時間なのに夏時間フラグが立っている場合は、フラグを強制的におろす */
void
resetDaylightSaving( void )
{
    time_t      t = time( NULL );
    struct tm   *tm = localtime( &t );

    if ( tm->tm_isdst == 1 ) {
        char    *p = _tzname[0];
        if ( !strcmp( p, "JST" ) ) {
            /* なぜか日本時間であるにも関わらず、夏時間になっている場合 */
            long l = _daylight;

            if ( l == 1 ) {
                // 環境変数 TZ を設定している場合は、(Visual Studio 2005 の)
                // 「C ランタイム ライブラリは、夏時間 (DST: Daylight Saving
                // Time) 計算の実装については米国の規則を前提としています」と
                // いうことで、勝手に夏時間にされてしまうらしい
                // 日本時間には(少なくとも現時点では)夏時間はないのに……
                _daylight = 0;
            }
        }
        // とりあえず、日本時間のみ考慮したが、本当は、他の夏時間未導入国・
        // 地域やアメリカと夏時間の開始・終了時期が異なる国・地域に対する配
        // 慮も必要
        // なお、Visual C++ 6 のランタイムでは、TZ=JST-9 と設定している場合
        // でも、日本時間が夏時間ありと判定されてしまうようなことはない。あ
        // くまでも Visual C++ 2005 のランタイムの問題である(Visual C++.NET
        // 2002/2003 に関しては未確認)
    }
}
#endif
#endif

#ifdef  USE_RURL
/* rurl.org を利用して短縮URLを生成 */
char    *
makeRurl( const char *url )
{
    Thread static char  result[MAX_URLLENGTH];
    size_t              sz = MAX_CONTENT_SIZE;
    char                *response = (char *)malloc( sz );

    memset( result, 0x00, MAX_URLLENGTH );
    strncpy( result, url, MAX_URLLENGTH - 2 );
    if ( response ) {
        char    request[BUFSIZ];

        sprintf( request,
                 "url=%s&"
                 "apikey=%s",
                 encodeURL(url), xmlrpc_p->rurlAPIkey );
        setUpReceiveBuffer( response, sz );
        http_post( "http://rurl.org/api/",
                   "application/x-www-form-urlencoded",
                   request, response );
        if ( *response ) {
            /*
             *  応答
             *    <?xml version="1.0" encoding="UTF-8" ?> 
             *    <rurl>
             *      <urls>
             *        <url goesto="元のURL">短縮URL</url> 
             *      </urls>
             *      <errors /> 
             *    </rurl>
             */
            char    *p = strstr( response, "<url goesto=\"" );
            if ( p ) {
                char    *q;

                p += 13;
                q = strchr( p, '>' );
                if ( q ) {
                    p = q + 1;
                    q = strchr( p, '<' );
                    if ( q ) {
                        strncpy( result, p, q - p );
                        result[q - p] = NUL;
                    }
                }
            }
        }

        free( response );
    }

    return ( result );
}
#endif  /* USE_RURL */


void    dputc( char c )
{
    // Visual Studio 2008 の VC++ (VC9) でビルドすると、以下の処理で
    // 落ちることが判明 (VC6、VC8 では現象発生せず) → 原因の解明と
    // 対策が必要
    fputc( c, xmlrpc_p->verboseFp ? xmlrpc_p->verboseFp : stderr );
}

void    dputs( const char *str )
{
    // Visual Studio 2008 の VC++ (VC9) でビルドすると、以下の処理で
    // 落ちることが判明 (VC6、VC8 では現象発生せず) → 原因の解明と
    // 対策が必要
    fputs( str, xmlrpc_p->verboseFp ? xmlrpc_p->verboseFp : stderr );
}

int     dprintf( const char *format, ... )
{
    Thread static char  buffer[MAX_CONTENT_SIZE * 16];
    size_t              sz = 0;
    va_list             args;

    buffer[0] = NUL;
    va_start( args, format );
    sz = vsprintf( buffer, format, args );
    va_end( args );

    dputs( buffer );

    return ( sz );
}
