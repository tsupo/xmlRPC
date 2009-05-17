/*
 *  任意の文字列をURLエンコードする
 *
 *        Copyleft (c) 2004, 2005 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  05 Feb 2004
 *
 * History:
 * $Log: /comm/xmlRPC/misc/encodeURL.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 28    09/03/30 19:48 Tsujimura543
 * OAuth 対応
 * 
 * 27    08/11/17 21:56 Tsujimura543
 * static → Thread static に変更
 * 
 * 26    08/05/15 19:27 Tsujimura543
 * (1) encodeURL() 内の sz2 の計算式を元に戻す
 * (2) encodeURL2(), encodeURLex(), translateURL() 内で使うバッファ
 *     も可変サイズ化した
 * 
 * 25    08/05/15 19:16 Tsujimura543
 * encodeURL() 内の sz2 の計算式を変更 (今までの値の2倍に変更)
 * 
 * 24    07/09/07 18:29 Tsujimura543
 * replaceEntityStrings() に第2引数を追加。Shift_JIS 以外の場合にも対応
 * 
 * 23    07/09/07 17:03 Tsujimura543
 * replaceEntityStrings() を追加
 * 
 * 22    07/01/29 13:21 Tsujimura543
 * encodeURLex() でも (#xxx; の ; を除き) ; をパーセントエスケープ対象に
 * するようにした
 * 
 * 21    06/07/18 20:44 Tsujimura543
 * &raquo; 対策 (はてなブックマークの挙動変更に伴う修正)
 * 
 * 20    06/05/15 22:40 Tsujimura543
 * encodeURL() 内で確保する out の大きさを修正(文字列 pp の長さを元に算出)
 * 
 * 19    06/02/27 21:03 Tsujimura543
 * 「実体参照→代替文字列変換テーブル」の実体を codeTbl.c として分離独立
 * 
 * 18    06/02/27 20:57 Tsujimura543
 * rep[] → entity_code_repTbl[] に名前を変更
 * 
 * 17    06/02/27 20:32 Tsujimura543
 * 実体参照→代替文字列変換テーブル関連の定義を codeTbl.h として
 * 分離独立させた
 * 
 * 16    06/02/25 0:06 Tsujimura543
 * encodeURLexX() 用のコード変換テーブルを完成させた
 * (いずれは別ファイルに分離する予定)
 * 
 * 15    06/02/23 1:07 Tsujimura543
 * encodeURLex2() を修正。del.icio.us へのブックマーク投稿にて動作確認。
 * 
 * 14    06/02/22 17:13 Tsujimura543
 * encodeURLex4() を追加
 * 
 * 13    06/02/22 16:48 Tsujimura543
 * encodeURLex3() を追加
 * 
 * 12    05/11/11 15:59 Tsujimura543
 * TM (&trade;) に関する処理を入れてみた(暫定)
 * 
 * 11    05/10/29 1:12 Tsujimura543
 * ブックマーク登録時に使用する処理を各々見直した(動作確認済み)
 * 
 * 10    05/10/28 22:03 Tsujimura543
 * encodeURLex() を修正 ('?' に変換していた分を "%3f" に変換するよう修正)
 * 
 * 9     05/10/28 21:00 Tsujimura543
 * encodeURLex2() を試験的に導入してみた
 * 
 * 8     05/10/28 18:22 Tsujimura543
 * encodeURLex() を追加
 * 
 * 7     05/05/30 20:22 Tsujimura543
 * A～Z, a～z, 0～9 と _ はエンコードせずにそのまま出力するようにした
 * (送信電文のバイト数を減らす効果がある)
 * 
 * 6     04/11/15 17:05 Tsujimura543
 * 引数が NULL のとき、領域解放するようにした
 * 
 * 5     04/11/15 11:09 Tsujimura543
 * translateURL() を追加
 * 
 * 4     04/11/02 21:10 Tsujimura543
 * バッファ確保失敗時は、オリジナルの文字列をそのまま返すようにした
 * 
 * 3     04/11/02 21:08 Tsujimura543
 * バッファを動的に確保するように変更。バッファサイズも増やす。
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
                    case CD_NBSP:   /* &nbsp; → 空白文字に置換 */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = '0';
                        break;
                    case CD_IEXCL:  /* &iexcl;(!の上下さかさま) → ! に置換 */
                        *q++ = '!';
                        break;
                    case CD_CENT:   /* &cent; (￠) → c に置換 */
                        *q++ = 'c';
                        break;
                    case CD_POUND:  /* &pound; (￡) → p に置換 */
                        *q++ = 'p';
                        break;
                    case CD_CURREN: /* &curren; → ? に置換 */
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'f';
                        break;
                    case CD_YEN:    /* &yen; → \ に置換 */
                        *q++ = '%';
                        *q++ = '5';
                        *q++ = 'c';
                        break;
                    case CD_BRVBAR: /* &brvbar; → | に置換 */
                        *q++ = '%';
                        *q++ = '7';
                        *q++ = 'c';
                        break;
                    case CD_SECT:   /* &sect; (§) → s に置換 */
                        *q++ = 's';
                        break;
                    case CD_COPY:   /* &copy; → (c) に置換 */
                        *q++ = '%'; /* ( */
                        *q++ = '2'; /* ( */
                        *q++ = '8'; /* ( */
                        *q++ = 'c';
                        *q++ = '%'; /* ) */
                        *q++ = '2'; /* ) */
                        *q++ = '9'; /* ) */
                        break;
                    case CD_ORDF:   /* &ordf; (上付きa) → a に置換 */
                        *q++ = 'a';
                        break;
                    case CD_ORDM:   /* &ordm; (上付きo) → o に置換 */
                        *q++ = 'o';
                        break;
                    case CD_LAQUO:  /* &laquo; (≪) → << に置換 */
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'c';
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'c';
                        break;
                    case CD_NOT:    /* &not; (￢) → 'not ' に置換 */
                        *q++ = 'n';
                        *q++ = 'o';
                        *q++ = 't';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = '0';
                        break;
                    case CD_SHY:    /* &shy; → - に置換 */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'd';
                        break;
                    case CD_REG:    /* &reg; → (R) に置換 */
                        *q++ = '%'; /* ( */
                        *q++ = '2'; /* ( */
                        *q++ = '8'; /* ( */
                        *q++ = 'R';
                        *q++ = '%'; /* ) */
                        *q++ = '2'; /* ) */
                        *q++ = '9'; /* ) */
                        break;
                    case CD_MACR:   /* &macr; → ~ に置換 */
                        *q++ = '%';
                        *q++ = '7';
                        *q++ = 'e';
                        break;
                    case CD_DEG:    /* &deg; ( °) → d に置換 */
                        *q++ = 'd';
                        break;
                    case CD_PLUSMN: /* &plusmn; (±) → +- に置換 */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'b';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'd';
                        break;
                    case CD_SUP2:   /* &sup2; (上付き2) → 2 に置換 */
                        *q++ = '2';
                        break;
                    case CD_SUP3:   /* &sup3; (上付き3) → 3 に置換 */
                        *q++ = '3';
                        break;
                    case CD_ACUTE:  /* &acute; (´) → ' に置換 */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = '7';
                        break;
                    case CD_MICRO:  /* &micro; (μ) → u に置換 */
                        *q++ = 'u';
                        break;
                    case CD_PARA:   /* &para; (¶) → * に置換 */
                    case CD_MIDDOT: /* &middot; (・) → * に置換 */
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'a';
                        break;
                    case CD_SUP1:   /* &sup1; (上付き1) → 1 に置換 */
                        *q++ = '1';
                        break;
                    case CD_RAQUO:  /* &raquo; (≫) → >> に置換 */
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'e';
                        *q++ = '%';
                        *q++ = '3';
                        *q++ = 'e';
                        break;
                    case CD_FRAC14: /* &frac14; → 1/4 に置換 */
                        *q++ = '1';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'f';
                        *q++ = '4';
                        break;
                    case CD_FRAC12: /* &frac12; → 1/2 に置換 */
                        *q++ = '1';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'f';
                        *q++ = '2';
                        break;
                    case CD_FRAC34: /* &frac34; → 3/4 に置換 */
                        *q++ = '3';
                        *q++ = '%';
                        *q++ = '2';
                        *q++ = 'f';
                        *q++ = '4';
                        break;
                    case CD_IQUEST: /* &iquest;(?の上下さかさま) → ?に置換 */
                        *q++ = '?';
                        break;
                    case CD_AGRAVE: /* &Agrave; (A の上に ` ) → A に置換 */
                    case CD_AACUTE: /* &Aacute; (A の上に ´) → A に置換 */
                    case CD_ACIRC:  /* &Acirc;  (A の上に ^ ) → A に置換 */
                    case CD_ATILDE: /* &Atilde; (A の上に ~ ) → A に置換 */
                    case CD_AUML:   /* &Auml;   (A の上に ¨) → A に置換 */
                    case CD_ARING:  /* &Aring;  (A の上に o ) → A に置換 */
                        *q++ = 'A';
                        break;
                    case CD_AELIG:  /* &AElig; (A と E が合体) → AE に置換 */
                        *q++ = 'A';
                        *q++ = 'E';
                        break;
                    case CD_CCEDIL: /* &Ccedil;  (C の下に ,) → C に置換 */
                        *q++ = 'C';
                        break;
                    case CD_EGRAVE: /* &Egrave; (E の上に ` ) → E に置換 */
                    case CD_EACUTE: /* &Eacute; (E の上に ´) → E に置換 */
                    case CD_ECIRC:  /* &Ecirc;  (E の上に ^ ) → E に置換 */
                    case CD_EUML:   /* &Euml;   (E の上に ¨) → E に置換 */
                        *q++ = 'E';
                        break;
                    case CD_IGRAVE: /* &Igrave; (I の上に ` ) → I に置換 */
                    case CD_IACUTE: /* &Iacute; (I の上に ´) → I に置換 */
                    case CD_ICIRC:  /* &Icirc;  (I の上に ^ ) → I に置換 */
                    case CD_IUML:   /* &Iuml;   (I の上に ¨) → I に置換 */
                        *q++ = 'I';
                        break;
                    case CD_ETH:    /* &ETH; (- 付きの D) → D に置換 */
                        *q++ = 'D';
                        break;
                    case CD_NTILDE: /* &Ntilde; (N の上に ~ ) → N に置換 */
                        *q++ = 'N';
                        break;
                    case CD_OGRAVE: /* &Ograve; (O の上に ` ) → O に置換 */
                    case CD_OACUTE: /* &Oacute; (O の上に ´) → O に置換 */
                    case CD_OCIRC:  /* &Ocirc;  (O の上に ^ ) → O に置換 */
                    case CD_OTILDE: /* &Otilde; (O の上に ~ ) → O に置換 */
                    case CD_OUML:   /* &Ouml;   (O の上に ¨) → O に置換 */
                    case CD_OSLASH: /* &Oslash; (斜線付きの O) → O に置換 */
                        *q++ = 'O';
                        break;
                    case CD_TIMES:  /* &times; (×) → X に置換 */
                        *q++ = 'X';
                        break;
                    case CD_UGRAVE: /* &Ugrave; (U の上に ` ) → U に置換 */
                    case CD_UACUTE: /* &Uacute; (U の上に ´) → U に置換 */
                    case CD_UCIRC:  /* &Ucirc;  (U の上に ^ ) → U に置換 */
                    case CD_UUML:   /* &Uuml;   (U の上に ¨) → U に置換 */
                        *q++ = 'U';
                        break;
                    case CD_YACUTE: /* &Yacute; (Y の上に ´) → Y に置換 */
                        *q++ = 'Y';
                        break;
                    case CD_THORN:  /* &THORN; (巨 によく似たT) → T に置換 */
                        *q++ = 'T';
                        break;
                    case CD_SZLIG:  /* &szlig; (エスツェット) → ss に置換 */
                        *q++ = 's';
                        *q++ = 's';
                        break;
                    case CD_AGRAVEs:/* &agrave; (a の上に ` ) → a に置換 */
                    case CD_AACUTEs:/* &aacute; (a の上に ´) → a に置換 */
                    case CD_ACIRCs: /* &acirc;  (a の上に ^ ) → a に置換 */
                    case CD_ATILDEs:/* &atilde; (a の上に ~ ) → a に置換 */
                    case CD_AUMLs:  /* &auml;   (a の上に ¨) → a に置換 */
                    case CD_ARINGs: /* &aring;  (a の上に o ) → a に置換 */
                        *q++ = 'a';
                        break;
                    case CD_AELIGs: /* &aelig; (a と e が合体) → ae に置換 */
                        *q++ = 'a';
                        *q++ = 'e';
                        break;
                    case CD_CCEDILs:/* &ccedil;  (c の下に ,) → c に置換 */
                        *q++ = 'c';
                        break;
                    case CD_EGRAVEs:/* &egrave; (e の上に ` ) → e に置換 */
                    case CD_EACUTEs:/* &eacute; (e の上に ´) → e に置換 */
                    case CD_ECIRCs: /* &ecirc;  (e の上に ^ ) → e に置換 */
                    case CD_EUMLs:  /* &euml;   (e の上に ¨) → e に置換 */
                        *q++ = 'e';
                        break;
                    case CD_IGRAVEs:/* &igrave; (i の上に ` ) → i に置換 */
                    case CD_IACUTEs:/* &iacute; (i の上に ´) → i に置換 */
                    case CD_ICIRCs: /* &icirc;  (i の上に ^ ) → i に置換 */
                    case CD_IUMLs:  /* &iuml;   (i の上に ¨) → i に置換 */
                        *q++ = 'i';
                        break;
                    case CD_ETHs:   /* &eth; (- 付きの d) → d に置換 */
                        *q++ = 'd';
                        break;
                    case CD_NTILDEs:/* &ntilde; (n の上に ~ ) → n に置換 */
                        *q++ = 'n';
                        break;
                    case CD_OGRAVEs:/* &ograve; (o の上に ` ) → o に置換 */
                    case CD_OACUTEs:/* &oacute; (o の上に ´) → o に置換 */
                    case CD_OCIRCs: /* &ocirc;  (o の上に ^ ) → o に置換 */
                    case CD_OTILDEs:/* &otilde; (o の上に ~ ) → o に置換 */
                    case CD_OUMLs:  /* &ouml;   (o の上に ¨) → o に置換 */
                    case CD_OSLASHs:/* &oslash; (斜線付きの o) → o に置換 */
                        *q++ = 'o';
                        break;
                    case CD_DIVIDE: /* &divide; (÷) → / に置換 */
                        *q++ = '/';
                        break;
                    case CD_UGRAVEs:/* &ugrave; (u の上に ` ) → u に置換 */
                    case CD_UACUTEs:/* &uacute; (u の上に ´) → u に置換 */
                    case CD_UCIRCs: /* &ucirc;  (u の上に ^ ) → u に置換 */
                    case CD_UUMLs:  /* &uuml;   (u の上に ¨) → u に置換 */
                        *q++ = 'u';
                        break;
                    case CD_YACUTEs:/* &yacute; (y の上に ´) → y に置換 */
                    case CD_YUMLs:  /* &yuml; (y の上に ¨) → y に置換 */
                        *q++ = 'y';
                        break;
                    case CD_THORNs: /* &thorn; (p と b が合体) → t に置換 */
                        *q++ = 't';
                        break;

                    case CD_UML:    /* &uml; (¨) → 除去 */
                    case CD_CEDIL:  /* &cedil; (c の下につく ,) → 除去 */
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
                        p += 2; /* ここに来ることはないはず */
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
                /* &trade; → TM に置換 */
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
        char *src   /* (I/O) UTF-8 文字列 */
    )
{
    char    *p, *q;
    char    tmp1[8], tmp2[8];

    strcpy( tmp1, sjis2utf( "≫" ) );
    strcpy( tmp2, sjis2utf( "≪" ) );
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

/* 暫定版 */
char	*
encodeURLex2(
        const char *p /* (I) UTF-8 文字列 */
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

    /* ISO-8859-1 の特殊文字(0xA0～0xFF) に対処するための処理 */
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

    /* いったんデコードしてから */
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

    /* 改めてエンコード */
    return ( encodeURL2( (char *)temp ) );
}


char	*
encodeURLex3(
        const char *p /* (I) EUC-JP 文字列 */
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

    /* いったんデコードしてから */
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

    /* 改めてエンコード */
    return ( encodeURL2( (char *)temp ) );
#else
    /* いったんデコードしてから */
    q = replaceEntityStrings( p, CHARSET_EUCJP );
    r = NULL;
    if ( q ) {
        /* 改めてエンコード */
        r = encodeURL2( q );
        replaceEntityStrings( NULL, CHARSET_UNKNOWN );
    }

    return ( r );
#endif
}

char	*
encodeURLex4(
        const char *p /* (I) Shift_JIS 文字列 */
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

    /* いったんデコードしてから */
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

    /* 改めてエンコード */
    return ( encodeURL2( (char *)temp ) );
#else
    /* いったんデコードしてから */
    q = replaceEntityStrings( p, CHARSET_SHIFTJIS );
    r = NULL;
    if ( q ) {
        /* 改めてエンコード */
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
