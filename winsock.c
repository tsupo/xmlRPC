/*
 *  winsock.c
 *      socket() �֘A����̂����AWin32 �Ǝ��̑�����L�q����
 *
 * History:
 * $Log: /comm/xmlRPC/winsock.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     04/07/07 11:53 Tsujimura543
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/winsock.c 1     09/05/14 3:46 tsupo $";
#endif

int
initializeSocket()
{
    int         ret = TRUE;
#ifdef  WIN32
    WORD        wVersionRequested;      /* Winsock version */
    WSADATA     sockInfo;               /* Winsock information structure */

    /* initialize for Winsock (requested Version 2.0) */
    wVersionRequested = MAKEWORD( 2, 0 );
    ret = WSAStartup( wVersionRequested, &sockInfo );
    if ( ret == SOCKET_ERROR ) {
        /* if not found dll as Winsock 2.0, request Winsock 1.1 */
        /* initialize for Winsock (requested Version 1.1) */
        wVersionRequested = MAKEWORD( 1, 1 );
        ret = WSAStartup( wVersionRequested, &sockInfo );
    }

#ifdef  __DEBUG
    if ( ret != SOCKET_ERROR ) {
        fprintf( stderr, "\n\tWinsock Version %d.%d\n",
                 LOBYTE( sockInfo.wVersion ),
                 HIBYTE( sockInfo.wVersion ) );
    }
#endif  /* _DEBUG */
#endif  /* WIN32  */

    return ( ret );
}


int
finalizeSocket()
{
#ifdef  WIN32
    WSACleanup();
#endif

    return ( TRUE );
}
