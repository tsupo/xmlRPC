/** \mainpage xmlRPC API �T�|�[�g���C�u����
 *   ���X�A
 *   <a href="http://www.na.rim.or.jp/~tsupo/program/blogTool/mt_xmlRpc.html"
 *   title="Movable Type �Ŏg���� XML-RPC API">�E�F�u���O�֘A�� XML-RPC API</a>
 *   �����
 *   <a href="http://www.amazon.com/gp/browse.html/ref=smm_sn_aws/104-2882495-4914322?%5Fencoding=UTF8&amp;node=3435361"
 *   title="Amazon Web Services">Amazon Web Services</a>
 *   �𗘗p����A�v���P�[�V������e�Ղɍ쐬�ł���悤�ɂ���̂��ړI�ō쐬���J�n�������C�u�����ł��邽�߁A
 *   xmlRPC �Ƃ������O�ɂȂ��Ă���B
 *   ���݂́AAtom API �� SOAP ���݂� API ���T�|�[�g���Ă���B�܂��AXML-RPC API
 *   �� Atom API ���g���Ȃ� blog �T�[�r�X(�̂����ꕔ)�����ɁA�L���𓊍e����
 *   API ��p�ӂ��Ă���B
 *
 *   ���̂Ƃ���AWindows �����̃��C�u���������p�ӂ��Ă��Ȃ����AUNIX �� Linux
 *   ���ւ̈ڐA��e�Ղɂ��邽�߁A�\�Ȍ��� ANSI C �͈͓̔��ŋL�q���Ă���B
 *   ��ނ������AWin32 API �𒼐ڎg�킴��𓾂Ȃ������ӏ��Ɋւ��Ă�
 *   \#ifdef WIN32 / \#endif �ň͂ޓ��A���m�ɕ������Ă���B
 *
 *   �Ȃ��A�{���C�u�����́A�����R�[�h�̕ϊ���
 *   <a href="http://www.gnu.org/software/libiconv/" title="libiconv -GNU Project">GNU iconv (libiconv)</a>
 *   �𗘗p���Ă���B�{���C�u�����𗘗p����A�v���P�[�V���������s����ɂ�
 *   ���炩����
 *   <a href="http://www.gnu.org/software/libiconv/" title="libiconv -GNU Project">libiconv</a>
 *   ���C���X�g�[�����Ă����K�v������B
 *
 *   �܂��A�{���C�u�����A�� SSL �֘A�̏����̎��s�ɍۂ��A
 *   <a href="http://www.openssh.com/" title="OpenSSH">OpenSSH</a>
 *   �𗘗p���Ă���B�������A�{���C�u������
 *   <a href="http://www.openssh.com/" title="OpenSSH">OpenSSH</a>
 *   �� static library ���g�p���Ă���̂ŁA
 *   �{���C�u�����𗘗p����A�v���P�[�V�����̗��p�҂̕���
 *   <a href="http://www.openssh.com/" title="OpenSSH">OpenSSH</a>
 *   �̃��C�u������ʓr�C���X�g�[������K�v�͂Ȃ��B
 */

/*
 *  xmlRPC.h
 *
 *    XML-RPC API �T�|�[�g���C�u����
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2008, 2009 by H.Tsujimura
 *      written by H.Tsujimura
 *      mailto: tsupo@na.rim.or.jp
 *
 *      See also:
 *       http://www.na.rim.or.jp/~tsupo/program/blogTool/mt_xmlRpc.html
 *       http://www.na.rim.or.jp/~tsupo/program/blogTool/bloggerApiClient.html
 *       http://watcher.moe-nifty.com/memo/cat153983/index.html
 *
 * History:
 * $Log: /comm/xmlRPC/xmlRPC.h $
 * 
 * 4     09/05/29 7:09 tsupo
 * 1.267��
 * 
 * 246   09/05/28 18:36 Tsujimura543
 * getResultFromXML_s() ��ǉ�
 * 
 * 245   09/05/27 22:03 Tsujimura543
 * setSigInfo3() ��ǉ�
 * 
 * 244   09/05/27 19:28 Tsujimura543
 * setSigInfo() ����荞��
 * 
 * 3     09/05/27 1:18 tsupo
 * 1.266��
 * 
 * 243   09/05/26 20:55 Tsujimura543
 * APIURL_TUMBLR_ACOUNT ��ǉ�
 * 
 * 242   09/05/26 16:56 Tsujimura543
 * (1) tumblr �֘A�� #define ��ǉ�
 * (2) �R�R���O�A�R�R���O�t���[�̃G���h�|�C���g�� http ���� https �ɕύX
 * 
 * 2     09/05/16 2:39 tsupo
 * �u1.263�Ł�1.264�Łv�̕ύX����荞��
 * 
 * 241   09/05/15 21:56 Tsujimura543
 * hmac_sha256() ��ǉ�
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 240   09/03/30 22:54 Tsujimura543
 * getNonce() ��ǉ�
 * 
 * 239   09/03/30 19:48 Tsujimura543
 * OAuth �Ή�
 * 
 * 238   09/03/27 20:15 Tsujimura543
 * hmac_sha1() ��ǉ�
 * 
 * 237   09/03/20 17:45 Tsujimura543
 * �E�F�u���u���O�� XML-RPC API �o�R�ł̓��e�A����m�F�I��
 * 
 * 236   09/03/17 22:42 Tsujimura543
 * Windows Live Spaces (����уE�F�u���u���O) �����̏�����ǉ�
 * 
 * 235   09/03/16 19:17 Tsujimura543
 * getCategories() ��ǉ�
 * 
 * 234   09/03/16 14:04 Tsujimura543
 * �u�E�F�u���u���O (XML-RPC API)�v�֘A�A�ǉ�
 * 
 * 233   08/11/27 14:49 Tsujimura543
 * getOpenSSLversion() �� getIconvVersion() ��ǉ�
 * 
 * 232   08/11/14 12:10 Tsujimura543
 * MAX_COOKIE_NAME_LENGTH �� MAX_COOKIE_VALUE_LENGTH ��ǉ�
 * 
 * 231   08/11/14 11:50 Tsujimura543
 * USE_APIKEY_H �� define �ς݂̏ꍇ�̂݁AapiKey.h ���C���N���[�h
 * ����悤�ɂ���
 * 
 * 230   08/09/10 23:52 Tsujimura543
 * �\�[�X�𐮗� (�R�����g�A�E�g���Ă������R�[�h���폜)
 * 
 * 229   08/09/10 22:48 Tsujimura543
 * �G�L�T�C�g�u���O�֘A�̊֐��Q���폜 (xmlRPC.dll �O�ֈړ�)
 * 
 * 228   08/09/10 21:43 Tsujimura543
 * �G�R���O�֘A�̊֐��Q���폜 (xmlRPC.dll �O�ֈړ�)
 * 
 * 227   08/09/10 18:25 Tsujimura543
 * �y�V�u���O�֘A�̊֐��Q���폜 (xmlRPC.dll �O�ֈړ�)
 * 
 * 226   08/09/09 23:58 Tsujimura543
 * �s�v�ɂȂ����@�\���폜 (����5)
 * 
 * 225   08/09/09 22:51 Tsujimura543
 * �s�v�ɂȂ����@�\���폜 (����4)
 * 
 * 224   08/09/09 21:23 Tsujimura543
 * �s�v�ɂȂ����@�\���폜 (����3)
 * 
 * 223   08/09/09 18:24 Tsujimura543
 * �s�v�ɂȂ����@�\���폜 (����2)
 * 
 * 222   08/09/09 17:52 Tsujimura543
 * �s�v�ɂȂ����@�\���폜
 * 
 * 221   08/07/25 23:07 Tsujimura543
 * http_deleteBASIC() ��ǉ�
 * 
 * 220   08/05/15 23:23 Tsujimura543
 * �O�����J�p�֐��Ƃ��� getStatusCode() ��ǉ�
 * 
 * 219   08/02/15 22:58 Tsujimura543
 * AMAZON_STYPE_ITEMLOOKUP �̒l�� 2 ���� 4 �ɕύX
 * 
 * 218   08/02/15 22:32 Tsujimura543
 * getSalesRankingOnAmazon4() ��ǉ�
 * 
 * 217   08/02/13 23:24 Tsujimura543
 * searchItemsOnAmazon4() ��ǉ�
 * 
 * 216   08/02/07 22:25 Tsujimura543
 * copyright �\�����C�� (2008 ��ǉ�)
 * 
 * 215   08/01/29 17:28 Tsujimura543
 * bk1�u���[�_�[�֘A�̃R�[�h���폜
 * (���ł�bk1�u���[�_�[���x�͔p�~����Ă���)
 * 
 * 214   08/01/23 16:40 Tsujimura543
 * http_getW, http_postW, http_putW, http_deleteW ��ǉ�
 * 
 * 213   07/12/20 15:20 Tsujimura543
 * Visual Studio 2005 �ɂ��R���p�C���`�F�b�N���ʂ𔽉f
 * 
 * 212   07/12/19 20:55 Tsujimura543
 * startup ��ǉ� (for connectHTTP)
 * 
 * 211   07/12/06 5:36 Tsujimura543
 * #pragma message �s��ǉ�
 * 
 * 210   07/12/06 1:26 Tsujimura543
 * getSendBufferPointer() ��ǉ�
 * 
 * 209   07/12/06 1:16 Tsujimura543
 * _httpExecute() �Ńo�C�i���t�@�C���̑��M�ɑΉ����邽�߂̏C�������{
 * 
 * 208   07/11/30 1:41 Tsujimura543
 * (1) ���v���O!�A�h���R���u���O�AJugem �����ɓ��ʂɗp�ӂ��Ă����������폜
 * (2) �A���[�o�u���O�����̓��ʏ������폜 (Atom API �֘A������)
 * 
 * 207   07/10/29 16:41 Tsujimura543
 * BLOGKIND_YAPLOG_X ��ǉ�
 * 
 * 206   07/10/29 15:17 Tsujimura543
 * APIURL_YAPLOG_X ��ǉ�
 * 
 * 205   07/10/09 20:08 Tsujimura543
 * dputc() ��ǉ�
 * 
 * 204   07/10/09 19:32 Tsujimura543
 * dputs() �� dprintf() ��ǉ�
 * 
 * 203   07/09/28 19:18 Tsujimura543
 * XMLRPC_ERROR_CHANGED_PROXYINFO �𓱓�
 * 
 * 202   07/09/14 22:40 Tsujimura543
 * MAX_URLLENGTH_MAX �̒�`�� http.h ���� xmlRPC.h �ֈړ�
 * 
 * 201   07/09/10 19:05 Tsujimura543
 * �e��Web�T�[�r�X�֘A�Ŏg�p���Ă��Ȃ����̂��I�v�V������(�����A�p�~)
 * 
 * 200   07/09/07 20:52 Tsujimura543
 * http�ʐM�̃X���b�h�Ԕr������Ή�
 * 
 * 199   07/09/07 18:29 Tsujimura543
 * replaceEntityStrings() �ɑ�2������ǉ��BShift_JIS �ȊO�̏ꍇ�ɂ��Ή�
 * 
 * 198   07/09/07 17:03 Tsujimura543
 * replaceEntityStrings() ��ǉ�
 * 
 * 197   07/09/04 20:21 Tsujimura543
 * verboseFp ��ǉ����AsetVerbos() �̑�2�����Œl��ύX�ł���悤�ɂ���
 * 
 * 196   07/09/04 20:10 Tsujimura543
 * dumpFp ��ǉ����AsetDump() �̑�2�����Œl��ύX�ł���悤�ɂ���
 * 
 * 195   07/08/29 16:07 Tsujimura543
 * http_headBASIC() ��ǉ�
 * 
 * 194   07/08/24 18:38 Tsujimura543
 * setReferer() ��ǉ�
 * 
 * 193   07/08/10 23:18 Tsujimura543
 * http_getBASICEx() ��ǉ�
 * 
 * 192   07/05/22 0:28 Tsujimura543
 * ���[�U���ƃp�X���[�h���K�v�� proxy�T�[�o���g���Ă� https �ʐM��
 * �Ή� (����m�F�ς�)
 * 
 * 191   07/04/09 17:36 Tsujimura543
 * rurl.org API �֘A������ǉ�
 * 
 * 190   07/04/09 16:19 Tsujimura543
 * CONF_FUNC �� typedef ��ǉ�
 * 
 * 189   07/03/26 16:05 Tsujimura543
 * (1) http�֘A�֐��Q���o�C�i���t�@�C���̎�M�ɂ��Ή�������
 * (2) getBinSize() ��ǉ�����
 * 
 * 188   07/03/16 18:31 Tsujimura543
 * http_postBASIC() ��ǉ�
 * 
 * 187   07/03/13 19:18 Tsujimura543
 * setProxy() �� setProxyInfo() �ɖ��̕ύX
 * 
 * 186   07/03/13 19:16 Tsujimura543
 * setProxy() ��ǉ�
 * 
 * 185   07/03/10 5:05 Tsujimura543
 * confirmProxyInfo() �̈�����2�ǉ�
 * 
 * 184   07/03/10 4:58 Tsujimura543
 * ���[�U���ƃp�X���[�h�̎w�肪�K�v��proxy�T�[�o�ɂ��b��I�ɑΉ�
 * 
 * 183   07/03/09 21:13 Tsujimura543
 * isNecessaryToCheckProxyInfo() ��ǉ��A����т���ɔ����C�������{
 * 
 * 182   07/03/09 17:25 Tsujimura543
 * setConfirmProxyInfoFunc() ��ǉ�
 * 
 * 181   07/03/09 16:59 Tsujimura543
 * XMLRPC�\���̂� confirmProxyInfo ��ǉ�
 * 
 * 180   07/03/06 23:33 Tsujimura543
 * typo �C��
 * 
 * 179   07/03/05 17:15 Tsujimura543
 * setKeywordLink() �Ɉ�����ǉ� (�o�b�t�@�I�[�o�[�t���[�΍�)
 * 
 * 178   07/03/02 11:42 Tsujimura543
 * ������Web�T�[�r�XAPI�L�[ �Ή�
 * 
 * 177   07/03/01 19:06 Tsujimura543
 * XMLRPC �\���̂� webPage �����o�̗̈�T�C�Y�𑝂₷ (512 �� 4096)
 * 
 * 176   07/02/23 23:08 Tsujimura543
 * JUGEM �ƃh���R���u���O�� XML-RPC API �֘A�̒�`��ǉ�
 * 
 * 175   07/01/23 15:31 Tsujimura543
 * postRakuten() �̓���m�F�A�I�� (�V�����Ǘ���ʂւ̑Ή���ƁA����)
 * 
 * 174   07/01/23 15:29 Tsujimura543
 * (1) getCategoryListRakuten() ��ǉ�
 * (2) postRakuten() �̈�����ǉ����A�J�e�S�����w�肵�ē��e�ł���悤�ɂ���
 * 
 * 173   07/01/17 19:26 Tsujimura543
 * �y�V�f�x���b�p�[ID �Ή�
 * 
 * 172   07/01/17 17:34 Tsujimura543
 * copyright �\�����C�� (2007 ��ǉ�)
 * 
 * 171   07/01/17 16:54 Tsujimura543
 * Windows �́u����v�̎擾�A�ݒ�p�̊֐���ǉ�
 * 
 * 170   06/12/23 0:09 Tsujimura543
 * proxy �g�p���� https �ڑ��̂Ƃ��̃w�b�_������ http �łȂ���΂����Ȃ�
 * �T�[�o�Ahttps �łȂ���΂����Ȃ��T�[�o�A�ǂ���ł������T�[�o�̂ǂ̃p
 * �^�[���ɂ��Ή����邽�߁A�t���O��1�ǉ����A�Ή����� 
 * 
 * 169   06/10/19 22:58 Tsujimura543
 * ���܂Ń��C�u�����O�ɂ� ����J������ getProxyInfo() �����J���邱�Ƃɂ���
 * 
 * 168   06/10/19 18:44 Tsujimura543
 * sendUpdateExtendedPing() ��ǉ�
 * 
 * 167   06/10/13 17:18 Tsujimura543
 * �E�F�u���u���O�ɓ��e����Ƃ��A�e���v���[�gID���w��\�ɂ���
 * 
 * 166   06/10/11 17:45 Tsujimura543
 * XML_STATEMENT �̉��s�R�[�h�� \n ���� \r\n �ɕύX
 * 
 * 165   06/10/07 1:34 Tsujimura543
 * http(������M�҂�)�^�C���A�E�g���Ԃ�ݒ�ύX�ł���悤�ɂ���
 * 
 * 164   06/09/25 15:13 Tsujimura543
 * http_headEx() ��ǉ�
 * 
 * 163   06/09/15 18:10 Tsujimura543
 * BLOGKIND_FREPA, BLOGKIND_YAHOO360, BLOGKIND_OPENPNE,
 * BLOGKIND_SIMANITY ��ǉ�
 * 
 * 162   06/09/15 14:42 Tsujimura543
 * �o�����[�R�}�[�X�֘A�̒�`�A�L���̈�A�֐����폜�E�p�~
 * 
 * 161   06/09/14 15:46 Tsujimura543
 * MAX_BLOGIDLENGTH �̒l�� 48 �ɕύX (Vox �΍�)
 * 
 * 160   06/09/14 13:28 Tsujimura543
 * VOX �̃G���h�|�C���gURL��ǉ�
 * 
 * 159   06/09/11 17:21 Tsujimura543
 * getBlogIDsJugem(), getBlogIDsExciteBlog(), getBlogIDsYaplog(),
 * getBlogIDsDrecom(), getBlogIDsEchoo(), getBlogIDsRakuten()
 * ��ǉ�
 * 
 * 158   06/09/11 15:15 Tsujimura543
 * getBlogIDsWebry() ��ǉ�
 * 
 * 157   06/09/11 12:06 Tsujimura543
 * �R�����g��ǉ�
 * 
 * 156a  06/09/10 5:48 tsupo
 * resetDaylightSaving() �𓱓�����
 * (Visual Studio 2005 �� C++ �����^�C���g�p���ɁA���{���ԂȂ̂ɉĎ��Ԃ�
 * ���肳��Ă��܂����̑΍�)
 * 
 * 156   06/09/08 0:00 Tsujimura543
 * APIURL_BLOGGER_GDATA ��ǉ� (GData API �Ή�����)
 * 
 * 155   06/09/05 12:54 Tsujimura543
 * convUnicode() �̃v���g�^�C�v�錾��ǉ�
 * 
 * 154   06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 153a  06/09/03 7:40 tsupo
 * MAX_COOKIE_LEN ��ǉ�
 * 
 * 153   06/09/02 1:12 Tsujimura543
 * http�ʐM���s�����ǂ������`�F�b�N�ł���֐���ǉ�����
 * 
 * 152   06/07/24 19:24 Tsujimura543
 * _httpExecute() �̃o�b�t�@�I�[�o�[�����h�~�΍�֘A�̎d�g�݂��C��
 * 
 * 151   06/07/24 14:10 Tsujimura543
 * setUpReceiveBuffer() ��ǉ�
 * 
 * 150   06/06/23 18:12 Tsujimura543
 * MAX_DESCRIPTION_LEN �̒l�� 2048 ���� 4096 �ɑ��₷ (for Flog)
 * 
 * 149   06/03/14 20:52 Tsujimura543
 * deleteCocologFiles() �� deleteFile() ��ǉ�
 * 
 * 148   06/03/13 16:49 Tsujimura543
 * getCurrentLocation() ��ǉ�
 * 
 * 147   06/03/07 10:37 Tsujimura543
 * TRUE, FALSE �̂ǂ��炩����݂̂����̃w�b�_�t�@�C���Œ�`����Ă���
 * �ꍇ�ɑΏ�
 * 
 * 146   06/03/03 16:21 Tsujimura543
 * httpGetFileBASIC() �̈����̏�����ύX
 * 
 * 145   06/02/22 17:13 Tsujimura543
 * encodeURLex4() ��ǉ�
 * 
 * 144   06/02/22 16:48 Tsujimura543
 * encodeURLex3() ��ǉ�
 * 
 * 143   06/02/08 18:28 Tsujimura543
 * utf2sjisEx() ��ǉ�
 * 
 * 142   06/02/06 17:44 Tsujimura543
 * �u�}�C�v���t�B�[���v�֘A�̏������폜
 * 
 * 141   06/01/31 14:14 Tsujimura543
 * lcc win32 �ł��R���p�C�����ʂ�悤�ɂ���
 * 
 * 140   06/01/26 17:08 Tsujimura543
 * COOKIE_INFO �\���̂�ύX���A�l(������)�̊i�[�̈�T�C�Y�𑝗ʂ���
 * 
 * 139   06/01/26 13:22 Tsujimura543
 * �A���[�o�u���O�� Atom API  �G���h�|�C���g URL �̒�`��ǉ�
 * 
 * 138   06/01/25 19:20 Tsujimura543
 * excite Blog �̃��O�C�������A���e������ύX (������ǉ�)
 * 
 * 137   06/01/13 16:03 Tsujimura543
 * dwsEmail, dwsHID ��ǉ�
 * 
 * 136   06/01/10 15:12 Tsujimura543
 * userAgent / setUserAgent() ��ǉ�
 * 
 * 135   05/12/27 18:34 Tsujimura543
 * loginColors() �� postColors() ��ǉ�
 * 
 * 134   05/12/27 18:32 Tsujimura543
 * BLOGKIND_COLORS ��ǉ�
 * 
 * 133   05/12/21 18:46 Tsujimura543
 * (1) euc2sjis() �̋@��ˑ������Ή��� euc2sjisEx() ��ǉ�
 * (2) �@��ˑ��������@���ˑ��̕�����ɒu������ regular() ��ǉ� 
 * 
 * 132   05/12/14 13:41 Tsujimura543
 * MSN Spaces �֘A�̒�`��ǉ�
 * 
 * 131   05/12/14 13:37 Tsujimura543
 * Yahoo! Japan ����Web�T�[�r�XAPI�Ή�����
 * 
 * 130   05/12/09 16:13 Tsujimura543
 * RAKUTEN_GENRE_PHOTOBOOL �� RAKUTEN_GENRE_PHOTOBOOK �ɏC��
 * 
 * 129   05/11/30 14:29 Tsujimura543
 * MAX_DESCRIPTION_LEN �̒�`(�l)�𓝈ꂵ�AxmlRPC.h �Ɉړ�
 * 
 * 128   05/11/28 14:40 Tsujimura543
 * ATOMURL_COCOLOGFREE ��ǉ�
 * 
 * 127   05/11/28 14:17 Tsujimura543
 * goo Blog �� �R�R���O�t���[ �֘A�̒�`��ǉ�
 * 
 * 126   05/11/17 21:31 Tsujimura543
 * http �ɂ�鑗�M�\�ȓd���T�C�Y�̏�����������̋�������ǂ��܂ł�
 * �傫���ł���悤�ɂ��� (�����T�C�Y�͏]���̒l)
 * 
 * 125   05/11/17 19:55 Tsujimura543
 * AMAZON_MODE_SPORTS ��ǉ�
 * 
 * 124   05/11/17 15:25 Tsujimura543
 * loginCocologFiles() �� uploadCocologFiles() ��ǉ�
 * 
 * 123   05/11/07 11:22 Tsujimura543
 * APIURL_DTIBLOG ��ǉ�
 * 
 * 122   05/10/29 1:12 Tsujimura543
 * �u�b�N�}�[�N�o�^���Ɏg�p���鏈�����e�X��������(����m�F�ς�)
 * 
 * 121   05/10/28 21:00 Tsujimura543
 * encodeURLex2() �������I�ɓ������Ă݂�
 * 
 * 120   05/10/28 18:22 Tsujimura543
 * encodeURLex() ��ǉ�
 * 
 * 119   05/10/28 15:36 Tsujimura543
 * iso8859_1toUtf8() ��ǉ�
 * 
 * 118   05/10/18 18:46 Tsujimura543
 * (1) _httpExecute() �̈����ǉ��ɔ����e��ύX�����{
 * (2) http_getEx2() �� http_postEx2() ��ǉ�
 * 
 * 117   05/09/21 23:43 Tsujimura543
 * doxygen �Ή��R�����g�ǉ�
 * 
 * 116   05/09/03 0:38 Tsujimura543
 * doxygen ����������u���C���y�[�W�v�����̃R�����g(�b��)��`���ɒǉ�
 * 
 * 115   05/09/02 14:35 Tsujimura543
 * affiriate �� affiliate �ɏC�� (�Ԃ�ԈႢ)
 * 
 * 114   05/07/20 14:27 Tsujimura543
 * livedoor Blog ��2005�N7�����j���[�A����̐V�G���h�|�C���gURL�̒�`���
 * ��
 * 
 * 113   05/07/19 10:54 Tsujimura543
 * So-net blog �֘A�̒�`��ǉ�
 * 
 * 112   05/06/28 22:06 Tsujimura543
 * httpPutBASIC() �Ɉ��� mimeType ��ǉ�
 * 
 * 111   05/06/28 15:30 Tsujimura543
 * httpDeleteBASIC(), httpPutBASIC(), httpPostBASIC() ��ǉ�
 * 
 * 110   05/06/28 11:06 Tsujimura543
 * blogger.com �� Atom API �̃G���h�|�C���gURL �Ɋւ��� http �� https
 * �ɕύX
 * 
 * 109   05/05/31 22:51 Tsujimura543
 * httpPutEx() ��ǉ�
 * 
 * 108   05/05/30 20:29 Tsujimura543
 * BLOGKIND_HATENA ��ǉ�
 * 
 * 107   05/05/24 14:43 Tsujimura543
 * BASIC�F�؂ɑΉ�
 * 
 * 106   05/05/19 16:31 Tsujimura543
 * isbn2urls() �ɑ�2������ǉ�
 * 
 * 105   05/05/19 13:42 Tsujimura543
 * setSpaceId3OnValueCommerce() �� setSpaceId4OnValueCommerce() ��ǉ�
 * 
 * 104   05/05/19 13:22 Tsujimura543
 * XMLRPC �\���̂� ValueCommerce �֘A�̃����o�𑝌� (2��1��)
 * 
 * 103   05/05/18 21:45 Tsujimura543
 * getSalesRankingOnRakuten() �̎d�l��ύX (�\���̂Ɍ������ʂ��i�[����
 * �悤�ɂ���)
 * 
 * 102   05/05/18 16:36 Tsujimura543
 * searchEntryOnFeedback() ��ǉ�
 * 
 * 101   05/05/18 14:25 Tsujimura543
 * extractFeatureWordsOnBulkfeeds() �� extractAnalyseOnBulkfeeds() ��
 * ������2�ǉ�
 * 
 * 100   05/04/28 11:22 Tsujimura543
 * updateRssOnBulkfeeds() �̖߂�l�̌^�� int ���� BOOL �ɕύX
 * 
 * 99    05/04/21 15:50 Tsujimura543
 * loginRakuten() �Ɉ�����1�ǉ�
 * 
 * 98    05/04/20 19:59 Tsujimura543
 * loginRakuten() �� postRakuten() ��ǉ�
 * 
 * 97    05/04/18 15:53 Tsujimura543
 * getResultFromXML() �Ȃ� XML �֘A���[�e�B���e�B�֐��̃v���g�^�C�v
 * �錾��ǉ�
 * 
 * 96    05/04/14 14:40 Tsujimura543
 * FC2BLOG �Ɋւ��� #define ��ǉ�
 * 
 * 95    05/04/01 16:45 Tsujimura543
 * postAmeblo() �̈����̐�����ύX
 * 
 * 94    05/04/01 16:32 Tsujimura543
 * getCategoryListAmeblo() ��ǉ�
 * 
 * 93    05/03/28 14:37 Tsujimura543
 * loginFC2NETWORK(), postFC2NETWORK() ��ǉ�
 * 
 * 92    05/03/25 20:49 Tsujimura543
 * postJugem() �̈�����ǉ����A�J�e�S�������w��ł���悤�ɂ���
 * 
 * 91    05/03/25 20:46 Tsujimura543
 * postExciteBlog() �̈�����ǉ����A�J�e�S�������w��ł���悤�ɂ���
 * 
 * 90    05/03/25 20:05 Tsujimura543
 * postDrecom() �̈�����ǉ����A�J�e�S�������w��ł���悤�ɂ���
 * 
 * 89    05/03/25 19:49 Tsujimura543
 * postYaplog() �̈�����ǉ����A�J�e�S�������w��ł���悤�ɂ���
 * 
 * 88    05/03/25 17:12 Tsujimura543
 * getCategoryIDbyName() ��ǉ�
 * 
 * 87    05/03/25 17:03 Tsujimura543
 * isDecString() ��ǉ�
 * 
 * 86    05/03/25 16:48 Tsujimura543
 * isHexString() ��ǉ�
 * 
 * 85    05/03/24 14:41 Tsujimura543
 * getCategoryListWebry() ��ǉ�
 * 
 * 84    05/03/23 19:36 Tsujimura543
 * getCategoryListYaplog(), getCategoryListDrecom(),
 * getCategoryListEchoo(), getCategoryListExciteBlog(),
 * getCategoryListJugem() ��ǉ�
 * 
 * 83    05/03/22 15:00 Tsujimura543
 * isUsedProxy() ��ǉ�
 * 
 * 82    05/03/08 20:35 Tsujimura543
 * �uSweetBox Blog�v�ɋL�q�𓝈�
 * 
 * 81    05/03/08 16:56 Tsujimura543
 * SweetBox Blog �Ɋւ��� #define ��ǉ�
 * 
 * 80    05/03/07 23:11 Tsujimura543
 * NetLaputa �� 269g �Ɋւ��� #define ��ǉ�
 * 
 * 79    05/02/21 14:02 Tsujimura543
 * APIURL_AMEBLO ��ǉ� (NewsHandler �Ɠ��� API ���g���邱�Ƃ��m�F)
 * 
 * 78    05/02/18 14:34 Tsujimura543
 * �u���������v���uBlogPet�v�ֈڍs�����̂ɔ����C��
 * 
 * 77    05/01/26 13:25 Tsujimura543
 * getTrackbackURL() ��ǉ�
 * 
 * 76    05/01/26 11:09 Tsujimura543
 * BLOGKIND_RAKUTEN ��ǉ�
 * 
 * 75    05/01/18 21:54 Tsujimura543
 * �R�����g�̊ԈႢ���C��
 * 
 * 74    05/01/18 11:03 Tsujimura543
 * http_getEx(), http_postEx() ��ǉ�
 * 
 * 73    04/12/28 15:31 Tsujimura543
 * ���M�o�b�t�@�T�C�Y��3MB�Ƃ���
 * 
 * 72    04/11/29 18:30 Tsujimura543
 * AMAZON_MOD_* �� AMAZON_MODE_* �ɕύX
 * 
 * 71    04/11/29 13:25 Tsujimura543
 * �R���\�[�����͊֘A�֐���ǉ�
 * 
 * 70    04/11/26 20:54 Tsujimura543
 * �E�F�u���u���O�Ή�
 * 
 * 69    04/11/25 17:19 Tsujimura543
 * loginEchoo() �Ɉ�����ǉ�
 * 
 * 68    04/11/25 10:21 Tsujimura543
 * postEchoo() �̈�����ǉ� (�J�e�S��ID���w��ł���悤�ɂ���)
 * 
 * 67    04/11/24 23:44 Tsujimura543
 * �G�R���O�Ή���ƊJ�n
 * 
 * 66    04/11/24 15:16 Tsujimura543
 * (1) HTTP ���N�G�X�g�̎�v�ȃ��\�b�h�𒼐ڎ��s����API��ǉ�
 * (2) https://www2.ggn.net/cgi-bin/ssl �� GET �ł��邱�Ƃ��m�F
 * 
 * 65    04/11/19 20:38 Tsujimura543
 * SSL �֘A�̊֐���ǉ�
 * 
 * 64    04/11/19 14:51 Tsujimura543
 * SSL �Ή�����
 * 
 * 63    04/11/17 18:43 Tsujimura543
 * struct biddersSearchResult �� long �^�̃����o�� unsigned long �ɕύX
 * 
 * 62    04/11/17 16:58 Tsujimura543
 * BIDDERS_LITE �̃����o remainingTime �̌^�𐔒l(long)����
 * ������(char[])�ɕύX
 * 
 * 61    04/11/17 16:12 Tsujimura543
 * struct biddersSearchResult �Ɂu���i��URL�v��ǉ�
 * 
 * 60    04/11/17 15:57 Tsujimura543
 * bidders�֘A�֐���ǉ�
 * 
 * 59    04/11/16 14:08 Tsujimura543
 * APIURL_SEESAABLOG_SEC ��ǉ� (https �͖��Ή�)
 * 
 * 58    04/11/15 14:45 Tsujimura543
 * setSiteIdOnValueCommerce(), setSpaceId1OnValueCommerce(),
 * setSpaceId2OnValueCommerce() ��ǉ�
 * 
 * 57    04/11/15 13:56 Tsujimura543
 * searchPagesDirectlyOnGoogle() ��ǉ�
 * 
 * 56    04/11/15 11:09 Tsujimura543
 * getAffiriateLinkOnJbook() �� translateURL() ��ǉ�
 * 
 * 55    04/11/12 21:09 Tsujimura543
 * searchPagesOnGoogle() �̑�5������ύX
 * 
 * 54    04/11/12 11:11 Tsujimura543
 * unbase64() ��ǉ�
 * 
 * 53    04/11/12 10:48 Tsujimura543
 * Google APIs ��ǉ�
 * 
 * 52    04/11/11 11:26 Tsujimura543
 * searchSimilarityOnBulkfeeds() �̈�����ύX
 * 
 * 51    04/11/04 16:56 Tsujimura543
 * �L�k�K�T Web Service �Ή�����
 * 
 * 50    04/11/04 16:44 Tsujimura543
 * �A�}�]���̃x�X�g�Z���[�ꗗ�̎擾���ʂ��\���̂Ɋi�[���ĕԂ��悤�ɂ���
 * 
 * 49    04/11/04 16:05 Tsujimura543
 * getNewWhisperOnCousagi() ��ǉ�
 * 
 * 48    04/11/04 15:59 Tsujimura543
 * setSubscriptionIDOnAmazon() ��ǉ�
 * 
 * 47    04/11/04 15:53 Tsujimura543
 * Amazon E-Commerce Service 4.0 �Ή�����
 * 
 * 46    04/11/02 21:46 Tsujimura543
 * �A�}�]���̌����I�v�V�����Ɂu���ׂĂ̏��i�v��ǉ�
 * 
 * 45    04/11/02 20:47 Tsujimura543
 * �A�}�]���̐V�J�e�S���u��������&�z�r�[�v�̌����ɑΉ�
 * 
 * 44    04/11/01 21:01 Tsujimura543
 * �x�����x�� 4 �ł� warning ���\�Ȍ��茸�炵�Ă݂�
 * 
 * 43    04/11/01 19:54 Tsujimura543
 * �w�u���������v����̂������߁x�������I�Ɏ���
 * 
 * 42    04/10/27 15:02 Tsujimura543
 * searchEntryOnBulkfeeds() �̎d�l��ύX�B�L�[���[�h������������(�L���ꗗ)
 * ��Ԃ��悤�ɂ���
 * 
 * 41    04/10/15 15:20 Tsujimura543
 * NewsHandler �� blog ID, post ID �͋���32byte�ł��邽�߁A�̈�𑝂₵��
 * �Ή�����
 * 
 * 40    04/10/14 23:20 Tsujimura543
 * getEndpointURLbyAutoDiscovery() �� blogID ���擾����悤�ɕύX
 * 
 * 39    04/10/14 21:56 Tsujimura543
 * getEndpointURLbyAutoDiscovery() ��ǉ�
 * 
 * 38    04/10/14 15:19 Tsujimura543
 * MAX_BLOGIDLENGTH �̒l�� 32 �ɕύX
 * 
 * 37    04/10/14 14:21 Tsujimura543
 * ���e�҂�ID��blog�̃I�[�i�[��ID����ID�̏ꍇ�ɑΉ� (JUGEM�̏ꍇ)
 * 
 * 36    04/10/12 13:45 Tsujimura543
 * �����p�R�[�h�̃v���g�^�C�v�錾��ǉ�
 * 
 * 35    04/10/08 19:19 Tsujimura543
 * loginKinugasa, postKinugasa ��ǉ�
 * 
 * 34    04/10/08 15:21 Tsujimura543
 * xmlRPC.h ���� API �L�[ (����сA���̓���) �𕪗��Ɨ������ĐV����
 * �w�b�_�t�@�C����p�ӂ���
 * 
 * 33    04/10/08 12:21 Tsujimura543
 * cookie �֘A���C�� (�o�b�t�@�T�C�Y�g���A�Ȃ�)
 * 
 * 32    04/10/05 16:17 Tsujimura543
 * AWS Subscription ID ��ǉ�
 * 
 * 31    04/10/01 12:06 Tsujimura543
 * �L�k�K�TWebService �Ή�
 * 
 * 30    04/09/28 16:40 Tsujimura543
 * �h���R���u���O�Ή�
 * 
 * 29    04/09/21 22:53 Tsujimura543
 * �A���[�o�u���O�Ή�
 * 
 * 28    04/09/17 14:05 Tsujimura543
 * getCategoryIDwithName() �� exciteBlog.c �����o���A���ʊ֐�������
 * 
 * 27    04/09/16 16:13 Tsujimura543
 * getCategoryID() �� jugem.c, myprofile.c, yaplog.c ������o���A
 * ���ʊ֐�������
 * 
 * 26    04/09/07 10:38 Tsujimura543
 * loginMixi, postMixi ��ǉ�
 * 
 * 25    04/09/03 11:36 Tsujimura543
 * loginMyprofile() �ɑ�4������ǉ�
 * 
 * 24    04/09/02 15:46 Tsujimura543
 * cookie�֘A�֐��Q��V�K�쐬
 * 
 * 23    04/09/01 22:17 Tsujimura543
 * �}�C�v���t�B�[���֘A�֐����C��(�Ԃ�~�X)
 * 
 * 22    04/09/01 22:11 Tsujimura543
 * �}�C�v���t�B�[���Ή�
 * 
 * 21    04/08/31 12:10 Tsujimura543
 * �֐��̃v���g�^�C�v�錾�𐮗�
 * 
 * 20    04/08/30 14:48 Tsujimura543
 * MAX_POSTIDLENGTH, MAX_USERIDLEN ������ 80 �ɕύX
 * 
 * 19    04/08/30 14:26 Tsujimura543
 * getRecentPostTitlesFromRSS ��ǉ�
 * 
 * 18    04/08/27 16:11 Tsujimura543
 * ���v���O�Ή�
 * 
 * 17    04/08/26 22:20 Tsujimura543
 * excite�u���O�ɓ��e�ł��邱�Ƃ��m�F
 * 
 * 16    04/08/26 11:26 Tsujimura543
 * loginExciteBlog, postExciteBlog ��ǉ�
 * 
 * 15    04/08/25 16:57 Tsujimura543
 * loginJugem, postJugem ��ǉ�
 * 
 * 14    04/08/19 10:43 Tsujimura543
 * SUPPORT_FOR_WIN95 �� #define ������ԂŃR���p�C������� Windows 95
 * (ORS2�ȑO) �ł��������̂��ł���(�͂�)
 * 
 * 13    04/08/19 9:04 Tsujimura543
 * TypaPad Germany �֘A�̒�`��ǉ� (�ǉ��R�ꂵ�Ă���)
 * 
 * 12    04/08/17 10:26 Tsujimura543
 * getRecentPostTitlesOnBloggerAPI, getRecentPostTitlesOnMetaWeblog ��ǉ�
 * 
 * 11    04/08/13 15:03 Tsujimura543
 * Blogger.com �� Atom API �֘A�̒�`��ǉ�
 * 
 * 10    04/08/12 21:19 Tsujimura543
 * LOVELOG �֘A�̒�`��ǉ�
 * 
 * 9     04/07/16 17:23 Tsujimura543
 * livedoor Blog �� Atom API �֘A�̓���m�F����
 * 
 * 8     04/07/16 14:08 Tsujimura543
 * �������� API �֘A�𐮗�
 * 
 * 7     04/07/14 18:49 Tsujimura543
 * Movable Type API �֘A�̊֐��̎d�l������
 * 
 * 6     04/07/12 15:50 Tsujimura543
 * metaWeblog API �֘A�̊֐��̎d�l������
 * 
 * 5     04/07/09 20:24 Tsujimura543
 * blogger API �֘A�̊֐��̎d�l������
 * 
 * 3     04/07/07 15:46 Tsujimura543
 * �ublog���e�[�u���v��ǉ�
 * 
 * 2     04/07/07 11:44 Tsujimura543
 * RCS �ɂ��Ő��Ǘ����� VSS �ɂ��Ő��Ǘ��Ɉڍs
 */

#ifndef __XML_RPC_H__
#define __XML_RPC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef  UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#ifdef  WIN32
#ifdef  _MSC_VER
#pragma warning ( disable : 4115 )
#pragma warning ( disable : 4996 )
#endif
#include <io.h>
#ifdef  SUPPORT_FOR_WIN95
#ifdef  _MSC_VER
#if		_MSC_VER < 1400
#pragma message ("warning C4201 ���o�Ă��A�������Ă�������")
#endif
#endif
#include <winsock2.h>
#else
#include <winsock.h>
#endif
#ifdef  _MSC_VER
#pragma warning ( default : 4115 )
#endif
#endif

#ifndef NUL
#define NUL     '\0'
#endif

#ifndef WIN32
#ifndef BOOL
#define BOOL    int
#endif
#endif

#ifndef TRUE
#ifdef  FALSE
#undef  FALSE
#endif  /* FALSE */
#define TRUE    (1)
#define FALSE   !TRUE
#endif

/* �萔�A���̑� */
#define DEFAULT_HTTP_PORT       80
#define DEFAULT_HTTPS_PORT      443
#define DEFAULT_HTTP_TIMEOUT    60
#define MAX_BLOGIDLENGTH    48
#define MAX_BLOGNAMELENGTH  128
#define MAX_URLLENGTH       384
#define MAX_URLLENGTH_MAX   4096
#define MAX_POSTIDLENGTH    80
#define MAX_CATIDLENGTH     80
#define MAX_CATNAMELENGTH   128
#define MAX_DATELENGTH      40
#define MAX_BOOLEANLENGTH   16
#define MAX_LOGICALLINELEN  256
#define MAX_USERIDLEN       80
#define MAX_PASSWDLEN       16
#define MAX_KEYLENGTH       64
#define MAX_NAMELEN         32
#define MAX_SERVERNAME      512
#define MAX_WEBPAGENAME     4096
#define MAX_DESCRIPTION_LEN 4096
#define MAX_CONTENT_SIZE    65536
#define SND_BUFFER_SIZE     (1024 * 1024 * 3)
#define RCV_BUFFER_SIZE     65536
#define MAX_COOKIE_LEN      4096
#define MAX_OAUTH_HEADER_LEN    1024

#define MAX_PINGSITES       16          /* update ping ���M��ő�o�^�\�� */
#define MAX_PINGS           20 /* 1�񂠂���̃g���b�N�o�b�Nping���M��ő吔 */

#define MAX_CATEGORIES      16 /* metaWeblog.newPost �� Windows Live Spaces */
                               /* �����Ǝ��g�������Ŏw��\�ȍő�J�e�S����*/
                               /* [�{���A����l�͂Ȃ��Ǝv���邪�A�ȒP�̂� */
                               /*  �߂ɐݒ肵�Ă���] (�b��l)               */
                               /* ���̒l�́AAtom API �ł��g�p����           */

/* blog��� */
#define BLOGKIND_UNKNOWN        0x00    /* �s��                         */
#define BLOGKIND_MOVABLETYPE    0x01    /* Movable Type                 */
#define BLOGKIND_TYPEPAD        0x02    /* TypePad                      */
#define BLOGKIND_COCOLOG        0x03    /* �R�R���O                     */
#define BLOGKIND_BLOGZINE       0x04    /* BLOGZINE                     */
#define BLOGKIND_TYPEPADJAPAN   0x05    /* TypePad Japan                */
#define BLOGKIND_TYPEPADFRANCE  0x06    /* TypePad France               */
#define BLOGKIND_TYPEPADGERMANY 0x07    /* TypePad Germany (DE)         */
#define BLOGKIND_COCOLOGFREE    0x08    /* �R�R���O�t���[               */
#define BLOGKIND_BLOGGER        0x11    /* Blogger                      */
#define BLOGKIND_BLOGGERAPI     0x12    /* Blogger API �T�|�[�g blog    */
#define BLOGKIND_METAWEBLOG     0x21    /* MetaWeblog API �T�|�[�g blog */
#define BLOGKIND_NEWSHANDLER    0x22    /* News-Handler                 */
#define BLOGKIND_SEESAABLOG     0x23    /* Seesaa BLOG                  */
#define BLOGKIND_NETLAPUTA      0x24    /* NetLaputa blog               */
#define BLOGKIND_269G           0x25    /* 269G                         */
#define BLOGKIND_SWEETBOX       0x26    /* SweetBox Blog                */
#define BLOGKIND_FC2BLOG        0x27    /* FC2BLOG                      */
#define BLOGKIND_GOOBLOG        0x28    /* goo Blog                     */
#define BLOGKIND_MSNSPACES      0x29    /* Windows Live Spaces          */
#define BLOGKIND_JUGEM_X        0x2A    /* JUGEM (XML-RPC API)          */
#define BLOGKIND_DRECOMBLOG_X   0x2B    /* �h���R��BLOG (XML-RPC API)   */
#define BLOGKIND_YAPLOG_X       0x2C    /* yaplog (XML-RPC API)         */
#define BLOGKIND_WEBRY_X        0x2D    /* �E�F�u���u���O (XML-RPC API) */
#define BLOGKIND_MTAPI          0x31    /* MovableType API �T�|�[�gblog */
#define BLOGKIND_ATOMAPI        0x41    /* Atom API �T�|�[�g blog       */
#define BLOGKIND_LIVEDOOR       0x42    /* livedoor Blog                */
#define BLOGKIND_LOVELOG        0x43    /* LOVELOG                      */
#define BLOGKIND_SONET          0x44    /* So-net blog                  */
#define BLOGKIND_VOX            0x45    /* Vox                          */
#define BLOGKIND_HATENADIARY    0x46    /* �͂Ăȃ_�C�A���[             */

#define BLOGKIND_JUGEM_OLD      0xE1    /* JUGEM (xxx.jugem.cc)         */
#define BLOGKIND_JUGEM_NEW      0xE2    /* JUGEM (xxx.jugem.jp)         */
#define BLOGKIND_EXCITEBLOG     0xE3    /* excite�u���O                 */
#define BLOGKIND_YAPLOG         0xE4    /* yaplog                       */
#define BLOGKIND_MYPROFILE      0xE5    /* �}�C�v���t�B�[��             */
#define BLOGKIND_MIXI           0xE6    /* mixi                         */
#define BLOGKIND_KINUGASA       0xE7    /* �L�k�K�T                     */
#define BLOGKIND_AMEBLO         0xE8    /* �A���[�o�u���O               */
#define BLOGKIND_DRECOMBLOG     0xE9    /* �h���R��BLOG                 */
#define BLOGKIND_ECHOO          0xEA    /* �G�R���O                     */
#define BLOGKIND_WEBRY          0xEB    /* �E�F�u���u���O               */
#define BLOGKIND_RAKUTEN        0xEC    /* �y�V�L��                     */
#define BLOGKIND_FC2NETWORK     0xED    /* FC2NETWORK                   */
#define BLOGKIND_HATENA         0xEF    /* �͂Ăȃu�b�N�}�[�N/Fotolife  */
#define BLOGKIND_COLORS         0xF0    /* COLORS                       */
#define BLOGKIND_FREPA          0xF1    /* �t���p                       */
#define BLOGKIND_YAHOO360       0xF2    /* Yahoo! Days                  */
#define BLOGKIND_OPENPNE        0xF3    /* OpenPNE                      */
#define BLOGKIND_SIMANITY       0xF4    /* ���܂ɂĂ�                   */
#define BLOGKIND_TUMBLR         0xF5    /* tumblr (�� text)             */

/* XML-RPC API �G���h�|�C���g URL */
#define APIURL_MOVABLETYPE      "$/mt/mt-xmlrpc.cgi"
#define APIURL_TYPEPAD          "http://www.typepad.com/t/api"
#define APIURL_TYPEPADJAPAN     "http://www.typepad.jp/t/api"
#define APIURL_TYPEPADFRANCE    APIURL_TYPEPAD
#define APIURL_TYPEPADGERMANY   APIURL_TYPEPAD
#define APIURL_COCOLOG          "https://app.cocolog-nifty.com/t/api/"
#define APIURL_COCOLOGFREE      "https://app.f.cocolog-nifty.com/t/api/"
#define APIURL_BLOGZINE         "http://app.blog.ocn.ne.jp/t/api/"
#define APIURL_NEWSHANDLER      "http://blog.nettribe.org/xmlrpc.php"
#define APIURL_SEESAABLOG       "http://blog.seesaa.jp/rpc/"
#define APIURL_SEESAABLOG_SEC   "https://ssl.seesaa.jp/blog/rpc" /* https�� */
#define APIURL_NETLAPUTA        "http://blog.netlaputa.ne.jp/rpc/"
#define APIURL_269G             "http://269g.jp/rpc"
#define APIURL_BLOGGER          "http://www.blogger.com/api"
#define APIURL_AMEBLO           "http://ameblo.jp/xmlrpc.php"
#define APIURL_SWEETBOX         "http://www.sweetbox.ws/api/xmlrpc"
#define APIURL_FC2BLOG          "http://blog.fc2.com/xmlrpc.php"
#define APIURL_DTIBLOG          "http://blog.dtiblog.com/xmlrpc.php"
#define APIURL_GOOBLOG          "http://blog.goo.ne.jp/xmlrpc.php"
#define APIURL_MSNSPACES        "https://storage.msn.com/storageservice/MetaWeblog.rpc"
#define APIURL_JUGEM_X          "http://$.jugem.jp/admin/xmlrpc.php"
#define APIURL_DRECOMBLOG_X     "http://blog.drecom.jp/api/xmlrpc"
#define APIURL_YAPLOG_X         "http://www.yaplog.jp/xmlrpc"
#define APIURL_WEBRY_X          "https://bblog.sso.biglobe.ne.jp/ap/xmlrpc"

#define APIURL_COUSAGI          "http://www.yomiusa.net/api/api.cgi"
#define APIURL_HATENA           "http://d.hatena.ne.jp/xmlrpc"

/* Atom API �G���h�|�C���g */
/*
 *  The root endpoints for weblogs, photo albums, and TypeLists are
 *  as follows:
 *      Weblogs: http://www.typepad.com/t/atom/weblog
 *      Photo Albums: http://www.typepad.com/t/atom/gallery
 *      TypeLists: http://www.typepad.com/t/atom/lists
 *        (see also: http://sixapart.com/developers/atom/typepad/)
 */
#define ATOMURL_TYPEPAD         "http://www.typepad.com/t/atom/weblog"
#define ATOMURL_TYPEPADJAPAN    "http://www.typepad.jp/t/atom/weblog"
#define ATOMURL_TYPEPADFRANCE   ATOMURL_TYPEPAD
#define ATOMURL_TYPEPADGERMANY  ATOMURL_TYPEPAD
#define ATOMURL_COCOLOG         "https://app.cocolog-nifty.com/t/atom/weblog"
#define ATOMURL_COCOLOGFREE     "https://app.f.cocolog-nifty.com/t/atom/weblog"
#define ATOMURL_BLOGZINE        "http://app.blog.ocn.ne.jp/t/atom/weblog"
#define ATOMURL_LIVEDOOR        "http://blog.livedoor.com/atom"
#define ATOMURL_LIVEDOOR_200507 "http://cms.blog.livedoor.com/atom" /* 2005�N7���ȍ~ */
#define ATOMURL_LOVELOG         "http://blog.dion.ne.jp/atom"
#define ATOMURL_BLOGGER         "https://www.blogger.com/atom"
#define ATOMURL_SONET           "http://blog.so-net.ne.jp/_atom/blog"   /* �L���p */
#define ATOMURL_SONET_IMAGE     "http://blog.so-net.ne.jp/_atom/image"  /* �摜�p */
#define ATOMURL_AMEBLO          "http://ameblo.jp:80/servlet/_atom/blog"    /* �L���p */
#define ATOMURL_AMEBLO_IMAGE    "http://ameblo.jp:80/servlet/_atom/image"   /* �摜�p */
#define ATOMURL_VOX             "http://www.vox.com/atom"
#define ATOMURL_HATENADIARY     "http://d.hatena.ne.jp/{hatenaID}/atom/blog"

#define APIURL_BLOGGER_GDATA    "https://www.blogger.com/feeds"     /* GData API          */
#define APIURL_VOX_DEVELOPERS   "http://www.vox.com/services/api"   /* Vox developers API */

/* ���̑� �G���g���|�C���g */
#define APIURL_TUMBLR_WRITE     "http://www.tumblr.com/api/write"   /* tumblr ���e�p */
#define APIURL_TUMBLR_ACOUNT    "http://www.tumblr.com/api/authenticate"
                                                      /* tumblr �A�J�E���g���擾�p */

/* blog ���̂��܂��܂Ƃ�����` */
#define JUGEMTYPE_OLD   1   /* ���Ŏ��ォ��̖����T�[�r�X xxx.jugem.cc */
#define JUGEMTYPE_NEW   2   /* �����ňȍ~                 xxx.jugem.jp */

/* XML�錾 */
#define XML_STATEMENT   "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"

/* �����R�[�h */
#define CHARSET_UNKNOWN     0   /* �s��        */
#define CHARSET_SHIFTJIS    1   /* Shift_JIS   */
#define CHARSET_EUCJP       2   /* EUC-JP      */
#define CHARSET_ISO2022JP   3   /* ISO-2022-JP */
#define CHARSET_UTF8        4   /* UTF-8       */

typedef int (__cdecl *CONF_FUNC)( int            *useProxy,
                                  char           *proxyServer,
                                  unsigned short *proxyPort,
                                  char           *proxyUserName,
                                  char           *proxyPassword );

#ifdef  XMLRPC_EXPORTS
#ifdef  USE_APIKEY_H
#include "apiKey.h"
#else
#define BULKFEEDS_API_KEY       "--------------------------------"
#define AMAZON_SUBSCRIPTION_ID  "--------------------"
#define AMAZON_ASSOCIATE_ID     "-----------"
#define RAKUTEN_DEVELOPER_ID    "--------------------------------"
#define RAKUTEN_AFFILIATE_ID    "--------.--------"
#define RAKUTEN_AFFILIATE_ID2   "--------.--------.--------.--------"
#endif

/* �f�[�^��` */
typedef struct sockaddr_in  SOCKADDR_IN;
typedef unsigned short      ushort;

typedef struct  xmlRPCparameter {
    int         initialized;                /* �������ς݂��ۂ�             */
    SOCKADDR_IN saddrHTTPremote;            /* sockaddr structure for httpd */
    DWORD       scdHTTP;                    /* socket descriptor  for httpd */
    char        *sndHTTP;   /* ���M�p�o�b�t�@ (�����T�C�Y: SND_BUFFER_SIZE) */
    char        rcvHTTP[RCV_BUFFER_SIZE + 1];         /* ��M�p�o�b�t�@     */
    int         sndHTTPBufferSize;                    /* ���M�o�b�t�@�T�C�Y */
    int         rcvHTTPbufferSize;                    /* ��M�o�b�t�@�T�C�Y */
    int         sndHTTPmessageSize;                   /* ���M�d���T�C�Y     */
    int         rcvHTTPmessageSize;                   /* ��M�d���T�C�Y     */

    char        userName[MAX_PATH];         /* blog���e�p���[�U��           */
    char        password[MAX_PATH];         /* blog���e�p�p�X���[�h         */
    int         blogKind;                   /* blog���                     */
    BOOL        useSSL;                     /* https, http �̂ǂ�����g���� */
    BOOL        recoverySSL;                /* https ���̃��J�o�����[�h     */
    void        *workArea1;        /* ������Ɨp���i�[�̈�ւ̃|�C���^ #1 */
    void        *workArea2;        /* ������Ɨp���i�[�̈�ւ̃|�C���^ #2 */

    char        webServer[MAX_SERVERNAME];
                                /* XML-RPC ���N�G�X�g���M�� Web�T�[�o URL�� */
                                /* �����u�T�[�o���v����                     */
    char        webPage[MAX_WEBPAGENAME];
                                /* XML-RPC ���N�G�X�g���M�� Web�T�[�o URL�� */
                                /* �����u�t�@�C�����v����                   */

    char        proxyServer[MAX_SERVERNAME];        /* proxy �T�[�o URL     */
    ushort      proxyPort;                          /* proxy �|�[�g�ԍ�     */
    char        proxyUserName[MAX_NAMELEN + 1];     /* proxy �T�[�o���[�U�� */
    char        proxyPassword[MAX_NAMELEN + 1];   /* proxy �T�[�o�p�X���[�h */
    char        proxyCookie[MAX_COOKIE_LEN];      /* proxy �T�[�o�p�N�b�L�[ */

    BOOL        useProxy;                           /* proxy ���g�����ۂ�   */
    CONF_FUNC   confirmProxyInfo;
                            /* proxy���g�����ۂ��m�F����֐�(��ʓr�A�Ǝ��� */
                            /* �p�ӂ���ꍇ�Ɏg�p)                          */
    BOOL        needToCheckProxyInfo;/* proxy���̐ݒ肪�Ԉ���Ă���\�� */
    BOOL        verbose;      /* if TRUE, enabled verbose mode              */
    FILE        *verboseFp;   /* if not NULL, output to stream as verboseFp */
#if defined (_DEBUG) || defined (CHECK_DETAIL)
    BOOL        dump;           /* if TRUE, dump received data             */
    FILE        *dumpFp;        /* if not NULL, output to stream as dumpFp */
#endif
    BOOL        active;                                 /* http�ʐM�����ۂ� */
    CRITICAL_SECTION    critic;                               /* �r������p */
    DWORD       threadID;                     /* http�ʐM���̃X���b�h��ID   */
    int         timedoutTime;                 /* http �^�C���A�E�g���� (�b) */
    long        startup;                      /* �A�v���P�[�V�����N������   */
    ushort      statusCode;       /* ���O�� http �ʐM����(�X�e�[�^�X�R�[�h) */

#define MAX_LLLEN   MAX_LOGICALLINELEN
    char        dataDir[MAX_PATH];  /* �f�[�^�t�@�C���i�[��f�B���N�g����   */
    char        userAgent[MAX_LLLEN * 2];/* �����I�Ɏw�肷�� User-Agent �̒l*/
    char        referer[MAX_URLLENGTH_MAX];/* �����I�Ɏw�肷�� Referer �̒l */
    DWORD       languageCode;                                       /* ���� */
    size_t      binSize;                                /* ��M�f�[�^�T�C�Y */
    char        keywordList[MAX_PATH];
                              /* �͂Ăȃ_�C�A���[�L�[���[�h���X�g�t�@�C���� */
    char        amazonSubscriptionID[MAX_LLLEN];/* Amazon subscription ID   */
    char        amazonAssociateID[MAX_LLLEN];   /* Amazon associate ID      */
    char        bulkfeedsAPIkey[MAX_LLLEN];     /* Bulkfeeds API Key        */
    char        rakutenDeveloperID[MAX_LLLEN];  /* �y�V�f�x���b�p�[ID       */
    char        rakutenAffiliateID[MAX_LLLEN];  /* �y�V�A�t�B���G�C�gID(��) */
    char        rakutenAffiliateID2[MAX_LLLEN]; /* �y�V�A�t�B���G�C�gID(�V) */
#ifdef  USE_AUTHORIZATION_OAUTH
    char        oauth_header[MAX_OAUTH_HEADER_LEN];
#endif
#undef  MAX_LLLEN
}   XMLRPC, *XMLRPC_t;

extern XMLRPC_t xmlrpc_p;
#endif  /* XMLRPC_EXPORTS */

/* blog ���e�[�u�� */
typedef struct blogInfoTable {
    int     blogType;       /* blog���                       */
    int     charSet;        /* �����R�[�h                     */
    char    *xmlEndpoint;   /* XML-RPC API �G���h�|�C���g URL */
    char    *atomEndpoint;  /* Atom API �G���h�|�C���g URL    */
}   BLOGINFOTBL, *BLOGINFOTBL_t;

#ifdef  XMLRPC_EXPORTS
extern BLOGINFOTBL  blogInfoTbl[];
#endif  /* XMLRPC_EXPORTS */

/* content �\���� */
typedef struct content {
    char    title[MAX_LOGICALLINELEN];      /* �L���̌���           */
    char    description[MAX_CONTENT_SIZE];  /* �L���̖{��           */
    char    dateCreated[MAX_DATELENGTH];    /* �L�������e���ꂽ���� */

    /* �ȉ��AMovableType �g���� */
    int     mt_allow_comments;              /* �R�����g���󂯓���邩�ۂ� */
    int     mt_allow_pings;     /* �g���b�N�o�b�NPing���󂯓���邩�ۂ�   */
    char    mt_convert_breaks[MAX_BOOLEANLENGTH];
                                            /* �L���{���̉��s�̈�����     */
    char    mt_text_more[MAX_CONTENT_SIZE]; /* �ǋL                       */
    char    mt_excerpt[MAX_CONTENT_SIZE];   /* �T�v                       */
    char    mt_keywords[MAX_LOGICALLINELEN];/* �L�[���[�h                 */
    int     numOfTrackbacks;/* ���M���悤�Ƃ��Ă���g���b�N�o�b�N Ping �� */
    char    mt_tb_ping_urls[MAX_PINGS][MAX_LOGICALLINELEN];
                     /* ���M���悤�Ƃ��Ă���g���b�N�o�b�N Ping �� URL �Q */

    /* �ȉ��AWindows Live Spaces �g���� (�E�F�u���u���O�ł��g�p) */
    int     numOfCategories;                    /* �w�肷��J�e�S���̐�   */
    char    categories[MAX_CATEGORIES][MAX_CATNAMELENGTH];
                                                /* �J�e�S��(�����w��\) */
}   CONTENT, *CONTENT_t;


/* file �\���� */
typedef struct fileInfo {
    unsigned char   *bits;          /* base64 �ŕ��������ꂽ�t�@�C���̒��g */
    char            name[MAX_PATH]; /* �t�@�C����                          */
    char            type[MAX_LOGICALLINELEN];/* �t�@�C����� Content-type: */
}   FILEINF, *FILEINF_t;


/* category �\���� #1 */
typedef struct category {
    char    categoryId[MAX_CATIDLENGTH];    /* �J�e�S��ID         */
    int     isPrimary;                      /* ���J�e�S�����ۂ� */
}   CATEGORY, *CATEGORY_t;

/* category �\���� #2 */
typedef struct categoryInfo {
    char    categoryId[MAX_CATIDLENGTH];    /* �J�e�S��ID (�p����)        */
    char    categoryName[MAX_CATNAMELENGTH];/* �J�e�S���̖��O (������ OK) */
    int     isPrimary;                      /* ���J�e�S�����ۂ�         */
}   CATINF, *CATINF_t;


/* blog ���\���� */
typedef struct blogInfo {
    char    url[MAX_URLLENGTH];             /* blog �g�b�v�y�[�W URL */
    char    blogID[MAX_BLOGIDLENGTH + 1];   /* blog ID               */
    char    blogName[MAX_BLOGNAMELENGTH];   /* blog �̖��O           */
}   BLOGINF, *BLOGINF_t;

/* ���[�U���\���� */
typedef struct  userInfo    {
    char    userid[MAX_USERIDLEN];  /* ���[�UID             */
    char    firstname[MAX_NAMELEN]; /* ��                   */
    char    lastname[MAX_NAMELEN];  /* ��                   */
    char    nickname[MAX_NAMELEN];  /* �j�b�N�l�[��         */
    char    email[MAX_PATH];        /* email �A�h���X       */
    char    url[MAX_URLLENGTH];     /* �z�[���y�[�W�A�h���X */
}   USERINF, *USERINF_t;

/* content ���\���� #1 */
typedef struct  contentInfo {
    int     yy;                         /* ���e���� �N */
    int     mm;                         /* ���e���� �� */
    int     dd;                         /* ���e���� �� */
    int     HH;                         /* ���e���� �� */
    int     MM;                         /* ���e���� �� */
    int     SS;                         /* ���e���� �b */
    char    userid[MAX_USERIDLEN];      /* ���e�Җ�    */
    char    postid[MAX_POSTIDLENGTH];   /* �L��ID      */
    char    content[MAX_CONTENT_SIZE];  /* �L���{��    */
}   CONTENTINF, *CONTENTINF_t;


/* content ���\���� #2 */
typedef struct  contentInfoEx   {
    int     yy;                             /* ���e���� �N   */
    int     mm;                             /* ���e���� ��   */
    int     dd;                             /* ���e���� ��   */
    int     HH;                             /* ���e���� ��   */
    int     MM;                             /* ���e���� ��   */
    int     SS;                             /* ���e���� �b   */
    char    userid[MAX_USERIDLEN];          /* ���e�Җ�      */
    char    postid[MAX_POSTIDLENGTH];       /* �L��ID        */
    char    description[MAX_CONTENT_SIZE];  /* �L���{��      */
    char    title[MAX_LOGICALLINELEN];      /* �L���薼      */
    char    link[MAX_URLLENGTH];            /* �L��URL       */
    char    permaLink[MAX_URLLENGTH];       /* �L��permalink */

    /* �������牺�́AMovableType�Ǝ��̊g�� (�{���� metaWeblog API �ɂ͑��� */
    /* ���Ȃ�)                                                             */
    char    mt_excerpt[MAX_CONTENT_SIZE];   /* �T�v          */
    char    mt_text_more[MAX_CONTENT_SIZE]; /* �ǋL          */
    int     mt_allow_comments;              /* �R�����g���󂯕t���邩�ۂ� */
    int     mt_allow_pings;           /* �g���b�N�o�b�N���󂯕t���邩�ۂ� */
    char    mt_convert_breaks[MAX_BOOLEANLENGTH];        /* ���s�̈�����  */
    char    mt_keywords[MAX_LOGICALLINELEN];/* �L�[���[�h    */

    /* �ȉ��AWindows Live Spaces �g���� (�E�F�u���u���O�ł��g�p) */
    int     numOfCategories;                    /* �w�肷��J�e�S���̐�   */
    char    categories[MAX_CATEGORIES][MAX_CATNAMELENGTH];
                                                /* �J�e�S��(�����w��\) */
    BOOL    publish;                            /* ���J���               */
}   CONTENTINFEX, *CONTENTINFEX_t;
            /* �ʏ�A�u�L��URL�v�Ɓu�L��permalink�v�͓��� URL �ɂȂ� (��  */
            /* �������Ƃ��ɕʂ̂��̂ɂȂ�̂��s��)                        */

/* category ���\���� */
typedef struct categoryListInfo {
    char    categoryId[MAX_CATIDLENGTH];    /* �J�e�S��ID (�p����)        */
    char    categoryName[MAX_CATNAMELENGTH];/* �J�e�S���̖��O (������ OK) */
}   CATLISTINF, *CATLISTINF_t;

/* �L���ꗗ */
typedef struct postInfo {
    int     yy;                         /* ���e���� �N */
    int     mm;                         /* ���e���� �� */
    int     dd;                         /* ���e���� �� */
    int     HH;                         /* ���e���� �� */
    int     MM;                         /* ���e���� �� */
    int     SS;                         /* ���e���� �b */
    char    userid[MAX_USERIDLEN];      /* ���e�Җ�    */
    char    postid[MAX_POSTIDLENGTH];   /* �L��ID      */
    char    title[MAX_LOGICALLINELEN];  /* �L���薼    */
}   POSTINF, *POSTINF_t;

/* �t�B���^��� */
typedef struct filterInfo   {
    char    key[MAX_LOGICALLINELEN];    /* �L�[ */
    char    label[MAX_LOGICALLINELEN];  /* ���� */
}   FILTERINF, *FILTERINF_t;

/* �g���b�N�o�b�N���\���� */
typedef struct trackbackInfo    {
    char    pingTitle[MAX_LOGICALLINELEN];  /* �L���薼     */
    char    pingURL[MAX_URLLENGTH];         /* �L��URL      */
    char    pingIP[20]; /* trackback ping ���M�� IP�A�h���X */
}   TBINF, *TBINF_t;

/* �֐��v���g�^�C�v�錾 */
char    *jis2euc( const char *p );
char    *sjis2euc( const char *p );
char    *sjis2utf( const char *p );
char    *utf2euc( const char *p );
char    *euc2sjis( const char *p );
char    *utf2sjis( const char *p );
char    *iso8859_1toUtf8( const char *p );
char    *euc2sjisEx( const char *p );
char    *regular( char *s );
char    *replaceEntityStrings( const char *p, int charSet );
char    *encodeURL( const char *p );
char	*encodeURLi( const char *pp, BOOL lowercase );
char    *encodeURL2( const char *p ); /* &#xxx; �f�ʂ��� */
char	*encodeURLex( const char *pp );
char	*encodeURLex2(
                const char *p /* (I) UTF-8 ������ */
            );
char	*encodeURLex3(
                const char *p /* (I) EUC-JP ������ */
            );
char	*encodeURLex4(
                const char *p /* (I) Shift_JIS ������ */
            );
char    *decodeURL( const char *p );
char    *translateURL( const char *p );
char    *convUnicode( unsigned long code ); /* ���l�Q�Ƃ̃f�R�[�h */
int     strncmpi( const char *, const char *, size_t len );

char    *getNonce( const char *preNonce );
                            /* Atom PP �ȊO�ł��g���� Nonce �������� */

int initializeSocket( void );   /* �\�P�b�g�֘A������ */
int finalizeSocket( void );     /* �\�P�b�g�֘A��n�� */

#define MAX_NUMBER_OF_ACTIVITY_CHECK    20
#define PERIOD_OF_ACTIVITY_CHECK        1000
BOOL    isActive( void );               /* http�ʐM�����ۂ�       */
void    setActive( BOOL active );       /* for internal use only  */
void    setTimeoutTime( int timeout );  /* �^�C���A�E�g���Ԃ̕ύX */

#define RBUF_MAGIC1 0xBEAFCAFE
#define RBUF_MAGIC2 0xDEADBEEF

#define setUpReceiveBuffer( p, sz )     \
    memset( (p), 0x00, (sz) );          \
    *(size_t *)(p)       = RBUF_MAGIC1; \
    *((size_t *)(p) + 1) = (sz);        \
    *((size_t *)(p) + 2) = RBUF_MAGIC2;

#define getReceiveBufferSize( p, sz )   \
    if ( (*(size_t *)(p)       == RBUF_MAGIC1) &&   \
         (*((size_t *)(p) + 2) == RBUF_MAGIC2)    )  { \
        (sz) = *((size_t *)(p) + 1);    \
        if ( (sz) > 1 ) \
            (sz)--; \
    }   \
    else    \
        (sz) = 0;   \
    *(size_t *)(p)       = 0;   \
    *((size_t *)(p) + 1) = 0;   \
    *((size_t *)(p) + 2) = 0;

#define setUpSendBuffer( p, sz, newP )  \
    *(size_t *)(p)       = RBUF_MAGIC2; \
    *((size_t *)(p) + 1) = (sz);        \
    *((size_t *)(p) + 2) = RBUF_MAGIC1; \
    (newP) = (char *)((size_t *)(p) + 3);

#define getSendBufferSize( p, sz, newP )   \
    if ( (*(size_t *)(p)       == RBUF_MAGIC2) &&   \
         (*((size_t *)(p) + 2) == RBUF_MAGIC1)    )  { \
        (sz) = *((size_t *)(p) + 1);    \
        (newP) = (char *)((size_t *)(p) + 3);   \
    }   \
    else {  \
        (sz) = 0;   \
        (newP) = (p); \
    }

#define getSendBufferPointer( p, newP ) \
    (newP) = (char *)((size_t *)(p) + 3);


int
httpPost( const char *webServer, const char *webPage,
          const char *mimeType,
          const char *request,   char *response );
                                /* http POST ���\�b�h���s */
int
httpPostBASIC( const char *webServer, const char *webPage,
               const char *userName,  const char *password,
               const char *mimeType,
               const char *request,   char *response );
                                /* http POST ���\�b�h���s(BASIC�F�ؑΉ���) */

int
httpPostEx( char *request, char *response );
                /* http POST ���\�b�h���s (�����������o���Ď擾�@�\�t��) */

int
httpPostEx2( const char *webServer, const char *webPage,
             const char *request,   char *response,
             const char *wsse );
                                /* http POST ���\�b�h���s (Atom API �p) */

int
httpPostWithSession( const char *webServer, const char *webPage,
                     const char *mimeType,
                     const char *sndBody, char *rcvBody, char *cookie,
                     char *webServerRedirected, char *cookieRedirected );
                            /* http POST ���\�b�h���s (�Z�b�V�����p��) */

int
httpGet( const char *webServer, const char *webPage,
         char *rcvBody, FILE *output, int printHead,
         const char *wsse,
         char *p3p, char *cookie,
         char *webServerRedirected, char *cookieRedirected );
                                /* http GET ���\�b�h���s  */
int
httpGetBASIC( const char *webServer, const char *webPage,
              const char *userName,  const char *password,
              char *rcvBody, FILE *output, int printHead,
              const char *wsse,
              char *p3p, char *cookie,
              char *webServerRedirected, char *cookieRedirected );
                                /* http GET ���\�b�h���s(BASIC�F�ؑΉ���) */

int
httpGetEx( const char *webServer, const char *webPage,
           char *rcvBody, FILE *output, int printHead,
           const char *wsse );
                                /* http GET ���\�b�h���s (Atom API �p) */

int
httpGetFile( const char *uri, const char *filename,
             int printHead );
                                /* http GET �ɂ��t�@�C���̎擾 */
int
httpGetFileBASIC( const char *uri, const char *filename,
                  const char *userName, const char *password,
                  int printHead );
                        /* http GET �ɂ��t�@�C���̎擾(BASIC�F�ؑΉ���) */
int
httpGetBuffer( const char *uri,
               char *rcvBuf, int printHead );
                                /* http GET �ɂ�镶����̎擾 */
int
httpGetBufferBASIC( const char *uri,
                    const char *userName, const char *password,
                    char *rcvBuf, int printHead );
                        /* http GET �ɂ�镶����̎擾(BASIC�F�ؑΉ���) */

int
httpPutBASIC( const char *webServer, const char *webPage,
              const char *userName,  const char *password,
              const char *mimeType,
              const char *request,   char *response,
              const char *wsse );
                                /* http PUT ���\�b�h���s(BASIC�F�ؑΉ���) */
int
httpPutEx( const char *webServer, const char *webPage,
           const char *request,   char *response,
           const char *wsse );
                                /* http PUT ���\�b�h���s (Atom API �p) */

int
httpDeleteBASIC( const char *webServer, const char *webPage,
                 const char *userName,  const char *password,
                 char *rcvBody, FILE *output, int printHead,
                 const char *wsse );
                                /* http DELETE ���\�b�h���s(BASIC�F�ؑΉ���)*/
int
httpDeleteEx( const char *webServer, const char *webPage,
              char *rcvBody, FILE *output, int printHead,
              const char *wsse );
                                /* http DELETE ���\�b�h���s (Atom API �p) */

int
httpGetBufferWithSession( const char *uri,
                          char       *rcvBuf,
                          int        printHead,
                          const char *wsse,
                          char       *p3p,  /* P3P: Platform for Privacy */
                                            /*      Preferences          */
                          char       *cookie,
                          char       *webServerRedirected,
                          char       *cookieRedirected );
                            /* http GET �ɂ�镶����̎擾 (�Z�b�V�����p��) */

int openHTTPS( void );                              /* SSL �J�n       */
int closeHTTPS( void );                             /* SSL �I��       */
int sendHTTPS( const char *request, size_t size );  /* SSL �f�[�^���M */
int recvHTTPS( char *response, size_t size );       /* SSL �f�[�^��M */


char    *
http_get( const char *url, char *response );
char    *
http_getEx( const char *url, char *response, char *cookie );
char    *
http_getEx2( const char *url,
             char *response, char *cookie,
             char *webServerRedirected, char *cookieRedirected );

char    *
http_getBASIC( const char *url,
               const char *userName, const char *password,
               char *response );    /* http_get() �� BASIC�F�ؑΉ���   */
char    *
http_getBASICEx( const char *url,
                 const char *userName, const char *password,
                 char *response, char *cookie );
                                    /* http_getEx() �� BASIC�F�ؑΉ��� */

char    *
http_head( const char *url, char *response );

char    *
http_headEx( const char *url, char *response, char *cookie );

char    *
http_headBASIC( const char *url,
                const char *userName, const char *password,
                char *response );   /* http_head() �� BASIC�F�ؑΉ���  */

char    *
http_delete( const char *url, char *response );

char    *
http_post( const char *url, const char *mimeType, const char *request,
           char *response );
char    *
http_postEx( const char *url, const char *mimeType, const char *request,
             char *response, char *cookie );
char    *
http_postEx2( const char *url, const char *mimeType, const char *request,
              char *response, char *cookie,
              char *webServerRedirected, char *cookieRedirected );
char    *
http_postBASIC( const char *url,
                const char *userName, const char *password,
                const char *mimeType, const char *request,
                char *response );   /* http_post() �� BASIC�F�ؑΉ���  */

char    *
http_put( const char *url, const char *mimeType, const char *filename,
          char *response );

char    *
http_deleteBASIC( const char *url,
                  const char *userName, const char *password,
                  const char *mimeType, const char *request,
                  char *response );   /* http_delete() �� BASIC�F�ؑΉ��� */

// for Atom PP
char    *
http_getW( const char *url, const char *wsse,
           const char *userName, const char *password,
           char *response );

char    *
http_postW( const char *url, const char *wsse,
            const char *userName, const char *password,
            const char *request, char *response );

char    *
http_putW( const char *url, const char *wsse,
           const char *userName, const char *password,
           const char *request, char *response );

char    *
http_deleteW( const char *url, const char *wsse,
              const char *userName, const char *password,
              char *response );


#if defined(WIN32) && !defined(__LCC__)
#define sleep   Sleep
#endif

/* OpenSSL �Ő��擾 */
char    *
getOpenSSLversion( char *buf, size_t bufSize );

/* iconv �Ő��擾 */
char    *
getIconvVersion( char *buf, size_t bufSize );

/* �{ ���C�u���� �Œ񋟂��� API */
void    setVerbose( int verbose, FILE *fp );    /* verbose ���[�h�ؑ�       */
void    setDump( int dump, FILE *dumpFp );      /* dump ���[�h�ؑ�          */
void    setUseProxy( int useProcy );            /* proxy ���[�h�ؑ�         */
void    setUserAgent( const char *userAgent );  /* User-Agent �ݒ�ύX      */
void    setReferer( const char *referer );      /* Referer �ݒ�ύX         */
void    setOAuthHeader( const char *header );   /* for OAuth                */
void    setUserInfo( const char *userName, const char *password );
                                                /* ���[�U���ݒ�           */
void    setTargetURL( const char *targetURL );  /* webServer, webPage �ݒ�  */
void    setBlogKind( int blogKind );            /* blog ��ʐݒ�            */

void    setDataDir( const char *dirname );
                                /* �f�[�^�t�@�C���i�[��f�B���N�g�����ݒ�   */
void    setKeywordList( const char *filename );
                                /* �͂Ăȃ_�C�A���[�L�[���[�h�t�@�C�����ݒ� */

void
getProxyInfo(
    int            *useProxy,
    char           *proxyServer,
    unsigned short *proxyPort,
    char           *proxyUserName,
    char           *proxyPassword );    /* proxy ���擾 */

unsigned short
getStatusCode( void );      /* ���O�� http �ʐM����(�X�e�[�^�X�R�[�h)�̎擾 */


/***** weblogUpdates API *****/
/* update ping ���M
 *      weblogUpdates.ping
 *          ����: update ping (blog�X�V�ʒm) �𑗐M���܂�
 *          ����: String weblogname,
 *                String weblogURL
 *          �Ԃ�l: ��������� �����o�[ flerror �̒l�� 0 (false) �ł���\����
 *                  ���Ԃ�܂��B
 *                  ���s����� �����o�[ flerror �̒l�� 1 (true)  �ł���\����
 *                  ���Ԃ�܂��B
 *          �Q�l: http://www.xmlrpc.com/weblogsCom
 *
 *    sendUpdatePing
 *      ����:
 *          char *weblogName    (I) blog �̖��O (Shift_JIS)
 *          char *weblogURL     (I) blog �� URL
 *      �߂�l:
 *          TRUE    update ping �o�^����
 *          FALSE   update ping �o�^���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) weblogName �Ŏw�肷�� blog �̖��O�ɂ��ẮA���� UTF-8 ��
 *              ����\������
 *          (2) blog �� URL �� URL �G���R�[�h���ׂ��������܂܂��ꍇ�́A
 *              ���炩���� URL �G���R�[�h���Ă�������
 */
BOOL
sendUpdatePing( const char *weblogName,
                const char *weblogURL );

/* weblogUpdates.ping �̊g���� weblogUpdates.extendedPing                   */
/*   Google blog search �ō̗p                                              */
/*     �ڍׂ� http://www.google.co.jp/help/blogsearch/pinging_API.html �Q�� */
BOOL
sendUpdateExtendedPing( const char *weblogName, // (I) blog �̖��O [Shift_JIS]
                        const char *weblogURL,  // (I) blog �� URL
                        const char *targetURL,  // (I) ping �Ώۂ� URL
                        const char *feedURL );  // (I) RSS/Atom �t�B�[�h�� URL

/*****  blogger API *****/
/* �V�K�L���̓��e
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
 *
 *    newPost
 *      ����:
 *          char *blogID        (I) blog ID
 *          char *userName      (I) ���[�U��
 *          char *password      (I) �p�X���[�h
 *          char *content       (I) �L�����e [UTF-8]
 *          BOOL publish        (I) ���e��� (FALSE: ������ / TRUE: ���J)
 *          char *postID        (O) ���e��̋L��ID
 *      �߂�l:
 *          TRUE    ���e����
 *          FALSE   ���e���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) �L�����e�̃T�C�Y�� SND_BUFFER_SIZE �̒l (���m�ɂ� 
 *              SND_BUFFER_SIZE ����uhttp �w�b�_�̃T�C�Y���v���������l)  ��
 *              �����Ȃ����ƁB�T�[�o�ɂ���ẮA���܂�傫�ȋL�����󂯕t����
 *              ���Ƃ��ł��Ȃ����Ƃ��\�z�����̂ŁA�T��64KB�����ł��邱�Ƃ�
 *              �]�܂���
 *          (3) �L�����e �� URL �G���R�[�h���ׂ��������܂܂��ꍇ�́A�{�֐�
 *              ���� URL �G���R�[�h���s�Ȃ��̂ŁA���炩���� URL �G���R�[�h��
 *              �Ă����K�v�͂Ȃ��B�Ȃ��AURL �G���R�[�h���s�Ȃ������ʁA�L����
 *              �e�̃T�C�Y�� SND_BUFFER_SIZE ���傫���Ȃ��Ă��܂����ꍇ�́A
 *              ���e�Ɏ��s����
 *          (4) �L���̓��e�ɐ��������ꍇ�ApostID  �̎w������̈�ɋL��ID (��
 *              ����) ���i�[����
 *          (5) �u�������v�̊T�O�̂Ȃ� blog �c�[���ɑ΂��ẮApublish �̒l��
 *              �Ӗ��������Ȃ�(��Ɂu���J�v��Ԃł̓��e�ƂȂ�)
 */

BOOL
newPost( const char *blogID,
         const char *userName,
         const char *password,
         const char *content,
         BOOL       publish,
         char       *postID );


/* �����L���̏㏑�����e
 *      blogger.editPost
 *          ����: ���ɂ���L���̏���ҏW���܂��D
 *          ����: String  appkey,
 *                String  postid,
 *                String  username,
 *                String  password,
 *                String  content,
 *                boolean publish
 *          �Ԃ�l: ��������� true ���C���s����� fault ���Ԃ�܂��D
 *
 *    editPost
 *      ����:
 *          char *postID        (I) �L��ID
 *          char *userName      (I) ���[�U��
 *          char *password      (I) �p�X���[�h
 *          char *content       (I) �L�����e [UTF-8]
 *          BOOL publish        (I) ���e��� (FALSE: ������ / TRUE: ���J)
 *      �߂�l:
 *          TRUE    �㏑�����e����
 *          FALSE   �㏑�����e���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) �L�����e�̃T�C�Y�� SND_BUFFER_SIZE �̒l (���m�ɂ� 
 *              SND_BUFFER_SIZE ����uhttp �w�b�_�̃T�C�Y���v���������l)  ��
 *              �����Ȃ����ƁB�T�[�o�ɂ���ẮA���܂�傫�ȋL�����󂯕t����
 *              ���Ƃ��ł��Ȃ����Ƃ��\�z�����̂ŁA�T��64KB�����ł��邱�Ƃ�
 *              �]�܂���
 *          (3) �L�����e �� URL �G���R�[�h���ׂ��������܂܂��ꍇ�́A�{�֐�
 *              ���� URL �G���R�[�h���s�Ȃ��̂ŁA���炩���� URL �G���R�[�h��
 *              �Ă����K�v�͂Ȃ��B�Ȃ��AURL �G���R�[�h���s�Ȃ������ʁA�L����
 *              �e�̃T�C�Y�� SND_BUFFER_SIZE ���傫���Ȃ��Ă��܂����ꍇ�́A
 *              ���e�Ɏ��s����
 *          (4) �u�������v�̊T�O�̂Ȃ� blog �c�[���ɑ΂��ẮApublish �̒l��
 *              �Ӗ��������Ȃ�(��Ɂu���J�v��Ԃł̓��e�ƂȂ�)�B�܂��A���ł�
 *              �u���J�v��Ԃœ��e�����L����ҏW����ꍇ�́Ablog �c�[���ɂ��
 *              �Ă͉������ł̓��e���w�����Ă��u���J�v��Ԃ̂܂܂ƂȂ邱�Ƃ�
 *              ����
 *          (5) �L���̒��g��S���ύX���Ă��Ȃ��ꍇ�ł��A�{�֐��ɂ��u���J�v
 *              ���w�肷��ƁArebuild �����s�����(���s����Ȃ� blog �c�[��
 *              ������)
 */

BOOL
editPost( const char *postID,
          const char *userName,
          const char *password,
          const char *content,
          BOOL       publish );


/* �����L���̍폜
 *      blogger.deletePost
 *          ����: �L�����폜���܂��D
 *          ����: String  appkey,
 *                String  postid,
 *                String  username,
 *                String  password,
 *                boolean publish
 *          �Ԃ�l: ��������� true�C���s����� fault ���Ԃ�܂��D
 *
 *    deletePost
 *      ����:
 *          char *postID        (I) �L��ID
 *          char *userName      (I) ���[�U��
 *          char *password      (I) �p�X���[�h
 *          BOOL publish        (I) ���e��� (FALSE: ������ / TRUE: ���J)
 *      �߂�l:
 *          TRUE    �폜����
 *          FALSE   �폜���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) publish �̒l�͖��������
 */

BOOL
deletePost( const char *postID,
            const char *userName,
            const char *password,
            BOOL       publish );


/* �w�茏�����̍ŐV�L���̎擾
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
 *
 *    getRecentPosts
 *      ����:
 *          char       *blogID        (I) blog ID
 *          char       *userName      (I) ���[�U��
 *          char       *password      (I) �p�X���[�h
 *          int        *numOfEntries  (I) �擾����L�����
 *                                    (O) ���ۂɎ擾�����L�����
 *          CONTENTINF *contentInfo   (O) �擾�����L�����
 *      �߂�l:
 *          0       �L�������݂��Ȃ��A�擾���s�A���M���s�A���̑��̃G���[����
 *          1 �ȏ�  �擾�ɐ��������L�����̐�
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) *numOfEntries �Ŏw�肵�����̕������A�ŐV�̋L������ߋ��̋L��
 *              �֑k������ɋL�������擾����
 *          (3) ���ۂɎ擾�ɐ��������L�����̐��� *numOfEntries �ɐݒ肷��
 */

int
getRecentPosts( const char *blogID,
                const char *userName,
                const char *password,
                int        *numOfEntries,
                CONTENTINF *contentInfo );


/* blog ���̎擾
 *     blogger.getUsersBlogs 
 *          ����: �����肳�񂪓��e�ł��� weblog �̌Q���Ԃ��܂��D
 *          ����: String appkey,
 *                String username,
 *                String password
 *          �Ԃ�l: ��������ƁC�\���̂̔z�񂪕Ԃ��Ă��܂��D 
 *                 �\���̂ɂ́C
 *                     String url,
 *                     String blogid,
 *                     String blogName
 *                 ���܂܂�܂��D 
 *                 ���s����ƁCfault ���Ԃ�܂��D
 *
 *    getUsersBlogs
 *      ����:
 *          char *userName  (I) ���[�U��
 *          char *password  (I) �p�X���[�h
 *          char *response  (O) �擾���� blog ��� [XML]
 *      �߂�l:
 *          TRUE    �擾����
 *          FALSE   �擾���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) response �̎����̈�͖{�֐��̌Ăяo�����ł��炩���ߊm�ۂ��Ă�
 *              ������
 *          (3) response �̎����̈�ɂ�  blogger.getUsersBlogs �ɑ΂���T�[�o
 *              ����̉������� (XML) �����̂܂܊i�[�����BXML �ł͂Ȃ��Ablog
 *              ��񂪗~�����ꍇ�́A�{�֐��𒼐ڌĂяo������ɖ{�֐��̃��b�p
 *              getBlogID() �܂��� getBlogIDs() ���Ăяo�����ƁB
 *              getBlogID() �� XML ���ɍŏ��ɏo������ blog �� blog ID �݂̂�
 *              ���o���AgetBlogIDs() �� XML ���Ɋ܂܂��S blog �̏��𔲂��o
 *              ��
 */

BOOL
getUsersBlogs( const char *userName,
               const char *password,
               char       *response );


/* ���[�U���̎擾
 *     blogger.getUserInfo 
 *          ����: �����肳��̏���Ԃ��܂��D
 *          ����: String appkey,
 *                String username,
 *                String password
 *          �Ԃ�l: ��������ƁC�\���̂̔z�񂪕Ԃ��Ă��܂��D 
 *                  �\���̂ɂ́C
 *                      String userid,
 *                      String firstname,
 *                      String lastname,
 *                      String nickname,
 *                      String email,
 *                      String url
 *                  ���܂܂�܂��D 
 *                  ���s����ƁCfault ���Ԃ�܂��D
 *                      ����: firstname �́CMovable Type �̃��[�U���̂����C��
 *                            ���̃X�y�[�X�̂Ƃ���܂ł̂��̂ł��D 
 *                            lastname �́C�ŏ��̃X�y�[�X�ȍ~�̂��̂ł��D
 *    getUserInfo
 *      ����:
 *          char    *userName      (I) ���[�U��
 *          char    *password      (I) �p�X���[�h
 *          int     numberOfUsers  (I) �擾���郆�[�U���̐� 
 *                                 (O) ���ۂɎ擾�������[�U���̐�
 *          USERINF *userInfo      (O) �擾�������[�U���
 *      �߂�l:
 *          0       �擾���s�A���M���s�A���̑��̃G���[����
 *          1 �ȏ�  �擾�ɐ����������[�U���̐� (== ���[�U��)
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 */

int
getUserInfo( const char *userName,
             const char *password,
             int        *numberOfUsers,
             USERINF    *userInfo );


/*****  metaWeblog API  *****/
/* �V�K�L���̓��e
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
 *                  ISO.8601 dateCreated, �L�������e���ꂽ����
 *                  String[] categories,  (�ȗ���) [Windows Live Spaces �p��
 *                                        ���āA�V���ɒǉ����ꂽ�p�����[�^�B
 *                                        Movable Type �ł͂��̈����ɂ͑Ή�
 *                                        ���Ă��Ȃ�]
 *              ����ɉ����āCMovable Type �ł͎���7�̍��ڂɒl�����ēn��
 *              ���Ƃ��ł��܂�: 
 *                  int      mt_allow_comments, allow_comments
 *                                              ���ڂւ̒l; (�R�����g����
 *                                              ����邩�ۂ�)
 *                  int      mt_allow_pings, allow_pings
 *                                              ���ڂւ̒l; (�g���b�N�o�b�N
 *                                              Ping���󂯓���邩�ۂ�)
 *                  String   mt_convert_breaks, convert_breaks
 *                                              ���ڂ̒l; (�L���{���̉��s��
 *                                              ������)
 *                  String   mt_text_more,      �ǋL�̒l; 
 *                  String   mt_excerpt,        �T�v�̒l;
 *                  String   mt_keywords,       �L�[���[�h�̒l;
 *                  array    mt_tb_ping_urls,   ���̋L���ɑ΂���g���b�N�o�b
 *                                              �N Ping �� URL �̌Q��;
 *              �ł��D 
 *              dateCreated ���g���Ȃ�CISO.8601 �`���łȂ��Ƃ����܂���D
 *              (�ȗ������ꍇ�͌��ݎ������w�肵�����̂Ƃ݂Ȃ����)
 *      �Ԃ�l: ��������ƁCString postid ���V�����L���� ID �l�Ƃ��ĕԂ��Ă�
 *              �܂��D
 *              ���s����ƁCfault �ł��D
 *
 *    newPostEx
 *      ����:
 *          char    *blogID    (I) blog ID
 *          char    *userName  (I) ���[�U��
 *          char    *password  (I) �p�X���[�h
 *          CONTENT *content   (I) �L�����
 *          BOOL    publish    (I) ���e��� (FALSE: ������ / TRUE: ���J)
 *          char    *postID    (O) ���e��̋L��ID
 *      �߂�l:
 *          TRUE    ���e����
 *          FALSE   ���e���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) �L�����e(content->description, content->mt_text_more,
 *              content->mt_excerpt �̍��v)�̃T�C�Y�� SND_BUFFER_SIZE �̒l
 *              (���m�ɂ� SND_BUFFER_SIZE ����uhttp �w�b�_�̃T�C�Y���v������
 *              ���l)�𒴂��Ȃ����ƁB�T�[�o�ɂ���ẮA���܂�傫�ȋL������
 *              �t���邱�Ƃ��ł��Ȃ����Ƃ��\�z�����̂ŁA�T�� 64KB�����ł���
 *              ���Ƃ��]�܂���
 *          (3) �L�����e �� URL �G���R�[�h���ׂ��������܂܂��ꍇ�́A�{�֐�
 *              ���� URL �G���R�[�h���s�Ȃ��̂ŁA���炩���� URL �G���R�[�h��
 *              �Ă����K�v�͂Ȃ��B�Ȃ��AURL �G���R�[�h���s�Ȃ������ʁA�L����
 *              �e�̃T�C�Y�� SND_BUFFER_SIZE ���傫���Ȃ��Ă��܂����ꍇ�́A
 *              ���e�Ɏ��s����
 *          (4) �L���̓��e�ɐ��������ꍇ�ApostID  �̎w������̈�ɋL��ID (��
 *              ����) ���i�[����
 *          (5) �u�������v�̊T�O�̂Ȃ� blog �c�[���ɑ΂��ẮApublish �̒l��
 *              �Ӗ��������Ȃ�(��Ɂu���J�v��Ԃł̓��e�ƂȂ�)
 */

BOOL
newPostEx( const char    *blogID,
           const char    *userName,
           const char    *password,
           const CONTENT *content,
           BOOL          publish,
           char          *postID );


/* �����L���̏㏑�����e
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
 *              ����ɉ����āCMovable Type �ł͎���7�̍��ڂɒl�����ēn��
 *              ���Ƃ��ł��܂��D
 *                  int      mt_allow_comments, allow_comments
 *                                              ���ڂւ̒l; (�R�����g����
 *                                              ����邩�ۂ�)
 *                  int      mt_allow_pings, allow_pings
 *                                              ���ڂւ̒l; (�g���b�N�o�b�N
 *                                              Ping���󂯓���邩�ۂ�)
 *                  String   mt_convert_breaks, convert_breaks
 *                                              ���ڂ̒l; (�L���{���̉��s�̈�
 *                                              ����)
 *                  String   mt_text_more,      �ǋL�̒l; 
 *                  String   mt_excerpt,        �T�v�̒l;
 *                  String   mt_keywords,       �L�[���[�h�̒l;
 *                  array    mt_tb_ping_urls,   ���̋L���ɑ΂���g���b�N�o�b�N
 *                                              Ping �� URL �̌Q��;
 *             �ł��DdateCreated ���g���Ȃ�CISO.8601 �`���łȂ��Ƃ����܂���D
 *      �Ԃ�l: ��������� true ���C���s����� fault ���Ԃ�܂��D
 *
 *    editPostEx
 *      ����:
 *          char    *postID    (I) �L��ID
 *          char    *userName  (I) ���[�U��
 *          char    *password  (I) �p�X���[�h
 *          CONTENT *content   (I) �L�����
 *          BOOL    publish    (I) ���e��� (FALSE: ������ / TRUE: ���J)
 *      �߂�l:
 *          TRUE    ���e����
 *          FALSE   ���e���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) �L�����e(content->description, content->mt_text_more,
 *              content->mt_excerpt �̍��v)�̃T�C�Y�� SND_BUFFER_SIZE �̒l
 *              (���m�ɂ� SND_BUFFER_SIZE ����uhttp �w�b�_�̃T�C�Y���v������
 *              ���l)�𒴂��Ȃ����ƁB�T�[�o�ɂ���ẮA���܂�傫�ȋL������
 *              �t���邱�Ƃ��ł��Ȃ����Ƃ��\�z�����̂ŁA�T�� 64KB�����ł���
 *              ���Ƃ��]�܂���
 *          (3) �L�����e �� URL �G���R�[�h���ׂ��������܂܂��ꍇ�́A�{�֐�
 *              ���� URL �G���R�[�h���s�Ȃ��̂ŁA���炩���� URL �G���R�[�h��
 *              �Ă����K�v�͂Ȃ��B�Ȃ��AURL �G���R�[�h���s�Ȃ������ʁA�L����
 *              �e�̃T�C�Y�� SND_BUFFER_SIZE ���傫���Ȃ��Ă��܂����ꍇ�́A
 *              ���e�Ɏ��s����
 *          (4) �u�������v�̊T�O�̂Ȃ� blog �c�[���ɑ΂��ẮApublish �̒l��
 *              �Ӗ��������Ȃ�(��Ɂu���J�v��Ԃł̓��e�ƂȂ�)�B�܂��A���ł�
 *              �u���J�v��Ԃœ��e�����L����ҏW����ꍇ�́Ablog �c�[���ɂ��
 *              �Ă͉������ł̓��e���w�����Ă��u���J�v��Ԃ̂܂܂ƂȂ邱�Ƃ�
 *              ����
 *          (5) �L���̒��g��S���ύX���Ă��Ȃ��ꍇ�ł��A�{�֐��ɂ��u���J�v
 *              ���w�肷��ƁArebuild �����s�����(���s����Ȃ� blog �c�[��
 *              ������)
 */

BOOL
editPostEx( const char    *postID,
            const char    *userName,
            const char    *password,
            const CONTENT *content,
            BOOL          publish );


/* �w��L���̎擾
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
 *
 *    getPost
 *      ����:
 *          char         *postID        (I) �L��ID
 *          char         *userName      (I) ���[�U��
 *          char         *password      (I) �p�X���[�h
 *          CONTENTINFEX *contentInfo   (O) �擾�����L�����
 *      �߂�l:
 *          TRUE    �擾����
 *          FALSE   �w��L�������݂��Ȃ��A�擾���s�A���M���s�A���̑��̃G���[
 *                  ����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 */

BOOL
getPost( const char   *postID,
         const char   *userName,
         const char   *password,
         CONTENTINFEX *contentInfo );


/* �w�茏�����̍ŐV�L���̎擾
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
 *          ����: dateCreated �́Cblogid �� weblog �ɂ����Ă̎��ԑтɂȂ��Ă�
 *                �܂��D 
 *                link �� permaLink �́C�ǂ���� �~�ς���Ă���L���ւ� URL��
 *                �Ȃ�܂��D
 *
 *    getRecentPostsEx
 *      ����:
 *          char         *blogID         (I) blog ID
 *          char         *userName       (I) ���[�U��
 *          char         *password       (I) �p�X���[�h
 *          int          *numberOfPosts  (I) �擾����L�����
 *                                       (O) ���ۂɎ擾�����L�����
 *          CONTENTINFEX *contentInfo    (O) �擾�����L�����
 *      �߂�l:
 *          0       �L�������݂��Ȃ��A�擾���s�A���M���s�A���̑��̃G���[����
 *          1 �ȏ�  �擾�ɐ��������L�����̐�
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) *numberOfPosts �Ŏw�肵�����̕������A�ŐV�̋L������ߋ��̋L��
 *              �֑k������ɋL�������擾����
 *          (3) ���ۂɎ擾�ɐ��������L�����̐��� *numberOfPosts �ɐݒ肷��
 */

int
getRecentPostsEx( const char   *blogID,
                  const char   *userName,
                  const char   *password,
                  int          *numberOfPosts,
                  CONTENTINFEX *contentInfo );


/* �t�@�C���̃A�b�v���[�h
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
 *
 *    getRecentPostsEx
 *      ����:
 *          char    *blogID    (I) blog ID
 *          char    *userName  (I) ���[�U��
 *          char    *password  (I) �p�X���[�h
 *          FILEINF *fileInf   (I) �A�b�v���[�h����t�@�C���Ɋւ�����
 *          char    *url       (O) �A�b�v���[�h�����t�@�C���� URL
 *      �߂�l:
 *          TRUE    �擾����
 *          FALSE   �A�b�v���[�h���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) �A�b�v���[�h��̃t�@�C�����́Ablog �̃g�b�v�f�B���N�g�������
 *              ���΃p�X�Ŏw�肷��B���݂��Ȃ��f�B���N�g�����w�肵���ꍇ�͍�
 *              �������(blog �c�[���ɂ���ẮA�G���[�ƂȂ�\������)
 *          (3) ���łɃT�[�o��ɓ����̃t�@�C�������݂���ꍇ�́A���̂܂܏㏑
 *              �������ꍇ�ƁA�ʂ̖��O�ŕۑ������ꍇ������B�O�҂̗�Ƃ�
 *              �� Movable Type�A��҂̗�Ƃ��� TypePad ����������
 */

BOOL
newMediaObject( const char *blogID,
                const char *userName,
                const char *password,
                FILEINF    *fileInf,
                char       *url );


/*****  MovableType API  *****/
/* �w�茏�����̋L�����̎擾
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
 *          ����: dateCreated �́Cblogid �� weblog �ɂ����Ă̎��ԑтɂȂ��Ă�
 *                �܂��D
 *
 *    getRecentPostTitles
 *      ����:
 *          char    *blogID         (I) blog ID
 *          char    *userName       (I) ���[�U��
 *          char    *password       (I) �p�X���[�h
 *          int     *numberOfPosts  (I) �擾����L�����
 *                                  (O) ���ۂɎ擾�����L�����
 *          POSTINF *postinf        (O) �擾�����L�����
 *      �߂�l:
 *          0       �L�������݂��Ȃ��A�擾���s�A���M���s�A���̑��̃G���[����
 *          1 �ȏ�  �擾�ɐ��������L�����̐�
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) *numberOfPosts �Ŏw�肵�����̕������A�ŐV�̋L������ߋ��̋L��
 *              �֑k������ɋL�������擾����
 *          (3) ���ۂɎ擾�ɐ��������L�����̐��� *numberOfPosts �ɐݒ肷��
 */

int
getRecentPostTitles( const char *blogID,
                     const char *userName,
                     const char *password,
                     int        *numberOfPosts,
                     POSTINF    *postinf );


/* �J�e�S���ꗗ�̎擾
 *  mt.getCategoryList 
 *      ����: ���� weblog �ɂ��邷�ׂĂ̕��ނ�Ԃ��܂��D
 *      ����: String blogid,
 *            String username,
 *            String password
 *      �Ԃ�l: ��������ƁC���̗v�f���܂ލ\���̂̔z�񂪕Ԃ��Ă��܂�:
 *                  String categoryId
 *                  String categoryName;
 *              ���s����ƁCfault ���Ԃ�܂��D
 *
 *    getCategoryList
 *      ����:
 *          char       *blogID           (I) blog ID
 *          char       *userName         (I) ���[�U��
 *          char       *password         (I) �p�X���[�h
 *          int        *numOfCategories  (I) �擾����J�e�S���̐�
 *                                       (O) ���ۂɎ擾�����J�e�S���̐�
 *          CATLISTINF *categories       (O) �擾�����J�e�S�����
 *      �߂�l:
 *          0       �J�e�S�������݂��Ȃ��A�擾���s�A���M���s�A���̑��̃G���[
 *                  ����
 *          1 �ȏ�  �擾�ɐ��������J�e�S���̐�
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) *numOfCategories �Ŏw�肵�����̕������A�J�e�S�������擾����
 *              ���ۂɑ��݂���J�e�S������ *numOfCategories �Ŏw�肵���l����
 *              �����ꍇ�́A�S�J�e�S���ł͂Ȃ��A*numOfCategories �Ŏw�肵����
 *              �����擾����
 *          (3) ���ۂɎ擾�ɐ��������J�e�S���̐��� *numOfCategories �ɐݒ肷��
 */

int
getCategoryList( const char   *blogID,
                 const char   *userName,
                 const char   *password,
                 long         *numOfCategories, /* �J�e�S���̐� */
                 CATLISTINF_t categories );     /* �J�e�S��     */


/* �w��L���ɑ΂��Đݒ�ς݂̃J�e�S���ꗗ�̎擾
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
 *
 *    getPostCategories
 *      ����:
 *          char   *postID              (I) �L��ID
 *          char   *userName            (I) ���[�U��
 *          char   *password            (I) �p�X���[�h
 *          int    *numberOfCategories  (I) �擾����J�e�S���̐�
 *                                      (O) ���ۂɎ擾�����J�e�S���̐�
 *          CATINF *categories          (O) �擾�����J�e�S�����
 *      �߂�l:
 *          0       �J�e�S�������݂��Ȃ��A�擾���s�A���M���s�A���̑��̃G���[
 *                  ����
 *          1 �ȏ�  �擾�ɐ��������J�e�S���̐�
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) *numberOfCategories �Ŏw�肵�����̕������A�J�e�S�������擾
 *              ����B���ۂɐݒ肳��Ă���J�e�S������ *numberOfCategories��
 *              �w�肵���l���傫���ꍇ�́A�S�J�e�S���ł͂Ȃ��A
 *              *numberOfCategories �Ŏw�肵���������擾����
 *          (3) ���ۂɎ擾�ɐ��������J�e�S���̐��� *numberOfCategories �ɐݒ�
 *              ����
 */

int
getPostCategories( const char *postID,
                   const char *userName,
                   const char *password,
                   long       *numberOfCategories,
                   CATINF     *categories );


/* �w��L���ւ̃J�e�S���̐ݒ�
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
 *
 *    setPostCategories
 *      ����:
 *          char     *postID             (I) �L��ID
 *          char     *userName           (I) ���[�U��
 *          char     *password           (I) �p�X���[�h
 *          long     numberOfCategories  (I) �ݒ肷��J�e�S���̐�
 *          CATEGORY *categories         (I) �ݒ肷��J�e�S�����
 *      �߂�l:
 *          TRUE   �ݒ萬��
 *          FALSE  �ݒ莸�s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) numberOfCategories �Ŏw�肵�����̕������A�J�e�S������ݒ�
 *              ����B
 */

BOOL
setPostCategories( const char *postID,
                   const char *userName,
                   const char *password,
                   long       numOfCategories,
                   CATEGORY   *categories );


/* �T�|�[�g���Ă��� XML-RPC API �ꗗ�̎擾
 *  mt.supportedMethods 
 *      ����: �T�[�o�Œ񋟂���Ă��� XML-RPC �̌Ăяo�����@���擾���܂��D
 *      ����: �Ȃ�
 *      �Ԃ�l: �T�[�o�Œ񋟂���Ă���Ăяo�����@�̔z�񂪕Ԃ�܂��D
 *
 *    getSupportedMethods
 *      ����:
 *          int  *numberOfMethods  (I) �擾����Ăяo�����@�̐�
 *                                 (O) ���ۂɎ擾�����Ăяo�����@�̐�
 *          char *methodList[]     (O) �擾�����Ăяo�����@�̃��X�g
 *      �߂�l:
 *          0       XML-RPC API �����݂��Ȃ��A�擾���s�A���M���s�A���̑���
 *                  �G���[����
 *          1 �ȏ�  �擾�ɐ������� XML-RPC API �̐�
 *      ���l:
 *          (1) *numberOfMethods  �Ŏw�肵�����̕������A�Ăяo�����@���擾
 *              ����B���ۂɑ��݂���Ăяo�����@�̐��� *numberOfMethods ��
 *              �w�肵���l���傫���ꍇ�́A*numberOfMethods  �Ŏw�肵����
 *              �����擾����
 *          (2) ���ۂɎ擾�ɐ��������Ăяo�����@�̐��� *numberOfMethods ��
 *              �ݒ肷��
 */

int
getSupportedMethods( int *numberOfMethods, char *methodList[] );


/*
 *  mt.supportedTextFilters 
 *      ����: �T�[�o�Œ񋟂���Ă��镶�����`�v���O�C���Ɋւ�������擾���܂�
 *      ����: �Ȃ�
 *      �Ԃ�l: String key
 *              String label
 *              ���܂ލ\���̂̔z�񂪂������Ă��܂��D 
 *              key �́C�������`�v���O�C������ʂ����ӂȕ�����ŁC label 
 *              �́C�����ǂ߂邩�����ɂ��������ł��D 
 *              key �́CnewPost��editPost�� mt_convert_breaks�ϐ��Ƃ��ēn��
 *              ���ׂ��l�ł��D
 *
 *    getSupportedFilters
 *      ����:
 *          int       *numberOfFilters  (I) �擾����v���O�C���̐�
 *                                      (O) ���ۂɎ擾�����v���O�C���̐�
 *          FILTERINF *filterList       (O) �擾�����v���O�C���̃��X�g
 *      �߂�l:
 *          0       �v���O�C�� �����݂��Ȃ��A�擾���s�A���M���s�A���̑���
 *                  �G���[����
 *          1 �ȏ�  �擾�ɐ������� XML-RPC API �̐�
 *      ���l:
 *          (1) *numberOfFilters �Ŏw�肵�����̕������A �v���O�C�����擾��
 *              ��B���ۂɑ��݂���Ăяo�����@�̐��� *numberOfFilters �Ŏw
 *              �肵���l���傫���ꍇ�́A*numberOfFilters�Ŏw�肵��������
 *              �擾����
 *          (2) ���ۂɎ擾�ɐ��������v���O�C���̐��� *numberOfFilters �ɐ�
 *              �肷��
 */

int
getSupportedFilters( int       *numberOfFilters,
                     FILTERINF *filterList );

/* �w��L���ɑ΂���g���b�N�o�b�N�ꗗ�̎擾
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
 *
 *    getTrackbackPings
 *      ����:
 *          char  *postID         (I) �L��ID
 *          int   *numberOfPings  (I) �擾����g���b�N�o�b�N���̐�
 *                                (O) ���ۂɎ擾�����g���b�N�o�b�N���̐�
 *          TBINF *tbInfo         (O) �擾�����g���b�N�o�b�N���
 *      �߂�l:
 *          0       �g���b�N�o�b�N�����݂��Ȃ��A�擾���s�A���M���s�A���̑���
 *                  �G���[����
 *          1 �ȏ�  �擾�ɐ��������g���b�N�o�b�N���̐�
 *      ���l:
 *          (1) *numberOfPings �Ŏw�肵�����̕������A�g���b�N�o�b�N�����擾
 *              ����B���ۂɑ��݂���g���b�N�o�b�N�̐��� *numberOfPings  �Ŏw
 *              �肵���l���傫���ꍇ�́A*numberOfPings �Ŏw�肵���������擾
 *              ����
 *          (2) ���ۂɎ擾�ɐ��������g���b�N�o�b�N���̐��� *numberOfPings 
 *              �ɐݒ肷��
 */

int
getTrackbackPings( const char *postID,
                   int        *numberOfPings,
                   TBINF      *tbInfo );


/* �č\�z�̎��s
 *  mt.publishPost 
 *      ����: weblog �ɂ��邷�ׂĂ̐ÓI�t�@�C�������J (�č\�z) ���܂��D 
 *            ����́C�V�X�e���ɋL���𓊍e���C�ۑ����邱�ƂƂ��Ȃ����Ƃł��D
 *            (�Ⴄ�̂́C���̕��@���� Ping ���s��Ȃ��C�Ƃ������Ƃł�)�D
 *      ����: String postid,
 *            String username,
 *            String password
 *      �Ԃ�l: ��������� true ���C���s����� fault ���Ԃ�܂��D
 *
 *    publishPost
 *      ����:
 *          char  *postID    (I) �L��ID
 *          char  *userName  (I) ���[�U��
 *          char  *password  (I) �p�X���[�h
 *      �߂�l:
 *          TRUE   �č\�z����
 *          FALSE  �č\�z���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 */

BOOL
publishPost( const char *postID,
             const char *userName,
             const char *password );


/* �w�蓊�e�����ł̓��e�\�� [����]
 *  mt.setNextScheduledPost
 *    (�d�l�A�ڍוs��)
 */


/* XML-RPC �𗘗p�������[�e�B���e�B�֐��Q */

/*
 * blog ID �̎擾
 *    ����:   ���[�U��, �p�X���[�h
 *    �߂�l: (�V�X�e�����ɑ��݂��� blog �̂����A�����΂�ŏ��Ɍ���
 *             ������ blog ��) blog ID
 *    ���l: �����_�̃R�R���O�̂悤�� 1�T�C�g 1blog �Œ�̏ꍇ�́A��
 *          �̊֐��ŏ\��
 *          �� 2004�N2��20���ȍ~�A�v���X��v�����o��B�R�R���O�ł���
 *             �� blog �ݒu�\�ɂȂ���
 */

int
getBlogID( const char *userName,
           const char *password,
           char       *blogID );  /* blog ID �̎擾 */

/*
 * blog ID �̎擾
 *    ����:   ���[�U��, �p�X���[�h, �擾���� blog ���i�[�ꏊ
 *    �߂�l: �V�X�e�����ɑ��݂��� blog �̐�
 *    ���l: Movable Type �œ���T�C�g���ɕ����� blog ��ݒu����
 *          ����ꍇ�́A���̊֐����g��
 */

int
getBlogIDs( const char *userName,
            const char *password,
            int        *numberOfBlogs,
            BLOGINF    *blogInfo );

/*
 * �ŐV�̋L���̎擾
 */

int
getRecentPost( const char *blogID,
               const char *userName,
               const char *password,
               CONTENTINF *contentInfo );
int
getRecentPost2( const char   *blogID,
                const char   *userName,
                const char   *password,
                CONTENTINFEX *contentInfo );
int
getRecentPost3( const char *blogID,
                const char *userName,
                const char *password,
                POSTINF    *postinf );

/* getRecentPostTitles() �� blogger API �� */
int
getRecentPostTitlesOnBloggerAPI( const char *blogID,
                                 const char *userName,
                                 const char *password,
                                 int        *numberOfPosts,
                                 POSTINF    *postinf );

/* getRecentPostTitles() �� metaWeblog API �� */
int
getRecentPostTitlesOnMetaWeblog( const char *blogID,
                                 const char *userName,
                                 const char *password,
                                 int        *numberOfPosts,
                                 POSTINF    *postinf );

/* RSS ���擾���A���̓��e������ POSTINF �\���̂ɏ����i�[���� */
/*          (XML-RPC API �͎g��Ȃ�)                           */
int
getRecentPostTitlesFromRSS(
        const char *rssURL,         // (I) RSS �� URL
        int        *numberOfPosts,  // (I) �擾����L�����̐�
                                    // (O) ���ۂɎ擾�����L�����̐�
        POSTINF    *postinf         // (O) �擾�����L�����
    );


/*
 * post ID �ꗗ�̎擾
 */

int
getRecentPostIDs( const char *blogID,
                  const char *userName,
                  const char *password,
                  int        *numberOfPosts,
                  char       listOfPostIDs[][MAX_POSTIDLENGTH] );

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
            char       *url );


/*
 *  �ȉ��AMovable Type �ł̓T�|�[�g����Ă��Ȃ� Blogger XML-RPC API
 *
 *  blogger.getTemplate
 *      see also:
 *        http://new.blogger.com/developers/api/1_docs/xmlrpc_getTemplate.html
 *      
 *      ����: appkey (string): Unique identifier/passcode of the application
 *                             sending the post. (See access info.)
 *            blogid (string): Unique identifier of the blog who's template is
 *                             to be returned.
 *            username (string): Login for a Blogger who has admin permission
 *                               on give blog.
 *            password (string): Password for said username.
 *            templateType (string): Determines which of the blog's templates
 *                                   will be returned.
 *                                   Currently, either "main" or "archiveIndex".
 *
 *  blogger.setTemplate 
 *      see also:
 *        http://new.blogger.com/developers/api/1_docs/xmlrpc_setTemplate.html
 *
 *      ����: appkey (string): Unique identifier/passcode of the application
 *                             sending the post. (See access info.)
 *            blogid (string): Unique identifier of the blog who's template is
 *                             to be returned.
 *            username (string): Login for a Blogger who has admin permission
 *                               on give blog.
 *            password (string): Password for said username.
 *            template (string): The text for the new template (usually mostly
 *                               HTML).
 *                               Must contain opening and closing <Blogger>
 *                               tags, since they're needed to publish.
 *            templateType (string): Determines which of the blog's templates
 *                                   will be returned.
 *                                   Currently, either "main" or "archiveIndex".
 *
 *  �ȉ��AMovable Type �ł̓T�|�[�g����Ă��Ȃ� metaWeblog XML-RPC API
 *      (http://www.xmlrpc.com/metaWeblogApi)
 *
 *  metaWeblog.getCategories
 *      ����: blogid, username, password
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

/* category ���\���� (metaWeblog.getCategories �p) */
typedef struct categories {
    char    categoryTitle[MAX_CATIDLENGTH];         /* �J�e�S���̖��O */
    char    categoryDescription[MAX_CATNAMELENGTH]; /* �J�e�S���̐��� */
}   CATEGORIES, *CATEGORIES_t;

int
getCategories( const char   *blogID,
               const char   *userName,
               const char   *password,
               long         *numOfCategories, /* �J�e�S���̐� */
               CATEGORIES_t categories );     /* �J�e�S��     */


/* ���̑��� blog �֘A XML-RPC
 *
 *      http://www.blogcensus.net/?page=API
 *          BlogCensus.isBlog( URL )
 *            Returns 1 if the provided URL is a crawled weblog, 0 otherwise
 *          BlogCensus.getGenerator( URL )
 *            Returns the name of the authoring tool used to generate the blog
 *          BlogCensus.getLanguage( URL )
 *            Returns a string containing the language the blog is written in
 *          BlogCensus.getIncomingLinkCount( URL )
 *            Returns an integer count of incoming links from other blogs
 *          BlogCensus.getOutgoingLinkCount( URL )
 *            Returns an integer count of outgoing links to other blogs
 *
 *      http://www.livejournal.com/doc/server/ljp.csp.xml-rpc.protocol.html
 *      (livejournal API)
 *          LJ.XMLRPC.login - validate user's password and get base
 *                            information needed for client to function
 *          LJ.XMLRPC.postevent - The most important mode, this is how a user
 *                            actually submits a new log entry to the server.
 *          LJ.XMLRPC.editevent - Edit or delete a user's past journal entry
 *          LJ.XMLRPC.editfriendgroups - Edit the user's defined groups of
 *                            friends.
 *          LJ.XMLRPC.editfriends - Add, edit, or delete friends from
 *                            the user's friends list.
 *          LJ.XMLRPC.getevents - Download parts of the user's journal.
 *          LJ.XMLRPC.getfriends - Returns a list of which other LiveJournal
 *                            users this user lists as their friend.
 *          LJ.XMLRPC.friendof - Returns a list of which other LiveJournal
 *                            users list this user as their friend.
 *          LJ.XMLRPC.getfriendgroups - Retrieves a list of the user's defined
 *                            groups of friends.
 *          LJ.XMLRPC.getdaycounts - This mode retrieves the number of journal
 *                            entries per day.
 *          LJ.XMLRPC.syncitems - Returns a list of all the items that have
 *                            been created or updated for a user.
 *          LJ.XMLRPC.checkfriends - Checks to see if your friends list has
 *                            been updated since a specified time.
 *          LJ.XMLRPC.consolecommand - Run an administrative command.
 *
 */

/*
 * XML-RPC API �Ƃ͊֌W�Ȃ����A���ɗ��Ǝv����API
 */

/*
 *  �g���b�N�o�b�N���M
 */
int
sendTrackbackPing( const char *blogName,
                   const char *articleTitle,
                   const char *articleURL,
                   const char *articleExcerpt,
                   const char *targetURL );

/*
 *  �w��L���̃g���b�N�o�b�N���M�pURL�̎擾
 *      (1) �����Ƃ��� trackback Auto-discovery �@�\���g���Ď擾
 *      (2) �������Atrackback Auto-discovery ���Ή��ȂƂ���ł��A
 *          �L���� URL �����ɁA���̖@���Ńg���b�N�o�b�N���M�p
 *          URL �����߂邱�Ƃ��ł���ꍇ�́A���� URL ��Ԃ�
 */
char    *
getTrackbackURL( const char *articleURL );


/* �͂Ăȃ_�C�A���[�L�[���[�h�����N�֘A API */

/*
 * �͂Ăȃ_�C�A���[�L�[���[�h���X�g�擾
 */

int
getHatenaKeywordList();

/*
 * �͂Ăȃ_�C�A���[�L�[���[�h�����N�ϊ�
 */

#define MODE_RAW        1
#define MODE_HTML       2

char    *
changeHatenaKeyword( const char *src, char *dst, int mode );

/* �͂Ăȃ_�C�A���[�L�[���[�h���������NAPI (XML-RPC API) */
/*
 *      uri: http://d.hatena.ne.jp/xmlrpc 
 *      encoding: utf8 
 *      methodName: hatena.setKeywordLink 
 *      parameters: �ȉ����Q�� 
 *          body(string): �L�[���[�h�𒊏o����e�L�X�g���w�肵�܂��B 
 *          score(int): 0�`50�B�L�[���[�h�X�R�A�̂������l���w�肵�܂��B
 *                      �w�肳�ꂽ�l�����X�R�A���傫���L�[���[�h�݂̂���
 *                      �o����܂��B
 *          cname(array): �L�[���[�h�̃J�e�S���[���w�肵�܂��B�w�肪������
 *                        �ꍇ�A�u��ʁv�Ǝw�肳�ꂽ�J�e�S���[�̃L�[���[�h
 *                        �����o����܂��B�w�肪���������ꍇ�́A�S�J�e�S���[
 *                        �ƂȂ�܂��B
 *                        book,music,movie,web,elec,animal,anime,food,sports,
 *                        game,comic,hatena,club���w��\�ł��B�ȗ��B
 *          a_target(string): �A���J�[(a)�^�O��target�����l���w�肵�܂��B
 *                            ��F_blank 
 *          a_class(string): �A���J�[(a)�^�O��class�����l���w�肵�܂��B
 *                           ��Fkeyword 
 *      [cname �� 2004�N6��17���ɒǉ����ꂽ����]
 */

/*  �L�[���[�h�̃J�e�S��         */
/*    �ȉ��̒l�̘_���a�Ŏw�肷�� */
#define CNAME_GENERAL       0x0000
#define CNAME_BOOK          0x0001
#define CNAME_MUSIC         0x0002
#define CNAME_MOVIE         0x0004
#define CNAME_WEB           0x0008
#define CNAME_ELEC          0x0010
#define CNAME_ANIMAL        0x0020
#define CNAME_ANIME         0x0040
#define CNAME_FOOD          0x0080
#define CNAME_SPORTS        0x0100
#define CNAME_GAME          0x0200
#define CNAME_COMIC         0x0400
#define CNAME_HATENA        0x0800
#define CNAME_CLUB          0x1000

char    *
setKeywordLink( const char    *src,
                char          *dst,
                size_t        dstSize,
                int           score,
                unsigned long cname,
                const char    *target,
                const char    *keywordClass );



/*
 *  Bulkfeeds API
 */

/* Bulkfeeds API �L�[�ݒ� */
void
setApiKeyOnBulkfeeds( const char *apiKey );

/* RSS �o�^/�X�V  �� weblogUpdates.ping ���g�p */

/* RSS/OPML���ڎw��ɂ��o�^/�X�V                               */
/*   GET http://bulkfeeds.net/app/add.xml?url=�o�^������RSS/OPML */
BOOL
updateRssOnBulkfeeds( const char *url );

/* RSS Feed ����                                                         */
/*  GET http://bulkfeeds.net/app/search.opml?q=�L�[���[�h;field=�����Ώ� */
/*  GET http://bulkfeeds.net/app/search.rdf?q=�L�[���[�h;field=�����Ώ�  */
/*            �L�[���[�h�� UTF-8 �̕������ URL �G���R�[�h��������       */
/*            �����Ώ� �� title | description | link �̂����ꂩ          */

#define OUTPUT_RSS  1
#define OUTPUT_OPML 2

int
searchRssOnBulkfeeds( const char *keyword, const char *field, int outputType );

/* RSS Item �S������ */
/*  GET http://bulkfeeds.net/app/search2.rdf?q=�L�[���[�h                */

int
searchEntryOnBulkfeeds(
        const char *keyword,        // (I) �L�[���[�h
        int        *numberOfPosts,  // (I) �擾����L�����̐�
                                    // (O) ���ۂɎ擾�����L�����̐�
        POSTINF    *postinf         // (O) �擾�����L�����
    );

/* RSS Similarity Search                                                 */
/*  GET http://bulkfeeds.net/app/similar.rdf?url=�A�h���X&apikey=API�L�[ */

int
searchSimilarityOnBulkfeeds(
        const char *url,            // (I) �ގ��L���������������L����URL
        const char *apiKey,         // (I) API�L�[
        int        *numberOfPosts,  // (I) �擾����L�����̐�
                                    // (O) ���ۂɎ擾�����L�����̐�
        POSTINF    *postinf         // (O) �擾�����L�����
    );

/* ��������10��擾                                                       */
/*  GET http://bulkfeeds.net/app/similar.xml?url=�A�h���X&apikey=API�L�[    */
/*   �Ԃ�l(XML) �̗�                                                       */
/*    <?xml version="1.0" encoding="utf-8" ?>                               */
/*    <terms about="http://watcher.moe-nifty.com/memo/2004/04/post_1.html"> */
/*    <term>�D�q</term>                                                     */
/*    <term>���q</term>                                                     */
/*    <term>BLOODY</term>                                                   */
/*    <term>�g���J</term>                                                   */
/*    <term>���</term>                                                     */
/*    <term>�b</term>                                                       */
/*    <term>�v��</term>                                                     */
/*    <term>�t��</term>                                                     */
/*    <term>��</term>                                                       */
/*    <term>�g</term>                                                       */
/*    </terms>                                                              */

#define MAX_LEN_BF_TERM 256 /* term ������ő咷 (�b��) */
typedef struct  bf_term {
    char    term[MAX_LEN_BF_TERM + 1];
}   BF_TERM;                /* ������(�`�ԑf)�i�[�̈� */

int
extractFeatureWordsOnBulkfeeds(
        const char *url,        // (I) ������𒊏o�������L����URL
        const char *apiKey,     // (I) API�L�[
        int        *numOfTrems, // (I) �擾���������̐� (�ő� 10��)
                                // (O) ���ۂɎ擾����������̐�
        BF_TERM    *terms       // (O) �擾����������
    );

/* �`�ԑf��� + �����ꒊ�o                                                  */
/*  GET http://bulkfeeds.net/app/terms.xml?content=��͑Ώە�����&apikey=API�L�[ */

int
extractAnalyseOnBulkfeeds(
        const char *content,    // (I) �`�ԑf���(�����ꒊ�o)�Ώۂ̕�����
        const char *apiKey,     // (I) API�L�[
        int        *numOfTrems, // (I) �擾���������̐�
                                // (O) ���ۂɎ擾����������̐�
        BF_TERM    *terms       // (O) �擾����������
    );

/* RSS Auto Discovery                                                     */
/*  GET http://bulkfeeds.net/app/discover.xml?url=�A�h���X&apikey=API�L�[ */

char    *
getRssUrlOnBulkfeeds( const char *blogUrl, const char *apiKey );


/*
 *  FeedBack API
 */

/* RSS Item �S������ */
/*   GET http://naoya.dyndns.org/feedback/app/rss?keyword=�L�[���[�h */

int
searchEntryOnFeedback(
        const char *keyword,        // (I) �L�[���[�h
        int        *numberOfPosts,  // (I) �擾����L�����̐�
                                    // (O) ���ۂɎ擾�����L�����̐�
        POSTINF    *postinf         // (O) �擾�����L�����
    );


/*
 *  Amazon Web Services API
 */

/*
 *  Amazon��XML Web�T�[�r�X��URL (REST)
 *
 *      http://xml-jp.amznxslt.com/onca/xml3?
 *
 *  ����URL��?�̌�Ɉȉ��̃p�����[�^�[��&�ő����Ďw�肵�܂��B
 *      t=      �A�\�V�G�C�gID  
 *      dev-t=  �f�B�x���b�p�[�E�g�[�N��  
 *      type=   �擾����f�[�^�̎��
 *                  lite:   �ȈՔ�
 *                  heavy:  ���S��
 *      page=   �������ʂ������̏ꍇ�̃y�[�W�ԍ�  
 *      mode=   �������鏤�i�̎��
 *                  books-jp:       �a��
 *                  books-us:       �m��
 *                  music-jp:       ���y
 *                  classical-jp:   ���y�N���V�b�N
 *                  dvd-jp:         DVD
 *                  vhs-jp:         �r�f�I
 *                  electronics-jp: �G���N�g���j�N�X
 *                  software-jp:    �\�t�g�E�F�A
 *                  videogames-jp:  �Q�[��
 *                  toys-jp:        ��������&�z�r�[
 *      f=      XSLT�𗘗p����ꍇ�́AXSLT��URL�B
 *              URL�̑���� f=xml�@�Ƃ���ƁAxml�����̂܂܎擾�ł���B
 *      KeywordSearch=
 *      ASINSearch=
 *      BrowseNodeSearch=
 *              KeywordSearch�Ȃǂ̌����̎�ނ��w�肵�āAKeywordSearch=������
 *              �L�[���[�h��Asin�ԍ��A�m�[�h�ԍ��Ȃǂ��w��  
 *      locale= jp
 */

/* Amazon �A�\�V�G�C�gID �̐ݒ� */
void
setAssociateIdOnAmazon( const char *associateID );

/* Amazon Subscription ID �̐ݒ� */
void
setSubscriptionIDOnAmazon( const char *subscriptionID );

/* Amazon �Ō��� */
/*   �擾����f�[�^�̎�� */
#define AMAZON_TYPE_LITE        1   /* �ȈՔ� */
#define AMAZON_TYPE_HEAVY       2   /* ���S�� */

/*   �������鏤�i�̎��   */
#define AMAZON_MODE_JBOOKS      1   /* �a��             */
#define AMAZON_MODE_EBOOKS      2   /* �m��             */
#define AMAZON_MODE_MUSIC       3   /* ���y             */
#define AMAZON_MODE_CLASSIC     4   /* ���y�N���V�b�N   */
#define AMAZON_MODE_DVD         5   /* DVD              */
#define AMAZON_MODE_VIDEO       6   /* �r�f�I           */
#define AMAZON_MODE_ELECTRONICS 7   /* �G���N�g���j�N�X */
#define AMAZON_MODE_SOFTWARE    8   /* �\�t�g�E�F�A     */
#define AMAZON_MODE_GAME        9   /* �Q�[��           */
#define AMAZON_MODE_KITCHEN     10  /* �L�b�`��         */
#define AMAZON_MODE_TOYS        11  /* ��������&�z�r�[  */
#define AMAZON_MODE_HOBBY       12  /* �z�r�[           */
#define AMAZON_MODE_SPORTS      13  /* �X�|�[�c         */
#define AMAZON_MODE_BLENDED     255 /* ���ׂĂ̏��i     */

/*   �������@             */
#define AMAZON_STYPE_KEYWORD    1   /* �L�[���[�h�Ō��� */
#define AMAZON_STYPE_ASIN       2   /* ISBN/ASIN �Ō��� */
#define AMAZON_STYPE_NODE       3   /* �m�[�h�ԍ��Ō��� */

/* for ECS4.0 */
/*   �擾����f�[�^�̎�� */
#define AMAZON_TYPE_SMALL       1   /* �ȈՔ� */
#define AMAZON_TYPE_MEDIUM      2   /* ���y�� */
#define AMAZON_TYPE_LARGE       3   /* ���S�� */

/*   �������@             */
#define AMAZON_STYPE_ITEMSEARCH 1   /* ���i�̌��� */
#define AMAZON_STYPE_ITEMLOOKUP 4   /* ���i�ڍ�   */

int
searchItemsOnAmazon4(
        int        type,        /* (I) Small, Medium, Large */
        int        mode,        /* (I) �����Ώە���         */
        int        searchType,  /* (I) �������             */
        const char *keyword,    /* (I) �����ΏۃL�[���[�h   */
        int        *numOfItems, /* (I/O) �������ʃA�C�e���� */
        void       *result      /* (O) �������ʊi�[�̈�     */
    );

/* Amazon �̃x�X�g�Z���[���X�g�擾 */
int
getSalesRankingOnAmazon4(
        int        type,        /* (I) heavy or lite        */
        int        mode,        /* (I) �����Ώە���(��g)   */
        int        node,        /* (I) �����Ώە���(�i����) */
        const char *genre,      /* (I) �����Ώە��얼       */
        int        *numOfItems, /* (I/O) �������ʃA�C�e���� */
        void       *result      /* (O) �������ʊi�[�̈�     */
    );

/*
 *  Rakuten Web Services API
 *      �E�]���^�� API �� �A�t�B���G�C�gID(��) �݂̂��g�p
 *      �E2007�N1���ɓo�ꂵ�� API �� �f�x���b�p�[ID �� �A
 *        �t�B���G�C�gID(�V) ���g�p
 */

/* �y�V �f�x���b�p�[ID �̐ݒ� */
void
setDeveloperIdOnRakuten( const char *developerID );

/* �y�V �A�t�B���G�C�gID(��) �̐ݒ� */
void
setAffiliateIdOnRakuten( const char *affiliateID );

/* �y�V �A�t�B���G�C�gID(�V) �̐ݒ� */
void
setAffiliateIdOnRakuten2( const char *affiliateID2 );

/* �y�V�u�b�N�X �Z�[���X�����L���O�̎擾 */
/*   �擾����t�@�C���̌`�� */
#define RAKUTEN_TYPE_HTML   1   /* html */
#define RAKUTEN_TYPE_XML    2   /* xml  */

/*   �ΏۃT�[�r�X */
#define RAKUTEN_SERVICE_BOOKS   1   /* �y�V�u�b�N�X */

/*   �W������ (�ΏۃT�[�r�X���u�y�V�u�b�N�X�v�̏ꍇ) */
#define RAKUTEN_GENRE_GENERAL       0   /* ����                   */
#define RAKUTEN_GENRE_COMICS        1   /* �R�~�b�N�E�W���u�i�C�� */
#define RAKUTEN_GENRE_CHALLENGE     2   /* ��w�E�A�E�E���i����   */
#define RAKUTEN_GENRE_CHILDREN      3   /* �G�{�E������           */
#define RAKUTEN_GENRE_NOVEL         4   /* ���|�E�m���t�B�N�V���� */
#define RAKUTEN_GENRE_COMPUTER      5   /* �o�b�E�V�X�e���J��     */
#define RAKUTEN_GENRE_BUSINESS      6   /* �r�W�l�X�E�o�ρE�o�c   */
#define RAKUTEN_GENRE_TRAVEL        7   /* ���s�E�I�s�E�A�E�g�h�A */
#define RAKUTEN_GENRE_HOWTO         8   /* �w�₪�킩��{         */
#define RAKUTEN_GENRE_HOBBY         9   /* �z�r�[�E�X�|�[�c       */
#define RAKUTEN_GENRE_LIFESTYLE     10  /* ���C�t�X�^�C��         */
#define RAKUTEN_GENRE_ENTERTAINMENT 11  /* �G���^�[�e�C�����g     */
#define RAKUTEN_GENRE_ACADEMIC      12  /* ��发�E�w�p��         */
#define RAKUTEN_GENRE_PHOTOBOOK     13  /* �ʐ^�W�E�^�����g       */


int
getSalesRankingOnRakuten(
        int  type,          /* (I) �擾����t�@�C���̌`�� */
        int  service,       /* (I) �ΏۃT�[�r�X           */
        int  genre,         /* (I) �W������               */
        int  *numOfItems,   /* (I/O) �������ʃA�C�e����   */
        void *result        /* (O) �������ʊi�[�̈�       */
    );


/*
 * cousagi XML-RPC API
 *
 *  cousagi.getNewEntry 
 *    ���� 
 *      ���������ɐV�����L�����������܂� 
 *    ���� 
 *      String  username, // �������� �̃��[�U��(�A�J�E���g)
 *      String  password, // ��L���[�U�� login �p�p�X���[�h
 *
 *  cousagi.getNewPhrase 
 *    ���� 
 *      ���������ɐV�������������܂� 
 *    ���� 
 *      String  username, // �������� �̃��[�U��(�A�J�E���g)
 *      String  password, // ��L���[�U�� login �p�p�X���[�h
 *
 *  cousagi.getNewHaiku 
 *    ���� 
 *      ���������ɐV�����o����r�܂��܂� 
 *    ���� 
 *      String  username, // �������� �̃��[�U��(�A�J�E���g)
 *      String  password, // ��L���[�U�� login �p�p�X���[�h
 *
 *  cousagi.getNewWhisper 
 *    ���� 
 *      ���������ɐV�����Q�����Ԃ₩���܂� 
 *    ���� 
 *      String  username, // �������� �̃��[�U��(�A�J�E���g)
 *      String  password, // ��L���[�U�� login �p�p�X���[�h
 */

/*
 *  Blog Pet ���
 */
#define BPTYPE_UNKNOWN  0x0000  /* ���ݒ�   */
#define BPTYPE_COUSAGI  0x0001  /* �������� */
#define BPTYPE_CONEKO   0x0002  /* ���˂�   */
#define BPTYPE_COINU    0x0003  /* ������   */
#define BPTYPE_COPANDA  0x0004  /* ���ς� */
#define BPTYPE_CONEZUMI 0x0005  /* ���˂��� */

/* BlogPet��ʂ�������������擾 (���܂�API) */
char    *
blogPetTypeString( int blogPetType );

/* �L���̐��� */
int
getNewEntryOnCousagi( const char *userName,
                      const char *password,
                      char       *title,
                      char       *body );

/* �����̐��� */
int
getNewPhraseOnCousagi( const char *userName,
                       const char *password,
                       char       *response );

/* �o��̉r�� */
int
getNewHaikuOnCousagi( const char *userName,
                      const char *password,
                      char       *response );

/* �Q���̐��� */
int
getNewWhisperOnCousagi( const char *userName,
                        const char *password,
                        char       *response );

/* ���������L���ɔo��𖄂ߍ��� (���܂�API) */
char    *insertHaikuIntoEntry( char       *body,
                               const char *haiku,
                               const char *cousagiName,
                               int        blogPetType );

/*
 *  ���܂�
 */

/* ISBN �� �e��URL�ϊ� */
char    *
isbn2urls(
        const char *isbn,    /* (I) ISBN                               */
        BOOL       isAffiliateAvalable,
                             /* (I) �A�t�B���G�C�g�����N���܂߂邩�ۂ� */
        const char *vcSID,   /* (I) ValueCommerce SID                  */
        const char *vcPID1,  /* (I) �N���l�R���}�g�u�b�N�T�[�r�X PID   */
        const char *vcPID2,  /* (I) JBOOK                        PID   */
        const char *vcPID3,  /* (I) �I�ɚ������X                 PID   */
        const char *vcPID4   /* (I) @�Ö{�s��                    PID   */
    );


#ifdef  XMLRPC_EXPORTS
/*
 *  ���ʊ֐�(���[�e�B���e�B�֐�)�Q
 */
int
getDateCreated( char **input,
                int *yy, int *mm, int *dd, int *HH, int *MM, int *SS,
                int *cnt, int cntMax,
                int *numOfInfo );

int
getUserid( char **input,
           char *userid,
           int *cnt, int cntMax,
           int *numOfInfo );

int
getPostid( char **input,
           char *postid,
           int *cnt, int cntMax,
           int *numOfInfo );

int
getContent( char **input,
            char *content,
            int *cnt, int cntMax,
            int *numOfInfo );

int
getTitle( char **input,
          char *title,
          int *cnt, int cntMax,
          int *numOfInfo );

int
getPingUrl( char **input,
            char *pingURL,
            int *cnt, int cntMax,
            int *numOfInfo );

int
getPingTitle( char **input,
              char *pingTitle,
              int *cnt, int cntMax,
              int *numOfInfo );

int
getPingIP( char **input,
           char *pingIP,
           int *cnt, int cntMax,
           int *numOfInfo );

int
getUrl( char **input,
        char *url,
        int *cnt, int cntMax,
        int *numOfInfo );

int
getBlogid( char **input,
           char *blogid,
           int *cnt, int cntMax,
           int *numOfInfo );

int
getBlogName( char **input,
             char *blogName,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getFirstname( char **input,
             char *blogName,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getLastname( char **input,
             char *lastname,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getNickname( char **input,
             char *nickname,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getEmail( char **input,
          char *email,
          int *cnt, int cntMax,
          int *numOfInfo );

int
getDescription( char **input,
                char *description,
                int *cnt, int cntMax,
                int *numOfInfo );

int
getLink( char **input,
         char *link,
         int *cnt, int cntMax,
         int *numOfInfo );

int
getPermaLink( char **input,
              char *permaLink,
              int *cnt, int cntMax,
              int *numOfInfo );

int
getExcerpt( char **input,
            char *excerpt,
            int *cnt, int cntMax,
            int *numOfInfo );

int
getExtended( char **input,
             char *excerpt,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getAllowComments( char **input,
                  int *allowComments,
                  int *cnt, int cntMax,
                  int *numOfInfo );

int
getAllowPings( char **input,
               int *allowPings,
               int *cnt, int cntMax,
               int *numOfInfo );

int
getConvertLineBreaks( char **input,
                      char *convertLineBreaks,
                      int *cnt, int cntMax,
                      int *numOfInfo );

int
getKeywords( char **input,
             char *keywords,
             int *cnt, int cntMax,
             int *numOfInfo );

int
getCategoryId( char **input,
               char *categoryId,
               int *cnt, int cntMax,
               int *numOfInfo );

int
getCategoryName( char **input,
                 char *categoryName,
                 int *cnt, int cntMax,
                 int *numOfInfo );

int
getIsPrimary( char **input,
              int *isPrimary,
              int *cnt, int cntMax,
              int *numOfInfo );

int
getKey( char **input,
        char *key,
        int *cnt, int cntMax,
        int *numOfInfo );

int
getLabel( char **input,
          char *label,
          int *cnt, int cntMax,
          int *numOfInfo );

int
getPublish( char **input,
            int *publish,
            int *cnt, int cntMax,
            int *numOfInfo );

int
getArrayCategories( char **input,
                    char *categories[MAX_CATEGORIES],
                    int  *numOfCategories );

char    *
getSingleString( const char *src, char *dst );

BOOL
getStringFromItem( const char *spec,
                   const char *in[],
                   char       *out,
                   int        size,
                   int        *cnt );

BOOL
getDateTimeFromItem( const char *spec,
                     const char *in[],
                     POSTINF    *out,
                     int        *cnt );

/* XML����f�[�^�����o�����߂̃��[�e�B���e�B�֐� */
char    *
getResultFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *sectionEnd,
        char       *result
    );

char    *
getResultFromXML_s(
        const char *xmlSrc,
        const char *tagName,
        const char *sectionEnd,
        char       *result,
        size_t     result_size
    );  // getResultFromXML �̃T�C�Y�`�F�b�N�@�\�t���o�[�W����

char    *
getIntegerFromXML(
        const char    *xmlSrc,
        const char    *tagName,
        const char    *sectionEnd,
        unsigned long *result
    );

char    *
getFloatFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *sectionEnd,
        double     *result
    );

char    *
getListFromXML(
        const char *xmlSrc,
        const char *tagName,
        const char *subTagName,
        const char *sectionEnd,
        char       *result,
        size_t     areaSizeOfResult
    );

#if (WINVER >= 0x0500)
#ifdef  _MSC_VER
void
resetDaylightSaving( void );
#endif
#endif

#endif  /* XMLRPC_EXPORTS */

/* �����R�[�h�ϊ� */
char    *
sjis2euc( const char *p );

char    *
utf2euc( const char *p );

char    *
jis2euc( const char *p );

char    *
jis2sjis( const char *p );

char    *
euc2sjis( const char *p );

char    *
utf2sjis( const char *p );

char    *
sjis2utf( const char *p );

char    *
jis2utf( const char *p );

char    *
euc2utf( const char *p );

char    *
utf2sjisEx( char *p );  /* �����̌^�� const char *p �ł͂Ȃ� char *p �� */
                        /* ���邱�Ƃɒ���! (�̈�j��^)                 */

/*
 *  �W�����͂���̓���
 */

/* ���l�̓��� */
BOOL
inputNumeric( int *num,     /* (O) ���͌��� (���l)      */
              int minimum,  /* (I) ���͉\���l�̍ŏ��l */
              int maximum );/* (I) ���͉\���l�̍ő�l */

/* yes/no �̓��� */
int
inputYesNo( int        *flag,       /* (O) ���͌��� (yes: TRUE, no: FALSE) */
            const char *prompt );   /* (I) �v�����v�g������                */

/* ������̓��� */
int
inputString( char       *dst,       /* (O) ���͌��� (������)          */
             const char *prompt,    /* (I) �v�����v�g������           */
             int        password ); /* (I) �p�X���[�h���̓��[�h���ۂ� */

/*
 *  ���̑�
 */
char    *
base64( const unsigned char *src, size_t sz );            // base64�G���R�[�h
char    *
unbase64( const unsigned char *src, unsigned char *dst, size_t *sz );
                                                          // base64�f�R�[�h

unsigned char   *
sha1( const unsigned char *src );               // SHA1�Í���

void
hmac_sha1(
    const unsigned char *text,      /* pointer to data stream        */
    int                 text_len,   /* length of data stream         */
    const unsigned char *key,       /* pointer to authentication key */
    int                 key_len,    /* length of authentication key  */
    void                *digest);   /* caller digest to be filled in */

void
hmac_sha256(
    const unsigned char *text,      /* pointer to data stream        */
    int                 text_len,   /* length of data stream         */
    const unsigned char *key,       /* pointer to authentication key */
    int                 key_len,    /* length of authentication key  */
    void                *digest);   /* caller digest to be filled in */

char    *
decodeString( char *src );                      // ���̎Q�Ƃ̃f�R�[�h

char    *
encodeString( const char *src, char *dst );     // ���̎Q�Ƃւ̃G���R�[�h

int
isHexString( const char *p );   // �w�蕶�����16�i�����񂩔ۂ�

int
isDecString( const char *p );   // �w�蕶�����10�i�����񂩔ۂ�

BOOL
setSigInfo(
        char       *key,
        char       *secret,
        const char *sig1,
        const char *sig2,
        const char *pre,
        const char *post
    );                      // BAZ�G���R�[�h������̃f�R�[�h #1

BOOL
setSigInfo3(
        char       *id1,
        char       *id2,
        char       *id3,
        const char *sig1,
        const char *sig2,
        const char *sig3,
        const char *pre1,
        const char *post1,
        const char *pre2,
        const char *post2
    );                      // BAZ�G���R�[�h������̃f�R�[�h #2

DWORD
getLanguageCode( void );    // Windows �̌�����擾
                            // (�Ⴆ�΁A���{���: 1041, �p��(USA)��: 1033)
void
setLanguageCode( DWORD languageCode );  // Windows �̌���������؂�ւ�

/* �G���h�|�C���gURL�擾 */
char    *
getEndpointURLbyAutoDiscovery( const char *topPageURL, char *blogID );


/* cookie */
#define MAX_COOKIE_NAME_LENGTH  80
#define MAX_COOKIE_VALUE_LENGTH 8192    // �{���� MAX_COOKIE_LEN �ȉ��̒l�� OK

typedef struct cookieInfo   {
    int numOfValuables;
    int maxNumOfValuables;
    struct cookieValuable {
        char    name[MAX_COOKIE_NAME_LENGTH];
        char    value[MAX_COOKIE_VALUE_LENGTH];
    }   *valuable;
}   COOKIE_INFO;

COOKIE_INFO *createCookie( void );
void        destroyCookie( COOKIE_INFO *p );
char        *saveCookie( COOKIE_INFO *cp, const char *cookie );
char        *loadCookie( const COOKIE_INFO *cp );

/* for �R�R���O - �R���g���[���p�l�� - �t�@�C���}�l�[�W�� */
int
loginCocologFiles( const char *username,    // (I) ���[�U��
                   const char *password,    // (I) �p�X���[�h
                   char       *cookie );    // (O) �N�b�L�[

int
uploadCocologFiles( FILEINF *fileInf, // (I)   �A�b�v���[�h����t�@�C���Ɋւ�
                                      //       ����
                    char    *url,     // (O)   �A�b�v���[�h�����t�@�C���� URL
                    char    *cookie );// (I/O) �N�b�L�[

int
deleteCocologFiles( const char *url,        // (I)   �폜�������t�@�C���� URL
                    char       *cookie );   // (I/O) �N�b�L�[

BOOL
deleteFile( const char *username,   // (I) ���[�U��
            const char *password,   // (I) �p�X���[�h
            const char *url );      // (I) �폜�������t�@�C���� URL

/* for �����������E�B�U�[�h */
int isUsedProxy( void );

/* for bookey */
char    *getCurrentLocation( char *url );   /* (I/O) ���O�ɎQ�Ƃ��� URL */

/* for BloGolEe */
void    setConfirmProxyInfoFunc( CONF_FUNC confirmProxyInfo );
BOOL    isNecessaryToCheckProxyInfo( void );

void    setProxyInfo( const char *proxyServer, unsigned short proxyPort,
                      const char *proxyUsername, const char *proxyPassword );

/* for Cjpeg */
size_t  getBinSize();

/* for chirrup */
#ifdef  USE_RURL
char    *
makeRurl( const char *url );    /* rurl.org �𗘗p���ĒZ�kURL�𐶐� */
#endif  /* USE_RURL */

/* for debugging, reporting, ... */
void    dputc( char c );
void    dputs( const char *str );
int     dprintf( const char *format, ... );

/* �G���[�R�[�h */
#define XMLRPC_ERROR_CHANGED_PROXYINFO  ((DWORD)0xFFBEAF01)

#endif  /* __XML_RPC_H__ */
