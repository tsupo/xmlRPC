/*
 *  decodeURL.c         tsupo@na.rim.or.jp
 *          by H. Tsujimura     August 1996
 *
 *  Copyright (c) 1996,1997,2003 by Hiroshi Tsujimura
 *  All Rights Reserved.
 *
 * History :
 * $Log: /comm/xmlRPC/misc/decodeURL.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 12    08/11/17 21:56 Tsujimura543
 * static �� Thread static �ɕύX
 * 
 * 11    08/05/20 22:49 Tsujimura543
 * hatenaApi.c �� searchKeyword() �o�R�ŌĂяo���ꂽ�Ƃ��ɁA���炩��
 * �������j�󂪌����ŗ����錻�ۂɑ΂��鉞�}���u�����{
 * 
 * 10    07/07/03 11:18 Tsujimura543
 * Visual Studio 2005 �ł̃r���h���ʂ𔽉f
 * 
 * 9     07/02/21 19:02 Tsujimura543
 * �����o�b�t�@�T�C�Y�� [BUFSIZ * 2] ���� [MAX_CONTENT_SIZE] �ɕύX
 * (BUFSIZ * 2 ��蒷��������������K�v��������������)
 * 
 * 8     05/11/11 16:01 Tsujimura543
 * UTF-8 �� 0xe2 0x84 0xa2 (&trade; ���Ȃ킿 TM �����̕����R�[�h) ������
 * ����ꍇ�́A" TM"�ɒu������悤�ɂ���
 * 
 * 7     05/10/28 21:16 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 6     05/10/28 14:20 Tsujimura543
 * �f�o�b�O�p�̃R�[�h���폜
 * 
 * 5     05/10/28 14:12 Tsujimura543
 * (c) �}�[�N�ȊO�� ISO-8859-1 �Ǝ�����(0xA0�`0xFF)�ɂ��Ώ��ł���悤�ɂ���
 * 
 * 4     05/10/27 20:47 Tsujimura543
 * �o�O�C���A����m�F�ς�
 * 
 * 3     05/10/27 20:36 Tsujimura543
 * (1) (c) �}�[�N�����ږ��ߍ��܂�Ă���ꍇ�� &#169; �ɒu������悤�ɂ���
 * (2) &amp;amp; �� &amp; �ɒu������悤�ɂ���
 * 
 * 2     04/07/07 11:56 Tsujimura543
 * ������Ƃ����C��
 * 
 * 1     04/07/07 11:24 Tsujimura543
 * �Ő��Ǘ��� RCS ���� VSS �ֈڍs
 *
 * Revision 1.5  2003/11/11  07:07:10  tsujimura543
 * const �w���t��
 *
 * Revision 1.4  2003/11/11  07:02:19  tsujimura543
 * K&R �\�L �� ANSI C �\�L �Ɋ��S�ڍs
 *
 * Revision 1.3  2003/03/11  12:13:53  tsujimura543
 * �R�����g�𐮗�
 *
 * Revision 1.2  2003/03/11  01:45:55  tsujimura543
 * RCS�R�����g�𖄂ߍ��ނ悤�ɂ���
 *
 * Revision 1.1  2003/02/25  05:52:29  tsujimura543
 * Initial revision
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/misc/decodeURL.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

#define MAX_CONTENT_SIZE    65536

static char *
_decodeURL( const char *pp )
{
    const char                  *p;
    char                        tmp[3], *q;
    Thread static unsigned char out[MAX_CONTENT_SIZE * 2];
    size_t                      sz = MAX_CONTENT_SIZE;
    /* ��: (���̂Ƃ���A�����s����)�������j��ɂ���Q�𖳊Q�����邽�߂� */
    /*     ���}���u�Ƃ��āAout �̃T�C�Y��2�{�ɐݒ�(��������A�΍���{���� */
    /*     ��A���ɖ߂�)                                       2008.05.20 */

    p = pp;
    q = (char *)&out[0];
    while ( *p ) {
        if ( *p == '%' ) {
            if ( (((*(p + 1) >= '0') && (*(p + 1) <= '9')) ||
                  ((*(p + 1) >= 'A') && (*(p + 1) <= 'F')) ||
                  ((*(p + 1) >= 'a') && (*(p + 1) <= 'f'))   ) &&
                 (((*(p + 2) >= '0') && (*(p + 2) <= '9')) ||
                  ((*(p + 2) >= 'A') && (*(p + 2) <= 'F')) ||
                  ((*(p + 2) >= 'a') && (*(p + 2) <= 'f'))   )    ) {
                tmp[0] = *++p;
                tmp[1] = *++p;
                tmp[2] = '\0';
                p++;
                *q++ = (unsigned char)(strtol( tmp, NULL, 16 ) & 0xFF);
                continue;
            }
        }
        else if ( *p == '+' ) {
            p++;
            *q++ = ' ';
            continue;
        }
        else if ( *p == '&' ) {
            if ( (*(p + 1) == 'a') &&
                 (*(p + 2) == 'm') && 
                 (*(p + 3) == 'p') &&
                 (*(p + 4) == ';')    ) {
                *q++ = *p++;
                p += 4;
                continue;
            }
        }

        *q++ = (unsigned char)(*p++);

        if ( q - (char *)out > (int)sz - 1 )    /* {@@} */
            break;                              /* {@@} */
    }
    *q = '\0';

    return ( (char *)&out[0] );
}

#ifdef  _MSC_VER
#pragma warning ( disable : 4996 )  // for Visual C++ 2005
#endif
char	*
decodeURL( const char *pp )
{
    char    *s;

    if ( ( ( s = strchr( pp, '\302' ) ) != NULL )     &&
         ( (unsigned short)(*(s + 1) & 0xFF) >= 160 )    ) {
        /* ISO-8859-1 �̓��ꕶ��(0xA0�`0xFF) �ɑΏ����邽�߂̏���          */
        /*  -- UTF-8 �ł� 0xC2 �����O�ɕt������Ă���                      */
        /*        ��: 0xC2(16�i) = 194(10�i) = 302(8�i)                    */
        /*            0xA0(16�i) = 160(10�i) = 240(8�i)                    */
        /*  -- ������u���p�J�i�v�� ISO-8591-1 �̓��ꕶ�����ƌ딻�肵��  */
        /*     ���܂��\���͎c�� (�Ⴆ�� &copy; �� �c�D (�̔��p�\�L) �Ƌ� */
        /*     �ʂł��Ȃ�                                                  */
        /*  -- 0xA0 �� &nbsp;(&#160;)���邢�͒P���ɋ󔒕����ɒu�����ׂ���? */
        char    temp[MAX_CONTENT_SIZE];
        int     pos = s - pp;

        if ( pos >= MAX_CONTENT_SIZE - 1 )  /* {@@} */
            s = _decodeURL( pp );           /* {@@} */
        else {                              /* {@@} */
            strncpy( temp, pp, pos );
            temp[pos++] = '&';
            temp[pos++] = '#';
            temp[pos++] = (char)('0' + ( (*(s + 1) & 0xFF) / 100));
            temp[pos++] = (char)('0' + (((*(s + 1) & 0xFF) / 10) % 10));
            temp[pos++] = (char)('0' + ( (*(s + 1) & 0xFF) % 10));
            temp[pos++] = ';';
            strcpy( &(temp[pos]), s + 2 );
            s = _decodeURL( temp );
        }                                   /* {@@} */
    }
    else if ( ( s = strstr( pp, "\342\204\242") ) != NULL ) {
        /* 0xe2 0x84 0xa2 �� TM (&trade;) */
        char    temp[MAX_CONTENT_SIZE];
        int     pos = s - pp;

        strncpy( temp, pp, pos );
        temp[pos++] = ' ';
        temp[pos++] = 'T';
        temp[pos++] = 'M';
        strcpy( &(temp[pos]), s + 3 );
        s = _decodeURL( temp );
    }
    else
        s = _decodeURL( pp );

    return ( s );
}
#ifdef  _MSC_VER
#pragma warning ( default : 4996 )  // for Visual C++ 2005
#endif
