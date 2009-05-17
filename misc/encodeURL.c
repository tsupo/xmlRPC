/*
 *  �C�ӂ̕������URL�G���R�[�h����
 *
 *        Copyleft (c) 2004, 2005 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  05 Feb 2004
 *
 * History:
 * $Log: /comm/xmlRPC/misc/encodeURL.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 28    09/03/30 19:48 Tsujimura543
 * OAuth �Ή�
 * 
 * 27    08/11/17 21:56 Tsujimura543
 * static �� Thread static �ɕύX
 * 
 * 26    08/05/15 19:27 Tsujimura543
 * (1) encodeURL() ���� sz2 �̌v�Z�������ɖ߂�
 * (2) encodeURL2(), encodeURLex(), translateURL() ���Ŏg���o�b�t�@
 *     ���σT�C�Y������
 * 
 * 25    08/05/15 19:16 Tsujimura543
 * encodeURL() ���� sz2 �̌v�Z����ύX (���܂ł̒l��2�{�ɕύX)
 * 
 * 24    07/09/07 18:29 Tsujimura543
 * replaceEntityStrings() �ɑ�2������ǉ��BShift_JIS �ȊO�̏ꍇ�ɂ��Ή�
 * 
 * 23    07/09/07 17:03 Tsujimura543
 * replaceEntityStrings() ��ǉ�
 * 
 * 22    07/01/29 13:21 Tsujimura543
 * encodeURLex() �ł� (#xxx; �� ; ������) ; ���p�[�Z���g�G�X�P�[�v�Ώۂ�
 * ����悤�ɂ���
 * 
 * 21    06/07/18 20:44 Tsujimura543
 * &raquo; �΍� (�͂Ăȃu�b�N�}�[�N�̋����ύX�ɔ����C��)
 * 
 * 20    06/05/15 22:40 Tsujimura543
 * encodeURL() ���Ŋm�ۂ��� out �̑傫�����C��(������ pp �̒��������ɎZ�o)
 * 
 * 19    06/02/27 21:03 Tsujimura543
 * �u���̎Q�Ɓ���֕�����ϊ��e�[�u���v�̎��̂� codeTbl.c �Ƃ��ĕ����Ɨ�
 * 
 * 18    06/02/27 20:57 Tsujimura543
 * rep[] �� entity_code_repTbl[] �ɖ��O��ύX
 * 
 * 17    06/02/27 20:32 Tsujimura543
 * ���̎Q�Ɓ���֕�����ϊ��e�[�u���֘A�̒�`�� codeTbl.h �Ƃ���
 * �����Ɨ�������
 * 
 * 16    06/02/25 0:06 Tsujimura543
 * encodeURLexX() �p�̃R�[�h�ϊ��e�[�u��������������
 * (������͕ʃt�@�C���ɕ�������\��)
 * 
 * 15    06/02/23 1:07 Tsujimura543
 * encodeURLex2() ���C���Bdel.icio.us �ւ̃u�b�N�}�[�N���e�ɂē���m�F�B
 * 
 * 14    06/02/22 17:13 Tsujimura543
 * encodeURLex4() ��ǉ�
 * 
 * 13    06/02/22 16:48 Tsujimura543
 * encodeURLex3() ��ǉ�
 * 
 * 12    05/11/11 15:59 Tsujimura543
 * TM (&trade;) �Ɋւ��鏈�������Ă݂�(�b��)
 * 
 * 11    05/10/29 1:12 Tsujimura543
 * �u�b�N�}�[�N�o�^���Ɏg�p���鏈�����e�X��������(����m�F�ς�)
 * 
 * 10    05/10/28 22:03 Tsujimura543
 * encodeURLex() ���C�� ('?' �ɕϊ����Ă������� "%3f" �ɕϊ�����悤�C��)
 * 
 * 9     05/10/28 21:00 Tsujimura543
 * encodeURLex2() �������I�ɓ������Ă݂�
 * 
 * 8     05/10/28 18:22 Tsujimura543
 * encodeURLex() ��ǉ�
 * 
 * 7     05/05/30 20:22 Tsujimura543
 * A�`Z, a�`z, 0�`9 �� _ �̓G���R�[�h�����ɂ��̂܂܏o�͂���悤�ɂ���
 * (���M�d���̃o�C�g�������炷���ʂ�����)
 * 
 * 6     04/11/15 17:05 Tsujimura543
 * ������ NULL �̂Ƃ��A�̈�������悤�ɂ���
 * 
 * 5     04/11/15 11:09 Tsujimura543
 * translateURL() ��ǉ�
 * 
 * 4     04/11/02 21:10 Tsujimura543
 * �o�b�t�@�m�ێ��s���́A�I���W�i���̕���������̂܂ܕԂ��悤�ɂ���
 * 
 * 3     04/11/02 21:08 Tsujimura543
 * �o�b�t�@�𓮓I�Ɋm�ۂ���悤�ɕύX�B�o�b�t�@�T�C�Y�����₷�B
 * 
 * 2     04/07/07 11:56 Tsujimura543
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmlRPC.h"
#include "codeTbl.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/misc/encodeURL.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

#ifndef MAX_CONTENT_SIZE
#define MAX_CONTENT_SIZE    65536
#endif

char	*
_encodeURL( const char *pp, BOOL lowercase, BOOL forOAuth )
{
    const char                  *p;
    char                        *q;
    int                         hex;
    const char                  *hexStr =
                                    lowercase ? "0123456789abcdef"
                                              : "0123456789ABCDEF";
    Thread static unsigned char *out = NULL;
    size_t                      sz = MAX_CONTENT_SIZE * 2;

    if ( out ) {
        free( out );
        out = NULL;
    }

    if ( pp ) {
        size_t  sz2 = strlen( pp ) * 4;
        if ( sz2 > sz )
            sz = sz2;
        out = (unsigned char *)malloc( sz );
    }

    if ( out ) {
        p = pp;
        q = (char *)out;
        while ( *p ) {
            if ( ((*p >= 'a') && (*p <= 'z')) ||
                 ((*p >= 'A') && (*p <= 'Z')) ||
                 ((*p >= '0') && (*p <= '9')) ||
                 (*p == '_')                  ||
                 (forOAuth && 
                  ((*p == '-') ||
                   (*p == '.') ||
                   (*p == '~')   )          )    ) {
                *q++ = *p++;
                continue;
            }
            hex  = (*p++ & 0xFF);
            *q++ = '%';
            *q++ = hexStr[(hex >> 4) & 0x0F];
            *q++ = hexStr[hex & 0x0F];
        }
        *q = '\0';
    }

    return ( out ? (char *)out : pp );
}

char	*
encodeURL( const char *pp )
{
    return ( _encodeURL( pp, FALSE, FALSE ) );
}

char	*
encodeURLi( const char *pp, BOOL lowercase )
{
    return ( _encodeURL( pp, lowercase, TRUE ) );
}


char	*
encodeURL2( const char *pp )
{
    const char                  *p;
    char                        *q;
    int                         hex;
    const char                  *hexStr = "0123456789ABCDEF";
    Thread static unsigned char *out = NULL;
    size_t                      sz = MAX_CONTENT_SIZE * 2;

    if ( out ) {
        free( out );
        out = NULL;
    }

    if ( pp ) {
        size_t  sz2 = strlen( pp ) * 4;
        if ( sz2 > sz )
            sz = sz2;
        out = (unsigned char *)malloc( sz );
    }

    if ( out ) {
        p = pp;
        q = (char *)out;
        while ( *p ) {
            if ( ((*p >= 'a') && (*p <= 'z')) ||
                 ((*p >= 'A') && (*p <= 'Z')) ||
                 ((*p >= '0') && (*p <= '9')) ||
                 (*p == '_') /* || (*p == ';') */ ) {
                *q++ = *p++;
                continue;
            }
            else if ( (*p == '&') && (*(p + 1) == '#') ) {
                *q++ = *p++;
                *q++ = *p++;
                continue;
            }
            hex  = (*p++ & 0xFF);
            *q++ = '%';
            *q++ = hexStr[(hex >> 4) & 0x0F];
            *q++ = hexStr[hex & 0x0F];
        }
        *q = '\0';
    }

    return ( out ? (char *)out : pp );
}

char    *
translateURL( const char *pp )
{
    const char                  *p;
    char                        *q;
    Thread static unsigned char *out = NULL;
    size_t                      sz = MAX_CONTENT_SIZE * 2;

    if ( out ) {
        free( out );
        out = NULL;
    }

    if ( pp ) {
        size_t  sz2 = strlen( pp ) * 4;
        if ( sz2 > sz )
            sz = sz2;
        out = (unsigned char *)malloc( sz );
    }

    if ( out ) {
        p = pp;
        q = (char *)out;
        while ( *p ) {
            if ( *p == '/' ) {
                *q++ = '%';
                *q++ = '2';
                *q++ = 'F';
            }
            else if ( *p == ':' ) {
                *q++ = '%';
                *q++ = '3';
                *q++ = 'A';
            }
            else if ( *p == '=' ) {
                *q++ = '%';
                *q++ = '3';
                *q++ = 'D';
            }
            else if ( *p == '?' ) {
                *q++ = '%';
                *q++ = '3';
                *q++ = 'F';
            }
            else if ( *p == '&' ) {
                *q++ = '%';
                *q++ = '2';
                *q++ = '6';
            }
            else if ( *p == '#' ) {
                *q++ = '%';
                *q++ = '2';
                *q++ = '3';
            }
            else
                *q++ = *p;
            p++;
        }
        *q = '\0';
    }

    return ( out ? (char *)out : pp );
}


char	*
encodeURLex( const char *pp )
{
    const char                  *p;
    char                        *q;
    int                         hex;
    const char                  *hexStr = "0123456789ABCDEF";
    Thread static unsigned char *out = NULL;
    size_t                      sz = MAX_CONTENT_SIZE * 2;

    if ( out ) {
        free( out );
        out = NULL;
    }

    if ( pp ) {
        size_t  sz2 = strlen( pp ) * 8;
        if ( sz2 > sz )
            sz = sz2;
        out = (unsigned char *)malloc( sz );
    }

    if ( out ) {
        p = pp;
        q = (char *)out;
        while ( *p ) {
            if ( ((*p >= 'a') && (*p <= 'z')) ||
                 ((*p >= 'A') && (*p <= 'Z')) ||
                 ((*p >= '0') && (*p <= '9')) ||
                 (*p == '_') /* || (*p == ';') */ ) {
                *q++ = *p++;
                continue;
            }
            else if ( (*p == '&') && (*(p + 1) == '#') &&
                      strchr( p + 2, ';' )                ) {
                long    l = atol( p + 2 );
                if ( (l >= CD_NBSP) && (l <= CD_YUMLs) ) {
                    char    *r;

                    switch ( l ) {
                    case CD_NBSP:   /* &nbsp; �� �󔒕����ɒu�� */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = '0';
                        break;
                    case CD_IEXCL:  /* &iexcl;(!�̏㉺��������) �� ! �ɒu�� */
                        *q++ = '!';
                        break;
                    case CD_CENT:   /* &cent; (��) �� c �ɒu�� */
                        *q++ = 'c';
                        break;
                    case CD_POUND:  /* &pound; (��) �� p �ɒu�� */
                        *q++ = 'p';
                        break;
                    case CD_CURREN: /* &curren; �� ? �ɒu�� */
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'f';
                        break;
                    case CD_YEN:    /* &yen; �� \ �ɒu�� */
                        *q++ = '%';
                        *q++ = '5';
                        *q++ = 'c';
                        break;
                    case CD_BRVBAR: /* &brvbar; �� | �ɒu�� */
                        *q++ = '%';
                        *q++ = '7';
                        *q++ = 'c';
                        break;
                    case CD_SECT:   /* &sect; (��) �� s �ɒu�� */
                        *q++ = 's';
                        break;
                    case CD_COPY:   /* &copy; �� (c) �ɒu�� */
                        *q++ = '%'; /* ( */
                        *q++ = '2'; /* ( */
                        *q++ = '8'; /* ( */
                        *q++ = 'c';
                        *q++ = '%'; /* ) */
                        *q++ = '2'; /* ) */
                        *q++ = '9'; /* ) */
                        break;
                    case CD_ORDF:   /* &ordf; (��t��a) �� a �ɒu�� */
                        *q++ = 'a';
                        break;
                    case CD_ORDM:   /* &ordm; (��t��o) �� o �ɒu�� */
                        *q++ = 'o';
                        break;
                    case CD_LAQUO:  /* &laquo; (��) �� << �ɒu�� */
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'c';
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'c';
                        break;
                    case CD_NOT:    /* &not; (��) �� 'not ' �ɒu�� */
                        *q++ = 'n';
                        *q++ = 'o';
                        *q++ = 't';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = '0';
                        break;
                    case CD_SHY:    /* &shy; �� - �ɒu�� */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'd';
                        break;
                    case CD_REG:    /* &reg; �� (R) �ɒu�� */
                        *q++ = '%'; /* ( */
                        *q++ = '2'; /* ( */
                        *q++ = '8'; /* ( */
                        *q++ = 'R';
                        *q++ = '%'; /* ) */
                        *q++ = '2'; /* ) */
                        *q++ = '9'; /* ) */
                        break;
                    case CD_MACR:   /* &macr; �� ~ �ɒu�� */
                        *q++ = '%';
                        *q++ = '7';
                        *q++ = 'e';
                        break;
                    case CD_DEG:    /* &deg; ( ��) �� d �ɒu�� */
                        *q++ = 'd';
                        break;
                    case CD_PLUSMN: /* &plusmn; (�}) �� +- �ɒu�� */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'b';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'd';
                        break;
                    case CD_SUP2:   /* &sup2; (��t��2) �� 2 �ɒu�� */
                        *q++ = '2';
                        break;
                    case CD_SUP3:   /* &sup3; (��t��3) �� 3 �ɒu�� */
                        *q++ = '3';
                        break;
                    case CD_ACUTE:  /* &acute; (�L) �� ' �ɒu�� */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = '7';
                        break;
                    case CD_MICRO:  /* &micro; (��) �� u �ɒu�� */
                        *q++ = 'u';
                        break;
                    case CD_PARA:   /* &para; (��) �� * �ɒu�� */
                    case CD_MIDDOT: /* &middot; (�E) �� * �ɒu�� */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'a';
                        break;
                    case CD_SUP1:   /* &sup1; (��t��1) �� 1 �ɒu�� */
                        *q++ = '1';
                        break;
                    case CD_RAQUO:  /* &raquo; (��) �� >> �ɒu�� */
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'e';
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'e';
                        break;
                    case CD_FRAC14: /* &frac14; �� 1/4 �ɒu�� */
                        *q++ = '1';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'f';
                        *q++ = '4';
                        break;
                    case CD_FRAC12: /* &frac12; �� 1/2 �ɒu�� */
                        *q++ = '1';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'f';
                        *q++ = '2';
                        break;
                    case CD_FRAC34: /* &frac34; �� 3/4 �ɒu�� */
                        *q++ = '3';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'f';
                        *q++ = '4';
                        break;
                    case CD_IQUEST: /* &iquest;(?�̏㉺��������) �� ?�ɒu�� */
                        *q++ = '?';
                        break;
                    case CD_AGRAVE: /* &Agrave; (A �̏�� ` ) �� A �ɒu�� */
                    case CD_AACUTE: /* &Aacute; (A �̏�� �L) �� A �ɒu�� */
                    case CD_ACIRC:  /* &Acirc;  (A �̏�� ^ ) �� A �ɒu�� */
                    case CD_ATILDE: /* &Atilde; (A �̏�� ~ ) �� A �ɒu�� */
                    case CD_AUML:   /* &Auml;   (A �̏�� �N) �� A �ɒu�� */
                    case CD_ARING:  /* &Aring;  (A �̏�� o ) �� A �ɒu�� */
                        *q++ = 'A';
                        break;
                    case CD_AELIG:  /* &AElig; (A �� E ������) �� AE �ɒu�� */
                        *q++ = 'A';
                        *q++ = 'E';
                        break;
                    case CD_CCEDIL: /* &Ccedil;  (C �̉��� ,) �� C �ɒu�� */
                        *q++ = 'C';
                        break;
                    case CD_EGRAVE: /* &Egrave; (E �̏�� ` ) �� E �ɒu�� */
                    case CD_EACUTE: /* &Eacute; (E �̏�� �L) �� E �ɒu�� */
                    case CD_ECIRC:  /* &Ecirc;  (E �̏�� ^ ) �� E �ɒu�� */
                    case CD_EUML:   /* &Euml;   (E �̏�� �N) �� E �ɒu�� */
                        *q++ = 'E';
                        break;
                    case CD_IGRAVE: /* &Igrave; (I �̏�� ` ) �� I �ɒu�� */
                    case CD_IACUTE: /* &Iacute; (I �̏�� �L) �� I �ɒu�� */
                    case CD_ICIRC:  /* &Icirc;  (I �̏�� ^ ) �� I �ɒu�� */
                    case CD_IUML:   /* &Iuml;   (I �̏�� �N) �� I �ɒu�� */
                        *q++ = 'I';
                        break;
                    case CD_ETH:    /* &ETH; (- �t���� D) �� D �ɒu�� */
                        *q++ = 'D';
                        break;
                    case CD_NTILDE: /* &Ntilde; (N �̏�� ~ ) �� N �ɒu�� */
                        *q++ = 'N';
                        break;
                    case CD_OGRAVE: /* &Ograve; (O �̏�� ` ) �� O �ɒu�� */
                    case CD_OACUTE: /* &Oacute; (O �̏�� �L) �� O �ɒu�� */
                    case CD_OCIRC:  /* &Ocirc;  (O �̏�� ^ ) �� O �ɒu�� */
                    case CD_OTILDE: /* &Otilde; (O �̏�� ~ ) �� O �ɒu�� */
                    case CD_OUML:   /* &Ouml;   (O �̏�� �N) �� O �ɒu�� */
                    case CD_OSLASH: /* &Oslash; (�ΐ��t���� O) �� O �ɒu�� */
                        *q++ = 'O';
                        break;
                    case CD_TIMES:  /* &times; (�~) �� X �ɒu�� */
                        *q++ = 'X';
                        break;
                    case CD_UGRAVE: /* &Ugrave; (U �̏�� ` ) �� U �ɒu�� */
                    case CD_UACUTE: /* &Uacute; (U �̏�� �L) �� U �ɒu�� */
                    case CD_UCIRC:  /* &Ucirc;  (U �̏�� ^ ) �� U �ɒu�� */
                    case CD_UUML:   /* &Uuml;   (U �̏�� �N) �� U �ɒu�� */
                        *q++ = 'U';
                        break;
                    case CD_YACUTE: /* &Yacute; (Y �̏�� �L) �� Y �ɒu�� */
                        *q++ = 'Y';
                        break;
                    case CD_THORN:  /* &THORN; (�� �ɂ悭����T) �� T �ɒu�� */
                        *q++ = 'T';
                        break;
                    case CD_SZLIG:  /* &szlig; (�G�X�c�F�b�g) �� ss �ɒu�� */
                        *q++ = 's';
                        *q++ = 's';
                        break;
                    case CD_AGRAVEs:/* &agrave; (a �̏�� ` ) �� a �ɒu�� */
                    case CD_AACUTEs:/* &aacute; (a �̏�� �L) �� a �ɒu�� */
                    case CD_ACIRCs: /* &acirc;  (a �̏�� ^ ) �� a �ɒu�� */
                    case CD_ATILDEs:/* &atilde; (a �̏�� ~ ) �� a �ɒu�� */
                    case CD_AUMLs:  /* &auml;   (a �̏�� �N) �� a �ɒu�� */
                    case CD_ARINGs: /* &aring;  (a �̏�� o ) �� a �ɒu�� */
                        *q++ = 'a';
                        break;
                    case CD_AELIGs: /* &aelig; (a �� e ������) �� ae �ɒu�� */
                        *q++ = 'a';
                        *q++ = 'e';
                        break;
                    case CD_CCEDILs:/* &ccedil;  (c �̉��� ,) �� c �ɒu�� */
                        *q++ = 'c';
                        break;
                    case CD_EGRAVEs:/* &egrave; (e �̏�� ` ) �� e �ɒu�� */
                    case CD_EACUTEs:/* &eacute; (e �̏�� �L) �� e �ɒu�� */
                    case CD_ECIRCs: /* &ecirc;  (e �̏�� ^ ) �� e �ɒu�� */
                    case CD_EUMLs:  /* &euml;   (e �̏�� �N) �� e �ɒu�� */
                        *q++ = 'e';
                        break;
                    case CD_IGRAVEs:/* &igrave; (i �̏�� ` ) �� i �ɒu�� */
                    case CD_IACUTEs:/* &iacute; (i �̏�� �L) �� i �ɒu�� */
                    case CD_ICIRCs: /* &icirc;  (i �̏�� ^ ) �� i �ɒu�� */
                    case CD_IUMLs:  /* &iuml;   (i �̏�� �N) �� i �ɒu�� */
                        *q++ = 'i';
                        break;
                    case CD_ETHs:   /* &eth; (- �t���� d) �� d �ɒu�� */
                        *q++ = 'd';
                        break;
                    case CD_NTILDEs:/* &ntilde; (n �̏�� ~ ) �� n �ɒu�� */
                        *q++ = 'n';
                        break;
                    case CD_OGRAVEs:/* &ograve; (o �̏�� ` ) �� o �ɒu�� */
                    case CD_OACUTEs:/* &oacute; (o �̏�� �L) �� o �ɒu�� */
                    case CD_OCIRCs: /* &ocirc;  (o �̏�� ^ ) �� o �ɒu�� */
                    case CD_OTILDEs:/* &otilde; (o �̏�� ~ ) �� o �ɒu�� */
                    case CD_OUMLs:  /* &ouml;   (o �̏�� �N) �� o �ɒu�� */
                    case CD_OSLASHs:/* &oslash; (�ΐ��t���� o) �� o �ɒu�� */
                        *q++ = 'o';
                        break;
                    case CD_DIVIDE: /* &divide; (��) �� / �ɒu�� */
                        *q++ = '/';
                        break;
                    case CD_UGRAVEs:/* &ugrave; (u �̏�� ` ) �� u �ɒu�� */
                    case CD_UACUTEs:/* &uacute; (u �̏�� �L) �� u �ɒu�� */
                    case CD_UCIRCs: /* &ucirc;  (u �̏�� ^ ) �� u �ɒu�� */
                    case CD_UUMLs:  /* &uuml;   (u �̏�� �N) �� u �ɒu�� */
                        *q++ = 'u';
                        break;
                    case CD_YACUTEs:/* &yacute; (y �̏�� �L) �� y �ɒu�� */
                    case CD_YUMLs:  /* &yuml; (y �̏�� �N) �� y �ɒu�� */
                        *q++ = 'y';
                        break;
                    case CD_THORNs: /* &thorn; (p �� b ������) �� t �ɒu�� */
                        *q++ = 't';
                        break;

                    case CD_UML:    /* &uml; (�N) �� ���� */
                    case CD_CEDIL:  /* &cedil; (c �̉��ɂ� ,) �� ���� */
                        break;

                    default:
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'f';
                        break;
                    }

                    r = strchr( p, ';' );
                    if ( r )
                        p = r + 1;
                    else
                        p += 2; /* �����ɗ��邱�Ƃ͂Ȃ��͂� */
                }
                else {
                    *q++ = *p++;
                    *q++ = *p++;
                }
                continue;
            }
            else if ( ((unsigned char)(*p) == 0xe2) &&
                      ((unsigned char)(*p) == 0x84) &&
                      ((unsigned char)(*p) == 0xa2)    ) {
                /* &trade; �� TM �ɒu�� */
                *q++ = ' ';
                *q++ = 'T';
                *q++ = 'M';
                p += 3;
                continue;
            }
            hex  = (*p++ & 0xFF);
            *q++ = '%';
            *q++ = hexStr[(hex >> 4) & 0x0F];
            *q++ = hexStr[hex & 0x0F];
        }
        *q = '\0';
    }

    return ( out ? (char *)out : pp );
}


BOOL
replaceString( char *target, const char *src, const char *dst )
{
    char    *p = target;
    char    *q;
    BOOL    ret = FALSE;

    if ( ( q = strstr( p, src ) ) != NULL ) {
        char    *temp;
        int     l = strlen( src );

        temp = (char *)malloc( strlen( p ) - l + strlen( dst ) + 1 );
        if ( temp ) {
            strncpy( temp, p, q - p );
            strcpy( &(temp[q - p]), dst );
            strcat( temp, q + l );

            strcpy( p, temp );
            free( temp );
            ret = TRUE;
        }
    }

    return ( ret );
}


char    *
replaceStringSub(
        char *src   /* (I/O) UTF-8 ������ */
    )
{
    char    *p, *q;
    char    tmp1[8], tmp2[8];

    strcpy( tmp1, sjis2utf( "��" ) );
    strcpy( tmp2, sjis2utf( "��" ) );
    p = src;
    while ( ( q = strstr( p, tmp1 ) ) != NULL ) {
        *q       = (unsigned char)0xC2;
        *(q + 1) = (unsigned char)0xBB;
        strcpy( q + 2, q + 3 );
    }
    while ( ( q = strstr( p, tmp2 ) ) != NULL ) {
        *q       = (unsigned char)0xC2;
        *(q + 1) = (unsigned char)0xAB;
        strcpy( q + 2, q + 3 );
    }
    while ( ( q = strstr( p, "&amp;raquo;" ) ) != NULL ) {
        *q       = (unsigned char)0xC2;
        *(q + 1) = (unsigned char)0xBB;
        strcpy( q + 2, q + 11 );
    }
    while ( ( q = strstr( p, "&amp;laquo;" ) ) != NULL ) {
        *q       = (unsigned char)0xC2;
        *(q + 1) = (unsigned char)0xBB;
        strcpy( q + 2, q + 11 );
    }

    return ( src );
}

/* �b��� */
char	*
encodeURLex2(
        const char *p /* (I) UTF-8 ������ */
    )
{
    BOOL                done = FALSE;
    char                *q, *r;
    unsigned char       temp[BUFSIZ * 6];
    int                 l, i, cnt;
    BOOL                ret;
    struct replaceTable *rep = entity_code_repTbl;

    if ( !p )
        return ( encodeURL2( NULL ) );

    /* ISO-8859-1 �̓��ꕶ��(0xA0�`0xFF) �ɑΏ����邽�߂̏��� */
    q = strstr( p, "&#" );
    r = q ? strchr( q, ';' ) : NULL;
    if ( q && r && ((l = atol(q + 2)) >= CD_NBSP) ) {
        int pos = q - p;

        strncpy( (char *)temp, p, pos );
        temp[pos++] = (unsigned char)0xC2;
        temp[pos++] = (unsigned char)(l & 0xFF);
        strcpy( (char *)(&(temp[pos])), r + 1 );
    }
    else
        strcpy( (char *)temp, p );

    replaceStringSub( (char *)temp ); /* {@@} */

    /* ��������f�R�[�h���Ă��� */
    do {
        q = strchr( (char *)temp, '&' );
        r = q ? strchr( q, ';' ) : NULL;
        if ( q && r ) {
            cnt = 0;
            for ( i = 0; rep[i].src; i++ ) {
                if ( !strstr( q, rep[i].src ) )
                    continue;

                if ( (rep[i].code >= 0x0080) && (rep[i].code <= 0x07FF) ) {
                    unsigned char   tmp[3];

                    tmp[0] = (unsigned char)
                                (((rep[i].code >> 6)   | 0x00C0) & 0xFF);
                    tmp[1] = (unsigned char)
                                (((rep[i].code & 0x3F) | 0x0080) & 0xFF);
                    tmp[2] = NUL;
                    ret = replaceString( q, rep[i].src, (char *)tmp );
                    if ( ret )
                        cnt++;
                }
                else if ((rep[i].code >= 0x0800) && (rep[i].code <= 0xFFFF)) {
                    unsigned char   tmp[4];

                    tmp[0] = (unsigned char)
                             (( (rep[i].code >> 12)         | 0x00E0) & 0xFF);
                    tmp[1] = (unsigned char)
                             ((((rep[i].code >>  6) & 0x3F) | 0x0080) & 0xFF);
                    tmp[2] = (unsigned char)
                             ( ((rep[i].code & 0x3F) | 0x0080) & 0xFF);
                    tmp[3] = NUL;
                    ret = replaceString( q, rep[i].src, (char *)tmp );
                    if ( ret )
                        cnt++;
                }
                else {
                    ret = replaceString(q, rep[i].src, sjis2utf(rep[i].dst));
                    if ( ret )
                        cnt++;
                }
            }
            if ( cnt == 0 )
                done = TRUE;
        }
        else
            done = TRUE;
    } while ( done == FALSE );

    /* ���߂ăG���R�[�h */
    return ( encodeURL2( (char *)temp ) );
}


char	*
encodeURLex3(
        const char *p /* (I) EUC-JP ������ */
    )
{
    char                *q, *r;
#if 0
    BOOL                done = FALSE;
    unsigned char       temp[BUFSIZ * 6];
    int                 i, cnt;
    BOOL                ret;
    struct replaceTable *rep = entity_code_repTbl;
#endif

    if ( !p )
        return ( encodeURL2( NULL ) );

#if 0
    strcpy( (char *)temp, p );

    /* ��������f�R�[�h���Ă��� */
    do {
        q = strchr( (char *)temp, '&' );
        r = q ? strchr( q, ';' ) : NULL;
        if ( q && r ) {
            cnt = 0;
            for ( i = 0; rep[i].src; i++ ) {
                ret = replaceString( q, rep[i].src, sjis2euc(rep[i].dst) );
                if ( ret )
                    cnt++;
            }
            if ( cnt == 0 )
                done = TRUE;
        }
        else
            done = TRUE;
    } while ( done == FALSE );

    /* ���߂ăG���R�[�h */
    return ( encodeURL2( (char *)temp ) );
#else
    /* ��������f�R�[�h���Ă��� */
    q = replaceEntityStrings( p, CHARSET_EUCJP );
    r = NULL;
    if ( q ) {
        /* ���߂ăG���R�[�h */
        r = encodeURL2( q );
        replaceEntityStrings( NULL, CHARSET_UNKNOWN );
    }

    return ( r );
#endif
}

char	*
encodeURLex4(
        const char *p /* (I) Shift_JIS ������ */
    )
{
    char                *q, *r;
#if 0
    BOOL                done = FALSE;
    unsigned char       temp[BUFSIZ * 6];
    int                 i, cnt;
    BOOL                ret;
    struct replaceTable *rep = entity_code_repTbl;
#endif

    if ( !p )
        return ( encodeURL2( NULL ) );

#if 0
    strcpy( (char *)temp, p );

    /* ��������f�R�[�h���Ă��� */
    do {
        q = strchr( (char *)temp, '&' );
        r = q ? strchr( q, ';' ) : NULL;
        if ( q && r ) {
            cnt = 0;
            for ( i = 0; rep[i].src; i++ ) {
                ret = replaceString( q, rep[i].src, rep[i].dst );
                if ( ret )
                    cnt++;
            }
            if ( cnt == 0 )
                done = TRUE;
        }
        else
            done = TRUE;
    } while ( done == FALSE );

    /* ���߂ăG���R�[�h */
    return ( encodeURL2( (char *)temp ) );
#else
    /* ��������f�R�[�h���Ă��� */
    q = replaceEntityStrings( p, CHARSET_SHIFTJIS );
    r = NULL;
    if ( q ) {
        /* ���߂ăG���R�[�h */
        r = encodeURL2( q );
        replaceEntityStrings( NULL, CHARSET_UNKNOWN );
    }

    return ( r );
#endif
}


char    *
replaceEntityStrings( const char *p, int charSet )
{
    Thread static char      *out = NULL;
    Thread static size_t    sz   = 0;

    if ( out ) {
        if ( !p || ( strlen( p ) * 2 + BUFSIZ > sz ) ) {
            free( out );
            out = NULL;
            sz  = 0;
        }
    }

    if ( p && !out ) {
        sz  = strlen( p ) * 2 + BUFSIZ;
        out = (char *)malloc( sz );
        if ( !out )
            sz = 0;
    }

    if ( out ) {
        struct replaceTable *rep = entity_code_repTbl;
        char                *q, *r;
        const char          *s;
        int                 cnt, i;
        BOOL                done = FALSE, ret;

        strcpy( out, p );

        do {
            q = strchr( out, '&' );
            r = q ? strchr( q, ';' ) : NULL;
            if ( q && r ) {
                cnt = 0;
                for ( i = 0; rep[i].src; i++ ) {
                    s = rep[i].dst;
                    switch ( charSet ) {
                    case CHARSET_EUCJP:
                        s = sjis2euc( rep[i].dst ); 
                        break;
                    case CHARSET_UTF8:
                        s = sjis2utf( rep[i].dst ); 
                        break;
                    }
                    ret = replaceString( q, rep[i].src, s );
                    if ( ret )
                        cnt++;
                }
                if ( cnt == 0 )
                    done = TRUE;
            }
            else
                done = TRUE;
        } while ( done == FALSE );
    }

    return ( out );
}
