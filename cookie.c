/*
 *  cookie.c
 *      cookie �֘A�֐��Q
 *
 * History:
 * $Log: /comm/xmlRPC/cookie.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 23    08/11/17 21:56 Tsujimura543
 * static �� Thread static �ɕύX
 * 
 * 22    07/09/26 13:51 Tsujimura543
 * CV_t �𓱓����A�\�[�X�𐮗�
 * 
 * 21    07/09/26 13:46 Tsujimura543
 * �ulivedoor Blog �����b�菈���v�� livedoor Blog �ȊO�ɂ��K�p����
 * �悤�ɂ���
 * 
 * 20    06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 19a   06/09/03 15:51 tsupo
 * assert �����Ă݂�
 * 
 * 19    06/03/10 18:18 Tsujimura543
 * joinCookie() ���C�� (cookieNew �� cookieOld �̗����ɓ������O��
 * �p�����[�^������ꍇ�A�V�������̒l���Â����̒l�ŏ㏑�����Ă���
 * �̂��A�Â����̒l��V�������̒l�ŏ㏑������悤�ɏC������)
 * 
 * 18    06/03/07 23:06 Tsujimura543
 * path �� domain �͊��S�ɍ폜����悤�ɂ��Ă݂�
 * 
 * 17    06/02/21 21:48 Tsujimura543
 * [����] path �͊��S�ɍ폜���Ă��܂��Ă��\��Ȃ�?
 * 
 * 16    06/02/21 21:42 Tsujimura543
 * Cookie �������ɒ����Ȃ��Ă����̂�h�����߁A path=/; ���폜����悤�ɂ���
 * 
 * 15    06/02/21 1:41 Tsujimura543
 * �ꕔ�̃T�C�g�Ɋւ��Ďb��I�� cookie ���̓��ʂȏ��������Ă����̂�
 * ���S�ɔp�~
 * 
 * 14    06/02/21 1:32 Tsujimura543
 * Expire �̐���N��2���\�L�ł���ꍇ�ɂ������������ł���悤�ɂ���
 * 
 * 13    06/02/06 12:10 Tsujimura543
 * joinCookie() ���C�� (�ҏW��� cookie �𔽉f�����Ɏ̂ĂĂ��܂��Ă���)
 * 
 * 12    06/01/27 0:09 Tsujimura543
 * joinCookie() ���C�� (Cookie �����񂪍ی��Ȃ������Ȃ��Ă����s����C��)
 * 
 * 11    06/01/26 17:10 Tsujimura543
 * 2�� cookie �����̂�����֐���ǉ�
 * 
 * 10    06/01/25 21:28 Tsujimura543
 * (1) expires ���`�F�b�N����悤�ɂ���
 * (2) livedoor Blog �����b�菈����ǉ�
 * 
 * 9     05/04/21 15:09 Tsujimura543
 * �y�V�L��ɑΉ��ł���悤�ɁAsaveCookie() �𒆐S�ɏC�������{
 * 
 * 8     04/11/26 20:52 Tsujimura543
 * �E�F�u���u���O�Ή�
 * 
 * 7     04/11/25 10:07 Tsujimura543
 * �G�R���O�Ή�
 * 
 * 6     04/10/08 20:29 Tsujimura543
 * �L�k�K�T�����L�Ή�
 * 
 * 5     04/10/08 12:18 Tsujimura543
 * excite�u���O�ɂ��K�p����悤�ɂ���
 * 
 * 4     04/09/28 13:54 Tsujimura543
 * �A���[�o�u���O�Ή�
 * 
 * 3     04/09/02 20:40 Tsujimura543
 * getCookie() �� httpPost.c ����ړ�
 * 
 * 2     04/09/02 15:44 Tsujimura543
 * ���t�@�N�^�����O�����{
 * 
 * 1     04/09/02 15:41 Tsujimura543
 * �V�K�쐬
 */

#include "xmlRPC.h"
#include <time.h>
#include <assert.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/cookie.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

typedef struct cookieValuable   CV_t;

#define COOKIE_UNIT 80

/* cookie���i�[�̈�̊m�� */
COOKIE_INFO *
createCookie()
{
    COOKIE_INFO *p;

    p = (COOKIE_INFO *)malloc( sizeof ( COOKIE_INFO ) );
    if ( !p )
        return ( NULL );

    p->valuable = (CV_t *)malloc( sizeof ( CV_t ) * COOKIE_UNIT );
    if ( !(p->valuable) ) {
        free( (void *)p );
        return ( NULL );
    }

    p->maxNumOfValuables = COOKIE_UNIT;
    p->numOfValuables    = 0;

    memset( p->valuable, 0x00, sizeof ( CV_t ) * COOKIE_UNIT );

    return ( p );
}


/* cookie���i�[�̈�̊g�� */
COOKIE_INFO *
reallocCookie( COOKIE_INFO *p )
{
    CV_t    *vp;

    if ( !p )
        return ( NULL );
    p->maxNumOfValuables += COOKIE_UNIT;
    vp = (CV_t *)malloc( sizeof ( CV_t ) * p->maxNumOfValuables );
    if ( vp ) {
        memcpy( vp, p->valuable,
                sizeof ( CV_t ) * (p->maxNumOfValuables - COOKIE_UNIT) );
        free( (void *)(p->valuable) );
        p->valuable = vp;
    }

    return ( p );
}


/* cookie���i�[�̈�̉�� */
void
destroyCookie( COOKIE_INFO *p )
{
    if ( !p )
        return;

    if ( p->valuable )
        free( (void *)(p->valuable) );
    free( (void *)p );
}


/* cookie �̕ۑ� */
char    *
saveCookie( COOKIE_INFO *cp, const char *cookie )
{
    Thread static char  newCookie[10240];
    const char          *p, *q, *r;
    CV_t                tmp;
    int                 found, done, i;

    if ( !cp )
        return ( NULL );

    p = strstr( cookie, ": " );
    if ( p )
        p += 2;
    else
        p = cookie;

    do {
        found = FALSE;
        done  = FALSE;
        q = strchr( p, ';' );
        if ( q ) {
            r = strchr( p, '=' );
            if ( r && (r < q ) ) {
                char    *s = strstr( q + 1, "secure;" );
                if ( s )
                    q = s + 6; /* "secure"(6�o�C�g)�����Z */

                strncpy( tmp.name,  p, r - p );
                tmp.name[r - p] = NUL;
                r++;
                strncpy( tmp.value, r, q - r );
                tmp.value[q - r] = NUL;
                found = TRUE;
            }
            p = q + 1;
            while ( *p == ' ' )
                p++;
        }
        else {
            done = TRUE;
            r = strchr( p, '=' );
            if ( r ) {
                strncpy( tmp.name,  p, r - p );
                tmp.name[r - p] = NUL;
                r++;
                while ( (*(r + (strlen( r ) - 1)) == '\r') ||
                        (*(r + (strlen( r ) - 1)) == '\n')    ) {
                    *(char *)(r + (strlen( r ) - 1)) = NUL;
                }
                strcpy( tmp.value, r );
                found = TRUE;

                p = r + strlen( r );
            }
        }

        if ( found ) {
            if ( (stricmp( tmp.name, "path"   ) != 0) &&
                 (stricmp( tmp.name, "domain" ) != 0)    ) {
                /* path �� domain �ȊO�Ɋւ��ẮA�d��������̂�����ꍇ�A */
                /* �ォ��o���������ŏ㏑������                            */
                int rewritten = FALSE;

                for ( i = 0; i < cp->numOfValuables; i++ ) {
                    if ( !strcmp( cp->valuable[i].name, tmp.name ) ) {
                        strcpy( cp->valuable[i].value, tmp.value );
                        rewritten = TRUE;
                        break;
                    }
                }

                if ( !rewritten ) {
                    if ( cp->numOfValuables == cp->maxNumOfValuables )
                        cp = reallocCookie( cp );
                    strcpy(cp->valuable[cp->numOfValuables].name,  tmp.name );
                    strcpy(cp->valuable[cp->numOfValuables].value, tmp.value);
                    (cp->numOfValuables)++;
                }
            }
            /*
            else {
                if ( cp->numOfValuables == cp->maxNumOfValuables )
                    cp = reallocCookie( cp );
                strcpy(cp->valuable[cp->numOfValuables].name,  tmp.name );
                strcpy(cp->valuable[cp->numOfValuables].value, tmp.value);
                (cp->numOfValuables)++;
            }
            */
        }
    } while ( *p && !done );

    return ( loadCookie( cp ) );
}


/* cookie �̎擾 */
char    *
loadCookie( const COOKIE_INFO *cp )
{
    Thread static char  newCookie[10240];
    int                 i;

    strcpy( newCookie, "Cookie: " );
    for ( i = 0; i < cp->numOfValuables; i++ ) {
        if ( i > 0 )
            strcat( newCookie, "; " );
        sprintf( newCookie + strlen( newCookie ),
                 "%s=%s",
                 cp->valuable[i].name, cp->valuable[i].value );
    }
    strcat( newCookie, "\r\n" );

    assert( strlen(newCookie) < MAX_COOKIE_LEN );

    return ( newCookie );
}


static BOOL
checkExpire( const char *p )
{
    /* �����؂ꂩ�ǂ����̃`�F�b�N */
    const char  *q = strstr( p, "\r\n" );
    const char  *r;
    time_t      t;
    struct tm   *tm;
    int         yyyyC, mmC, ddC, HHC, MMC, SSC;
    int         yyyyE, mmE, ddE, HHE, MME, SSE;

    if ( !q )
        q = strchr( p, '\n' );
    if ( !q )
        q = strchr( p, '\r' );
    if ( !q )
        return ( FALSE );
    r = strstr( p, "expires=" );
    if ( !r )
        r = strstr( p, "Expires=" );
    if ( !r || (r > q) )
        return ( FALSE );

    /* expires=Thu, 23-Feb-2006 05:16:29 GMT */
    p = r + 8;
    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    ddE = atol( p );

    while ( ((*p < 'A') || (*p > 'S')) && (p < q) )
        p++;
    if ( !strncmp( p, "Jan", 3 ) )
        mmE = 1;
    else if ( !strncmp( p, "Feb", 3 ) )
        mmE = 2;
    else if ( !strncmp( p, "Mar", 3 ) )
        mmE = 3;
    else if ( !strncmp( p, "Apr", 3 ) )
        mmE = 4;
    else if ( !strncmp( p, "May", 3 ) )
        mmE = 5;
    else if ( !strncmp( p, "Jun", 3 ) )
        mmE = 6;
    else if ( !strncmp( p, "Jul", 3 ) )
        mmE = 7;
    else if ( !strncmp( p, "Aug", 3 ) )
        mmE = 8;
    else if ( !strncmp( p, "Sep", 3 ) )
        mmE = 9;
    else if ( !strncmp( p, "Oct", 3 ) )
        mmE = 10;
    else if ( !strncmp( p, "Nov", 3 ) )
        mmE = 11;
    else if ( !strncmp( p, "Dec", 3 ) )
        mmE = 12;
    else
        return ( FALSE );

    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    yyyyE = atol( p );
    if ( yyyyE < 100 )
        yyyyE += 2000;

    while ( ((*p >= '0') && (*p <= '9')) && (p < q) )
        p++;
    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    HHE = atol( p );

    while ( ((*p >= '0') && (*p <= '9')) && (p < q) )
        p++;
    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    MME = atol( p );

    while ( ((*p >= '0') && (*p <= '9')) && (p < q) )
        p++;
    while ( ((*p < '0') || (*p > '9')) && (p < q) )
        p++;
    if ( p >= q )
        return ( FALSE );
    SSE = atol( p );

    /* ���ݎ������擾 */
    t  = time( NULL );
    tm = gmtime( &t );  /* GMT */
    yyyyC = tm->tm_year + 1900;
    mmC   = tm->tm_mon + 1;
    ddC   = tm->tm_mday;
    HHC   = tm->tm_hour;
    MMC   = tm->tm_min;
    SSC   = tm->tm_sec;

    /* ���ݎ����� expire �������r */
    if ( yyyyE < yyyyC )
        return ( TRUE );    /* �����؂� */
    if ( yyyyE > yyyyC )
        return ( FALSE );

    if ( mmE < mmC )
        return ( TRUE );    /* �����؂� */
    if ( mmE > mmC )
        return ( FALSE );

    if ( ddE < ddC )
        return ( TRUE );    /* �����؂� */
    if ( ddE > ddC )
        return ( FALSE );

    if ( HHE < HHC )
        return ( TRUE );    /* �����؂� */
    if ( HHE > HHC )
        return ( FALSE );

    if ( MME < MMC )
        return ( TRUE );    /* �����؂� */
    if ( MME > MMC )
        return ( FALSE );

    if ( SSE < SSC )
        return ( TRUE );    /* �����؂� */
    if ( SSE > SSC )
        return ( FALSE );

    return ( TRUE );        /* �����؂� */
}

/*
 *  Web�T�[�o����󂯎���� http �����d������ cookie �����o��
 */

char    *
getCookie( char *cookie )
{
    char    *p = cookie, *q, *r;
    char    *temp = (char *)malloc( strlen( p ) );
    BOOL    skip  = FALSE;
    BOOL    first = TRUE;

    if ( !temp )
        return ( NULL );

    r = temp;
    while ( ( q = strstr( p, "Set-Cookie: " ) ) != NULL ) {
        if ( checkExpire( q + 12 ) ) {
            /* �����؂�̏ꍇ */
            p = q + 12;
            continue;   /* �������� */
        }
        skip = FALSE;
        if ( first ) {
            q += 4; /* "Set-" �������̂Ă� */
            first = FALSE;
        }
        else {
            *r++ = ';';
            *r++ = ' ';
            q += 12;/* "Set-Cookie: " �������̂Ă� */
        }
        while ( *q && (*q != '\n') && (*q != '\r') ) {
            if ( !skip && (*q == ';') ) {
                /* "; expire=XXXX" �������̂Ă� */
                if ( !strncmpi( q + 1, " expires=", 9 ) ) {
                    skip = TRUE;
                    q += 9;
                }
                else if ( !strncmpi( q + 1, " domain=", 7 ) ) {
                    /* "; domain=XXXX" �������̂Ă� */
                    skip = TRUE;
                    q += 7;
                }
                else if ( !strncmpi( q + 1, " path=", 5 ) ) {
                    /* "; path=XXXX" �������̂Ă� */
                    skip = TRUE;
                    q += 5;
                }
            }
            if ( !skip )
                *r++ = *q;
            q++;
        }
        p = q;
    }
    if ( !first ) {
        *r++ = '\r';
        *r++ = '\n';
    }
    *r = '\0';

    p = temp;
    while ( ( q = strstr( p, "path=/; " ) ) != NULL )
        strcpy( q, q + 8 );

    strcpy( cookie, temp );
    free( temp );

    return ( cookie );
}

char    *
joinCookie( char *cookieNew, const char *cookieOld )
{
    COOKIE_INFO *cp;
    char        *p, *q, *r;
    int         cnt = 0;
    size_t      len = strlen( cookieNew ) + strlen( cookieOld );

    assert( len < MAX_COOKIE_LEN );

    r = (char *)malloc( len + 1 );
    if ( r ) {
        /* cookieNew := cookieOld + cookieNew */
        strcpy( r, cookieOld );
        p = &(r[strlen(r) - 2]);
        q = strstr( cookieNew, ": " );
        if ( p && q ) {
            *p++ = ';';
            *p++ = ' ';
            *p   = NUL;
            q += 2;
            strcpy( p, q );
            strcpy( cookieNew, r );
            free( r );
        }
    }
    else {
#if 0
        /* cookieNew := cookieNew + cookieOld */
        p = &(cookieNew[strlen(cookieNew) - 2]);
        q = strstr( cookieOld, ": " );
        if ( p && q ) {
            *p++ = ';';
            *p++ = ' ';
            *p   = NUL;
            q += 2;
            strcpy( p, q );
        }
#else
        return ( cookieNew );
#endif
    }

    p = cookieNew;
    r = p + (strlen( p ) - 1);
    while ( ( q = strchr( p, ';' ) ) != NULL ) {
        cnt++;
        p = q + 1;
        if ( p >= r )
            break;
    }

    if ( cnt > 1 ) {
        cp = (COOKIE_INFO *)createCookie();
        p = saveCookie( cp, cookieNew );
        if ( p )
            strcpy( cookieNew, p );
        destroyCookie( cp );
    }

    return ( cookieNew );
}
