/*
 *  amazon.c
 *
 * History:
 * $Log: /comm/xmlRPC/amazon.c $
 * 
 * 3     09/06/02 2:49 tsupo
 * 1.268版
 * 
 * 43    09/06/01 19:06 Tsujimura543
 * Product Advertising API (+ HMAC-SHA256方式署名付き) 対応
 * [動作確認済み]
 * 
 * 42    09/06/01 16:21 Tsujimura543
 * amazonAccessKeyID と amazonAccessKeySecret を追加
 * 
 * 2     09/05/29 7:09 tsupo
 * 1.267版
 * 
 * 41    09/05/28 18:37 Tsujimura543
 * バッファオーバーラン対策を強化
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 40    08/09/09 21:23 Tsujimura543
 * 不要になった機能を削除 (その3)
 * 
 * 39    08/02/18 22:55 Tsujimura543
 * (VSS データ修復)
 * 
 * 38    08/02/18 22:54 Tsujimura543
 * searchItemsOnAmazon4() と getSalesRankingOnAmazon4() を修正し、
 * 11件以上のデータを取得可能にした
 * 
 * 37    08/02/18 20:55 Tsujimura543
 * searchItemsOnAmazon4() と getSalesRankingOnAmazon4() を
 * ForeignBooks に対応
 * 
 * 36    08/02/18 20:50 Tsujimura543
 * searchItemsOnAmazon4() と getSalesRankingOnAmazon4() を
 * Blended に対応
 * 
 * 35    08/02/18 20:23 Tsujimura543
 * getItemsFromResultSmall() と getItemsFromResultMedium() を修正
 *   (1) バグフィックス
 *   (2) Music 対応
 * 
 * 34    08/02/15 23:01 Tsujimura543
 * searchItemsOnAmazon4() の searchType のデフォルトを
 * AMAZON_STYPE_ITEMLOOKUP から AMAZON_STYPE_ITEMSEARCH
 * へ変更
 * 
 * 33    08/02/15 22:43 Tsujimura543
 * コメントを追加
 * 
 * 32    08/02/15 22:38 Tsujimura543
 * getSalesRankingOnAmazon4() を追加
 * 
 * 31    08/02/15 3:16 Tsujimura543
 * getItemsFromResultMedium() を強化 (Books 対応)
 * 
 * 30    08/02/15 2:20 Tsujimura543
 * (1) avalability → availability に修正 (typo)
 * (2) getItemsFromResultSmall() を強化 (画像あり版、Books にも対応)
 * 
 * 29    08/02/14 1:40 Tsujimura543
 * ECS4.0 暫定対応版
 * 
 * 28    08/02/13 23:24 Tsujimura543
 * searchItemsOnAmazon4() を追加 (まだ、未完成)
 * 
 * 27    07/03/03 15:03 Tsujimura543
 * sjis2utf() が NULL を返す場合の対策を実施
 * 
 * 26    06/07/24 20:10 Tsujimura543
 * _httpExecute() のバッファオーバーラン防止機能を利用するようにした
 * 
 * 25    05/11/18 18:40 Tsujimura543
 * sportinggoods-jp を sporting-goods-jp に修正
 * 
 * 24    05/11/17 20:30 Tsujimura543
 * AMAZON_MODE_SPORTS 関係の処理を追加 (暫定)
 * 
 * 23    05/04/18 16:58 Tsujimura543
 * isbn2urls() を isbn.c へ移管
 * 
 * 22    05/04/18 16:48 Tsujimura543
 * ValueCommerce 関連部分を valueCommerce.c として分離独立させた
 * 
 * 21    05/04/18 16:17 Tsujimura543
 * 「楽天アフィリエイト」関連部分を rakuten.c として分離独立させた
 * 
 * 20    05/04/18 16:02 Tsujimura543
 * getResultFromXML() など XML 関連ユーティリティ関数を xmlUtil.c
 * に移管
 * 
 * 19    05/04/18 15:58 Tsujimura543
 * bidders 関連部分を分離独立させ、bidders.c に移管
 * 
 * 18    04/11/29 18:30 Tsujimura543
 * AMAZON_MOD_* → AMAZON_MODE_* に変更
 * 
 * 17    04/11/17 18:48 Tsujimura543
 * searchItemsByNicknameOnBidders() と searchItemsByTrademarkOnBidders()
 * を実装、動作を確認
 * 
 * 16    04/11/17 18:19 Tsujimura543
 * searchItemsOnBidders() を実装。動作確認済み
 * 
 * 15    04/11/17 16:02 Tsujimura543
 * setAffiriateIDOnBidders() と setLinkIDOnBidders() を追加
 * 
 * 14    04/11/15 17:06 Tsujimura543
 * encodeURL() 内で確保した領域の解放処理を追加
 * 
 * 13    04/11/15 14:45 Tsujimura543
 * setSiteIdOnValueCommerce(), setSpaceId1OnValueCommerce(),
 * setSpaceId2OnValueCommerce() を追加
 * 
 * 12    04/11/15 11:43 Tsujimura543
 * getAffiriateLinkOnJbook() を修正、動作確認終了
 * 
 * 11    04/11/15 11:10 Tsujimura543
 * getAffiriateLinkOnJbook() を追加
 * 
 * 10    04/11/11 11:26 Tsujimura543
 * エンドポイントURLを変更
 * 
 * 9     04/11/04 16:44 Tsujimura543
 * ベストセラー一覧の取得結果も構造体に格納して返すようにした
 * 
 * 8     04/11/04 15:59 Tsujimura543
 * setSubscriptionIDOnAmazon() を追加
 * 
 * 7     04/11/02 21:46 Tsujimura543
 * アマゾンの検索オプションに「すべての商品」を追加
 * 
 * 6     04/11/02 20:46 Tsujimura543
 * (1) HEAVY版の検索結果返却対応
 * (2) アマゾンの新カテゴリ「おもちゃ&ホビー」の検索に対応
 * 
 * 5     04/11/01 21:01 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 4     04/11/01 19:56 Tsujimura543
 * 検索結果を構造体に設定して返すようにした (とりあえず、LITE版のみ)
 * 
 * 3     04/10/08 15:30 Tsujimura543
 * JBOOK の Valuecommerce 経由 MyLink に対応
 * 
 * 2     04/07/07 11:45 Tsujimura543
 */

#include "xmlRPC.h"
#include "amazon.h"
#include <openssl/x509.h>

#include <assert.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/amazon.c 3     09/06/02 2:49 tsupo $";
#endif

/* for Product Advertising API */
char    *makeCreated( time_t t );


/* Amazon アソシエイトID の設定 */
void
setAssociateIdOnAmazon( const char *associateID )
{
    if ( xmlrpc_p && associateID && *associateID )
        strcpy( xmlrpc_p->amazonAssociateID, associateID );
}

#if 0
/* Amazon Developer's Token の設定 */
void
setDevelopersTokenOnAmazon( const char *developerToken )
{
    if ( xmlrpc_p && developerToken && *developerToken )
        strcpy( xmlrpc_p->amazonDevelopperKey, developerToken );
}
#endif

/* Amazon Subscription ID の設定 */
void
setSubscriptionIDOnAmazon( const char *subscriptionID )
{
    if ( xmlrpc_p && subscriptionID && *subscriptionID )
        strcpy( xmlrpc_p->amazonSubscriptionID, subscriptionID );
}


/* Product Advertising API     */
/*    Access Key ID の設定     */
void
setAccessKeyIDOnAmazon( const char *key )
{
    if ( xmlrpc_p && key && *key )
        strcpy( xmlrpc_p->amazonAccessKeyID, key );
}

/*    Secret Access Key の設定 */
void
setAccessKeySecretOnAmazon( const char *secret )
{
    if ( xmlrpc_p && secret && *secret )
        strcpy( xmlrpc_p->amazonAccessKeySecret, secret );
}


/* Amazon で検索 */
#define BUFFER_SIZE     4096
#define ITEMS_PER_PAGE  10

/*
 *  検索結果解析 Small版
 */
int
getItemsFromResultSmall(
        const char  *xmlSrc,        /* (I) 検索結果 (xml)       */
        int         *numOfItems,    /* (I/O) 検索結果アイテム数 */
        AMAZON_LITE *result,        /* (O) 検索結果格納領域     */
        BOOL        *next           /* (O) 検索結果次ページあり */
    )
{
    const char  *p, *q, *r;
    const char  *sectionEnd   = "</Item>";
    int         numberOfItems = 0;
    int         itemPage      = 0;
    int         totalPages    = 0;

    /* Small の場合
     *  <Item>
     *    <ASIN>B00126NO4A</ASIN>
     *    <DetailPageURL>http://www.amazon.co.jp/gp/redirect.html%3FASIN=B00126NO4A%26tag=tsuporoswebpa-22%26lcode=xm2%26cID=2025%26ccmID=165953%26location=/o/ASIN/B00126NO4A%253FSubscriptionId=1P4XSJK2N3A8DR4AYN02</DetailPageURL>
     *    <ItemAttributes>
     *      <Manufacturer>Air Gates</Manufacturer>
     *      <ProductGroup>Sports</ProductGroup>
     *      <Title>Air Gates（エアゲイツ）AG-11Ti チタン配合ゴルフボール 12P</Title>
     *    </ItemAttributes>
     *  </Item>
     */

    /* Small,Request,ItemAttributes,OfferFull,Images の場合
     *  <Item>
     *    <ASIN>B00126NO4A</ASIN>
     *    <DetailPageURL>http://www.amazon.co.jp/gp/redirect.html%3FASIN=B00126NO4A%26tag=tsuporoswebpa-22%26lcode=xm2%26cID=2025%26ccmID=165953%26location=/o/ASIN/B00126NO4A%253FSubscriptionId=1P4XSJK2N3A8DR4AYN02</DetailPageURL>
     *    <SmallImage>
     *      <URL>http://ecx.images-amazon.com/images/I/113U-ZG0W1L.jpg</URL>
     *      <Height Units="pixels">75</Height>
     *      <Width Units="pixels">75</Width>
     *    </SmallImage>
     *    <MediumImage>
     *      <URL>http://ecx.images-amazon.com/images/I/21i9BuxKI%2BL.jpg</URL>
     *      <Height Units="pixels">160</Height>
     *      <Width Units="pixels">160</Width>
     *    </MediumImage>
     *    <LargeImage>
     *      <URL>http://ecx.images-amazon.com/images/I/41Q2bD0tM7L.jpg</URL>
     *      <Height Units="pixels">450</Height>
     *      <Width Units="pixels">450</Width>
     *    </LargeImage>
     *    <ImageSets>
     *      <ImageSet Category="primary">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01BoE2vPF8L.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">30</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/113U-ZG0W1L.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">75</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/21i9BuxKI%2BL.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">160</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/41Q2bD0tM7L.jpg</URL>
     *          <Height Units="pixels">450</Height>
     *          <Width Units="pixels">450</Width>
     *        </LargeImage>
     *      </ImageSet>
     *      <ImageSet Category="variant">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/013VM6PLYsL.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">30</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/117LaTGjC1L.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">75</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/21e9g2PG4TL.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">160</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/415ujfHD2JL.jpg</URL>
     *          <Height Units="pixels">450</Height>
     *          <Width Units="pixels">450</Width>
     *        </LargeImage>
     *      </ImageSet>
     *      <ImageSet Category="variant">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01ua8-G8qDL.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">30</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/11PN5gKGUoL.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">75</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/214%2BL%2BHK8PL.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">160</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/51pX4U5s5lL.jpg</URL>
     *          <Height Units="pixels">450</Height>
     *          <Width Units="pixels">450</Width>
     *        </LargeImage>
     *      </ImageSet>
     *      <ImageSet Category="variant">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01HR-IkeqJL.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">30</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01WeZCCGddL.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">75</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/21Fb12axNGL.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">160</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/412CbC1v4EL.jpg</URL>
     *          <Height Units="pixels">500</Height>
     *          <Width Units="pixels">500</Width>
     *        </LargeImage>
     *      </ImageSet>
     *    </ImageSets>
     *    <ItemAttributes>
     *      <Binding>Misc.</Binding>
     *      <Brand>Air Gates</Brand>
     *      <Feature>AIR FLIGHTディンプルの空力性能とチタンコアの融合！</Feature>
     *      <Label>Air Gates</Label>
     *      <Manufacturer>Air Gates</Manufacturer>
     *      <MPN>2004230390001</MPN>
     *      <ProductGroup>Sports</ProductGroup>
     *      <Publisher>Air Gates</Publisher>
     *      <Studio>Air Gates</Studio>
     *      <Title>Air Gates（エアゲイツ）AG-11Ti チタン配合ゴルフボール 12P</Title>
     *    </ItemAttributes>
     *    <OfferSummary>
     *      <LowestNewPrice>
     *        <Amount>780</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>￥ 780</FormattedPrice>
     *      </LowestNewPrice>
     *      <TotalNew>1</TotalNew>
     *      <TotalUsed>0</TotalUsed>
     *      <TotalCollectible>0</TotalCollectible>
     *      <TotalRefurbished>0</TotalRefurbished>
     *    </OfferSummary>
     *    <Offers>
     *      <TotalOffers>0</TotalOffers>
     *      <TotalOfferPages>0</TotalOfferPages>
     *    </Offers>
     *  </Item>
     */

    /* Small,Request,ItemAttributes,OfferFull,Images で Books の場合
     *  <Item>
     *    <ASIN>4798112968</ASIN>
     *    <DetailPageURL>http://www.amazon.co.jp/gp/redirect.html%3FASIN=4798112968%26tag=tsuporoswebpa-22%26lcode=xm2%26cID=2025%26ccmID=165953%26location=/o/ASIN/4798112968%253FSubscriptionId=1P4XSJK2N3A8DR4AYN02</DetailPageURL>
     *    <SmallImage>
     *      <URL>http://ecx.images-amazon.com/images/I/11RpoWUII9L.jpg</URL>
     *      <Height Units="pixels">75</Height>
     *      <Width Units="pixels">59</Width>
     *    </SmallImage>
     *    <MediumImage>
     *      <URL>http://ecx.images-amazon.com/images/I/21YWLjqtD5L.jpg</URL>
     *      <Height Units="pixels">160</Height>
     *      <Width Units="pixels">125</Width>
     *    </MediumImage>
     *    <LargeImage>
     *      <URL>http://ecx.images-amazon.com/images/I/41EIwLc32RL.jpg</URL>
     *      <Height Units="pixels">383</Height>
     *      <Width Units="pixels">300</Width>
     *    </LargeImage>
     *    <ImageSets>
     *      <ImageSet Category="primary">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01z45E2C-ZL.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">24</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/11RpoWUII9L.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">59</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/21YWLjqtD5L.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">125</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/41EIwLc32RL.jpg</URL>
     *          <Height Units="pixels">383</Height>
     *          <Width Units="pixels">300</Width>
     *        </LargeImage>
     *      </ImageSet>
     *    </ImageSets>
     *    <ItemAttributes>
     *      <Author>漆尾 貴義</Author>
     *      <Binding>大型本</Binding>
     *      <Creator Role="著">漆尾 貴義</Creator>
     *      <EAN>9784798112961</EAN>
     *      <ISBN>4798112968</ISBN>
     *      <Label>翔泳社</Label>
     *      <ListPrice>
     *        <Amount>2940</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>￥ 2,940</FormattedPrice>
     *      </ListPrice>
     *      <Manufacturer>翔泳社</Manufacturer>
     *      <NumberOfPages>360</NumberOfPages>
     *      <PackageDimensions>
     *        <Height Units="hundredths-inches">94</Height>
     *        <Length Units="hundredths-inches">906</Length>
     *        <Weight Units="hundredths-pounds">150</Weight>
     *        <Width Units="hundredths-inches">724</Width>
     *      </PackageDimensions>
     *      <ProductGroup>Book</ProductGroup>
     *      <PublicationDate>2007-04-20</PublicationDate>
     *      <Publisher>翔泳社</Publisher>
     *      <Studio>翔泳社</Studio>
     *      <Title>10日でおぼえるAjax 入門教室</Title>
     *    </ItemAttributes>
     *    <OfferSummary>
     *      <LowestNewPrice>
     *        <Amount>2940</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>￥ 2,940</FormattedPrice>
     *      </LowestNewPrice>
     *      <LowestUsedPrice>
     *        <Amount>2200</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>￥ 2,200</FormattedPrice>
     *      </LowestUsedPrice>
     *      <TotalNew>1</TotalNew>
     *      <TotalUsed>6</TotalUsed>
     *      <TotalCollectible>0</TotalCollectible>
     *      <TotalRefurbished>0</TotalRefurbished>
     *    </OfferSummary>
     *    <Offers>
     *      <TotalOffers>1</TotalOffers>
     *      <TotalOfferPages>1</TotalOfferPages>
     *      <Offer>
     *        <Merchant>
     *          <MerchantId>AN1VRQENFRJN5</MerchantId>
     *          <Name>Amazon.co.jp</Name>
     *          <GlancePage>http://www.amazon.co.jp/gp/help/seller/home.html?seller=AN1VRQENFRJN5</GlancePage>
     *        </Merchant>
     *        <OfferAttributes>
     *          <Condition>New</Condition>
     *          <SubCondition>new</SubCondition>
     *        </OfferAttributes>
     *        <OfferListing>
     *          <OfferListingId>QAAORmHM9cIxRgaCEOiFGyCJXx4Io244O8FzHZpV891IgnoPfeCxkmfOnC270e0RaRSAGD94SGpeoL5aYpfwvw%3D%3D</OfferListingId>
     *          <Price>
     *            <Amount>2940</Amount>
     *            <CurrencyCode>JPY</CurrencyCode>
     *            <FormattedPrice>￥ 2,940</FormattedPrice>
     *          </Price>
     *          <Availability>通常4〜5日以内に発送</Availability>
     *          <IsEligibleForSuperSaverShipping>1</IsEligibleForSuperSaverShipping>
     *        </OfferListing>
     *      </Offer>
     *    </Offers>
     *  </Item>
     */

    *next = FALSE;
    p = xmlSrc;
    if ( p && *p ) {
        q = strstr( p, "<ItemPage>" );
        if ( q ) {
            p = q + 10;
            itemPage = atol( p );
        }

        q = strstr( p, "<TotalPages>" );
        if ( q ) {
            p = q + 12;
            totalPages = atol( p );
        }

        if ( totalPages > itemPage )
            *next = TRUE;   /* 次ページあり */
    }

    while ( p && *p ) {
        p = strstr( p, "<Item><ASIN>" );
        if ( !p )
            break;
        r = strstr( p, sectionEnd );
        if ( !r )
            break;

        memset( result, 0x00, sizeof ( AMAZON_LITE ) );
        p += 6;
        p = getResultFromXML_s( p, "ASIN",          sectionEnd,
                               result->asin, MAX_NAMELEN - 1 );
        p = getResultFromXML_s( p, "DetailPageURL", sectionEnd,
                                result->url, MAX_URLLENGTH_MAX - 1 );

        result->imageURLsmall[0]  = NUL;
        result->imageURLmedium[0] = NUL;
        result->imageURLlarge[0]  = NUL;

        // SmallImage
        q = strstr( p, "<SmallImage>" );
        if ( q && (q < r) )
            p = getResultFromXML_s(q, "URL", sectionEnd,
                                   result->imageURLsmall, MAX_URLLENGTH - 1);

        // MediumImage
        q = strstr( p, "<MediumImage>" );
        if ( q && (q < r) )
            p = getResultFromXML_s(q, "URL", sectionEnd,
                                   result->imageURLmedium, MAX_URLLENGTH - 1);

        // LargeImage
        q = strstr( p, "<LargeImage>" );
        if ( q && (q < r) )
            p = getResultFromXML_s(q, "URL", sectionEnd,
                                   result->imageURLlarge, MAX_URLLENGTH - 1);

        // ItemAttributes
        result->authors[0]      = NUL;
        result->listPrice[0]    = NUL;
        result->manufacturer[0] = NUL;
        result->releaseDate[0]  = NUL;
        result->productName[0]  = NUL;

        q = strstr( p, "<Author>" );
        if ( q && (q < r) )
            p = getResultFromXML_s( p, "Author", sectionEnd,
                                    result->authors,
                                    MAX_AUTHORINFO_LENGTH - 1 );
        else {
            q = strstr( p, "<Artist>" );
            if ( q && (q < r) )
                p = getResultFromXML_s( p, "Artist", sectionEnd,
                                        result->authors,
                                        MAX_AUTHORINFO_LENGTH - 1 );
            else {
                q = strstr( p, "<Label>" );
                if ( q && (q < r) )
                    p = getResultFromXML_s( p, "Label", sectionEnd,
                                            result->authors,
                                            MAX_AUTHORINFO_LENGTH - 1 );
            }
        }

        q = strstr( p, "<ListPrice><Amount>" );
        if ( q && (q < r) )
            p = getResultFromXML_s( q, "Amount", sectionEnd,
                                    result->listPrice, MAX_PRICE_LENGTH - 1 );

        q = strstr( p, "<Manufacturer>" );
        if ( q && (q < r) )
            p = getResultFromXML_s( p, "Manufacturer", sectionEnd,
                                    result->manufacturer,
                                    MAX_MANUFACTURER_LENGTH - 1 );

        q = strstr( p, "<PublicationDate>" );
        if ( q && (q < r) )
            p = getResultFromXML_s( p, "PublicationDate", sectionEnd,
                                    result->releaseDate, MAX_DATELENGTH - 1 );
        else {
            q = strstr( p, "<ReleaseDate>" );
            if ( q && (q < r) )
                p = getResultFromXML_s( p, "ReleaseDate", sectionEnd,
                                        result->releaseDate,
                                        MAX_DATELENGTH - 1 );
        }

        q = strstr( p, "<Title>" );
        if ( q && (q < r) )
            p = getResultFromXML_s( p, "Title", sectionEnd,
                                    result->productName,
                                    MAX_PRODUCTSNAME_LENGTH - 1 );

        // OfferSummary
        result->availability[0] = NUL;
        result->amazonPrice[0]  = NUL;
        result->usedPrice[0]    = NUL;

        q = strstr( p, "<LowestNewPrice>" );
        if ( q && (q < r) )
            p = getResultFromXML_s(q, "Amount", sectionEnd,
                                   result->amazonPrice, MAX_PRICE_LENGTH - 1);

        q = strstr( p, "<LowestUsedPrice>" );
        if ( q && (q < r) )
            p = getResultFromXML_s( q, "Amount", sectionEnd,
                                    result->usedPrice, MAX_PRICE_LENGTH - 1 );

        if ( result->listPrice[0] == NUL ) {
            q = strstr( p, "<Amount>" );
            if ( q && (q < r) )
                p = getResultFromXML_s( p, "Amount", sectionEnd,
                                        result->listPrice,
                                        MAX_PRICE_LENGTH - 1 );
        }

        if ( result->amazonPrice[0] == NUL ) {
            q = strstr( p, "<FormattedPrice>" );
            if ( q && (q < r) )
                p = getResultFromXML_s( p, "FormattedPrice", sectionEnd,
                                        result->amazonPrice,
                                        MAX_PRICE_LENGTH - 1 );
        }

        // Offers
        q = strstr( p, "<Availability>" );
        if ( q && (q < r) )
            p = getResultFromXML_s( p, "Availability", sectionEnd,
                                    result->availability,
                                    MAX_LOGICALLINELEN - 1 );

        numberOfItems++;
        if ( numberOfItems >= *numOfItems )
            break;
        result++;
    }
    *numOfItems = numberOfItems;

    return ( numberOfItems );
}

/*
 *  検索結果解析 Medium版
 */
int
getItemsFromResultMedium(
        const char   *xmlSrc,       /* (I) 検索結果 (xml)       */
        int          *numOfItems,   /* (I/O) 検索結果アイテム数 */
        AMAZON_HEAVY *result,       /* (O) 検索結果格納領域     */
        BOOL         *next          /* (O) 検索結果次ページあり */
    )
{
    int             numberOfItems = 0;
    unsigned long   numOfNodes    = 0;
    unsigned long   numOfReview   = 0;
    int             itemPage      = 0;
    int             totalPages    = 0;
    const char      *p, *q, *r;
    const char      *sectionEnd   = "</Item>";

    /* Medium の場合
     *  <Item>
     *    <ASIN>B00126NO4A</ASIN>
     *    <DetailPageURL>http://www.amazon.co.jp/gp/redirect.html%3FASIN=B00126NO4A%26tag=tsuporoswebpa-22%26lcode=xm2%26cID=2025%26ccmID=165953%26location=/o/ASIN/B00126NO4A%253FSubscriptionId=1P4XSJK2N3A8DR4AYN02</DetailPageURL>
     *    <SalesRank>6690</SalesRank>
     *    <SmallImage>
     *      <URL>http://ecx.images-amazon.com/images/I/113U-ZG0W1L.jpg</URL>
     *      <Height Units="pixels">75</Height>
     *      <Width Units="pixels">75</Width>
     *    </SmallImage>
     *    <MediumImage>
     *      <URL>http://ecx.images-amazon.com/images/I/21i9BuxKI%2BL.jpg</URL>
     *      <Height Units="pixels">160</Height>
     *      <Width Units="pixels">160</Width>
     *    </MediumImage>
     *    <LargeImage>
     *      <URL>http://ecx.images-amazon.com/images/I/41Q2bD0tM7L.jpg</URL>
     *      <Height Units="pixels">450</Height>
     *      <Width Units="pixels">450</Width>
     *    </LargeImage>
     *    <ImageSets>
     *      <ImageSet Category="primary">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01BoE2vPF8L.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">30</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/113U-ZG0W1L.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">75</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/21i9BuxKI%2BL.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">160</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/41Q2bD0tM7L.jpg</URL>
     *          <Height Units="pixels">450</Height>
     *          <Width Units="pixels">450</Width>
     *        </LargeImage>
     *      </ImageSet>
     *      <ImageSet Category="variant">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/013VM6PLYsL.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">30</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/117LaTGjC1L.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">75</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/21e9g2PG4TL.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">160</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/415ujfHD2JL.jpg</URL>
     *          <Height Units="pixels">450</Height>
     *          <Width Units="pixels">450</Width>
     *        </LargeImage>
     *      </ImageSet>
     *      <ImageSet Category="variant">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01ua8-G8qDL.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">30</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/11PN5gKGUoL.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">75</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/214%2BL%2BHK8PL.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">160</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/51pX4U5s5lL.jpg</URL>
     *          <Height Units="pixels">450</Height>
     *          <Width Units="pixels">450</Width>
     *        </LargeImage>
     *      </ImageSet>
     *      <ImageSet Category="variant">
     *        <SwatchImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01HR-IkeqJL.jpg</URL>
     *          <Height Units="pixels">30</Height>
     *          <Width Units="pixels">30</Width>
     *        </SwatchImage>
     *        <SmallImage>
     *          <URL>http://ecx.images-amazon.com/images/I/01WeZCCGddL.jpg</URL>
     *          <Height Units="pixels">75</Height>
     *          <Width Units="pixels">75</Width>
     *        </SmallImage>
     *        <MediumImage>
     *          <URL>http://ecx.images-amazon.com/images/I/21Fb12axNGL.jpg</URL>
     *          <Height Units="pixels">160</Height>
     *          <Width Units="pixels">160</Width>
     *        </MediumImage>
     *        <LargeImage>
     *          <URL>http://ecx.images-amazon.com/images/I/412CbC1v4EL.jpg</URL>
     *          <Height Units="pixels">500</Height>
     *          <Width Units="pixels">500</Width>
     *        </LargeImage>
     *      </ImageSet>
     *    </ImageSets>
     *    <ItemAttributes>
     *      <Binding>Misc.</Binding>
     *      <Brand>Air Gates</Brand>
     *      <Feature>AIR FLIGHTディンプルの空力性能とチタンコアの融合！</Feature>
     *      <Label>Air Gates</Label>
     *      <Manufacturer>Air Gates</Manufacturer>
     *      <MPN>2004230390001</MPN>
     *      <ProductGroup>Sports</ProductGroup>
     *      <Publisher>Air Gates</Publisher>
     *      <Studio>Air Gates</Studio>
     *      <Title>Air Gates（エアゲイツ）AG-11Ti チタン配合ゴルフボール 12P</Title>
     *    </ItemAttributes>
     *    <OfferSummary>
     *      <LowestNewPrice>
     *        <Amount>780</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>￥ 780</FormattedPrice>
     *      </LowestNewPrice>
     *      <TotalNew>1</TotalNew>
     *      <TotalUsed>0</TotalUsed>
     *      <TotalCollectible>0</TotalCollectible>
     *      <TotalRefurbished>0</TotalRefurbished>
     *    </OfferSummary>
     *    <EditorialReviews>
     *      <EditorialReview>
     *        <Source>Product Description</Source>
     *        <Content>
     *          〜〜◆◆Air Gates（エアゲイツ）開発コンセプト◆◆〜〜
     *          AirGatesは、アスリートゴルファーを目指すアベレージゴルファーに満足頂ける高性能と、スポーティで斬新なデザインを融合したハイコストパフォーマンスブランドです。
     *          【 ボールの性能 ・・・】 
     *          ■DUPONT社製極薄サーリンカバー＆ハイエナジーソフトチタンコアでソフトフィーリング、ビッグキャリーを実現しました。
     *          ■432 AIR FLIGHTディンプルで優れた空力性能を発揮。アゲンスト時でも高弾道かつ優れた飛距離性能を実現します。
     *          ■ハイエナジーソフトチタンコアは優れた反発性能でビッグキャリーをもたらします。
     *          【 ボールデザイン ・・・】
     *          ■ナンバー部分は、他のボールとの区別がつきやすく、特徴のあるデザインになっています。■
     *        </Content>
     *      </EditorialReview>
     *    </EditorialReviews>
     *  </Item>
     */

    *next = FALSE;
    p = xmlSrc;
    if ( p && *p ) {
        q = strstr( p, "<ItemPage>" );
        if ( q ) {
            p = q + 10;
            itemPage = atol( p );
        }

        q = strstr( p, "<TotalPages>" );
        if ( q ) {
            p = q + 12;
            totalPages = atol( p );
        }

        if ( totalPages > itemPage )
            *next = TRUE;   /* 次ページあり */
    }

    while ( p && *p ) {
        p = strstr( p, "<Item><ASIN>" );
        if ( !p )
            break;
        r = strstr( p, sectionEnd );
        if ( !r )
            break;

        memset( result, 0x00, sizeof ( AMAZON_HEAVY ) );
        numOfNodes  = 0;
        numOfReview = 0;
        p += 6;
        p = getResultFromXML( p, "ASIN",          sectionEnd,
                              result->asin );
        p = getResultFromXML( p, "DetailPageURL", sectionEnd,
                              result->url );
        p = getIntegerFromXML(p, "SalesRank",     sectionEnd,
                              &(result->salesRank) );

        result->imageURLsmall[0]  = NUL;
        result->imageURLmedium[0] = NUL;
        result->imageURLlarge[0]  = NUL;

        // SmallImage
        q = strstr( p, "<SmallImage>" );
        if ( q && (q < r) )
            p = getResultFromXML( q, "URL", sectionEnd,
                                  result->imageURLsmall );

        // MediumImage
        q = strstr( p, "<MediumImage>" );
        if ( q && (q < r) )
            p = getResultFromXML( q, "URL", sectionEnd,
                                  result->imageURLmedium );

        // LargeImage
        q = strstr( p, "<LargeImage>" );
        if ( q && (q < r) )
            p = getResultFromXML( q, "URL", sectionEnd,
                                  result->imageURLlarge );

        // ItemAttributes
        result->authors[0]     = NUL;
        result->media[0]       = NUL;
        result->releaseDate[0] = NUL;
        result->listPrice[0]   = NUL;
        result->isbn[0]        = NUL;

        q = strstr( p, "<Author>" );
        if ( q && (q < r) )
            p = getResultFromXML( p, "Author", sectionEnd,
                                  result->authors );
        else {
            q = strstr( p, "<Artist>" );
            if ( q && (q < r) )
                p = getResultFromXML( p, "Artist", sectionEnd,
                                      result->authors );
        }

        p = getResultFromXML( p, "Binding", sectionEnd,
                              result->media );

        if ( result->authors[0] == NUL )
            p = getResultFromXML( p, "Label", sectionEnd,
                                  result->authors );

        q = strstr( p, "<EAN>" );
        if ( q && (q < r) )
            p = getResultFromXML( p, "EAN", sectionEnd,
                                  result->isbn );       // 13桁ISBN
        else {
            q = strstr( p, "<ISBN>" );
            if ( q && (q < r) )
                p = getResultFromXML( p, "ISBN", sectionEnd,
                                      result->isbn );   // 10桁ISBN
        }

        q = strstr( p, "<ListPrice><Amount>" );
        if ( q && (q < r) )
            p = getResultFromXML( q, "Amount", sectionEnd,
                                  result->listPrice );

        q = strstr( p, "<Manufacturer>" );
        if ( q && (q < r) )
            p = getResultFromXML( p, "Manufacturer", sectionEnd,
                                  result->manufacturer );

        q = strstr( p, "<PublicationDate>" );
        if ( q && (q < r) )
            p = getResultFromXML( p, "PublicationDate", sectionEnd,
                                  result->releaseDate );
        else {
            q = strstr( p, "<ReleaseDate>" );
            if ( q && (q < r) )
                p = getResultFromXML( p, "ReleaseDate", sectionEnd,
                                      result->releaseDate );
        }

        q = strstr( p, "<Title>" );
        if ( q && (q < r) )
            p = getResultFromXML( p, "Title", sectionEnd,
                                  result->productName );

        // OfferSummary
        result->availability[0] = NUL;
        result->amazonPrice[0]  = NUL;
        result->usedPrice[0]    = NUL;

        q = strstr( p, "<LowestNewPrice>" );
        if ( q && (q < r) )
            p = getResultFromXML( q, "Amount", sectionEnd,
                                  result->amazonPrice );

        q = strstr( p, "<LowestUsedPrice>" );
        if ( q && (q < r) )
            p = getResultFromXML( q, "Amount", sectionEnd,
                                  result->usedPrice );

        if ( result->listPrice[0] == NUL ) {
            q = strstr( p, "<Amount>" );
            if ( q && (q < r) )
                p = getResultFromXML( p, "Amount", sectionEnd,
                                      result->listPrice );
        }

        if ( result->amazonPrice[0] == NUL ) {
            q = strstr( p, "<FormattedPrice>" );
            if ( q && (q < r) )
                p = getResultFromXML( p, "FormattedPrice", sectionEnd,
                                      result->amazonPrice );
        }

        // Offers
        q = strstr( p, "<Availability>" );
        if ( q && (q < r) )
            p = getResultFromXML( p, "Availability", sectionEnd,
                                  result->availability );

        result->numOfBrowseNodes     = 0;
        result->reviews.numOfReviews = 0;
        result->similarProcducts[0]  = NUL;

        numberOfItems++;
        if ( numberOfItems >= *numOfItems )
            break;
        result++;
    }
    *numOfItems = numberOfItems;

    return ( numberOfItems );
}



/* Large の場合
 *  <Item>
 *    <ASIN>B00126NO4A</ASIN>
 *    <DetailPageURL>http://www.amazon.co.jp/gp/redirect.html%3FASIN=B00126NO4A%26tag=tsuporoswebpa-22%26lcode=xm2%26cID=2025%26ccmID=165953%26location=/o/ASIN/B00126NO4A%253FSubscriptionId=1P4XSJK2N3A8DR4AYN02</DetailPageURL>
 *    <SalesRank>6703</SalesRank>
 *    <SmallImage>
 *      <URL>http://ecx.images-amazon.com/images/I/113U-ZG0W1L.jpg</URL>
 *      <Height Units="pixels">75</Height>
 *      <Width Units="pixels">75</Width>
 *    </SmallImage>
 *    <MediumImage>
 *      <URL>http://ecx.images-amazon.com/images/I/21i9BuxKI%2BL.jpg</URL>
 *      <Height Units="pixels">160</Height>
 *      <Width Units="pixels">160</Width>
 *    </MediumImage>
 *    <LargeImage>
 *      <URL>http://ecx.images-amazon.com/images/I/41Q2bD0tM7L.jpg</URL>
 *      <Height Units="pixels">450</Height>
 *      <Width Units="pixels">450</Width>
 *    </LargeImage>
 *    <ImageSets>
 *      <ImageSet Category="primary">
 *        <SwatchImage>
 *          <URL>http://ecx.images-amazon.com/images/I/01BoE2vPF8L.jpg</URL>
 *          <Height Units="pixels">30</Height>
 *          <Width Units="pixels">30</Width>
 *        </SwatchImage>
 *        <SmallImage>
 *          <URL>http://ecx.images-amazon.com/images/I/113U-ZG0W1L.jpg</URL>
 *          <Height Units="pixels">75</Height>
 *          <Width Units="pixels">75</Width>
 *        </SmallImage>
 *        <MediumImage>
 *          <URL>http://ecx.images-amazon.com/images/I/21i9BuxKI%2BL.jpg</URL>
 *          <Height Units="pixels">160</Height>
 *          <Width Units="pixels">160</Width>
 *        </MediumImage>
 *        <LargeImage>
 *          <URL>http://ecx.images-amazon.com/images/I/41Q2bD0tM7L.jpg</URL>
 *          <Height Units="pixels">450</Height>
 *          <Width Units="pixels">450</Width>
 *        </LargeImage>
 *      </ImageSet>
 *      <ImageSet Category="variant">
 *        <SwatchImage>
 *          <URL>http://ecx.images-amazon.com/images/I/013VM6PLYsL.jpg</URL>
 *          <Height Units="pixels">30</Height>
 *          <Width Units="pixels">30</Width>
 *        </SwatchImage>
 *        <SmallImage>
 *          <URL>http://ecx.images-amazon.com/images/I/117LaTGjC1L.jpg</URL>
 *          <Height Units="pixels">75</Height>
 *          <Width Units="pixels">75</Width>
 *        </SmallImage>
 *        <MediumImage>
 *          <URL>http://ecx.images-amazon.com/images/I/21e9g2PG4TL.jpg</URL>
 *          <Height Units="pixels">160</Height>
 *          <Width Units="pixels">160</Width>
 *        </MediumImage>
 *        <LargeImage>
 *          <URL>http://ecx.images-amazon.com/images/I/415ujfHD2JL.jpg</URL>
 *          <Height Units="pixels">450</Height>
 *          <Width Units="pixels">450</Width>
 *        </LargeImage>
 *      </ImageSet>
 *      <ImageSet Category="variant">
 *        <SwatchImage>
 *          <URL>http://ecx.images-amazon.com/images/I/01ua8-G8qDL.jpg</URL>
 *          <Height Units="pixels">30</Height>
 *          <Width Units="pixels">30</Width>
 *        </SwatchImage>
 *        <SmallImage>
 *          <URL>http://ecx.images-amazon.com/images/I/11PN5gKGUoL.jpg</URL>
 *          <Height Units="pixels">75</Height>
 *          <Width Units="pixels">75</Width>
 *        </SmallImage>
 *        <MediumImage>
 *          <URL>http://ecx.images-amazon.com/images/I/214%2BL%2BHK8PL.jpg</URL>
 *          <Height Units="pixels">160</Height>
 *          <Width Units="pixels">160</Width>
 *        </MediumImage>
 *        <LargeImage>
 *          <URL>http://ecx.images-amazon.com/images/I/51pX4U5s5lL.jpg</URL>
 *          <Height Units="pixels">450</Height>
 *          <Width Units="pixels">450</Width>
 *        </LargeImage>
 *      </ImageSet>
 *      <ImageSet Category="variant">
 *        <SwatchImage>
 *          <URL>http://ecx.images-amazon.com/images/I/01HR-IkeqJL.jpg</URL>
 *          <Height Units="pixels">30</Height>
 *          <Width Units="pixels">30</Width>
 *        </SwatchImage>
 *        <SmallImage>
 *          <URL>http://ecx.images-amazon.com/images/I/01WeZCCGddL.jpg</URL>
 *          <Height Units="pixels">75</Height>
 *          <Width Units="pixels">75</Width>
 *        </SmallImage>
 *        <MediumImage>
 *          <URL>http://ecx.images-amazon.com/images/I/21Fb12axNGL.jpg</URL>
 *          <Height Units="pixels">160</Height>
 *          <Width Units="pixels">160</Width>
 *        </MediumImage>
 *        <LargeImage>
 *          <URL>http://ecx.images-amazon.com/images/I/412CbC1v4EL.jpg</URL>
 *          <Height Units="pixels">500</Height>
 *          <Width Units="pixels">500</Width>
 *        </LargeImage>
 *      </ImageSet>
 *    </ImageSets>
 *    <ItemAttributes>
 *      <Binding>Misc.</Binding>
 *      <Brand>Air Gates</Brand>
 *      <Feature>AIR FLIGHTディンプルの空力性能とチタンコアの融合！</Feature>
 *      <Label>Air Gates</Label>
 *      <Manufacturer>Air Gates</Manufacturer>
 *      <MPN>2004230390001</MPN>
 *      <ProductGroup>Sports</ProductGroup>
 *      <Publisher>Air Gates</Publisher>
 *      <Studio>Air Gates</Studio>
 *      <Title>Air Gates（エアゲイツ）AG-11Ti チタン配合ゴルフボール 12P</Title>
 *    </ItemAttributes>
 *    <OfferSummary>
 *      <LowestNewPrice>
 *        <Amount>780</Amount>
 *        <CurrencyCode>JPY</CurrencyCode>
 *        <FormattedPrice>￥ 780</FormattedPrice>
 *      </LowestNewPrice>
 *      <TotalNew>1</TotalNew>
 *      <TotalUsed>0</TotalUsed>
 *      <TotalCollectible>0</TotalCollectible>
 *      <TotalRefurbished>0</TotalRefurbished>
 *    </OfferSummary>
 *    <Offers>
 *      <TotalOffers>0</TotalOffers>
 *      <TotalOfferPages>0</TotalOfferPages>
 *    </Offers>
 *    <EditorialReviews>
 *      <EditorialReview>
 *        <Source>Product Description</Source>
 *        <Content>
 *          〜〜◆◆Air Gates（エアゲイツ）開発コンセプト◆◆〜〜
 *          AirGatesは、アスリートゴルファーを目指すアベレージゴルファーに満足頂ける高性能と、スポーティで斬新なデザインを融合したハイコストパフォーマンスブランドです。
 *          【 ボールの性能・・・】 
 *          ■DUPONT社製極薄サーリンカバー＆ハイエナジーソフトチタンコアでソフトフィーリング、ビッグキャリーを実現しました。 
 *          ■432 AIR FLIGHTディンプルで優れた空力性能を発揮。アゲンスト時でも高弾道かつ優れた飛距離性能を実現します。 
 *          ■ハイエナジーソフトチタンコアは優れた反発性能でビッグキャリーをもたらします。
 *          【 ボールデザイン ・・・】 
 *          ■ナンバー部分は、他のボールとの区別がつきやすく、特徴のあるデザインになっています。 
 *          ■
 *        </Content>
 *      </EditorialReview>
 *    </EditorialReviews>
 *    <BrowseNodes>
 *      <BrowseNode>
 *        <BrowseNodeId>15314411</BrowseNodeId>
 *        <Name>ゴルフボール</Name>
 *        <Children>
 *          <BrowseNode>
 *            <BrowseNodeId>15320151</BrowseNodeId>
 *            <Name>メンズ</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>15343311</BrowseNodeId>
 *            <Name>レディース</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>15343301</BrowseNodeId>
 *            <Name>ロストボール</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>15320161</BrowseNodeId>
 *            <Name>その他</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>16005651</BrowseNodeId>
 *            <Name>全商品</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>16005661</BrowseNodeId>
 *            <Name>ブランド別</Name>
 *          </BrowseNode>
 *        </Children>
 *        <Ancestors>
 *          <BrowseNode>
 *            <BrowseNodeId>14315441</BrowseNodeId>
 *            <Name>ゴルフ</Name>
 *            <Ancestors>
 *              <BrowseNode>
 *                <BrowseNodeId>14315361</BrowseNodeId>
 *                <Name>カテゴリー別</Name>
 *                <Ancestors>
 *                  <BrowseNode>
 *                    <BrowseNodeId>14304371</BrowseNodeId>
 *                    <Name>スポーツ&amp;アウトドア</Name>
 *                  </BrowseNode>
 *                </Ancestors>
 *              </BrowseNode>
 *            </Ancestors>
 *          </BrowseNode>
 *        </Ancestors>
 *      </BrowseNode>
 *      <BrowseNode>
 *        <BrowseNodeId>15741001</BrowseNodeId>
 *        <Name>ゴルフ</Name>
 *        <Ancestors>
 *          <BrowseNode>
 *            <BrowseNodeId>15740941</BrowseNodeId>
 *            <Name>ユーズドスポーツ</Name>
 *            <Ancestors>
 *              <BrowseNode>
 *                <BrowseNodeId>1058424</BrowseNodeId>
 *                <Name>jp-used</Name>
 *              </BrowseNode>
 *            </Ancestors>
 *          </BrowseNode>
 *        </Ancestors>
 *      </BrowseNode>
 *    </BrowseNodes>
 *  </Item>
 */

int
searchItemsOnAmazon4(
        int        type,        /* (I) Small, Medium, Large */
        int        mode,        /* (I) 検索対象分野         */
        int        searchType,  /* (I) 検索種別             */
        const char *keyword,    /* (I) 検索対象キーワード   */
        int        *numOfItems, /* (I/O) 検索結果アイテム数 */
        void       *result      /* (O) 検索結果格納領域     */
    )
{
    int     ret = 0;
    char    *typeString  = "";
    char    *modeString  = "";
    char    *stypeString = "";
    char    targetURL[BUFFER_SIZE];
    char    *rcvBuf;
    char    *p;
    int     numberOfItems    = 0;
    int     numberOfMaxItems = *numOfItems;
    int     page             = 0;
    BOOL    next             = FALSE;
    size_t  unit             = 0;
    size_t  offset           = 0;
    size_t  sz;

    switch ( type ) {
    case AMAZON_TYPE_SMALL:     /* or AMAZON_TYPE_LITE */
        typeString = "Small%2CRequest%2CItemAttributes%2COfferFull%2CImages%2C";
        break;
    case AMAZON_TYPE_MEDIUM:    /* or AMAZON_TYPE_HEAVY */
        typeString = "Medium%2CRequest%2CItemAttributes%2COfferFull%2CImages%2C";
        break;
    case AMAZON_TYPE_LARGE:
    default:
        typeString = "Large";
        break;
    }

    switch ( mode ) {
    case AMAZON_MODE_JBOOKS:
        modeString = "Books";
        break;
    case AMAZON_MODE_EBOOKS:
        modeString = "ForeignBooks";
        break;
    case AMAZON_MODE_MUSIC:
        modeString = "Music";
        break;
    case AMAZON_MODE_CLASSIC:
        modeString = "Classical";
        break;
    case AMAZON_MODE_DVD:
        modeString = "DVD";
        break;
    case AMAZON_MODE_VIDEO:
        modeString = "VHS";
        break;
    case AMAZON_MODE_ELECTRONICS:
        modeString = "Electronics";
        break;
    case AMAZON_MODE_SOFTWARE:
        modeString = "Software";
        break;
    case AMAZON_MODE_GAME:
        modeString = "VideoGames";
        break;
    case AMAZON_MODE_KITCHEN:
        modeString = "Kitchen";
        break;
    case AMAZON_MODE_TOYS:
        modeString = "Toys";
        break;
    case AMAZON_MODE_HOBBY:
        modeString = "Hobbies";
        break;
    case AMAZON_MODE_SPORTS:
        modeString = "SportingGoods";
        break;
    case AMAZON_MODE_BLENDED:
    default:
        modeString = "Blended";
        break;
    }

    switch ( searchType ) {
    case AMAZON_STYPE_ITEMLOOKUP:
        stypeString = "ItemLookup";
        break;
    case AMAZON_STYPE_ITEMSEARCH:
    default:
        stypeString = "ItemSearch";
        break;
    }

    sz = MAX_CONTENT_SIZE * 64;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( numberOfItems );

    *numOfItems = 0;
    do {
        p = sjis2utf( keyword );
        sz     = MAX_CONTENT_SIZE * 64;
        offset = unit * ITEMS_PER_PAGE;
        numberOfItems = (numberOfMaxItems - *numOfItems) >= ITEMS_PER_PAGE
                            ? ITEMS_PER_PAGE
                            : (numberOfMaxItems - *numOfItems);
        page++;
        next = FALSE;

        if ( xmlrpc_p->amazonAccessKeyID[0]     &&
             xmlrpc_p->amazonAccessKeySecret[0]    ) {
            /* Product Advertising API (2009年5月16日以降) */
            char    req[MAX_DESCRIPTION_LEN];
            char    message[MAX_DESCRIPTION_LEN * 4];
            char    digest[MAX_LOGICALLINELEN];
            char    timeStamp[MAX_DATELENGTH];
            char    *signature;

            strcpy( timeStamp, makeCreated( 0 ) );

            /* signature の生成 */
            sprintf( req,
                     "AWSAccessKeyId=%s&"
                     "AssociateTag=%s&"
                     "ContentType=text%%2Fxml&"
                     "ItemPage=%d&"
                     "Keywords=%s&"
                     "Operation=%s&"
                     "ResponseGroup=%s&"
                     "SearchIndex=%s&"
                     "Service=AWSECommerceService&",
                     xmlrpc_p->amazonAccessKeyID,
                     xmlrpc_p->amazonAssociateID,
                     page,
                     encodeURLi( p ? p : keyword, FALSE ),
                     stypeString,
                     typeString,
                     modeString );
            if ( strcmp( modeString, "Blended" ) != 0 )
                strcat( req,
                         "Sort=titlerank&" );
            sprintf( req + strlen(req),
                     "Timestamp=%s",
                     encodeURLi( timeStamp, FALSE ) );

            sprintf( message,
                     "%s\n"
                     "%s\n"
                     "%s\n"
                     "%s",
                     "GET",
                     "webservices.amazon.co.jp",
                     "/onca/xml",
                     req );

            memset( digest, 0x00, MAX_LOGICALLINELEN );
            hmac_sha256( (unsigned char *)message,
                         strlen(message),
                         (unsigned char *)xmlrpc_p->amazonAccessKeySecret,
                         strlen(xmlrpc_p->amazonAccessKeySecret),
                         digest );
            signature = base64((unsigned char *)digest, SHA256_DIGEST_LENGTH);

            /* GET する URL の生成 */
            sprintf( targetURL,
                     "http://webservices.amazon.co.jp/onca/xml?"
                     "%s&"
                     "Signature=%s",
                     req,
                     encodeURLi( signature, FALSE ) );
        }
        else {
            /* 従来の AWS */
            sprintf( targetURL,
                     "http://webservices.amazon.co.jp/onca/xml?"
                     "Service=AWSECommerceService&"
                     "AWSAccessKeyId=%s&"
                     "AssociateTag=%s&"
                     "ResponseGroup=%s&"
                     "ItemPage=%d&",
                     xmlrpc_p->amazonSubscriptionID,
                     xmlrpc_p->amazonAssociateID,
                     typeString,
                     page );
            assert( strlen( targetURL ) < BUFFER_SIZE );

            if ( strcmp( modeString, "Blended" ) != 0 )
                sprintf( targetURL + strlen(targetURL),
                         "Sort=titlerank&" );

            sprintf( targetURL + strlen(targetURL),
                     "Operation=%s&"
                     "ContentType=text%%2Fxml&"
                     "Keywords=%s&"
                     "SearchIndex=%s",
                     stypeString,
                     encodeURL( p ? p : keyword ),
                     modeString );
        }

        setUpReceiveBuffer( rcvBuf, sz );
        ret = httpGetBuffer( targetURL, rcvBuf, FALSE );
        assert( strlen( rcvBuf ) < MAX_CONTENT_SIZE * 64 );

        if ( (ret != -1) && (rcvBuf[0] != NUL) ) {
            if ( !strncmp( typeString, "Small", 5 ) )
                *numOfItems += getItemsFromResultSmall(
                                    rcvBuf, &numberOfItems,
                                    (AMAZON_LITE *)result + offset,
                                    &next );
            else
                *numOfItems += getItemsFromResultMedium(
                                    rcvBuf, &numberOfItems,
                                    (AMAZON_HEAVY *)result + offset,
                                    &next );
                                        /* Medium / Large 兼用 (暫定) */
            if ( numberOfMaxItems <= *numOfItems )
                break;
            unit++;
        }
    } while ( next );

    encodeURL( NULL );
    free( rcvBuf );

    return ( *numOfItems );
}

/* Amazon のベストセラーリスト取得 (ECS4.0版) */
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif

int
getSalesRankingOnAmazon4(
        int        type,        /* (I) Small, Medium, Large */
        int        mode,        /* (I) 検索対象分野(大枠)   */
        int        node,        /* (I) 検索対象分野(絞込み) */
        const char *genre,      /* (I) 検索対象分野名       */
        int        *numOfItems, /* (I/O) 検索結果アイテム数 */
        void       *result      /* (O) 検索結果格納領域     */
    )
{
    int     ret = 0;
    char    *typeString  = "";
    char    *modeString  = "";
    char    *stypeString = "";
    char    targetURL[BUFFER_SIZE];
    char    *rcvBuf;
    int     numberOfItems    = 0;
    int     numberOfMaxItems = *numOfItems;
    int     page             = 0;
    BOOL    next             = FALSE;
    size_t  unit             = 0;
    size_t  offset           = 0;
    size_t  sz;

    switch ( type ) {
    case AMAZON_TYPE_SMALL:     /* or AMAZON_TYPE_LITE */
        typeString =
          "Small%2CRequest%2CItemAttributes%2COfferFull%2CImages%2CSalesRank";
        break;
    case AMAZON_TYPE_MEDIUM:    /* or AMAZON_TYPE_HEAVY */
        typeString = "Medium";
        break;
    case AMAZON_TYPE_LARGE:
    default:
        typeString = "Large";
        break;
    }

    switch ( mode ) {
    case AMAZON_MODE_JBOOKS:
        modeString = "Books";
        break;
    case AMAZON_MODE_EBOOKS:
        modeString = "ForeignBooks";
        break;
    case AMAZON_MODE_MUSIC:
        modeString = "Music";
        break;
    case AMAZON_MODE_CLASSIC:
        modeString = "Classical";
        break;
    case AMAZON_MODE_DVD:
        modeString = "DVD";
        break;
    case AMAZON_MODE_VIDEO:
        modeString = "VHS";
        break;
    case AMAZON_MODE_ELECTRONICS:
        modeString = "Electronics";
        break;
    case AMAZON_MODE_SOFTWARE:
        modeString = "Software";
        break;
    case AMAZON_MODE_GAME:
        modeString = "VideoGames";
        break;
    case AMAZON_MODE_KITCHEN:
        modeString = "Kitchen";
        break;
    case AMAZON_MODE_TOYS:
        modeString = "Toys";
        break;
    case AMAZON_MODE_HOBBY:
        modeString = "Hobbies";
        break;
    case AMAZON_MODE_SPORTS:
        modeString = "SportingGoods";
        break;
    case AMAZON_MODE_BLENDED:
    default:
        modeString = "Blended";
        break;
    }

    stypeString = "ItemSearch";

    sz = MAX_CONTENT_SIZE * 4;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( numberOfItems );

    *numOfItems = 0;
    do {
        sz     = MAX_CONTENT_SIZE * 4;
        offset = unit * ITEMS_PER_PAGE;
        numberOfItems = (numberOfMaxItems - *numOfItems) >= ITEMS_PER_PAGE
                            ? ITEMS_PER_PAGE
                            : (numberOfMaxItems - *numOfItems);
        page++;
        next = FALSE;

        if ( xmlrpc_p->amazonAccessKeyID[0]     &&
             xmlrpc_p->amazonAccessKeySecret[0]    ) {
            /* Product Advertising API (2009年5月16日以降) */
            char    req[MAX_DESCRIPTION_LEN];
            char    message[MAX_DESCRIPTION_LEN * 4];
            char    digest[MAX_LOGICALLINELEN];
            char    timeStamp[MAX_DATELENGTH];
            char    *signature;

            strcpy( timeStamp, makeCreated( 0 ) );

            /* signature の生成 */
            sprintf( req,
                     "AWSAccessKeyId=%s&"
                     "AssociateTag=%s&"
                     "BrowseNode=%d&"
                     "ContentType=text%%2Fxml&"
                     "ItemPage=%d&"
                     "Operation=%s&"
                     "ResponseGroup=%s&"
                     "SearchIndex=%s&"
                     "Service=AWSECommerceService&",
                     xmlrpc_p->amazonAccessKeyID,
                     xmlrpc_p->amazonAssociateID,
                     node,
                     page,
                     stypeString,
                     typeString,
                     modeString );
            if ( strcmp( modeString, "Blended" ) != 0 )
                strcat( req,
                         "Sort=salesrank&" );
            sprintf( req + strlen(req),
                     "Timestamp=%s",
                     encodeURLi( timeStamp, FALSE ) );

            sprintf( message,
                     "%s\n"
                     "%s\n"
                     "%s\n"
                     "%s",
                     "GET",
                     "webservices.amazon.co.jp",
                     "/onca/xml",
                     req );

            memset( digest, 0x00, MAX_LOGICALLINELEN );
            hmac_sha256( (unsigned char *)message,
                         strlen(message),
                         (unsigned char *)xmlrpc_p->amazonAccessKeySecret,
                         strlen(xmlrpc_p->amazonAccessKeySecret),
                         digest );
            signature = base64((unsigned char *)digest, SHA256_DIGEST_LENGTH);

            /* GET する URL の生成 */
            sprintf( targetURL,
                     "http://webservices.amazon.co.jp/onca/xml?"
                     "%s&"
                     "Signature=%s",
                     req,
                     encodeURLi( signature, FALSE ) );
        }
        else {
            /* 従来の AWS */
            sprintf( targetURL,
                     "http://webservices.amazon.co.jp/onca/xml?"
                     "Service=AWSECommerceService&"
                     "AWSAccessKeyId=%s&"
                     "AssociateTag=%s&"
                     "ResponseGroup=%s&"
                     "ItemPage=%d&",
                     xmlrpc_p->amazonSubscriptionID,
                     xmlrpc_p->amazonAssociateID,
                     typeString,
                     page );

            if ( strcmp( modeString, "Blended" ) != 0 )
                sprintf( targetURL + strlen(targetURL),
                         "Sort=salesrank&" );

            sprintf( targetURL + strlen(targetURL),
                     "Operation=%s&"
                     "ContentType=text%%2Fxml&"
                     "BrowseNode=%d&"
                     "SearchIndex=%s",
                     stypeString,
                     node,
                     modeString );
        }

        setUpReceiveBuffer( rcvBuf, sz );
        ret = httpGetBuffer( targetURL, rcvBuf, FALSE );

        if ( (ret != -1) && (rcvBuf[0] != NUL) ) {
            if ( !strncmp( typeString, "Small", 5 ) )
                *numOfItems += getItemsFromResultSmall(
                                    rcvBuf, &numberOfItems,
                                    (AMAZON_LITE *)result + offset,
                                    &next );
            else
                *numOfItems += getItemsFromResultMedium(
                                    rcvBuf, &numberOfItems,
                                    (AMAZON_HEAVY *)result + offset,
                                    &next );
                                        /* Medium / Large 兼用 (暫定) */
            if ( numberOfMaxItems <= *numOfItems )
                break;
            unit++;
        }
    } while ( next );

    encodeURL( NULL );
    free( rcvBuf );

    return ( *numOfItems );
}

#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif
