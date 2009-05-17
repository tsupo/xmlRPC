/*
 *  console.c
 *      console 入力関連関数群
 *
 * History:
 * $Log: /comm/xmlRPC/console.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     04/11/29 14:52 Tsujimura543
 * inputNumeric() のプロンプト文字列先頭の改行をやめる
 * 
 * 1     04/11/29 13:24 Tsujimura543
 * コンソール入力関連関数を1つのファイルにまとめる
 */

#include "xmlRPC.h"
#ifdef  WIN32
#include <conio.h>
#endif

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/console.c 1     09/05/14 3:46 tsupo $";
#endif

/* 数値の入力 */
BOOL
inputNumeric( int *num,     /* (O) 入力結果 (数値)      */
              int minimum,  /* (I) 入力可能数値の最小値 */
              int maximum ) /* (I) 入力可能数値の最大値 */
{
    char    *p, *q;
    char    buf[BUFSIZ];
    int     i;
    BOOL    done = FALSE;   /* 目的の数値の入力が完了したか否か */

    fprintf( stderr, "[%d-%d]: 選択してください: ", minimum, maximum );
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


/* yes/no の入力 */
int
inputYesNo( int        *flag,       /* (O) 入力結果 (yes: TRUE, no: FALSE) */
            const char *prompt )    /* (I) プロンプト文字列                */
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
            /* 標準入力がリダイレクトされている場合 */
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


/* 文字列の入力 */
int
inputString( char       *dst,       /* (O) 入力結果 (文字列)          */
             const char *prompt,    /* (I) プロンプト文字列           */
             int        password )  /* (I) パスワード入力モードか否か */
{
    int     done = FALSE;
    int     ret  = 0;
    char    *p, *q, buf[BUFSIZ];

    do {
        fputs( prompt, stderr );

#ifdef  WIN32
        if ( (password == FALSE) || !isatty( fileno( stdin ) ) ) {
            /* 通常入力用 (もしくは標準入力がリダイレクトされている場合) */
            p = fgets( buf, BUFSIZ - 1, stdin );
            if ( !p ) {
                clearerr( stdin );
                continue;
            }
        }
        else {
            /* パスワード入力用 */
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
