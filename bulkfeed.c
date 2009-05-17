/*
 *  bulkfeed.c
 *
 * History:
 * $Log: /comm/xmlRPC/bulkfeed.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 22    08/11/17 21:42 Tsujimura543
 * static char �� Thread static char �ɕύX
 * 
 * 21    08/09/09 17:33 Tsujimura543
 * searchEntryOnFeedback() ��p�~
 * 
 * 20    07/03/03 14:59 Tsujimura543
 * FeedBack �Ɋւ���R�����g��ǉ�
 * 
 * 19    07/03/03 14:59 Tsujimura543
 * utf2sjis(), sjis2utf() �� NULL ��Ԃ��ꍇ�Ɉȍ~�̏����ŗ�����s��ɑΏ�
 * 
 * 18    06/11/20 18:48 Tsujimura543
 * �� �Ƃ�����Ă����������Ȃ��̂ŁA�ŏ��Ɏ������Ă����āA���̒l���g����
 *     ���������m�ۂ���悤�ɂ��Ă݂�(��A���܂łƎ����l���S�R�Ⴄ�B������
 *     �̐��݃o�O������̂���?)
 * 
 * 17    06/11/20 18:32 Tsujimura543
 * extractAnalyseOnBulkfeeds() ���� malloc() ���� request �̃T�C�Y���܂�
 * ����Ȃ����Ƃ�����悤�Ȃ̂ŁA���ۂ̌v���l���Q�l�ɑ傫�ڂ̒l��ݒ肵��
 * �݂�
 * 
 * 16    06/11/16 19:42 Tsujimura543
 * ���s����K�v�̂Ȃ� memset() ���폜
 * 
 * 15    06/11/16 19:37 Tsujimura543
 * extractAnalyseOnBulkfeeds() ���� malloc() ���� request �̃T�C�Y�������
 * ���₵��
 * 
 * 14    06/07/24 20:10 Tsujimura543
 * _httpExecute() �̃o�b�t�@�I�[�o�[�����h�~�@�\�𗘗p����悤�ɂ���
 * 
 * 13    06/02/09 16:37 Tsujimura543
 * extractAnalyseOnBulkfeeds() ���̎�M�o�b�t�@�T�C�Y�𑝗�
 * 
 * 12    06/02/02 22:11 Tsujimura543
 * getTerms() ���C��
 * 
 * 11    06/02/02 15:31 Tsujimura543
 * extractAnalyseOnBulkfeeds() ���C�� (API �� URL ���Ԉ���Ă���)
 * 
 * 10    05/05/18 16:36 Tsujimura543
 * searchEntryOnFeedback() ��ǉ�
 * 
 * 9     05/05/18 16:29 Tsujimura543
 * searchRssOnBulkfeeds() �̏������኱�C���B�b��d�l�ł��邱�Ƃ𖾋L�B
 * 
 * 8     05/05/18 14:25 Tsujimura543
 * extractFeatureWordsOnBulkfeeds() �� extractAnalyseOnBulkfeeds() ��
 * ������2�ǉ�
 * 
 * 7     05/05/17 18:58 Tsujimura543
 * getRssUrlOnBulkfeeds() �̕Ԃ�������� RSS �� URL ���̂��̂ɕύX
 * 
 * 6     05/04/28 11:25 Tsujimura543
 * updateRssOnBulkfeeds() �̖߂�l�̌^�� int ���� BOOL �ɕύX
 * 
 * 5     04/11/15 17:06 Tsujimura543
 * encodeURL() ���Ŋm�ۂ����̈�̉��������ǉ�
 * 
 * 4     04/11/11 11:26 Tsujimura543
 * searchSimilarityOnBulkfeeds() �̈�����ύX
 * 
 * 3     04/10/27 15:02 Tsujimura543
 * searchEntryOnBulkfeeds() �̎d�l��ύX�B�L�[���[�h������������(�L���ꗗ)
 * ��Ԃ��悤�ɂ���
 * 
 * 2     04/07/07 11:58 Tsujimura543
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/bulkfeed.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/*
 *  Bulkfeeds API
 */

static int
getTerms( const char *buf, int numOfTerms, BF_TERM *terms )
{
    char    *p   = strstr( buf, "<terms about=\"" );
    int     num  = 0;
    int     skip = 14;

    if ( !p ) {
        p = strstr( buf, "<terms>" );
        skip = 7;
    }
    if ( p ) {
        char    *q = strstr( p + skip, "<term>" );
        char    *r = strstr( p + skip, "</terms>" );

        while ( q && (q < r) ) {
            p = q + 6;
            q = strstr( p, "</term>" );
            if ( !q )
                break;

            strncpy( terms[num].term, p, q - p );
            terms[num].term[q - p] = NUL;

            if ( ++num >= numOfTerms )
                break;

            q = strstr( p, "<term>" );
        }
    }

    return ( num );
}


/* Bulkfeeds API Key �ݒ� */
void
setApiKeyOnBulkfeeds( const char *apiKey )
{
    if ( xmlrpc_p && apiKey && *apiKey )
        strcpy( xmlrpc_p->bulkfeedsAPIkey, apiKey );
}

/* RSS �o�^/�X�V  �� weblogUpdates.ping ���g�p */

/* RSS/OPML���ڎw��ɂ��o�^/�X�V                               */
/*   GET http://bulkfeeds.net/app/add.xml?url=�o�^������RSS/OPML */
BOOL
updateRssOnBulkfeeds( const char *url )
{
    int     res;
    BOOL    ret = FALSE;
    char    rcvBuf[BUFSIZ * 2];
    char    addr[BUFSIZ];
    size_t  sz  = BUFSIZ * 2;

    sprintf( addr, "http://bulkfeeds.net/app/add.xml?url=%s", url );

    setUpReceiveBuffer( rcvBuf, sz );
    res = httpGetBuffer( addr, rcvBuf, FALSE );
    if ( (res != -1) && rcvBuf[0] )
        ret = TRUE;

    return ( ret );
}


/* RSS Feed ����                                                          */
/*   GET http://bulkfeeds.net/app/search.opml?q=�L�[���[�h;field=�����Ώ� */
/*   GET http://bulkfeeds.net/app/search.rdf?q=�L�[���[�h;field=�����Ώ�  */
/*             �L�[���[�h�� UTF-8 �̕������ URL �G���R�[�h��������       */
/*             �����Ώ� �� title | description | link �̂����ꂩ          */

#define BUFFER_SIZE 2048
#define RCV_BUF_SIZ 102400

int
searchRssOnBulkfeeds( const char *keyword, const char *field, int outputType )
{
    int     ret = 0;
    char    *rcvBuf;
    char    addr[BUFSIZ];
    char    *pp;
    size_t  sz;

    sz = RCV_BUF_SIZ;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( ret );

    pp = sjis2utf( keyword );
    if ( outputType == OUTPUT_RSS )
        sprintf( addr, "http://bulkfeeds.net/app/search.rdf?q=%s&field=%s",
                 encodeURL( pp ? pp : keyword ), field );
    else
        sprintf( addr, "http://bulkfeeds.net/app/search.opml?q=%s&field=%s",
                 encodeURL( pp ? pp : keyword ), field );

    setUpReceiveBuffer( rcvBuf, sz );
    ret = httpGetBuffer( addr, rcvBuf, FALSE );
    if ( (ret != -1) && (rcvBuf[0]) ) {
        /* ����: �{���͎擾�����������W���o�͂ɕ\������̂ł͂Ȃ��A */
        /*       API �̌Ăяo�����ɓn���ׂ��ł��邪�A2005�N5��18����  */
        /*       �݁Ablukfeeds �̓��Y API ���@�\��~���̂��߁A�b��I  */
        /*       �ɁA�W���o�͂ɕ\������d�l�Ƃ��Ă���                 */
        if ( strlen( rcvBuf ) < BUFFER_SIZE ) {
            pp = utf2sjis( rcvBuf );
            fputs( pp ? pp : rcvBuf, stdout );
        }
        else {
            char    buf[BUFFER_SIZE];
            char    *p;
            char    *q;

            p = rcvBuf;
            do {
                q = strchr( p, '\n' );
                if ( !q )
                    q = p + strlen( p ) - 1;
                strncpy( buf, p, q - p + 1 );
                buf[q - p + 1] = '\0';
                pp = utf2sjis( buf );
                    fputs( p ? p : buf, stdout );
                p = q + 1;
            } while ( strlen( p ) >= BUFFER_SIZE );
            if ( p && *p ) {
                pp = utf2sjis( p );
                fputs( pp ? pp : p, stdout );
            }
        }
    }

    encodeURL( NULL );
    free( rcvBuf );

    return ( ret );
}

/* RSS Item �S������ */
/*   GET http://bulkfeeds.net/app/search2.rdf?q=�L�[���[�h                */

int
searchEntryOnBulkfeeds(
        const char *keyword,        // (I) �L�[���[�h
        int        *numberOfPosts,  // (I) �擾����L�����̐�
                                    // (O) ���ۂɎ擾�����L�����̐�
        POSTINF    *postinf         // (O) �擾�����L�����
    )
{
    int     ret = 0;
    char    addr[BUFSIZ];

    sprintf( addr, "http://bulkfeeds.net/app/search2.rdf?q=%s",
             encodeURL( sjis2utf( keyword ) ) );
    ret = getRecentPostTitlesFromRSS( addr, numberOfPosts, postinf );
    encodeURL( NULL );

    return ( ret );
}

/* RSS Similarity Search                                                  */
/*   GET http://bulkfeeds.net/app/similar.rdf?url=�A�h���X&apikey=API�L�[ */

int
searchSimilarityOnBulkfeeds(
        const char *url,            // (I) �ގ��L���������������L����URL
        const char *apiKey,         // (I) API�L�[
        int        *numberOfPosts,  // (I) �擾����L�����̐�
                                    // (O) ���ۂɎ擾�����L�����̐�
        POSTINF    *postinf         // (O) �擾�����L�����
    )
{
    int         ret = 0;
    const char  *key;
    char        addr[BUFSIZ];

    if ( !apiKey )
        key = xmlrpc_p->bulkfeedsAPIkey;
    else
        key = apiKey;

    sprintf( addr, "http://bulkfeeds.net/app/similar.rdf?url=%s&apikey=%s",
             url, key );
    ret = getRecentPostTitlesFromRSS( addr, numberOfPosts, postinf );

    return ( ret );
}

/* ��������10��擾                                                         */
/*   GET http://bulkfeeds.net/app/similar.xml?url=�A�h���X&apikey=API�L�[     */
/*    �Ԃ�l(XML) �̗�                                                        */
/*      <?xml version="1.0" encoding="utf-8" ?>                               */
/*      <terms about="http://watcher.moe-nifty.com/memo/2004/04/post_1.html"> */
/*      <term>�D�q</term>                                                     */
/*      <term>���q</term>                                                     */
/*      <term>BLOODY</term>                                                   */
/*      <term>�g���J</term>                                                   */
/*      <term>���</term>                                                     */
/*      <term>�b</term>                                                       */
/*      <term>�v��</term>                                                     */
/*      <term>�t��</term>                                                     */
/*      <term>��</term>                                                       */
/*      <term>�g</term>                                                       */
/*      </terms>                                                              */

int
extractFeatureWordsOnBulkfeeds(
        const char *url,        // (I) ������𒊏o�������L����URL
        const char *apiKey,     // (I) API�L�[
        int        *numOfTerms, // (I) �擾���������̐� (�ő� 10��)
                                // (O) ���ۂɎ擾����������̐�
        BF_TERM    *terms       // (O) �擾����������
    )
{
    int         ret = 0, r;
    const char  *key;
    char        *rcvBuf;
    char        addr[BUFSIZ];
    size_t      sz;

    if ( !url || !(url[0]) || !numOfTerms || !terms )
        return ( ret );

    sz = RCV_BUF_SIZ;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( ret );

    if ( *numOfTerms > 10 )
        *numOfTerms = 10;

    if ( !apiKey )
        key = xmlrpc_p->bulkfeedsAPIkey;
    else
        key = apiKey;

    sprintf( addr, "http://bulkfeeds.net/app/similar.xml?url=%s&apikey=%s",
             encodeURL(url), key );

    setUpReceiveBuffer( rcvBuf, sz );
    r = httpGetBuffer( addr, rcvBuf, FALSE );
    if ( rcvBuf[0] )
        ret = *numOfTerms = getTerms( rcvBuf, *numOfTerms, terms );

    free( rcvBuf );

    return ( ret );
}

/* �`�ԑf��� + �����ꒊ�o                                                        */
/*   GET http://bulkfeeds.net/app/terms.xml?content=��͑Ώە�����&apikey=API�L�[ */

int
extractAnalyseOnBulkfeeds(
        const char *content,    // (I) �`�ԑf���(�����ꒊ�o)�Ώۂ̕�����
        const char *apiKey,     // (I) API�L�[
        int        *numOfTerms, // (I) �擾���������̐�
                                // (O) ���ۂɎ擾����������̐�
        BF_TERM    *terms       // (O) �擾����������
    )
{
    int         ret = 0;
    const char  *key;
    char        *rcvBuf;
    char        url[MAX_URLLENGTH];
    char        *request;
    char        *p;
    size_t      sz, szTarget;

    if ( !content || !(content[0]) || !numOfTerms || !terms )
        return ( ret );

    sz = MAX_CONTENT_SIZE;
    rcvBuf = (char *)malloc( sz );
    if ( !rcvBuf )
        return ( ret );

    if ( !apiKey )
        key = xmlrpc_p->bulkfeedsAPIkey;
    else
        key = apiKey;

    p = sjis2utf(content);
    if ( p )
        szTarget = strlen(encodeURL(p));
    else
        szTarget = strlen(content) * 18;

    request = (char *)malloc( szTarget + strlen(key) + BUFSIZ );
    if ( !request ) {
        free( rcvBuf );
        return ( ret );
    }

    strcpy( url, "http://bulkfeeds.net/app/terms.xml" );
    sprintf( request, "content=%s&apikey=%s",
             encodeURL( p ? p : content ), key );
    setTargetURL( url );

    setUpReceiveBuffer( rcvBuf, sz );
    http_post( url, "application/x-www-form-urlencoded", request, rcvBuf );
    if ( rcvBuf[0] )
        ret = *numOfTerms = getTerms( rcvBuf, *numOfTerms, terms );
    encodeURL( NULL );

    free( request );
    free( rcvBuf );

    return ( ret );
}

/* RSS Auto Discovery                                                      */
/*   GET http://bulkfeeds.net/app/discover.xml?url=�A�h���X&apikey=API�L�[ */
/*    �Ԃ�l(XML) �̗�                                                     */
/*      <?xml version="1.0" encoding="UTF-8" ?>                            */
/*      <result about="http://watcher.moe-nifty.com/memo/">                */
/*      <success>http://watcher.moe-nifty.com/memo/index.rdf</success>     */
/*      </result>                                                          */

char    *
getRssUrlOnBulkfeeds( const char *blogUrl, const char *apiKey )
{
    int                 ret = 0;
    const char          *key;
    char                addr[BUFSIZ];
    Thread static char  buf[BUFFER_SIZE];
    size_t              sz  = BUFFER_SIZE;

    if ( !apiKey )
        key = xmlrpc_p->bulkfeedsAPIkey;
    else
        key = apiKey;

    sprintf( addr, "http://bulkfeeds.net/app/discover.xml?url=%s&apikey=%s",
             blogUrl, key );

    setUpReceiveBuffer( buf, sz );
    ret = httpGetBuffer( addr, buf, FALSE );
    if ( buf[0] ) {
        char    *p = strstr( buf, "<success>" ), *q;
        if ( p ) {
            p += 9;
            q = strstr( p, "</success>" );
            if ( q )
                *q = NUL;
            strcpy( buf, p );
        }
        else
            buf[0] = NUL;
    }

    return ( buf );
}


#if 0
/*
 *  FeedBack API
 */

/* RSS Item �S������ */
/*   GET http://naoya.dyndns.org/feedback/app/rss?keyword=�L�[���[�h */
/*   ���݁AFeedBack �͉^�p��~�� (�ĊJ����\��͂Ȃ�?)               */

int
searchEntryOnFeedback(
        const char *keyword,        // (I) �L�[���[�h
        int        *numberOfPosts,  // (I) �擾����L�����̐�
                                    // (O) ���ۂɎ擾�����L�����̐�
        POSTINF    *postinf         // (O) �擾�����L�����
    )
{
    int     ret = 0;
    char    *p;
    char    addr[BUFSIZ];

    p = sjis2utf( keyword );
    sprintf( addr, "http://naoya.dyndns.org/feedback/app/rss?keyword=%s",
             encodeURL( p ? p : keyword ) );
    ret = getRecentPostTitlesFromRSS( addr, numberOfPosts, postinf );
    encodeURL( NULL );

    return ( ret );
}
#endif
