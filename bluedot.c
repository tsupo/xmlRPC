/*
 *  bludot.c
 *
 * History:
 * $Log: /comm/xmlRPC/bluedot.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/02/25 16:22 Tsujimura543
 * bluedot.us �� faves.com �ւ̈ڍs�ɔ����C�������{
 * 
 * 3     07/01/29 20:11 Tsujimura543
 * getNumberOfTagsOnBlueDot() ��ǉ�
 * 
 * 2     07/01/11 19:39 Tsujimura543
 * Blue Dot �� html �̏������������ɕς�������߁AgetNumberOfBookmarksOnBl
 * ueDot() ���C��
 * 
 * 1     06/10/06 21:56 Tsujimura543
 * �V�K�쐬 (del.icio.us �݊� API)
 */

#include "xmlRPC.h"
#include "delicious.h"
#include "bluedot.h"
#include "deliciousApi.h"
#include <time.h>
#include <math.h>

#define isWhiteSpace(c) \
    (((c) == ' ') || ((c) == '\t') || ((c) == '\r') || ((c) == '\n'))

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/bluedot.c 1     09/05/14 3:46 tsupo $";
#endif

/*
 *  Blue Dot: del.icio.us API
 */

/* ���t�ʓ��e���̈ꗗ�̎擾 */

long
getListOfDatesOnBlueDot(
        const char      *userName,      /* (I) ���[�U��       */
        const char      *password,      /* (I) �p�X���[�h     */
        char            *tag,           /* (I) �^�O           */
        long            *numOfDates,    /* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_DATES *dates          /* (O) �擾�������   */
    )
{
    return ( getListOfDatesOnDeliciousAPI( DAPI_BLUEDOT,
                                           userName, password,
                                           tag, numOfDates, dates ) );
}


/* �g���Ă���^�O�̈ꗗ�̎擾 */

long
getListOfTagsOnBlueDot(
        const char     *userName,   /* (I) ���[�U��       */
        const char     *password,   /* (I) �p�X���[�h     */
        long           *numOfTags,  /* (I) �擾������ */
                                    /* (O) �擾������� */
        DELICIOUS_TAGS *tags        /* (O) �擾�������   */
    )
{
    return ( getListOfTagsOnDeliciousAPI( DAPI_BLUEDOT,
                                          userName, password,
                                          numOfTags, tags ) );
}


/* �w�肵�����t�ɓ��e�����G���g���̈ꗗ�̎擾 */

long
getListOfPostsOnBlueDot(
        const char      *userName,  /* (I) ���[�U��                         */
        const char      *password,  /* (I) �p�X���[�h                       */
        const char      *tag,       /* (I) �������� (�^�O)                  */
        const char      *dateTime,  /* (I) �������� (���e����)
                                                   yyyy-mm-ddThh:mm:ssZ�`�� */
        const char      *targetUrl, /* (I) �������� (URL)                   */
        long            *numOfPosts,/* (I) �擾������                   */
                                    /* (O) �擾�������                   */
        DELICIOUS_POSTS *posts      /* (O) �擾�������                     */
    )
{
    return ( getListOfPostsOnDeliciousAPI( DAPI_BLUEDOT,
                                           userName, password,
                                           tag, dateTime, targetUrl,
                                           numOfPosts, posts ) );
}


/* �ŋ߂̃G���g���ꗗ�̎擾 */

long
getRecentPostsOnBlueDot(
        const char      *userName,  /* (I) ���[�U��        */
        const char      *password,  /* (I) �p�X���[�h      */
        const char      *tag,       /* (I) �������� (�^�O) */
        long            *numOfPosts,/* (I) �擾������  */
                                    /* (O) �擾�������  */
        DELICIOUS_POSTS *posts      /* (O) �擾�������    */
    )
{
    return ( getRecentPostsOnDeliciousAPI( DAPI_BLUEDOT,
                                           userName, password,
                                           tag, numOfPosts, posts ) );
}


/* �S�G���g���̎擾 */

long
getAllPostsOnBlueDot(
        const char      *userName,  /* (I) ���[�U��        */
        const char      *password,  /* (I) �p�X���[�h      */
        const char      *tag,       /* (I) �������� (�^�O) */
        long            *numOfPosts,/* (I) �擾������  */
                                    /* (O) �擾�������  */
        DELICIOUS_POSTS *posts      /* (O) �擾�������    */
    )
{
    return ( getAllPostsOnDeliciousAPI( DAPI_BLUEDOT,
                                        userName, password,
                                        tag, numOfPosts, posts ) );
}


/* �ŏI�X�V�����̎擾 */

long
getLastUpdateOnBlueDot(
        const char *userName,   /* (I) ���[�U��     */
        const char *password,   /* (I) �p�X���[�h   */
        char       *dateTime    /* (O) �擾������� */
    )
{
    return ( getLastUpdateOnDeliciousAPI( DAPI_BLUEDOT,
                                          userName, password,
                                          dateTime ) );
}


/* �G���g���̓��e(�u�b�N�}�[�N�̒ǉ��o�^) */

BOOL
postEntryOnBlueDot(
    const char      *userName,      /* (I) ���[�U��               */
    const char      *password,      /* (I) �p�X���[�h             */
    DELICIOUS_ENTRY *entry     )    /* (I) �o�^������(���e���e) */
{
    return ( postEntryOnDeliciousAPI( DAPI_BLUEDOT,
                                      userName, password, entry ) );
}


/* �G���g���̍폜 */

BOOL
deleteEntryOnBlueDot(
        const char *userName,   /* (I) ���[�U��                    */
        const char *password,   /* (I) �p�X���[�h                  */
        const char *url         /* (I) �폜����G���g���� URL �v�f */
    )
{
    return ( deleteEntryOnDeliciousAPI( DAPI_BLUEDOT,
                                        userName, password, url ) );
}


/* �^�O�̕ύX */

BOOL
renameTagOnBlueDot(
        const char *userName,   /* (I) ���[�U��   */
        const char *password,   /* (I) �p�X���[�h */
        const char *oldTag,     /* (I) �Â��^�O   */
        const char *newTag      /* (I) �V�����^�O */
    )
{
    return ( renameTagOnDeliciousAPI( DAPI_BLUEDOT,
                                      userName, password,
                                      oldTag, newTag ) );
}


/*
 *  �ǉ��@�\
 */

/* ���u�b�N�}�[�N���̎擾 */

long
getNumberOfBookmarksOnBlueDot(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    )
{
    long    num = 0;
    char    url[BUFSIZ];
    char    *response;
    size_t  sz;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE * 16;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

 // sprintf( url, "http://bluedot.us/users/%s", userName );
    sprintf( url, "http://faves.com/users/%s", userName );

    setUpReceiveBuffer( response, sz );
    http_get( url, response );
    if ( response[0] ) {
        char    *p = strstr( response, "Faves<img" );
        if ( p ) {
            char    *q = p;
            char    *r;
            char    buf[BUFSIZ];
            int     i = 0;

            while ( (p > response) && (*(p - 1) != '>') )
                p--;
            r = strstr( p, "of" );
            if ( r )
                p = r + 2;

            while ( *p && (p < q) ) {
                if ( (*p >= '0') && (*p <= '9') )
                    buf[i++] = *p;
                p++;
            }
            buf[i] = NUL;
            num = atol( buf );
        }
    }
    free( response );

    return ( num );
}


/* ���^�O���̎擾 */
long
getNumberOfTagsOnBlueDot(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    )
{
    long    num = 0;
    char    url[MAX_URLLENGTH];
    char    cookie[MAX_COOKIE_LEN];
    char    *response;
    size_t  sz;
    int     r;

    cookie[0] = NUL;
    sz = MAX_CONTENT_SIZE * 16;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    r = loginBlueDot( userName, password, cookie );
    if ( r || *cookie ) {
     // sprintf( url, "http://bluedot.us/users/%s/tag", userName );
        sprintf( url, "http://faves.com/users/%s/tag", userName );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
        if ( *response ) {
            char    *p = strstr( response, "var tagExplorerMax =" );

            if ( p ) {
                p += 20;
                while ( isWhiteSpace( *p ) )
                    p++;
                num = atol( p );
            }

            if ( num == 0 ) {
                p = strstr( response, "<span>1 - 20</span> of " );
                if ( p ) {
                    int     n = 0;
                    char    *q;

                    p += 23;
                    q = strstr( p, "</div>" );
                    do {
                        while ( (*(q - 1) >= '0') && (*(q - 1) <= '9') )
                            q--;
                        num += (int)(atol( q ) * pow( 1000.0, (double)n ));
                        n++;
                    } while ( *--q == ',' );
                }
            }
        }
    }

    free( response );

    return ( num );
}


/* Blue Dot �� login */
int
loginBlueDot(
        const char *userName,   /* (I)   ���[�U��   */
        const char *password,   /* (I)   �p�X���[�h */
        char       *cookie      /* (I/O) �N�b�L�[   */
    )
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !cookie )
         return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

 // strcpy( url, "https://secure.bluedot.us/signIn" );
    strcpy( url, "https://secure.faves.com/signIn" );
    setTargetURL( url );
    sprintf( request,
             "rUsername=%s&"
             "rPassword=%s&"
             "rememberMe=1&"
             "action=Sign+In",
             userName, password );
    setUpReceiveBuffer( response, sz );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               "application/x-www-form-urlencoded",
                               request, response, cookie,
                               NULL, NULL );

    if ( ret == -1 )
        ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
    else if ( *response ) {
     // if ( strstr( response, "https://secure.bluedot.us/signOut" ) != NULL )
        if ( strstr( response, "https://secure.faves.com/signOut" ) != NULL )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }

    free( response );
    free( request  );

    return ( ret );
}

