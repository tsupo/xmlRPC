/*
 *  misc.c
 *      ���[�e�B���e�B�֐��Q
 *
 * History:
 * $Log: /comm/xmlRPC/misc.c $
 * 
 * 2     09/05/27 2:56 tsupo
 * ./noproxy.txt �t�@�C��������΁A�uproxy���g��Ȃ��v�Ɣ��f����悤�ɂ���
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 92    09/03/30 19:48 Tsujimura543
 * OAuth �Ή�
 * 
 * 91    09/03/20 22:25 Tsujimura543
 * �u�͂Ăȃ_�C�A���[�v�� Atom API �ɑΉ�
 * 
 * 90    08/11/17 22:10 Tsujimura543
 * static char �� Thread static char �ɕύX
 * 
 * 89    08/02/07 19:03 Tsujimura543
 * isUsedProxy() / getProxyInfo() ��������J��Ԃ��Ăяo����Ă��܂�
 * ���Ƃ����錻�ۂɑΏ�
 * 
 * 88    07/12/06 1:15 Tsujimura543
 * unbase64() �̈�����ǉ�
 * 
 * 87    07/10/16 22:50 Tsujimura543
 * __argv[0] �Ƀf�B���N�g�������܂܂�Ȃ��ꍇ�ɂ��Ή�
 * 
 * 86    07/10/10 2:03 Tsujimura543
 * dprintf() ���̍�Ɨp�o�b�t�@�T�C�Y���Œ�ɖ߂�
 * 
 * 85    07/10/09 21:26 Tsujimura543
 * dprintf() ���Ŏg�p����o�b�t�@�̃T�C�Y�v�Z�����C��
 * 
 * 84    07/10/09 20:08 Tsujimura543
 * dputc() ��ǉ�
 * 
 * 83    07/10/09 19:36 Tsujimura543
 * dprintf() ���̍�Ɨp�o�b�t�@�T�C�Y���ςɂ���
 * 
 * 82    07/10/09 19:32 Tsujimura543
 * dputs() �� dprintf() ��ǉ�
 * 
 * 81    07/09/28 19:18 Tsujimura543
 * XMLRPC_ERROR_CHANGED_PROXYINFO �𓱓�
 * 
 * 80    07/09/28 18:42 Tsujimura543
 * confirmProxyInfo() �ŕ\������_�C�A���O(MessageBox)�̕������C��
 * 
 * 79    07/09/14 22:41 Tsujimura543
 * setReferer() ���C�� (referer �̍ő咷��ύX)
 * 
 * 78    07/09/10 19:04 Tsujimura543
 * makeRurl() ��p�~
 * 
 * 77    07/09/04 20:21 Tsujimura543
 * verboseFp ��ǉ����AsetVerbos() �̑�2�����Œl��ύX�ł���悤�ɂ���
 * 
 * 76    07/09/04 20:10 Tsujimura543
 * dumpFp ��ǉ����AsetDump() �̑�2�����Œl��ύX�ł���悤�ɂ���
 * 
 * 75    07/08/24 18:38 Tsujimura543
 * setReferer() ��ǉ�
 * 
 * 74    07/07/03 14:39 Tsujimura543
 * decodeString() �� &dquot; �Ɋւ��鏈����ǉ�
 * 
 * 73    07/06/04 14:33 Tsujimura543
 * getProxyInfo() ���C�� (__argv �����Ȃ��Ƃ��ɗ�����s��ɑΏ�)
 * 
 * 72    07/05/21 19:53 Tsujimura543
 * getProxyInfo() �� proxy.txt ��ǂޕ������C��
 * 
 * 71    07/04/10 23:12 Tsujimura543
 * ���t�@�N�^�����O
 * 
 * 70    07/04/09 19:10 Tsujimura543
 * makeRurl() ���C��
 * 
 * 69    07/04/09 17:36 Tsujimura543
 * rurl.org API �֘A������ǉ�
 * 
 * 68    07/04/09 16:34 Tsujimura543
 * setProxyInfo() ��ύX�A�������񏉊������Ă���ݒ肪�K�v�ȃ����o�̂�
 * ������悤�ɂ���
 * 
 * 67    07/04/09 16:26 Tsujimura543
 * getProxyInfo() ���C���A�����Ɂuproxy���₢���킹�v���b�Z�[�W�{�b�N�X
 * ���o�����錻�ۂɑΏ� [�ΏǗÖ@] (�z�肵�Ă��郌�W�X�g���\���ł͂Ȃ���
 * ���ɔ���?)
 * 
 * 66    07/03/13 19:54 Tsujimura543
 * useProxy �� TRUE �̂Ƃ��AsetTargetURL() ���Ŗ��� getproxyInfo() ����
 * �悤�ɂȂ��Ă����̂���߂�
 * 
 * 65    07/03/13 19:18 Tsujimura543
 * setProxy() �� setProxyInfo() �ɖ��̕ύX
 * 
 * 64    07/03/13 19:16 Tsujimura543
 * setProxy() ��ǉ�
 * 
 * 63    07/03/10 6:15 Tsujimura543
 * proxy�֘A�̏������C��
 * 
 * 62    07/03/10 5:05 Tsujimura543
 * confirmProxyInfo() �̈�����2�ǉ�
 * 
 * 61    07/03/10 4:58 Tsujimura543
 * ���[�U���ƃp�X���[�h�̎w�肪�K�v��proxy�T�[�o�ɂ��b��I�ɑΉ�
 * 
 * 60    07/03/09 21:13 Tsujimura543
 * isNecessaryToCheckProxyInfo() ��ǉ��A����т���ɔ����C�������{
 * 
 * 59    07/03/09 17:26 Tsujimura543
 * (1) getProxyInfo() ���C�� (proxy���̎����擾�Ɏ��s�����ꍇ�̏���
 *     ��ǉ�)
 * (2) setConfirmProxyInfoFunc() ��ǉ�
 * 
 * 58    07/03/03 15:21 Tsujimura543
 * sjis2utf() �� NULL ��Ԃ��ꍇ�̑΍�����{
 * 
 * 57    07/02/14 22:10 Tsujimura543
 * getProxyInfoViaOpera() �͌��݂̃R�[�h�̂܂܂�����Ȃ��Ă��������Ƃ��m�F
 * 
 * 56    07/02/13 12:04 Tsujimura543
 * getProxyInfoViaInternetExplorer() �� getProxyInfoViaFirefox() ��
 * �C���Bproxy�T�[�o�̐ݒ�͎c�����܂܂ł��邪�Aproxy�T�[�o�͎g���
 * ���ݒ�ɕύX���Ă���Ƃ������󋵂ɂ��Ή�
 * 
 * 55    07/01/17 16:54 Tsujimura543
 * Windows �́u����v�̎擾�A�ݒ�p�̊֐���ǉ�
 * 
 * 54    06/10/27 1:54 Tsujimura543
 * getProxyInfo() �֘A�̉��C�����{���AFirefox 2 �ɑΉ�����
 * 
 * 53    06/10/19 22:58 Tsujimura543
 * ���܂Ń��C�u�����O�ɂ� ����J������ getProxyInfo() �����J���邱�Ƃɂ���
 * 
 * 52    06/09/19 17:01 Tsujimura543
 * (1) �s�v�ɂȂ����R�[�h�̍폜
 * (2) Opera 9 �Ɋւ��鏈���̐���(�R�����g)��ǉ�
 * 
 * 51    06/09/19 16:17 Tsujimura543
 * getProxyInfo() �֘A�̉��C�����{
 *   (1) �u�ʏ�g�p����u���E�U�v�̐ݒ��D��I�Ɏ擾����悤�ɂ���
 *   (2) Opera 9 �ɑΉ����� (�]���� Opera �Ή������� Opera 8 �܂łɂ���
 *       �Ή�������Ă��Ȃ�����)
 * 
 * 50    06/09/11 12:05 Tsujimura543
 * �R�����g��ǉ�
 * 
 * 49a   06/09/10 5:48 tsupo
 * resetDaylightSaving() �𓱓�����
 * (Visual Studio 2005 �� C++ �����^�C���g�p���ɁA���{���ԂȂ̂ɉĎ��Ԃ�
 * ���肳��Ă��܂����̑΍�)
 * 
 * 49    06/07/24 20:10 Tsujimura543
 * _httpExecute() �̃o�b�t�@�I�[�o�[�����h�~�@�\�𗘗p����悤�ɂ���
 * 
 * 48    06/06/01 14:33 Tsujimura543
 * getTrackbackURL() ���y�V�L��́u�Í������ꂽ�g���b�N�o�b�NURL�v�ɑΉ�
 * 
 * 47    06/03/13 16:49 Tsujimura543
 * getCurrentLocation() ��ǉ�
 * 
 * 46    06/03/09 14:37 Tsujimura543
 * unbase64() ����茵���ȏ������s�Ȃ��悤�ɏ���������
 *  (�������ʎ��͍̂��܂łƓ���)
 * 
 * 45    06/01/26 18:09 Tsujimura543
 * �o�b�t�@�I�[�o�[�����΍�����{
 * 
 * 44    06/01/25 19:18 Tsujimura543
 * �C����� setTargetURL() �̓�����m�F�B���Ȃ�
 * 
 * 43    06/01/25 19:14 Tsujimura543
 * setTargetURL() ���C�� (���[�g�f�B���N�g�������� URL �̏ꍇ�A������ / ������
 * �Ă�����⊮����悤�ɂ���  [�Ⴆ�΁Ahttp://aaa.bbb �� http://aaa.bbb/ �̂�
 * ���� / ��t�����Ă���A�������s�Ȃ��悤�ɂ���])
 * 
 * 42    06/01/10 15:26 Tsujimura543
 * setUserAgent() ���C�����A��x�ݒ肵�� User-Agent ���f�t�H���g�l�ɖ߂���
 * �悤�ɂ���
 * 
 * 41    06/01/10 15:12 Tsujimura543
 * userAgent / setUserAgent() ��ǉ�
 * 
 * 40    05/10/31 13:49 Tsujimura543
 * getProxyInfoViaFirefox() ���C�����A�ݒ�t�@�C�����f�t�H���g�̏ꏊ�ȊO��
 * �ύX���Ă���ꍇ�ɂ��Ή��ł���悤�ɂ���
 * 
 * 39    05/10/18 18:08 Tsujimura543
 * httpGet() �̈����ǉ��ɔ����C�������{
 * 
 * 38    05/10/04 15:07 Tsujimura543
 * Opera �̐ݒ��񂩂� proxy �֘A����ǂݎ�鏈����ǉ�
 * 
 * 37    05/10/04 14:01 Tsujimura543
 * Firefox �̐ݒ��񂩂� proxy �֘A����ǂݎ�鏈����ǉ�
 * 
 * 36    05/03/25 17:03 Tsujimura543
 * isDecString() ��ǉ�
 * 
 * 35    05/03/25 16:49 Tsujimura543
 * isHexString() �� webry.c ����ړ�
 * 
 * 34    05/03/22 15:00 Tsujimura543
 * isUsedProxy() ��ǉ�
 * 
 * 33    05/02/23 10:59 Tsujimura543
 * getTrackbackURL() ���Ɂu�S�~�|���v������ǉ�
 * 
 * 32    05/02/21 10:27 Tsujimura543
 * getTrackbackURL() ���C�� (����Web�y�[�W���Ƀ����g���𕡐��ݒu���Ă���
 * �ꍇ�̑΍�)
 * 
 * 31    05/02/17 12:06 Tsujimura543
 * �����g���֘A�������C��
 * 
 * 30    05/02/15 19:53 Tsujimura543
 * sendTrackbackPing() ���� str[3] �̃o�b�t�@�T�C�Y���s�����ė̈�j��
 * �������Ă����̂��C��
 * 
 * 29    05/02/14 19:16 Tsujimura543
 * �g���b�N�o�b�N�֘A�������������� Fix
 * 
 * 28    05/02/14 19:13 Tsujimura543
 * normalizeString() ��ǉ��A�g���b�N�o�b�N���M������ normalizeString()
 * ���g���ď�������
 * 
 * 27    05/02/14 18:37 Tsujimura543
 * getTrackbackURL() �Ŏ擾���� URL �̖����ɃS�~�������Ƃ�����s�
 * �ɑΏ�
 * 
 * 26    05/02/09 18:12 Tsujimura543
 * getTrackbackURL() �� XOOPS �ɑΉ�
 * 
 * 25    05/02/09 18:03 Tsujimura543
 * getTrackbackURL() �� teeter totter �ɑΉ�
 * 
 * 24    05/02/09 13:43 Tsujimura543
 * �u�擾����URL�����΃p�X�\�L�ł���ΐ�΃p�X�\�L�ɕϊ����鏈���v��ǉ�
 * 
 * 23    05/02/08 19:05 Tsujimura543
 * getTrackbackURL() �� HaloScan ���g���Ă��� Web �y�[�W�ɂ��Ή�������
 * 
 * 22    05/02/08 15:38 Tsujimura543
 * getTrackbackURL() �� MSN Spaces �ɑΉ�
 * 
 * 21    05/02/07 13:59 Tsujimura543
 * getTrackbackURL() �� NAVER�u���O �� BLOGari �ɂ��Ή�
 * 
 * 20    05/02/07 11:24 Tsujimura543
 * getTrackbackURL() ���u�֐��ǂ��ƃR���v�ɂ��Ή�
 * 
 * 19    05/02/05 19:38 Tsujimura543
 * getTrackbackURL() ���X�ɏC�� (�y�V�L��֘A����) �� ����m�F����
 * 
 * 18    05/02/05 19:09 Tsujimura543
 * getTrackbackURL() ���X�ɏC�� (�y�V�L��֘A����)
 * 
 * 17    05/02/05 18:24 Tsujimura543
 * getTrackbackURL() ���C�� (�����g��, �y�V�L�� �֘A�����̊e�o�OFix)
 * 
 * 16    05/02/03 14:06 Tsujimura543
 * getTrackbackURL() ���u�}�C�Ղꂷ�v�ɂ��Ή�������
 * 
 * 15    05/02/02 20:45 Tsujimura543
 * �g���b�N�o�b�N���M���� error �������Ԃ��Ă������ǂ����`�F�b�N����悤
 * �ɂ���
 * 
 * 14    05/02/02 13:13 Tsujimura543
 * memla! blog �΍� (�g���b�N�o�b�N���M�ɑ΂��鉞����M�p�o�b�t�@�T�C�Y��
 * ���₷)
 * 
 * 13    05/01/28 14:56 Tsujimura543
 * FC2BLOG ��3�̃T�[�o�̂��� blog2.fc2.com �ɂ��� blog �̂݁Atrackback
 * auto-discovery �����܂������Ȃ�(�e���v���[�g�̃o�O�������ł�)���ۂɁA�{
 * ���C�u�������Ŏb��I�ɑΏ�
 * 
 * 12    05/01/26 22:01 Tsujimura543
 * �����g�����g���Ă���Web�y�[�W�̃g���b�N�o�b�N���M�pURL���擾�ł���悤
 * �ɂ���
 * 
 * 11    05/01/26 20:21 Tsujimura543
 * getTrackbackURL() ��ǉ�
 * 
 * 10    04/11/25 10:06 Tsujimura543
 * setTargetURL() ���C���B�`���ŕK�� useSSL ���N���A����(FALSE�ɂ���)
 * �悤�ɂ����B
 * 
 * 9     04/11/19 14:55 Tsujimura543
 * https �Ή�
 * 
 * 8     04/11/15 17:06 Tsujimura543
 * encodeURL() ���Ŋm�ۂ����̈�̉��������ǉ�
 * 
 * 7     04/11/12 15:45 Tsujimura543
 * unbase64() ��ǉ� (����m�F�ς�)
 * 
 * 6     04/11/01 21:02 Tsujimura543
 * �x�����x�� 4 �ł� warning ���\�Ȍ��茸�炵�Ă݂�
 * 
 * 5     04/09/03 15:25 Tsujimura543
 * �}�C�v���t�B�[���Ή� [�b��]
 * 
 * 4     04/08/31 15:57 Tsujimura543
 * decodeString() �ł� &amp; ���݂̏������C��
 * 
 * 3     04/07/08 16:33 Tsujimura543
 * �֐� setTargetURL() �� blog ��ʐݒ�@�\��t���B
 * 
 * 2     04/07/07 11:55 Tsujimura543
 */

#include "xmlRPC.h"
#include <sys/stat.h>

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/misc.c 2     09/05/27 2:56 tsupo $";
#endif

#ifdef  _MSC_VER
#define Thread  __declspec( thread )
#else
#define Thread
#endif

/*
 *  �O������J ���[�e�B���e�B�֐�
 */

/*
 *  �������܂ޕ�����(Shift_JIS)���w�肵�������ɐ؂�l�߂�
 */

#ifndef	iskanji1
#define	iskanji1(s) \
    (((((short)s & 0xFF)>=0x81) && (((short)s & 0xFF)<=0x9f)) || \
     ((((short)s & 0xFF)>=0xe0) && (((short)s & 0xFF)<=0xfc)))
#endif
#ifndef	iskanji2
#define	iskanji2(s) \
    (((((short)s & 0xFF)>=0x40) && (((short)s & 0xFF)<=0x7e)) || \
     ((((short)s & 0xFF)>=0x80) && (((short)s & 0xFF)<=0xfc)))
#endif

char    *
normalizeString( char *dst, const char *src, size_t len )
{
    /* ������1�o�C�g�ڂŏI������̂������ */
    char        *p = dst;
    const char  *q = src;
    int         flag = 0;

    if ( !p || !q )
        return ( p );

    if ( *q && (strlen( q ) > len) ) {
        strncpy( p, q, len );
        p[len] = NUL;
    }
    else
        strcpy( p, q );

    while ( *q ) {
        if ( (flag == 0) && iskanji1( *q ) ) {
            flag = 1;
        }
        else if ( (flag == 1) && iskanji2( *q ) ) {
            flag = 0;
        }
        q++;
    }

    if ( flag )
        p[len - 1] = NUL;

    return ( p );
}


/*
 *  proxy �T�[�o�� �� proxy �|�[�g�ԍ��̎擾
 *    �Eproxy.txt �Ƃ����t�@�C�������݂���ꍇ�A���Y�t�@�C���������ǂݎ��
 *    �Eproxy.txt �Ƃ����t�@�C�������݂��Ȃ��ꍇ�AWin32 ���ł���΁AInternet
 *      Explorer �� proxy �֘A����ǂݎ��(Internet Explorer �� proxy �֘A��
 *      �񂪓ǂݎ��Ȃ������ꍇ�́AFirefox �� proxy �֘A����ǂݎ��B ����
 *      �� Firefox �̏������Ȃ������ꍇ�́AOpera �̏������)
 *   �Ȃ��Aproxy �Ɋւ���u���v�̃t�H�[�}�b�g��  �T�[�o��:�|�[�g�ԍ� �Ƃ���
 *   �`���Ƃ���
 */

#define BR_UNKNOWN      0   /* �s��    */
#define BR_IEXPLORER    1   /* IE      */
#define BR_FIREFOX      2   /* Firefox */
#define BR_OPERA        3   /* Opera   */
#define BR_EXTRA        4   /* ���̑�  */

static int
getDefaultBrowser( void )
{
    int     ret = BR_UNKNOWN;
    long    r;
    HKEY    hk;
    long    type;
    char    buf[BUFSIZ];
    long    sz = BUFSIZ - 1;

#if 0
    r = RegOpenKeyEx( HKEY_CLASSES_ROOT,
                      "htmlfile\\shell\\open\\command",
                      0,
                      KEY_READ,
                      &hk );
#else
    r = RegOpenKeyEx( HKEY_CLASSES_ROOT,
                      "http\\shell\\open\\ddeexec\\Application",
                      0,
                      KEY_READ,
                      &hk );
#endif
    if ( r == ERROR_SUCCESS ) {
        r = RegQueryValueEx( hk,
                             "",
                             NULL,
                             (unsigned long *)&type,
                             (unsigned char *)buf,
                             (unsigned long *)&sz );
        if ( r == ERROR_SUCCESS ) {
            if ( type == REG_SZ ) {
                if ( strstr( buf, "iexplore" ) ||
                     strstr( buf, "IExplore" )    )
                    ret = BR_IEXPLORER;
                else if ( strstr( buf, "firefox" ) ||
                          strstr( buf, "Firefox" )    )
                    ret = BR_FIREFOX;
                else if ( strstr( buf, "opera" ) ||
                          strstr( buf, "Opera" )    )
                    ret = BR_OPERA;
                else
                    ret = BR_EXTRA;
            }
        }
        RegCloseKey( hk );
    }

    return ( ret );
}

static BOOL
getProxyInfoViaInternetExplorer(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword
    )
{
    /*
     *  Internet Explorer �̐ݒ�𒲂ׂ�
     */

    /* �ȉ��̃��W�X�g������ proxy �֘A�����擾����                   */
    /*   HKEY_CURRENT_USER                                             */
    /*     Software\Microsoft\Windows\CurrentVersion\Internet Settings */
    /*       ProxyServer                                               */

    long    ret;
    HKEY    hk;
    long    type;
    char    buf[BUFSIZ], *p;
    long    sz = BUFSIZ - 1;
    BOOL    isInternetExplorerActive = FALSE;

    ret = RegOpenKeyEx( HKEY_CURRENT_USER,
            "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
                        0,
                        KEY_READ,
                        &hk );
    if ( ret == ERROR_SUCCESS ) {
        isInternetExplorerActive = TRUE;
                            /* Internet Explorer �C���X�g�[���ς� */
        ret = RegQueryValueEx( hk,
                               "ProxyEnable",
                               NULL,
                               (unsigned long *)&type,
                               (unsigned char *)buf,
                               (unsigned long *)&sz );
        if ( ret == ERROR_SUCCESS ) {
            BOOL    proxyEnable = FALSE;
            if ( type == REG_DWORD )
                proxyEnable = ((unsigned long *)buf) ? TRUE : FALSE;
            else if ( type == REG_BINARY )
                proxyEnable = buf[0] ? TRUE : FALSE;

            if ( proxyEnable ) {
                sz = BUFSIZ - 1;
                ret = RegQueryValueEx( hk,
                                       "ProxyServer",
                                       NULL,
                                       (unsigned long *)&type,
                                       (unsigned char *)buf,
                                       (unsigned long *)&sz );
                if ( ret == ERROR_SUCCESS ) {
                    if ( type == REG_SZ ) {
                        char    *q;

                        p = buf;
                        q = strchr( buf, ':' );
                        if ( q ) {
                            char    *r;
                            r = strchr( buf, '@' );
                            if ( r ) {
                                *r++ = NUL;
                                if ( r > q ) {
                                    *q++ = NUL;
                                    if ( proxyUserName )
                                        strcpy( proxyUserName, p );
                                    if ( proxyPassword )
                                        strcpy( proxyPassword, q );

                                    q = strchr( r, ':' );
                                }
                                else {
                                    if ( proxyUserName )
                                        strcpy( proxyUserName, p );
                                }

                                p = r;
                            }

                            if ( q )
                                *q = NUL;
                            strcpy( proxyServer, p );
                            if ( q )
                                *proxyPort =
                                    (unsigned short)(atol( q + 1 ) & 0xFFFF);
                            if ( (*proxyPort > 0)        &&
                                 (proxyServer[0] != NUL)    ) {
                                if ( xmlrpc_p->verbose )
                                    if ( isatty( fileno( stderr ) ) )
                                        fprintf( stderr, "\tproxy = %s:%d\n",
                                                 proxyServer, *proxyPort );
                                *useProxy = TRUE;
                            }
                        }
                    }
                }
            }
        }
        RegCloseKey( hk );
    }

    return ( isInternetExplorerActive );
}

static BOOL
getProxyInfoViaFirefox(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword
    )
{
    /*
     *  Firefox �̐ݒ�𒲂ׂ�
     */

    /* �菇                                                              */
    /*  (1) ���W�X�g��                                                   */
    /*        HKEY_CURRENT_USER\Software\Mozilla\Mozilla Firefox         */
    /*      �����݂���΁AFirefox �C���X�g�[���ς�                       */
    /*  (2) ���ϐ� USERPROFILE �̎w���f�B���N�g���ȉ��̃t�@�C����T��  */
    /*  (3) Application Data/Mozilla/Firefox/profiles.ini �Ƃ����t�@�C�� */
    /*      ����                                                         */
    /*        Path=Profiles/*.default                                    */
    /*      �Ƃ����s���擾���� (* �����͊��ɂ���ĕς��)              */
    /*  (4) Application Data/Mozilla/Firefox/Profiles/*.default/prefs.js */
    /*      (�������A�ݒ�t�@�C����u���ꏊ��(Profiles/*.default�ȊO��)  */
    /*       �ʂ̂Ƃ���ɕύX���Ă���ꍇ���l������ Path  �̎����f�B���N */
    /*      �g���������� prefs.js ��T������������)                      */
    /*      �Ƃ����t�@�C���̒���                                         */
    /*        user_pref("network.proxy.http", "proxy�T�[�o��");          */
    /*        user_pref("network.proxy.http_port", �|�[�g�ԍ�);          */
    /*      �Ƃ����L�q������΁Aproxy ���g�p����                         */
    /* ����: �p�r�ɍ��킹�� profile �𕡐��p�ӂ��g�������Ă���悤�ȏꍇ */
    /*       �́A���̎菇�� proxy �̐ݒ���擾�ł���Ƃ͌���Ȃ�         */

#if 0
    long    ret;
    HKEY    hk;
    long    type;
    long    sz = BUFSIZ - 1;
#endif
    char    buf[BUFSIZ];
    BOOL    isFirefoxActive = FALSE;

#if 0
    ret = RegOpenKeyEx( HKEY_CURRENT_USER,
                        "Software\\Mozilla\\Mozilla Firefox",
                        0,
                        KEY_READ,
                        &hk );
    if ( ret == ERROR_SUCCESS ) {
        // Firefox 2.x �ł́A���̃��W�X�g�����g�p���Ȃ��Ȃ���
        // (Firefox 1.x �̂Ƃ��̂ݗL��)
        ret = RegQueryValueEx( hk,
                               "CurrentVersion",
                               NULL,
                               (unsigned long *)&type,
                               (unsigned char *)buf,
                               (unsigned long *)&sz );
        if ( ret == ERROR_SUCCESS ) {
            /* Firefox �C���X�g�[���ς݂ł���Ɣ��f */
            isFirefoxActive = TRUE;
        }
        RegCloseKey( hk );
    }

    if ( isFirefoxActive == TRUE ) {
#endif
        char    *p = getenv("USERPROFILE");

        if ( p && *p ) {
            char    targetDir[MAX_PATH];
            char    filename[MAX_PATH];
            char    path[MAX_PATH];
            FILE    *fp;
            BOOL    isRelative = TRUE;

            sprintf( targetDir,
                     "%s\\Application Data\\Mozilla\\Firefox\\", p );
            sprintf( filename, "%sprofiles.ini", targetDir );
            path[0] = NUL;

            if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
                char    *p;

                isFirefoxActive = TRUE;
                while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
                    if ( !strncmp( p, "IsRelative=", 11 ) ) {
                        p += 11;
                        isRelative = (atol( p ) == 0) ? FALSE : TRUE;
                        continue;
                    }
                    if ( !strncmp( p, "Path=", 5 ) ) {
                        p += 5;
                        strcpy( path, p );
                        while ( (path[strlen(p) - 1] == '\n') ||
                                (path[strlen(p) - 1] == '\r') ||
                                (path[strlen(p) - 1] == ' ' ) ||
                                (path[strlen(p) - 1] == '/' ) ||
                                (path[strlen(p) - 1] == '\\')    )
                            path[strlen(p) - 1] = NUL;
                        break;
                    }
                }
                fclose( fp );

                if ( path[0] ) {
                    if ( isRelative )
                        sprintf( filename, "%s%s\\prefs.js",
                                 targetDir, path );
                    else
                        sprintf( filename, "%s\\prefs.js", path );

                    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
                        BOOL    enableProxy = FALSE;

                        while ( (p = fgets( buf, BUFSIZ - 1, fp )) != NULL ) {
                            if ( !strncmp( p,
                                           "user_pref(\"network.proxy.http\"",
                                           30 ) ) {
                                char    *q;

                                p += 30;
                                q = strchr( p, '"' );
                                if ( q ) {
                                    q++;
                                    p = strchr( q, '"' );
                                    if ( p ) {
                                        char    *r;

                                        *p = NUL;

                                        r = strchr( q, '@' );
                                        if ( r ) {
                                            char    *s;

                                            *r++ = NUL;
                                            s = strchr( q, ':' );
                                            if ( s ) {
                                                *s++ = NUL;
                                                if ( proxyUserName )
                                                    strcpy(proxyUserName, q);
                                                if ( proxyPassword )
                                                    strcpy(proxyPassword, s);
                                            }
                                            else {
                                                if ( proxyUserName )
                                                    strcpy(proxyUserName, q);
                                            }

                                            q = r;
                                        }

                                        strcpy( proxyServer, q );
                                        enableProxy = TRUE;
                                        *proxyPort  = DEFAULT_HTTP_PORT;
                                            /* �Ƃ肠�����A�f�t�H���g�l�� */
                                            /* ����Ă���                 */
                                    }
                                }
                            }
                            else if ( !strncmp( p,
                                      "user_pref(\"network.proxy.http_port\"",
                                                35 ) ) {
                                p += 35;
                                while ( *p && ((*p < '0') || (*p > '9')) )
                                    p++;
                                if ( *p ) {
                                    *proxyPort =
                                        (unsigned short)(atol( p ) & 0xFFFF);
                                    enableProxy = TRUE;
                                }
                            }
                            else if ( !strncmp( p,
                                      "user_pref(\"network.proxy.type\"",
                                                30 ) ) {
                                int type = 0;
                                p += 30;
                                while ( *p && ((*p < '0') || (*p > '9')) )
                                    p++;
                                if ( *p ) {
                                    type = atol( p );
                                            /* 1: �蓮�Ńv���L�V��ݒ肷�� */
                                            /* 2: �����v���L�V�ݒ�X�N���v */
                                            /*    �gURL                    */
                                            /* 4: ���̃l�b�g���[�N�̃v���L */
                                            /*    �V�ݒ���������o����     */
                                }
                                if ( enableProxy || (type >= 1) ) {
                                    *useProxy = TRUE;
                                    if ( type != 1 )                /* @@ */
                                        isFirefoxActive = FALSE;    /* @@ */
                                    break;
                                }
                            }
                        }
                        fclose( fp );
                    }
                }
            }
        }
#if 0
    }
#endif

    return ( isFirefoxActive );
}


static BOOL
readProxySettingFromOperaIni(
        const char     *filename,
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword 
    )
{
    BOOL    found = FALSE;
    char    buf[BUFSIZ];
    char    *p;
    FILE    *fp;

    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            if ( !strncmpi( p, "HTTP Server=",  12 ) ||
                 !strncmpi( p, "HTTPS Server=", 13 )    ) {
                    /* Opera 8 �܂ł� Server,                     */
                    /* Opera 9 ��     server [s ���������ɂȂ���] */
                char    *q;
                char    *r;

                found = TRUE;
                p = strchr( p + 11, '=' ) + 1;
                q = strchr( p, ':' );
                r = strchr( p, '@' );
                if ( r ) {
                    if ( q && (q < r) ) {
                        *q++ = NUL;
                        if ( proxyUserName )
                            strcpy( proxyUserName, p );
                        *r = NUL;
                        if ( proxyPassword )
                            strcpy( proxyPassword, q );
                    }
                    else {
                        *r = NUL;
                        if ( proxyUserName )
                            strcpy( proxyUserName, p );
                    }

                    p = r + 1;
                    q = strchr( p, ':' );
                }

                if ( !q ) {
                    q = p + (strlen(p) - 1);
                    while ( (q > p) && (*q == '\n') || (*q == '\r') )
                        *q-- = NUL;
                    strcpy( proxyServer, p );
                    *proxyPort = DEFAULT_HTTP_PORT;
                                        /* �Ƃ肠�����A�f�t�H���g�l�� */
                                        /* ����Ă���                 */
                }
                else {
                    *q++ = NUL;
                    strcpy( proxyServer, p );
                    *proxyPort = (unsigned short)(atol( q ) & 0xFFFF);
                }
                *useProxy = TRUE;

                break;
            }
        }
        fclose( fp );
    }

    return ( found );
}

static BOOL
getProxyInfoViaOpera(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword
    )
{
    /*
     *  Opera �̐ݒ�𒲂ׂ�
     */

    /* �菇                                                               */
    /*  (1) ���W�X�g��                                                    */
    /*        HKEY_CURRENT_USER\Software\Opera Software                   */
    /*      �����݂���΁AOpera �C���X�g�[���ς�                          */
    /*  (2) ��L���W�X�g������ �L�[                                       */
    /*        Last Directory2                                             */
    /*      �̒l���擾 (Last Directory2 �̒l�����Ȃ������ꍇ��          */
    /*      Last Directory3 �̒l���擾)                                   */
    /*  (3) Last Directory2 �� Last Directory3 �����Ȃ������ꍇ��       */
    /*        Plugin Path                                                 */
    /*      �̒l���擾                                                    */
    /*  (4) ��L (2) �܂��� (3) �œ�����񂩂� Opera �̃C���X�g�[����f�B */
    /*      ���N�g�����ǂ������f                                          */
    /*  (5) Opera �̃C���X�g�[����f�B���N�g���ɂ��� OperaDef6.ini �Ƃ��� */
    /*      �t�@�C���̒���                                                */
    /*         HTTP Server=proxy�T�[�o��:�|�[�g�ԍ�                       */
    /*      �Ƃ����L�q������΁Aproxy ���g�p���� (Opera 6 �` 8)           */
    /*  (6) ���ϐ� USERPROFILE �̎w���f�B���N�g���ȉ���                 */
    /*      Application Data/Opera/Opera/profile/opera6.ini �Ƃ����t�@�C  */
    /*      ���̒���                                                      */
    /*         HTTP server=proxy�T�[�o��:�|�[�g�ԍ�                       */
    /*      �Ƃ����L�q������΁Aproxy ���g�p���� (Opera 9)                */

    long    ret;
    HKEY    hk;
    long    type;
    long    sz = BUFSIZ - 1;
    char    buf[BUFSIZ];
    char    *p;
    BOOL    isOperaActive = FALSE;

    ret = RegOpenKeyEx( HKEY_CURRENT_USER,
                        "Software\\Opera Software",
                        0,
                        KEY_READ,
                        &hk );
    if ( ret == ERROR_SUCCESS ) {
        ret = RegQueryValueEx( hk,
                               "Last Directory2",
                               NULL,
                               (unsigned long *)&type,
                               (unsigned char *)buf,
                               (unsigned long *)&sz );
        if ( ret != ERROR_SUCCESS )
            ret = RegQueryValueEx( hk,
                                   "Last Directory3",
                                   NULL,
                                   (unsigned long *)&type,
                                   (unsigned char *)buf,
                                   (unsigned long *)&sz );
                        // ������ �ʏ�͂��ꂪ hit ���� (Opera 6 �ȍ~) ������
        if ( ret != ERROR_SUCCESS ) {
            ret = RegQueryValueEx( hk,
                                   "Plugin Path",
                                   NULL,
                                   (unsigned long *)&type,
                                   (unsigned char *)buf,
                                   (unsigned long *)&sz );
            if ( ret == ERROR_SUCCESS ) {
                p = strstr( buf, "\\\\Program\\\\Plugins" );
                if ( p && *p )
                    *p = NUL;
            }
        }
        if ( ret != ERROR_SUCCESS ) {
            // for Opera 9
            ret = RegQueryValueEx( hk,
                                   "Last CommandLine v2",
                                   NULL,
                                   (unsigned long *)&type,
                                   (unsigned char *)buf,
                                   (unsigned long *)&sz );
            if ( ret == ERROR_SUCCESS ) {
                p = strstr( buf, "\\\\Opera.exe" );
                if ( p && *p )
                    *p = NUL;
            }
        }
        if ( ret == ERROR_SUCCESS ) {
            /* Opera �C���X�g�[���ς݂ł���Ɣ��f */
            isOperaActive = TRUE;
        }
        RegCloseKey( hk );
    }

    if ( isOperaActive == TRUE ) {
        BOOL    found = FALSE;
        char    filename[MAX_PATH];

        sprintf( filename, "%s\\OperaDef6.ini", buf );

        found = readProxySettingFromOperaIni( filename,
                                              useProxy,
                                              proxyServer, proxyPort,
                                              proxyUserName, proxyPassword );
        if ( found == FALSE ) {
            // for Opera 9
            char    *p = getenv("USERPROFILE");

            if ( p && *p ) {
                char    targetDir[MAX_PATH];

                sprintf( targetDir,
                         "%s\\Application Data\\Opera\\Opera\\profile\\", p );
                sprintf( filename, "%sopera6.ini", targetDir );
                found = readProxySettingFromOperaIni(
                                                filename,
                                                useProxy,
                                                proxyServer, proxyPort,
                                                proxyUserName, proxyPassword);
            }
        }
    }

    return ( isOperaActive );
}

void
confirmProxyInfo(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword )
{
    LCID    l = getLanguageCode();

    SetLastError( ERROR_SUCCESS );
    if ( isatty( fileno( stdin ) ) && isatty( fileno( stderr ) ) ) {
        int     yesNo;
        FILE    *fp;

        inputYesNo( &yesNo,
                    l == 0x0411
                        ? "�C���^�[�l�b�g�ւ̐ڑ��� proxy �T�[�o��"
                          "���p���Ă��܂���?"
                        : "Do you access the Internet via a proxy "
                          "server ?" );
        if ( yesNo == TRUE ) {
            char    *p, *q;
            char    buf1[BUFSIZ];
            char    buf2[BUFSIZ];
            char    buf3[BUFSIZ];
            char    buf4[BUFSIZ];

            inputString( buf1,
                         l == 0x0411
                            ? "proxy�T�[�o��URL(�܂���IP�A�h���X): "
                            : "proxy server's URL (or IP address): ",
                            FALSE );
            inputString( buf2,
                         l == 0x0411
                            ? "proxy�T�[�o�̃|�[�g�ԍ�: "
                            : "proxy port number: ",
                            FALSE );

            buf3[0] = NUL;
            buf4[0] = NUL;
            inputYesNo( &yesNo,
                        l == 0x0411
                            ? "���� proxy �T�[�o�𗘗p����̂Ƀ��[�U����"
                              "�K�v�ł���?"
                            : "Do you use this proxy server with "
                              "username ?" );
            if ( yesNo == TRUE ) {
                inputString( buf3,
                             l == 0x0411
                                ? "proxy�T�[�o�̃��[�U��: "
                                : "proxy username: ",
                                FALSE );

                inputYesNo( &yesNo,
                            l == 0x0411
                                ? "���� proxy �T�[�o�𗘗p����̂�"
                                  "�p�X���[�h���K�v�ł���?"
                                : "Do you use this proxy server with "
                                  "password ?" );
                if ( yesNo == TRUE ) {
                    inputString( buf4,
                                 l == 0x0411
                                    ? "proxy�T�[�o�̃p�X���[�h: "
                                    : "proxy password: ",
                                    TRUE );
                }
            }

            if ( ( fp = fopen( "proxy.txt", "w" ) ) != NULL ) {
                p = buf1;
                while ( (*p == ' ') || (*p == '\t') )
                    p++;
                if ( *p                                     &&
                     (((q = strchr( p, '.' )) != NULL) ||
                      (*p < '0') || (*p > '9')            )    ) {
                    strcpy( proxyServer, p );
                    fprintf( fp, "%s\n", proxyServer );
                }

                p = buf2;
                while ( (*p == ' ') || (*p == '\t') )
                    p++;
                if ( (*p >= '0') && (*p <= '9') ) {
                    *proxyPort = (unsigned short)((atol( p ) & 0xFFFF));
                    fprintf( fp, "%d\n", *proxyPort );

                    if ( buf3[0] ) {
                        fprintf( fp, "%s\n", buf3 );
                        if ( proxyUserName )
                            strcpy( proxyUserName, buf3 );
                        if ( buf4[0] ) {
                            fprintf( fp, "%s\n", buf4 );
                            if ( proxyPassword )
                                strcpy( proxyPassword, buf4 );
                        }
                    }
                }

                fclose( fp );

                if ( (*proxyPort > 0) && (proxyServer[0] != NUL) ) {
                    if ( xmlrpc_p->verbose && isatty( fileno( stderr ) ) )
                        fprintf( stderr, "\tproxy = %s:%d\n",
                                 proxyServer, *proxyPort );
                    *useProxy = TRUE;
                }
            }
        }
    }
    else {
        int ret = MessageBox( NULL,
                              l == 0x0411
                                ? "proxy�T�[�o�o�R�ŃC���^�[�l�b�g��"
                                  "���p���Ă��܂���?"
                                : "Do you access the Internet via a "
                                  "proxy server ?",
                              l == 0x0411
                                ? "�C���^�[�l�b�g���p�`�Ԋm�F"
                                : "Confirmation of proxy server",
                            MB_YESNO|MB_ICONQUESTION );
        if ( ret == IDYES ) {
            MessageBox( NULL,
                        l == 0x0411
                          ?
    "���萔�����������܂����Aproxy�T�[�o�̏����������t�@�C����p�ӂ���"
    "���������B\n\n"
    "    �t�@�C����: proxy.txt\n"
    "    �t�@�C���̒��g: \n"
    "      �ȉ���2�s����Ȃ�e�L�X�g�t�@�C��\n"
    "         proxy �T�[�o��(�܂��� IP�A�h���X)\n"
    "         �|�[�g�ԍ�\n\n"
    "      �܂��́A�ȉ���4�s����Ȃ�e�L�X�g�t�@�C��\n"
    "         proxy �T�[�o��(�܂��� IP�A�h���X)\n"
    "         �|�[�g�ԍ�\n"
    "         proxy �T�[�o�ɃA�N�Z�X���邽�߂̃��[�U��\n"
    "         proxy �T�[�o�ɃA�N�Z�X���邽�߂̃p�X���[�h\n\n"
    "��L�̃t�@�C�����A�v���P�[�V����(*.exe)�̂���t�H���_�ɒu���Ă�����"
    "���B\n\n\n"
    "�t�@�C���̗p�ӂ��I���܂�����AOK �{�^���������Ă��������B"
                                  :
    "Make an information file for proxy server.\n\n"
    "    Filename: proxy.txt\n"
    "    Contents of file: \n"
    "      Text file that consists of the following two lines\n"
    "        proxy server's URL (or IP address)\n"
    "        proxy port number\n\n"
    "      Or, Text file that consists of the following four lines\n"
    "        proxy server's URL (or IP address)\n"
    "        proxy port number\n"
    "        username for proxy server\n"
    "        password for proxy server\n\n"
    "Put this file on the folder with the application (that is *.exe).\n\n\n"
    "When you make and put this file, and push the OK button." ,
                        l == 0x0411
                          ? "�ݒ�t�@�C���쐬�v��"
                          : "Make information file for proxy server",
                        MB_OK|MB_ICONQUESTION );

            getProxyInfo( useProxy, proxyServer, proxyPort,
                          proxyUserName, proxyPassword );
        }
        else
            *useProxy = FALSE;

        SetLastError( XMLRPC_ERROR_CHANGED_PROXYINFO );
    }
}

void
getProxyInfo(
        int            *useProxy,
        char           *proxyServer,
        unsigned short *proxyPort,
        char           *proxyUserName,
        char           *proxyPassword
    )
{
    FILE        *fp;
    BOOL        isActive = FALSE;
    char        filename[MAX_PATH];
    struct stat s;

    if ( !useProxy || !proxyServer || !proxyPort )
        return;

    if ( stat( "./noproxy.txt", &s ) == 0 ) {
        *useProxy = FALSE;
        return;
    }

#ifdef  WIN32
    if ( __argv && __argv[0] && __argv[0][0] ) {
        char    *p;

        strcpy( filename, __argv[0] );
        p = strrchr( filename, '\\' );
        if ( p )
            *p = NUL;
        else {
            p = strrchr( filename, '/' );
            if ( p )
                *p = NUL;
            else
                strcpy( filename, "." );
        }
        strcat( filename, "/proxy.txt" );
    }
    else
        strcpy( filename, "./proxy.txt" );
#else
    strcpy( filename, "./proxy.txt" );
#endif
    if ( ( fp = fopen( filename, "r" ) ) != NULL ) {
        char    *p, *q;
        char    buf[BUFSIZ];
        int     lineCnt     = 0;
        BOOL    useUserName = FALSE;

        while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
            if ( p[strlen(p) - 1] == '\n' )
                p[strlen(p) - 1] = NUL;
            if ( ((q = strchr( p, '.' )) != NULL) ||
                 (*p < '0') || (*p > '9') ) {
                if ( lineCnt == 0 )
                    strcpy( proxyServer, p );
                else if ( useUserName == FALSE ) {
                    if ( proxyUserName )
                        strcpy( proxyUserName, p );
                    useUserName = TRUE;
                }
                else if ( useUserName == TRUE ) {
                    if ( proxyPassword )
                        strcpy( proxyPassword, p );
                    break;  /* �c��̍s�͓ǂ܂Ȃ� */
                }
                lineCnt++;
            }
            else if ( (*p >= '0') && (*p <= '9') ) {
                *proxyPort = (unsigned short)((atol( p ) & 0xFFFF));
                lineCnt++;
            }
        }
        fclose( fp );

        if ( (*proxyPort > 0) && (proxyServer[0] != NUL) ) {
            if ( xmlrpc_p->verbose && isatty( fileno( stderr ) ) ) {
                if ( proxyUserName && *proxyUserName ) {
                    if ( proxyPassword && *proxyPassword )
                        fprintf( stderr, "\tproxy = %s:%s@%s:%d\n",
                                 proxyUserName, proxyPassword,
                                 proxyServer, *proxyPort );
                    else
                        fprintf( stderr, "\tproxy = %s@%s:%d\n",
                                 proxyUserName,
                                 proxyServer, *proxyPort );
                }
                else
                    fprintf( stderr, "\tproxy = %s:%d\n",
                             proxyServer, *proxyPort );
            }
            *useProxy = TRUE;
            isActive  = TRUE;
        }
    }

#ifdef  WIN32
    if ( *useProxy == FALSE ) {
        int     browser = getDefaultBrowser();

        switch ( browser ) {
        case BR_FIREFOX:
            isActive = getProxyInfoViaFirefox( useProxy,
                                               proxyServer, proxyPort,
                                               proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaInternetExplorer(
                                        useProxy, proxyServer, proxyPort,
                                        proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaOpera(useProxy,
                                                proxyServer, proxyPort,
                                                proxyUserName, proxyPassword);
            break;

        case BR_OPERA:
            isActive = getProxyInfoViaOpera( useProxy, proxyServer, proxyPort,
                                             proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaInternetExplorer(
                                        useProxy, proxyServer, proxyPort,
                                        proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaFirefox( useProxy,
                                               proxyServer, proxyPort,
                                               proxyUserName, proxyPassword );
            break;

        case BR_IEXPLORER:
        default:
            isActive = getProxyInfoViaInternetExplorer(
                                            useProxy, proxyServer, proxyPort,
                                            proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaFirefox( useProxy,
                                               proxyServer, proxyPort,
                                               proxyUserName, proxyPassword );
            if ( *useProxy == FALSE )
                isActive = getProxyInfoViaOpera( useProxy,
                                               proxyServer, proxyPort,
                                               proxyUserName, proxyPassword );
            break;
        }
    }
#endif  /* WIN32 */

    if ( isActive == FALSE ) {
        if ( xmlrpc_p->confirmProxyInfo ) {
            if ( xmlrpc_p->confirmProxyInfo != (CONF_FUNC)(-1) )
                isActive = xmlrpc_p->confirmProxyInfo(
                                        useProxy,
                                        proxyServer, proxyPort,
                                        proxyUserName, proxyPassword );
        }
        else
            confirmProxyInfo( useProxy,
                              proxyServer, proxyPort,
                              proxyUserName, proxyPassword );
    }
}

int
isUsedProxy()
{
    int             useProxy = FALSE;
    char            server[MAX_PATH];
    unsigned short  proxyPort = 0;
    char            proxyUserName[MAX_NAMELEN + 1];
    char            proxyPassword[MAX_NAMELEN + 1];

    server[0]        = NUL;
    proxyUserName[0] = NUL;
    proxyPassword[0] = NUL;
    getProxyInfo( &useProxy, server, &proxyPort,
                  proxyUserName, proxyPassword );

    return ( useProxy );
}

void    setConfirmProxyInfoFunc( CONF_FUNC confirmProxyInfo )
{
    if ( confirmProxyInfo )
        xmlrpc_p->confirmProxyInfo = confirmProxyInfo;
    else
        xmlrpc_p->confirmProxyInfo = NULL;
}

BOOL    isNecessaryToCheckProxyInfo()
{
    return ( xmlrpc_p->needToCheckProxyInfo );
}

void    setProxyInfo( const char *proxyServer, unsigned short proxyPort,
                      const char *proxyUsername, const char *proxyPassword )
{
    xmlrpc_p->proxyServer[0]   = NUL;
    xmlrpc_p->proxyPort        = 0;
    xmlrpc_p->proxyUserName[0] = NUL;
    xmlrpc_p->proxyPassword[0] = NUL;

    if ( proxyServer && *proxyServer ) {
        strcpy( xmlrpc_p->proxyServer, proxyServer );
        xmlrpc_p->proxyPort = proxyPort;
        if ( proxyUsername && *proxyUsername ) {
            strcpy( xmlrpc_p->proxyUserName, proxyUsername );
            if ( proxyPassword && *proxyPassword )
                strcpy( xmlrpc_p->proxyPassword, proxyPassword );
        }
    }
}

int
httpPostEx( char *request, char *response )
{
    int ret   = 0;
    int done  = FALSE;
    int count = 0;

    do {
        ret = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        NULL,
                        request, response );

        done = TRUE;
        if ( (ret == 0) || (response[0] != NUL) ) {
            char    *p = strstr( response, "<struct>" );
            if ( p ) {
                char    *q = strchr( p, 0xC3 );
                if ( q ) {
#ifndef _DEBUG
                    if ( xmlrpc_p->verbose )
#endif
                        if ( isatty( fileno( stderr ) ) )
                            fprintf( stderr, "�����������o!!\n" );
                    done = FALSE;
                }
            }
        }
        count++;
        if ( count > 16 )
            break;
    } while ( !done );

    return ( ret );
}


/*
 *  �O�����J�p ���[�e�B���e�B�֐�
 */

/* verbose ���[�h�ؑ� */
void    setVerbose( int verbose, FILE *fp )
{
    if ( xmlrpc_p ) {
        xmlrpc_p->verbose = verbose;
        if ( verbose )
            xmlrpc_p->verboseFp = fp;
        else
            xmlrpc_p->verboseFp = stderr;
    }
}


/* dump ���[�h�ؑ� */
#if !defined (_DEBUG) && !defined (CHECK_DETAIL)
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
#endif
void    setDump( int dump, FILE *dumpFp )
{
#if defined (_DEBUG) || defined (CHECK_DETAIL)
    if ( xmlrpc_p ) {
        xmlrpc_p->dump = dump;
        if ( dump )
            xmlrpc_p->dumpFp = dumpFp;
        else
            xmlrpc_p->dumpFp = NULL;
    }
#endif
}
#if !defined (_DEBUG) && !defined (CHECK_DETAIL)
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif
#endif


/* proxy ���[�h�ؑ� */
void    setUseProxy( int useProxy )
{
    if ( xmlrpc_p )
        xmlrpc_p->useProxy = useProxy;
}


/* User-Agent �ݒ�ύX */
void    setUserAgent( const char *userAgent )
{
    if ( xmlrpc_p ) {
        memset( xmlrpc_p->userAgent, NUL, MAX_LOGICALLINELEN );
        if ( userAgent && userAgent[0] )
            strncpy( xmlrpc_p->userAgent, userAgent, MAX_LOGICALLINELEN - 2 );
    }
}

/* Referer �ݒ�ύX */
void    setReferer( const char *referer )
{
    if ( xmlrpc_p ) {
        memset( xmlrpc_p->referer, NUL, MAX_URLLENGTH_MAX );
        if ( referer && referer[0] )
            strncpy( xmlrpc_p->referer, referer, MAX_URLLENGTH_MAX - 2 );
    }
}

/* for OAuth */
#if !defined(USE_AUTHORIZATION_OAUTH)
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
#endif
void    setOAuthHeader( const char *header )
{
#ifdef  USE_AUTHORIZATION_OAUTH
    if ( xmlrpc_p ) {
        memset( xmlrpc_p->oauth_header, NUL, MAX_OAUTH_HEADER_LEN );
        if ( header && header[0] )
            strncpy( xmlrpc_p->oauth_header, header, MAX_OAUTH_HEADER_LEN - 2 );
    }
#endif
    return;
}
#if !defined(USE_AUTHORIZATION_OAUTH)
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif
#endif

/* ���[�U���ݒ� */
void    setUserInfo( const char *userName, const char *password )
{
    if ( xmlrpc_p ) {
        strcpy( xmlrpc_p->userName, userName );
        strcpy( xmlrpc_p->password, password );
    }
}


/* webServer, webPage �ݒ� */
void    setTargetURL( const char *targetURL )
{
    const char  *p, *q;
    const char  *hStr = "http://";
    const char  *sStr = "https://";
    char        *url;
    int         len   = strlen( hStr );
    BLOGINFOTBL *pp;

    url = (char *)malloc( strlen(targetURL) + 16 );
    if ( !url )
        return;

    strcpy( url, targetURL );
    p = strstr( url, "://" );
    if ( p ) {
        p += 3;
        q = strchr( p, '/' );
        if ( !q )
            strcat( url, "/" );
    }

    p = url;
    xmlrpc_p->useSSL = FALSE;
    if ( !strncmp( p, hStr, len ) ) {
        p += len;
        xmlrpc_p->useSSL = FALSE;
    }
    else {
        len   = strlen( sStr );
        if ( !strncmp( p, sStr, len ) ) {
            p += len;
            xmlrpc_p->useSSL = TRUE;
        }
    }
    if ( ( q = strchr( p, '/' ) ) != NULL ) {
        strncpy( xmlrpc_p->webServer, p, q - p );
        xmlrpc_p->webServer[q - p] = NUL;
        strcpy( xmlrpc_p->webPage, q );
    }

    if ( xmlrpc_p->useProxy ) {
        if ( !(xmlrpc_p->proxyServer[0]) ) {
            xmlrpc_p->useProxy = FALSE;
            getProxyInfo( &xmlrpc_p->useProxy,
                          xmlrpc_p->proxyServer,
                          &xmlrpc_p->proxyPort,
                          xmlrpc_p->proxyUserName,
                          xmlrpc_p->proxyPassword );
            if ( xmlrpc_p->useProxy == FALSE )
                if ( isatty( fileno( stderr ) ) )
                    fprintf( stderr, "\tNot specified proxy server\n" );
        }
    }

    for ( pp = &(blogInfoTbl[0]); pp->blogType != -1; pp++ ) {
        if ( pp->xmlEndpoint && *(pp->xmlEndpoint) &&
             !strcmp( targetURL, pp->xmlEndpoint ) ) {
            xmlrpc_p->blogKind = pp->blogType;
            break;
        }
        if ( pp->atomEndpoint && *(pp->atomEndpoint) ) {
            if ( !strcmp( targetURL, pp->atomEndpoint ) ) {
                xmlrpc_p->blogKind = pp->blogType;
                break;
            }
            
            p = strchr( pp->atomEndpoint, '{' );
            if ( p ) {
                size_t  len = p - pp->atomEndpoint;
                if ( !strncmp( targetURL, pp->atomEndpoint, len ) ) {
                    xmlrpc_p->blogKind = pp->blogType;
                    break;
                }
            }
        }
    }

    free( url );
}


/* blog ��ʐݒ� */
void    setBlogKind( int blogKind )
{
    if ( xmlrpc_p )
        xmlrpc_p->blogKind = blogKind;
}


/* �f�[�^�t�@�C���i�[��f�B���N�g�����ݒ� */
void    setDataDir( const char *dirname )
{
    if ( xmlrpc_p ) {
        strcpy( xmlrpc_p->dataDir, dirname );
    }
}

/* �͂Ăȃ_�C�A���[�L�[���[�h���X�g�t�@�C�����ݒ� */
void    setKeywordList( const char *filename )
{
    if ( xmlrpc_p ) {
        strcpy( xmlrpc_p->keywordList, filename );
    }
}



/* base64 �G���R�[�_ */
static char b[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  /* 0000000000111111111122222222223333333333444444444455555555556666 */
  /* 0123456789012345678901234567890123456789012345678901234567890123 */
char    *
base64( const unsigned char *src, size_t sz )
{
    unsigned char               *pp, *p, *q;
    Thread static unsigned char *qq = NULL;
    size_t                      i, safe = sz;

    if ( qq ) {
        free( qq );
        qq = NULL;
    }
    if ( !src || (sz == 0) )
        return ( NULL );

    if ( (sz % 3) == 1 ) {
        p = (unsigned char *)malloc( sz + 2 );
        if ( !p )
            return ( NULL );
        memcpy( p, src, sz );
        p[sz] = p[sz + 1] = '=';
        sz += 2;
    }
    else if ( (sz % 3) == 2 ) {
        p = (unsigned char *)malloc( sz + 1 );
        if ( !p )
            return ( NULL );
        memcpy( p, src, sz );
        p[sz] = '=';
        sz++;
    }
    else
        p = (unsigned char *)src;

    q = (unsigned char *)malloc( (sz / 3) * 4 + 2 );
    if ( !q ) {
        if ( p != src )
            free( p );
        return ( NULL );
    }

    pp = p;
    qq = q;
    for ( i = 0; i < sz; i += 3 ) {
        q[0] = b[(p[0] & 0xFC) >> 2];
        q[1] = b[((p[0] & 0x03) << 4) | ((p[1] & 0xF0) >> 4)];
        q[2] = b[((p[1] & 0x0F) << 2) | ((p[2] & 0xC0) >> 6)];
        q[3] = b[p[2] & 0x3F];
        p += 3;
        q += 4;
    }
    *q = NUL;
    if ( (safe % 3) == 1 ) {
        *(q - 1) = '=';
        *(q - 2) = '=';
    }
    if ( (safe % 3) == 2 )
        *(q - 1) = '=';

    if ( pp != src )
        free( pp );
    return ( (char *)qq );
}

/* base64�f�R�[�_ */
static int
code( int c )
{
    int ret = -1, i;

    for ( i = 0; i < 64; i++ ) {
        if ( c == b[i] ) {
            ret = i;
            break;
        }
    }

    return ( ret );
}

char   *
unbase64( const unsigned char *src, unsigned char *dst, size_t *sz )
{
    const char      *p;
    unsigned char   *q;
    int             i, j, k, l;

    if ( src && *src && dst ) {
        p = (char *)src;
        q = dst;

        while ( *p ) {
            i = code( *p++ );
            j = code( *p++ );
            k = code( *p++ );
            l = code( *p++ );

            *q++ = (unsigned char)(((i & 0x3F) << 2) | ((j & 0x30) >> 4));

            if ( k == -1 ) {
                *q++ = NUL;
                break;
            }
            else
                *q++ = (unsigned char)(((j & 0x0F) << 4) | ((k & 0x3C) >> 2));

            if ( l == -1 ) {
                *q++ = NUL;
                break;
            }
            else
                *q++ = (unsigned char)(((k & 0x03) << 6) | (l & 0x3F));
        }

        *q = NUL;
        if ( sz )
            *sz = q - dst;
    }

    return ( dst ? (char *)dst : (char *)src );
}


/*
 *  �g���b�N�o�b�N���M
 *      blogName, articleURL, targetURL �̂ݕK�{
 */
int
sendTrackbackPing( const char *blogName,
                   const char *articleTitle,
                   const char *articleURL,
                   const char *articleExcerpt,
                   const char *targetURL )
{
    int     ret = -1;
    char    str[3][1024];
    char    request[2048];
    char    *response;
    char    *p, *q;
    size_t  sz;

    if ( !blogName     || !(*blogName)     ||
         !articleURL   || !(*articleURL)   ||
         !targetURL    || !(*targetURL)       )
        return ( ret );

    // 80�o�C�g�ȉ��ɂȂ�悤�ɐ؂�l�߂�
    normalizeString( str[0], blogName, 80 );
    q = sjis2utf(str[0]);
    p = encodeURL( q ? q : str[0] );
    strcpy( str[0], p ); // blogName

    if ( articleTitle && *articleTitle ) {
        // 160�o�C�g�ȉ��ɂȂ�悤�ɐ؂�l�߂�
        normalizeString( str[1], articleTitle, 160 );
        q = sjis2utf(str[1]);
        p = encodeURL( q ? q : str[1] );
        strcpy( str[1], p ); // articleTitle

        if ( articleExcerpt && *articleExcerpt ) {
            // 160�o�C�g�ȉ��ɂȂ�悤�ɐ؂�l�߂�
            normalizeString( str[2], articleExcerpt, 160 );
            q = sjis2utf(str[2]);
            p = encodeURL( q ? q : str[2] );
            strcpy( str[2], p ); // articleExcerpt
	        sprintf( request,
                     "title=%s"
                     "&url=%s"
                     "&excerpt=%s"
                     "&blog_name=%s"
                     "&charset=UTF-8", // ����: charset �w��͓��{�� blog �E
                                       //       (�̈ꕔ)�Œ񏥂��ꂽ���̂ł�
                                       //       ��(�����R�[�h���݂̖�������
                                       //       ���邽��)
                                       //       ���������āA�ǂ� blog ���T�|�[
                                       //       �g���Ă���Ƃ͌���Ȃ�(�T�|�[
                                       //       �g���Ă��Ȃ��ꍇ�́Acharset��
                                       //       ���͒P�ɖ�������邾��)
                     str[1],    // articleTitle
                     articleURL,// articleURL
                     str[2],    // articleExcerpt
		             str[0] );  // blogName
        }
        else {
	        sprintf( request,
                     "title=%s"
                     "&url=%s"
                     "&blog_name=%s"
                     "&charset=UTF-8",
                     str[1],    // articleTitle
                     articleURL,// articleURL
		             str[0] );  // blogName
        }
    }
    else {
        if ( articleExcerpt && *articleExcerpt ) {
            // 160�o�C�g�ȉ��ɂȂ�悤�ɐ؂�l�߂�
            normalizeString( str[1], articleExcerpt, 160 );
            q = sjis2utf(str[1]);
            p = encodeURL( q ? q : str[1] );
            strcpy( str[1], p ); // articleExcerpt
	        sprintf( request,
                     "url=%s"
                     "&excerpt=%s"
                     "&blog_name=%s"
                     "&charset=UTF-8",
                     articleURL,
                     str[1],    // articleExcerpt
		             str[0] );  // blogName
        }
        else {
	        sprintf( request,
                     "url=%s"
                     "&blog_name=%s"
                     "&charset=UTF-8",
                     articleURL,
		             str[0] );  // blogName
        }
    }

    sz = MAX_CONTENT_SIZE * 64;
    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );

    if ( xmlrpc_p ) {
        /* GET ���\�b�h�ɂ��g���b�N�o�b�N���M�� 2003�N2���� �܂ŗL���A�� */
        /* ��ȍ~�� POST ���\�b�h�̂ݗL���Ƃ������ƂɂȂ��Ă��邪�A���ۂ�  */
        /* �́AMovableType 2.6x ���A���݂ł� GET, POST �̂ǂ���ł��󂯕t  */
        /* ������̂�����                                                  */
#ifdef  USE_HTTPGET_VERSION_TRACKBACK
        char    action[2048];

        sprintf( action, "%s?%s", targetURL, request );
        setTargetURL( action );
        setUpReceiveBuffer( response, sz );
        ret = httpGet( xmlrpc_p->webServer, xmlrpc_p->webPage,
                       response, stderr, 0 );
#else   /* USE_HTTPPOST_VERSION_TRACKBACK */
        setTargetURL( targetURL );
        setUpReceiveBuffer( response, sz );
        ret = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        "application/x-www-form-urlencoded",
                        request, response );
#endif  /* USE_HTTPPOST_VERSION_TRACKBACK */

        // response �̒��g���ᖡ���āA�g���b�N�o�b�N���M����/���s�𔻒f
        if ( strstr( response, "<error>1</error>" ) )
            ret = -1;
    }

    /* �̈��� */
    free( response );
    encodeURL( NULL );

    return ( ret ); // ret: 0 �̂Ƃ�����I���A-1 �̂Ƃ��G���[�A-2 �̂Ƃ��ʐM
                    //      �r���ŉ���ؒf���o(����I���Ƃ݂Ȃ�)
}

char    *
decodeEncyptedTrackbackURL( const char *encyptedTrackbackURL )
{
    /* �Í�������Ă���g���b�N�o�b�NURL�𕜍����� (for �y�V�L��) */
    Thread static char  trackbackURL[MAX_URLLENGTH];
    const char          *p = encyptedTrackbackURL;
    char                *q = trackbackURL;

    trackbackURL[0] = NUL;
    while ( *p )
        *q++ = (char)(*p++ ^ 0x04);
    *q = NUL;

    return ( trackbackURL );
}

/*
 *  �w��L���̃g���b�N�o�b�N���M�pURL�̎擾
 *      (1) �����Ƃ��� trackback Auto-discovery �@�\���g���Ď擾
 *      (2) �������Atrackback Auto-discovery ���Ή��ȂƂ���ł��A
 *          �L���� URL �����ɁA���̖@���Ńg���b�N�o�b�N���M�p
 *          URL �����߂邱�Ƃ��ł���ꍇ�́A���� URL ��Ԃ�
 */
char    *
getTrackbackURL( const char *articleURL )
{
    Thread static char  trackbackURL[MAX_URLLENGTH];
    char                jsURL[MAX_URLLENGTH];
    char                *response;
    const char          *p, *q;
    int                 ret;
    size_t              sz;

    memset( trackbackURL, NUL, MAX_URLLENGTH );

    /* �w�� Web �y�[�W���擾 */
    sz = MAX_CONTENT_SIZE * 64; /* �O�̂��߂ɑ傫�߂Ɋm�� */
    response = (char *)malloc( sz );
    if ( !response )
        return ( NULL );

    setTargetURL( articleURL );
    setUpReceiveBuffer( response, sz );
    ret = httpGet( xmlrpc_p->webServer, xmlrpc_p->webPage,
                   response, NULL, FALSE,
                   NULL, NULL, NULL, NULL, NULL );
    if ( response[0] == NUL  ) {
        free( response );
        return ( NULL );
    }

    /* �����g�����g�p���Ă��邩�ǂ����̃`�F�b�N */
    jsURL[0] = NUL;
    if ( ( p = strstr( response,
                  "=\"http://rentra.zansin.jp/pl/gate.tb/" ) ) != NULL ) {

        // �����g�����g���Ă���ꍇ
        p += 2;
        q = strstr( p, "\">" );
        if ( q ) {
            char    dummy[BUFSIZ];
            char    *r;
            int     l;

            r = strstr( p, "gate.tb/" );
            if ( !(((*(r + 8) >= '0') && (*(r + 8) <= '9')) ||
                   ((*(r + 8) >= 'A') && (*(r + 8) <= 'Z')) ||
                   ((*(r + 8) >= 'a') && (*(r + 8) <= 'z'))   ) ) {
                free( response );
                return ( NULL );
            }

            strncpy( jsURL, p, r - p );
            jsURL[r - p] = NUL;
            strcat( jsURL, "normal.tb/" );

            l = strlen( jsURL );
            r += 8;
            strncat( jsURL, r, q - r);
            jsURL[l + (q - r)] = NUL;

            sprintf( dummy, "Referer: %s\r\n", articleURL );
                /* -- Referer: �̎w�肪�Ȃ��ƌx�����b�Z�[�W���Ԃ��Ă��� */

            /* JavaScript ���擾 */
            setTargetURL( jsURL );
            setUpReceiveBuffer( response, sz );
            ret = httpGet( xmlrpc_p->webServer, xmlrpc_p->webPage,
                           response, NULL, FALSE,
                           NULL, NULL, dummy, NULL, NULL );
            if ( response[0] == NUL  ) {
                free( response );
                return ( NULL );
            }

            p = strstr( response, "http://rentra.zansin.jp/pl/tb_show.cgi/" );
            if ( p ) {
                q = strchr( p, '\'' );
                if ( !q )
                    q = strchr( p, '"' );
                if ( q ) {
                    strncpy( jsURL, p, q - p );
                    jsURL[q - p] = NUL;
                }
            }
        }
    }

    /* trackback auto-discovery �����݂� */
    /* (1) head ������ df:Description ������ꍇ (MovableType �Ȃ�) */
    /* (2) body ������ df:Description ������ꍇ (�{���� trackback  */
    /*     auto-discovery)                                          */
    p = strstr( response, "rdf:Description" );
    if ( !p )
        p = strstr( response, "RDF:DESCRIPTION" );
    if ( p ) {
        p += 15;
        q = strstr( p, "trackback:ping=\"=\"" );
        if ( q )
            q += 2; // blog2.fc2.com �̃o�O�ɑΉ�
        else
            q = strstr( p, "trackback:ping=\"" );
        if ( q ) {
            p = q + 16;
            q = strchr( p, '"' );
            if ( q ) {
                strncpy( trackbackURL, p, q - p );
                trackbackURL[q - p] = NUL;
            }
        }
    }

    /* (3) ���̑��A����� blog/CMS�c�[�� �Ή����� */
    if ( trackbackURL[0] == NUL ) {
        if ((p=strstr(response,"=\"http://www.haloscan.com/load/")) != NULL) {
            // HaloScan ���g���Ă���ꍇ
            char    userID[MAX_URLLENGTH];
            char    tbID[32];

            p += strlen( "=\"http://www.haloscan.com/load/" );
            q = strchr( p, '"');
            if ( !q )
                q = strchr( p, '>' );
            if ( q ) {
                strncpy( userID, p, q - p );
                userID[q - p] = NUL;

                if ( ( p = strstr( q + 1, ":HaloScanTB(" ) ) != NULL ) {
                    p += strlen( ":HaloScanTB(" );
                    while ( *p && ((*p < '0') || (*p > '9')) )
                        p++;
                    if ( *p ) {
                        q = p + 1;
                        while ( (*q >= '0') && (*q <= '9') )
                            q++;
                        strncpy( tbID, p, q - p );
                        tbID[q - p] = NUL;

                        sprintf( trackbackURL,
                                 "http://www.haloscan.com/tb/%s/%s",
                                 userID, tbID );
                    }
                }
            }
        }
        else if ( !strncmp(articleURL, "http://plaza.rakuten.co.jp/", 27) ) {
            /* �y�V�L��̏ꍇ */
            p = strstr( response, "<span class=\"jscrypt\"" );
            if ( p ) {
                /* �g���b�N�o�b�NURL���Í�������Ă���ꍇ (2006�N5��29���ȍ~) */
                p += 21;
                q = strstr( p, "title=\"" );
                if ( q ) {
                    p = q + 7;
                    q = strchr( p, '"' );
                    if ( q ) {
                        char    encryptedTbID[80];
                        strncpy( encryptedTbID, p, q - p );
                        encryptedTbID[q - p] = NUL;
                        q = decodeString( encryptedTbID );
                        if ( q )
                            strcpy( encryptedTbID, q );
                        q = decodeEncyptedTrackbackURL( encryptedTbID );
                        if ( q )
                            strcpy( trackbackURL, q );
                    }
                }
            }
            else {
                /* �]���̊y�V�L��̏ꍇ (2006�N5��29���ȑO) */
                p = strstr( response, "&tbUrl=http://tb.plaza.rakuten.co.jp/" );
                q = NULL;
                if ( p ) {
                    p += 7;
                    q = strchr( p, '"' );
                }
                else {
                    p = strstr( response, "http://tb.plaza.rakuten.co.jp/" );
                    if ( p ) {
                        q = strchr( p, '\n' );
                        if ( !q )
                            q = strchr( p, '\r' );
                        if ( !q )
                            q = strchr( p, ' ' );
                    }
                }
                if ( p && q ) {
                    strncpy( trackbackURL, p, q - p );
                    trackbackURL[q - p] = NUL;
                }
                if ( trackbackURL[0] == NUL )  {
                    sprintf( trackbackURL, "http://tb.plaza.rakuten.co.jp/%s",
                             articleURL + 27 );
                }
            }
        }
        else if ( !strncmp( articleURL, "http://blog.melma.com", 21 ) ||
                  ( strstr( articleURL, "ap.teacup.com/" ) != NULL )     ) {
            /* melma! blog �܂��� AutoPage �̏ꍇ */
            if ( ( p = strchr( articleURL, '#' ) ) != NULL ) {
                strncpy( trackbackURL, articleURL, p - articleURL );
                trackbackURL[p - articleURL] = NUL;
            }
            else
                strcpy( trackbackURL, articleURL );

            /* AutoPage �̏ꍇ */
            if ( strstr( articleURL,"ap.teacup.com/" ) != NULL ) {
                if ( ( p = strstr( articleURL, ".html") ) != NULL ) {
                    strncpy( trackbackURL, articleURL, p - articleURL );
                    trackbackURL[p - articleURL] = NUL;
                }

                if ( !strstr( trackbackURL, "applet" ) ) {
                    char    temp[MAX_URLLENGTH];

                    p = strstr( trackbackURL, "teacup.com/" ) + 11;
                    strncpy( temp, trackbackURL, p - trackbackURL );
                    temp[p - trackbackURL] = NUL;
                    strcat( temp, "applet/" );
                    strcat( temp, p );
                    strcpy( trackbackURL, temp );
                }
            }

            /* �ȉ��Amelma! blog, AutoPage ���ʏ��� */
            if ( trackbackURL[strlen(trackbackURL) - 1] != '/' )
                strcat( trackbackURL, "/" );
            strcat( trackbackURL, "trackback" );
        }
        else if ( strstr( articleURL, "http://yaplog.jp/"      ) ||
                  strstr( articleURL, "http://blog.drecom.jp/" )    ) {
            // ���v���O! �܂��� �h���R���u���O �̏ꍇ
            //  ��) http://yaplog.jp/cocousagi/archive/50
            //          �� http://yaplog.jp/cocousagi/tb_ping/50
            char    temp[MAX_URLLENGTH];

            p = strstr( articleURL, "archive/" );
            q = strrchr( articleURL, '/' );
            if ( p && q ) {
                strncpy( temp, articleURL, p - articleURL );
                temp[p - articleURL] = NUL;
                strcat( temp, "tb_ping" );
                strcat( temp, q );
                strcpy( trackbackURL, temp );
            }
        }
        else if (strstr(articleURL,"http://carlife.carview.co.jp/User.asp")) {
            // �݂�J���̏ꍇ
            //  ��) http://carlife.carview.co.jp/User.asp?UserDiaryID=78139
            //          �� http://feed.carview.co.jp/tb.aspx?t=blog&i=78139
            p = strrchr( articleURL, '=' );
            if ( p ) {
                p++;
                sprintf( trackbackURL,
                         "http://feed.carview.co.jp/tb.aspx?t=blog&i=%s", p );
            }
        }
        else if ( !strncmp( articleURL, "http://www.mypress.jp/", 22 ) &&
                  ( ( p = strstr( articleURL, "?story_id=" ) ) != NULL ) ) {
            // �}�C�Ղꂷ �̏ꍇ
            //  ��) http://www.mypress.jp/v2_writers/tenmonbu/story/?story_id=895426
            //          �� http://www.mypress.jp/trackback/tb_popup.php?tb_id=895426
            p += 10;
            sprintf( trackbackURL,
                     "http://www.mypress.jp/trackback/tb_popup.php?tb_id=%s",
                     p );
        }
        else if ( !strncmp( articleURL, "http://blog.kansai.com/", 23 ) ) {
            // �֐��ǂ��ƃR�� �̏ꍇ
            //  ��) http://blog.kansai.com/ukiyo/1
            //          �� http://blog.kansai.com/tb/ukiyo/1
            p = articleURL;
            p += 23;
            sprintf( trackbackURL,
                     "http://blog.kansai.com/tb/%s", p );
        }
        else if ( !strncmp( articleURL, "http://blog.zaq.ne.jp/", 22 ) ) {
            // BLOGari �̏ꍇ
            //  ��) http://blog.zaq.ne.jp/unplugged/article/232/
            //         �� http://blog.zaq.ne.jp/unplugged/trackback/232/ 
            char    temp[MAX_URLLENGTH];

            p = strstr( articleURL, "article/" );
            q = strrchr( articleURL, '/' );
            if ( p && q ) {
                strncpy( temp, articleURL, p - articleURL );
                temp[p - articleURL] = NUL;
                strcat( temp, "trackback" );
                strcat( temp, q );
                strcpy( trackbackURL, temp );
            }
        }
        else if ( !strncmp( articleURL, "http://blog.naver.co.jp/", 24 ) ) {
            // NAVER�u���O �̏ꍇ
            //  ��) http://blog.naver.co.jp/yahoo__bb/50000981932
            //      http://blog.naver.co.jp/yahoo__bb.do?Redirect=Dlog&Qs=/yahoo__bb/50000981932
            //      http://blog.naver.co.jp/post/postView.jsp?blogId=yahoo__bb&logNo=50000981932
            //         �� http://blog.naver.co.jp/tb/yahoo__bb/50000981932
            char    *r, *s;
            char    userName[MAX_URLLENGTH];

            userName[0] = NUL;
            p = articleURL;
            p += 24;
            q = p + strlen( p );
            while ( (*(q - 1) >= '0') && (*(q - 1) <= '9') )
                q--;
            if ( !strncmp( p, "post/", 5 ) ) {
                p += 5;
                r = strstr( p, "blogId=" );
                if ( r ) {
                    r += 7;
                    s = strchr( r, '&' );
                    if ( !s )
                        s = r + strlen( r );
                    strncpy( userName, r, s - r );
                    userName[s - r] = NUL;
                }
            }
            else {
                r = strstr( p, ".do?" );
                if ( !r )
                    r = strchr( p, '/' );
                if ( r ) {
                    strncpy( userName, p, r - p );
                    userName[r - p] = NUL;
                }
            }

            if ( userName[0] && (q > p) )
                sprintf( trackbackURL,
                         "http://blog.naver.co.jp/tb/%s/%s",
                         userName, q );
        }
        else if ( !strncmp( articleURL,
                            "http://spaces.msn.com/members/", 30 ) ) {
            // msn Spaces �̏ꍇ
            //  ��) http://spaces.msn.com/members/kazumao/Blog/cns!1pmDEFJ6LYrvL9rl0_HcQKfw!210.entry
            //         �� http://spaces.msn.com/members/kazumao/blog/cns!1pmDEFJ6LYrvL9rl0_HcQKfw!210.trak
            //           (http://spaces.msn.com/members/kazumao/Blog/cns!1pmDEFJ6LYrvL9rl0_HcQKfw!210.trak)
            if ( ( p = strstr( articleURL, ".entry" ) ) != NULL ) {
                strcpy( trackbackURL, articleURL );
                strcpy( trackbackURL + (p - articleURL), ".trak" );
            }
        }
        else if ( jsURL[0] ||
                  strstr( articleURL,
                          "http://rentra.zansin.jp/pl/tb_show.cgi/" ) ) {
            // �����g���̏ꍇ
            if ( jsURL[0] == NUL )
                strcpy( jsURL, articleURL );
            p = strstr( jsURL, "tb_show.cgi/" );
            if ( p ) {
                q = p + 12;
                strncpy( trackbackURL, jsURL, p - jsURL );
                trackbackURL[p - jsURL] = NUL;
                strcat( trackbackURL, "get.tb/" );
                strcat( trackbackURL, q );
            }
        }
        else {
            // ����ȊO
            // �gid="trackback"�h�ȃ^�O�ߕӂ��炻����ۂ� URL ���E���o��
            if ( ((p = strstr(response, "id=\"trackback\""  )) != NULL) ||
                 ((p = strstr(response, "name=\"trackback\"")) != NULL)    ) {
                if ( ( q = strstr( p + 14, "http://" ) ) != NULL ) {
                    if ( ( ( p = strchr( q, '"' ) ) != NULL ) ||
                         ( ( p = strchr( q, ' ' ) ) != NULL ) ||
                         ( ( p = strchr( q, '>' ) ) != NULL ) ||
                         ( ( p = strchr( q, '<' ) ) != NULL )    ) {
                        char    *r = strchr( q + 7, '/' );
                        if ( r && !strncmp( q, articleURL, r - q ) ) {
                            strncpy( trackbackURL, q, p - q );
                            trackbackURL[p - q] = NUL;
                            if ( ( r = strchr( trackbackURL, '<' ) ) != NULL )
                                *r = NUL;
                            if ( ( r = strchr( trackbackURL, '>' ) ) != NULL )
                                *r = NUL;
                            if ( ( r = strchr( trackbackURL, ' ' ) ) != NULL )
                                *r = NUL;
                            if ( ( r = strchr( trackbackURL, '"' ) ) != NULL )
                                *r = NUL;
                        }
                    }
                }
            }

            if ( trackbackURL[0] == NUL ) {
                // trackback.php �Ƃ� trackback.cgi �Ƃ����E���Ă݂�
                //   (Nucleus �͂��̕��@�őΉ��ł���)
                if ( !p )
                    p = response;
                q = strstr( p, "trackback.php?" );
                if ( !q )
                    q = strstr( p, "trackback.cgi?" );
                if ( !q )
                    q = strstr( p, "trackback.pl?" );
                if ( !q )
                    q = strstr( p, "trackback.asp?" );
                if ( !q )
                    q = strstr( p, "trackback.jsp?" );
                if ( !q )
                    q = strstr( p, "action.php?" );
                if ( !q )
                    q = strstr( p, "/tt_tb.cgi/" ); /* teeter totter */
                if ( !q )
                    q = strstr( p, "/tb.php/" );    /* XOOPS */

                if ( q ) {
                    p = q;
                    while ( (p > response) &&
                            (*p != '"')    &&
                            (*p != '\'')   &&
                            (*p != '>')    &&
                            (*p != '=')    &&
                            (*p != '\t')   &&
                            (*p != ' ')       )
                        p--;
                    while ( *q             &&
                            (*q != '"')    &&
                            (*q != '\'')   &&
                            (*q != '<')    &&
                            (*q != '\t')   &&
                            (*q != ' ')       )
                        q++;
                    if ( p && ((*p == '"')  ||
                               (*p == '\'') ||  
                               (*p == '>')  ||
                               (*p == '=')  ||
                               (*p == '\t') ||
                               (*p == ' ')    ) &&
                         q && ((*q == '"')  ||
                               (*q == '\'') ||
                               (*q == '<')  ||
                               (*q == '\t') ||
                               (*q == ' ')    )    ) {
                        p++;
                        strncpy( trackbackURL, p, q - p );
                        trackbackURL[p - q] = NUL;
                    }
                }
            }
        }
    }

    free( response );

    if ( trackbackURL[0] ) {
        char    *p, *q;

        /* �S�~�|�� (��Ƃ��� JUGEM �΍�)                                */
        /*  -- recvHTTP() ���́u�S�~�|���v�ő|�����؂�Ȃ������S�~�̑|�� */
        while ( ( ( p = strchr( trackbackURL, '\r' ) ) != NULL ) ||
                ( ( p = strchr( trackbackURL, '\n' ) ) != NULL )    ) {
            if ( *p == '\r' ) {
                q = strchr( p + 1, '\r' );
                if ( *(p - 1) == '\n' )
                    p--;
            }
            else
                q = strchr( p + 1, '\n' );
            if ( q ) {
                if ( ( *(q + 1) == '\n' ) || ( *(q + 1) == '\r' ) )
                    q++;
                strcpy( p, q + 1 );
            }
            else
                strcpy( p, p + 1 );
        }

        /* "&amp;" �� "&" �̒u�� */
        while ( ( p = strstr( trackbackURL, "&amp;" ) ) != NULL )
            strcpy( p + 1, p + 5 );

        /* �g���b�N�o�b�NURL�̐��K�� */
        if ( trackbackURL[0] == '/' ) {
            char    temp[MAX_URLLENGTH];

            if ( ((p = strchr( articleURL, '~' ))   != NULL) ||
                 ((p = strstr( articleURL, "%7E" )) != NULL) ||
                 ((p = strstr( articleURL, "%7e" )) != NULL)    ) {
                p = strchr( p + 1, '/' );
            }
            else {
                p = strstr( articleURL, "://" );
                if ( p )
                    p = strchr( p + 3, '/' );
            }

            /* ���΃p�X �� ��΃p�X */
            if ( p ) {
                strncpy( temp, articleURL, p - articleURL );
                temp[p - articleURL] = NUL;
                strcat( temp, trackbackURL );
                strcpy( trackbackURL, temp );
            }
        }
    }

    return ( trackbackURL );
}


/*
 * ���̎Q�Ƃ̃f�R�[�h
 */

char    *
decodeString( char *src )
{
    char    *p = src, *q;

    while ( ( q = strstr( p, "&lt;" ) ) != NULL ) {
        *q = '<';
        strcpy( q + 1, q + 4 );
    }
    while ( ( q = strstr( p, "&gt;" ) ) != NULL ) {
        *q = '>';
        strcpy( q + 1, q + 4 );
    }
    while ( ( q = strstr( p, "&quot;" ) ) != NULL ) {
        *q = '"';
        strcpy( q + 1, q + 6 );
    }
    while ( ( q = strstr( p, "&amp;" ) ) != NULL ) {
        *q = '&';
        strcpy( q + 1, q + 5 );
    }

    while ( ( q = strstr( p, "&dquot;" ) ) != NULL ) {
        *q = '"';
        strcpy( q + 1, q + 7 );
    }

    return ( src );
}


/*
 * ���̎Q�Ƃւ̃G���R�[�h
 */

char    *
encodeString( const char *src, char *dst )
{
    const char  *p = src;
    char        *q = dst;

    while ( *p ) {
        if ( *p == '<' ) {
            *q++ = '&';
            *q++ = 'l';
            *q++ = 't';
            *q++ = ';';
        }
        else if ( *p == '>' ) {
            *q++ = '&';
            *q++ = 'g';
            *q++ = 't';
            *q++ = ';';
        }
        else if ( *p == '"' ) {
            *q++ = '&';
            *q++ = 'q';
            *q++ = 'u';
            *q++ = 'o';
            *q++ = 't';
            *q++ = ';';
        }
        else if ( *p == '&' ) {
            *q++ = '&';
            *q++ = 'a';
            *q++ = 'm';
            *q++ = 'p';
            *q++ = ';';
        }
        else
            *q++ = *p;

        p++;
    }
    *q = NUL;

    return ( dst );
}


/* �w�蕶�����16�i�����񂩔ۂ� */
int
isHexString( const char *p )
{
    int ret = 1;

    while ( *p ) {
        if ( ((*p >= '0') && (*p <= '9')) ||
             ((*p >= 'a') && (*p <= 'f')) ||
             ((*p >= 'A') && (*p <= 'F'))    ) {
            p++;
            continue;
        }

        ret = 0;
        break;
    }

    return ( ret );
}

/* �w�蕶�����10�i�����񂩔ۂ� */
int
isDecString( const char *p )
{
    int ret = 1;

    while ( *p ) {
        if ( (*p >= '0') && (*p <= '9') ) {
            p++;
            continue;
        }

        ret = 0;
        break;
    }

    return ( ret );
}

/* ���O�ɎQ�Ƃ��� URL ��Ԃ� */
char    *
getCurrentLocation( char *url )
{
    if ( xmlrpc_p && url ) {
        if ( xmlrpc_p->webServer[0] && xmlrpc_p->webPage[0] )
            sprintf( url, "%s://%s%s",
                     xmlrpc_p->useSSL ? "https" : "http",
                     xmlrpc_p->webServer,
                     xmlrpc_p->webPage );
    }

    return ( url );
}

/* Windows �̌�����擾 (�Ⴆ�΁A���{���: 1041, �p��(USA)��: 1033) */
DWORD
getLanguageCode( void )
{
    return ( xmlrpc_p ? xmlrpc_p->languageCode : GetThreadLocale() );
}

/* ����������؂�ւ� */
void
setLanguageCode( DWORD languageCode )
{
    if ( xmlrpc_p )
        xmlrpc_p->languageCode = languageCode;
    SetThreadLocale( languageCode );
}


#if (WINVER >= 0x0500)
#ifdef  _MSC_VER
#include <time.h>

/* ���{���ԂȂ̂ɉĎ��ԃt���O�������Ă���ꍇ�́A�t���O�������I�ɂ��낷 */
void
resetDaylightSaving( void )
{
    time_t      t = time( NULL );
    struct tm   *tm = localtime( &t );

    if ( tm->tm_isdst == 1 ) {
        char    *p = _tzname[0];
        if ( !strcmp( p, "JST" ) ) {
            /* �Ȃ������{���Ԃł���ɂ��ւ�炸�A�Ď��ԂɂȂ��Ă���ꍇ */
            long l = _daylight;

            if ( l == 1 ) {
                // ���ϐ� TZ ��ݒ肵�Ă���ꍇ�́A(Visual Studio 2005 ��)
                // �uC �����^�C�� ���C�u�����́A�Ď��� (DST: Daylight Saving
                // Time) �v�Z�̎����ɂ��Ă͕č��̋K����O��Ƃ��Ă��܂��v��
                // �������ƂŁA����ɉĎ��Ԃɂ���Ă��܂��炵��
                // ���{���Ԃɂ�(���Ȃ��Ƃ������_�ł�)�Ď��Ԃ͂Ȃ��̂Ɂc�c
                _daylight = 0;
            }
        }
        // �Ƃ肠�����A���{���Ԃ̂ݍl���������A�{���́A���̉Ď��Ԗ��������E
        // �n���A�����J�ƉĎ��Ԃ̊J�n�E�I���������قȂ鍑�E�n��ɑ΂���z
        // �����K�v
        // �Ȃ��AVisual C++ 6 �̃����^�C���ł́ATZ=JST-9 �Ɛݒ肵�Ă���ꍇ
        // �ł��A���{���Ԃ��Ď��Ԃ���Ɣ��肳��Ă��܂��悤�Ȃ��Ƃ͂Ȃ��B��
        // ���܂ł� Visual C++ 2005 �̃����^�C���̖��ł���(Visual C++.NET
        // 2002/2003 �Ɋւ��Ă͖��m�F)
    }
}
#endif
#endif

#ifdef  USE_RURL
/* rurl.org �𗘗p���ĒZ�kURL�𐶐� */
char    *
makeRurl( const char *url )
{
    Thread static char  result[MAX_URLLENGTH];
    size_t              sz = MAX_CONTENT_SIZE;
    char                *response = (char *)malloc( sz );

    memset( result, 0x00, MAX_URLLENGTH );
    strncpy( result, url, MAX_URLLENGTH - 2 );
    if ( response ) {
        char    request[BUFSIZ];

        sprintf( request,
                 "url=%s&"
                 "apikey=%s",
                 encodeURL(url), xmlrpc_p->rurlAPIkey );
        setUpReceiveBuffer( response, sz );
        http_post( "http://rurl.org/api/",
                   "application/x-www-form-urlencoded",
                   request, response );
        if ( *response ) {
            /*
             *  ����
             *    <?xml version="1.0" encoding="UTF-8" ?> 
             *    <rurl>
             *      <urls>
             *        <url goesto="����URL">�Z�kURL</url> 
             *      </urls>
             *      <errors /> 
             *    </rurl>
             */
            char    *p = strstr( response, "<url goesto=\"" );
            if ( p ) {
                char    *q;

                p += 13;
                q = strchr( p, '>' );
                if ( q ) {
                    p = q + 1;
                    q = strchr( p, '<' );
                    if ( q ) {
                        strncpy( result, p, q - p );
                        result[q - p] = NUL;
                    }
                }
            }
        }

        free( response );
    }

    return ( result );
}
#endif  /* USE_RURL */


void    dputc( char c )
{
    // Visual Studio 2008 �� VC++ (VC9) �Ńr���h����ƁA�ȉ��̏�����
    // �����邱�Ƃ����� (VC6�AVC8 �ł͌��۔�������) �� �����̉𖾂�
    // �΍􂪕K�v
    fputc( c, xmlrpc_p->verboseFp ? xmlrpc_p->verboseFp : stderr );
}

void    dputs( const char *str )
{
    // Visual Studio 2008 �� VC++ (VC9) �Ńr���h����ƁA�ȉ��̏�����
    // �����邱�Ƃ����� (VC6�AVC8 �ł͌��۔�������) �� �����̉𖾂�
    // �΍􂪕K�v
    fputs( str, xmlrpc_p->verboseFp ? xmlrpc_p->verboseFp : stderr );
}

int     dprintf( const char *format, ... )
{
    Thread static char  buffer[MAX_CONTENT_SIZE * 16];
    size_t              sz = 0;
    va_list             args;

    buffer[0] = NUL;
    va_start( args, format );
    sz = vsprintf( buffer, format, args );
    va_end( args );

    dputs( buffer );

    return ( sz );
}
