/*
 *  xmlRPCapi.c
 *
 *    XML-RPC API サポートライブラリ
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2009 by H.Tsujimura
 *      written by H.Tsujimura
 *
 * History:
 * $Log: /comm/xmlRPC/xmlRPCapi.c $
 * 
 * 2     09/05/22 21:07 tsupo
 * 「1.264版→1.265版」の変更を取り込む
 * 
 * 53    09/05/22 17:42 Tsujimura543
 * ソースを整理
 * 
 * 52    09/05/22 17:40 Tsujimura543
 * uploadFile() を修正(ココログの .. へのファイルアップロード時、ココログ
 * へのログイン処理実行の副作用でアップロード対象のファイルの中身を格納し
 * ているメモリ領域の内容が破壊されてしまう不具合があった)
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 51    09/03/20 17:45 Tsujimura543
 * ウェブリブログの XML-RPC API 経由での投稿、動作確認終了
 * 
 * 50    09/03/17 22:42 Tsujimura543
 * Windows Live Spaces (およびウェブリブログ) 向けの処理を追加
 * 
 * 49    09/03/16 19:17 Tsujimura543
 * getCategories() を追加
 * 
 * 48    07/12/14 0:10 Tsujimura543
 * isActive() をいったん元に戻す
 * 
 * 47    07/12/13 22:23 Tsujimura543
 * isActive() を見直し
 * 
 * 46    07/12/06 1:49 Tsujimura543
 * uploadFile() 内の不要なコードを削除
 * 
 * 45    07/10/29 20:04 Tsujimura543
 * XML-RPC API 経由での ヤプログ! への投稿に対応
 * 
 * 44    07/10/09 19:41 Tsujimura543
 * dputs(), dprintf() を導入
 * 
 * 43    07/09/28 16:48 Tsujimura543
 * DEBUG_FOR_ADS 部分を正式なデバッグ用機能として取り込んだ
 * 
 * 42    07/09/07 20:52 Tsujimura543
 * http通信のスレッド間排他制御対応
 * 
 * 41    07/03/03 15:23 Tsujimura543
 * sjis2utf() が NULL を返す場合の対策を実施
 * 
 * 40    07/02/26 16:21 Tsujimura543
 * editPostEx() もドリコムブログに対応させた
 * 
 * 39    07/02/24 1:59 Tsujimura543
 * XML-RPC API 経由でのドリコムブログへの投稿に対応
 * (JUGEM に関しては、特に特別な処理を書かなくても XML-RPC API 経由での
 * 投稿に成功した)
 * 
 * 38    06/12/04 13:36 Tsujimura543
 * newMediaObject() を修正(アップロードしようとしているファイルのサイズ
 * に応じてタイムアウト時間の値を変更するようにした)
 * 
 * 37    06/10/19 18:44 Tsujimura543
 * sendUpdateExtendedPing() を追加
 * 
 * 36    06/10/07 1:34 Tsujimura543
 * http(応答受信待ち)タイムアウト時間を設定変更できるようにした
 * 
 * 35    06/09/08 10:14 Tsujimura543
 * setPostCategories() を修。FC2blog でもカテゴリの設定ができるように
 * なったことを確認。
 * 
 * 34    06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 でのビルドチェック結果を反映
 * 
 * 33a   06/09/03 20:17 tsupo
 * cookie まわりを修正
 * 
 * 33    06/09/02 1:12 Tsujimura543
 * http通信実行中かどうかをチェックできる関数を追加した
 * 
 * 32    06/07/24 20:10 Tsujimura543
 * _httpExecute() のバッファオーバーラン防止機能を利用するようにした
 * 
 * 31    06/07/14 16:23 Tsujimura543
 * あずスタさん向けデバッグバージョン (DEBUG_FOR_ADS)
 * 
 * 30    06/03/14 23:39 Tsujimura543
 * uploadFile() と deleteFile() をココログフリーにも対応させた
 * 
 * 29    06/03/14 20:53 Tsujimura543
 * deleteFile() を追加
 * 
 * 28    05/12/16 13:52 Tsujimura543
 * ココログでのエラー発生時の response が BUFSIZ * 4 よりも大きい場合が
 * ある(サーバ高負荷時に再構築しようとした場合)ため、暫定的な対策を実施
 * 
 * 27    05/11/17 21:31 Tsujimura543
 * http による送信可能な電文サイズの上限をメモリの許す限りどこまでも
 * 大きくできるようにした (初期サイズは従来の値)
 * 
 * 26    05/11/17 16:10 Tsujimura543
 * uploadFile() を修正し、ココログの場合のみ、サイトトップディレクトリへの
 * アップロードをサポート (cocolog.c と連携)
 * 
 * 25    05/01/04 15:08 Tsujimura543
 * コメントを修正
 * 
 * 24    05/01/04 15:05 Tsujimura543
 * newMediaObject() で、ファイル名に error が含まれる場合、アップロードに
 * 失敗したと誤判定してしまう不具合に対処
 * 
 * 23    04/12/28 15:34 Tsujimura543
 * ココログでのエラー発生時の response が BUFSIZ より大きい(1200バイト超)
 * 場合があるため、response を静的に確保している場合は BUFSIZ * 4 の大き
 * さを確保するようにしてみた
 * 
 * 22    04/12/16 19:11 Tsujimura543
 * uploadFile() の第4引数が空文字列のとき、余分な / が付いてしまうのを
 * 避けるため、第4引数が NULL の場合と処理を同じにした。
 * 
 * 21    04/11/01 21:02 Tsujimura543
 * 警告レベル 4 での warning を可能な限り減らしてみた
 * 
 * 20    04/11/01 19:53 Tsujimura543
 * 『「こうさぎ」からのおすすめ』を試験的に実装
 * 
 * 19    04/10/15 15:20 Tsujimura543
 * NewsHandler の blog ID, post ID は共に32byteであるため、領域を増やして
 * 対応する
 * 
 * 18    04/09/28 17:04 Tsujimura543
 * dc:creator の存在しない RSS (アメーバブログ) も扱えるようにした
 * 
 * 17    04/08/31 12:06 Tsujimura543
 * getStringFromItem()、getDateTimeFromItem() を xmlRPCutil.c に移動
 * 
 * 16    04/08/30 18:26 Tsujimura543
 * getRecentPostTitlesFromRSS を追加
 * 
 * 15    04/08/27 18:12 Tsujimura543
 * JUGEM, exciteブログ, ヤプログ の各々の対応処理を別ソースファイルとして
 * 分離独立させた
 * 
 * 14    04/08/27 16:12 Tsujimura543
 * ヤプログ対応
 * 
 * 13    04/08/27 11:25 Tsujimura543
 * exciteブログへの投稿時、カテゴリIDが1(未分類)の場合、カテゴリの選択肢を
 * 表示するようにした
 * 
 * 12    04/08/27 10:47 Tsujimura543
 * postExciteBlog() 内で設定する htmlflag の値を 0 から 1 に変更した
 * 
 * 11    04/08/26 23:00 Tsujimura543
 * ・exciteブログへ投稿するときにフラグの意味を逆にしていたのを修正
 *   (公開、コメント可、トラックバック可になるように修正した)
 * ・exciteブログへの投稿処理にカテゴリIDからカテゴリ名を牽く機能を付加
 * 
 * 10    04/08/26 22:20 Tsujimura543
 * exciteブログに投稿できることを確認
 * 
 * 9     04/08/25 16:58 Tsujimura543
 * loginJugem, postJugem を追加
 * 
 * 8     04/08/20 18:45 Tsujimura543
 * WebサーバがIISの場合、エラー時に大きなhtmlを送ってくることがある(バッファ
 * オーバーランが発生する)現象への対策を実施
 * 
 * 7     04/08/17 12:23 Tsujimura543
 * getRecentPostTitlesOnBloggerAPI, getRecentPostTitlesOnMetaWeblog を追加
 * 
 * 6     04/08/16 19:08 Tsujimura543
 * getRecentPostTitles(), getRecentPostsEx() を修正(生成するXMLの内容修正)
 * 
 * 5     04/07/14 18:50 Tsujimura543
 * Movable Type API 関連の関数の仕様見直し
 * 
 * 4     04/07/12 15:50 Tsujimura543
 * metaWeblog API 関連の関数の仕様見直し
 * 
 * 3     04/07/09 20:24 Tsujimura543
 * blogger API 関連の関数の仕様見直し
 * 
 * 2     04/07/07 11:50 Tsujimura543
 * RCS による版数管理から VSS による版数管理に移行
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/xmlRPCapi.c 2     09/05/22 21:07 tsupo $";
#endif


char    *encodeString( const char *src, char *dst );

BOOL    isActive( void )
{
    BOOL    ret = FALSE;

    if ( xmlrpc_p ) {
        EnterCriticalSection( &xmlrpc_p->critic );
        ret = xmlrpc_p->active;
        if ( ret ) {
            if ( xmlrpc_p->threadID == GetCurrentThreadId() )
                ret = FALSE;
        }
        LeaveCriticalSection( &xmlrpc_p->critic );
    }

    return ( ret );
}

void
setActive( BOOL active )
{
    if ( xmlrpc_p ) {
        EnterCriticalSection( &xmlrpc_p->critic );
        xmlrpc_p->active = active;
        if ( active )
            xmlrpc_p->threadID = GetCurrentThreadId();
        else
            xmlrpc_p->threadID = 0;
        LeaveCriticalSection( &xmlrpc_p->critic );
    }
}

void
setTimeoutTime( int timeout )
{
    if ( xmlrpc_p ) {
        if ( !isActive() ) {
            EnterCriticalSection( &xmlrpc_p->critic );
            xmlrpc_p->timedoutTime = (timeout > 0) ? timeout
                                                   : DEFAULT_HTTP_TIMEOUT;
            LeaveCriticalSection( &xmlrpc_p->critic );
        }
    }
}

/*
 *  update ping の送信
 *      weblogUpdates.ping
 *          説明: update ping (blog更新通知) を送信します
 *          引数: String weblogname,
 *                String weblogURL
 *          返り値: 成功すると メンバー flerror の値が 0 (false) である構造
 *                  体が返ります。
 *                  失敗すると メンバー flerror の値が 1 (true) である構造体
 *                  が返ります。
 */

BOOL
sendUpdatePing( const char *weblogName, // (I) blog の名前 [Shift_JIS]
                const char *weblogURL ) // (I) blog の URL
{
    int     ret = FALSE, r;
    char    buffer[BUFSIZ];
    char    response[BUFSIZ * 4];
    char    *p;
    size_t  sz  = BUFSIZ * 4;

    if ( !weblogName || !(weblogName[0]) || !weblogURL || !(weblogURL[0]) )
        return ( ret );
    if ( (strlen( weblogName ) >= MAX_BLOGNAMELENGTH) ||
         (strlen( weblogURL )  >= MAX_URLLENGTH)         )
        return ( ret );

    memset( buffer, NUL, BUFSIZ );
    p = sjis2utf( weblogName );
	sprintf( buffer,
		     XML_STATEMENT
		     "<methodCall>\n<methodName>weblogUpdates.ping</methodName>\n"
		     "<params>\n"
             "<param>\n<value>%s</value>\n</param>\n"
		     "<param>\n<value>%s</value>\n</param>\n"
             "</params>\n"
		     "</methodCall>\n\n",
             p ? p : weblogName, weblogURL );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL ) {
        /* 送信に成功した場合 */
        char    *p, *q;

        if ( ( p = strstr( response, "flerror" ) ) != NULL ) {
            if ( ( q = strchr( p + 7, '0' ) ) != NULL )
                ret = TRUE; /* update ping 成功 */
        }
    }

    return ( ret );
}

BOOL
sendUpdateExtendedPing( const char *weblogName, // (I) blog の名前 [Shift_JIS]
                        const char *weblogURL,  // (I) blog の URL
                        const char *targetURL,  // (I) ping 対象の URL
                        const char *feedURL )   // (I) RSS/Atom フィードの URL
{
    int     ret = FALSE, r;
    char    buffer[BUFSIZ];
    char    response[BUFSIZ * 4];
    char    *p;
    size_t  sz  = BUFSIZ * 4;

    if ( !weblogName || !(weblogName[0]) ||
         !weblogURL  || !(weblogURL[0])  ||
         !feedURL    || !(feedURL[0])       )
        return ( ret );
    if ((strlen( weblogName ) >= MAX_BLOGNAMELENGTH)                      ||
        (strlen( weblogURL )  >= MAX_URLLENGTH)                           ||
        (targetURL && *targetURL && (strlen(targetURL) >= MAX_URLLENGTH)) ||
        (strlen( feedURL )    >= MAX_URLLENGTH)                             )
        return ( ret );

    memset( buffer, NUL, BUFSIZ );
    p = sjis2utf( weblogName );
	sprintf( buffer,
		     XML_STATEMENT
		     "<methodCall>\n<methodName>weblogUpdates.extendedPing</methodName>\n"
		     "<params>\n"
             "<param>\n<value>%s</value>\n</param>\n"
		     "<param>\n<value>%s</value>\n</param>\n"
		     "<param>\n<value>%s</value>\n</param>\n"
		     "<param>\n<value>%s</value>\n</param>\n"
             "</params>\n"
		     "</methodCall>\n\n",
             p ? p : weblogName,
             weblogURL,
             targetURL && *targetURL ? targetURL : weblogURL,
             feedURL );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL ) {
        /* 送信に成功した場合 */
        char    *p, *q;

        if ( ( p = strstr( response, "flerror" ) ) != NULL ) {
            if ( ( q = strchr( p + 7, '0' ) ) != NULL )
                ret = TRUE; /* update ping 成功 */
        }
    }

    return ( ret );
}


/*
 *  blogger API
 */

/*
 *      blogger.newPost
 *          説明: 新しい記事をつくります．また，公開することもできます．
 *          引数: String  appkey,
 *                String  blogid,
 *                String  username,
 *                String  password,
 *                String  content,
 *                boolean publish
 *          返り値: 成功すると，String postid が新しい記事の ID 値として
 *                  得られます．
 *                  失敗したら，fault が返ります．
 */

BOOL
newPost( const char *blogID,    // (I) blog ID
         const char *userName,  // (I) ユーザ名
         const char *password,  // (I) パスワード
         const char *content,   // (I) 記事内容 [UTF-8]
         BOOL       publish,    // (I) 投稿状態 (FALSE: 下書き / TRUE: 公開)
         char       *postID )   // (O) 投稿後の記事ID
{
    int     ret = FALSE, r;
    char    *buffer;
    char    response[BUFSIZ * 4];
    int     len = !content ? 0 : strlen( content );
    size_t  sz  = BUFSIZ * 4;
    char    *tmp;

    if ( !blogID                             ||
         !(blogID[0])                        ||
         (strlen(blogID) > MAX_BLOGIDLENGTH) ||
         !postID                             ||
         (len == 0)                          ||
         (len >= SND_BUFFER_SIZE - BUFSIZ)      )
        return ( ret );
    *postID = NUL;

    tmp = (char *)malloc( len * 5 + 1 );
    if ( !tmp )
        return ( ret );

    encodeString( content, tmp );
    if ( strlen( tmp ) >= SND_BUFFER_SIZE - BUFSIZ ) {
        free( tmp );
        return ( ret );
    }

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( len + BUFSIZ );
    if ( !buffer ) {
        free( tmp );
        return ( ret );
    }

	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>blogger.newPost</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><boolean>%d</boolean></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             "C1C2C3C4C5", blogID, userName, password, tmp,
             publish == TRUE ? 1 : 0 );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL ) {
        if ( !strstr( response, "<methodResponse><fault><value>" ) ) {
            /*
             * String   postid
             */
            getSingleString( response, postID );
            ret = TRUE;
        }
    }

    free( buffer );
    free( tmp );

    return ( ret );
}


/*
 *      blogger.editPost
 *          説明: 既にある記事の情報を編集します．
 *          引数: String  appkey,
 *                String  postid,
 *                String  username,
 *                String  password,
 *                String  content,
 *                boolean publish
 *          返り値: 成功すると true が，失敗すると fault が返ります．
 */

BOOL
editPost( const char *postID,   // (I) 記事ID
          const char *userName, // (I) ユーザ名
          const char *password, // (I) パスワード
          const char *content,  // (I) 記事内容 [UTF-8]
          BOOL       publish )  // (I) 投稿状態 (FALSE: 下書き / TRUE: 公開)
{
    int     ret = FALSE, r;
    char    *buffer;
    char    response[BUFSIZ * 4];
    int     len = !content ? 0 : strlen( content );
    size_t  sz  = BUFSIZ * 4;
    char    *tmp;

    if ( !postID                                ||
         !(*postID)                             ||
         (strlen( postID ) >= MAX_POSTIDLENGTH) ||
         (len == 0)                             ||
         (len >= SND_BUFFER_SIZE - BUFSIZ)         )
        return ( ret );

    tmp = (char *)malloc( len * 5 + 1 );
    if ( !tmp )
        return ( ret );

    encodeString( content, tmp );
    if ( strlen( tmp ) >= SND_BUFFER_SIZE - BUFSIZ ) {
        free( tmp );
        return ( ret );
    }

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( len + BUFSIZ );
    if ( !buffer ) {
        free( tmp );
        return ( ret );
    }

	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>blogger.editPost</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><boolean>%d</boolean></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             "C1C2C3C4C5", postID, userName, password, tmp,
             publish == TRUE ? 1 : 0 );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL )
        if ( !strstr( response, "<methodResponse><fault><value>" ) )
            ret = TRUE;

    free( buffer );
    free( tmp );

    return ( ret );
}


/*
 *      blogger.deletePost
 *          説明: 記事を削除します．
 *          引数: String  appkey,
 *                String  postid,
 *                String  username,
 *                String  password,
 *                boolean publish
 *          返り値: 成功すると true，失敗すると fault が返ります．
 */

BOOL
deletePost( const char *postID,     // (I) 記事ID
            const char *userName,   // (I) ユーザ名
            const char *password,   // (I) パスワード
            BOOL       publish )    // (I) 投稿状態 [無視される]
{
    int     ret = FALSE, r;
    char    buffer[BUFSIZ];
    char    response[BUFSIZ * 4];
    size_t  sz  = BUFSIZ * 4;

    if ( !postID || !(postID[0]) || (strlen( postID ) >= MAX_POSTIDLENGTH) )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>blogger.deletePost</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><boolean>%d</boolean></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             "C1C2C3C4C5", postID, userName, password,
             publish == TRUE ? 1 : 0 );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL )
        if ( !strstr( response, "<methodResponse><fault><value>" ) )
            ret = TRUE;

    return ( ret );
}


/*
 *      blogger.getRecentPosts 
 *          説明: 最新の記事をシステムからとってきます．
 *          引数: String appkey,
 *                String blogid,
 *                String username,
 *                String password,
 *                int    numberOfPosts
 *          返り値: 成功すると，構造体の配列が返ってきます． 
 *                  構造体には，
 *                      ISO.8601 dateCreated,
 *                      String   userid,
 *                      String   postid,
 *                      String   content
 *                  が含まれます．(順は不同)
 *                  失敗すると，fault が返ります．
 *              注意: dateCreated は，blogid の weblog においての時間帯に
 *                    なっています．
 */

int
getRecentPosts( const char *blogID,         // (I) blog ID
                const char *userName,       // (I) ユーザ名
                const char *password,       // (I) パスワード
                int        *numOfEntries,   // (I) 取得したい記事情報の数
                                            // (O) 実際に取得した記事情報の数
                CONTENTINF *contentInfo )   // (O) 取得した記事情報
{
    int     ret = -1;
    char    buffer[BUFSIZ];
    char    *response;
    int     numOfRecentEntries = 0;
    size_t  sz;

    if ( !blogID                             ||
         !(blogID[0])                        ||
         (strlen(blogID) > MAX_BLOGIDLENGTH) ||
         !numOfEntries                       ||
         (*numOfEntries <= 0)                ||
         !contentInfo                           )
        return ( numOfRecentEntries );

    sz = *numOfEntries * 128 * 1024;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfRecentEntries );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
         XML_STATEMENT
         "<methodCall>\n<methodName>blogger.getRecentPosts</methodName>\n"
         "<params>\n"
         "<param>\n<value><string>%s</string></value>\n</param>\n"
         "<param>\n<value><string>%s</string></value>\n</param>\n"
         "<param>\n<value><string>%s</string></value>\n</param>\n"
         "<param>\n<value><string>%s</string></value>\n</param>\n"
         "<param>\n<value><i4>%d</i4></value>\n</param>\n"
         "</params>\n"
         "</methodCall>\n\n",
             "C1C2C3C4C5", blogID, userName, password, *numOfEntries );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    ret = httpPostEx( buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * ISO.8601 dateCreated,
         * String   userid,
         * String   postid,
         * String   content
         */
        char    *p = response;
        char    *q = strstr( p, "<array>" );
        int     cnt = 0;

        if ( q ) {
            q += 7;
            while ( *q ) {
                if ( !strstr( q, "<name>" ) )
                    break;
                if ( numOfRecentEntries >= *numOfEntries )
                    break;

                ret = getDateCreated( &q,
                                      &(contentInfo[numOfRecentEntries].yy),
                                      &(contentInfo[numOfRecentEntries].mm),
                                      &(contentInfo[numOfRecentEntries].dd),
                                      &(contentInfo[numOfRecentEntries].HH),
                                      &(contentInfo[numOfRecentEntries].MM),
                                      &(contentInfo[numOfRecentEntries].SS),
                                      &cnt, 4,
                                      &numOfRecentEntries );
                if ( ret == 4 ) {
                    cnt = 0;
                    continue;
                }

                ret = getUserid( &q,
                                 contentInfo[numOfRecentEntries].userid,
                                 &cnt, 4,
                                 &numOfRecentEntries );

                if ( ret == 4 ) {
                    cnt = 0;
                    continue;
                }

                ret = getPostid( &q,
                                 contentInfo[numOfRecentEntries].postid,
                                 &cnt, 4,
                                 &numOfRecentEntries );

                if ( ret == 4 ) {
                    cnt = 0;
                    continue;
                }

                ret = getContent( &q,
                                  contentInfo[numOfRecentEntries].content,
                                  &cnt, 4,
                                  &numOfRecentEntries );

                if ( ret == 4 ) {
                    cnt = 0;
                    continue;
                }

                q++;
            }
        }
    }

    free( response );
    *numOfEntries = numOfRecentEntries;

    return ( numOfRecentEntries );
}


/*
 *  blogger.getUsersBlogs 
 *      説明: 書き手さんが投稿できる weblog の群れを返します．
 *      引数: String appkey,
 *            String username,
 *            String password
 *      返り値: 成功すると，構造体の配列が返ってきます． 
 *              構造体には，
 *                  String url,
 *                  String blogid,
 *                  String blogName
 *              が含まれます． 
 *              失敗すると，fault が返ります．
 */

BOOL
getUsersBlogs( const char *userName,    // (I) ユーザ名
               const char *password,    // (I) パスワード
               char       *response )   // (O) blogger.getUsersBlogs の
                                        //     実行結果 (XML)
{
    int     ret = FALSE, r;
    char    buffer[BUFSIZ];

    if ( !response )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
    sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>blogger.getUsersBlogs</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             "C1C2C3C4", userName, password );
 // response[0] = NUL;

    r = httpPostEx( buffer, response );

    if ( response[0] != NUL )
        if ( !strstr( response, "<methodResponse><fault><value>" ) )
            ret = TRUE;

    return ( ret );
}


/*
 *  blogger.getUserInfo 
 *      説明: 書き手さんの情報を返します．
 *      引数: String appkey,
 *            String username,
 *            String password
 *      返り値: 成功すると，構造体の配列が返ってきます． 
 *              構造体には，
 *                  String userid,
 *                  String firstname,
 *                  String lastname,
 *                  String nickname,
 *                  String email,
 *                  String url
 *              が含まれます． 
 *              失敗すると，fault が返ります．
 *          注意: firstname は，Movable Type のユーザ名のうち，最初のスペース
 *                のところまでのものです． 
 *                lastname は，最初のスペース以降のものです．
 */

int
getUserInfo( const char *userName,      // (I) ユーザ名
             const char *password,      // (I) パスワード
             int        *numberOfUsers, // (I) 取得したいユーザ情報の数
                                        // (O) 実際に取得したユーザ情報の数
             USERINF    *userInfo )     // (O) 取得したユーザ情報
{
    int     ret = -1;
    char    buffer[BUFSIZ];
    char    *response;
    int     numOfUsers = 0;
    size_t  sz;

    if ( !numberOfUsers || (*numberOfUsers <= 0) || !userInfo )
        return ( numOfUsers );

    sz = *numberOfUsers * 10240;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfUsers );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>blogger.getUserInfo</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             "C1C2C3C4", userName, password );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    ret = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * String userid,
         * String firstname,
         * String lastname,
         * String nickname,
         * String email,
         * String url
         */
        char    *p = response;
        char    *q = strstr( p, "<array>" );
        int     cnt = 0;

        if ( !q ) {
            /* 返ってきたのが配列ではない場合        */
            /*   → ユーザ数 == 1 とみなして処理続行 */
            q = strstr( p, "<params>" );
        }

        if ( q ) {
            q += 7;
            while ( *q ) {
                if ( !strstr( q, "<name>" ) )
                    break;

                ret = getUserid( &q,
                                 userInfo[numOfUsers].userid,
                                 &cnt, 6,
                                 &numOfUsers );
                if ( ret == 6 ) {
                    if ( numOfUsers >= *numberOfUsers )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getFirstname( &q,
                                    userInfo[numOfUsers].firstname,
                                    &cnt, 6,
                                    &numOfUsers );
                if ( ret == 6 ) {
                    if ( numOfUsers >= *numberOfUsers )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getLastname( &q,
                                   userInfo[numOfUsers].lastname,
                                   &cnt, 6,
                                   &numOfUsers );
                if ( ret == 6 ) {
                    if ( numOfUsers >= *numberOfUsers )
                        break;
                    cnt = 0;
                    continue;
                }


                ret = getNickname( &q,
                                   userInfo[numOfUsers].nickname,
                                   &cnt, 6,
                                   &numOfUsers );
                if ( ret == 6 ) {
                    if ( numOfUsers >= *numberOfUsers )
                        break;
                    cnt = 0;
                    continue;
                }


                ret = getEmail( &q,
                                userInfo[numOfUsers].email,
                                &cnt, 6,
                                &numOfUsers );
                if ( ret == 6 ) {
                    if ( numOfUsers >= *numberOfUsers )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getUrl( &q,
                              userInfo[numOfUsers].url,
                              &cnt, 6,
                              &numOfUsers );
                if ( ret == 6 ) {
                    if ( numOfUsers >= *numberOfUsers )
                        break;
                    cnt = 0;
                    continue;
                }

                q++;
            }
        }
    }

    free( response );
    *numberOfUsers = numOfUsers;

    return ( numOfUsers );
}


/*
 *  metaWeblog API
 */

/*
 *  metaWeblog.newPost 
 *      説明: 新しい記事をつくります． また，公開することもできます．
 *      引数: String  blogid,
 *            String  username,
 *            String  password,
 *            struct  content,
 *            boolean publish
 *        注意: content 構造体は，次のような標準的な項目を含みます: 
 *                  String   title,       記事の件名
 *                  String   description, 記事の本文
 *                  ISO.8601 dateCreated, 記事が投稿された日時． 
 *                  String[] categories,  (省略可) [Windows Live Spaces 用と
 *                                        して、新たに追加されたパラメータ。
 *                                        Movable Type ではこの引数には対応
 *                                        していない]
 *              それに加えて，Movable Type では次の7つの項目に値を入れて渡すこ
 *              とができます: 
 *                  int      mt_allow_comments, allow_comments 項目への値; (コ
 *                                              メントを受け入れるか否か)
 *                  int      mt_allow_pings,   allow_pings 項目への値; (トラッ
 *                                             クバックPingを受け入れるか否か)
 *                  String   mt_convert_breaks, convert_breaks 項目の値; (記事
 *                                              本文の改行の扱い方)
 *                  String   mt_text_more,      追記の値; 
 *                  String   mt_excerpt,        概要の値;
 *                  String   mt_keywords,       キーワードの値;
 *                  array    mt_tb_ping_urls,   その記事に対するトラックバック
 *                                              Ping の URL の群れ;
 *              です． 
 *              dateCreated を使うなら，ISO.8601 形式でないといけません．(省略
 *              した場合は現在時刻を指定したものとみなされる)
 *      返り値: 成功すると，String postid が新しい記事の ID 値として返ってきま
 *              す
 *              失敗すると，fault です．
 */

BOOL
newPostEx( const char    *blogID,   // (I) blog ID
           const char    *userName, // (I) ユーザ名
           const char    *password, // (I) パスワード
           const CONTENT *content,  // (I) 記事情報
           BOOL          publish,   // (I) 投稿状態 (FALSE:下書き / TRUE:公開)
           char          *postID )  // (O) 投稿後の記事ID
{
    int     ret = FALSE, r, i, totalLen;
    char    *buffer;
    char    *response;
    int     len = !content ? 0
                           : !(content->description)
                                 ? 0
                                 : strlen( content->description );
    size_t  sz  = MAX_CONTENT_SIZE;
    char    *tmp1 = NULL, *tmp2 = NULL, *tmp3 = NULL;

    if ( !postID                               ||
         !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         (len == 0)                            ||
         (len >= SND_BUFFER_SIZE - BUFSIZ)        )
        return ( ret );
    *postID = NUL;

    tmp1 = (char *)malloc( len * 5 + 1 );
    if ( !tmp1 )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response ) {
        free( tmp1 );
        return ( ret );
    }

    encodeString( content->description, tmp1 );
    totalLen = strlen( tmp1 );
    if ( totalLen >= SND_BUFFER_SIZE - BUFSIZ ) {
        free( response );
        free( tmp1 );
        return ( ret );
    }

    if ( content->mt_text_more[0] != NUL ) {
        tmp2 = (char *)malloc( strlen( content->mt_text_more ) * 5 + 1 );
        if ( !tmp2 ) {
            free( response );
            free( tmp1 );
            return ( ret );
        }

        encodeString( content->mt_text_more, tmp2 );
        totalLen += strlen( tmp2 );
        if ( totalLen >= SND_BUFFER_SIZE - BUFSIZ ) {
            free( tmp2 );
            free( response );
            free( tmp1 );
            return ( ret );
        }
    }

    if ( content->mt_excerpt[0] != NUL ) {
        tmp3 = (char *)malloc( strlen( content->mt_excerpt ) * 5 + 1 );
        if ( !tmp3 ) {
            if ( tmp2 )
                free( tmp2 );
            free( response );
            free( tmp1 );
            return ( ret );
        }

        encodeString( content->mt_excerpt, tmp3 );
        totalLen += strlen( tmp3 );
        if ( totalLen >= SND_BUFFER_SIZE - BUFSIZ ) {
            free( tmp3 );
            if ( tmp2 )
                free( tmp2 );
            free( response );
            free( tmp1 );
            return ( ret );
        }
    }

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( len + MAX_CONTENT_SIZE +
                             content->numOfTrackbacks * MAX_LOGICALLINELEN );
    if ( !buffer ) {
        if ( tmp3 )
            free( tmp3 );
        if ( tmp2 )
            free( tmp2 );
        free( response );
        free( tmp1 );
        return ( ret );
    }

	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>metaWeblog.newPost</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n",
             blogID, userName, password );

    sprintf( buffer + strlen( buffer ),
             "<param>\n<value>\n<struct>\n"
             "<member>\n<name>title</name>\n"
             "<value>\n<string>%s</string>\n</value>\n</member>\n"
             "<member>\n<name>description</name>\n"
             "<value>\n<string>%s</string>\n</value>\n</member>\n",
             content->title, tmp1 );

    if ( content->numOfCategories > 0 ) {
        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>categories</name>\n<value>\n<array>\n" );

        for ( i = 0; i < content->numOfCategories; i++ )
            sprintf( buffer + strlen( buffer ),
                     "<data>\n<value>\n<string>%s</string></value>\n</data>\n",
                     content->categories[i] );

        sprintf( buffer + strlen( buffer ),
                 "</array>\n</value>\n</member>\n" );
    }

    if ( (xmlrpc_p->blogKind != BLOGKIND_DRECOMBLOG_X) &&
         (xmlrpc_p->blogKind != BLOGKIND_YAPLOG_X)        ) {
        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>dateCreated</name>\n<value>\n"
                 "<dateTime.iso8601>%s</dateTime.iso8601>\n"
                 "</value>\n</member>\n",
                 content->dateCreated );
        if ( (xmlrpc_p->blogKind != BLOGKIND_MSNSPACES) &&
             (xmlrpc_p->blogKind != BLOGKIND_WEBRY_X)      ) {
            sprintf( buffer + strlen( buffer ),
                     "<member>\n<name>mt_allow_comments</name>\n"
                     "<value>\n<i4>%d</i4>\n</value>\n</member>\n",
                     content->mt_allow_comments );
            sprintf( buffer + strlen( buffer ),
                     "<member>\n<name>mt_allow_pings</name>\n"
                     "<value>\n<i4>%d</i4>\n</value>\n</member>\n",
                     content->mt_allow_pings );
        }
    }
    else {
        if ( content->dateCreated[0] )
            sprintf( buffer + strlen( buffer ),
                     "<member>\n<name>dateCreated</name>\n<value>\n"
                     "<dateTime.iso8601>%s</dateTime.iso8601>\n"
                     "</value>\n</member>\n",
                     content->dateCreated );
        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_allow_comments</name>\n"
                 "<value>\n<int>%d</int>\n</value>\n</member>\n",
                 content->mt_allow_comments );
        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_allow_pings</name>\n"
                 "<value>\n<int>%d</int>\n</value>\n</member>\n",
                 content->mt_allow_pings );
    }

    if ( (xmlrpc_p->blogKind != BLOGKIND_MSNSPACES) &&
         (xmlrpc_p->blogKind != BLOGKIND_WEBRY_X)      ) {
        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_convert_breaks</name>\n"
                 "<value>\n<string>%s</string>\n</value>\n</member>\n",
                 content->mt_convert_breaks );
        if ( content->mt_text_more[0] )
            sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_text_more</name>\n"
                 "<value>\n<string>%s</string>\n</value>\n</member>\n",
                 tmp2 );
        if ( content->mt_excerpt[0] )
            sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_excerpt</name>\n"
                 "<value>\n<string>%s</string>\n</value>\n</member>\n",
                 tmp3 );
        if ( content->mt_keywords[0] )
            sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_keywords</name>\n"
                 "<value>\n<string>%s</string>\n</value>\n</member>\n",
                 content->mt_keywords );

        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_tb_ping_urls</name>\n"
                 "<value>\n<array>\n" );

        if ( content->numOfTrackbacks > 0 ) {
            for ( i = 0; i < content->numOfTrackbacks; i++ ) {
                sprintf( buffer + strlen( buffer ),
                         "<data>\n<value>\n<string>%s</string>"
                         "</value>\n</data>\n",
                         content->mt_tb_ping_urls[i] );
            }
        }
        else
            sprintf( buffer + strlen( buffer ),
                     "<data/>\n" );

        sprintf( buffer + strlen( buffer ),
                 "</array>\n</value>\n</member>\n" );
    }

	sprintf( buffer + strlen( buffer ),
             "</struct>\n</value>\n</param>\n"
             "<param>\n<value><boolean>%d</boolean></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             publish == TRUE ? 1 : 0 );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL ) {
        if ( !strncmp( response, "<?xml", 5 ) &&
             !strstr( response, "<methodResponse><fault><value>" ) ) {
            /*
             * String   postid
             */
            getSingleString( response, postID );
            if ( postID && *postID )
                ret = TRUE;
        }
    }

    if ( tmp3 )
        free( tmp3 );
    if ( tmp2 )
        free( tmp2 );
    free( response );
    free( tmp1 );
    free( buffer );

    return ( ret );
}


/*
 *  metaWeblog.editPost 
 *      説明: 既にある記事の情報を更新します．
 *      引数: String  postid,
 *            String  username,
 *            String  password,
 *            struct  content,
 *            boolean publish
 *        注意: content 構造体は，次のような標準的な項目を含みます:
 *                  String   title,       記事の件名
 *                  String   description, 記事の本文
 *                  ISO.8601 dateCreated, 記事が投稿された日時． 
 *                  String[] categories,  (省略可) [Windows Live Spaces 用と
 *                                        して、新たに追加されたパラメータ。
 *                                        Movable Type ではこの引数には対応
 *                                        していない]
 *              それに加えて，Movable Type では次の7つの項目に値を入れて渡すこ
 *              とができます．
 *                  int      mt_allow_comments, allow_comments 項目への値; (コ
 *                                              メントを受け入れるか否か)
 *                  int      mt_allow_pings,   allow_pings 項目への値; (トラッ
 *                                             クバックPingを受け入れるか否か)
 *                  String   mt_convert_breaks, convert_breaks 項目の値; (記事
 *                                              本文の改行の扱い方)
 *                  String   mt_text_more,      追記の値; 
 *                  String   mt_excerpt,        概要の値;
 *                  String   mt_keywords,       キーワードの値;
 *                  array    mt_tb_ping_urls,   その記事に対するトラックバック
 *                                              Ping の URL の群れ;
 *             です． dateCreated を使うなら，ISO.8601 形式でないといけません
 *      返り値: 成功すると true が，失敗すると fault が返ります．
 */

BOOL
editPostEx( const char    *postID,  // (I) 記事ID
            const char    *userName,// (I) ユーザ名
            const char    *password,// (I) パスワード
            const CONTENT *content, // (I) 記事情報
            BOOL          publish ) // (I) 投稿状態 (FALSE:下書き / TRUE:公開)
{
    int     ret = FALSE, r, i, totalLen;
    char    *buffer;
    char    response[BUFSIZ * 4];
    int     len = !content ? 0
                           : !(content->description)
                                 ? 0
                                 : strlen( content->description );
    size_t  sz  = BUFSIZ * 4;
    char    *tmp1 = NULL, *tmp2 = NULL, *tmp3 = NULL;

    if ( !postID                                ||
         !(postID[0])                           ||
         (strlen( postID ) >= MAX_POSTIDLENGTH) ||
         (len == 0)                             ||
         (len >= SND_BUFFER_SIZE - BUFSIZ)         )
        return ( ret );

    tmp1 = (char *)malloc( len * 5 + 1 );
    if ( !tmp1 )
        return ( ret );

    encodeString( content->description, tmp1 );
    totalLen = strlen( tmp1 );
    if ( totalLen >= SND_BUFFER_SIZE - BUFSIZ ) {
        free( tmp1 );
        return ( ret );
    }

    if ( content->mt_text_more[0] != NUL ) {
        tmp2 = (char *)malloc( strlen( content->mt_text_more ) * 5 + 1 );
        if ( !tmp2 ) {
            free( tmp1 );
            return ( ret );
        }

        encodeString( content->mt_text_more, tmp2 );
        totalLen += strlen( tmp2 );
        if ( totalLen >= SND_BUFFER_SIZE - BUFSIZ ) {
            free( tmp2 );
            free( tmp1 );
            return ( ret );
        }
    }

    if ( content->mt_excerpt[0] != NUL ) {
        tmp3 = (char *)malloc( strlen( content->mt_excerpt ) * 5 + 1 );
        if ( !tmp3 ) {
            if ( tmp2 )
                free( tmp2 );
            free( tmp1 );
            return ( ret );
        }

        encodeString( content->mt_excerpt, tmp3 );
        totalLen += strlen( tmp3 );
        if ( totalLen >= SND_BUFFER_SIZE - BUFSIZ ) {
            free( tmp3 );
            if ( tmp2 )
                free( tmp2 );
            free( tmp1 );
            return ( ret );
        }
    }

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( len + BUFSIZ * 4 +
                             content->numOfTrackbacks * MAX_LOGICALLINELEN );
    if ( !buffer ) {
        if ( tmp3 )
            free( tmp3 );
        if ( tmp2 )
            free( tmp2 );
        free( tmp1 );
        return ( ret );
    }

	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>metaWeblog.editPost</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n",
             postID, userName, password );

    sprintf( buffer + strlen( buffer ),
             "<param>\n<value>\n<struct>\n"
             "<member>\n<name>title</name>\n"
             "<value>\n<string>%s</string>\n</value>\n</member>\n"
             "<member>\n<name>description</name>\n"
             "<value>\n<string>%s</string>\n</value>\n</member>\n"
             "<member>\n<name>dateCreated</name>\n"
             "<value>\n<dateTime.iso8601>%s</dateTime.iso8601>\n</value>\n"
             "</member>\n",
             content->title, tmp1, content->dateCreated );

    if ( content->numOfCategories > 0 ) {
        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>categories</name>\n<value>\n<array>\n" );

        for ( i = 0; i < content->numOfCategories; i++ )
            sprintf( buffer + strlen( buffer ),
                     "<data>\n<value>\n<string>%s</string></value>\n</data>\n",
                     content->categories[i] );

        sprintf( buffer + strlen( buffer ),
                 "</array>\n</value>\n</member>\n" );
    }

    if ( (xmlrpc_p->blogKind != BLOGKIND_MSNSPACES) &&
         (xmlrpc_p->blogKind != BLOGKIND_WEBRY_X)      ) {
        if ( (xmlrpc_p->blogKind != BLOGKIND_DRECOMBLOG_X) &&
             (xmlrpc_p->blogKind != BLOGKIND_YAPLOG_X)        ) {
            sprintf( buffer + strlen( buffer ),
                     "<member>\n<name>mt_allow_comments</name>\n"
                     "<value>\n<i4>%d</i4>\n</value>\n</member>\n",
                     content->mt_allow_comments );
            sprintf( buffer + strlen( buffer ),
                     "<member>\n<name>mt_allow_pings</name>\n"
                     "<value>\n<i4>%d</i4>\n</value>\n</member>\n",
                     content->mt_allow_pings );
        }
        else {
            char    *p = strstr( buffer, "Z</dateTime.iso8601>" );
            if ( p )
                strcpy( p, p + 1 ); /* {@@} */

            sprintf( buffer + strlen( buffer ),
                     "<member>\n<name>mt_allow_comments</name>\n"
                     "<value>\n<int>%d</int>\n</value>\n</member>\n",
                     content->mt_allow_comments );
            sprintf( buffer + strlen( buffer ),
                     "<member>\n<name>mt_allow_pings</name>\n"
                     "<value>\n<int>%d</int>\n</value>\n</member>\n",
                     content->mt_allow_pings );
        }

        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_convert_breaks</name>\n"
                 "<value>\n<string>%s</string>\n</value>\n</member>\n",
                 content->mt_convert_breaks );
        if ( content->mt_text_more[0] )
            sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_text_more</name>\n"
                 "<value>\n<string>%s</string>\n</value>\n</member>\n",
                 tmp2 );
        if ( content->mt_excerpt[0] )
            sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_excerpt</name>\n"
                 "<value>\n<string>%s</string>\n</value>\n</member>\n",
                 tmp3 );
        if ( content->mt_keywords[0] )
            sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_keywords</name>\n"
                 "<value>\n<string>%s</string>\n</value>\n</member>\n",
                 content->mt_keywords );

        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>mt_tb_ping_urls</name>\n"
                 "<value>\n<array>\n" );

        if ( content->numOfTrackbacks > 0 ) {
            for ( i = 0; i < content->numOfTrackbacks; i++ ) {
                sprintf( buffer + strlen( buffer ),
                         "<data>\n<value>\n<string>%s</string>"
                         "</value>\n</data>\n",
                         content->mt_tb_ping_urls[i] );
            }
        }
        else
            sprintf( buffer + strlen( buffer ),
                     "<data/>\n" );

        sprintf( buffer + strlen( buffer ),
                 "</array>\n</value>\n</member>\n" );
    }

	sprintf( buffer + strlen( buffer ),
             "</struct>\n</value>\n</param>\n"
             "<param>\n<value><boolean>%d</boolean></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             publish == TRUE ? 1 : 0 );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL )
        if ( !strstr( response, "<methodResponse><fault><value>" ) )
            ret = TRUE;

    if ( tmp3 )
        free( tmp3 );
    if ( tmp2 )
        free( tmp2 );
    free( tmp1 );
    free( buffer );

    return ( ret );
}


/*
 *  metaWeblog.getPost 
 *      説明: 指定した投稿についての情報を返します．
 *      引数: String postid,
 *            String username,
 *            String password
 *      返り値: 成功すると，次の要素を含む構造体が返ってきます:
 *                  String   userid,
 *                  ISO.8601 dateCreated,
 *                  String   postid,
 *                  String   description,
 *                  String   title,
 *                  String   link,
 *                  String   permaLink,
 *                  String   mt_excerpt,
 *                  String   mt_text_more,
 *                  int      mt_allow_comments,
 *                  int      mt_allow_pings,
 *                  String   mt_convert_breaks,
 *                  String   mt_keywords;
 *                  String[] categories,  [Windows Live Spaces 用として、新
 *                  bool     publish,      たに追加された要素。Movable Type
 *                                         には存在しない。逆に mt_ で始まる
 *                                         要素は Windows Live Spaces では存
 *                                         在しない]
 *              失敗すると，fault が返ります．
 *          注意: link と permaLink は，どちらも 蓄積されている記事への URL
 *                になります． 
 *                mt_ではじまっている項目は，metaWeblog.getPost API に Movable
 *                Type が追加したものです．
 */

BOOL
getPost( const char   *postID,      // (I) 記事ID
         const char   *userName,    // (I) ユーザ名
         const char   *password,    // (I) パスワード
         CONTENTINFEX *contentInfo )// (I) 記事情報
{
    int     ret = FALSE, r, r2;
    char    buffer[BUFSIZ];
    char    *response;
    int     numOfContents = 0;
    size_t  sz  = 128 * 1024;

    if ( !postID || !(postID[0]) || !contentInfo )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    response[0] = NUL;
    memset( contentInfo, 0x00, sizeof ( CONTENTINFEX ) );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>metaWeblog.getPost</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             postID, userName, password );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPostEx( buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * String   userid,            (Windows Live Spaces では存在しない)
         * ISO.8601 dateCreated,
         * String   postid,
         * String   description,
         * String   title,
         * String   link,
         * String   permaLink,         (Windows Live Spaces では存在しない)
         * String   mt_excerpt, (mt拡張: このフィールドが存在するとは限らない)
         * String   mt_text_more,      (mt拡張)
         * int      mt_allow_comments, (mt拡張)
         * int      mt_allow_pings,    (mt拡張)
         * String   mt_convert_breaks, (mt拡張)
         * String   mt_keywords;       (mt拡張)
         * String[] categories;        (Windows Live Spaces拡張)
         * boolean  publish;           (Windows Live Spaces拡張)
         */
        char    *p = response;
        char    *q = strstr( p, "<param>" );
        int     cnt = 0;

        if ( q ) {
            q += 7;
            while ( *q ) {
                if ( !strncmp( q, "</struct>", 9 ) &&
                     !strstr( q, "<param>" )          )
                     break;

                /* 必須フィールド */
                r = getDateCreated( &q,
                                    &(contentInfo[numOfContents].yy),
                                    &(contentInfo[numOfContents].mm),
                                    &(contentInfo[numOfContents].dd),
                                    &(contentInfo[numOfContents].HH),
                                    &(contentInfo[numOfContents].MM),
                                    &(contentInfo[numOfContents].SS),
                                    &cnt, 13,
                                    &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getUserid( &q,
                               contentInfo[numOfContents].userid,
                               &cnt, 13,
                               &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getPostid( &q,
                               contentInfo[numOfContents].postid,
                               &cnt, 13,
                               &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getDescription( &q,
                                    contentInfo[numOfContents].description,
                                    &cnt, 13,
                                    &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getTitle( &q,
                              contentInfo[numOfContents].title,
                              &cnt, 13,
                              &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getLink( &q,
                             contentInfo[numOfContents].link,
                             &cnt, 13,
                             &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getPermaLink( &q,
                                  contentInfo[numOfContents].permaLink,
                                  &cnt, 13,
                                  &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                /* 省略可能フィールド (MovableType独自拡張) */
                r = getExcerpt( &q,
                                contentInfo[numOfContents].mt_excerpt,
                                &cnt, 13,
                                &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getExtended( &q,
                                 contentInfo[numOfContents].mt_text_more,
                                 &cnt, 13,
                                 &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getAllowComments( &q,
                              &(contentInfo[numOfContents].mt_allow_comments),
                                      &cnt, 13,
                                      &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getAllowPings( &q,
                                 &(contentInfo[numOfContents].mt_allow_pings),
                                   &cnt, 13,
                                   &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getConvertLineBreaks( &q,
                                 contentInfo[numOfContents].mt_convert_breaks,
                                          &cnt, 13,
                                          &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getKeywords( &q,
                                 contentInfo[numOfContents].mt_keywords,
                                 &cnt, 13,
                                 &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                /* Windows Live Spaces 独自拡張 */
                r = getPublish( &q,
                                &(contentInfo[numOfContents].publish),
                                &cnt, 13,
                                &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r2 = getArrayCategories(
                        &q,
                        (char **)contentInfo[numOfContents].categories,
                        &(contentInfo[numOfContents].numOfCategories) );
                if ( r2 > 0 ) {
                    r++;
                    if ( r == 13 ) {
                        cnt = 0;
                        continue;
                    }
                }

                q++;
            }

            ret = TRUE;
        }
    }

    free( response );

    return ( ret );
}


/*
 *  metaWeblog.getRecentPosts 
 *      説明: 最近投稿された記事の群れを返します．
 *      引数: String blogid,
 *            String username,
 *            String password,
 *            int    numberOfPosts
 *      返り値: 成功すると，次の要素を含む構造体が返ってきます． 
 *                  ISO.8601 dateCreated,
 *                  String   userid,
 *                  String   postid,
 *                  String   description,
 *                  String   title,
 *                  String   link,
 *                  String   permaLink, 
 *                  String   mt_excerpt,
 *                  String   mt_text_more,
 *                  int      mt_allow_comments,
 *                  int      mt_allow_pings,
 *                  String   mt_convert_breaks,
 *                  String   mt_keywords;
 *                  String[] categories,  [Windows Live Spaces 用として、新
 *                  bool     publish,      たに追加された要素。Movable Type
 *                                         には存在しない。逆に mt_ で始まる
 *                                         要素は Windows Live Spaces では存
 *                                         在しない]
 *              失敗すると，fault が返ります．
 *          注意: dateCreated は，blogid の weblog においての時間帯になって
 *                います． 
 *                link と permaLink は，どちらも 蓄積されている記事への URL
 *                になります．
 */

int
getRecentPostsEx( const char   *blogID,         // (I) 記事ID
                  const char   *userName,       // (I) ユーザ名
                  const char   *password,       // (I) パスワード
                  int          *numberOfPosts,  // (I) 取得する記事の数
                                                // (O) 実際に取得した記事の数
                  CONTENTINFEX *contentInfo )   // (O) 取得した記事情報
{
    int     r, r2;
    char    buffer[BUFSIZ];
    char    *response;
    int     numOfContents = 0;
    size_t  sz;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !numberOfPosts                        ||
         (*numberOfPosts <= 0)                 ||
         !contentInfo                             )
        return ( numOfContents );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    sz = 65536 * *numberOfPosts;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfContents );

    memset( contentInfo, 0x00, sizeof ( CONTENTINFEX ) * *numberOfPosts );
    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
          XML_STATEMENT
          "<methodCall>\n<methodName>metaWeblog.getRecentPosts</methodName>\n"
          "<params>\n"
          "<param>\n<value><string>%s</string></value>\n</param>\n"
          "<param>\n<value><string>%s</string></value>\n</param>\n"
          "<param>\n<value><string>%s</string></value>\n</param>\n"
          "<param>\n<value><i4>%d</i4></value>\n</param>\n"
          "</params>\n"
          "</methodCall>\n\n",
             blogID, userName, password, *numberOfPosts );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPostEx( buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * String   userid,
         * ISO.8601 dateCreated,
         * String   postid,
         * String   description,
         * String   title,
         * String   link,
         * String   permaLink,         (Windows Live Spaces では存在しない)
         * String   mt_excerpt, (mt拡張: このフィールドが存在するとは限らない)
         * String   mt_text_more,      (mt拡張)
         * int      mt_allow_comments, (mt拡張)
         * int      mt_allow_pings,    (mt拡張)
         * String   mt_convert_breaks, (mt拡張)
         * String   mt_keywords;       (mt拡張)
         * String[] categories;        (Windows Live Spaces拡張)
         * boolean  publish;           (Windows Live Spaces拡張)
         */
        char    *p = response;
        char    *q = strstr( p, "<param>" );
        int     cnt = 0;

        if ( q ) {
            q += 7;
            while ( *q ) {
                if ( !strncmp( q, "</data>", 7 ) ) {
                    q += 7;
                    if ( r < 13 ) {
                        numOfContents++;
                        cnt = 0;
                    }
                }

                if ( !strstr( q, "<name>" ) )
                    break;
                if ( numOfContents >= *numberOfPosts )
                    break;
                if ( !strncmp( q, "</struct>", 9 ) ) {
                    char    *r;
                    r = strstr( q, "<struct>" );
                    if ( r )
                        q = r + 8;
                }

                /* 必須フィールド */
                r = getDateCreated( &q,
                                    &(contentInfo[numOfContents].yy),
                                    &(contentInfo[numOfContents].mm),
                                    &(contentInfo[numOfContents].dd),
                                    &(contentInfo[numOfContents].HH),
                                    &(contentInfo[numOfContents].MM),
                                    &(contentInfo[numOfContents].SS),
                                    &cnt, 13,
                                    &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getUserid( &q,
                               contentInfo[numOfContents].userid,
                               &cnt, 13,
                               &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getPostid( &q,
                               contentInfo[numOfContents].postid,
                               &cnt, 13,
                               &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getDescription( &q,
                                    contentInfo[numOfContents].description,
                                    &cnt, 13,
                                    &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getTitle( &q,
                              contentInfo[numOfContents].title,
                              &cnt, 13,
                              &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getLink( &q,
                             contentInfo[numOfContents].link,
                             &cnt, 13,
                             &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getPermaLink( &q,
                                  contentInfo[numOfContents].permaLink,
                                  &cnt, 13,
                                  &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                /* 省略可能フィールド (MovableType独自拡張) */
                r = getExcerpt( &q,
                                contentInfo[numOfContents].mt_excerpt,
                                &cnt, 13,
                                &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getExtended( &q,
                                 contentInfo[numOfContents].mt_text_more,
                                 &cnt, 13,
                                 &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getAllowComments( &q,
                              &(contentInfo[numOfContents].mt_allow_comments),
                                      &cnt, 13,
                                      &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getAllowPings( &q,
                                 &(contentInfo[numOfContents].mt_allow_pings),
                                   &cnt, 13,
                                   &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getConvertLineBreaks( &q,
                                 contentInfo[numOfContents].mt_convert_breaks,
                                          &cnt, 13,
                                          &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r = getKeywords( &q,
                                 contentInfo[numOfContents].mt_keywords,
                                 &cnt, 13,
                                 &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                /* Windows Live Spaces 独自拡張 */
                r = getPublish( &q,
                                &(contentInfo[numOfContents].publish),
                                &cnt, 13,
                                &numOfContents );
                if ( r == 13 ) {
                    cnt = 0;
                    continue;
                }

                r2 = getArrayCategories(
                        &q,
                        (char **)contentInfo[numOfContents].categories,
                        &(contentInfo[numOfContents].numOfCategories) );
                if ( r2 > 0 ) {
                    r++;
                    if ( r == 13 ) {
                        cnt = 0;
                        continue;
                    }
                }

                q++;
            }
        }
    }

    free( response );
    *numberOfPosts = numOfContents;

    return ( numOfContents );
}

/*
 *  metaWeblog.newMediaObject 
 *      説明: ファイルを webサーバに転送します．
 *      引数: String blogid,
 *            String username,
 *            String password,
 *            struct file
 *          注意: file 構造体には，2つの項目があります:
 *                    base64 bits (the base64 で符号化された，ファイルの中身)
 *                    String name (ファイル名 ). 
 *                type 項目 (ファイルの種類) は，今のところ無視されます．
 *      返り値: 転送したファイルへの URL が返ってきます．
 */

BOOL
newMediaObject( const char *blogID,     // (I) blog ID
                const char *userName,   // (I) ユーザ名
                const char *password,   // (I) パスワード
                FILEINF    *fileInf,    // (I) アップロードするファイルに関す
                                        //     る情報
                char       *url )       // (O) アップロードしたファイルの URL
{
    int     ret  = FALSE, r;
    char    *buffer, *p;
    char    response[BUFSIZ * 4];
    long    size = 0;
    size_t  sz   = BUFSIZ * 4;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !fileInf                              ||
         !url                                     )
        return ( ret );

    size = strlen( (char *)(fileInf->bits) );
    buffer = (char *)malloc( size * sizeof ( char ) + 1024 );
    if ( !buffer ) {
        fputs( "newMediaObject: memory exhausted.\n", stderr );
        return ( ret );
    }

    if ( xmlrpc_p->verbose )
        dprintf( "newMediaObject: アップロードしようとしているファイル"
                 " → %s\n",
                 fileInf->name );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

	sprintf( buffer,
             XML_STATEMENT
          "<methodCall>\n<methodName>metaWeblog.newMediaObject</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n",
             blogID, userName, password );
    sprintf( buffer + strlen( buffer ),
             "<param>\n<value>\n<struct>\n"
             "<member>\n<name>bits</name>\n"
             "<value>\n<base64>%s</base64>\n</value>\n"
             "</member>\n"
             "<member>\n<name>name</name>\n"
             "<value>\n<string>%s</string>\n</value>\n"
             "</member>\n"
             "</struct>\n</value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             fileInf->bits, fileInf->name );

    setUpReceiveBuffer( response, sz ); /* {@@} */

    setTimeoutTime( DEFAULT_HTTP_TIMEOUT *
                    (1 + (strlen((char *)(fileInf->bits)) / (1024 * 1024))) );
                                    // サイズに比例したタイムアウト時間を設定
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT ); // デフォルト値に戻しておく

    if ( response[0] != NUL ) {
        if ( xmlrpc_p->verbose )
            dputs( "newMediaObject: リクエスト発行成功\n" );

        if ( strstr( response, "<methodResponse><fault><value>" ) ) {
            if ( strstr( response, "ERROR" ) ||
                 strstr( response, "error" )    )
                if ( strstr( response,
                             "The request or reply is too large." ) )
                    fprintf( stderr,
                     "アップロードしようとしているファイルが大きすぎます\n" );
            fprintf( stderr, "アップロードに失敗しました\n" );
            if ( xmlrpc_p->verbose )
                dputs( "newMediaObject: アップロード失敗 "
                       "(ファイルが大きすぎる?)\n" );
        }
        else {
            p = strstr( response, "<name>" );
            if ( p ) {
                p = strstr( p + 1, "url" );
                if ( p ) {
                    p = strstr( p + 1, "</name>" );
                    if ( p )
                        p = strstr( p + 1, "http:" );
                }
            }
            if ( !p || strstr( response, "faultString" ) ) {
                fprintf( stderr, "アップロードに失敗しました\n" );
                if ( xmlrpc_p->verbose )
                    dputs( "newMediaObject: アップロード失敗 "
                           "(サーバからエラー応答受信)\n" );
            }
            else {
                ret = TRUE;

                /*
                 * String   url
                 */
                getSingleString( response, url );
                if ( xmlrpc_p->verbose )
                    dputs( "newMediaObject: アップロード成功\n" );
            }
        }
    }

    free( buffer );

    return ret;
}


/*
 *  Movable Type API
 */

/*
 *  mt.getRecentPostTitles 
 *      説明: 最近投稿された記事の群れを，帯域にやさしく返します．
 *      引数: String blogid,
 *            String username,
 *            String password,
 *            int    numberOfPosts
 *      返り値: 成功すると，次の要素を含む構造体の配列が返ってきます:
 *                  ISO.8601 dateCreated,
 *                  String   userid,
 *                  String   postid,
 *                  String   title; 
 *              失敗すると，faultが返ります．
 *          注意: dateCreated は，blogid の weblog においての時間帯になって
 *                います．
 */

int
getRecentPostTitles( const char *blogID,        // (I) blog ID
                     const char *userName,      // (I) ユーザ名
                     const char *password,      // (I) パスワード
                     int        *numberOfPosts, // (I) 取得する記事情報の数
                                                // (O) 実際に取得した記事情報
                                                //     の数
                     POSTINF    *postinf )      // (O) 取得した記事情報
{
    int     ret = FALSE;
    char    buffer[BUFSIZ];
    char    *response;
    int     numOfPosts = 0;
    size_t  sz;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !numberOfPosts                        ||
         (*numberOfPosts <= 0)                 ||
         !postinf                                 )
        return ( numOfPosts );

    sz = (*numberOfPosts + 1) * BUFSIZ;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfPosts );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>mt.getRecentPostTitles</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><i4>%d</i4></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             blogID, userName, password, *numberOfPosts );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    ret = httpPostEx( buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * ISO.8601 dateCreated,
         * String   userid,
         * String   postid,
         * String   title; 
         */
        char    *p = response;
        char    *q = strstr( p, "<array>" );
        int     cnt = 0;

        if ( q ) {
            q += 7;
            while ( *q ) {
                if ( !strstr( q, "<name>" ) )
                    break;
                if ( numOfPosts >= *numberOfPosts )
                    break;

                ret = getDateCreated( &q,
                                      &(postinf[numOfPosts].yy),
                                      &(postinf[numOfPosts].mm),
                                      &(postinf[numOfPosts].dd),
                                      &(postinf[numOfPosts].HH),
                                      &(postinf[numOfPosts].MM),
                                      &(postinf[numOfPosts].SS),
                                      &cnt, 4,
                                      &numOfPosts );
                if ( ret == 4 ) {
                    cnt = 0;
                    continue;
                }

                ret = getUserid( &q,
                                 postinf[numOfPosts].userid,
                                 &cnt, 4,
                                 &numOfPosts );

                if ( ret == 4 ) {
                    cnt = 0;
                    continue;
                }

                ret = getPostid( &q,
                                 postinf[numOfPosts].postid,
                                 &cnt, 4,
                                 &numOfPosts );

                if ( ret == 4 ) {
                    cnt = 0;
                    continue;
                }

                ret = getTitle( &q,
                                 postinf[numOfPosts].title,
                                 &cnt, 4,
                                 &numOfPosts );

                if ( ret == 4 ) {
                    cnt = 0;
                    continue;
                }

                q++;
            }
        }
    }

    free( response );
    *numberOfPosts = numOfPosts;

    return ( numOfPosts );
}


/*
 *  mt.getCategoryList 
 *      説明: その weblog にあるすべての分類を返します．
 *      引数: String blogid,
 *            String username,
 *            String password
 *      返り値: 成功すると，次の要素を含む構造体の配列が返ってきます:
 *                  String categoryId
 *                  String categoryName;
 *              失敗すると，fault が返ります．
 */

int
getCategoryList( const char   *blogID,          // (I) blog ID
                 const char   *userName,        // (I) ユーザ名
                 const char   *password,        // (I) パスワード
                 long         *numOfCategories, // (I) 取得するカテゴリの数
                                                // (O) 取得したカテゴリの数
                 CATLISTINF_t categories )      // (O) 取得したカテゴリ情報
{
    int     ret = 0;
    int     num = 0;
    char    buffer[BUFSIZ];
    char    *response;
    size_t  sz;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !numOfCategories                      ||
         (*numOfCategories <= 0)               ||
         !categories                              )
        return ( num );

    sz = (*numOfCategories + 1) * BUFSIZ;
    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>mt.getCategoryList</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             blogID, userName, password );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    ret = httpPostEx( buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * String categoryId
         * String categoryName
         */
        char    *p = response;
        char    *q = strstr( p, "<array>" );
        int     cnt = 0;

        if ( q ) {
            q += 7;
            while ( *q ) {
                ret = getCategoryId( &q,
                                     categories[num].categoryId,
                                     &cnt, 2,
                                     &num );

                if ( ret == 2 ) {
                    if ( num >= *numOfCategories )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getCategoryName( &q,
                                       categories[num].categoryName,
                                       &cnt, 2,
                                       &num );

                if ( ret == 2 ) {
                    if ( num >= *numOfCategories )
                        break;
                    cnt = 0;
                    continue;
                }

                q++;
            }
        }
    }

    free( response );
    *numOfCategories = num;

    return ( num );
}


/*
 *  mt.getPostCategories 
 *      説明: その投稿に指定されてある分類をすべて返します．
 *      引数: String postid,
 *            String username,
 *            String password
 *      返り値: 成功すると，次の要素を含む構造体の配列が返ってきます:
 *                  String  categoryName,
 *                  String  categoryId,
 *                  boolean isPrimary; 
 *              失敗すると，fault が返ります．
 *          注意: isPrimary は，分類がその分類の第一分類かどうか，ということを
 *                意味します．
 */

int
getPostCategories( const char *postID,             // (I) 記事ID
                   const char *userName,           // (I) ユーザ名
                   const char *password,           // (I) パスワード
                   long       *numberOfCategories, // (I) 取得するカテゴリの数
                                                   // (O) 取得したカテゴリの数
                   CATINF     *categories )        // (O) 取得したカテゴリ情報
{
    int     ret = FALSE;
    char    buffer[BUFSIZ];
    char    *response;
    int     numOfCategories = 0;
    size_t  sz;

    if ( !postID                                ||
         !(postID[0])                           ||
         (strlen( postID ) >= MAX_POSTIDLENGTH) ||
         !numberOfCategories                    ||
         (*numberOfCategories <= 0)             ||
         !categories                               )
        return ( numOfCategories );

    sz = (*numberOfCategories + 1) * BUFSIZ;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfCategories );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>mt.getPostCategories</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             postID, userName, password );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    ret = httpPostEx( buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * String categoryId
         * String categoryName
         * boolean isPrimary; 
         */
        char    *p = response;
        char    *q = strstr( p, "<array>" );
        int     cnt = 0;

        if ( q ) {
            q += 7;
            while ( *q ) {
                ret = getCategoryId( &q,
                                     categories[numOfCategories].categoryId,
                                     &cnt, 3,
                                     &numOfCategories );
                if ( ret == 3 ) {
                    if ( numOfCategories >= *numberOfCategories )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getCategoryName( &q,
                                     categories[numOfCategories].categoryName,
                                       &cnt, 3,
                                       &numOfCategories );
                if ( ret == 3 ) {
                    if ( numOfCategories >= *numberOfCategories )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getIsPrimary( &q,
                                    &(categories[numOfCategories].isPrimary),
                                    &cnt, 3,
                                    &numOfCategories );
                if ( ret == 3 ) {
                    if ( numOfCategories >= *numberOfCategories )
                        break;
                    cnt = 0;
                    continue;
                }

                q++;
            }
        }
    }

    free( response );
    *numberOfCategories = numOfCategories;

    return ( numOfCategories );
}

/*
 *  mt.setPostCategories 
 *      説明: 記事の分類を設定します．
 *      引数: String postid,
 *            String username,
 *            String password,
 *            array  categories
 *          注意: categories は，次の要素を含む構造体の配列です:
 *                    String  categoryId，
 *                    boolean isPrimary． 
 *                isPrimary を使い，第一分類を指定することも可能です． 
 *                このフラグを指定しなければ，配列のひとつめの要素が，その記事
 *                の第一分類になります．
 *      返り値: 成功すると true が，失敗すると fault が返ります．
 */

BOOL
setPostCategories( const char *postID,          // (I) 記事ID 
                   const char *userName,        // (I) ユーザ名
                   const char *password,        // (I) パスワード
                   long       numOfCategories,  // (I) 設定するカテゴリの数
                   CATEGORY   *categories )     // (I) 設定するカテゴリ情報
{
    int         ret = FALSE, r, i;
    char        *buffer;
    char        response[BUFSIZ * 4];
    CATEGORY_t  cat;
    size_t      sz  = BUFSIZ * 4;

    if ( !postID                                ||
         !(postID[0])                           ||
         (strlen( postID ) >= MAX_POSTIDLENGTH) ||
         (numOfCategories <= 0)                 ||
         !categories                               )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( numOfCategories * BUFSIZ + BUFSIZ );
    if ( !buffer )
        return ( ret );

	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>mt.setPostCategories</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n",
             postID, userName, password );

    sprintf( buffer + strlen( buffer ),
             "<param>\n<value>\n<array>\n" );

    for ( i = 0; i < numOfCategories; i++ ) {
        cat = &(categories[i]);
        sprintf( buffer + strlen( buffer ),
                 "<data>\n<value>\n<struct>\n<member>\n"
                 "<name>categoryId</name>\n"
                 "<value><string>%s</string></value>\n"
                 "</member>\n",
                 cat->categoryId );
        sprintf( buffer + strlen( buffer ),
                 "<member>\n<name>isPrimary</name>\n"
                 "<value><boolean>%d</boolean></value>\n"
                 "</member>\n"
                 "</struct>\n</value>\n</data>\n",
                 cat->isPrimary == TRUE ? 1 : 0 );
    }

    sprintf( buffer + strlen( buffer ),
             "</array>\n</value>\n</param>\n" );

	sprintf( buffer + strlen( buffer ),
             "</params>\n"
             "</methodCall>\n\n" );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL )
        if ( !strstr( response, "<methodResponse><fault><value>" ) )
            ret = TRUE;

    free( buffer );

    return ( ret );
}


/*
 *  mt.supportedMethods 
 *      説明: サーバで提供されている XML-RPC の呼び出し方法を取得します．
 *      引数: なし
 *      返り値: サーバで提供されている呼び出し方法の配列が返ります．
 */

int
getSupportedMethods( int  *numberOfMethods, // (I) 取得する呼び出し方法の数
                                            // (O) 取得した呼び出し方法の数
                     char *methodList[] )   // (O) 取得した呼び出し方法の一覧
{
    int     r;
    int     numOfMethods = 0;
    char    buffer[BUFSIZ];
    char    *response;
    size_t  sz;

    if ( !numberOfMethods        ||
         !(numberOfMethods[0])   ||
         (*numberOfMethods <= 0) ||
         !methodList                )
        return ( numOfMethods );

    sz = (*numberOfMethods + 1) * BUFSIZ;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfMethods ); 

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>mt.supportedMethods</methodName>\n"
             "<params />\n"
             "</methodCall>\n\n" );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        char    *p = response;
        char    *q = strstr( p, "<array>" );
        char    *s, *t;

        if ( q ) {
            q += 7;
            while ( *q ) {
                if ( ( s = strstr( q, "<string>" ) ) != NULL ) {
                    s += 8;
                    if ( ( t = strstr( s, "</string>" ) ) != NULL ) {
                        strncpy( methodList[numOfMethods], s, t - s );
                        methodList[numOfMethods][t - s] = NUL;
                        numOfMethods++;
                        q = t + 9;
                        if ( numOfMethods >= *numberOfMethods )
                            break;
                        continue;
                    }
                }

                q++;
            }
        }
    }

    free( response );
    *numberOfMethods = numOfMethods;

    return ( numOfMethods );
}


/*
 *  mt.supportedTextFilters 
 *      説明: サーバで提供されている文書整形プラグインに関する情報を取得します．
 *      引数: なし
 *      返り値: String key
 *              String label
 *              を含む構造体の配列がかえってきます． 
 *              key は，文書整形プラグインを区別する一意な文字列で，label は，
 *              それを読めるかたちにした説明です． 
 *              key は，newPostとeditPostに mt_convert_breaks変数として渡され
 *              るべき値です．
 */

int
getSupportedFilters( int       *numberOfFilters,// (I) 取得するフィルタの数
                                                // (O) 取得したフィルタの数
                     FILTERINF *filterList )    // (O) 取得したフィルタ情報
{
    int     ret, r;
    char    buffer[BUFSIZ];
    char    *response;
    int     numOfFilters = 0;
    size_t  sz;

    if ( !numberOfFilters        ||
         !(numberOfFilters[0])   ||
         (*numberOfFilters <= 0) ||
         !filterList                )
        return ( numOfFilters );

    sz = (*numberOfFilters + 1) * BUFSIZ;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfFilters );

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>mt.supportedTextFilters</methodName>\n"
             "<params />\n"
             "</methodCall>\n\n" );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * String key
         * String label
         */
        char    *p = response;
        char    *q = strstr( p, "<array>" );
        int     cnt = 0;

        if ( q ) {
            q += 7;
            while ( *q ) {
                ret = getKey( &q,
                              filterList[numOfFilters].key,
                              &cnt, 2,
                              &numOfFilters );
                if ( ret == 2 ) {
                    if ( numOfFilters >= *numberOfFilters )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getLabel( &q,
                                filterList[numOfFilters].label,
                                &cnt, 2,
                                &numOfFilters );
                if ( ret == 2 ) {
                    if ( numOfFilters >= *numberOfFilters )
                        break;
                    cnt = 0;
                    continue;
                }

                q++;
            }
        }
    }

    free( response );
    *numberOfFilters = numOfFilters;

    return ( numOfFilters );
}


/*
 *  mt.getTrackbackPings 
 *      説明: 指定した記事に送られた トラックバック Ping の群れを取得します． 
 *            これを使うのは，指定した記事への Ping の群れをプログラムとかが
 *            取得して，それらの Ping それぞれに，同じ処理を順番に行うような
 *            場合でしょう． 
 *            たとえば，ある話題についての記事とそれに言及している記事から成
 *            る web グラフを作り上げるような場合，みたいな．
 *      引数: String postid
 *      返り値: 次の要素を含む構造体の配列が返ってきます: 
 *                  String pingTitle (Ping してきた記事の件名),
 *                  String pingURL (記事の URL),
 *                  String pingIP (Ping してきたホストの IP アドレス)．
 */

int
getTrackbackPings(
        const char *postID,         // (I) 記事ID
        int        *numberOfPings,  // (I) 取得するトラックバック情報数
                                    // (O) 取得したトラックバック情報数
        TBINF      *tbInfo          // (O) 取得したトラックバック情報
    )
{
    int     ret = FALSE;
    char    buffer[BUFSIZ];
    char    *response;
    int     numOfPings = 0;
    int     cnt;
    char    *p, *q;
    size_t  sz;

    if ( !postID                               ||
         !(postID[0])                          ||
         (strlen(postID) >= MAX_POSTIDLENGTH ) ||
         !numberOfPings                        ||
         !(numberOfPings[0])                   ||
         (*numberOfPings <= 0)                 ||
         !tbInfo                                  )
        return ( numOfPings );

    sz = (*numberOfPings + 1) * BUFSIZ;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfPings );

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>mt.getTrackbackPings</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             postID );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    ret = httpPostEx( buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        p = strstr( response, "<struct>" );
        if ( !p                             ||
             strstr( response, "<data />" ) ||
             strstr( response, "<data/>"  )    ) {
            /* トラックバックなし */
            free( response );
            *numberOfPings = numOfPings;

            return ( numOfPings );
        }

        /* トラックバックあり */
        while ( p ) {
            q = p + 8;
            cnt = 0;

            while ( *q ) {
                if ( numOfPings >= *numberOfPings )
                    break;

                ret = getPingUrl( &q,
                                  tbInfo[numOfPings].pingURL,
                                  &cnt, 3,
                                  &numOfPings );
                if ( ret == 3 )
                    break;

                ret = getPingTitle( &q,
                                    tbInfo[numOfPings].pingTitle,
                                    &cnt, 3,
                                    &numOfPings );
                if ( ret == 3 )
                    break;

                ret = getPingIP( &q,
                                 tbInfo[numOfPings].pingIP,
                                 &cnt, 3,
                                 &numOfPings );
                if ( ret == 3 )
                    break;

                q++;
            }

            p = strstr( q, "<struct>" );
        }
    }

    free( response );
    *numberOfPings = numOfPings;

    return ( numOfPings );
}


/*
 *  mt.publishPost 
 *      説明: weblog にあるすべての静的ファイルを公開 (再構築) します． 
 *            これは，システムに記事を投稿し，保存することとおなじことです．
 *            (違うのは，この方法だと Ping を行わない，ということです)．
 *      引数: String postid,
 *            String username,
 *            String password
 *      返り値: 成功すると true が，失敗すると fault が返ります．
 */

BOOL
publishPost( const char *postID,    // (I) 記事ID
             const char *userName,  // (I) ユーザ名
             const char *password ) // (I) パスワード
{
    int     ret = FALSE, r;
    char    buffer[BUFSIZ];
    char    response[BUFSIZ * 8];   /* ココログでエラー発生時に3000byte強の */
    size_t  sz  = BUFSIZ * 8;       /* 応答が返ってくることがあるため、大き */
                                    /* めに確保している                     */
    if ( !postID                               ||
         !(postID[0])                          ||
         (strlen(postID) >= MAX_POSTIDLENGTH )    )
        return ( ret );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>mt.publishPost</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             postID, userName, password );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );

    if ( response[0] != NUL )
        if ( !strstr( response, "<methodResponse><fault><value>" ) )
            ret = TRUE;

    return ( ret );
}

/*
 *  metaWeblog.getCategories
 *      引数: blogid, username, password
 *              Windows Live Spaces では
 *                - blogid は常に "MyBlog" を指定する
 *                - username は Space名(ブログのURL中のブログ毎にユニークな
 *                  文字列部分)を指定する
 *      返り値: カテゴリの数分、以下の内容の構造体を返す。
 *                  description,
 *                  htmlUrl,
 *                  rssUrl
 *
 *              ただし、Windows Live Spaces (および ウェブリブログ)では、
 *              以下の内容の構造体を返す
 *                  description,
 *                  title,
 *              (description と title には、ともに「カテゴリ名」が格納される)
 */

int
getCategories( const char   *blogID,
               const char   *userName,
               const char   *password,
               long         *numOfCategories, /* カテゴリの数 */
               CATEGORIES_t categories )      /* カテゴリ     */
{
    int     numberOfCategories = 0;
    int     ret, r;
    char    buffer[BUFSIZ];
    char    *response;
    size_t  sz  = 128 * 1024;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !numOfCategories                      ||
         (*numOfCategories <= 0)               ||
         !categories                              )
        return ( numberOfCategories );

    sz = (*numOfCategories + 1) * BUFSIZ;
    response = (char *)malloc( sz );
    if ( !response )
        return ( numberOfCategories );

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    memset( buffer, NUL, BUFSIZ );
	sprintf( buffer,
             XML_STATEMENT
             "<methodCall>\n<methodName>metaWeblog.getCategories</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             blogID, userName, password );

    setUpReceiveBuffer( response, sz );
    r = httpPostEx( buffer, response );

    if ( (response[0] != NUL) &&
         !strstr( response, "<methodResponse><fault><value>" ) ) {
        /*
         * String description
         * String title
         */
        char    *p = response;
        char    *q = strstr( p, "<array>" );
        int     cnt = 0;

        if ( q ) {
            q += 7;
            while ( *q ) {
                ret = getDescription(
                        &q,
                        categories[numberOfCategories].categoryDescription,
                        &cnt, 2,
                        &numberOfCategories );
                if ( ret == 2 ) {
                    if ( numberOfCategories >= *numOfCategories )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getTitle( &q,
                                categories[numberOfCategories].categoryTitle,
                                &cnt, 2,
                                &numberOfCategories );
                if ( ret == 2 ) {
                    if ( numberOfCategories >= *numOfCategories )
                        break;
                    cnt = 0;
                    continue;
                }

                q++;
            }
        }
    }

    free( response );

    return ( numberOfCategories );
}


/*
 * XML-RPC API を利用したユーティリティ関数群
 */

/*
 * blog ID の取得
 *    引数:   ユーザ名, パスワード, 取得した blog 情報格納場所
 *    戻り値: 取得に成功した場合 TRUE、失敗した場合 FALSE
 */

int
getBlogID( const char *userName,    // (I) ユーザ名
           const char *password,    // (I) パスワード
           char       *blogID )     // (O) 最初に見つかった blog ID
{
    int     ret = FALSE;
    char    *response;
    size_t  sz;

    if ( !blogID )
        return ( ret );

    sz = 10240 * 20 * sizeof ( char );
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    ret = getUsersBlogs( userName, password, response );

    if ( ret == TRUE ) {
        char    *p = response;
        char    *q = strstr( p, "blogid" );
        char    *r;

        /*
         * String   blogid
         */

        if ( q ) {
            p = q + 6;
            q = strstr( p, "<string>" );
            if ( q ) {
                q += 8;
                r = strstr( q, "</string>" );
                if ( r ) {
                    strncpy( blogID, q, r - q );
                    blogID[r - q] = NUL;
                }
            }
        }
    }
    else
        ret = FALSE;

    free( response );

    return ( ret );
}

/*
 * blog ID の取得
 *    引数:   ユーザ名, パスワード, 取得した blog 情報格納場所
 *    戻り値: システム内に存在する blog の数
 */

int
getBlogIDs( const char *userName,       // (I) ユーザ名
            const char *password,       // (I) パスワード
            int        *numberOfBlogs,  // (I/O) blog 情報数
            BLOGINF    *blogInfo )      // (O) blog 情報
{
    int     ret        = FALSE;
    int     cnt        = 0;
    int     numOfBlogs = 0;
    char    *response;
    size_t  sz;

    if ( !numberOfBlogs || (*numberOfBlogs <= 0) || !blogInfo )
        return ( numOfBlogs );

    sz = 10240 * (*numberOfBlogs) * sizeof ( char );
    response = (char *)malloc( sz );
    if ( !response )
        return ( numOfBlogs );

    setUpReceiveBuffer( response, sz ); /* {@@} */
    ret = getUsersBlogs( userName, password, response );

    if ( ret == TRUE ) {
        /*
         * String url,
         * String blogid,
         * String blogName
         */
        char    *p = response;
        char    *q = strstr( p, "<array>" );

        if ( q ) {
            q += 7;
            while ( *q ) {
                ret = getUrl( &q,
                              blogInfo[numOfBlogs].url,
                              &cnt, 3,
                              &numOfBlogs );
                if ( ret == 3 ) {
                    if ( numOfBlogs >= *numberOfBlogs )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getBlogid( &q,
                                 blogInfo[numOfBlogs].blogID,
                                 &cnt, 3,
                                 &numOfBlogs );
                if ( ret == 3 ) {
                    if ( numOfBlogs >= *numberOfBlogs )
                        break;
                    cnt = 0;
                    continue;
                }

                ret = getBlogName( &q,
                                   blogInfo[numOfBlogs].blogName,
                                   &cnt, 3,
                                   &numOfBlogs );
                if ( ret == 3 ) {
                    if ( numOfBlogs >= *numberOfBlogs )
                        break;
                    cnt = 0;
                    continue;
                }

                q++;
            }
        }
    }

    free( response );
    *numberOfBlogs = numOfBlogs;

    return ( numOfBlogs );
}




/*
 *  最新記事(1個だけ)を取得
 *    引数:   blog ID, ユーザ名, パスワード
 *    戻り値: 実行結果
 */

int
getRecentPost( const char *blogID,
               const char *userName,
               const char *password,
               CONTENTINF *contentInfo )
{
    int num = 1;
    return ( getRecentPosts( blogID, userName, password, &num, contentInfo ) );
}

int
getRecentPost2( const char   *blogID,
                const char   *userName,
                const char   *password,
                CONTENTINFEX *contentInfo )
{
#if 1
    return ( getPost( blogID, userName, password, contentInfo ) );
#else
    int num = 1;
    return ( getRecentPostsEx( blogID, userName, password, &num, contentInfo ) );
#endif
}

int
getRecentPost3( const char *blogID,
                const char *userName,
                const char *password,
                POSTINF    *postinf )
{
    int num = 1;
    return ( getRecentPostTitles( blogID, userName, password, &num, postinf ) );
}


int
getRecentPostIDs( const char *blogID,
                  const char *userName,
                  const char *password,
                  int        *numberOfPosts,
                  char       listOfPostIDs[][80] )
{
    POSTINF *postinf;
    int     ret, i;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !numberOfPosts                           )
        return ( 0 );

    postinf = (POSTINF *)malloc( *numberOfPosts * sizeof ( POSTINF ) );
    if ( !postinf )
        return ( 0 );

    ret = getRecentPostTitles( blogID,
                               userName,
                               password,
                               numberOfPosts,
                               postinf );
    if ( ret > 0 ) {
        for ( i = 0; i < ret; i++ ) {
            strcpy( listOfPostIDs[i], postinf[i].postid );
        }
    }

    free( postinf );

    return ( ret );
}


/*
 * ファイルのアップロード
 */

int
uploadFile( const char *blogID,
            const char *userName,
            const char *password,
            const char *dirname,    /* upload先ディレクトリ名(blog のトップ */
                                    /* ディレクトリからの相対パス; 存在しな */
                                    /* い場合は作成される)                  */
            const char *fileName,
            size_t     fileSize,
            const char *fileType,
            char       *url )
{
    FILEINF         fInfo;
    const char      *p;
    char            *q = NULL;
    unsigned char   *buf;
    char            *bits = NULL;
    FILE            *fp;
    int             ret = 0;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !fileName                             ||
         (fileSize == 0)                       ||
         !url                                     )
        return ( -1 );
    if ( fileSize >= (size_t)(xmlrpc_p->sndHTTPBufferSize) ) {
        char    *xp = (char *)malloc( fileSize * 3 + MAX_CONTENT_SIZE );
        if ( xp ) {
            free( xmlrpc_p->sndHTTP );
            xmlrpc_p->sndHTTP = xp;
            xmlrpc_p->sndHTTPBufferSize = fileSize * 3 + MAX_CONTENT_SIZE;
        }
        else
            return ( -1 );
    }

    buf = (unsigned char *)malloc( fileSize * 3 + 2 );
    if ( !buf )
        return ( -2 );

    p = strrchr( fileName, '/' );
    if ( !p ) {
        p = strrchr( fileName, '\\' );
        if ( !p )
            p = fileName;
        else
            p++;
    }
    else
        p++;

    if ( fileType )
        strcpy( fInfo.type, fileType );
    else
        strcpy( fInfo.type, "application/unknown" );    /* 暫定 */
    if ( dirname && dirname[0] )
        sprintf( fInfo.name, "%s/%s", dirname, p );
    else
        strcpy( fInfo.name, p );

    fp = fopen( fileName, "rb" );
    if ( !fp ) {
        free( buf );
        return ( -3 );
    }

    fread( buf, sizeof ( char ), fileSize, fp );
    buf[fileSize] = NUL;

    fclose( fp );

    q = base64( buf, fileSize );
    if ( !q ) {
        (void)base64( NULL, 0 );
                        /* base64() 内で確保したメモリを free する */
        free( buf );
        return ( -4 );
    }
    bits = (char *)malloc( strlen( q ) + 1 );
    if ( !bits )
        return ( -4 );
    strcpy( bits, q );
    fInfo.bits = (unsigned char *)bits;

    if ( !strcmp( dirname, ".." )                           &&
         ((xmlrpc_p->blogKind == BLOGKIND_COCOLOG)     ||
          (xmlrpc_p->blogKind == BLOGKIND_COCOLOGFREE)    )    ) {
        char    *cookie = (char *)malloc( MAX_COOKIE_LEN );

        if ( cookie ) {
            int r;

            // ココログに login
            memset( cookie, 0x00, MAX_COOKIE_LEN );
            r = loginCocologFiles( userName, password, cookie );
            if ( r ) {
                // ファイルをアップロード
                ret = uploadCocologFiles( &fInfo, url, cookie );
            }

            free( cookie );
        }
    }
    else
        ret = newMediaObject( blogID, userName, password, &fInfo, url );

    if ( bits )
        free( bits );
    if ( q )
        (void)base64( NULL, 0 );
                        /* base64() 内で確保したメモリを free する */
    free( buf );

    return ( ret );
}


/* getRecentPostTitles() の blogger API 版 */
int
getRecentPostTitlesOnBloggerAPI( const char *blogID,
                                 const char *userName,
                                 const char *password,
                                 int        *numberOfPosts,
                                 POSTINF    *postinf )
{
    int         i;
    int         numOfPosts = 0;
    CONTENTINF  *contentInfo;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !numberOfPosts                        ||
         (*numberOfPosts <= 0)                 ||
         !postinf                                 )
        return ( numOfPosts );

    contentInfo = (CONTENTINF *)malloc(sizeof (CONTENTINF) * *numberOfPosts);
    if ( !contentInfo )
        return ( numOfPosts );

    numOfPosts = getRecentPosts( blogID, userName, password,
                                 numberOfPosts, contentInfo );
    for ( i = 0; i < numOfPosts; i++ ) {
        strcpy( postinf[i].postid, contentInfo[i].postid );
        strcpy( postinf[i].userid, contentInfo[i].userid );
        sprintf( postinf[i].title, "[%s] %04d-%02d-%02d %02d:%02d:%02d",
                 postinf[i].postid,
                 contentInfo[i].yy, contentInfo[i].mm, contentInfo[i].dd,
                 contentInfo[i].HH, contentInfo[i].MM, contentInfo[i].SS );
                      /* 注意: blogger API では title は取得できないので、 */
                      /*       記事IDとタイムスタンプを元に仮の title を生 */
                      /*       成することで対応する                        */
        postinf[i].yy = contentInfo[i].yy;
        postinf[i].mm = contentInfo[i].mm;
        postinf[i].dd = contentInfo[i].dd;
        postinf[i].HH = contentInfo[i].HH;
        postinf[i].MM = contentInfo[i].MM;
        postinf[i].SS = contentInfo[i].SS;
    }

    *numberOfPosts = numOfPosts;
    free( contentInfo );

    return ( numOfPosts );
}

/* getRecentPostTitles() の metaWeblog API 版 */
int
getRecentPostTitlesOnMetaWeblog( const char *blogID,
                                 const char *userName,
                                 const char *password,
                                 int        *numberOfPosts,
                                 POSTINF    *postinf )
{
    int             i;
    int             numOfPosts = 0;
    CONTENTINFEX    *contentInfo;

    if ( !blogID                               ||
         !(blogID[0])                          ||
         (strlen( blogID ) > MAX_BLOGIDLENGTH) ||
         !numberOfPosts                        ||
         (*numberOfPosts <= 0)                 ||
         !postinf                                 )
        return ( numOfPosts );

    contentInfo =
        (CONTENTINFEX *)malloc( sizeof (CONTENTINFEX) * *numberOfPosts );
    if ( !contentInfo )
        return ( numOfPosts );

    numOfPosts = getRecentPostsEx( blogID, userName, password,
                                   numberOfPosts, contentInfo );
    for ( i = 0; i < numOfPosts; i++ ) {
        strcpy( postinf[i].postid, contentInfo[i].postid );
        strcpy( postinf[i].userid, contentInfo[i].userid );
        strcpy( postinf[i].title,  contentInfo[i].title );
        postinf[i].yy = contentInfo[i].yy;
        postinf[i].mm = contentInfo[i].mm;
        postinf[i].dd = contentInfo[i].dd;
        postinf[i].HH = contentInfo[i].HH;
        postinf[i].MM = contentInfo[i].MM;
        postinf[i].SS = contentInfo[i].SS;
    }

    *numberOfPosts = numOfPosts;
    free( contentInfo );

    return ( numOfPosts );
}


/*
 *  RSS を取得し、POSTINF構造体に情報を設定する
 *      --- RSS 1.0 と RSS 2.0 に対応
 */

int
getRecentPostTitlesFromRSS(
        const char *rssURL,         // (I) RSS の URL
        int        *numberOfPosts,  // (I) 取得する記事情報の数
                                    // (O) 実際に取得した記事情報
                                    //     の数
        POSTINF    *postinf         // (O) 取得した記事情報
    )
{
    char    *buffer, *p, *q, *pre;
    int     numOfPost = 0;
    int     ret, cnt;
    size_t  sz;

    if ( !numberOfPosts        ||
         (*numberOfPosts <= 0) ||
         !rssURL               ||
         !(*rssURL)               )
        return ( numOfPost );

    /* RSS ファイルを取得 */
    sz = RCV_BUFFER_SIZE * 4;
    buffer = (char *)malloc( sz );
    if ( !buffer )
        return ( numOfPost );

    setUpReceiveBuffer( buffer, sz );   /* {@@} */
    ret = httpGetBuffer( rssURL, buffer, FALSE );

    /* RSS ファイルを解析 */
    for ( p = buffer; (numOfPost < *numberOfPosts) && *p; ) {
        if ( !strncmp( p, "<item rdf:about=\"", 17 ) ||
             !strncmp( p, "<item>", 6 )                 ) { 
            q = strchr( p, '>' );
            if ( !q )
                continue;

            cnt = 0;
            p = q + 1;

            postinf[numOfPost].title[0]  = NUL;
            postinf[numOfPost].postid[0] = NUL;
            postinf[numOfPost].userid[0] = NUL;

            do {
                while ( *p && (*p != '<') )
                    p++;
                if ( !(*p) )
                    break;

                pre = p;
                if ( getStringFromItem( "title", &p,
                                        postinf[numOfPost].title,
                                        MAX_LOGICALLINELEN, &cnt ) )
                    continue;
                if ( getStringFromItem( "link", &p,
                                        postinf[numOfPost].postid,
                                        MAX_POSTIDLENGTH, &cnt ) )
                    continue;
                if ( getStringFromItem( "dc:creator", &p,
                                        postinf[numOfPost].userid,
                                        MAX_USERIDLEN, &cnt ) )
                    continue;
                if ( getDateTimeFromItem( "dc:date", &p,
                                          &(postinf[numOfPost]),
                                          &cnt) )
                    continue;

                if ( !strncmp( p, "</item>", 7 ) )
                    break;
                if ( p == pre )
                    p++;
            } while ( *p && (cnt < 4) );

            if ( (cnt == 4) ||
                 ((cnt == 3) && (postinf[numOfPost].userid[0] == NUL)) )
                numOfPost++;
            else
                break;
        }

        if ( *p == '<' )
            p++;
        if ( ( q = strchr( p, '<' ) ) != NULL )
            p = q;
        else
            p++;
    }
    *numberOfPosts = numOfPost;
    free( buffer );

    return ( numOfPost );
}


/*
 *  ココログにアップロードしたファイルの削除
 */
BOOL
deleteFile( const char *username, const char *password, const char *url )
{
    int     ret = 0;
    char    *cookie = (char *)malloc( MAX_COOKIE_LEN );

    if ( cookie ) {
        memset( cookie, 0x00, MAX_COOKIE_LEN );
        if ( loginCocologFiles( username, password, cookie ) )
            ret = deleteCocologFiles( url, cookie );
        free( cookie );
    }

    return ( ret == 0 ? FALSE : TRUE );
}