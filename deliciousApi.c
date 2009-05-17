/*
 *  deliciousApi.c
 *      del.icio.us API ����� del.icio.us �݊� API (Blue Dot API) ���ʏ���
 *          written by H.Tsujimura  2 May 2005 / 6 Oct 2006
 *
 * History:
 * $Log: /comm/xmlRPC/deliciousApi.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 24    08/07/25 0:41 Tsujimura543
 * getAllPostsFromDeliciousXML() �� private saving �ɑΉ�
 * 
 * 23    08/07/24 22:59 Tsujimura543
 * API �� URL �� secure.bluedot.us �� secure.faves.com �ɒu������
 * 
 * 22    08/07/24 22:48 Tsujimura543
 * (1) del.icio.us �� private �w��ł̃u�b�N�}�[�N���e�ɑΉ�
 *      (faves.com �̕��͖��m�F)
 * (2) private saving �ȃu�b�N�}�[�N�̍폜�� API �łł��邱�Ƃ��m�F�ł�
 *     �����߁A��������폜���������ɖ߂���
 * 
 * 21    08/07/22 11:28 Tsujimura543
 * del.icio.us �� private saving �ȃu�b�N�}�[�N�̍폜�ɑΉ� (�e�X�g�����{)
 * 
 * 20    08/07/22 11:01 Tsujimura543
 * BlueDot �̏ꍇ�� getAllPostsFromDeliciousHTML() ���Ăяo��
 * �Ȃ��悤�ɏC��
 * 
 * 19    08/05/16 18:57 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 18    08/05/16 18:54 Tsujimura543
 * getPostsOnDelicious() �ŁAAPI �ɂ��S���擾�Ɏ��s�����ꍇ�́A
 * Web�y�[�W�̃X�N���C�s���O�ɂ��u�b�N�}�[�N�擾�����݂�悤��
 * ���Ă݂�
 * 
 * 17    07/11/12 19:05 Tsujimura543
 * postEntryOnDeliciousAPI() ���ŕ����R�[�h�ϊ����s���ɗ�����s����C��
 * 
 * 16    07/07/09 13:47 Tsujimura543
 * getAllPostsFromDeliciousXML() ��ύX�Ahttp://scuttle.org/ ����
 * del.icio.us �� post/all �݊��`���� export �����f�[�^�ɂ��Ή�����
 * (�Q�l: http://www.tsunematsu.cc/2007/07/07/2038/)
 * 
 * 15    07/06/08 21:34 Tsujimura543
 * postEntryOnDeliciousAPI() ���C���ABlue Dot �̏ꍇ�̂݃��g���C������
 * ����Ă݂�
 * 
 * 14    07/05/21 19:51 Tsujimura543
 * postEntryOnDeliciousAPI() ���C�� (�����̕ύX�͑S���Ȃ�)
 * 
 * 13    07/04/16 16:41 Tsujimura543
 * getAllPostsFromDeliciousXML() ���C���Adescription �� extended ��
 * ���s���܂܂��ꍇ�͏�������悤�ɂ���
 * 
 * 12    07/04/16 15:38 Tsujimura543
 * getAllPostsFromDeliciousXML ��ǉ�
 * 
 * 11    07/03/03 15:33 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 10    07/03/03 15:09 Tsujimura543
 * sjis2utf() �� NULL ��Ԃ��ꍇ�̑΍�����{
 * 
 * 9     07/01/29 16:30 Tsujimura543
 * �^�O�֘A��API�ɑΉ�����e�֐����C��
 * 
 * 8     07/01/24 15:53 Tsujimura543
 * removeTagOnDeliciousAPI() �̏I�����̃���������������C��
 * 
 * 7     07/01/24 15:44 Tsujimura543
 * removeTagOnDeliciousAPI() ��ǉ�
 * 
 * 6     07/01/11 20:07 Tsujimura543
 * Blue Dot ����擾�������ʂ������������邱�Ƃ����錏�ɑ΂���b��Ώ�
 * 
 * 5     06/11/13 20:36 Tsujimura543
 * �폜�Ώ� URL �̕����񒷂� 512�o�C�g���傫����
 * deleteEntryOnDeliciousAPI() ���ŃN���b�V������s��ɑΏ�
 * 
 * 4     06/10/18 19:39 Tsujimura543
 * �u�b�N�}�[�N�擾�����Ńo�b�t�@�I�[�o�[��������������\�������邱�Ƃ�
 * ���������̂ŁA�΍�����{
 * 
 * 3     06/10/06 21:44 Tsujimura543
 * �u�b�N�}�[�N���e���� extend �����̕����񒷃`�F�b�N�� del.icio.us �̏ꍇ
 * �݂̂ɂ���
 * 
 * 2     06/10/06 21:24 Tsujimura543
 * �� del.icio.us API �G���h�|�C���gURL�Ή��������폜
 * 
 * 1     06/10/06 21:07 Tsujimura543
 * delicious.c ���� del.icio.us(�݊�)API �����u�b�N�}�[�N�T�[�r�X���ʏ���
 * �𔲂��o���ĕʃt�@�C���Ƃ��ēƗ�������
 */

#include "deliciousApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/deliciousApi.c 1     09/05/14 3:46 tsupo $";
#endif

/*
 *  del.icio.us (�݊�) API ���ʏ���
 */

/*
 *  ���ʊ֐�
 *      �G���g���ꗗ�̎擾 (+ �擾���� XML �̉��)
 */

long
getAllPostsFromDeliciousXML(
        const char      *buf,           /* (I) �擾������  */
        long            *numOfPosts,    /* (I) �擾������  */
                                        /* (O) �擾�������  */
        DELICIOUS_POSTS *posts          /* (O) �擾�������    */
    )
{
    long    num = 0;

    if ( buf && *buf ) {
        char    *p = strstr( buf, "<posts " );

        if ( p ) {
            char    tmp[MAX_DESCRIPTION_LEN];
            char    *q, *r, *s, *t, *terminate;
            long    l;

            p += 5;
            while ( ( q = strstr( p, "<post " ) ) != NULL ) {
                q += 6;
                terminate = strstr( q, " />" );
                if ( !terminate )
                    terminate = strstr( q, "/>" );
                if ( !terminate )
                    break;

                posts[num].href[0]        = NUL;
                posts[num].description[0] = NUL;
                posts[num].extended[0]    = NUL;
                posts[num].hash[0]        = NUL;
                posts[num].others         = 0;
                posts[num].tag[0]         = NUL;
                posts[num].dateTime[0]    = NUL;
                posts[num].shared         = TRUE;

                /* href */
                r = strstr( q, "href=\"" );
                if ( !r )
                    break;
                r += 6;
                s = strchr( r, '"' );
                if ( !s )
                    break;
                strncpy( posts[num].href, r, s - r );
                posts[num].href[s - r] = NUL;
                if ( strstr( posts[num].href, "&amp;amp;" ) ) {
                    while ( ( r = strstr(posts[num].href, "&amp;amp;") ) != NULL )
                        strcpy( r + 1, r + 5 );
                }
                else {
                    while ( ( r = strstr(posts[num].href, "&amp;") ) != NULL )
                        strcpy( r + 1, r + 5 );
                }

                /* description */
                r = strstr( q, "description=\"" );
                if ( r && (r < terminate) ) {
                    r += 13;
                    s = strchr( r, '"' );
                    if ( s ) {
                        char    *pp, *qq;

                        strncpy( tmp, r, s - r );
                        tmp[s - r] = NUL;
                        t = utf2sjisEx(tmp);
                        s = decodeURL( t ? t : tmp );
                        strcpy( posts[num].description, s ? s : tmp );

                        pp = posts[num].description;
                        while ( ( ( qq = strchr( pp, '\r' ) ) != NULL ) ||
                                ( ( qq = strchr( pp, '\n' ) ) != NULL )    ) {
                            if ( *(qq + 1) == '\n' )
                                strcpy( qq, qq + 2 );
                            else
                                strcpy( qq, qq + 1 );
                            pp = qq;
                        }
                    }
                }

                /* extended */
                r = strstr( q, "extended=\"" );
                if ( r && (r < terminate) ) {
                    r += 10;
                    s = strchr( r, '"' );
                    if ( s ) {
                        char    *pp, *qq;

                        strncpy( tmp, r, s - r );
                        tmp[s - r] = NUL;
                        t = utf2sjisEx(tmp);
                        if ( t )
                            s = strchr( t, '%' ) ? t : decodeURL( t );
                        else
                            s = strchr( tmp, '%' ) ? tmp : decodeURL( tmp );
                        strcpy( posts[num].extended, s ? s : tmp );

                        pp = posts[num].extended;
                        while ( ( ( qq = strchr( pp, '\r' ) ) != NULL ) ||
                                ( ( qq = strchr( pp, '\n' ) ) != NULL )    ) {
                            if ( *(qq + 1) == '\n' )
                                strcpy( qq, qq + 2 );
                            else
                                strcpy( qq, qq + 1 );
                            pp = qq;
                        }
                    }
                }

                /* hash */
                r = strstr( q, "hash=\"" );
                if ( r && (r < terminate) ) {
                    r += 6;
                    s = strchr( r, '"' );
                    if ( s ) {
                        strncpy( posts[num].hash, r, s - r );
                        posts[num].hash[s - r] = NUL;
                    }
                }

                /* others */
                r = strstr( q, "others=\"" );
                if ( r && (r < terminate) ) {
                    r += 8;
                    l = atol(r);
                    posts[num].others = l;
                }

                /* tag */
                r = strstr( q, "tag=\"" );
                if ( r && (r < terminate) ) {
                    r += 5;
                    s = strchr( r, '"' );
                    if ( s ) {
                        strncpy( tmp, r, s - r );
                        tmp[s - r] = NUL;
                        t = utf2sjisEx(tmp);
                        s = decodeURL( t ? t : tmp );
                        strcpy( posts[num].tag, s ? s : tmp );
                    }
                }

                /* time */
                r = strstr( q, "time=\"" );
                if ( r && (r < terminate) ) {
                    r += 6;
                    s = strchr( r, '"' );
                    if ( s ) {
                        strncpy( posts[num].dateTime, r, s - r );
                        posts[num].dateTime[s - r] = NUL;
                    }
                }

                /* shared */
                r = strstr( q, "shared=\"" );
                if ( r && (r < terminate) ) {
                    r += 8;
                    if ( !strncmpi( r, "no", 2 ) )
                        posts[num].shared = FALSE;
                }

                num++;
                if ( num >= *numOfPosts )
                    break;
                p = strchr( q, '>' );
                if ( !p )
                    break;
            }

            *numOfPosts = num;
        }
    }

    return ( num );
}

long
getPostsOnDelicious(
        const char      *url,
        const char      *userName,
        const char      *password,
        long            *numOfPosts,
        DELICIOUS_POSTS *posts 
    )
{
    long    num = 0;
    long    blocks = *numOfPosts / 64;
    char    *response;
    size_t  sz;

    if ( blocks <= 16 )
        blocks = 16;

    sz = MAX_CONTENT_SIZE * blocks;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );

    num = getAllPostsFromDeliciousXML( response, numOfPosts, posts );
    free( response );

    if ( (num == 0) || (getStatusCode() == 503) )
        if ( !strncmp( url, "https://api.del.icio.us/", 24 ) )
            num = getAllPostsFromDeliciousHTML( userName, password,
                                                numOfPosts, posts );

    return ( num );
}


/*
 *  �ȉ��A���ۂ� API ���Ăяo������
 */

/*
 *  ���t�ʓ��e���̈ꗗ�̎擾
 *      API �̏ڍׂ� http://del.icio.us/help/api/posts ���Q��
 */

long
getListOfDatesOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�     */
        const char         *userName,   /* (I) ���[�U��       */
        const char         *password,   /* (I) �p�X���[�h     */
        char               *tag,        /* (I) �^�O           */
        long               *numOfDates, /* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_DATES    *dates       /* (O) �擾�������   */
    )
{
    long    num = 0;
    char    url[BUFSIZ];
    char    *response;
    size_t  sz;

    if ( !numOfDates || (*numOfDates <= 0) || !dates )
        return ( num );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        strcpy( url, "https://api.del.icio.us/v1/posts/dates" );
        break;

    case DAPI_BLUEDOT:
     // strcpy( url, "https://secure.bluedot.us/v1/posts/dates" );
        strcpy( url, "https://secure.faves.com/v1/posts/dates" );
        break;
    }

    if ( tag && *tag )
        sprintf( url + strlen(url),
                 "?tag=%s",
                 encodeURL(tag) );

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<dates tag=\"" );

        if ( p ) {
            char        *q, *r;
            long        l;
            int         yyyy, mm, dd;
            time_t      t = time( NULL );
            struct tm   *tm = localtime( &t );

            yyyy = tm->tm_year + 1900;
            mm   = tm->tm_mon  + 1;
            dd   = tm->tm_mday;

            p += 12;
            while ( ( q = strstr( p, "<date " ) ) != NULL ) {
                q += 6;

                /* count */
                dates[num].count = 0;
                r = strstr( q, "count=\"" );
                if ( r ) {
                    r += 7;
                    l = atol( r );
                    dates[num].count = l;
                }

                /* date */
                dates[num].yyyy = yyyy;
                dates[num].mm   = mm;
                dates[num].dd   = dd;
                r = strstr( q, "date=\"" );
                if ( r ) {
                    r += 6;
                    l = atol( r );
                    dates[num].yyyy = l;
                    r += 5;
                    if ( *r == '0' )
                        r++;
                    l = atol( r );
                    dates[num].mm = l;
                    while ( *r && (*r != '-') )
                        r++;
                    if ( *r == '-' ) {
                        r++;
                        l = atol( r );
                        dates[num].dd = l;
                    }
                }

                num++;
                if ( num >= *numOfDates )
                    break;
                p = strchr( q, '>' );
                if ( !p )
                    break;
            }

            *numOfDates = num;
        }
    }
    free( response );

    return ( num );
}


/*
 *  �g���Ă���^�O�̈ꗗ�̎擾
 *      API �̏ڍׂ� http://del.icio.us/help/api/tags ���Q��
 */

long
getListOfTagsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�     */
        const char         *userName,   /* (I) ���[�U��       */
        const char         *password,   /* (I) �p�X���[�h     */
        long               *numOfTags,  /* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_TAGS     *tags        /* (O) �擾�������   */
    )
{
    long    num = 0;
    char    url[BUFSIZ];
    char    *response;
    size_t  sz;

    if ( !numOfTags || (*numOfTags <= 0) || !tags )
        return ( num );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE * (1 + *numOfTags / 320);
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        strcpy( url, "https://api.del.icio.us/v1/tags/get" );
        break;

    case DAPI_BLUEDOT:
     // strcpy( url, "https://secure.bluedot.us/v1/tags/get" );
        strcpy( url, "https://secure.faves.com/v1/tags/get" );
        break;
    }

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<tags" );

        if ( p ) {
            char    *q, *r, *s;
            long    l;

            p += 5;
            while ( ( q = strstr( p, "<tag " ) ) != NULL ) {
                q += 5;

                /* count */
                tags[num].count = 0;
                r = strstr( q, "count=\"" );
                if ( r ) {
                    r += 7;
                    l = atol( r );
                    tags[num].count = l;
                }

                /* tag */
                tags[num].tag[0] = NUL;
                r = strstr( q, "tag=\"" );
                if ( r ) {
                    r += 5;
                    s = strchr( r, '"' );
                    if ( s ) {
                        strncpy( tags[num].tag, r, s - r );
                        tags[num].tag[s - r] = NUL;
                    }
                }

                num++;
                if ( num >= *numOfTags )
                    break;
                p = strchr( q, '>' );
                if ( !p )
                    break;
            }

            *numOfTags = num;
        }
    }
    free( response );

    return ( num );
}


/*
 *  �w�肵�����t�ɓ��e�����G���g���̈ꗗ�̎擾
 *      API �̏ڍׂ� http://del.icio.us/help/api/posts ���Q��
 */

long
getListOfPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,    /* (I) API �񋟌�                    */
        const char         *userName,  /* (I) ���[�U��                      */
        const char         *password,  /* (I) �p�X���[�h                    */
        const char         *tag,       /* (I) �������� (�^�O)               */
        const char         *dateTime,  /* (I) �������� (���e����)
                                                   yyyy-mm-ddThh:mm:ssZ�`�� */
        const char         *targetUrl, /* (I) �������� (URL)                */
        long               *numOfPosts,/* (I) �擾������                */
                                       /* (O) �擾�������                */
        DELICIOUS_POSTS    *posts      /* (O) �擾�������                  */
    )
{
    long    num = 0;
    char    url[BUFSIZ];

    if ( !numOfPosts || (*numOfPosts <= 0) || !posts )
        return ( num );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        strcpy( url, "https://api.del.icio.us/v1/posts/get" );
        break;

    case DAPI_BLUEDOT:
     // strcpy( url, "https://secure.bluedot.us/v1/posts/get" );
        strcpy( url, "https://secure.faves.com/v1/posts/get" );
        break;
    }

    if ( tag && *tag )
        sprintf( url + strlen(url),
                 "?tag=%s",
                 encodeURL(tag) );
    if ( dateTime && *dateTime )
        sprintf( url + strlen(url),
                 "%cdt=%s",
                 (tag && *tag) ? '&' : '?',
                 dateTime );
#ifndef  BEFORE_20060809
    if ( targetUrl && *targetUrl )
        sprintf( url + strlen(url),
                 "%curl=%s",
                 ((tag && *tag) || (dateTime && *dateTime)) ? '&' : '?',
                 targetUrl );
#endif

    num = getPostsOnDelicious( url, userName, password, numOfPosts, posts );

    return ( num );
}


/*
 *  �ŋ߂̃G���g���ꗗ�̎擾
 *      API �̏ڍׂ� http://del.icio.us/help/api/posts ���Q��
 *
 *      Blue Dot �̏ꍇ��
 *          https://secure.bluedot.us/v1/posts/recent?tags=full
 *      �Ō��������Ƃ��đS�^�O���w�肵�����̂Ƃ��邱�Ƃ��ł���
 */

long
getRecentPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�      */
        const char         *userName,   /* (I) ���[�U��        */
        const char         *password,   /* (I) �p�X���[�h      */
        const char         *tag,        /* (I) �������� (�^�O) */
        long               *numOfPosts, /* (I) �擾������  */
                                        /* (O) �擾�������  */
        DELICIOUS_POSTS    *posts       /* (O) �擾�������    */
    )
{
    long    num = 0;
    char    url[BUFSIZ];

    if ( !numOfPosts || (*numOfPosts <= 0) || !posts )
        return ( num );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    if ( *numOfPosts > 100 )
        *numOfPosts = 100;

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        strcpy( url, "https://api.del.icio.us/v1/posts/recent" );
        break;

    case DAPI_BLUEDOT:
     // strcpy( url, "https://secure.bluedot.us/v1/posts/recent" );
        strcpy( url, "https://secure.faves.com/v1/posts/recent" );
        break;
    }

    if ( tag && *tag )
        sprintf( url + strlen(url),
                 "?tag=%s",
                 encodeURL(tag) );
    sprintf( url + strlen(url),
             "%ccount=%d",
             (tag && *tag) ? '&' : '?',
             *numOfPosts );

    num = getPostsOnDelicious( url, userName, password, numOfPosts, posts );

    return ( num );
}


/*
 *  �S�G���g���̎擾
 *      API �̏ڍׂ� http://del.icio.us/help/api/posts ���Q��
 */

long
getAllPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�      */
        const char         *userName,   /* (I) ���[�U��        */
        const char         *password,   /* (I) �p�X���[�h      */
        const char         *tag,        /* (I) �������� (�^�O) */
        long               *numOfPosts, /* (I) �擾������  */
                                        /* (O) �擾�������  */
        DELICIOUS_POSTS    *posts       /* (O) �擾�������    */
    )
{
    long    num = 0;
    char    url[BUFSIZ];

    if ( !numOfPosts || (*numOfPosts <= 0) || !posts )
        return ( num );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        strcpy( url, "https://api.del.icio.us/v1/posts/all" );
        break;

    case DAPI_BLUEDOT:
     // strcpy( url, "https://secure.bluedot.us/v1/posts/all" );
        strcpy( url, "https://secure.faves.com/v1/posts/all" );
        break;
    }

    if ( tag && *tag )
        sprintf( url + strlen(url),
                 "?tag=%s",
                 encodeURL(tag) );

    num = getPostsOnDelicious( url, userName, password, numOfPosts, posts );

    return ( num );
}


/*
 *  �ŏI�X�V�����̎擾
 *      API �̏ڍׂ� http://del.icio.us/help/api/update ���Q��
 */

long
getLastUpdateOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�   */
        const char         *userName,   /* (I) ���[�U��     */
        const char         *password,   /* (I) �p�X���[�h   */
        char               *dateTime    /* (O) �擾������� */
    )
{
    long    num = 0;
    char    url[BUFSIZ];
    char    *response;
    size_t  sz;

    if ( !dateTime )
        return ( num );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        strcpy( url, "https://api.del.icio.us/v1/posts/update" );
        break;

    case DAPI_BLUEDOT:
     // strcpy( url, "https://secure.bluedot.us/v1/posts/update" );
        strcpy( url, "https://secure.faves.com/v1/posts/update" );
        break;
    }

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<update " );

        if ( p ) {
            char    *q, *r;

            p += 8;
            q = strstr( p, "time=\"" );
            if ( q ) {
                q += 6;
                r = strchr( q, '"' );
                if ( r ) {
                    strncpy( dateTime, q, r - q );
                    dateTime[r - q] = NUL;
                    num = 1;
                }
            }
        }
    }
    free( response );

    return ( num );
}


/*
 *  �G���g���̓��e(�u�b�N�}�[�N�̒ǉ��o�^)
 *      API �̏ڍׂ� http://del.icio.us/help/api/posts ���Q��
 */

static char *
normalizeExtended( char *extended )
{
    if ( strlen( extended ) > MAX_EXTENDED_LENGTH ) {
        char    *s = extended;
        BOOL    kanjiFlag = FALSE;
        int     i = 0;

        while ( *s ) {
            if ( ++i > MAX_EXTENDED_LENGTH )
                break;
            if ( !kanjiFlag && iskanji1( *s ) )
                kanjiFlag = TRUE;
            else
                kanjiFlag = FALSE;
            *s++;
        }
        if ( kanjiFlag )
            *(s - 1) = NUL;
        else
            *s = NUL;
    }

    return ( extended );
}

BOOL
postEntryOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�             */
        const char         *userName,   /* (I) ���[�U��               */
        const char         *password,   /* (I) �p�X���[�h             */
        DELICIOUS_ENTRY    *entry       /* (I) �o�^������(���e���e) */
    )
{
    BOOL    ret = FALSE;
    char    *url;
    char    *response;
    char    *p;
    size_t  sz;
    int     retry = 1;

    if ( !entry || !(entry->url[0]) )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    url = (char *)malloc( sizeof ( DELICIOUS_ENTRY ) + BUFSIZ );
    if ( !url )
        return ( ret );

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( url );
        return ( ret );
    }
    memset( url, 0x00, sizeof ( DELICIOUS_ENTRY ) + BUFSIZ );

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        sprintf( url,
                 "https://api.del.icio.us/v1/posts/add"
                 "?url=%s",
                 encodeURL(entry->url) );
        break;

    case DAPI_BLUEDOT:
        sprintf( url,
              // "https://secure.bluedot.us/v1/posts/add"
                 "https://secure.faves.com/v1/posts/add"
                 "?url=%s",
                 encodeURL(entry->url) );
        break;
    }

    if ( entry->description[0] ) {
        p = sjis2utf( entry->description );
        sprintf( url + strlen(url),
                 "&description=%s",
                 p ? encodeURLex2( p )
                   : encodeURL( entry->description ) );
    }
    if ( entry->extended[0] ) {
        // extended ��(UTF-8��)�ő�255�o�C�g�܂� (del.icio.us �̏ꍇ�̂�)
        //   Blue Dot ��255�o�C�g�ȏ�ł����Ȃ����e�ł���
        p = sjis2utf( entry->extended );
        if ( p && ((apiType != DAPI_DELICIOUS) || (strlen( p ) <= 255)) )
            sprintf( url + strlen(url), "&extended=%s", encodeURL( p ) );
        else {
            // UTF-8��255�o�C�g�ȉ� �� Shift_JIS��170�o�C�g�ȉ� �ɂ���
            //   -- 255 / 3 * 2 = 170 (�����锼�p�p�������܂܂�Ă��Ȃ���
            //                         ���肵���ꍇ)
            char    *q;

            p = normalizeExtended( entry->extended );
            q = sjis2utf(p);
            sprintf( url + strlen(url), "&extended=%s",
                     encodeURL( q ? q : p ) );
        }
    }
    if ( entry->tag[0] ) {
        p = sjis2utf(entry->tag);
        sprintf( url + strlen(url),
                 "&tags=%s",
                 encodeURL( p ? p : entry->tag ) );
    }
    if ( entry->dateTime[0] )
        sprintf( url + strlen(url),
                 "&dt=%s",
                 encodeURL(entry->dateTime) );
    if ( entry->shared == FALSE )
        sprintf( url + strlen(url),
                 "&shared=no" );

    do  {
        setUpReceiveBuffer( response, sz );
        http_getBASIC( url, userName, password, response );
        retry--;
    } while ( (response[0] == NUL) &&
              (apiType == DAPI_BLUEDOT) && (retry >= 0) );
    if ( *response ) {
        p = strstr( response, "<result" );

        /* <result code="something went wrong" /> */
        if ( p && !strstr( p, "<result code=\"something went wrong\" />" ) )
            ret = TRUE;
    }
    free( response );
    free( url );
    encodeURLex2( NULL );

    return ( ret );
}


/*
 *  �G���g���̍폜
 *      API �̏ڍׂ� http://del.icio.us/help/api/posts ���Q��
 */

BOOL
deleteEntryOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�                  */
        const char         *userName,   /* (I) ���[�U��                    */
        const char         *password,   /* (I) �p�X���[�h                  */
        const char         *url         /* (I) �폜����G���g���� URL �v�f */
    )
{
    BOOL    ret = FALSE;
    char    *target;
    char    *response;
    size_t  sz;

    if ( !url || !(*url) )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    target = (char *)malloc( MAX_URLLENGTH + strlen( url ) * 3 );
    if ( !target )
        return ( ret );

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( target );
        return ( ret );
    }

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        sprintf( target,
                 "https://api.del.icio.us/v1/posts/delete"
                 "?url=%s",
                 encodeURL(url) );
        break;

    case DAPI_BLUEDOT:
        sprintf( target,
              // "https://secure.bluedot.us/v1/posts/delete"
                 "https://secure.faves.com/v1/posts/delete"
                 "?url=%s",
                 encodeURL(url) );
        break;
    }

    setUpReceiveBuffer( response, sz );
    http_getBASIC( target, userName, password, response );
    if ( response && *response ) {
        char    *p = strstr( response, "<result" );

        if ( p )
            ret = TRUE;
    }

#if 0
    if ( ret == FALSE ) {
        if ( apiType == DAPI_DELICIOUS ) {
            // private saving �̏ꍇ
            //  -- �G���g���y�[�W���擾
            sprintf( target,
                     "http://del.icio.us/url/%s",
                     encodeURL(url) );
            setUpReceiveBuffer( response, sz );
            http_getBASIC( target, userName, password, response );
            if ( response && *response ) {
                //  -- delete �p URL �𒊏o
                char    *p = strstr( response, "?delete=&amp;key=" );
                if ( p ) {
                    char    delKey[BUFSIZ];
                    char    *q = strchr( p, '"' );
                    if ( q ) {
                        strncpy( delKey, p, q - p );
                        delKey[q - p] = NUL;

                        sprintf( target,
                                 "http://del.icio.us/%s%s",
                                 userName, delKey );

                        //  -- delete ���s
                        http_getBASIC( target, userName, password, response );
                        if ( response && *response ) {
                            ret = TRUE;
                        }
                    }
                }
            }
        }
    }
#endif

    free( response );
    free( target );

    return ( ret );
}


/*
 *  �^�O�̕ύX
 *      API �̏ڍׂ� http://del.icio.us/help/api/tags ���Q��
 */

BOOL
renameTagOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌� */
        const char         *userName,   /* (I) ���[�U��   */
        const char         *password,   /* (I) �p�X���[�h */
        const char         *oldTag,     /* (I) �Â��^�O   */
        const char         *newTag      /* (I) �V�����^�O */
    )
{
    BOOL    ret = FALSE;
    char    url[BUFSIZ * 2];
    char    *response;
    char    *p;
    size_t  sz;

    if ( !oldTag || !(*oldTag) || !newTag || !(*newTag) )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        p = sjis2utf( oldTag );
        sprintf( url,
                 "https://api.del.icio.us/v1/tags/rename"
                 "?old=%s",
                 encodeURL( p ? p : oldTag ) );
        break;

    case DAPI_BLUEDOT:
        p = sjis2utf( oldTag );
        sprintf( url,
              // "https://secure.bluedot.us/v1/tags/rename"
                 "https://secure.faves.com/v1/tags/rename"
                 "?old=%s",
                 encodeURL( p ? p : oldTag ) );
        break;
    }

    p = sjis2utf( newTag );
    sprintf( url + strlen(url), "&new=%s",
             encodeURL( p ? p : newTag ) );

    setUpReceiveBuffer( response, sz );
    http_getBASIC( url, userName, password, response );
    if ( response && *response ) {
        p = strstr( response, "<result" );
        if ( p )
            ret = TRUE;
    }
    free( response );

    return ( ret );
}


/*
 *  �^�O�̍폜
 */

BOOL
removeTagOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�     */
        const char         *userName,   /* (I) ���[�U��       */
        const char         *password,   /* (I) �p�X���[�h     */
        const char         *tag         /* (I) �폜�Ώۂ̃^�O */
    )
{
    BOOL    ret = FALSE;
    char    url[BUFSIZ * 2];
    char    request[2048];
    char    cookie[MAX_COOKIE_LEN];
    char    *response;
    size_t  sz;
    int     r;

    if ( !tag || !(*tag) )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    url[0]    = NUL;
    cookie[0] = NUL;
    sz = MAX_CONTENT_SIZE;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    switch ( apiType ) {
    case DAPI_DELICIOUS:
        r = loginDelicious( userName, password, cookie );
        if ( r )
            sprintf( url,
                     "https://secure.del.icio.us/settings/%s/tags/delete",
                     userName );
        break;

    case DAPI_BLUEDOT:
        /* Blue Dot �ɂ́A���܂̂Ƃ���A���̋@�\�͂Ȃ� */
        break;
    }

    if ( url[0] ) {
        char    *p = sjis2utf( tag );
        sprintf( request,
                 "deltag=%s&"
                 "submit=delete+tag",
                 encodeURL( p ? p : tag ) );
        setUpReceiveBuffer( response, sz );
        http_postEx( url, "application/x-www-form-urlencoded",
                     request, response, cookie );
        if ( *response )
            ret = TRUE;
    }

    free( response );

    return ( ret );
}
