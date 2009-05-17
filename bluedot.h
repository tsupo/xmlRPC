/*
 *  bludot.h
 *
 * History:
 * $Log: /comm/xmlRPC/bluedot.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 2     07/01/29 20:11 Tsujimura543
 * getNumberOfTagsOnBlueDot() ��ǉ�
 * 
 * 1     06/10/06 21:56 Tsujimura543
 * �V�K�쐬 (del.icio.us �݊� API)
 */

#ifndef __BLUE_DOT_H__
#define __BLUE_DOT_H__

/*
 *  Blue Dot: del.icio.us API
 */

/* ���t�ʓ��e���̈ꗗ�̎擾 */
long
getListOfDatesOnBlueDot(
        const char      *userName,      /* (I) ���[�U��       */
        const char      *password,      /* (I) �p�X���[�h     */
        char            *tag,           /* (I) �^�O           */
        long            *numOfDates,    /* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_DATES *dates          /* (O) �擾�������   */
    );

/* �g���Ă���^�O�̈ꗗ�̎擾 */
long
getListOfTagsOnBlueDot(
        const char     *userName,   /* (I) ���[�U��       */
        const char     *password,   /* (I) �p�X���[�h     */
        long           *numOfTags,  /* (I) �擾������ */
                                    /* (O) �擾������� */
        DELICIOUS_TAGS *tags        /* (O) �擾�������   */
    );

/* �w�肵�����t�ɓ��e�����G���g���̈ꗗ�̎擾 */
long
getListOfPostsOnBlueDot(
        const char      *userName,  /* (I) ���[�U��                   */
        const char      *password,  /* (I) �p�X���[�h                 */
        const char      *tag,       /* (I) �������� (�^�O)            */
        const char      *dateTime,  /* (I) �������� (���e����)        */
                                    /*       yyyy-mm-ddThh:mm:ssZ�`�� */
        const char      *targetUrl, /* (I) �������� (URL)             */
        long            *numOfPosts,/* (I) �擾������             */
                                    /* (O) �擾�������             */
        DELICIOUS_POSTS *posts      /* (O) �擾�������               */
    );

/* �ŋ߂̃G���g���ꗗ�̎擾 */
long
getRecentPostsOnBlueDot(
        const char      *userName,  /* (I) ���[�U��        */
        const char      *password,  /* (I) �p�X���[�h      */
        const char      *tag,       /* (I) �������� (�^�O) */
        long            *numOfPosts,/* (I) �擾������  */
                                    /* (O) �擾�������  */
        DELICIOUS_POSTS *posts      /* (O) �擾�������    */
    );

/* �S�G���g���̎擾 */
long
getAllPostsOnBlueDot(
        const char      *userName,  /* (I) ���[�U��        */
        const char      *password,  /* (I) �p�X���[�h      */
        const char      *tag,       /* (I) �������� (�^�O) */
        long            *numOfPosts,/* (I) �擾������  */
                                    /* (O) �擾�������  */
        DELICIOUS_POSTS *posts      /* (O) �擾�������    */
    );

/* �ŏI�X�V�����̎擾 */
long
getLastUpdateOnBlueDot(
        const char *userName,   /* (I) ���[�U��     */
        const char *password,   /* (I) �p�X���[�h   */
        char       *dateTime    /* (O) �擾������� */
    );

/* �G���g���̓��e(�u�b�N�}�[�N�̒ǉ��o�^) */
BOOL
postEntryOnBlueDot(
    const char      *userName,      /* (I) ���[�U��               */
    const char      *password,      /* (I) �p�X���[�h             */
    DELICIOUS_ENTRY *entry     );   /* (I) �o�^������(���e���e) */


/* �G���g���̍폜 */
BOOL
deleteEntryOnBlueDot(
        const char *userName,   /* (I) ���[�U��                    */
        const char *password,   /* (I) �p�X���[�h                  */
        const char *url         /* (I) �폜����G���g���� URL �v�f */
    );

/* �^�O�̕ύX */
BOOL
renameTagOnBlueDot(
        const char *userName,   /* (I) ���[�U��   */
        const char *password,   /* (I) �p�X���[�h */
        const char *oldTag,     /* (I) �Â��^�O   */
        const char *newTag      /* (I) �V�����^�O */
    );

/*
 *  �ǉ��@�\
 */

/* ���u�b�N�}�[�N���̎擾 */
long
getNumberOfBookmarksOnBlueDot(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    );

/* ���^�O���̎擾 */
long
getNumberOfTagsOnBlueDot(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    );

/* Blue Dot �� login */
int
loginBlueDot(
        const char *userName,   /* (I)   ���[�U��   */
        const char *password,   /* (I)   �p�X���[�h */
        char       *cookie      /* (I/O) �N�b�L�[   */
    );

#endif  /* __BLUE_DOT_H__ */
