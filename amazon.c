/*
 *  amazon.c
 *
 * History:
 * $Log: /comm/xmlRPC/amazon.c $
 * 
 * 2     09/05/29 7:09 tsupo
 * 1.267��
 * 
 * 41    09/05/28 18:37 Tsujimura543
 * �o�b�t�@�I�[�o�[�����΍������
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 40    08/09/09 21:23 Tsujimura543
 * �s�v�ɂȂ����@�\���폜 (����3)
 * 
 * 39    08/02/18 22:55 Tsujimura543
 * (VSS �f�[�^�C��)
 * 
 * 38    08/02/18 22:54 Tsujimura543
 * searchItemsOnAmazon4() �� getSalesRankingOnAmazon4() ���C�����A
 * 11���ȏ�̃f�[�^���擾�\�ɂ���
 * 
 * 37    08/02/18 20:55 Tsujimura543
 * searchItemsOnAmazon4() �� getSalesRankingOnAmazon4() ��
 * ForeignBooks �ɑΉ�
 * 
 * 36    08/02/18 20:50 Tsujimura543
 * searchItemsOnAmazon4() �� getSalesRankingOnAmazon4() ��
 * Blended �ɑΉ�
 * 
 * 35    08/02/18 20:23 Tsujimura543
 * getItemsFromResultSmall() �� getItemsFromResultMedium() ���C��
 *   (1) �o�O�t�B�b�N�X
 *   (2) Music �Ή�
 * 
 * 34    08/02/15 23:01 Tsujimura543
 * searchItemsOnAmazon4() �� searchType �̃f�t�H���g��
 * AMAZON_STYPE_ITEMLOOKUP ���� AMAZON_STYPE_ITEMSEARCH
 * �֕ύX
 * 
 * 33    08/02/15 22:43 Tsujimura543
 * �R�����g��ǉ�
 * 
 * 32    08/02/15 22:38 Tsujimura543
 * getSalesRankingOnAmazon4() ��ǉ�
 * 
 * 31    08/02/15 3:16 Tsujimura543
 * getItemsFromResultMedium() ������ (Books �Ή�)
 * 
 * 30    08/02/15 2:20 Tsujimura543
 * (1) avalability �� availability �ɏC�� (typo)
 * (2) getItemsFromResultSmall() ������ (�摜����ŁABooks �ɂ��Ή�)
 * 
 * 29    08/02/14 1:40 Tsujimura543
 * ECS4.0 �b��Ή���
 * 
 * 28    08/02/13 23:24 Tsujimura543
 * searchItemsOnAmazon4() ��ǉ� (�܂��A������)
 * 
 * 27    07/03/03 15:03 Tsujimura543
 * sjis2utf() �� NULL ��Ԃ��ꍇ�̑΍�����{
 * 
 * 26    06/07/24 20:10 Tsujimura543
 * _httpExecute() �̃o�b�t�@�I�[�o�[�����h�~�@�\�𗘗p����悤�ɂ���
 * 
 * 25    05/11/18 18:40 Tsujimura543
 * sportinggoods-jp �� sporting-goods-jp �ɏC��
 * 
 * 24    05/11/17 20:30 Tsujimura543
 * AMAZON_MODE_SPORTS �֌W�̏�����ǉ� (�b��)
 * 
 * 23    05/04/18 16:58 Tsujimura543
 * isbn2urls() �� isbn.c �ֈڊ�
 * 
 * 22    05/04/18 16:48 Tsujimura543
 * ValueCommerce �֘A������ valueCommerce.c �Ƃ��ĕ����Ɨ�������
 * 
 * 21    05/04/18 16:17 Tsujimura543
 * �u�y�V�A�t�B���G�C�g�v�֘A������ rakuten.c �Ƃ��ĕ����Ɨ�������
 * 
 * 20    05/04/18 16:02 Tsujimura543
 * getResultFromXML() �Ȃ� XML �֘A���[�e�B���e�B�֐��� xmlUtil.c
 * �Ɉڊ�
 * 
 * 19    05/04/18 15:58 Tsujimura543
 * bidders �֘A�����𕪗��Ɨ������Abidders.c �Ɉڊ�
 * 
 * 18    04/11/29 18:30 Tsujimura543
 * AMAZON_MOD_* �� AMAZON_MODE_* �ɕύX
 * 
 * 17    04/11/17 18:48 Tsujimura543
 * searchItemsByNicknameOnBidders() �� searchItemsByTrademarkOnBidders()
 * �������A������m�F
 * 
 * 16    04/11/17 18:19 Tsujimura543
 * searchItemsOnBidders() �������B����m�F�ς�
 * 
 * 15    04/11/17 16:02 Tsujimura543
 * setAffiriateIDOnBidders() �� setLinkIDOnBidders() ��ǉ�
 * 
 * 14    04/11/15 17:06 Tsujimura543
 * encodeURL() ���Ŋm�ۂ����̈�̉��������ǉ�
 * 
 * 13    04/11/15 14:45 Tsujimura543
 * setSiteIdOnValueCommerce(), setSpaceId1OnValueCommerce(),
 * setSpaceId2OnValueCommerce() ��ǉ�
 * 
 * 12    04/11/15 11:43 Tsujimura543
 * getAffiriateLinkOnJbook() ���C���A����m�F�I��
 * 
 * 11    04/11/15 11:10 Tsujimura543
 * getAffiriateLinkOnJbook() ��ǉ�
 * 
 * 10    04/11/11 11:26 Tsujimura543
 * �G���h�|�C���gURL��ύX
 * 
 * 9     04/11/04 16:44 Tsujimura543
 * �x�X�g�Z���[�ꗗ�̎擾���ʂ��\���̂Ɋi�[���ĕԂ��悤�ɂ���
 * 
 * 8     04/11/04 15:59 Tsujimura543
 * setSubscriptionIDOnAmazon() ��ǉ�
 * 
 * 7     04/11/02 21:46 Tsujimura543
 * �A�}�]���̌����I�v�V�����Ɂu���ׂĂ̏��i�v��ǉ�
 * 
 * 6     04/11/02 20:46 Tsujimura543
 * (1) HEAVY�ł̌������ʕԋp�Ή�
 * (2) �A�}�]���̐V�J�e�S���u��������&�z�r�[�v�̌����ɑΉ�
 * 
 * 5     04/11/01 21:01 Tsujimura543
 * �x�����x�� 4 �ł� warning ���\�Ȍ��茸�炵�Ă݂�
 * 
 * 4     04/11/01 19:56 Tsujimura543
 * �������ʂ��\���̂ɐݒ肵�ĕԂ��悤�ɂ��� (�Ƃ肠�����ALITE�ł̂�)
 * 
 * 3     04/10/08 15:30 Tsujimura543
 * JBOOK �� Valuecommerce �o�R MyLink �ɑΉ�
 * 
 * 2     04/07/07 11:45 Tsujimura543
 */

#include "xmlRPC.h"
#include "amazon.h"
#include <assert.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/amazon.c 2     09/05/29 7:09 tsupo $";
#endif


/*
 *  �������ʉ�� LITE��
 */
int
getItemsFromResultLite(
        const char  *xmlSrc,        /* (I) �������� (xml)       */
        int         *numOfItems,    /* (I/O) �������ʃA�C�e���� */
        AMAZON_LITE *result         /* (O) �������ʊi�[�̈�     */
    )
{
    int         numberOfItems = 0;
    const char  *p, *q;
    const char  *sectionEnd = "</Details>";

    /*
     * LITE �̏ꍇ
     *
     * <Details url="http://www.amazon.co.jp/exec/obidos/ASIN/4757512295/tsuporoswebpa-22?dev-t=D3622K0GSMQGO7%26camp=2025%26link_code=xm2">
     *    <Asin>4757512295</Asin>
     *    <ProductName>���i��</ProductName>
     *    <Catalog>Book</Catalog>
     *    <Authors>
     *       <Author>�����</Author>
     *    </Authors>
     *    <ReleaseDate>2004/08/06</ReleaseDate>
     *    <Manufacturer>�o�Ŏ�</Manufacturer>
     *    <ImageUrlSmall>http://images-jp.amazon.com/images/P/4757512295.09.THUMBZZZ.jpg</ImageUrlSmall>
     *    <ImageUrlMedium>http://images-jp.amazon.com/images/P/4757512295.09.MZZZZZZZ.jpg</ImageUrlMedium>
     *    <ImageUrlLarge>http://images-jp.amazon.com/images/P/4757512295.09.LZZZZZZZ.jpg</ImageUrlLarge>
     *    <Availability>�݌ɏ�</Availability>
     *    <ListPrice>�艿</ListPrice>
     *    <OurPrice>�̔����i</OurPrice>
     *    <UsedPrice>���É��i</UsedPrice>
     * </Details>
     */

    p = xmlSrc;
    while ( p && *p ) {
        p = strstr( p, "<Details url=\"" );
        if ( !p )
            break;

        memset( result, 0x00, sizeof ( AMAZON_LITE ) );
        p += 14;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( result->url, p, q - p );
            result->url[q - p] = NUL;
            p = q + 1;
        }

        p = getResultFromXML( p, "Asin",        sectionEnd,
                              result->asin );
        p = getResultFromXML( p, "ProductName", sectionEnd,
                              result->productName );

        p = getListFromXML( p, "Authors", "Author", sectionEnd,
                            result->authors, MAX_AUTHORINFO_LENGTH );

        p = getResultFromXML( p, "ReleaseDate",    sectionEnd,
                              result->releaseDate );
        p = getResultFromXML( p, "Manufacturer",   sectionEnd,
                              result->manufacturer );
        p = getResultFromXML( p, "ImageUrlSmall",  sectionEnd,
                              result->imageURLsmall );
        p = getResultFromXML( p, "ImageUrlMedium", sectionEnd,
                              result->imageURLmedium );
        p = getResultFromXML( p, "ImageUrlLarge",  sectionEnd,
                              result->imageURLlarge );
        p = getResultFromXML( p, "Availability",   sectionEnd,
                              result->availability );
        p = getResultFromXML( p, "ListPrice",      sectionEnd,
                              result->listPrice );
        p = getResultFromXML( p, "OurPrice",       sectionEnd,
                              result->amazonPrice );
        p = getResultFromXML( p, "UsedPrice",      sectionEnd,
                              result->usedPrice );

        numberOfItems++;
        if ( numberOfItems >= *numOfItems )
            break;
        result++;
    }
    *numOfItems = numberOfItems;

    return ( numberOfItems );
}

/*
 *  �������ʉ�� HEAVY��
 */
int
getItemsFromResultHeavy(
        const char   *xmlSrc,       /* (I) �������� (xml)       */
        int          *numOfItems,   /* (I/O) �������ʃA�C�e���� */
        AMAZON_HEAVY *result        /* (O) �������ʊi�[�̈�     */
    )
{
    int             numberOfItems = 0;
    unsigned long   numOfNodes    = 0;
    unsigned long   numOfReview   = 0;
    const char      *p, *q, *r;
    const char      *sectionEnd    = "</Details>";
    const char      *nodeListEnd   = "</BrowseList>";
    const char      *nodeEnd       = "</BrowseNode>";
    const char      *reviewListEnd = "</Reviews>";
    const char      *reviewEnd     = "</CustomerReview>";

    /*
     * HEAVY �̏ꍇ
     * <Details url="http://www.amazon.co.jp/exec/obidos/ASIN/4757512295/tsuporoswebpa-22?dev-t=D3622K0GSMQGO7%26camp=2025%26link_code=xm2">
     *    <Asin>4757512295</Asin>
     *    <ProductName>���i��</ProductName>
     *    <Catalog>Book</Catalog>
     *    <Authors>
     *       <Author>�����</Author>
     *    </Authors>
     *    <ReleaseDate>2004/08/06</ReleaseDate>
     *    <Manufacturer>�o�Ŏ�</Manufacturer>
     *    <ImageUrlSmall>http://images-jp.amazon.com/images/P/4757512295.09.THUMBZZZ.jpg</ImageUrlSmall>
     *    <ImageUrlMedium>http://images-jp.amazon.com/images/P/4757512295.09.MZZZZZZZ.jpg</ImageUrlMedium>
     *    <ImageUrlLarge>http://images-jp.amazon.com/images/P/4757512295.09.LZZZZZZZ.jpg</ImageUrlLarge>
     *    <ListPrice>�艿</ListPrice>
     *    <OurPrice>�̔����i</OurPrice>
     *    <UsedPrice>���É��i</UsedPrice>
     *    <SalesRank>33,288</SalesRank>
     *    <BrowseList>
     *       <BrowseNode>
     *          <BrowseId>12075941</BrowseId>
     *          <BrowseName>�m�[�h��</BrowseName>
     *       </BrowseNode>
     *    </BrowseList>
     *    <Media>���s�`��</Media>
     *    <Isbn>4757505523</Isbn>
     *    <Availability>�݌ɏ�</Availability>
     *    <Reviews>
     *       <AvgCustomerRating>4</AvgCustomerRating>
     *       <TotalCustomerReviews>1</TotalCustomerReviews>
     *       <CustomerReview>
     *          <Rating>4</Rating>
     *          <Summary>�T�v</Summary>
     *          <Comment>�R�����g</Comment>
     *       </CustomerReview>
     *    </Reviews>
     *    <SimilarProducts>
     *       <Product>4757511744</Product>
     *       <Product>4757512392</Product>
     *       <Product>4757503687</Product>
     *       <Product>4757502877</Product>
     *       <Product>4757512635</Product>
     *    </SimilarProducts>
     * </Details>
     */

    p = xmlSrc;
    while ( p && *p ) {
        p = strstr( p, "<Details url=\"" );
        if ( !p )
            break;

        memset( result, 0x00, sizeof ( AMAZON_HEAVY ) );
        numOfNodes  = 0;
        numOfReview = 0;
        p += 14;
        q = strchr( p, '"' );
        if ( q ) {
            strncpy( result->url, p, q - p );
            result->url[q - p] = NUL;
            p = q + 1;
        }

        p = getResultFromXML( p, "Asin",        sectionEnd,
                              result->asin );
        p = getResultFromXML( p, "ProductName", sectionEnd,
                              result->productName );

        p = getListFromXML( p, "Authors", "Author", sectionEnd,
                            result->authors, MAX_AUTHORINFO_LENGTH );

        p = getResultFromXML( p, "ReleaseDate",    sectionEnd,
                              result->releaseDate );
        p = getResultFromXML( p, "Manufacturer",   sectionEnd,
                              result->manufacturer );
        p = getResultFromXML( p, "ImageUrlSmall",  sectionEnd,
                              result->imageURLsmall );
        p = getResultFromXML( p, "ImageUrlMedium", sectionEnd,
                              result->imageURLmedium );
        p = getResultFromXML( p, "ImageUrlLarge",  sectionEnd,
                              result->imageURLlarge );
        p = getResultFromXML( p, "ListPrice",      sectionEnd,
                              result->listPrice );
        p = getResultFromXML( p, "OurPrice",       sectionEnd,
                              result->amazonPrice );
        p = getResultFromXML( p, "UsedPrice",      sectionEnd,
                              result->usedPrice );
        p = getIntegerFromXML(p, "SalesRank",      sectionEnd,
                              &(result->salesRank) );

        q = strstr( p, "<BrowseList>" );
        r = strstr( p, sectionEnd );
        if ( q && r ) {
            if ( q < r ) {
                char    *s = strstr( q + 12, nodeListEnd );

                q += 12;
                r = strchr( q, '<' );
                while ( r && !strncmp( r, "<BrowseNode>", 12 ) ) {
                    q = r + 12;
                    r = strchr( q, '<' );

                    if ( r ) {
                        p = r;
                        p = getResultFromXML( p, "BrowseId",   nodeEnd,
                                result->browseNodes[numOfNodes].browseNode );
                        p = getResultFromXML( p, "BrowseName", nodeEnd,
                                result->browseNodes[numOfNodes].nodeName );
                        numOfNodes++;
                    }

                    q = strstr( p, nodeEnd );
                    if ( q ) {
                        r = strchr( q + strlen(nodeEnd), '<' );
                        if ( r && (r == s) )
                            break;
                    }
                    else
                        break;  /* �\���G���[ */
                    if ( numOfNodes >= MAX_NUMOFNODES )
                        break;
                }

                p = q + 1;
            }
        }
        result->numOfBrowseNodes = numOfNodes;

        p = getResultFromXML( p, "Media",        sectionEnd,
                              result->media );
        p = getResultFromXML( p, "Isbn",         sectionEnd,
                              result->isbn );
        p = getResultFromXML( p, "Availability", sectionEnd,
                              result->availability );

        q = strstr( p, "<Reviews>" );
        r = strstr( p, sectionEnd );
        if ( q && r ) {
            if ( q < r ) {
                char    *s = strstr( q + 9, reviewListEnd );

                q += 9;
                r = strchr( q, '<' );
                if ( r ) {
                    p = r;
                    p = getFloatFromXML(  p, "AvgCustomerRating",
                                          reviewListEnd,
                                          &(result->reviews.averageRating) );
                    p = getIntegerFromXML(p, "TotalCustomerReviews",
                                          reviewListEnd,
                                          &(result->reviews.numOfReviews) );

                    r = strchr( p, '<' );
                    while ( r && !strncmp( r, "<CustomerReview>", 16 ) ) {
                        q = r + 16;
                        r = strchr( q, '<' );
                        if ( r ) {
                            p = r;
                            p = getIntegerFromXML(p, "Rating",  reviewEnd,
                               &(result->reviews.review[numOfReview].rating));
                            p = getResultFromXML( p, "Summary", reviewEnd,
                                 result->reviews.review[numOfReview].summury);
                            p = getResultFromXML( p, "Comment", reviewEnd,
                                 result->reviews.review[numOfReview].comment);
                            numOfReview++;
                        }

                        q = strstr( p, reviewEnd );
                        if ( q ) {
                            r = strchr( q + strlen(reviewEnd), '<' );
                            if ( r && (r == s) )
                                break;
                        }
                        else
                            break;  /* �\���G���[ */

                        if ((numOfReview == result->reviews.numOfReviews) ||
                            (numOfReview >= MAX_NUMOFREVIEWS)               )
                            break;
                    }
                }

                p = q + 1;
            }
        }
        result->reviews.numOfReviews = numOfReview;

        p = getListFromXML( p, "SimilarProducts", "Product", sectionEnd,
                            result->similarProcducts, MAX_LOGICALLINELEN );

        numberOfItems++;
        if ( numberOfItems >= *numOfItems )
            break;
        result++;
    }
    *numOfItems = numberOfItems;

    return ( numberOfItems );
}


/* Amazon �A�\�V�G�C�gID �̐ݒ� */
void
setAssociateIdOnAmazon( const char *associateID )
{
    if ( xmlrpc_p && associateID && *associateID )
        strcpy( xmlrpc_p->amazonAssociateID, associateID );
}

#if 0
/* Amazon Developer's Token �̐ݒ� */
void
setDevelopersTokenOnAmazon( const char *developerToken )
{
    if ( xmlrpc_p && developerToken && *developerToken )
        strcpy( xmlrpc_p->amazonDevelopperKey, developerToken );
}
#endif

/* Amazon Subscription ID �̐ݒ� */
void
setSubscriptionIDOnAmazon( const char *subscriptionID )
{
    if ( xmlrpc_p && subscriptionID && *subscriptionID )
        strcpy( xmlrpc_p->amazonSubscriptionID, subscriptionID );
}


/* Amazon �Ō��� */
#define BUFFER_SIZE     4096
#define ITEMS_PER_PAGE  10

#if 0
int
searchItemsOnAmazon(
        int        type,        /* (I) heavy or lite        */
        int        mode,        /* (I) �����Ώە���         */
        int        searchType,  /* (I) �������             */
        const char *keyword,    /* (I) �����ΏۃL�[���[�h   */
        int        *numOfItems, /* (I/O) �������ʃA�C�e���� */
        void       *result      /* (O) �������ʊi�[�̈�     */
    )
{
    int     ret = 0;
    char    *typeString  = "";
    char    *modeString  = "";
    char    *stypeString = "";
    char    targetURL[BUFFER_SIZE];
    char    *rcvBuf;
    char    *p;
    int     numberOfItems = 0;
    size_t  sz;

    switch ( type ) {
    case AMAZON_TYPE_HEAVY:
        typeString = "heavy";
        break;
    case AMAZON_TYPE_LITE:
    default:
        typeString = "lite";
        break;
    }

    switch ( mode ) {
    case AMAZON_MODE_JBOOKS:
        modeString = "books-jp";
        break;
    case AMAZON_MODE_EBOOKS:
        modeString = "books-us";
        break;
    case AMAZON_MODE_MUSIC:
        modeString = "music-jp";
        break;
    case AMAZON_MODE_CLASSIC:
        modeString = "classical-jp";
        break;
    case AMAZON_MODE_DVD:
        modeString = "dvd-jp";
        break;
    case AMAZON_MODE_VIDEO:
        modeString = "vhs-jp";
        break;
    case AMAZON_MODE_ELECTRONICS:
        modeString = "electronics-jp";
        break;
    case AMAZON_MODE_SOFTWARE:
        modeString = "software-jp";
        break;
    case AMAZON_MODE_GAME:
        modeString = "videogames-jp";
        break;
    case AMAZON_MODE_KITCHEN:
        modeString = "kitchen-jp";
        break;
    case AMAZON_MODE_TOYS:
        modeString = "toys-jp";
        break;
    case AMAZON_MODE_HOBBY:
        modeString = "hobbies-jp";
        break;
    case AMAZON_MODE_SPORTS:
        modeString = "sporting-goods-jp";
        break;
    case AMAZON_MODE_BLENDED:
    default:
        modeString = "blended";
        break;
    }

    switch ( searchType ) {
    case AMAZON_STYPE_ASIN:
        stypeString = "ASINSearch";
        break;
    case AMAZON_STYPE_NODE:
        stypeString = "BrowseNodeSearch";
        break;
    case AMAZON_STYPE_KEYWORD:
    default:
        stypeString = "KeywordSearch";
        break;
    }

    sz = MAX_CONTENT_SIZE * 4;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( numberOfItems );

    p = sjis2utf( keyword );
    sprintf( targetURL,
#if 0
             "http://xml-jp.amznxslt.com/onca/xml3?t=%s&dev-t=%s"
#else
             "http://xml.amazon.co.jp/onca/xml3?t=%s&dev-t=%s"
#endif
             "&type=%s&mode=%s&f=xml&%s=%s&locale=jp",
             xmlrpc_p->amazonAssociateID, xmlrpc_p->amazonDevelopperKey,
             typeString, modeString, stypeString,
             encodeURL( p ? p : keyword ) );

    setUpReceiveBuffer( rcvBuf, sz );
    ret = httpGetBuffer( targetURL, rcvBuf, FALSE );

    if ( (ret != -1) && (rcvBuf[0] != NUL) ) {
        if ( !strcmp( typeString, "lite" ) )
            numberOfItems = getItemsFromResultLite(
                                rcvBuf, numOfItems, result );
        else
            numberOfItems = getItemsFromResultHeavy(
                                rcvBuf, numOfItems, result );
    }

    encodeURL( NULL );
    free( rcvBuf );

    return ( numberOfItems );
}


/* Amazon �̃x�X�g�Z���[���X�g�擾 */
int
getSalesRankingOnAmazon(
        int        type,        /* (I) heavy or lite        */
        int        mode,        /* (I) �����Ώە���(��g)   */
        int        node,        /* (I) �����Ώە���(�i����) */
        const char *genre,      /* (I) �����Ώە��얼       */
        int        *numOfItems, /* (I/O) �������ʃA�C�e���� */
        void       *result      /* (O) �������ʊi�[�̈�     */
    )
{
    int     ret = 0;
    char    *typeString  = "";
    char    *modeString  = "";
    char    *stypeString = "";
    char    targetURL[BUFFER_SIZE];
    char    *rcvBuf;
    char    *p;
    int     numberOfItems = 0;
    size_t  sz;

    switch ( type ) {
    case AMAZON_TYPE_HEAVY:
        typeString = "heavy";
        break;
    case AMAZON_TYPE_LITE:
    default:
        typeString = "lite";
        break;
    }

    switch ( mode ) {
    case AMAZON_MODE_JBOOKS:
        modeString = "books-jp";
        break;
    case AMAZON_MODE_EBOOKS:
        modeString = "books-us";
        break;
    case AMAZON_MODE_MUSIC:
        modeString = "music-jp";
        break;
    case AMAZON_MODE_CLASSIC:
        modeString = "classical-jp";
        break;
    case AMAZON_MODE_DVD:
        modeString = "dvd-jp";
        break;
    case AMAZON_MODE_VIDEO:
        modeString = "vhs-jp";
        break;
    case AMAZON_MODE_ELECTRONICS:
        modeString = "electronics-jp";
        break;
    case AMAZON_MODE_SOFTWARE:
        modeString = "software-jp";
        break;
    case AMAZON_MODE_GAME:
        modeString = "videogames-jp";
        break;
    case AMAZON_MODE_KITCHEN:
        modeString = "kitchen-jp";
        break;
    case AMAZON_MODE_TOYS:
        modeString = "toys-jp";
        break;
    case AMAZON_MODE_HOBBY:
        modeString = "hobbies-jp";
        break;
    case AMAZON_MODE_SPORTS:
        modeString = "sporting-goods-jp";
        break;
    case AMAZON_MODE_BLENDED:
    default:
        modeString = "blended";
        break;
    }

    stypeString = "BrowseNodeSearch";

    sz = MAX_CONTENT_SIZE * 4;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( numberOfItems );

    p = sjis2utf( genre );
    sprintf( targetURL,
#if 0
             "http://xml-jp.amznxslt.com/onca/xml3?t=%s&dev-t=%s&"
#else
             "http://xml.amazon.co.jp/onca/xml3?t=%s&dev-t=%s&"
#endif
             "type=%s&sort=+salesrank&mode=%s&f=xml&%s=%d&genre=%s&locale=jp",
             xmlrpc_p->amazonAssociateID, xmlrpc_p->amazonDevelopperKey,
             typeString, modeString, stypeString, node,
             encodeURL( p ? p : genre ) );

    setUpReceiveBuffer( rcvBuf, sz );
    ret = httpGetBuffer( targetURL, rcvBuf, FALSE );

    if ( (ret != -1) && (rcvBuf[0] != NUL) ) {
        if ( !strcmp( typeString, "lite" ) )
            numberOfItems = getItemsFromResultLite(
                                rcvBuf, numOfItems, result );
        else
            numberOfItems = getItemsFromResultHeavy(
                                rcvBuf, numOfItems, result );
    }

    encodeURL( NULL );
    free( rcvBuf );

    return ( numberOfItems );
}
#endif


/*
 *  �������ʉ�� Small��
 */
int
getItemsFromResultSmall(
        const char  *xmlSrc,        /* (I) �������� (xml)       */
        int         *numOfItems,    /* (I/O) �������ʃA�C�e���� */
        AMAZON_LITE *result,        /* (O) �������ʊi�[�̈�     */
        BOOL        *next           /* (O) �������ʎ��y�[�W���� */
    )
{
    const char  *p, *q, *r;
    const char  *sectionEnd   = "</Item>";
    int         numberOfItems = 0;
    int         itemPage      = 0;
    int         totalPages    = 0;

    /* Small �̏ꍇ
     *  <Item>
     *    <ASIN>B00126NO4A</ASIN>
     *    <DetailPageURL>http://www.amazon.co.jp/gp/redirect.html%3FASIN=B00126NO4A%26tag=tsuporoswebpa-22%26lcode=xm2%26cID=2025%26ccmID=165953%26location=/o/ASIN/B00126NO4A%253FSubscriptionId=1P4XSJK2N3A8DR4AYN02</DetailPageURL>
     *    <ItemAttributes>
     *      <Manufacturer>Air Gates</Manufacturer>
     *      <ProductGroup>Sports</ProductGroup>
     *      <Title>Air Gates�i�G�A�Q�C�c�jAG-11Ti �`�^���z���S���t�{�[�� 12P</Title>
     *    </ItemAttributes>
     *  </Item>
     */

    /* Small,Request,ItemAttributes,OfferFull,Images �̏ꍇ
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
     *      <Feature>AIR FLIGHT�f�B���v���̋�͐��\�ƃ`�^���R�A�̗Z���I</Feature>
     *      <Label>Air Gates</Label>
     *      <Manufacturer>Air Gates</Manufacturer>
     *      <MPN>2004230390001</MPN>
     *      <ProductGroup>Sports</ProductGroup>
     *      <Publisher>Air Gates</Publisher>
     *      <Studio>Air Gates</Studio>
     *      <Title>Air Gates�i�G�A�Q�C�c�jAG-11Ti �`�^���z���S���t�{�[�� 12P</Title>
     *    </ItemAttributes>
     *    <OfferSummary>
     *      <LowestNewPrice>
     *        <Amount>780</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>�� 780</FormattedPrice>
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

    /* Small,Request,ItemAttributes,OfferFull,Images �� Books �̏ꍇ
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
     *      <Author>���� �M�`</Author>
     *      <Binding>��^�{</Binding>
     *      <Creator Role="��">���� �M�`</Creator>
     *      <EAN>9784798112961</EAN>
     *      <ISBN>4798112968</ISBN>
     *      <Label>�ĉj��</Label>
     *      <ListPrice>
     *        <Amount>2940</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>�� 2,940</FormattedPrice>
     *      </ListPrice>
     *      <Manufacturer>�ĉj��</Manufacturer>
     *      <NumberOfPages>360</NumberOfPages>
     *      <PackageDimensions>
     *        <Height Units="hundredths-inches">94</Height>
     *        <Length Units="hundredths-inches">906</Length>
     *        <Weight Units="hundredths-pounds">150</Weight>
     *        <Width Units="hundredths-inches">724</Width>
     *      </PackageDimensions>
     *      <ProductGroup>Book</ProductGroup>
     *      <PublicationDate>2007-04-20</PublicationDate>
     *      <Publisher>�ĉj��</Publisher>
     *      <Studio>�ĉj��</Studio>
     *      <Title>10���ł��ڂ���Ajax ���勳��</Title>
     *    </ItemAttributes>
     *    <OfferSummary>
     *      <LowestNewPrice>
     *        <Amount>2940</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>�� 2,940</FormattedPrice>
     *      </LowestNewPrice>
     *      <LowestUsedPrice>
     *        <Amount>2200</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>�� 2,200</FormattedPrice>
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
     *            <FormattedPrice>�� 2,940</FormattedPrice>
     *          </Price>
     *          <Availability>�ʏ�4�`5���ȓ��ɔ���</Availability>
     *          <IsEligibleForSuperSaverShipping>1</IsEligibleForSuperSaverShipping>
     *        </OfferListing>
     *      </Offer>
     *    </Offers>
     *  </Item>
     */

    *next = FALSE;
    p = xmlSrc;
#ifdef  _DEBUG
    {
        FILE    *fp = fopen( "./amazonResult.xml", "w" );
        if ( fp ) {
            fputs( p, fp );
            fclose( fp );
        }
    }
#endif
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
            *next = TRUE;   /* ���y�[�W���� */
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
 *  �������ʉ�� Medium��
 */
int
getItemsFromResultMedium(
        const char   *xmlSrc,       /* (I) �������� (xml)       */
        int          *numOfItems,   /* (I/O) �������ʃA�C�e���� */
        AMAZON_HEAVY *result,       /* (O) �������ʊi�[�̈�     */
        BOOL         *next          /* (O) �������ʎ��y�[�W���� */
    )
{
    int             numberOfItems = 0;
    unsigned long   numOfNodes    = 0;
    unsigned long   numOfReview   = 0;
    int             itemPage      = 0;
    int             totalPages    = 0;
    const char      *p, *q, *r;
    const char      *sectionEnd   = "</Item>";

    /* Medium �̏ꍇ
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
     *      <Feature>AIR FLIGHT�f�B���v���̋�͐��\�ƃ`�^���R�A�̗Z���I</Feature>
     *      <Label>Air Gates</Label>
     *      <Manufacturer>Air Gates</Manufacturer>
     *      <MPN>2004230390001</MPN>
     *      <ProductGroup>Sports</ProductGroup>
     *      <Publisher>Air Gates</Publisher>
     *      <Studio>Air Gates</Studio>
     *      <Title>Air Gates�i�G�A�Q�C�c�jAG-11Ti �`�^���z���S���t�{�[�� 12P</Title>
     *    </ItemAttributes>
     *    <OfferSummary>
     *      <LowestNewPrice>
     *        <Amount>780</Amount>
     *        <CurrencyCode>JPY</CurrencyCode>
     *        <FormattedPrice>�� 780</FormattedPrice>
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
     *          �`�`����Air Gates�i�G�A�Q�C�c�j�J���R���Z�v�g�����`�`
     *          AirGates�́A�A�X���[�g�S���t�@�[��ڎw���A�x���[�W�S���t�@�[�ɖ��������鍂���\�ƁA�X�|�[�e�B�Ŏa�V�ȃf�U�C����Z�������n�C�R�X�g�p�t�H�[�}���X�u�����h�ł��B
     *          �y �{�[���̐��\ �E�E�E�z 
     *          ��DUPONT�А��ɔ��T�[�����J�o�[���n�C�G�i�W�[�\�t�g�`�^���R�A�Ń\�t�g�t�B�[�����O�A�r�b�O�L�����[���������܂����B
     *          ��432 AIR FLIGHT�f�B���v���ŗD�ꂽ��͐��\�𔭊��B�A�Q���X�g���ł����e�����D�ꂽ�򋗗����\���������܂��B
     *          ���n�C�G�i�W�[�\�t�g�`�^���R�A�͗D�ꂽ�������\�Ńr�b�O�L�����[�������炵�܂��B
     *          �y �{�[���f�U�C�� �E�E�E�z
     *          ���i���o�[�����́A���̃{�[���Ƃ̋�ʂ����₷���A�����̂���f�U�C���ɂȂ��Ă��܂��B��
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
            *next = TRUE;   /* ���y�[�W���� */
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
                                  result->isbn );       // 13��ISBN
        else {
            q = strstr( p, "<ISBN>" );
            if ( q && (q < r) )
                p = getResultFromXML( p, "ISBN", sectionEnd,
                                      result->isbn );   // 10��ISBN
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



/* Large �̏ꍇ
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
 *      <Feature>AIR FLIGHT�f�B���v���̋�͐��\�ƃ`�^���R�A�̗Z���I</Feature>
 *      <Label>Air Gates</Label>
 *      <Manufacturer>Air Gates</Manufacturer>
 *      <MPN>2004230390001</MPN>
 *      <ProductGroup>Sports</ProductGroup>
 *      <Publisher>Air Gates</Publisher>
 *      <Studio>Air Gates</Studio>
 *      <Title>Air Gates�i�G�A�Q�C�c�jAG-11Ti �`�^���z���S���t�{�[�� 12P</Title>
 *    </ItemAttributes>
 *    <OfferSummary>
 *      <LowestNewPrice>
 *        <Amount>780</Amount>
 *        <CurrencyCode>JPY</CurrencyCode>
 *        <FormattedPrice>�� 780</FormattedPrice>
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
 *          �`�`����Air Gates�i�G�A�Q�C�c�j�J���R���Z�v�g�����`�`
 *          AirGates�́A�A�X���[�g�S���t�@�[��ڎw���A�x���[�W�S���t�@�[�ɖ��������鍂���\�ƁA�X�|�[�e�B�Ŏa�V�ȃf�U�C����Z�������n�C�R�X�g�p�t�H�[�}���X�u�����h�ł��B
 *          �y �{�[���̐��\�E�E�E�z 
 *          ��DUPONT�А��ɔ��T�[�����J�o�[���n�C�G�i�W�[�\�t�g�`�^���R�A�Ń\�t�g�t�B�[�����O�A�r�b�O�L�����[���������܂����B 
 *          ��432 AIR FLIGHT�f�B���v���ŗD�ꂽ��͐��\�𔭊��B�A�Q���X�g���ł����e�����D�ꂽ�򋗗����\���������܂��B 
 *          ���n�C�G�i�W�[�\�t�g�`�^���R�A�͗D�ꂽ�������\�Ńr�b�O�L�����[�������炵�܂��B
 *          �y �{�[���f�U�C�� �E�E�E�z 
 *          ���i���o�[�����́A���̃{�[���Ƃ̋�ʂ����₷���A�����̂���f�U�C���ɂȂ��Ă��܂��B 
 *          ��
 *        </Content>
 *      </EditorialReview>
 *    </EditorialReviews>
 *    <BrowseNodes>
 *      <BrowseNode>
 *        <BrowseNodeId>15314411</BrowseNodeId>
 *        <Name>�S���t�{�[��</Name>
 *        <Children>
 *          <BrowseNode>
 *            <BrowseNodeId>15320151</BrowseNodeId>
 *            <Name>�����Y</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>15343311</BrowseNodeId>
 *            <Name>���f�B�[�X</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>15343301</BrowseNodeId>
 *            <Name>���X�g�{�[��</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>15320161</BrowseNodeId>
 *            <Name>���̑�</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>16005651</BrowseNodeId>
 *            <Name>�S���i</Name>
 *          </BrowseNode>
 *          <BrowseNode>
 *            <BrowseNodeId>16005661</BrowseNodeId>
 *            <Name>�u�����h��</Name>
 *          </BrowseNode>
 *        </Children>
 *        <Ancestors>
 *          <BrowseNode>
 *            <BrowseNodeId>14315441</BrowseNodeId>
 *            <Name>�S���t</Name>
 *            <Ancestors>
 *              <BrowseNode>
 *                <BrowseNodeId>14315361</BrowseNodeId>
 *                <Name>�J�e�S���[��</Name>
 *                <Ancestors>
 *                  <BrowseNode>
 *                    <BrowseNodeId>14304371</BrowseNodeId>
 *                    <Name>�X�|�[�c&amp;�A�E�g�h�A</Name>
 *                  </BrowseNode>
 *                </Ancestors>
 *              </BrowseNode>
 *            </Ancestors>
 *          </BrowseNode>
 *        </Ancestors>
 *      </BrowseNode>
 *      <BrowseNode>
 *        <BrowseNodeId>15741001</BrowseNodeId>
 *        <Name>�S���t</Name>
 *        <Ancestors>
 *          <BrowseNode>
 *            <BrowseNodeId>15740941</BrowseNodeId>
 *            <Name>���[�Y�h�X�|�[�c</Name>
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
        int        mode,        /* (I) �����Ώە���         */
        int        searchType,  /* (I) �������             */
        const char *keyword,    /* (I) �����ΏۃL�[���[�h   */
        int        *numOfItems, /* (I/O) �������ʃA�C�e���� */
        void       *result      /* (O) �������ʊi�[�̈�     */
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

     // memset( targetURL, 0x00, BUFFER_SIZE );
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
                                        /* Medium / Large ���p (�b��) */
            if ( numberOfMaxItems <= *numOfItems )
                break;
            unit++;
        }
    } while ( next );

    encodeURL( NULL );
    free( rcvBuf );

    return ( *numOfItems );
}

/* Amazon �̃x�X�g�Z���[���X�g�擾 (ECS4.0��) */
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif

int
getSalesRankingOnAmazon4(
        int        type,        /* (I) Small, Medium, Large */
        int        mode,        /* (I) �����Ώە���(��g)   */
        int        node,        /* (I) �����Ώە���(�i����) */
        const char *genre,      /* (I) �����Ώە��얼       */
        int        *numOfItems, /* (I/O) �������ʃA�C�e���� */
        void       *result      /* (O) �������ʊi�[�̈�     */
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
                                        /* Medium / Large ���p (�b��) */
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
