/*
 *  multipart.c
 *      multipart/form-data ���������߂̊֐��Q
 *
 * History:
 * $Log: /comm/xmlRPC/multipart.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 10    09/03/23 16:02 Tsujimura543
 * MULITIPART_ITEM_TYPE_FILE �w�莞�ɃN���b�V�����邱�Ƃ�����
 * �s����C��
 * 
 * 9     08/11/17 22:12 Tsujimura543
 * static �� Thread static �ɕύX
 * 
 * 8     07/12/06 2:46 Tsujimura543
 * MULITIPART_ITEM_TYPE_FILE �ł̃t�@�C���A�b�v���[�h���Ƀo�b�t�@
 * �I�[�o�[�������邱�Ƃ�����s��ɑΏ�
 * 
 * 7     07/12/06 1:14 Tsujimura543
 * MULITIPART_ITEM_TYPE_FILE �ł̃o�C�i���t�@�C���̃A�b�v���[�h�ɑΉ�
 * 
 * 6     06/07/24 14:07 Tsujimura543
 * �R�����g�� typo ���C��
 * 
 * 5     05/11/17 19:14 Tsujimura543
 * �������� fix
 * 
 * 4     05/11/17 19:06 Tsujimura543
 * �e�L�X�g�t�@�C���̂݃A�b�v���[�h�\�Ƃ��������t���ŁA�t�@�C���̃A�b�v
 * ���[�h�ɑΉ� (�R�R���O�ȊO�ł̓���͖��m�F)
 * 
 * 3     05/11/17 15:14 Tsujimura543
 * MULITIPART_ITEM_TYPE_FILE ���T�|�[�g
 * 
 * 2     04/09/07 10:54 Tsujimura543
 * �]���ȃR�����g���폜
 *
 * 1     04/09/07 10:41 Tsujimura543
 * myprofile.c ���� multipart �֘A�̋��ʊ֐��𕪗�
 */

#include "xmlRPC.h"
#include "atomApi.h"
#include "multipart.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/multipart.c 1     09/05/14 3:46 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

char    *
getMultiPartID( void )
{
    Thread static char  buf[48];
    char                *p = makeNonce( NULL, BLOGKIND_ATOMAPI );
                            /* �b��I�� makeNonce() �𗬗p */
    p[13] = NUL;
    sprintf( buf, "---------------------------%s", p );

    return ( buf );
}

char    *
makeMultiPartItem( const char *separator, 
                   int        itemType,
                   const char *itemName,
                   long       itemValueInteger,
                   const char *itemValueString,
                   size_t     *sz )
{
    Thread static char      *buf   = NULL;
    Thread static size_t    bufSiz = 0;

    if ( itemType == MULITIPART_ITEM_TYPE_BUFFERFREE ) {
        if ( buf ) {
            free( buf );
            buf    = NULL;
            bufSiz = 0;
            return ( buf );
        }

        return ( NULL );
    }

    if ( itemType == MULITIPART_ITEM_TYPE_FILE ) {
        if ( itemValueString != NULL ) {
            FILEINF *fp = (FILEINF *)itemValueString;

            if ( buf ) {
                free( buf );
                buf    = NULL;
                bufSiz = 0;
            }

            bufSiz = strlen( (char *)(fp->bits) ) + BUFSIZ;
        }
    }
    else if ( !buf )
        bufSiz = MAX_CONTENT_SIZE * 2;

    if ( !buf ) {
        buf = (char *)malloc( bufSiz );
        if ( !buf )
            return ( NULL );
    }
    memset( buf, 0x00, bufSiz );

    sprintf( buf,
             "--%s\r\nContent-Disposition: form-data; name=\"%s\"",
             separator, itemName );
    switch ( itemType ) {
    case MULITIPART_ITEM_TYPE_INTEGER:
        sprintf( buf + strlen( buf ), "\r\n\r\n%d\r\n", itemValueInteger );
        break;

    case MULITIPART_ITEM_TYPE_STRING:
        if ( itemValueString && *itemValueString )
            sprintf( buf + strlen( buf ), "\r\n\r\n%s\r\n", itemValueString );
        else
            strcat( buf, "\r\n\r\n\r\n" );
        break;

    case MULITIPART_ITEM_TYPE_FILE:
        if ( itemValueString != NULL ) {
            FILEINF         *fp = (FILEINF *)itemValueString;
            unsigned char   *dst;

            dst = (unsigned char *)malloc( strlen( (char *)(fp->bits) ) );
            if ( dst ) {
                char    *tail;
                size_t  szz = 0;
                char    *p  = unbase64( fp->bits, dst, &szz );

                tail = buf + strlen( buf );
                sprintf( tail,
                         "; filename=\"%s\"\r\n"
                         "Content-Type: application/octet-stream\r\n\r\n",
                         fp->name );
                tail += strlen( tail );

                memcpy( tail, p, szz );
                tail += szz;
                strcpy( tail, "\r\n" );
                tail += strlen( tail );

                szz = tail - buf;

                free( dst );

                if ( sz )
                    *sz = szz;
            }
        }
        else
            strcat( buf,
                    "; filename=\"\"\r\n"
                    "Content-Type: application/octet-stream\r\n\r\n\r\n" );
        break;

    default:
        strcat( buf, "\r\n\r\n\r\n" );
        break;
    }

    return ( buf );
}

