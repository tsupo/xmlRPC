/*
 *  deliciousApi.h
 *      del.icio.us API ����� del.icio.us �݊� API (Blue Dot API) ���ʏ���
 *          written by H.Tsujimura  2 May 2005 / 6 Oct 2006
 *
 * History:
 * $Log: /comm/xmlRPC/deliciousApi.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     07/04/16 15:38 Tsujimura543
 * getAllPostsFromDeliciousXML ��ǉ�
 * 
 * 3     07/01/24 15:44 Tsujimura543
 * removeTagOnDeliciousAPI() ��ǉ�
 * 
 * 2     06/10/06 21:45 Tsujimura543
 * �R�����g���C��
 * 
 * 1     06/10/06 21:07 Tsujimura543
 * delicious.c ���� del.icio.us(�݊�)API �����u�b�N�}�[�N�T�[�r�X���ʏ���
 * �𔲂��o���ĕʃt�@�C���Ƃ��ēƗ�������
 */

#ifndef __DELICIOUS_API_H__
#define __DELICIOUS_API_H__

#include "xmlRPC.h"
#include "delicious.h"
#include <time.h>

/*
 *  del.icio.us (�݊�) API ���ʏ���
 */

#ifndef	iskanji1
#define	iskanji1(s) \
    (((((short)s & 0xFF)>=0x81) && (((short)s & 0xFF)<=0x9f)) || \
     ((((short)s & 0xFF)>=0xe0) && (((short)s & 0xFF)<=0xfc)))
#endif

#define MAX_EXTENDED_LENGTH 170


typedef enum deliciousApiType   {
    DAPI_DELICIOUS,     /* del.icio.us */
    DAPI_BLUEDOT,       /* Blue Dot    */
}   DELICIOUS_API_TYPE;


/* �擾�����G���g�����̉�͏���                               */
/*      -- �G���g�������擾����֐��Q����Ăяo����鋤�ʊ֐� */
long
getPostsOnDelicious(
        const char      *url,
        const char      *userName,
        const char      *password,
        long            *numOfPosts,
        DELICIOUS_POSTS *posts 
    );

/*  ���t�ʓ��e���ꗗ�̎擾 */
long
getListOfDatesOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�     */
        const char         *userName,   /* (I) ���[�U��       */
        const char         *password,   /* (I) �p�X���[�h     */
        char               *tag,        /* (I) �^�O           */
        long               *numOfDates, /* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_DATES    *dates       /* (O) �擾�������   */
    );

/*  �^�O�ꗗ�̎擾 */
long
getListOfTagsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�     */
        const char         *userName,   /* (I) ���[�U��       */
        const char         *password,   /* (I) �p�X���[�h     */
        long               *numOfTags,  /* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_TAGS     *tags        /* (O) �擾�������   */
    );

/* �w�肵�����t�ɓ��e�����G���g���̈ꗗ�̎擾 */
long
getListOfPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,    /* (I) API �񋟌�                 */
        const char         *userName,  /* (I) ���[�U��                   */
        const char         *password,  /* (I) �p�X���[�h                 */
        const char         *tag,       /* (I) �������� (�^�O)            */
        const char         *dateTime,  /* (I) �������� (���e����)        */
                                       /*       yyyy-mm-ddThh:mm:ssZ�`�� */
        const char         *targetUrl, /* (I) �������� (URL)             */
        long               *numOfPosts,/* (I) �擾������             */
                                       /* (O) �擾�������             */
        DELICIOUS_POSTS    *posts      /* (O) �擾�������               */
    );

/* �ŋ߂̃G���g���ꗗ�̎擾 */
long
getRecentPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�      */
        const char         *userName,   /* (I) ���[�U��        */
        const char         *password,   /* (I) �p�X���[�h      */
        const char         *tag,        /* (I) �������� (�^�O) */
        long               *numOfPosts, /* (I) �擾������  */
                                        /* (O) �擾�������  */
        DELICIOUS_POSTS    *posts       /* (O) �擾�������    */
    );

/* �ŏI�X�V�����̎擾 */
long
getLastUpdateOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�   */
        const char         *userName,   /* (I) ���[�U��     */
        const char         *password,   /* (I) �p�X���[�h   */
        char               *dateTime    /* (O) �擾������� */
    );

/* �S�G���g���̎擾 */
long
getAllPostsOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�      */
        const char         *userName,   /* (I) ���[�U��        */
        const char         *password,   /* (I) �p�X���[�h      */
        const char         *tag,        /* (I) �������� (�^�O) */
        long               *numOfPosts, /* (I) �擾������  */
                                        /* (O) �擾�������  */
        DELICIOUS_POSTS    *posts       /* (O) �擾�������    */
    );

long
getAllPostsFromDeliciousXML(
        const char      *buf,           /* (I) �擾������  */
        long            *numOfPosts,    /* (I) �擾������  */
                                        /* (O) �擾�������  */
        DELICIOUS_POSTS *posts          /* (O) �擾�������    */
    );

/* �u�b�N�}�[�N�̓��e */
BOOL
postEntryOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�             */
        const char         *userName,   /* (I) ���[�U��               */
        const char         *password,   /* (I) �p�X���[�h             */
        DELICIOUS_ENTRY    *entry       /* (I) �o�^������(���e���e) */
    );

/* �u�b�N�}�[�N�̍폜 */
BOOL
deleteEntryOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�                  */
        const char         *userName,   /* (I) ���[�U��                    */
        const char         *password,   /* (I) �p�X���[�h                  */
        const char         *url         /* (I) �폜����G���g���� URL �v�f */
    );

/* �^�O�̕ύX(�u��) */
BOOL
renameTagOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌� */
        const char         *userName,   /* (I) ���[�U��   */
        const char         *password,   /* (I) �p�X���[�h */
        const char         *oldTag,     /* (I) �Â��^�O   */
        const char         *newTag      /* (I) �V�����^�O */
    );

/* �^�O�̍폜 */
BOOL
removeTagOnDeliciousAPI(
        DELICIOUS_API_TYPE apiType,     /* (I) API �񋟌�     */
        const char         *userName,   /* (I) ���[�U��       */
        const char         *password,   /* (I) �p�X���[�h     */
        const char         *tag         /* (I) �폜�Ώۂ̃^�O */
    );

#endif  /* __DELICIOUS_API_H__ */
