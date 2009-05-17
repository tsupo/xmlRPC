/*
 *  blogInfo.c
 *      blog 情報テーブル
 * History:
 * $Log: /comm/xmlRPC/blogInfo.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 15    09/03/20 22:25 Tsujimura543
 * 「はてなダイアリー」の Atom API に対応
 * 
 * 14    09/03/16 14:04 Tsujimura543
 * 「ウェブリブログ (XML-RPC API)」関連、追加
 * 
 * 13    07/11/30 1:41 Tsujimura543
 * (1) ヤプログ!、ドリコムブログ、Jugem 向けに特別に用意していた処理を削除
 * (2) アメーバブログ向けの特別処理を削除 (Atom API 関連を除く)
 * 
 * 12    07/10/29 16:44 Tsujimura543
 * ヤプログ! の XML-RPC API 関連の定義を追加
 * 
 * 11    07/02/23 23:15 Tsujimura543
 * JUGEM とドリコムブログの XML-RPC API 関連の定義を追加
 * 
 * 10    06/09/14 13:46 Tsujimura543
 * VOX 関連の記述を追加
 * 
 * 9     06/03/15 21:57 Tsujimura543
 * livedoor Blog のエンドポイント URL を ATOMURL_LIVEDOOR_200507 に変更
 * 
 * 8     06/02/20 23:22 Tsujimura543
 * マイプロフィール関連の記述を削除
 * 
 * 7     06/01/26 13:24 Tsujimura543
 * アメーバブログ の Atom API に対応
 * 
 * 6     05/11/28 15:05 Tsujimura543
 * ココログフリー対応
 * 
 * 5     05/07/19 11:17 Tsujimura543
 * So-net blog 対応
 * 
 * 4     04/09/28 13:54 Tsujimura543
 * アメーバブログ対応
 * 
 * 3     04/09/03 15:24 Tsujimura543
 * マイプロフィール対応 [暫定]
 * 
 * 2     04/08/19 9:06 Tsujimura543
 * LOVELOG, TypePad Germany, blogger を追加
 * 
 * 1     04/07/07 15:45 Tsujimura543
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/blogInfo.c 1     09/05/14 3:46 tsupo $";
#endif


BLOGINFOTBL blogInfoTbl[] = {
    /*
     *  TypePad系
     */
    {   /* ココログ */
        BLOGKIND_COCOLOG,
        CHARSET_UTF8,
        APIURL_COCOLOG,
        ATOMURL_COCOLOG
    },
    {   /* ココログフリー */
        BLOGKIND_COCOLOGFREE,
        CHARSET_UTF8,
        APIURL_COCOLOGFREE,
        ATOMURL_COCOLOGFREE
    },
    {   /* ブログ人 */
        BLOGKIND_BLOGZINE,
        CHARSET_UTF8,
        APIURL_BLOGZINE,
        ATOMURL_BLOGZINE
    },
    {   /* TypePad */
        BLOGKIND_TYPEPAD,
        CHARSET_UTF8,
        APIURL_TYPEPAD,
        ATOMURL_TYPEPAD
    },
    {   /* TypePad Japan */
        BLOGKIND_TYPEPADJAPAN,
        CHARSET_UTF8,
        APIURL_TYPEPADJAPAN,
        ATOMURL_TYPEPADJAPAN
    },
    {   /* TypePad France */
        BLOGKIND_TYPEPADFRANCE,
        CHARSET_UTF8,
        APIURL_TYPEPADFRANCE,
        ATOMURL_TYPEPADFRANCE
    },
    {   /* TypePad Germany */
        BLOGKIND_TYPEPADGERMANY,
        CHARSET_UTF8,
        APIURL_TYPEPADGERMANY,
        ATOMURL_TYPEPADGERMANY
    },

    /*
     *  metaWeblog API サポート blog
     */
    {   /* News-Handler */
        BLOGKIND_NEWSHANDLER,
        CHARSET_EUCJP,
        APIURL_NEWSHANDLER,
        ""
    },
    {   /* Seesaa BLOG */
        BLOGKIND_SEESAABLOG,
        CHARSET_SHIFTJIS,
        APIURL_SEESAABLOG,
        ""
    },

    /*
     *  MovableType API サポート blog
     */
    {   /* ドリコムブログ (XML-RPC API) */
        BLOGKIND_DRECOMBLOG_X,
        CHARSET_SHIFTJIS,
        APIURL_DRECOMBLOG_X,
        ""
    },
    {   /* JUGEM (XML-RPC API) */
        BLOGKIND_JUGEM_X,
        CHARSET_EUCJP,
        APIURL_JUGEM_X,
        ""
    },
    {   /* ヤプログ! (XML-RPC API) */
        BLOGKIND_YAPLOG_X,
        CHARSET_SHIFTJIS,
        APIURL_YAPLOG_X,
        ""
    },
    {   /* ウェブリブログ (XML-RPC API) */
        BLOGKIND_WEBRY_X,
        CHARSET_UTF8,
        APIURL_WEBRY_X,
        ""
    },

    /*
     *  Atom API サポート blog
     */
    {   /* livedoor Blog */
        BLOGKIND_LIVEDOOR,
        CHARSET_EUCJP,
        "",
        ATOMURL_LIVEDOOR_200507
    },

    {   /* LOVELOG */
        BLOGKIND_LOVELOG,
        CHARSET_EUCJP,
        "",
        ATOMURL_LOVELOG
    },

    {   /* So-net blog */
        BLOGKIND_SONET,
        CHARSET_UTF8,
        "",
        ATOMURL_SONET
    },

    {   /* アメーバブログ */
        BLOGKIND_AMEBLO,
        CHARSET_EUCJP,
        "",
        ATOMURL_AMEBLO
    },

    {   /* blogger */
        BLOGKIND_BLOGGER,
        CHARSET_UTF8,
        APIURL_BLOGGER,
        ATOMURL_BLOGGER
    },

    {   /* Vox */
        BLOGKIND_VOX,
        CHARSET_UTF8,
        "",
        ATOMURL_VOX
    },

    {   /* はてなダイアリー */
        BLOGKIND_HATENADIARY,
        CHARSET_EUCJP,
        "",
        ATOMURL_HATENADIARY
    },

    /* 以下の blog は、XML-RPC API や Atom API を使わず、blog 管理画面と */
    /* 直接通信する方式で対応                                            */
    {   /* exciteブログ */
        BLOGKIND_EXCITEBLOG,
        CHARSET_UTF8,
        NULL,
        NULL
    },

    { -1, -1, NULL, NULL }
};
