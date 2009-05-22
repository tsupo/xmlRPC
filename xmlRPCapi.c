/*
 *  xmlRPCapi.c
 *
 *    XML-RPC API �T�|�[�g���C�u����
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2009 by H.Tsujimura
 *      written by H.Tsujimura
 *
 * History:
 * $Log: /comm/xmlRPC/xmlRPCapi.c $
 * 
 * 2     09/05/22 21:07 tsupo
 * �u1.264�Ł�1.265�Łv�̕ύX����荞��
 * 
 * 53    09/05/22 17:42 Tsujimura543
 * �\�[�X�𐮗�
 * 
 * 52    09/05/22 17:40 Tsujimura543
 * uploadFile() ���C��(�R�R���O�� .. �ւ̃t�@�C���A�b�v���[�h���A�R�R���O
 * �ւ̃��O�C���������s�̕���p�ŃA�b�v���[�h�Ώۂ̃t�@�C���̒��g���i�[��
 * �Ă��郁�����̈�̓��e���j�󂳂�Ă��܂��s���������)
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 51    09/03/20 17:45 Tsujimura543
 * �E�F�u���u���O�� XML-RPC API �o�R�ł̓��e�A����m�F�I��
 * 
 * 50    09/03/17 22:42 Tsujimura543
 * Windows Live Spaces (����уE�F�u���u���O) �����̏�����ǉ�
 * 
 * 49    09/03/16 19:17 Tsujimura543
 * getCategories() ��ǉ�
 * 
 * 48    07/12/14 0:10 Tsujimura543
 * isActive() ���������񌳂ɖ߂�
 * 
 * 47    07/12/13 22:23 Tsujimura543
 * isActive() ��������
 * 
 * 46    07/12/06 1:49 Tsujimura543
 * uploadFile() ���̕s�v�ȃR�[�h���폜
 * 
 * 45    07/10/29 20:04 Tsujimura543
 * XML-RPC API �o�R�ł� ���v���O! �ւ̓��e�ɑΉ�
 * 
 * 44    07/10/09 19:41 Tsujimura543
 * dputs(), dprintf() �𓱓�
 * 
 * 43    07/09/28 16:48 Tsujimura543
 * DEBUG_FOR_ADS �����𐳎��ȃf�o�b�O�p�@�\�Ƃ��Ď�荞��
 * 
 * 42    07/09/07 20:52 Tsujimura543
 * http�ʐM�̃X���b�h�Ԕr������Ή�
 * 
 * 41    07/03/03 15:23 Tsujimura543
 * sjis2utf() �� NULL ��Ԃ��ꍇ�̑΍�����{
 * 
 * 40    07/02/26 16:21 Tsujimura543
 * editPostEx() ���h���R���u���O�ɑΉ�������
 * 
 * 39    07/02/24 1:59 Tsujimura543
 * XML-RPC API �o�R�ł̃h���R���u���O�ւ̓��e�ɑΉ�
 * (JUGEM �Ɋւ��ẮA���ɓ��ʂȏ����������Ȃ��Ă� XML-RPC API �o�R�ł�
 * ���e�ɐ�������)
 * 
 * 38    06/12/04 13:36 Tsujimura543
 * newMediaObject() ���C��(�A�b�v���[�h���悤�Ƃ��Ă���t�@�C���̃T�C�Y
 * �ɉ����ă^�C���A�E�g���Ԃ̒l��ύX����悤�ɂ���)
 * 
 * 37    06/10/19 18:44 Tsujimura543
 * sendUpdateExtendedPing() ��ǉ�
 * 
 * 36    06/10/07 1:34 Tsujimura543
 * http(������M�҂�)�^�C���A�E�g���Ԃ�ݒ�ύX�ł���悤�ɂ���
 * 
 * 35    06/09/08 10:14 Tsujimura543
 * setPostCategories() ���C�BFC2blog �ł��J�e�S���̐ݒ肪�ł���悤��
 * �Ȃ������Ƃ��m�F�B
 * 
 * 34    06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 33a   06/09/03 20:17 tsupo
 * cookie �܂����C��
 * 
 * 33    06/09/02 1:12 Tsujimura543
 * http�ʐM���s�����ǂ������`�F�b�N�ł���֐���ǉ�����
 * 
 * 32    06/07/24 20:10 Tsujimura543
 * _httpExecute() �̃o�b�t�@�I�[�o�[�����h�~�@�\�𗘗p����悤�ɂ���
 * 
 * 31    06/07/14 16:23 Tsujimura543
 * �����X�^��������f�o�b�O�o�[�W���� (DEBUG_FOR_ADS)
 * 
 * 30    06/03/14 23:39 Tsujimura543
 * uploadFile() �� deleteFile() ���R�R���O�t���[�ɂ��Ή�������
 * 
 * 29    06/03/14 20:53 Tsujimura543
 * deleteFile() ��ǉ�
 * 
 * 28    05/12/16 13:52 Tsujimura543
 * �R�R���O�ł̃G���[�������� response �� BUFSIZ * 4 �����傫���ꍇ��
 * ����(�T�[�o�����׎��ɍč\�z���悤�Ƃ����ꍇ)���߁A�b��I�ȑ΍�����{
 * 
 * 27    05/11/17 21:31 Tsujimura543
 * http �ɂ�鑗�M�\�ȓd���T�C�Y�̏�����������̋�������ǂ��܂ł�
 * �傫���ł���悤�ɂ��� (�����T�C�Y�͏]���̒l)
 * 
 * 26    05/11/17 16:10 Tsujimura543
 * uploadFile() ���C�����A�R�R���O�̏ꍇ�̂݁A�T�C�g�g�b�v�f�B���N�g���ւ�
 * �A�b�v���[�h���T�|�[�g (cocolog.c �ƘA�g)
 * 
 * 25    05/01/04 15:08 Tsujimura543
 * �R�����g���C��
 * 
 * 24    05/01/04 15:05 Tsujimura543
 * newMediaObject() �ŁA�t�@�C������ error ���܂܂��ꍇ�A�A�b�v���[�h��
 * ���s�����ƌ딻�肵�Ă��܂��s��ɑΏ�
 * 
 * 23    04/12/28 15:34 Tsujimura543
 * �R�R���O�ł̃G���[�������� response �� BUFSIZ ���傫��(1200�o�C�g��)
 * �ꍇ�����邽�߁Aresponse ��ÓI�Ɋm�ۂ��Ă���ꍇ�� BUFSIZ * 4 �̑傫
 * �����m�ۂ���悤�ɂ��Ă݂�
 * 
 * 22    04/12/16 19:11 Tsujimura543
 * uploadFile() �̑�4�������󕶎���̂Ƃ��A�]���� / ���t���Ă��܂��̂�
 * �����邽�߁A��4������ NULL �̏ꍇ�Ə����𓯂��ɂ����B
 * 
 * 21    04/11/01 21:02 Tsujimura543
 * �x�����x�� 4 �ł� warning ���\�Ȍ��茸�炵�Ă݂�
 * 
 * 20    04/11/01 19:53 Tsujimura543
 * �w�u���������v����̂������߁x�������I�Ɏ���
 * 
 * 19    04/10/15 15:20 Tsujimura543
 * NewsHandler �� blog ID, post ID �͋���32byte�ł��邽�߁A�̈�𑝂₵��
 * �Ή�����
 * 
 * 18    04/09/28 17:04 Tsujimura543
 * dc:creator �̑��݂��Ȃ� RSS (�A���[�o�u���O) ��������悤�ɂ���
 * 
 * 17    04/08/31 12:06 Tsujimura543
 * getStringFromItem()�AgetDateTimeFromItem() �� xmlRPCutil.c �Ɉړ�
 * 
 * 16    04/08/30 18:26 Tsujimura543
 * getRecentPostTitlesFromRSS ��ǉ�
 * 
 * 15    04/08/27 18:12 Tsujimura543
 * JUGEM, excite�u���O, ���v���O �̊e�X�̑Ή�������ʃ\�[�X�t�@�C���Ƃ���
 * �����Ɨ�������
 * 
 * 14    04/08/27 16:12 Tsujimura543
 * ���v���O�Ή�
 * 
 * 13    04/08/27 11:25 Tsujimura543
 * excite�u���O�ւ̓��e���A�J�e�S��ID��1(������)�̏ꍇ�A�J�e�S���̑I������
 * �\������悤�ɂ���
 * 
 * 12    04/08/27 10:47 Tsujimura543
 * postExciteBlog() ���Őݒ肷�� htmlflag �̒l�� 0 ���� 1 �ɕύX����
 * 
 * 11    04/08/26 23:00 Tsujimura543
 * �Eexcite�u���O�֓��e����Ƃ��Ƀt���O�̈Ӗ����t�ɂ��Ă����̂��C��
 *   (���J�A�R�����g�A�g���b�N�o�b�N�ɂȂ�悤�ɏC������)
 * �Eexcite�u���O�ւ̓��e�����ɃJ�e�S��ID����J�e�S�����������@�\��t��
 * 
 * 10    04/08/26 22:20 Tsujimura543
 * excite�u���O�ɓ��e�ł��邱�Ƃ��m�F
 * 
 * 9     04/08/25 16:58 Tsujimura543
 * loginJugem, postJugem ��ǉ�
 * 
 * 8     04/08/20 18:45 Tsujimura543
 * Web�T�[�o��IIS�̏ꍇ�A�G���[���ɑ傫��html�𑗂��Ă��邱�Ƃ�����(�o�b�t�@
 * �I�[�o�[��������������)���ۂւ̑΍�����{
 * 
 * 7     04/08/17 12:23 Tsujimura543
 * getRecentPostTitlesOnBloggerAPI, getRecentPostTitlesOnMetaWeblog ��ǉ�
 * 
 * 6     04/08/16 19:08 Tsujimura543
 * getRecentPostTitles(), getRecentPostsEx() ���C��(��������XML�̓��e�C��)
 * 
 * 5     04/07/14 18:50 Tsujimura543
 * Movable Type API �֘A�̊֐��̎d�l������
 * 
 * 4     04/07/12 15:50 Tsujimura543
 * metaWeblog API �֘A�̊֐��̎d�l������
 * 
 * 3     04/07/09 20:24 Tsujimura543
 * blogger API �֘A�̊֐��̎d�l������
 * 
 * 2     04/07/07 11:50 Tsujimura543
 * RCS �ɂ��Ő��Ǘ����� VSS �ɂ��Ő��Ǘ��Ɉڍs
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
 *  update ping �̑��M
 *      weblogUpdates.ping
 *          ����: update ping (blog�X�V�ʒm) �𑗐M���܂�
 *          ����: String weblogname,
 *                String weblogURL
 *          �Ԃ�l: ��������� �����o�[ flerror �̒l�� 0 (false) �ł���\��
 *                  �̂��Ԃ�܂��B
 *                  ���s����� �����o�[ flerror �̒l�� 1 (true) �ł���\����
 *                  ���Ԃ�܂��B
 */

BOOL
sendUpdatePing( const char *weblogName, // (I) blog �̖��O [Shift_JIS]
                const char *weblogURL ) // (I) blog �� URL
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
        /* ���M�ɐ��������ꍇ */
        char    *p, *q;

        if ( ( p = strstr( response, "flerror" ) ) != NULL ) {
            if ( ( q = strchr( p + 7, '0' ) ) != NULL )
                ret = TRUE; /* update ping ���� */
        }
    }

    return ( ret );
}

BOOL
sendUpdateExtendedPing( const char *weblogName, // (I) blog �̖��O [Shift_JIS]
                        const char *weblogURL,  // (I) blog �� URL
                        const char *targetURL,  // (I) ping �Ώۂ� URL
                        const char *feedURL )   // (I) RSS/Atom �t�B�[�h�� URL
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
        /* ���M�ɐ��������ꍇ */
        char    *p, *q;

        if ( ( p = strstr( response, "flerror" ) ) != NULL ) {
            if ( ( q = strchr( p + 7, '0' ) ) != NULL )
                ret = TRUE; /* update ping ���� */
        }
    }

    return ( ret );
}


/*
 *  blogger API
 */

/*
 *      blogger.newPost
 *          ����: �V�����L��������܂��D�܂��C���J���邱�Ƃ��ł��܂��D
 *          ����: String  appkey,
 *                String  blogid,
 *                String  username,
 *                String  password,
 *                String  content,
 *                boolean publish
 *          �Ԃ�l: ��������ƁCString postid ���V�����L���� ID �l�Ƃ���
 *                  �����܂��D
 *                  ���s������Cfault ���Ԃ�܂��D
 */

BOOL
newPost( const char *blogID,    // (I) blog ID
         const char *userName,  // (I) ���[�U��
         const char *password,  // (I) �p�X���[�h
         const char *content,   // (I) �L�����e [UTF-8]
         BOOL       publish,    // (I) ���e��� (FALSE: ������ / TRUE: ���J)
         char       *postID )   // (O) ���e��̋L��ID
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
 *          ����: ���ɂ���L���̏���ҏW���܂��D
 *          ����: String  appkey,
 *                String  postid,
 *                String  username,
 *                String  password,
 *                String  content,
 *                boolean publish
 *          �Ԃ�l: ��������� true ���C���s����� fault ���Ԃ�܂��D
 */

BOOL
editPost( const char *postID,   // (I) �L��ID
          const char *userName, // (I) ���[�U��
          const char *password, // (I) �p�X���[�h
          const char *content,  // (I) �L�����e [UTF-8]
          BOOL       publish )  // (I) ���e��� (FALSE: ������ / TRUE: ���J)
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
 *          ����: �L�����폜���܂��D
 *          ����: String  appkey,
 *                String  postid,
 *                String  username,
 *                String  password,
 *                boolean publish
 *          �Ԃ�l: ��������� true�C���s����� fault ���Ԃ�܂��D
 */

BOOL
deletePost( const char *postID,     // (I) �L��ID
            const char *userName,   // (I) ���[�U��
            const char *password,   // (I) �p�X���[�h
            BOOL       publish )    // (I) ���e��� [���������]
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
 *          ����: �ŐV�̋L�����V�X�e������Ƃ��Ă��܂��D
 *          ����: String appkey,
 *                String blogid,
 *                String username,
 *                String password,
 *                int    numberOfPosts
 *          �Ԃ�l: ��������ƁC�\���̂̔z�񂪕Ԃ��Ă��܂��D 
 *                  �\���̂ɂ́C
 *                      ISO.8601 dateCreated,
 *                      String   userid,
 *                      String   postid,
 *                      String   content
 *                  ���܂܂�܂��D(���͕s��)
 *                  ���s����ƁCfault ���Ԃ�܂��D
 *              ����: dateCreated �́Cblogid �� weblog �ɂ����Ă̎��ԑт�
 *                    �Ȃ��Ă��܂��D
 */

int
getRecentPosts( const char *blogID,         // (I) blog ID
                const char *userName,       // (I) ���[�U��
                const char *password,       // (I) �p�X���[�h
                int        *numOfEntries,   // (I) �擾�������L�����̐�
                                            // (O) ���ۂɎ擾�����L�����̐�
                CONTENTINF *contentInfo )   // (O) �擾�����L�����
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
 *      ����: �����肳�񂪓��e�ł��� weblog �̌Q���Ԃ��܂��D
 *      ����: String appkey,
 *            String username,
 *            String password
 *      �Ԃ�l: ��������ƁC�\���̂̔z�񂪕Ԃ��Ă��܂��D 
 *              �\���̂ɂ́C
 *                  String url,
 *                  String blogid,
 *                  String blogName
 *              ���܂܂�܂��D 
 *              ���s����ƁCfault ���Ԃ�܂��D
 */

BOOL
getUsersBlogs( const char *userName,    // (I) ���[�U��
               const char *password,    // (I) �p�X���[�h
               char       *response )   // (O) blogger.getUsersBlogs ��
                                        //     ���s���� (XML)
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
 *      ����: �����肳��̏���Ԃ��܂��D
 *      ����: String appkey,
 *            String username,
 *            String password
 *      �Ԃ�l: ��������ƁC�\���̂̔z�񂪕Ԃ��Ă��܂��D 
 *              �\���̂ɂ́C
 *                  String userid,
 *                  String firstname,
 *                  String lastname,
 *                  String nickname,
 *                  String email,
 *                  String url
 *              ���܂܂�܂��D 
 *              ���s����ƁCfault ���Ԃ�܂��D
 *          ����: firstname �́CMovable Type �̃��[�U���̂����C�ŏ��̃X�y�[�X
 *                �̂Ƃ���܂ł̂��̂ł��D 
 *                lastname �́C�ŏ��̃X�y�[�X�ȍ~�̂��̂ł��D
 */

int
getUserInfo( const char *userName,      // (I) ���[�U��
             const char *password,      // (I) �p�X���[�h
             int        *numberOfUsers, // (I) �擾���������[�U���̐�
                                        // (O) ���ۂɎ擾�������[�U���̐�
             USERINF    *userInfo )     // (O) �擾�������[�U���
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
            /* �Ԃ��Ă����̂��z��ł͂Ȃ��ꍇ        */
            /*   �� ���[�U�� == 1 �Ƃ݂Ȃ��ď������s */
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
 *      ����: �V�����L��������܂��D �܂��C���J���邱�Ƃ��ł��܂��D
 *      ����: String  blogid,
 *            String  username,
 *            String  password,
 *            struct  content,
 *            boolean publish
 *        ����: content �\���̂́C���̂悤�ȕW���I�ȍ��ڂ��܂݂܂�: 
 *                  String   title,       �L���̌���
 *                  String   description, �L���̖{��
 *                  ISO.8601 dateCreated, �L�������e���ꂽ�����D 
 *                  String[] categories,  (�ȗ���) [Windows Live Spaces �p��
 *                                        ���āA�V���ɒǉ����ꂽ�p�����[�^�B
 *                                        Movable Type �ł͂��̈����ɂ͑Ή�
 *                                        ���Ă��Ȃ�]
 *              ����ɉ����āCMovable Type �ł͎���7�̍��ڂɒl�����ēn����
 *              �Ƃ��ł��܂�: 
 *                  int      mt_allow_comments, allow_comments ���ڂւ̒l; (�R
 *                                              �����g���󂯓���邩�ۂ�)
 *                  int      mt_allow_pings,   allow_pings ���ڂւ̒l; (�g���b
 *                                             �N�o�b�NPing���󂯓���邩�ۂ�)
 *                  String   mt_convert_breaks, convert_breaks ���ڂ̒l; (�L��
 *                                              �{���̉��s�̈�����)
 *                  String   mt_text_more,      �ǋL�̒l; 
 *                  String   mt_excerpt,        �T�v�̒l;
 *                  String   mt_keywords,       �L�[���[�h�̒l;
 *                  array    mt_tb_ping_urls,   ���̋L���ɑ΂���g���b�N�o�b�N
 *                                              Ping �� URL �̌Q��;
 *              �ł��D 
 *              dateCreated ���g���Ȃ�CISO.8601 �`���łȂ��Ƃ����܂���D(�ȗ�
 *              �����ꍇ�͌��ݎ������w�肵�����̂Ƃ݂Ȃ����)
 *      �Ԃ�l: ��������ƁCString postid ���V�����L���� ID �l�Ƃ��ĕԂ��Ă���
 *              ��
 *              ���s����ƁCfault �ł��D
 */

BOOL
newPostEx( const char    *blogID,   // (I) blog ID
           const char    *userName, // (I) ���[�U��
           const char    *password, // (I) �p�X���[�h
           const CONTENT *content,  // (I) �L�����
           BOOL          publish,   // (I) ���e��� (FALSE:������ / TRUE:���J)
           char          *postID )  // (O) ���e��̋L��ID
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
 *      ����: ���ɂ���L���̏����X�V���܂��D
 *      ����: String  postid,
 *            String  username,
 *            String  password,
 *            struct  content,
 *            boolean publish
 *        ����: content �\���̂́C���̂悤�ȕW���I�ȍ��ڂ��܂݂܂�:
 *                  String   title,       �L���̌���
 *                  String   description, �L���̖{��
 *                  ISO.8601 dateCreated, �L�������e���ꂽ�����D 
 *                  String[] categories,  (�ȗ���) [Windows Live Spaces �p��
 *                                        ���āA�V���ɒǉ����ꂽ�p�����[�^�B
 *                                        Movable Type �ł͂��̈����ɂ͑Ή�
 *                                        ���Ă��Ȃ�]
 *              ����ɉ����āCMovable Type �ł͎���7�̍��ڂɒl�����ēn����
 *              �Ƃ��ł��܂��D
 *                  int      mt_allow_comments, allow_comments ���ڂւ̒l; (�R
 *                                              �����g���󂯓���邩�ۂ�)
 *                  int      mt_allow_pings,   allow_pings ���ڂւ̒l; (�g���b
 *                                             �N�o�b�NPing���󂯓���邩�ۂ�)
 *                  String   mt_convert_breaks, convert_breaks ���ڂ̒l; (�L��
 *                                              �{���̉��s�̈�����)
 *                  String   mt_text_more,      �ǋL�̒l; 
 *                  String   mt_excerpt,        �T�v�̒l;
 *                  String   mt_keywords,       �L�[���[�h�̒l;
 *                  array    mt_tb_ping_urls,   ���̋L���ɑ΂���g���b�N�o�b�N
 *                                              Ping �� URL �̌Q��;
 *             �ł��D dateCreated ���g���Ȃ�CISO.8601 �`���łȂ��Ƃ����܂���
 *      �Ԃ�l: ��������� true ���C���s����� fault ���Ԃ�܂��D
 */

BOOL
editPostEx( const char    *postID,  // (I) �L��ID
            const char    *userName,// (I) ���[�U��
            const char    *password,// (I) �p�X���[�h
            const CONTENT *content, // (I) �L�����
            BOOL          publish ) // (I) ���e��� (FALSE:������ / TRUE:���J)
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
 *      ����: �w�肵�����e�ɂ��Ă̏���Ԃ��܂��D
 *      ����: String postid,
 *            String username,
 *            String password
 *      �Ԃ�l: ��������ƁC���̗v�f���܂ލ\���̂��Ԃ��Ă��܂�:
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
 *                  String[] categories,  [Windows Live Spaces �p�Ƃ��āA�V
 *                  bool     publish,      ���ɒǉ����ꂽ�v�f�BMovable Type
 *                                         �ɂ͑��݂��Ȃ��B�t�� mt_ �Ŏn�܂�
 *                                         �v�f�� Windows Live Spaces �ł͑�
 *                                         �݂��Ȃ�]
 *              ���s����ƁCfault ���Ԃ�܂��D
 *          ����: link �� permaLink �́C�ǂ���� �~�ς���Ă���L���ւ� URL
 *                �ɂȂ�܂��D 
 *                mt_�ł͂��܂��Ă��鍀�ڂ́CmetaWeblog.getPost API �� Movable
 *                Type ���ǉ��������̂ł��D
 */

BOOL
getPost( const char   *postID,      // (I) �L��ID
         const char   *userName,    // (I) ���[�U��
         const char   *password,    // (I) �p�X���[�h
         CONTENTINFEX *contentInfo )// (I) �L�����
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
         * String   userid,            (Windows Live Spaces �ł͑��݂��Ȃ�)
         * ISO.8601 dateCreated,
         * String   postid,
         * String   description,
         * String   title,
         * String   link,
         * String   permaLink,         (Windows Live Spaces �ł͑��݂��Ȃ�)
         * String   mt_excerpt, (mt�g��: ���̃t�B�[���h�����݂���Ƃ͌���Ȃ�)
         * String   mt_text_more,      (mt�g��)
         * int      mt_allow_comments, (mt�g��)
         * int      mt_allow_pings,    (mt�g��)
         * String   mt_convert_breaks, (mt�g��)
         * String   mt_keywords;       (mt�g��)
         * String[] categories;        (Windows Live Spaces�g��)
         * boolean  publish;           (Windows Live Spaces�g��)
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

                /* �K�{�t�B�[���h */
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

                /* �ȗ��\�t�B�[���h (MovableType�Ǝ��g��) */
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

                /* Windows Live Spaces �Ǝ��g�� */
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
 *      ����: �ŋߓ��e���ꂽ�L���̌Q���Ԃ��܂��D
 *      ����: String blogid,
 *            String username,
 *            String password,
 *            int    numberOfPosts
 *      �Ԃ�l: ��������ƁC���̗v�f���܂ލ\���̂��Ԃ��Ă��܂��D 
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
 *                  String[] categories,  [Windows Live Spaces �p�Ƃ��āA�V
 *                  bool     publish,      ���ɒǉ����ꂽ�v�f�BMovable Type
 *                                         �ɂ͑��݂��Ȃ��B�t�� mt_ �Ŏn�܂�
 *                                         �v�f�� Windows Live Spaces �ł͑�
 *                                         �݂��Ȃ�]
 *              ���s����ƁCfault ���Ԃ�܂��D
 *          ����: dateCreated �́Cblogid �� weblog �ɂ����Ă̎��ԑтɂȂ���
 *                ���܂��D 
 *                link �� permaLink �́C�ǂ���� �~�ς���Ă���L���ւ� URL
 *                �ɂȂ�܂��D
 */

int
getRecentPostsEx( const char   *blogID,         // (I) �L��ID
                  const char   *userName,       // (I) ���[�U��
                  const char   *password,       // (I) �p�X���[�h
                  int          *numberOfPosts,  // (I) �擾����L���̐�
                                                // (O) ���ۂɎ擾�����L���̐�
                  CONTENTINFEX *contentInfo )   // (O) �擾�����L�����
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
         * String   permaLink,         (Windows Live Spaces �ł͑��݂��Ȃ�)
         * String   mt_excerpt, (mt�g��: ���̃t�B�[���h�����݂���Ƃ͌���Ȃ�)
         * String   mt_text_more,      (mt�g��)
         * int      mt_allow_comments, (mt�g��)
         * int      mt_allow_pings,    (mt�g��)
         * String   mt_convert_breaks, (mt�g��)
         * String   mt_keywords;       (mt�g��)
         * String[] categories;        (Windows Live Spaces�g��)
         * boolean  publish;           (Windows Live Spaces�g��)
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

                /* �K�{�t�B�[���h */
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

                /* �ȗ��\�t�B�[���h (MovableType�Ǝ��g��) */
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

                /* Windows Live Spaces �Ǝ��g�� */
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
 *      ����: �t�@�C���� web�T�[�o�ɓ]�����܂��D
 *      ����: String blogid,
 *            String username,
 *            String password,
 *            struct file
 *          ����: file �\���̂ɂ́C2�̍��ڂ�����܂�:
 *                    base64 bits (the base64 �ŕ��������ꂽ�C�t�@�C���̒��g)
 *                    String name (�t�@�C���� ). 
 *                type ���� (�t�@�C���̎��) �́C���̂Ƃ��떳������܂��D
 *      �Ԃ�l: �]�������t�@�C���ւ� URL ���Ԃ��Ă��܂��D
 */

BOOL
newMediaObject( const char *blogID,     // (I) blog ID
                const char *userName,   // (I) ���[�U��
                const char *password,   // (I) �p�X���[�h
                FILEINF    *fileInf,    // (I) �A�b�v���[�h����t�@�C���Ɋւ�
                                        //     ����
                char       *url )       // (O) �A�b�v���[�h�����t�@�C���� URL
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
        dprintf( "newMediaObject: �A�b�v���[�h���悤�Ƃ��Ă���t�@�C��"
                 " �� %s\n",
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
                                    // �T�C�Y�ɔ�Ⴕ���^�C���A�E�g���Ԃ�ݒ�
    r = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  NULL, buffer, response );
    setTimeoutTime( DEFAULT_HTTP_TIMEOUT ); // �f�t�H���g�l�ɖ߂��Ă���

    if ( response[0] != NUL ) {
        if ( xmlrpc_p->verbose )
            dputs( "newMediaObject: ���N�G�X�g���s����\n" );

        if ( strstr( response, "<methodResponse><fault><value>" ) ) {
            if ( strstr( response, "ERROR" ) ||
                 strstr( response, "error" )    )
                if ( strstr( response,
                             "The request or reply is too large." ) )
                    fprintf( stderr,
                     "�A�b�v���[�h���悤�Ƃ��Ă���t�@�C�����傫�����܂�\n" );
            fprintf( stderr, "�A�b�v���[�h�Ɏ��s���܂���\n" );
            if ( xmlrpc_p->verbose )
                dputs( "newMediaObject: �A�b�v���[�h���s "
                       "(�t�@�C�����傫������?)\n" );
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
                fprintf( stderr, "�A�b�v���[�h�Ɏ��s���܂���\n" );
                if ( xmlrpc_p->verbose )
                    dputs( "newMediaObject: �A�b�v���[�h���s "
                           "(�T�[�o����G���[������M)\n" );
            }
            else {
                ret = TRUE;

                /*
                 * String   url
                 */
                getSingleString( response, url );
                if ( xmlrpc_p->verbose )
                    dputs( "newMediaObject: �A�b�v���[�h����\n" );
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
 *      ����: �ŋߓ��e���ꂽ�L���̌Q����C�ш�ɂ₳�����Ԃ��܂��D
 *      ����: String blogid,
 *            String username,
 *            String password,
 *            int    numberOfPosts
 *      �Ԃ�l: ��������ƁC���̗v�f���܂ލ\���̂̔z�񂪕Ԃ��Ă��܂�:
 *                  ISO.8601 dateCreated,
 *                  String   userid,
 *                  String   postid,
 *                  String   title; 
 *              ���s����ƁCfault���Ԃ�܂��D
 *          ����: dateCreated �́Cblogid �� weblog �ɂ����Ă̎��ԑтɂȂ���
 *                ���܂��D
 */

int
getRecentPostTitles( const char *blogID,        // (I) blog ID
                     const char *userName,      // (I) ���[�U��
                     const char *password,      // (I) �p�X���[�h
                     int        *numberOfPosts, // (I) �擾����L�����̐�
                                                // (O) ���ۂɎ擾�����L�����
                                                //     �̐�
                     POSTINF    *postinf )      // (O) �擾�����L�����
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
 *      ����: ���� weblog �ɂ��邷�ׂĂ̕��ނ�Ԃ��܂��D
 *      ����: String blogid,
 *            String username,
 *            String password
 *      �Ԃ�l: ��������ƁC���̗v�f���܂ލ\���̂̔z�񂪕Ԃ��Ă��܂�:
 *                  String categoryId
 *                  String categoryName;
 *              ���s����ƁCfault ���Ԃ�܂��D
 */

int
getCategoryList( const char   *blogID,          // (I) blog ID
                 const char   *userName,        // (I) ���[�U��
                 const char   *password,        // (I) �p�X���[�h
                 long         *numOfCategories, // (I) �擾����J�e�S���̐�
                                                // (O) �擾�����J�e�S���̐�
                 CATLISTINF_t categories )      // (O) �擾�����J�e�S�����
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
 *      ����: ���̓��e�Ɏw�肳��Ă��镪�ނ����ׂĕԂ��܂��D
 *      ����: String postid,
 *            String username,
 *            String password
 *      �Ԃ�l: ��������ƁC���̗v�f���܂ލ\���̂̔z�񂪕Ԃ��Ă��܂�:
 *                  String  categoryName,
 *                  String  categoryId,
 *                  boolean isPrimary; 
 *              ���s����ƁCfault ���Ԃ�܂��D
 *          ����: isPrimary �́C���ނ����̕��ނ̑�ꕪ�ނ��ǂ����C�Ƃ������Ƃ�
 *                �Ӗ����܂��D
 */

int
getPostCategories( const char *postID,             // (I) �L��ID
                   const char *userName,           // (I) ���[�U��
                   const char *password,           // (I) �p�X���[�h
                   long       *numberOfCategories, // (I) �擾����J�e�S���̐�
                                                   // (O) �擾�����J�e�S���̐�
                   CATINF     *categories )        // (O) �擾�����J�e�S�����
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
 *      ����: �L���̕��ނ�ݒ肵�܂��D
 *      ����: String postid,
 *            String username,
 *            String password,
 *            array  categories
 *          ����: categories �́C���̗v�f���܂ލ\���̂̔z��ł�:
 *                    String  categoryId�C
 *                    boolean isPrimary�D 
 *                isPrimary ���g���C��ꕪ�ނ��w�肷�邱�Ƃ��\�ł��D 
 *                ���̃t���O���w�肵�Ȃ���΁C�z��̂ЂƂ߂̗v�f���C���̋L��
 *                �̑�ꕪ�ނɂȂ�܂��D
 *      �Ԃ�l: ��������� true ���C���s����� fault ���Ԃ�܂��D
 */

BOOL
setPostCategories( const char *postID,          // (I) �L��ID 
                   const char *userName,        // (I) ���[�U��
                   const char *password,        // (I) �p�X���[�h
                   long       numOfCategories,  // (I) �ݒ肷��J�e�S���̐�
                   CATEGORY   *categories )     // (I) �ݒ肷��J�e�S�����
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
 *      ����: �T�[�o�Œ񋟂���Ă��� XML-RPC �̌Ăяo�����@���擾���܂��D
 *      ����: �Ȃ�
 *      �Ԃ�l: �T�[�o�Œ񋟂���Ă���Ăяo�����@�̔z�񂪕Ԃ�܂��D
 */

int
getSupportedMethods( int  *numberOfMethods, // (I) �擾����Ăяo�����@�̐�
                                            // (O) �擾�����Ăяo�����@�̐�
                     char *methodList[] )   // (O) �擾�����Ăяo�����@�̈ꗗ
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
 *      ����: �T�[�o�Œ񋟂���Ă��镶�����`�v���O�C���Ɋւ�������擾���܂��D
 *      ����: �Ȃ�
 *      �Ԃ�l: String key
 *              String label
 *              ���܂ލ\���̂̔z�񂪂������Ă��܂��D 
 *              key �́C�������`�v���O�C������ʂ����ӂȕ�����ŁClabel �́C
 *              �����ǂ߂邩�����ɂ��������ł��D 
 *              key �́CnewPost��editPost�� mt_convert_breaks�ϐ��Ƃ��ēn����
 *              ��ׂ��l�ł��D
 */

int
getSupportedFilters( int       *numberOfFilters,// (I) �擾����t�B���^�̐�
                                                // (O) �擾�����t�B���^�̐�
                     FILTERINF *filterList )    // (O) �擾�����t�B���^���
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
 *      ����: �w�肵���L���ɑ���ꂽ �g���b�N�o�b�N Ping �̌Q����擾���܂��D 
 *            ������g���̂́C�w�肵���L���ւ� Ping �̌Q����v���O�����Ƃ���
 *            �擾���āC������ Ping ���ꂼ��ɁC�������������Ԃɍs���悤��
 *            �ꍇ�ł��傤�D 
 *            ���Ƃ��΁C����b��ɂ��Ă̋L���Ƃ���Ɍ��y���Ă���L�����琬
 *            �� web �O���t�����グ��悤�ȏꍇ�C�݂����ȁD
 *      ����: String postid
 *      �Ԃ�l: ���̗v�f���܂ލ\���̂̔z�񂪕Ԃ��Ă��܂�: 
 *                  String pingTitle (Ping ���Ă����L���̌���),
 *                  String pingURL (�L���� URL),
 *                  String pingIP (Ping ���Ă����z�X�g�� IP �A�h���X)�D
 */

int
getTrackbackPings(
        const char *postID,         // (I) �L��ID
        int        *numberOfPings,  // (I) �擾����g���b�N�o�b�N���
                                    // (O) �擾�����g���b�N�o�b�N���
        TBINF      *tbInfo          // (O) �擾�����g���b�N�o�b�N���
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
            /* �g���b�N�o�b�N�Ȃ� */
            free( response );
            *numberOfPings = numOfPings;

            return ( numOfPings );
        }

        /* �g���b�N�o�b�N���� */
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
 *      ����: weblog �ɂ��邷�ׂĂ̐ÓI�t�@�C�������J (�č\�z) ���܂��D 
 *            ����́C�V�X�e���ɋL���𓊍e���C�ۑ����邱�ƂƂ��Ȃ����Ƃł��D
 *            (�Ⴄ�̂́C���̕��@���� Ping ���s��Ȃ��C�Ƃ������Ƃł�)�D
 *      ����: String postid,
 *            String username,
 *            String password
 *      �Ԃ�l: ��������� true ���C���s����� fault ���Ԃ�܂��D
 */

BOOL
publishPost( const char *postID,    // (I) �L��ID
             const char *userName,  // (I) ���[�U��
             const char *password ) // (I) �p�X���[�h
{
    int     ret = FALSE, r;
    char    buffer[BUFSIZ];
    char    response[BUFSIZ * 8];   /* �R�R���O�ŃG���[��������3000byte���� */
    size_t  sz  = BUFSIZ * 8;       /* �������Ԃ��Ă��邱�Ƃ����邽�߁A�傫 */
                                    /* �߂Ɋm�ۂ��Ă���                     */
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
 *      ����: blogid, username, password
 *              Windows Live Spaces �ł�
 *                - blogid �͏�� "MyBlog" ���w�肷��
 *                - username �� Space��(�u���O��URL���̃u���O���Ƀ��j�[�N��
 *                  �����񕔕�)���w�肷��
 *      �Ԃ�l: �J�e�S���̐����A�ȉ��̓��e�̍\���̂�Ԃ��B
 *                  description,
 *                  htmlUrl,
 *                  rssUrl
 *
 *              �������AWindows Live Spaces (����� �E�F�u���u���O)�ł́A
 *              �ȉ��̓��e�̍\���̂�Ԃ�
 *                  description,
 *                  title,
 *              (description �� title �ɂ́A�Ƃ��Ɂu�J�e�S�����v���i�[�����)
 */

int
getCategories( const char   *blogID,
               const char   *userName,
               const char   *password,
               long         *numOfCategories, /* �J�e�S���̐� */
               CATEGORIES_t categories )      /* �J�e�S��     */
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
 * XML-RPC API �𗘗p�������[�e�B���e�B�֐��Q
 */

/*
 * blog ID �̎擾
 *    ����:   ���[�U��, �p�X���[�h, �擾���� blog ���i�[�ꏊ
 *    �߂�l: �擾�ɐ��������ꍇ TRUE�A���s�����ꍇ FALSE
 */

int
getBlogID( const char *userName,    // (I) ���[�U��
           const char *password,    // (I) �p�X���[�h
           char       *blogID )     // (O) �ŏ��Ɍ������� blog ID
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
 * blog ID �̎擾
 *    ����:   ���[�U��, �p�X���[�h, �擾���� blog ���i�[�ꏊ
 *    �߂�l: �V�X�e�����ɑ��݂��� blog �̐�
 */

int
getBlogIDs( const char *userName,       // (I) ���[�U��
            const char *password,       // (I) �p�X���[�h
            int        *numberOfBlogs,  // (I/O) blog ���
            BLOGINF    *blogInfo )      // (O) blog ���
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
 *  �ŐV�L��(1����)���擾
 *    ����:   blog ID, ���[�U��, �p�X���[�h
 *    �߂�l: ���s����
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
 * �t�@�C���̃A�b�v���[�h
 */

int
uploadFile( const char *blogID,
            const char *userName,
            const char *password,
            const char *dirname,    /* upload��f�B���N�g����(blog �̃g�b�v */
                                    /* �f�B���N�g������̑��΃p�X; ���݂��� */
                                    /* ���ꍇ�͍쐬�����)                  */
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
        strcpy( fInfo.type, "application/unknown" );    /* �b�� */
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
                        /* base64() ���Ŋm�ۂ����������� free ���� */
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

            // �R�R���O�� login
            memset( cookie, 0x00, MAX_COOKIE_LEN );
            r = loginCocologFiles( userName, password, cookie );
            if ( r ) {
                // �t�@�C�����A�b�v���[�h
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
                        /* base64() ���Ŋm�ۂ����������� free ���� */
    free( buf );

    return ( ret );
}


/* getRecentPostTitles() �� blogger API �� */
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
                      /* ����: blogger API �ł� title �͎擾�ł��Ȃ��̂ŁA */
                      /*       �L��ID�ƃ^�C���X�^���v�����ɉ��� title �� */
                      /*       �����邱�ƂőΉ�����                        */
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

/* getRecentPostTitles() �� metaWeblog API �� */
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
 *  RSS ���擾���APOSTINF�\���̂ɏ���ݒ肷��
 *      --- RSS 1.0 �� RSS 2.0 �ɑΉ�
 */

int
getRecentPostTitlesFromRSS(
        const char *rssURL,         // (I) RSS �� URL
        int        *numberOfPosts,  // (I) �擾����L�����̐�
                                    // (O) ���ۂɎ擾�����L�����
                                    //     �̐�
        POSTINF    *postinf         // (O) �擾�����L�����
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

    /* RSS �t�@�C�����擾 */
    sz = RCV_BUFFER_SIZE * 4;
    buffer = (char *)malloc( sz );
    if ( !buffer )
        return ( numOfPost );

    setUpReceiveBuffer( buffer, sz );   /* {@@} */
    ret = httpGetBuffer( rssURL, buffer, FALSE );

    /* RSS �t�@�C������� */
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
 *  �R�R���O�ɃA�b�v���[�h�����t�@�C���̍폜
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