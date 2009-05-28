/** \mainpage xmlRPC API サポートライブラリ
 *   元々、
 *   <a href="http://www.na.rim.or.jp/~tsupo/program/blogTool/mt_xmlRpc.html"
 *   title="Movable Type で使える XML-RPC API">ウェブログ関連の XML-RPC API</a>
 *   および
 *   <a href="http://www.amazon.com/gp/browse.html/ref=smm_sn_aws/104-2882495-4914322?%5Fencoding=UTF8&amp;node=3435361"
 *   title="Amazon Web Services">Amazon Web Services</a>
 *   を利用するアプリケーションを容易に作成できるようにするのが目的で作成を開始したライブラリであるため、
 *   xmlRPC という名前になっている。
 *   現在は、Atom API や SOAP 絡みの API もサポートしている。また、XML-RPC API
 *   も Atom API も使えない blog サービス(のごく一部)向けに、記事を投稿する
 *   API を用意している。
 *
 *   今のところ、Windows 向けのライブラリしか用意していないが、UNIX や Linux
 *   等への移植を容易にするため、可能な限り ANSI C の範囲内で記述している。
 *   やむをえず、Win32 API を直接使わざるを得なかった箇所に関しては
 *   \#ifdef WIN32 / \#endif で囲む等、明確に分離している。
 *
 *   なお、本ライブラリは、文字コードの変換に
 *   <a href="http://www.gnu.org/software/libiconv/" title="libiconv -GNU Project">GNU iconv (libiconv)</a>
 *   を利用している。本ライブラリを利用するアプリケーションを実行するには
 *   あらかじめ
 *   <a href="http://www.gnu.org/software/libiconv/" title="libiconv -GNU Project">libiconv</a>
 *   をインストールしておく必要がある。
 *
 *   また、本ライブラリアは SSL 関連の処理の実行に際し、
 *   <a href="http://www.openssh.com/" title="OpenSSH">OpenSSH</a>
 *   を利用している。ただし、本ライブラリは
 *   <a href="http://www.openssh.com/" title="OpenSSH">OpenSSH</a>
 *   の static library を使用しているので、
 *   本ライブラリを利用するアプリケーションの利用者の方で
 *   <a href="http://www.openssh.com/" title="OpenSSH">OpenSSH</a>
 *   のライブラリを別途インストールする必要はない。
 */

/*
 *  xmlRPC.h
 *
 *    XML-RPC API サポートライブラリ
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2008, 2009 by H.Tsujimura
 *      written by H.Tsujimura
 *      mailto: tsupo@na.rim.or.jp
 *
 *      See also:
 *       http://www.na.rim.or.jp/~tsupo/program/blogTool/mt_xmlRpc.html
 *       http://www.na.rim.or.jp/~tsupo/program/blogTool/bloggerApiClient.html
 *       http://watcher.moe-nifty.com/memo/cat153983/index.html
 *
 * History:
 * $Log: /comm/xmlRPC/xmlRPC.h $
 * 
 * 4     09/05/29 7:09 tsupo
 * 1.267版
 * 
 * 246   09/05/28 18:36 Tsujimura543
 * getResultFromXML_s() を追加
 * 
 * 245   09/05/27 22:03 Tsujimura543
 * setSigInfo3() を追加
 * 
 * 244   09/05/27 19:28 Tsujimura543
 * setSigInfo() を取り込む
 * 
 * 3     09/05/27 1:18 tsupo
 * 1.266版
 * 
 * 243   09/05/26 20:55 Tsujimura543
 * APIURL_TUMBLR_ACOUNT を追加
 * 
 * 242   09/05/26 16:56 Tsujimura543
 * (1) tumblr 関連の #define を追加
 * (2) ココログ、ココログフリーのエンドポイントを http から https に変更
 * 
 * 2     09/05/16 2:39 tsupo
 * 「1.263版→1.264版」の変更を取り込む
 * 
 * 241   09/05/15 21:56 Tsujimura543
 * hmac_sha256() を追加
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 240   09/03/30 22:54 Tsujimura543
 * getNonce() を追加
 * 
 * 239   09/03/30 19:48 Tsujimura543
 * OAuth 対応
 * 
 * 238   09/03/27 20:15 Tsujimura543
 * hmac_sha1() を追加
 * 
 * 237   09/03/20 17:45 Tsujimura543
 * ウェブリブログの XML-RPC API 経由での投稿、動作確認終了
 * 
 * 236   09/03/17 22:42 Tsujimura543
 * Windows Live Spaces (およびウェブリブログ) 向けの処理を追加
 * 
 * 235   09/03/16 19:17 Tsujimura543
 * getCategories() を追加
 * 
 * 234   09/03/16 14:04 Tsujimura543
 * 「ウェブリブログ (XML-RPC API)」関連、追加
 * 
 * 233   08/11/27 14:49 Tsujimura543
 * getOpenSSLversion() と getIconvVersion() を追加
 * 
 * 232   08/11/14 12:10 Tsujimura543
 * MAX_COOKIE_NAME_LENGTH と MAX_COOKIE_VALUE_LENGTH を追加
 * 
 * 231   08/11/14 11:50 Tsujimura543
 * USE_APIKEY_H が define 済みの場合のみ、apiKey.h をインクルード
 * するようにした
 * 
 * 230   08/09/10 23:52 Tsujimura543
 * ソースを整理 (コメントアウトしてあったコードを削除)
 * 
 * 229   08/09/10 22:48 Tsujimura543
 * エキサイトブログ関連の関数群を削除 (xmlRPC.dll 外へ移動)
 * 
 * 228   08/09/10 21:43 Tsujimura543
 * エコログ関連の関数群を削除 (xmlRPC.dll 外へ移動)
 * 
 * 227   08/09/10 18:25 Tsujimura543
 * 楽天ブログ関連の関数群を削除 (xmlRPC.dll 外へ移動)
 * 
 * 226   08/09/09 23:58 Tsujimura543
 * 不要になった機能を削除 (その5)
 * 
 * 225   08/09/09 22:51 Tsujimura543
 * 不要になった機能を削除 (その4)
 * 
 * 224   08/09/09 21:23 Tsujimura543
 * 不要になった機能を削除 (その3)
 * 
 * 223   08/09/09 18:24 Tsujimura543
 * 不要になった機能を削除 (その2)
 * 
 * 222   08/09/09 17:52 Tsujimura543
 * 不要になった機能を削除
 * 
 * 221   08/07/25 23:07 Tsujimura543
 * http_deleteBASIC() を追加
 * 
 * 220   08/05/15 23:23 Tsujimura543
 * 外部公開用関数として getStatusCode() を追加
 * 
 * 219   08/02/15 22:58 Tsujimura543
 * AMAZON_STYPE_ITEMLOOKUP の値を 2 から 4 に変更
 * 
 * 218   08/02/15 22:32 Tsujimura543
 * getSalesRankingOnAmazon4() を追加
 * 
 * 217   08/02/13 23:24 Tsujimura543
 * searchItemsOnAmazon4() を追加
 * 
 * 216   08/02/07 22:25 Tsujimura543
 * copyright 表示を修正 (2008 を追加)
 * 
 * 215   08/01/29 17:28 Tsujimura543
 * bk1ブリーダー関連のコードを削除
 * (すでにbk1ブリーダー制度は廃止されている)
 * 
 * 214   08/01/23 16:40 Tsujimura543
 * http_getW, http_postW, http_putW, http_deleteW を追加
 * 
 * 213   07/12/20 15:20 Tsujimura543
 * Visual Studio 2005 によるコンパイルチェック結果を反映
 * 
 * 212   07/12/19 20:55 Tsujimura543
 * startup を追加 (for connectHTTP)
 * 
 * 211   07/12/06 5:36 Tsujimura543
 * #pragma message 行を追加
 * 
 * 210   07/12/06 1:26 Tsujimura543
 * getSendBufferPointer() を追加
 * 
 * 209   07/12/06 1:16 Tsujimura543
 * _httpExecute() でバイナリファイルの送信に対応するための修正を実施
 * 
 * 208   07/11/30 1:41 Tsujimura543
 * (1) ヤプログ!、ドリコムブログ、Jugem 向けに特別に用意していた処理を削除
 * (2) アメーバブログ向けの特別処理を削除 (Atom API 関連を除く)
 * 
 * 207   07/10/29 16:41 Tsujimura543
 * BLOGKIND_YAPLOG_X を追加
 * 
 * 206   07/10/29 15:17 Tsujimura543
 * APIURL_YAPLOG_X を追加
 * 
 * 205   07/10/09 20:08 Tsujimura543
 * dputc() を追加
 * 
 * 204   07/10/09 19:32 Tsujimura543
 * dputs() と dprintf() を追加
 * 
 * 203   07/09/28 19:18 Tsujimura543
 * XMLRPC_ERROR_CHANGED_PROXYINFO を導入
 * 
 * 202   07/09/14 22:40 Tsujimura543
 * MAX_URLLENGTH_MAX の定義を http.h から xmlRPC.h へ移動
 * 
 * 201   07/09/10 19:05 Tsujimura543
 * 各種Webサービス関連で使用していないものをオプション化(実質、廃止)
 * 
 * 200   07/09/07 20:52 Tsujimura543
 * http通信のスレッド間排他制御対応
 * 
 * 199   07/09/07 18:29 Tsujimura543
 * replaceEntityStrings() に第2引数を追加。Shift_JIS 以外の場合にも対応
 * 
 * 198   07/09/07 17:03 Tsujimura543
 * replaceEntityStrings() を追加
 * 
 * 197   07/09/04 20:21 Tsujimura543
 * verboseFp を追加し、setVerbos() の第2引数で値を変更できるようにした
 * 
 * 196   07/09/04 20:10 Tsujimura543
 * dumpFp を追加し、setDump() の第2引数で値を変更できるようにした
 * 
 * 195   07/08/29 16:07 Tsujimura543
 * http_headBASIC() を追加
 * 
 * 194   07/08/24 18:38 Tsujimura543
 * setReferer() を追加
 * 
 * 193   07/08/10 23:18 Tsujimura543
 * http_getBASICEx() を追加
 * 
 * 192   07/05/22 0:28 Tsujimura543
 * ユーザ名とパスワードが必要な proxyサーバを使っての https 通信に
 * 対応 (動作確認済み)
 * 
 * 191   07/04/09 17:36 Tsujimura543
 * rurl.org API 関連処理を追加
 * 
 * 190   07/04/09 16:19 Tsujimura543
 * CONF_FUNC の typedef を追加
 * 
 * 189   07/03/26 16:05 Tsujimura543
 * (1) http関連関数群をバイナリファイルの受信にも対応させた
 * (2) getBinSize() を追加した
 * 
 * 188   07/03/16 18:31 Tsujimura543
 * http_postBASIC() を追加
 * 
 * 187   07/03/13 19:18 Tsujimura543
 * setProxy() → setProxyInfo() に名称変更
 * 
 * 186   07/03/13 19:16 Tsujimura543
 * setProxy() を追加
 * 
 * 185   07/03/10 5:05 Tsujimura543
 * confirmProxyInfo() の引数を2個追加
 * 
 * 184   07/03/10 4:58 Tsujimura543
 * ユーザ名とパスワードの指定が必要なproxyサーバにも暫定的に対応
 * 
 * 183   07/03/09 21:13 Tsujimura543
 * isNecessaryToCheckProxyInfo() を追加、およびそれに伴う修正を実施
 * 
 * 182   07/03/09 17:25 Tsujimura543
 * setConfirmProxyInfoFunc() を追加
 * 
 * 181   07/03/09 16:59 Tsujimura543
 * XMLRPC構造体に confirmProxyInfo を追加
 * 
 * 180   07/03/06 23:33 Tsujimura543
 * typo 修正
 * 
 * 179   07/03/05 17:15 Tsujimura543
 * setKeywordLink() に引数を追加 (バッファオーバーフロー対策)
 * 
 * 178   07/03/02 11:42 Tsujimura543
 * じゃらんWebサービスAPIキー 対応
 * 
 * 177   07/03/01 19:06 Tsujimura543
 * XMLRPC 構造体の webPage メンバの領域サイズを増やす (512 → 4096)
 * 
 * 176   07/02/23 23:08 Tsujimura543
 * JUGEM とドリコムブログの XML-RPC API 関連の定義を追加
 * 
 * 175   07/01/23 15:31 Tsujimura543
 * postRakuten() の動作確認、終了 (新しい管理画面への対応作業、完了)
 * 
 * 174   07/01/23 15:29 Tsujimura543
 * (1) getCategoryListRakuten() を追加
 * (2) postRakuten() の引数を追加し、カテゴリを指定して投稿できるようにした
 * 
 * 173   07/01/17 19:26 Tsujimura543
 * 楽天デベロッパーID 対応
 * 
 * 172   07/01/17 17:34 Tsujimura543
 * copyright 表示を修正 (2007 を追加)
 * 
 * 171   07/01/17 16:54 Tsujimura543
 * Windows の「言語」の取得、設定用の関数を追加
 * 
 * 170   06/12/23 0:09 Tsujimura543
 * proxy 使用時の https 接続のときのヘッダ部分が http でなければいけない
 * サーバ、https でなければいけないサーバ、どちらでもいいサーバのどのパ
 * ターンにも対応するため、フラグを1個追加し、対応した 
 * 
 * 169   06/10/19 22:58 Tsujimura543
 * 今までライブラリ外には 非公開だった getProxyInfo() を公開することにした
 * 
 * 168   06/10/19 18:44 Tsujimura543
 * sendUpdateExtendedPing() を追加
 * 
 * 167   06/10/13 17:18 Tsujimura543
 * ウェブリブログに投稿するとき、テンプレートIDを指定可能にした
 * 
 * 166   06/10/11 17:45 Tsujimura543
 * XML_STATEMENT の改行コードを \n から \r\n に変更
 * 
 * 165   06/10/07 1:34 Tsujimura543
 * http(応答受信待ち)タイムアウト時間を設定変更できるようにした
 * 
 * 164   06/09/25 15:13 Tsujimura543
 * http_headEx() を追加
 * 
 * 163   06/09/15 18:10 Tsujimura543
 * BLOGKIND_FREPA, BLOGKIND_YAHOO360, BLOGKIND_OPENPNE,
 * BLOGKIND_SIMANITY を追加
 * 
 * 162   06/09/15 14:42 Tsujimura543
 * バリューコマース関連の定義、記憶領域、関数を削除・廃止
 * 
 * 161   06/09/14 15:46 Tsujimura543
 * MAX_BLOGIDLENGTH の値を 48 に変更 (Vox 対策)
 * 
 * 160   06/09/14 13:28 Tsujimura543
 * VOX のエンドポイントURLを追加
 * 
 * 159   06/09/11 17:21 Tsujimura543
 * getBlogIDsJugem(), getBlogIDsExciteBlog(), getBlogIDsYaplog(),
 * getBlogIDsDrecom(), getBlogIDsEchoo(), getBlogIDsRakuten()
 * を追加
 * 
 * 158   06/09/11 15:15 Tsujimura543
 * getBlogIDsWebry() を追加
 * 
 * 157   06/09/11 12:06 Tsujimura543
 * コメントを追加
 * 
 * 156a  06/09/10 5:48 tsupo
 * resetDaylightSaving() を導入した
 * (Visual Studio 2005 の C++ ランタイム使用時に、日本時間なのに夏時間と
 * 判定されてしまう件の対策)
 * 
 * 156   06/09/08 0:00 Tsujimura543
 * APIURL_BLOGGER_GDATA を追加 (GData API 対応準備)
 * 
 * 155   06/09/05 12:54 Tsujimura543
 * convUnicode() のプロトタイプ宣言を追加
 * 
 * 154   06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 153a  06/09/03 7:40 tsupo
 * MAX_COOKIE_LEN を追加
 * 
 * 153   06/09/02 1:12 Tsujimura543
 * http通信実行中かどうかをチェックできる関数を追加した
 * 
 * 152   06/07/24 19:24 Tsujimura543
 * _httpExecute() のバッファオーバーラン防止対策関連の仕組みを修正
 * 
 * 151   06/07/24 14:10 Tsujimura543
 * setUpReceiveBuffer() を追加
 * 
 * 150   06/06/23 18:12 Tsujimura543
 * MAX_DESCRIPTION_LEN の値を 2048 から 4096 に増やす (for Flog)
 * 
 * 149   06/03/14 20:52 Tsujimura543
 * deleteCocologFiles() と deleteFile() を追加
 * 
 * 148   06/03/13 16:49 Tsujimura543
 * getCurrentLocation() を追加
 * 
 * 147   06/03/07 10:37 Tsujimura543
 * TRUE, FALSE のどちらか一方のみが他のヘッダファイルで定義されている
 * 場合に対処
 * 
 * 146   06/03/03 16:21 Tsujimura543
 * httpGetFileBASIC() の引数の順序を変更
 * 
 * 145   06/02/22 17:13 Tsujimura543
 * encodeURLex4() を追加
 * 
 * 144   06/02/22 16:48 Tsujimura543
 * encodeURLex3() を追加
 * 
 * 143   06/02/08 18:28 Tsujimura543
 * utf2sjisEx() を追加
 * 
 * 142   06/02/06 17:44 Tsujimura543
 * 「マイプロフィール」関連の処理を削除
 * 
 * 141   06/01/31 14:14 Tsujimura543
 * lcc win32 でもコンパイルが通るようにした
 * 
 * 140   06/01/26 17:08 Tsujimura543
 * COOKIE_INFO 構造体を変更し、値(文字列)の格納領域サイズを増量した
 * 
 * 139   06/01/26 13:22 Tsujimura543
 * アメーバブログの Atom API  エンドポイント URL の定義を追加
 * 
 * 138   06/01/25 19:20 Tsujimura543
 * excite Blog のログイン処理、投稿処理を変更 (引数を追加)
 * 
 * 137   06/01/13 16:03 Tsujimura543
 * dwsEmail, dwsHID を追加
 * 
 * 136   06/01/10 15:12 Tsujimura543
 * userAgent / setUserAgent() を追加
 * 
 * 135   05/12/27 18:34 Tsujimura543
 * loginColors() と postColors() を追加
 * 
 * 134   05/12/27 18:32 Tsujimura543
 * BLOGKIND_COLORS を追加
 * 
 * 133   05/12/21 18:46 Tsujimura543
 * (1) euc2sjis() の機種依存文字対応版 euc2sjisEx() を追加
 * (2) 機種依存文字を機種非依存の文字列に置換する regular() を追加 
 * 
 * 132   05/12/14 13:41 Tsujimura543
 * MSN Spaces 関連の定義を追加
 * 
 * 131   05/12/14 13:37 Tsujimura543
 * Yahoo! Japan 検索WebサービスAPI対応準備
 * 
 * 130   05/12/09 16:13 Tsujimura543
 * RAKUTEN_GENRE_PHOTOBOOL を RAKUTEN_GENRE_PHOTOBOOK に修正
 * 
 * 129   05/11/30 14:29 Tsujimura543
 * MAX_DESCRIPTION_LEN の定義(値)を統一し、xmlRPC.h に移動
 * 
 * 128   05/11/28 14:40 Tsujimura543
 * ATOMURL_COCOLOGFREE を追加
 * 
 * 127   05/11/28 14:17 Tsujimura543
 * goo Blog と ココログフリー 関連の定義を追加
 * 
 * 126   05/11/17 21:31 Tsujimura543
 * http による送信可能な電文サイズの上限をメモリの許す限りどこまでも
 * 大きくできるようにした (初期サイズは従来の値)
 * 
 * 125   05/11/17 19:55 Tsujimura543
 * AMAZON_MODE_SPORTS を追加
 * 
 * 124   05/11/17 15:25 Tsujimura543
 * loginCocologFiles() と uploadCocologFiles() を追加
 * 
 * 123   05/11/07 11:22 Tsujimura543
 * APIURL_DTIBLOG を追加
 * 
 * 122   05/10/29 1:12 Tsujimura543
 * ブックマーク登録時に使用する処理を各々見直した(動作確認済み)
 * 
 * 121   05/10/28 21:00 Tsujimura543
 * encodeURLex2() を試験的に導入してみた
 * 
 * 120   05/10/28 18:22 Tsujimura543
 * encodeURLex() を追加
 * 
 * 119   05/10/28 15:36 Tsujimura543
 * iso8859_1toUtf8() を追加
 * 
 * 118   05/10/18 18:46 Tsujimura543
 * (1) _httpExecute() の引数追加に伴う各種変更を実施
 * (2) http_getEx2() と http_postEx2() を追加
 * 
 * 117   05/09/21 23:43 Tsujimura543
 * doxygen 対応コメント追加
 * 
 * 116   05/09/03 0:38 Tsujimura543
 * doxygen が生成する「メインページ」向けのコメント(暫定)を冒頭に追加
 * 
 * 115   05/09/02 14:35 Tsujimura543
 * affiriate → affiliate に修正 (綴り間違い)
 * 
 * 114   05/07/20 14:27 Tsujimura543
 * livedoor Blog の2005年7月リニューアル後の新エンドポイントURLの定義を追
 * 加
 * 
 * 113   05/07/19 10:54 Tsujimura543
 * So-net blog 関連の定義を追加
 * 
 * 112   05/06/28 22:06 Tsujimura543
 * httpPutBASIC() に引数 mimeType を追加
 * 
 * 111   05/06/28 15:30 Tsujimura543
 * httpDeleteBASIC(), httpPutBASIC(), httpPostBASIC() を追加
 * 
 * 110   05/06/28 11:06 Tsujimura543
 * blogger.com の Atom API のエンドポイントURL に関して http → https
 * に変更
 * 
 * 109   05/05/31 22:51 Tsujimura543
 * httpPutEx() を追加
 * 
 * 108   05/05/30 20:29 Tsujimura543
 * BLOGKIND_HATENA を追加
 * 
 * 107   05/05/24 14:43 Tsujimura543
 * BASIC認証に対応
 * 
 * 106   05/05/19 16:31 Tsujimura543
 * isbn2urls() に第2引数を追加
 * 
 * 105   05/05/19 13:42 Tsujimura543
 * setSpaceId3OnValueCommerce() と setSpaceId4OnValueCommerce() を追加
 * 
 * 104   05/05/19 13:22 Tsujimura543
 * XMLRPC 構造体の ValueCommerce 関連のメンバを増減 (2増1減)
 * 
 * 103   05/05/18 21:45 Tsujimura543
 * getSalesRankingOnRakuten() の仕様を変更 (構造体に検索結果を格納する
 * ようにした)
 * 
 * 102   05/05/18 16:36 Tsujimura543
 * searchEntryOnFeedback() を追加
 * 
 * 101   05/05/18 14:25 Tsujimura543
 * extractFeatureWordsOnBulkfeeds() と extractAnalyseOnBulkfeeds() の
 * 引数を2個追加
 * 
 * 100   05/04/28 11:22 Tsujimura543
 * updateRssOnBulkfeeds() の戻り値の型を int から BOOL に変更
 * 
 * 99    05/04/21 15:50 Tsujimura543
 * loginRakuten() に引数を1個追加
 * 
 * 98    05/04/20 19:59 Tsujimura543
 * loginRakuten() と postRakuten() を追加
 * 
 * 97    05/04/18 15:53 Tsujimura543
 * getResultFromXML() など XML 関連ユーティリティ関数のプロトタイプ
 * 宣言を追加
 * 
 * 96    05/04/14 14:40 Tsujimura543
 * FC2BLOG に関する #define を追加
 * 
 * 95    05/04/01 16:45 Tsujimura543
 * postAmeblo() の引数の説明を変更
 * 
 * 94    05/04/01 16:32 Tsujimura543
 * getCategoryListAmeblo() を追加
 * 
 * 93    05/03/28 14:37 Tsujimura543
 * loginFC2NETWORK(), postFC2NETWORK() を追加
 * 
 * 92    05/03/25 20:49 Tsujimura543
 * postJugem() の引数を追加し、カテゴリ名を指定できるようにした
 * 
 * 91    05/03/25 20:46 Tsujimura543
 * postExciteBlog() の引数を追加し、カテゴリ名を指定できるようにした
 * 
 * 90    05/03/25 20:05 Tsujimura543
 * postDrecom() の引数を追加し、カテゴリ名を指定できるようにした
 * 
 * 89    05/03/25 19:49 Tsujimura543
 * postYaplog() の引数を追加し、カテゴリ名を指定できるようにした
 * 
 * 88    05/03/25 17:12 Tsujimura543
 * getCategoryIDbyName() を追加
 * 
 * 87    05/03/25 17:03 Tsujimura543
 * isDecString() を追加
 * 
 * 86    05/03/25 16:48 Tsujimura543
 * isHexString() を追加
 * 
 * 85    05/03/24 14:41 Tsujimura543
 * getCategoryListWebry() を追加
 * 
 * 84    05/03/23 19:36 Tsujimura543
 * getCategoryListYaplog(), getCategoryListDrecom(),
 * getCategoryListEchoo(), getCategoryListExciteBlog(),
 * getCategoryListJugem() を追加
 * 
 * 83    05/03/22 15:00 Tsujimura543
 * isUsedProxy() を追加
 * 
 * 82    05/03/08 20:35 Tsujimura543
 * 「SweetBox Blog」に記述を統一
 * 
 * 81    05/03/08 16:56 Tsujimura543
 * SweetBox Blog に関する #define を追加
 * 
 * 80    05/03/07 23:11 Tsujimura543
 * NetLaputa と 269g に関する #define を追加
 * 
 * 79    05/02/21 14:02 Tsujimura543
 * APIURL_AMEBLO を追加 (NewsHandler と同じ API が使えることを確認)
 * 
 * 78    05/02/18 14:34 Tsujimura543
 * 「こうさぎ」が「BlogPet」へ移行したのに伴う修正
 * 
 * 77    05/01/26 13:25 Tsujimura543
 * getTrackbackURL() を追加
 * 
 * 76    05/01/26 11:09 Tsujimura543
 * BLOGKIND_RAKUTEN を追加
 * 
 * 75    05/01/18 21:54 Tsujimura543
 * コメントの間違いを修正
 * 
 * 74    05/01/18 11:03 Tsujimura543
 * http_getEx(), http_postEx() を追加
 * 
 * 73    04/12/28 15:31 Tsujimura543
 * 送信バッファサイズを3MBとする
 * 
 * 72    04/11/29 18:30 Tsujimura543
 * AMAZON_MOD_* → AMAZON_MODE_* に変更
 * 
 * 71    04/11/29 13:25 Tsujimura543
 * コンソール入力関連関数を追加
 * 
 * 70    04/11/26 20:54 Tsujimura543
 * ウェブリブログ対応
 * 
 * 69    04/11/25 17:19 Tsujimura543
 * loginEchoo() に引数を追加
 * 
 * 68    04/11/25 10:21 Tsujimura543
 * postEchoo() の引数を追加 (カテゴリIDを指定できるようにした)
 * 
 * 67    04/11/24 23:44 Tsujimura543
 * エコログ対応作業開始
 * 
 * 66    04/11/24 15:16 Tsujimura543
 * (1) HTTP リクエストの主要なメソッドを直接実行するAPIを追加
 * (2) https://www2.ggn.net/cgi-bin/ssl を GET できることを確認
 * 
 * 65    04/11/19 20:38 Tsujimura543
 * SSL 関連の関数を追加
 * 
 * 64    04/11/19 14:51 Tsujimura543
 * SSL 対応準備
 * 
 * 63    04/11/17 18:43 Tsujimura543
 * struct biddersSearchResult の long 型のメンバを unsigned long に変更
 * 
 * 62    04/11/17 16:58 Tsujimura543
 * BIDDERS_LITE のメンバ remainingTime の型を数値(long)から
 * 文字列(char[])に変更
 * 
 * 61    04/11/17 16:12 Tsujimura543
 * struct biddersSearchResult に「商品のURL」を追加
 * 
 * 60    04/11/17 15:57 Tsujimura543
 * bidders関連関数を追加
 * 
 * 59    04/11/16 14:08 Tsujimura543
 * APIURL_SEESAABLOG_SEC を追加 (https は未対応)
 * 
 * 58    04/11/15 14:45 Tsujimura543
 * setSiteIdOnValueCommerce(), setSpaceId1OnValueCommerce(),
 * setSpaceId2OnValueCommerce() を追加
 * 
 * 57    04/11/15 13:56 Tsujimura543
 * searchPagesDirectlyOnGoogle() を追加
 * 
 * 56    04/11/15 11:09 Tsujimura543
 * getAffiriateLinkOnJbook() と translateURL() を追加
 * 
 * 55    04/11/12 21:09 Tsujimura543
 * searchPagesOnGoogle() の第5引数を変更
 * 
 * 54    04/11/12 11:11 Tsujimura543
 * unbase64() を追加
 * 
 * 53    04/11/12 10:48 Tsujimura543
 * Google APIs を追加
 * 
 * 52    04/11/11 11:26 Tsujimura543
 * searchSimilarityOnBulkfeeds() の引数を変更
 * 
 * 51    04/11/04 16:56 Tsujimura543
 * キヌガサ Web Service 対応準備
 * 
 * 50    04/11/04 16:44 Tsujimura543
 * アマゾンのベストセラー一覧の取得結果も構造体に格納して返すようにした
 * 
 * 49    04/11/04 16:05 Tsujimura543
 * getNewWhisperOnCousagi() を追加
 * 
 * 48    04/11/04 15:59 Tsujimura543
 * setSubscriptionIDOnAmazon() を追加
 * 
 * 47    04/11/04 15:53 Tsujimura543
 * Amazon E-Commerce Service 4.0 対応準備
 * 
 * 46    04/11/02 21:46 Tsujimura543
 * アマゾンの検索オプションに「すべての商品」を追加
 * 
 * 45    04/11/02 20:47 Tsujimura543
 * アマゾンの新カテゴリ「おもちゃ&ホビー」の検索に対応
 * 
 * 44    04/11/01 21:01 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 43    04/11/01 19:54 Tsujimura543
 * 『「こうさぎ」からのおすすめ』を試験的に実装
 * 
 * 42    04/10/27 15:02 Tsujimura543
 * searchEntryOnBulkfeeds() の仕様を変更。キーワード検索した結果(記事一覧)
 * を返すようにした
 * 
 * 41    04/10/15 15:20 Tsujimura543
 * NewsHandler の blog ID, post ID は共に32byteであるため、領域を増やして
 * 対応する
 * 
 * 40    04/10/14 23:20 Tsujimura543
 * getEndpointURLbyAutoDiscovery() で blogID も取得するように変更
 * 
 * 39    04/10/14 21:56 Tsujimura543
 * getEndpointURLbyAutoDiscovery() を追加
 * 
 * 38    04/10/14 15:19 Tsujimura543
 * MAX_BLOGIDLENGTH の値を 32 に変更
 * 
 * 37    04/10/14 14:21 Tsujimura543
 * 投稿者のIDとblogのオーナーのIDが別IDの場合に対応 (JUGEMの場合)
 * 
 * 36    04/10/12 13:45 Tsujimura543
 * 調査用コードのプロトタイプ宣言を追加
 * 
 * 35    04/10/08 19:19 Tsujimura543
 * loginKinugasa, postKinugasa を追加
 * 
 * 34    04/10/08 15:21 Tsujimura543
 * xmlRPC.h から API キー (および、その同類) を分離独立させて新たな
 * ヘッダファイルを用意した
 * 
 * 33    04/10/08 12:21 Tsujimura543
 * cookie 関連を修正 (バッファサイズ拡張、など)
 * 
 * 32    04/10/05 16:17 Tsujimura543
 * AWS Subscription ID を追加
 * 
 * 31    04/10/01 12:06 Tsujimura543
 * キヌガサWebService 対応
 * 
 * 30    04/09/28 16:40 Tsujimura543
 * ドリコムブログ対応
 * 
 * 29    04/09/21 22:53 Tsujimura543
 * アメーバブログ対応
 * 
 * 28    04/09/17 14:05 Tsujimura543
 * getCategoryIDwithName() を exciteBlog.c から取出し、共通関数化した
 * 
 * 27    04/09/16 16:13 Tsujimura543
 * getCategoryID() を jugem.c, myprofile.c, yaplog.c から取り出し、
 * 共通関数化した
 * 
 * 26    04/09/07 10:38 Tsujimura543
 * loginMixi, postMixi を追加
 * 
 * 25    04/09/03 11:36 Tsujimura543
 * loginMyprofile() に第4引数を追加
 * 
 * 24    04/09/02 15:46 Tsujimura543
 * cookie関連関数群を新規作成
 * 
 * 23    04/09/01 22:17 Tsujimura543
 * マイプロフィール関連関数名修正(綴りミス)
 * 
 * 22    04/09/01 22:11 Tsujimura543
 * マイプロフィール対応
 * 
 * 21    04/08/31 12:10 Tsujimura543
 * 関数のプロトタイプ宣言を整理
 * 
 * 20    04/08/30 14:48 Tsujimura543
 * MAX_POSTIDLENGTH, MAX_USERIDLEN を共に 80 に変更
 * 
 * 19    04/08/30 14:26 Tsujimura543
 * getRecentPostTitlesFromRSS を追加
 * 
 * 18    04/08/27 16:11 Tsujimura543
 * ヤプログ対応
 * 
 * 17    04/08/26 22:20 Tsujimura543
 * exciteブログに投稿できることを確認
 * 
 * 16    04/08/26 11:26 Tsujimura543
 * loginExciteBlog, postExciteBlog を追加
 * 
 * 15    04/08/25 16:57 Tsujimura543
 * loginJugem, postJugem を追加
 * 
 * 14    04/08/19 10:43 Tsujimura543
 * SUPPORT_FOR_WIN95 を #define した状態でコンパイルすると Windows 95
 * (ORS2以前) でも動くものができる(はず)
 * 
 * 13    04/08/19 9:04 Tsujimura543
 * TypaPad Germany 関連の定義を追加 (追加漏れしていた)
 * 
 * 12    04/08/17 10:26 Tsujimura543
 * getRecentPostTitlesOnBloggerAPI, getRecentPostTitlesOnMetaWeblog を追加
 * 
 * 11    04/08/13 15:03 Tsujimura543
 * Blogger.com の Atom API 関連の定義を追加
 * 
 * 10    04/08/12 21:19 Tsujimura543
 * LOVELOG 関連の定義を追加
 * 
 * 9     04/07/16 17:23 Tsujimura543
 * livedoor Blog の Atom API 関連の動作確認完了
 * 
 * 8     04/07/16 14:08 Tsujimura543
 * こうさぎ API 関連を整理
 * 
 * 7     04/07/14 18:49 Tsujimura543
 * Movable Type API 関連の関数の仕様見直し
 * 
 * 6     04/07/12 15:50 Tsujimura543
 * metaWeblog API 関連の関数の仕様見直し
 * 
 * 5     04/07/09 20:24 Tsujimura543
 * blogger API 関連の関数の仕様見直し
 * 
 * 3     04/07/07 15:46 Tsujimura543
 * 「blog情報テーブル」を追加
 * 
 * 2     04/07/07 11:44 Tsujimura543
 * RCS による版数管理から VSS による版数管理に移行
 */

#ifndef __XML_RPC_H__
#define __XML_RPC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef  UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#ifdef  WIN32
#ifdef  _MSC_VER
#pragma warning ( disable : 4115 )
#pragma warning ( disable : 4996 )
#endif
#include <io.h>
#ifdef  SUPPORT_FOR_WIN95
#ifdef  _MSC_VER
#if		_MSC_VER < 1400
#pragma message ("warning C4201 が出ても、無視してください")
#endif
#endif
#include <winsock2.h>
#else
#include <winsock.h>
#endif
#ifdef  _MSC_VER
#pragma warning ( default : 4115 )
#endif
#endif

#ifndef NUL
#define NUL     '\0'
#endif

#ifndef WIN32
#ifndef BOOL
#define BOOL    int
#endif
#endif

#ifndef TRUE
#ifdef  FALSE
#undef  FALSE
#endif  /* FALSE */
#define TRUE    (1)
#define FALSE   !TRUE
#endif

/* 定数、その他 */
#define DEFAULT_HTTP_PORT       80
#define DEFAULT_HTTPS_PORT      443
#define DEFAULT_HTTP_TIMEOUT    60
#define MAX_BLOGIDLENGTH    48
#define MAX_BLOGNAMELENGTH  128
#define MAX_URLLENGTH       384
#define MAX_URLLENGTH_MAX   4096
#define MAX_POSTIDLENGTH    80
#define MAX_CATIDLENGTH     80
#define MAX_CATNAMELENGTH   128
#define MAX_DATELENGTH      40
#define MAX_BOOLEANLENGTH   16
#define MAX_LOGICALLINELEN  256
#define MAX_USERIDLEN       80
#define MAX_PASSWDLEN       16
#define MAX_KEYLENGTH       64
#define MAX_NAMELEN         32
#define MAX_SERVERNAME      512
#define MAX_WEBPAGENAME     4096
#define MAX_DESCRIPTION_LEN 4096
#define MAX_CONTENT_SIZE    65536
#define SND_BUFFER_SIZE     (1024 * 1024 * 3)
#define RCV_BUFFER_SIZE     65536
#define MAX_COOKIE_LEN      4096
#define MAX_OAUTH_HEADER_LEN    1024

#define MAX_PINGSITES       16          /* update ping 送信先最大登録可能数 */
#define MAX_PINGS           20 /* 1回あたりのトラックバックping送信先最大数 */

#define MAX_CATEGORIES      16 /* metaWeblog.newPost 等 Windows Live Spaces */
                               /* 向け独自拡張部分で指定可能な最大カテゴリ数*/
                               /* [本来、上限値はないと思われるが、簡単のた */
                               /*  めに設定しておく] (暫定値)               */
                               /* この値は、Atom API でも使用する           */

/* blog種別 */
#define BLOGKIND_UNKNOWN        0x00    /* 不明                         */
#define BLOGKIND_MOVABLETYPE    0x01    /* Movable Type                 */
#define BLOGKIND_TYPEPAD        0x02    /* TypePad                      */
#define BLOGKIND_COCOLOG        0x03    /* ココログ                     */
#define BLOGKIND_BLOGZINE       0x04    /* BLOGZINE                     */
#define BLOGKIND_TYPEPADJAPAN   0x05    /* TypePad Japan                */
#define BLOGKIND_TYPEPADFRANCE  0x06    /* TypePad France               */
#define BLOGKIND_TYPEPADGERMANY 0x07    /* TypePad Germany (DE)         */
#define BLOGKIND_COCOLOGFREE    0x08    /* ココログフリー               */
#define BLOGKIND_BLOGGER        0x11    /* Blogger                      */
#define BLOGKIND_BLOGGERAPI     0x12    /* Blogger API サポート blog    */
#define BLOGKIND_METAWEBLOG     0x21    /* MetaWeblog API サポート blog */
#define BLOGKIND_NEWSHANDLER    0x22    /* News-Handler                 */
#define BLOGKIND_SEESAABLOG     0x23    /* Seesaa BLOG                  */
#define BLOGKIND_NETLAPUTA      0x24    /* NetLaputa blog               */
#define BLOGKIND_269G           0x25    /* 269G                         */
#define BLOGKIND_SWEETBOX       0x26    /* SweetBox Blog                */
#define BLOGKIND_FC2BLOG        0x27    /* FC2BLOG                      */
#define BLOGKIND_GOOBLOG        0x28    /* goo Blog                     */
#define BLOGKIND_MSNSPACES      0x29    /* Windows Live Spaces          */
#define BLOGKIND_JUGEM_X        0x2A    /* JUGEM (XML-RPC API)          */
#define BLOGKIND_DRECOMBLOG_X   0x2B    /* ドリコムBLOG (XML-RPC API)   */
#define BLOGKIND_YAPLOG_X       0x2C    /* yaplog (XML-RPC API)         */
#define BLOGKIND_WEBRY_X        0x2D    /* ウェブリブログ (XML-RPC API) */
#define BLOGKIND_MTAPI          0x31    /* MovableType API サポートblog */
#define BLOGKIND_ATOMAPI        0x41    /* Atom API サポート blog       */
#define BLOGKIND_LIVEDOOR       0x42    /* livedoor Blog                */
#define BLOGKIND_LOVELOG        0x43    /* LOVELOG                      */
#define BLOGKIND_SONET          0x44    /* So-net blog                  */
#define BLOGKIND_VOX            0x45    /* Vox                          */
#define BLOGKIND_HATENADIARY    0x46    /* はてなダイアリー             */

#define BLOGKIND_JUGEM_OLD      0xE1    /* JUGEM (xxx.jugem.cc)         */
#define BLOGKIND_JUGEM_NEW      0xE2    /* JUGEM (xxx.jugem.jp)         */
#define BLOGKIND_EXCITEBLOG     0xE3    /* exciteブログ                 */
#define BLOGKIND_YAPLOG         0xE4    /* yaplog                       */
#define BLOGKIND_MYPROFILE      0xE5    /* マイプロフィール             */
#define BLOGKIND_MIXI           0xE6    /* mixi                         */
#define BLOGKIND_KINUGASA       0xE7    /* キヌガサ                     */
#define BLOGKIND_AMEBLO         0xE8    /* アメーバブログ               */
#define BLOGKIND_DRECOMBLOG     0xE9    /* ドリコムBLOG                 */
#define BLOGKIND_ECHOO          0xEA    /* エコログ                     */
#define BLOGKIND_WEBRY          0xEB    /* ウェブリブログ               */
#define BLOGKIND_RAKUTEN        0xEC    /* 楽天広場                     */
#define BLOGKIND_FC2NETWORK     0xED    /* FC2NETWORK                   */
#define BLOGKIND_HATENA         0xEF    /* はてなブックマーク/Fotolife  */
#define BLOGKIND_COLORS         0xF0    /* COLORS                       */
#define BLOGKIND_FREPA          0xF1    /* フレパ                       */
#define BLOGKIND_YAHOO360       0xF2    /* Yahoo! Days                  */
#define BLOGKIND_OPENPNE        0xF3    /* OpenPNE                      */
#define BLOGKIND_SIMANITY       0xF4    /* しまにてぃ                   */
#define BLOGKIND_TUMBLR         0xF5    /* tumblr (の text)             */

/* XML-RPC API エンドポイント URL */
#define APIURL_MOVABLETYPE      "$/mt/mt-xmlrpc.cgi"
#define APIURL_TYPEPAD          "http://www.typepad.com/t/api"
#define APIURL_TYPEPADJAPAN     "http://www.typepad.jp/t/api"
#define APIURL_TYPEPADFRANCE    APIURL_TYPEPAD
#define APIURL_TYPEPADGERMANY   APIURL_TYPEPAD
#define APIURL_COCOLOG          "https://app.cocolog-nifty.com/t/api/"
#define APIURL_COCOLOGFREE      "https://app.f.cocolog-nifty.com/t/api/"
#define APIURL_BLOGZINE         "http://app.blog.ocn.ne.jp/t/api/"
#define APIURL_NEWSHANDLER      "http://blog.nettribe.org/xmlrpc.php"
#define APIURL_SEESAABLOG       "http://blog.seesaa.jp/rpc/"
#define APIURL_SEESAABLOG_SEC   "https://ssl.seesaa.jp/blog/rpc" /* https版 */
#define APIURL_NETLAPUTA        "http://blog.netlaputa.ne.jp/rpc/"
#define APIURL_269G             "http://269g.jp/rpc"
#define APIURL_BLOGGER          "http://www.blogger.com/api"
#define APIURL_AMEBLO           "http://ameblo.jp/xmlrpc.php"
#define APIURL_SWEETBOX         "http://www.sweetbox.ws/api/xmlrpc"
#define APIURL_FC2BLOG          "http://blog.fc2.com/xmlrpc.php"
#define APIURL_DTIBLOG          "http://blog.dtiblog.com/xmlrpc.php"
#define APIURL_GOOBLOG          "http://blog.goo.ne.jp/xmlrpc.php"
#define APIURL_MSNSPACES        "https://storage.msn.com/storageservice/MetaWeblog.rpc"
#define APIURL_JUGEM_X          "http://$.jugem.jp/admin/xmlrpc.php"
#define APIURL_DRECOMBLOG_X     "http://blog.drecom.jp/api/xmlrpc"
#define APIURL_YAPLOG_X         "http://www.yaplog.jp/xmlrpc"
#define APIURL_WEBRY_X          "https://bblog.sso.biglobe.ne.jp/ap/xmlrpc"

#define APIURL_COUSAGI          "http://www.yomiusa.net/api/api.cgi"
#define APIURL_HATENA           "http://d.hatena.ne.jp/xmlrpc"

/* Atom API エンドポイント */
/*
 *  The root endpoints for weblogs, photo albums, and TypeLists are
 *  as follows:
 *      Weblogs: http://www.typepad.com/t/atom/weblog
 *      Photo Albums: http://www.typepad.com/t/atom/gallery
 *      TypeLists: http://www.typepad.com/t/atom/lists
 *        (see also: http://sixapart.com/developers/atom/typepad/)
 */
#define ATOMURL_TYPEPAD         "http://www.typepad.com/t/atom/weblog"
#define ATOMURL_TYPEPADJAPAN    "http://www.typepad.jp/t/atom/weblog"
#define ATOMURL_TYPEPADFRANCE   ATOMURL_TYPEPAD
#define ATOMURL_TYPEPADGERMANY  ATOMURL_TYPEPAD
#define ATOMURL_COCOLOG         "https://app.cocolog-nifty.com/t/atom/weblog"
#define ATOMURL_COCOLOGFREE     "https://app.f.cocolog-nifty.com/t/atom/weblog"
#define ATOMURL_BLOGZINE        "http://app.blog.ocn.ne.jp/t/atom/weblog"
#define ATOMURL_LIVEDOOR        "http://blog.livedoor.com/atom"
#define ATOMURL_LIVEDOOR_200507 "http://cms.blog.livedoor.com/atom" /* 2005年7月以降 */
#define ATOMURL_LOVELOG         "http://blog.dion.ne.jp/atom"
#define ATOMURL_BLOGGER         "https://www.blogger.com/atom"
#define ATOMURL_SONET           "http://blog.so-net.ne.jp/_atom/blog"   /* 記事用 */
#define ATOMURL_SONET_IMAGE     "http://blog.so-net.ne.jp/_atom/image"  /* 画像用 */
#define ATOMURL_AMEBLO          "http://ameblo.jp:80/servlet/_atom/blog"    /* 記事用 */
#define ATOMURL_AMEBLO_IMAGE    "http://ameblo.jp:80/servlet/_atom/image"   /* 画像用 */
#define ATOMURL_VOX             "http://www.vox.com/atom"
#define ATOMURL_HATENADIARY     "http://d.hatena.ne.jp/{hatenaID}/atom/blog"

#define APIURL_BLOGGER_GDATA    "https://www.blogger.com/feeds"     /* GData API          */
#define APIURL_VOX_DEVELOPERS   "http://www.vox.com/services/api"   /* Vox developers API */

/* その他 エントリポイント */
#define APIURL_TUMBLR_WRITE     "http://www.tumblr.com/api/write"   /* tumblr 投稿用 */
#define APIURL_TUMBLR_ACOUNT    "http://www.tumblr.com/api/authenticate"
                                                      /* tumblr アカウント情報取得用 */

/* blog 毎のこまごまとした定義 */
#define JUGEMTYPE_OLD   1   /* β版時代からの無料サービス xxx.jugem.cc */
#define JUGEMTYPE_NEW   2   /* 正式版以降                 xxx.jugem.jp */

/* XML宣言 */
#define XML_STATEMENT   "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"

/* 文字コード */
#define CHARSET_UNKNOWN     0   /* 不明        */
#define CHARSET_SHIFTJIS    1   /* Shift_JIS   */
#define CHARSET_EUCJP       2   /* EUC-JP      */
#define CHARSET_ISO2022JP   3   /* ISO-2022-JP */
#define CHARSET_UTF8        4   /* UTF-8       */

typedef int (__cdecl *CONF_FUNC)( int            *useProxy,
                                  char           *proxyServer,
                                  unsigned short *proxyPort,
                                  char           *proxyUserName,
                                  char           *proxyPassword );

#ifdef  XMLRPC_EXPORTS
#ifdef  USE_APIKEY_H
#include "apiKey.h"
#else
#define BULKFEEDS_API_KEY       "--------------------------------"
#define AMAZON_SUBSCRIPTION_ID  "--------------------"
#define AMAZON_ASSOCIATE_ID     "-----------"
#define RAKUTEN_DEVELOPER_ID    "--------------------------------"
#define RAKUTEN_AFFILIATE_ID    "--------.--------"
#define RAKUTEN_AFFILIATE_ID2   "--------.--------.--------.--------"
#endif

/* データ定義 */
typedef struct sockaddr_in  SOCKADDR_IN;
typedef unsigned short      ushort;

typedef struct  xmlRPCparameter {
    int         initialized;                /* 初期化済みか否か             */
    SOCKADDR_IN saddrHTTPremote;            /* sockaddr structure for httpd */
    DWORD       scdHTTP;                    /* socket descriptor  for httpd */
    char        *sndHTTP;   /* 送信用バッファ (初期サイズ: SND_BUFFER_SIZE) */
    char        rcvHTTP[RCV_BUFFER_SIZE + 1];         /* 受信用バッファ     */
    int         sndHTTPBufferSize;                    /* 送信バッファサイズ */
    int         rcvHTTPbufferSize;                    /* 受信バッファサイズ */
    int         sndHTTPmessageSize;                   /* 送信電文サイズ     */
    int         rcvHTTPmessageSize;                   /* 受信電文サイズ     */

    char        userName[MAX_PATH];         /* blog投稿用ユーザ名           */
    char        password[MAX_PATH];         /* blog投稿用パスワード         */
    int         blogKind;                   /* blog種別                     */
    BOOL        useSSL;                     /* https, http のどちらを使うか */
    BOOL        recoverySSL;                /* https 時のリカバリモード     */
    void        *workArea1;        /* 内部作業用情報格納領域へのポインタ #1 */
    void        *workArea2;        /* 内部作業用情報格納領域へのポインタ #2 */

    char        webServer[MAX_SERVERNAME];
                                /* XML-RPC リクエスト送信先 Webサーバ URLの */
                                /* うち「サーバ名」部分                     */
    char        webPage[MAX_WEBPAGENAME];
                                /* XML-RPC リクエスト送信先 Webサーバ URLの */
                                /* うち「ファイル名」部分                   */

    char        proxyServer[MAX_SERVERNAME];        /* proxy サーバ URL     */
    ushort      proxyPort;                          /* proxy ポート番号     */
    char        proxyUserName[MAX_NAMELEN + 1];     /* proxy サーバユーザ名 */
    char        proxyPassword[MAX_NAMELEN + 1];   /* proxy サーバパスワード */
    char        proxyCookie[MAX_COOKIE_LEN];      /* proxy サーバ用クッキー */

    BOOL        useProxy;                           /* proxy を使うか否か   */
    CONF_FUNC   confirmProxyInfo;
                            /* proxyを使うか否か確認する関数(を別途、独自に */
                            /* 用意する場合に使用)                          */
    BOOL        needToCheckProxyInfo;/* proxy情報の設定が間違っている可能性 */
    BOOL        verbose;      /* if TRUE, enabled verbose mode              */
    FILE        *verboseFp;   /* if not NULL, output to stream as verboseFp */
#if defined (_DEBUG) || defined (CHECK_DETAIL)
    BOOL        dump;           /* if TRUE, dump received data             */
    FILE        *dumpFp;        /* if not NULL, output to stream as dumpFp */
#endif
    BOOL        active;                                 /* http通信中か否か */
    CRITICAL_SECTION    critic;                               /* 排他制御用 */
    DWORD       threadID;                     /* http通信中のスレッドのID   */
    int         timedoutTime;                 /* http タイムアウト時間 (秒) */
    long        startup;                      /* アプリケーション起動日時   */
    ushort      statusCode;       /* 直前の http 通信結果(ステータスコード) */

#define MAX_LLLEN   MAX_LOGICALLINELEN
    char        dataDir[MAX_PATH];  /* データファイル格納先ディレクトリ名   */
    char        userAgent[MAX_LLLEN * 2];/* 明示的に指定する User-Agent の値*/
    char        referer[MAX_URLLENGTH_MAX];/* 明示的に指定する Referer の値 */
    DWORD       languageCode;                                       /* 言語 */
    size_t      binSize;                                /* 受信データサイズ */
    char        keywordList[MAX_PATH];
                              /* はてなダイアリーキーワードリストファイル名 */
    char        amazonSubscriptionID[MAX_LLLEN];/* Amazon subscription ID   */
    char        amazonAssociateID[MAX_LLLEN];   /* Amazon associate ID      */
    char        bulkfeedsAPIkey[MAX_LLLEN];     /* Bulkfeeds API Key        */
    char        rakutenDeveloperID[MAX_LLLEN];  /* 楽天デベロッパーID       */
    char        rakutenAffiliateID[MAX_LLLEN];  /* 楽天アフィリエイトID(旧) */
    char        rakutenAffiliateID2[MAX_LLLEN]; /* 楽天アフィリエイトID(新) */
#ifdef  USE_AUTHORIZATION_OAUTH
    char        oauth_header[MAX_OAUTH_HEADER_LEN];
#endif
#undef  MAX_LLLEN
}   XMLRPC, *XMLRPC_t;

extern XMLRPC_t xmlrpc_p;
#endif  /* XMLRPC_EXPORTS */

/* blog 情報テーブル */
typedef struct blogInfoTable {
    int     blogType;       /* blog種別                       */
    int     charSet;        /* 文字コード                     */
    char    *xmlEndpoint;   /* XML-RPC API エンドポイント URL */
    char    *atomEndpoint;  /* Atom API エンドポイント URL    */
}   BLOGINFOTBL, *BLOGINFOTBL_t;

#ifdef  XMLRPC_EXPORTS
extern BLOGINFOTBL  blogInfoTbl[];
#endif  /* XMLRPC_EXPORTS */

/* content 構造体 */
typedef struct content {
    char    title[MAX_LOGICALLINELEN];      /* 記事の件名           */
    char    description[MAX_CONTENT_SIZE];  /* 記事の本文           */
    char    dateCreated[MAX_DATELENGTH];    /* 記事が投稿された日時 */

    /* 以下、MovableType 拡張部 */
    int     mt_allow_comments;              /* コメントを受け入れるか否か */
    int     mt_allow_pings;     /* トラックバックPingを受け入れるか否か   */
    char    mt_convert_breaks[MAX_BOOLEANLENGTH];
                                            /* 記事本文の改行の扱い方     */
    char    mt_text_more[MAX_CONTENT_SIZE]; /* 追記                       */
    char    mt_excerpt[MAX_CONTENT_SIZE];   /* 概要                       */
    char    mt_keywords[MAX_LOGICALLINELEN];/* キーワード                 */
    int     numOfTrackbacks;/* 送信しようとしているトラックバック Ping 数 */
    char    mt_tb_ping_urls[MAX_PINGS][MAX_LOGICALLINELEN];
                     /* 送信しようとしているトラックバック Ping の URL 群 */

    /* 以下、Windows Live Spaces 拡張部 (ウェブリブログでも使用) */
    int     numOfCategories;                    /* 指定するカテゴリの数   */
    char    categories[MAX_CATEGORIES][MAX_CATNAMELENGTH];
                                                /* カテゴリ(複数指定可能) */
}   CONTENT, *CONTENT_t;


/* file 構造体 */
typedef struct fileInfo {
    unsigned char   *bits;          /* base64 で符号化されたファイルの中身 */
    char            name[MAX_PATH]; /* ファイル名                          */
    char            type[MAX_LOGICALLINELEN];/* ファイル種別 Content-type: */
}   FILEINF, *FILEINF_t;


/* category 構造体 #1 */
typedef struct category {
    char    categoryId[MAX_CATIDLENGTH];    /* カテゴリID         */
    int     isPrimary;                      /* 第一カテゴリか否か */
}   CATEGORY, *CATEGORY_t;

/* category 構造体 #2 */
typedef struct categoryInfo {
    char    categoryId[MAX_CATIDLENGTH];    /* カテゴリID (英数字)        */
    char    categoryName[MAX_CATNAMELENGTH];/* カテゴリの名前 (漢字も OK) */
    int     isPrimary;                      /* 第一カテゴリか否か         */
}   CATINF, *CATINF_t;


/* blog 情報構造体 */
typedef struct blogInfo {
    char    url[MAX_URLLENGTH];             /* blog トップページ URL */
    char    blogID[MAX_BLOGIDLENGTH + 1];   /* blog ID               */
    char    blogName[MAX_BLOGNAMELENGTH];   /* blog の名前           */
}   BLOGINF, *BLOGINF_t;

/* ユーザ情報構造体 */
typedef struct  userInfo    {
    char    userid[MAX_USERIDLEN];  /* ユーザID             */
    char    firstname[MAX_NAMELEN]; /* 名                   */
    char    lastname[MAX_NAMELEN];  /* 姓                   */
    char    nickname[MAX_NAMELEN];  /* ニックネーム         */
    char    email[MAX_PATH];        /* email アドレス       */
    char    url[MAX_URLLENGTH];     /* ホームページアドレス */
}   USERINF, *USERINF_t;

/* content 情報構造体 #1 */
typedef struct  contentInfo {
    int     yy;                         /* 投稿日時 年 */
    int     mm;                         /* 投稿日時 月 */
    int     dd;                         /* 投稿日時 日 */
    int     HH;                         /* 投稿日時 時 */
    int     MM;                         /* 投稿日時 分 */
    int     SS;                         /* 投稿日時 秒 */
    char    userid[MAX_USERIDLEN];      /* 投稿者名    */
    char    postid[MAX_POSTIDLENGTH];   /* 記事ID      */
    char    content[MAX_CONTENT_SIZE];  /* 記事本文    */
}   CONTENTINF, *CONTENTINF_t;


/* content 情報構造体 #2 */
typedef struct  contentInfoEx   {
    int     yy;                             /* 投稿日時 年   */
    int     mm;                             /* 投稿日時 月   */
    int     dd;                             /* 投稿日時 日   */
    int     HH;                             /* 投稿日時 時   */
    int     MM;                             /* 投稿日時 分   */
    int     SS;                             /* 投稿日時 秒   */
    char    userid[MAX_USERIDLEN];          /* 投稿者名      */
    char    postid[MAX_POSTIDLENGTH];       /* 記事ID        */
    char    description[MAX_CONTENT_SIZE];  /* 記事本文      */
    char    title[MAX_LOGICALLINELEN];      /* 記事題名      */
    char    link[MAX_URLLENGTH];            /* 記事URL       */
    char    permaLink[MAX_URLLENGTH];       /* 記事permalink */

    /* ここから下は、MovableType独自の拡張 (本来の metaWeblog API には存在 */
    /* しない)                                                             */
    char    mt_excerpt[MAX_CONTENT_SIZE];   /* 概要          */
    char    mt_text_more[MAX_CONTENT_SIZE]; /* 追記          */
    int     mt_allow_comments;              /* コメントを受け付けるか否か */
    int     mt_allow_pings;           /* トラックバックを受け付けるか否か */
    char    mt_convert_breaks[MAX_BOOLEANLENGTH];        /* 改行の扱い方  */
    char    mt_keywords[MAX_LOGICALLINELEN];/* キーワード    */

    /* 以下、Windows Live Spaces 拡張部 (ウェブリブログでも使用) */
    int     numOfCategories;                    /* 指定するカテゴリの数   */
    char    categories[MAX_CATEGORIES][MAX_CATNAMELENGTH];
                                                /* カテゴリ(複数指定可能) */
    BOOL    publish;                            /* 公開状態               */
}   CONTENTINFEX, *CONTENTINFEX_t;
            /* 通常、「記事URL」と「記事permalink」は同じ URL になる (ど  */
            /* ういうときに別のものになるのか不明)                        */

/* category 情報構造体 */
typedef struct categoryListInfo {
    char    categoryId[MAX_CATIDLENGTH];    /* カテゴリID (英数字)        */
    char    categoryName[MAX_CATNAMELENGTH];/* カテゴリの名前 (漢字も OK) */
}   CATLISTINF, *CATLISTINF_t;

/* 記事一覧 */
typedef struct postInfo {
    int     yy;                         /* 投稿日時 年 */
    int     mm;                         /* 投稿日時 月 */
    int     dd;                         /* 投稿日時 日 */
    int     HH;                         /* 投稿日時 時 */
    int     MM;                         /* 投稿日時 分 */
    int     SS;                         /* 投稿日時 秒 */
    char    userid[MAX_USERIDLEN];      /* 投稿者名    */
    char    postid[MAX_POSTIDLENGTH];   /* 記事ID      */
    char    title[MAX_LOGICALLINELEN];  /* 記事題名    */
}   POSTINF, *POSTINF_t;

/* フィルタ情報 */
typedef struct filterInfo   {
    char    key[MAX_LOGICALLINELEN];    /* キー */
    char    label[MAX_LOGICALLINELEN];  /* 説明 */
}   FILTERINF, *FILTERINF_t;

/* トラックバック情報構造体 */
typedef struct trackbackInfo    {
    char    pingTitle[MAX_LOGICALLINELEN];  /* 記事題名     */
    char    pingURL[MAX_URLLENGTH];         /* 記事URL      */
    char    pingIP[20]; /* trackback ping 送信元 IPアドレス */
}   TBINF, *TBINF_t;

/* 関数プロトタイプ宣言 */
char    *jis2euc( const char *p );
char    *sjis2euc( const char *p );
char    *sjis2utf( const char *p );
char    *utf2euc( const char *p );
char    *euc2sjis( const char *p );
char    *utf2sjis( const char *p );
char    *iso8859_1toUtf8( const char *p );
char    *euc2sjisEx( const char *p );
char    *regular( char *s );
char    *replaceEntityStrings( const char *p, int charSet );
char    *encodeURL( const char *p );
char	*encodeURLi( const char *pp, BOOL lowercase );
char    *encodeURL2( const char *p ); /* &#xxx; 素通し版 */
char	*encodeURLex( const char *pp );
char	*encodeURLex2(
                const char *p /* (I) UTF-8 文字列 */
            );
char	*encodeURLex3(
                const char *p /* (I) EUC-JP 文字列 */
            );
char	*encodeURLex4(
                const char *p /* (I) Shift_JIS 文字列 */
            );
char    *decodeURL( const char *p );
char    *translateURL( const char *p );
char    *convUnicode( unsigned long code ); /* 数値参照のデコード */
int     strncmpi( const char *, const char *, size_t len );

char    *getNonce( const char *preNonce );
                            /* Atom PP 以外でも使える Nonce 生成処理 */

int initializeSocket( void );   /* ソケット関連初期化 */
int finalizeSocket( void );     /* ソケット関連後始末 */

#define MAX_NUMBER_OF_ACTIVITY_CHECK    20
#define PERIOD_OF_ACTIVITY_CHECK        1000
BOOL    isActive( void );               /* http通信中か否か       */
void    setActive( BOOL active );       /* for internal use only  */
void    setTimeoutTime( int timeout );  /* タイムアウト時間の変更 */

#define RBUF_MAGIC1 0xBEAFCAFE
#define RBUF_MAGIC2 0xDEADBEEF

#define setUpReceiveBuffer( p, sz )     \
    memset( (p), 0x00, (sz) );          \
    *(size_t *)(p)       = RBUF_MAGIC1; \
    *((size_t *)(p) + 1) = (sz);        \
    *((size_t *)(p) + 2) = RBUF_MAGIC2;

#define getReceiveBufferSize( p, sz )   \
    if ( (*(size_t *)(p)       == RBUF_MAGIC1) &&   \
         (*((size_t *)(p) + 2) == RBUF_MAGIC2)    )  { \
        (sz) = *((size_t *)(p) + 1);    \
        if ( (sz) > 1 ) \
            (sz)--; \
    }   \
    else    \
        (sz) = 0;   \
    *(size_t *)(p)       = 0;   \
    *((size_t *)(p) + 1) = 0;   \
    *((size_t *)(p) + 2) = 0;

#define setUpSendBuffer( p, sz, newP )  \
    *(size_t *)(p)       = RBUF_MAGIC2; \
    *((size_t *)(p) + 1) = (sz);        \
    *((size_t *)(p) + 2) = RBUF_MAGIC1; \
    (newP) = (char *)((size_t *)(p) + 3);

#define getSendBufferSize( p, sz, newP )   \
    if ( (*(size_t *)(p)       == RBUF_MAGIC2) &&   \
         (*((size_t *)(p) + 2) == RBUF_MAGIC1)    )  { \
        (sz) = *((size_t *)(p) + 1);    \
        (newP) = (char *)((size_t *)(p) + 3);   \
    }   \
    else {  \
        (sz) = 0;   \
        (newP) = (p); \
    }

#define getSendBufferPointer( p, newP ) \
    (newP) = (char *)((size_t *)(p) + 3);


int
httpPost( const char *webServer, const char *webPage,
          const char *mimeType,
          const char *request,   char *response );
                                /* http POST メソッド実行 */
int
httpPostBASIC( const char *webServer, const char *webPage,
               const char *userName,  const char *password,
               const char *mimeType,
               const char *request,   char *response );
                                /* http POST メソッド実行(BASIC認証対応版) */

int
httpPostEx( char *request, char *response );
                /* http POST メソッド実行 (文字化け検出時再取得機能付き) */

int
httpPostEx2( const char *webServer, const char *webPage,
             const char *request,   char *response,
             const char *wsse );
                                /* http POST メソッド実行 (Atom API 用) */

int
httpPostWithSession( const char *webServer, const char *webPage,
                     const char *mimeType,
                     const char *sndBody, char *rcvBody, char *cookie,
                     char *webServerRedirected, char *cookieRedirected );
                            /* http POST メソッド実行 (セッション継続) */

int
httpGet( const char *webServer, const char *webPage,
         char *rcvBody, FILE *output, int printHead,
         const char *wsse,
         char *p3p, char *cookie,
         char *webServerRedirected, char *cookieRedirected );
                                /* http GET メソッド実行  */
int
httpGetBASIC( const char *webServer, const char *webPage,
              const char *userName,  const char *password,
              char *rcvBody, FILE *output, int printHead,
              const char *wsse,
              char *p3p, char *cookie,
              char *webServerRedirected, char *cookieRedirected );
                                /* http GET メソッド実行(BASIC認証対応版) */

int
httpGetEx( const char *webServer, const char *webPage,
           char *rcvBody, FILE *output, int printHead,
           const char *wsse );
                                /* http GET メソッド実行 (Atom API 用) */

int
httpGetFile( const char *uri, const char *filename,
             int printHead );
                                /* http GET によるファイルの取得 */
int
httpGetFileBASIC( const char *uri, const char *filename,
                  const char *userName, const char *password,
                  int printHead );
                        /* http GET によるファイルの取得(BASIC認証対応版) */
int
httpGetBuffer( const char *uri,
               char *rcvBuf, int printHead );
                                /* http GET による文字列の取得 */
int
httpGetBufferBASIC( const char *uri,
                    const char *userName, const char *password,
                    char *rcvBuf, int printHead );
                        /* http GET による文字列の取得(BASIC認証対応版) */

int
httpPutBASIC( const char *webServer, const char *webPage,
              const char *userName,  const char *password,
              const char *mimeType,
              const char *request,   char *response,
              const char *wsse );
                                /* http PUT メソッド実行(BASIC認証対応版) */
int
httpPutEx( const char *webServer, const char *webPage,
           const char *request,   char *response,
           const char *wsse );
                                /* http PUT メソッド実行 (Atom API 用) */

int
httpDeleteBASIC( const char *webServer, const char *webPage,
                 const char *userName,  const char *password,
                 char *rcvBody, FILE *output, int printHead,
                 const char *wsse );
                                /* http DELETE メソッド実行(BASIC認証対応版)*/
int
httpDeleteEx( const char *webServer, const char *webPage,
              char *rcvBody, FILE *output, int printHead,
              const char *wsse );
                                /* http DELETE メソッド実行 (Atom API 用) */

int
httpGetBufferWithSession( const char *uri,
                          char       *rcvBuf,
                          int        printHead,
                          const char *wsse,
                          char       *p3p,  /* P3P: Platform for Privacy */
                                            /*      Preferences          */
                          char       *cookie,
                          char       *webServerRedirected,
                          char       *cookieRedirected );
                            /* http GET による文字列の取得 (セッション継続) */

int openHTTPS( void );                              /* SSL 開始       */
int closeHTTPS( void );                             /* SSL 終了       */
int sendHTTPS( const char *request, size_t size );  /* SSL データ送信 */
int recvHTTPS( char *response, size_t size );       /* SSL データ受信 */


char    *
http_get( const char *url, char *response );
char    *
http_getEx( const char *url, char *response, char *cookie );
char    *
http_getEx2( const char *url,
             char *response, char *cookie,
             char *webServerRedirected, char *cookieRedirected );

char    *
http_getBASIC( const char *url,
               const char *userName, const char *password,
               char *response );    /* http_get() の BASIC認証対応版   */
char    *
http_getBASICEx( const char *url,
                 const char *userName, const char *password,
                 char *response, char *cookie );
                                    /* http_getEx() の BASIC認証対応版 */

char    *
http_head( const char *url, char *response );

char    *
http_headEx( const char *url, char *response, char *cookie );

char    *
http_headBASIC( const char *url,
                const char *userName, const char *password,
                char *response );   /* http_head() の BASIC認証対応版  */

char    *
http_delete( const char *url, char *response );

char    *
http_post( const char *url, const char *mimeType, const char *request,
           char *response );
char    *
http_postEx( const char *url, const char *mimeType, const char *request,
             char *response, char *cookie );
char    *
http_postEx2( const char *url, const char *mimeType, const char *request,
              char *response, char *cookie,
              char *webServerRedirected, char *cookieRedirected );
char    *
http_postBASIC( const char *url,
                const char *userName, const char *password,
                const char *mimeType, const char *request,
                char *response );   /* http_post() の BASIC認証対応版  */

char    *
http_put( const char *url, const char *mimeType, const char *filename,
          char *response );

char    *
http_deleteBASIC( const char *url,
                  const char *userName, const char *password,
                  const char *mimeType, const char *request,
                  char *response );   /* http_delete() の BASIC認証対応版 */

// for Atom PP
char    *
http_getW( const char *url, const char *wsse,
           const char *userName, const char *password,
           char *response );

char    *
http_postW( const char *url, const char *wsse,
            const char *userName, const char *password,
            const char *request, char *response );

char    *
http_putW( const char *url, const char *wsse,
           const char *userName, const char *password,
           const char *request, char *response );

char    *
http_deleteW( const char *url, const char *wsse,
              const char *userName, const char *password,
              char *response );


#if defined(WIN32) && !defined(__LCC__)
#define sleep   Sleep
#endif

/* OpenSSL 版数取得 */
char    *
getOpenSSLversion( char *buf, size_t bufSize );

/* iconv 版数取得 */
char    *
getIconvVersion( char *buf, size_t bufSize );

/* 本 ライブラリ で提供する API */
void    setVerbose( int verbose, FILE *fp );    /* verbose モード切替       */
void    setDump( int dump, FILE *dumpFp );      /* dump モード切替          */
void    setUseProxy( int useProcy );            /* proxy モード切替         */
void    setUserAgent( const char *userAgent );  /* User-Agent 設定変更      */
void    setReferer( const char *referer );      /* Referer 設定変更         */
void    setOAuthHeader( const char *header );   /* for OAuth                */
void    setUserInfo( const char *userName, const char *password );
                                                /* ユーザ情報設定           */
void    setTargetURL( const char *targetURL );  /* webServer, webPage 設定  */
void    setBlogKind( int blogKind );            /* blog 種別設定            */

void    setDataDir( const char *dirname );
                                /* データファイル格納先ディレクトリ名設定   */
void    setKeywordList( const char *filename );
                                /* はてなダイアリーキーワードファイル名設定 */

void
getProxyInfo(
    int            *useProxy,
    char           *proxyServer,
    unsigned short *proxyPort,
    char           *proxyUserName,
    char           *proxyPassword );    /* proxy 情報取得 */

unsigned short
getStatusCode( void );      /* 直前の http 通信結果(ステータスコード)の取得 */


/***** weblogUpdates API *****/
/* update ping 送信
 *      weblogUpdates.ping
 *          説明: update ping (blog更新通知) を送信します
 *          引数: String weblogname,
 *                String weblogURL
 *          返り値: 成功すると メンバー flerror の値が 0 (false) である構造体
 *                  が返ります。
 *                  失敗すると メンバー flerror の値が 1 (true)  である構造体
 *                  が返ります。
 *          参考: http://www.xmlrpc.com/weblogsCom
 *
 *    sendUpdatePing
 *      引数:
 *          char *weblogName    (I) blog の名前 (Shift_JIS)
 *          char *weblogURL     (I) blog の URL
 *      戻り値:
 *          TRUE    update ping 登録成功
 *          FALSE   update ping 登録失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) weblogName で指定する blog の名前については、将来 UTF-8 に
 *              する可能性あり
 *          (2) blog の URL に URL エンコードすべき文字が含まれる場合は、
 *              あらかじめ URL エンコードしておくこと
 */
BOOL
sendUpdatePing( const char *weblogName,
                const char *weblogURL );

/* weblogUpdates.ping の拡張版 weblogUpdates.extendedPing                   */
/*   Google blog search で採用                                              */
/*     詳細は http://www.google.co.jp/help/blogsearch/pinging_API.html 参照 */
BOOL
sendUpdateExtendedPing( const char *weblogName, // (I) blog の名前 [Shift_JIS]
                        const char *weblogURL,  // (I) blog の URL
                        const char *targetURL,  // (I) ping 対象の URL
                        const char *feedURL );  // (I) RSS/Atom フィードの URL

/*****  blogger API *****/
/* 新規記事の投稿
 *      blogger.newPost
 *          説明: 新しい記事をつくります．また，公開することもできます．
 *          引数: String  appkey,
 *                String  blogid,
 *                String  username,
 *                String  password,
 *                String  content,
 *                boolean publish
 *          返り値: 成功すると，String postid が新しい記事の ID 値として
 *                  得られます．
 *                  失敗したら，fault が返ります．
 *
 *    newPost
 *      引数:
 *          char *blogID        (I) blog ID
 *          char *userName      (I) ユーザ名
 *          char *password      (I) パスワード
 *          char *content       (I) 記事内容 [UTF-8]
 *          BOOL publish        (I) 投稿状態 (FALSE: 下書き / TRUE: 公開)
 *          char *postID        (O) 投稿後の記事ID
 *      戻り値:
 *          TRUE    投稿成功
 *          FALSE   投稿失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) 記事内容のサイズは SND_BUFFER_SIZE の値 (正確には 
 *              SND_BUFFER_SIZE から「http ヘッダのサイズ分」を引いた値)  を
 *              超えないこと。サーバによっては、あまり大きな記事を受け付ける
 *              ことができないことが予想されるので、概ね64KB未満であることが
 *              望ましい
 *          (3) 記事内容 に URL エンコードすべき文字が含まれる場合は、本関数
 *              内で URL エンコードを行なうので、あらかじめ URL エンコードし
 *              ておく必要はない。なお、URL エンコードを行なった結果、記事内
 *              容のサイズが SND_BUFFER_SIZE より大きくなってしまった場合は、
 *              投稿に失敗する
 *          (4) 記事の投稿に成功した場合、postID  の指示する領域に記事ID (文
 *              字列) を格納する
 *          (5) 「下書き」の概念のない blog ツールに対しては、publish の値は
 *              意味を持たない(常に「公開」状態での投稿となる)
 */

BOOL
newPost( const char *blogID,
         const char *userName,
         const char *password,
         const char *content,
         BOOL       publish,
         char       *postID );


/* 既存記事の上書き投稿
 *      blogger.editPost
 *          説明: 既にある記事の情報を編集します．
 *          引数: String  appkey,
 *                String  postid,
 *                String  username,
 *                String  password,
 *                String  content,
 *                boolean publish
 *          返り値: 成功すると true が，失敗すると fault が返ります．
 *
 *    editPost
 *      引数:
 *          char *postID        (I) 記事ID
 *          char *userName      (I) ユーザ名
 *          char *password      (I) パスワード
 *          char *content       (I) 記事内容 [UTF-8]
 *          BOOL publish        (I) 投稿状態 (FALSE: 下書き / TRUE: 公開)
 *      戻り値:
 *          TRUE    上書き投稿成功
 *          FALSE   上書き投稿失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) 記事内容のサイズは SND_BUFFER_SIZE の値 (正確には 
 *              SND_BUFFER_SIZE から「http ヘッダのサイズ分」を引いた値)  を
 *              超えないこと。サーバによっては、あまり大きな記事を受け付ける
 *              ことができないことが予想されるので、概ね64KB未満であることが
 *              望ましい
 *          (3) 記事内容 に URL エンコードすべき文字が含まれる場合は、本関数
 *              内で URL エンコードを行なうので、あらかじめ URL エンコードし
 *              ておく必要はない。なお、URL エンコードを行なった結果、記事内
 *              容のサイズが SND_BUFFER_SIZE より大きくなってしまった場合は、
 *              投稿に失敗する
 *          (4) 「下書き」の概念のない blog ツールに対しては、publish の値は
 *              意味を持たない(常に「公開」状態での投稿となる)。また、すでに
 *              「公開」状態で投稿した記事を編集する場合は、blog ツールによっ
 *              ては下書きでの投稿を指示しても「公開」状態のままとなることが
 *              ある
 *          (5) 記事の中身を全く変更していない場合でも、本関数により「公開」
 *              を指定すると、rebuild が実行される(実行されない blog ツール
 *              もある)
 */

BOOL
editPost( const char *postID,
          const char *userName,
          const char *password,
          const char *content,
          BOOL       publish );


/* 既存記事の削除
 *      blogger.deletePost
 *          説明: 記事を削除します．
 *          引数: String  appkey,
 *                String  postid,
 *                String  username,
 *                String  password,
 *                boolean publish
 *          返り値: 成功すると true，失敗すると fault が返ります．
 *
 *    deletePost
 *      引数:
 *          char *postID        (I) 記事ID
 *          char *userName      (I) ユーザ名
 *          char *password      (I) パスワード
 *          BOOL publish        (I) 投稿状態 (FALSE: 下書き / TRUE: 公開)
 *      戻り値:
 *          TRUE    削除成功
 *          FALSE   削除失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) publish の値は無視される
 */

BOOL
deletePost( const char *postID,
            const char *userName,
            const char *password,
            BOOL       publish );


/* 指定件数分の最新記事の取得
 *      blogger.getRecentPosts 
 *          説明: 最新の記事をシステムからとってきます．
 *          引数: String appkey,
 *                String blogid,
 *                String username,
 *                String password,
 *                int    numberOfPosts
 *          返り値: 成功すると，構造体の配列が返ってきます． 
 *                  構造体には，
 *                      ISO.8601 dateCreated,
 *                      String   userid,
 *                      String   postid,
 *                      String   content
 *                  が含まれます．(順は不同)
 *                  失敗すると，fault が返ります．
 *              注意: dateCreated は，blogid の weblog においての時間帯に
 *                    なっています．
 *
 *    getRecentPosts
 *      引数:
 *          char       *blogID        (I) blog ID
 *          char       *userName      (I) ユーザ名
 *          char       *password      (I) パスワード
 *          int        *numOfEntries  (I) 取得する記事情報数
 *                                    (O) 実際に取得した記事情報数
 *          CONTENTINF *contentInfo   (O) 取得した記事情報
 *      戻り値:
 *          0       記事が存在しない、取得失敗、送信失敗、その他のエラー発生
 *          1 以上  取得に成功した記事情報の数
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) *numOfEntries で指定した数の分だけ、最新の記事から過去の記事
 *              へ遡る方向に記事情報を取得する
 *          (3) 実際に取得に成功した記事情報の数を *numOfEntries に設定する
 */

int
getRecentPosts( const char *blogID,
                const char *userName,
                const char *password,
                int        *numOfEntries,
                CONTENTINF *contentInfo );


/* blog 情報の取得
 *     blogger.getUsersBlogs 
 *          説明: 書き手さんが投稿できる weblog の群れを返します．
 *          引数: String appkey,
 *                String username,
 *                String password
 *          返り値: 成功すると，構造体の配列が返ってきます． 
 *                 構造体には，
 *                     String url,
 *                     String blogid,
 *                     String blogName
 *                 が含まれます． 
 *                 失敗すると，fault が返ります．
 *
 *    getUsersBlogs
 *      引数:
 *          char *userName  (I) ユーザ名
 *          char *password  (I) パスワード
 *          char *response  (O) 取得した blog 情報 [XML]
 *      戻り値:
 *          TRUE    取得成功
 *          FALSE   取得失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) response の示す領域は本関数の呼び出し元であらかじめ確保してお
 *              くこと
 *          (3) response の示す領域には  blogger.getUsersBlogs に対するサーバ
 *              からの応答結果 (XML) がそのまま格納される。XML ではなく、blog
 *              情報が欲しい場合は、本関数を直接呼び出す代わりに本関数のラッパ
 *              getBlogID() または getBlogIDs() を呼び出すこと。
 *              getBlogID() は XML 中に最初に出現する blog の blog ID のみを抜
 *              き出し、getBlogIDs() は XML 中に含まれる全 blog の情報を抜き出
 *              す
 */

BOOL
getUsersBlogs( const char *userName,
               const char *password,
               char       *response );


/* ユーザ情報の取得
 *     blogger.getUserInfo 
 *          説明: 書き手さんの情報を返します．
 *          引数: String appkey,
 *                String username,
 *                String password
 *          返り値: 成功すると，構造体の配列が返ってきます． 
 *                  構造体には，
 *                      String userid,
 *                      String firstname,
 *                      String lastname,
 *                      String nickname,
 *                      String email,
 *                      String url
 *                  が含まれます． 
 *                  失敗すると，fault が返ります．
 *                      注意: firstname は，Movable Type のユーザ名のうち，最
 *                            初のスペースのところまでのものです． 
 *                            lastname は，最初のスペース以降のものです．
 *    getUserInfo
 *      引数:
 *          char    *userName      (I) ユーザ名
 *          char    *password      (I) パスワード
 *          int     numberOfUsers  (I) 取得するユーザ情報の数 
 *                                 (O) 実際に取得したユーザ情報の数
 *          USERINF *userInfo      (O) 取得したユーザ情報
 *      戻り値:
 *          0       取得失敗、送信失敗、その他のエラー発生
 *          1 以上  取得に成功したユーザ情報の数 (== ユーザ数)
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 */

int
getUserInfo( const char *userName,
             const char *password,
             int        *numberOfUsers,
             USERINF    *userInfo );


/*****  metaWeblog API  *****/
/* 新規記事の投稿
 *  metaWeblog.newPost 
 *      説明: 新しい記事をつくります． また，公開することもできます．
 *      引数: String  blogid,
 *            String  username,
 *            String  password,
 *            struct  content,
 *            boolean publish
 *        注意: content 構造体は，次のような標準的な項目を含みます: 
 *                  String   title,       記事の件名
 *                  String   description, 記事の本文
 *                  ISO.8601 dateCreated, 記事が投稿された日時
 *                  String[] categories,  (省略可) [Windows Live Spaces 用と
 *                                        して、新たに追加されたパラメータ。
 *                                        Movable Type ではこの引数には対応
 *                                        していない]
 *              それに加えて，Movable Type では次の7つの項目に値を入れて渡す
 *              ことができます: 
 *                  int      mt_allow_comments, allow_comments
 *                                              項目への値; (コメントを受け
 *                                              入れるか否か)
 *                  int      mt_allow_pings, allow_pings
 *                                              項目への値; (トラックバック
 *                                              Pingを受け入れるか否か)
 *                  String   mt_convert_breaks, convert_breaks
 *                                              項目の値; (記事本文の改行の
 *                                              扱い方)
 *                  String   mt_text_more,      追記の値; 
 *                  String   mt_excerpt,        概要の値;
 *                  String   mt_keywords,       キーワードの値;
 *                  array    mt_tb_ping_urls,   その記事に対するトラックバッ
 *                                              ク Ping の URL の群れ;
 *              です． 
 *              dateCreated を使うなら，ISO.8601 形式でないといけません．
 *              (省略した場合は現在時刻を指定したものとみなされる)
 *      返り値: 成功すると，String postid が新しい記事の ID 値として返ってき
 *              ます．
 *              失敗すると，fault です．
 *
 *    newPostEx
 *      引数:
 *          char    *blogID    (I) blog ID
 *          char    *userName  (I) ユーザ名
 *          char    *password  (I) パスワード
 *          CONTENT *content   (I) 記事情報
 *          BOOL    publish    (I) 投稿状態 (FALSE: 下書き / TRUE: 公開)
 *          char    *postID    (O) 投稿後の記事ID
 *      戻り値:
 *          TRUE    投稿成功
 *          FALSE   投稿失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) 記事内容(content->description, content->mt_text_more,
 *              content->mt_excerpt の合計)のサイズは SND_BUFFER_SIZE の値
 *              (正確には SND_BUFFER_SIZE から「http ヘッダのサイズ分」を引い
 *              た値)を超えないこと。サーバによっては、あまり大きな記事を受け
 *              付けることができないことが予想されるので、概ね 64KB未満である
 *              ことが望ましい
 *          (3) 記事内容 に URL エンコードすべき文字が含まれる場合は、本関数
 *              内で URL エンコードを行なうので、あらかじめ URL エンコードし
 *              ておく必要はない。なお、URL エンコードを行なった結果、記事内
 *              容のサイズが SND_BUFFER_SIZE より大きくなってしまった場合は、
 *              投稿に失敗する
 *          (4) 記事の投稿に成功した場合、postID  の指示する領域に記事ID (文
 *              字列) を格納する
 *          (5) 「下書き」の概念のない blog ツールに対しては、publish の値は
 *              意味を持たない(常に「公開」状態での投稿となる)
 */

BOOL
newPostEx( const char    *blogID,
           const char    *userName,
           const char    *password,
           const CONTENT *content,
           BOOL          publish,
           char          *postID );


/* 既存記事の上書き投稿
 *  metaWeblog.editPost 
 *      説明: 既にある記事の情報を更新します．
 *      引数: String  postid,
 *            String  username,
 *            String  password,
 *            struct  content,
 *            boolean publish
 *        注意: content 構造体は，次のような標準的な項目を含みます:
 *                  String   title,       記事の件名
 *                  String   description, 記事の本文
 *                  ISO.8601 dateCreated, 記事が投稿された日時． 
 *                  String[] categories,  (省略可) [Windows Live Spaces 用と
 *                                        して、新たに追加されたパラメータ。
 *                                        Movable Type ではこの引数には対応
 *                                        していない]
 *              それに加えて，Movable Type では次の7つの項目に値を入れて渡す
 *              ことができます．
 *                  int      mt_allow_comments, allow_comments
 *                                              項目への値; (コメントを受け
 *                                              入れるか否か)
 *                  int      mt_allow_pings, allow_pings
 *                                              項目への値; (トラックバック
 *                                              Pingを受け入れるか否か)
 *                  String   mt_convert_breaks, convert_breaks
 *                                              項目の値; (記事本文の改行の扱
 *                                              い方)
 *                  String   mt_text_more,      追記の値; 
 *                  String   mt_excerpt,        概要の値;
 *                  String   mt_keywords,       キーワードの値;
 *                  array    mt_tb_ping_urls,   その記事に対するトラックバック
 *                                              Ping の URL の群れ;
 *             です．dateCreated を使うなら，ISO.8601 形式でないといけません．
 *      返り値: 成功すると true が，失敗すると fault が返ります．
 *
 *    editPostEx
 *      引数:
 *          char    *postID    (I) 記事ID
 *          char    *userName  (I) ユーザ名
 *          char    *password  (I) パスワード
 *          CONTENT *content   (I) 記事情報
 *          BOOL    publish    (I) 投稿状態 (FALSE: 下書き / TRUE: 公開)
 *      戻り値:
 *          TRUE    投稿成功
 *          FALSE   投稿失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) 記事内容(content->description, content->mt_text_more,
 *              content->mt_excerpt の合計)のサイズは SND_BUFFER_SIZE の値
 *              (正確には SND_BUFFER_SIZE から「http ヘッダのサイズ分」を引い
 *              た値)を超えないこと。サーバによっては、あまり大きな記事を受け
 *              付けることができないことが予想されるので、概ね 64KB未満である
 *              ことが望ましい
 *          (3) 記事内容 に URL エンコードすべき文字が含まれる場合は、本関数
 *              内で URL エンコードを行なうので、あらかじめ URL エンコードし
 *              ておく必要はない。なお、URL エンコードを行なった結果、記事内
 *              容のサイズが SND_BUFFER_SIZE より大きくなってしまった場合は、
 *              投稿に失敗する
 *          (4) 「下書き」の概念のない blog ツールに対しては、publish の値は
 *              意味を持たない(常に「公開」状態での投稿となる)。また、すでに
 *              「公開」状態で投稿した記事を編集する場合は、blog ツールによっ
 *              ては下書きでの投稿を指示しても「公開」状態のままとなることが
 *              ある
 *          (5) 記事の中身を全く変更していない場合でも、本関数により「公開」
 *              を指定すると、rebuild が実行される(実行されない blog ツール
 *              もある)
 */

BOOL
editPostEx( const char    *postID,
            const char    *userName,
            const char    *password,
            const CONTENT *content,
            BOOL          publish );


/* 指定記事の取得
 *  metaWeblog.getPost 
 *      説明: 指定した投稿についての情報を返します．
 *      引数: String postid,
 *            String username,
 *            String password
 *      返り値: 成功すると，次の要素を含む構造体が返ってきます:
 *                  String   userid,
 *                  ISO.8601 dateCreated,
 *                  String   postid,
 *                  String   description,
 *                  String   title,
 *                  String   link,
 *                  String   permaLink,
 *                  String   mt_excerpt,
 *                  String   mt_text_more,
 *                  int      mt_allow_comments,
 *                  int      mt_allow_pings,
 *                  String   mt_convert_breaks,
 *                  String   mt_keywords;
 *                  String[] categories,  [Windows Live Spaces 用として、新
 *                  bool     publish,      たに追加された要素。Movable Type
 *                                         には存在しない。逆に mt_ で始まる
 *                                         要素は Windows Live Spaces では存
 *                                         在しない]
 *              失敗すると，fault が返ります．
 *          注意: link と permaLink は，どちらも 蓄積されている記事への URL 
 *                になります． 
 *                mt_ではじまっている項目は，metaWeblog.getPost API に Movable
 *                Type が追加したものです．
 *
 *    getPost
 *      引数:
 *          char         *postID        (I) 記事ID
 *          char         *userName      (I) ユーザ名
 *          char         *password      (I) パスワード
 *          CONTENTINFEX *contentInfo   (O) 取得した記事情報
 *      戻り値:
 *          TRUE    取得成功
 *          FALSE   指定記事が存在しない、取得失敗、送信失敗、その他のエラー
 *                  発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 */

BOOL
getPost( const char   *postID,
         const char   *userName,
         const char   *password,
         CONTENTINFEX *contentInfo );


/* 指定件数分の最新記事の取得
 *  metaWeblog.getRecentPosts 
 *      説明: 最近投稿された記事の群れを返します．
 *      引数: String blogid,
 *            String username,
 *            String password,
 *            int    numberOfPosts
 *      返り値: 成功すると，次の要素を含む構造体が返ってきます． 
 *                  ISO.8601 dateCreated,
 *                  String   userid,
 *                  String   postid,
 *                  String   description,
 *                  String   title,
 *                  String   link,
 *                  String   permaLink, 
 *                  String   mt_excerpt,
 *                  String   mt_text_more,
 *                  int      mt_allow_comments,
 *                  int      mt_allow_pings,
 *                  String   mt_convert_breaks,
 *                  String   mt_keywords;
 *                  String[] categories,  [Windows Live Spaces 用として、新
 *                  bool     publish,      たに追加された要素。Movable Type
 *                                         には存在しない。逆に mt_ で始まる
 *                                         要素は Windows Live Spaces では存
 *                                         在しない]
 *              失敗すると，fault が返ります．
 *          注意: dateCreated は，blogid の weblog においての時間帯になってい
 *                ます． 
 *                link と permaLink は，どちらも 蓄積されている記事への URLに
 *                なります．
 *
 *    getRecentPostsEx
 *      引数:
 *          char         *blogID         (I) blog ID
 *          char         *userName       (I) ユーザ名
 *          char         *password       (I) パスワード
 *          int          *numberOfPosts  (I) 取得する記事情報数
 *                                       (O) 実際に取得した記事情報数
 *          CONTENTINFEX *contentInfo    (O) 取得した記事情報
 *      戻り値:
 *          0       記事が存在しない、取得失敗、送信失敗、その他のエラー発生
 *          1 以上  取得に成功した記事情報の数
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) *numberOfPosts で指定した数の分だけ、最新の記事から過去の記事
 *              へ遡る方向に記事情報を取得する
 *          (3) 実際に取得に成功した記事情報の数を *numberOfPosts に設定する
 */

int
getRecentPostsEx( const char   *blogID,
                  const char   *userName,
                  const char   *password,
                  int          *numberOfPosts,
                  CONTENTINFEX *contentInfo );


/* ファイルのアップロード
 *  metaWeblog.newMediaObject 
 *      説明: ファイルを webサーバに転送します．
 *      引数: String blogid,
 *            String username,
 *            String password,
 *            struct file
 *          注意: file 構造体には，2つの項目があります:
 *                    base64 bits (the base64 で符号化された，ファイルの中身)
 *                    String name (ファイル名 ). 
 *                type 項目 (ファイルの種類) は，今のところ無視されます．
 *      返り値: 転送したファイルへの URL が返ってきます．
 *
 *    getRecentPostsEx
 *      引数:
 *          char    *blogID    (I) blog ID
 *          char    *userName  (I) ユーザ名
 *          char    *password  (I) パスワード
 *          FILEINF *fileInf   (I) アップロードするファイルに関する情報
 *          char    *url       (O) アップロードしたファイルの URL
 *      戻り値:
 *          TRUE    取得成功
 *          FALSE   アップロード失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) アップロード先のファイル名は、blog のトップディレクトリからの
 *              相対パスで指定する。存在しないディレクトリを指定した場合は作
 *              成される(blog ツールによっては、エラーとなる可能性あり)
 *          (3) すでにサーバ上に同名のファイルが存在する場合は、そのまま上書
 *              きされる場合と、別の名前で保存される場合がある。前者の例とし
 *              て Movable Type、後者の例として TypePad が挙げられる
 */

BOOL
newMediaObject( const char *blogID,
                const char *userName,
                const char *password,
                FILEINF    *fileInf,
                char       *url );


/*****  MovableType API  *****/
/* 指定件数分の記事情報の取得
 *  mt.getRecentPostTitles 
 *      説明: 最近投稿された記事の群れを，帯域にやさしく返します．
 *      引数: String blogid,
 *            String username,
 *            String password,
 *            int    numberOfPosts
 *      返り値: 成功すると，次の要素を含む構造体の配列が返ってきます:
 *                  ISO.8601 dateCreated,
 *                  String   userid,
 *                  String   postid,
 *                  String   title; 
 *              失敗すると，faultが返ります．
 *          注意: dateCreated は，blogid の weblog においての時間帯になってい
 *                ます．
 *
 *    getRecentPostTitles
 *      引数:
 *          char    *blogID         (I) blog ID
 *          char    *userName       (I) ユーザ名
 *          char    *password       (I) パスワード
 *          int     *numberOfPosts  (I) 取得する記事情報数
 *                                  (O) 実際に取得した記事情報数
 *          POSTINF *postinf        (O) 取得した記事情報
 *      戻り値:
 *          0       記事が存在しない、取得失敗、送信失敗、その他のエラー発生
 *          1 以上  取得に成功した記事情報の数
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) *numberOfPosts で指定した数の分だけ、最新の記事から過去の記事
 *              へ遡る方向に記事情報を取得する
 *          (3) 実際に取得に成功した記事情報の数を *numberOfPosts に設定する
 */

int
getRecentPostTitles( const char *blogID,
                     const char *userName,
                     const char *password,
                     int        *numberOfPosts,
                     POSTINF    *postinf );


/* カテゴリ一覧の取得
 *  mt.getCategoryList 
 *      説明: その weblog にあるすべての分類を返します．
 *      引数: String blogid,
 *            String username,
 *            String password
 *      返り値: 成功すると，次の要素を含む構造体の配列が返ってきます:
 *                  String categoryId
 *                  String categoryName;
 *              失敗すると，fault が返ります．
 *
 *    getCategoryList
 *      引数:
 *          char       *blogID           (I) blog ID
 *          char       *userName         (I) ユーザ名
 *          char       *password         (I) パスワード
 *          int        *numOfCategories  (I) 取得するカテゴリの数
 *                                       (O) 実際に取得したカテゴリの数
 *          CATLISTINF *categories       (O) 取得したカテゴリ情報
 *      戻り値:
 *          0       カテゴリが存在しない、取得失敗、送信失敗、その他のエラー
 *                  発生
 *          1 以上  取得に成功したカテゴリの数
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) *numOfCategories で指定した数の分だけ、カテゴリ情報を取得する
 *              実際に存在するカテゴリ数が *numOfCategories で指定した値より大
 *              きい場合は、全カテゴリではなく、*numOfCategories で指定した分
 *              だけ取得する
 *          (3) 実際に取得に成功したカテゴリの数を *numOfCategories に設定する
 */

int
getCategoryList( const char   *blogID,
                 const char   *userName,
                 const char   *password,
                 long         *numOfCategories, /* カテゴリの数 */
                 CATLISTINF_t categories );     /* カテゴリ     */


/* 指定記事に対して設定済みのカテゴリ一覧の取得
 *  mt.getPostCategories 
 *      説明: その投稿に指定されてある分類をすべて返します．
 *      引数: String postid,
 *            String username,
 *            String password
 *      返り値: 成功すると，次の要素を含む構造体の配列が返ってきます:
 *                  String  categoryName,
 *                  String  categoryId,
 *                  boolean isPrimary; 
 *              失敗すると，fault が返ります．
 *          注意: isPrimary は，分類がその分類の第一分類かどうか，ということを
 *                意味します．
 *
 *    getPostCategories
 *      引数:
 *          char   *postID              (I) 記事ID
 *          char   *userName            (I) ユーザ名
 *          char   *password            (I) パスワード
 *          int    *numberOfCategories  (I) 取得するカテゴリの数
 *                                      (O) 実際に取得したカテゴリの数
 *          CATINF *categories          (O) 取得したカテゴリ情報
 *      戻り値:
 *          0       カテゴリが存在しない、取得失敗、送信失敗、その他のエラー
 *                  発生
 *          1 以上  取得に成功したカテゴリの数
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) *numberOfCategories で指定した数の分だけ、カテゴリ情報を取得
 *              する。実際に設定されているカテゴリ数が *numberOfCategoriesで
 *              指定した値より大きい場合は、全カテゴリではなく、
 *              *numberOfCategories で指定した分だけ取得する
 *          (3) 実際に取得に成功したカテゴリの数を *numberOfCategories に設定
 *              する
 */

int
getPostCategories( const char *postID,
                   const char *userName,
                   const char *password,
                   long       *numberOfCategories,
                   CATINF     *categories );


/* 指定記事へのカテゴリの設定
 *  mt.setPostCategories 
 *      説明: 記事の分類を設定します．
 *      引数: String postid,
 *            String username,
 *            String password,
 *            array  categories
 *          注意: categories は，次の要素を含む構造体の配列です:
 *                    String  categoryId，
 *                    boolean isPrimary． 
 *                isPrimary を使い，第一分類を指定することも可能です． 
 *                このフラグを指定しなければ，配列のひとつめの要素が，その記事
 *                の第一分類になります．
 *      返り値: 成功すると true が，失敗すると fault が返ります．
 *
 *    setPostCategories
 *      引数:
 *          char     *postID             (I) 記事ID
 *          char     *userName           (I) ユーザ名
 *          char     *password           (I) パスワード
 *          long     numberOfCategories  (I) 設定するカテゴリの数
 *          CATEGORY *categories         (I) 設定するカテゴリ情報
 *      戻り値:
 *          TRUE   設定成功
 *          FALSE  設定失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) numberOfCategories で指定した数の分だけ、カテゴリ情報を設定
 *              する。
 */

BOOL
setPostCategories( const char *postID,
                   const char *userName,
                   const char *password,
                   long       numOfCategories,
                   CATEGORY   *categories );


/* サポートしている XML-RPC API 一覧の取得
 *  mt.supportedMethods 
 *      説明: サーバで提供されている XML-RPC の呼び出し方法を取得します．
 *      引数: なし
 *      返り値: サーバで提供されている呼び出し方法の配列が返ります．
 *
 *    getSupportedMethods
 *      引数:
 *          int  *numberOfMethods  (I) 取得する呼び出し方法の数
 *                                 (O) 実際に取得した呼び出し方法の数
 *          char *methodList[]     (O) 取得した呼び出し方法のリスト
 *      戻り値:
 *          0       XML-RPC API が存在しない、取得失敗、送信失敗、その他の
 *                  エラー発生
 *          1 以上  取得に成功した XML-RPC API の数
 *      備考:
 *          (1) *numberOfMethods  で指定した数の分だけ、呼び出し方法を取得
 *              する。実際に存在する呼び出し方法の数が *numberOfMethods で
 *              指定した値より大きい場合は、*numberOfMethods  で指定した分
 *              だけ取得する
 *          (2) 実際に取得に成功した呼び出し方法の数を *numberOfMethods に
 *              設定する
 */

int
getSupportedMethods( int *numberOfMethods, char *methodList[] );


/*
 *  mt.supportedTextFilters 
 *      説明: サーバで提供されている文書整形プラグインに関する情報を取得します
 *      引数: なし
 *      返り値: String key
 *              String label
 *              を含む構造体の配列がかえってきます． 
 *              key は，文書整形プラグインを区別する一意な文字列で， label 
 *              は，それを読めるかたちにした説明です． 
 *              key は，newPostとeditPostに mt_convert_breaks変数として渡さ
 *              れるべき値です．
 *
 *    getSupportedFilters
 *      引数:
 *          int       *numberOfFilters  (I) 取得するプラグインの数
 *                                      (O) 実際に取得したプラグインの数
 *          FILTERINF *filterList       (O) 取得したプラグインのリスト
 *      戻り値:
 *          0       プラグイン が存在しない、取得失敗、送信失敗、その他の
 *                  エラー発生
 *          1 以上  取得に成功した XML-RPC API の数
 *      備考:
 *          (1) *numberOfFilters で指定した数の分だけ、 プラグインを取得す
 *              る。実際に存在する呼び出し方法の数が *numberOfFilters で指
 *              定した値より大きい場合は、*numberOfFiltersで指定した分だけ
 *              取得する
 *          (2) 実際に取得に成功したプラグインの数を *numberOfFilters に設
 *              定する
 */

int
getSupportedFilters( int       *numberOfFilters,
                     FILTERINF *filterList );

/* 指定記事に対するトラックバック一覧の取得
 *  mt.getTrackbackPings 
 *      説明: 指定した記事に送られた トラックバック Ping の群れを取得します．
 *            これを使うのは，指定した記事への Ping の群れをプログラムとかが 
 *            取得して，それらの Ping それぞれに，同じ処理を順番に行うような
 *            場合でしょう． 
 *            たとえば，ある話題についての記事とそれに言及している記事から成
 *            る web グラフを作り上げるような場合，みたいな．
 *      引数: String postid
 *      返り値: 次の要素を含む構造体の配列が返ってきます: 
 *                  String pingTitle (Ping してきた記事の件名),
 *                  String pingURL (記事の URL),
 *                  String pingIP (Ping してきたホストの IP アドレス)．
 *
 *    getTrackbackPings
 *      引数:
 *          char  *postID         (I) 記事ID
 *          int   *numberOfPings  (I) 取得するトラックバック情報の数
 *                                (O) 実際に取得したトラックバック情報の数
 *          TBINF *tbInfo         (O) 取得したトラックバック情報
 *      戻り値:
 *          0       トラックバックが存在しない、取得失敗、送信失敗、その他の
 *                  エラー発生
 *          1 以上  取得に成功したトラックバック情報の数
 *      備考:
 *          (1) *numberOfPings で指定した数の分だけ、トラックバック情報を取得
 *              する。実際に存在するトラックバックの数が *numberOfPings  で指
 *              定した値より大きい場合は、*numberOfPings で指定した分だけ取得
 *              する
 *          (2) 実際に取得に成功したトラックバック情報の数を *numberOfPings 
 *              に設定する
 */

int
getTrackbackPings( const char *postID,
                   int        *numberOfPings,
                   TBINF      *tbInfo );


/* 再構築の実行
 *  mt.publishPost 
 *      説明: weblog にあるすべての静的ファイルを公開 (再構築) します． 
 *            これは，システムに記事を投稿し，保存することとおなじことです．
 *            (違うのは，この方法だと Ping を行わない，ということです)．
 *      引数: String postid,
 *            String username,
 *            String password
 *      返り値: 成功すると true が，失敗すると fault が返ります．
 *
 *    publishPost
 *      引数:
 *          char  *postID    (I) 記事ID
 *          char  *userName  (I) ユーザ名
 *          char  *password  (I) パスワード
 *      戻り値:
 *          TRUE   再構築成功
 *          FALSE  再構築失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 */

BOOL
publishPost( const char *postID,
             const char *userName,
             const char *password );


/* 指定投稿日時での投稿予約 [推定]
 *  mt.setNextScheduledPost
 *    (仕様、詳細不明)
 */


/* XML-RPC を利用したユーティリティ関数群 */

/*
 * blog ID の取得
 *    引数:   ユーザ名, パスワード
 *    戻り値: (システム内に存在する blog のうち、いちばん最初に見つ
 *             かった blog の) blog ID
 *    備考: 現時点のココログのように 1サイト 1blog 固定の場合は、こ
 *          の関数で十分
 *          → 2004年2月20日以降、プラスやプロが登場。ココログでも複
 *             数 blog 設置可能になった
 */

int
getBlogID( const char *userName,
           const char *password,
           char       *blogID );  /* blog ID の取得 */

/*
 * blog ID の取得
 *    引数:   ユーザ名, パスワード, 取得した blog 情報格納場所
 *    戻り値: システム内に存在する blog の数
 *    備考: Movable Type で同一サイト内に複数の blog を設置して
 *          いる場合は、この関数を使う
 */

int
getBlogIDs( const char *userName,
            const char *password,
            int        *numberOfBlogs,
            BLOGINF    *blogInfo );

/*
 * 最新の記事の取得
 */

int
getRecentPost( const char *blogID,
               const char *userName,
               const char *password,
               CONTENTINF *contentInfo );
int
getRecentPost2( const char   *blogID,
                const char   *userName,
                const char   *password,
                CONTENTINFEX *contentInfo );
int
getRecentPost3( const char *blogID,
                const char *userName,
                const char *password,
                POSTINF    *postinf );

/* getRecentPostTitles() の blogger API 版 */
int
getRecentPostTitlesOnBloggerAPI( const char *blogID,
                                 const char *userName,
                                 const char *password,
                                 int        *numberOfPosts,
                                 POSTINF    *postinf );

/* getRecentPostTitles() の metaWeblog API 版 */
int
getRecentPostTitlesOnMetaWeblog( const char *blogID,
                                 const char *userName,
                                 const char *password,
                                 int        *numberOfPosts,
                                 POSTINF    *postinf );

/* RSS を取得し、その内容を元に POSTINF 構造体に情報を格納する */
/*          (XML-RPC API は使わない)                           */
int
getRecentPostTitlesFromRSS(
        const char *rssURL,         // (I) RSS の URL
        int        *numberOfPosts,  // (I) 取得する記事情報の数
                                    // (O) 実際に取得した記事情報の数
        POSTINF    *postinf         // (O) 取得した記事情報
    );


/*
 * post ID 一覧の取得
 */

int
getRecentPostIDs( const char *blogID,
                  const char *userName,
                  const char *password,
                  int        *numberOfPosts,
                  char       listOfPostIDs[][MAX_POSTIDLENGTH] );

/*
 * ファイルのアップロード
 */

int
uploadFile( const char *blogID,
            const char *userName,
            const char *password,
            const char *dirname,    /* upload先ディレクトリ名(blog のトップ */
                                    /* ディレクトリからの相対パス; 存在しな */
                                    /* い場合は作成される)                  */
            const char *fileName,
            size_t     fileSize,
            const char *fileType,
            char       *url );


/*
 *  以下、Movable Type ではサポートされていない Blogger XML-RPC API
 *
 *  blogger.getTemplate
 *      see also:
 *        http://new.blogger.com/developers/api/1_docs/xmlrpc_getTemplate.html
 *      
 *      引数: appkey (string): Unique identifier/passcode of the application
 *                             sending the post. (See access info.)
 *            blogid (string): Unique identifier of the blog who's template is
 *                             to be returned.
 *            username (string): Login for a Blogger who has admin permission
 *                               on give blog.
 *            password (string): Password for said username.
 *            templateType (string): Determines which of the blog's templates
 *                                   will be returned.
 *                                   Currently, either "main" or "archiveIndex".
 *
 *  blogger.setTemplate 
 *      see also:
 *        http://new.blogger.com/developers/api/1_docs/xmlrpc_setTemplate.html
 *
 *      引数: appkey (string): Unique identifier/passcode of the application
 *                             sending the post. (See access info.)
 *            blogid (string): Unique identifier of the blog who's template is
 *                             to be returned.
 *            username (string): Login for a Blogger who has admin permission
 *                               on give blog.
 *            password (string): Password for said username.
 *            template (string): The text for the new template (usually mostly
 *                               HTML).
 *                               Must contain opening and closing <Blogger>
 *                               tags, since they're needed to publish.
 *            templateType (string): Determines which of the blog's templates
 *                                   will be returned.
 *                                   Currently, either "main" or "archiveIndex".
 *
 *  以下、Movable Type ではサポートされていない metaWeblog XML-RPC API
 *      (http://www.xmlrpc.com/metaWeblogApi)
 *
 *  metaWeblog.getCategories
 *      引数: blogid, username, password
 *      返り値: カテゴリの数分、以下の内容の構造体を返す。
 *                  description,
 *                  htmlUrl,
 *                  rssUrl
 *
 *              ただし、Windows Live Spaces (および ウェブリブログ)では、
 *              以下の内容の構造体を返す
 *                  description,
 *                  title,
 *              (description と title には、ともに「カテゴリ名」が格納される)
 */

/* category 情報構造体 (metaWeblog.getCategories 用) */
typedef struct categories {
    char    categoryTitle[MAX_CATIDLENGTH];         /* カテゴリの名前 */
    char    categoryDescription[MAX_CATNAMELENGTH]; /* カテゴリの説明 */
}   CATEGORIES, *CATEGORIES_t;

int
getCategories( const char   *blogID,
               const char   *userName,
               const char   *password,
               long         *numOfCategories, /* カテゴリの数 */
               CATEGORIES_t categories );     /* カテゴリ     */


/* その他の blog 関連 XML-RPC
 *
 *      http://www.blogcensus.net/?page=API
 *          BlogCensus.isBlog( URL )
 *            Returns 1 if the provided URL is a crawled weblog, 0 otherwise
 *          BlogCensus.getGenerator( URL )
 *            Returns the name of the authoring tool used to generate the blog
 *          BlogCensus.getLanguage( URL )
 *            Returns a string containing the language the blog is written in
 *          BlogCensus.getIncomingLinkCount( URL )
 *            Returns an integer count of incoming links from other blogs
 *          BlogCensus.getOutgoingLinkCount( URL )
 *            Returns an integer count of outgoing links to other blogs
 *
 *      http://www.livejournal.com/doc/server/ljp.csp.xml-rpc.protocol.html
 *      (livejournal API)
 *          LJ.XMLRPC.login - validate user's password and get base
 *                            information needed for client to function
 *          LJ.XMLRPC.postevent - The most important mode, this is how a user
 *                            actually submits a new log entry to the server.
 *          LJ.XMLRPC.editevent - Edit or delete a user's past journal entry
 *          LJ.XMLRPC.editfriendgroups - Edit the user's defined groups of
 *                            friends.
 *          LJ.XMLRPC.editfriends - Add, edit, or delete friends from
 *                            the user's friends list.
 *          LJ.XMLRPC.getevents - Download parts of the user's journal.
 *          LJ.XMLRPC.getfriends - Returns a list of which other LiveJournal
 *                            users this user lists as their friend.
 *          LJ.XMLRPC.friendof - Returns a list of which other LiveJournal
 *                            users list this user as their friend.
 *          LJ.XMLRPC.getfriendgroups - Retrieves a list of the user's defined
 *                            groups of friends.
 *          LJ.XMLRPC.getdaycounts - This mode retrieves the number of journal
 *                            entries per day.
 *          LJ.XMLRPC.syncitems - Returns a list of all the items that have
 *                            been created or updated for a user.
 *          LJ.XMLRPC.checkfriends - Checks to see if your friends list has
 *                            been updated since a specified time.
 *          LJ.XMLRPC.consolecommand - Run an administrative command.
 *
 */

/*
 * XML-RPC API とは関係ないが、役に立つと思われるAPI
 */

/*
 *  トラックバック送信
 */
int
sendTrackbackPing( const char *blogName,
                   const char *articleTitle,
                   const char *articleURL,
                   const char *articleExcerpt,
                   const char *targetURL );

/*
 *  指定記事のトラックバック送信用URLの取得
 *      (1) 原則として trackback Auto-discovery 機能を使って取得
 *      (2) ただし、trackback Auto-discovery 未対応なところでも、
 *          記事の URL を元に、一定の法則でトラックバック送信用
 *          URL を求めることができる場合は、その URL を返す
 */
char    *
getTrackbackURL( const char *articleURL );


/* はてなダイアリーキーワードリンク関連 API */

/*
 * はてなダイアリーキーワードリスト取得
 */

int
getHatenaKeywordList();

/*
 * はてなダイアリーキーワードリンク変換
 */

#define MODE_RAW        1
#define MODE_HTML       2

char    *
changeHatenaKeyword( const char *src, char *dst, int mode );

/* はてなダイアリーキーワード自動リンクAPI (XML-RPC API) */
/*
 *      uri: http://d.hatena.ne.jp/xmlrpc 
 *      encoding: utf8 
 *      methodName: hatena.setKeywordLink 
 *      parameters: 以下を参照 
 *          body(string): キーワードを抽出するテキストを指定します。 
 *          score(int): 0～50。キーワードスコアのしきい値を指定します。
 *                      指定された値よりもスコアが大きいキーワードのみが抽
 *                      出されます。
 *          cname(array): キーワードのカテゴリーを指定します。指定があった
 *                        場合、「一般」と指定されたカテゴリーのキーワード
 *                        が抽出されます。指定が無かった場合は、全カテゴリー
 *                        となります。
 *                        book,music,movie,web,elec,animal,anime,food,sports,
 *                        game,comic,hatena,clubが指定可能です。省略可。
 *          a_target(string): アンカー(a)タグのtarget属性値を指定します。
 *                            例：_blank 
 *          a_class(string): アンカー(a)タグのclass属性値を指定します。
 *                           例：keyword 
 *      [cname は 2004年6月17日に追加された引数]
 */

/*  キーワードのカテゴリ         */
/*    以下の値の論理和で指定する */
#define CNAME_GENERAL       0x0000
#define CNAME_BOOK          0x0001
#define CNAME_MUSIC         0x0002
#define CNAME_MOVIE         0x0004
#define CNAME_WEB           0x0008
#define CNAME_ELEC          0x0010
#define CNAME_ANIMAL        0x0020
#define CNAME_ANIME         0x0040
#define CNAME_FOOD          0x0080
#define CNAME_SPORTS        0x0100
#define CNAME_GAME          0x0200
#define CNAME_COMIC         0x0400
#define CNAME_HATENA        0x0800
#define CNAME_CLUB          0x1000

char    *
setKeywordLink( const char    *src,
                char          *dst,
                size_t        dstSize,
                int           score,
                unsigned long cname,
                const char    *target,
                const char    *keywordClass );



/*
 *  Bulkfeeds API
 */

/* Bulkfeeds API キー設定 */
void
setApiKeyOnBulkfeeds( const char *apiKey );

/* RSS 登録/更新  → weblogUpdates.ping を使用 */

/* RSS/OPML直接指定による登録/更新                               */
/*   GET http://bulkfeeds.net/app/add.xml?url=登録したいRSS/OPML */
BOOL
updateRssOnBulkfeeds( const char *url );

/* RSS Feed 検索                                                         */
/*  GET http://bulkfeeds.net/app/search.opml?q=キーワード;field=検索対象 */
/*  GET http://bulkfeeds.net/app/search.rdf?q=キーワード;field=検索対象  */
/*            キーワードは UTF-8 の文字列を URL エンコードしたもの       */
/*            検索対象 は title | description | link のいずれか          */

#define OUTPUT_RSS  1
#define OUTPUT_OPML 2

int
searchRssOnBulkfeeds( const char *keyword, const char *field, int outputType );

/* RSS Item 全文検索 */
/*  GET http://bulkfeeds.net/app/search2.rdf?q=キーワード                */

int
searchEntryOnBulkfeeds(
        const char *keyword,        // (I) キーワード
        int        *numberOfPosts,  // (I) 取得する記事情報の数
                                    // (O) 実際に取得した記事情報の数
        POSTINF    *postinf         // (O) 取得した記事情報
    );

/* RSS Similarity Search                                                 */
/*  GET http://bulkfeeds.net/app/similar.rdf?url=アドレス&apikey=APIキー */

int
searchSimilarityOnBulkfeeds(
        const char *url,            // (I) 類似記事を検索したい記事のURL
        const char *apiKey,         // (I) APIキー
        int        *numberOfPosts,  // (I) 取得する記事情報の数
                                    // (O) 実際に取得した記事情報の数
        POSTINF    *postinf         // (O) 取得した記事情報
    );

/* 特徴語上位10語取得                                                       */
/*  GET http://bulkfeeds.net/app/similar.xml?url=アドレス&apikey=APIキー    */
/*   返り値(XML) の例                                                       */
/*    <?xml version="1.0" encoding="utf-8" ?>                               */
/*    <terms about="http://watcher.moe-nifty.com/memo/2004/04/post_1.html"> */
/*    <term>優子</term>                                                     */
/*    <term>小倉</term>                                                     */
/*    <term>BLOODY</term>                                                   */
/*    <term>トレカ</term>                                                   */
/*    <term>種類</term>                                                     */
/*    <term>獣</term>                                                       */
/*    <term>計画</term>                                                     */
/*    <term>付い</term>                                                     */
/*    <term>化</term>                                                       */
/*    <term>“</term>                                                       */
/*    </terms>                                                              */

#define MAX_LEN_BF_TERM 256 /* term 文字列最大長 (暫定) */
typedef struct  bf_term {
    char    term[MAX_LEN_BF_TERM + 1];
}   BF_TERM;                /* 特徴語(形態素)格納領域 */

int
extractFeatureWordsOnBulkfeeds(
        const char *url,        // (I) 特徴語を抽出したい記事のURL
        const char *apiKey,     // (I) APIキー
        int        *numOfTrems, // (I) 取得する特徴語の数 (最大 10個)
                                // (O) 実際に取得した特徴語の数
        BF_TERM    *terms       // (O) 取得した特徴語
    );

/* 形態素解析 + 特徴語抽出                                                  */
/*  GET http://bulkfeeds.net/app/terms.xml?content=解析対象文字列&apikey=APIキー */

int
extractAnalyseOnBulkfeeds(
        const char *content,    // (I) 形態素解析(特徴語抽出)対象の文字列
        const char *apiKey,     // (I) APIキー
        int        *numOfTrems, // (I) 取得する特徴語の数
                                // (O) 実際に取得した特徴語の数
        BF_TERM    *terms       // (O) 取得した特徴語
    );

/* RSS Auto Discovery                                                     */
/*  GET http://bulkfeeds.net/app/discover.xml?url=アドレス&apikey=APIキー */

char    *
getRssUrlOnBulkfeeds( const char *blogUrl, const char *apiKey );


/*
 *  FeedBack API
 */

/* RSS Item 全文検索 */
/*   GET http://naoya.dyndns.org/feedback/app/rss?keyword=キーワード */

int
searchEntryOnFeedback(
        const char *keyword,        // (I) キーワード
        int        *numberOfPosts,  // (I) 取得する記事情報の数
                                    // (O) 実際に取得した記事情報の数
        POSTINF    *postinf         // (O) 取得した記事情報
    );


/*
 *  Amazon Web Services API
 */

/*
 *  AmazonのXML WebサービスのURL (REST)
 *
 *      http://xml-jp.amznxslt.com/onca/xml3?
 *
 *  このURLの?の後に以下のパラメーターを&で続けて指定します。
 *      t=      アソシエイトID  
 *      dev-t=  ディベロッパー・トークン  
 *      type=   取得するデータの種類
 *                  lite:   簡易版
 *                  heavy:  完全版
 *      page=   検索結果が複数の場合のページ番号  
 *      mode=   検索する商品の種類
 *                  books-jp:       和書
 *                  books-us:       洋書
 *                  music-jp:       音楽
 *                  classical-jp:   音楽クラシック
 *                  dvd-jp:         DVD
 *                  vhs-jp:         ビデオ
 *                  electronics-jp: エレクトロニクス
 *                  software-jp:    ソフトウェア
 *                  videogames-jp:  ゲーム
 *                  toys-jp:        おもちゃ&ホビー
 *      f=      XSLTを利用する場合は、XSLTのURL。
 *              URLの代わりに f=xml　とすると、xmlがそのまま取得できる。
 *      KeywordSearch=
 *      ASINSearch=
 *      BrowseNodeSearch=
 *              KeywordSearchなどの検索の種類を指定して、KeywordSearch=○○に
 *              キーワードやAsin番号、ノード番号などを指定  
 *      locale= jp
 */

/* Amazon アソシエイトID の設定 */
void
setAssociateIdOnAmazon( const char *associateID );

/* Amazon Subscription ID の設定 */
void
setSubscriptionIDOnAmazon( const char *subscriptionID );

/* Amazon で検索 */
/*   取得するデータの種類 */
#define AMAZON_TYPE_LITE        1   /* 簡易版 */
#define AMAZON_TYPE_HEAVY       2   /* 完全版 */

/*   検索する商品の種類   */
#define AMAZON_MODE_JBOOKS      1   /* 和書             */
#define AMAZON_MODE_EBOOKS      2   /* 洋書             */
#define AMAZON_MODE_MUSIC       3   /* 音楽             */
#define AMAZON_MODE_CLASSIC     4   /* 音楽クラシック   */
#define AMAZON_MODE_DVD         5   /* DVD              */
#define AMAZON_MODE_VIDEO       6   /* ビデオ           */
#define AMAZON_MODE_ELECTRONICS 7   /* エレクトロニクス */
#define AMAZON_MODE_SOFTWARE    8   /* ソフトウェア     */
#define AMAZON_MODE_GAME        9   /* ゲーム           */
#define AMAZON_MODE_KITCHEN     10  /* キッチン         */
#define AMAZON_MODE_TOYS        11  /* おもちゃ&ホビー  */
#define AMAZON_MODE_HOBBY       12  /* ホビー           */
#define AMAZON_MODE_SPORTS      13  /* スポーツ         */
#define AMAZON_MODE_BLENDED     255 /* すべての商品     */

/*   検索方法             */
#define AMAZON_STYPE_KEYWORD    1   /* キーワードで検索 */
#define AMAZON_STYPE_ASIN       2   /* ISBN/ASIN で検索 */
#define AMAZON_STYPE_NODE       3   /* ノード番号で検索 */

/* for ECS4.0 */
/*   取得するデータの種類 */
#define AMAZON_TYPE_SMALL       1   /* 簡易版 */
#define AMAZON_TYPE_MEDIUM      2   /* 普及版 */
#define AMAZON_TYPE_LARGE       3   /* 完全版 */

/*   検索方法             */
#define AMAZON_STYPE_ITEMSEARCH 1   /* 商品の検索 */
#define AMAZON_STYPE_ITEMLOOKUP 4   /* 商品詳細   */

int
searchItemsOnAmazon4(
        int        type,        /* (I) Small, Medium, Large */
        int        mode,        /* (I) 検索対象分野         */
        int        searchType,  /* (I) 検索種別             */
        const char *keyword,    /* (I) 検索対象キーワード   */
        int        *numOfItems, /* (I/O) 検索結果アイテム数 */
        void       *result      /* (O) 検索結果格納領域     */
    );

/* Amazon のベストセラーリスト取得 */
int
getSalesRankingOnAmazon4(
        int        type,        /* (I) heavy or lite        */
        int        mode,        /* (I) 検索対象分野(大枠)   */
        int        node,        /* (I) 検索対象分野(絞込み) */
        const char *genre,      /* (I) 検索対象分野名       */
        int        *numOfItems, /* (I/O) 検索結果アイテム数 */
        void       *result      /* (O) 検索結果格納領域     */
    );

/*
 *  Rakuten Web Services API
 *      ・従来型の API は アフィリエイトID(旧) のみを使用
 *      ・2007年1月に登場した API は デベロッパーID と ア
 *        フィリエイトID(新) を使用
 */

/* 楽天 デベロッパーID の設定 */
void
setDeveloperIdOnRakuten( const char *developerID );

/* 楽天 アフィリエイトID(旧) の設定 */
void
setAffiliateIdOnRakuten( const char *affiliateID );

/* 楽天 アフィリエイトID(新) の設定 */
void
setAffiliateIdOnRakuten2( const char *affiliateID2 );

/* 楽天ブックス セールスランキングの取得 */
/*   取得するファイルの形式 */
#define RAKUTEN_TYPE_HTML   1   /* html */
#define RAKUTEN_TYPE_XML    2   /* xml  */

/*   対象サービス */
#define RAKUTEN_SERVICE_BOOKS   1   /* 楽天ブックス */

/*   ジャンル (対象サービスが「楽天ブックス」の場合) */
#define RAKUTEN_GENRE_GENERAL       0   /* 総合                   */
#define RAKUTEN_GENRE_COMICS        1   /* コミック・ジュブナイル */
#define RAKUTEN_GENRE_CHALLENGE     2   /* 語学・就職・資格試験   */
#define RAKUTEN_GENRE_CHILDREN      3   /* 絵本・児童書           */
#define RAKUTEN_GENRE_NOVEL         4   /* 文芸・ノンフィクション */
#define RAKUTEN_GENRE_COMPUTER      5   /* ＰＣ・システム開発     */
#define RAKUTEN_GENRE_BUSINESS      6   /* ビジネス・経済・経営   */
#define RAKUTEN_GENRE_TRAVEL        7   /* 旅行・紀行・アウトドア */
#define RAKUTEN_GENRE_HOWTO         8   /* 学問がわかる本         */
#define RAKUTEN_GENRE_HOBBY         9   /* ホビー・スポーツ       */
#define RAKUTEN_GENRE_LIFESTYLE     10  /* ライフスタイル         */
#define RAKUTEN_GENRE_ENTERTAINMENT 11  /* エンターテイメント     */
#define RAKUTEN_GENRE_ACADEMIC      12  /* 専門書・学術書         */
#define RAKUTEN_GENRE_PHOTOBOOK     13  /* 写真集・タレント       */


int
getSalesRankingOnRakuten(
        int  type,          /* (I) 取得するファイルの形式 */
        int  service,       /* (I) 対象サービス           */
        int  genre,         /* (I) ジャンル               */
        int  *numOfItems,   /* (I/O) 検索結果アイテム数   */
        void *result        /* (O) 検索結果格納領域       */
    );


/*
 * cousagi XML-RPC API
 *
 *  cousagi.getNewEntry 
 *    説明 
 *      こうさぎに新しく記事を書かせます 
 *    引数 
 *      String  username, // こうさぎ のユーザ名(アカウント)
 *      String  password, // 上記ユーザの login 用パスワード
 *
 *  cousagi.getNewPhrase 
 *    説明 
 *      こうさぎに新しく発言させます 
 *    引数 
 *      String  username, // こうさぎ のユーザ名(アカウント)
 *      String  password, // 上記ユーザの login 用パスワード
 *
 *  cousagi.getNewHaiku 
 *    説明 
 *      こうさぎに新しく俳句を詠ませます 
 *    引数 
 *      String  username, // こうさぎ のユーザ名(アカウント)
 *      String  password, // 上記ユーザの login 用パスワード
 *
 *  cousagi.getNewWhisper 
 *    説明 
 *      こうさぎに新しく寝言をつぶやかせます 
 *    引数 
 *      String  username, // こうさぎ のユーザ名(アカウント)
 *      String  password, // 上記ユーザの login 用パスワード
 */

/*
 *  Blog Pet 種別
 */
#define BPTYPE_UNKNOWN  0x0000  /* 未設定   */
#define BPTYPE_COUSAGI  0x0001  /* こうさぎ */
#define BPTYPE_CONEKO   0x0002  /* こねこ   */
#define BPTYPE_COINU    0x0003  /* こいぬ   */
#define BPTYPE_COPANDA  0x0004  /* こぱんだ */
#define BPTYPE_CONEZUMI 0x0005  /* こねずみ */

/* BlogPet種別を示す文字列を取得 (おまけAPI) */
char    *
blogPetTypeString( int blogPetType );

/* 記事の生成 */
int
getNewEntryOnCousagi( const char *userName,
                      const char *password,
                      char       *title,
                      char       *body );

/* 発言の生成 */
int
getNewPhraseOnCousagi( const char *userName,
                       const char *password,
                       char       *response );

/* 俳句の詠唱 */
int
getNewHaikuOnCousagi( const char *userName,
                      const char *password,
                      char       *response );

/* 寝言の生成 */
int
getNewWhisperOnCousagi( const char *userName,
                        const char *password,
                        char       *response );

/* 生成した記事に俳句を埋め込む (おまけAPI) */
char    *insertHaikuIntoEntry( char       *body,
                               const char *haiku,
                               const char *cousagiName,
                               int        blogPetType );

/*
 *  おまけ
 */

/* ISBN → 各種URL変換 */
char    *
isbn2urls(
        const char *isbn,    /* (I) ISBN                               */
        BOOL       isAffiliateAvalable,
                             /* (I) アフィリエイトリンクを含めるか否か */
        const char *vcSID,   /* (I) ValueCommerce SID                  */
        const char *vcPID1,  /* (I) クロネコヤマトブックサービス PID   */
        const char *vcPID2,  /* (I) JBOOK                        PID   */
        const char *vcPID3,  /* (I) 紀伊國屋書店                 PID   */
        const char *vcPID4   /* (I) @古本市場                    PID   */
    );


#ifdef  XMLRPC_EXPORTS
/*
 *  共通関数(ユーティリティ関数)群
 */
int
getDateCreated( char **input,
                int *yy, int *mm, int *dd, int *HH, int *MM, int *SS,
                int *cnt, int cntMax,
                int *numOfInfo );

int
getUserid( char **input,
           char *userid,
           int *cnt, int cntMax,
           int *numOfInfo );

int
getPostid( char **input,
           char *postid,
           int *cnt, int cntMax,
           int *numOfInfo );

int
getContent( char **input,
            char *content,
            int *cnt, int cntMax,
            int *numOfInfo );

int
getTitle( char **input,
          char *title,
          int *cnt, int cntMax,
          int *numOfInfo );

int
getPingUrl( char **input,
            char *pingURL,
            int *cnt, int cntMax,
            int *numOfInfo );

int
getPingTitle( char **input,
              char *pingTitle,
              int *cnt, int cntMax,
              int *numOfInfo );

int
getPingIP( char **input,
           char *pingIP,
           int *cnt, int cntMax,
           int *numOfInfo );

int
getUrl( char **input,
        char *url,
        int *cnt, int cntMax,
        int *numOfInfo );

int
getBlogid( char **input,
           char *blogid,
           int *cnt, int cntMax,
           int *numOfInfo );

int
getBlogName( char **input,
             char *blogName,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getFirstname( char **input,
             char *blogName,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getLastname( char **input,
             char *lastname,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getNickname( char **input,
             char *nickname,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getEmail( char **input,
          char *email,
          int *cnt, int cntMax,
          int *numOfInfo );

int
getDescription( char **input,
                char *description,
                int *cnt, int cntMax,
                int *numOfInfo );

int
getLink( char **input,
         char *link,
         int *cnt, int cntMax,
         int *numOfInfo );

int
getPermaLink( char **input,
              char *permaLink,
              int *cnt, int cntMax,
              int *numOfInfo );

int
getExcerpt( char **input,
            char *excerpt,
            int *cnt, int cntMax,
            int *numOfInfo );

int
getExtended( char **input,
             char *excerpt,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getAllowComments( char **input,
                  int *allowComments,
                  int *cnt, int cntMax,
                  int *numOfInfo );

int
getAllowPings( char **input,
               int *allowPings,
               int *cnt, int cntMax,
               int *numOfInfo );

int
getConvertLineBreaks( char **input,
                      char *convertLineBreaks,
                      int *cnt, int cntMax,
                      int *numOfInfo );

int
getKeywords( char **input,
             char *keywords,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getCategoryId( char **input,
               char *categoryId,
               int *cnt, int cntMax,
               int *numOfInfo );

int
getCategoryName( char **input,
                 char *categoryName,
                 int *cnt, int cntMax,
                 int *numOfInfo );

int
getIsPrimary( char **input,
              int *isPrimary,
              int *cnt, int cntMax,
              int *numOfInfo );

int
getKey( char **input,
        char *key,
        int *cnt, int cntMax,
        int *numOfInfo );

int
getLabel( char **input,
          char *label,
          int *cnt, int cntMax,
          int *numOfInfo );

int
getPublish( char **input,
            int *publish,
            int *cnt, int cntMax,
            int *numOfInfo );

int
getArrayCategories( char **input,
                    char *categories[MAX_CATEGORIES],
                    int  *numOfCategories );

char    *
getSingleString( const char *src, char *dst );

BOOL
getStringFromItem( const char *spec,
                   const char *in[],
                   char       *out,
                   int        size,
                   int        *cnt );

BOOL
getDateTimeFromItem( const char *spec,
                     const char *in[],
                     POSTINF    *out,
                     int        *cnt );

/* XMLからデータを取り出すためのユーティリティ関数 */
char    *
getResultFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *sectionEnd,
        char       *result
    );

char    *
getResultFromXML_s(
        const char *xmlSrc,
        const char *tagName,
        const char *sectionEnd,
        char       *result,
        size_t     result_size
    );  // getResultFromXML のサイズチェック機能付加バージョン

char    *
getIntegerFromXML(
        const char    *xmlSrc,
        const char    *tagName,
        const char    *sectionEnd,
        unsigned long *result
    );

char    *
getFloatFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *sectionEnd,
        double     *result
    );

char    *
getListFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *subTagName,
        const char *sectionEnd,
        char       *result,
        size_t     areaSizeOfResult
    );

#if (WINVER >= 0x0500)
#ifdef  _MSC_VER
void
resetDaylightSaving( void );
#endif
#endif

#endif  /* XMLRPC_EXPORTS */

/* 文字コード変換 */
char    *
sjis2euc( const char *p );

char    *
utf2euc( const char *p );

char    *
jis2euc( const char *p );

char    *
jis2sjis( const char *p );

char    *
euc2sjis( const char *p );

char    *
utf2sjis( const char *p );

char    *
sjis2utf( const char *p );

char    *
jis2utf( const char *p );

char    *
euc2utf( const char *p );

char    *
utf2sjisEx( char *p );  /* 引数の型が const char *p ではなく char *p で */
                        /* あることに注意! (領域破壊型)                 */

/*
 *  標準入力からの入力
 */

/* 数値の入力 */
BOOL
inputNumeric( int *num,     /* (O) 入力結果 (数値)      */
              int minimum,  /* (I) 入力可能数値の最小値 */
              int maximum );/* (I) 入力可能数値の最大値 */

/* yes/no の入力 */
int
inputYesNo( int        *flag,       /* (O) 入力結果 (yes: TRUE, no: FALSE) */
            const char *prompt );   /* (I) プロンプト文字列                */

/* 文字列の入力 */
int
inputString( char       *dst,       /* (O) 入力結果 (文字列)          */
             const char *prompt,    /* (I) プロンプト文字列           */
             int        password ); /* (I) パスワード入力モードか否か */

/*
 *  その他
 */
char    *
base64( const unsigned char *src, size_t sz );            // base64エンコード
char    *
unbase64( const unsigned char *src, unsigned char *dst, size_t *sz );
                                                          // base64デコード

unsigned char   *
sha1( const unsigned char *src );               // SHA1暗号化

void
hmac_sha1(
    const unsigned char *text,      /* pointer to data stream        */
    int                 text_len,   /* length of data stream         */
    const unsigned char *key,       /* pointer to authentication key */
    int                 key_len,    /* length of authentication key  */
    void                *digest);   /* caller digest to be filled in */

void
hmac_sha256(
    const unsigned char *text,      /* pointer to data stream        */
    int                 text_len,   /* length of data stream         */
    const unsigned char *key,       /* pointer to authentication key */
    int                 key_len,    /* length of authentication key  */
    void                *digest);   /* caller digest to be filled in */

char    *
decodeString( char *src );                      // 実体参照のデコード

char    *
encodeString( const char *src, char *dst );     // 実体参照へのエンコード

int
isHexString( const char *p );   // 指定文字列は16進文字列か否か

int
isDecString( const char *p );   // 指定文字列は10進文字列か否か

BOOL
setSigInfo(
        char       *key,
        char       *secret,
        const char *sig1,
        const char *sig2,
        const char *pre,
        const char *post
    );                      // BAZエンコード文字列のデコード #1

BOOL
setSigInfo3(
        char       *id1,
        char       *id2,
        char       *id3,
        const char *sig1,
        const char *sig2,
        const char *sig3,
        const char *pre1,
        const char *post1,
        const char *pre2,
        const char *post2
    );                      // BAZエンコード文字列のデコード #2

DWORD
getLanguageCode( void );    // Windows の言語を取得
                            // (例えば、日本語版: 1041, 英語(USA)版: 1033)
void
setLanguageCode( DWORD languageCode );  // Windows の言語を強制切り替え

/* エンドポイントURL取得 */
char    *
getEndpointURLbyAutoDiscovery( const char *topPageURL, char *blogID );


/* cookie */
#define MAX_COOKIE_NAME_LENGTH  80
#define MAX_COOKIE_VALUE_LENGTH 8192    // 本来は MAX_COOKIE_LEN 以下の値で OK

typedef struct cookieInfo   {
    int numOfValuables;
    int maxNumOfValuables;
    struct cookieValuable {
        char    name[MAX_COOKIE_NAME_LENGTH];
        char    value[MAX_COOKIE_VALUE_LENGTH];
    }   *valuable;
}   COOKIE_INFO;

COOKIE_INFO *createCookie( void );
void        destroyCookie( COOKIE_INFO *p );
char        *saveCookie( COOKIE_INFO *cp, const char *cookie );
char        *loadCookie( const COOKIE_INFO *cp );

/* for ココログ - コントロールパネル - ファイルマネージャ */
int
loginCocologFiles( const char *username,    // (I) ユーザ名
                   const char *password,    // (I) パスワード
                   char       *cookie );    // (O) クッキー

int
uploadCocologFiles( FILEINF *fileInf, // (I)   アップロードするファイルに関す
                                      //       る情報
                    char    *url,     // (O)   アップロードしたファイルの URL
                    char    *cookie );// (I/O) クッキー

int
deleteCocologFiles( const char *url,        // (I)   削除したいファイルの URL
                    char       *cookie );   // (I/O) クッキー

BOOL
deleteFile( const char *username,   // (I) ユーザ名
            const char *password,   // (I) パスワード
            const char *url );      // (I) 削除したいファイルの URL

/* for ここうさぎウィザード */
int isUsedProxy( void );

/* for bookey */
char    *getCurrentLocation( char *url );   /* (I/O) 直前に参照した URL */

/* for BloGolEe */
void    setConfirmProxyInfoFunc( CONF_FUNC confirmProxyInfo );
BOOL    isNecessaryToCheckProxyInfo( void );

void    setProxyInfo( const char *proxyServer, unsigned short proxyPort,
                      const char *proxyUsername, const char *proxyPassword );

/* for Cjpeg */
size_t  getBinSize();

/* for chirrup */
#ifdef  USE_RURL
char    *
makeRurl( const char *url );    /* rurl.org を利用して短縮URLを生成 */
#endif  /* USE_RURL */

/* for debugging, reporting, ... */
void    dputc( char c );
void    dputs( const char *str );
int     dprintf( const char *format, ... );

/* エラーコード */
#define XMLRPC_ERROR_CHANGED_PROXYINFO  ((DWORD)0xFFBEAF01)

#endif  /* __XML_RPC_H__ */
