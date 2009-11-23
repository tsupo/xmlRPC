/*
 *  https.c
 *      https �T�|�[�g���W���[��
 *
 * History:
 * $Log: /comm/xmlRPC/https.c $
 * 
 * 5     09/11/23 22:36 tsupo
 * 1.277��
 * 
 * 26    09/10/30 20:50 Tsujimura543
 * text_len �� 1024 ���傫���Ƃ��Ahmac_sha256() ���Ń������j��
 * �N����s��ɑΏ� (hmac_sha1() �Ɠ��l�̑Ώ��ŉ���)
 * 
 * 4     09/11/23 13:27 tsupo
 * 1.273��
 * 
 * 25    09/09/02 19:59 Tsujimura543
 * @nifty SSO �΍�����{ (connection established �Ȃ̂ɁASSL_connect()
 * ���G���[��Ԃ��Ă���)
 * 
 * 24    09/07/02 23:22 Tsujimura543
 * SSL_connect() �ŃG���[�����������Ƃ��̏������b��C��
 * 
 * 2     09/05/16 2:39 tsupo
 * �u1.263�Ł�1.264�Łv�̕ύX����荞��
 * 
 * 23    09/05/15 22:03 Tsujimura543
 * �R�����g�C��
 * 
 * 22    09/05/15 21:56 Tsujimura543
 * hmac_sha256() ��ǉ�
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 21    08/11/27 14:48 Tsujimura543
 * getOpenSSLversion() ��ǉ�
 * 
 * 20    07/10/09 19:57 Tsujimura543
 * dputs(), dprintf() �𓱓�
 * 
 * 19    07/09/28 20:59 Tsujimura543
 * _openHTTPS() �� proxy ���ݒ肵����������ǉ�
 * 
 * 18    07/09/14 19:38 Tsujimura543
 * �����[�X�r���h�łŏo�͂��郍�O���e�𐮗�
 * 
 * 17    07/09/13 22:27 Tsujimura543
 * ���O�ɏo�͂�����e���኱�C��
 * 
 * 16    07/09/13 22:03 Tsujimura543
 * verbose �� TRUE ���̃��O�o�͂ɑΉ�
 * 
 * 15    07/06/29 22:05 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 14    07/06/29 22:02 Tsujimura543
 * TypeKey �F�؂Ɏ��s����悤�ɂȂ��Ă��܂������߁A�΍�����{
 * (�����玸�s����悤�ɂȂ����̂��͕s��)
 * 
 * 13    07/05/22 0:26 Tsujimura543
 * �������j�󂪂�蔭�����ɂ������Ă݂�
 * 
 * 12    07/05/21 19:55 Tsujimura543
 * ���[�U���ƃp�X���[�h���K�v�� proxy�T�[�o���g���Ă� https �ʐM��
 * �Ή� (�ǂ����Ń������j�󂪋N���Ă���\������B������)
 * 
 * 11    06/07/26 14:45 Tsujimura543
 * EXP-RC4-MD5 �ł� SSL_connect() �� handshake failure �ɂȂ�ꍇ��
 * ���邽�߁A�V���� DES-CBC3-SHA ���Ή�����悤�ɂ��Ă݂�
 * 
 * 10    06/07/25 14:53 Tsujimura543
 * �O�̂��߂� CONNECT ���N�G�X�g�̃w�b�_���� Content-Length: 0 ������
 * �悤�ɂ��Ă݂�
 * 
 * 9     06/07/25 14:41 Tsujimura543
 * https �ʐM���� User-Agent ���U���ł���悤�ɂ���
 * 
 * 8     05/03/17 19:30 Tsujimura543
 * WIN32 ���̏ꍇ�� close() �ł͂Ȃ� closesocket() �Ń\�P�b�g�����
 * �悤�ɏC��
 * 
 * 7     04/11/29 17:29 Tsujimura543
 * OpenSSL �̃��C�u������ release/debug �̗����̃r���h�ł�p�ӂ����̂�
 * �����Adebug �r���h���̓��ʈ������O�� 
 * 
 * 6     04/11/26 21:23 Tsujimura543
 * �E�F�u���u���O�ɓ��e�ł��邱�Ƃ��m�F
 * 
 * 5     04/11/26 13:59 Tsujimura543
 * SSL �ڑ����s���̃��g���C������ǉ�
 * 
 * 4     04/11/25 15:51 Tsujimura543
 * https �̓���(GET �� POST)����ʂ�m�F
 * 
 * 3     04/11/24 15:15 Tsujimura543
 * https://www2.ggn.net/cgi-bin/ssl �� GET �ł��邱�Ƃ��m�F
 * 
 * 2     04/11/19 20:39 Tsujimura543
 * �b��� (proxy�o�R�ł̒ʐM�͂܂��s���S)
 * 
 * 1     04/11/19 15:37 Tsujimura543
 * https �T�|�[�g���W���[��: �ŏ��̃o�[�W����
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

/* root CA �̏ؖ��� */
#define ROOT_CA     "ca-bundle.crt"


/* �F�،��ʊm�F */
void
verify_ssl( SSL *ssl )
{
    long    verify_result;

    verify_result = SSL_get_verify_result( ssl );

    if ( xmlrpc_p->verbose ) {
        if ( verify_result == X509_V_OK )
            dputs( "�F�؂ɐ������܂���\n" );
#ifdef  _DEBUG
        else
            dputs( "�F�؎��ɃG���[���������܂������A�����𑱍s���܂��B\n" );
#endif
    }
}


/* �� */
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

    /* SSL�J�n */
    if ( first == TRUE ) {
        /* �ȉ��́A�ŏ���1�񂾂����s����� OK */
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
    /* rootCA ��o�^ */
    if ( ! SSL_CTX_load_verify_locations(ctx, ROOT_CA, NULL) ) {
        if ( xmlrpc_p->verbose )
            dprintf( "rootCA [%s] �̓Ǎ��݂Ɏ��s���܂����������𑱍s���܂�\n",
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
                    !strstr(p, "Connection established")) { // @nifty SSO �΍�
                    MessageBox( NULL,
                                "�T�[�o������ڑ���ؒf����܂����B    ",
                                "https �ڑ����s",
                                MB_OK | MB_ICONINFORMATION );
                }
            }

            return ( -1 );
        }

        if ( xmlrpc_p->useProxy ) {
            // proxy �T�[�o���ݒ肵����
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

    /* �ǂ̈Í����������g�p���邩��\�� (DES-CBC3-MD5 �Ȃ�) */
    {
        const char  *cipher;
        cipher = SSL_get_cipher( ssl );
        if ( xmlrpc_p->verbose )
            dprintf( "�Í�������: %s\n", cipher );
    }

    /* �ǂ� SSL �v���g�R�����g�p���邩��\�� (SSLv2, SSLv3/TLSv1 �Ȃ�) */
    {
        char    *version;
        version = SSL_get_cipher_version( ssl );
        if ( xmlrpc_p->verbose )
            dprintf( "�v���g�R��: %s\n", version );
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
    /* �� �Ō��1�񂾂����s
    ERR_free_strings();
    */

    xmlrpc_p->workArea1 = NULL;
    xmlrpc_p->workArea2 = NULL;

    return ( ret );
}



/* SSL �J�n */
int
openHTTPS()
{
    if ( (xmlrpc_p->workArea1 != NULL) || (xmlrpc_p->workArea2 != NULL) )
        return ( 0 );   /* SSL �g�p�� */

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

    /* SSL�J�n */
    return ( _openHTTPS() );
}


/* SSL �I�� */
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
        return ( 0 );   /* SSL ���g�p */

    return ( _closeHTTPS() );
}


/* SSL �f�[�^���M */
int
sendHTTPS( const char *request, size_t size )
{
    SSL *ssl = (SSL *)(xmlrpc_p->workArea2);
    int ret;

    ret = SSL_write( ssl, request, size );

    return ( size );
}


/* SSL �f�[�^��M */
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


/* OpenSSL �Ő��擾 */
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
