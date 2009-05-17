/*
 *  はてなキーワードリンク関連API
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2008 by H.Tsujimura
 *      written by H.Tsujimura
 *
 * History:
 * $Log: /comm/xmlRPC/hatenaApi.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 71    09/04/27 19:31 Tsujimura543
 * 「はてなブックマーク」のAPIの応答の形式が変更されたのに伴う修正
 * (2009年4月25日近辺に変更された模様)
 * 
 * 70    09/01/26 23:36 Tsujimura543
 * はてな側の不具合 (http://i.hatena.ne.jp/idea/23100) に対する
 * 暫定対処を実施
 * 
 * 69    09/01/08 13:29 Tsujimura543
 * getPostsFromRSS() を「はてなブックマーク2」用に修正
 * 
 * 68    08/12/15 17:06 Tsujimura543
 * cookie 解放忘れ箇所、修正
 * 
 * 67    08/12/01 19:02 Tsujimura543
 * URL に & が含まれると、ブックマークの登録に失敗する現象に対処
 * (リニューアル後の「はてなブックマーク」で発生するようになった)
 * 
 * 66    08/11/28 17:02 Tsujimura543
 * getRecentPostsOnHatenaUser() の終了条件を修正
 * 
 * 65    08/11/28 15:58 Tsujimura543
 * getRecentPostsOnHatenaUser() の情報源取得対象を Atom Feed
 * から RSS に変更 (はてなブックマークリニューアル後、Atom Feed
 * の of パラメータが機能しなくなってしまったため)
 * 
 * 64    08/11/28 0:52 Tsujimura543
 * リニューアル後の「はてなブックマーク」では、まだ削除用のAPIが機能
 * していないことを確認
 * 
 * 63    08/11/27 22:51 Tsujimura543
 * renameTagFromBookmarksOnHatena() と
 * removeTagFromBookmarksOnHatena() を
 * リニューアル後の「はてなブックマーク」用に修正した
 * (が、「タグ一覧の取得」ができないため、
 *    タグ一覧取得 → 置換・削除したいタグを選択 → 置換・削除実行
 * という流れでの処理ができない)
 * 
 * 62    08/11/27 20:53 Tsujimura543
 * postBookmarkWithCollectionOnHatena() を2008年11月25日リニューアル
 * 後の「はてなブックマーク」に対応させた
 * (タグの一括置換、一括削除は未対応)
 * 
 * 61    08/11/25 20:03 Tsujimura543
 * getBookmarkOnHatenaWithURI() 内で取得した response の内容が
 * 予期しないものだったときに、クラッシュすることがある不具合に対処
 * 
 * 60    08/05/20 23:06 Tsujimura543
 * searchKeyword() で stack overflow が発生するのを予防する処理を追加
 * 
 * 59    08/02/08 18:47 Tsujimura543
 * コメントを修正、追加
 * 
 * 58    08/02/08 18:46 Tsujimura543
 * loginHatenaBookmark() を修正 (いつの間にか、login form のパラメータ
 * が変更されていた)
 * 
 * 57    07/09/10 14:59 Tsujimura543
 * 若干リファクタリング
 * 
 * 56    07/09/06 17:55 Tsujimura543
 * 「はてなブックマーク」への登録・編集API発行時、コメント、タグの両方とも
 * 空の場合はAPIの実行を中止していたのをやめ、APIを実行するようにした
 * 
 * 55    07/06/26 13:24 Tsujimura543
 * changeHatenaKeyword() を修正し、はてなダイアリーキーワードAPIが
 * 停止中でもそれなりに動くようにした
 * 
 * 54    07/03/20 0:19 Tsujimura543
 * コメントを修正
 * 
 * 53    07/03/20 0:18 Tsujimura543
 * searchKeywordEx() を修正。文字コード変換失敗の可能性を考慮するように
 * した
 * 
 * 52    07/03/05 17:27 Tsujimura543
 * setKeywordLink() をさらに修正
 * 
 * 51    07/03/05 17:19 Tsujimura543
 * setKeywordLink() を修正(バッファオーバーラン対策)
 * [引数追加 + tmp, request, response の各領域の確保方法修正]
 * 
 * 50    07/03/03 15:18 Tsujimura543
 * sjis2utf() が NULL を返す場合の対策を実施
 * 
 * 49    07/02/02 20:55 Tsujimura543
 * getBookmarkOnHatena() と getBookmarkOnHatenaWithURI() でタグが
 * 取得できない不具合を修正 (はてなブックマークの仕様変更対応し忘れ)
 * 
 * 48    07/01/29 21:24 Tsujimura543
 * getListOfTagsOnHatena() を追加
 * 
 * 47    06/11/16 1:40 Tsujimura543
 * getPosts() と getPostsFromRSS() をリファクタリング
 * 
 * 46    06/11/15 23:52 Tsujimura543
 * getPostsFromRSS() を修正、<title>要素の先頭に改行が存在する場合は、
 * その改行を捨てるようにした
 * 
 * 45    06/11/15 21:35 Tsujimura543
 * getPostsFromHatenaFeed() の動作を確認。getPosts() や getPostsFromRSS()
 * の処理に時間がかかりすぎているため、高速化が今後の課題。
 * 
 * 44    06/11/15 18:37 Tsujimura543
 * getPostsFromHatenaFeed() の第1引数を「ファイル名」から「FILE *」に変更
 * 
 * 43    06/11/15 18:15 Tsujimura543
 * コメント(getPostsFromHatenaFeed() の引数の説明)を修正
 * 
 * 42    06/11/15 18:12 Tsujimura543
 * getPostsFromHatenaFeed() と freePostsFromHatenaFeed() を追加
 * 
 * 41    06/10/23 16:21 Tsujimura543
 * 受信バッファオーバーラン対策を追加
 * 
 * 40    06/10/18 19:39 Tsujimura543
 * ブックマーク取得処理でバッファオーバーランが発生する可能性があることが
 * 判明したので、対策を実施
 * 
 * 39    06/09/12 12:30 Tsujimura543
 * editBookmarkOnHatena() の warning 4100 を抑制する
 * 
 * 38    06/09/11 12:00 Tsujimura543
 * ソースコードを整理
 * 
 * 37a   06/09/09 23:04 tsupo
 * また、アマゾンの URL にバリエーションが増えたため、getASIN() を修正
 * 
 * 37    06/09/04 22:29 Tsujimura543
 * getASIN() を追加
 * 
 * 36    06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 35a   06/09/03 20:17 tsupo
 * cookie まわりを修正
 * 
 * 35    06/07/24 22:17 Tsujimura543
 * utf2sjis() 失敗時は utf2sjisEx() を呼び出すようにした
 * 
 * 34    06/07/24 19:21 Tsujimura543
 * getPosts() で解析中の XML の title 要素の先頭が改行の場合、
 * その改行を捨てるようにした
 * 
 * 33    06/07/18 20:44 Tsujimura543
 * &raquo; 対策 (はてなブックマークの挙動変更に伴う修正)
 * 
 * 32    06/07/18 13:51 Tsujimura543
 * デバッグ用コードを削除
 * 
 * 31    06/07/11 11:58 Tsujimura543
 * すでに登録済みのブックマークに対してさらに postBookmarkOnHatena()
 * しようとした場合、上書き登録するようにした
 * 
 * 30    06/04/07 13:30 Tsujimura543
 * postBookmarkWithCollectionOnHatena() を修正
 * (コレクションに追加できなくなってしまっていた)
 * 
 * 29    06/04/06 22:14 Tsujimura543
 * (1) postBookmarkWithCollectionOnHatena() を追加
 * (2) loginHatenaBookmark() を変更 (EUC-JP → UTF-8、など)
 * 
 * 28    05/11/30 14:09 Tsujimura543
 * はてなブックマークで使用可能なタグの数が 3 から 10 に変更されたのに
 * 伴う修正を実施
 * 
 * 27    05/10/28 13:49 Tsujimura543
 * utf2sjis() 失敗時の処理を見直した
 * 
 * 26    05/10/27 21:02 Tsujimura543
 * 取得した title の utf2sjis() が失敗した場合の処理を追加
 * 
 * 25    05/10/18 18:41 Tsujimura543
 * httpPostWithSession() の引数追加に伴う修正を実施
 * 
 * 24    05/10/18 18:02 Tsujimura543
 * httpGetBufferWithSession() の引数追加に伴う修正を実施
 * 
 * 23    05/09/27 16:02 Tsujimura543
 * コードの整理
 * 
 * 22    05/09/27 15:57 Tsujimura543
 * はてなブックマークの一覧取得系関数で、ブックマークの登録日時を返却する
 * ように修正(コードを追加)した
 * 
 * 21    05/08/08 17:57 Tsujimura543
 * renameTagFromBookmarksOnHatena(), removeTagFromBookmarksOnHatena()
 * を追加
 * 
 * 20    05/07/21 16:45 Tsujimura543
 * getNumberOfBookmarksOnHatena() を追加 (動作確認済み)
 * 
 * 19    05/07/20 20:50 Tsujimura543
 * getBookmarkOnHatenaWithURI() を追加
 * 
 * 18    05/07/20 20:31 Tsujimura543
 * getRecentPostsOnHatenaUserWith{Tag,Word,Date}() を修正
 * 
 * 17    05/07/20 20:10 Tsujimura543
 * getRecentPostsOnHatenaUserWith{Tag,Word,Date}() を追加
 * 
 * 16    05/07/20 20:02 Tsujimura543
 * getRecentPostsOnHatenaUser() を追加
 * 
 * 15    05/07/20 19:02 Tsujimura543
 * getRecentPostsOnHatena() で tag を拾えるようにした
 * (はてなブックマーク の 2005年7月5日実施の API 拡張に対応) 
 * 
 * 14    05/06/09 22:31 Tsujimura543
 * postBookmarkOnHatena() に引数を1個追加した
 * 
 * 13    05/06/02 21:59 Tsujimura543
 * 動作確認完了
 * 
 * 12    05/06/01 21:13 Tsujimura543
 * getRecentPostsOnHatena() を実装
 * 
 * 11    05/06/01 12:11 Tsujimura543
 * deleteBookmarkOnHatena() を実装
 * 
 * 10    05/06/01 0:08 Tsujimura543
 * editBookmarkOnHatena() を実装
 * 
 * 9     05/05/31 22:25 Tsujimura543
 * getBookmarkOnHatena() を実装
 * 
 * 8     05/05/31 19:20 Tsujimura543
 * postBookmarkOnHatena() を実装
 * 
 * 7     04/11/15 17:06 Tsujimura543
 * encodeURL() 内で確保した領域の解放処理を追加
 * 
 * 6     04/11/01 21:02 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 5     04/08/31 13:31 Tsujimura543
 * static にできる関数は static にした
 * 
 * 4     04/08/31 13:27 Tsujimura543
 * 動的に確保した領域について、念のため、確保直後に領域内をNULクリアするよ
 * うにした
 * 
 * 3     04/08/31 13:24 Tsujimura543
 * http POST で使う電文格納領域を動的に確保するように変更
 * 
 * 2     04/07/07 11:56 Tsujimura543
 */

#include "xmlRPC.h"
#include <sys/stat.h>
#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/hatenaApi.c 1     09/05/14 3:46 tsupo $";
#endif


/*
 *  はてなダイアリーキーワード
 */

static int  codeSet = CSET_SHIFTJIS;


static void
skipAnkerCloser( FILE *fp, FILE *gp, const char *t, int mode, int *anker )
{
    char    *p;

    if ( *anker == 1 ) {
        if ( ( p = strchr( t, '>' ) ) != NULL ) {
            for ( ; (t <= p) && t; t++ )
                fputc( *t, gp );
            *anker = 2;
        }
        else {
            fputs( t, gp );
            return;
        }
    }

    if ( *anker == 2 ) {
        p = strstr( t, "</a>" );
        if ( p ) {
            *(p + 3) = '\0';
            fputs( t, gp );
            fputc( '>', gp );
            *anker = 0;
            t = p + 4;
            searchKeyword( fp, gp, t, mode );
        }
        else
            fputs( t, gp );
    }
}

static void
skipAnker( FILE *fp, FILE *gp, const char *t, int mode, int *anker )
{
    char    *p;

    p = strchr( t + 3, '>' );
    if ( p ) {
        char    *q = strstr( p + 1, "</a>" );

        if ( !q )
            q = strstr( p + 1, "</A>" );
        if ( !q ) {
            *anker = 2;
            fputs( t, gp );
            return;
        }
        *(q + 3) = '\0';
        fputs( t, gp );
        fputc( '>', gp );
        t = q + 4;
        searchKeyword( fp, gp, t, mode );
    }
    else {
        *anker = 1;
        fputs( t, stdout );
    }
}

static void
skipInner( FILE *fp, FILE *gp, const char *t, int mode, int *inner )
{
    char    *p;

    if ( ( p = strchr( t, '>' ) ) != NULL ) {
        for ( ; (t <= p) && *t; t++ )
            fputc( *t, gp );
        *inner = 0;
        searchKeyword( fp, gp, t, mode );
    }
    else
        fputs( t, gp );
}

static void
skipTag( FILE *fp, FILE *gp, const char *t, int mode, int *inner )
{
    char    *p;

    p = strchr( t + 2, '>' );
    if ( p ) {
        if ( !strncmpi(t,
            "<META http-equiv=\"Content-Type\" content=\"text/html; charset=",
                       60) ) {
            const char  *q = t + 60;

            if ( !strncmpi( q, "EUC-JP", 6 ) )
                codeSet = CSET_EUCJP;
            else if ( !strncmpi( q, "Shift_JIS", 9 ) )
                codeSet = CSET_SHIFTJIS;
            else if ( !strncmpi( q, "ISO-2022-JP", 11 ) )
                codeSet = CSET_ISO2022JP;
            else if ( !strncmpi( q, "UTF-8", 5 ) )
                codeSet = CSET_UTF8;
        }

        if ( !strncmpi( t, "</head>", 7 ) ) {
            /* はてなキーワードリンク用スタイルシートを埋め込む */
            fputs( "<style type=\"text/css\">\n", gp );
            fputs( "a.hatena { color: black;\n"
                   "text-decoration: none;\n"
                   "border-bottom: 1px solid gray;\n}\n", gp );
            fputs( "</style>\n", gp );
        }
        for ( ; (t <= p) && *t; t++ )
            fputc( *t, gp );
        searchKeyword( fp, gp, t, mode );
    }
    else {
        *inner = 1;
        fputs( t, gp );
    }
}

static void
searchKeyword( FILE *fp, FILE *gp, const char *word, int mode )
{
    char        *p, *r, buf[BUFSIZ];
    char        *t = (char *)word;
    size_t      len;
    int         flag  = 1;
    static int  inner = 0;
    static int  anker = 0;
    static int  depth = 0;

    depth++;
    if ( depth >= 100 ) {
        /* stack overflow 防止 */
        depth--;
        return;
    }

    if ( anker >= 1 ) {
        /* <a ...> に対応する </a> を探索 */
        skipAnkerCloser( fp, gp, t, mode, &anker );
        depth--;
        return;
    }

    if ( inner == 1 ) {
        /* “<...”に対応する“>”を探索 */
        skipInner( fp, gp, t, mode, &inner );
        depth--;
        return;
    }

    while ( (*t == ' ') || (*t == '\t') || (*t == '\r') || (*t == '\n') ) {
        fputc( *t, gp );
        t++;
    }

    /* 文字列の先頭にタグがある場合 */
    if ( !strncmpi( t, "<a ", 3 ) ) {
        /* <a ...> ～ </a> をキーワード変換対象外とし、そのまま出力 */
        skipAnker( fp, gp, t, mode, &anker );
        depth--;
        return;
    }

    if ( (*t == '<')                                     &&
         ( ((*(t + 1) >= 'a') && (*(t + 1) <= 'z')) ||
           ((*(t + 1) >= 'A') && (*(t + 1) <= 'Z')) ||
           (*(t + 1) == '!')                        ||
           (*(t + 1) == '?')                        ||
           (*(t + 1) == '/')                           )    ) {
        /* “<...”～“>”をキーワード変換対象外とし、そのまま出力 */
        skipTag( fp, gp, t, mode, &inner );
        depth--;
        return;
    }

    while ( (*t == ' ') || (*t == '\t') || (*t == '\r') || (*t == '\n') ) {
        fputc( *t, gp );
        t++;
    }
    if ( *t == '\0' ) {
        depth--;
        return;
    }

    /* 文字列の途中にタグがある場合 */
    if ( ( p = strchr( t, '<' ) ) != NULL ) {
        if ( ((*(p + 1) >= 'a') && (*(p + 1) <= 'z')) ||
             ((*(p + 1) >= 'A') && (*(p + 1) <= 'Z')) ||
             (*(p + 1) == '!')                        ||
             (*(p + 1) == '?')                        ||
             (*(p + 1) == '/')                           ) {
            /* タグの前にある文字列を変換 */
            *p = '\0';
            searchKeyword( fp, gp, t, mode );

            /* タグ部分をそのまま出力した後、それ以降の文字列を変換 */
            *p = '<';
            t = p;
            searchKeyword( fp, gp, t, mode );
            depth--;
            return;
        }
    }

    /* タグが含まれない文字列の場合 */
    rewind( fp ); /* キーワードファイルの先頭に戻る */
    while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
        /* キーワードを取得し、キーワード検索を実行 */
        if ( (*p == '\n') || (*p == '\r') )
            continue;
        len = strlen( p );
        while ( (p[len - 1] == '\n') || (p[len - 1] == '\r') ) {
            p[len - 1] = '\0';
            len--;
        }
        if ( (len == 0) || !(*p) )
            continue;

        if ( ( r = strstr( t, p ) ) != NULL ) {
            /* 検索対象にキーワードが含まれる場合 */
            *r = '\0';
            /* 今回マッチした部分よりも前の部分にもキーワードがある可能性が */
            /* あるので、前の部分だけ切り出して探索を実行                   */
            if ( t && *t )
                searchKeyword( fp, gp, t, mode );

            /* 自動リンク生成 */
            if ( mode == MODE_HTML )
                fprintf( gp, "<a class=\"hatena\" "
                         "href=\"http://d.hatena.ne.jp/keyword/%s\">%s</a>",
                         encodeURL( p ), p ); /* リンクを生成 */
            else
                fprintf( gp, "&lt;a class=\"hatena\" "
                  "href=\"http://d.hatena.ne.jp/keyword/%s\"&gt;%s&lt;/a&gt;",
                         encodeURL( p ), p ); /* リンクを生成 */

            /* 検索対象の残りの部分について、さらに探索を続ける */
            t = r + strlen( p );
            searchKeyword( fp, gp, t, mode );
            flag = 0;
            break;
        }
    }

    /* キーワードが見つからなかった場合は、そのまま出力 */
    if ( flag )
        fputs( t, gp );

    /* 領域解放 */
    encodeURL( NULL );
    depth--;
}

#if 0
static void
makeAutoLink( FILE *fp, FILE *gp )
{
    char    *p, *q;
    char    buf[BUFSIZ];

    while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
        /* EUC-JP に変換 */
        if ( codeSet != CSET_EUCJP ) {
            switch ( codeSet ) {
            case CSET_SHIFTJIS:
                q = sjis2euc( p );
                break;
            case CSET_ISO2022JP:
                q = jis2euc( p );
                break;
            case CSET_UTF8:
                q = utf2euc( p );
                break;
            default:
                q = p;
                break;
            }

            if ( !q )
                continue;

            p = q;
        }

        searchKeyword( gp, stdout, p, MODE_HTML );
    }
}
#endif

static void
searchKeywordEx( FILE *fp, char *dst, const char *src, int mode )
{
    char    *p, *q;
    char    buf[BUFSIZ];
    FILE    *gp;
    char    tempfile[MAX_PATH];

    sprintf( tempfile, "%stempTemp.$$$", xmlrpc_p->dataDir );
    if ( ( gp = fopen( tempfile, "w" ) ) != NULL ) {
        /* EUC-JP に変換 */
        p = (char *)src;
        if ( codeSet != CSET_EUCJP ) {
            switch ( codeSet ) {
            case CSET_SHIFTJIS:
                q = sjis2euc( src );
                break;
            case CSET_ISO2022JP:
                q = jis2euc( src );
                break;
            case CSET_UTF8:
                q = utf2euc( src );
                break;
            default:
                q = (char *)src;
                break;
            }

            if ( q )
                p = q;
        }

        searchKeyword( fp, gp, p, mode );
        fclose( gp );

        dst[0] = '\0';
        if ( ( gp = fopen( tempfile, "r" ) ) != NULL ) {
            while ( ( p = fgets( buf, BUFSIZ - 1, gp ) ) != NULL )
                strcat( dst, p );
            fclose( gp );
        }

        unlink( tempfile );
    }
    else
        strcpy( dst, src );
}



/*
 *  キーワードファイル名取得
 */

static char *
getKeywordFilename()
{
    char        *filename = NULL;
    char        *dirname  = NULL;
    static char keywordFilename[MAX_PATH];

    keywordFilename[0] = '\0';
    if ( xmlrpc_p ) {
        if ( xmlrpc_p->dataDir[0] )
            dirname  = xmlrpc_p->dataDir;
        if ( xmlrpc_p->keywordList[0] )
            filename = xmlrpc_p->keywordList; 
    }
    if ( !dirname || !(dirname[0]) )
        dirname  = "./";
    if ( !filename || !(filename[0]) )
        filename = "keyword.lst";
    strcpy( keywordFilename, dirname  );
    strcat( keywordFilename, filename );

    return ( keywordFilename );
}


/*
 *  キーワードファイルフォーマット変換
 */
static int
changeFormat( const char *srcFile, const char *dstFile )
{
    FILE    *fp, *gp;
    char    buf[BUFSIZ];
    char    *p;
    int     ret = 0;

    if ( ( fp = fopen( srcFile, "r" ) ) != NULL ) {
        if ( ( gp = fopen( dstFile, "w" ) ) != NULL ) {
            while ( ( p = fgets( buf, BUFSIZ, fp ) ) != NULL ) {
                if ( (*p == '\r') || (*p == '\n') )
                    break;
            }
            clearerr( fp );
            while ( ( p = fgets( buf, BUFSIZ, fp ) ) != NULL ) {
                while ( *p ) {
                    if ( *p == '\\' ) {
                        p++;
                        if ( !(*p) )
                            break;
                        if ( *p == 's' )
                            fputc( ' ', gp );
                        else if ( !strncmp( p, "&amp\\;", 6 ) ) {
                            p += 5;
                            fputc( '&', gp );
                        }
                        else if ( !strncmp( p, "&gt\\;", 5 ) ) {
                            p += 4;
                            fputc( '>', gp );
                        }
                        else if ( !strncmp( p, "&lt\\;", 5 ) ) {
                            p += 4;
                            fputc( '<', gp );
                        }
                        else
                            fputc( *p, gp );
                    }
                    else if ( *p != '|' )
                        fputc( *p, gp );
                    else {
                        fputc( '\n', gp );
                        ret++;
                    }
                    p++;
                }
            }
            fputc( '\n', gp );
            ret++;
            fclose( gp );
        }

        fclose( fp );
    }

    return ( ret ); /* キーワード数 */
}



/*
 *  はてなダイアリーキーワードリスト取得
 */

int
getHatenaKeywordList()
{
    char        keywordFilename[MAX_PATH];
    char        originalFilename[MAX_PATH];
    int         needToGet = FALSE;
    struct stat s;
    int         ret = 0;

    strcpy( keywordFilename, getKeywordFilename() );
    strcpy( originalFilename, keywordFilename );
    strcat( originalFilename, ".orig" );

    if ( !stat( keywordFilename, &s ) ) {
        time_t  t = time( NULL );
        if ( s.st_mtime < t - 72 * 60 * 60 )
            needToGet = TRUE;
                /* 前回の取得から 72時間以上経過している場合のみ再取得する */
    }
    else
        needToGet = TRUE;
                /* ファイルが存在しないので、取得する */

    if ( needToGet == FALSE )
        return ( ret ); /* 既存の キーワードリストファイル を使用する */

    /* キーワードリストを取得する */
    ret = httpGetFile( HATENA_API_URL, originalFilename, TRUE );

    /* 取得したキーワードリストを元にキーワードリストファイルを生成する */
    changeFormat( originalFilename, keywordFilename );
#ifndef _DEBUG
    unlink( originalFilename );
#endif

    return ( ret );
}


/*
 * はてなダイアリーキーワードリンク変換
 *    指定文字列中のキーワードが「はてなキーワード」に存在するかどうか調べ、
 *    存在する場合は、リンクを生成する
 *        Copyleft (c) 2004 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  05 Feb 2004
 */

char    *
stripScript( const char *src, char *dst )
{
    const char  *p = src;
    char        *q = dst;

    while ( *p ) {
        if ( *p == '<' ) {
            if ( !strncmp( p + 1, "script ", 7 ) ) {
                char    *r;

                p += 8;
                r = strstr( p, "</script>" );
                if ( r ) {
                    p = r + 9;
                    continue;
                }
            }
        }

        *q++ = *p++;
    }
    *q = NUL;

    return ( dst );
}

char    *
changeHatenaKeyword( const char *src, char *dst, int mode )
{
    FILE    *fp;
    char    keywordFilename[MAX_PATH];
    char    *p = (char *)malloc( (src && *src) ? strlen( src ) + 1
                                               : MAX_CONTENT_SIZE  );
    if ( !p )
        return ( NULL );
    stripScript( src, p );

    if ( (mode != MODE_RAW) && (mode != MODE_HTML) )
        mode = MODE_HTML;

    strcpy( keywordFilename, getKeywordFilename() );
    if ( ( fp = fopen( keywordFilename, "r" ) ) == NULL ) {
        getHatenaKeywordList();
        fp = fopen( keywordFilename, "r" );
    }
    if ( fp ) {
        char    *q = decodeURL( p );
        if ( q ) {
            char    *r = (char *)malloc( strlen( q ) + 1 );
            if ( r ) {
                strcpy( r, q );
                searchKeywordEx( fp, dst, r, mode );
                free( r );
            }
        }
        fclose( fp );
    }
    else
        strcpy( dst, p );

    free( p );

    return ( dst );
}


/* はてなダイアリーキーワード自動リンクAPI  2004.06.15 */
/*
 *      uri: http://d.hatena.ne.jp/xmlrpc 
 *      encoding: utf8 
 *      methodName: hatena.setKeywordLink 
 *      parameters: 以下を参照 
 *          body(string): キーワードを抽出するテキストを指定します。 
 *          score(int): 0～50。キーワードスコアのしきい値を指定します。
 *                      指定された値よりもスコアが大きいキーワードのみが抽
 *                      出されます。
 *          cname(array): キーワードのカテゴリーを指定します。指定があった
 *                        場合、「一般」と指定されたカテゴリーのキーワード
 *                        が抽出されます。指定が無かった場合は、全カテゴリー
 *                        となります。
 *                        book,music,movie,web,elec,animal,anime,food,sports,
 *                        game,comic,hatena,clubが指定可能です。省略可。
 *          a_target(string): アンカー(a)タグのtarget属性値を指定します。
 *                            例：_blank 
 *          a_class(string): アンカー(a)タグのclass属性値を指定します。
 *                           例：keyword 
 *      [cname は 2004年6月17日に追加された引数]
 */

char    *
setKeywordLink( const char    *src,
                char          *dst,
                size_t        dstSize,
                int           score,
                unsigned long cname,
                const char    *target,
                const char    *keywordClass )
{
    int     ret = FALSE;
    char    *request;
    char    *response;
    char    *tmp = NULL;
    size_t  sz, len;

    if ( dstSize < strlen( src ) )
        return ( NULL );
    tmp = (char *)malloc( strlen( src ) * 6 + 1 );
    if ( !tmp )
        return ( NULL );
    encodeString( src, tmp );

    len = MAX_CONTENT_SIZE + strlen( tmp );
    request = (char *)malloc( len );
    if ( !request ) {
        free( tmp );
        return ( NULL );
    }
    memset( request, 0x00, len );

    sz = len * 16;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( tmp );
        return ( response );
    }

    setTargetURL( HATENA_ENDPOINT_URL );
    if ( cname == CNAME_GENERAL ) {
	    sprintf( request,
                 XML_STATEMENT
             "<methodCall>\n<methodName>hatena.setKeywordLink</methodName>\n"
             "<params>\n<param>\n<value>\n<struct>\n"
             "<member>\n<name>body</name>\n<value>%s</value>\n</member>\n"
             "<member>\n<name>score</name>\n"
             "<value><i4>%d</i4></value>\n</member>\n"
             "<member>\n<name>a_target</name>\n<value>%s</value>\n</member>\n"
             "<member>\n<name>a_class</name>\n<value>%s</value>\n</member>\n"
             "</struct>\n</value>\n</param>\n</params>\n"
             "</methodCall>\n\n",
                 tmp,
                 score <  0 ?  0 :
                 score > 50 ? 50 :
                              score,
                 target,
                 keywordClass );
    }
    else {
        int len;

	    sprintf( request,
                 XML_STATEMENT
              "<methodCall>\n<methodName>hatena.setKeywordLink</methodName>\n"
              "<params>\n<param>\n<value>\n<struct>\n"
              "<member>\n<name>body</name>\n<value>%s</value>\n</member>\n"
              "<member>\n<name>score</name>\n"
              "<value><i4>%d</i4></value>\n</member>\n",
                 tmp,
                 score <  0 ?  0 :
                 score > 50 ? 50 :
                              score );

        strcat( request,
                "<member>\n<name>cname</name>\n<value>\n<array>\n<data>\n" );

        if ( (cname & CNAME_BOOK)   == CNAME_BOOK ) {
            strcat( request, "<value><string>book</string></value>\n" );
        }
        if ( (cname & CNAME_MUSIC)  == CNAME_MUSIC ) {
            strcat( request, "<value><string>music</string></value>\n" );
        }
        if ( (cname & CNAME_MOVIE)  == CNAME_MOVIE ) {
            strcat( request, "<value><string>movie</string></value>\n" );
        }
        if ( (cname & CNAME_WEB)    == CNAME_WEB ) {
            strcat( request, "<value><string>web</string></value>\n" );
        }
        if ( (cname & CNAME_ELEC)   == CNAME_ELEC ) {
            strcat( request, "<value><string>elec</string></value>\n" );
        }
        if ( (cname & CNAME_ANIMAL) == CNAME_ANIMAL ) {
            strcat( request, "<value><string>animal</string></value>\n" );
        }
        if ( (cname & CNAME_ANIME)  == CNAME_ANIME ) {
            strcat( request, "<value><string>anime</string></value>\n" );
        }
        if ( (cname & CNAME_FOOD)   == CNAME_FOOD ) {
            strcat( request, "<value><string>food</string></value>\n" );
        }
        if ( (cname & CNAME_SPORTS) == CNAME_SPORTS ) {
            strcat( request, "<value><string>sports</string></value>\n" );
        }
        if ( (cname & CNAME_GAME)   == CNAME_GAME ) {
            strcat( request, "<value><string>game</string></value>\n" );
        }
        if ( (cname & CNAME_COMIC)  == CNAME_COMIC ) {
            strcat( request, "<value><string>comic</string></value>\n" );
        }
        if ( (cname & CNAME_HATENA) == CNAME_HATENA ) {
            strcat( request, "<value><string>hatena</string></value>\n" );
        }
        if ( (cname & CNAME_CLUB)   == CNAME_CLUB ) {
            strcat( request, "<value><string>club</string></value>\n" );
        }

        strcat( request,
                "</data>\n</array>\n</value>\n</member>\n" );

        len = strlen( request );
        sprintf( request + len,
             "<member>\n<name>a_target</name>\n<value>%s</value>\n</member>\n"
             "<member>\n<name>a_class</name>\n<value>%s</value>\n</member>\n"
             "</struct>\n</value>\n</param>\n</params>\n"
             "</methodCall>\n\n",
                 target,
                 keywordClass );
    }

    dst[0] = NUL;
    setUpReceiveBuffer( response, sz );
    ret = httpPostEx( request, response );

    if ( (ret == 0) || (*response != NUL) ) {
        /* 以下、http://i.hatena.ne.jp/idea/23100 の件の暫定対処 */
        /* (はてな側の不具合が原因。不具合が直れば、この暫定処理 */
        /* は不要になる)                                         */
        const char  *word =
            "&lt;a class=&quot;hatena&quot; target=&quot;_blank&quot; "
            "href=&quot;http://d.hatena.ne.jp/keyword/&quot;&gt;&lt;/a&gt;";
        char    *p = strstr( response, word );
        if ( p ) {
            int len = strlen(word);
            while ( p ) {
                strcpy( p, p + len );
                p = strstr( response, word );
            }
        }
    }

    if ( (ret == 0) || (*response != NUL) ) {
        char    *p = response;
        char    *q = strstr( p, "<string>" ), *r;

        if ( q ) {
            q += 8;
            r = strstr( q, "</string>" );
            if ( r ) {
                size_t  len = min( dstSize - 1, (size_t)(r - q) );
                strncpy( dst, q, len == dstSize - 1 ? len - 1 : len );
                dst[len] = NUL;
                if ( len == dstSize - 1 ) {
                    char    *p = strrchr( dst, '>' );
                    if ( p )
                        *(p + 1) = NUL;
                }
                decodeString( dst );
            }
        }
    }

    free( response );
    free( request );
    free( tmp );

    return ( dst );
} 


/*
 *  はてなブックマーク
 */

/*
 *  getASIN()
 *      URL に含まれる ASIN を取り出す
 *      (amazon, はてな の URL が対象)
 */
static char *
getASIN(
        const char *url,    /* (I) 解析対象 URL */
        char       *asin    /* (O) ASIN 文字列  */
    )
{
    char    *p, *q;

    asin[0] = NUL;
    p = strstr( url, "/ASIN/" );
    if ( !p )
        p = strstr( url, "/asin/" );    /*「はてな」の場合を含む */
    if ( !p ) {
        p = strstr( url, "/gp/product/" );
        if ( p ) {
            p += 6;
            if ( !strncmp( p + 6, "images/", 7 ) )
                p += 7;
        }
    }
    if ( p )
        p += 6;

    if ( !p && strstr( url, "amazon" ) ) {
        p = strstr( url, "/detail/" );
        if ( p ) {
            /* インスタントストア (このパターンの場合は必ず、直前に */
            /* associate ID が存在する)                             */
            if ( (*(p - 1) >= '0') && (*(p - 1) <= '9') )
                p += 8;
            else
                p = NULL;
        }

        if ( !p ) {
            /* 検索結果 (2006年8月24日ごろから出現し始めた形式) */
            p = strstr( url, "/dp/" );
            if ( p )
                p += 4;
        }
        if ( !p ) {
            /* 
             *  /tg/任意の文字列/-/XXX/ や
             *  /tg/任意の文字列/任意の文字列/-/XXX/ の場合
             */
            p = strstr( url, "/tg/" );
            q = strstr( url, "/-/"  );
            if ( p && q && (p < q) )
                p = q + 3;
            else
                p = NULL;
        }
    }

    if ( p ) {
        if ( !strncmp( p, "list/", 5 ) )
            p += 5;
        q = strchr( p, '/' );
        if ( q ) {
            strncpy( asin, p, q - p );
            asin[q - p] = NUL;
        }
        else if ( strlen( p ) > 10 ) {
            strncpy( asin, p, 10 );
            asin[10] = NUL;
        }
        else
            strcpy( asin, p );
    }

    return ( asin );
}

static char *
getRkm( char *rkm, const char *htmlSrcCode )
{
    char    *p, *q;

    rkm[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"rkm\" " );
    if ( p ) {
        p = strstr( p, "value=\"" );
        if ( p ) {
            p += 7;
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( rkm, p, q - p );
                rkm[q - p] = NUL;
            }
        }
    }
    else {
        p = strstr( htmlSrcCode, " name=\"rks\" " );
        if ( p ) {
            p = strstr( p, "value=\"" );
            if ( p ) {
                p += 7;
                q = strchr( p, '\"' );
                if ( q ) {
                    strncpy( rkm, p, q - p );
                    rkm[q - p] = NUL;
                }
            }
        }
    }

    return ( rkm );
}

static char *
getEid( char *eid, const char *htmlSrcCode )
{
    char    *p, *q;

    eid[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"eid\" " );
    if ( p ) {
        p = strstr( p, "value=\"" );
        if ( p ) {
            p += 7;
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( eid, p, q - p );
                eid[q - p] = NUL;
            }
        }
    }

    return ( eid );
}

static char *
getHref( char *href, const char *htmlSrcCode )
{
    char    *p, *q;

    href[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"url\" " );
    if ( p ) {
        p = strstr( p, "value=\"" );
        if ( p ) {
            p += 7;
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( href, p, q - p );
                href[q - p] = NUL;
            }
        }
    }

    return ( href );
}

static char *
getTitleText( char *title, const char *htmlSrcCode )
{
    char    *p, *q;

    title[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"title\" " );
    if ( p ) {
        p = strstr( p, "value=\"" );
        if ( p ) {
            p += 7;
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( title, p, q - p );
                title[q - p] = NUL;
            }
        }
    }

    return ( title );
}


char    *
makeWSSE( const char *username, const char *password, char *buffer,
          int blogKind );

char    *
makeExtended( const char *tags, const char *summary, char *extended )
{
    const char  *p, *q;
    char        temp[MAX_DESCRIPTION_LEN];
    int         len = 0;

    extended[0] = NUL;
    if ( !tags || !(*tags) ) {
        if ( summary && *summary )
            strcpy( extended, summary );
        return ( extended );
    }

    p = tags;
    while ( *p ) {
        q = strchr( p, ' ' );
        if ( q ) {
            strncpy( temp, p, q - p );
            temp[q - p] = NUL;
            sprintf( extended + len, "[%s]", temp );
            p = q + 1;
            len = strlen( extended );
            continue;
        }

        sprintf( extended + len, "[%s]", p );
        break;
    }
    if ( summary && *summary )
        strcat( extended, summary );

    return ( extended );
}

char    *
getSummary( const char *extended, char *tags, char *summary )
{
    const char  *p;
    char        *r;

    *tags    = NUL;
    *summary = NUL;

    p = utf2sjis( extended );
    if ( !p ) {
        strcpy( summary, extended );
        p = utf2sjisEx( summary );
        if ( !p )
            return ( summary );
    }
    if ( *p != '[' ) {
        strcpy( summary, p );
        return ( summary );
    }

    p++;
    r = tags;
    while ( *p ) {
        /* 課題: Shift_JIS の場合、漢字の2バイト目に '[' や ']' が来る */
        /*       場合があり、現状のコードのままでは誤動作する          */
        while ( *p && (*p != ']') )
            *r++ = *p++;
        if ( (*p == NUL) || (*++p == NUL) )
            break;
        if ( *p != '[' )
            break;

        *r++ = ' ';
        p++;
    }
    *r = NUL;
    if ( p )
        strcpy( summary, p );
    else
        *summary = NUL;

    return ( summary );
}


static long
getPosts(
        const char      *xmlSrc,        /* (I) XML文書 (Atom 0.3)       */
        long            *numOfPosts,    /* (I) 取得するブックマークの数 */
                                        /* (O) 取得したブックマークの数 */
        HATENA_BOOKMARK *posts          /* (O) 取得したブックマーク     */
    )
{
    const char  *p, *q, *r, *s, *t, *u;
    const char  *base;
    char        temp[MAX_DESCRIPTION_LEN];
    int         cnt;
    long        num = 0;

    /*
     * <?xml version="1.0" encoding="utf-8"?>
     * <feed version="0.3"
     *       xmlns="http://purl.org/atom/ns#"
     *       xml:lang="ja">
     *   <title>tsupoのブックマーク</title>
     *   <link rel="alternate" type="text/html" href="http://b.hatena.ne.jp/tsupo/" />
     *   <link rel="service.post" type="application/x.atom+xml" href="http://b.hatena.ne.jp/atom/post" title="tsupoのブックマーク" />
     *   <modified>2005-06-01T14:46:30+09:00</modified>
     *   <author>
     *     <name>tsupo</name>
     *   </author>
     *   <id>tag:hatena.ne.jp,2005:bookmark-tsupo</id>
     *   <generator url="http://b.hatena.ne.jp/" version="0.1">Hatena::Bookmark</generator>
     * 
     *   <entry>
     *     <title>タイトル変更試験#003</title>
     *       <link rel="related" type="text/html" href="http://www.asahi.com/national/update/0531/TKY200505310127.html#test2" />
     *     <link rel="alternate" type="text/html" href="http://b.hatena.ne.jp/tsupo/20050601#275963" />
     *     <link rel="service.edit" type="application/x.atom+xml" href="http://b.hatena.ne.jp/atom/edit/275963" title="タイトル変更試験#003" />
     *     <issued>2005-06-01T14:46:30+09:00</issued>
     *     <author>
     *       <name>tsupo</name>
     *     </author>
     *     <id>tag:hatena.ne.jp,2005:bookmark-tsupo-275963</id>
     *     <summary type="text/plain">はてなブックマークを Atom API で操作してみるテスト。</summary>
     *   </entry>
     *   ……
     * </feed>
     *
     *
     * 2005年7月5日以降、<dc:subject> を使って tag を表現するようになった
     *
     * <entry>
     *  <title>Paj&#39;s Home: Cryptography: JavaScript MD5: sha1.js</title>
     *  <link rel="related" type="text/html" href="http://pajhome.org.uk/crypt/md5/sha1src.html" />
     *  <link rel="alternate" type="text/html" href="http://b.hatena.ne.jp/tsupo/20050715#148091" />
     *  <link rel="service.edit" type="application/x.atom+xml" href="http://b.hatena.ne.jp/atom/edit/148091" title="Paj&#39;s Home: Cryptography: JavaScript MD5: sha1.js" />
     *  <issued>2005-07-15T15:23:40+09:00</issued>
     *  <author>
     *   <name>tsupo</name>
     *  </author>
     *  <id>tag:hatena.ne.jp,2005:bookmark-tsupo-148091</id>
     *  <summary type="text/plain">A JavaScript implementation of the Secure Hash Algorithm, SHA-1</summary>
     *  <dc:subject>Javascript</dc:subject>
     *  <dc:subject>SHA-1</dc:subject>
     *  <dc:subject>library</dc:subject>
     * </entry>
     *
     *
     * 2008年11月25日のリニューアルで、以下のようなフォーマットに変更された [タグ情報が見当たらない]
     *
     * <entry>
     *  <title>Twitter / mala: そんなわけでライブドアにいますよ</title>
     *  <link type="text/html" rel="related" href="http://twitter.com/bulkneets/status/1026257962"/>
     *  <link type="text/html" rel="alternate" href="http://b.hatena.ne.jp/tsupo/20081127#bookmark-11017126"/>
     *  <link type="application/x.atom+xml" rel="service.edit" title="Twitter / mala: そんなわけでライブドアにいますよ" href="http://b.hatena.ne.jp/atom/edit/11017126"/>
     *  <author>
     *    <name>tsupo</name>
     *  </author>
     *  <summary>20:55 京都観光を終えて (mala)</summary>
     *  <id>tag:hatena.ne.jp,2005:bookmark-tsupo-11017126</id>
     *  <issued>2008-11-27T21:57:50</issued>
     * </entry>
     *
     */
    p = xmlSrc;
    while ( ( q = strstr( p, "<entry>" ) ) != NULL ) {
        q += 7;
        u = strstr( p, "</entry>" );
        if ( !u )
            break;
        base = q;

        /* title */
        posts[num].title[0] = NUL;
        r = strstr( base, "<title" );
        if ( r && (r < u) ) {
            r += 6;
            s = strchr( r, '>' );
            if ( s ) {
                s++;
                while ( (*s == '\r') || (*s == '\n') )
                    s++;
                r = strstr( s, "</title>" );
                if ( r ) {
                    strncpy( temp, s, r - s );
                    temp[r - s] = NUL;
                    q = r + 8;
                    s = decodeURL( utf2sjisEx(temp) );
                    strcpy( posts[num].title, s ? s : temp );
                }
            }
        }

        /* href */
        posts[num].href[0] = NUL;
        r = strstr( base, "<link rel=\"related\"" );
        if ( !r ) {
            r = strstr( base, " rel=\"related\" href=\"" );
            if ( r )
                r -= 4;
        }
        if ( r && (r < u) ) {
            r += 19;
            s = strstr( r, "href=\"" );
            if ( s ) {
                s += 6;
                while ( (*s == '\r') || (*s == '\n') )
                    s++;
                r = strchr( s, '"' );
                if ( r ) {
                    strncpy( posts[num].href, s, r - s );
                    posts[num].href[r - s] = NUL;
                    q = r + 1;
                }
            }
        }

        /* entryID */
        posts[num].entryID[0] = NUL;
        r = strstr( base, "<link rel=\"service.edit\"" );
        if ( !r ) {
            r = strstr( base, " rel=\"service.edit\" title=\"" );
            if ( r )
                r += 4;
        }
        if ( r && (r < u) ) {
            r += 24;
            s = strstr( r, "/atom/edit/" );
            if ( !s ) {
                s = strstr( r, "atom/edit/" );
                if ( s )
                    s--;
            }
            if ( s ) {
                s += 11;
                r = strchr( s, '"' );
                if ( r ) {
                    strncpy( posts[num].entryID, s, r - s );
                    posts[num].entryID[r - s] = NUL;
                    q = r + 1;
                }
            }
        }

        /* issued */
        posts[num].yyyy = 0;
        posts[num].mm   = 0;
        posts[num].dd   = 0;
        posts[num].HH   = 0;
        posts[num].MM   = 0;
        posts[num].SS   = 0;
        r = strstr( base, "<issued" );
        if ( r && (r < u) ) {
            r += 7;
            s = strchr( r, '>' );
            if ( s ) {
                s++;
                r = strstr( s, "</issued>" );
                if ( r ) {
                    strncpy( temp, s, r - s );
                    temp[r - s] = NUL;
                    q = r + 9;
                    posts[num].yyyy = atol( temp );
                    posts[num].mm   = ((temp[5] -'0') * 10) + (temp[6] -'0');
                    posts[num].dd   = ((temp[8] -'0') * 10) + (temp[9] -'0');
                    posts[num].HH   = ((temp[11]-'0') * 10) + (temp[12]-'0');
                    posts[num].MM   = ((temp[14]-'0') * 10) + (temp[15]-'0');
                    posts[num].SS   = ((temp[17]-'0') * 10) + (temp[18]-'0');
                }
            }
        }

        /* summary */
        posts[num].summary[0] = NUL;
        r = strstr( base, "<summary" );
        if ( r && (r < u) ) {
            r += 8;
            s = strchr( r, '>' );
            if ( s ) {
                s++;
                while ( (*s == '\r') || (*s == '\n') )
                    s++;
                r = strstr( s, "</summary>" );
                if ( r ) {
                    strncpy( temp, s, r - s );
                    temp[r - s] = NUL;
                    q = r + 10;
                    t = utf2sjisEx(temp);
                    if ( t )
                        strcpy( posts[num].summary, t );
                }
            }
        }

        /* tags */
        posts[num].tags[0] = NUL;
        cnt = 0;
        do {
            r = strstr( base, "<dc:subject>" );
            if ( r && (r < u) ) {
                r += 12;
                s = strstr( r, "</dc:subject>" );
                if ( s ) {
                    strncpy( temp, r, s - r );
                    temp[s - r] = NUL;
                    q = s + 13;
                    t = utf2sjisEx(temp);
                    if ( t ) {
                        if ( cnt > 0 )
                            strcat( posts[num].tags, " " );
                        strcat( posts[num].tags, t );
                    }
                    cnt++;
                }
            }
            else
                break;
        } while ( cnt < 10 );    /* はてなブックマークでは tag は10個まで */

        num++;
        p = u + 8; /* </entry> */
    }
    *numOfPosts = num;

    return ( num );
}

static long
getPostsFromRSS(
        const char      *xmlSrc,        /* (I) XML文書 (RSS 1.0)        */
        long            *numOfPosts,    /* (I) 取得するブックマークの数 */
                                        /* (O) 取得したブックマークの数 */
        HATENA_BOOKMARK *posts          /* (O) 取得したブックマーク     */
    )
{
    const char      *p, *q, *r, *s, *t, *u;
    char            temp[MAX_DESCRIPTION_LEN];
    int             cnt;
    long            num = 0;
    HATENA_BOOKMARK *hb;

    p = xmlSrc;
    while ( ( q = strstr( p, "<item rdf:about=\"" ) ) != NULL ) {
        q += 17;
        u = strstr( q, "</item>" );
        if ( !u )
            break;

        hb = &(posts[num]);

        /* href */
        hb->href[0] = NUL;
        r = strstr( q, "\">" );
        if ( r && (r < u) ) {
            strncpy( hb->href, q, r - q );
            hb->href[r - q] = NUL;
            q = r + 2;
            // 「はてなブックマーク2」ではブックマークへのリンクが
            // 格納されるようになった
        }

        /* title */
        hb->title[0] = NUL;
        r = strstr( q, "<title>" );
        if ( r && (r < u) ) {
            r += 7;
            while ( (*r == '\r') || (*r == '\n') )
                r++;
            s = strstr( r, "</title>" );
            if ( s ) {
                strncpy( temp, r, s - r );
                temp[s - r] = NUL;
                q = s + 8;
                s = decodeURL( utf2sjisEx(temp) );
                strcpy( hb->title, s ? s : temp );
            }
        }

        /* link (for はてなブックマーク2) */
        r = strstr( q, "<link>" );
        if ( r && (r < u) ) {
            r += 6;
            s = strstr( r, "</link>" );
            if ( s ) {
                strncpy( hb->href, r, s - r );
                hb->href[s - r] = NUL;
                q = s + 7;
            }
        }

        /* entryID (はてなブックマークの RSS フィードバージョンには entryID */
        /*          に関する情報が格納されていない)                         */
        hb->entryID[0] = NUL;

        /* summary */
        hb->summary[0] = NUL;
        r = strstr( q, "<description>" );
        if ( r && (r < u) ) {
            r += 13;
            s = strstr( r, "</description>" );
            if ( s ) {
                strncpy( temp, r, s - r );
                temp[s - r] = NUL;
                q = s + 14;
                t = utf2sjisEx(temp);
                if ( t )
                    strcpy( hb->summary, t );
            }
        }

        /* issued */
        hb->yyyy = 0;
        hb->mm   = 0;
        hb->dd   = 0;
        hb->HH   = 0;
        hb->MM   = 0;
        hb->SS   = 0;
        r = strstr( q, "<dc:date>" );
        if ( r && (r < u) ) {
            r += 9;
            s = strstr( r, "</dc:date>" );
            if ( s ) {
                strncpy( temp, r, s - r );
                temp[s - r] = NUL;
                q = s + 10;
                hb->yyyy = atol( temp );
                hb->mm   = ((temp[5] -'0') * 10) + (temp[6] -'0');
                hb->dd   = ((temp[8] -'0') * 10) + (temp[9] -'0');
                hb->HH   = ((temp[11]-'0') * 10) + (temp[12]-'0');
                hb->MM   = ((temp[14]-'0') * 10) + (temp[15]-'0');
                hb->SS   = ((temp[17]-'0') * 10) + (temp[18]-'0');
            }
        }

        /* tags */
        hb->tags[0] = NUL;
        cnt = 0;
        do {
            r = strstr( q, "<dc:subject>" );
            if ( r && (r < u) ) {
                r += 12;
                s = strstr( r, "</dc:subject>" );
                if ( s ) {
                    strncpy( temp, r, s - r );
                    temp[s - r] = NUL;
                    q = s + 13;
                    t = utf2sjisEx(temp);
                    if ( t ) {
                        if ( cnt > 0 )
                            strcat( hb->tags, " " );
                        strcat( hb->tags, t );
                    }
                    cnt++;
                }
            }
            else
                break;
        } while ( cnt < 10 );    /* はてなブックマークでは tag は10個まで */

        num++;
        p = u + 7; /* </item> */
    }
    *numOfPosts = num;

    return ( num );
}


/* 新規ブックマークの投稿 (PostURI への POST) */

char    *
encodeAmpersand( const char *str )
{
    static char buf[MAX_URLLENGTH * 4];
    const char  *p;
    char        *q;

    p = str;
    q = strchr( p, '&' );
    if ( !q ) {
        strcpy( buf, p );
        return ( buf );
    }

    q = buf;
    while ( *p ) {
        *q++ = *p;
        if ( *p == '&' ) {
            *q++ = 'a';
            *q++ = 'm';
            *q++ = 'p';
            *q++ = ';';
        }
        p++;
    }
    *q = NUL;

    return ( buf );    
}

BOOL
postBookmarkOnHatena(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        const char *href,   /* (I) ブックマーク対象 Web ページ URL       */
        char       *title,  /* (O) 題名                                  */
        const char *summary,/* (I) コメント                              */
        const char *tags,   /* (I) tag (空白文字で区切って複数tag指定可) */
        char       *entryID /* (O) edit用エントリID                      */
    )
{
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    extended[MAX_DESCRIPTION_LEN * 2];
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !href || !(*href) || !entryID )
        return ( ret );

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    memset( wsse,    0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/post", HATENA_B_ENDPOINT_URL );
    setTargetURL( url );

    /*
     * <entry xmlns="http://purl.org/atom/ns#">
     *  <title>dummy</title>
     *  <link rel="related" type="text/html" href="http://www.example.com/" />
     *  <summary type="text/plain">[tag1][tag2]…[tagN]コメント</summary>
     * </entry>
     */
    memset( extended, 0x00, MAX_DESCRIPTION_LEN * 2 );
    makeExtended( tags, summary, extended );

    sprintf( request,
             "<entry xmlns=\"http://purl.org/atom/ns#\">\n"
             "<title>dummy</title>\n"
             "<link rel=\"related\" type=\"text/html\" href=\"%s\" />\n",
             encodeAmpersand(href) );
    if ( *extended ) {
        char    *p = sjis2utf(extended);
        sprintf( request + strlen(request),
                 "<summary type=\"text/plain\">%s</summary>\n",
                 encodeAmpersand( p ? p : extended ) );
    }
    sprintf( request + strlen(request),
             "</entry>" );

    setUpReceiveBuffer( response, sz );
    res = httpPostEx2( xmlrpc_p->webServer, xmlrpc_p->webPage,
                       request, response,
                       wsse );

    if ( response[0] != NUL ) {
        char    *p, *q;
        char    newExtended[MAX_DESCRIPTION_LEN * 2];
        BOOL    nesessaryToEdit = TRUE;

        /*
         * <?xml version="1.0" encoding="utf-8"?>
         * <entry xmlns="http://purl.org/atom/ns#">
         *  <title>Example Web Page</title>
         *  <link rel="related" type="text/html" href="http://www.example.com/" />
         *  <link rel="alternate" type="text/html" href="http://b.hatena.ne.jp/tsupo/20050531#275963" />
         *  <link rel="service.edit" type="application/x.atom+xml" href="http://b.hatena.ne.jp/atom/edit/275963" title="Example Web Page" />
         *  <author>
         *   <name>tsupo</name>
         *  </author>
         *  <generator url="http://b.hatena.ne.jp/" version="0.1">Hatena::Bookmark</generator>
         *  <issued>2005-05-31T15:49:07+09:00</issued>
         *  <id>tag:hatena.ne.jp,2005:bookmark-tsupo-275963</id>
         *  <summary type="text/plain">[tag1][tag2]…[tagN]コメント</summary>
         * </entry>
         */
        entryID[0]     = NUL;
        title[0]       = NUL;
        newExtended[0] = NUL;
        p = strstr( response, "<link rel=\"service.edit\"" );
        if ( p ) {
            p += 24;
            q = strstr( p, "/atom/edit/" );
            if ( !q ) {
                q = strstr( p, "atom/edit/" );
                if ( q )
                    q--;
            }
            if ( q ) {
                q += 11;
                p = strchr( q, '"' );
                if ( p ) {
                    strncpy( entryID, q, p - q );
                    entryID[p - q] = NUL;
                    ret = TRUE;
                }
            }

            q = strstr( response, "<title>" );
            if ( q ) {
                char    temp[1024];

                q += 7;
                p = strstr( q, "</title>" );
                strncpy( temp, q, p - q );
                temp[p - q] = NUL;
                p = utf2sjis(temp);
                if ( !p )
                    p = utf2sjisEx(temp);
                if ( p )
                    strcpy( title, p );
            }

            q = strstr( response, "<summary " );
            if ( q ) {
                q += 9;
                p = strchr( q, '>' );
                if ( p ) {
                    p++;
                    q = strstr( p, "</summary>" );
                    if ( q ) {
                        strncpy( newExtended, p, q - p );
                        newExtended[q - p] = NUL;
                        p = sjis2utf( extended );
                        if ( !strcmp( newExtended, p ? p : extended ) )
                            nesessaryToEdit = FALSE;
                    }
                }
            }

            if ( nesessaryToEdit && title[0] && entryID[0] )
                ret = editBookmarkOnHatena( usrname, passwd, href,
                                            /*utf2sjisEx(title)*/ title,
                                            summary, tags, entryID );
        }
    }

    free( response );
    free( request );

    return ( ret );
}


/* 投稿したブックマークの参照 (EditURI への GET) */

BOOL
getBookmarkOnHatena(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        char       *href,   /* (O) ブックマーク対象 Web ページ URL       */
        char       *title,  /* (O) 題名                                  */
        char       *summary,/* (O) コメント                              */
        char       *tags,   /* (O) tag (空白文字で区切って複数tag指定可) */
        const char *entryID /* (I) edit用エントリID                      */
    )
{
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    extended[MAX_DESCRIPTION_LEN * 2];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !entryID || !(*entryID) || !href || !title || !summary || !tags )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/edit/%s", HATENA_B_ENDPOINT_URL, entryID );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     wsse );

    if ( response[0] != NUL ) {
        char    *p, *q;

        /* title   */
        p = strstr( response, "<title" );
        if ( p ) {
            p += 6;
            q = strchr( p, '>' );
            if ( q ) {
                q++;
                p = strchr( q, '<' );
                if ( p ) {
                    char    temp[BUFSIZ];
                    char    *r;

                    strncpy( temp, q, p - q );
                    temp[p - q] = NUL;
                    r = utf2sjis( temp );
                    if ( !r )
                        r = utf2sjisEx( temp );
                    strcpy( title, r ? r : temp );
                    ret = TRUE;
                }
            }
        }

        /* href    */
        p = strstr( response, "<link rel=\"related\"" );
        if ( p ) {
            p += 19;
            q = strstr( p, "href=\"" );
            if ( q ) {
                q += 6;
                p = strchr( q, '"' );
                if ( p ) {
                    strncpy( href, q, p - q );
                    href[p - q] = NUL;
                }
            }
        }

        /* summary */
        p = strstr( response, "<summary" );
        if ( p ) {
            p += 8;
            q = strchr( p, '>' );
            if ( q ) {
                q++;
                p = strchr( q, '<' );
                if ( p ) {
                    strncpy( extended, q, p - q );
                    extended[p - q] = NUL;
                    getSummary( extended, tags, summary );
                }
            }
        }

        /* tags */
        if ( tags[0] == NUL ) {
            char    temp[MAX_DESCRIPTION_LEN];
            char    *s, *t, *u;
            int     cnt = 0;

            do {
                q = strstr( p, "<dc:subject>" );
                u = strstr( p, "</entry>" );
                if ( q && u && (q < u) ) {
                    q += 12;
                    s = strstr( q, "</dc:subject>" );
                    if ( s ) {
                        strncpy( temp, q, s - q );
                        temp[s - q] = NUL;
                        p = s + 13;
                        t = utf2sjisEx(temp);
                        if ( t ) {
                            if ( cnt > 0 )
                                strcat( tags, " " );
                            strcat( tags, t );
                        }
                        cnt++;
                    }
                }
                else
                    break;
            } while ( cnt < 10 ); /* はてなブックマークでは tag は10個まで */
        }
    }

    free( response );

    return ( ret );
}

BOOL
getBookmarkOnHatenaWithURI(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        const char *href,   /* (I) ブックマーク対象 Web ページ URL       */
        char       *title,  /* (O) 題名                                  */
        char       *summary,/* (O) コメント                              */
        char       *tags,   /* (O) tag (空白文字で区切って複数tag指定可) */
        char       *entryID /* (O) edit用エントリID                      */
    )
{
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    extended[MAX_DESCRIPTION_LEN * 2];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !href || !(*href) || !href ||
        !title || !summary || !tags || !entryID )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/edit?url=%s", HATENA_B_ENDPOINT_URL, href );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     wsse );

    if ( response[0] != NUL ) {
        char    *p, *q;

        /* title   */
        p = strstr( response, "<title" );
        if ( p ) {
            p += 6;
            q = strchr( p, '>' );
            if ( q ) {
                char    *pp = sjis2utf("はてなブックマーク - ");
                size_t  len = strlen(pp);
                q++;
                if ( !strncmp( q, pp, len ) )
                    q += len;
                p = strchr( q, '<' );
                if ( p ) {
                    char    temp[BUFSIZ];
                    char    *r;

                    strncpy( temp, q, p - q );
                    temp[p - q] = NUL;
                    r = utf2sjis( temp );
                    if ( !r )
                        r = utf2sjisEx( temp );
                    strcpy( title, r ? r : temp );
                    ret = TRUE;
                }
            }
        }

        /* id      */
        p = strstr( response, "<id>" );
        if ( p ) {
            p += 4;
            q = strstr( p, "</id>" );
            if ( q ) {
                char    temp[BUFSIZ];

                strncpy( temp, p, q - p );
                temp[q - p] = NUL;
                strcpy( entryID, strrchr( temp, '-' ) + 1 );
                p = q + 5;
            }
        }

        /* summary */
        p = strstr( response, "<summary" );
        if ( p ) {
            p += 8;
            q = strchr( p, '>' );
            if ( q ) {
                q++;
                p = strchr( q, '<' );
                if ( p ) {
                    strncpy( extended, q, p - q );
                    extended[p - q] = NUL;
                    getSummary( extended, tags, summary );
                }
            }
        }

        /* tags */
        if ( tags[0] == NUL ) {
            char    temp[MAX_DESCRIPTION_LEN];
            char    *s, *t, *u;
            int     cnt = 0;

            if ( !p )
                p = response;
            do {
                q = strstr( p, "<dc:subject>" );
                u = strstr( p, "</entry>" );
                if ( q && u && (q < u) ) {
                    q += 12;
                    s = strstr( q, "</dc:subject>" );
                    if ( s ) {
                        strncpy( temp, q, s - q );
                        temp[s - q] = NUL;
                        p = s + 13;
                        t = utf2sjisEx(temp);
                        if ( t ) {
                            if ( cnt > 0 )
                                strcat( tags, " " );
                            strcat( tags, t );
                        }
                        cnt++;
                    }
                }
                else
                    break;
            } while ( cnt < 10 ); /* はてなブックマークでは tag は10個まで */
        }
    }

    free( response );

    return ( ret );
}



/* 投稿したブックマークのタイトル、コメントの変更 (EditURI への PUT) */
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
BOOL
editBookmarkOnHatena(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        const char *href,   /* (I) ブックマーク対象 Web ページ URL       */
        const char *title,  /* (I) 題名                                  */
        const char *summary,/* (I) コメント                              */
        const char *tags,   /* (I) tag (空白文字で区切って複数tag指定可) */
        const char *entryID /* (I) edit用エントリID                      */
    )
{
    /* 注意: この API では href は変更できない */
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    extended[MAX_DESCRIPTION_LEN * 2];
    char    *request;
    char    *response;
    char    *p, *q;
    char    tmp1[8], tmp2[8];
    size_t  sz = MAX_CONTENT_SIZE;

    if ( /* !href || !(*href) || */
         !entryID || !(*entryID) ||
         !title   || !(*title)      )
        return ( ret );

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    memset( wsse,    0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/edit/%s", HATENA_B_ENDPOINT_URL, entryID );
    setTargetURL( url );

    /*
     *  <entry xmlns="http://purl.org/atom/ns#">
     *      <title>New Title</title>
     *      <summary type="text/plain">[tag1][tag2]…[tagN]コメント</summary>
     *  </entry>
     */
    memset( extended, 0x00, MAX_DESCRIPTION_LEN * 2 );
    makeExtended( tags, summary, extended );
    strcpy( tmp1, sjis2utf( "≫" ) );
    strcpy( tmp2, sjis2utf( "≪" ) );
    p = sjis2utf(title);
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
    sprintf( request,
             "<entry xmlns=\"http://purl.org/atom/ns#\">\n"
             "<title>%s</title>\n",
             p ? p : title );
    if ( *extended ) {
        p = sjis2utf(extended);
        sprintf( request + strlen( request ),
                 "<summary type=\"text/plain\">%s</summary>\n",
                 p ? p : extended );
    }
    sprintf( request + strlen( request ),
             "</entry>" );

    setUpReceiveBuffer( response, sz );
    res = httpPutEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     request, response,
                     wsse );

 /* if ( response[0] != NUL ) */
        ret = TRUE;

    free( response );
    free( request );

    return ( ret );
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

/* 投稿したブックマークの削除 (EditURI への DELETE) */

BOOL
deleteBookmarkOnHatena(
        const char *usrname,/* (I) ユーザ名         */
        const char *passwd, /* (I) パスワード       */
        const char *entryID /* (I) edit用エントリID */
    )
{
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !entryID || !(*entryID) )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/edit/%s", HATENA_B_ENDPOINT_URL, entryID );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpDeleteEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        response, NULL, FALSE,
                        wsse );
    if ( *response ) {
        if ( !strstr( response, "403 Forbidden" ) )
            ret = TRUE;
    }

    free( response );

    return ( ret );
}


/* 最近投稿したブックマークの一覧の取得 (FeedURI への GET) */

long
getRecentPostsOnHatena(
        const char      *usrname,       /* (I) ユーザ名                 */
        const char      *passwd,        /* (I) パスワード               */
        long            *numOfPosts,    /* (I) 取得するブックマークの数 */
                                        /* (O) 取得したブックマークの数 */
        HATENA_BOOKMARK *posts          /* (O) 取得したブックマーク     */
    )
{
    long    num = 0;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts || (*numOfPosts <= 0) || !posts )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );
    response[0] = NUL;

    sprintf( url, "%s/feed", HATENA_B_ENDPOINT_URL );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     wsse );

    if ( response[0] != NUL )
        num = getPosts( response, numOfPosts, posts );

    free( response );

    return ( num );
}


/* 指定ユーザの最近投稿したブックマークの一覧の取得 (REST API) */
long
getRecentPostsOnHatenaUser(
        const char      *username,      /* (I) 取得対象ユーザ名(はてなID)   */
        long            offset,         /* (I) 取得開始ブックマーク位置     */
        long            *numOfPosts,    /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        HATENA_BOOKMARK *posts,         /* (O) 取得したブックマーク         */
        BOOL            *more           /* (O) 取得可能残存ブックマーク有無 */
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         (offset < 0) || !more )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;

#ifdef  USE_ATOMFEED
    sprintf( url, "http://b.hatena.ne.jp/%s/atomfeed?of=%d",
             username, offset );
#else
    sprintf( url, "http://b.hatena.ne.jp/%s/rss?of=%d",
             username, offset );
#endif
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     NULL );

    if ( response[0] != NUL ) {
        const char  *p = response;

#ifdef  USE_ATOMFEED
        if (strstr(p, "<link rel=\"next\" type=\"application/atom+xml\""  )||
            strstr(p, "<link rel=\"next\" type=\"application/x.atom+xml\"")  )
            *more = TRUE;
        else
            *more = FALSE;

        num = getPosts( response, numOfPosts, posts );
#else
        /*
         * <opensearch:startIndex>401</opensearch:startIndex> 
         * <opensearch:itemsPerPage>20</opensearch:itemsPerPage> 
         * <opensearch:totalResults>13556</opensearch:totalResults> 
         */

        int     startIndex   = 0;
        int     itemsPerPage = 0;
        int     totalResults = 0;
        char    *q;

        q = strstr( p, "<opensearch:startIndex>" );
        if ( q )
            startIndex = atol( q + 23 );
        q = strstr( p, "<opensearch:itemsPerPage>" );
        if ( q )
            itemsPerPage = atol( q + 25 );
        q = strstr( p, "<opensearch:totalResults>" );
        if ( q )
            totalResults = atol( q + 25 );

        *more = FALSE;
        if ( totalResults > 0 ) {
            int rest = totalResults - startIndex;
            if ( rest > itemsPerPage )
                *more = TRUE;
        }

        num = getPostsFromRSS( response, numOfPosts, posts );
#endif
    }

    free( response );

    return ( num );
}

long
getRecentPostsOnHatenaUserWithTag(
        const char      *username,      /* (I) 取得対象ユーザ名(はてなID)   */
        const char      *tag,           /* (I) 検索条件 (tag)               */
        long            offset,         /* (I) 取得開始ブックマーク位置     */
        long            *numOfPosts,    /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        HATENA_BOOKMARK *posts,         /* (O) 取得したブックマーク         */
        BOOL            *more           /* (O) 取得可能残存ブックマーク有無 */
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    char    *target;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         !tag         || !(*tag)            ||
         (offset < 0) || !more )
        return ( num );

    target = sjis2utf( tag );
    if ( !target )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;

    sprintf( url, "http://b.hatena.ne.jp/%s/atomfeed?tag=%s&of=%d",
             username, target, offset );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     NULL );

    if ( response[0] != NUL ) {
        char    *p;

        p = response;
        if ( strstr( p, "<link rel=\"next\" type=\"application/atom+xml\"" ) )
            *more = TRUE;
        else
            *more = FALSE;

        num = getPosts( response, numOfPosts, posts );
    }

    free( response );

    return ( num );
}

long
getRecentPostsOnHatenaUserWithWord(
        const char      *username,      /* (I) 取得対象ユーザ名(はてなID)   */
        const char      *word,          /* (I) 検索条件 (キーワード)        */
        long            offset,         /* (I) 取得開始ブックマーク位置     */
        long            *numOfPosts,    /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        HATENA_BOOKMARK *posts,         /* (O) 取得したブックマーク         */
        BOOL            *more           /* (O) 取得可能残存ブックマーク有無 */
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    char    *target;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         !word        || !(*word)           ||
         (offset < 0) || !more )
        return ( num );

    target = sjis2utf( word );
    if ( !target )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;

    sprintf( url, "http://b.hatena.ne.jp/%s/atomfeed?word=%s&of=%d",
             username, target, offset );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     NULL );

    if ( response[0] != NUL ) {
        char    *p;

        p = response;
        if ( strstr( p, "<link rel=\"next\" type=\"application/atom+xml\"" ) )
            *more = TRUE;
        else
            *more = FALSE;

        num = getPosts( response, numOfPosts, posts );
    }

    free( response );

    return ( num );
}

long
getRecentPostsOnHatenaUserWithDate(
        const char      *username,      /* (I) 取得対象ユーザ名(はてなID)   */
        const char      *date,          /* (I) 検索条件 (日付,yyyymmdd形式) */
        long            offset,         /* (I) 取得開始ブックマーク位置     */
        long            *numOfPosts,    /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        HATENA_BOOKMARK *posts,         /* (O) 取得したブックマーク         */
        BOOL            *more           /* (O) 取得可能残存ブックマーク有無 */
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         !date        || !(*date)           ||
         (offset < 0) || !more )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;

    sprintf( url, "http://b.hatena.ne.jp/%s/atomfeed?date=%s&of=%d",
             username, date, offset );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     NULL );

    if ( response[0] != NUL ) {
        char    *p;

        p = response;
#if 0
        if ( strstr( p, "<link rel=\"next\" type=\"application/atom+xml\"" ) )
            *more = TRUE;
        else
            *more = FALSE;
#else
        *more = FALSE;
#endif

        num = getPosts( response, numOfPosts, posts );
    }

    free( response );

    return ( num );
}


/* ブックマークに付けたタグの一括置換
                    (REST API, はてなに login 済みの状態である必要あり) */
BOOL
renameTagFromBookmarksOnHatena(
        const char *userName,   /* (I) ユーザ名   */
        const char *password,   /* (I) パスワード */
        const char *oldTag,     /* (I) 古いタグ   */
        const char *newTag      /* (I) 新しいタグ */
    )
{
    BOOL    ret = FALSE;
    char    *cookie;
    char    *s;
    char    _oldTag[BUFSIZ];
    char    _newTag[BUFSIZ];

    if ( !oldTag || !(*oldTag) || !newTag || !(*newTag) )
        return ( ret );

    s = sjis2utf(oldTag);
    if ( !s )
        return ( ret );
    strcpy( _oldTag, encodeURL(s) );

    s = sjis2utf(newTag);
    if ( !s )
        return ( ret );
    strcpy( _newTag, encodeURL(s) );

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( ret );
    memset( cookie,  0x00, MAX_COOKIE_LEN );

    /* はてなに login */
    ret = loginHatenaBookmark( userName, password, cookie );
    if ( ret ) {
        char    *request;
        char    *response;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_CONTENT_SIZE * 4;

        ret = FALSE;

        request  = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request ) {
            free( cookie );
            return ( ret );
        }
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            free( cookie );
            return ( ret );
        }
        memset( request, 0x00, MAX_CONTENT_SIZE );

#ifdef  BEFORE_20081125
        /* http://b.hatena.ne.jp/ユーザ名/古いタグ/?mode=edit を取得 */
        sprintf( url, "http://b.hatena.ne.jp/%s/%s/?mode=edit",
                 userName, _oldTag );
#else
        /* http://b.hatena.ne.jp/ユーザ名/tag?tag=古いタグ を取得 */
        sprintf( url, "http://b.hatena.ne.jp/%s/tag?tag=%s",
                 userName, _oldTag );
#endif
        setUpReceiveBuffer( response, sz );
        httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
                                  NULL, NULL );

        if ( *response ) {
            char    rkm[MAX_KEYLENGTH];

            /* rkm の値を取得 */
            getRkm( rkm, response );

#ifdef  BEFORE_20081125
            /* 一括置換を実行(http://b.hatena.ne.jp/ユーザ名/タグ/ へ POST) */
            sprintf( url, "http://b.hatena.ne.jp/%s/%s/", userName, _oldTag );
            setTargetURL( url );
            sprintf( request,
                     "mode=editenter&"
                     "rkm=%s&"
                     "oldtag=%s&"
                     "newtag=%s",
                     encodeURL(rkm), _oldTag, _newTag );
#else
            /* 一括置換を実行                                         */
            /*      (http://b.hatena.ne.jp/ユーザ名/tag.edit へ POST) */
            sprintf( url, "http://b.hatena.ne.jp/%s/tag.edit", userName );
            setTargetURL( url );
            sprintf( request,
                     "rks=%s&"
                     "tag=%s&"
                     "newtag=%s",
                     encodeURL(rkm), _oldTag, _newTag );
#endif
            setUpReceiveBuffer( response, sz );
            httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                                 "application/x-www-form-urlencoded",
                                 request, response, cookie,
                                 NULL, NULL );

            if ( *response ) {
                char    *p;

#ifdef  BEFORE_20081125
                p = strstr( response, "name=\"oldtag\" value=\"" );
#else
                p = strstr( response, "name=\"tag\" value=\"" );
#endif
                if ( p ) {
#ifdef  BEFORE_20081125
                    p += 21;
#else
                    p += 18;
#endif
                    if ( !strncmp( p, _newTag, strlen(_newTag) ) &&
                         (p[strlen(_newTag)] == '"' )               )
                        ret = TRUE;
                }
            }
        }

        free( response );
        free( request );
    }

    free( cookie );

    return ( ret );
}


/* ブックマークに付けたタグの削除
                    (REST API, はてなに login 済みの状態である必要あり) */
BOOL
removeTagFromBookmarksOnHatena(
        const char *userName,   /* (I) ユーザ名       */
        const char *password,   /* (I) パスワード     */
        const char *tag         /* (I) 削除対象のタグ */
    )
{
    BOOL    ret = FALSE;
    char    *cookie;
    char    *s;
    char    _tag[BUFSIZ];

    if ( !tag || !(*tag) )
        return ( ret );

    s = sjis2utf(tag);
    if ( !s )
        return ( ret );
    strcpy( _tag, encodeURL(s) );

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( ret );
    memset( cookie,  0x00, MAX_COOKIE_LEN );

    /* はてなに login */
    ret = loginHatenaBookmark( userName, password, cookie );
    if ( ret ) {
        char    *request;
        char    *response;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_CONTENT_SIZE * 4;

        ret = FALSE;
        request  = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request )  {
            free( cookie );
            return ( ret );
        }
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            free( cookie );
            return ( ret );
        }
        memset( request, 0x00, MAX_CONTENT_SIZE );

#ifdef  BEFORE_20081125
        /* http://b.hatena.ne.jp/ユーザ名/タグ/?mode=edit を取得 */
        sprintf( url, "http://b.hatena.ne.jp/%s/%s/?mode=edit",
                 userName, _tag );
#else
        /* http://b.hatena.ne.jp/ユーザ名/tag?tag=タグ を取得 */
        sprintf( url, "http://b.hatena.ne.jp/%s/tag?tag=%s",
                 userName, _tag );
#endif
        setUpReceiveBuffer( response, sz );
        httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
                                  NULL, NULL );

        if ( *response ) {
            char    rkm[MAX_KEYLENGTH];

            /* rkm の値を取得 */
            getRkm( rkm, response );

#ifdef  BEFORE_20081125
            /* 削除を実行 (http://b.hatena.ne.jp/ユーザ名/タグ/ へ POST) */
            sprintf( url, "http://b.hatena.ne.jp/%s/%s/", userName, _tag );
            setTargetURL( url );
            sprintf( request,
                     "mode=deleteenter&"
                     "rkm=%s&"
                     "oldtag=%s",
                     encodeURL(rkm), _tag );
#else
            /* 削除を実行                                               */
            /*      (http://b.hatena.ne.jp/ユーザ名/tag.delete へ POST) */
            sprintf( url, "http://b.hatena.ne.jp/%s/tag.delete", userName );
            setTargetURL( url );
            sprintf( request,
                     "rks=%s&"
                     "tag=%s",
                     encodeURL(rkm), _tag );
#endif
            setUpReceiveBuffer( response, sz );
            httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                                 "application/x-www-form-urlencoded",
                                 request, response, cookie,
                                 NULL, NULL );
            if ( *response ) {
                char    target[BUFSIZ];

                sprintf( target, "/rss?tag=%s\"", _tag );
                if ( strstr( response, target ) )
                    ret = TRUE;
            }
        }

        free( response );
        free( request );
    }

    free( cookie );

    return ( ret );
}


/*
 *  追加機能
 */

/* 総ブックマーク数の取得 (FeedURI への GET で得た XMLを解析することで実現) */

long
getNumberOfBookmarksOnHatena(
        const char *userName,   /* (I) ユーザ名   */
        const char *password    /* (I) パスワード */
    )
{
    long    num = 0;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( userName, password, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/feed", HATENA_B_ENDPOINT_URL );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     wsse );

    if ( response[0] != NUL ) {
        /* <openSearch:totalResults>1581</openSearch:totalResults> */
        char    *p = strstr( response, "<openSearch:totalResults>" );
        if ( p ) {
            p += 25;
            while ( *p == '0' )
                p++;
            if ( (*p >= '1') && (*p <= '9') )
                num = atol( p );
        }
    }

    free( response );

    return ( num );
}



/*
 *  はてな(ブックマーク)に login
 */

BOOL
loginHatenaBookmark(
    const char *username,   // (I) はてなID (もしくはメールアドレス)
    const char *password,   // (I) パスワード
    char       *cookie )    // (O) クッキー
{
    int     ret = FALSE, r;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !cookie )
         return ( ret );

    if ( !username )
        username = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );

    strcpy( url,
            "https://www.hatena.ne.jp/login?"
            "backurl=http%3A%2F%2Fb.hatena.ne.jp%2F" );
    setUpReceiveBuffer( response, sz );
    httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
                              NULL, NULL );

    strcpy( url, "https://www.hatena.ne.jp/login" );
    setTargetURL( url );
    sprintf( request,
             "name=%s&"
             "password=%s&"
             "persistent=1&"
             "location=http://b.hatena.ne.jp/",
             username, password );
    setUpReceiveBuffer( response, sz );
    r = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                             "application/x-www-form-urlencoded",
                             request, response, cookie,
                             NULL, NULL );
    if ( r == -1 )
        ret = FALSE;        /* サーバとの通信失敗 */
    else if ( *response ) {
        if ( strstr(response, sjis2utf("パスワードが認証されました")) ||
             strstr(response, sjis2utf("ログイン中です"))                )
            ret = TRUE;     /* ログイン成功 */
        else {
            ret = FALSE;    /* ログイン失敗 */
            if ( strstr(response, "<meta http-equiv=\"R") ) {
                setUpReceiveBuffer( response, sz );
                http_getEx( "http://b.hatena.ne.jp/", response, cookie );
                if ( *response ) {
                    if ( strstr(response, sjis2utf("ログアウト")) )
                        ret = TRUE;     /* ログイン成功 */
                }
            }
        }
    }

    free( response );
    free( request  );

    return ( ret );
}


/* 新規ブックマークの投稿 + コレクションへの追加 (form への POST) */
BOOL
postBookmarkWithCollectionOnHatena(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        const char *href,   /* (I) ブックマーク対象 Web ページ URL       */
        char       *title,  /* (O) 題名                                  */
        const char *summary,/* (I) コメント                              */
        const char *tags,   /* (I) tag (空白文字で区切って複数tag指定可) */
        char       *entryID /* (O) edit用エントリID                      */
    )
{
    BOOL    ret = FALSE;
    char    *cookie;
    char    extended[MAX_DESCRIPTION_LEN * 2];

    if ( !href || !(*href) || !entryID )
        return ( ret );

    entryID[0] = NUL;
    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( ret );
    memset( cookie,   0x00, MAX_COOKIE_LEN );
    memset( extended, 0x00, MAX_DESCRIPTION_LEN * 2 );
    makeExtended( tags, summary, extended );

    /* はてなに login */
    ret = loginHatenaBookmark( usrname, passwd, cookie );
    if ( ret ) {
        char    *request;
        char    *response;
        char    *p;
        char    url[BUFSIZ * 2];
        char    asin[32];
        size_t  sz = MAX_CONTENT_SIZE * 4;

        ret = FALSE;

        request  = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request ) {
            free( cookie );
            return ( ret );
        }
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            free( cookie );
            return ( ret );
        }
        memset( request, 0x00, MAX_CONTENT_SIZE );

        /* asin の値を取得 */
        getASIN( href, asin );

        /* ブックマーク投稿フォームを取得 */
        p = sjis2utf(title);
#ifdef  BEFORE_20081125
        sprintf( url,
                 "http://b.hatena.ne.jp/add?"
                 "mode=confirm&"
                 "is_bm=1&"
                 "title=%s&",
                 encodeURL(p ? p : title) );
        sprintf( url + strlen(url),
                 "url=%s",
                 encodeURL(href) );
#else
        sprintf( url,
                 "http://b.hatena.ne.jp/%s/add.confirm?"
                 "url=%s",
                 usrname,
                 encodeURL(href) );
#endif
        setUpReceiveBuffer( response, sz );
        httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
                                  NULL, NULL );
        if ( *response ) {
            char    rkm[MAX_KEYLENGTH];
            char    _href[BUFSIZ * 2];

            /* rkm の値を取得 */
            getRkm( rkm, response );
            getEid( entryID, response );
            getHref( _href, response );
            getTitleText( title, response );

            /* ブックマークを投稿 */
            memset( response, 0x00, MAX_CONTENT_SIZE * 4 );
#ifdef  BEFORE_20081125
            strcpy( url, "http://b.hatena.ne.jp/add" );
            setTargetURL( url );
            sprintf( request,
                     "mode=enter&" );
            if ( entryID[0] )
                sprintf( request + strlen(request),
                         "eid=%s&",
                         entryID );
            else
                sprintf( request + strlen(request),
                         "eid=&" );
            sprintf( request + strlen(request),
                     "url=%s&",
                     encodeURL( _href[0] ? _href : href ) );
            sprintf( request + strlen(request),
                     "rkm=%s&"
                     "is_bm=1&"
                     "force_url=1&"
                     "asin=%s&", 
                     encodeURL(rkm),
                     asin );
            sprintf( request + strlen(request),
                     "title=%s&",
                     encodeURL(title) ); // UTF-8
            if ( *extended ) {
                p = sjis2utf(extended);
                sprintf( request + strlen(request),
                         "comment=%s&",
                         encodeURL(p ? p : extended) );
            }
            else
                sprintf( request + strlen(request),
                         "comment=&" );
            sprintf( request + strlen(request),
                     "addasin=1&"
                     "commit=%s",
                     encodeURL(sjis2utf("追加する")) );
#else
            sprintf( url, "http://b.hatena.ne.jp/%s/add.edit", usrname );
            setTargetURL( url );
            sprintf( request,
                     "rks=%s&", 
                     encodeURL(rkm) );
            sprintf( request + strlen(request),
                     "url=%s&", 
                     encodeURL( _href[0] ? _href : href ) );
            if ( *extended ) {
                p = sjis2utf(extended);
                sprintf( request + strlen(request),
                         "comment=%s&",
                         encodeURL(p ? p : extended) );
            }
            else
                sprintf( request + strlen(request),
                         "comment=&" );
            sprintf( request + strlen(request),
                     "add_asin=1&"
                     "asin=%s&", 
                     asin );
#endif
            setUpReceiveBuffer( response, sz );
            httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                                 "application/x-www-form-urlencoded",
                                 request, response, cookie,
                                 NULL, NULL );

            if ( *response ) {
                if ( entryID[0] == NUL )
                    getEid( entryID, response );
                ret = TRUE;
            }
        }

        free( response );
        free( request );
    }

    free( cookie );

    return ( ret );
}


/*
 *  はてなブックマークから RSS/Atomフィード形式で export したファイルから
 *  エントリ情報を読み取る
 */

#define HB_FEED_TYPE_UNKNOWN    0
#define HB_FEED_TYPE_RSS        1
#define HB_FEED_TYPE_ATOM       2

long
getPostsFromHatenaFeed(
    FILE            *fp,        /* (I) (RSS/Atomフィード)ファイルストリーム */
    HATENA_BOOKMARK **posts,    /* (O) 取得したブックマーク         */
    long            *numOfPosts /* (O) 取得したブックマークの数     */
  )
{
    size_t      fileSize = 0;
    long        num      = 0;
    char        buf[MAX_CONTENT_SIZE];
    char        *p, *q, *xmlSrc;
    int         feedType = HB_FEED_TYPE_UNKNOWN;
    struct stat s;

    if ( numOfPosts )
        *numOfPosts = 0;
    if ( !posts || !fp || !numOfPosts )
        return ( num );

    if ( !fstat( fileno( fp ), &s ) )
        fileSize = s.st_size;
    if ( fileSize == 0 )
        return ( num );

    xmlSrc = (char *)malloc( fileSize + BUFSIZ );
    if ( !xmlSrc )
        return ( num );

    q = xmlSrc;
    while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
        if ( feedType == HB_FEED_TYPE_UNKNOWN ) {
            if ( strstr( p, "<feed version=\"0.3\"" ) )
                feedType = HB_FEED_TYPE_ATOM;
            else if ( strstr( p, "<rdf:RDF " ) )
                feedType = HB_FEED_TYPE_RSS;
        }
        strcpy( q, p );
        q += strlen( p );

        if ( feedType == HB_FEED_TYPE_ATOM ) {
            if ( strstr( p, "<entry>" ) )
                num++;
        }
        else if ( feedType == HB_FEED_TYPE_RSS ) {
            if ( strstr( p, "<item rdf:about=\"" ) )
                num++;
        }
    }

    if ( (num > 0) && (feedType != HB_FEED_TYPE_UNKNOWN) ) {
        *numOfPosts = num;
        *posts = (HATENA_BOOKMARK *)malloc(sizeof ( HATENA_BOOKMARK ) * num);
        num = 0;
        if ( *posts ) {
            if ( feedType == HB_FEED_TYPE_ATOM )
                num = getPosts( xmlSrc, numOfPosts, *posts );
            else
                num = getPostsFromRSS( xmlSrc, numOfPosts, *posts );
        }
    }
    free( xmlSrc );

    *numOfPosts = num;
    return ( num );
}

void
freePostsFromHatenaFeed( HATENA_BOOKMARK *posts )
{
    if ( posts )
        free( posts );
}


/* タグ一覧の取得 */
int
getListOfTagsOnHatena(
        const char *username,   /* (I) ユーザ名         */
        const char *password,   /* (I) パスワード       */
        long       *numOfTags,  /* (I) 取得するタグの数 */
                                /* (O) 取得したタグの数 */
        TagList    *lp          /* (O) タグ一覧         */
    )
{
    int     num = 0;
    char    *cookie;
    int     ret;

    if ( !numOfTags || (*numOfTags <= 0) || !lp )
        return ( num );

    if ( !username )
        username = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( num );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    /* はてなに login */
    ret = loginHatenaBookmark( username, password, cookie );
    if ( ret ) {
        char    url[MAX_URLLENGTH];
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 16;

        response = (char *)malloc( sz );
        if ( !response ) {
            free( cookie );
            return ( num );
        }

#ifdef  BEFORE_20081125
        sprintf( url, "http://b.hatena.ne.jp/%s/tag", username );
#else
        /* リニューアル後の「はてなブックマーク」では「タグの表示をしない」 */
        /* 設定にしていると、タグ一覧を取得する術がない                     */
        sprintf( url, "http://b.hatena.ne.jp/%s/tag", username );// [機能せず]

        strcpy( strchr( cookie, '\r' ),
                "; config_tab=config_table_design_button\r\n" );
#endif
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );

        if ( *response ) {
            char    *p, *q, *r;

            p = strstr( response, "<ul class=\"taglist\"" );
            if ( p ) {
                p += 19;

                do {
                    q = strstr( p, "\" class=\"tag-" );
                    if ( !q )
                        break;
                    q += 12;

                    r = strchr( q, '>' );
                    if ( !r )
                        break;

                    p = r + 1;
                    q = strstr( p, "</a>" );
                    if ( !q )
                        break;

                    strncpy( lp[num].tag, p, q - p );
                    lp[num].tag[q - p] = NUL;

                    num++;
                } while ( num < *numOfTags );
            }
        }

        free( response );
    }

    *numOfTags = num;
    free( cookie );

    return ( num );
}
