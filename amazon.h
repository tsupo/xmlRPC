//  $Header: /comm/xmlRPC/amazon.h 2     09/05/29 7:09 tsupo $
/*! @file
 *  @brief Amazon Web Services 関連各種定義
 *  @author tsujimura543
 *  @date $Date: 09/05/29 7:09 $
 *  @version $Revision: 2 $
 *  @note
 * History:
 * $Log: /comm/xmlRPC/amazon.h $
 * 
 * 2     09/05/29 7:09 tsupo
 * 1.267版
 * 
 * 25    09/05/28 18:37 Tsujimura543
 * バッファオーバーラン対策を強化
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 24    08/02/15 2:42 Tsujimura543
 * MAX_PRODUCTSNAME_LENGTH の値を倍にした
 * 
 * 23    08/02/15 2:16 Tsujimura543
 * avalability → availability に修正 (typo)
 * 
 * 22    05/11/17 19:55 Tsujimura543
 * AMAZON_MODE_MINICAR を AMAZON_NODE_MINICAR に修正
 * 
 * 21    05/09/03 0:24 Tsujimura543
 * コメントを修正、追加
 * 
 * 20    05/09/03 0:02 Tsujimura543
 * さらにコメントを書き直し
 * 
 * 19    05/08/30 19:31 Tsujimura543
 * doxygen + graphviz で日本語を使うデモンストレーションに使うため、若干
 * コメントを修正
 * 
 * 18    05/08/29 17:49 Tsujimura543
 * doxygen 1.4.4(を改造したもの) にて、出力内容(htmlドキュメント)を確認。
 * いったん、fix
 * 
 * 17    05/08/18 16:37 Tsujimura543
 * コメントを doxygen 対応にする作業終了
 * (一部の文字が化ける問題が残っている)
 * 
 * 16    05/08/18 11:37 Tsujimura543
 * コメントを doxygen 対応にする作業、試行錯誤中
 * 
 * 15    05/08/18 11:02 Tsujimura543
 * 試験的にコメントの記述を doxygen 対応にしてみる
 * 
 * 14    05/05/18 18:32 Tsujimura543
 * コメントを修正
 * 
 * 13    05/04/18 16:23 Tsujimura543
 * 「楽天アフィリエイト」関連のコメントを rakuten.c へ移動
 * 
 * 12    05/04/18 16:08 Tsujimura543
 * Google API 関連のコメントを google.c へ移動
 * 
 * 11    05/04/18 15:44 Tsujimura543
 * bidders 関連部分を bidders.h として分離独立させた
 * 
 * 10    04/11/17 15:58 Tsujimura543
 * bidders関連の各種定義を追加
 * 
 * 9     04/11/16 22:49 Tsujimura543
 * 「bidders カテゴリID」の定義を追加
 * 
 * 8     04/11/16 15:19 Tsujimura543
 * bidders Web Service の仕様をコメントの形で掲載
 * 
 * 7     04/11/05 21:40 Tsujimura543
 * Google Web Service API の request と response の例をコメントの形で掲載
 * 
 * 6     04/11/02 18:06 Tsujimura543
 * HEAVY版の averageRating を unsigned long から double に変更
 * 
 * 5     04/11/02 16:53 Tsujimura543
 * 「おもちゃ&ホビー」の主要カテゴリのノード番号の定義を追加
 * 
 * 4     04/11/02 16:39 Tsujimura543
 * HEAVY版構造体修正
 * 
 * 3     04/11/01 19:55 Tsujimura543
 * 検索結果格納用の構造体の定義を追加
 * 
 * 2     04/07/07 11:43 Tsujimura543
 * 版数管理を VSS で行なうようにする 
 */

#ifndef __AMAZON_H__
#define __AMAZON_H__

/** \defgroup amazon Amazon Web Services (AWS) 関連各種定義
 */
/** \defgroup nodeID ノードの種類
 *  \ingroup amazon
 *  Common Amazon.co.jp Browse Nodes
 *  (Amazon.co.jp の主要なノードIDの一覧)
 */
/*
 *  The following is a list of some of our more popular browse nodes for
 *  the Amazon.co.jp Web site.
 */

/** \defgroup books 和書
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>Books, Literature & Fiction 466284</li>
 *      <li>Books, Philosophy & Religion 571582</li>
 *      <li>Books, Society & Politics 571584</li>
 *      <li>Books, Nonfiction 492152</li>
 *      <li>Books, Travel & Geography 466286</li>
 *      <li>Books, Business & Career 466282</li>
 *      <li>Books, Investment & Financial Management 492054</li>
 *      <li>Books, Science 466290</li>
 *      <li>Books, Computer & Internet 466298</li>
 *      <li>Books, Art & Photography 466294</li>
 *      <li>Books, Entertainment 466296</li>
 *      <li>Books, Sports & Hobby 466292</li>
 *      <li>Books, Home & Family 466304</li>
 *      <li>Books, Foreign Language Reference 466302</li>
 *      <li>Books, Education 3148931</li>
 *      <li>Books, Children's Books 466306</li>
 *      <li>Books, Cartoons & Anime 466280</li>
 *      <li>Books, New Releases 466300</li>
 *      <li>Books, Sheet Music 746102</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_FICTION         466284  //!< 文学・評論
#define AMAZON_NODE_PHILOSOPHY      571582  //!< 思想・人文
#define AMAZON_NODE_SOCIETY         571584  //!< 政治・社会
#define AMAZON_NODE_NONFICTION      492152  //!< ノンフィクション
#define AMAZON_NODE_TRAVEL          466286  //!< 歴史・地理・旅行ガイド
#define AMAZON_NODE_BUISINESS       466282  //!< ビジネス・経済
#define AMAZON_NODE_FINANCIAL       492054  //!< 起業・経営
#define AMAZON_NODE_SCIENCE         466290  //!< 科学・テクノロジー
#define AMAZON_NODE_COMPUTER        466298  //!< コンピュータ・インターネット
#define AMAZON_NODE_ART             466294  //!< アート
#define AMAZON_NODE_ENTERTAINMENT   466296  //!< エンターテイメント
#define AMAZON_NODE_SPORTS          466292  //!< 実用・スポーツ
#define AMAZON_NODE_FAMILY          466304  //!< 趣味書
                                /**!< \note
                                 * 「仕様書」では「趣味書」となっているが、
                                 *「家庭・家族」の間違いであると思われる
                                 */
#define AMAZON_NODE_REFERENCE       466302  //!< 参考書・語学・辞事典
#define AMAZON_NODE_EDUCATION       3148931 //!< 教育
#define AMAZON_NODE_CHILDREN        466306  //!< こども
#define AMAZON_NODE_CARTOON         466280  //!< コミック
#define AMAZON_NODE_NEWRELEASE      466300  //!< 新書・文庫
                                /**!< \note
                                 * 「仕様書」では「新書・文庫」となっているが、
                                 * 「新刊」の間違いであると思われる
                                 */
#define AMAZON_NODE_SHEETMUSIC      746102  //!< 楽譜・スコア・ピアノ譜

#define AMAZON_NODE_FOREIGNBOOKS    1000    //!< 洋書
/*@}*/

/** \defgroup foreignBooks 洋書
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>English Books, Arts & Photography 1</li>
 *      <li>English Books, Audiobooks 44</li>
 *      <li>English Books, Biographies & Memoirs 2</li>
 *      <li>English Books, Business & Investing 3</li>
 *      <li>English Books, Children's Books 4</li>
 *      <li>English Books, Computers & Internet 5</li>
 *      <li>English Books, Cooking, Food & Wine 6</li>
 *      <li>English Books, Engineering 13643</li>
 *      <li>English Books, Entertainment 86</li>
 *      <li>English Books, Gay & Lesbian 301889</li>
 *      <li>English Books, Health, Mind & Body 10</li>
 *      <li>English Books, History 9</li>
 *      <li>English Books, Home & Garden 48</li>
 *      <li>English Books, Horror 49</li>
 *      <li>English Books, Law 10777</li>
 *      <li>English Books, Literature & Fiction 17</li>
 *      <li>English Books, Medicine 13996</li>
 *      <li>English Books, Mystery & Thrillers 18</li>
 *      <li>English Books, Nonfiction 53</li>
 *      <li>English Books, Outdoors & Nature 290060</li>
 *      <li>English Books, Parenting & Families 20</li>
 *      <li>English Books, Professional & Technical 173507</li>
 *      <li>English Books, Reference 21</li>
 *      <li>English Books, Religion & Spirituality 22</li>
 *      <li>English Books, Romance 23</li>
 *      <li>English Books, Science 75</li>
 *      <li>English Books, Science Fiction & Fantasy 25</li>
 *      <li>English Books, Sports 26</li>
 *      <li>English Books, Teens 28</li>
 *      <li>English Books, Travel 27</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_E_ART           1     //!< アート
#define AMAZON_NODE_E_AUDIOBOOKS    44    //!< 音の出る本
#define AMAZON_NODE_E_BIOGRAPHY     2     //!< 伝記・回想録
#define AMAZON_NODE_E_BUISINESS     3     //!< ビジネス・経済・起業・経営
#define AMAZON_NODE_E_CHILDREN      4     //!< こども
#define AMAZON_NODE_E_COMPUTER      5     //!< コンピュータ・インターネット
#define AMAZON_NODE_E_COOKING       6     //!< 料理・食事
#define AMAZON_NODE_E_ENGINEERING   13643 //!< 工学・実用
#define AMAZON_NODE_E_ENTERTAINMENT 86    //!< エンターテイメント
#define AMAZON_NODE_E_BLGL          301889//!< 同性愛
#define AMAZON_NODE_E_HEALTH        10    //!< 健康・心と体
#define AMAZON_NODE_E_HISTORY       9     //!< 歴史
#define AMAZON_NODE_E_HOME          48    //!< 家庭・庭園
#define AMAZON_NODE_E_HORROR        49    //!< ホラー
#define AMAZON_NODE_E_LAW           10777 //!< 法律
#define AMAZON_NODE_E_FICTION       17    //!< 文学・評論
#define AMAZON_NODE_E_MEDICINE      13996 //!< 薬
#define AMAZON_NODE_E_MYSTERY       18    //!< ミステリ・スリラー
#define AMAZON_NODE_E_NONFICTION    53    //!< ノンフィクション
#define AMAZON_NODE_E_NATURE        290060//!< アウトドア・自然
#define AMAZON_NODE_E_FAMILY        20    //!< 親学・家族
#define AMAZON_NODE_E_PROFESSIONAL  173507//!< 専門書・技術書
#define AMAZON_NODE_E_REFERENCE     21    //!< 参考書・語学・辞事典
#define AMAZON_NODE_E_RELIGION      22    //!< 宗教・精神論
#define AMAZON_NODE_E_ROMANCE       23    //!< 恋愛
#define AMAZON_NODE_E_SCIENCE       75    //!< 科学・テクノロジー
#define AMAZON_NODE_E_SCIFI         25    //!< SF・ファンタジー
#define AMAZON_NODE_E_SPORTS        26    //!< スポーツ
#define AMAZON_NODE_E_TEENS         28    //!< 思春期
#define AMAZON_NODE_E_TRAVEL        27    //!< 旅行
/*@}*/

/** \defgroup electronics エレクトロニクス
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>Electronics, Digital Cameras 3371371</li>
 *      <li>Electronics, DVD Players 3371441</li>
 *      <li>Electronics, Portable Audio 3371411</li>
 *      <li>Electronics, Computer 3371341</li>
 *      <li>Electronics, PC Peripherals 3371351</li>
 *      <li>Electronics, Printer & Scanner 3371361</li>
 *      <li>Electronics, Network Equipment 3371381</li>
 *      <li>Electronics, PDA 3371401</li>
 *      <li>Electronics, Accessories 3371421</li>
 *      <li>Electronics, Storage & Memory 3371391</li>
 *      <li>Electronics, Audio Visual 3371431</li>
 *      <li>Electronics, Video Game Hardware 3371461</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_EL_DIGITALCAMERA 3371371 //!< デジタルカメラ
#define AMAZON_NODE_EL_DVDPLAYER     3371441 //!< DVDプレーヤー・レコーダー
#define AMAZON_NODE_EL_PORTABLEAUDIO 3371411 //!< ポータブルオーディオ
#define AMAZON_NODE_EL_COMPUTER      3371341 //!< コンピュータ
#define AMAZON_NODE_EL_PERIPHERAL    3371351 //!< PC周辺機器・パーツ
#define AMAZON_NODE_EL_PRINTER       3371361 //!< プリンタ・スキャナ
#define AMAZON_NODE_EL_NETWORK       3371381 //!< ネットワーク機器
#define AMAZON_NODE_EL_PDA           3371401 //!< PDA・電子辞書
#define AMAZON_NODE_EL_ACCESSORY     3371421 //!< アクセサリ・サプライ
#define AMAZON_NODE_EL_STORAGE       3371391 //!< ストレージメディア
#define AMAZON_NODE_EL_AUDIOVISUAL   3371431 //!< オーディオ・ビジュアル
#define AMAZON_NODE_EL_VIDEOGAME     3371461 //!< ゲーム機本体
/*@}*/

/** \defgroup music 音楽
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>Music, J-Pop 569170</li>
 *      <li>Music, Popular 569290</li>
 *      <li>Music, Rock 569292</li>
 *      <li>Music, Hard Rock 569298</li>
 *      <li>Music, Blues & Country 562050</li>
 *      <li>Music, Soul & R&B 569318</li>
 *      <li>Music, Hip Hop 569320</li>
 *      <li>Music, Dance 569322</li>
 *      <li>Music, Jazz Fusion 562052</li>
 *      <li>Music, World 562056</li>
 *      <li>Music, New Age 562064</li>
 *      <li>Music, Soundtracks 562058</li>
 *      <li>Music, Animation 562060</li>
 *      <li>Music, Children & Family 562062</li>
 *      <li>Music, Ballad 569174</li>
 *      <li>Music, Traditional 569186</li>
 *      <li>Music, Sports 899296</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_M_JPOP        569170    //!< J-POP
#define AMAZON_NODE_M_POPULAR     569290    //!< ポピュラー
#define AMAZON_NODE_M_ROCK        569292    //!< ロック
#define AMAZON_NODE_M_HARDROCK    569298    //!< ハードロック
#define AMAZON_NODE_M_BLUES       562050    //!< ブルース・カントリー
#define AMAZON_NODE_M_SOUL        569318    //!< ソウル・リズム&ブルース
#define AMAZON_NODE_M_HIPHOP      569320    //!< ヒップホップ
#define AMAZON_NODE_M_DANCE       569322    //!< ダンス
#define AMAZON_NODE_M_JAZZ        562052    //!< ジャズ・フュージョン
#define AMAZON_NODE_M_WORLD       562056    //!< ワールド
#define AMAZON_NODE_M_NEWAGE      562064    //!< ニューエイジ
#define AMAZON_NODE_M_SOUNDTRACKS 562058    //!< サウンドトラック
#define AMAZON_NODE_M_ANIME       562060    //!< アニメ・ゲーム
#define AMAZON_NODE_M_CHILDREN    562062    //!< キッズ・ファミリー
#define AMAZON_NODE_M_BALLAD      569174    //!< バラード
#define AMAZON_NODE_M_TRADITIONAL 569186    //!< 伝統音楽
#define AMAZON_NODE_M_SPORTS      899296    //!< スポーツ

#define AMAZON_NODE_M_JAPANESE    562044    //!< J-POP・日本の音楽
#define AMAZON_NODE_M_FOREIGN     562046    //!< 海外のロック・ポップス
#define AMAZON_NODE_M_MOODY       562048    //!< ダンス・ソウル・ヒップホップ
#define AMAZON_NODE_M_CLASSIC     562054    //!< クラシック
#define AMAZON_NODE_M_EASYLISTENING 562064  //!< イージーリスニング・その他
/**< \note
 * AMAZON_NODE_M_NEWAGE と AMAZON_NODE_M_EASYLISTENING が共に 562064 
 * なのは変 ?
 */
/*@}*/

/** \defgroup classical クラシック音楽
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>Classical, Classical 701040</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_C_CLASSIC           701040  //!< クラシック
/*@}*/

/** \defgroup dvd DVD
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>DVD, Japanese 562014</li>
 *      <li>DVD, Foreign 562016</li>
 *      <li>DVD, Music 562018</li>
 *      <li>DVD, Animation 562020</li>
 *      <li>DVD, Hobby & Fitness 562022</li>
 *      <li>DVD, Sports 562024</li>
 *      <li>DVD, Family 562026</li>
 *      <li>DVD, TV Documentary 562028</li>
 *      <li>DVD, Box Sets 564522</li>
 *      <li>DVD, Adult 896246</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_D_JAPANESE      562014  //!< 日本映画
#define AMAZON_NODE_D_FOREIGN       562016  //!< 外国映画
#define AMAZON_NODE_D_MUSIC         562018  //!< 音楽・ステージ
#define AMAZON_NODE_D_ANIME         562020  //!< アニメ
#define AMAZON_NODE_D_HOBBY         562022  //!< ホビー・実用
#define AMAZON_NODE_D_SPORTS        562024  //!< スポーツ・フィットネス
#define AMAZON_NODE_D_FAMILY        562026  //!< キッズ・ファミリー
#define AMAZON_NODE_D_DOCUMENTARY   562028  //!< TV・ドキュメンタリー
#define AMAZON_NODE_D_BOXSETS       564522  //!< DVDボックス
#define AMAZON_NODE_D_ADULT         896246  //!< アダルト

#define AMAZON_NODE_D_IDOL          562030  //!< アイドル・イメージ・その他
/*@}*/

/** \defgroup video ビデオ
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>VHS, Japanese 561984</li>
 *      <li>VHS, Foreign 561986</li>
 *      <li>VHS, Music 561988</li>
 *      <li>VHS, Animation 561990</li>
 *      <li>VHS, Hobby & Fitness 561992</li>
 *      <li>VHS, Sports 561994</li>
 *      <li>VHS, Family 561996</li>
 *      <li>VHS, TV Documentary 561998</li>
 *      <li>VHS, Imports 564546</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_V_JAPANESE      561984  //!< 日本映画
#define AMAZON_NODE_V_FOREIGN       561986  //!< 外国映画
#define AMAZON_NODE_V_MUSIC         561988  //!< 音楽・ステージ
#define AMAZON_NODE_V_ANIME         561990  //!< アニメ
#define AMAZON_NODE_V_HOBBY         561992  //!< ホビー・実用
#define AMAZON_NODE_V_SPORTS        561994  //!< スポーツ・フィットネス
#define AMAZON_NODE_V_FAMILY        561996  //!< キッズ・ファミリー
#define AMAZON_NODE_V_DOCUMENTARY   561998  //!< TV・ドキュメンタリー
#define AMAZON_NODE_V_IMPORTS       564546  //!< 輸入物

#define AMAZON_NODE_V_IDOL          562000  //!< アイドル・イメージ・その他
/*@}*/

/** \defgroup software ソフトウェア
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>Software, Games 689132</li>
 *      <li>Software, Children's 1040140</li>
 *      <li>Software, Hobby 637656</li>
 *      <li>Software, Foreign Language Training 637658</li>
 *      <li>Software, Internet 637648</li>
 *      <li>Software, General Business 637644</li>
 *      <li>Software, Industry-Specific Business 1040106</li>
 *      <li>Software, Graphics 637652</li>
 *      <li>Software, Music 637654</li>
 *      <li>Software, Utility 637662</li>
 *      <li>Software, Network Management 1040116</li>
 *      <li>Software, Programming 637650</li>
 *      <li>Software, Operating System 637666</li>
 *      <li>Software, Macintosh 3137861</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_S_GAME              689132  //!< ゲーム
#define AMAZON_NODE_S_CHILDREN          1040140 //!< 知育
#define AMAZON_NODE_S_HOME              637656  //!< ホーム・実用
                            /**< \note 
                             * 「仕様書」では「ホーム・実用」となっているが、
                             *「趣味」の間違いであると思われる
                             */
#define AMAZON_NODE_S_EDUCATION         637658  //!< 教育・ホビー
                            /**< \note
                             * 「仕様書」では「教育・ホビー」となっているが、
                             * 「外国語学習」の間違いであると思われる
                             */
#define AMAZON_NODE_S_INTERNET          637648  //!< Web開発
#define AMAZON_NODE_S_BUISENESS         637644  //!< ビジネス・オフィス
#define AMAZON_NODE_S_INDUSTORIAL       1040140
                                             //!< 工場向け・生産管理・品質管理
#define AMAZON_NODE_S_GRAPHICS          637652  //!< グラフィックス
#define AMAZON_NODE_S_MUSIC             637654  //!< 映像・音楽
#define AMAZON_NODE_S_UTILITY           637662  //!< ユーティリティ
#define AMAZON_NODE_S_NETWORKMANAGEMENT 1040116 //!< ネットワーク管理
#define AMAZON_NODE_S_PROGRAMMING       637650  //!< プログラミング
#define AMAZON_NODE_S_OPERATINGSYSTEM   637666  //!< OS
#define AMAZON_NODE_S_MACINTOSH         3137861 //!< Macintosh

#define AMAZON_NODE_S_NETWORK           637646  //!< 通信・ネットワーク
#define AMAZON_NODE_S_SECURITY          637664  //!< セキュリティ
#define AMAZON_NODE_S_LINUX             689118  //!< Linux
/*@}*/

/** \defgroup games ビデオゲーム
 *  \ingroup nodeID
 *  ノードID一覧
 *    <ul>
 *      <li>Video Games, Play Station 2 637874</li>
 *      <li>Video Games, Play Station 637876</li>
 *      <li>Video Games, Nintendo Gamecube 637878</li>
 *      <li>Video Games, Game Boy Advance 637880</li>
 *      <li>Video Games, Game Boy 637882</li>
 *      <li>Video Games, Xbox 639096</li>
 *      <li>Video Games, Other 637886</li>
 *    </ul>
 *  \note 上記のノードIDは AWS の仕様書に掲載されているものであるが、
 *      実際に使用されているノードIDは別の値に変更されていることがあるので注意
 */
/*@{*/
#define AMAZON_NODE_PS2             637874  //!< PlayStation2
#define AMAZON_NODE_PLAYSTATION     637876  //!< PlayStation
#define AMAZON_NODE_GAMECUBE        637878  //!< NINTENDO GAMECUBE
#define AMAZON_NODE_GBA             637880  //!< GAMEBOY ADVANCE
#define AMAZON_NODE_GAMEBOY         637882  //!< GAMEBOY
#define AMAZON_NODE_XBOX            637884  //!< Xbox (639096 の間違い?)
#define AMAZON_NODE_ANOTHERMACHINE  637886  //!< その他の機種
/*@}*/

/** \defgroup kitchen  キッチン
 *  \ingroup nodeID
 */
/*@{*/
#define AMAZON_NODE_KITCHEN     3895781 //!< キッチン用品
#define AMAZON_NODE_COOKING     3895771 //!< 調理機器
#define AMAZON_NODE_HAIR        3895751 //!< 理美容グッズ
#define AMAZON_NODE_HEALTH      3895741 //!< 健康グッズ
#define AMAZON_NODE_LIVING      3895791 //!< 生活家電
#define AMAZON_NODE_SEASON      3895761 //!< 季節家電
#define AMAZON_NODE_LIGHT       4082801 //!< 照明器具
#define AMAZON_NODE_ACCESSORY   3895801 //!< 消耗品・アクセサリ
/*@}*/

/** \defgroup toys おもちゃ & ホビー
 *  \ingroup nodeID
 */
/*@{*/
#define AMAZON_NODE_TOYS            13299531    //!< おもちゃ & ホビー
#define AMAZON_NODE_EDU_TOYS        13321671    //!< 知育玩具
#define AMAZON_NODE_DOLLS           13321731    //!<人形・ミニドール
#define AMAZON_NODE_COSTUMEPLAY     13321761    //!< 変身・なりきり
#define AMAZON_NODE_ACTIONFIGURE    13321821    //!< アクションフィギュア
#define AMAZON_NODE_MINICAR         13321831    //!< ミニカー・車
#define AMAZON_NODE_GAMES           637394      //!< ゲーム
/*@}*/

/**
 *  \defgroup amazonSearch 検索結果格納用構造体
 *  \ingroup amazon
 */
/** \defgroup stringLength 検索結果文字列最大長
 *  \ingroup amazonSearch
 */
/*@{*/
#define MAX_PRODUCTSNAME_LENGTH 256  //!< 「商品名、書名」最大長
#define MAX_AUTHORINFO_LENGTH   128  //!< 「作者、編者」最大長
#define MAX_MANUFACTURER_LENGTH 128  //!< 「発行元、発売元」最大長
#define MAX_PRICE_LENGTH        48   //!< 「定価、販売価格」最大長
#define MAX_NODEID_LENGTH       16   //!< 「ノードID」最大長
#define MAX_NODENAME_LENGTH     80   //!< 「ジャンル名」最大長
#define MAX_MEDIALEN            40   //!< 「販売形態」最大長
#define MAX_COMMENT_LENGTH      4096 //!< 「評者のコメント」最大長

#define MAX_NUMOFNODES          12   //!< 最大関連ジャンル数
#define MAX_NUMOFREVIEWS        3    //!< 最大(取得可能)レビュー数
/*@}*/

/** \defgroup liteType 検索結果格納用(軽量版)
 *  \ingroup amazonSearch
 */
/*@{*/
//! LITEタイプ
/** type を lite に指定して検索したときの検索結果を格納する */
typedef struct amazonSearchResultLite   {
    char    url[MAX_URLLENGTH_MAX];                //!< 商品ページURL
    char    asin[MAX_NAMELEN];                     //!< ASIN
    char    productName[MAX_PRODUCTSNAME_LENGTH];  //!< 商品名、書名
    char    authors[MAX_AUTHORINFO_LENGTH];        //!< 作者、編者
    char    releaseDate[MAX_DATELENGTH];           //!< 発行年月日
    char    manufacturer[MAX_MANUFACTURER_LENGTH]; //!< 発行元、発売元
    char    imageURLsmall[MAX_URLLENGTH];          //!< 小さな画像のURL
    char    imageURLmedium[MAX_URLLENGTH];        //!< 普通サイズの画像のURL
    char    imageURLlarge[MAX_URLLENGTH];          //!< 大きな画像のURL
    char    availability[MAX_LOGICALLINELEN];      //!< 在庫状況
    char    listPrice[MAX_PRICE_LENGTH];           //!< 定価
    char    amazonPrice[MAX_PRICE_LENGTH];         //!< 販売価格
    char    usedPrice[MAX_PRICE_LENGTH];//!< マーケットプレイスでの販売価格最低値
}   AMAZON_LITE, *AMAZON_LITE_t;
/*@}*/

/** \defgroup heavyType 検索結果格納用(重量版)
 *  \ingroup amazonSearch
 */
/*@{*/
//! HEAVYタイプ
/** type を heavy に指定して検索したときの検索結果を格納する */
typedef struct amazonSearchResultHeavy  {
    char    url[MAX_URLLENGTH_MAX];              //!< 商品ページURL
    char    asin[MAX_NAMELEN];                   //!< ASIN
    char    productName[MAX_PRODUCTSNAME_LENGTH];//!< 商品名、書名
    char    authors[MAX_AUTHORINFO_LENGTH];      //!< 作者、編者
    char    releaseDate[MAX_DATELENGTH];         //!< 発行年月日
    char    manufacturer[MAX_MANUFACTURER_LENGTH];//!< 発行元、発売元
    char    imageURLsmall[MAX_URLLENGTH];        //!< 小さな画像のURL
    char    imageURLmedium[MAX_URLLENGTH];       //!< 普通サイズの画像のURL
    char    imageURLlarge[MAX_URLLENGTH];        //!< 大きな画像のURL
    char    availability[MAX_LOGICALLINELEN];    //!< 在庫状況
    char    listPrice[MAX_PRICE_LENGTH];         //!< 定価
    char    amazonPrice[MAX_PRICE_LENGTH];       //!< 販売価格
    char    usedPrice[MAX_PRICE_LENGTH]; //!< マーケットプレイスでの販売価格最低値
    unsigned long   salesRank;                   //!< 売り上げ順位

    long    numOfBrowseNodes;                    //!< ノード数

    /** \struct browseList amazon.h "amazon.h"
     *  \brief ノード(ジャンル)
     *
     *      browseNodeSearch 用の「ノードID」とそのノードIDに対応する
     *      「ジャンル名」を保持します
     */
    struct browseList   {
        char    browseNode[MAX_NODEID_LENGTH];   //!<    ノードID
        char    nodeName[MAX_NODENAME_LENGTH];   //!<    ジャンル名
    }   browseNodes[MAX_NUMOFNODES];             //!< ノード

    char    media[MAX_MEDIALEN];                 //!< 販売形態
    char    isbn[MAX_NAMELEN];                   //!< ISBN

    /** \struct reviewsOnAmazon amazon.h "amazon.h"
     *  \brief レビュー
     *
     *      当該書籍・商品に関するレビューの一覧(配列)
     */
    struct reviewsOnAmazon {
        double          averageRating;           //!<    全評者の評価の平均
        unsigned long   numOfReviews;            //!<    レビュー数

        /** \struct reviewOnAmazon amazon.h "amazon.h"
         *  \brief  1評者のレビュー
         *
         *      評者の評価、コメント、評者自身に関する情報を保持します
         */
        struct reviewOnAmazon {
            unsigned long   rating;              //!<      評価 (5段階)
            char    summury[MAX_LOGICALLINELEN]; //!<      評者に関する情報
            char    comment[MAX_COMMENT_LENGTH]; //!<      評者のコメント
        }   review[MAX_NUMOFREVIEWS];            //!<    評者毎のレビュー
    }       reviews;                             //!< 全評者のレビュー

    char    similarProcducts[MAX_LOGICALLINELEN];//!< 関連商品のASIN (複数)
}   AMAZON_HEAVY, *AMAZON_HEAVY_t;
/*@}*/


/*
 * AWS parameters
 *
 *  Parameter Types
 *      This section shows the various parameter types that can be used with
 *      Amazon.com Web Services.
 *
 *    REST Parameter    SOAP Element    Description
 *
 *      t                   tag                 Associates tag
 *      ct                  N/A                 Content-type for returned data
 *                                               (important for those who use 
 *                                                XSL or are using proprietary
 *                                                systems that can't handle 
 *                                                the text/HTML content type)
 *      dev-t               devtag              Developer token
 *      sort                sort                Sort type 
 *      mode                mode                Product line
 *      type                type                Output type
 *      f                   N/A                 Output format
 *      page                page                Result page
 *      offer               offer               The offer parameter is used to
 *                                              request and limit the types of
 *                                              offerings returned as part of
 *                                              an ASIN search. If the offer 
 *                                              parameter is not supplied then
 *                                              the returned data does not 
 *                                              include any offering 
 *                                              information. If the parameter
 *                                              is supplied it must be one of
 *                                              the following values: 
 *                                                  1.       ThirdPartyNew
 *                                                  2.       Used
 *                                                  3.       Collectible
 *                                                  4.       Refurbished
 *                                                  5.       All
 *      offerpage           offerpage           The offerpage parameter is 
 *                                              used to request a particular 
 *                                              page of offering information. 
 *                                              The default value is 1; 25 
 *                                              offerings are returned per 
 *                                              page. 
 *                                              To put offer and offerpage 
 *                                              together, consider the  
 *                                              following page:
 *                                                  http://www.amazon.com/exec/obidos/tg/stores/offering/list/-/0385503822/used/ref%3Dbuy%5Fpb%5Fu%5F
 *                                              The offer parameter selects 
 *                                              a single "tab" of info 
 *                                              (Used/New/Collectible). Then 
 *                                              the offerpage selects 
 *                                              successive chunks of 25 offers
 *                                              within the page. 
 *      offerstatus         offerstatus         The offerstatus parameter is 
 *                                              used to request either open  
 *                                              (value ="open") or closed 
 *                                              (value="closed") offers when
 *                                              requesting information about
 *                                              a seller using the 
 *                                              SellerSearch request (REST) or
 *                                              a SellerRequest (SOAP).
 *      keywords            keywords            The keyword parameter is used
 *                                              in SellerSearch requests, and
 *                                              allows the user to filter 
 *                                              a specific seller's products 
 *                                              by a keyword. 
 *      N/A                 seller-browse-id    The seller-browse-id parameter
 *                                              is used in SellerSearch 
 *                                              requests, and allows the user 
 *                                              to filter a specific seller's
 *                                              products by a browse ID. 
 *                                              Seller browse IDs use
 *                                              a different taxonomy than 
 *                                              Amazon.com retail? to view the
 *                                              seller browse ID tree, please 
 *                                              go here:
 *                                                  http://s1.amazon.com/exec/varzea/ts/browse-zshops/68280
 *                                              The ID is the number after the
 *                                              "browse-zshops" string.
 *      locale              locale              International locale specifier
 *      price               price               The price parameter may be 
 *                                              used to narrow search results 
 *                                              within a price range, 
 *                                              specified in pennies (i.e., 
 *                                              price=3200-3500 narrows search
 *                                              results to products with 
 *                                              an OurPrice between $32.00 and
 *                                              $35.00 (may be used with 
 *                                              foreign currencies as well))
 *      desc                desc                Include the desc parameter in 
 *                                              Seller Profile Search, Seller 
 *                                              Search, or Marketplace Search
 *                                              to retrieve marketplace 
 *                                              exchange descriptions. 
 *      sims                sims                Include the sims parameter in
 *                                              a remote shopping cart add, 
 *                                              get, or modify request to get
 *                                              a list of ASINs that represent
 *                                              the intersection of the 
 *                                              current cart ASINs' 
 *                                              similarities. 
 *      CartId              CartId              Unique identifier for 
 *                                              an Amazon shopping cart. For
 *                                              use in remote shopping cart 
 *                                              requests. This parameter and 
 *                                              the HMAC parameter must be 
 *                                              included in any request to
 *                                              an existing Amazon remote 
 *                                              shopping cart.  
 *      Hmac                HMAC                Security token that, coupled
 *                                              with the CartId, is required 
 *                                              to make requests to 
 *                                              an existing remote shopping 
 *                                              cart. 
 *      Item                Item                The Item parameter allows
 *                                              a user to modify or remove
 *                                              an item from an Amazon remote
 *                                              shopping cart. Please see the
 *                                              documentation for more 
 *                                              information. 
 *      index               index               This parameter may be used in
 *                                              Seller Search and Marketplace
 *                                              Search to narrow search 
 *                                              results so that they come from
 *                                              only zShops (index=zshops) or
 *                                              only marketplace
 *                                              (index=marketplace). 
 *      keyword             keyword             Specify search terms for 
 *                                              Marketplace Search in this 
 *                                              parameter. Note: This is 
 *                                              different than the "keywords"
 *                                              parameter above. 
 *      keyword-search      keyword_search      This parameter may be used in
 *                                              Marketplace Search to ensure 
 *                                              search results are based on 
 *                                              product titles only 
 *                                              (keyword-search=title) or on
 *                                              product title and description
 *                                              (keyword-search=titledesc). 
 *      browse-id           browse_id           Use this parameter to specify
 *                                              a marketplace browse ID for
 *                                              Marketplace Search. 
 *      zipcode             zipcode             Use this parameter to retrieve
 *                                              products from sellers located
 *                                              in a particular ZIP code. 
 *      area-id             area_id             Use this parameter to specify
 *                                              a numerical country code 
 *                                              representing the country from
 *                                              which or to which you wish the
 *                                              search results to be shipped. 
 *                                              This parameter must be used in
 *                                              combination with the "geo" 
 *                                              parameter.
 *      geo                 geo                 Use this parameter to specify
 *                                              whether you would like the 
 *                                              search results to include 
 *                                              products that are shippable
 *                                              from (geo=ship-from) or to
 *                                              (geo=ship-to) the country 
 *                                              specified by the country code
 *                                              in the "area_id" parameter.  
 *      listing-id          listing_id          Use this parameter to query
 *                                              for information about
 *                                              a specific zShops listing. 
 *      BrowseNodeSearch    browse_node         Browse node search specifier
 *      SellerSearch        seller_id           Seller search specifier
 *      AsinSearch          asin                ASIN/ISBN search specifier
 *      UpcSearch           upc                 UPC search specifier
 *      ExchangeSearch      exchange_id         Exchange search specifier
 *      AuthorSearch        author              Author search specifier
 *      ArtistSearch        artist              Artist/Musician search 
 *                                              specifier
 *      ActorSearch         actor               Actor/Actress search specifier
 *      DirectorSearch      director            Director search specifier
 *      ManufacturerSearch  manufacturer        Manufacturer search specifier
 *      ListmaniaSearch     lm_id               Listmania search specifier
 *      SimilaritySearch    asin                Similarity search specifier
 *      SellerProfile       seller_id           The SellerProfile parameter 
 *                                              requests request for 
 *                                              information about a particular
 *                                              seller. The value of the 
 *                                              parameter is an encrypted 
 *                                              representation of the Seller
 *                                              ID. 
 *      WishlistSearch      wishlist_id         Wish list query specifier
 *      PowerSearch         power               Power search query specifier
 *      MarketplaceSearch   marketplace_search  Marketplace or zShops search
 *                                              specifier 
 *      BlendedSearch       blended             All product search specifier 
 *      TextStreamSearch    textStream          Search specifier for request
 *                                              that allows the user to search
 *                                              for Amazon products with 
 *                                              product details that match
 *                                              a chunk of text. 
 *
 */

#endif  /* __AMAZON_H__ */
