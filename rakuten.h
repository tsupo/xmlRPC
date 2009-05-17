//  $Header: /comm/xmlRPC/rakuten.h 1     09/05/14 3:46 tsupo $
/*! @file
 *  @brief for Rakuten Web Services
 *  @author tsujimura543
 *  @date $Date: 09/05/14 3:46 $
 *  @version $Revision: 1 $
 *  @note
 * History:
 * $Log: /comm/xmlRPC/rakuten.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     07/02/21 19:45 Tsujimura543
 * catalogSearchOnRakutenWebAPI 用の「ソート順」の定義を追加
 * 
 * 8     07/02/21 19:05 Tsujimura543
 * RAKUTEN_CATALOG 構造体の catalogName と catalogCaption も増量
 * 
 * 7     07/02/21 19:03 Tsujimura543
 * RAKUTEN_ITEM 構造体の itemName と itemCaption の格納領域を各々増量
 * 
 * 6     07/02/20 22:32 Tsujimura543
 * catalogSearchOnRakutenWebAPI() の引数を1個(carrier)削除
 * 
 * 5     07/02/20 21:20 Tsujimura543
 * 楽天ウェブサービスのうち、ItemSearch と GenreSearch を実装
 * (動作は未確認)
 * 
 * 4     07/02/19 20:56 Tsujimura543
 * 2006年12月開始の「楽天ウェブサービス」API向け構造体の定義(暫定版)を追加
 * 
 * 3     05/09/02 21:11 Tsujimura543
 * コメントを追加
 * 
 * 2     05/09/02 14:17 Tsujimura543
 * doxygen 向けにコメントを書き換え
 * 
 * 1     05/05/18 21:44 Tsujimura543
 * 検索結果格納用構造体の定義を用意
 */

#ifndef __RAKUTEN_H__
#define __RAKUTEN_H__
#include "amazon.h"

/*
 * 楽天ブックス salesranking
 *
 *  http://xml.affiliate.rakuten.co.jp/?type=種別&service=books&hash=アフィリエイトID&genre=ジャンルコード&num=件数
 *
 *   ex)
 *    http://xml.affiliate.rakuten.co.jp/?type=html&service=books&hash=0008a695.5601c7dd&genre=0&num=10
 *    http://xml.affiliate.rakuten.co.jp/?type=xml&service=books&hash=0008a695.5601c7dd&genre=0&num=10
 *
 *      種別
 *          html: HTML で応答
 *          xml: XML で応答
 *      ジャンルコード
 *          0: 総合
 *          1: コミック・ジュブナイル
 *          2: 語学・就職・資格試験
 *          3: 絵本・児童書
 *          4: 文芸・ノンフィクション
 *          5: ＰＣ・システム開発
 *          6: ビジネス・経済・経営
 *          7: 旅行・紀行・アウトドア
 *          8: 学問がわかる本
 *          9: ホビー・スポーツ
 *         10: ライフスタイル
 *         11: エンターテイメント
 *         12: 専門書・学術書
 *         13: 写真集・タレント
 *      件数
 *          1 ～ 10 (10 より大きな値を指定すると 10 を指定したものとみなす)
 *
 *      注意:
 *          文字コードは html の場合、EUC-JP; xml の場合、UTF-8
 *
 *      応答例 (xml)
 *          <?xml version="1.0" encoding="UTF-8" standalone="yes" ?> 
 *          <RWS version="1.0.0" type="SalesRanking" service="楽天ブックス" date="2004/05/10">
 *          <item>
 *              <Isbn>4915512517</Isbn> 
 *              <SalesRank>1</SalesRank> 
 *              <Url>http://pt.afl.rakuten.co.jp/c/0008a695.5601c7dd/?url=http%3A%2F%2Fbooks.rakuten.co.jp%2FRBOOKS%2F0001654002%2F</Url> 
 *              <ProductName>【予約】 ハリー・ポッターと不死鳥の騎士団</ProductName> 
 *              <Manufacturer>静山社</Manufacturer> 
 *              <ImageUrlSmall>http://image.books.rakuten.co.jp/books/com/images/goods/91551251.jpg</ImageUrlSmall> 
 *              <ListPrice>4200</ListPrice> 
 *              <Authors>
 *                  <Author id="1" name="Ｊ．Ｋ．ローリング" /> 
 *              </Authors>
 *          </item>
 *          </RWS>
 */


/**
 *  \defgroup rakutenSearch 「楽天ブックス」検索結果格納用構造体
 */
/** \defgroup rakutenTypeHtml 検索結果格納用構造体(RAKUTEN_TYPE_HTML 用)
 *  \ingroup rakutenSearch
 */
/*@{*/
//! 検索結果格納用構造体(軽量版)
typedef struct rakutenSearchResultLite  {
    char    url[MAX_URLLENGTH];                    //!< 商品ページURL
    char    productName[MAX_PRODUCTSNAME_LENGTH];  //!< 商品名、書名
}   RAKUTEN_LITE, *RAKUTEN_LITE_t;
/*@}*/

/** \defgroup rakutenTypeXml 検索結果格納用構造体(RAKUTEN_TYPE_XML 用)
 *  \ingroup rakutenSearch
 */
/*@{*/
//! 検索結果格納用構造体(重量版)
typedef struct rakutenSearchResultHeavy {
    char    url[MAX_URLLENGTH];                    //!< 商品ページURL
    char    isbn[MAX_NAMELEN];                     //!< ISBN
    char    productName[MAX_PRODUCTSNAME_LENGTH];  //!< 商品名、書名
    char    authors[MAX_AUTHORINFO_LENGTH];        //!< 作者、編者
    char    manufacturer[MAX_MANUFACTURER_LENGTH]; //!< 発行元、発売元
    char    imageURLsmall[MAX_URLLENGTH];          //!< 小さな画像のURL
    char    listPrice[MAX_PRICE_LENGTH];           //!< 定価
    unsigned long   salesRank;                     //!< 売り上げ順位
}   RAKUTEN_HEAVY, *RAKUTEN_HEAVY_t;
/*@}*/


/** \defgroup rakutenWebAPI 楽天ウェブサービス 関連各種定義
 */
/*
 *  楽天ウェブサービス
 */

/** \defgroup areaLength 文字列格納領域最大長
 *  \ingroup rakutenWebAPI
 */
/*@{*/
#define RAKUTEN_VERSION_LEN 12      //!< 「バージョン」最大長
#define RAKUTEN_DTIME_LEN   20      //!< 「日時」最大長
#define RAKUTEN_OPE_LEN     24      //!< 「操作」最大長
#define RAKUTEN_NAME_LEN    128     //!< 「メーカー名」、「シリーズ名」最大長
#define RAKUTEN_STATMSG_LEN 1024    //!< 「実行結果ステータス詳細」最大長
/*@}*/

/** \defgroup sortOrder ソート順
 *  \ingroup rakutenWebAPI
 */
/*@{*/
// item 用
#define RAKUTEN_SORT_AFFRATE_ASCENDING  1   //!< アフィリエイト料率順(昇順) +affiliateRate
#define RAKUTEN_SORT_AFFRATE_DESCENDING 2   //!< アフィリエイト料率順(降順) -affiliateRate
#define RAKUTEN_SORT_RVCNT_ASCENDING    3   //!< レビュー件数順(昇順) +reviewCount
#define RAKUTEN_SORT_RVCNT_DESCENDING   4   //!< レビュー件数順(降順) -reviewCount
#define RAKUTEN_SORT_PRICE_ASCENDING    5   //!< 価格順(昇順) +itemPrice
#define RAKUTEN_SORT_PRICE_DESCENDING   6   //!< 価格順(降順) -itemPrice
#define RAKUTEN_SORT_DTIME_ASCENDING    7   //!< 商品更新日時順(昇順) +updateTimestamp
#define RAKUTEN_SORT_DTIME_DESCENDING   8   //!< 商品更新日時順(降順) -updateTimestamp

// catalog 用
#define RAKUTEN_SORT_RDATE_ASCENDING    17  //!< カタログ登録順(昇順) +registerDate
#define RAKUTEN_SORT_RDATE_DESCENDING   18  //!< カタログ登録順(降順) -registerDate
#define RAKUTEN_SORT_RLDATE_ASCENDING   19  //!< 発売日が古い順   +releaseDate
#define RAKUTEN_SORT_RLDATE_DESCENDING  20  //!< 発売日が新しい順 -releaseDate
#define RAKUTEN_SORT_RVNUM_ASCENDING    21  //!< レビュー件数順(昇順) +reviewNum
#define RAKUTEN_SORT_RVNUM_DESCENDING   22  //!< レビュー件数順(降順) -reviewNum

// item, catalog 共用
#define RAKUTEN_SORT_RANDOM_ORDER       33   //!< ランダム順 random
/*@}*/

/** \defgroup rakutenItem 商品個別情報格納用構造体
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! 商品個別情報
typedef struct rakutenItem  {
    // 商品情報
    char    itemName[MAX_DESCRIPTION_LEN];      //!< 商品名
    char    itemCode[MAX_KEYLENGTH];            //!< 商品コード (例 book:11918897)
    int     itemPrice;                          //!< 商品価格
    char    itemCaption[MAX_CONTENT_SIZE];      //!< 商品説明文
    char    itemUrl[MAX_URLLENGTH];             //!< 商品URL
    char    affiliateUrl[MAX_URLLENGTH];        //!< アフィリエイトURL 
    BOOL    imageFlag;                          //!< 商品画像有無フラグ
    char    smallImageUrl[MAX_URLLENGTH];       //!< 商品画像URL 64x64 
    char    mediumImageUrl[MAX_URLLENGTH];      //!< 商品画像URL 128x128 
    BOOL    availability;                       //!< 販売可能フラグ
    BOOL    taxFlag;                            //!< 消費税フラグ
    BOOL    postageFlag;                        //!< 送料フラグ
    BOOL    creditCardFlag;                     //!< クレジットカード利用可能フラグ
    BOOL    shopOfTheYearFlag;                  //!< ショップオブザイヤーフラグ
    double  affiliateRate;                      //!< アフィリエイト利用利率
    char    startTime[RAKUTEN_DTIME_LEN];       //!< 販売開始時刻 YYYY-MM-DD HH:MM形式
    char    endTime[RAKUTEN_DTIME_LEN];         //!< 販売終了時刻 YYYY-MM-DD HH:MM形式
    int     reviewCount;                        //!< レビュー件数
    double  reviewAverage;                      //!< レビュー平均
    // 店舗情報
    char    shopName[MAX_LOGICALLINELEN];       //!< 店舗名
    char    shopCode[MAX_KEYLENGTH];            //!< 店舗コード
    char    shopUrl[MAX_URLLENGTH];             //!< 店舗URL
    // ジャンル情報
    int     genreId;                            //!< ジャンルID
}   RAKUTEN_ITEM;
/*@}*/

/** \defgroup rakutenCatalog カタログ情報格納用構造体
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! カタログ情報
typedef struct rakutenCatalog   {
    // 商品情報
    char    catalogName[MAX_DESCRIPTION_LEN];   //!< カタログ名称
    char    catalogCode[MAX_KEYLENGTH];         //!< カタログコード
    char    modelNo[MAX_KEYLENGTH];             //!< 型番
    char    makerName[RAKUTEN_NAME_LEN];        //!< メーカー名
    char    seriesName[RAKUTEN_NAME_LEN];       //!< シリーズ名
    char    onSaleDate[MAX_LOGICALLINELEN];     //!< 発売日
    int     catalogPrice;                       //!< 標準価格 (オープン価格のとき -1)
    char    catalogCaption[MAX_CONTENT_SIZE];   //!< カタログ説明文
    char    catalogUrl[MAX_URLLENGTH];          //!< カタログURL
    BOOL    imageFlag;                          //!< カタログ画像有無フラグ
    char    smallImageUrl[MAX_URLLENGTH];       //!< カタログ画像URL 64x64
    char    mediumImageUrl[MAX_URLLENGTH];      //!< カタログ画像URL 128x128
    int     reviewCount;                        //!< レビュー件数
    // ジャンル情報
    int     genreId;                            //!< ジャンルID
}   RAKUTEN_CATALOG;
/*@}*/

/** \defgroup rautenGenre ジャンル情報格納用構造体
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! カタログ情報
typedef struct rautenGenre  {
    int     genreId;                        //!< ジャンルID
    char    genreName[MAX_LOGICALLINELEN];  //!< ジャンル名
    int     genreLevel;                     //!< ジャンル階層
}   RAKUTEN_GENRE;
/*@}*/


/** \defgroup rakutenSearchRequest 検索要求格納用構造体 (ItemSearch, BookSearch, CDSearch, DVDSearch, CatalogSearch用)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! 検索要求格納用構造体・その1 (2007-02-14版)
typedef struct rakutenSearchRequest {
    // 共通パラメータ
    char    developerId[MAX_NAMELEN + 1];   //!< デベロッパーID
    char    affiliateId[MAX_KEYLENGTH];     //!< アフィリエイトID
    char    operation[RAKUTEN_OPE_LEN];     //!< 操作
    // サービス固有パラメータ   -- ItemSearch, BookSearch, CDSearch, DVDSearch, CatalogSearch
    char    keyword[MAX_DESCRIPTION_LEN];   //!< 検索キーワード
    char    version[RAKUTEN_VERSION_LEN];   //!< バージョン
    char    shopCode[MAX_NAMELEN];          //!< ショップコード (ItemSearchのみ)
    long    genreId;                        //!< ジャンルID
    char    catalogCode[MAX_KEYLENGTH];     //!< カタログコード (ItemSearchのみ)
    int     hits;                           //!< 1ページあたりの取得件数
    int     page;                           //!< 取得ページ (1以上100以下)
    int     sort;                           //!< ソート
    long    minPrice;                       //!< 最小価格
    long    maxPrice;                       //!< 最大価格
    int     availability;                   //!< 販売可能フラグ
    int     field;                          //!< 検索フィールド
    int     carrier;                        //!< キャリア
    int     imageFlag;                      //!< 商品画像有無フラグ
    int     releaseRange;                   //!< 発売時期 (CatalogSearchのみ)
}   RAKUTEN_API_REQUEST;
/*@}*/  // BookSearch, CDSearch, DVDSearch は「楽天ブックス」のみが検索対象となる

/** \defgroup rakutenSearchResponse 検索結果格納用構造体 (ItemSearch, BookSearch, CDSearch, DVDSearch用)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! 検索結果格納用構造体・その1 (2007-02-14版)
typedef struct rakutenSearchResponse {
    char            status[MAX_NAMELEN];            //!< 実行結果ステータス
    char            statusMsg[RAKUTEN_STATMSG_LEN]; //!< 実行結果ステータス詳細
    int             count;                          //!< 検索結果の総商品数 
    int             page;                           //!< 現在のページ番号 
    int             first;                          //!< 検索結果の何件目からか 
    int             last;                           //!< 検索結果の何件目までか 
    int             hits;                           //!< 一度に返却する商品数 
    int             carrier;                        //!< キャリア (PC=0 or mobile=1)
    int             pageCount;                      //!< 総ページ数 (最大100)
    int             numOfItems;                     //!< 取得した商品情報の数
    RAKUTEN_ITEM    *item;                          //!< 商品情報 + 店舗情報 + ジャンル情報
}   RAKUTEN_API_RESPONSE;
/*@}*/

/** \defgroup rakutenSearchResponse1 検索結果格納用構造体 (CatalogSearch用)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! 検索結果格納用構造体・その1-亜種 (2007-02-14版)
typedef struct rakutenSearchResponse1 {
    char            status[MAX_NAMELEN];            //!< 実行結果ステータス
    char            statusMsg[RAKUTEN_STATMSG_LEN]; //!< 実行結果ステータス詳細
    int             count;                          //!< 検索結果の総商品数 
    int             page;                           //!< 現在のページ番号 
    int             first;                          //!< 検索結果の何件目からか 
    int             last;                           //!< 検索結果の何件目までか 
    int             hits;                           //!< 一度に返却する商品数 
    int             carrier;                        //!< キャリア (PC=0 or mobile=1)
    int             pageCount;                      //!< 総ページ数 (最大100)
    int             numOfCatalogs;                  //!< 取得したカタログ情報の数
    RAKUTEN_CATALOG *catalog;                       //!< 商品情報 + ジャンル情報
}   RAKUTEN_API_RESPONSE1;
/*@}*/

/** \defgroup rakutenSearchRequest2 検索要求格納用構造体 (GenreSearch用)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! 検索要求格納用構造体・その2 (2006-12-26版)
typedef struct rakutenSearchRequest2 {
    // 共通パラメータ
    char    developerId[MAX_NAMELEN + 1];   //!< デベロッパーID
    char    affiliateId[MAX_KEYLENGTH];     //!< アフィリエイトID
    char    operation[RAKUTEN_OPE_LEN];     //!< 操作
    // サービス固有パラメータ   -- GenreSearch
    long    genreId;                        //!< ジャンルID
    char    version[RAKUTEN_VERSION_LEN];   //!< バージョン
    BOOL    genrePath;                      //!< ジャンルパス
}   RAKUTEN_API_REQUEST2;
/*@}*/

/** \defgroup rakutenSearchResponse2 検索結果格納用構造体 (GenreSearch用)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! 検索結果格納用構造体・その2 (2006-12-26版)
typedef struct rakutenSearchResponse2 {
    char            status[MAX_NAMELEN];            //!< 実行結果ステータス
    char            statusMsg[RAKUTEN_STATMSG_LEN]; //!< 実行結果ステータス詳細
    // 親ジャンル
    int             numOfDepth;                     //!< ルートから親までの深さ
    RAKUTEN_GENRE   *parent;                        //!< 親ジャンル / 祖先ジャンル
    // 自ジャンル
    RAKUTEN_GENRE   current;                        //!< 検索要求で指定した genreId に対応するジャンル
    // 子ジャンル
    int             numOfChilds;                    //!< 子ジャンル数
    RAKUTEN_GENRE   *child;                         //!< 子ジャンル(複数存在する場合あり)
}   RAKUTEN_API_RESPONSE2;
/*@}*/


/** \defgroup rakutenSearchRequest3 検索要求格納用構造体 (ItemCodeSearch用)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! 検索要求格納用構造体・その3 (2007-02-14版)
typedef struct rakutenSearchRequest3 {
    // 共通パラメータ
    char    developerId[MAX_NAMELEN + 1];   //!< デベロッパーID
    char    affiliateId[MAX_KEYLENGTH];     //!< アフィリエイトID
    char    operation[RAKUTEN_OPE_LEN];     //!< 操作
    // サービス固有パラメータ   -- ItemCodeSearch
    char    itemCode[MAX_KEYLENGTH];        //!< 商品コード (例 book:11918897)
    char    version[RAKUTEN_VERSION_LEN];   //!< バージョン
    int     carrier;                        //!< キャリア
}   RAKUTEN_API_REQUEST3;
/*@}*/

/** \defgroup rakutenSearchResponse3 検索結果格納用構造体 (ItemCodeSearch用)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! 検索結果格納用構造体・その3 (2007-02-14版)
typedef struct rakutenSearchResponse3 {
    char            status[MAX_NAMELEN];            //!< 実行結果ステータス
    char            statusMsg[RAKUTEN_STATMSG_LEN]; //!< 実行結果ステータス詳細
    int             carrier;                        //!< キャリア (PC=0 or mobile=1)
    RAKUTEN_ITEM    *item;                          //!< 商品情報 + 店舗情報 + ジャンル情報
}   RAKUTEN_API_RESPONSE3;
/*@}*/


// 楽天商品検索API       -- ItemSearch (version:2007-02-14)
RAKUTEN_API_RESPONSE    *
itemSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        const char *keyword,
        const char *shopCode,
        long       genreId,
        const char *catalogCode,
        int        hits,
        int        page,
        int        sort,
        long       minPrice,
        long       maxPrice,
        int        field,
        int        carrier,
        int        imageFlag
    );

RAKUTEN_API_RESPONSE    *
itemSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


// 楽天ジャンル検索API   -- GenreSearch (version:2006-12-26)
RAKUTEN_API_RESPONSE2   *
genreSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        long       genreId,
        BOOL       genrePath
    );

RAKUTEN_API_RESPONSE2   *
genreSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST2 *p );


// 楽天商品コード検索API -- ItemCodeSearch (version:2007-02-14)
RAKUTEN_API_RESPONSE3   *
itemCodeSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        const char *itemCode,
        int        carrier
    );

RAKUTEN_API_RESPONSE3   *
itemCodeSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST3 *p );


// 楽天書籍検索API       -- BookSearch (version:2007-02-14)
RAKUTEN_API_RESPONSE    *
bookSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        const char *keyword,
        long       genreId,
        int        hits,
        int        page,
        int        sort,
        long       minPrice,
        long       maxPrice,
        int        field,
        int        carrier,
        int        imageFlag
    );

RAKUTEN_API_RESPONSE    *
bookSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


// 楽天CD検索API         -- CDSearch (version:2007-02-14)
RAKUTEN_API_RESPONSE    *
cdSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        const char *keyword,
        long       genreId,
        int        hits,
        int        page,
        int        sort,
        long       minPrice,
        long       maxPrice,
        int        field,
        int        carrier,
        int        imageFlag
    );

RAKUTEN_API_RESPONSE    *
cdSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


// 楽天DVD検索API        -- DVDSearch (version:2007-02-14)
RAKUTEN_API_RESPONSE    *
dvdSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        const char *keyword,
        long       genreId,
        int        hits,
        int        page,
        int        sort,
        long       minPrice,
        long       maxPrice,
        int        field,
        int        carrier,
        int        imageFlag
    );

RAKUTEN_API_RESPONSE    *
dvdSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


// 楽天カタログ検索API   -- CatalogSearch (version:2007-02-14)
RAKUTEN_API_RESPONSE1   *
catalogSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        const char *keyword,
        long       genreId,
        int        hits,
        int        page,
        int        sort,
        long       minPrice,
        long       maxPrice,
        int        field,
        int        imageFlag,
        int        releaseRange
    );

RAKUTEN_API_RESPONSE1   *
catalogSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


void
freeRakutenApiResponce( RAKUTEN_API_RESPONSE *p );

void
freeRakutenApiResponce1( RAKUTEN_API_RESPONSE1 *p );

void
freeRakutenApiResponce2( RAKUTEN_API_RESPONSE2 *p );

void
freeRakutenApiResponce3( RAKUTEN_API_RESPONSE3 *p );

#endif  /* __RAKUTEN_H__ */
