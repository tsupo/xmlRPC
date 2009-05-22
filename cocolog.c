/*
 *  cocolog.c
 *      ココログ の管理画面と直接対話し、ファイルをアップロードする処理
 *
 * History:
 * $Log: /comm/xmlRPC/cocolog.c $
 * 
 * 2     09/05/22 21:07 tsupo
 * 「1.264版→1.265版」の変更を取り込む
 * 
 * 17    09/05/22 17:45 Tsujimura543
 * uploadCocologFiles() を修正。アップロード成功時のファイル名取得処理
 * を最近のココログのファイルマネージャの仕様に合うように更新
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 16    07/12/06 1:46 Tsujimura543
 * uploadCocologFiles() を変更、バイナリファイルのアップロードに対応した
 * 
 * 15    07/10/09 19:51 Tsujimura543
 * dputs(), dprintf() を導入
 * 
 * 14    07/09/28 20:57 Tsujimura543
 * reallocするサイズが間違っていた(元のサイズを指定していた)のを修正
 * 
 * 13    07/09/28 17:15 Tsujimura543
 * response格納領域が小さすぎた場合は、reallocし直して再試行するよう
 * にしてみた
 * 
 * 12    07/09/28 16:49 Tsujimura543
 * (1) DEBUG_FOR_ADS 部分を正式なデバッグ用機能として取り込んだ
 * (2) アップロード済みファイルがある程度以上多いと、magic_token の取得
 *     に失敗する不具合があることが判明。とりあえず、response格納領域の
 *     サイズを大幅に増やすことで暫定対応
 * 
 * 11    07/01/22 18:38 Tsujimura543
 * コメント(typo)を修正
 * 
 * 10    06/12/12 11:49 Tsujimura543
 * loginCocologFiles() の終了時にも encodeURL() 内作業領域を解放する
 * ようにした
 * 
 * 9     06/12/04 13:35 Tsujimura543
 * コメントを修正
 * 
 * 8     06/12/04 13:34 Tsujimura543
 * (1) 65536バイトより大きなファイルをアップロードしようとすると、メモリ
 *     オーバーランが発生する不具合に対処
 * (2) アップロードしようとしているファイルのサイズに応じて、タイムアウ
 *     ト時間を設定し直すようにした
 * 
 * 7     06/10/20 21:39 Tsujimura543
 * 受信バッファオーバーラン対策を実施
 * 
 * 6     06/07/14 16:23 Tsujimura543
 * あずスタさん向けデバッグバージョン (DEBUG_FOR_ADS)
 * 
 * 5     06/03/15 18:31 Tsujimura543
 * getMagicToken() を static 化
 * 
 * 4     06/03/15 18:25 Tsujimura543
 * ココログフリーでのトップディレクトリ(..を指定した場合)のアップロードにも
 * 対応した (動作確認済み)
 * 
 * 3     06/03/14 23:39 Tsujimura543
 * uploadFile() と deleteFile() をココログフリーにも対応させた
 * 
 * 2     06/03/14 20:53 Tsujimura543
 * deleteCocologFiles() を追加
 * 
 * 1     05/11/17 16:07 Tsujimura543
 * 新規作成
 */

#include "xmlRPC.h"
#include "multipart.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/cocolog.c 2     09/05/22 21:07 tsupo $";
#endif

#define COCOLOGFREE_FILEMANAGER \
            "https://app.f.cocolog-nifty.com/t/app/control/files"
#define COCOLOG_FILEMANAGER     \
            "https://app.cocolog-nifty.com/t/app/control/files"

static char *
getMagicToken(
        const char *path,           // (I)   カレントディレクトリ
        char       *magic_token,    // (O)   magic_token の値
        char       **response,      // (I/O) 作業用 (受信バッファ)
        size_t     *sz,             // (I)   受信バッファサイズ
        char       *cookie          // (I/O) クッキー
    )
{
    char    targetURL[MAX_URLLENGTH];

    // ココログフリーの場合のみ magic_token を入手必要あり
    //   (おそらく 従来のココログも TypePad 1.6 ベースに移行したら、
    //    magic_token を使うようになるものと思われるので、将来に備え
    //    ておく)
    *magic_token = NUL;
    if ( *path )
        sprintf( targetURL,
                 xmlrpc_p->blogKind == BLOGKIND_COCOLOGFREE
                    ? COCOLOGFREE_FILEMANAGER "?path=%s"
                    : COCOLOG_FILEMANAGER "?path=%s",
                 path );
    else
        strcpy( targetURL,
                xmlrpc_p->blogKind == BLOGKIND_COCOLOGFREE
                    ? COCOLOGFREE_FILEMANAGER
                    : COCOLOG_FILEMANAGER );
    setUpReceiveBuffer( *response, *sz );
    http_getEx( targetURL, *response, cookie );
    if ( **response ) {
        char    *p, *q;

        p = strstr( *response, "name=\"magic_token\"" );
        if ( p ) {
            p += 18;
            q = strstr( p, "value=\"" );
            if ( q ) {
                p = q + 7;
                q = strchr( p, '"' );
                if ( q ) {
                    strncpy( magic_token, p, q - p );
                    magic_token[q - p] = NUL;
                }
            }
        }
        else {
            char    *p;
            size_t  newSz = *sz * 16;

            if ( newSz <= MAX_CONTENT_SIZE * 512 ) {
                p = (char *)realloc( *response, newSz );
                if ( p ) {
                    *response = p;
                    *sz       = newSz;
                    return ( getMagicToken( path, magic_token,
                                            response, sz, cookie ) );
                }
            }
        }
    }

    if ( xmlrpc_p->verbose )
        dprintf( "getMagicToken: magic_token 取得%s\n",
                 *magic_token ? "成功" : "失敗" );

    return ( magic_token );
}

int
loginCocologFiles( const char *username,    // (I) ユーザ名
                   const char *password,    // (I) パスワード
                   char       *cookie )     // (O) クッキー
{
    int     ret = 0;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE;

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
            xmlrpc_p->blogKind == BLOGKIND_COCOLOGFREE
                ? COCOLOGFREE_FILEMANAGER
                : COCOLOG_FILEMANAGER );
    setTargetURL( url );
    sprintf( request,
             "username=%s&"
             "password=%s&"
             "remember=1&"
             "submit=%s",
             username, password,
             encodeURL(sjis2utf("ログイン")) );
    setUpReceiveBuffer( response, sz );
#if 0
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               "application/x-www-form-urlencoded",
                               request, response, cookie,
                               NULL, NULL );
#else
    http_postEx( url, "application/x-www-form-urlencoded",
                 request, response, cookie );
#endif

 // if ( ret == -1 ) {
 //     ret = 0;        /* サーバとの通信失敗 */
 //     if ( xmlrpc_p->verbose )
 //         dputs( "loginCocologFiles: login失敗 (サーバとの通信失敗)\n" );
 // }
 /* else */ if ( *response ) {
        char    targetString[BUFSIZ];
        sprintf( targetString, "| %sさん", username );
        if ( strstr( response, sjis2utf(targetString) ) != NULL ) {
            ret = 1;    /* ログイン成功 */
            if ( xmlrpc_p->verbose )
                dputs( "loginCocologFiles: login成功\n" );
        }
        else {
            ret = 0;    /* ログイン失敗 */
            if ( xmlrpc_p->verbose )
                dputs( "loginCocologFiles: login失敗 (ユーザ名またはパスワー"
                       "ドが違う、あるいはココログの仕様が変わった)\n" );
        }
    }
    else {
        ret = 0;        /* サーバとの通信失敗 */
        if ( xmlrpc_p->verbose )
            dputs( "loginCocologFiles: login失敗 (サーバとの通信失敗)\n" );
    }

    encodeURL( NULL );
    free( response );
    free( request  );

    return ( ret );
}

int
uploadCocologFiles( FILEINF *fileInf, // (I)   アップロードするファイルに関す
                                      //       る情報
                    char    *url,     // (O)   アップロードしたファイルの URL
                    char    *cookie ) // (I/O) クッキー
{
    int     ret = 0;
    char    targetURL[MAX_URLLENGTH];
    char    contentType[MAX_LOGICALLINELEN];
    char    magic_token[MAX_KEYLENGTH];
    char    *request;
    char    *response;
    char    *separator = getMultiPartID();
    size_t  szz = 0;
    size_t  sz  = MAX_CONTENT_SIZE * 4;
    size_t  bt;
    char    *base;
    char    *tail;
    char    *p;

    if (!cookie || !(*cookie) ||
         !fileInf             ||
         !(fileInf->bits)     ||
         !url                    )
        return ( ret );

    if ( xmlrpc_p->verbose )
        dprintf( "uploadCocologFiles: アップロードしようとしているファイル"
                 " → %s\n",
                 fileInf->name );

    bt = strlen( (char *)(fileInf->bits) );
    request  = (char *)malloc( MAX_CONTENT_SIZE + bt );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE + bt );
    getSendBufferPointer( request, base );
    tail = base;

    /* magic_token を取得 */
    getMagicToken( "", magic_token, &response, &sz, cookie );

    /* ファイルをアップロード */
    sprintf( contentType, "multipart/form-data; boundary=%s", separator );
    strcpy( targetURL, 
            xmlrpc_p->blogKind == BLOGKIND_COCOLOGFREE
                ? COCOLOGFREE_FILEMANAGER
                : COCOLOG_FILEMANAGER );
    setTargetURL( targetURL );
    strcpy( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "__mode", 0, "upload", NULL ) );
    if ( magic_token[0] )
        strcat( tail, 
                makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                                   "magic_token", 0, magic_token, NULL ) );
    strcat( tail, 
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "path", 0, NULL, NULL ) );

    szz  =  strlen( tail );
    tail += szz;
    szz  =  0;
    p    =  makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_FILE,
                               "file", 0, (char *)fileInf, &szz );
    memcpy( tail, p, szz );
    tail += szz;

    strcat( tail,
            makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_STRING,
                               "submit", 0,
                               encodeURL(sjis2utf("アップロード")),
                               NULL ) );
    sprintf( tail + strlen( tail ), "--%s--\r\n", separator );
    szz  =  strlen( tail );
    tail += szz;

    makeMultiPartItem( separator, MULITIPART_ITEM_TYPE_BUFFERFREE,
                       NULL, 0, NULL, NULL );

    szz = tail - base;
    setUpSendBuffer( request, szz, base );
    setUpReceiveBuffer( response, sz );

    setTimeoutTime( DEFAULT_HTTP_TIMEOUT * (1 + (bt / (1024 * 1024))) );
                                    // サイズに比例したタイムアウト時間を設定
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               contentType,
                               request, response, cookie,
                               NULL, NULL );
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT ); // デフォルト値に戻しておく

    /* url 取得 */
    url[0] = NUL;
    if ( response[0] ) {
        char    *p = strstr( response, "\"/t/app/control/files\"" );
        char    *q = strstr( response, "id=\"duplicate_file\"" );
        char    *r;

        if ( xmlrpc_p->verbose )
            dputs( "uploadCocologFiles: アップロードリクエスト発行成功\n" );

        if ( ( r = strrchr( fileInf->name, '/' ) ) == NULL )
            r = fileInf->name;
        else
            r++;

        if ( q ) {
            // 「同じ名前の古いファイルがこのフォルダ内にあります」の場合
            char    temp[32];
            char    *s = strstr( q, "name=\"temp\" value=\"" );

            if ( xmlrpc_p->verbose )
                dputs( "uploadCocologFiles: 同じ名前の古いファイルが"
                       "このフォルダ内にあります\n" );

            p = NULL;
            if ( s ) {
                char    *t;
                s += 19;
                t = strchr( s, '"' );
                strncpy( temp, s, t - s );
                temp[t - s] = NUL;

                // ファイルを置き換え
                memset( request,  0x00, MAX_CONTENT_SIZE );
                strcpy( url,
                        xmlrpc_p->blogKind == BLOGKIND_COCOLOGFREE
                            ? COCOLOGFREE_FILEMANAGER
                            : COCOLOG_FILEMANAGER );
                setTargetURL( url );
                if ( magic_token[0] )
                    sprintf( request,
                             "__mode=upload&"
                             "magic_token=%s&"
                             "temp=%s&"
                             "path=&"
                             "name=%s&"
                             "overwrite_yes=%s",
                             magic_token,
                             temp, r,
                             encodeURL(sjis2utf("ファイルを置き換えます")) );
                else
                    sprintf( request,
                             "__mode=upload&"
                             "temp=%s&"
                             "path=&"
                             "name=%s&"
                             "overwrite_yes=%s",
                             temp, r,
                             encodeURL(sjis2utf("ファイルを置き換えます")) );
                setUpReceiveBuffer( response, sz );
                ret = httpPostWithSession(
                            xmlrpc_p->webServer, xmlrpc_p->webPage,
                            "application/x-www-form-urlencoded",
                            request, response, cookie,
                            NULL, NULL );
                if ( response[0] ) {
                    if ( xmlrpc_p->verbose )
                        dputs("uploadCocologFiles: 置換リクエスト発行成功\n");
                    p = strstr( response, "\"/t/app/control/files\"" );
                }
                else {
                    if ( xmlrpc_p->verbose )
                        dputs("uploadCocologFiles: 置換リクエスト発行失敗\n");
                }
            }
        }

        if ( p ) {
            char    targetString[BUFSIZ];

            p += 22;
            sprintf( targetString, ">%s</a>", r );
            q = strstr( p, targetString );
            if ( !q ) {
                /* ファイルをアップロードするとファイル名中の大文字が小文字 */
                /* に変えられてしまうため、以下の対策を実施                 */
                char    *s = targetString;
                while ( *s ) {
                    if ( (*s >= 'A') && (*s <= 'Z') )
                        *s = (char)(*s - 'A' + 'a');
                    s++;
                }
                q = strstr( p, targetString );
            }
            if ( q ) {
                while ( (q >= response) && *q && (strncmp( q, "href=\"", 6 ) != 0) )
                    q--;
                if ( !strncmp( q, "href=\"", 6 ) ) {
                    q += 6;
                    p = strchr( q, '"' );
                    if ( p ) {
                        strncpy( url, q, p - q );
                        url[p - q] = NUL;
                        if ( xmlrpc_p->verbose )
                            dprintf( "uploadCocologFiles: アップロードした"
                                     "ファイルのURL → %s\n",
                                     url );
                    }
                }
            }
        }
    }
    else {
        if ( xmlrpc_p->verbose )
            dputs( "uploadCocologFiles: アップロードリクエスト発行失敗\n" );
    }

    encodeURL( NULL );
    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

int
deleteCocologFiles( const char *url,        // (I)   削除したいファイルの URL
                    char       *cookie )    // (I/O) クッキー
{
    int     ret = 0;
    char    targetURL[MAX_URLLENGTH];
    char    *request;
    char    *response;
    char    path[MAX_URLLENGTH];
    char    filename[MAX_URLLENGTH];
    char    magic_token[MAX_KEYLENGTH];
    char    *p, *q;
    size_t  sz = MAX_CONTENT_SIZE * 4;

    if (!cookie || !(*cookie) ||
         !url                    )
        return ( ret );

    if ( xmlrpc_p->verbose ) {
        dprintf( "deleteCocologFiles: 削除しようとしているファイル(URL)"
                 " → %s\n",
                 url );
    }

    path[0]     = NUL;
    filename[0] = NUL;
    p = strstr( url, "://" );
    if ( !p )
        return ( ret );
    p += 3;
    q = strchr( p, '/' );
    if ( !q )
        return ( ret );
    p = q + 1;
    q = strrchr( p, '/' );
    if ( q ) {
        strncpy( path, p, q - p );
        path[q - p] = NUL;
    }
    strcpy( filename, p );

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request,  0x00, MAX_CONTENT_SIZE );

    /* magic_token を取得 */
    getMagicToken( path, magic_token, &response, &sz, cookie );

    /* ファイルを削除 */
    strcpy( targetURL,
            xmlrpc_p->blogKind == BLOGKIND_COCOLOGFREE
                ? COCOLOGFREE_FILEMANAGER
                : COCOLOG_FILEMANAGER );
    setTargetURL( targetURL );
    if ( magic_token[0] ) {
        if ( path[0] )
            sprintf( request,
                     "type=file&"
                     "__mode=delete&"
                     "magic_token=%s&"
                     "path=%s&"
                     "id=%s&"
                     "submit=%s",
                     magic_token,
                     path, filename,
                     encodeURL( sjis2utf("削除する") ) );
        else
            sprintf( request,
                     "type=file&"
                     "__mode=delete&"
                     "magic_token=%s&"
                     "path=&"
                     "id=%s&"
                     "submit=%s",
                     magic_token,
                     filename,
                     encodeURL( sjis2utf("削除する") ) );
    }
    else {
        if ( path[0] )
            sprintf( request,
                     "type=file&"
                     "__mode=delete&"
                     "path=%s&"
                     "id=%s&"
                     "submit=%s",
                     path, filename,
                     encodeURL( sjis2utf("削除する") ) );
        else
            sprintf( request,
                     "type=file&"
                     "__mode=delete&"
                     "path=&"
                     "id=%s&"
                     "submit=%s",
                     filename,
                     encodeURL( sjis2utf("削除する") ) );
    }
    setUpReceiveBuffer( response, sz );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               "application/x-www-form-urlencoded",
                               request, response, cookie,
                               NULL, NULL );
    if ( response[0] ) {
        ret = 1;
        if ( xmlrpc_p->verbose )
            dputs( "deleteCocologFiles: 削除リクエスト発行成功\n" );
    }
    else {
        ret = 0;
        if ( xmlrpc_p->verbose )
            dputs( "deleteCocologFiles: 削除リクエスト発行失敗\n" );
    }
    encodeURL( NULL );

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

