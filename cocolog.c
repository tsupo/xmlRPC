/*
 *  cocolog.c
 *      �R�R���O �̊Ǘ���ʂƒ��ڑΘb���A�t�@�C�����A�b�v���[�h���鏈��
 *
 * History:
 * $Log: /comm/xmlRPC/cocolog.c $
 * 
 * 2     09/05/22 21:07 tsupo
 * �u1.264�Ł�1.265�Łv�̕ύX����荞��
 * 
 * 17    09/05/22 17:45 Tsujimura543
 * uploadCocologFiles() ���C���B�A�b�v���[�h�������̃t�@�C�����擾����
 * ���ŋ߂̃R�R���O�̃t�@�C���}�l�[�W���̎d�l�ɍ����悤�ɍX�V
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 16    07/12/06 1:46 Tsujimura543
 * uploadCocologFiles() ��ύX�A�o�C�i���t�@�C���̃A�b�v���[�h�ɑΉ�����
 * 
 * 15    07/10/09 19:51 Tsujimura543
 * dputs(), dprintf() �𓱓�
 * 
 * 14    07/09/28 20:57 Tsujimura543
 * realloc����T�C�Y���Ԉ���Ă���(���̃T�C�Y���w�肵�Ă���)�̂��C��
 * 
 * 13    07/09/28 17:15 Tsujimura543
 * response�i�[�̈悪�����������ꍇ�́Arealloc�������čĎ��s����悤
 * �ɂ��Ă݂�
 * 
 * 12    07/09/28 16:49 Tsujimura543
 * (1) DEBUG_FOR_ADS �����𐳎��ȃf�o�b�O�p�@�\�Ƃ��Ď�荞��
 * (2) �A�b�v���[�h�ς݃t�@�C����������x�ȏ㑽���ƁAmagic_token �̎擾
 *     �Ɏ��s����s������邱�Ƃ������B�Ƃ肠�����Aresponse�i�[�̈��
 *     �T�C�Y��啝�ɑ��₷���ƂŎb��Ή�
 * 
 * 11    07/01/22 18:38 Tsujimura543
 * �R�����g(typo)���C��
 * 
 * 10    06/12/12 11:49 Tsujimura543
 * loginCocologFiles() �̏I�����ɂ� encodeURL() ����Ɨ̈���������
 * �悤�ɂ���
 * 
 * 9     06/12/04 13:35 Tsujimura543
 * �R�����g���C��
 * 
 * 8     06/12/04 13:34 Tsujimura543
 * (1) 65536�o�C�g���傫�ȃt�@�C�����A�b�v���[�h���悤�Ƃ���ƁA������
 *     �I�[�o�[��������������s��ɑΏ�
 * (2) �A�b�v���[�h���悤�Ƃ��Ă���t�@�C���̃T�C�Y�ɉ����āA�^�C���A�E
 *     �g���Ԃ�ݒ肵�����悤�ɂ���
 * 
 * 7     06/10/20 21:39 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 6     06/07/14 16:23 Tsujimura543
 * �����X�^��������f�o�b�O�o�[�W���� (DEBUG_FOR_ADS)
 * 
 * 5     06/03/15 18:31 Tsujimura543
 * getMagicToken() �� static ��
 * 
 * 4     06/03/15 18:25 Tsujimura543
 * �R�R���O�t���[�ł̃g�b�v�f�B���N�g��(..���w�肵���ꍇ)�̃A�b�v���[�h�ɂ�
 * �Ή����� (����m�F�ς�)
 * 
 * 3     06/03/14 23:39 Tsujimura543
 * uploadFile() �� deleteFile() ���R�R���O�t���[�ɂ��Ή�������
 * 
 * 2     06/03/14 20:53 Tsujimura543
 * deleteCocologFiles() ��ǉ�
 * 
 * 1     05/11/17 16:07 Tsujimura543
 * �V�K�쐬
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
        const char *path,           // (I)   �J�����g�f�B���N�g��
        char       *magic_token,    // (O)   magic_token �̒l
        char       **response,      // (I/O) ��Ɨp (��M�o�b�t�@)
        size_t     *sz,             // (I)   ��M�o�b�t�@�T�C�Y
        char       *cookie          // (I/O) �N�b�L�[
    )
{
    char    targetURL[MAX_URLLENGTH];

    // �R�R���O�t���[�̏ꍇ�̂� magic_token �����K�v����
    //   (�����炭 �]���̃R�R���O�� TypePad 1.6 �x�[�X�Ɉڍs������A
    //    magic_token ���g���悤�ɂȂ���̂Ǝv����̂ŁA�����ɔ���
    //    �Ă���)
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
        dprintf( "getMagicToken: magic_token �擾%s\n",
                 *magic_token ? "����" : "���s" );

    return ( magic_token );
}

int
loginCocologFiles( const char *username,    // (I) ���[�U��
                   const char *password,    // (I) �p�X���[�h
                   char       *cookie )     // (O) �N�b�L�[
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
             encodeURL(sjis2utf("���O�C��")) );
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
 //     ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
 //     if ( xmlrpc_p->verbose )
 //         dputs( "loginCocologFiles: login���s (�T�[�o�Ƃ̒ʐM���s)\n" );
 // }
 /* else */ if ( *response ) {
        char    targetString[BUFSIZ];
        sprintf( targetString, "| %s����", username );
        if ( strstr( response, sjis2utf(targetString) ) != NULL ) {
            ret = 1;    /* ���O�C������ */
            if ( xmlrpc_p->verbose )
                dputs( "loginCocologFiles: login����\n" );
        }
        else {
            ret = 0;    /* ���O�C�����s */
            if ( xmlrpc_p->verbose )
                dputs( "loginCocologFiles: login���s (���[�U���܂��̓p�X���["
                       "�h���Ⴄ�A���邢�̓R�R���O�̎d�l���ς����)\n" );
        }
    }
    else {
        ret = 0;        /* �T�[�o�Ƃ̒ʐM���s */
        if ( xmlrpc_p->verbose )
            dputs( "loginCocologFiles: login���s (�T�[�o�Ƃ̒ʐM���s)\n" );
    }

    encodeURL( NULL );
    free( response );
    free( request  );

    return ( ret );
}

int
uploadCocologFiles( FILEINF *fileInf, // (I)   �A�b�v���[�h����t�@�C���Ɋւ�
                                      //       ����
                    char    *url,     // (O)   �A�b�v���[�h�����t�@�C���� URL
                    char    *cookie ) // (I/O) �N�b�L�[
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
        dprintf( "uploadCocologFiles: �A�b�v���[�h���悤�Ƃ��Ă���t�@�C��"
                 " �� %s\n",
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

    /* magic_token ���擾 */
    getMagicToken( "", magic_token, &response, &sz, cookie );

    /* �t�@�C�����A�b�v���[�h */
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
                               encodeURL(sjis2utf("�A�b�v���[�h")),
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
                                    // �T�C�Y�ɔ�Ⴕ���^�C���A�E�g���Ԃ�ݒ�
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               contentType,
                               request, response, cookie,
                               NULL, NULL );
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT ); // �f�t�H���g�l�ɖ߂��Ă���

    /* url �擾 */
    url[0] = NUL;
    if ( response[0] ) {
        char    *p = strstr( response, "\"/t/app/control/files\"" );
        char    *q = strstr( response, "id=\"duplicate_file\"" );
        char    *r;

        if ( xmlrpc_p->verbose )
            dputs( "uploadCocologFiles: �A�b�v���[�h���N�G�X�g���s����\n" );

        if ( ( r = strrchr( fileInf->name, '/' ) ) == NULL )
            r = fileInf->name;
        else
            r++;

        if ( q ) {
            // �u�������O�̌Â��t�@�C�������̃t�H���_���ɂ���܂��v�̏ꍇ
            char    temp[32];
            char    *s = strstr( q, "name=\"temp\" value=\"" );

            if ( xmlrpc_p->verbose )
                dputs( "uploadCocologFiles: �������O�̌Â��t�@�C����"
                       "���̃t�H���_���ɂ���܂�\n" );

            p = NULL;
            if ( s ) {
                char    *t;
                s += 19;
                t = strchr( s, '"' );
                strncpy( temp, s, t - s );
                temp[t - s] = NUL;

                // �t�@�C����u������
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
                             encodeURL(sjis2utf("�t�@�C����u�������܂�")) );
                else
                    sprintf( request,
                             "__mode=upload&"
                             "temp=%s&"
                             "path=&"
                             "name=%s&"
                             "overwrite_yes=%s",
                             temp, r,
                             encodeURL(sjis2utf("�t�@�C����u�������܂�")) );
                setUpReceiveBuffer( response, sz );
                ret = httpPostWithSession(
                            xmlrpc_p->webServer, xmlrpc_p->webPage,
                            "application/x-www-form-urlencoded",
                            request, response, cookie,
                            NULL, NULL );
                if ( response[0] ) {
                    if ( xmlrpc_p->verbose )
                        dputs("uploadCocologFiles: �u�����N�G�X�g���s����\n");
                    p = strstr( response, "\"/t/app/control/files\"" );
                }
                else {
                    if ( xmlrpc_p->verbose )
                        dputs("uploadCocologFiles: �u�����N�G�X�g���s���s\n");
                }
            }
        }

        if ( p ) {
            char    targetString[BUFSIZ];

            p += 22;
            sprintf( targetString, ">%s</a>", r );
            q = strstr( p, targetString );
            if ( !q ) {
                /* �t�@�C�����A�b�v���[�h����ƃt�@�C�������̑啶���������� */
                /* �ɕς����Ă��܂����߁A�ȉ��̑΍�����{                 */
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
                            dprintf( "uploadCocologFiles: �A�b�v���[�h����"
                                     "�t�@�C����URL �� %s\n",
                                     url );
                    }
                }
            }
        }
    }
    else {
        if ( xmlrpc_p->verbose )
            dputs( "uploadCocologFiles: �A�b�v���[�h���N�G�X�g���s���s\n" );
    }

    encodeURL( NULL );
    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

int
deleteCocologFiles( const char *url,        // (I)   �폜�������t�@�C���� URL
                    char       *cookie )    // (I/O) �N�b�L�[
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
        dprintf( "deleteCocologFiles: �폜���悤�Ƃ��Ă���t�@�C��(URL)"
                 " �� %s\n",
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

    /* magic_token ���擾 */
    getMagicToken( path, magic_token, &response, &sz, cookie );

    /* �t�@�C�����폜 */
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
                     encodeURL( sjis2utf("�폜����") ) );
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
                     encodeURL( sjis2utf("�폜����") ) );
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
                     encodeURL( sjis2utf("�폜����") ) );
        else
            sprintf( request,
                     "type=file&"
                     "__mode=delete&"
                     "path=&"
                     "id=%s&"
                     "submit=%s",
                     filename,
                     encodeURL( sjis2utf("�폜����") ) );
    }
    setUpReceiveBuffer( response, sz );
    ret = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                               "application/x-www-form-urlencoded",
                               request, response, cookie,
                               NULL, NULL );
    if ( response[0] ) {
        ret = 1;
        if ( xmlrpc_p->verbose )
            dputs( "deleteCocologFiles: �폜���N�G�X�g���s����\n" );
    }
    else {
        ret = 0;
        if ( xmlrpc_p->verbose )
            dputs( "deleteCocologFiles: �폜���N�G�X�g���s���s\n" );
    }
    encodeURL( NULL );

    free( response );
    free( request  );

    return ( ret == -1 ? 0 : 1 );
}

