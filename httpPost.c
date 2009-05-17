/*
 *  httpPost
 *      XML-RPC client (send request and receive result via http)
 *        Copyright (c) 2003, 2004 by Hiroshi Tsujimura (tsupo@na.rim.or.jp)
 *        All Right Reserved.
 *
 *      02 Nov 2003
 *
 * History:
 * $Log: /comm/xmlRPC/httpPost.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 27    08/01/23 16:40 Tsujimura543
 * http_postW, http_putW ��ǉ�
 * 
 * 26    05/10/18 18:44 Tsujimura543
 * _httpExecute() �̈����ǉ��ɔ����e��ύX�����{
 * 
 * 25    05/06/28 22:06 Tsujimura543
 * httpPutBASIC() �Ɉ��� mimeType ��ǉ�
 * 
 * 24    05/06/28 15:23 Tsujimura543
 * httpPostBASIC() �� httpPutBASIC() ��ǉ�
 * 
 * 23    05/05/31 22:51 Tsujimura543
 * httpPutEx() ��ǉ�
 * 
 * 22    04/11/24 15:46 Tsujimura543
 * _http_post() �� http.c �ֈړ�
 * 
 * 21    04/11/24 15:37 Tsujimura543
 * connectHTTP(), disconnectHTTP(), sendHTTP(), recvHTTP() �� http.c �ֈړ�
 * 
 * 20    04/11/19 22:11 Tsujimura543
 * _httpPost() �̖{�̂� _httpExecute() �ɓ���
 * 
 * 19    04/11/19 21:05 Tsujimura543
 * https �Ή� (�b��) -- �Ƃ肠�����A�]���� http ���f�O���[�h���Ă��Ȃ�
 * ���Ƃ��m�F
 * 
 * 18    04/11/17 13:24 Tsujimura543
 * Amazon Web Services �΍�Ƃ��āAconnectHTTP() �Őݒ肷�� flag �̒l��
 * �����𕪊򂷂闬��𕜊�������
 * 
 * 17    04/11/05 15:29 Tsujimura543
 * �����p�R�[�h�g���� (��M��)
 * 
 * 16    04/11/01 21:02 Tsujimura543
 * �x�����x�� 4 �ł� warning ���\�Ȍ��茸�炵�Ă݂�
 * 
 * 15    04/10/12 13:46 Tsujimura543
 * (1) �����p�R�[�h�g����
 * (2) HTTP���N�G�X�g�w�b�_�� Connection: close ��ǉ�
 * 
 * 14    04/10/08 12:20 Tsujimura543
 * 302 �� Location �ړ�����������ꍇ�AHTTP POST �ł͂Ȃ� HTTP GET ��
 * �ړ�����悤�ɏC�� (�����Ƀ��_�C���N�g���ꑱ����̂�����邽��)
 * 
 * 13    04/10/05 16:10 Tsujimura543
 * 302 Moved Temporarily ���o���̂� Location: �Ŏw�肳�ꂽ URL �Ɉړ�����
 * �͂����A����ȊO�̂Ƃ��� Location: �w�肳��Ă���ꍇ�Ɉړ����Ă��܂���
 * �����̂��C��
 * 
 * 12    04/10/05 13:40 Tsujimura543
 * �O�̂��߂� Cache-Control: no-cache ��t������悤�ɂ��Ă݂��B
 * 
 * 11    04/09/02 20:40 Tsujimura543
 * getCookie() �� cookie.c �Ɉړ�
 * 
 * 10    04/09/01 22:12 Tsujimura543
 * �}�C�v���t�B�[���Ή� (�b��)
 * 
 * 9     04/09/01 16:22 Tsujimura543
 * Location: �̐擪�� / �Ŏn�܂��Ă���ꍇ�̏�����ǉ�
 * 
 * 8     04/08/27 16:13 Tsujimura543
 * Loaction: �� URL �̌��ɃR�����g���t���Ă���ꍇ�ɑΏ�
 * 
 * 7     04/08/27 9:03 Tsujimura543
 * cookie �֌W�̏����𐮗�����
 * 
 * 6     04/08/26 22:20 Tsujimura543
 * excite�u���O�ɓ��e�ł��邱�Ƃ��m�F
 * 
 * 5     04/08/25 16:58 Tsujimura543
 * cookie �̑���M�𔺂� post ���\�b�h�ɑΉ�
 * 
 * 4     04/07/09 14:36 Tsujimura543
 * �R�����g���C��
 *
 * 1     04/07/07 11:24 Tsujimura543
 * RCS �ɂ��Ő��Ǘ����� VSS �ɂ��Ő��Ǘ��Ɉڍs
 *
 * Revision 1.1  2003/11/02 15:04:46  tsupo
 * Initial revision
 *
 */

#include "xmlRPC.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/httpPost.c 1     09/05/14 3:46 tsupo $";
#endif


/*
 *  HTTP���N�G�X�g��POST���\�b�h�֘A�����Q
 */

/*
 *  httpPost() --- post a XML-RPC request via httpd process
 *      arguments: 
 *          char *webServer;   web server which has target web page
 *          char *webPage;     target web page
 *      return: if get OK, returns 0; else returns non 0 value
 *              (if detected disconnection before receiving target web page,
 *               returns -2)
 */

int
httpPost( const char *webServer, const char *webPage,
          const char *mimeType,
          const char *request, char *response )
{
    return ( _httpPost( webServer, webPage,
                        NULL, NULL,
                        mimeType,
                        request, response, NULL, NULL,
                        NULL, NULL ) );
}


int
httpPostEx2( const char *webServer, const char *webPage,
             const char *request,   char *response,
             const char *wsse )
{
    return ( _httpPost( webServer, webPage,
                        NULL, NULL,
                        NULL,
                        request, response, wsse, NULL,
                        NULL, NULL ) );
}

int
httpPostWithSession( const char *webServer, const char *webPage,
                     const char *mimeType,
                     const char *sndBody, char *rcvBody, char *cookie,
                     char *webServerRedirected, char *cookieRedirected )
{
    return ( _httpPost( webServer, webPage,
                        NULL, NULL,
                        mimeType,
                        sndBody, rcvBody, NULL, cookie,
                        webServerRedirected, cookieRedirected ) );
}

/* for blogger.com Atom API -- http POST ���\�b�h���s(BASIC�F�ؑΉ��� -- */
int
httpPostBASIC( const char *webServer, const char *webPage,
               const char *userName,  const char *password,
               const char *mimeType,
               const char *request,   char *response )
{
    return ( _httpPost( webServer, webPage,
                        userName, password,
                        mimeType,
                        request, response, NULL, NULL,
                        NULL, NULL ) );
}


/*
 *  HTTP���N�G�X�g��PUT���\�b�h�֘A�����Q
 */

int
httpPutEx( const char *webServer, const char *webPage,
           const char *request,   char *response,
           const char *wsse )
{
    return ( httpPutBASIC( webServer, webPage,
                           NULL, NULL,
                           NULL,
                           request, response,
                           wsse ) );
}

/* for blogger.com Atom API -- http PUT ���\�b�h���s(BASIC�F�ؑΉ��� -- */
int
httpPutBASIC( const char *webServer, const char *webPage,
              const char *userName,  const char *password,
              const char *mimeType,
              const char *request,   char *response,
              const char *wsse )
{
    int stackCount = 0;
    int ret;

    ret = _httpExecute( "PUT",
                        webServer, webPage,
                        mimeType, request,
                        userName, password,
                        response, NULL, FALSE,
                        wsse, NULL, NULL,
                        NULL, NULL,
                        stackCount );

    return ( ret );
}



// for Atom PP

char    *
http_postW( const char *url, const char *wsse,
            const char *userName, const char *password,
            const char *request, char *response )
{
    setTargetURL( url );
    _httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
               userName, password,
               NULL,
               request, response, wsse, NULL,
               NULL, NULL );

    return ( response );
}

char    *
http_putW( const char *url, const char *wsse,
           const char *userName, const char *password,
           const char *request, char *response )
{
    setTargetURL( url );
    httpPutBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  userName, password,
                  NULL,
                  request, response,
                  wsse );

    return ( response );
}
