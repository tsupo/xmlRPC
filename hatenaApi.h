/*
 *  hatenaApi.h
 *
 * History:
 * $Log: /comm/xmlRPC/hatenaApi.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 22    08/11/28 10:51 Tsujimura543
 * loginHatenaBookmark() �� DLL �O������Q�Ƃł���悤�ɂ���
 * 
 * 21    08/05/15 22:26 Tsujimura543
 * HATENA_BOOKMARK �\���̂� href �̃T�C�Y��2�{�ɂ���
 * 
 * 20    07/01/29 21:24 Tsujimura543
 * getListOfTagsOnHatena() ��ǉ�
 * 
 * 19    06/11/15 18:37 Tsujimura543
 * getPostsFromHatenaFeed() �̑�1�������u�t�@�C�����v����uFILE *�v�ɕύX
 * 
 * 18    06/11/15 18:15 Tsujimura543
 * �R�����g(getPostsFromHatenaFeed() �̈����̐���)���C��
 * 
 * 17    06/11/15 18:12 Tsujimura543
 * getPostsFromHatenaFeed() �� freePostsFromHatenaFeed() ��ǉ�
 * 
 * 16    06/10/12 19:20 Tsujimura543
 * XML_STATEMENT �̉��s�R�[�h�� \n ���� \r\n �ɕύX
 * 
 * 15    06/04/06 22:13 Tsujimura543
 * postBookmarkWithCollectionOnHatena() ��ǉ�
 * 
 * 14    05/09/26 16:40 Tsujimura543
 * HATENA_BOOKMARK �Ɂu�u�b�N�}�[�N�o�^�����v�̃t�B�[���h��ǉ�
 * 
 * 13    05/08/08 17:57 Tsujimura543
 * loginHatenaBookmark() ��ǉ�
 * 
 * 12    05/07/21 16:04 Tsujimura543
 * �R�����g���C�� (������ǉ�)
 * 
 * 11    05/07/21 15:47 Tsujimura543
 * renameTagFromBookmarksOnHatena(), removeTagFromBookmarksOnHatena(),
 * getNumberOfBookmarksOnHatena() ��ǉ�
 * 
 * 10    05/07/20 20:35 Tsujimura543
 * getBookmarkOnHatenaWithURI() ��ǉ�
 * 
 * 9     05/07/20 20:06 Tsujimura543
 * getRecentPostsOnHatenaUserWith{Tag,Word,Date}() ��ǉ�
 * 
 * 8     05/07/20 19:19 Tsujimura543
 * getRecentPostsOnHatenaUser() ��ǉ�
 * 
 * 7     05/06/09 22:30 Tsujimura543
 * postBookmarkOnHatena() �Ɉ�����1�ǉ�����
 * 
 * 6     05/05/31 19:33 Tsujimura543
 * getBookmarkOnHatena() �Ɉ���(title[�薼])��ǉ�
 * 
 * 5     05/05/30 18:36 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N API �̊e�֐��̈���(���[�U���ƃp�X���[�h)��ǉ�
 * 
 * 4     05/05/30 18:31 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�v�֘A�̒�`�A�錾��ǉ�
 * 
 * 3     04/11/01 21:01 Tsujimura543
 * �x�����x�� 4 �ł� warning ���\�Ȍ��茸�炵�Ă݂�
 * 
 * 2     04/07/07 11:43 Tsujimura543
 */

#ifndef __HATENA_API_H__
#define __HATENA_API_H__

/* charset (code set) */
#define CSET_SHIFTJIS   1
#define CSET_ISO2022JP  2
#define CSET_EUCJP      3
#define CSET_UTF8       4

/* �͂Ăȃ_�C�A���[�L�[���[�h */

#define HATENA_API_URL  "http://d.hatena.ne.jp/images/keyword/keywordlist"
#define CGINAME       "http://www.na.rim.or.jp/~tsupo/program/api/keyword.cgi"

#ifndef XML_STATEMENT
#define XML_STATEMENT   "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
#endif
#define HATENA_ENDPOINT_URL "http://d.hatena.ne.jp/xmlrpc"

char    *decodeString( char *src );
char    *encodeString( const char *src, char *dst );

static void searchKeyword( FILE *fp, FILE *gp, const char *word, int mode );
static void searchKeywordEx( FILE *fp, char *dst, const char *src, int mode );


/* �͂Ăȃu�b�N�}�[�N */
#include "delicious.h"

#define HATENA_B_ENDPOINT_URL "http://b.hatena.ne.jp/atom"

/*
 *  �V�K�u�b�N�}�[�N�̓��e (PostURI �ւ� POST)
 *      POST /atom/post
 *      <entry xmlns="http://purl.org/atom/ns#">
 *          <title>dummy</title>
 *          <link rel="related" type="text/html" href="http://www.example.com/" />
 *          <summary type="text/plain">�T���v���R�����g�ł�</summary>
 *      </entry>
 *
 *      tag ��t������ꍇ�́A�ȉ��̂悤�ɂ���
 *      <entry xmlns="http://purl.org/atom/ns#">
 *          <title>dummy</title>
 *          <link rel="related" type="text/html" href="http://www.example.com/" />
 *          <summary type="text/plain">[tag1][tag2]�c[tagN]�T���v���R�����g�ł�</summary>
 *      </entry>
 *
 *      ��: PostURI �ɂ�铊�e���̓u�b�N�}�[�N�̃^�C�g����ҏW���邱�Ƃ�
 *          �ł��܂���B�^�C�g����link�v�f�Ɏw�肵��URL���玩���擾����
 *          �ݒ肳��܂��B
 */

BOOL
postBookmarkOnHatena(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        const char *href,   /* (I) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        char       *title,  /* (O) �薼                                  */
        const char *summary,/* (I) �R�����g                              */
        const char *tags,   /* (I) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        char       *entryID /* (O) edit�p�G���g��ID                      */
    );

/*
 *  ���e�����u�b�N�}�[�N�̎Q�� (EditURI �ւ� GET)
 *      GET /atom/edit/XXXX
 */

BOOL
getBookmarkOnHatena(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        char       *href,   /* (O) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        char       *title,  /* (O) �薼                                  */
        char       *summary,/* (O) �R�����g                              */
        char       *tags,   /* (O) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        const char *entryID /* (I) edit�p�G���g��ID                      */
    );

BOOL
getBookmarkOnHatenaWithURI(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        const char *href,   /* (I) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        char       *title,  /* (O) �薼                                  */
        char       *summary,/* (O) �R�����g                              */
        char       *tags,   /* (O) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        char       *entryID /* (O) edit�p�G���g��ID                      */
    );

/*
 *  ���e�����u�b�N�}�[�N�̃^�C�g���A�R�����g�̕ύX (EditURI �ւ� PUT)
 *      PUT /atom/edit/XXXX
 *      <entry xmlns="http://purl.org/atom/ns#">
 *          <title>Sample Page</title>
 *          <summary type="text/plain">�T���v���ł��B</summary>
 *      </entry>
 *
 *      tag ��t������ꍇ�́A�ȉ��̂悤�ɂ���
 *      <entry xmlns="http://purl.org/atom/ns#">
 *          <title>Sample Page</title>
 *          <summary type="text/plain">[tag1][tag2]�c[tagN]�T���v���ł��B</summary>
 *      </entry>
 */

BOOL
editBookmarkOnHatena(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        const char *href,   /* (I) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        const char *title,  /* (I) �薼                                  */
        const char *summary,/* (I) �R�����g                              */
        const char *tags,   /* (I) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        const char *entryID /* (I) edit�p�G���g��ID                      */
    );

/*
 *  ���e�����u�b�N�}�[�N�̍폜 (EditURI �ւ� DELETE)
 *      DELETE /atom/edit/XXXX
 */

BOOL
deleteBookmarkOnHatena(
        const char *usrname,/* (I) ���[�U��         */
        const char *passwd, /* (I) �p�X���[�h       */
        const char *entryID /* (I) edit�p�G���g��ID */
    );

/*
 *  �ŋߓ��e�����u�b�N�}�[�N�̈ꗗ�̎擾 (FeedURI �ւ� GET)
 *      GET /atom/feed
 */

typedef struct entryOnHatena    {
    char href[MAX_URLLENGTH * 2];       /* �u�b�N�}�[�N�Ώ� Web �y�[�W URL  */
    char title[MAX_DESCRIPTION_LEN];    /* �薼                             */
    char summary[MAX_DESCRIPTION_LEN];  /* �R�����g                         */
    char tags[MAX_DESCRIPTION_LEN];     /* tag (�󔒋�؂�ŕ����w��\) */
    char entryID[HASH_LENGTH + 1];      /* edit�p�G���g��ID                 */
    int  yyyy;                          /* �u�b�N�}�[�N�o�^����  �N         */
    int  mm;                            /* �u�b�N�}�[�N�o�^����  ��         */
    int  dd;                            /* �u�b�N�}�[�N�o�^����  ��         */
    int  HH;                            /* �u�b�N�}�[�N�o�^����  ��         */
    int  MM;                            /* �u�b�N�}�[�N�o�^����  ��         */
    int  SS;                            /* �u�b�N�}�[�N�o�^����  �b         */
}   HATENA_BOOKMARK;

long
getRecentPostsOnHatena(
        const char      *usrname,       /* (I) ���[�U��                 */
        const char      *passwd,        /* (I) �p�X���[�h               */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐� */
                                        /* (O) �擾�����u�b�N�}�[�N�̐� */
        HATENA_BOOKMARK *posts          /* (O) �擾�����u�b�N�}�[�N     */
    );


/*
 *  �w�胆�[�U�̍ŋߓ��e�����u�b�N�}�[�N�̈ꗗ�̎擾 (REST API)
 */

long
getRecentPostsOnHatenaUser(
        const char      *username,      /* (I) �擾�Ώۃ��[�U��(�͂Ă�ID)   */
        long            offset,         /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        HATENA_BOOKMARK *posts,         /* (O) �擾�����u�b�N�}�[�N         */
        BOOL            *more           /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    );

long
getRecentPostsOnHatenaUserWithTag(
        const char      *username,      /* (I) �擾�Ώۃ��[�U��(�͂Ă�ID)   */
        const char      *tag,           /* (I) �������� (tag)               */
        long            offset,         /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        HATENA_BOOKMARK *posts,         /* (O) �擾�����u�b�N�}�[�N         */
        BOOL            *more           /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    );

long
getRecentPostsOnHatenaUserWithWord(
        const char      *username,      /* (I) �擾�Ώۃ��[�U��(�͂Ă�ID)   */
        const char      *word,          /* (I) �������� (�L�[���[�h)        */
        long            offset,         /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        HATENA_BOOKMARK *posts,         /* (O) �擾�����u�b�N�}�[�N         */
        BOOL            *more           /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    );

long
getRecentPostsOnHatenaUserWithDate(
        const char      *username,      /* (I) �擾�Ώۃ��[�U��(�͂Ă�ID)   */
        const char      *date,          /* (I) �������� (���t,yyyymmdd�`��) */
        long            offset,         /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        HATENA_BOOKMARK *posts,         /* (O) �擾�����u�b�N�}�[�N         */
        BOOL            *more           /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    );


/* �u�b�N�}�[�N�ɕt�����^�O�̈ꊇ�u��
                    (REST API, �͂ĂȂ� login �ς݂̏�Ԃł���K�v����) */
BOOL
renameTagFromBookmarksOnHatena(
        const char *userName,   /* (I) ���[�U��   */
        const char *password,   /* (I) �p�X���[�h */
        const char *oldTag,     /* (I) �Â��^�O   */
        const char *newTag      /* (I) �V�����^�O */
    );          /* �{�֐����Łu�͂Ăȁv�ւ� login ���������s���� */


/* �u�b�N�}�[�N�ɕt�����^�O�̍폜
                    (REST API, �͂ĂȂ� login �ς݂̏�Ԃł���K�v����) */
BOOL
removeTagFromBookmarksOnHatena(
        const char *userName,   /* (I) ���[�U��       */
        const char *password,   /* (I) �p�X���[�h     */
        const char *tag         /* (I) �폜�Ώۂ̃^�O */
    );          /* �{�֐����Łu�͂Ăȁv�ւ� login ���������s���� */

/*
 *  �ǉ��@�\
 */

/* ���u�b�N�}�[�N���̎擾 (FeedURI �ւ� GET �œ���XML����͂��邱�ƂŎ���) */

long
getNumberOfBookmarksOnHatena(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    );

/* �V�K�u�b�N�}�[�N�̓��e + �R���N�V�����ւ̒ǉ� (form �ւ� POST) */
BOOL
postBookmarkWithCollectionOnHatena(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        const char *href,   /* (I) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        char       *title,  /* (O) �薼                                  */
        const char *summary,/* (I) �R�����g                              */
        const char *tags,   /* (I) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        char       *entryID /* (O) edit�p�G���g��ID                      */
    );


/* �͂Ăȃu�b�N�}�[�N���� RSS/Atom�t�B�[�h�`���� export �����t�@�C������ */
/* �G���g������ǂݎ��                                                */
long
getPostsFromHatenaFeed(
    FILE            *fp,        /* (I) (RSS/Atom�t�B�[�h)�t�@�C���X�g���[�� */
    HATENA_BOOKMARK **posts,    /* (O) �擾�����u�b�N�}�[�N                 */
    long            *numOfPosts /* (O) �擾�����u�b�N�}�[�N�̐�             */
  );

/* getPostsFromHatenaFeed() �Ŏ擾�����u�b�N�}�[�N���i�[�̈�̉�� */
void
freePostsFromHatenaFeed( HATENA_BOOKMARK *posts );


/* �^�O�ꗗ�̎擾 */
#ifndef MAX_TAG_LENGTH
typedef struct tagList  {
#define MAX_TAG_LENGTH  512             /* �^�O�ő咷 (�b��l) */
    char    tag[MAX_TAG_LENGTH];        /* tag (����)          */
}   TagList;
#endif  /* MAX_TAG_LENGTH */

int
getListOfTagsOnHatena(
        const char *usrname,    /* (I) ���[�U��         */
        const char *passwd,     /* (I) �p�X���[�h       */
        long       *numOfTags,  /* (I) �擾����^�O�̐� */
                                /* (O) �擾�����^�O�̐� */
        TagList    *lp          /* (O) �^�O�ꗗ         */
    );

//#ifdef  XMLRPC_EXPORTS
/*  �͂Ă�(�u�b�N�}�[�N)�� login */
BOOL
loginHatenaBookmark(
    const char *username,   // (I) �͂Ă�ID (�������̓��[���A�h���X)
    const char *password,   // (I) �p�X���[�h
    char       *cookie );   // (O) �N�b�L�[
//#endif  /* XMLRPC_EXPORTS */

#endif  /* __HATENA_API_H__ */
