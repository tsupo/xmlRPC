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
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 9     07/02/21 19:45 Tsujimura543
 * catalogSearchOnRakutenWebAPI �p�́u�\�[�g���v�̒�`��ǉ�
 * 
 * 8     07/02/21 19:05 Tsujimura543
 * RAKUTEN_CATALOG �\���̂� catalogName �� catalogCaption ������
 * 
 * 7     07/02/21 19:03 Tsujimura543
 * RAKUTEN_ITEM �\���̂� itemName �� itemCaption �̊i�[�̈���e�X����
 * 
 * 6     07/02/20 22:32 Tsujimura543
 * catalogSearchOnRakutenWebAPI() �̈�����1��(carrier)�폜
 * 
 * 5     07/02/20 21:20 Tsujimura543
 * �y�V�E�F�u�T�[�r�X�̂����AItemSearch �� GenreSearch ������
 * (����͖��m�F)
 * 
 * 4     07/02/19 20:56 Tsujimura543
 * 2006�N12���J�n�́u�y�V�E�F�u�T�[�r�X�vAPI�����\���̂̒�`(�b���)��ǉ�
 * 
 * 3     05/09/02 21:11 Tsujimura543
 * �R�����g��ǉ�
 * 
 * 2     05/09/02 14:17 Tsujimura543
 * doxygen �����ɃR�����g����������
 * 
 * 1     05/05/18 21:44 Tsujimura543
 * �������ʊi�[�p�\���̂̒�`��p��
 */

#ifndef __RAKUTEN_H__
#define __RAKUTEN_H__
#include "amazon.h"

/*
 * �y�V�u�b�N�X salesranking
 *
 *  http://xml.affiliate.rakuten.co.jp/?type=���&service=books&hash=�A�t�B���G�C�gID&genre=�W�������R�[�h&num=����
 *
 *   ex)
 *    http://xml.affiliate.rakuten.co.jp/?type=html&service=books&hash=0008a695.5601c7dd&genre=0&num=10
 *    http://xml.affiliate.rakuten.co.jp/?type=xml&service=books&hash=0008a695.5601c7dd&genre=0&num=10
 *
 *      ���
 *          html: HTML �ŉ���
 *          xml: XML �ŉ���
 *      �W�������R�[�h
 *          0: ����
 *          1: �R�~�b�N�E�W���u�i�C��
 *          2: ��w�E�A�E�E���i����
 *          3: �G�{�E������
 *          4: ���|�E�m���t�B�N�V����
 *          5: �o�b�E�V�X�e���J��
 *          6: �r�W�l�X�E�o�ρE�o�c
 *          7: ���s�E�I�s�E�A�E�g�h�A
 *          8: �w�₪�킩��{
 *          9: �z�r�[�E�X�|�[�c
 *         10: ���C�t�X�^�C��
 *         11: �G���^�[�e�C�����g
 *         12: ��发�E�w�p��
 *         13: �ʐ^�W�E�^�����g
 *      ����
 *          1 �` 10 (10 ���傫�Ȓl���w�肷��� 10 ���w�肵�����̂Ƃ݂Ȃ�)
 *
 *      ����:
 *          �����R�[�h�� html �̏ꍇ�AEUC-JP; xml �̏ꍇ�AUTF-8
 *
 *      ������ (xml)
 *          <?xml version="1.0" encoding="UTF-8" standalone="yes" ?> 
 *          <RWS version="1.0.0" type="SalesRanking" service="�y�V�u�b�N�X" date="2004/05/10">
 *          <item>
 *              <Isbn>4915512517</Isbn> 
 *              <SalesRank>1</SalesRank> 
 *              <Url>http://pt.afl.rakuten.co.jp/c/0008a695.5601c7dd/?url=http%3A%2F%2Fbooks.rakuten.co.jp%2FRBOOKS%2F0001654002%2F</Url> 
 *              <ProductName>�y�\��z �n���[�E�|�b�^�[�ƕs�����̋R�m�c</ProductName> 
 *              <Manufacturer>�ÎR��</Manufacturer> 
 *              <ImageUrlSmall>http://image.books.rakuten.co.jp/books/com/images/goods/91551251.jpg</ImageUrlSmall> 
 *              <ListPrice>4200</ListPrice> 
 *              <Authors>
 *                  <Author id="1" name="�i�D�j�D���[�����O" /> 
 *              </Authors>
 *          </item>
 *          </RWS>
 */


/**
 *  \defgroup rakutenSearch �u�y�V�u�b�N�X�v�������ʊi�[�p�\����
 */
/** \defgroup rakutenTypeHtml �������ʊi�[�p�\����(RAKUTEN_TYPE_HTML �p)
 *  \ingroup rakutenSearch
 */
/*@{*/
//! �������ʊi�[�p�\����(�y�ʔ�)
typedef struct rakutenSearchResultLite  {
    char    url[MAX_URLLENGTH];                    //!< ���i�y�[�WURL
    char    productName[MAX_PRODUCTSNAME_LENGTH];  //!< ���i���A����
}   RAKUTEN_LITE, *RAKUTEN_LITE_t;
/*@}*/

/** \defgroup rakutenTypeXml �������ʊi�[�p�\����(RAKUTEN_TYPE_XML �p)
 *  \ingroup rakutenSearch
 */
/*@{*/
//! �������ʊi�[�p�\����(�d�ʔ�)
typedef struct rakutenSearchResultHeavy {
    char    url[MAX_URLLENGTH];                    //!< ���i�y�[�WURL
    char    isbn[MAX_NAMELEN];                     //!< ISBN
    char    productName[MAX_PRODUCTSNAME_LENGTH];  //!< ���i���A����
    char    authors[MAX_AUTHORINFO_LENGTH];        //!< ��ҁA�Ҏ�
    char    manufacturer[MAX_MANUFACTURER_LENGTH]; //!< ���s���A������
    char    imageURLsmall[MAX_URLLENGTH];          //!< �����ȉ摜��URL
    char    listPrice[MAX_PRICE_LENGTH];           //!< �艿
    unsigned long   salesRank;                     //!< ����グ����
}   RAKUTEN_HEAVY, *RAKUTEN_HEAVY_t;
/*@}*/


/** \defgroup rakutenWebAPI �y�V�E�F�u�T�[�r�X �֘A�e���`
 */
/*
 *  �y�V�E�F�u�T�[�r�X
 */

/** \defgroup areaLength ������i�[�̈�ő咷
 *  \ingroup rakutenWebAPI
 */
/*@{*/
#define RAKUTEN_VERSION_LEN 12      //!< �u�o�[�W�����v�ő咷
#define RAKUTEN_DTIME_LEN   20      //!< �u�����v�ő咷
#define RAKUTEN_OPE_LEN     24      //!< �u����v�ő咷
#define RAKUTEN_NAME_LEN    128     //!< �u���[�J�[���v�A�u�V���[�Y���v�ő咷
#define RAKUTEN_STATMSG_LEN 1024    //!< �u���s���ʃX�e�[�^�X�ڍׁv�ő咷
/*@}*/

/** \defgroup sortOrder �\�[�g��
 *  \ingroup rakutenWebAPI
 */
/*@{*/
// item �p
#define RAKUTEN_SORT_AFFRATE_ASCENDING  1   //!< �A�t�B���G�C�g������(����) +affiliateRate
#define RAKUTEN_SORT_AFFRATE_DESCENDING 2   //!< �A�t�B���G�C�g������(�~��) -affiliateRate
#define RAKUTEN_SORT_RVCNT_ASCENDING    3   //!< ���r���[������(����) +reviewCount
#define RAKUTEN_SORT_RVCNT_DESCENDING   4   //!< ���r���[������(�~��) -reviewCount
#define RAKUTEN_SORT_PRICE_ASCENDING    5   //!< ���i��(����) +itemPrice
#define RAKUTEN_SORT_PRICE_DESCENDING   6   //!< ���i��(�~��) -itemPrice
#define RAKUTEN_SORT_DTIME_ASCENDING    7   //!< ���i�X�V������(����) +updateTimestamp
#define RAKUTEN_SORT_DTIME_DESCENDING   8   //!< ���i�X�V������(�~��) -updateTimestamp

// catalog �p
#define RAKUTEN_SORT_RDATE_ASCENDING    17  //!< �J�^���O�o�^��(����) +registerDate
#define RAKUTEN_SORT_RDATE_DESCENDING   18  //!< �J�^���O�o�^��(�~��) -registerDate
#define RAKUTEN_SORT_RLDATE_ASCENDING   19  //!< ���������Â���   +releaseDate
#define RAKUTEN_SORT_RLDATE_DESCENDING  20  //!< ���������V������ -releaseDate
#define RAKUTEN_SORT_RVNUM_ASCENDING    21  //!< ���r���[������(����) +reviewNum
#define RAKUTEN_SORT_RVNUM_DESCENDING   22  //!< ���r���[������(�~��) -reviewNum

// item, catalog ���p
#define RAKUTEN_SORT_RANDOM_ORDER       33   //!< �����_���� random
/*@}*/

/** \defgroup rakutenItem ���i�ʏ��i�[�p�\����
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! ���i�ʏ��
typedef struct rakutenItem  {
    // ���i���
    char    itemName[MAX_DESCRIPTION_LEN];      //!< ���i��
    char    itemCode[MAX_KEYLENGTH];            //!< ���i�R�[�h (�� book:11918897)
    int     itemPrice;                          //!< ���i���i
    char    itemCaption[MAX_CONTENT_SIZE];      //!< ���i������
    char    itemUrl[MAX_URLLENGTH];             //!< ���iURL
    char    affiliateUrl[MAX_URLLENGTH];        //!< �A�t�B���G�C�gURL 
    BOOL    imageFlag;                          //!< ���i�摜�L���t���O
    char    smallImageUrl[MAX_URLLENGTH];       //!< ���i�摜URL 64x64 
    char    mediumImageUrl[MAX_URLLENGTH];      //!< ���i�摜URL 128x128 
    BOOL    availability;                       //!< �̔��\�t���O
    BOOL    taxFlag;                            //!< ����Ńt���O
    BOOL    postageFlag;                        //!< �����t���O
    BOOL    creditCardFlag;                     //!< �N���W�b�g�J�[�h���p�\�t���O
    BOOL    shopOfTheYearFlag;                  //!< �V���b�v�I�u�U�C���[�t���O
    double  affiliateRate;                      //!< �A�t�B���G�C�g���p����
    char    startTime[RAKUTEN_DTIME_LEN];       //!< �̔��J�n���� YYYY-MM-DD HH:MM�`��
    char    endTime[RAKUTEN_DTIME_LEN];         //!< �̔��I������ YYYY-MM-DD HH:MM�`��
    int     reviewCount;                        //!< ���r���[����
    double  reviewAverage;                      //!< ���r���[����
    // �X�܏��
    char    shopName[MAX_LOGICALLINELEN];       //!< �X�ܖ�
    char    shopCode[MAX_KEYLENGTH];            //!< �X�܃R�[�h
    char    shopUrl[MAX_URLLENGTH];             //!< �X��URL
    // �W���������
    int     genreId;                            //!< �W������ID
}   RAKUTEN_ITEM;
/*@}*/

/** \defgroup rakutenCatalog �J�^���O���i�[�p�\����
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �J�^���O���
typedef struct rakutenCatalog   {
    // ���i���
    char    catalogName[MAX_DESCRIPTION_LEN];   //!< �J�^���O����
    char    catalogCode[MAX_KEYLENGTH];         //!< �J�^���O�R�[�h
    char    modelNo[MAX_KEYLENGTH];             //!< �^��
    char    makerName[RAKUTEN_NAME_LEN];        //!< ���[�J�[��
    char    seriesName[RAKUTEN_NAME_LEN];       //!< �V���[�Y��
    char    onSaleDate[MAX_LOGICALLINELEN];     //!< ������
    int     catalogPrice;                       //!< �W�����i (�I�[�v�����i�̂Ƃ� -1)
    char    catalogCaption[MAX_CONTENT_SIZE];   //!< �J�^���O������
    char    catalogUrl[MAX_URLLENGTH];          //!< �J�^���OURL
    BOOL    imageFlag;                          //!< �J�^���O�摜�L���t���O
    char    smallImageUrl[MAX_URLLENGTH];       //!< �J�^���O�摜URL 64x64
    char    mediumImageUrl[MAX_URLLENGTH];      //!< �J�^���O�摜URL 128x128
    int     reviewCount;                        //!< ���r���[����
    // �W���������
    int     genreId;                            //!< �W������ID
}   RAKUTEN_CATALOG;
/*@}*/

/** \defgroup rautenGenre �W���������i�[�p�\����
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �J�^���O���
typedef struct rautenGenre  {
    int     genreId;                        //!< �W������ID
    char    genreName[MAX_LOGICALLINELEN];  //!< �W��������
    int     genreLevel;                     //!< �W�������K�w
}   RAKUTEN_GENRE;
/*@}*/


/** \defgroup rakutenSearchRequest �����v���i�[�p�\���� (ItemSearch, BookSearch, CDSearch, DVDSearch, CatalogSearch�p)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �����v���i�[�p�\���́E����1 (2007-02-14��)
typedef struct rakutenSearchRequest {
    // ���ʃp�����[�^
    char    developerId[MAX_NAMELEN + 1];   //!< �f�x���b�p�[ID
    char    affiliateId[MAX_KEYLENGTH];     //!< �A�t�B���G�C�gID
    char    operation[RAKUTEN_OPE_LEN];     //!< ����
    // �T�[�r�X�ŗL�p�����[�^   -- ItemSearch, BookSearch, CDSearch, DVDSearch, CatalogSearch
    char    keyword[MAX_DESCRIPTION_LEN];   //!< �����L�[���[�h
    char    version[RAKUTEN_VERSION_LEN];   //!< �o�[�W����
    char    shopCode[MAX_NAMELEN];          //!< �V���b�v�R�[�h (ItemSearch�̂�)
    long    genreId;                        //!< �W������ID
    char    catalogCode[MAX_KEYLENGTH];     //!< �J�^���O�R�[�h (ItemSearch�̂�)
    int     hits;                           //!< 1�y�[�W������̎擾����
    int     page;                           //!< �擾�y�[�W (1�ȏ�100�ȉ�)
    int     sort;                           //!< �\�[�g
    long    minPrice;                       //!< �ŏ����i
    long    maxPrice;                       //!< �ő剿�i
    int     availability;                   //!< �̔��\�t���O
    int     field;                          //!< �����t�B�[���h
    int     carrier;                        //!< �L�����A
    int     imageFlag;                      //!< ���i�摜�L���t���O
    int     releaseRange;                   //!< �������� (CatalogSearch�̂�)
}   RAKUTEN_API_REQUEST;
/*@}*/  // BookSearch, CDSearch, DVDSearch �́u�y�V�u�b�N�X�v�݂̂������ΏۂƂȂ�

/** \defgroup rakutenSearchResponse �������ʊi�[�p�\���� (ItemSearch, BookSearch, CDSearch, DVDSearch�p)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �������ʊi�[�p�\���́E����1 (2007-02-14��)
typedef struct rakutenSearchResponse {
    char            status[MAX_NAMELEN];            //!< ���s���ʃX�e�[�^�X
    char            statusMsg[RAKUTEN_STATMSG_LEN]; //!< ���s���ʃX�e�[�^�X�ڍ�
    int             count;                          //!< �������ʂ̑����i�� 
    int             page;                           //!< ���݂̃y�[�W�ԍ� 
    int             first;                          //!< �������ʂ̉����ڂ��炩 
    int             last;                           //!< �������ʂ̉����ڂ܂ł� 
    int             hits;                           //!< ��x�ɕԋp���鏤�i�� 
    int             carrier;                        //!< �L�����A (PC=0 or mobile=1)
    int             pageCount;                      //!< ���y�[�W�� (�ő�100)
    int             numOfItems;                     //!< �擾�������i���̐�
    RAKUTEN_ITEM    *item;                          //!< ���i��� + �X�܏�� + �W���������
}   RAKUTEN_API_RESPONSE;
/*@}*/

/** \defgroup rakutenSearchResponse1 �������ʊi�[�p�\���� (CatalogSearch�p)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �������ʊi�[�p�\���́E����1-���� (2007-02-14��)
typedef struct rakutenSearchResponse1 {
    char            status[MAX_NAMELEN];            //!< ���s���ʃX�e�[�^�X
    char            statusMsg[RAKUTEN_STATMSG_LEN]; //!< ���s���ʃX�e�[�^�X�ڍ�
    int             count;                          //!< �������ʂ̑����i�� 
    int             page;                           //!< ���݂̃y�[�W�ԍ� 
    int             first;                          //!< �������ʂ̉����ڂ��炩 
    int             last;                           //!< �������ʂ̉����ڂ܂ł� 
    int             hits;                           //!< ��x�ɕԋp���鏤�i�� 
    int             carrier;                        //!< �L�����A (PC=0 or mobile=1)
    int             pageCount;                      //!< ���y�[�W�� (�ő�100)
    int             numOfCatalogs;                  //!< �擾�����J�^���O���̐�
    RAKUTEN_CATALOG *catalog;                       //!< ���i��� + �W���������
}   RAKUTEN_API_RESPONSE1;
/*@}*/

/** \defgroup rakutenSearchRequest2 �����v���i�[�p�\���� (GenreSearch�p)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �����v���i�[�p�\���́E����2 (2006-12-26��)
typedef struct rakutenSearchRequest2 {
    // ���ʃp�����[�^
    char    developerId[MAX_NAMELEN + 1];   //!< �f�x���b�p�[ID
    char    affiliateId[MAX_KEYLENGTH];     //!< �A�t�B���G�C�gID
    char    operation[RAKUTEN_OPE_LEN];     //!< ����
    // �T�[�r�X�ŗL�p�����[�^   -- GenreSearch
    long    genreId;                        //!< �W������ID
    char    version[RAKUTEN_VERSION_LEN];   //!< �o�[�W����
    BOOL    genrePath;                      //!< �W�������p�X
}   RAKUTEN_API_REQUEST2;
/*@}*/

/** \defgroup rakutenSearchResponse2 �������ʊi�[�p�\���� (GenreSearch�p)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �������ʊi�[�p�\���́E����2 (2006-12-26��)
typedef struct rakutenSearchResponse2 {
    char            status[MAX_NAMELEN];            //!< ���s���ʃX�e�[�^�X
    char            statusMsg[RAKUTEN_STATMSG_LEN]; //!< ���s���ʃX�e�[�^�X�ڍ�
    // �e�W������
    int             numOfDepth;                     //!< ���[�g����e�܂ł̐[��
    RAKUTEN_GENRE   *parent;                        //!< �e�W������ / �c��W������
    // ���W������
    RAKUTEN_GENRE   current;                        //!< �����v���Ŏw�肵�� genreId �ɑΉ�����W������
    // �q�W������
    int             numOfChilds;                    //!< �q�W��������
    RAKUTEN_GENRE   *child;                         //!< �q�W������(�������݂���ꍇ����)
}   RAKUTEN_API_RESPONSE2;
/*@}*/


/** \defgroup rakutenSearchRequest3 �����v���i�[�p�\���� (ItemCodeSearch�p)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �����v���i�[�p�\���́E����3 (2007-02-14��)
typedef struct rakutenSearchRequest3 {
    // ���ʃp�����[�^
    char    developerId[MAX_NAMELEN + 1];   //!< �f�x���b�p�[ID
    char    affiliateId[MAX_KEYLENGTH];     //!< �A�t�B���G�C�gID
    char    operation[RAKUTEN_OPE_LEN];     //!< ����
    // �T�[�r�X�ŗL�p�����[�^   -- ItemCodeSearch
    char    itemCode[MAX_KEYLENGTH];        //!< ���i�R�[�h (�� book:11918897)
    char    version[RAKUTEN_VERSION_LEN];   //!< �o�[�W����
    int     carrier;                        //!< �L�����A
}   RAKUTEN_API_REQUEST3;
/*@}*/

/** \defgroup rakutenSearchResponse3 �������ʊi�[�p�\���� (ItemCodeSearch�p)
 *  \ingroup rakutenWebAPI
 */
/*@{*/
//! �������ʊi�[�p�\���́E����3 (2007-02-14��)
typedef struct rakutenSearchResponse3 {
    char            status[MAX_NAMELEN];            //!< ���s���ʃX�e�[�^�X
    char            statusMsg[RAKUTEN_STATMSG_LEN]; //!< ���s���ʃX�e�[�^�X�ڍ�
    int             carrier;                        //!< �L�����A (PC=0 or mobile=1)
    RAKUTEN_ITEM    *item;                          //!< ���i��� + �X�܏�� + �W���������
}   RAKUTEN_API_RESPONSE3;
/*@}*/


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
    );

RAKUTEN_API_RESPONSE    *
itemSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


// �y�V�W����������API   -- GenreSearch (version:2006-12-26)
RAKUTEN_API_RESPONSE2   *
genreSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        long       genreId,
        BOOL       genrePath
    );

RAKUTEN_API_RESPONSE2   *
genreSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST2 *p );


// �y�V���i�R�[�h����API -- ItemCodeSearch (version:2007-02-14)
RAKUTEN_API_RESPONSE3   *
itemCodeSearchOnRakutenWebAPI(
        const char *developerId,
        const char *affiliateId,
        const char *itemCode,
        int        carrier
    );

RAKUTEN_API_RESPONSE3   *
itemCodeSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST3 *p );


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
    );

RAKUTEN_API_RESPONSE    *
bookSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


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
    );

RAKUTEN_API_RESPONSE    *
cdSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


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
    );

RAKUTEN_API_RESPONSE    *
dvdSearchOnRakutenWebAPIex( const RAKUTEN_API_REQUEST *p );


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
