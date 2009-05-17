/*
 *  delicious.h
 *
 *      for del.icio.us API
 *
 * History:
 * $Log: /comm/xmlRPC/delicious.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 13    08/07/25 0:44 Tsujimura543
 * (1) private saving 対応
 * (2) hash が 32バイトから33バイトに変更されたのに伴う対応
 *     (最大64ビットまで対応できるようにしておいた)
 * 
 * 12    08/05/16 15:17 Tsujimura543
 * getAllPostsFromDeliciousHTML() を追加
 * 
 * 11    08/05/15 22:37 Tsujimura543
 * DELICIOUS_POSTS 構造体の href のサイズを2倍にした
 * 
 * 10    07/01/26 17:57 Tsujimura543
 * getNumberOfTagsOnDelicious() を追加
 * 
 * 9     07/01/24 15:43 Tsujimura543
 * removeTagOnDelicious() と loginDelicious() を追加
 * 
 * 8     06/08/17 11:49 Tsujimura543
 * del.icio.us の API 改定(2006年8月9日)に対応
 * 
 * 7     05/12/01 14:55 Tsujimura543
 * MAX_DESCRIPTION_LEN の定義(値)を統一し、xmlRPC.h に移動
 * 
 * 6     05/06/02 21:59 Tsujimura543
 * 動作確認完了
 * 
 * 5     05/06/02 13:55 Tsujimura543
 * getNumberOfBookmarksOnDelicious() を追加
 * 
 * 4     05/05/27 20:50 Tsujimura543
 * 要求と応答の例をコメントに追加
 * 
 * 3     05/05/26 14:20 Tsujimura543
 * deleteEntryOnDelicious のコメントを追加(要求と応答の例を追加)
 * 
 * 2     05/05/25 21:38 Tsujimura543
 * 関数のプロトタイプ宣言と構造体の定義の記述、完了
 * 
 * 1     05/05/24 22:14 Tsujimura543
 * とりあえず、コメントのみ記述
 */

#ifndef __DELICIOUS_H__
#define __DELICIOUS_H__

/*
 *  ・del.icio.us API の仕様(最新版) は、http://del.icio.us/doc/api を参照
 *  ・del.icio.us API は BASIC認証による認証を採用している
 *  ・API の連続実行を行なう場合、少なくとも1秒以上間隔を空けて実行すること
 *  ・503 エラーに注意
 *  ・User-Agent の内容によっては ban することがある
 */

/*
 *  日付別投稿数の一覧の取得
 *    function: http://del.icio.us/api/posts/dates?
 *          &tag= filter by this tag - optional
 *      returns a list of dates with the number of posts at each date. 
 *      [tag] adds a filter
 *
 *   例 1)
 *    要求
 *      http://del.icio.us/api/posts/dates
 *    応答
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <dates tag="" user="tsupo">
 *          <date count="8" date="2005-05-24" /> 
 *          <date count="1" date="2005-05-23" /> 
 *          <date count="11" date="2005-05-22" />
 *           (中略)
 *          <date count="51" date="2005-01-18" /> 
 *          <date count="44" date="2005-01-17" /> 
 *          <date count="10" date="2005-01-14" /> 
 *      </dates>
 *
 *   例 2)
 *    要求
 *      http://del.icio.us/api/posts/dates?tag=umeda
 *    応答
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <dates tag="umeda" user="tsupo">
 *          <date count="2" date="2005-04-28" /> 
 *          <date count="3" date="2005-04-27" /> 
 *          <date count="2" date="2005-04-12" /> 
 *          <date count="5" date="2005-04-06" /> 
 *          <date count="2" date="2005-03-28" /> 
 *      </dates>
 */

typedef struct datesOnDelicious {
    int     yyyy;   /* 投稿日 (年)        */
    int     mm;     /* 投稿日 (月)        */
    int     dd;     /* 投稿日 (日)        */
    long    count;  /* 当該投稿日の投稿数 */
}   DELICIOUS_DATES;

long
getListOfDatesOnDelicious(
        const char      *userName,      /* (I) ユーザ名       */
        const char      *password,      /* (I) パスワード     */
        char            *tag,           /* (I) タグ           */
        long            *numOfDates,    /* (I) 取得する情報数 */
                                        /* (O) 取得した情報数 */
        DELICIOUS_DATES *dates          /* (O) 取得した情報   */
    );


/*
 *  使っているタグの一覧の取得
 *    function: http://del.icio.us/api/tags/get?
 *      returns a list of tags the user has used.
 *
 *   例)
 *    要求
 *      http://del.icio.us/api/tags/get
 *    応答
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <tags>
 *          <tag count="12" tag=".NET" /> 
 *          <tag count="1" tag="29man" /> 
 *          <tag count="1" tag="2ch" /> 
 *           (中略)
 *          <tag count="1" tag="zipCode" /> 
 *          <tag count="2" tag="zoids" /> 
 *          <tag count="1" tag="zoo" /> 
 *      </tags>
 */

#define MAX_TAG_LEN     128 /* [暫定値] */

typedef struct tagsOnDelicious  {
    char    tag[MAX_TAG_LEN];   /* タグ                           */
    long    count;              /* 当該タグ付けされたエントリの数 */
}   DELICIOUS_TAGS;

long
getListOfTagsOnDelicious(
        const char     *userName,   /* (I) ユーザ名       */
        const char     *password,   /* (I) パスワード     */
        long           *numOfTags,  /* (I) 取得する情報数 */
                                    /* (O) 取得した情報数 */
        DELICIOUS_TAGS *tags        /* (O) 取得した情報   */
    );


/*
 *  指定した日付に投稿したエントリの一覧の取得
 *    function: http://del.icio.us/api/posts/get?
 *          &tag= filter by this tag - optional
 *          &dt= filter by this date
 *      returns a list of posts on a given date, filtered by tag. if no 
 *      date is supplied, most recent date will be used
 *
 *   例 1)
 *    要求
 *      http://del.icio.us/api/posts/get
 *    応答 (引数を指定しなかった場合は、「今日」(もしくはいちばん最後の投稿日)
 *          の分が返る)
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <posts dt="2005-05-24" tag="" user="tsupo">
 *          <post href="http://hatena.g.hatena.ne.jp/hatenabookmark/20050524/1116917761"
 *              description="はてな各サービスの機能変更、お知らせなど - はてなブックマーク日記 - タグ機能の追加について"
 *              extended="本日、はてなブックマークにタグ機能を追加しました。"
 *              hash="dc2662b2b06bdda9584d91fec41443bb"
 *              others="4"
 *              tag="bookmark hatena socialBookmark tag"
 *              time="2005-05-24T09:05:06Z" /> 
 *          <post href="http://kotonoha.main.jp/2005/05/24making-trackback-policy.html"
 *              description="トラックバック・ポリシーを作ろう。ルールやマナーに悩む人のための作成ガイド [絵文録ことのは]2005/05/24"
 *              extended="「トラックバックされたくないならなんでトラックバックできるようになっとんねん！」とツッコムのが関西型の流儀である"
 *              hash="d432e0590e9a6eb83043dd1a009a1f9b"
 *              others="1"
 *              tag="blog policy trackback"
 *              time="2005-05-24T07:50:29Z" /> 
 *          <post href="http://www10.ocn.ne.jp/~fanta-sy/index00.html"
 *              description="ふぁんたじぃ　いりゅうじょん: 最近の教科書って…"
 *              extended="意外と　どういう教科書を使っているか知らない人も　多いんじゃないかなと思って紹介するページを作りました。"
 *              hash="64ed15c02124ef2fb58624498bafa386"
 *              others="2"
 *              tag="moe"
 *              time="2005-05-24T01:23:04Z" /> 
 *      </posts>
 *
 *   例 2)
 *    要求
 *      http://del.icio.us/api/posts/get?dt=20050521
 *    応答
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <posts dt="20050521" tag="" user="tsupo">
 *          <post href="http://d.hatena.ne.jp/churchill/20050521/p2"
 *              description="平成に生まれて - あやうく騙されるとこだったぜ"
 *              extended="私が想像してたのはコメント欄に「かわいい犬ですね。うふふ。」なんていうコメントが溢れかえる日記だったのです。"
 *              hash="16248f29b98ff8c9d50c50ca6eaa3407"
 *              others="1"
 *              tag="dialy hatena"
 *              time="2005-05-21T18:32:44Z" /> 
 *          <post href="http://www.hotnam.com/news/050521032025.html"
 *              description="ベトナムで広がる日本の HENTAI アニメ - HOTNAM！ベトナム最新情報"
 *              extended="若者はHENTAIアニメに新感覚を求め、画像の美しさにのめり込み、もはや古典的なアダルトビデオでは好奇心を満たせなくなっている。"
 *              hash="cc3241e8b5ab81b21ed379d618b2c4b5"
 *              others="2"
 *              tag="HENTAI anime comic vietNam"
 *              time="2005-05-21T18:45:27Z" />
 *      </posts>
 *
 *   例 3)
 *    要求
 *      http://del.icio.us/api/posts/get?dt=20050524&tag=moe
 *    応答
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <posts dt="20050524" tag="moe" user="tsupo">
 *          <post href="http://www10.ocn.ne.jp/~fanta-sy/index00.html"
 *              description="ふぁんたじぃ　いりゅうじょん: 最近の教科書って…"
 *              extended="意外と　どういう教科書を使っているか知らない人も　多いんじゃないかなと思って紹介するページを作りました。"
 *              hash="64ed15c02124ef2fb58624498bafa386"
 *              others="2"
 *              tag="moe"
 *              time="2005-05-24T01:23:04Z" />
 *      </posts>
 */

#define HASH_LENGTH         64
typedef struct postsOnDelicious {
    char    href[MAX_URLLENGTH * 2];     /* ブックマーク対象Webページ URL */
    char    description[MAX_DESCRIPTION_LEN];   /* 当該 Webページの title */
    char    extended[MAX_DESCRIPTION_LEN];      /* 概要もしくはコメント   */
    char    hash[HASH_LENGTH + 1];       /* 参照ページURL生成用ハッシュ値 */
    long    others;      /* 自分以外に当該URLをブックマークしている人の数 */
    char    tag[MAX_DESCRIPTION_LEN];/* タグ (空白区切りで複数個指定可能) */
    char    dateTime[MAX_DATELENGTH];           /* 投稿日時               */
    BOOL    shared;                             /* 共有(公開)するか否か   */
}   DELICIOUS_POSTS;

long
getListOfPostsOnDelicious(
        const char      *userName,  /* (I) ユーザ名                         */
        const char      *password,  /* (I) パスワード                       */
        const char      *tag,       /* (I) 検索条件 (タグ)                  */
#ifdef  BEFORE_20060809
        const char      *dateTime,  /* (I) 検索条件 (投稿日時) yyyymmdd形式 */
#else
        const char      *dateTime,  /* (I) 検索条件 (投稿日時)
                                                   yyyy-mm-ddThh:mm:ssZ形式 */
        const char      *targetUrl, /* (I) 検索条件 (URL)                   */
#endif

        long            *numOfPosts,/* (I) 取得する情報数                   */
                                    /* (O) 取得した情報数                   */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報                     */
    );


/*
 *  最近のエントリ一覧の取得
 *    function: http://del.icio.us/api/posts/recent?
 *          &tag= filter by this tag - optional
 *          &count= number of items to retrieve - optional (defaults to 15, maximum 100)
 *      returns a list of most recent posts, possibly filtered by tag, maxes out at 100.
 *    注意: 2005年5月25日現在、description に日本語が存在すると文字化けが
 *          発生する現象が見られる
 *    注意: この API で取得した post 要素には others 属性は含まれていない
 */

long
getRecentPostsOnDelicious(
        const char      *userName,  /* (I) ユーザ名        */
        const char      *password,  /* (I) パスワード      */
        const char      *tag,       /* (I) 検索条件 (タグ) */
        long            *numOfPosts,/* (I) 取得する情報数  */
                                    /* (O) 取得した情報数  */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報    */
    );


/*
 *  全エントリの取得
 *    function: http://del.icio.us/api/posts/all
 *          &tag= filter by this tag - optional
 *      returns all posts. use sparingly. call update function first
 *      to see if you need to fetch this at all.
 *    注意: この API で取得した post 要素には others 属性は含まれていない
 */

long
getAllPostsOnDelicious(
        const char      *userName,  /* (I) ユーザ名        */
        const char      *password,  /* (I) パスワード      */
        const char      *tag,       /* (I) 検索条件 (タグ) */
        long            *numOfPosts,/* (I) 取得する情報数  */
                                    /* (O) 取得した情報数  */
        DELICIOUS_POSTS *posts      /* (O) 取得した情報    */
    );


/*
 *  最終更新日時の取得
 *    function: http://del.icio.us/api/posts/update
 *      returns the last update time for the user. combine this
 *      with posts/all to see if the data returned has changed
 *      since last fetch. this call is pretty lightweight. don't
 *      call posts/all unless you have to.
 *
 *   例)
 *    要求
 *      http://del.icio.us/api/posts/update
 *    応答
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <update time="2005-05-25T11:03:19Z" /> 
 */

long
getLastUpdateOnDelicious(
        const char *userName,   /* (I) ユーザ名     */
        const char *password,   /* (I) パスワード   */
        char       *dateTime    /* (O) 取得した情報 */
    );


/*
 *  エントリの投稿(ブックマークの追加登録)
 *    function: http://del.icio.us/api/posts/add?
 *          &url= url for post
 *          &description= description for post
 *          &extended= extended for post
 *          &tags= space-delimited list of tags
 *          &dt= datestamp for post, format "CCYY-MM-DDThh:mm:ssZ"
 *      makes a post to delicious. 
 *      the datestamp requires a LITERAL "T" and "Z" like in ISO8601 at
 *      http://www.cl.cam.ac.uk/~mgk25/iso-time.html. for example:
 *      "1984-09-01T14:21:31Z"
 *   例)
 *    要求
 *      http://del.icio.us/api/posts/add?url=http%3A%2F%2Fexample.com%2Fdel.icio.us%2FAPI%2Ftest%2F
 *      &description=%E3%81%93%E3%81%AE%E3%83%96%E3%83%83%E3%82%AF%E3%83%9E%E3%83%BC%E3%82%AF%E3%81%AF%20%64%65%6C%2E%69%63%69%6F%2E%75%73%20%41%50%49%20%E3%82%92%E4%BD%BF%E3%81%A3%E3%81%A6%E3%81%BF%E3%82%8B%E3%83%86%E3%82%B9%E3%83%88%E3%81%A7%E3%81%99%E3%80%82%E7%84%A1%E8%A6%96%E3%81%97%E3%81%A6%E3%81%8F%E3%81%A0%E3%81%95%E3%81%84%E3%80%82
 *      &extended=%E7%8F%BE%E5%9C%A8%E3%80%81%64%65%6C%2E%69%63%69%6F%2E%75%73%20%41%50%49%20%E3%82%AF%E3%83%A9%E3%82%A4%E3%82%A2%E3%83%B3%E3%83%88%E3%81%AE%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%E4%B8%AD%E3%81%A7%E3%81%99%E3%80%82
 *      &tags=%74%65%73%74%20%64%65%62%75%67%20%64%65%6C%2E%69%63%69%6F%2E%75%73%20%41%50%49%20%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%20%E3%83%86%E3%82%B9%E3%83%88%20%E3%83%96%E3%83%83%E3%82%AF%E3%83%9E%E3%83%BC%E3%82%AF
 *      &dt=%32%30%30%35%2D%30%35%2D%32%37%54%30%37%3A%33%34%3A%33%31%5A
 *    応答
 *      <?xml version='1.0' standalone='yes'?>
 *      <result code="done" />
 */

typedef struct entryOnDelicious {
    char    url[MAX_URLLENGTH];          /* ブックマーク対象Webページ URL */
    char    description[MAX_DESCRIPTION_LEN];   /* 当該 Webページの title */
    char    extended[MAX_DESCRIPTION_LEN];      /* 概要もしくはコメント   */
    char    tag[MAX_DESCRIPTION_LEN];/* タグ (空白区切りで複数個指定可能) */
    char    dateTime[MAX_DATELENGTH];           /* 投稿日時               */
    BOOL    shared;                             /* 共有(公開)するか否か   */
}   DELICIOUS_ENTRY;

BOOL
postEntryOnDelicious(
        const char      *userName,  /* (I) ユーザ名               */
        const char      *password,  /* (I) パスワード             */
        DELICIOUS_ENTRY *entry      /* (I) 登録する情報(投稿内容) */
    );


/*
 *  エントリの削除
 *    function: http://del.icio.us/api/posts/delete?
 *          &url= url for post
 *      deletes a post from delicious
 *   例)
 *    要求
 *       http://del.icio.us/api/posts/delete?url=http%3A%2F%2Fexample.com%2Fdel.icio.us%2FAPI%2Ftest%2F
 *    応答
 *      <?xml version='1.0' standalone='yes'?>
 *      <result code="done" />
 */

BOOL
deleteEntryOnDelicious(
        const char *userName,   /* (I) ユーザ名                    */
        const char *password,   /* (I) パスワード                  */
        const char *url         /* (I) 削除するエントリの URL 要素 */
    );


/*
 *  タグの変更
 *    function: http://del.icio.us/api/tags/rename?
 *          &old= old tag
 *          &new= new tag
 *      renames a tag
 *
 *   例)
 *    要求
 *      http://del.icio.us/api/tags/rename?old=trueworthy&new=trustworthy
 *    応答
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <result>done</result> 
 */

BOOL
renameTagOnDelicious(
        const char *userName,   /* (I) ユーザ名   */
        const char *password,   /* (I) パスワード */
        const char *oldTag,     /* (I) 古いタグ   */
        const char *newTag      /* (I) 新しいタグ */
    );


/*
 *  タグ分類表の取得
 *    function: http://del.icio.us/api/tags/bundles/all
 *      retrieves all bundles
 *
 *   例)
 *    要求
 *      http://del.icio.us/api/tags/bundles/all
 *    応答
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <bundles>
 *          <bundle name="charactercode" tags="hankaku zenkaku" /> 
 *          <bundle name="fun" tags="aprilFool foods neta pairYoung" /> 
 *          <bundle name="facility" tags="AU DDIpocket IPMO PENCK PHS WindowsCE.NET ZipCode bank business dial-up education farmwareUpdate life mobile money-order patent point send-money softwareFactory symbian telephony" /> 
 *           (中略)
 *          <bundle name="BBS" tags="ASCII-NET" /> 
 *          <bundle name="security" tags="XSS cabir phishing secureProgramming system:unfiled virus websense" /> 
 *          <bundle name="wiki" tags="FSWiki JSPWiki MoWiki pukiwiki pyukiwiki wiki" /> 
 *      </bundles>
 */

typedef struct bundlesOnDelicious   {
    char    name[MAX_URLLENGTH];        /* 「分類」の名前 URL */
    char    tags[MAX_DESCRIPTION_LEN];  /* 当該分類に所属するタグ (空白区切りで複数個指定) */
}   DELICIOUS_BUNDLES;

long
getListOfBundlesOnDelicious(
        const char        *userName,    /* (I) ユーザ名       */
        const char        *password,    /* (I) パスワード     */
        long              *numOfBundles,/* (I) 取得する情報数 */
                                        /* (O) 取得した情報数 */
        DELICIOUS_BUNDLES *bundles      /* (O) 取得した情報   */
    );


/*
 *  タグの分類
 *    function: http://del.icio.us/api/tags/bundles/set
 *          &bundle= bundle name
 *          &tags= space-separated list of tags
 *      assigns a set of tags to a single bundle, wipes away previous settings for bundle
 *   例)
 *    要求
 *      http://del.icio.us/api/tags/bundles/set?bundle=culture&tags=vietNam
 *    応答 (成功時)
 *      <?xml version='1.0' standalone='yes'?>
 *      <result>ok</result>
 *    応答 (エラー発生時)
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <result code="something went wrong" />
 *    注意: すでに bundle で指定した名前の分類が存在する場合は上書きされる
 *          (今までの分類は消えてしまう)
 */

BOOL
setBundleOnDelicious(
        const char *userName,   /* (I) ユーザ名        */
        const char *password,   /* (I) パスワード      */
        const char *bundle,     /* (I) 「分類」の名前  */
        const char *tags        /* (I) タグ (空白区切りで複数個指定可能) */
    );

/*
 *  分類の削除
 *    function: http://del.icio.us/api/tags/bundles/delete
 *          &bundle= bundle name
 *      deletes a bundle
 *   例)
 *    要求
 *      http://del.icio.us/api/tags/bundles/delete?bundle=testTestTest
 *    応答
 *      <?xml version='1.0' standalone='yes'?>
 *      <result>ok</result>
 */

BOOL
deleteBundleOnDelicious(
        const char *userName,   /* (I) ユーザ名        */
        const char *password,   /* (I) パスワード      */
        const char *bundle      /* (I) 「分類」の名前  */
    );


/*
 *  追加機能
 */

/* 総ブックマーク数の取得 */
long
getNumberOfBookmarksOnDelicious(
        const char *userName,   /* (I) ユーザ名   */
        const char *password    /* (I) パスワード */
    );

/* 総タグ数の取得 */
long
getNumberOfTagsOnDelicious(
        const char *userName,   /* (I) ユーザ名   */
        const char *password    /* (I) パスワード */
    );

/* タグの削除 */
BOOL
removeTagOnDelicious(
        const char *userName,   /* (I) ユーザ名       */
        const char *password,   /* (I) パスワード     */
        const char *tag         /* (I) 削除対象のタグ */
    );

/* del.icio.us へ login */
int
loginDelicious(
        const char *userName,   /* (I)   ユーザ名   */
        const char *password,   /* (I)   パスワード */
        char       *cookie      /* (I/O) クッキー   */
    );

/* del.icio.us からブックマークを取得 (スクレイピング版) */
long
getAllPostsFromDeliciousHTML(
        const char      *userName,   /* (I) ユーザ名       */
        const char      *password,   /* (I) パスワード     */
        long            *numOfPosts, /* (I) 取得する情報数 */
                                     /* (O) 取得した情報数 */
        DELICIOUS_POSTS *posts       /* (O) 取得した情報   */
    );

#endif  /* __DELICIOUS_H__ */
