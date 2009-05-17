/*
 *  hatenaApi.h
 *
 * History:
 * $Log: /comm/xmlRPC/hatenaApi.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 22    08/11/28 10:51 Tsujimura543
 * loginHatenaBookmark() を DLL 外からも参照できるようにした
 * 
 * 21    08/05/15 22:26 Tsujimura543
 * HATENA_BOOKMARK 構造体の href のサイズを2倍にした
 * 
 * 20    07/01/29 21:24 Tsujimura543
 * getListOfTagsOnHatena() を追加
 * 
 * 19    06/11/15 18:37 Tsujimura543
 * getPostsFromHatenaFeed() の第1引数を「ファイル名」から「FILE *」に変更
 * 
 * 18    06/11/15 18:15 Tsujimura543
 * コメント(getPostsFromHatenaFeed() の引数の説明)を修正
 * 
 * 17    06/11/15 18:12 Tsujimura543
 * getPostsFromHatenaFeed() と freePostsFromHatenaFeed() を追加
 * 
 * 16    06/10/12 19:20 Tsujimura543
 * XML_STATEMENT の改行コードを \n から \r\n に変更
 * 
 * 15    06/04/06 22:13 Tsujimura543
 * postBookmarkWithCollectionOnHatena() を追加
 * 
 * 14    05/09/26 16:40 Tsujimura543
 * HATENA_BOOKMARK に「ブックマーク登録日時」のフィールドを追加
 * 
 * 13    05/08/08 17:57 Tsujimura543
 * loginHatenaBookmark() を追加
 * 
 * 12    05/07/21 16:04 Tsujimura543
 * コメントを修正 (説明を追加)
 * 
 * 11    05/07/21 15:47 Tsujimura543
 * renameTagFromBookmarksOnHatena(), removeTagFromBookmarksOnHatena(),
 * getNumberOfBookmarksOnHatena() を追加
 * 
 * 10    05/07/20 20:35 Tsujimura543
 * getBookmarkOnHatenaWithURI() を追加
 * 
 * 9     05/07/20 20:06 Tsujimura543
 * getRecentPostsOnHatenaUserWith{Tag,Word,Date}() を追加
 * 
 * 8     05/07/20 19:19 Tsujimura543
 * getRecentPostsOnHatenaUser() を追加
 * 
 * 7     05/06/09 22:30 Tsujimura543
 * postBookmarkOnHatena() に引数を1個追加した
 * 
 * 6     05/05/31 19:33 Tsujimura543
 * getBookmarkOnHatena() に引数(title[題名])を追加
 * 
 * 5     05/05/30 18:36 Tsujimura543
 * はてなブックマーク API の各関数の引数(ユーザ名とパスワード)を追加
 * 
 * 4     05/05/30 18:31 Tsujimura543
 * 「はてなブックマーク」関連の定義、宣言を追加
 * 
 * 3     04/11/01 21:01 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 2     04/07/07 11:43 Tsujimura543
 */

#ifndef __HATENA_API_H__
#define __HATENA_API_H__

/* charset (code set) */
#define CSET_SHIFTJIS   1
#define CSET_ISO2022JP  2
#define CSET_EUCJP      3
#define CSET_UTF8       4

/* はてなダイアリーキーワード */

#define HATENA_API_URL  "http://d.hatena.ne.jp/images/keyword/keywordlist"
#define CGINAME       "http://www.na.rim.or.jp/~tsupo/program/api/keyword.cgi"

#ifndef XML_STATEMENT
#define XML_STATEMENT   "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
#endif
#define HATENA_ENDPOINT_URL "http://d.hatena.ne.jp/xmlrpc"

char    *decodeString( char *src );
char    *encodeString( const char *src, char *dst );

static void searchKeyword( FILE *fp, FILE *gp, const char *word, int mode );
static void searchKeywordEx( FILE *fp, char *dst, const char *src, int mode );


/* はてなブックマーク */
#include "delicious.h"

#define HATENA_B_ENDPOINT_URL "http://b.hatena.ne.jp/atom"

/*
 *  新規ブックマークの投稿 (PostURI への POST)
 *      POST /atom/post
 *      <entry xmlns="http://purl.org/atom/ns#">
 *          <title>dummy</title>
 *          <link rel="related" type="text/html" href="http://www.example.com/" />
 *          <summary type="text/plain">サンプルコメントです</summary>
 *      </entry>
 *
 *      tag を付加する場合は、以下のようにする
 *      <entry xmlns="http://purl.org/atom/ns#">
 *          <title>dummy</title>
 *          <link rel="related" type="text/html" href="http://www.example.com/" />
 *          <summary type="text/plain">[tag1][tag2]…[tagN]サンプルコメントです</summary>
 *      </entry>
 *
 *      注: PostURI による投稿時はブックマークのタイトルを編集することは
 *          できません。タイトルはlink要素に指定したURLから自動取得され
 *          設定されます。
 */

BOOL
postBookmarkOnHatena(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        const char *href,   /* (I) ブックマーク対象 Web ページ URL       */
        char       *title,  /* (O) 題名                                  */
        const char *summary,/* (I) コメント                              */
        const char *tags,   /* (I) tag (空白文字で区切って複数tag指定可) */
        char       *entryID /* (O) edit用エントリID                      */
    );

/*
 *  投稿したブックマークの参照 (EditURI への GET)
 *      GET /atom/edit/XXXX
 */

BOOL
getBookmarkOnHatena(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        char       *href,   /* (O) ブックマーク対象 Web ページ URL       */
        char       *title,  /* (O) 題名                                  */
        char       *summary,/* (O) コメント                              */
        char       *tags,   /* (O) tag (空白文字で区切って複数tag指定可) */
        const char *entryID /* (I) edit用エントリID                      */
    );

BOOL
getBookmarkOnHatenaWithURI(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        const char *href,   /* (I) ブックマーク対象 Web ページ URL       */
        char       *title,  /* (O) 題名                                  */
        char       *summary,/* (O) コメント                              */
        char       *tags,   /* (O) tag (空白文字で区切って複数tag指定可) */
        char       *entryID /* (O) edit用エントリID                      */
    );

/*
 *  投稿したブックマークのタイトル、コメントの変更 (EditURI への PUT)
 *      PUT /atom/edit/XXXX
 *      <entry xmlns="http://purl.org/atom/ns#">
 *          <title>Sample Page</title>
 *          <summary type="text/plain">サンプルです。</summary>
 *      </entry>
 *
 *      tag を付加する場合は、以下のようにする
 *      <entry xmlns="http://purl.org/atom/ns#">
 *          <title>Sample Page</title>
 *          <summary type="text/plain">[tag1][tag2]…[tagN]サンプルです。</summary>
 *      </entry>
 */

BOOL
editBookmarkOnHatena(
        const char *usrname,/* (I) ユーザ名                              */
        const char *passwd, /* (I) パスワード                            */
        const char *href,   /* (I) ブックマーク対象 Web ページ URL       */
        const char *title,  /* (I) 題名                                  */
        const char *summary,/* (I) コメント                              */
        const char *tags,   /* (I) tag (空白文字で区切って複数tag指定可) */
        const char *entryID /* (I) edit用エントリID                      */
    );

/*
 *  投稿したブックマークの削除 (EditURI への DELETE)
 *      DELETE /atom/edit/XXXX
 */

BOOL
deleteBookmarkOnHatena(
        const char *usrname,/* (I) ユーザ名         */
        const char *passwd, /* (I) パスワード       */
        const char *entryID /* (I) edit用エントリID */
    );

/*
 *  最近投稿したブックマークの一覧の取得 (FeedURI への GET)
 *      GET /atom/feed
 */

typedef struct entryOnHatena    {
    char href[MAX_URLLENGTH * 2];       /* ブックマーク対象 Web ページ URL  */
    char title[MAX_DESCRIPTION_LEN];    /* 題名                             */
    char summary[MAX_DESCRIPTION_LEN];  /* コメント                         */
    char tags[MAX_DESCRIPTION_LEN];     /* tag (空白区切りで複数個指定可能) */
    char entryID[HASH_LENGTH + 1];      /* edit用エントリID                 */
    int  yyyy;                          /* ブックマーク登録日時  年         */
    int  mm;                            /* ブックマーク登録日時  月         */
    int  dd;                            /* ブックマーク登録日時  日         */
    int  HH;                            /* ブックマーク登録日時  時         */
    int  MM;                            /* ブックマーク登録日時  分         */
    int  SS;                            /* ブックマーク登録日時  秒         */
}   HATENA_BOOKMARK;

long
getRecentPostsOnHatena(
        const char      *usrname,       /* (I) ユーザ名                 */
        const char      *passwd,        /* (I) パスワード               */
        long            *numOfPosts,    /* (I) 取得するブックマークの数 */
                                        /* (O) 取得したブックマークの数 */
        HATENA_BOOKMARK *posts          /* (O) 取得したブックマーク     */
    );


/*
 *  指定ユーザの最近投稿したブックマークの一覧の取得 (REST API)
 */

long
getRecentPostsOnHatenaUser(
        const char      *username,      /* (I) 取得対象ユーザ名(はてなID)   */
        long            offset,         /* (I) 取得開始ブックマーク位置     */
        long            *numOfPosts,    /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        HATENA_BOOKMARK *posts,         /* (O) 取得したブックマーク         */
        BOOL            *more           /* (O) 取得可能残存ブックマーク有無 */
    );

long
getRecentPostsOnHatenaUserWithTag(
        const char      *username,      /* (I) 取得対象ユーザ名(はてなID)   */
        const char      *tag,           /* (I) 検索条件 (tag)               */
        long            offset,         /* (I) 取得開始ブックマーク位置     */
        long            *numOfPosts,    /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        HATENA_BOOKMARK *posts,         /* (O) 取得したブックマーク         */
        BOOL            *more           /* (O) 取得可能残存ブックマーク有無 */
    );

long
getRecentPostsOnHatenaUserWithWord(
        const char      *username,      /* (I) 取得対象ユーザ名(はてなID)   */
        const char      *word,          /* (I) 検索条件 (キーワード)        */
        long            offset,         /* (I) 取得開始ブックマーク位置     */
        long            *numOfPosts,    /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        HATENA_BOOKMARK *posts,         /* (O) 取得したブックマーク         */
        BOOL            *more           /* (O) 取得可能残存ブックマーク有無 */
    );

long
getRecentPostsOnHatenaUserWithDate(
        const char      *username,      /* (I) 取得対象ユーザ名(はてなID)   */
        const char      *date,          /* (I) 検索条件 (日付,yyyymmdd形式) */
        long            offset,         /* (I) 取得開始ブックマーク位置     */
        long            *numOfPosts,    /* (I) 取得するブックマークの数     */
                                        /* (O) 取得したブックマークの数     */
        HATENA_BOOKMARK *posts,         /* (O) 取得したブックマーク         */
        BOOL            *more           /* (O) 取得可能残存ブックマーク有無 */
    );


/* ブックマークに付けたタグの一括置換
                    (REST API, はてなに login 済みの状態である必要あり) */
BOOL
renameTagFromBookmarksOnHatena(
        const char *userName,   /* (I) ユーザ名   */
        const char *password,   /* (I) パスワード */
        const char *oldTag,     /* (I) 古いタグ   */
        const char *newTag      /* (I) 新しいタグ */
    );          /* 本関数内で「はてな」への login 処理も実行する */


/* ブックマークに付けたタグの削除
                    (REST API, はてなに login 済みの状態である必要あり) */
BOOL
removeTagFromBookmarksOnHatena(
        const char *userName,   /* (I) ユーザ名       */
        const char *password,   /* (I) パスワード     */
        const char *tag         /* (I) 削除対象のタグ */
    );          /* 本関数内で「はてな」への login 処理も実行する */

/*
 *  追加機能
 */

/* 総ブックマーク数の取得 (FeedURI への GET で得たXMLを解析することで実現) */

long
getNumberOfBookmarksOnHatena(
        const char *userName,   /* (I) ユーザ名   */
        const char *password    /* (I) パスワード */
    );

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
    );


/* はてなブックマークから RSS/Atomフィード形式で export したファイルから */
/* エントリ情報を読み取る                                                */
long
getPostsFromHatenaFeed(
    FILE            *fp,        /* (I) (RSS/Atomフィード)ファイルストリーム */
    HATENA_BOOKMARK **posts,    /* (O) 取得したブックマーク                 */
    long            *numOfPosts /* (O) 取得したブックマークの数             */
  );

/* getPostsFromHatenaFeed() で取得したブックマーク情報格納領域の解放 */
void
freePostsFromHatenaFeed( HATENA_BOOKMARK *posts );


/* タグ一覧の取得 */
#ifndef MAX_TAG_LENGTH
typedef struct tagList  {
#define MAX_TAG_LENGTH  512             /* タグ最大長 (暫定値) */
    char    tag[MAX_TAG_LENGTH];        /* tag (分類)          */
}   TagList;
#endif  /* MAX_TAG_LENGTH */

int
getListOfTagsOnHatena(
        const char *usrname,    /* (I) ユーザ名         */
        const char *passwd,     /* (I) パスワード       */
        long       *numOfTags,  /* (I) 取得するタグの数 */
                                /* (O) 取得したタグの数 */
        TagList    *lp          /* (O) タグ一覧         */
    );

//#ifdef  XMLRPC_EXPORTS
/*  はてな(ブックマーク)に login */
BOOL
loginHatenaBookmark(
    const char *username,   // (I) はてなID (もしくはメールアドレス)
    const char *password,   // (I) パスワード
    char       *cookie );   // (O) クッキー
//#endif  /* XMLRPC_EXPORTS */

#endif  /* __HATENA_API_H__ */
