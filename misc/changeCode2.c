/*
 *  �����R�[�h�ϊ� ����2
 *
 *        Copyleft (c) 2005 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  21 Dec 2005
 *
 * History:
 * $Log: /comm/xmlRPC/misc/changeCode2.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 9     08/11/17 21:48 Tsujimura543
 * static �� Thread static �ɕύX
 * 
 * 8     07/03/20 0:20 Tsujimura543
 * euc2sjisEx() ���Ń������I�[�o�[��������������\�����������̂ŏC��
 * 
 * 7     07/01/17 17:35 Tsujimura543
 * utf2sjisEx() �� &ccedil; �֘A������ǉ� (Vox �΍�)
 * 
 * 6     06/11/15 23:45 Tsujimura543
 * utf2sjisEx() �����t�@�N�^�����O
 * 
 * 5     06/07/18 20:44 Tsujimura543
 * &raquo; �΍� (�͂Ăȃu�b�N�}�[�N�̋����ύX�ɔ����C��)
 * 
 * 4     06/07/18 17:26 Tsujimura543
 * &raquo; �΍��ǉ� (�͂Ăȃu�b�N�}�[�N�̋����ύX�ɑΉ�)
 * 
 * 3     06/02/22 16:50 Tsujimura543
 * &raquo; �΍�����{ (�b��)
 * 
 * 2     06/02/08 18:28 Tsujimura543
 * utf2sjisEx() ��ǉ�
 * 
 * 1     05/12/21 18:46 Tsujimura543
 * (1) euc2sjis() �̋@��ˑ������Ή��� euc2sjisEx() ��V�K�쐬
 * (2) �@��ˑ��������@���ˑ��̕�����ɒu������ regular() ��V�K�쐬
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
 *  �u������@��ˑ������v���@��Ɉˑ����Ȃ���֕�����ɒu������
 */

static struct t {
    char    *src;
    char    *dst;
} regex_tbl[] = {
    /* ���[�}���� */
    { "�T", "I"   }, { "�U", "II"   }, { "�V", "III" }, { "�W", "IV"   },
    { "�X", "V"   }, { "�Y", "VI"   }, { "�Z", "VII" }, { "�[", "VIII" },
    { "�\", "IX"  }, { "�]", "X"    }, { "�@", "i"   }, { "�A", "ii"   },
    { "�B", "iii" }, { "�C", "iv"   }, { "�D", "v"   }, { "�E", "vi"   },
    { "�F", "vii" }, { "�G", "viii" }, { "�H", "ix"  }, { "�I", "x"    },

    /* �ەt������ */
    { "�@", "(1)"  }, { "�A", "(2)"  }, { "�B", "(3)"  }, { "�C", "(4)"  },
    { "�D", "(5)"  }, { "�E", "(6)"  }, { "�F", "(7)"  }, { "�G", "(8)"  },
    { "�H", "(9)"  }, { "�I", "(10)" }, { "�J", "(11)" }, { "�K", "(12)" },
    { "�L", "(13)" }, { "�M", "(14)" }, { "�N", "(15)" }, { "�O", "(16)" },
    { "�P", "(17)" }, { "�Q", "(18)" }, { "�R", "(19)" }, { "�S", "(20)" },

    /* ���̑��A���ꕶ�� */
    { "��", "����" }, { "��", "�吳" }, { "��", "���a" }, { "�~", "����" },
    { "�_", "�~��" }, { "�a", "�Z���`" }, { "�`", "�L��" },
    { "�b", "���[�g��"   },
    { "�c", "�O����"     }, { "�d", "�g��" },
    { "�g", "���b�g��"   },
    { "�f", "�w�N�^�[��" }, { "�e", "�A�[��" },
    { "�m", "�~���o�[��" },
    { "�h", "���b�g"     },
    { "�i", "�J�����["   },
    { "�l", "�p�[�Z���g" },
    { "�j", "�h��"       }, { "�k", "�Z���g" },
    { "�n", "�y�[�W"     },
    { "��", "(��)" }, { "��", "(��)" }, { "��", "(�L)" }, 
    { "��", "(��)" }, { "��", "(��)" }, { "��", "(��)" },
    { "��", "(��)" }, { "��", "(�E)" },
    { "�o", "mm" }, { "�p", "cm" }, { "�q", "km" },
    { "�r", "mg" }, { "�s", "kg" },
    { "�t", "cc" },
    { "�u", "m2" },
    { "��", "No." },
    { "��", "KK" },
    { "��", "TEL" },
    { "��", "�g" }, { "��", "�h" },

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
 * GNU iconv �ɗ���Ȃ������R�[�h�ϊ�����
 *      iconv �ɂ��ϊ����s��(������@��ˑ������Ȃǂ��܂܂��ꍇ)��
 *      �g�p����
 */

static void
__euc2sjis( unsigned char *c1, unsigned char *c2 )
{
    /* �܂��A2�o�C�g�ڂ�ϊ� */
    if ( ( *c1 % 2 ) == 0 )
        *c2 -= 0x02;
    else {
        *c2 -= 0x61;
        if( *c2 > 0x7E )
            *c2 += 0x01;
    }

    /* ���ɁA1�o�C�g�ڂ�ϊ� */
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
            q = "��";
        }
        else if ( b == 0xab ) {
            p++;
            q = "��";
        }
        else if ( (b >= 0xc0) && (b <= 0xdf) ) {
            temp[0] = *p++;
            temp[1] = *p++;
            temp[2] = NUL;
            if ( ((unsigned char)(temp[0]) == 0xC2) &&
                 ((unsigned char)(temp[1]) == 0xBB)    )
#if 0
                q = "&raquo;"; // &#187; �� 160 + 16 + 11 = BB
#else
                q = "��";
#endif
            else
            if ( ((unsigned char)(temp[0]) == 0xC2) &&
                 ((unsigned char)(temp[1]) == 0xAB)    )
#if 0
                q = "&laquo;"; // &#171; �� 160 + 11 = AB
#else
                q = "��";
#endif
            else
            if ( ((unsigned char)(temp[0]) == 0xC3) &&
                 ((unsigned char)(temp[1]) == 0xA7)    )
#if 0
                q = "&ccedil;"; // &#231; �� 160 + 64 + 7 = A7
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
