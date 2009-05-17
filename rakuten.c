/*
 *  rakuten.c
 *
 * History:
 * $Log: /comm/xmlRPC/rakuten.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 27    08/09/10 18:25 Tsujimura543
 * �y�V�u���O�֘A�̊֐��Q���폜 (xmlRPC.dll �O�ֈړ�)
 * 
 * 26    07/02/21 19:46 Tsujimura543
 * CatalogSearch �̓�����m�F
 * 
 * 25    07/02/21 19:15 Tsujimura543
 * ItemCodeSearch, BookSearch, CDSearch, DVDSearch �̓�����m�F
 * (itemCaption �������Ώۂɂł���悤�ɁAdecodeURL() �̓����o�b�t�@�T�C�Y
 * ��ύX����)
 * 
 * 24    07/02/21 14:48 Tsujimura543
 * ItemSearch �� GenreSearch �̓�����m�F
 * 
 * 23    07/02/20 22:42 Tsujimura543
 * CatalogSearch ������ (����͖��m�F)
 * 
 * 22    07/02/20 22:07 Tsujimura543
 * BookSearch, CDSearch, DVDSearch ������ (����͖��m�F)
 * 
 * 21    07/02/20 21:48 Tsujimura543
 * ItemCodeSearch ������ (����͖��m�F)
 * 
 * 20    07/02/20 21:20 Tsujimura543
 * �y�V�E�F�u�T�[�r�X�̂����AItemSearch �� GenreSearch ������
 * (����͖��m�F)
 * 
 * 19    07/01/23 15:31 Tsujimura543
 * postRakuten() �̓���m�F�A�I�� (�V�����Ǘ���ʂւ̑Ή���ƁA����)
 * 
 * 18    07/01/23 15:29 Tsujimura543
 * (1) getCategoryListRakuten() ��ǉ�
 * (2) postRakuten() �̈�����ǉ����A�J�e�S�����w�肵�ē��e�ł���悤�ɂ���
 * 
 * 17    07/01/23 14:01 Tsujimura543
 * ���O�C���V�[�P���X���C�� (2007�N1��17���t�̊Ǘ���ʎd�l�ύX�ɑΉ�)
 * 
 * 16    07/01/17 19:26 Tsujimura543
 * �y�V�f�x���b�p�[ID �Ή�
 * 
 * 15    06/10/23 16:21 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍��ǉ�
 * 
 * 14    06/09/12 21:48 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�t���[�h�~�΍�����{
 * 
 * 13    06/09/11 18:23 Tsujimura543
 * getBlogIDsRakuten() ��ǉ�
 * 
 * 12    06/02/20 23:30 Tsujimura543
 * cookie ���̓��ʈ�������߂�
 * 
 * 11    05/12/12 14:43 Tsujimura543
 * RAKUTEN_GENRE_PHOTOBOOL �� RAKUTEN_GENRE_PHOTOBOOK �ɏC��
 * 
 * 10    05/10/18 18:58 Tsujimura543
 * httpPostWithSession() �̈����ǉ��ɔ����C�������{
 * 
 * 9     05/10/18 18:11 Tsujimura543
 * httpGetBufferWithSession() �̈����ǉ��ɔ����C�������{
 * 
 * 8     05/09/02 14:37 Tsujimura543
 * affiriate �� affiliate �ɏC�� (�Ԃ�ԈႢ)
 * 
 * 7     05/05/18 21:56 Tsujimura543
 * getSalesRankingOnRakuten() �̎d�l��ύX (�\���̂Ɍ������ʂ��i�[����
 * �悤�ɂ���) [���̋@�\����������̂ɕK�v�Ȋ֐���ǉ�]
 * 
 * 6     05/04/21 19:10 Tsujimura543
 * postRakuten() ���C�����A���e�������������ǂ����m�F����悤�ɂ���
 * 
 * 5     05/04/21 16:04 Tsujimura543
 * loginRakuten() �ɑ�4������ǉ�
 * 
 * 4     05/04/21 15:14 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 3     05/04/21 15:10 Tsujimura543
 * loginRakuten() �� postRakuten() ��ǉ��B���e�ł��邱�Ƃ��m�F�B
 * (�J�e�S���w��͖��Ή�)
 * 
 * 2     05/04/18 16:23 Tsujimura543
 * �u�y�V�A�t�B���G�C�g�v�֘A�̃R�����g�� amazon.h ����ړ�
 * 
 * 1     05/04/18 16:18 Tsujimura543
 * �u�y�V�A�t�B���G�C�g�v�֘A������ amazon.c ���番���Ɨ������Arakuten.c
 * �Ƃ���
 */

#include "xmlRPC.h"
#include "rakuten.h"
#include <time.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/rakuten.c 1     09/05/14 3:46 tsupo $";
#endif

/*
 * �y�V�A�t�B���G�C�g�֘A
 */

#define BUFFER_SIZE         512
#define SEARCH_RESULT_SIZE  102400

/* �y�V �f�x���b�p�[ID �̐ݒ� */
void
setDeveloperIdOnRakuten( const char *developerID )
{
    if ( xmlrpc_p && developerID && *developerID )
        strcpy( xmlrpc_p->rakutenDeveloperID, developerID );
}

/* �y�V �A�t�B���G�C�gID(��) �̐ݒ� */
void
setAffiliateIdOnRakuten( const char *affiliateID )
{
    if ( xmlrpc_p && affiliateID && *affiliateID )
        strcpy( xmlrpc_p->rakutenAffiliateID, affiliateID );
}

/* �y�V �A�t�B���G�C�gID(�V) �̐ݒ� */
void
setAffiliateIdOnRakuten2( const char *affiliateID2 )
{
    if ( xmlrpc_p && affiliateID2 && *affiliateID2 )
        strcpy( xmlrpc_p->rakutenAffiliateID2, affiliateID2 );
}

/*
 * �ȉ��̌`���� XML ���� name �����o��
 *
 *   <tagName>
 *      <subTagName typeName="name" />
 *   </tagName>
 */

char    *
getListExFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *subTagName,
        const char *typeName,
        const char *sectionEnd,
        char       *result,
        size_t     areaSizeOfResult
    )
{
    const char  *p = xmlSrc, *q, *r, *s;
    char        targetTag[MAX_NAMELEN];
    char        targetEnd[MAX_NAMELEN];
    char        subTag[MAX_NAMELEN];
    char        name[MAX_NAMELEN];
    int         taglen, sublen, namelen;

    sprintf( targetTag, "<%s>",  tagName );
    sprintf( targetEnd, "</%s>", tagName );
    sprintf( subTag,    "<%s ",  subTagName );
    sprintf( name,      "%s=\"", typeName );
    taglen  = strlen( targetTag );
    sublen  = strlen( subTag );
    namelen = strlen( name );

    q = strstr( p, targetTag );
    r = strstr( p, sectionEnd );
    if ( q && r ) {
        if ( q < r ) {
            size_t  len = 0;
            char    *t = strstr( q + taglen, targetEnd );

            if ( t ) {
                result[0] = NUL;

                q += taglen;
                r = strchr( q, '<' );
                while ( r && !strncmp( r, subTag, sublen ) ) {
                    q = r + sublen;
                    r = strstr( q, name );
                    if ( r ) {
                        r += namelen;
                        s = strchr( r, '"' );
                        if ( s ) {
                            if ( len > 0 ) {
                                strcat( result, ", " );
                                len += 2;
                            }
                            strncat( result, r, s - r );
                            result[len + (s - r)] = NUL;
                            len += (s - r);
                        }
                    }

                    r = strchr( q, '>' );
                    if ( r && (r == t) )
                        break;
                    if ( len >= areaSizeOfResult )
                        break;
                }

                p = q + 1;
            }
        }
    }

    return ( (char *)p );
}


/*
 *  �������ʉ�� �y�V�u�b�N�X XML �� (HEAVY ��)
 */
int
getItemsFromResultRakutenHeavy(
        const char    *xmlSrc,      /* (I) �������� (xml)       */
        int           *numOfItems,  /* (I/O) �������ʃA�C�e���� */
        RAKUTEN_HEAVY *result       /* (O) �������ʊi�[�̈�     */
    )
{
    int         numberOfItems = 0;
    const char  *sectionEnd   = "</item>";
    const char  *p;

    /*
     * �y�V�u�b�N�X, XML �`��
     *    <item>
     *      <Isbn>4839915253</Isbn>
     *      <SalesRank>10</SalesRank>
     *      <Url>http://pt.afl.rakuten.co.jp/c/0008a695.5601c7dd/?url=http%3A%2F%2Fbooks.rakuten.co.jp%2FRBOOKS%2F0001682468%2F</Url>
     *      <ProductName>�����I�p�\�R���u���G�N�Z��</ProductName>
     *      <Manufacturer>�����R�~���j�P�[�V�����Y</Manufacturer>
     *      <ImageUrlSmall>http://image.books.rakuten.co.jp/books/com/images/goods/83991525.jpg</ImageUrlSmall>
     *      <ListPrice>530</ListPrice>
     *      <Authors>
     *        <Author id="1" name="�����R�~���j�P�[�V�����Y"/>
     *      </Authors>
     *    </item>
     */

    p = xmlSrc;
    while ( p && *p ) {
        p = strstr( p, "<item>" );
        if ( !p )
            break;

        memset( result, 0x00, sizeof ( RAKUTEN_HEAVY ) );
        p += 7;
        p = getResultFromXML( p, "Isbn",        sectionEnd,
                              result->isbn );
        p = getIntegerFromXML(p, "SalesRank",      sectionEnd,
                              &(result->salesRank) );
        p = getResultFromXML( p, "Url", sectionEnd,
                              result->url );
        p = getResultFromXML( p, "ProductName", sectionEnd,
                              result->productName );
        p = getResultFromXML( p, "Manufacturer",   sectionEnd,
                              result->manufacturer );
        p = getResultFromXML( p, "ImageUrlSmall",  sectionEnd,
                              result->imageURLsmall );
        p = getResultFromXML( p, "ListPrice",      sectionEnd,
                              result->listPrice );

        p = getListExFromXML( p, "Authors", "Author", "name", sectionEnd,
                              result->authors, MAX_AUTHORINFO_LENGTH );

        numberOfItems++;
        if ( numberOfItems >= *numOfItems )
            break;
        result++;
    }
    *numOfItems = numberOfItems;

    return ( numberOfItems );
}


/*
 *  �������ʉ�� �y�V�u�b�N�X HTML �� (LITE ��)
 */
int
getItemsFromResultRakutenLite(
        const char   *xmlSrc,       /* (I) �������� (xml)       */
        int          *numOfItems,   /* (I/O) �������ʃA�C�e���� */
        RAKUTEN_LITE *result        /* (O) �������ʊi�[�̈�     */
    )
{
    int         numberOfItems = 0;
    const char  *p = xmlSrc, *q, *r, *s;

    while ( ( q = strstr( p, "<a " ) ) != NULL ) {
        memset( result, 0x00, sizeof ( RAKUTEN_LITE ) );
        r = strstr( q + 3, "href=\"" );
        if ( r ) {
            r += 6;
            s = strchr( r, '"' );
            if ( s ) {
                strncpy( result->url, r, s - r );
                result->url[s - r] = NUL;

                r = strchr( s + 1, '>' );
                if ( r ) {
                    r++;
                    s = strchr( r, '<' );
                    if ( s ) {
                        strncpy( result->productName, r, s - r );
                        result->productName[s - r] = NUL;

                        numberOfItems++;
                        if ( numberOfItems >= *numOfItems )
                            break;
                        result++;

                        q = strchr( s + 1, '>' );
                        if ( q )
                            p = q + 1;
                        else
                            p = s + 1;
                    }
                }
                else
                    p = s + 1;
            }
            else
                p = r + 1;
        }
        else
            p = q + 3;
    }
    *numOfItems = numberOfItems;

    return ( numberOfItems );
}


/* �y�V�u�b�N�X �Z�[���X�����L���O�̎擾 */
int
getSalesRankingOnRakuten(
        int  type,          /* (I) �擾����t�@�C���̌`�� */
        int  service,       /* (I) �ΏۃT�[�r�X           */
        int  genre,         /* (I) �W������               */
        int  *numOfItems,   /* (I/O) �������ʃA�C�e����   */
        void *result        /* (O) �������ʊi�[�̈�       */
    )
{
    int     ret = 0, num = 0;
    char    *typeString  = "";
    char    *servString  = "";
    char    targetURL[BUFFER_SIZE];
    char    *rcvBuf;
    size_t  sz = SEARCH_RESULT_SIZE;

    if ( !numOfItems || (*numOfItems <= 0) || !result )
        return ( ret );

    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( ret );

    switch ( type ) {
    case RAKUTEN_TYPE_HTML:
        typeString = "html";
        break;
    case RAKUTEN_TYPE_XML:
    default:
        typeString = "xml";
        break;
    }

    if ( *numOfItems > 10 )
        *numOfItems = 10;

    switch ( service ) {
    case RAKUTEN_SERVICE_BOOKS:
    default:
        servString = "books";   /* ���̂Ƃ���A�u�y�V�u�b�N�X�v�̂ݑΉ� */
        break;
    }

    if ( (genre < RAKUTEN_GENRE_GENERAL)   ||
         (genre > RAKUTEN_GENRE_PHOTOBOOK)    )
        genre = RAKUTEN_GENRE_GENERAL;

    sprintf( targetURL,
             "http://xml.affiliate.rakuten.co.jp/?type=%s&"
             "service=%s&hash=%s&genre=%d&num=%d",
             typeString, servString,
             xmlrpc_p->rakutenAffiliateID,
             genre, *numOfItems );
    setUpReceiveBuffer( rcvBuf, sz );
    ret = httpGetBuffer( targetURL, rcvBuf, FALSE );

    if ( rcvBuf[0] ) {
        if ( type == RAKUTEN_TYPE_XML ) {
            RAKUTEN_HEAVY   *r = (RAKUTEN_HEAVY *)result;

            num = getItemsFromResultRakutenHeavy( rcvBuf, numOfItems, r );
        }
        else {
            RAKUTEN_LITE    *r = (RAKUTEN_LITE *)result;

            num = getItemsFromResultRakutenLite( rcvBuf, numOfItems, r );
        }
    }

    ret = *numOfItems = num;
    free( rcvBuf );

    return ( ret );
}



/*
 *  �y�V�E�F�u�T�[�r�X �֘A
 */

static char    *
decodeURL2( char *s )
{
    char    *p;
    char    *q;

    strcpy( s, decodeURL( s ) );
    p = s;
    while ( *p ) {
        q = strstr( p, "&lt;" );
        if ( q ) {
            *q = '<';
            strcpy( q + 1, q + 4 );
            continue;
        }

        q = strstr( p, "&gt;" );
        if ( q ) {
            *q = '>';
            strcpy( q + 1, q + 4 );
            continue;
        }

        q = strstr( p, "&nbsp;" );
        if ( q ) {
            *q = ' ';
            strcpy( q + 1, q + 6 );
            continue;
        }

        q = strstr( p, "&copy;" );
        if ( q ) {
            *q       = '(';
            *(q + 1) = 'c';
            *(q + 2) = ')';
            strcpy( q + 3, q + 6 );
            continue;
        }

        q = strstr( p, "&quot;" );
        if ( q ) {
            *q = '"';
            strcpy( q + 1, q + 6 );
            continue;
        }

        q = strstr( p, "&#39;" );
        if ( q ) {
            *q = '\'';
            strcpy( q + 1, q + 5 );
            continue;
        }

        break;
    }

    p = s;
    while ( *p ) {
        q = strstr( p, "<br>" );
        if ( q ) {
            *q = '\n';
            strcpy( q + 1, q + 4 );
            continue;
        }
        q = strstr( p, "<br />" );
        if ( q ) {
            *q = '\n';
            strcpy( q + 1, q + 6 );
            continue;
        }

        q = strchr( p, '<' );
        if ( q ) {
            char    *r = strchr( q, '>' );
            if ( r ) {
                strcpy( q, r + 1 );
                continue;
            }
        }

        break;
    }

    return ( s );
}

char    *
getStringFromElement(
        char       *dst,
        const char *src,
        const char *terminator,
        const char *elementName
    )
{
    char    *p, *q;
    char    targetS[32];
    char    targetE[32];
    int     len;

    *dst = NUL;
    sprintf( targetS, "<%s>",  elementName );
    sprintf( targetE, "</%s>", elementName );
    len = strlen( targetS );

    p = strstr( src, targetS );
    if ( p && (p < terminator) ) {
        p += len;
        q = strstr( p, targetE );
        if ( q && (q < terminator) ) {
            strncpy( dst, p, q - p );
            dst[q - p] = NUL;
        }
    }

    return ( dst );
}

char    *
getDecodedStringFromElement(
        char       *dst,
        const char *src,
        const char *terminator,
        const char *elementName
    )
{
    char    *p, *q;

    p = getStringFromElement( dst, src, terminator, elementName );
    if ( p && *p ) {
        q = decodeURL2( p );
        strcpy( dst, q );
        p = utf2sjisEx( dst );
        if ( p )
            strcpy( dst, p );
    }

    return ( dst );
}

char    *
getUrlFromElement(
        char       *dst,
        const char *src,
        const char *terminator,
        const char *elementName
    )
{
    char    *p, *q;

    p = getStringFromElement( dst, src, terminator, elementName );
    if ( p && *p ) {
        q = decodeURL( p );
        strcpy( dst, q );
    }

    return ( dst );
}

int
getIntegerFromElement(
        const char *src,
        const char *terminator,
        const char *elementName
    )
{
    char    *p, *q;
    char    targetS[32];
    char    targetE[32];
    int     len;
    int     ret = 0;

    sprintf( targetS, "<%s>",  elementName );
    sprintf( targetE, "</%s>", elementName );
    len = strlen( targetS );

    p = strstr( src, targetS );
    if ( p && (p < terminator) ) {
        q = p + len;
        p = strstr( q, targetE );
        if ( p && (p < terminator) )
            ret = atol( q );
    }

    return ( ret );
}

double
getDoubleFromElement(
        const char *src,
        const char *terminator,
        const char *elementName
    )
{
    char    *p, *q;
    char    targetS[32];
    char    targetE[32];
    int     len;
    double  ret = 0.0;

    sprintf( targetS, "<%s>",  elementName );
    sprintf( targetE, "</%s>", elementName );
    len = strlen( targetS );

    p = strstr( src, targetS );
    if ( p && (p < terminator) ) {
        q = p + len;
        p = strstr( q, targetE );
        if ( p && (p < terminator) )
            ret = atof( q );
    }

    return ( ret );
}

void
getItemsFromResponse(
        const char   *src,
        RAKUTEN_ITEM *item,
        int          numOfItems
    )
{
    int         cnt = 0;
    const char  *t = src;
    char        *u, *v;

    do {
        u = strstr( t, "<Item>" );
        if ( !u )
            break;
        t = u + 6;
        v = strstr( t, "</Item>" );
        if ( !v )
            break;

        memset( &(item[cnt]), 0x00, sizeof ( RAKUTEN_ITEM ) );

        getDecodedStringFromElement( item[cnt].itemName, t, v, "itemName" );
        getStringFromElement( item[cnt].itemCode, t, v, "itemCode" );

        item[cnt].itemPrice = getIntegerFromElement( t, v, "itemPrice" );

        getDecodedStringFromElement( item[cnt].itemCaption,
                                     t, v, "itemCaption" );
        getUrlFromElement( item[cnt].itemUrl, t, v, "itemUrl" );
        getUrlFromElement( item[cnt].affiliateUrl, t, v, "affiliateUrl" );

        item[cnt].imageFlag = getIntegerFromElement( t, v, "imageFlag" );

        getUrlFromElement( item[cnt].smallImageUrl, t, v, "smallImageUrl" );
        getUrlFromElement( item[cnt].mediumImageUrl, t, v, "mediumImageUrl" );

        item[cnt].availability      =
                        getIntegerFromElement( t, v, "availability" );
        item[cnt].taxFlag           =
                        getIntegerFromElement( t, v, "taxFlag" );
        item[cnt].postageFlag       =
                        getIntegerFromElement( t, v, "postageFlag" );
        item[cnt].creditCardFlag    =
                        getIntegerFromElement( t, v, "creditCardFlag" );
        item[cnt].shopOfTheYearFlag =
                        getIntegerFromElement( t, v, "shopOfTheYearFlag" );
        item[cnt].affiliateRate     =
                        getDoubleFromElement( t, v, "affiliateRate" );

        getStringFromElement( item[cnt].startTime, t, v, "startTime" );
        getStringFromElement( item[cnt].endTime, t, v, "endTime" );

        item[cnt].reviewCount   = getIntegerFromElement(t, v, "reviewCount");
        item[cnt].reviewAverage = getDoubleFromElement(t, v, "reviewAverage");

        getDecodedStringFromElement( item[cnt].shopName, t, v, "shopName" );
        getStringFromElement( item[cnt].shopCode, t, v, "shopCode" );
        getUrlFromElement( item[cnt].shopUrl, t, v, "shopUrl" );

        item[cnt].genreId = getIntegerFromElement( t, v, "genreId" );

        t = v + 7;
        cnt++;
    } while ( cnt < numOfItems );
}

void
getCatalogsFromResponse(
        const char      *src,
        RAKUTEN_CATALOG *catalog,
        int             numOfCatalogs
    )
{
    int         cnt = 0;
    const char  *t = src;
    char        *u, *v;

    do {
        u = strstr( t, "<Catalog>" );
        if ( !u )
            break;
        t = u + 9;
        v = strstr( t, "</Catalog>" );
        if ( !v )
            break;

        getDecodedStringFromElement( catalog[cnt].catalogName,
                                     t, v, "catalogName" );
        getStringFromElement( catalog[cnt].catalogCode, t, v, "catalogCode" );
        getDecodedStringFromElement( catalog[cnt].modelNo, t, v, "modelNo" );
        getDecodedStringFromElement( catalog[cnt].makerName,
                                     t, v, "makerName" );
        getDecodedStringFromElement( catalog[cnt].seriesName,
                                     t, v, "seriesName" );
        getDecodedStringFromElement( catalog[cnt].onSaleDate,
                                     t, v, "onSaleDate" );

        catalog[cnt].catalogPrice =
                        getIntegerFromElement( t, v, "catalogPrice" );

        getDecodedStringFromElement( catalog[cnt].catalogCaption,
                                     t, v, "catalogCaption" );
        getUrlFromElement( catalog[cnt].catalogUrl, t, v, "catalogUrl" );

        catalog[cnt].imageFlag = getIntegerFromElement( t, v, "imageFlag" );

        getUrlFromElement(catalog[cnt].smallImageUrl, t, v, "smallImageUrl");
        getUrlFromElement(catalog[cnt].mediumImageUrl,t, v, "mediumImageUrl");

        catalog[cnt].reviewCount = getIntegerFromElement(t, v, "reviewCount");
        catalog[cnt].genreId     = getIntegerFromElement( t, v, "genreId" );

        t = v + 10;
        cnt++;
    } while ( cnt < numOfCatalogs );
}

char    *
getSortOrderString( int sort, const char *defaultOrder )
{
    const char  *s = "-reviewCount"; // �f�t�H���g

    if ( defaultOrder && *defaultOrder )
        s = defaultOrder;

    switch ( sort ) {
    // item �p
    case RAKUTEN_SORT_AFFRATE_ASCENDING:    // �A�t�B���G�C�g������(����)
        s = "+affiliateRate";
        break;
    case RAKUTEN_SORT_AFFRATE_DESCENDING:   // �A�t�B���G�C�g������(�~��)
        s = "-affiliateRate";
        break;
    case RAKUTEN_SORT_RVCNT_ASCENDING:      // ���r���[������(����)
        s = "+reviewCount";
        break;
    case RAKUTEN_SORT_RVCNT_DESCENDING:     // ���r���[������(�~��)
        s = "-reviewCount";
        break;
    case RAKUTEN_SORT_PRICE_ASCENDING:      // ���i��(����)
        s = "+itemPrice";
        break;
    case RAKUTEN_SORT_PRICE_DESCENDING:     // ���i��(�~��)
        s = "-itemPrice";
        break;
    case RAKUTEN_SORT_DTIME_ASCENDING:      // ���i�X�V������(����)
        s = "+updateTimestamp";
        break;
    case RAKUTEN_SORT_DTIME_DESCENDING:     // ���i�X�V������(�~��)
        s = "-updateTimestamp";
        break;

    // catalog �p
    case RAKUTEN_SORT_RDATE_ASCENDING:      // �J�^���O�o�^��(����)
        s = "+registerDate";
        break;
    case RAKUTEN_SORT_RDATE_DESCENDING:     // �J�^���O�o�^��(�~��)
        s = "-registerDate";
        break;
    case RAKUTEN_SORT_RLDATE_ASCENDING:     // ���������Â���
        s = "+releaseDate";
        break;
    case RAKUTEN_SORT_RLDATE_DESCENDING:    // ���������V������
        s = "-releaseDate";
        break;
    case RAKUTEN_SORT_RVNUM_ASCENDING:      // ���r���[������(����)
        s = "+reviewNum";
        break;
    case RAKUTEN_SORT_RVNUM_DESCENDING:     // ���r���[������(�~��)
        s = "-reviewNum";
        break;

    // item, catalog ���p
    case RAKUTEN_SORT_RANDOM_ORDER:         // �����_����
        s = "random";
        break;
    }

    return ( encodeURL(s) );
}


// �y�V���i����API       -- ItemSearch (version:2007-02-14)
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
    )
{
    char                    *url;
    char                    *request;
    char                    *response;
    size_t                  sz = MAX_CONTENT_SIZE * 64;
    RAKUTEN_API_RESPONSE    *p = NULL;
    const char              *s;

    if ( !keyword || !(*keyword) )
        return ( p );

    if ( !developerId || !(*developerId) )
        developerId = xmlrpc_p->rakutenDeveloperID;
    if ( !affiliateId || !(*affiliateId) )
        affiliateId = xmlrpc_p->rakutenAffiliateID2;

    request = (char *)malloc( sizeof ( RAKUTEN_API_REQUEST ) +
                                                    MAX_DESCRIPTION_LEN );
    if ( !request )
        return ( p );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( p );
    }

    sprintf( request,
             "developerId=%s&",
             developerId );
    if ( affiliateId && *affiliateId )
        sprintf( request + strlen(request),
                 "affiliateId=%s&",
                 affiliateId );

    s = sjis2utf(keyword);
    sprintf( request + strlen(request),
             "operation=ItemSearch&"
             "keyword=%s&"
             "version=2007-02-14&",
             encodeURL( s ? s : keyword ) );

    if ( shopCode && *shopCode )
        sprintf( request + strlen(request),
                 "shopCode=%s&",
                 shopCode );

    if ( catalogCode && *catalogCode )
        sprintf( request + strlen(request),
                 "catalogCode=%s&",
                 catalogCode );
    else
        sprintf( request + strlen(request),
                 "genreId=%d&",
                 genreId >= 0 ? genreId : 0 );

    sprintf( request + strlen(request),
             "hits=%d&",
             (hits >= 1) && (hits <= 30) ? hits : 30 );
    sprintf( request + strlen(request),
             "page=%d&",
             (page >= 1) && (page <= 100) ? page : 1 );

    sprintf( request + strlen(request),
             "sort=%s&",
             getSortOrderString( sort, NULL ) );

    if ( minPrice > 0 ) {
        sprintf( request + strlen(request),
                 "minPrice=%d&",
                 minPrice );
        if ( maxPrice > minPrice )
            sprintf( request + strlen(request),
                     "maxPrice=%d&",
                     maxPrice );
    }
    sprintf( request + strlen(request),
             "availability=1&"
             "field=%d&"
             "carrier=%d&"
             "imageFlag=%d",
             field     ? 1 : 0,
             carrier   ? 1 : 0,
             imageFlag ? 1 : 0 );

    url = (char *)malloc( strlen( request ) + 64 );
    if ( !url ) {
        free( response );
        free( request );
        return ( p );
    }

    sprintf( url, "http://api.rakuten.co.jp/rws/1.3/rest?%s", request );
    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( *response && strstr( response, "<Status>Success</Status>" ) ) {
        int                     num = 0;
        char                    *t, *u;
        RAKUTEN_API_RESPONSE    res;

        res.count     = 0;
        res.page      = 0;
        res.hits      = 0;
        res.carrier   = 0;
        res.pageCount = 0;

        res.first = 1;
        res.last  = 0;

        t = strstr( response, "</ItemSearch>" );
        u = strstr( response, "<Items>" );
        if ( t && u && (t > u) )
            t = u;
        if ( t ) {
            res.count     = getIntegerFromElement( response, t, "count" );
            res.page      = getIntegerFromElement( response, t, "page" );
            res.first     = getIntegerFromElement( response, t, "first" );
            res.last      = getIntegerFromElement( response, t, "last" );
            res.hits      = getIntegerFromElement( response, t, "hits" );
            res.carrier   = getIntegerFromElement( response, t, "carrier" );
            res.pageCount = getIntegerFromElement( response, t, "pageCount" );
        }

        num = res.last - res.first + 1;
        t = u ? u : NULL;
        if ( (num > 0) && t ) {
            p = (RAKUTEN_API_RESPONSE *)malloc(
                                            sizeof ( RAKUTEN_API_RESPONSE ) );
            if ( p ) {
                p->item = (RAKUTEN_ITEM *)malloc(
                                            sizeof ( RAKUTEN_ITEM ) * num );
                if ( p->item ) {
                    t += 7;
                    p->numOfItems = num;
                    getItemsFromResponse( t, p->item, num );

                    p->count     = res.count;
                    p->page      = res.page;
                    p->first     = res.first;
                    p->last      = res.last;
                    p->hits      = res.hits;
                    p->carrier   = res.carrier;
                    p->pageCount = res.pageCount;
                }
                else {
                    free( p );
                    p = NULL;
                }
            }
        }
    }

    free( url );
    free( response );
    free( request );
    encodeURL( NULL );

    return ( p );
}

RAKUTEN_API_RESPONSE    *
itemSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p )
{
    RAKUTEN_API_RESPONSE    *pp = NULL;
    if ( p )
        pp = itemSearchOnRakutenWebAPI( p->developerId, p->affiliateId,
                                        p->keyword, p->shopCode,
                                        p->genreId, p->catalogCode,
                                        p->hits, p->page, p->sort,
                                        p->minPrice, p->maxPrice,
                                        p->field, p->carrier, p->imageFlag );
    return ( pp );
}


// �y�V�W����������API   -- GenreSearch (version:2006-12-26)
void
getGenreInfoFromResponse(
        const char    *src,
        const char    *terminator,
        const char    *elementName,
        RAKUTEN_GENRE *genreInfo,
        int           numOfGenreInfo
    )
{
    const char  *p, *q, *r;
    char        targetS[32];
    char        targetE[32];
    int         len;
    int         cnt = 0;

    sprintf( targetS, "<%s>",  elementName );
    sprintf( targetE, "</%s>", elementName );
    len = strlen( targetS );

    p = src;
    do {
        q = strstr( p, targetS );
        r = strstr( p, targetE );
        if ( !q || !r || (q > r) )
            break;

        q += len;
        genreInfo[cnt].genreId    = getIntegerFromElement( q, r, "genreId" );
        getDecodedStringFromElement( genreInfo[cnt].genreName,
                                     q, r, "genreName" );
        genreInfo[cnt].genreLevel = getIntegerFromElement(q, r, "genreLevel");

        cnt++;
        if ( cnt >= numOfGenreInfo )
            break;
        p = r + (len + 1);
    } while ( (p < terminator) && *p );
}

RAKUTEN_API_RESPONSE2   *
genreSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        long       genreId,
        BOOL       genrePath
    )
{
    RAKUTEN_API_RESPONSE2   *p = NULL;
    char                    url[MAX_URLLENGTH];
    char                    *request;
    char                    *response;
    size_t                  sz = MAX_CONTENT_SIZE * 64;
    const char              *s;

    if ( !developerId || !(*developerId) )
        developerId = xmlrpc_p->rakutenDeveloperID;
    if ( !affiliateId || !(*affiliateId) )
        affiliateId = xmlrpc_p->rakutenAffiliateID2;

    request = (char *)malloc( sizeof ( RAKUTEN_API_REQUEST2 ) +
                                                    MAX_DESCRIPTION_LEN );
    if ( !request )
        return ( p );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( p );
    }

    sprintf( request,
             "developerId=%s&",
             developerId );
    if ( affiliateId && *affiliateId )
        sprintf( request + strlen(request),
                 "affiliateId=%s&",
                 affiliateId );

    sprintf( request + strlen(request),
             "operation=GenreSearch&"
             "genreId=%d&"
             "version=2006-12-26&"
             "genrePath=%d",
             genreId >= 0 ? genreId : 0,
             genrePath == FALSE ? 0 : 1 );

    sprintf( url, "http://api.rakuten.co.jp/rws/1.1/rest?%s", request );
    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( *response && strstr( response, "<Status>Success</Status>" ) ) {
        // current �����[�g(genreId �� 0)�̂Ƃ��́Achild �̂ݑ��� (current �����݂��Ȃ�)
        // current �� genreLevel �� 1 �ȏ�̂Ƃ� current �� child ������
        // current �� genreLevel �� 2 �ȏ�̂Ƃ� parent �� current �� child ������
        int     numOfParent  = 0;
        int     numOfCurrent = 0;
        int     numOfChild   = 0;
        char    *t, *u;

        s = response;
        t = strstr( s, "</GenreSearch>" );
        u = strstr( s, "<parent>" );
        if ( t && u && (t > u) ) {
            // parent �����݂���ꍇ
            do {
                numOfParent++;
                s = u + 8;
                u = strstr( s, "<parent>" );
                if ( u && (u > t) )
                    break;
            } while ( u && *u );
        }

        u = strstr( s, "<current>" );
        if ( t && u && (t > u) ) {
            // current �����݂���ꍇ
            numOfCurrent++;
        }

        u = strstr( s, "<child>" );
        if ( t && u && (t > u) ) {
            // child �����݂���ꍇ
            do {
                numOfChild++;
                s = u + 8;
                u = strstr( s, "<child>" );
                if ( u && (u > t) )
                    break;
            } while ( u && *u );
        }

        if ( numOfParent + numOfCurrent + numOfChild > 0 ) {
            p = (RAKUTEN_API_RESPONSE2 *)malloc(
                                    sizeof ( RAKUTEN_API_RESPONSE2 ) );
            if ( p ) {
                p->parent = NULL;
                p->child   = NULL;
                if ( numOfParent > 0 ) {
                    p->numOfDepth = numOfParent;
                    p->parent = (RAKUTEN_GENRE *)malloc(
                                    sizeof ( RAKUTEN_GENRE ) * numOfParent );
                    if ( !(p->parent) ) {
                        free( p );
                        free( response );
                        free( request );
                        p = NULL;
                        return ( p );
                    }
                }
                if ( numOfChild > 0 ) {
                    p->numOfChilds = numOfChild;
                    p->child = (RAKUTEN_GENRE *)malloc(
                                    sizeof ( RAKUTEN_GENRE ) * numOfChild );
                    if ( !(p->child) ) {
                        if ( p->parent )
                            free( p->parent );
                        free( p );
                        free( response );
                        free( request );
                        p = NULL;
                        return ( p );
                    }
                }

                // parent
                if ( numOfParent > 0 ) {
                    s = response;
                    u = strstr( s, "<parent>" );
                    getGenreInfoFromResponse( u, t, "parent",
                                              p->parent, numOfParent );
                }

                // current
                if ( numOfCurrent > 0 ) {
                    s = response;
                    u = strstr( s, "<current>" );
                    getGenreInfoFromResponse( u, t, "current",
                                              &(p->current), 1 );
                }
                else {
                    p->current.genreId      = 0;
                    p->current.genreLevel   = 0;
                    p->current.genreName[0] = NUL; 
                }

                // child
                if ( numOfChild > 0 ) {
                    s = response;
                    u = strstr( s, "<child>" );
                    getGenreInfoFromResponse( u, t, "child",
                                              p->child, numOfChild );
                }
            }
        }
    }

    free( response );
    free( request );
    encodeURL( NULL );

    return ( p );
}

RAKUTEN_API_RESPONSE2   *
genreSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST2 *p )
{
    RAKUTEN_API_RESPONSE2   *pp = NULL;
    if ( p )
        pp = genreSearchOnRakutenWebAPI( p->developerId, p->affiliateId,
                                         p->genreId, p->genrePath );
    return ( pp );
}


// �y�V���i�R�[�h����API -- ItemCodeSearch (version:2007-02-14)
RAKUTEN_API_RESPONSE3   *
itemCodeSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        const char *itemCode,
        int        carrier
    )
{
    RAKUTEN_API_RESPONSE3   *p = NULL;
    char                    url[MAX_URLLENGTH];
    char                    *request;
    char                    *response;
    size_t                  sz = MAX_CONTENT_SIZE * 64;

    if ( !developerId || !(*developerId) )
        developerId = xmlrpc_p->rakutenDeveloperID;
    if ( !affiliateId || !(*affiliateId) )
        affiliateId = xmlrpc_p->rakutenAffiliateID2;

    request = (char *)malloc( sizeof ( RAKUTEN_API_REQUEST3 ) +
                                                    MAX_DESCRIPTION_LEN );
    if ( !request )
        return ( p );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( p );
    }

    sprintf( request,
             "developerId=%s&",
             developerId );
    if ( affiliateId && *affiliateId )
        sprintf( request + strlen(request),
                 "affiliateId=%s&",
                 affiliateId );

    sprintf( request + strlen(request),
             "operation=ItemCodeSearch&"
             "itemCode=%s&"
             "version=2007-02-14&"
             "carrier=%d",
             encodeURL(itemCode),
             carrier == 1 ? 1 : 0 );

    sprintf( url, "http://api.rakuten.co.jp/rws/1.3/rest?%s", request );
    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( *response && strstr( response, "<Status>Success</Status>" ) ) {
        char    *t, *u;

        t = strstr( response, "</ItemCodeSearch>" );
        u = strstr( response, "<Item>" );
        if ( t && u && (t > u) ) {
            p = (RAKUTEN_API_RESPONSE3 *)malloc(
                                            sizeof (RAKUTEN_API_RESPONSE3) );
            if ( p ) {
                p->item = (RAKUTEN_ITEM *)malloc( sizeof ( RAKUTEN_ITEM ) );
                if ( p->item ) {
                    p->carrier = getIntegerFromElement( u, t, "carrier" );
                    getItemsFromResponse( u, p->item, 1 );
                }
                else {
                    free( p );
                    p = NULL;
                }
            }
        }
    }

    free( response );
    free( request );
    encodeURL( NULL );

    return ( p );
}

RAKUTEN_API_RESPONSE3   *
itemCodeSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST3 *p )
{
    RAKUTEN_API_RESPONSE3   *pp = NULL;
    if ( p )
        pp = itemCodeSearchOnRakutenWebAPI( p->developerId, p->affiliateId,
                                            p->itemCode, p->carrier );
    return ( pp );
}




RAKUTEN_API_RESPONSE    *
itemSearchOnRakutenBooks(
        const char *developerId,
        const char *affiliateId,
        const char *keyword,
        const char *operation,
        long       defaultGenreId,
        long       genreId,
        int        hits,
        int        page,
        int        sort,
        long       minPrice,
        long       maxPrice,
        int        field,
        int        carrier,
        int        imageFlag
    )
{
    char                    *url;
    char                    *request;
    char                    *response;
    size_t                  sz = MAX_CONTENT_SIZE * 64;
    RAKUTEN_API_RESPONSE    *p = NULL;
    const char              *s;

    if ( !keyword || !(*keyword) )
        return ( p );

    if ( !developerId || !(*developerId) )
        developerId = xmlrpc_p->rakutenDeveloperID;
    if ( !affiliateId || !(*affiliateId) )
        affiliateId = xmlrpc_p->rakutenAffiliateID2;

    request = (char *)malloc( sizeof ( RAKUTEN_API_REQUEST ) +
                                                    MAX_DESCRIPTION_LEN );
    if ( !request )
        return ( p );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( p );
    }

    sprintf( request,
             "developerId=%s&",
             developerId );
    if ( affiliateId && *affiliateId )
        sprintf( request + strlen(request),
                 "affiliateId=%s&",
                 affiliateId );

    s = sjis2utf(keyword);
    sprintf( request + strlen(request),
             "operation=%s&"
             "keyword=%s&"
             "version=2007-02-14&",
             operation,
             encodeURL( s ? s : keyword ) );

    sprintf( request + strlen(request),
             "genreId=%d&",
             genreId > 0 ? genreId : defaultGenreId );

    sprintf( request + strlen(request),
             "hits=%d&",
             (hits >= 1) && (hits <= 30) ? hits : 30 );
    sprintf( request + strlen(request),
             "page=%d&",
             (page >= 1) && (page <= 100) ? page : 1 );

    sprintf( request + strlen(request),
             "sort=%s&",
             getSortOrderString( sort, NULL ) );

    if ( minPrice > 0 ) {
        sprintf( request + strlen(request),
                 "minPrice=%d&",
                 minPrice );
        if ( maxPrice > minPrice )
            sprintf( request + strlen(request),
                     "maxPrice=%d&",
                     maxPrice );
    }
    sprintf( request + strlen(request),
             "availability=1&"
             "field=%d&"
             "carrier=%d&"
             "imageFlag=%d",
             field     ? 1 : 0,
             carrier   ? 1 : 0,
             imageFlag ? 1 : 0 );

    url = (char *)malloc( strlen( request ) + 64 );
    if ( !url ) {
        free( response );
        free( request );
        return ( p );
    }

    sprintf( url, "http://api.rakuten.co.jp/rws/1.3/rest?%s", request );
    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( *response && strstr( response, "<Status>Success</Status>" ) ) {
        int                     num = 0;
        char                    *t, *u;
        RAKUTEN_API_RESPONSE    res;

        res.count     = 0;
        res.page      = 0;
        res.hits      = 0;
        res.carrier   = 0;
        res.pageCount = 0;

        res.first = 1;
        res.last  = 0;

        t = strstr( response, "</BookSearch>" );
        if ( !t ) {
            if ( !strcmp( operation, "CDSearch" ) )
                t = strstr( response, "</CDSearch>" );
            else if ( !strcmp( operation, "DVDSearch" ) )
                t = strstr( response, "</DVDSearch>" );
        }
        u = strstr( response, "<Items>" );
        if ( t && u && (t > u) )
            t = u;
        if ( t ) {
            res.count     = getIntegerFromElement( response, t, "count" );
            res.page      = getIntegerFromElement( response, t, "page" );
            res.first     = getIntegerFromElement( response, t, "first" );
            res.last      = getIntegerFromElement( response, t, "last" );
            res.hits      = getIntegerFromElement( response, t, "hits" );
            res.carrier   = getIntegerFromElement( response, t, "carrier" );
            res.pageCount = getIntegerFromElement( response, t, "pageCount" );
        }

        num = res.last - res.first + 1;
        t = u ? u : NULL;
        if ( (num > 0) && t ) {
            p = (RAKUTEN_API_RESPONSE *)malloc(
                                            sizeof ( RAKUTEN_API_RESPONSE ) );
            if ( p ) {
                p->item = (RAKUTEN_ITEM *)malloc(
                                            sizeof ( RAKUTEN_ITEM ) * num );
                if ( p->item ) {
                    t += 7;
                    p->numOfItems = num;
                    getItemsFromResponse( t, p->item, num );

                    p->count     = res.count;
                    p->page      = res.page;
                    p->first     = res.first;
                    p->last      = res.last;
                    p->hits      = res.hits;
                    p->carrier   = res.carrier;
                    p->pageCount = res.pageCount;
                }
                else {
                    free( p );
                    p = NULL;
                }
            }
        }
    }

    free( url );
    free( response );
    free( request );
    encodeURL( NULL );

    return ( p );
}


// �y�V���Ќ���API       -- BookSearch (version:2007-02-14)

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
    )
{
    return ( itemSearchOnRakutenBooks( developerId, affiliateId,
                                       keyword, "BookSearch",
                                       200162, genreId,
                                       hits, page, sort, minPrice, maxPrice,
                                       field, carrier, imageFlag ) );
                // genreID=200162(�{�E�G���E�R�~�b�N)
                //  200162 ���g�A�������� 200162 �̎q���W�������̂ݎw��\
}

RAKUTEN_API_RESPONSE    *
bookSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p )
{
    RAKUTEN_API_RESPONSE    *pp = NULL;
    if ( p )
        pp = bookSearchOnRakutenWebAPI( p->developerId, p->affiliateId,
                                        p->keyword,
                                        p->genreId,
                                        p->hits, p->page, p->sort,
                                        p->minPrice, p->maxPrice,
                                        p->field, p->carrier, p->imageFlag );
    return ( pp );
}


// �y�VCD����API         -- CDSearch (version:2007-02-14)
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
    )
{
    return ( itemSearchOnRakutenBooks( developerId, affiliateId,
                                       keyword, "CDSearch",
                                       101311, genreId,
                                       hits, page, sort, minPrice, maxPrice,
                                       field, carrier, imageFlag ) );
                // genreID=101311(CD)
                //  101311 ���g�A�������� 101311 �̎q���W�������̂ݎw��\
}

RAKUTEN_API_RESPONSE    *
cdSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p )
{
    RAKUTEN_API_RESPONSE    *pp = NULL;
    if ( p )
        pp = cdSearchOnRakutenWebAPI( p->developerId, p->affiliateId,
                                      p->keyword,
                                      p->genreId,
                                      p->hits, p->page, p->sort,
                                      p->minPrice, p->maxPrice,
                                      p->field, p->carrier, p->imageFlag );
    return ( pp );
}


// �y�VDVD����API        -- DVDSearch (version:2007-02-14)
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
    )
{
    return ( itemSearchOnRakutenBooks( developerId, affiliateId,
                                       keyword, "DVDSearch",
                                       101354, genreId,
                                       hits, page, sort, minPrice, maxPrice,
                                       field, carrier, imageFlag ) );
                // genreID=101354(DVD)
                //  101354 ���g�A�������� 101354 �̎q���W�������̂ݎw��\
}

RAKUTEN_API_RESPONSE    *
dvdSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p )
{
    RAKUTEN_API_RESPONSE    *pp = NULL;
    if ( p )
        pp = dvdSearchOnRakutenWebAPI( p->developerId, p->affiliateId,
                                       p->keyword,
                                       p->genreId,
                                       p->hits, p->page, p->sort,
                                       p->minPrice, p->maxPrice,
                                       p->field, p->carrier, p->imageFlag );
    return ( pp );
}


// �y�V�J�^���O����API   -- CatalogSearch (version:2007-02-14)
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
    )
{
    RAKUTEN_API_RESPONSE1   *p = NULL;
    char                    *url;
    char                    *request;
    char                    *response;
    size_t                  sz = MAX_CONTENT_SIZE * 64;
    const char              *s;

    if ( !keyword || !(*keyword) )
        return ( p );

    if ( !developerId || !(*developerId) )
        developerId = xmlrpc_p->rakutenDeveloperID;
    if ( !affiliateId || !(*affiliateId) )
        affiliateId = xmlrpc_p->rakutenAffiliateID2;

    request = (char *)malloc( sizeof ( RAKUTEN_API_REQUEST ) +
                                                    MAX_DESCRIPTION_LEN );
    if ( !request )
        return ( p );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( p );
    }

    sprintf( request,
             "developerId=%s&",
             developerId );
    if ( affiliateId && *affiliateId )
        sprintf( request + strlen(request),
                 "affiliateId=%s&",
                 affiliateId );

    s = sjis2utf(keyword);
    sprintf( request + strlen(request),
             "operation=CatalogSearch&"
             "keyword=%s&"
             "version=2007-02-14&",
             encodeURL( s ? s : keyword ) );

    sprintf( request + strlen(request),
             "genreId=%d&",
             genreId >= 0 ? genreId : 0 );

    sprintf( request + strlen(request),
             "hits=%d&",
             (hits >= 1) && (hits <= 30) ? hits : 30 );
    sprintf( request + strlen(request),
             "page=%d&",
             (page >= 1) && (page <= 100) ? page : 1 );

    sprintf( request + strlen(request),
             "sort=%s&",
             getSortOrderString( sort, "-registerDate" ) );

    if ( minPrice > 0 ) {
        sprintf( request + strlen(request),
                 "minPrice=%d&",
                 minPrice );
        if ( maxPrice > minPrice )
            sprintf( request + strlen(request),
                     "maxPrice=%d&",
                     maxPrice );
    }
    sprintf( request + strlen(request),
             "availability=1&"
             "field=%d&"
             "imageFlag=%d&"
             "releaseRange=%d",
             field     ? 1 : 0,
             imageFlag ? 1 : 0,
             (releaseRange < 0) || (releaseRange > 12) ? 0 : releaseRange );

    url = (char *)malloc( strlen( request ) + 64 );
    if ( !url ) {
        free( response );
        free( request );
        return ( p );
    }

    sprintf( url, "http://api.rakuten.co.jp/rws/1.3/rest?%s", request );
    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( *response && strstr( response, "<Status>Success</Status>" ) ) {
        int                     num = 0;
        char                    *t, *u;
        RAKUTEN_API_RESPONSE1   res;

        res.count     = 0;
        res.page      = 0;
        res.hits      = 0;
        res.carrier   = 0;
        res.pageCount = 0;

        res.first = 1;
        res.last  = 0;

        t = strstr( response, "</CatalogSearch>" );
        u = strstr( response, "<Catalogs>" );
        if ( t && u && (t > u) )
            t = u;
        if ( t ) {
            res.count     = getIntegerFromElement( response, t, "count" );
            res.page      = getIntegerFromElement( response, t, "page" );
            res.first     = getIntegerFromElement( response, t, "first" );
            res.last      = getIntegerFromElement( response, t, "last" );
            res.hits      = getIntegerFromElement( response, t, "hits" );
            res.carrier   = getIntegerFromElement( response, t, "carrier" );
            res.pageCount = getIntegerFromElement( response, t, "pageCount" );
        }

        num = res.last - res.first + 1;
        t = u ? u : NULL;
        if ( (num > 0) && t ) {
            p = (RAKUTEN_API_RESPONSE1 *)malloc(
                                            sizeof ( RAKUTEN_API_RESPONSE1 ) );
            if ( p ) {
                p->catalog = (RAKUTEN_CATALOG *)malloc(
                                            sizeof ( RAKUTEN_CATALOG ) * num );
                if ( p->catalog ) {
                    t += 10;
                    p->numOfCatalogs = num;
                    getCatalogsFromResponse( t, p->catalog, num );

                    p->count     = res.count;
                    p->page      = res.page;
                    p->first     = res.first;
                    p->last      = res.last;
                    p->hits      = res.hits;
                    p->carrier   = res.carrier;
                    p->pageCount = res.pageCount;
                }
                else {
                    free( p );
                    p = NULL;
                }
            }
        }
    }

    free( url );
    free( response );
    free( request );
    encodeURL( NULL );

    return ( p );
}

RAKUTEN_API_RESPONSE1   *
catalogSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p )
{
    RAKUTEN_API_RESPONSE1   *pp = NULL;
    if ( p )
        pp = catalogSearchOnRakutenWebAPI( p->developerId, p->affiliateId,
                                           p->keyword, p->genreId,
                                           p->hits, p->page, p->sort,
                                           p->minPrice, p->maxPrice,
                                           p->field, p->imageFlag,
                                           p->releaseRange );
    return ( pp );
}


void
freeRakutenApiResponce( RAKUTEN_API_RESPONSE *p )
{
    if ( p ) {
        if ( p->item )
            free( p->item );
        free( p );
    }
}

void
freeRakutenApiResponce1( RAKUTEN_API_RESPONSE1 *p )
{
    if ( p ) {
        if ( p->catalog )
            free( p->catalog );
        free( p );
    }
}

void
freeRakutenApiResponce2( RAKUTEN_API_RESPONSE2 *p )
{
    if ( p ) {
        if ( p->child )
            free( p->child );
        if ( p->parent )
            free( p->parent );
        free( p );
    }
}

void
freeRakutenApiResponce3( RAKUTEN_API_RESPONSE3 *p )
{
    if ( p ) {
        if ( p->item )
            free( p->item );
        free( p );
    }
}

