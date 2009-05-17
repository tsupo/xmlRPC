/*
 *  httpGet
 *      get a file via http
 *        Copyright (c) 2003 by Hiroshi Tsujimura (tsujimura543@oki.com)
 *        All Right Reserved.
 *
 *      28 July 2003
 *
 * History:
 * $Log: /comm/xmlRPC/httpGet.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 32    08/07/25 23:34 Tsujimura543
 * http_deleteBASIC() ��ǉ�
 * 
 * 31    08/01/23 16:41 Tsujimura543
 * http_getW, http_deleteW ��ǉ�
 * 
 * 30    07/05/22 0:24 Tsujimura543
 * BASIC�F�� + cookie �����g�p�Ή�����
 * 
 * 29    06/03/10 14:36 Tsujimura543
 * httpGetFileBASIC() ���Ŏg�� fopen() �̃��[�h�� w ���� wb �ɕύX
 * 
 * 28    06/03/03 16:21 Tsujimura543
 * httpGetFileBASIC() �̈����̏�����ύX
 * 
 * 27    05/10/18 18:44 Tsujimura543
 * _httpExecute() �̈����ǉ��ɔ����e��ύX�����{
 * 
 * 26    05/06/28 21:29 Tsujimura543
 * httpDeleteBASIC() ���C��
 * 
 * 25    05/06/28 15:27 Tsujimura543
 * httpDeleteBASIC() ��ǉ�
 * 
 * 24    05/05/24 14:44 Tsujimura543
 * BASIC�F�؂ɑΉ�
 * 
 * 23    04/11/24 15:44 Tsujimura543
 * _httpGet() �� _httpDelete() �� http.c �ֈړ�
 * 
 * 22    04/11/24 15:32 Tsujimura543
 * _httpExecute() �� http.c �ֈړ�
 * 
 * 21    04/11/24 15:14 Tsujimura543
 * https://www2.ggn.net/cgi-bin/ssl �� GET �ł��邱�Ƃ��m�F
 * 
 * 20    04/11/19 22:10 Tsujimura543
 * _httpExecute() �ɂ�� POST ���\�b�h�̓���̊m�F�I��
 * 
 * 19    04/11/19 21:44 Tsujimura543
 * _httpExecute() �� POST ���\�b�h�ɂ��Ή��ł���悤�ɏC��
 * 
 * 18    04/11/19 21:06 Tsujimura543
 * https �Ή� (�b��) -- �Ƃ肠�����A�]���� http ���f�O���[�h���Ă��Ȃ�
 * ���Ƃ��m�F
 * 
 * 17    04/11/19 20:45 Tsujimura543
 * https �Ή� (�b��)
 * 
 * 16    04/11/17 13:24 Tsujimura543
 * Amazon Web Services �΍�Ƃ��āAconnectHTTP() �Őݒ肷�� flag �̒l��
 * �����𕪊򂷂闬��𕜊�������
 * 
 * 15    04/11/16 15:20 Tsujimura543
 * ��� HTTP 1.1 �ɂ��Ă݂� (Amazon Web Services 3.x �΍�)
 * 
 * 14    04/11/05 15:29 Tsujimura543
 * �����p�R�[�h�g���� (��M��)
 * 
 * 13    04/10/12 13:46 Tsujimura543
 * (1) �����p�R�[�h�g����
 * (2) HTTP���N�G�X�g�w�b�_�� Connection: close ��ǉ�
 * 
 * 12    04/10/08 12:18 Tsujimura543
 * httpGetBufferWithSession() �̈����ǉ�
 * 
 * 11    04/10/05 16:12 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 10    04/10/05 16:09 Tsujimura543
 * 302 Moved Temporarily ���o���̂� Location: �Ŏw�肳�ꂽ URL �Ɉړ�����
 * �͂����A����ȊO�̂Ƃ��� Location: �w�肳��Ă���ꍇ�Ɉړ����Ă��܂���
 * �����̂��C��
 * 
 * 9     04/10/05 13:39 Tsujimura543
 * ����̏ꍇ���� Cache-Control: no-cache ��t���ĂȂ������̂��A
 * ��ɕt����悤�ɂ��� (��Ƃ��� livedoor Blog �΍�)
 * 
 * 8     04/09/01 16:22 Tsujimura543
 * Location: �̐擪�� / �Ŏn�܂��Ă���ꍇ�̏�����ǉ�
 * 
 * 7     04/08/27 16:13 Tsujimura543
 * Loaction: �� URL �̌��ɃR�����g���t���Ă���ꍇ�ɑΏ�
 * 
 * 6     04/08/27 9:03 Tsujimura543
 * cookie �֌W�̏����𐮗�����
 * 
 * 5     04/08/26 22:21 Tsujimura543
 * excite�u���O�ɓ��e�ł��邱�Ƃ��m�F
 * 
 * 4     04/07/14 9:15 Tsujimura543
 * X-WSSE: �t�����ȊO�� Host: ��t������悤�ɂ���
 * 
 * 3     04/07/09 14:37 Tsujimura543
 * �R�����g���C��
 *
 * 1     04/07/07 11:24 Tsujimura543
 * RCS �ɂ��Ő��Ǘ����� VSS �ɂ��Ő��Ǘ��Ɉڍs
 *
 * Revision 1.6  2003/12/25  03:22:36  tsujimura543
 * HTTP response�w�b�_ �\���@�\��t�� (-h�I�v�V����)
 *
 * Revision 1.5  2003/09/26  05:04:23  tsujimura543
 * �R�����g�̈ꕔ�̊����R�[�h�� ISO-2022-JP �ɂȂ��Ă����̂� Shift_JIS �ɕύX
 * (�R�����g�݂̂̕ύX)
 *
 * Revision 1.4  2003/09/26  00:21:33  tsujimura543
 * HTTP ���N�G�X�g�w�b�_�� User-Agent: ���܂߂�悤�ɂ����B
 *
 * Revision 1.3  2003/09/16  06:56:49  tsujimura543
 * Windows ���̏ꍇ�Aproxy.txt �����݂��Ȃ���΁A���W�X�g������proxy����
 * �擾����悤�ɂ����B
 *
 * Revision 1.2  2003/09/02  04:47:31  tsujimura543
 * When -p specified, if not found 'proxy.txt', then finish the process.
 *
 * Revision 1.1  2003/09/02  04:41:52  tsujimura543
 * Initial revision
 *
 */

#include "xmlRPC.h"
#include "http.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/httpGet.c 1     09/05/14 3:46 tsupo $";
#endif


/*
 *  HTTP���N�G�X�g��GET���\�b�h�֘A�����Q
 */


/*
 *  httpGet() --- get a web page
 *      arguments: 
 *          char *webServer;   web server which has target web page
 *          char *webPage;     target web page
 *          FILE *output;      stream for writing as target web page
 *      return: if get OK, returns TRUE; else returns FALSE
 */

int
httpGet( const char *webServer, const char *webPage,
         char *rcvBody, FILE *output, int printHead,
         const char *wsse,
         char *p3p, char *cookie,
         char *webServerRedirected, char *cookieRedirected )
{
    return ( _httpGet( webServer, webPage,
                       NULL, NULL,
                       rcvBody, output, printHead, wsse,
                       p3p, cookie,
                       webServerRedirected, cookieRedirected ) );
}

int
httpGetBASIC( const char *webServer, const char *webPage,
              const char *userName,  const char *password,
              char *rcvBody, FILE *output, int printHead,
              const char *wsse,
              char *p3p, char *cookie,
              char *webServerRedirected, char *cookieRedirected )
{
    return ( _httpGet( webServer, webPage,
                       userName, password,
                       rcvBody, output, printHead, wsse,
                       p3p, cookie,
                       webServerRedirected, cookieRedirected ) );
}


/* for Atom API */
int
httpGetEx( const char *webServer, const char *webPage,
           char *rcvBody, FILE *output, int printHead,
           const char *wsse )
{
    return ( _httpGet( webServer, webPage,
                       NULL, NULL,
                       rcvBody, output, printHead, wsse,
                       NULL, NULL,
                       NULL, NULL ) );
}

int
httpDeleteEx( const char *webServer, const char *webPage,
              char *rcvBody, FILE *output, int printHead,
              const char *wsse )
{
    return ( _httpDelete( webServer, webPage,
                          NULL, NULL,
                          rcvBody, output, printHead, wsse ) );
}


int
httpGetFile( const char *uri, const char *filename,
             int printHead )
{
    return ( httpGetFileBASIC( uri, filename, NULL, NULL, printHead ) );
}

int
httpGetFileBASIC( const char *uri, const char *filename,
                  const char *userName, const char *password,
                  int printHead )
{
    int     ret = 0;
    FILE    *fp;

    setTargetURL( uri );
    if ( ( fp = fopen( filename, "wb" ) ) != NULL ) {
        ret = httpGetBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                            userName, password,
                            NULL, fp, printHead, NULL, NULL, NULL,
                            NULL, NULL );
        fclose( fp );
    }

    return ( ret );
}


int
httpGetBuffer( const char *uri,
               char *rcvBuf, int printHead )
{
    return ( httpGetBufferBASIC( uri, NULL, NULL, rcvBuf, printHead ) );
}

int
httpGetBufferBASIC( const char *uri,
                    const char *userName, const char *password,
                    char *rcvBuf, int printHead )
{
    int     ret     = 0;
    char    *cookie = NULL;

#if 0
    if ( xmlrpc_p->proxyUserName[0] ) {
        cookie = (char *)malloc( MAX_COOKIE_LEN );
        if ( cookie )
            memset( cookie, 0x00, MAX_COOKIE_LEN );
    }
#endif

    setTargetURL( uri );
    ret = httpGetBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        userName, password,
                        rcvBuf, NULL, printHead, NULL, NULL,
                        cookie,
                        NULL, NULL );

#if 0
    if ( cookie )
        free( cookie );
#endif

    return ( ret );
}


int
httpGetBufferWithSession( const char *uri,
                          char       *rcvBuf,
                          int        printHead,
                          const char *wsse,
                          char       *p3p,
                          char       *cookie,
                          char       *webServerRedirected,
                          char       *cookieRedirected )
{
    int     ret = 0;

    setTargetURL( uri );
    ret = httpGet( xmlrpc_p->webServer, xmlrpc_p->webPage,
                   rcvBuf, NULL, printHead, wsse, p3p, cookie,
                   webServerRedirected, cookieRedirected );

    return ( ret );
}


/* for blogger.com Atom API -- http DELETE ���\�b�h���s(BASIC�F�ؑΉ��� -- */
int
httpDeleteBASIC( const char *webServer, const char *webPage,
                 const char *userName,  const char *password,
                 char *response, FILE *output, int printHead,
                 const char *wsse )
{
    return ( _httpDelete( webServer, webPage,
                          userName, password,
                          response, output, printHead, wsse ) );
}


// for Atom PP
char    *
http_getW( const char *url, const char *wsse,
           const char *userName, const char *password,
           char *response )
{
    setTargetURL( url );
    httpGetBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                  userName, password,
                  response, NULL, FALSE,
                  wsse,
                  NULL, NULL,
                  NULL, NULL );

    return ( response );
}

char    *
http_deleteW( const char *url, const char *wsse,
              const char *userName, const char *password,
              char *response )
{
    setTargetURL( url );
    httpDeleteBASIC( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     userName, password,
                     response, NULL, FALSE,
                     wsse );

    return ( response );
}


// for RESTful API (cf. Diigo)
char    *
http_deleteBASIC( const char *url,
                  const char *userName, const char *password,
                  const char *mimeType, const char *request,
                  char *response )
{
    int stackCount = 0;

    setTargetURL( url );

    _httpExecute( "DELETE",
                  xmlrpc_p->webServer, xmlrpc_p->webPage,
                  mimeType, request,
                  userName, password,
                  response, NULL, FALSE,
                  NULL, NULL, NULL,
                  NULL, NULL, stackCount );

    return ( response );
}
