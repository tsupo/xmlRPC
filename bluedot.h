/*
 *  bludot.h
 *
 * History:
 * $Log: /comm/xmlRPC/bluedot.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 2     07/01/29 20:11 Tsujimura543
 * getNumberOfTagsOnBlueDot() を追加
 * 
 * 1     06/10/06 21:56 Tsujimura543
 * 新規作成 (del.icio.us 互換 API)
 */

#ifndef __BLUE_DOT_H__
#define __BLUE_DOT_H__

/*
 *  Blue Dot: del.icio.us API
 */

/* 日付別投稿数の一覧の取得 */
long
getListOfDatesOnBlueDot(
        const char      *userName,      /* (I) ユーザ名       */
        const char      *password,      /* (I) パスワード     */
        char            *tag,           /* (I) タグ           */
        long            *numOfDates,    /* (I) 取得する情報数 */
                                        /* (O) 取得した情報数 */
        DELICIOUS_DATES *dates          /* (O) 取得した情報   */
    );

/* 使っているタグの一覧の取得 */
long
getListOfTagsOnBlueDot(
        const char     *userName,   /* (I) ユーザ名       */
        const char     *password,   /* (I) パスワード     */
        long           *numOfTags,  /* (I) 取得する情報数 */
                                    /* (O) 取得した情報数 */
        DELICIOUS_TAGS *tags        /* (O) 取得した情報   */
    );

/* 指定した日付に投稿したエントリの一覧の取得 */
long
getListOfPostsOnBlueDot(
        const char      *userName,  /* (I) ユーザ名                   */
        const char      *password,  /* (I) パスワード                 */
        const char      *tag,       /* (I) 検索条件 (タグ)            */
        const char      *dateTime,  /* (I) 検索条件 (投稿日時)        */
                                    /*       yyyy-mm-ddThh:mm:ssZ形式 */
        const char      *targetUrl, /* (I) 検索条件 (URL)             */
        long            *numOfPosts,/* (I) 取得する情報数             */
                                    /* (O) 取得した情報数             */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報               */
    );

/* 最近のエントリ一覧の取得 */
long
getRecentPostsOnBlueDot(
        const char      *userName,  /* (I) ユーザ名        */
        const char      *password,  /* (I) パスワード      */
        const char      *tag,       /* (I) 検索条件 (タグ) */
        long            *numOfPosts,/* (I) 取得する情報数  */
                                    /* (O) 取得した情報数  */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報    */
    );

/* 全エントリの取得 */
long
getAllPostsOnBlueDot(
        const char      *userName,  /* (I) ユーザ名        */
        const char      *password,  /* (I) パスワード      */
        const char      *tag,       /* (I) 検索条件 (タグ) */
        long            *numOfPosts,/* (I) 取得する情報数  */
                                    /* (O) 取得した情報数  */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報    */
    );

/* 最終更新日時の取得 */
long
getLastUpdateOnBlueDot(
        const char *userName,   /* (I) ユーザ名     */
        const char *password,   /* (I) パスワード   */
        char       *dateTime    /* (O) 取得した情報 */
    );

/* エントリの投稿(ブックマークの追加登録) */
BOOL
postEntryOnBlueDot(
    const char      *userName,      /* (I) ユーザ名               */
    const char      *password,      /* (I) パスワード             */
    DELICIOUS_ENTRY *entry     );   /* (I) 登録する情報(投稿内容) */


/* エントリの削除 */
BOOL
deleteEntryOnBlueDot(
        const char *userName,   /* (I) ユーザ名                    */
        const char *password,   /* (I) パスワード                  */
        const char *url         /* (I) 削除するエントリの URL 要素 */
    );

/* タグの変更 */
BOOL
renameTagOnBlueDot(
        const char *userName,   /* (I) ユーザ名   */
        const char *password,   /* (I) パスワード */
        const char *oldTag,     /* (I) 古いタグ   */
        const char *newTag      /* (I) 新しいタグ */
    );

/*
 *  追加機能
 */

/* 総ブックマーク数の取得 */
long
getNumberOfBookmarksOnBlueDot(
        const char *userName,   /* (I) ユーザ名   */
        const char *password    /* (I) パスワード */
    );

/* 総タグ数の取得 */
long
getNumberOfTagsOnBlueDot(
        const char *userName,   /* (I) ユーザ名   */
        const char *password    /* (I) パスワード */
    );

/* Blue Dot へ login */
int
loginBlueDot(
        const char *userName,   /* (I)   ユーザ名   */
        const char *password,   /* (I)   パスワード */
        char       *cookie      /* (I/O) クッキー   */
    );

#endif  /* __BLUE_DOT_H__ */
