/*
 *  RSA による暗号化・復号を実行する
 *
 *        Copyleft (c) 2005 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  20 Sep 2005
 *
 * History:
 * $Log: /comm/xmlRPC/encryptRSA.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 6     06/03/09 18:31 Tsujimura543
 * OpenSSL のエラーを人間が読んで分かる文字列で表示するようにした
 * 
 * 5     05/09/21 22:39 Tsujimura543
 * freeRSAkey() と freeRSAbuffer() を追加
 * 
 * 4     05/09/21 18:42 Tsujimura543
 * encodeByRSA() の第2引数を in のみから in,out に変更
 * 
 * 3     05/09/20 21:24 Tsujimura543
 * コメントを整理
 * 
 * 2     05/09/20 21:22 Tsujimura543
 * generateRSAkey() をライブラリ外非公開にし、encodeByRSA() を呼ぶだけ
 * で暗号化できるようにした。
 * 
 * 1     05/09/20 19:59 Tsujimura543
 * 最初の版
 */

#include "xmlRPC.h"
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include "encryptRSA.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/encryptRSA.c 1     09/05/14 3:46 tsupo $";
#endif

#define KEYBIT_LEN      192     /* 鍵長 (単位: ビット)        */
#define KEYSTR_LEN      10240   /* 鍵対応文字列格納領域サイズ */
#define RANDOMIZE_BASE  65537   /* 乱数の種 (素数)            */

static BOOL first = TRUE;   /* SSL_load_error_strings() を実行済みか否か */
                            /*    (TRUE: 未実行, FALSE: 実行済み)        */

/*
 *  鍵の生成
 */
RSA *
generateRSAkey( unsigned char **rsaString )
{
    RSA     *rsa = NULL;

    /* 鍵対応文字列格納領域の確保 */
    *rsaString = (unsigned char *)malloc( KEYSTR_LEN );
    if ( *rsaString ) {
        /* RSA 鍵生成 */
        rsa = RSA_generate_key( KEYBIT_LEN, RANDOMIZE_BASE, NULL, NULL );
        if ( !rsa ) {
            free( *rsaString );
            *rsaString = NULL;
        }
        else {
            sprintf( (char *)(*rsaString),
                     "%s,%s,%s,%s,%s",
                     BN_bn2hex(rsa->p),
                     BN_bn2hex(rsa->q),
                     BN_bn2hex(rsa->n),
                     BN_bn2hex(rsa->e),
                     BN_bn2hex(rsa->d) );
#ifdef  _DEBUG
            fprintf( stderr, "鍵: %s\n",
                     base64( *rsaString, strlen( (char *)(*rsaString) ) ) );
#endif
        }
    }

    return ( rsa );
}


/*
 *  RSA による暗号化
 */
int
encodeByRSA( const char    *targetString,
             unsigned char **rsaString,
             unsigned char **cryptedBuffer )
{
    int         crypted_len = 0;
    char        errbuf[1024];
    int         numOfBlock, i, nx = 0, sz;
    const char  *p;
    char        target[32];
    RSA         *rsa = NULL;
#define BLOCK_SIZE  12
    if ( first == TRUE ) {
        /* 以下は、最初の1回だけ実行すれば OK */
        ERR_load_crypto_strings();
        first = FALSE;
    }

    numOfBlock = (strlen( targetString ) + (BLOCK_SIZE - 1)) / BLOCK_SIZE;

    if ( !rsaString )
        return ( crypted_len );
    if ( *rsaString && **rsaString ) {
        /* RSA鍵の復元 */
        rsa = recoveryRSAkey( *rsaString );
    }
    else {
        /* RSA鍵の生成 */
        rsa = generateRSAkey( rsaString );
    }
    if ( rsa ) {
        /* 暗号化結果格納領域の確保 */
        *cryptedBuffer = (unsigned char *)malloc( RSA_size(rsa) * numOfBlock );
        if ( *cryptedBuffer ) {
            /* 暗号化 */
            for ( i = 0, nx = 0, p = targetString; i < numOfBlock; i++ ) {
                if ( strlen( targetString ) <= BLOCK_SIZE )
                    sz = strlen( targetString );
                else if ( i < numOfBlock - 1 )
                    sz = BLOCK_SIZE;
                else
                    sz = strlen( targetString ) % BLOCK_SIZE;
                strncpy( target, p, sz );
                target[sz] = NUL;

                crypted_len = RSA_private_encrypt(
                                    sz, (unsigned char *)target,
                                    (unsigned char *)(*cryptedBuffer + nx),
                                    rsa, RSA_PKCS1_PADDING );
                if ( crypted_len == -1 ){
                    fprintf( stderr, "encodeByRSA: err=%s\n",
                             ERR_error_string( ERR_get_error(), errbuf ) );
                    break;
                }

                nx += crypted_len;
                p  += sz;
            }
            crypted_len = nx;
        }

        RSA_free( rsa );
    }

    return ( crypted_len );
}


/*
 *  鍵の復元
 */
RSA *
recoveryRSAkey( const unsigned char *rsaString )
{
    RSA     *rsa = NULL;

    if ( strchr( (char *)rsaString, ',' ) ) {
        rsa = RSA_generate_key( KEYBIT_LEN, RANDOMIZE_BASE, NULL, NULL );
        if ( rsa ) {
            const char  *p;
            char        *temp;
            char        *q, *n, *e, *d;

            temp = (char *)malloc( strlen( (char *)rsaString ) + 1 );
            if ( temp ) {
                strcpy( temp, (char *)rsaString );

                p = temp;
                q = strchr( p, ',' );
                *q++ = NUL;
                n = strchr( q, ',' );
                *n++ = NUL;
                e = strchr( n, ',' );
                *e++ = NUL;
                d = strchr( e, ',' );
                *d++ = NUL;

                BN_hex2bn(&(rsa->p), p);
                BN_hex2bn(&(rsa->q), q);
                BN_hex2bn(&(rsa->n), n);
                BN_hex2bn(&(rsa->e), e);
                BN_hex2bn(&(rsa->d), d);

                free( temp );
            }
        }
    }

    return ( rsa );
}


/*
 *  RSA による復号
 */
int
decodeByRSA( char                **targetString,
             const unsigned char *rsaString,
             const unsigned char *cryptedBuffer,
             int                 crypted_len )
{
    int         decrypted_len = 0, len;
    char        errbuf[1024];
    RSA         *rsa = NULL;
    int         numOfBlock, i, nx = 0, sz;
    const char  *p;
    char        target[32];
#define ENCBLOCK_SIZE   24
    if ( first == TRUE ) {
        /* 以下は、最初の1回だけ実行すれば OK */
        ERR_load_crypto_strings();
        first = FALSE;
    }

    numOfBlock = (crypted_len + (ENCBLOCK_SIZE - 1)) / ENCBLOCK_SIZE;

    /* RSA情報復元 */
    rsa = recoveryRSAkey( rsaString );
    if ( rsa ) {
        /* 復号結果格納領域の確保 */
        *targetString = (char *)malloc( RSA_size(rsa) * numOfBlock );
        if ( *targetString ) {
            /* 復号 */
            memset( *targetString, 0, RSA_size( rsa ) * numOfBlock );
            for ( i = 0, nx = 0, p = (char *)cryptedBuffer;
                  i < numOfBlock; i++ ) {
                if ( crypted_len <= ENCBLOCK_SIZE )
                    sz = crypted_len;
                else
                    sz = ENCBLOCK_SIZE;
                memcpy( target, p, sz );
                target[sz] = NUL;

                len = RSA_public_decrypt( sz, (unsigned char *)target,
                                        (unsigned char *)(*targetString + nx),
                                          rsa, RSA_PKCS1_PADDING );
                if ( len == -1 ){
                    fprintf( stderr, "decodeByRSA: err=%s\n",
                             ERR_error_string( ERR_get_error(), errbuf ) );
                    /* 注意: エラーが発生してもデコード自体は成功している */
                    /*       こともある                                   */
                    break;
                }

                nx += len;
                p  += sz;
            }
            decrypted_len = nx;
        }

        RSA_free( rsa );
    }

    return ( decrypted_len );
}


/*
 *  「鍵対応文字列」の解放
 */
void
freeRSAkey( unsigned char *rsaString )
{
    if ( rsaString )
        free( rsaString );
}

/*
 *  「暗号化結果」もしくは「復号結果」の解放
 */
void
freeRSAbuffer( char *buffer )
{
    if ( buffer )
        free( buffer );
}
