/*
 *  �����R�[�h�ϊ�
 *    ���镶���R�[�h�̕������ʂ̕����R�[�h�ɕϊ�����
 *
 *        Copyleft (c) 2004 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  05 Feb 2004
 *
 * History:
 * $Log: /comm/xmlRPC/misc/changeCode.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 19    08/11/27 15:08 Tsujimura543
 * getIconvVersion() �̏o�͌`��������ɕύX
 * 
 * 18    08/11/27 15:06 Tsujimura543
 * getIconvVersion() �̏o�͌`����ύX
 * 
 * 17    08/11/27 14:48 Tsujimura543
 * getIconvVersion() ��ǉ�
 * 
 * 16    08/11/17 21:46 Tsujimura543
 * static char �� Thread static char �ɕύX
 * 
 * 15    07/11/13 22:20 Tsujimura543
 * �킩��Ȃ��Ȃ��Ă��܂��Ă����u�����R�[�h���ʏ����v�̏o�T���悤�₭
 * �˂��~�߂邱�Ƃɐ����B�o�T�𖾎�����
 * 
 * 14    06/11/16 1:15 Tsujimura543
 * convertCode() ���� memset() ���g��Ȃ��悤�ɏ��������Ă݂�
 * 
 * 13    06/11/15 23:27 Tsujimura543
 * convertCode() ���̗]���� memset() �Ăяo�����폜
 * 
 * 12    06/05/11 15:19 Tsujimura543
 * convertCode() ���Ŏg�p���� inbuf �̃T�C�Y�𓮓I�Ɍ��肷��悤�ɕύX
 * 
 * 11    06/03/22 16:53 Tsujimura543
 * convertCode() �������ɍċA����̂�h�~���邽�߂̏C�������{
 * 
 * 10    06/02/09 22:53 Tsujimura543
 * BUFFER_SIZE ��2�{�̒l�ɕύX
 * 
 * 9     06/02/08 16:46 Tsujimura543
 * ��������������Y���o�H�������� �� �C���ς�
 * 
 * 8     05/12/22 19:08 Tsujimura543
 * UTF-8 ������� euc2sjis() �� sjis2utf() �ɓn���Ɗ��҂��Ȃ����������
 * �悤�ɂȂ��Ă��܂����̂��C��
 * 
 * 7     05/12/21 18:49 Tsujimura543
 * �@��ˑ��������܂܂��ꍇ�Aeuc2sjis() �̒����� euc2sjisEx() ���Ăяo��
 * �悤�ɂ��邱�ƂŁA�����𑱍s�ł���悤�ɂ��� 
 * 
 * 6     05/11/11 0:15 Tsujimura543
 * UTF-8 �� Shift_JIS �ϊ������s���邢�����̃P�[�X�ɑ΂���΍�����{
 * 
 * 5     05/10/28 15:36 Tsujimura543
 * iso8859_1toUtf8() ��ǉ�
 * 
 * 4     04/11/01 21:02 Tsujimura543
 * �x�����x�� 4 �ł� warning ���\�Ȍ��茸�炵�Ă݂�
 * 
 * 3     04/11/01 19:56 Tsujimura543
 * �o�b�t�@�T�C�Y�ύX
 * 
 * 2     04/07/07 11:57 Tsujimura543
 */

#include "xmlRPC.h"
#include "iconv.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/misc/changeCode.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

#if 0
#define BUFFER_SIZE 20480
#else
#define BUFFER_SIZE (65536 * 2)
#endif

/* �����R�[�h���ʏ���: �������� */
/*
 *  �����R�[�h�ȈՔ���
 *      �o�T: fj �ɓ��e���ꂽ�L�� (1996�N)
 *          Newsgroups: fj.kanji,fj.sources
 *          From: hironobu@tiny.or.jp (Hironobu Takahashi)
 *          Subject: kanji-type (Re: guess kanji code)
 *          Message-ID: <1996Jul2.012859.15825@tiny.or.jp>
 *          Followup-To: fj.kanji
 *          Organization: Tsukuba Internet Club
 *          References: <BABA.96Jun27021124@saori.kusastro.kyoto-u.ac.jp> <BABA.96Jun29015026@saori.kusastro.kyoto-u.ac.jp> <6338@mozart.castanopsis.iijnet.or.jp> <4r7am4$va@post.trc.rwcp.or.jp>
 *          Date: Tue, 2 Jul 1996 01:28:59 GMT
 *
 *      http://katsu.watanabe.name/ancientfj/article.php?mid=%3C1996Jul2%2E012859%2E15825%40tiny%2Eor%2Ejp%3E
 */
#define __CHANGE_CODE_C__
#include "kanjidata.h"
#undef  __CHANGE_CODE_C__

/* �����̃R�[�f�B���O�������L�q���� ENUM �ł��B
 *
 * UNKNOWN: �����킩��Ȃ�����
 * BROKEN: MSB �� 1 �̃R�[�h���������ꂽ�� EUC �ł�MS�����ł��Ȃ�����
 * JISC6226_78, JISX0208_83, JISX0208_90: ������ 'JIS'�B��ʂ���K�v���邩��?
 * EUC: �g��UNIX?? ����������? ���΂��� UNIX �̃x���_�[���񋟂���R�[�f�B
 *      ���O�����B���Ȃ݂� EUC �� DEC �����̈Ⴂ�͌䑶�m�ł���? (^o^)
 * MSKANJI: �}�C�N���\�t�g�Ђ���`���������̃R�[�f�B���O�B����� ShiftJIS 
 *      �ƌĂԂ̂��������̂��ǂ����킩��Ȃ��B������ɂ��悠�܂�g�������
 *      �������̂ł͂Ȃ��B */

/* *c �ɂ���ė^����ꂽ 2 �o�C�g c[0]c[1] ���\�����镶���� EUC �Ƃ���
   ���߂ł��邩�ǂ������ׂ܂��B*/
static int
is_euc( const unsigned char *c )
{
    int pos, bit;

    pos = (c[0] & 0x7f) * 8 + (c[1] / 32 | 4);
    bit = (0x80000000 >> (c[1] & 31));

    return ( (kanji_jiscode_euc[pos] & bit) ? 1 : 0 );
}

/* *c �ɂ���ė^����ꂽ 2 �o�C�g c[0]c[1] ���\�����镶����MS�����Ƃ�
   �ĉ��߂ł��邩�ǂ������ׂ܂��B*/
static int
is_mskanji( const unsigned char *c )
{
    int pos, bit;

    pos = (c[0]&0x7f) * 8 + (c[1] / 32);
    bit = (0x80000000 >> (c[1] & 31));

    return ( (kanji_jiscode_mskanji[pos] & bit) ? 1 : 0 );
}

/* *c �ɂ���ė^����ꂽ 2 �o�C�g c[0]c[1] ���\�����镶����EUC��������MS��
   ���Ƃ��Ăǂ̒��x���߉\���̎w�W��^���܂��B

   kanjidata.h �ɗ^����ꂽ�\�̒l�� 96 �N 6 ���Ƀ|�X�g���ꂽ fj �ł̑S�L��
   �ɓo�ꂵ�������̐��𔽉f���Ă��܂��B������e�����̕p�x���z�̊��Ғl�Ƃ�
   �Ďg�p���Ă��܂��B�Ȃ� 1 �������ʂ𗚂����Ă���܂����A����̓T���v����
   ���\���ł͂Ȃ����߂ɁA�p�x�̒Ⴂ�����̑΂ɂ��d�݂��傫���Ȃ邱�Ƃ��
   ���邽�߂ł��B

   ��萳�m�ȕ\���쐬���邽�߂ɂ͂��傫�Ȏ����ƌ���A���S���Y���̏ڍׂ�
   �������K�v�ł��傤�B*/

static void
calc_probability(
        const unsigned char *c,
        double              *prob_euc,
        double              *prob_mskanji
    )
{
    double  euc_case, mskanji_case;

    /* ���ꂼ��ŉ��߂����ꍇ�̊����̏o���p�x��\��������o���܂� */
    euc_case     = prob_euc_table[c[0] - 0xA0][c[1] - 0xA1] + 1;
    mskanji_case = prob_mskanji_table[c[0] - 0xa0][c[1] - 0xA1] + 1;

    /* ���ꂼ��̉\���ɂ��ăx�C�Y���v�u�I�v�ɗ^���܂��B����͐��K��
     * �̂��߂̍��ł��B*/
    *prob_euc     += euc_case / (euc_case + mskanji_case);
    *prob_mskanji += mskanji_case / (euc_case + mskanji_case);
}

/* �����̃R�[�f�B���O���������肷�郋�[�`�� 
 * 
 * buffer[] �ɗ^����ꂽ������ 1 byte ���Ɍ��Ă����Č��肷��B
 * ������񍬍݂��Ă����ꍇ�̓���͕ۏ؂���Ȃ��B�܂� jisx0208 
 * �� 90 �N�łɋK�肳�ꂽ��������������B�����ɂ� JISC6226 �� 
 * 83 �͂ق�̏��������������̂����ǁc
 *
 * ����������̃��[�J�[�������g�p���Ă���R�[�h�|�C���g�͌�
 * �Ȃ��B���� NEC �� 98 �ŗL�̊g���ɂ��Ă͕����Ƃ͌��Ȃ��B��
 * ��ȊO�̕������猈�肳���B
 *
 * h_euc ��EUC��MS�����̂�����Ƃ����߉\�ȕ��������̏ꍇ�� 
 * EUC �ł��鎖�O�m����^����B�Ⴆ�Η^���Ε��͂̂��� 90% ���x
 * �� EUC �ł���ƍl������΂��̒l�� 0.9 �ɂ���B�t��MS����
 * �� 70% ���炢�Ɗ��҂ł���� 0.3 �ɂ���B�悭�킩��Ȃ���� 
 * 0.5 �ɂ��Ă����Ă�����Ȃ�ɂ悢���ʂ�������͂��B */

static enum KANJI_CODE
decide_kanji_coding_type(
        const unsigned char *buffer,
        double              h_euc
    )
{
    const unsigned char *c;

    double  prob_euc, prob_mskanji, prob_chars; /* EUC �� MS��������ӂɌ�
                        ��ł��Ȃ����Ɏ��O�m���������Č��肷�邽�߂̕ϐ�
                        ���܂茵���Ȍ����͂��ĂȂ��̂ł��Ȃ��ł� */

    enum KANJI_CODE unknown = KC_UNKNOWN; /* �����R�[�h�����m�̏ꍇ�̋�ʗp�B
                        MSB �� 1 �̕������������̂ɁA���ꂪ EUC �ł� MS 
                        �����ł��Ȃ���΂���� BROKEN �ɂ���B�Ō�ɖ��m
                        �̂܂܂Ȃ炱�̒l��Ԃ��B
                        NEC��98�ŗL�̊g�����������̍s�ɂ��Ă͂��� 
                        BROKEN ��Ԃ��܂��B ���ێ��͓ǂގ�i���Ȃ����c */

    /* EUC �� MS�����������G���R�[�f�B���O���������Ƀ`�F�b�N���܂� */

    /* �ŏ��� 3 �͋� junet �ȗ��g�p����Ă���R�[�f�B���O�� 
       iso-2022 �� jisx0208-90 �̊g���������Ă���܂��B������
       ���� JISC6226 �� JISX0208* �� EUC, MS��������u���Ă���
       �̂͐��m�ɂ͐���������܂���B*/

    /* JISC6226_78 ��? */
    for ( c = buffer; *c != '\0'; c++ )
        if ( c[0] == '\033' )
            if ( c[1] == '$' )
                if ( c[2] == '@' )
                    return KC_JISC6226_78;

    /* JISX0208_83 ��? */
    for ( c = buffer; *c != '\0'; c++ )
        if ( c[0] == '\033' )
            if ( c[1] == '$' )
                if ( c[2] == 'B' )
                    return KC_JISX0208_83;

    /* JISX0208_90 ��? */
    for ( c = buffer; *c != '\0'; c++ )
        if ( c[0] == '\033' )
            if ( c[1] == '&' )
                if ( c[2] == '@' )
                    if ( c[3] == '\033' )
                        if ( c[4] == '$' )
                            if ( c[5] == 'B' )
                                return KC_JISX0208_90;

    /* EUC �� MS�����̃e�X�g */

    /* ���v�l�̏����� */
    prob_euc     = 0.0; /* EUC �ł���\���𔽉f�����ώZ�l������܂�       */
    prob_mskanji = 0.0; /* MS�����ł���\���𔽉f�����ώZ�l������܂�     */
    prob_chars   = 0.0; /* �����̃R�[�f�B���O�̉\�������镶����������܂� */

    /* �s�̐擪����u�炵���v�������T�[�`���� */
    for ( c = buffer; *c != '\0'; ) {
        if ( (c[0] & 0x80) == 0 ) { /* ����͂ǂ���ł��Ȃ�����ǂݔ�΂� */
            c++;
        }
        else {
            if ( is_euc(c) ) {  /* EUC �Ƃ��ĔF���ł���ꍇ */
                if ( is_mskanji(c))  {  /* �ň��P�[�X�B�ݒ�s�ǖ�� */
                    calc_probability( c, &prob_euc, &prob_mskanji );
                    prob_chars++;
                }
                else {  /* ���̕������ EUC �Ƃ��Ă����F���ł��Ȃ� */
                    return KC_EUC;
                }
            }
            else {  /* EUC �ł͂Ȃ��ꍇ */
                if ( is_mskanji(c) ) {  /* ���̕������ MS�����Ƃ��Ă����F���ł��Ȃ� */
                    return KC_MSKANJI;
                }
                else {  /* ����͕ς� */
                    unknown = KC_BROKEN;
                }
            }
            c += 2; /* 2 �����ǂݔ�΂� */
        }
    }
    if ( prob_chars > 0.0 ) {   /* �����ꂩ�Ǝv���镶�����݂����� */
        return ( ((prob_euc * h_euc) >= (prob_mskanji * (1.0 - h_euc)))
                    ? KC_EUC
                    : KC_MSKANJI );
    }

    /* ���ǉ����킩��Ȃ��������͂��̂܂܃��^�[�� ... ���ӔC :-) */
    return unknown;
}
/* �����R�[�h���ʏ���: �����܂� */



/*
 *  �����R�[�h�ϊ�����
 *    GNU iconv ���C�u�����𗘗p
 */
char    *
convertCode( const char *p, const char *inCode, const char *outCode )
{
    char                *inbuf;
    Thread static char  outbuf[BUFFER_SIZE * 2 + 1];
    int                 result;
    size_t              inbufSiz  = BUFFER_SIZE;
    size_t              outbufSiz = BUFFER_SIZE * 2;
    iconv_t             cd;
    char                *inp;
    char                *outp;

    if ( outbuf[0] ) {
        register char   *p = outbuf;

        while ( *p ) {
            *p++ = NUL;
            if ( p > outbuf + BUFFER_SIZE * 2 )
                break;
        }
    }
    cd = iconv_open( outCode, inCode );
    if ( cd == NULL )
        return ( NULL );

    inbufSiz = (p ? strlen(p) : BUFFER_SIZE) + 1;
    inbuf    = (char *)malloc( inbufSiz );
    if ( !inbuf ) {
        iconv_close( cd );
        return ( NULL );
    }

    strcpy( inbuf, p );
    inp       = inbuf;
    outp      = outbuf;
    inbufSiz  = strlen( inp );
    outbufSiz = BUFFER_SIZE * 2;
    result = iconv( cd,
                    &inp,  &inbufSiz,
                    &outp, &outbufSiz );

    iconv_close( cd );

    if ( result < 0 ) {
        unsigned char   *q = (unsigned char *)inp;
        if (!strcmp( inCode, "UTF-8" ) &&
            (((*q == 0xe2) && (*(q + 1) == 0x80) && (*(q + 2) == 0x94)) ||
             ((*q == 0xe2) && (*(q + 1) == 0x88) && (*(q + 2) == 0x92)) ||
             ((*q == 0xef) && (*(q + 1) == 0xbc) && (*(q + 2) == 0x8d))   )) {
            /* �ȉ��A�ϊ��Ɏ��s����ꍇ�̑΍� */
            char            *r;
            unsigned char   *s;
            char            *temp1 = (char *)malloc( BUFFER_SIZE * 2 + 1 );
            char            *temp2 = (char *)malloc( BUFFER_SIZE * 2 + 1 );
            if ( !temp1 || !temp2 ) {
                if ( temp2 )
                    free( temp2 );
                if ( temp1 )
                    free( temp1 );
                free( inbuf );
                return ( NULL );
            }

            /* �����I�� "�\" �� unfication ���� */
#if 0
            *q       = 0xe2;
            *(q + 1) = 0x80;
            *(q + 2) = 0x95;
#else
            s = q;
            while ( *s ) {
                if (((*s == 0xe2) && (*(s+1) == 0x80) && (*(s+2) == 0x94))||
                    ((*s == 0xe2) && (*(s+1) == 0x88) && (*(s+2) == 0x92))||
                    ((*s == 0xef) && (*(s+1) == 0xbc) && (*(s+2) == 0x8d))  ){
                    *s++ = 0xe2;
                    *s++ = 0x80;
                    *s++ = 0x95;
                }
                else
                    s++;
            }
#endif
            strcpy( temp1, outbuf );
            strcpy( temp2, inp );

            r = convertCode( temp2, inCode, outCode );
            if ( r ) {
                strcat( temp1, outbuf );
                strcpy( outbuf, temp1 );

                free( temp2 );
                free( temp1 );
                free( inbuf );
                return ( outbuf );
            }

            free( temp2 );
            free( temp1 );
        }
        free( inbuf );

        return ( NULL );
    }
    free( inbuf );

    return ( outbuf );
}


/* Shift_JIS �� EUC-JP �ϊ� */
char    *
sjis2euc( const char *p )
{
    char    *s = convertCode( p, "CP932", "EUC-JP" );

    if ( !s &&
         (decide_kanji_coding_type((unsigned char *)p, 0.5) == KC_MSKANJI) ) {
        char    *temp = malloc( strlen( p ) + BUFSIZ );
        
        if ( temp ) {
            strcpy( temp, p );
            regular( temp );
            s = convertCode( temp, "CP932", "EUC-JP" );
            free( temp );
        }
    }

    return ( s );
}


/* Shift_JIS �� UTF-8 �ϊ� */
char    *
sjis2utf( const char *p )
{
    char    *s = convertCode( p, "CP932", "UTF-8" );

    if ( !s &&
         (decide_kanji_coding_type((unsigned char *)p, 0.5) == KC_MSKANJI) ) {
        char    *temp = malloc( strlen( p ) + BUFSIZ );
        
        if ( temp ) {
            strcpy( temp, p );
            regular( temp );
            s = convertCode( temp, "CP932", "UTF-8" );
            free( temp );
        }
    }

    return ( s );
}


/* UTF-8 �� EUC-JP �ϊ� */
char    *
utf2euc( const char *p )
{
    char            *q, *r;
    unsigned char   aaa[4];
    int             flag = 0;

    /* "�`" (UTF-8 �� 0xEF 0xBD 0x9E) ���܂ޕ�����̏ꍇ�A */
    /* iconv() ���ϊ��Ɏ��s���邽�߂̑΍�                  */
    aaa[0] = 0xEF; aaa[1] = 0xBD; aaa[2] = 0x9E; aaa[3] = 0x00;
    if ( ( q = strstr( p, (char *)aaa ) ) != NULL ) {
        *q++ = '_';
        *q++ = '_';
        *q++ = '_';
        flag = 1;
    }

    q = convertCode( p, "UTF-8", "EUC-JP" );
    if ( q && flag ) {
        r = strstr( q, "___" );
        while ( r ) {
            *r = '\0';
            strcat( q, "�`" );
            strcat( q, r + 3 );
            r = strstr( q, "___" );
        }
    }
    else if ( flag ) {
        /* "�B�`" ���̃p�^�[���̏ꍇ�A��������ϊ��Ɏ��s���邪�A */
        /* "�`" �� "___" �ɒu����A�ēx�ϊ������݂�Ɛ�������    */
        return ( utf2euc( p ) ); /* �ēx�ϊ� */
    }

    return ( q );
}


/* ISO-2022-JP �� Shift_JIS �ϊ� */
char    *
jis2sjis( const char *p )
{
    return ( convertCode( p, "ISO-2022-JP", "CP932" ) );
}


/* ISO-2022-JP �� EUC-JP �ϊ� */
char    *
jis2euc( const char *p )
{
    return ( convertCode( p, "ISO-2022-JP", "EUC-JP" ) );
}


/* ISO-2022-JP �� UTF-8 �ϊ� */
char    *
jis2utf( const char *p )
{
    return ( convertCode( p, "ISO-2022-JP", "UTF-8" ) );
}


/* EUC-JP �� Shift_JIS �ϊ� */
char    *
euc2sjis( const char *p )
{
    char    *s = convertCode( p, "EUC-JP", "CP932" );

    if ( !s )
        if ( decide_kanji_coding_type( (unsigned char *)p, 0.5 ) == KC_EUC )
            s = euc2sjisEx( p );

    return ( s );
}


/* EUC-JP �� UTF-8 �ϊ� */
char    *
euc2utf( const char *p )
{
    return ( convertCode( p, "EUC-JP", "UTF-8" ) );
}


/* UTF-8 �� Shift_JIS �ϊ� */
char    *
utf2sjis( const char *p )
{
    char            *q, *r;
    unsigned char   aaa[4];
    int             flag = 0;

    /* "�`" (UTF-8 �� 0xEF 0xBD 0x9E) ���܂ޕ�����̏ꍇ�A */
    /* iconv() ���ϊ��Ɏ��s���邽�߂̑΍�                  */
    aaa[0] = 0xEF; aaa[1] = 0xBD; aaa[2] = 0x9E; aaa[3] = 0x00;
    if ( ( q = strstr( p, (char *)aaa ) ) != NULL ) {
        *q++ = '_';
        *q++ = '_';
        *q++ = '_';
        flag = 1;
    }

    q = convertCode( p, "UTF-8", "CP932" );
    if ( q && flag ) {
        r = strstr( q, "___" );
        while ( r ) {
            *r = '\0';
            strcat( q, "�`" );
            strcat( q, r + 3 );
            r = strstr( q, "___" );
        }
    }
    else if ( flag ) {
        /* "�B�`" ���̃p�^�[���̏ꍇ�A��������ϊ��Ɏ��s���邪�A */
        /* "�`" �� "___" �ɒu����A�ēx�ϊ������݂�Ɛ�������    */
        return ( utf2sjis( p ) ); /* �ēx�ϊ� */
    }

    return ( q );
}


/* ISO-8859-1 �� UTF-8 �ϊ� */
char    *
iso8859_1toUtf8( const char *p )
{
    return ( convertCode( p, "ISO-8859-1", "UTF-8" ) );
}


/* iconv �Ő��擾 */
char    *
getIconvVersion( char *buf, size_t bufSize )
{
    char        *p = buf;
    size_t      sz = bufSize;
    static char version[BUFSIZ];

    sprintf( version, "libiconv: FileVersion %d.%d.0.0",
             _libiconv_version >> 8, _libiconv_version & 0xFF );

    if ( buf && (bufSize > 0) ) {
        strncpy( p, version, sz - 1 );
        p[sz - 1] = NUL;
    }
    else
        p = version;

    return ( p );
}
