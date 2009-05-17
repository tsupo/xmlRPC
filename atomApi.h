/*
 *  atom API
 *
 * History:
 * $Log: /comm/xmlRPC/atomApi.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 14    09/03/16 15:04 Tsujimura543
 * MAX_CATEGORIES �̒�`�� xmlRPC.h �ֈڂ���
 * 
 * 13    06/01/23 14:38 Tsujimura543
 * listPostsOnAtomAPI() �̒���(6)��ǉ�
 * 
 * 12    05/08/17 15:09 Tsujimura543
 * postEntryOnAtomAPI() �� editEntryOnAtomAPI() �Ɉ�����ǉ����A
 * ���������e�\�Ƃ��� (�Ώۂ� blogger.com �̂�)
 * 
 * 11    05/07/01 11:16 Tsujimura543
 * (�{�t�@�C��������)�R�����g������ɍ��킹�ďC��
 * 
 * 10    05/06/28 21:58 Tsujimura543
 * editEntryOnAtomAPI() ��ǉ�
 * 
 * 9     04/10/15 11:55 Tsujimura543
 * �R�����g�̏C��
 * 
 * 8     04/10/15 11:52 Tsujimura543
 * getEndpointURLbyAutoDiscoveryOnAtomAPI() ��ǉ�
 * 
 * 7     04/08/13 14:28 Tsujimura543
 * getRecentPostTitlesOnAtomAPI() ��ǉ�
 * 
 * 6     04/08/12 21:17 Tsujimura543
 * getBlogIDsOnAtomAPI() ��ǉ�
 * 
 * 5     04/07/16 19:19 Tsujimura543
 * postEntryOnAtomAPI() �Ɉ�����ǉ����A�T�v���w��ł���悤�ɂ���
 * 
 * 4     04/07/16 13:57 Tsujimura543
 * Atom API �֘A�A�S�ʌ������BXML-RPC API �֘A�֐��Ƃ̐�����}��B
 * 
 * 3     04/07/09 20:30 Tsujimura543
 * livedoor Blog �� Atom API �Ή�
 * 
 * 2     04/07/07 11:43 Tsujimura543
 * RCS �ɂ��Ő��Ǘ����� VSS �ɂ��Ő��Ǘ��Ɉڍs
 */

#ifndef __ATOM_API_H__
#define __ATOM_API_H__

#include "xmlRPC.h"

#define MAX_TYPELENGTH  80

/*
 *  Atom authentication uses WSSE, and is represented as an "X-WSSE" HTTP
 *  header.
 *      X-WSSE: UsernameToken Username="name", PasswordDigest="digest", 
 *      Created="timestamp", Nonce="nonce"
 *          Username
 *              The username that the user enters (the TypePad username).
 *          Nonce
 *              A secure token generated anew for each HTTP request.
 *          Created
 *              The ISO-8601 timestamp marking when Nonce was created.
 *          PasswordDigest
 *              A SHA-1 digest of the Nonce, Created timestamp, and the
 *              password that the user supplies, base64-encoded. In other
 *              words, this should be calculated as:
 *                  base64(sha1(Nonce . Created . Password))
 */

/* PasswordDigest �̐��� */
char    *makePasswordDigest(
            const char *nonce,
            const char *created,
            const char *password,
            int        blogKind );

char    *makeCreated( time_t t );
char    *makeNonce( const char *preNonce, int blogKind );

/* WSSE �̐��� */
char    *makeWSSE( const char *username, const char *password, char *buffer,
                   int blogKind );


/* Atom API �G���h�|�C���g URL ��� */
typedef struct atomApiUrlInfo   {
    char    urlType[MAX_TYPELENGTH];    /* URL �̎�� */
    char    url[MAX_URLLENGTH];         /* URL        */
    char    mimeType[MAX_TYPELENGTH];   /* MIME ���  */
    char    title[MAX_LOGICALLINELEN];  /* ���O       */
}   ATOM_URL_INFO, *ATOM_URL_INFO_t;

/* category ��� */
typedef struct categoryListInfoEx {
    long    numberOfCategories;         /* �J�e�S���̐� */
    char    categoryName[MAX_CATEGORIES][MAX_CATNAMELENGTH];
                                        /* �J�e�S���̖��O (������ OK) */
}   CATLISTINFEX, *CATLISTINFEX_t;


/*
 *  Atom API
 *    �ȉ��� Atom API �֘A�֐��ł́A�����Ƃ��ĕ����R�[�h�� UTF-8 (��������
 *    US-ASCII)�ł��邱�Ƃ�O��ɂ��Ă���
 */

/* Listing the User's Weblogs
 * �w�茏������URL���̎擾
 *    listWeblogsOnAtomAPI
 *      ����:
 *          char          *userName   (I) ���[�U��
 *          char          *password   (I) �p�X���[�h
 *          int           *numOfUrls  (I) �擾����URL���
 *                                    (O) ���ۂɎ擾����URL���
 *          ATOM_URL_INFO *urlInfo    (O) �擾����URL���
 *      �߂�l:
 *          0       �擾���s�A���M���s�A���̑��̃G���[����
 *          1 �ȏ�  �擾�ɐ�������URL���̐�
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) *numOfUrls �Ŏw�肵�����̕������AURL�����擾����
 *          (3) ���ۂɎ擾�ɐ�������URL���̐��� *numOfUrls �ɐݒ肷��
 */
int
listWeblogsOnAtomAPI( const char      *username,
                      const char      *password,
                      long            *numOfUrls,
                      ATOM_URL_INFO_t urlInfo );


/* Listing the Posts in a Weblog
 * �w�茏�����̋L�����̎擾
 *    listPostsOnAtomAPI
 *      ����:
 *          char         *userName      (I) ���[�U��
 *          char         *password      (I) �p�X���[�h
 *          char         *blogID        (I) blog ID
 *          int          *numOfEntries  (I) �擾����L�����
 *                                      (O) ���ۂɎ擾�����L�����
 *          CONTENTINFEX *contentInfo   (O) �擾�����L�����
 *          CATLISTINFEX *categoryInfo  (O) �擾�����J�e�S�����
 *      �߂�l:
 *          0       �L�������݂��Ȃ��A�擾���s�A���M���s�A���̑��̃G���[����
 *          1 �ȏ�  �擾�ɐ�������URL���̐�
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) *numOfEntries �Ŏw�肵�����̕������A�ŐV�̋L������ߋ�������
 *              �k���ċL�������擾����
 *          (3) contentInfo �� categoryInfo �̔z��̑傫���́A���ɁA
 *              *numOfEntries �Ŏw�肵���l�ȏ�ł���K�v������
 *          (4) ���ۂɎ擾�ɐ��������L�����̐��� *numOfEntries �ɐݒ肷��
 *          (5) Atom API �ł̓J�e�S���́u�J�e�S�����v�Ŏ�舵���B�u�J�e�S��
 *              ID�v�Ƃ����T�O�͂Ȃ��̂Œ���(�ȉ��A���� Atom API �֘A�֐���
 *              �����l)
 *          (6) Bloggers.com �̓Ǝ��g���Ƃ��āAconvertLineBreaks(���s�������I
 *              ��<br />�ɕϊ����邩�ۂ�)�̒l���擾�ł���悤�ɂȂ��Ă���B
 *              ���̒l�͖{���A�e�L�����ƂɓƗ��ɐݒ�\�ł���ׂ��ł��邪�A��
 *              ��́A�L�����e���_��(�Ǘ���ʂł�)�ݒ�l���������ɓK�p�����B
 *              �{API�Ŏ擾�ł��� convertLineBreaks �̒l�́A�{API���s���_�̊�
 *              ����ʂ̐ݒ�l�ł���A�e�L���̓��e���_�����̊Ǘ���ʂ̐ݒ�l��
 *              �͂Ȃ����Ƃɒ��ӁB
 *              �Ȃ��ApostEntryOnAtomAPI() �� editEntryOnAtomAPI() �ł�
 *              convertLineBreaks �̒l�𐧌�ł��Ȃ� [�����ł���悤�ɂȂ�?])
 *               �� http://code.blogger.com/archives/atom-docs.html#extensions
 *              * MovableType/TypaPad, libedoor Blog ���ABloggers.com �̊g����
 *                ���������͗l
 */
int
listPostsOnAtomAPI( const char   *username,
                    const char   *password,
                    const char   *blogID,
                    int          *numOfEntries,
                    CONTENTINFEX *contentInfo,
                    CATLISTINFEX *categoryInfo );


/* Retrieving a list of categories
 * �w��blog�Ŏg�p�\�ȃJ�e�S���ꗗ�̎擾
 *    listCategoriesOnAtomAPI
 *      ����:
 *          char       *userName         (I) ���[�U��
 *          char       *password         (I) �p�X���[�h
 *          char       *blogID           (I) blog ID
 *          long       *numOfCategories  (I) �擾����J�e�S�����
 *                                       (O) ���ۂɎ擾�����J�e�S�����
 *          CATLISTINF *categories       (O) �擾�����J�e�S�����
 *      �߂�l:
 *          0       �J�e�S�������݂��Ȃ��A�擾���s�A���M���s�A���̑��̃G���[
 *                  ����
 *          1 �ȏ�  �擾�ɐ��������J�e�S�����̐�
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 *          (2) *numOfCategories�Ŏw�肵�����̕������A�J�e�S�������擾����
 *          (3) ���ۂɎ擾�ɐ��������J�e�S�����̐��� *numOfCategories �ɐ�
 *              �肷��
 */
int
listCategoriesOnAtomAPI(
        const char   *username,
        const char   *password,
        const char   *blogID,
        long         *numOfCategories, /* �J�e�S���̐� */
        CATLISTINF_t categories        /* �J�e�S��     */
    );


/* Posting an entry
 * �L���̓��e
 *    postEntryOnAtomAPI
 *      ����:
 *          char       *userName    (I) ���[�U��
 *          char       *password    (I) �p�X���[�h
 *          char       *blogID      (I) blog ID
 *          char       *title       (I) �薼
 *          char       *summary     (I) �T�v
 *          char       *content     (I) �{��
 *          CATLISTINF *categories  (I) �ݒ肷��J�e�S��
 *          BOOL       publish      (I) ���e��� (FALSE: ������, TRUE: ���J)
 *                                      -- �����_�ł́Ablogger.com �ł̂ݗL��
 *          char       *postID      (O) ���e��̋L��ID
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
 *          (4) �T�v���w�肵�Ă��Ablog �c�[���ɂ���Ă͖��������B
 *          (5) �L���̓��e�ɐ��������ꍇ�ApostID  �̎w������̈�ɋL��ID (��
 *              ����) ���i�[����
 *          (6) ��Ɂu���J�v��Ԃœ��e�����
 *          (7) TypePad �n�ł́Arebuild �����s����܂ŁA�J�e�S�����͔��f��
 *              ��Ȃ�(�ݒ�͂���邪���f�͂���Ȃ�)
 */
int
postEntryOnAtomAPI(
        const char         *username,
        const char         *password,
        const char         *blogID,
        const char         *title,          /* �薼           */
        const char         *summary,        /* �T�v           */
        const char         *content,        /* �{��           */
        const CATLISTINFEX *categoryInfo,   /* �J�e�S��       */
        BOOL               publish,         /* ���e���       */
        char               *postID          /* ���e��̋L��ID */
    );

/* Editing an entry
 * �L���̕ҏW (�����L���̏㏑�����e)
 *    editEntryOnAtomAPI
 *      ����:
 *          char       *userName    (I) ���[�U��
 *          char       *password    (I) �p�X���[�h
 *          char       *blogID      (I) blog ID
 *          char       *title       (I) �薼
 *          char       *summary     (I) �T�v
 *          char       *content     (I) �{��
 *          CATLISTINF *categories  (I) �ݒ肷��J�e�S��
 *          BOOL       publish      (I) ���e��� (FALSE: ������, TRUE: ���J)
 *                                      -- �����_�ł́Ablogger.com �ł̂ݗL��
 *          char       *postID      (I) �ҏW�Ώۂ̋L��ID
 *      �߂�l:
 *          TRUE    �㏑�����e����
 *          FALSE   �㏑�����e���s�A���M���s�A���̑��̃G���[����
 */
int
editEntryOnAtomAPI(
        const char         *username,       // (I) ���[�UID
        const char         *password,       // (I) �p�X���[�h
        const char         *blogID,         // (I) blog ID
        const char         *title,          // (I) �薼
        const char         *summary,        // (I) �T�v
        const char         *content,        // (I) �{��
        const CATLISTINFEX *categoryInfo,   // (I) �ݒ肷��J�e�S��
        BOOL               publish,         // (I) ���e���
        const char         *postID          // (I) �ҏW�Ώۂ̋L��ID
    );

/* Retrieving a Post
 * �w��L���̎擾
 *    getRecentPostOnAtomAPI
 *      ����:
 *          char         *userName      (I) ���[�U��
 *          char         *password      (I) �p�X���[�h
 *          char         *blogID        (I) blog ID
 *          char         *entryID       (I) �L��ID
 *          CONTENTINFEX *contentInfo   (O) �擾�����L�����
 *          CATLISTINFEX *categoryInfo  (O) �擾�����J�e�S�����
 *      �߂�l:
 *          TRUE    �擾����
 *          FALSE   �擾���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 */
BOOL
getRecentPostOnAtomAPI(
        const char   *username,
        const char   *password,
        const char   *blogID,
        const char   *entryID,
        CONTENTINFEX *contentInfo,  /* �L�����     */
        CATLISTINFEX *categoryInfo  /* �J�e�S����� */
    );


/* Deleting a Post
 * �w��L���̍폜
 *    deletePostOnAtomAPI
 *      ����:
 *          char         *userName      (I) ���[�U��
 *          char         *password      (I) �p�X���[�h
 *          char         *blogID        (I) blog ID
 *          char         *entryID       (I) �L��ID
 *      �߂�l:
 *          TRUE    �폜����
 *          FALSE   �폜���s�A���M���s�A���̑��̃G���[����
 *      ���l:
 *          (1) userName ����� password �� NULL �̏ꍇ�A setUserInfo() �Ő�
 *              �肵�����[�U���A�p�X���[�h���g�p����
 */
BOOL
deletePostOnAtomAPI( const char *username,
                     const char *password,
                     const char *blogID,
                     const char *entryID );

/*
 *  ���[�e�B���e�B�֐��Q
 */

/*
 * blog ID �̎擾
 *    ����:   ���[�U��, �p�X���[�h, �擾���� blog ���i�[�ꏊ
 *    �߂�l: �V�X�e�����ɑ��݂��� blog �̐�
 *    ���l:   getBlogIDs() �� Atom API �o�[�W����
 */
int
getBlogIDsOnAtomAPI(
        const char *userName,       // (I) ���[�U��
        const char *password,       // (I) �p�X���[�h
        int        *numberOfBlogs,  // (I/O) blog ���
        BLOGINF    *blogInfo );     // (O) blog ���

/*
 * �w�茏�����̋L�����̎擾
 *    ����:   blog ID, ���[�U��, �p�X���[�h, �擾����L�����,
 *            �擾�����L�����i�[�ꏊ
 *    �߂�l: �擾�����L�����
 *    ���l:   getRecentPostTitles() �� Atom API �o�[�W����
 */
int
getRecentPostTitlesOnAtomAPI(
        const char *blogID,         // (I) blog ID
        const char *userName,       // (I) ���[�U��
        const char *password,       // (I) �p�X���[�h
        int        *numberOfPosts,  // (I/O) �L�����
        POSTINF    *postinf         // (O) �L�����
    );

/*
 * �G���h�|�C���gURL�̎擾
 *    ����:   �g�b�v�y�[�WURL, �擾���� blog ID �̊i�[�ꏊ
 *    �߂�l: �擾�����G���h�|�C���gURL
 *    ���l:   getEndpointURLbyAutoDiscovery() �� Atom API �o�[�W����
 *            �g�b�v�y�[�W�� html head ������
 *               <link rel="alternate" type="application/atom+xml" �c�c
 *            �Ƃ����s������΁A���Y�s�Ŏw�肳��Ă��� Atom Feed �t�@�C����
 *            ���ɁA�G���h�|�C���gURL�����߂�B
 *            ���Y�s�����݂��Ȃ��ꍇ�́A�g�b�v�y�[�W������ atom.xml �Ƃ���
 *            Atom Feed �t�@�C�������݂�����̂Ɖ��肵�Aatom.xml �t�@�C��
 *            ����A�G���h�|�C���gURL�����߂�B
 *            �������A Atom Feed �t�@�C������
 *                <link rel="service.post" type="application/x.atom+xml" �c�c
 *            �Ƃ����s�����݂��Ȃ��ꍇ�́A�G���h�|�C���gURL�̎擾�͂ł��Ȃ��B
 */
char    *
getEndpointURLbyAutoDiscoveryOnAtomAPI(
        const char *topPageURL, // (I) �g�b�v�y�[�W URL
        char       *blogID      // (O) blog ID
    );


/*
 * �ۑ�E���_:
 *   (1) Atom API ���g���ē��e����ꍇ�A�u�{���v�Ɓu�T�v�v�ȊO�̗v�f�A
 *       �u�ǋL�v�A�u�L�[���[�h�v�̎�舵���������܂��Ă��Ȃ��͗l�B
 *       ���������āA�u�ǋL�v��u�L�[���[�h�v���g���ē��e�������ꍇ�́A
 *       ���ʁAXML-RPC API ���g�����ƂƂ���B
 *   (2) Atom API �ł́u�J�e�S���v�̎�舵�������܂������ɂ͌��܂��Ă�
 *       �Ȃ��B�b��I�� TypePad �ł̎����ɏ]�����Ƃɂ���B(livedoor Blog
 *       �� TypePad �ł̎����Ă��̗p���Ă���͗l)
 *   (3) X-WSSE: �Ɋւ��āATypaPad �ł̎����ƁA(BASIC�F�� + SSL �̗p�ȑO
 *       ��) Blogger �ł̎������H������Ă���(���� Nonce �̐������@�A�G��
 *       �R�[�h���@�ɈႢ������)�BTypePad 1.5 �ŁA�]���� TypePad �� WSSE
 *       �� livedoor Blog �� WSSE (= BASIC�F�� + SSL �̗p�ȑO�� Blogger
 *       �� WSSE)�̗������ɑΉ��������߁A�Ȍ�A�{���C�u�����ł��A��҂�
 *       WSSE �œ��ꂷ�邱�Ƃɂ���(2005�N6������)
 *   (4) �R�R���O�ł� Atom API �̎����͒��r���[�ȏ�Ԃł���(�L���̓��e�A
 *       �L���̍폜�A�J�e�S���ꗗ�̎擾�A�L���̎擾�A�L���̕ҏW�͈ꉞ�A
 *       ��ʂ�ł��邪�A�T�[�o������Ԃ��Ă��� XML �������r���ŐK�؂�
 *       �g���{�ɂȂ邱�Ƃ�����ȂǁA��肪�c���Ă���B���݁A�T�[�o����
 *       �Ώ��҂��B
 *   (5) �{���C�u�����́A��Ƃ��āA�R�R���O�� livedoor Blog �œ���m�F��
 *       �s�Ȃ��Ă���B���� blog �c�[���ł͓��얢���؂ł���B
 *   (6) Blogger �� WSSE �F�؂���߁ABASIC�F�� + SSL ���̗p�����B�{���C
 *       �u������2005�N6������ BASIC�F�� + SSL �ɂ�� Atom API �̎��s��
 *       �Ή������BBlogger �œ���m�F�ς݁B
 *   (7) ������V���ȔF�ؕ��@���̗p�����\�������邽�߁A�K�X�A�{���C
 *       �u�����̃A�b�v�f�[�g���s�Ȃ��\��B
 */

#endif  /* __ATOM_API_H__ */
