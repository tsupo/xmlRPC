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
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 12    08/11/17 21:56 Tsujimura543
 * static → Thread static に変更
 * 
 * 11    08/05/20 22:49 Tsujimura543
 * hatenaApi.c の searchKeyword() 経由で呼び出されたときに、何らかの
 * メモリ破壊が原因で落ちる現象に対する応急処置を実施
 * 
 * 10    07/07/03 11:18 Tsujimura543
 * Visual Studio 2005 でのビルド結果を反映
 * 
 * 9     07/02/21 19:02 Tsujimura543
 * 内部バッファサイズを [BUFSIZ * 2] から [MAX_CONTENT_SIZE] に変更
 * (BUFSIZ * 2 より長い文字列を扱う必要が発生したため)
 * 
 * 8     05/11/11 16:01 Tsujimura543
 * UTF-8 で 0xe2 0x84 0xa2 (&trade; すなわち TM 相当の文字コード) が存在
 * する場合は、" TM"に置換するようにした
 * 
 * 7     05/10/28 21:16 Tsujimura543
 * ソースコードを整理
 * 
 * 6     05/10/28 14:20 Tsujimura543
 * デバッグ用のコードを削除
 * 
 * 5     05/10/28 14:12 Tsujimura543
 * (c) マーク以外の ISO-8859-1 独自文字(0xA0～0xFF)にも対処できるようにした
 * 
 * 4     05/10/27 20:47 Tsujimura543
 * バグ修正、動作確認済み
 * 
 * 3     05/10/27 20:36 Tsujimura543
 * (1) (c) マークが直接埋め込まれている場合は &#169; に置換するようにした
 * (2) &amp;amp; → &amp; に置換するようにした
 * 
 * 2     04/07/07 11:56 Tsujimura543
 * ちょっとした修正
 * 
 * 1     04/07/07 11:24 Tsujimura543
 * 版数管理を RCS から VSS へ移行
 *
 * Revision 1.5  2003/11/11  07:07:10  tsujimura543
 * const 指定を付加
 *
 * Revision 1.4  2003/11/11  07:02:19  tsujimura543
 * K&R 表記 → ANSI C 表記 に完全移行
 *
 * Revision 1.3  2003/03/11  12:13:53  tsujimura543
 * コメントを整理
 *
 * Revision 1.2  2003/03/11  01:45:55  tsujimura543
 * RCSコメントを埋め込むようにする
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
    /* 注: (今のところ、原因不明の)メモリ破壊による被害を無害化するための */
    /*     応急処置として、out のサイズを2倍に設定(原因特定、対策実施し次 */
    /*     第、元に戻す)                                       2008.05.20 */

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
        /* ISO-8859-1 の特殊文字(0xA0～0xFF) に対処するための処理          */
        /*  -- UTF-8 では 0xC2 が直前に付加されている                      */
        /*        註: 0xC2(16進) = 194(10進) = 302(8進)                    */
        /*            0xA0(16進) = 160(10進) = 240(8進)                    */
        /*  -- いわゆる「半角カナ」を ISO-8591-1 の特殊文字だと誤判定して  */
        /*     しまう可能性は残る (例えば &copy; は ツゥ (の半角表記) と区 */
        /*     別できない                                                  */
        /*  -- 0xA0 は &nbsp;(&#160;)あるいは単純に空白文字に置換すべきか? */
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
        /* 0xe2 0x84 0xa2 → TM (&trade;) */
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
