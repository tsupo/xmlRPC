/*
 *  isbn.c
 *      ISBN → 各種(オンライン書店)URL変換処理
 *
 * History:
 * $Log: /comm/xmlRPC/isbn.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 7     08/11/17 22:02 Tsujimura543
 * static char → Thread static char に変更
 * 
 * 6     08/01/29 17:25 Tsujimura543
 * bk1ブリーダー関連のコードを削除
 * (すでにbk1ブリーダー制度は廃止されている)
 * 
 * 5     07/09/10 19:03 Tsujimura543
 * BK1関連の処理をオプション化。なお、本ライブラリは13桁ISBNには未対応
 * である。
 * 
 * 4     06/09/15 14:48 Tsujimura543
 * xmlRPC.dll からバリューコマース関連機能を削除・廃止するのに伴い、
 * isbn2urls() の仕様を変更(引数を追加)
 * 
 * 3     05/09/02 14:47 Tsujimura543
 * affiriate → affiliate に修正 (綴り間違い)
 * 
 * 2     05/05/20 23:37 Tsujimura543
 * 生成するリンクを2005年5月20日時点のものに変更
 * 
 * 1     05/04/18 16:59 Tsujimura543
 * isbn2urls() を amazon.c から移管
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/isbn.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char    *
escapeAmpasand( char *p )
{
    char    *s = p, *t, *u;
    char    temp[BUFSIZ];

    while ( *s && ((t = strchr( s, '&' )) != NULL) ) {
        strcpy( temp, t + 1 );
        u = t + 1;
        *u++ = 'a';
        *u++ = 'm';
        *u++ = 'p';
        *u++ = ';';
        strcpy( u, temp );
        s = u;
    }

    return ( p );
}

/*
 *  ISBN → 各種(オンライン書店)URL変換
 *      引数として与える ISBN の形式は
 *          4-8443-1812-8
 *          4844318128
 *      の2パターンの両方とも可とする
 *      (ASIN は amazon のみのローカルなコードなので、
 *       変換対象外とする)
 *
 *    4-8443-1940-X →
 *      http://www.e-hon.ne.jp/bec/SA/Detail?refShinCode=0100000000000031368234
 *      http://www.bk1.co.jp/cgi-bin/bk1detail.cgi?aid=02sanseid01&bibid=02435568&volno=0000
 *      http://books.yahoo.co.jp/bin/detail?id=31368234
 *      http://product.esbooks.co.jp/product/keyword/keyword?accd=31368234
 *              (31368234 というコードは、トーハン[もしくは流通関連会社共通]
 *               の管理番号?)
 *    4-8334-5002-X →
 *      http://www.e-hon.ne.jp/bec/SA/Detail?refShinCode=0100000000000031375396
 *      http://product.esbooks.co.jp/product/all/top?accd=31375396
 *          (31375396 → 上4桁(3137):出版社番号?, 下4桁(5396):書籍番号?)
 *    のように各社独自のコードマッピングをしている場合は変換対象外とする
 *
 *    日本では、JANコードも使われているが、現時点では対応しないことにする
 *      (ISBNコード→JANコード変換には(出版社が決めた)書籍の分類コード、
 *       価格、初版発行年月日等の情報が別途必要になるが、JANコード→ISBN
 *       コード変換は、他の情報を必要としないため、可能であると思われる)
 */

char    *
isbn2urlsOnJBOOK( const char *isbn,  BOOL isAffiliateAvalable,
                  const char *vcSID, const char *vcPID )
{
    Thread static char  buf[BUFSIZ];
    char                link[MAX_URLLENGTH];

    sprintf( link, "http://www.jbook.co.jp/product.asp?isbn=%s", isbn );
    if ( isAffiliateAvalable && vcSID && vcSID[0] && vcPID && vcPID[0] )
        sprintf( buf,
                 "http://ck.jp.ap.valuecommerce.com/servlet/referral?"
                 "sid=%s&amp;pid=%s&amp;vc_url=%s",
                 vcSID, vcPID, translateURL(link) );
    else
        strcpy( buf, escapeAmpasand(link) );

    return ( buf );
}

char    *
isbn2urlsOnJBOOKtracking( BOOL isAffiliateAvalable,
                          const char *vcSID, const char *vcPID )
{
    Thread static char  buf[BUFSIZ];

    if ( isAffiliateAvalable && vcSID && vcSID[0] && vcPID && vcPID[0] )
        sprintf( buf,
                 "<img src=\"http://ad.jp.ap.valuecommerce.com/servlet/"
                 "gifbanner?sid=%s&amp;pid=%s\" height=\"1\" width=\"1\""
                 " border=\"0\" alt=\"JBOOK\" />",
                 vcSID, vcPID );
    else
        strcpy( buf, " " );

    return ( buf );
}


char    *
isbn2urlsOnAmazon( const char *isbn, BOOL isAffiliateAvalable )
{
    Thread static char  buf[BUFSIZ];

    if ( isAffiliateAvalable )
        sprintf( buf,
                 "http://www.amazon.co.jp/exec/obidos/redirect?path=ASIN/%s"
                 "&amp;link_code=as2&amp;camp=247&amp;tag=%s&amp;"
                 "creative=1211",
                 isbn,
                 xmlrpc_p && xmlrpc_p->amazonAssociateID[0]
                    ? xmlrpc_p->amazonAssociateID
                    : AMAZON_ASSOCIATE_ID   /* Amazon アソシエイトID */
               );
    else
        sprintf( buf,
                 "http://www.amazon.co.jp/exec/obidos/ASIN/%s", isbn );

    return ( buf );
}

char    *
isbn2urlsOnAmazonTracking( const char *isbn, BOOL isAffiliateAvalable )
{
    Thread static char  buf[BUFSIZ];

    if ( isAffiliateAvalable )
        sprintf( buf,
                 "<img src=\"http://www.assoc-amazon.jp/e/ir?t=%s&amp;l=as2"
                 "&amp;o=9&amp;a=%s\" width=\"1\" height=\"1\" border=\"0\" "
                 "alt=\"\" style=\"border:none !important; margin:0px "
                 "!important;\" />",
                 xmlrpc_p && xmlrpc_p->amazonAssociateID[0]
                    ? xmlrpc_p->amazonAssociateID
                    : AMAZON_ASSOCIATE_ID,  /* Amazon アソシエイトID */
                 isbn );
    else
        strcpy( buf, " " );

    return ( buf );
}


char    *
isbn2urlsOnRakutenBooks( const char *isbn, BOOL isAffiliateAvalable )
{
    Thread static char  buf[BUFSIZ];
    char                link[MAX_URLLENGTH];

    sprintf( link, "http://books.rakuten.co.jp/b.jsp?i=%s", isbn );
    if ( isAffiliateAvalable )
        sprintf( buf,
                 "http://pt.afl.rakuten.co.jp/c/%s/?url=%s",
                 xmlrpc_p && xmlrpc_p->rakutenAffiliateID[0]
                    ? xmlrpc_p->rakutenAffiliateID
                    : RAKUTEN_AFFILIATE_ID, /* 楽天アフィリエイトID */
                 translateURL(link) );
    else
        strcpy( buf, escapeAmpasand(link) );

    return ( buf );
}


char    *
isbn2urlsOnKinokuniya( const char *isbn,  BOOL isAffiliateAvalable,
                       const char *vcSID, const char *vcPID )
{
    Thread static char  buf[BUFSIZ];
    char                link[MAX_URLLENGTH];

    sprintf( link,
             "http://bookweb.kinokuniya.co.jp/guest/cgi-bin/wshosea.cgi"
             "?RECNO=1&W-ISBN=%s",
             isbn );
    if ( isAffiliateAvalable && vcSID && vcSID[0] && vcPID && vcPID[0] )
        sprintf( buf,
                 "http://ck.jp.ap.valuecommerce.com/servlet/referral?"
                 "sid=%s&amp;pid=%s&amp;vc_url=%s",
                 vcSID, vcPID, translateURL(link) );
    else
        strcpy( buf, escapeAmpasand(link) );

    return ( buf );
}

char    *
isbn2urlsOnKinokuniyaTracking( BOOL isAffiliateAvalable,
                               const char *vcSID, const char *vcPID )
{
    Thread static char  buf[BUFSIZ];

    if ( isAffiliateAvalable && vcSID && vcSID[0] && vcPID && vcPID[0] )
        sprintf( buf,
                 "<img src=\"http://ad.jp.ap.valuecommerce.com/servlet/"
                 "gifbanner?sid=%s&amp;pid=%s\" height=\"1\" width=\"1\""
                 " border=\"0\" alt=\"紀伊國屋\" />",
                 vcSID, vcPID );
    else
        strcpy( buf, " " );

    return ( buf );
}


char    *
isbn2urlsOnBookService( const char *isbn,  BOOL isAffiliateAvalable,
                        const char *vcSID, const char *vcPID )
{
    Thread static char  buf[BUFSIZ];
    char                link[MAX_URLLENGTH];

    sprintf( link,
             "https://market.bookservice.co.jp/emp-bin/eh_writer.exe/top/"
             "dairiten_isbn/receive_guest.html?isbn_cd=%s",
             isbn );
    if ( isAffiliateAvalable && vcSID && vcSID[0] && vcPID && vcPID[0] )
        sprintf( buf,
                 "http://ck.jp.ap.valuecommerce.com/servlet/referral?"
                 "sid=%s&amp;pid=%s&amp;vc_url=%s",
                 vcSID, vcPID, translateURL(link) );
    else
        strcpy( buf, escapeAmpasand(link) );

    return ( buf );
}

char    *
isbn2urlsOnBookServiceTracking( BOOL isAffiliateAvalable,
                                const char *vcSID, const char *vcPID )
{
    Thread static char  buf[BUFSIZ];

    if ( isAffiliateAvalable && vcSID && vcSID[0] && vcPID && vcPID[0] )
        sprintf( buf,
                 "<img src=\"http://ad.jp.ap.valuecommerce.com/servlet/"
                 "gifbanner?sid=%s&amp;pid=%s\" height=\"1\" width=\"1\""
                 " border=\"0\" alt=\"クロネコヤマト ブックサービス\" />",
                 vcSID, vcPID );
    else
        strcpy( buf, " " );

    return ( buf );
}


char    *
isbn2urlsOnUBOOK( const char *isbn,  BOOL isAffiliateAvalable,
                  const char *vcSID, const char *vcPID )
{
    Thread static char  buf[BUFSIZ];
    char                link[MAX_URLLENGTH];

    sprintf( link,
             "http://www.ubook.co.jp/shop/goods/goods.asp?country=SYS01001"
             "&isbn=%s&search=x&shop=",
             isbn );
    if ( isAffiliateAvalable && vcSID && vcSID[0] && vcPID && vcPID[0] )
        sprintf( buf,
                 "http://ck.jp.ap.valuecommerce.com/servlet/referral?"
                 "sid=%s&amp;pid=%s&amp;vc_url=%s",
                 vcSID, vcPID, translateURL(link) );
    else
        strcpy( buf, escapeAmpasand(link) );

    return ( buf );
}

char    *
isbn2urlsOnUBOOKtracking( BOOL isAffiliateAvalable,
                          const char *vcSID, const char *vcPID )
{
    Thread static char  buf[BUFSIZ];

    if ( isAffiliateAvalable && vcSID && vcSID[0] && vcPID && vcPID[0] )
        sprintf( buf,
                 "<img src=\"http://ad.jp.ap.valuecommerce.com/servlet/"
                 "gifbanner?sid=%s&amp;pid=%s\" height=\"1\" width=\"1\""
                 " border=\"0\" alt=\"@古本市場\" />",
                 vcSID, vcPID );
    else
        strcpy( buf, " " );

    return ( buf );
}


char    *
isbn2urls( const char *isbn, BOOL isAffiliateAvalable,
           const char *vcSID,   /* ValueCommerce SID */
           const char *vcPID1,  /* クロネコヤマトブックサービス PID */
           const char *vcPID2,  /* JBOOK                        PID */
           const char *vcPID3,  /* 紀伊國屋書店                 PID */
           const char *vcPID4   /* @古本市場                    PID */
          )
{
    int                 l, i, j;
    const char          *p = isbn, *q;
    const char          *isbn1, *isbn2;
    char                another[BUFSIZ];
    Thread static char  urlString[10240];

    urlString[0] = '\0';
    if ( p && *p )
        l = strlen( p );
    else
        return ( NULL );

    if ( ( q = strchr( p, '-' ) ) != NULL ) {
        for ( i = 0; *p; p++ ) {
            if ( *p != '-' )
                another[i++] = *p;
        }
        another[i] = '\0';

        isbn1 = isbn;       /* 4-8443-1812-8 形式 */
        isbn2 = another;    /* 4844318128 形式    */
    }
    else {
        for ( i = 0, j = 0; *p; p++, i++ ) {
            switch ( i ) {
            case 0:
            case 4:
            case 8:
                another[j++] = *p;
                another[j++] = '-';
                break;
            default:
                another[j++] = *p;
                break;
            }
        }
        another[j] = '\0';

        isbn1 = another;    /* 4-8443-1812-8 形式 */
        isbn2 = isbn;       /* 4844318128 形式    */
    }

    sprintf( urlString,
             "<div class=\"isbn\">\n"
             "[ ISBN:%s: <a href=\"%s\">Amazon</a>%s\n"
             " - <a href=\"%s\">JBOOK</a>%s\n"
             " - <a href=\"%s\">楽天ブックス</a>\n"
             " - <a href=\"http://pc.bookmall.co.jp/search/info.php?"
             "Isbn=%s\">ブックモールPC</a>\n"
             " - <a href=\"http://www.manah.net/book/product.jsp?sku=B%s\">"
             "ManaHouse</a>\n"
             " - <a href=\"%s\">紀伊國屋</a>%s\n"

             " - <a href=\"http://www.netdirect.co.jp/search/ISSSchDetail."
             "asp?ISBN=%s\">旭屋</a>\n"
             " - <a href=\"http://www.maruzen.co.jp/cgi-bin/mis?Cgifrom="
             "m2-ezy-02&amp;Dbs=MPW&amp;VhIBW=%s\">丸善</a>\n"
             " - <a href=\"http://books.yahoo.co.jp/bin/search_key?pp=3&amp;"
             "p=%s\">Yahoo! ブックス</a>\n"
             " - <a href=\"http://www.cbook24.com/bm_detail.asp?sku=%s\">"
             "cbook24</a>\n"
             " - <a href=\"http://www.esbooks.co.jp/search?author_location=00"
             "&amp;keyword=&amp;book_name=&amp;author=&amp;content=&amp;"
             "publisher=&amp;isbn=%s&amp;keyword_switch=1&amp;floor=&amp;"
             "image_disp_flg=1&amp;out_of_print=1&amp;sort_order=8&amp;"
             "invent_cond=&amp;item_num=20&amp;shelf_submit.x=21&amp;"
             "shelf_submit.y=10\">セブンアンドワイ</a>\n"

             " - <a href=\"%s\" />クロネコヤマト ブックサービス</a>%s\n"

             " - <a href=\"http://book.mycom.co.jp/cgi-bin/main.cgi?CMD="
             "keyword&amp;FUNC=select&amp;V_MODE=1&amp;V_ISBN=%s&amp;"
             "V_CHK_ALL=1\">MYCOM BOOKS</a>\n"

             " - <a href=\"%s\">@古本市場</a>%s\n"

             " ]\n"
             "</div>",
             isbn1, /* 4-8443-1812-8 形式 - 見出し */

             isbn2urlsOnAmazon( isbn2, isAffiliateAvalable ),
             isbn2urlsOnAmazonTracking( isbn2, isAffiliateAvalable ),
                    /* 4844318128 形式    - Amazon */

             isbn2urlsOnJBOOK( isbn2, isAffiliateAvalable, vcSID, vcPID2 ),
             isbn2urlsOnJBOOKtracking( isAffiliateAvalable, vcSID, vcPID2 ),
                    /* 4844318128 形式    - JBOOK  */

             isbn2urlsOnRakutenBooks( isbn2, isAffiliateAvalable ),
                    /* 4844318128 形式    - 楽天ブックス     */

             isbn1, /* 4-8443-1812-8 形式 - ブックモールPC   */
             isbn2, /* 4844318128 形式    - ManaHouse        */

             isbn2urlsOnKinokuniya( isbn2, isAffiliateAvalable,
                                    vcSID, vcPID3 ),
             isbn2urlsOnKinokuniyaTracking( isAffiliateAvalable,
                                    vcSID, vcPID3 ),
                    /* 4844318128 形式    - 紀伊國屋         */

             isbn2, /* 4844318128 形式    - 旭屋             */
             isbn1, /* 4-8443-1812-8 形式 - 丸善             */
             isbn1, /* 4-8443-1812-8 形式 - Yahoo! ブックス  */
             isbn2, /* 4844318128 形式    - cbook24.com      */
             isbn1, /* 4-8443-1812-8 形式 - セブンアンドワイ */

             isbn2urlsOnBookService( isbn2, isAffiliateAvalable,
                                     vcSID, vcPID1 ),
             isbn2urlsOnBookServiceTracking( isAffiliateAvalable,
                                             vcSID, vcPID1 ),
                    /* 4844318128 形式    - クロネコヤマト ブックサービス */

             isbn2, /* 4844318128 形式    - MYCOM BOOKS      */

             isbn2urlsOnUBOOK( isbn2, isAffiliateAvalable,
                               vcSID, vcPID4 ),
             isbn2urlsOnUBOOKtracking( isAffiliateAvalable,
                                       vcSID, vcPID4 )
                    /* 4844318128 形式    - @古本市場        */
            );

    return ( urlString );
}
