/*
 *  console.c
 *      console ���͊֘A�֐��Q
 *
 * History:
 * $Log: /comm/xmlRPC/console.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     04/11/29 14:52 Tsujimura543
 * inputNumeric() �̃v�����v�g������擪�̉��s����߂�
 * 
 * 1     04/11/29 13:24 Tsujimura543
 * �R���\�[�����͊֘A�֐���1�̃t�@�C���ɂ܂Ƃ߂�
 */

#include "xmlRPC.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/console.c 1     09/05/14 3:46 tsupo $";
#endif

/* ���l�̓��� */
BOOL
inputNumeric( int *num,     /* (O) ���͌��� (���l)      */
              int minimum,  /* (I) ���͉\���l�̍ŏ��l */
              int maximum ) /* (I) ���͉\���l�̍ő�l */
{
    char    *p, *q;
    char    buf[BUFSIZ];
    int     i;
    BOOL    done = FALSE;   /* �ړI�̐��l�̓��͂������������ۂ� */

    fprintf( stderr, "[%d-%d]: �I�����Ă�������: ", minimum, maximum );
    p = fgets( buf, BUFSIZ - 1, stdin );
    if ( !p ) {
        clearerr( stdin );
    }
    else {
        while ( (*p == ' ') || (*p == '\t') )
            p++;
        q = p;
        while ( *q )
            q++;
        q--;
        while ( (q > p) &&
                ((*q == '\n') || (*q == '\r') ||
                 (*q == ' ')  || (*q == '\t')    ) ) {
            *q-- = NUL;
        }
        if ( p && *p && (q >= p) ) {
            i = atol( p );
            if ( (i >= minimum) && (i <= maximum) ) {
                done = TRUE;
                *num = i;
            }
        }
    }

    return ( done );
}


/* yes/no �̓��� */
int
inputYesNo( int        *flag,       /* (O) ���͌��� (yes: TRUE, no: FALSE) */
            const char *prompt )    /* (I) �v�����v�g������                */
{
    int     done = FALSE;
    int     ret  = 0;
    char    *p, *q, buf[BUFSIZ];
#ifdef  WIN32
    int     c, i = 0;
#endif

    do {
        fputs( prompt, stderr );
        fputs( " (y/n) ", stderr );

#ifdef  WIN32
        if ( !isatty( fileno( stdin ) ) ) {
            /* �W�����͂����_�C���N�g����Ă���ꍇ */
            p = fgets( buf, BUFSIZ - 1, stdin );
            if ( !p ) {
                clearerr( stdin );
                continue;
            }
        }
        else {
            i = 0;
            do {
                c = getch();
                if ( c == '\r' ) {
                    putch( '\r' );
                    putch( '\n' );

                    /* for Windows 95, Windows 98 */
                    while ( kbhit() )
                        getch();
                    break;
                }
                if ( c == '\b' ) {
                    if ( i > 0) {
                        i--;
                        putch( '\b' );
                        putch( ' ' );
                        putch( '\b' );
                    }
                    continue;
                }
                if ( (i >= 1)         ||
                     ((c != 'y') &&
                      (c != 'Y') &&
                      (c != 'n') &&
                      (c != 'N')    )    ) {
                    continue;
                }

                buf[i] = (char)(c & 0xFF);
                i++;
                putch( c );
            } while ( i < BUFSIZ - 1 );
            buf[i] = NUL;
            p = buf;
        }
#else
        p = fgets( buf, BUFSIZ - 1, stdin );
        if ( !p ) {
            clearerr( stdin );
            continue;
        }
#endif

        while ( (*p == ' ') || (*p == '\t') )
            p++;
        q = p;
        while ( *q )
            q++;
        q--;
        while ( (q > p) &&
                ((*q == '\n') || (*q == '\r') ||
                 (*q == ' ')  || (*q == '\t')    ) ) {
            *q-- = NUL;
        }
        if ( p && *p && (q >= p) ) {
            if ( (*p == 'y') || (*p == 'Y') ) {
                *flag = TRUE;
                done = TRUE;
            }
            else if ( (*p == 'n') || (*p == 'N') ) {
                *flag = FALSE;
                done = TRUE;
            }
        }
    } while ( done == FALSE );

    return ( ret );
}


/* ������̓��� */
int
inputString( char       *dst,       /* (O) ���͌��� (������)          */
             const char *prompt,    /* (I) �v�����v�g������           */
             int        password )  /* (I) �p�X���[�h���̓��[�h���ۂ� */
{
    int     done = FALSE;
    int     ret  = 0;
    char    *p, *q, buf[BUFSIZ];

    do {
        fputs( prompt, stderr );

#ifdef  WIN32
        if ( (password == FALSE) || !isatty( fileno( stdin ) ) ) {
            /* �ʏ���͗p (�������͕W�����͂����_�C���N�g����Ă���ꍇ) */
            p = fgets( buf, BUFSIZ - 1, stdin );
            if ( !p ) {
                clearerr( stdin );
                continue;
            }
        }
        else {
            /* �p�X���[�h���͗p */
            int     c, i = 0;

            do {
                c = getch();
                if ( c == '\r' ) {
                    putch( '\r' );
                    putch( '\n' );

                    /* for Windows 95, Windows 98 */
                    while ( kbhit() )
                        getch();
                    break;
                }
                if ( c == '\b' ) {
                    if ( i > 0) {
                        i--;
                        putch( '\b' );
                        putch( ' ' );
                        putch( '\b' );
                    }
                    continue;
                }
                if ( c < ' ' ) {
                    continue;
                }

                buf[i] = (char)(c & 0xFF);
                i++;
                putch( '*' );
            } while ( i < BUFSIZ - 1 );
            buf[i] = NUL;
            p = buf;
        }
#else
        p = fgets( buf, BUFSIZ - 1, stdin );
        if ( !p ) {
            clearerr( stdin );
            continue;
        }
#endif

        while ( (*p == ' ') || (*p == '\t') )
            p++;

        if ( (*p == '\n') || (*p == '\r') )
            continue;

        q = p;
        while ( *q )
            q++;
        q--;
        while ( (q > p) &&
                ((*q == '\n') || (*q == '\r') ||
                 (*q == ' ')  || (*q == '\t')    ) ) {
            *q-- = NUL;
        }
        if ( p && *p && (q >= p) ) {
            strcpy( dst, p );
            done = TRUE;
        }
    } while ( done == FALSE );

    return ( ret );
}
