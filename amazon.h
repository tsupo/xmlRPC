//  $Header: /comm/xmlRPC/amazon.h 2     09/05/29 7:09 tsupo $
/*! @file
 *  @brief Amazon Web Services �֘A�e���`
 *  @author tsujimura543
 *  @date $Date: 09/05/29 7:09 $
 *  @version $Revision: 2 $
 *  @note
 * History:
 * $Log: /comm/xmlRPC/amazon.h $
 * 
 * 2     09/05/29 7:09 tsupo
 * 1.267��
 * 
 * 25    09/05/28 18:37 Tsujimura543
 * �o�b�t�@�I�[�o�[�����΍������
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 24    08/02/15 2:42 Tsujimura543
 * MAX_PRODUCTSNAME_LENGTH �̒l��{�ɂ���
 * 
 * 23    08/02/15 2:16 Tsujimura543
 * avalability �� availability �ɏC�� (typo)
 * 
 * 22    05/11/17 19:55 Tsujimura543
 * AMAZON_MODE_MINICAR �� AMAZON_NODE_MINICAR �ɏC��
 * 
 * 21    05/09/03 0:24 Tsujimura543
 * �R�����g���C���A�ǉ�
 * 
 * 20    05/09/03 0:02 Tsujimura543
 * ����ɃR�����g����������
 * 
 * 19    05/08/30 19:31 Tsujimura543
 * doxygen + graphviz �œ��{����g���f�����X�g���[�V�����Ɏg�����߁A�኱
 * �R�����g���C��
 * 
 * 18    05/08/29 17:49 Tsujimura543
 * doxygen 1.4.4(��������������) �ɂāA�o�͓��e(html�h�L�������g)���m�F�B
 * ��������Afix
 * 
 * 17    05/08/18 16:37 Tsujimura543
 * �R�����g�� doxygen �Ή��ɂ����ƏI��
 * (�ꕔ�̕������������肪�c���Ă���)
 * 
 * 16    05/08/18 11:37 Tsujimura543
 * �R�����g�� doxygen �Ή��ɂ����ƁA���s���뒆
 * 
 * 15    05/08/18 11:02 Tsujimura543
 * �����I�ɃR�����g�̋L�q�� doxygen �Ή��ɂ��Ă݂�
 * 
 * 14    05/05/18 18:32 Tsujimura543
 * �R�����g���C��
 * 
 * 13    05/04/18 16:23 Tsujimura543
 * �u�y�V�A�t�B���G�C�g�v�֘A�̃R�����g�� rakuten.c �ֈړ�
 * 
 * 12    05/04/18 16:08 Tsujimura543
 * Google API �֘A�̃R�����g�� google.c �ֈړ�
 * 
 * 11    05/04/18 15:44 Tsujimura543
 * bidders �֘A������ bidders.h �Ƃ��ĕ����Ɨ�������
 * 
 * 10    04/11/17 15:58 Tsujimura543
 * bidders�֘A�̊e���`��ǉ�
 * 
 * 9     04/11/16 22:49 Tsujimura543
 * �ubidders �J�e�S��ID�v�̒�`��ǉ�
 * 
 * 8     04/11/16 15:19 Tsujimura543
 * bidders Web Service �̎d�l���R�����g�̌`�Ōf��
 * 
 * 7     04/11/05 21:40 Tsujimura543
 * Google Web Service API �� request �� response �̗���R�����g�̌`�Ōf��
 * 
 * 6     04/11/02 18:06 Tsujimura543
 * HEAVY�ł� averageRating �� unsigned long ���� double �ɕύX
 * 
 * 5     04/11/02 16:53 Tsujimura543
 * �u��������&�z�r�[�v�̎�v�J�e�S���̃m�[�h�ԍ��̒�`��ǉ�
 * 
 * 4     04/11/02 16:39 Tsujimura543
 * HEAVY�ō\���̏C��
 * 
 * 3     04/11/01 19:55 Tsujimura543
 * �������ʊi�[�p�̍\���̂̒�`��ǉ�
 * 
 * 2     04/07/07 11:43 Tsujimura543
 * �Ő��Ǘ��� VSS �ōs�Ȃ��悤�ɂ��� 
 */

#ifndef __AMAZON_H__
#define __AMAZON_H__

/** \defgroup amazon Amazon Web Services (AWS) �֘A�e���`
 */
/** \defgroup nodeID �m�[�h�̎��
 *  \ingroup amazon
 *  Common Amazon.co.jp Browse Nodes
 *  (Amazon.co.jp �̎�v�ȃm�[�hID�̈ꗗ)
 */
/*
 *  The following is a list of some of our more popular browse nodes for
 *  the Amazon.co.jp Web site.
 */

/** \defgroup books �a��
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>Books, Literature & Fiction 466284</li>
 *      <li>Books, Philosophy & Religion 571582</li>
 *      <li>Books, Society & Politics 571584</li>
 *      <li>Books, Nonfiction 492152</li>
 *      <li>Books, Travel & Geography 466286</li>
 *      <li>Books, Business & Career 466282</li>
 *      <li>Books, Investment & Financial Management 492054</li>
 *      <li>Books, Science 466290</li>
 *      <li>Books, Computer & Internet 466298</li>
 *      <li>Books, Art & Photography 466294</li>
 *      <li>Books, Entertainment 466296</li>
 *      <li>Books, Sports & Hobby 466292</li>
 *      <li>Books, Home & Family 466304</li>
 *      <li>Books, Foreign Language Reference 466302</li>
 *      <li>Books, Education 3148931</li>
 *      <li>Books, Children's Books 466306</li>
 *      <li>Books, Cartoons & Anime 466280</li>
 *      <li>Books, New Releases 466300</li>
 *      <li>Books, Sheet Music 746102</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_FICTION         466284  //!< ���w�E�]�_
#define AMAZON_NODE_PHILOSOPHY      571582  //!< �v�z�E�l��
#define AMAZON_NODE_SOCIETY         571584  //!< �����E�Љ�
#define AMAZON_NODE_NONFICTION      492152  //!< �m���t�B�N�V����
#define AMAZON_NODE_TRAVEL          466286  //!< ���j�E�n���E���s�K�C�h
#define AMAZON_NODE_BUISINESS       466282  //!< �r�W�l�X�E�o��
#define AMAZON_NODE_FINANCIAL       492054  //!< �N�ƁE�o�c
#define AMAZON_NODE_SCIENCE         466290  //!< �Ȋw�E�e�N�m���W�[
#define AMAZON_NODE_COMPUTER        466298  //!< �R���s���[�^�E�C���^�[�l�b�g
#define AMAZON_NODE_ART             466294  //!< �A�[�g
#define AMAZON_NODE_ENTERTAINMENT   466296  //!< �G���^�[�e�C�����g
#define AMAZON_NODE_SPORTS          466292  //!< ���p�E�X�|�[�c
#define AMAZON_NODE_FAMILY          466304  //!< ���
                                /**!< \note
                                 * �u�d�l���v�ł́u����v�ƂȂ��Ă��邪�A
                                 *�u�ƒ�E�Ƒ��v�̊ԈႢ�ł���Ǝv����
                                 */
#define AMAZON_NODE_REFERENCE       466302  //!< �Q�l���E��w�E�����T
#define AMAZON_NODE_EDUCATION       3148931 //!< ����
#define AMAZON_NODE_CHILDREN        466306  //!< ���ǂ�
#define AMAZON_NODE_CARTOON         466280  //!< �R�~�b�N
#define AMAZON_NODE_NEWRELEASE      466300  //!< �V���E����
                                /**!< \note
                                 * �u�d�l���v�ł́u�V���E���Ɂv�ƂȂ��Ă��邪�A
                                 * �u�V���v�̊ԈႢ�ł���Ǝv����
                                 */
#define AMAZON_NODE_SHEETMUSIC      746102  //!< �y���E�X�R�A�E�s�A�m��

#define AMAZON_NODE_FOREIGNBOOKS    1000    //!< �m��
/*@}*/

/** \defgroup foreignBooks �m��
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>English Books, Arts & Photography 1</li>
 *      <li>English Books, Audiobooks 44</li>
 *      <li>English Books, Biographies & Memoirs 2</li>
 *      <li>English Books, Business & Investing 3</li>
 *      <li>English Books, Children's Books 4</li>
 *      <li>English Books, Computers & Internet 5</li>
 *      <li>English Books, Cooking, Food & Wine 6</li>
 *      <li>English Books, Engineering 13643</li>
 *      <li>English Books, Entertainment 86</li>
 *      <li>English Books, Gay & Lesbian 301889</li>
 *      <li>English Books, Health, Mind & Body 10</li>
 *      <li>English Books, History 9</li>
 *      <li>English Books, Home & Garden 48</li>
 *      <li>English Books, Horror 49</li>
 *      <li>English Books, Law 10777</li>
 *      <li>English Books, Literature & Fiction 17</li>
 *      <li>English Books, Medicine 13996</li>
 *      <li>English Books, Mystery & Thrillers 18</li>
 *      <li>English Books, Nonfiction 53</li>
 *      <li>English Books, Outdoors & Nature 290060</li>
 *      <li>English Books, Parenting & Families 20</li>
 *      <li>English Books, Professional & Technical 173507</li>
 *      <li>English Books, Reference 21</li>
 *      <li>English Books, Religion & Spirituality 22</li>
 *      <li>English Books, Romance 23</li>
 *      <li>English Books, Science 75</li>
 *      <li>English Books, Science Fiction & Fantasy 25</li>
 *      <li>English Books, Sports 26</li>
 *      <li>English Books, Teens 28</li>
 *      <li>English Books, Travel 27</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_E_ART           1     //!< �A�[�g
#define AMAZON_NODE_E_AUDIOBOOKS    44    //!< ���̏o��{
#define AMAZON_NODE_E_BIOGRAPHY     2     //!< �`�L�E��z�^
#define AMAZON_NODE_E_BUISINESS     3     //!< �r�W�l�X�E�o�ρE�N�ƁE�o�c
#define AMAZON_NODE_E_CHILDREN      4     //!< ���ǂ�
#define AMAZON_NODE_E_COMPUTER      5     //!< �R���s���[�^�E�C���^�[�l�b�g
#define AMAZON_NODE_E_COOKING       6     //!< �����E�H��
#define AMAZON_NODE_E_ENGINEERING   13643 //!< �H�w�E���p
#define AMAZON_NODE_E_ENTERTAINMENT 86    //!< �G���^�[�e�C�����g
#define AMAZON_NODE_E_BLGL          301889//!< ������
#define AMAZON_NODE_E_HEALTH        10    //!< ���N�E�S�Ƒ�
#define AMAZON_NODE_E_HISTORY       9     //!< ���j
#define AMAZON_NODE_E_HOME          48    //!< �ƒ�E�뉀
#define AMAZON_NODE_E_HORROR        49    //!< �z���[
#define AMAZON_NODE_E_LAW           10777 //!< �@��
#define AMAZON_NODE_E_FICTION       17    //!< ���w�E�]�_
#define AMAZON_NODE_E_MEDICINE      13996 //!< ��
#define AMAZON_NODE_E_MYSTERY       18    //!< �~�X�e���E�X�����[
#define AMAZON_NODE_E_NONFICTION    53    //!< �m���t�B�N�V����
#define AMAZON_NODE_E_NATURE        290060//!< �A�E�g�h�A�E���R
#define AMAZON_NODE_E_FAMILY        20    //!< �e�w�E�Ƒ�
#define AMAZON_NODE_E_PROFESSIONAL  173507//!< ��发�E�Z�p��
#define AMAZON_NODE_E_REFERENCE     21    //!< �Q�l���E��w�E�����T
#define AMAZON_NODE_E_RELIGION      22    //!< �@���E���_�_
#define AMAZON_NODE_E_ROMANCE       23    //!< ����
#define AMAZON_NODE_E_SCIENCE       75    //!< �Ȋw�E�e�N�m���W�[
#define AMAZON_NODE_E_SCIFI         25    //!< SF�E�t�@���^�W�[
#define AMAZON_NODE_E_SPORTS        26    //!< �X�|�[�c
#define AMAZON_NODE_E_TEENS         28    //!< �v�t��
#define AMAZON_NODE_E_TRAVEL        27    //!< ���s
/*@}*/

/** \defgroup electronics �G���N�g���j�N�X
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>Electronics, Digital Cameras 3371371</li>
 *      <li>Electronics, DVD Players 3371441</li>
 *      <li>Electronics, Portable Audio 3371411</li>
 *      <li>Electronics, Computer 3371341</li>
 *      <li>Electronics, PC Peripherals 3371351</li>
 *      <li>Electronics, Printer & Scanner 3371361</li>
 *      <li>Electronics, Network Equipment 3371381</li>
 *      <li>Electronics, PDA 3371401</li>
 *      <li>Electronics, Accessories 3371421</li>
 *      <li>Electronics, Storage & Memory 3371391</li>
 *      <li>Electronics, Audio Visual 3371431</li>
 *      <li>Electronics, Video Game Hardware 3371461</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_EL_DIGITALCAMERA 3371371 //!< �f�W�^���J����
#define AMAZON_NODE_EL_DVDPLAYER     3371441 //!< DVD�v���[���[�E���R�[�_�[
#define AMAZON_NODE_EL_PORTABLEAUDIO 3371411 //!< �|�[�^�u���I�[�f�B�I
#define AMAZON_NODE_EL_COMPUTER      3371341 //!< �R���s���[�^
#define AMAZON_NODE_EL_PERIPHERAL    3371351 //!< PC���Ӌ@��E�p�[�c
#define AMAZON_NODE_EL_PRINTER       3371361 //!< �v�����^�E�X�L���i
#define AMAZON_NODE_EL_NETWORK       3371381 //!< �l�b�g���[�N�@��
#define AMAZON_NODE_EL_PDA           3371401 //!< PDA�E�d�q����
#define AMAZON_NODE_EL_ACCESSORY     3371421 //!< �A�N�Z�T���E�T�v���C
#define AMAZON_NODE_EL_STORAGE       3371391 //!< �X�g���[�W���f�B�A
#define AMAZON_NODE_EL_AUDIOVISUAL   3371431 //!< �I�[�f�B�I�E�r�W���A��
#define AMAZON_NODE_EL_VIDEOGAME     3371461 //!< �Q�[���@�{��
/*@}*/

/** \defgroup music ���y
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>Music, J-Pop 569170</li>
 *      <li>Music, Popular 569290</li>
 *      <li>Music, Rock 569292</li>
 *      <li>Music, Hard Rock 569298</li>
 *      <li>Music, Blues & Country 562050</li>
 *      <li>Music, Soul & R&B 569318</li>
 *      <li>Music, Hip Hop 569320</li>
 *      <li>Music, Dance 569322</li>
 *      <li>Music, Jazz Fusion 562052</li>
 *      <li>Music, World 562056</li>
 *      <li>Music, New Age 562064</li>
 *      <li>Music, Soundtracks 562058</li>
 *      <li>Music, Animation 562060</li>
 *      <li>Music, Children & Family 562062</li>
 *      <li>Music, Ballad 569174</li>
 *      <li>Music, Traditional 569186</li>
 *      <li>Music, Sports 899296</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_M_JPOP        569170    //!< J-POP
#define AMAZON_NODE_M_POPULAR     569290    //!< �|�s�����[
#define AMAZON_NODE_M_ROCK        569292    //!< ���b�N
#define AMAZON_NODE_M_HARDROCK    569298    //!< �n�[�h���b�N
#define AMAZON_NODE_M_BLUES       562050    //!< �u���[�X�E�J���g���[
#define AMAZON_NODE_M_SOUL        569318    //!< �\�E���E���Y��&�u���[�X
#define AMAZON_NODE_M_HIPHOP      569320    //!< �q�b�v�z�b�v
#define AMAZON_NODE_M_DANCE       569322    //!< �_���X
#define AMAZON_NODE_M_JAZZ        562052    //!< �W���Y�E�t���[�W����
#define AMAZON_NODE_M_WORLD       562056    //!< ���[���h
#define AMAZON_NODE_M_NEWAGE      562064    //!< �j���[�G�C�W
#define AMAZON_NODE_M_SOUNDTRACKS 562058    //!< �T�E���h�g���b�N
#define AMAZON_NODE_M_ANIME       562060    //!< �A�j���E�Q�[��
#define AMAZON_NODE_M_CHILDREN    562062    //!< �L�b�Y�E�t�@�~���[
#define AMAZON_NODE_M_BALLAD      569174    //!< �o���[�h
#define AMAZON_NODE_M_TRADITIONAL 569186    //!< �`�����y
#define AMAZON_NODE_M_SPORTS      899296    //!< �X�|�[�c

#define AMAZON_NODE_M_JAPANESE    562044    //!< J-POP�E���{�̉��y
#define AMAZON_NODE_M_FOREIGN     562046    //!< �C�O�̃��b�N�E�|�b�v�X
#define AMAZON_NODE_M_MOODY       562048    //!< �_���X�E�\�E���E�q�b�v�z�b�v
#define AMAZON_NODE_M_CLASSIC     562054    //!< �N���V�b�N
#define AMAZON_NODE_M_EASYLISTENING 562064  //!< �C�[�W�[���X�j���O�E���̑�
/**< \note
 * AMAZON_NODE_M_NEWAGE �� AMAZON_NODE_M_EASYLISTENING ������ 562064 
 * �Ȃ͕̂� ?
 */
/*@}*/

/** \defgroup classical �N���V�b�N���y
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>Classical, Classical 701040</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_C_CLASSIC           701040  //!< �N���V�b�N
/*@}*/

/** \defgroup dvd DVD
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>DVD, Japanese 562014</li>
 *      <li>DVD, Foreign 562016</li>
 *      <li>DVD, Music 562018</li>
 *      <li>DVD, Animation 562020</li>
 *      <li>DVD, Hobby & Fitness 562022</li>
 *      <li>DVD, Sports 562024</li>
 *      <li>DVD, Family 562026</li>
 *      <li>DVD, TV Documentary 562028</li>
 *      <li>DVD, Box Sets 564522</li>
 *      <li>DVD, Adult 896246</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_D_JAPANESE      562014  //!< ���{�f��
#define AMAZON_NODE_D_FOREIGN       562016  //!< �O���f��
#define AMAZON_NODE_D_MUSIC         562018  //!< ���y�E�X�e�[�W
#define AMAZON_NODE_D_ANIME         562020  //!< �A�j��
#define AMAZON_NODE_D_HOBBY         562022  //!< �z�r�[�E���p
#define AMAZON_NODE_D_SPORTS        562024  //!< �X�|�[�c�E�t�B�b�g�l�X
#define AMAZON_NODE_D_FAMILY        562026  //!< �L�b�Y�E�t�@�~���[
#define AMAZON_NODE_D_DOCUMENTARY   562028  //!< TV�E�h�L�������^���[
#define AMAZON_NODE_D_BOXSETS       564522  //!< DVD�{�b�N�X
#define AMAZON_NODE_D_ADULT         896246  //!< �A�_���g

#define AMAZON_NODE_D_IDOL          562030  //!< �A�C�h���E�C���[�W�E���̑�
/*@}*/

/** \defgroup video �r�f�I
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>VHS, Japanese 561984</li>
 *      <li>VHS, Foreign 561986</li>
 *      <li>VHS, Music 561988</li>
 *      <li>VHS, Animation 561990</li>
 *      <li>VHS, Hobby & Fitness 561992</li>
 *      <li>VHS, Sports 561994</li>
 *      <li>VHS, Family 561996</li>
 *      <li>VHS, TV Documentary 561998</li>
 *      <li>VHS, Imports 564546</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_V_JAPANESE      561984  //!< ���{�f��
#define AMAZON_NODE_V_FOREIGN       561986  //!< �O���f��
#define AMAZON_NODE_V_MUSIC         561988  //!< ���y�E�X�e�[�W
#define AMAZON_NODE_V_ANIME         561990  //!< �A�j��
#define AMAZON_NODE_V_HOBBY         561992  //!< �z�r�[�E���p
#define AMAZON_NODE_V_SPORTS        561994  //!< �X�|�[�c�E�t�B�b�g�l�X
#define AMAZON_NODE_V_FAMILY        561996  //!< �L�b�Y�E�t�@�~���[
#define AMAZON_NODE_V_DOCUMENTARY   561998  //!< TV�E�h�L�������^���[
#define AMAZON_NODE_V_IMPORTS       564546  //!< �A����

#define AMAZON_NODE_V_IDOL          562000  //!< �A�C�h���E�C���[�W�E���̑�
/*@}*/

/** \defgroup software �\�t�g�E�F�A
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>Software, Games 689132</li>
 *      <li>Software, Children's 1040140</li>
 *      <li>Software, Hobby 637656</li>
 *      <li>Software, Foreign Language Training 637658</li>
 *      <li>Software, Internet 637648</li>
 *      <li>Software, General Business 637644</li>
 *      <li>Software, Industry-Specific Business 1040106</li>
 *      <li>Software, Graphics 637652</li>
 *      <li>Software, Music 637654</li>
 *      <li>Software, Utility 637662</li>
 *      <li>Software, Network Management 1040116</li>
 *      <li>Software, Programming 637650</li>
 *      <li>Software, Operating System 637666</li>
 *      <li>Software, Macintosh 3137861</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_S_GAME              689132  //!< �Q�[��
#define AMAZON_NODE_S_CHILDREN          1040140 //!< �m��
#define AMAZON_NODE_S_HOME              637656  //!< �z�[���E���p
                            /**< \note 
                             * �u�d�l���v�ł́u�z�[���E���p�v�ƂȂ��Ă��邪�A
                             *�u��v�̊ԈႢ�ł���Ǝv����
                             */
#define AMAZON_NODE_S_EDUCATION         637658  //!< ����E�z�r�[
                            /**< \note
                             * �u�d�l���v�ł́u����E�z�r�[�v�ƂȂ��Ă��邪�A
                             * �u�O����w�K�v�̊ԈႢ�ł���Ǝv����
                             */
#define AMAZON_NODE_S_INTERNET          637648  //!< Web�J��
#define AMAZON_NODE_S_BUISENESS         637644  //!< �r�W�l�X�E�I�t�B�X
#define AMAZON_NODE_S_INDUSTORIAL       1040140
                                             //!< �H������E���Y�Ǘ��E�i���Ǘ�
#define AMAZON_NODE_S_GRAPHICS          637652  //!< �O���t�B�b�N�X
#define AMAZON_NODE_S_MUSIC             637654  //!< �f���E���y
#define AMAZON_NODE_S_UTILITY           637662  //!< ���[�e�B���e�B
#define AMAZON_NODE_S_NETWORKMANAGEMENT 1040116 //!< �l�b�g���[�N�Ǘ�
#define AMAZON_NODE_S_PROGRAMMING       637650  //!< �v���O���~���O
#define AMAZON_NODE_S_OPERATINGSYSTEM   637666  //!< OS
#define AMAZON_NODE_S_MACINTOSH         3137861 //!< Macintosh

#define AMAZON_NODE_S_NETWORK           637646  //!< �ʐM�E�l�b�g���[�N
#define AMAZON_NODE_S_SECURITY          637664  //!< �Z�L�����e�B
#define AMAZON_NODE_S_LINUX             689118  //!< Linux
/*@}*/

/** \defgroup games �r�f�I�Q�[��
 *  \ingroup nodeID
 *  �m�[�hID�ꗗ
 *    <ul>
 *      <li>Video Games, Play Station 2 637874</li>
 *      <li>Video Games, Play Station 637876</li>
 *      <li>Video Games, Nintendo Gamecube 637878</li>
 *      <li>Video Games, Game Boy Advance 637880</li>
 *      <li>Video Games, Game Boy 637882</li>
 *      <li>Video Games, Xbox 639096</li>
 *      <li>Video Games, Other 637886</li>
 *    </ul>
 *  \note ��L�̃m�[�hID�� AWS �̎d�l���Ɍf�ڂ���Ă�����̂ł��邪�A
 *      ���ۂɎg�p����Ă���m�[�hID�͕ʂ̒l�ɕύX����Ă��邱�Ƃ�����̂Œ���
 */
/*@{*/
#define AMAZON_NODE_PS2             637874  //!< PlayStation2
#define AMAZON_NODE_PLAYSTATION     637876  //!< PlayStation
#define AMAZON_NODE_GAMECUBE        637878  //!< NINTENDO GAMECUBE
#define AMAZON_NODE_GBA             637880  //!< GAMEBOY ADVANCE
#define AMAZON_NODE_GAMEBOY         637882  //!< GAMEBOY
#define AMAZON_NODE_XBOX            637884  //!< Xbox (639096 �̊ԈႢ?)
#define AMAZON_NODE_ANOTHERMACHINE  637886  //!< ���̑��̋@��
/*@}*/

/** \defgroup kitchen  �L�b�`��
 *  \ingroup nodeID
 */
/*@{*/
#define AMAZON_NODE_KITCHEN     3895781 //!< �L�b�`���p�i
#define AMAZON_NODE_COOKING     3895771 //!< �����@��
#define AMAZON_NODE_HAIR        3895751 //!< �����e�O�b�Y
#define AMAZON_NODE_HEALTH      3895741 //!< ���N�O�b�Y
#define AMAZON_NODE_LIVING      3895791 //!< �����Ɠd
#define AMAZON_NODE_SEASON      3895761 //!< �G�߉Ɠd
#define AMAZON_NODE_LIGHT       4082801 //!< �Ɩ����
#define AMAZON_NODE_ACCESSORY   3895801 //!< ���Օi�E�A�N�Z�T��
/*@}*/

/** \defgroup toys �������� & �z�r�[
 *  \ingroup nodeID
 */
/*@{*/
#define AMAZON_NODE_TOYS            13299531    //!< �������� & �z�r�[
#define AMAZON_NODE_EDU_TOYS        13321671    //!< �m��ߋ�
#define AMAZON_NODE_DOLLS           13321731    //!<�l�`�E�~�j�h�[��
#define AMAZON_NODE_COSTUMEPLAY     13321761    //!< �ϐg�E�Ȃ肫��
#define AMAZON_NODE_ACTIONFIGURE    13321821    //!< �A�N�V�����t�B�M���A
#define AMAZON_NODE_MINICAR         13321831    //!< �~�j�J�[�E��
#define AMAZON_NODE_GAMES           637394      //!< �Q�[��
/*@}*/

/**
 *  \defgroup amazonSearch �������ʊi�[�p�\����
 *  \ingroup amazon
 */
/** \defgroup stringLength �������ʕ�����ő咷
 *  \ingroup amazonSearch
 */
/*@{*/
#define MAX_PRODUCTSNAME_LENGTH 256  //!< �u���i���A�����v�ő咷
#define MAX_AUTHORINFO_LENGTH   128  //!< �u��ҁA�Ҏҁv�ő咷
#define MAX_MANUFACTURER_LENGTH 128  //!< �u���s���A�������v�ő咷
#define MAX_PRICE_LENGTH        48   //!< �u�艿�A�̔����i�v�ő咷
#define MAX_NODEID_LENGTH       16   //!< �u�m�[�hID�v�ő咷
#define MAX_NODENAME_LENGTH     80   //!< �u�W���������v�ő咷
#define MAX_MEDIALEN            40   //!< �u�̔��`�ԁv�ő咷
#define MAX_COMMENT_LENGTH      4096 //!< �u�]�҂̃R�����g�v�ő咷

#define MAX_NUMOFNODES          12   //!< �ő�֘A�W��������
#define MAX_NUMOFREVIEWS        3    //!< �ő�(�擾�\)���r���[��
/*@}*/

/** \defgroup liteType �������ʊi�[�p(�y�ʔ�)
 *  \ingroup amazonSearch
 */
/*@{*/
//! LITE�^�C�v
/** type �� lite �Ɏw�肵�Č��������Ƃ��̌������ʂ��i�[���� */
typedef struct amazonSearchResultLite   {
    char    url[MAX_URLLENGTH_MAX];                //!< ���i�y�[�WURL
    char    asin[MAX_NAMELEN];                     //!< ASIN
    char    productName[MAX_PRODUCTSNAME_LENGTH];  //!< ���i���A����
    char    authors[MAX_AUTHORINFO_LENGTH];        //!< ��ҁA�Ҏ�
    char    releaseDate[MAX_DATELENGTH];           //!< ���s�N����
    char    manufacturer[MAX_MANUFACTURER_LENGTH]; //!< ���s���A������
    char    imageURLsmall[MAX_URLLENGTH];          //!< �����ȉ摜��URL
    char    imageURLmedium[MAX_URLLENGTH];        //!< ���ʃT�C�Y�̉摜��URL
    char    imageURLlarge[MAX_URLLENGTH];          //!< �傫�ȉ摜��URL
    char    availability[MAX_LOGICALLINELEN];      //!< �݌ɏ�
    char    listPrice[MAX_PRICE_LENGTH];           //!< �艿
    char    amazonPrice[MAX_PRICE_LENGTH];         //!< �̔����i
    char    usedPrice[MAX_PRICE_LENGTH];//!< �}�[�P�b�g�v���C�X�ł̔̔����i�Œ�l
}   AMAZON_LITE, *AMAZON_LITE_t;
/*@}*/

/** \defgroup heavyType �������ʊi�[�p(�d�ʔ�)
 *  \ingroup amazonSearch
 */
/*@{*/
//! HEAVY�^�C�v
/** type �� heavy �Ɏw�肵�Č��������Ƃ��̌������ʂ��i�[���� */
typedef struct amazonSearchResultHeavy  {
    char    url[MAX_URLLENGTH_MAX];              //!< ���i�y�[�WURL
    char    asin[MAX_NAMELEN];                   //!< ASIN
    char    productName[MAX_PRODUCTSNAME_LENGTH];//!< ���i���A����
    char    authors[MAX_AUTHORINFO_LENGTH];      //!< ��ҁA�Ҏ�
    char    releaseDate[MAX_DATELENGTH];         //!< ���s�N����
    char    manufacturer[MAX_MANUFACTURER_LENGTH];//!< ���s���A������
    char    imageURLsmall[MAX_URLLENGTH];        //!< �����ȉ摜��URL
    char    imageURLmedium[MAX_URLLENGTH];       //!< ���ʃT�C�Y�̉摜��URL
    char    imageURLlarge[MAX_URLLENGTH];        //!< �傫�ȉ摜��URL
    char    availability[MAX_LOGICALLINELEN];    //!< �݌ɏ�
    char    listPrice[MAX_PRICE_LENGTH];         //!< �艿
    char    amazonPrice[MAX_PRICE_LENGTH];       //!< �̔����i
    char    usedPrice[MAX_PRICE_LENGTH]; //!< �}�[�P�b�g�v���C�X�ł̔̔����i�Œ�l
    unsigned long   salesRank;                   //!< ����グ����

    long    numOfBrowseNodes;                    //!< �m�[�h��

    /** \struct browseList amazon.h "amazon.h"
     *  \brief �m�[�h(�W������)
     *
     *      browseNodeSearch �p�́u�m�[�hID�v�Ƃ��̃m�[�hID�ɑΉ�����
     *      �u�W���������v��ێ����܂�
     */
    struct browseList   {
        char    browseNode[MAX_NODEID_LENGTH];   //!<    �m�[�hID
        char    nodeName[MAX_NODENAME_LENGTH];   //!<    �W��������
    }   browseNodes[MAX_NUMOFNODES];             //!< �m�[�h

    char    media[MAX_MEDIALEN];                 //!< �̔��`��
    char    isbn[MAX_NAMELEN];                   //!< ISBN

    /** \struct reviewsOnAmazon amazon.h "amazon.h"
     *  \brief ���r���[
     *
     *      ���Y���ЁE���i�Ɋւ��郌�r���[�̈ꗗ(�z��)
     */
    struct reviewsOnAmazon {
        double          averageRating;           //!<    �S�]�҂̕]���̕���
        unsigned long   numOfReviews;            //!<    ���r���[��

        /** \struct reviewOnAmazon amazon.h "amazon.h"
         *  \brief  1�]�҂̃��r���[
         *
         *      �]�҂̕]���A�R�����g�A�]�Ҏ��g�Ɋւ������ێ����܂�
         */
        struct reviewOnAmazon {
            unsigned long   rating;              //!<      �]�� (5�i�K)
            char    summury[MAX_LOGICALLINELEN]; //!<      �]�҂Ɋւ�����
            char    comment[MAX_COMMENT_LENGTH]; //!<      �]�҂̃R�����g
        }   review[MAX_NUMOFREVIEWS];            //!<    �]�Җ��̃��r���[
    }       reviews;                             //!< �S�]�҂̃��r���[

    char    similarProcducts[MAX_LOGICALLINELEN];//!< �֘A���i��ASIN (����)
}   AMAZON_HEAVY, *AMAZON_HEAVY_t;
/*@}*/


/*
 * AWS parameters
 *
 *  Parameter Types
 *      This section shows the various parameter types that can be used with
 *      Amazon.com Web Services.
 *
 *    REST Parameter    SOAP Element    Description
 *
 *      t                   tag                 Associates tag
 *      ct                  N/A                 Content-type for returned data
 *                                               (important for those who use 
 *                                                XSL or are using proprietary
 *                                                systems that can't handle 
 *                                                the text/HTML content type)
 *      dev-t               devtag              Developer token
 *      sort                sort                Sort type 
 *      mode                mode                Product line
 *      type                type                Output type
 *      f                   N/A                 Output format
 *      page                page                Result page
 *      offer               offer               The offer parameter is used to
 *                                              request and limit the types of
 *                                              offerings returned as part of
 *                                              an ASIN search. If the offer 
 *                                              parameter is not supplied then
 *                                              the returned data does not 
 *                                              include any offering 
 *                                              information. If the parameter
 *                                              is supplied it must be one of
 *                                              the following values: 
 *                                                  1.       ThirdPartyNew
 *                                                  2.       Used
 *                                                  3.       Collectible
 *                                                  4.       Refurbished
 *                                                  5.       All
 *      offerpage           offerpage           The offerpage parameter is 
 *                                              used to request a particular 
 *                                              page of offering information. 
 *                                              The default value is 1; 25 
 *                                              offerings are returned per 
 *                                              page. 
 *                                              To put offer and offerpage 
 *                                              together, consider the  
 *                                              following page:
 *                                                  http://www.amazon.com/exec/obidos/tg/stores/offering/list/-/0385503822/used/ref%3Dbuy%5Fpb%5Fu%5F
 *                                              The offer parameter selects 
 *                                              a single "tab" of info 
 *                                              (Used/New/Collectible). Then 
 *                                              the offerpage selects 
 *                                              successive chunks of 25 offers
 *                                              within the page. 
 *      offerstatus         offerstatus         The offerstatus parameter is 
 *                                              used to request either open  
 *                                              (value ="open") or closed 
 *                                              (value="closed") offers when
 *                                              requesting information about
 *                                              a seller using the 
 *                                              SellerSearch request (REST) or
 *                                              a SellerRequest (SOAP).
 *      keywords            keywords            The keyword parameter is used
 *                                              in SellerSearch requests, and
 *                                              allows the user to filter 
 *                                              a specific seller's products 
 *                                              by a keyword. 
 *      N/A                 seller-browse-id    The seller-browse-id parameter
 *                                              is used in SellerSearch 
 *                                              requests, and allows the user 
 *                                              to filter a specific seller's
 *                                              products by a browse ID. 
 *                                              Seller browse IDs use
 *                                              a different taxonomy than 
 *                                              Amazon.com retail? to view the
 *                                              seller browse ID tree, please 
 *                                              go here:
 *                                                  http://s1.amazon.com/exec/varzea/ts/browse-zshops/68280
 *                                              The ID is the number after the
 *                                              "browse-zshops" string.
 *      locale              locale              International locale specifier
 *      price               price               The price parameter may be 
 *                                              used to narrow search results 
 *                                              within a price range, 
 *                                              specified in pennies (i.e., 
 *                                              price=3200-3500 narrows search
 *                                              results to products with 
 *                                              an OurPrice between $32.00 and
 *                                              $35.00 (may be used with 
 *                                              foreign currencies as well))
 *      desc                desc                Include the desc parameter in 
 *                                              Seller Profile Search, Seller 
 *                                              Search, or Marketplace Search
 *                                              to retrieve marketplace 
 *                                              exchange descriptions. 
 *      sims                sims                Include the sims parameter in
 *                                              a remote shopping cart add, 
 *                                              get, or modify request to get
 *                                              a list of ASINs that represent
 *                                              the intersection of the 
 *                                              current cart ASINs' 
 *                                              similarities. 
 *      CartId              CartId              Unique identifier for 
 *                                              an Amazon shopping cart. For
 *                                              use in remote shopping cart 
 *                                              requests. This parameter and 
 *                                              the HMAC parameter must be 
 *                                              included in any request to
 *                                              an existing Amazon remote 
 *                                              shopping cart.  
 *      Hmac                HMAC                Security token that, coupled
 *                                              with the CartId, is required 
 *                                              to make requests to 
 *                                              an existing remote shopping 
 *                                              cart. 
 *      Item                Item                The Item parameter allows
 *                                              a user to modify or remove
 *                                              an item from an Amazon remote
 *                                              shopping cart. Please see the
 *                                              documentation for more 
 *                                              information. 
 *      index               index               This parameter may be used in
 *                                              Seller Search and Marketplace
 *                                              Search to narrow search 
 *                                              results so that they come from
 *                                              only zShops (index=zshops) or
 *                                              only marketplace
 *                                              (index=marketplace). 
 *      keyword             keyword             Specify search terms for 
 *                                              Marketplace Search in this 
 *                                              parameter. Note: This is 
 *                                              different than the "keywords"
 *                                              parameter above. 
 *      keyword-search      keyword_search      This parameter may be used in
 *                                              Marketplace Search to ensure 
 *                                              search results are based on 
 *                                              product titles only 
 *                                              (keyword-search=title) or on
 *                                              product title and description
 *                                              (keyword-search=titledesc). 
 *      browse-id           browse_id           Use this parameter to specify
 *                                              a marketplace browse ID for
 *                                              Marketplace Search. 
 *      zipcode             zipcode             Use this parameter to retrieve
 *                                              products from sellers located
 *                                              in a particular ZIP code. 
 *      area-id             area_id             Use this parameter to specify
 *                                              a numerical country code 
 *                                              representing the country from
 *                                              which or to which you wish the
 *                                              search results to be shipped. 
 *                                              This parameter must be used in
 *                                              combination with the "geo" 
 *                                              parameter.
 *      geo                 geo                 Use this parameter to specify
 *                                              whether you would like the 
 *                                              search results to include 
 *                                              products that are shippable
 *                                              from (geo=ship-from) or to
 *                                              (geo=ship-to) the country 
 *                                              specified by the country code
 *                                              in the "area_id" parameter.  
 *      listing-id          listing_id          Use this parameter to query
 *                                              for information about
 *                                              a specific zShops listing. 
 *      BrowseNodeSearch    browse_node         Browse node search specifier
 *      SellerSearch        seller_id           Seller search specifier
 *      AsinSearch          asin                ASIN/ISBN search specifier
 *      UpcSearch           upc                 UPC search specifier
 *      ExchangeSearch      exchange_id         Exchange search specifier
 *      AuthorSearch        author              Author search specifier
 *      ArtistSearch        artist              Artist/Musician search 
 *                                              specifier
 *      ActorSearch         actor               Actor/Actress search specifier
 *      DirectorSearch      director            Director search specifier
 *      ManufacturerSearch  manufacturer        Manufacturer search specifier
 *      ListmaniaSearch     lm_id               Listmania search specifier
 *      SimilaritySearch    asin                Similarity search specifier
 *      SellerProfile       seller_id           The SellerProfile parameter 
 *                                              requests request for 
 *                                              information about a particular
 *                                              seller. The value of the 
 *                                              parameter is an encrypted 
 *                                              representation of the Seller
 *                                              ID. 
 *      WishlistSearch      wishlist_id         Wish list query specifier
 *      PowerSearch         power               Power search query specifier
 *      MarketplaceSearch   marketplace_search  Marketplace or zShops search
 *                                              specifier 
 *      BlendedSearch       blended             All product search specifier 
 *      TextStreamSearch    textStream          Search specifier for request
 *                                              that allows the user to search
 *                                              for Amazon products with 
 *                                              product details that match
 *                                              a chunk of text. 
 *
 */

#endif  /* __AMAZON_H__ */
