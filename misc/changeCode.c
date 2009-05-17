/*
 *  漢字コード変換
 *    ある文字コードの文字列を別の文字コードに変換する
 *
 *        Copyleft (c) 2004 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  05 Feb 2004
 *
 * History:
 * $Log: /comm/xmlRPC/misc/changeCode.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 19    08/11/27 15:08 Tsujimura543
 * getIconvVersion() の出力形式をさらに変更
 * 
 * 18    08/11/27 15:06 Tsujimura543
 * getIconvVersion() の出力形式を変更
 * 
 * 17    08/11/27 14:48 Tsujimura543
 * getIconvVersion() を追加
 * 
 * 16    08/11/17 21:46 Tsujimura543
 * static char → Thread static char に変更
 * 
 * 15    07/11/13 22:20 Tsujimura543
 * わからなくなってしまっていた「文字コード判別処理」の出典をようやく
 * 突き止めることに成功。出典を明示した
 * 
 * 14    06/11/16 1:15 Tsujimura543
 * convertCode() 中で memset() を使わないように書き換えてみた
 * 
 * 13    06/11/15 23:27 Tsujimura543
 * convertCode() 内の余分な memset() 呼び出しを削除
 * 
 * 12    06/05/11 15:19 Tsujimura543
 * convertCode() 内で使用する inbuf のサイズを動的に決定するように変更
 * 
 * 11    06/03/22 16:53 Tsujimura543
 * convertCode() が無限に再帰するのを防止するための修正を実施
 * 
 * 10    06/02/09 22:53 Tsujimura543
 * BUFFER_SIZE を2倍の値に変更
 * 
 * 9     06/02/08 16:46 Tsujimura543
 * メモリを解放し忘れる経路があった → 修正済み
 * 
 * 8     05/12/22 19:08 Tsujimura543
 * UTF-8 文字列を euc2sjis() や sjis2utf() に渡すと期待しない動作をする
 * ようになってしまったのを修正
 * 
 * 7     05/12/21 18:49 Tsujimura543
 * 機種依存文字が含まれる場合、euc2sjis() の中から euc2sjisEx() を呼び出す
 * ようにすることで、処理を続行できるようにした 
 * 
 * 6     05/11/11 0:15 Tsujimura543
 * UTF-8 → Shift_JIS 変換が失敗するいくつかのケースに対する対策を実施
 * 
 * 5     05/10/28 15:36 Tsujimura543
 * iso8859_1toUtf8() を追加
 * 
 * 4     04/11/01 21:02 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 3     04/11/01 19:56 Tsujimura543
 * バッファサイズ変更
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

/* 文字コード判別処理: ここから */
/*
 *  漢字コード簡易判定
 *      出典: fj に投稿された記事 (1996年)
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

/* 漢字のコーディング方式を記述する ENUM です。
 *
 * UNKNOWN: 何かわからなかった
 * BROKEN: MSB が 1 のコードが発見されたが EUC でもMS漢字でもなかった
 * JISC6226_78, JISX0208_83, JISX0208_90: 言わゆる 'JIS'。区別する必要あるかな?
 * EUC: 拡張UNIX?? だったかな? しばしば UNIX のベンダーが提供するコーディ
 *      ング方式。ちなみに EUC と DEC 漢字の違いは御存知ですか? (^o^)
 * MSKANJI: マイクロソフト社が定義した漢字のコーディング。これを ShiftJIS 
 *      と呼ぶのが正しいのかどうかわからない。いずれにせよあまり使い勝手の
 *      いいものではない。 */

/* *c によって与えられた 2 バイト c[0]c[1] が表現する文字が EUC として
   解釈できるかどうか調べます。*/
static int
is_euc( const unsigned char *c )
{
    int pos, bit;

    pos = (c[0] & 0x7f) * 8 + (c[1] / 32 | 4);
    bit = (0x80000000 >> (c[1] & 31));

    return ( (kanji_jiscode_euc[pos] & bit) ? 1 : 0 );
}

/* *c によって与えられた 2 バイト c[0]c[1] が表現する文字がMS漢字とし
   て解釈できるかどうか調べます。*/
static int
is_mskanji( const unsigned char *c )
{
    int pos, bit;

    pos = (c[0]&0x7f) * 8 + (c[1] / 32);
    bit = (0x80000000 >> (c[1] & 31));

    return ( (kanji_jiscode_mskanji[pos] & bit) ? 1 : 0 );
}

/* *c によって与えられた 2 バイト c[0]c[1] が表現する文字がEUCもしくはMS漢
   字としてどの程度解釈可能かの指標を与えます。

   kanjidata.h に与えられた表の値は 96 年 6 月にポストされた fj での全記事
   に登場した漢字の数を反映しています。これを各漢字の頻度分布の期待値とし
   て使用しています。なお 1 だけ下駄を履かせてありますが、これはサンプル数
   が十分ではないために、頻度の低い漢字の対による重みが大きくなることを避
   けるためです。

   より正確な表を作成するためにはより大きな辞書と決定アルゴリズムの詳細な
   検討が必要でしょう。*/

static void
calc_probability(
        const unsigned char *c,
        double              *prob_euc,
        double              *prob_mskanji
    )
{
    double  euc_case, mskanji_case;

    /* それぞれで解釈した場合の漢字の出現頻度を表から引き出します */
    euc_case     = prob_euc_table[c[0] - 0xA0][c[1] - 0xA1] + 1;
    mskanji_case = prob_mskanji_table[c[0] - 0xa0][c[1] - 0xA1] + 1;

    /* それぞれの可能性についてベイズ統計「的」に与えます。分母は正規化
     * のための項です。*/
    *prob_euc     += euc_case / (euc_case + mskanji_case);
    *prob_mskanji += mskanji_case / (euc_case + mskanji_case);
}

/* 漢字のコーディング方式を決定するルーチン 
 * 
 * buffer[] に与えられた文字を 1 byte 毎に見ていって決定する。
 * もちろん混在していた場合の動作は保証されない。また jisx0208 
 * の 90 年版に規定された文字だけを見る。厳密には JISC6226 や 
 * 83 はほんの少しだけ小さいのだけど…
 *
 * もちろん特定のメーカーだけが使用しているコードポイントは見
 * ない。特に NEC の 98 固有の拡張については文字とは見ない。そ
 * れ以外の文字から決定される。
 *
 * h_euc はEUCとMS漢字のいずれとも解釈可能な文字だけの場合に 
 * EUC である事前確率を与える。例えば与えば文章のうち 90% 程度
 * が EUC であると考えられればこの値を 0.9 にする。逆にMS漢字
 * が 70% ぐらいと期待できれば 0.3 にする。よくわからなければ 
 * 0.5 にしておいてもそれなりによい結果が得られるはず。 */

static enum KANJI_CODE
decide_kanji_coding_type(
        const unsigned char *buffer,
        double              h_euc
    )
{
    const unsigned char *c;

    double  prob_euc, prob_mskanji, prob_chars; /* EUC と MS漢字が一意に決
                        定できない時に事前知識をもって決定するための変数
                        あまり厳密な検討はしてないのでつつかないでね */

    enum KANJI_CODE unknown = KC_UNKNOWN; /* 漢字コードが未知の場合の区別用。
                        MSB が 1 の文字があったのに、これが EUC でも MS 
                        漢字でもなければこれを BROKEN にする。最後に未知
                        のままならこの値を返す。
                        NECの98固有の拡張文字だけの行についてはこの 
                        BROKEN を返します。 実際私は読む手段がないし… */

    /* EUC と MS漢字を除くエンコーディング方式を順にチェックします */

    /* 最初の 3 つは旧 junet 以来使用されているコーディングに 
       iso-2022 の jisx0208-90 の拡張を加えてあります。ここで
       言う JISC6226 や JISX0208* と EUC, MS漢字を並置している
       のは正確には正しくありません。*/

    /* JISC6226_78 か? */
    for ( c = buffer; *c != '\0'; c++ )
        if ( c[0] == '\033' )
            if ( c[1] == '$' )
                if ( c[2] == '@' )
                    return KC_JISC6226_78;

    /* JISX0208_83 か? */
    for ( c = buffer; *c != '\0'; c++ )
        if ( c[0] == '\033' )
            if ( c[1] == '$' )
                if ( c[2] == 'B' )
                    return KC_JISX0208_83;

    /* JISX0208_90 か? */
    for ( c = buffer; *c != '\0'; c++ )
        if ( c[0] == '\033' )
            if ( c[1] == '&' )
                if ( c[2] == '@' )
                    if ( c[3] == '\033' )
                        if ( c[4] == '$' )
                            if ( c[5] == 'B' )
                                return KC_JISX0208_90;

    /* EUC と MS漢字のテスト */

    /* 統計値の初期化 */
    prob_euc     = 0.0; /* EUC である可能性を反映した積算値が入ります       */
    prob_mskanji = 0.0; /* MS漢字である可能性を反映した積算値が入ります     */
    prob_chars   = 0.0; /* 両方のコーディングの可能性がある文字数が入ります */

    /* 行の先頭から「らしい」文字をサーチする */
    for ( c = buffer; *c != '\0'; ) {
        if ( (c[0] & 0x80) == 0 ) { /* これはどちらでもないから読み飛ばす */
            c++;
        }
        else {
            if ( is_euc(c) ) {  /* EUC として認識できる場合 */
                if ( is_mskanji(c))  {  /* 最悪ケース。設定不良問題 */
                    calc_probability( c, &prob_euc, &prob_mskanji );
                    prob_chars++;
                }
                else {  /* この文字列は EUC としてしか認識できない */
                    return KC_EUC;
                }
            }
            else {  /* EUC ではない場合 */
                if ( is_mskanji(c) ) {  /* この文字列は MS漢字としてしか認識できない */
                    return KC_MSKANJI;
                }
                else {  /* これは変だ */
                    unknown = KC_BROKEN;
                }
            }
            c += 2; /* 2 文字読み飛ばす */
        }
    }
    if ( prob_chars > 0.0 ) {   /* いずれかと思われる文字がみつかった */
        return ( ((prob_euc * h_euc) >= (prob_mskanji * (1.0 - h_euc)))
                    ? KC_EUC
                    : KC_MSKANJI );
    }

    /* 結局何もわからなかった時はそのままリターン ... 無責任 :-) */
    return unknown;
}
/* 文字コード判別処理: ここまで */



/*
 *  漢字コード変換処理
 *    GNU iconv ライブラリを利用
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
            /* 以下、変換に失敗する場合の対策 */
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

            /* 強制的に "―" に unfication する */
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


/* Shift_JIS → EUC-JP 変換 */
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


/* Shift_JIS → UTF-8 変換 */
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


/* UTF-8 → EUC-JP 変換 */
char    *
utf2euc( const char *p )
{
    char            *q, *r;
    unsigned char   aaa[4];
    int             flag = 0;

    /* "～" (UTF-8 で 0xEF 0xBD 0x9E) を含む文字列の場合、 */
    /* iconv() が変換に失敗するための対策                  */
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
            strcat( q, "～" );
            strcat( q, r + 3 );
            r = strstr( q, "___" );
        }
    }
    else if ( flag ) {
        /* "。～" 等のパターンの場合、いったん変換に失敗するが、 */
        /* "～" → "___" に置換後、再度変換を試みると成功する    */
        return ( utf2euc( p ) ); /* 再度変換 */
    }

    return ( q );
}


/* ISO-2022-JP → Shift_JIS 変換 */
char    *
jis2sjis( const char *p )
{
    return ( convertCode( p, "ISO-2022-JP", "CP932" ) );
}


/* ISO-2022-JP → EUC-JP 変換 */
char    *
jis2euc( const char *p )
{
    return ( convertCode( p, "ISO-2022-JP", "EUC-JP" ) );
}


/* ISO-2022-JP → UTF-8 変換 */
char    *
jis2utf( const char *p )
{
    return ( convertCode( p, "ISO-2022-JP", "UTF-8" ) );
}


/* EUC-JP → Shift_JIS 変換 */
char    *
euc2sjis( const char *p )
{
    char    *s = convertCode( p, "EUC-JP", "CP932" );

    if ( !s )
        if ( decide_kanji_coding_type( (unsigned char *)p, 0.5 ) == KC_EUC )
            s = euc2sjisEx( p );

    return ( s );
}


/* EUC-JP → UTF-8 変換 */
char    *
euc2utf( const char *p )
{
    return ( convertCode( p, "EUC-JP", "UTF-8" ) );
}


/* UTF-8 → Shift_JIS 変換 */
char    *
utf2sjis( const char *p )
{
    char            *q, *r;
    unsigned char   aaa[4];
    int             flag = 0;

    /* "～" (UTF-8 で 0xEF 0xBD 0x9E) を含む文字列の場合、 */
    /* iconv() が変換に失敗するための対策                  */
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
            strcat( q, "～" );
            strcat( q, r + 3 );
            r = strstr( q, "___" );
        }
    }
    else if ( flag ) {
        /* "。～" 等のパターンの場合、いったん変換に失敗するが、 */
        /* "～" → "___" に置換後、再度変換を試みると成功する    */
        return ( utf2sjis( p ) ); /* 再度変換 */
    }

    return ( q );
}


/* ISO-8859-1 → UTF-8 変換 */
char    *
iso8859_1toUtf8( const char *p )
{
    return ( convertCode( p, "ISO-8859-1", "UTF-8" ) );
}


/* iconv 版数取得 */
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
