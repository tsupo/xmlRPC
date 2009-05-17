/*
 *  漢字コード変換 その2
 *
 *        Copyleft (c) 2005 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  21 Dec 2005
 *
 * History:
 * $Log: /comm/xmlRPC/misc/changeCode2.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 9     08/11/17 21:48 Tsujimura543
 * static → Thread static に変更
 * 
 * 8     07/03/20 0:20 Tsujimura543
 * euc2sjisEx() 内でメモリオーバーランが発生する可能性があったので修正
 * 
 * 7     07/01/17 17:35 Tsujimura543
 * utf2sjisEx() に &ccedil; 関連処理を追加 (Vox 対策)
 * 
 * 6     06/11/15 23:45 Tsujimura543
 * utf2sjisEx() をリファクタリング
 * 
 * 5     06/07/18 20:44 Tsujimura543
 * &raquo; 対策 (はてなブックマークの挙動変更に伴う修正)
 * 
 * 4     06/07/18 17:26 Tsujimura543
 * &raquo; 対策を追加 (はてなブックマークの挙動変更に対応)
 * 
 * 3     06/02/22 16:50 Tsujimura543
 * &raquo; 対策を実施 (暫定)
 * 
 * 2     06/02/08 18:28 Tsujimura543
 * utf2sjisEx() を追加
 * 
 * 1     05/12/21 18:46 Tsujimura543
 * (1) euc2sjis() の機種依存文字対応版 euc2sjisEx() を新規作成
 * (2) 機種依存文字を機種非依存の文字列に置換する regular() を新規作成
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/misc/changeCode2.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

#if 0
#define BUFFER_SIZE 20480
#else
#define BUFFER_SIZE 65536
#endif


/*
 *  「いわゆる機種依存文字」を機種に依存しない代替文字列に置換する
 */

static struct t {
    char    *src;
    char    *dst;
} regex_tbl[] = {
    /* ローマ数字 */
    { "Ⅰ", "I"   }, { "Ⅱ", "II"   }, { "Ⅲ", "III" }, { "Ⅳ", "IV"   },
    { "Ⅴ", "V"   }, { "Ⅵ", "VI"   }, { "Ⅶ", "VII" }, { "Ⅷ", "VIII" },
    { "Ⅸ", "IX"  }, { "Ⅹ", "X"    }, { "ⅰ", "i"   }, { "ⅱ", "ii"   },
    { "ⅲ", "iii" }, { "ⅳ", "iv"   }, { "ⅴ", "v"   }, { "ⅵ", "vi"   },
    { "ⅶ", "vii" }, { "ⅷ", "viii" }, { "ⅸ", "ix"  }, { "ⅹ", "x"    },

    /* 丸付き数字 */
    { "①", "(1)"  }, { "②", "(2)"  }, { "③", "(3)"  }, { "④", "(4)"  },
    { "⑤", "(5)"  }, { "⑥", "(6)"  }, { "⑦", "(7)"  }, { "⑧", "(8)"  },
    { "⑨", "(9)"  }, { "⑩", "(10)" }, { "⑪", "(11)" }, { "⑫", "(12)" },
    { "⑬", "(13)" }, { "⑭", "(14)" }, { "⑮", "(15)" }, { "⑯", "(16)" },
    { "⑰", "(17)" }, { "⑱", "(18)" }, { "⑲", "(19)" }, { "⑳", "(20)" },

    /* その他、特殊文字 */
    { "㍾", "明治" }, { "㍽", "大正" }, { "㍼", "昭和" }, { "㍻", "平成" },
    { "㍉", "ミリ" }, { "㌢", "センチ" }, { "㌔", "キロ" },
    { "㍍", "メートル"   },
    { "㌘", "グラム"     }, { "㌧", "トン" },
    { "㍑", "リットル"   },
    { "㌶", "ヘクタール" }, { "㌃", "アール" },
    { "㍊", "ミリバール" },
    { "㍗", "ワット"     },
    { "㌍", "カロリー"   },
    { "㌫", "パーセント" },
    { "㌦", "ドル"       }, { "㌣", "セント" },
    { "㌻", "ページ"     },
    { "㈱", "(株)" }, { "㈹", "(代)" }, { "㈲", "(有)" }, 
    { "㊤", "(上)" }, { "㊥", "(中)" }, { "㊦", "(下)" },
    { "㊧", "(左)" }, { "㊨", "(右)" },
    { "㎜", "mm" }, { "㎝", "cm" }, { "㎞", "km" },
    { "㎎", "mg" }, { "㎏", "kg" },
    { "㏄", "cc" },
    { "㎡", "m2" },
    { "№", "No." },
    { "㏍", "KK" },
    { "℡", "TEL" },
    { "〝", "“" }, { "〟", "”" },

    { NULL, NULL}
};

char    *
regular( char *s )
{
    char    *p;
    char    *q;
    int     i, j;
    int     len1;
    int     len2;

    p = s;
    while ( *p ) {
        do {
            while ( *p && ( *((unsigned char *)p) <= 0x7f) )
                p++;
            if ( !(*p) )
                break;

            for ( i = 0; regex_tbl[i].src != NULL; i++ ) {
                if ( !strncmp( p, regex_tbl[i].src, 2 ) ) {
                    len1 = strlen( regex_tbl[i].src );
                    len2 = strlen( regex_tbl[i].dst );

                    if ( len1 > len2 ) {
                        strncpy( p, regex_tbl[i].dst, len2 );
                        strcpy( p + len2, p + len1 );
                        p += len2;
                        p--;
                        break;
                    }
                    else if ( len1 == len2 ) {
                        for ( j = 0; j < len1; j++ )
                            *p++ = regex_tbl[i].dst[j++];
                        p--;
                        break;
                    }

                    q = &(p[strlen(p)]);
                    while ( q > p ) {
                        *(q + (len2 - len1)) = *q;
                        q--;
                    }
                    strncpy( p, regex_tbl[i].dst, len2 );
                    p += len2;
                    p--;
                    break;
                }
            }
            if ( regex_tbl[i].src == NULL )
                p++;
            p++;
        } while ( *p );
    }

    return ( s );
}


/*
 * GNU iconv に頼らない文字コード変換処理
 *      iconv による変換失敗時(いわゆる機種依存文字などが含まれる場合)に
 *      使用する
 */

static void
__euc2sjis( unsigned char *c1, unsigned char *c2 )
{
    /* まず、2バイト目を変換 */
    if ( ( *c1 % 2 ) == 0 )
        *c2 -= 0x02;
    else {
        *c2 -= 0x61;
        if( *c2 > 0x7E )
            *c2 += 0x01;
    }

    /* 次に、1バイト目を変換 */
    if ( *c1 < 0xDF )
        *c1 = (unsigned char)(((*c1 + 1) / 2) + 0x30);
    else
        *c1 = (unsigned char)(((*c1 + 1) / 2) + 0x70);
}

static char *
_euc2sjis( char *s )
{
    unsigned char   c1, c2 = 0;
    char            *t = s;

    while ( *t ) {
        c1 = (unsigned char)(*t++);
        if ( c1 <  0x80 )
            continue;
        c2 = (unsigned char)(*t++);
        if ( c1 == 0x8E )
            continue;

        __euc2sjis( &c1, &c2 );
        *(t - 2) = c1;
        *(t - 1) = c2;
    }

    return ( s );
}

char    *
euc2sjisEx( const char *p )
{
    Thread static char      *outbuf = NULL;
    Thread static size_t    sz = BUFFER_SIZE * 2 + 1;
    size_t                  len;

    if ( !p ) {
        if ( outbuf )
            free( outbuf );
        outbuf = NULL;

        return ( NULL );
    }
    len = strlen( p ) + BUFSIZ + 1;

    if ( !outbuf ) {
        sz = len > sz ? len : sz;
        outbuf = (char *)malloc( sz );
    }
    else if ( len > sz ) {
        char    *q;

        sz = len;
        q = (char *)realloc( outbuf, sz );
        if ( q )
            outbuf = q;
    }

    if ( !outbuf )
        return ( NULL );

    memset( outbuf, 0x00, sz );
    strcpy( outbuf, p );
    _euc2sjis( outbuf );
    regular( outbuf );

    return ( outbuf );
}


char    *
utf2sjisEx( char *s )
{
    char            *p = s, *q;
    char            temp[8];
    char            *buf;
    int             origLen;
    unsigned char   b;

    q = utf2sjis( p );
    if ( q )
        return ( q );

    origLen = strlen( s );
    buf = (char *)malloc( origLen + 1 );
    if ( !buf )
        return ( s );
    buf[0] = NUL;

    while ( *p ) {
        b = (unsigned char)(*p);
        if ( b <= 0x7f ) {
            temp[0] = *p++;
            temp[1] = NUL;
            q = temp;
        }
        else if ( b == 0xbb ) {
            p++;
            q = "≫";
        }
        else if ( b == 0xab ) {
            p++;
            q = "≪";
        }
        else if ( (b >= 0xc0) && (b <= 0xdf) ) {
            temp[0] = *p++;
            temp[1] = *p++;
            temp[2] = NUL;
            if ( ((unsigned char)(temp[0]) == 0xC2) &&
                 ((unsigned char)(temp[1]) == 0xBB)    )
#if 0
                q = "&raquo;"; // &#187; → 160 + 16 + 11 = BB
#else
                q = "≫";
#endif
            else
            if ( ((unsigned char)(temp[0]) == 0xC2) &&
                 ((unsigned char)(temp[1]) == 0xAB)    )
#if 0
                q = "&laquo;"; // &#171; → 160 + 11 = AB
#else
                q = "≪";
#endif
            else
            if ( ((unsigned char)(temp[0]) == 0xC3) &&
                 ((unsigned char)(temp[1]) == 0xA7)    )
#if 0
                q = "&ccedil;"; // &#231; → 160 + 64 + 7 = A7
#else
                q = "c";
#endif
            else
                q = utf2sjis( temp );
        }
        else if ( (b >= 0xe0) && (b <= 0xef) ) {
            temp[0] = *p++;
            temp[1] = *p++;
            temp[2] = *p++;
            temp[3] = NUL;
            q = utf2sjis( temp );
            if ( !q ) {
                if ( ((unsigned char)(temp[0]) == 0xEF) &&
                     ((unsigned char)(temp[1]) == 0xBF) &&
                     ((unsigned char)(temp[2]) == 0xBD)    )
                    q = "&raquo;";
            }
        }
        else if ( (b >= 0xf0) && (b <= 0xf7) ) {
            temp[0] = *p++;
            temp[1] = *p++;
            temp[2] = *p++;
            temp[3] = *p++;
            temp[4] = NUL;
            q = utf2sjis( temp );
        }
        else {
            q = NULL;
            p++;
        }
        if ( q ) {
            int len = strlen(buf) + strlen(q);
            if ( len > origLen ) {
                char    *buf2 = (char *)malloc( len * 2 + 1 );
                if ( buf2 ) {
                    strcpy( buf2, buf );
                    free( buf );
                    buf = buf2;
                    origLen = len * 2;
                }
                else
                    break;
            }
            strcat( buf, q );
        }
    }

    strcpy( s, buf );
    free( buf );

    return ( s );
}
