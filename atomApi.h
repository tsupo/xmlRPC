/*
 *  atom API
 *
 * History:
 * $Log: /comm/xmlRPC/atomApi.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 14    09/03/16 15:04 Tsujimura543
 * MAX_CATEGORIES の定義を xmlRPC.h へ移した
 * 
 * 13    06/01/23 14:38 Tsujimura543
 * listPostsOnAtomAPI() の注釈(6)を追加
 * 
 * 12    05/08/17 15:09 Tsujimura543
 * postEntryOnAtomAPI() と editEntryOnAtomAPI() に引数を追加し、
 * 下書き投稿可能とした (対象は blogger.com のみ)
 * 
 * 11    05/07/01 11:16 Tsujimura543
 * (本ファイル末尾の)コメントを現状に合わせて修正
 * 
 * 10    05/06/28 21:58 Tsujimura543
 * editEntryOnAtomAPI() を追加
 * 
 * 9     04/10/15 11:55 Tsujimura543
 * コメントの修正
 * 
 * 8     04/10/15 11:52 Tsujimura543
 * getEndpointURLbyAutoDiscoveryOnAtomAPI() を追加
 * 
 * 7     04/08/13 14:28 Tsujimura543
 * getRecentPostTitlesOnAtomAPI() を追加
 * 
 * 6     04/08/12 21:17 Tsujimura543
 * getBlogIDsOnAtomAPI() を追加
 * 
 * 5     04/07/16 19:19 Tsujimura543
 * postEntryOnAtomAPI() に引数を追加し、概要を指定できるようにした
 * 
 * 4     04/07/16 13:57 Tsujimura543
 * Atom API 関連、全面見直し。XML-RPC API 関連関数との整合を図る。
 * 
 * 3     04/07/09 20:30 Tsujimura543
 * livedoor Blog の Atom API 対応
 * 
 * 2     04/07/07 11:43 Tsujimura543
 * RCS による版数管理から VSS による版数管理に移行
 */

#ifndef __ATOM_API_H__
#define __ATOM_API_H__

#include "xmlRPC.h"

#define MAX_TYPELENGTH  80

/*
 *  Atom authentication uses WSSE, and is represented as an "X-WSSE" HTTP
 *  header.
 *      X-WSSE: UsernameToken Username="name", PasswordDigest="digest", 
 *      Created="timestamp", Nonce="nonce"
 *          Username
 *              The username that the user enters (the TypePad username).
 *          Nonce
 *              A secure token generated anew for each HTTP request.
 *          Created
 *              The ISO-8601 timestamp marking when Nonce was created.
 *          PasswordDigest
 *              A SHA-1 digest of the Nonce, Created timestamp, and the
 *              password that the user supplies, base64-encoded. In other
 *              words, this should be calculated as:
 *                  base64(sha1(Nonce . Created . Password))
 */

/* PasswordDigest の生成 */
char    *makePasswordDigest(
            const char *nonce,
            const char *created,
            const char *password,
            int        blogKind );

char    *makeCreated( time_t t );
char    *makeNonce( const char *preNonce, int blogKind );

/* WSSE の生成 */
char    *makeWSSE( const char *username, const char *password, char *buffer,
                   int blogKind );


/* Atom API エンドポイント URL 情報 */
typedef struct atomApiUrlInfo   {
    char    urlType[MAX_TYPELENGTH];    /* URL の種類 */
    char    url[MAX_URLLENGTH];         /* URL        */
    char    mimeType[MAX_TYPELENGTH];   /* MIME 種別  */
    char    title[MAX_LOGICALLINELEN];  /* 名前       */
}   ATOM_URL_INFO, *ATOM_URL_INFO_t;

/* category 情報 */
typedef struct categoryListInfoEx {
    long    numberOfCategories;         /* カテゴリの数 */
    char    categoryName[MAX_CATEGORIES][MAX_CATNAMELENGTH];
                                        /* カテゴリの名前 (漢字も OK) */
}   CATLISTINFEX, *CATLISTINFEX_t;


/*
 *  Atom API
 *    以下の Atom API 関連関数では、原則として文字コードは UTF-8 (もしくは
 *    US-ASCII)であることを前提にしている
 */

/* Listing the User's Weblogs
 * 指定件数分のURL情報の取得
 *    listWeblogsOnAtomAPI
 *      引数:
 *          char          *userName   (I) ユーザ名
 *          char          *password   (I) パスワード
 *          int           *numOfUrls  (I) 取得するURL情報数
 *                                    (O) 実際に取得したURL情報数
 *          ATOM_URL_INFO *urlInfo    (O) 取得したURL情報
 *      戻り値:
 *          0       取得失敗、送信失敗、その他のエラー発生
 *          1 以上  取得に成功したURL情報の数
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) *numOfUrls で指定した数の分だけ、URL情報を取得する
 *          (3) 実際に取得に成功したURL情報の数を *numOfUrls に設定する
 */
int
listWeblogsOnAtomAPI( const char      *username,
                      const char      *password,
                      long            *numOfUrls,
                      ATOM_URL_INFO_t urlInfo );


/* Listing the Posts in a Weblog
 * 指定件数分の記事情報の取得
 *    listPostsOnAtomAPI
 *      引数:
 *          char         *userName      (I) ユーザ名
 *          char         *password      (I) パスワード
 *          char         *blogID        (I) blog ID
 *          int          *numOfEntries  (I) 取得する記事情報数
 *                                      (O) 実際に取得した記事情報数
 *          CONTENTINFEX *contentInfo   (O) 取得した記事情報
 *          CATLISTINFEX *categoryInfo  (O) 取得したカテゴリ情報
 *      戻り値:
 *          0       記事が存在しない、取得失敗、送信失敗、その他のエラー発生
 *          1 以上  取得に成功したURL情報の数
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) *numOfEntries で指定した数の分だけ、最新の記事から過去方向に
 *              遡って記事情報を取得する
 *          (3) contentInfo と categoryInfo の配列の大きさは、共に、
 *              *numOfEntries で指定した値以上である必要がある
 *          (4) 実際に取得に成功した記事情報の数を *numOfEntries に設定する
 *          (5) Atom API ではカテゴリは「カテゴリ名」で取り扱う。「カテゴリ
 *              ID」という概念はないので注意(以下、他の Atom API 関連関数で
 *              も同様)
 *          (6) Bloggers.com の独自拡張として、convertLineBreaks(改行を自動的
 *              に<br />に変換するか否か)の値を取得できるようになっている。
 *              この値は本来、各記事ごとに独立に設定可能であるべきであるが、現
 *              状は、記事投稿時点の(管理画面での)設定値が無条件に適用される。
 *              本APIで取得できる convertLineBreaks の値は、本API実行時点の管
 *              理画面の設定値であり、各記事の投稿時点当時の管理画面の設定値で
 *              はないことに注意。
 *              なお、postEntryOnAtomAPI() や editEntryOnAtomAPI() では
 *              convertLineBreaks の値を制御できない [将来できるようになる?])
 *               → http://code.blogger.com/archives/atom-docs.html#extensions
 *              * MovableType/TypaPad, libedoor Blog も、Bloggers.com の拡張に
 *                準拠した模様
 */
int
listPostsOnAtomAPI( const char   *username,
                    const char   *password,
                    const char   *blogID,
                    int          *numOfEntries,
                    CONTENTINFEX *contentInfo,
                    CATLISTINFEX *categoryInfo );


/* Retrieving a list of categories
 * 指定blogで使用可能なカテゴリ一覧の取得
 *    listCategoriesOnAtomAPI
 *      引数:
 *          char       *userName         (I) ユーザ名
 *          char       *password         (I) パスワード
 *          char       *blogID           (I) blog ID
 *          long       *numOfCategories  (I) 取得するカテゴリ情報数
 *                                       (O) 実際に取得したカテゴリ情報数
 *          CATLISTINF *categories       (O) 取得したカテゴリ情報
 *      戻り値:
 *          0       カテゴリが存在しない、取得失敗、送信失敗、その他のエラー
 *                  発生
 *          1 以上  取得に成功したカテゴリ情報の数
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) *numOfCategoriesで指定した数の分だけ、カテゴリ情報を取得する
 *          (3) 実際に取得に成功したカテゴリ情報の数を *numOfCategories に設
 *              定する
 */
int
listCategoriesOnAtomAPI(
        const char   *username,
        const char   *password,
        const char   *blogID,
        long         *numOfCategories, /* カテゴリの数 */
        CATLISTINF_t categories        /* カテゴリ     */
    );


/* Posting an entry
 * 記事の投稿
 *    postEntryOnAtomAPI
 *      引数:
 *          char       *userName    (I) ユーザ名
 *          char       *password    (I) パスワード
 *          char       *blogID      (I) blog ID
 *          char       *title       (I) 題名
 *          char       *summary     (I) 概要
 *          char       *content     (I) 本文
 *          CATLISTINF *categories  (I) 設定するカテゴリ
 *          BOOL       publish      (I) 投稿状態 (FALSE: 下書き, TRUE: 公開)
 *                                      -- 現時点では、blogger.com でのみ有効
 *          char       *postID      (O) 投稿後の記事ID
 *      戻り値:
 *          TRUE    投稿成功
 *          FALSE   投稿失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 *          (2) 記事内容のサイズは SND_BUFFER_SIZE の値 (正確には 
 *              SND_BUFFER_SIZE から「http ヘッダのサイズ分」を引いた値)  を
 *              超えないこと。サーバによっては、あまり大きな記事を受け付ける
 *              ことができないことが予想されるので、概ね64KB未満であることが
 *              望ましい
 *          (3) 記事内容 に URL エンコードすべき文字が含まれる場合は、本関数
 *              内で URL エンコードを行なうので、あらかじめ URL エンコードし
 *              ておく必要はない。なお、URL エンコードを行なった結果、記事内
 *              容のサイズが SND_BUFFER_SIZE より大きくなってしまった場合は、
 *              投稿に失敗する
 *          (4) 概要を指定しても、blog ツールによっては無視される。
 *          (5) 記事の投稿に成功した場合、postID  の指示する領域に記事ID (文
 *              字列) を格納する
 *          (6) 常に「公開」状態で投稿される
 *          (7) TypePad 系では、rebuild を実行するまで、カテゴリ情報は反映さ
 *              れない(設定はされるが反映はされない)
 */
int
postEntryOnAtomAPI(
        const char         *username,
        const char         *password,
        const char         *blogID,
        const char         *title,          /* 題名           */
        const char         *summary,        /* 概要           */
        const char         *content,        /* 本文           */
        const CATLISTINFEX *categoryInfo,   /* カテゴリ       */
        BOOL               publish,         /* 投稿状態       */
        char               *postID          /* 投稿後の記事ID */
    );

/* Editing an entry
 * 記事の編集 (既存記事の上書き投稿)
 *    editEntryOnAtomAPI
 *      引数:
 *          char       *userName    (I) ユーザ名
 *          char       *password    (I) パスワード
 *          char       *blogID      (I) blog ID
 *          char       *title       (I) 題名
 *          char       *summary     (I) 概要
 *          char       *content     (I) 本文
 *          CATLISTINF *categories  (I) 設定するカテゴリ
 *          BOOL       publish      (I) 投稿状態 (FALSE: 下書き, TRUE: 公開)
 *                                      -- 現時点では、blogger.com でのみ有効
 *          char       *postID      (I) 編集対象の記事ID
 *      戻り値:
 *          TRUE    上書き投稿成功
 *          FALSE   上書き投稿失敗、送信失敗、その他のエラー発生
 */
int
editEntryOnAtomAPI(
        const char         *username,       // (I) ユーザID
        const char         *password,       // (I) パスワード
        const char         *blogID,         // (I) blog ID
        const char         *title,          // (I) 題名
        const char         *summary,        // (I) 概要
        const char         *content,        // (I) 本文
        const CATLISTINFEX *categoryInfo,   // (I) 設定するカテゴリ
        BOOL               publish,         // (I) 投稿状態
        const char         *postID          // (I) 編集対象の記事ID
    );

/* Retrieving a Post
 * 指定記事の取得
 *    getRecentPostOnAtomAPI
 *      引数:
 *          char         *userName      (I) ユーザ名
 *          char         *password      (I) パスワード
 *          char         *blogID        (I) blog ID
 *          char         *entryID       (I) 記事ID
 *          CONTENTINFEX *contentInfo   (O) 取得した記事情報
 *          CATLISTINFEX *categoryInfo  (O) 取得したカテゴリ情報
 *      戻り値:
 *          TRUE    取得成功
 *          FALSE   取得失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 */
BOOL
getRecentPostOnAtomAPI(
        const char   *username,
        const char   *password,
        const char   *blogID,
        const char   *entryID,
        CONTENTINFEX *contentInfo,  /* 記事情報     */
        CATLISTINFEX *categoryInfo  /* カテゴリ情報 */
    );


/* Deleting a Post
 * 指定記事の削除
 *    deletePostOnAtomAPI
 *      引数:
 *          char         *userName      (I) ユーザ名
 *          char         *password      (I) パスワード
 *          char         *blogID        (I) blog ID
 *          char         *entryID       (I) 記事ID
 *      戻り値:
 *          TRUE    削除成功
 *          FALSE   削除失敗、送信失敗、その他のエラー発生
 *      備考:
 *          (1) userName および password が NULL の場合、 setUserInfo() で設
 *              定したユーザ名、パスワードを使用する
 */
BOOL
deletePostOnAtomAPI( const char *username,
                     const char *password,
                     const char *blogID,
                     const char *entryID );

/*
 *  ユーティリティ関数群
 */

/*
 * blog ID の取得
 *    引数:   ユーザ名, パスワード, 取得した blog 情報格納場所
 *    戻り値: システム内に存在する blog の数
 *    備考:   getBlogIDs() の Atom API バージョン
 */
int
getBlogIDsOnAtomAPI(
        const char *userName,       // (I) ユーザ名
        const char *password,       // (I) パスワード
        int        *numberOfBlogs,  // (I/O) blog 情報数
        BLOGINF    *blogInfo );     // (O) blog 情報

/*
 * 指定件数分の記事情報の取得
 *    引数:   blog ID, ユーザ名, パスワード, 取得する記事情報数,
 *            取得した記事情報格納場所
 *    戻り値: 取得した記事情報数
 *    備考:   getRecentPostTitles() の Atom API バージョン
 */
int
getRecentPostTitlesOnAtomAPI(
        const char *blogID,         // (I) blog ID
        const char *userName,       // (I) ユーザ名
        const char *password,       // (I) パスワード
        int        *numberOfPosts,  // (I/O) 記事情報数
        POSTINF    *postinf         // (O) 記事情報
    );

/*
 * エンドポイントURLの取得
 *    引数:   トップページURL, 取得した blog ID の格納場所
 *    戻り値: 取得したエンドポイントURL
 *    備考:   getEndpointURLbyAutoDiscovery() の Atom API バージョン
 *            トップページの html head 部分に
 *               <link rel="alternate" type="application/atom+xml" ……
 *            という行があれば、当該行で指定されている Atom Feed ファイルを
 *            元に、エンドポイントURLを求める。
 *            当該行が存在しない場合は、トップページ直下に atom.xml という
 *            Atom Feed ファイルが存在するものと仮定し、atom.xml ファイル
 *            から、エンドポイントURLを求める。
 *            ただし、 Atom Feed ファイル中に
 *                <link rel="service.post" type="application/x.atom+xml" ……
 *            という行が存在しない場合は、エンドポイントURLの取得はできない。
 */
char    *
getEndpointURLbyAutoDiscoveryOnAtomAPI(
        const char *topPageURL, // (I) トップページ URL
        char       *blogID      // (O) blog ID
    );


/*
 * 課題・問題点:
 *   (1) Atom API を使って投稿する場合、「本文」と「概要」以外の要素、
 *       「追記」、「キーワード」の取り扱い方が決まっていない模様。
 *       したがって、「追記」や「キーワード」を使って投稿したい場合は、
 *       当面、XML-RPC API を使うこととする。
 *   (2) Atom API では「カテゴリ」の取り扱い方もまだ正式には決まってい
 *       ない。暫定的に TypePad での実装に従うことにする。(livedoor Blog
 *       も TypePad での実装案を採用している模様)
 *   (3) X-WSSE: に関して、TypaPad での実装と、(BASIC認証 + SSL 採用以前
 *       の) Blogger での実装が食い違っている(特に Nonce の生成方法、エン
 *       コード方法に違いがある)。TypePad 1.5 で、従来の TypePad の WSSE
 *       と livedoor Blog の WSSE (= BASIC認証 + SSL 採用以前の Blogger
 *       の WSSE)の両方式に対応したため、以後、本ライブラリでも、後者の
 *       WSSE で統一することにした(2005年6月現在)
 *   (4) ココログでの Atom API の実装は中途半端な状態である(記事の投稿、
 *       記事の削除、カテゴリ一覧の取得、記事の取得、記事の編集は一応、
 *       一通りできるが、サーバ側から返ってくる XML 文書が途中で尻切れ
 *       トンボになることがあるなど、問題が残っている。現在、サーバ側の
 *       対処待ち。
 *   (5) 本ライブラリは、主として、ココログと livedoor Blog で動作確認を
 *       行なっている。他の blog ツールでは動作未検証である。
 *   (6) Blogger は WSSE 認証をやめ、BASIC認証 + SSL を採用した。本ライ
 *       ブラリも2005年6月末に BASIC認証 + SSL による Atom API の実行に
 *       対応した。Blogger で動作確認済み。
 *   (7) 今後も新たな認証方法が採用される可能性があるため、適宜、本ライ
 *       ブラリのアップデートを行なう予定。
 */

#endif  /* __ATOM_API_H__ */
