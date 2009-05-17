/*
 *  delicious.c
 *
 * History:
 * $Log: /comm/xmlRPC/delicious.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 38    08/08/12 11:03 Tsujimura543
 * getNumberOfTagsOnDelicious() �� del.icio.us �V�f�U�C���ɑΉ�
 * 
 * 37a   08/08/03 17:14 tsupo
 * del.icio.us �� delicious.com �ւ̕ύX�ɔ����C��
 * (��Ƃ��ăX�N���C�s���O���������C��)
 * 
 * 37    08/07/25 0:57 Tsujimura543
 * private saving �Ή��֘A�A����m�F�ς�
 * 
 * 36    08/07/24 22:44 Tsujimura543
 * getAllPostsFromDeliciousHTML() �� private saving ����Ă���
 * �u�b�N�}�[�N�ɂ��Ή�������
 * 
 * 35    08/05/16 18:53 Tsujimura543
 * getAllPostsFromDeliciousHTML() ��ǉ�
 * 
 * 34    08/03/17 16:05 Tsujimura543
 * getNumberOfBookmarksOnDelicious() ���C���A���[�U���̖����ɐ�����
 * �܂܂��ꍇ�ł��A�������u�b�N�}�[�N�������擾�ł���悤�ɂ���
 * 
 * 33    07/03/03 15:06 Tsujimura543
 * sjis2utf() �� NULL ��Ԃ��ꍇ�̑΍�����{
 * 
 * 32    07/01/29 16:29 Tsujimura543
 * getNumberOfTagsOnDelicious() ��ǉ�
 * 
 * 31    07/01/24 15:43 Tsujimura543
 * removeTagOnDelicious() �� loginDelicious() ��ǉ�
 * 
 * 30    06/10/06 21:21 Tsujimura543
 * �R�����g���C��
 * 
 * 29    06/10/06 21:20 Tsujimura543
 * �\�[�X�𐮗�
 * 
 * 28    06/10/06 21:18 Tsujimura543
 * ���� del.icio.us �݊� API �����u�b�N�}�[�N�T�[�r�X�Ƃ̊Ԃŋ��ʉ��\��
 * ������ deliciousApi.c �ֈڂ���
 * 
 * 27    06/08/17 11:49 Tsujimura543
 * del.icio.us �� API ����(2006�N8��9��)�ɑΉ�
 * 
 * 26    06/07/24 20:10 Tsujimura543
 * _httpExecute() �̃o�b�t�@�I�[�o�[�����h�~�@�\�𗘗p����悤�ɂ���
 * 
 * 25    06/02/08 18:35 Tsujimura543
 * �R�����g���C��
 * 
 * 24    06/02/08 18:33 Tsujimura543
 * (1) getNumberOfBookmarksOnDelicious() ���C��
 *    (�܂� http://del.icio.us/���[�U��/ ���擾���A���u�b�N�}�[�N�������߂�
 *     ���Ƃɐ�������΁A���̒l��Ԃ��悤�ɂ����B�擾�Ɏ��s�����ꍇ�́A�]��
 *     �ʂ�AAPI ���g���ē��v�����擾���A�Z�o����)
 * (2) getPostsOnDelicious() ���̎�M�o�b�t�@�T�C�Y�́A���u�b�N�}�[�N������
 *    �ɎZ�o����悤�ɂ���
 * 
 * 23    06/02/08 17:05 Tsujimura543
 * getPostsOnDelicious() ���̎�M�o�b�t�@�T�C�Y�𑝂₵�� (�b��Ώ�)
 * 
 * 22    05/12/12 17:05 Tsujimura543
 * del.icio.us �ɓo�^����u�b�N�}�[�N�� extended �� UTF-8 �� 255�o�C�g���
 * �傫���Ȃ�Ȃ��悤�ɒ������鏈����ǉ�
 * 
 * 21    05/10/29 1:12 Tsujimura543
 * �u�b�N�}�[�N�o�^���Ɏg�p���鏈�����e�X��������(����m�F�ς�)
 * 
 * 20    05/10/28 21:00 Tsujimura543
 * encodeURLex2() �������I�ɓ������Ă݂�
 * 
 * 19    05/10/28 13:42 Tsujimura543
 * �擾���� tag, �R�����g�� utf2sjis() �����s�����ꍇ�̏�����ǉ�
 * 
 * 18    05/10/27 21:02 Tsujimura543
 * �擾���� title �� utf2sjis() �����s�����ꍇ�̏�����ǉ�
 * 
 * 17    05/09/27 21:30 Tsujimura543
 * ���t�@�N�^�����O�����{
 * 
 * 16    05/09/27 15:55 Tsujimura543
 * getAllPostsOnDelicious() ���̎�M�o�b�t�@�T�C�Y���g��
 * 
 * 15    05/06/27 22:22 Tsujimura543
 * postEntryOnDelicious() ���s���� del.icio.us ����ے艞�����Ԃ��Ă���
 * �ꍇ�̏�����ǉ� (�P�ɃG���[���^�[������悤�ɂ�������)
 * 
 * 14    05/06/09 22:32 Tsujimura543
 * getAllPostsOnDelicious() ���Ŏg���Ă����M�o�b�t�@�T�C�Y�𑝂₵��
 * 
 * 13    05/06/02 21:59 Tsujimura543
 * ����m�F����
 * 
 * 12    05/06/02 18:20 Tsujimura543
 * getNumberOfBookmarksOnDelicious() ��ǉ�
 * 
 * 11    05/05/27 20:50 Tsujimura543
 * deleteBundleOnDelicious() ������
 * 
 * 10    05/05/27 20:41 Tsujimura543
 * setBundleOnDelicious() ������
 * 
 * 9     05/05/27 19:40 Tsujimura543
 * getListOfBundlesOnDelicious() ������
 * 
 * 8     05/05/27 18:50 Tsujimura543
 * renameTagOnDelicious() ������
 * 
 * 7     05/05/27 16:23 Tsujimura543
 * deleteEntryOnDelicious() ������
 * 
 * 6     05/05/27 15:32 Tsujimura543
 * postEntryOnDelicious() ������
 * 
 * 5     05/05/26 18:49 Tsujimura543
 * getLastUpdateOnDelicious() ������
 * 
 * 4     05/05/26 17:57 Tsujimura543
 * getRecentPostsOnDelicious() �� getAllPostsOnDelicious() ������
 * 
 * 3     05/05/26 16:53 Tsujimura543
 * getListOfPostsOnDelicious() ������
 * 
 * 2     05/05/26 14:51 Tsujimura543
 * getListOfTagsOnDelicious() ������
 * 
 * 1     05/05/26 14:22 Tsujimura543
 * getListOfDatesOnDelicious() ������
 */

#include "xmlRPC.h"
#include "delicious.h"
#include "deliciousApi.h"
#include <time.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/delicious.c 1     09/05/14 3:46 tsupo $";
#endif

/*
 *  del.icio.us API
 */

/*
 *  ���t�ʓ��e���̈ꗗ�̎擾
 */

long
getListOfDatesOnDelicious(
        const char      *userName,      /* (I) ���[�U��       */
        const char      *password,      /* (I) �p�X���[�h     */
        char            *tag,           /* (I) �^�O           */
        long            *numOfDates,    /* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_DATES *dates          /* (O) �擾�������   */
    )
{
    return ( getListOfDatesOnDeliciousAPI( DAPI_DELICIOUS,
                                           userName, password,
                                           tag, numOfDates, dates ) );
}


/*
 *  �g���Ă���^�O�̈ꗗ�̎擾
 */

long
getListOfTagsOnDelicious(
        const char     *userName,   /* (I) ���[�U��       */
        const char     *password,   /* (I) �p�X���[�h     */
        long           *numOfTags,  /* (I) �擾������ */
                                    /* (O) �擾������� */
        DELICIOUS_TAGS *tags        /* (O) �擾�������   */
    )
{
    return ( getListOfTagsOnDeliciousAPI( DAPI_DELICIOUS,
                                          userName, password,
                                          numOfTags, tags ) );
}


/*
 *  �w�肵�����t�ɓ��e�����G���g���̈ꗗ�̎擾
 */

long
getListOfPostsOnDelicious(
        const char      *userName,  /* (I) ���[�U��                   */
        const char      *password,  /* (I) �p�X���[�h                 */
        const char      *tag,       /* (I) �������� (�^�O)            */
        const char      *dateTime,  /* (I) �������� (���e����)        */
                                    /*       yyyy-mm-ddThh:mm:ssZ�`�� */
        const char      *targetUrl, /* (I) �������� (URL)             */
        long            *numOfPosts,/* (I) �擾������             */
                                    /* (O) �擾�������             */
        DELICIOUS_POSTS *posts      /* (O) �擾�������               */
    )
{
    return ( getListOfPostsOnDeliciousAPI( DAPI_DELICIOUS,
                                           userName, password,
                                           tag, dateTime, targetUrl,
                                           numOfPosts, posts ) );
}


/*
 *  �ŋ߂̃G���g���ꗗ�̎擾
 */

long
getRecentPostsOnDelicious(
        const char      *userName,  /* (I) ���[�U��        */
        const char      *password,  /* (I) �p�X���[�h      */
        const char      *tag,       /* (I) �������� (�^�O) */
        long            *numOfPosts,/* (I) �擾������  */
                                    /* (O) �擾�������  */
        DELICIOUS_POSTS *posts      /* (O) �擾�������    */
    )
{
    return ( getRecentPostsOnDeliciousAPI( DAPI_DELICIOUS,
                                           userName, password,
                                           tag, numOfPosts, posts ) );
}


/*
 *  �S�G���g���̎擾
 */

long
getAllPostsOnDelicious(
        const char      *userName,  /* (I) ���[�U��        */
        const char      *password,  /* (I) �p�X���[�h      */
        const char      *tag,       /* (I) �������� (�^�O) */
        long            *numOfPosts,/* (I) �擾������  */
                                    /* (O) �擾�������  */
        DELICIOUS_POSTS *posts      /* (O) �擾�������    */
    )
{
    return ( getAllPostsOnDeliciousAPI( DAPI_DELICIOUS,
                                        userName, password,
                                        tag, numOfPosts, posts ) );
}


/*
 *  �ŏI�X�V�����̎擾
 */

long
getLastUpdateOnDelicious(
        const char *userName,   /* (I) ���[�U��     */
        const char *password,   /* (I) �p�X���[�h   */
        char       *dateTime    /* (O) �擾������� */
    )
{
    return ( getLastUpdateOnDeliciousAPI( DAPI_DELICIOUS,
                                          userName, password,
                                          dateTime ) );
}


/*
 *  �G���g���̓��e(�u�b�N�}�[�N�̒ǉ��o�^)
 */

BOOL
postEntryOnDelicious(
    const char      *userName,      /* (I) ���[�U��               */
    const char      *password,      /* (I) �p�X���[�h             */
    DELICIOUS_ENTRY *entry     )    /* (I) �o�^������(���e���e) */
{
    return ( postEntryOnDeliciousAPI( DAPI_DELICIOUS,
                                      userName, password,
                                      entry ) );
}


/*
 *  �G���g���̍폜
 */

BOOL
deleteEntryOnDelicious(
        const char *userName,   /* (I) ���[�U��                    */
        const char *password,   /* (I) �p�X���[�h                  */
        const char *url         /* (I) �폜����G���g���� URL �v�f */
    )
{
    return ( deleteEntryOnDeliciousAPI( DAPI_DELICIOUS,
                                        userName, password,
                                        url ) );
}


/*
 *  �^�O�̕ύX
 */

BOOL
renameTagOnDelicious(
        const char *userName,   /* (I) ���[�U��   */
        const char *password,   /* (I) �p�X���[�h */
        const char *oldTag,     /* (I) �Â��^�O   */
        const char *newTag      /* (I) �V�����^�O */
    )
{
    return ( renameTagOnDeliciousAPI( DAPI_DELICIOUS,
                                      userName, password,
                                      oldTag, newTag ) );
}


/*
 *  �^�O���ޕ\�̎擾
 *      API �̏ڍׂ� http://del.icio.us/help/api/bundles ���Q��
 */

long
getListOfBundlesOnDelicious(
        const char        *userName,    /* (I) ���[�U��       */
        const char        *password,    /* (I) �p�X���[�h     */
        long              *numOfBundles,/* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_BUNDLES *bundles      /* (O) �擾�������   */
    )
{
    long    num = 0;
    char    url[BUFSIZ];
    char    *response;
    size_t  sz;

    if ( !numOfBundles || (*numOfBundles <= 0) || !bundles )
        return ( num );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

#ifdef  BEFORE_20060809
    strcpy( url, "http://del.icio.us/api/tags/bundles/all" );
#else
    strcpy( url, "https://api.del.icio.us/v1/tags/bundles/all" );
#endif

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<bundles" );

        if ( p ) {
            char    *q, *r, *s;

            p += 8;
            while ( ( q = strstr( p, "<bundle " ) ) != NULL ) {
                q += 8;

                /* name */
                bundles[num].name[0] = NUL;
                r = strstr( q, "name=\"" );
                if ( r ) {
                    r += 6;
                    s = strchr( r, '"' );
                    if ( s ) {
                        strncpy( bundles[num].name, r, s - r );
                        bundles[num].name[s - r] = NUL;
                    }
                }

                /* tags */
                bundles[num].tags[0] = NUL;
                r = strstr( q, "tags=\"" );
                if ( r ) {
                    r += 6;
                    s = strchr( r, '"' );
                    if ( s ) {
                        strncpy( bundles[num].tags, r, s - r );
                        bundles[num].tags[s - r] = NUL;
                    }
                }

                num++;
                if ( num >= *numOfBundles )
                    break;
                p = strchr( q, '>' );
                if ( !p )
                    break;
            }

            *numOfBundles = num;
        }
    }
    free( response );

    return ( num );
}


/*
 *  �^�O�̕���
 *      API �̏ڍׂ� http://del.icio.us/help/api/bundles ���Q��
 */

BOOL
setBundleOnDelicious(
        const char *userName,   /* (I) ���[�U��        */
        const char *password,   /* (I) �p�X���[�h      */
        const char *bundle,     /* (I) �u���ށv�̖��O  */
        const char *tags        /* (I) �^�O (�󔒋�؂�ŕ����w��\) */
    )
{
    BOOL    ret = FALSE;
    char    *url;
    char    *response;
    char    *p;
    size_t  sz;

    if ( !tags || !(*tags) || !bundle || !(*bundle) )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    url = (char *)malloc( BUFSIZ * 2 );
    if ( !url )
        return ( ret );

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( url );
        return ( ret );
    }
    memset( url, 0x00, BUFSIZ * 2 );

    p = sjis2utf(bundle);
    sprintf( url,
#ifdef  BEFORE_20060809
             "http://del.icio.us/api/tags/bundles/set"
#else
             "https://api.del.icio.us/v1/tags/bundles/set"
#endif
             "?bundle=%s",
             encodeURL( p ? p : bundle ) );
    p = sjis2utf(tags);
    sprintf( url + strlen(url),
             "&tags=%s",
             encodeURL( p ? p : tags ) );

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<result" );

        if ( p && (strstr( p + 7, "ok" ) != NULL) )
            ret = TRUE;
    }
    free( response );
    free( url );

    return ( ret );
}


/*
 *  ���ނ̍폜
 *      API �̏ڍׂ� http://del.icio.us/help/api/bundles ���Q��
 */

BOOL
deleteBundleOnDelicious(
        const char *userName,   /* (I) ���[�U��        */
        const char *password,   /* (I) �p�X���[�h      */
        const char *bundle      /* (I) �u���ށv�̖��O  */
    )
{
    BOOL    ret = FALSE;
    char    url[BUFSIZ];
    char    *response;
    char    *p;
    size_t  sz;

    if ( !bundle || !(*bundle) )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !response )
        return ( ret );

    p = sjis2utf(bundle);
    sprintf( url,
#ifdef  BEFORE_20060809
             "http://del.icio.us/api/tags/bundles/delete"
#else
             "https://api.del.icio.us/v1/tags/bundles/delete"
#endif
             "?bundle=%s",
             encodeURL( p ? p : bundle ) );

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<result" );

        if ( p && (strstr( p + 7, "ok" ) != NULL) )
            ret = TRUE;
    }
    free( response );

    return ( ret );
}


/*
 *  �ǉ��@�\
 */

/* ���u�b�N�}�[�N���̎擾 */

long
getNumberOfBookmarksOnDelicious(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    )
{
    long    num = 0;
    long    n;
    char    url[BUFSIZ];
    char    cookie[MAX_COOKIE_LEN];
    char    *response;
    size_t  sz;
    int     r;

    cookie[0] = NUL;
    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE * 16;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    sprintf( url, "http://delicious.com/%s/", userName );
    setUpReceiveBuffer( response, sz );

    r = loginDelicious( userName, password, cookie );
    if ( r )
        http_getEx( url, response, cookie );
    else
        http_get( url, response );
    if ( response[0] ) {
        char    *p = strstr( response, "<span id=\"tagScopeCount\">" );
        if ( p ) {
            char    *q;
            
            p = strchr( p, '>' ) + 1;
            q = strstr( p, "</" );
            if ( q ) {
                num = atol( p );
                free( response );
                return ( num );
            }
        }
    }

#ifdef  BEFORE_20060809
    strcpy( url, "http://del.icio.us/api/posts/dates" );
#else
    strcpy( url, "https://api.del.icio.us/v1/posts/dates" );
#endif

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<dates tag=\"" );

        if ( p ) {
            char    *q, *r;

            p += 12;
            while ( ( q = strstr( p, "<date " ) ) != NULL ) {
                q += 6;

                /* count */
                r = strstr( q, "count=\"" );
                if ( r ) {
                    r += 7;
                    n = atol( r );
                    num += n;
                }

                p = strchr( q, '>' );
                if ( !p )
                    break;
            }
        }
    }
    free( response );

    return ( num );
}

/* ���^�O���̎擾 */
long
getNumberOfTagsOnDelicious(
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

    r = loginDelicious( userName, password, cookie );
    if ( r ) {
        strcpy( url,
            "https://secure.delicious.com/settings/tags/rename?noredir" );
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );
        if ( *response ) {
            char    *p = strstr(response,
                                "<select class=\"field\" name=\"old_tag\">");

            if ( p ) {
                char    *q, *r;

                p += 37;
                r = strstr( p, "</select>" );
                if ( r ) {
                    do {
                        q = strstr( p, "<option>" );
                        if ( !q || (q > r) )
                            break;
                        num++;
                        p = q + 8;
                    } while ( p < r );
                }
            }
        }
    }

    return ( num );
}


/*
 *  �^�O�̍폜
 */

BOOL
removeTagOnDelicious(
        const char *userName,   /* (I) ���[�U��       */
        const char *password,   /* (I) �p�X���[�h     */
        const char *tag         /* (I) �폜�Ώۂ̃^�O */
    )
{
    return ( removeTagOnDeliciousAPI( DAPI_DELICIOUS,
                                      userName, password, tag ) );
}


/*
 *  del.icio.us �� login
 *      API �����݂��Ȃ��Ȃǂ̗��R�ŁA���� del.icio.us �ƑΘb����
 *      �R�}���h�𔭍s����K�v������ꍇ�Ɏg�p����
 */

int
loginDelicious(
        const char *userName,
        const char *password,
        char       *cookie
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

    strcpy( url, "https://secure.delicious.com/login" );
    setTargetURL( url );
    sprintf( request,
		     "jump=ub&"
			 "noui=no&"
			 "v=&"
             "username=%s&"
             "password=%s&"
			 "rememberme=1&"
             "submit=submit",
             userName, password );
    setUpReceiveBuffer( response, sz );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               "application/x-www-form-urlencoded",
                               request, response, cookie,
                               NULL, NULL );

    if ( ret == -1 )
        ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
    else if ( *response ) {
        if ( strstr( response, "Signed in as " ) != NULL )
            ret = 1;    /* ���O�C������ */
        else
            ret = 0;    /* ���O�C�����s */
    }

    free( response );
    free( request  );

    return ( ret );
}


long
getAllPostsFromDeliciousHTML(
        const char      *userName,   /* (I) ���[�U��       */
        const char      *password,   /* (I) �p�X���[�h     */
        long            *numOfPosts, /* (I) �擾������ */
                                     /* (O) �擾������� */
        DELICIOUS_POSTS *posts       /* (O) �擾�������   */
    )
{
    long        num   = 0;
    long        total = *numOfPosts;
    long        page  = 1;
    BOOL        cont  = TRUE;
    size_t      sz    = MAX_CONTENT_SIZE * 20;
    char        url[MAX_URLLENGTH];
    char        dateTime[MAX_DATELENGTH];
    char        *response;
    char        *response2;
    char        *cookie;
    char        *p, *q, *r, *s, *t;

#define ITEMS_PER_PAGE  100

    *numOfPosts = 0;
    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( num );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    if ( password && *password ) {
        /* del.icio.us �� login */
        if ( !loginDelicious( userName, password, cookie ) ) {
            // login ���s
            free( cookie );
            return ( num );
        }
    }

    response = (char *)malloc( sz );
    if ( !response ) {
        free( cookie );
        return ( num );
    }
    response2 = (char *)malloc( sz );
    if ( !response2 ) {
        free( response );
        free( cookie );
        return ( num );
    }

    dateTime[0] = NUL;
    sprintf( url,
             "http://delicious.com/%s?detail=2&setcount=%d",
             userName, ITEMS_PER_PAGE );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    http_getEx( url, response, cookie );
    do {
        if ( !response || !(response[0]) )
            break;

        // �u�b�N�}�[�N�𔲂��o��
        p = strstr( response, "id=\"bookmarklist\"" );
        if ( !p )
            break;
        p += 17;

        do {
            posts[num].href[0]        = NUL;
            posts[num].description[0] = NUL;
            posts[num].extended[0]    = NUL;
            posts[num].hash[0]        = NUL;
            posts[num].others         = 0;
            posts[num].tag[0]         = NUL;
            posts[num].dateTime[0]    = NUL;
            posts[num].shared         = TRUE;

            q = strstr( p, "<div class=\"data\">" );
            s = strstr( p, "<div class=\"clr\"></div>" );
            t = strstr( p, "<div class=\"dateGroup\">" );
            if ( !q || !s || (q > s) )
                break;

            if ( t && (t < q) ) {
                // dateTime
                t = strstr( t + 23, "<span title=\"" );
                if ( t ) {
                    int         yy = 0, mm = 9, dd = 0;
                    int         i;
                    static char monStr[12][4] = {
                        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
                    };

                    t += 13;
                    if ( *t == '0' )
                        t++;
                    dd = atol(t);

                    while ( ((*t < 'A') || (*t > 'Z')) && (t < q) )
                        t++;
                    for ( i = 0; i < 12; i++ ) {
                        if ( !strncmpi( t, monStr[i], 3 ) ) {
                            mm = i + 1;
                            break;
                        }
                    }

                    while ( ((*t <= '0') || (*t > '9')) && (t < q) )
                        t++;
                    yy = atol( t ) + 2000;

                    if ( (yy > 0) && (mm > 0) && (dd > 0) )
                        sprintf( dateTime, "%04d-%02d-%02dT00:00:00Z",
                                 yy, mm, dd );
                }
            }

            p = q + 18;
            q = strstr( p, "<a class=\"action " );
            t = strstr( p, "<h4" );
            if ( !q || (q > s) )
                break;

            if ( q && (q < t) ) {
                p = q + 17;
                if ( !strncmp( p, "private", 7 ) ) {
                    // shared
                    posts[num].shared = FALSE;
                }
            }

            // url
            q = strstr( p, "<h4" );
            if ( !q || (q > s) )
                break;
            p = strstr( q + 3, "<a " );
            if ( !p || (p > s) )
                break;
            q = strstr( p + 3, "href=\"" );
            if ( !q || (q > s) )
                break;
            p = q + 6;
            q = strchr( p, '"' );
            if ( !q || (q > s) )
                break;
            strncpy( posts[num].href, p, q - p );
            posts[num].href[q - p] = NUL;
            while ( ( r = strstr( posts[num].href, "&amp;" ) ) != NULL )
                strcpy( r + 1, r + 5 );

            // �^�C�g�� (description)
            p = q + 1;
            q = strchr( p, '>' );
            if ( !q || (q > s) )
                break;
            p = q + 1;
            q = strstr( p, "</a>" );
            if ( !q || (q > s) )
                break;
            strncpy( posts[num].description, p, q - p );
            posts[num].description[q - p] = NUL;
            r = utf2sjis( posts[num].description );
            if ( r )
                strcpy( posts[num].description, r );
            else
                utf2sjisEx( posts[num].description );
            /* del.icio.us �̃^�C�g���ɂ͉��s���܂܂꓾�� */
            while ( ((p = strchr(posts[num].description, '\r')) != NULL) ||
                    ((p = strchr(posts[num].description, '\n')) != NULL)    )
                strcpy( p, p + 1 ); /* ���s����菜�� */
            p = q + 4;

            // others
            t = strstr( p, "<span class=\"delNavCount\">" );
            if ( t && (t < s) ) {
                p = t + 26;
                q = strstr( p, "</span>" );
                if ( q && (q < s) ) {
                    posts[num].others = atol( p );
                    p = q + 7;
                }
            }

            // �R�����g (extended) [optional]
            q = strstr( p, "<div class=\"description\">" );
            if ( q && (q < s) ) {
                p = q + 25;
                while ( (*p == ' ')  || (*p == '\t') ||
                        (*p == '\r') || (*p == '\n')    )
                    p++;
                q = strstr( p, "</div>" );
                if ( q && (q < s) ) {
                    while ( (*(q - 1) == ' ')  || (*(q - 1) == '\t') ||
                            (*(q - 1) == '\r') || (*(q - 1) == '\n')    )
                        q--;
                    strncpy( posts[num].extended, p, q - p );
                    posts[num].extended[q - p] = NUL;
                    r = utf2sjis( posts[num].extended );
                    if ( r )
                        strcpy( posts[num].extended, r );
                    else
                        utf2sjisEx( posts[num].extended );
                    /* del.icio.us �̃^�C�g���ɂ͉��s���܂܂꓾�� */
                    while (((p = strchr(posts[num].extended,'\r')) != NULL)||
                           ((p = strchr(posts[num].extended,'\n')) != NULL)  )
                        strcpy( p, p + 1 ); /* ���s����菜�� */

                    p = q + 6;
                }
            }

            // hash
            q = strstr( p, "hash=" );
            if ( q && (q < s) ) {
                p = q + 5;
                q = strchr( p, '&' );
                if ( q && (q < s) ) {
                    strncpy( posts[num].hash, p, q - p );
                    posts[num].hash[q - p] = NUL;

                    p = q + 5;
                }
            }

            // �^�O (tag)
            q = strstr( p, "<ul class=\"tag-chain\">" );
            if ( q && (q < s) ) {
                p = q + 22;
                q = strstr( p, "<a class=\"tag-chain-item-link" );
                r = strstr( p, "</ul>" );
                if ( q && r && (q < s) && (q < r) && (r < s) ) {
                    int len;

                    p = q + 29;
                    do {
                        q = strstr( p, "<span " );
                        if ( !q || (q > r) )
                            break;
                        p = q + 6;
                        q = strchr( p, '>' );
                        if ( !q || (q > r) )
                            break;
                        p = q + 1;
                        q = strstr( p, "</span>" );
                        if ( !q || (q > r) )
                            break;

                        if ( posts[num].tag[0] == NUL )
                            len = 0;
                        else {
                            strcat( posts[num].tag, " " );
                            len = strlen( posts[num].tag );
                        }
                        strncat( posts[num].tag, p, q - p );
                        posts[num].tag[len + (q - p)] = NUL;

                        p = q + 7;
                    } while ( p < r );
                    if ( posts[num].tag[0] ) {
                        r = utf2sjis( posts[num].tag );
                        if ( r )
                            strcpy( posts[num].tag, r );
                        else
                            utf2sjisEx( posts[num].tag );
                    }
                }
            }

            // �N���� (dateTime)
            if ( dateTime[0] )
                strcpy( posts[num].dateTime, dateTime );

            p = s + strlen("<div class=\"clr\"></div>");

            num++;
            if ( num >= total )
                break;
        } while ( p && *p );

        // ����
        cont = FALSE;
        if ( num < total ) {
            if ( page * ITEMS_PER_PAGE >= total )
                break;
            q = strstr( p, "class=\"pn next\">Next" );
            if ( q ) {
                while ( p < q ) {
                    if ( *q == '<' )
                        break;
                    q--;
                }
                if ( *q == '<' ) {
                    p = strstr( q, "href=\"" );
                    if ( p ) {
                        p += 6;
                        q = strchr( p, '"' );
                        if ( q ) {
                            strcpy( url, "http://delicious.com" );
                            strncpy( url + 20, p, q - p );
                            (url + 20)[q - p] = NUL;

                            Sleep( 1000 );

                            setTargetURL( url );
                            setUpReceiveBuffer( response, sz );
                            http_getEx( url, response, cookie );
                            cont = TRUE;
                        }
                    }
                }
            }
        }
    } while ( cont );

    *numOfPosts = num;

    free( response2 );
    free( response );
    free( cookie );

    return ( num );
}
