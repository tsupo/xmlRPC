/*
 *  https.c
 *      https サポートモジュール
 *
 * History:
 * $Log: /comm/xmlRPC/https.c $
 * 
 * 5     09/11/23 22:36 tsupo
 * 1.277版
 * 
 * 26    09/10/30 20:50 Tsujimura543
 * text_len が 1024 より大きいとき、hmac_sha256() 内でメモリ破壊が
 * 起きる不具合に対処 (hmac_sha1() と同様の対処で解決)
 * 
 * 4     09/11/23 13:27 tsupo
 * 1.273版
 * 
 * 25    09/09/02 19:59 Tsujimura543
 * @nifty SSO 対策を実施 (connection established なのに、SSL_connect()
 * がエラーを返してくる)
 * 
 * 24    09/07/02 23:22 Tsujimura543
 * SSL_connect() でエラーが発生したときの処理を暫定修正
 * 
 * 2     09/05/16 2:39 tsupo
 * 「1.263版→1.264版」の変更を取り込む
 * 
 * 23    09/05/15 22:03 Tsujimura543
 * コメント修正
 * 
 * 22    09/05/15 21:56 Tsujimura543
 * hmac_sha256() を追加
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 21    08/11/27 14:48 Tsujimura543
 * getOpenSSLversion() を追加
 * 
 * 20    07/10/09 19:57 Tsujimura543
 * dputs(), dprintf() を導入
 * 
 * 19    07/09/28 20:59 Tsujimura543
 * _openHTTPS() に proxy 情報設定し直し処理を追加
 * 
 * 18    07/09/14 19:38 Tsujimura543
 * リリースビルド版で出力するログ内容を整理
 * 
 * 17    07/09/13 22:27 Tsujimura543
 * ログに出力する内容を若干修正
 * 
 * 16    07/09/13 22:03 Tsujimura543
 * verbose が TRUE 時のログ出力に対応
 * 
 * 15    07/06/29 22:05 Tsujimura543
 * ソースコードを整理
 * 
 * 14    07/06/29 22:02 Tsujimura543
 * TypeKey 認証に失敗するようになってしまったため、対策を実施
 * (いつから失敗するようになったのかは不明)
 * 
 * 13    07/05/22 0:26 Tsujimura543
 * メモリ破壊がより発生しにくくしてみた
 * 
 * 12    07/05/21 19:55 Tsujimura543
 * ユーザ名とパスワードが必要な proxyサーバを使っての https 通信に
 * 対応 (どこかでメモリ破壊が起きている可能性あり。調査中)
 * 
 * 11    06/07/26 14:45 Tsujimura543
 * EXP-RC4-MD5 では SSL_connect() で handshake failure になる場合が
 * あるため、新たに DES-CBC3-SHA も対応するようにしてみた
 * 
 * 10    06/07/25 14:53 Tsujimura543
 * 念のために CONNECT リクエストのヘッダ部に Content-Length: 0 を入れる
 * ようにしてみた
 * 
 * 9     06/07/25 14:41 Tsujimura543
 * https 通信時も User-Agent を偽装できるようにした
 * 
 * 8     05/03/17 19:30 Tsujimura543
 * WIN32 環境の場合は close() ではなく closesocket() でソケットを閉じる
 * ように修正
 * 
 * 7     04/11/29 17:29 Tsujimura543
 * OpenSSL のライブラリを release/debug の両方のビルド版を用意したのに
 * 伴い、debug ビルド時の特別扱いを外す 
 * 
 * 6     04/11/26 21:23 Tsujimura543
 * ウェブリブログに投稿できることを確認
 * 
 * 5     04/11/26 13:59 Tsujimura543
 * SSL 接続失敗時のリトライ処理を追加
 * 
 * 4     04/11/25 15:51 Tsujimura543
 * https の動作(GET と POST)を一通り確認
 * 
 * 3     04/11/24 15:15 Tsujimura543
 * https://www2.ggn.net/cgi-bin/ssl を GET できることを確認
 * 
 * 2     04/11/19 20:39 Tsujimura543
 * 暫定版 (proxy経由での通信はまだ不完全)
 * 
 * 1     04/11/19 15:37 Tsujimura543
 * https サポートモジュール: 最初のバージョン
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/https.c 5     09/11/23 22:36 tsupo $";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#ifdef  UNIX
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <sys/types.h>
#ifdef  UNIX
#include <sys/uio.h>
#include <unistd.h>
#endif

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include <assert.h>

void
confirmProxyInfo(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword );

/* root CA の証明書 */
#define ROOT_CA     "ca-bundle.crt"


/* 認証結果確認 */
void
verify_ssl( SSL *ssl )
{
    long    verify_result;

    verify_result = SSL_get_verify_result( ssl );

    if ( xmlrpc_p->verbose ) {
        if ( verify_result == X509_V_OK )
            dputs( "認証に成功しました\n" );
#ifdef  _DEBUG
        else
            dputs( "認証時にエラーが発生しましたが、処理を続行します。\n" );
#endif
    }
}


/* 種 */
void
randomize()
{
    unsigned short  rand_ret;
    static int      first = TRUE;

    srand( (unsigned)time( NULL ) );

    RAND_poll();
    while ( RAND_status() == 0 ) {
        rand_ret = (unsigned short)(rand() % 65536);
        RAND_seed( &rand_ret, sizeof ( rand_ret ) );
    }
}


int
_openHTTPS()
{
    SSL         *ssl;
    SSL_CTX     *ctx;
    int         ret;
    static BOOL first = TRUE;
    X509        *server_cert;

    /* SSL開始 */
    if ( first == TRUE ) {
        /* 以下は、最初の1回だけ実行すれば OK */
        SSL_library_init();
        SSL_load_error_strings();
        SSLeay_add_ssl_algorithms();
        randomize();

        first = FALSE;
    }

    assert( xmlrpc_p->workArea1 == NULL );
    assert( xmlrpc_p->workArea2 == NULL );
    xmlrpc_p->workArea1 = NULL;
    xmlrpc_p->workArea2 = NULL;

    ctx = SSL_CTX_new( SSLv23_client_method() );
    if ( !ctx ) {
        ERR_print_errors_fp( stderr );
        return ( -1 );
    }
    xmlrpc_p->workArea1 = ctx;

#if 0
    /* rootCA を登録 */
    if ( ! SSL_CTX_load_verify_locations(ctx, ROOT_CA, NULL) ) {
        if ( xmlrpc_p->verbose )
            dprintf( "rootCA [%s] の読込みに失敗しましたが処理を続行します\n",
                     ROOT_CA );
    }
#endif
    SSL_CTX_set_verify_depth(ctx, SSL_VERIFY_PEER);

    SSL_CTX_set_mode( ctx, SSL_MODE_AUTO_RETRY );

    ssl = SSL_new( ctx );
    if ( !ssl ) {
        ERR_print_errors_fp( stderr );
        return ( -1 );
    }
    xmlrpc_p->workArea2 = ssl;

    ret = SSL_set_fd( ssl, xmlrpc_p->scdHTTP );
    if ( ret == 0 ) {
        ERR_print_errors_fp( stderr );
        return ( -1 );
    }

    if ( SSL_CTX_set_cipher_list( ctx, "EXP-RC4-MD5" ) == 0 ) {
        ERR_print_errors_fp( stderr );
        return ( -1 );
    }
    if ( SSL_CTX_set_cipher_list( ctx, "DES-CBC3-SHA" ) == 0 ) {
        ERR_print_errors_fp( stderr );
        return ( -1 );
    }

    ret = SSL_connect( ssl );
    if ( ret != 1 ){
        int r = SSL_get_error( ssl, ret );
        if ( r == SSL_ERROR_SYSCALL ) {
            DWORD err = GetLastError();

            if ( err == WSAECONNRESET ) {
                char    *p = xmlrpc_p->rcvHTTP;
                if (!(*p) ||
                    !strstr(p, "Connection established")) { // @nifty SSO 対策
                    MessageBox( NULL,
                                "サーバ側から接続を切断されました。    ",
                                "https 接続失敗",
                                MB_OK | MB_ICONINFORMATION );
                }
            }

            return ( -1 );
        }

        if ( xmlrpc_p->useProxy ) {
            // proxy サーバ情報設定し直し
            BOOL    useProxy = FALSE;
            if ( xmlrpc_p->confirmProxyInfo ) {
                if ( xmlrpc_p->confirmProxyInfo != (CONF_FUNC)(-1) )
                    xmlrpc_p->confirmProxyInfo( &useProxy,
                                                xmlrpc_p->proxyServer,
                                                &(xmlrpc_p->proxyPort),
                                                xmlrpc_p->proxyUserName,
                                                xmlrpc_p->proxyPassword );
            }
            else
                confirmProxyInfo( &useProxy,
                                  xmlrpc_p->proxyServer,
                                  &(xmlrpc_p->proxyPort),
                                  xmlrpc_p->proxyUserName,
                                  xmlrpc_p->proxyPassword );
        }

        return ( -1 );
    }

    /* どの暗号化方式を使用するかを表示 (DES-CBC3-MD5 など) */
    {
        const char  *cipher;
        cipher = SSL_get_cipher( ssl );
        if ( xmlrpc_p->verbose )
            dprintf( "暗号化方式: %s\n", cipher );
    }

    /* どの SSL プロトコルを使用するかを表示 (SSLv2, SSLv3/TLSv1 など) */
    {
        char    *version;
        version = SSL_get_cipher_version( ssl );
        if ( xmlrpc_p->verbose )
            dprintf( "プロトコル: %s\n", version );
    }

    server_cert = SSL_get_peer_certificate(ssl); 

    verify_ssl(ssl);

    X509_free(server_cert);

    xmlrpc_p->workArea1 = ctx;
    xmlrpc_p->workArea2 = ssl;

    return ( 0 );
}

int
_closeHTTPS()
{
    SSL     *ssl;
    SSL_CTX *ctx;
    int     ret = 0;

    ctx = (SSL_CTX *)(xmlrpc_p->workArea1);
    ssl = (SSL *)(xmlrpc_p->workArea2);

    if ( ssl ) {
        ret = SSL_shutdown( ssl );
        if ( ret != 1 ) {
            ERR_print_errors_fp( stderr );
            ret = -1;
        }
        else
            ret = 0;
        SSL_free( ssl );
    }

    if ( ctx ) {
        SSL_CTX_free( ctx );
    }
    /* ↓ 最後の1回だけ実行
    ERR_free_strings();
    */

    xmlrpc_p->workArea1 = NULL;
    xmlrpc_p->workArea2 = NULL;

    return ( ret );
}



/* SSL 開始 */
int
openHTTPS()
{
    if ( (xmlrpc_p->workArea1 != NULL) || (xmlrpc_p->workArea2 != NULL) )
        return ( 0 );   /* SSL 使用中 */

    if ( xmlrpc_p->useProxy == TRUE ) {
        int     ret;
        char    *p;

        p = strchr( xmlrpc_p->webServer, ':' );
        if ( p && (*(p + 1) >= '0') &&(*(p + 1) <= '9') ) {
            sprintf( xmlrpc_p->sndHTTP, "CONNECT %s",
                     xmlrpc_p->webServer );
         // *p = NUL;
        }
        else
            sprintf( xmlrpc_p->sndHTTP, "CONNECT %s:%d",
                     xmlrpc_p->webServer,
                     DEFAULT_HTTPS_PORT );
        strcat( xmlrpc_p->sndHTTP, " HTTP/1.0\r\n" );
     // strcat( xmlrpc_p->sndHTTP, "Accept: */*\r\n" );
        sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                 "User-Agent: %s\r\n",
                 xmlrpc_p->userAgent[0]
                    ? xmlrpc_p->userAgent
                    : "httpRead/1.1 (written by H.Tsujimura)" );
        sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                 "Host: %s\r\n", xmlrpc_p->webServer );

        if ( xmlrpc_p->proxyUserName[0] ) {
            char   auth[128];
            char   *p;

            if ( !(xmlrpc_p->proxyPassword[0]) )
                sprintf( auth, "%s", xmlrpc_p->proxyUserName );
            else
                sprintf( auth, "%s:%s",
                         xmlrpc_p->proxyUserName, xmlrpc_p->proxyPassword );
            p = base64( (unsigned char *)auth, strlen( auth ) );
            if ( p )
                sprintf( &xmlrpc_p->sndHTTP[strlen(xmlrpc_p->sndHTTP)],
                         "Proxy-Authorization: Basic %s\r\n", p );
        }

     // strcat( xmlrpc_p->sndHTTP, "Connection: close\r\n" );
        strcat( xmlrpc_p->sndHTTP, "Content-Length: 0\r\n" );
        strcat( xmlrpc_p->sndHTTP, "Cache-Control: no-cache\r\n\r\n" );
        if ( xmlrpc_p->verbose )
            dprintf( "\n\t%s\n", xmlrpc_p->sndHTTP );

        xmlrpc_p->sndHTTPmessageSize = strlen( xmlrpc_p->sndHTTP );

        ret = send( xmlrpc_p->scdHTTP, xmlrpc_p->sndHTTP,
                    xmlrpc_p->sndHTTPmessageSize, 0 );
        if ( ret > 0 ) {
            do {
                xmlrpc_p->rcvHTTPbufferSize = RCV_BUFFER_SIZE;
                ret = recv( xmlrpc_p->scdHTTP, xmlrpc_p->rcvHTTP,
                            xmlrpc_p->rcvHTTPbufferSize, 0 );
                if ( (ret > 0) && xmlrpc_p->verbose )
                    dprintf( "%s\n", xmlrpc_p->rcvHTTP );
                if ( ret <= 0 )
                    break;
            } while ( ret == xmlrpc_p->rcvHTTPbufferSize );
        }
    }

    /* SSL開始 */
    return ( _openHTTPS() );
}


/* SSL 終了 */
int
closeHTTPS()
{
    SSL     *ssl;
    SSL_CTX *ctx;

    ctx = (SSL_CTX *)(xmlrpc_p->workArea1);
    ssl = (SSL *)(xmlrpc_p->workArea2);

    if ( xmlrpc_p->useProxy == TRUE ) {
#ifdef  WIN32
        closesocket( xmlrpc_p->scdHTTP );
#else
        close( xmlrpc_p->scdHTTP );
#endif
    }

    if ( (ctx == NULL) || (ssl == NULL) )
        return ( 0 );   /* SSL 未使用 */

    return ( _closeHTTPS() );
}


/* SSL データ送信 */
int
sendHTTPS( const char *request, size_t size )
{
    SSL *ssl = (SSL *)(xmlrpc_p->workArea2);
    int ret;

    ret = SSL_write( ssl, request, size );

    return ( size );
}


/* SSL データ受信 */
int
recvHTTPS( char *response, size_t size )
{
    SSL *ssl = (SSL *)(xmlrpc_p->workArea2);
    int recv_size;

    recv_size = SSL_read( ssl, response, size );
    if ( (recv_size > 0) && ((size_t)recv_size < size) )
        response[recv_size /* + 1 */] = NUL;

    return ( recv_size );
}


/* OpenSSL 版数取得 */
char    *
getOpenSSLversion( char *buf, size_t bufSize )
{
    char        *p = buf;
    size_t      sz = bufSize;
    static char version[BUFSIZ];

    if ( !buf || (bufSize == 0) ) {
        p  = version;
        sz = BUFSIZ;
    }
    strncpy( p, SSLeay_version(SSLEAY_VERSION), sz - 1 );
    p[sz - 1] = NUL;

    return ( p );
}


/* HMACSHA256 */
void
hmac_sha256(
    const unsigned char *text,      /* pointer to data stream        */
    int                 text_len,   /* length of data stream         */
    const unsigned char *key,       /* pointer to authentication key */
    int                 key_len,    /* length of authentication key  */
    void                *digest)    /* caller digest to be filled in */
{
#if 0
    unsigned char k_ipad[65];   /* inner padding -
                                 * key XORd with ipad
                                 */
    unsigned char k_opad[65];   /* outer padding -
                                 * key XORd with opad
                                 */
    unsigned char tk[SHA256_DIGEST_LENGTH];
    unsigned char tk2[SHA256_DIGEST_LENGTH];
    unsigned char bufferIn[1024];
    unsigned char bufferOut[1024];
    int           i;

    /* if key is longer than 64 bytes reset it to key=sha256(key) */
    if ( key_len > 64 ) {
        SHA256( key, key_len, tk );
        key     = tk;
        key_len = SHA256_DIGEST_LENGTH;
    }

    /*
     * the HMAC_SHA256 transform looks like:
     *
     * SHA256(K XOR opad, SHA256(K XOR ipad, text))
     *
     * where K is an n byte key
     * ipad is the byte 0x36 repeated 64 times
     * opad is the byte 0x5c repeated 64 times
     * and text is the data being protected
     */

    /* start out by storing key in pads */
    memset( k_ipad, 0, sizeof k_ipad );
    memset( k_opad, 0, sizeof k_opad );
    memcpy( k_ipad, key, key_len );
    memcpy( k_opad, key, key_len );

    /* XOR key with ipad and opad values */
    for ( i = 0; i < 64; i++ ) {
        k_ipad[i] ^= 0x36;
        k_opad[i] ^= 0x5c;
    }

    /*
     * perform inner SHA256
     */
    memset( bufferIn, 0x00, 1024 );
    memcpy( bufferIn, k_ipad, 64 );
    memcpy( bufferIn + 64, text, text_len );

    SHA256( bufferIn, 64 + text_len, tk2 );

    /*
     * perform outer SHA256
     */
    memset( bufferOut, 0x00, 1024 );
    memcpy( bufferOut, k_opad, 64 );
    memcpy( bufferOut + 64, tk2, SHA256_DIGEST_LENGTH );

    SHA256( bufferOut, 64 + SHA256_DIGEST_LENGTH, digest );
#else
    unsigned int    result_len;
    unsigned char   result[EVP_MAX_MD_SIZE];

    HMAC( EVP_sha256(),
          key,    key_len,
          text,   text_len,
          result, &result_len);

    memcpy( digest, (const void *)result, result_len );
#endif
}
