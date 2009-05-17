/*
 *  deliciousApi.h
 *      del.icio.us API および del.icio.us 互換 API (Blue Dot API) 共通処理
 *          written by H.Tsujimura  2 May 2005 / 6 Oct 2006
 *
 * History:
 * $Log: /comm/xmlRPC/deliciousApi.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     07/04/16 15:38 Tsujimura543
 * getAllPostsFromDeliciousXML を追加
 * 
 * 3     07/01/24 15:44 Tsujimura543
 * removeTagOnDeliciousAPI() を追加
 * 
 * 2     06/10/06 21:45 Tsujimura543
 * コメントを修正
 * 
 * 1     06/10/06 21:07 Tsujimura543
 * delicious.c から del.icio.us(互換)API をもつブックマークサービス共通処理
 * を抜き出して別ファイルとして独立させた
 */

#ifndef __DELICIOUS_API_H__
#define __DELICIOUS_API_H__

#include "xmlRPC.h"
#include "delicious.h"
#include <time.h>

/*
 *  del.icio.us (互換) API 共通処理
 */

#ifndef	iskanji1
#define	iskanji1(s) \
    (((((short)s & 0xFF)>=0x81) && (((short)s & 0xFF)<=0x9f)) || \
     ((((short)s & 0xFF)>=0xe0) && (((short)s & 0xFF)<=0xfc)))
#endif

#define MAX_EXTENDED_LENGTH 170


typedef enum deliciousApiType   {
    DAPI_DELICIOUS,     /* del.icio.us */
    DAPI_BLUEDOT,       /* Blue Dot    */
}   DELICIOUS_API_TYPE;


/* 取得したエントリ情報の解析処理                               */
/*      -- エントリ情報を取得する関数群から呼び出される共通関数 */
long
getPostsOnDelicious(
        const char      *url,
        const char      *userName,
        const char      *password,
        long            *numOfPosts,
        DELICIOUS_POSTS *posts 
    );

/*  日付別投稿数一覧の取得 */
long
getListOfDatesOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元     */
        const char         *userName,   /* (I) ユーザ名       */
        const char         *password,   /* (I) パスワード     */
        char               *tag,        /* (I) タグ           */
        long               *numOfDates, /* (I) 取得する情報数 */
                                        /* (O) 取得した情報数 */
        DELICIOUS_DATES    *dates       /* (O) 取得した情報   */
    );

/*  タグ一覧の取得 */
long
getListOfTagsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元     */
        const char         *userName,   /* (I) ユーザ名       */
        const char         *password,   /* (I) パスワード     */
        long               *numOfTags,  /* (I) 取得する情報数 */
                                        /* (O) 取得した情報数 */
        DELICIOUS_TAGS     *tags        /* (O) 取得した情報   */
    );

/* 指定した日付に投稿したエントリの一覧の取得 */
long
getListOfPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,    /* (I) API 提供元                 */
        const char         *userName,  /* (I) ユーザ名                   */
        const char         *password,  /* (I) パスワード                 */
        const char         *tag,       /* (I) 検索条件 (タグ)            */
        const char         *dateTime,  /* (I) 検索条件 (投稿日時)        */
                                       /*       yyyy-mm-ddThh:mm:ssZ形式 */
        const char         *targetUrl, /* (I) 検索条件 (URL)             */
        long               *numOfPosts,/* (I) 取得する情報数             */
                                       /* (O) 取得した情報数             */
        DELICIOUS_POSTS    *posts      /* (O) 取得した情報               */
    );

/* 最近のエントリ一覧の取得 */
long
getRecentPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元      */
        const char         *userName,   /* (I) ユーザ名        */
        const char         *password,   /* (I) パスワード      */
        const char         *tag,        /* (I) 検索条件 (タグ) */
        long               *numOfPosts, /* (I) 取得する情報数  */
                                        /* (O) 取得した情報数  */
        DELICIOUS_POSTS    *posts       /* (O) 取得した情報    */
    );

/* 最終更新日時の取得 */
long
getLastUpdateOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元   */
        const char         *userName,   /* (I) ユーザ名     */
        const char         *password,   /* (I) パスワード   */
        char               *dateTime    /* (O) 取得した情報 */
    );

/* 全エントリの取得 */
long
getAllPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元      */
        const char         *userName,   /* (I) ユーザ名        */
        const char         *password,   /* (I) パスワード      */
        const char         *tag,        /* (I) 検索条件 (タグ) */
        long               *numOfPosts, /* (I) 取得する情報数  */
                                        /* (O) 取得した情報数  */
        DELICIOUS_POSTS    *posts       /* (O) 取得した情報    */
    );

long
getAllPostsFromDeliciousXML(
        const char      *buf,           /* (I) 取得する情報元  */
        long            *numOfPosts,    /* (I) 取得する情報数  */
                                        /* (O) 取得した情報数  */
        DELICIOUS_POSTS *posts          /* (O) 取得した情報    */
    );

/* ブックマークの投稿 */
BOOL
postEntryOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元             */
        const char         *userName,   /* (I) ユーザ名               */
        const char         *password,   /* (I) パスワード             */
        DELICIOUS_ENTRY    *entry       /* (I) 登録する情報(投稿内容) */
    );

/* ブックマークの削除 */
BOOL
deleteEntryOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元                  */
        const char         *userName,   /* (I) ユーザ名                    */
        const char         *password,   /* (I) パスワード                  */
        const char         *url         /* (I) 削除するエントリの URL 要素 */
    );

/* タグの変更(置換) */
BOOL
renameTagOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元 */
        const char         *userName,   /* (I) ユーザ名   */
        const char         *password,   /* (I) パスワード */
        const char         *oldTag,     /* (I) 古いタグ   */
        const char         *newTag      /* (I) 新しいタグ */
    );

/* タグの削除 */
BOOL
removeTagOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API 提供元     */
        const char         *userName,   /* (I) ユーザ名       */
        const char         *password,   /* (I) パスワード     */
        const char         *tag         /* (I) 削除対象のタグ */
    );

#endif  /* __DELICIOUS_API_H__ */
