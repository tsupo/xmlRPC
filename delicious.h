/*
 *  delicious.h
 *
 *      for del.icio.us API
 *
 * History:
 * $Log: /comm/xmlRPC/delicious.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 13    08/07/25 0:44 Tsujimura543
 * (1) private saving �Ή�
 * (2) hash �� 32�o�C�g����33�o�C�g�ɕύX���ꂽ�̂ɔ����Ή�
 *     (�ő�64�r�b�g�܂őΉ��ł���悤�ɂ��Ă�����)
 * 
 * 12    08/05/16 15:17 Tsujimura543
 * getAllPostsFromDeliciousHTML() ��ǉ�
 * 
 * 11    08/05/15 22:37 Tsujimura543
 * DELICIOUS_POSTS �\���̂� href �̃T�C�Y��2�{�ɂ���
 * 
 * 10    07/01/26 17:57 Tsujimura543
 * getNumberOfTagsOnDelicious() ��ǉ�
 * 
 * 9     07/01/24 15:43 Tsujimura543
 * removeTagOnDelicious() �� loginDelicious() ��ǉ�
 * 
 * 8     06/08/17 11:49 Tsujimura543
 * del.icio.us �� API ����(2006�N8��9��)�ɑΉ�
 * 
 * 7     05/12/01 14:55 Tsujimura543
 * MAX_DESCRIPTION_LEN �̒�`(�l)�𓝈ꂵ�AxmlRPC.h �Ɉړ�
 * 
 * 6     05/06/02 21:59 Tsujimura543
 * ����m�F����
 * 
 * 5     05/06/02 13:55 Tsujimura543
 * getNumberOfBookmarksOnDelicious() ��ǉ�
 * 
 * 4     05/05/27 20:50 Tsujimura543
 * �v���Ɖ����̗���R�����g�ɒǉ�
 * 
 * 3     05/05/26 14:20 Tsujimura543
 * deleteEntryOnDelicious �̃R�����g��ǉ�(�v���Ɖ����̗��ǉ�)
 * 
 * 2     05/05/25 21:38 Tsujimura543
 * �֐��̃v���g�^�C�v�錾�ƍ\���̂̒�`�̋L�q�A����
 * 
 * 1     05/05/24 22:14 Tsujimura543
 * �Ƃ肠�����A�R�����g�̂݋L�q
 */

#ifndef __DELICIOUS_H__
#define __DELICIOUS_H__

/*
 *  �Edel.icio.us API �̎d�l(�ŐV��) �́Ahttp://del.icio.us/doc/api ���Q��
 *  �Edel.icio.us API �� BASIC�F�؂ɂ��F�؂��̗p���Ă���
 *  �EAPI �̘A�����s���s�Ȃ��ꍇ�A���Ȃ��Ƃ�1�b�ȏ�Ԋu���󂯂Ď��s���邱��
 *  �E503 �G���[�ɒ���
 *  �EUser-Agent �̓��e�ɂ���Ă� ban ���邱�Ƃ�����
 */

/*
 *  ���t�ʓ��e���̈ꗗ�̎擾
 *    function: http://del.icio.us/api/posts/dates?
 *          &tag= filter by this tag - optional
 *      returns a list of dates with the number of posts at each date. 
 *      [tag] adds a filter
 *
 *   �� 1)
 *    �v��
 *      http://del.icio.us/api/posts/dates
 *    ����
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <dates tag="" user="tsupo">
 *          <date count="8" date="2005-05-24" /> 
 *          <date count="1" date="2005-05-23" /> 
 *          <date count="11" date="2005-05-22" />
 *           (����)
 *          <date count="51" date="2005-01-18" /> 
 *          <date count="44" date="2005-01-17" /> 
 *          <date count="10" date="2005-01-14" /> 
 *      </dates>
 *
 *   �� 2)
 *    �v��
 *      http://del.icio.us/api/posts/dates?tag=umeda
 *    ����
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <dates tag="umeda" user="tsupo">
 *          <date count="2" date="2005-04-28" /> 
 *          <date count="3" date="2005-04-27" /> 
 *          <date count="2" date="2005-04-12" /> 
 *          <date count="5" date="2005-04-06" /> 
 *          <date count="2" date="2005-03-28" /> 
 *      </dates>
 */

typedef struct datesOnDelicious {
    int     yyyy;   /* ���e�� (�N)        */
    int     mm;     /* ���e�� (��)        */
    int     dd;     /* ���e�� (��)        */
    long    count;  /* ���Y���e���̓��e�� */
}   DELICIOUS_DATES;

long
getListOfDatesOnDelicious(
        const char      *userName,      /* (I) ���[�U��       */
        const char      *password,      /* (I) �p�X���[�h     */
        char            *tag,           /* (I) �^�O           */
        long            *numOfDates,    /* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_DATES *dates          /* (O) �擾�������   */
    );


/*
 *  �g���Ă���^�O�̈ꗗ�̎擾
 *    function: http://del.icio.us/api/tags/get?
 *      returns a list of tags the user has used.
 *
 *   ��)
 *    �v��
 *      http://del.icio.us/api/tags/get
 *    ����
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <tags>
 *          <tag count="12" tag=".NET" /> 
 *          <tag count="1" tag="29man" /> 
 *          <tag count="1" tag="2ch" /> 
 *           (����)
 *          <tag count="1" tag="zipCode" /> 
 *          <tag count="2" tag="zoids" /> 
 *          <tag count="1" tag="zoo" /> 
 *      </tags>
 */

#define MAX_TAG_LEN     128 /* [�b��l] */

typedef struct tagsOnDelicious  {
    char    tag[MAX_TAG_LEN];   /* �^�O                           */
    long    count;              /* ���Y�^�O�t�����ꂽ�G���g���̐� */
}   DELICIOUS_TAGS;

long
getListOfTagsOnDelicious(
        const char     *userName,   /* (I) ���[�U��       */
        const char     *password,   /* (I) �p�X���[�h     */
        long           *numOfTags,  /* (I) �擾������ */
                                    /* (O) �擾������� */
        DELICIOUS_TAGS *tags        /* (O) �擾�������   */
    );


/*
 *  �w�肵�����t�ɓ��e�����G���g���̈ꗗ�̎擾
 *    function: http://del.icio.us/api/posts/get?
 *          &tag= filter by this tag - optional
 *          &dt= filter by this date
 *      returns a list of posts on a given date, filtered by tag. if no 
 *      date is supplied, most recent date will be used
 *
 *   �� 1)
 *    �v��
 *      http://del.icio.us/api/posts/get
 *    ���� (�������w�肵�Ȃ������ꍇ�́A�u�����v(�������͂����΂�Ō�̓��e��)
 *          �̕����Ԃ�)
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <posts dt="2005-05-24" tag="" user="tsupo">
 *          <post href="http://hatena.g.hatena.ne.jp/hatenabookmark/20050524/1116917761"
 *              description="�͂ĂȊe�T�[�r�X�̋@�\�ύX�A���m�点�Ȃ� - �͂Ăȃu�b�N�}�[�N���L - �^�O�@�\�̒ǉ��ɂ���"
 *              extended="�{���A�͂Ăȃu�b�N�}�[�N�Ƀ^�O�@�\��ǉ����܂����B"
 *              hash="dc2662b2b06bdda9584d91fec41443bb"
 *              others="4"
 *              tag="bookmark hatena socialBookmark tag"
 *              time="2005-05-24T09:05:06Z" /> 
 *          <post href="http://kotonoha.main.jp/2005/05/24making-trackback-policy.html"
 *              description="�g���b�N�o�b�N�E�|���V�[����낤�B���[����}�i�[�ɔY�ސl�̂��߂̍쐬�K�C�h [�G���^���Ƃ̂�]2005/05/24"
 *              extended="�u�g���b�N�o�b�N���ꂽ���Ȃ��Ȃ�Ȃ�Ńg���b�N�o�b�N�ł���悤�ɂȂ��Ƃ�˂�I�v�ƃc�b�R���̂��֐��^�̗��V�ł���"
 *              hash="d432e0590e9a6eb83043dd1a009a1f9b"
 *              others="1"
 *              tag="blog policy trackback"
 *              time="2005-05-24T07:50:29Z" /> 
 *          <post href="http://www10.ocn.ne.jp/~fanta-sy/index00.html"
 *              description="�ӂ��񂽂����@����イ�����: �ŋ߂̋��ȏ����āc"
 *              extended="�ӊO�Ɓ@�ǂ��������ȏ����g���Ă��邩�m��Ȃ��l���@�����񂶂�Ȃ����ȂƎv���ďЉ��y�[�W�����܂����B"
 *              hash="64ed15c02124ef2fb58624498bafa386"
 *              others="2"
 *              tag="moe"
 *              time="2005-05-24T01:23:04Z" /> 
 *      </posts>
 *
 *   �� 2)
 *    �v��
 *      http://del.icio.us/api/posts/get?dt=20050521
 *    ����
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <posts dt="20050521" tag="" user="tsupo">
 *          <post href="http://d.hatena.ne.jp/churchill/20050521/p2"
 *              description="�����ɐ��܂�� - ���₤���x�����Ƃ���������"
 *              extended="�����z�����Ă��̂̓R�����g���Ɂu���킢�����ł��ˁB���ӂӁB�v�Ȃ�Ă����R�����g����ꂩ������L�������̂ł��B"
 *              hash="16248f29b98ff8c9d50c50ca6eaa3407"
 *              others="1"
 *              tag="dialy hatena"
 *              time="2005-05-21T18:32:44Z" /> 
 *          <post href="http://www.hotnam.com/news/050521032025.html"
 *              description="�x�g�i���ōL������{�� HENTAI �A�j�� - HOTNAM�I�x�g�i���ŐV���"
 *              extended="��҂�HENTAI�A�j���ɐV���o�����߁A�摜�̔������ɂ̂߂荞�݁A���͂�ÓT�I�ȃA�_���g�r�f�I�ł͍D��S�𖞂����Ȃ��Ȃ��Ă���B"
 *              hash="cc3241e8b5ab81b21ed379d618b2c4b5"
 *              others="2"
 *              tag="HENTAI anime comic vietNam"
 *              time="2005-05-21T18:45:27Z" />
 *      </posts>
 *
 *   �� 3)
 *    �v��
 *      http://del.icio.us/api/posts/get?dt=20050524&tag=moe
 *    ����
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <posts dt="20050524" tag="moe" user="tsupo">
 *          <post href="http://www10.ocn.ne.jp/~fanta-sy/index00.html"
 *              description="�ӂ��񂽂����@����イ�����: �ŋ߂̋��ȏ����āc"
 *              extended="�ӊO�Ɓ@�ǂ��������ȏ����g���Ă��邩�m��Ȃ��l���@�����񂶂�Ȃ����ȂƎv���ďЉ��y�[�W�����܂����B"
 *              hash="64ed15c02124ef2fb58624498bafa386"
 *              others="2"
 *              tag="moe"
 *              time="2005-05-24T01:23:04Z" />
 *      </posts>
 */

#define HASH_LENGTH         64
typedef struct postsOnDelicious {
    char    href[MAX_URLLENGTH * 2];     /* �u�b�N�}�[�N�Ώ�Web�y�[�W URL */
    char    description[MAX_DESCRIPTION_LEN];   /* ���Y Web�y�[�W�� title */
    char    extended[MAX_DESCRIPTION_LEN];      /* �T�v�������̓R�����g   */
    char    hash[HASH_LENGTH + 1];       /* �Q�ƃy�[�WURL�����p�n�b�V���l */
    long    others;      /* �����ȊO�ɓ��YURL���u�b�N�}�[�N���Ă���l�̐� */
    char    tag[MAX_DESCRIPTION_LEN];/* �^�O (�󔒋�؂�ŕ����w��\) */
    char    dateTime[MAX_DATELENGTH];           /* ���e����               */
    BOOL    shared;                             /* ���L(���J)���邩�ۂ�   */
}   DELICIOUS_POSTS;

long
getListOfPostsOnDelicious(
        const char      *userName,  /* (I) ���[�U��                         */
        const char      *password,  /* (I) �p�X���[�h                       */
        const char      *tag,       /* (I) �������� (�^�O)                  */
#ifdef  BEFORE_20060809
        const char      *dateTime,  /* (I) �������� (���e����) yyyymmdd�`�� */
#else
        const char      *dateTime,  /* (I) �������� (���e����)
                                                   yyyy-mm-ddThh:mm:ssZ�`�� */
        const char      *targetUrl, /* (I) �������� (URL)                   */
#endif

        long            *numOfPosts,/* (I) �擾������                   */
                                    /* (O) �擾�������                   */
        DELICIOUS_POSTS *posts      /* (O) �擾�������                     */
    );


/*
 *  �ŋ߂̃G���g���ꗗ�̎擾
 *    function: http://del.icio.us/api/posts/recent?
 *          &tag= filter by this tag - optional
 *          &count= number of items to retrieve - optional (defaults to 15, maximum 100)
 *      returns a list of most recent posts, possibly filtered by tag, maxes out at 100.
 *    ����: 2005�N5��25�����݁Adescription �ɓ��{�ꂪ���݂���ƕ���������
 *          �������錻�ۂ�������
 *    ����: ���� API �Ŏ擾���� post �v�f�ɂ� others �����͊܂܂�Ă��Ȃ�
 */

long
getRecentPostsOnDelicious(
        const char      *userName,  /* (I) ���[�U��        */
        const char      *password,  /* (I) �p�X���[�h      */
        const char      *tag,       /* (I) �������� (�^�O) */
        long            *numOfPosts,/* (I) �擾������  */
                                    /* (O) �擾�������  */
        DELICIOUS_POSTS *posts      /* (O) �擾�������    */
    );


/*
 *  �S�G���g���̎擾
 *    function: http://del.icio.us/api/posts/all
 *          &tag= filter by this tag - optional
 *      returns all posts. use sparingly. call update function first
 *      to see if you need to fetch this at all.
 *    ����: ���� API �Ŏ擾���� post �v�f�ɂ� others �����͊܂܂�Ă��Ȃ�
 */

long
getAllPostsOnDelicious(
        const char      *userName,  /* (I) ���[�U��        */
        const char      *password,  /* (I) �p�X���[�h      */
        const char      *tag,       /* (I) �������� (�^�O) */
        long            *numOfPosts,/* (I) �擾������  */
                                    /* (O) �擾�������  */
        DELICIOUS_POSTS *posts      /* (O) �擾�������    */
    );


/*
 *  �ŏI�X�V�����̎擾
 *    function: http://del.icio.us/api/posts/update
 *      returns the last update time for the user. combine this
 *      with posts/all to see if the data returned has changed
 *      since last fetch. this call is pretty lightweight. don't
 *      call posts/all unless you have to.
 *
 *   ��)
 *    �v��
 *      http://del.icio.us/api/posts/update
 *    ����
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <update time="2005-05-25T11:03:19Z" /> 
 */

long
getLastUpdateOnDelicious(
        const char *userName,   /* (I) ���[�U��     */
        const char *password,   /* (I) �p�X���[�h   */
        char       *dateTime    /* (O) �擾������� */
    );


/*
 *  �G���g���̓��e(�u�b�N�}�[�N�̒ǉ��o�^)
 *    function: http://del.icio.us/api/posts/add?
 *          &url= url for post
 *          &description= description for post
 *          &extended= extended for post
 *          &tags= space-delimited list of tags
 *          &dt= datestamp for post, format "CCYY-MM-DDThh:mm:ssZ"
 *      makes a post to delicious. 
 *      the datestamp requires a LITERAL "T" and "Z" like in ISO8601 at
 *      http://www.cl.cam.ac.uk/~mgk25/iso-time.html. for example:
 *      "1984-09-01T14:21:31Z"
 *   ��)
 *    �v��
 *      http://del.icio.us/api/posts/add?url=http%3A%2F%2Fexample.com%2Fdel.icio.us%2FAPI%2Ftest%2F
 *      &description=%E3%81%93%E3%81%AE%E3%83%96%E3%83%83%E3%82%AF%E3%83%9E%E3%83%BC%E3%82%AF%E3%81%AF%20%64%65%6C%2E%69%63%69%6F%2E%75%73%20%41%50%49%20%E3%82%92%E4%BD%BF%E3%81%A3%E3%81%A6%E3%81%BF%E3%82%8B%E3%83%86%E3%82%B9%E3%83%88%E3%81%A7%E3%81%99%E3%80%82%E7%84%A1%E8%A6%96%E3%81%97%E3%81%A6%E3%81%8F%E3%81%A0%E3%81%95%E3%81%84%E3%80%82
 *      &extended=%E7%8F%BE%E5%9C%A8%E3%80%81%64%65%6C%2E%69%63%69%6F%2E%75%73%20%41%50%49%20%E3%82%AF%E3%83%A9%E3%82%A4%E3%82%A2%E3%83%B3%E3%83%88%E3%81%AE%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%E4%B8%AD%E3%81%A7%E3%81%99%E3%80%82
 *      &tags=%74%65%73%74%20%64%65%62%75%67%20%64%65%6C%2E%69%63%69%6F%2E%75%73%20%41%50%49%20%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%20%E3%83%86%E3%82%B9%E3%83%88%20%E3%83%96%E3%83%83%E3%82%AF%E3%83%9E%E3%83%BC%E3%82%AF
 *      &dt=%32%30%30%35%2D%30%35%2D%32%37%54%30%37%3A%33%34%3A%33%31%5A
 *    ����
 *      <?xml version='1.0' standalone='yes'?>
 *      <result code="done" />
 */

typedef struct entryOnDelicious {
    char    url[MAX_URLLENGTH];          /* �u�b�N�}�[�N�Ώ�Web�y�[�W URL */
    char    description[MAX_DESCRIPTION_LEN];   /* ���Y Web�y�[�W�� title */
    char    extended[MAX_DESCRIPTION_LEN];      /* �T�v�������̓R�����g   */
    char    tag[MAX_DESCRIPTION_LEN];/* �^�O (�󔒋�؂�ŕ����w��\) */
    char    dateTime[MAX_DATELENGTH];           /* ���e����               */
    BOOL    shared;                             /* ���L(���J)���邩�ۂ�   */
}   DELICIOUS_ENTRY;

BOOL
postEntryOnDelicious(
        const char      *userName,  /* (I) ���[�U��               */
        const char      *password,  /* (I) �p�X���[�h             */
        DELICIOUS_ENTRY *entry      /* (I) �o�^������(���e���e) */
    );


/*
 *  �G���g���̍폜
 *    function: http://del.icio.us/api/posts/delete?
 *          &url= url for post
 *      deletes a post from delicious
 *   ��)
 *    �v��
 *       http://del.icio.us/api/posts/delete?url=http%3A%2F%2Fexample.com%2Fdel.icio.us%2FAPI%2Ftest%2F
 *    ����
 *      <?xml version='1.0' standalone='yes'?>
 *      <result code="done" />
 */

BOOL
deleteEntryOnDelicious(
        const char *userName,   /* (I) ���[�U��                    */
        const char *password,   /* (I) �p�X���[�h                  */
        const char *url         /* (I) �폜����G���g���� URL �v�f */
    );


/*
 *  �^�O�̕ύX
 *    function: http://del.icio.us/api/tags/rename?
 *          &old= old tag
 *          &new= new tag
 *      renames a tag
 *
 *   ��)
 *    �v��
 *      http://del.icio.us/api/tags/rename?old=trueworthy&new=trustworthy
 *    ����
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <result>done</result> 
 */

BOOL
renameTagOnDelicious(
        const char *userName,   /* (I) ���[�U��   */
        const char *password,   /* (I) �p�X���[�h */
        const char *oldTag,     /* (I) �Â��^�O   */
        const char *newTag      /* (I) �V�����^�O */
    );


/*
 *  �^�O���ޕ\�̎擾
 *    function: http://del.icio.us/api/tags/bundles/all
 *      retrieves all bundles
 *
 *   ��)
 *    �v��
 *      http://del.icio.us/api/tags/bundles/all
 *    ����
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <bundles>
 *          <bundle name="charactercode" tags="hankaku zenkaku" /> 
 *          <bundle name="fun" tags="aprilFool foods neta pairYoung" /> 
 *          <bundle name="facility" tags="AU DDIpocket IPMO PENCK PHS WindowsCE.NET ZipCode bank business dial-up education farmwareUpdate life mobile money-order patent point send-money softwareFactory symbian telephony" /> 
 *           (����)
 *          <bundle name="BBS" tags="ASCII-NET" /> 
 *          <bundle name="security" tags="XSS cabir phishing secureProgramming system:unfiled virus websense" /> 
 *          <bundle name="wiki" tags="FSWiki JSPWiki MoWiki pukiwiki pyukiwiki wiki" /> 
 *      </bundles>
 */

typedef struct bundlesOnDelicious   {
    char    name[MAX_URLLENGTH];        /* �u���ށv�̖��O URL */
    char    tags[MAX_DESCRIPTION_LEN];  /* ���Y���ނɏ�������^�O (�󔒋�؂�ŕ����w��) */
}   DELICIOUS_BUNDLES;

long
getListOfBundlesOnDelicious(
        const char        *userName,    /* (I) ���[�U��       */
        const char        *password,    /* (I) �p�X���[�h     */
        long              *numOfBundles,/* (I) �擾������ */
                                        /* (O) �擾������� */
        DELICIOUS_BUNDLES *bundles      /* (O) �擾�������   */
    );


/*
 *  �^�O�̕���
 *    function: http://del.icio.us/api/tags/bundles/set
 *          &bundle= bundle name
 *          &tags= space-separated list of tags
 *      assigns a set of tags to a single bundle, wipes away previous settings for bundle
 *   ��)
 *    �v��
 *      http://del.icio.us/api/tags/bundles/set?bundle=culture&tags=vietNam
 *    ���� (������)
 *      <?xml version='1.0' standalone='yes'?>
 *      <result>ok</result>
 *    ���� (�G���[������)
 *      <?xml version="1.0" standalone="yes" ?> 
 *      <result code="something went wrong" />
 *    ����: ���ł� bundle �Ŏw�肵�����O�̕��ނ����݂���ꍇ�͏㏑�������
 *          (���܂ł̕��ނ͏����Ă��܂�)
 */

BOOL
setBundleOnDelicious(
        const char *userName,   /* (I) ���[�U��        */
        const char *password,   /* (I) �p�X���[�h      */
        const char *bundle,     /* (I) �u���ށv�̖��O  */
        const char *tags        /* (I) �^�O (�󔒋�؂�ŕ����w��\) */
    );

/*
 *  ���ނ̍폜
 *    function: http://del.icio.us/api/tags/bundles/delete
 *          &bundle= bundle name
 *      deletes a bundle
 *   ��)
 *    �v��
 *      http://del.icio.us/api/tags/bundles/delete?bundle=testTestTest
 *    ����
 *      <?xml version='1.0' standalone='yes'?>
 *      <result>ok</result>
 */

BOOL
deleteBundleOnDelicious(
        const char *userName,   /* (I) ���[�U��        */
        const char *password,   /* (I) �p�X���[�h      */
        const char *bundle      /* (I) �u���ށv�̖��O  */
    );


/*
 *  �ǉ��@�\
 */

/* ���u�b�N�}�[�N���̎擾 */
long
getNumberOfBookmarksOnDelicious(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    );

/* ���^�O���̎擾 */
long
getNumberOfTagsOnDelicious(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    );

/* �^�O�̍폜 */
BOOL
removeTagOnDelicious(
        const char *userName,   /* (I) ���[�U��       */
        const char *password,   /* (I) �p�X���[�h     */
        const char *tag         /* (I) �폜�Ώۂ̃^�O */
    );

/* del.icio.us �� login */
int
loginDelicious(
        const char *userName,   /* (I)   ���[�U��   */
        const char *password,   /* (I)   �p�X���[�h */
        char       *cookie      /* (I/O) �N�b�L�[   */
    );

/* del.icio.us ����u�b�N�}�[�N���擾 (�X�N���C�s���O��) */
long
getAllPostsFromDeliciousHTML(
        const char      *userName,   /* (I) ���[�U��       */
        const char      *password,   /* (I) �p�X���[�h     */
        long            *numOfPosts, /* (I) �擾������ */
                                     /* (O) �擾������� */
        DELICIOUS_POSTS *posts       /* (O) �擾�������   */
    );

#endif  /* __DELICIOUS_H__ */
