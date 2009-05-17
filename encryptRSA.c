/*
 *  RSA �ɂ��Í����E���������s����
 *
 *        Copyleft (c) 2005 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  20 Sep 2005
 *
 * History:
 * $Log: /comm/xmlRPC/encryptRSA.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 6     06/03/09 18:31 Tsujimura543
 * OpenSSL �̃G���[��l�Ԃ��ǂ�ŕ����镶����ŕ\������悤�ɂ���
 * 
 * 5     05/09/21 22:39 Tsujimura543
 * freeRSAkey() �� freeRSAbuffer() ��ǉ�
 * 
 * 4     05/09/21 18:42 Tsujimura543
 * encodeByRSA() �̑�2������ in �݂̂��� in,out �ɕύX
 * 
 * 3     05/09/20 21:24 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 2     05/09/20 21:22 Tsujimura543
 * generateRSAkey() �����C�u�����O����J�ɂ��AencodeByRSA() ���ĂԂ���
 * �ňÍ����ł���悤�ɂ����B
 * 
 * 1     05/09/20 19:59 Tsujimura543
 * �ŏ��̔�
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

#define KEYBIT_LEN      192     /* ���� (�P��: �r�b�g)        */
#define KEYSTR_LEN      10240   /* ���Ή�������i�[�̈�T�C�Y */
#define RANDOMIZE_BASE  65537   /* �����̎� (�f��)            */

static BOOL first = TRUE;   /* SSL_load_error_strings() �����s�ς݂��ۂ� */
                            /*    (TRUE: �����s, FALSE: ���s�ς�)        */

/*
 *  ���̐���
 */
RSA *
generateRSAkey( unsigned char **rsaString )
{
    RSA     *rsa = NULL;

    /* ���Ή�������i�[�̈�̊m�� */
    *rsaString = (unsigned char *)malloc( KEYSTR_LEN );
    if ( *rsaString ) {
        /* RSA ������ */
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
            fprintf( stderr, "��: %s\n",
                     base64( *rsaString, strlen( (char *)(*rsaString) ) ) );
#endif
        }
    }

    return ( rsa );
}


/*
 *  RSA �ɂ��Í���
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
        /* �ȉ��́A�ŏ���1�񂾂����s����� OK */
        ERR_load_crypto_strings();
        first = FALSE;
    }

    numOfBlock = (strlen( targetString ) + (BLOCK_SIZE - 1)) / BLOCK_SIZE;

    if ( !rsaString )
        return ( crypted_len );
    if ( *rsaString && **rsaString ) {
        /* RSA���̕��� */
        rsa = recoveryRSAkey( *rsaString );
    }
    else {
        /* RSA���̐��� */
        rsa = generateRSAkey( rsaString );
    }
    if ( rsa ) {
        /* �Í������ʊi�[�̈�̊m�� */
        *cryptedBuffer = (unsigned char *)malloc( RSA_size(rsa) * numOfBlock );
        if ( *cryptedBuffer ) {
            /* �Í��� */
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
 *  ���̕���
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
 *  RSA �ɂ�镜��
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
        /* �ȉ��́A�ŏ���1�񂾂����s����� OK */
        ERR_load_crypto_strings();
        first = FALSE;
    }

    numOfBlock = (crypted_len + (ENCBLOCK_SIZE - 1)) / ENCBLOCK_SIZE;

    /* RSA��񕜌� */
    rsa = recoveryRSAkey( rsaString );
    if ( rsa ) {
        /* �������ʊi�[�̈�̊m�� */
        *targetString = (char *)malloc( RSA_size(rsa) * numOfBlock );
        if ( *targetString ) {
            /* ���� */
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
                    /* ����: �G���[���������Ă��f�R�[�h���̂͐������Ă��� */
                    /*       ���Ƃ�����                                   */
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
 *  �u���Ή�������v�̉��
 */
void
freeRSAkey( unsigned char *rsaString )
{
    if ( rsaString )
        free( rsaString );
}

/*
 *  �u�Í������ʁv�������́u�������ʁv�̉��
 */
void
freeRSAbuffer( char *buffer )
{
    if ( buffer )
        free( buffer );
}
