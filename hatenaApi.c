/*
 *  �͂ĂȃL�[���[�h�����N�֘AAPI
 *
 *      Copyright (c) 2004, 2005, 2006, 2007, 2008 by H.Tsujimura
 *      written by H.Tsujimura
 *
 * History:
 * $Log: /comm/xmlRPC/hatenaApi.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 71    09/04/27 19:31 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�v��API�̉����̌`�����ύX���ꂽ�̂ɔ����C��
 * (2009�N4��25���ߕӂɕύX���ꂽ�͗l)
 * 
 * 70    09/01/26 23:36 Tsujimura543
 * �͂Ăȑ��̕s� (http://i.hatena.ne.jp/idea/23100) �ɑ΂���
 * �b��Ώ������{
 * 
 * 69    09/01/08 13:29 Tsujimura543
 * getPostsFromRSS() ���u�͂Ăȃu�b�N�}�[�N2�v�p�ɏC��
 * 
 * 68    08/12/15 17:06 Tsujimura543
 * cookie ����Y��ӏ��A�C��
 * 
 * 67    08/12/01 19:02 Tsujimura543
 * URL �� & ���܂܂��ƁA�u�b�N�}�[�N�̓o�^�Ɏ��s���錻�ۂɑΏ�
 * (���j���[�A����́u�͂Ăȃu�b�N�}�[�N�v�Ŕ�������悤�ɂȂ���)
 * 
 * 66    08/11/28 17:02 Tsujimura543
 * getRecentPostsOnHatenaUser() �̏I���������C��
 * 
 * 65    08/11/28 15:58 Tsujimura543
 * getRecentPostsOnHatenaUser() �̏�񌹎擾�Ώۂ� Atom Feed
 * ���� RSS �ɕύX (�͂Ăȃu�b�N�}�[�N���j���[�A����AAtom Feed
 * �� of �p�����[�^���@�\���Ȃ��Ȃ��Ă��܂�������)
 * 
 * 64    08/11/28 0:52 Tsujimura543
 * ���j���[�A����́u�͂Ăȃu�b�N�}�[�N�v�ł́A�܂��폜�p��API���@�\
 * ���Ă��Ȃ����Ƃ��m�F
 * 
 * 63    08/11/27 22:51 Tsujimura543
 * renameTagFromBookmarksOnHatena() ��
 * removeTagFromBookmarksOnHatena() ��
 * ���j���[�A����́u�͂Ăȃu�b�N�}�[�N�v�p�ɏC������
 * (���A�u�^�O�ꗗ�̎擾�v���ł��Ȃ����߁A
 *    �^�O�ꗗ�擾 �� �u���E�폜�������^�O��I�� �� �u���E�폜���s
 * �Ƃ�������ł̏������ł��Ȃ�)
 * 
 * 62    08/11/27 20:53 Tsujimura543
 * postBookmarkWithCollectionOnHatena() ��2008�N11��25�����j���[�A��
 * ��́u�͂Ăȃu�b�N�}�[�N�v�ɑΉ�������
 * (�^�O�̈ꊇ�u���A�ꊇ�폜�͖��Ή�)
 * 
 * 61    08/11/25 20:03 Tsujimura543
 * getBookmarkOnHatenaWithURI() ���Ŏ擾���� response �̓��e��
 * �\�����Ȃ����̂������Ƃ��ɁA�N���b�V�����邱�Ƃ�����s��ɑΏ�
 * 
 * 60    08/05/20 23:06 Tsujimura543
 * searchKeyword() �� stack overflow ����������̂�\�h���鏈����ǉ�
 * 
 * 59    08/02/08 18:47 Tsujimura543
 * �R�����g���C���A�ǉ�
 * 
 * 58    08/02/08 18:46 Tsujimura543
 * loginHatenaBookmark() ���C�� (���̊Ԃɂ��Alogin form �̃p�����[�^
 * ���ύX����Ă���)
 * 
 * 57    07/09/10 14:59 Tsujimura543
 * �኱���t�@�N�^�����O
 * 
 * 56    07/09/06 17:55 Tsujimura543
 * �u�͂Ăȃu�b�N�}�[�N�v�ւ̓o�^�E�ҏWAPI���s���A�R�����g�A�^�O�̗����Ƃ�
 * ��̏ꍇ��API�̎��s�𒆎~���Ă����̂���߁AAPI�����s����悤�ɂ���
 * 
 * 55    07/06/26 13:24 Tsujimura543
 * changeHatenaKeyword() ���C�����A�͂Ăȃ_�C�A���[�L�[���[�hAPI��
 * ��~���ł�����Ȃ�ɓ����悤�ɂ���
 * 
 * 54    07/03/20 0:19 Tsujimura543
 * �R�����g���C��
 * 
 * 53    07/03/20 0:18 Tsujimura543
 * searchKeywordEx() ���C���B�����R�[�h�ϊ����s�̉\�����l������悤��
 * ����
 * 
 * 52    07/03/05 17:27 Tsujimura543
 * setKeywordLink() ������ɏC��
 * 
 * 51    07/03/05 17:19 Tsujimura543
 * setKeywordLink() ���C��(�o�b�t�@�I�[�o�[�����΍�)
 * [�����ǉ� + tmp, request, response �̊e�̈�̊m�ە��@�C��]
 * 
 * 50    07/03/03 15:18 Tsujimura543
 * sjis2utf() �� NULL ��Ԃ��ꍇ�̑΍�����{
 * 
 * 49    07/02/02 20:55 Tsujimura543
 * getBookmarkOnHatena() �� getBookmarkOnHatenaWithURI() �Ń^�O��
 * �擾�ł��Ȃ��s����C�� (�͂Ăȃu�b�N�}�[�N�̎d�l�ύX�Ή����Y��)
 * 
 * 48    07/01/29 21:24 Tsujimura543
 * getListOfTagsOnHatena() ��ǉ�
 * 
 * 47    06/11/16 1:40 Tsujimura543
 * getPosts() �� getPostsFromRSS() �����t�@�N�^�����O
 * 
 * 46    06/11/15 23:52 Tsujimura543
 * getPostsFromRSS() ���C���A<title>�v�f�̐擪�ɉ��s�����݂���ꍇ�́A
 * ���̉��s���̂Ă�悤�ɂ���
 * 
 * 45    06/11/15 21:35 Tsujimura543
 * getPostsFromHatenaFeed() �̓�����m�F�BgetPosts() �� getPostsFromRSS()
 * �̏����Ɏ��Ԃ������肷���Ă��邽�߁A������������̉ۑ�B
 * 
 * 44    06/11/15 18:37 Tsujimura543
 * getPostsFromHatenaFeed() �̑�1�������u�t�@�C�����v����uFILE *�v�ɕύX
 * 
 * 43    06/11/15 18:15 Tsujimura543
 * �R�����g(getPostsFromHatenaFeed() �̈����̐���)���C��
 * 
 * 42    06/11/15 18:12 Tsujimura543
 * getPostsFromHatenaFeed() �� freePostsFromHatenaFeed() ��ǉ�
 * 
 * 41    06/10/23 16:21 Tsujimura543
 * ��M�o�b�t�@�I�[�o�[�����΍��ǉ�
 * 
 * 40    06/10/18 19:39 Tsujimura543
 * �u�b�N�}�[�N�擾�����Ńo�b�t�@�I�[�o�[��������������\�������邱�Ƃ�
 * ���������̂ŁA�΍�����{
 * 
 * 39    06/09/12 12:30 Tsujimura543
 * editBookmarkOnHatena() �� warning 4100 ��}������
 * 
 * 38    06/09/11 12:00 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 37a   06/09/09 23:04 tsupo
 * �܂��A�A�}�]���� URL �Ƀo���G�[�V���������������߁AgetASIN() ���C��
 * 
 * 37    06/09/04 22:29 Tsujimura543
 * getASIN() ��ǉ�
 * 
 * 36    06/09/04 14:16 Tsujimura543
 * Visual Studio 2005 �ł̃r���h�`�F�b�N���ʂ𔽉f
 * 
 * 35a   06/09/03 20:17 tsupo
 * cookie �܂����C��
 * 
 * 35    06/07/24 22:17 Tsujimura543
 * utf2sjis() ���s���� utf2sjisEx() ���Ăяo���悤�ɂ���
 * 
 * 34    06/07/24 19:21 Tsujimura543
 * getPosts() �ŉ�͒��� XML �� title �v�f�̐擪�����s�̏ꍇ�A
 * ���̉��s���̂Ă�悤�ɂ���
 * 
 * 33    06/07/18 20:44 Tsujimura543
 * &raquo; �΍� (�͂Ăȃu�b�N�}�[�N�̋����ύX�ɔ����C��)
 * 
 * 32    06/07/18 13:51 Tsujimura543
 * �f�o�b�O�p�R�[�h���폜
 * 
 * 31    06/07/11 11:58 Tsujimura543
 * ���łɓo�^�ς݂̃u�b�N�}�[�N�ɑ΂��Ă���� postBookmarkOnHatena()
 * ���悤�Ƃ����ꍇ�A�㏑���o�^����悤�ɂ���
 * 
 * 30    06/04/07 13:30 Tsujimura543
 * postBookmarkWithCollectionOnHatena() ���C��
 * (�R���N�V�����ɒǉ��ł��Ȃ��Ȃ��Ă��܂��Ă���)
 * 
 * 29    06/04/06 22:14 Tsujimura543
 * (1) postBookmarkWithCollectionOnHatena() ��ǉ�
 * (2) loginHatenaBookmark() ��ύX (EUC-JP �� UTF-8�A�Ȃ�)
 * 
 * 28    05/11/30 14:09 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�Ŏg�p�\�ȃ^�O�̐��� 3 ���� 10 �ɕύX���ꂽ�̂�
 * �����C�������{
 * 
 * 27    05/10/28 13:49 Tsujimura543
 * utf2sjis() ���s���̏�������������
 * 
 * 26    05/10/27 21:02 Tsujimura543
 * �擾���� title �� utf2sjis() �����s�����ꍇ�̏�����ǉ�
 * 
 * 25    05/10/18 18:41 Tsujimura543
 * httpPostWithSession() �̈����ǉ��ɔ����C�������{
 * 
 * 24    05/10/18 18:02 Tsujimura543
 * httpGetBufferWithSession() �̈����ǉ��ɔ����C�������{
 * 
 * 23    05/09/27 16:02 Tsujimura543
 * �R�[�h�̐���
 * 
 * 22    05/09/27 15:57 Tsujimura543
 * �͂Ăȃu�b�N�}�[�N�̈ꗗ�擾�n�֐��ŁA�u�b�N�}�[�N�̓o�^������ԋp����
 * �悤�ɏC��(�R�[�h��ǉ�)����
 * 
 * 21    05/08/08 17:57 Tsujimura543
 * renameTagFromBookmarksOnHatena(), removeTagFromBookmarksOnHatena()
 * ��ǉ�
 * 
 * 20    05/07/21 16:45 Tsujimura543
 * getNumberOfBookmarksOnHatena() ��ǉ� (����m�F�ς�)
 * 
 * 19    05/07/20 20:50 Tsujimura543
 * getBookmarkOnHatenaWithURI() ��ǉ�
 * 
 * 18    05/07/20 20:31 Tsujimura543
 * getRecentPostsOnHatenaUserWith{Tag,Word,Date}() ���C��
 * 
 * 17    05/07/20 20:10 Tsujimura543
 * getRecentPostsOnHatenaUserWith{Tag,Word,Date}() ��ǉ�
 * 
 * 16    05/07/20 20:02 Tsujimura543
 * getRecentPostsOnHatenaUser() ��ǉ�
 * 
 * 15    05/07/20 19:02 Tsujimura543
 * getRecentPostsOnHatena() �� tag ���E����悤�ɂ���
 * (�͂Ăȃu�b�N�}�[�N �� 2005�N7��5�����{�� API �g���ɑΉ�) 
 * 
 * 14    05/06/09 22:31 Tsujimura543
 * postBookmarkOnHatena() �Ɉ�����1�ǉ�����
 * 
 * 13    05/06/02 21:59 Tsujimura543
 * ����m�F����
 * 
 * 12    05/06/01 21:13 Tsujimura543
 * getRecentPostsOnHatena() ������
 * 
 * 11    05/06/01 12:11 Tsujimura543
 * deleteBookmarkOnHatena() ������
 * 
 * 10    05/06/01 0:08 Tsujimura543
 * editBookmarkOnHatena() ������
 * 
 * 9     05/05/31 22:25 Tsujimura543
 * getBookmarkOnHatena() ������
 * 
 * 8     05/05/31 19:20 Tsujimura543
 * postBookmarkOnHatena() ������
 * 
 * 7     04/11/15 17:06 Tsujimura543
 * encodeURL() ���Ŋm�ۂ����̈�̉��������ǉ�
 * 
 * 6     04/11/01 21:02 Tsujimura543
 * �x�����x�� 4 �ł� warning ���\�Ȍ��茸�炵�Ă݂�
 * 
 * 5     04/08/31 13:31 Tsujimura543
 * static �ɂł���֐��� static �ɂ���
 * 
 * 4     04/08/31 13:27 Tsujimura543
 * ���I�Ɋm�ۂ����̈�ɂ��āA�O�̂��߁A�m�ے���ɗ̈����NUL�N���A�����
 * ���ɂ���
 * 
 * 3     04/08/31 13:24 Tsujimura543
 * http POST �Ŏg���d���i�[�̈�𓮓I�Ɋm�ۂ���悤�ɕύX
 * 
 * 2     04/07/07 11:56 Tsujimura543
 */

#include "xmlRPC.h"
#include <sys/stat.h>
#ifdef  WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "hatenaApi.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/hatenaApi.c 1     09/05/14 3:46 tsupo $";
#endif


/*
 *  �͂Ăȃ_�C�A���[�L�[���[�h
 */

static int  codeSet = CSET_SHIFTJIS;


static void
skipAnkerCloser( FILE *fp, FILE *gp, const char *t, int mode, int *anker )
{
    char    *p;

    if ( *anker == 1 ) {
        if ( ( p = strchr( t, '>' ) ) != NULL ) {
            for ( ; (t <= p) && t; t++ )
                fputc( *t, gp );
            *anker = 2;
        }
        else {
            fputs( t, gp );
            return;
        }
    }

    if ( *anker == 2 ) {
        p = strstr( t, "</a>" );
        if ( p ) {
            *(p + 3) = '\0';
            fputs( t, gp );
            fputc( '>', gp );
            *anker = 0;
            t = p + 4;
            searchKeyword( fp, gp, t, mode );
        }
        else
            fputs( t, gp );
    }
}

static void
skipAnker( FILE *fp, FILE *gp, const char *t, int mode, int *anker )
{
    char    *p;

    p = strchr( t + 3, '>' );
    if ( p ) {
        char    *q = strstr( p + 1, "</a>" );

        if ( !q )
            q = strstr( p + 1, "</A>" );
        if ( !q ) {
            *anker = 2;
            fputs( t, gp );
            return;
        }
        *(q + 3) = '\0';
        fputs( t, gp );
        fputc( '>', gp );
        t = q + 4;
        searchKeyword( fp, gp, t, mode );
    }
    else {
        *anker = 1;
        fputs( t, stdout );
    }
}

static void
skipInner( FILE *fp, FILE *gp, const char *t, int mode, int *inner )
{
    char    *p;

    if ( ( p = strchr( t, '>' ) ) != NULL ) {
        for ( ; (t <= p) && *t; t++ )
            fputc( *t, gp );
        *inner = 0;
        searchKeyword( fp, gp, t, mode );
    }
    else
        fputs( t, gp );
}

static void
skipTag( FILE *fp, FILE *gp, const char *t, int mode, int *inner )
{
    char    *p;

    p = strchr( t + 2, '>' );
    if ( p ) {
        if ( !strncmpi(t,
            "<META http-equiv=\"Content-Type\" content=\"text/html; charset=",
                       60) ) {
            const char  *q = t + 60;

            if ( !strncmpi( q, "EUC-JP", 6 ) )
                codeSet = CSET_EUCJP;
            else if ( !strncmpi( q, "Shift_JIS", 9 ) )
                codeSet = CSET_SHIFTJIS;
            else if ( !strncmpi( q, "ISO-2022-JP", 11 ) )
                codeSet = CSET_ISO2022JP;
            else if ( !strncmpi( q, "UTF-8", 5 ) )
                codeSet = CSET_UTF8;
        }

        if ( !strncmpi( t, "</head>", 7 ) ) {
            /* �͂ĂȃL�[���[�h�����N�p�X�^�C���V�[�g�𖄂ߍ��� */
            fputs( "<style type=\"text/css\">\n", gp );
            fputs( "a.hatena { color: black;\n"
                   "text-decoration: none;\n"
                   "border-bottom: 1px solid gray;\n}\n", gp );
            fputs( "</style>\n", gp );
        }
        for ( ; (t <= p) && *t; t++ )
            fputc( *t, gp );
        searchKeyword( fp, gp, t, mode );
    }
    else {
        *inner = 1;
        fputs( t, gp );
    }
}

static void
searchKeyword( FILE *fp, FILE *gp, const char *word, int mode )
{
    char        *p, *r, buf[BUFSIZ];
    char        *t = (char *)word;
    size_t      len;
    int         flag  = 1;
    static int  inner = 0;
    static int  anker = 0;
    static int  depth = 0;

    depth++;
    if ( depth >= 100 ) {
        /* stack overflow �h�~ */
        depth--;
        return;
    }

    if ( anker >= 1 ) {
        /* <a ...> �ɑΉ����� </a> ��T�� */
        skipAnkerCloser( fp, gp, t, mode, &anker );
        depth--;
        return;
    }

    if ( inner == 1 ) {
        /* �g<...�h�ɑΉ�����g>�h��T�� */
        skipInner( fp, gp, t, mode, &inner );
        depth--;
        return;
    }

    while ( (*t == ' ') || (*t == '\t') || (*t == '\r') || (*t == '\n') ) {
        fputc( *t, gp );
        t++;
    }

    /* ������̐擪�Ƀ^�O������ꍇ */
    if ( !strncmpi( t, "<a ", 3 ) ) {
        /* <a ...> �` </a> ���L�[���[�h�ϊ��ΏۊO�Ƃ��A���̂܂܏o�� */
        skipAnker( fp, gp, t, mode, &anker );
        depth--;
        return;
    }

    if ( (*t == '<')                                     &&
         ( ((*(t + 1) >= 'a') && (*(t + 1) <= 'z')) ||
           ((*(t + 1) >= 'A') && (*(t + 1) <= 'Z')) ||
           (*(t + 1) == '!')                        ||
           (*(t + 1) == '?')                        ||
           (*(t + 1) == '/')                           )    ) {
        /* �g<...�h�`�g>�h���L�[���[�h�ϊ��ΏۊO�Ƃ��A���̂܂܏o�� */
        skipTag( fp, gp, t, mode, &inner );
        depth--;
        return;
    }

    while ( (*t == ' ') || (*t == '\t') || (*t == '\r') || (*t == '\n') ) {
        fputc( *t, gp );
        t++;
    }
    if ( *t == '\0' ) {
        depth--;
        return;
    }

    /* ������̓r���Ƀ^�O������ꍇ */
    if ( ( p = strchr( t, '<' ) ) != NULL ) {
        if ( ((*(p + 1) >= 'a') && (*(p + 1) <= 'z')) ||
             ((*(p + 1) >= 'A') && (*(p + 1) <= 'Z')) ||
             (*(p + 1) == '!')                        ||
             (*(p + 1) == '?')                        ||
             (*(p + 1) == '/')                           ) {
            /* �^�O�̑O�ɂ��镶�����ϊ� */
            *p = '\0';
            searchKeyword( fp, gp, t, mode );

            /* �^�O���������̂܂܏o�͂�����A����ȍ~�̕������ϊ� */
            *p = '<';
            t = p;
            searchKeyword( fp, gp, t, mode );
            depth--;
            return;
        }
    }

    /* �^�O���܂܂�Ȃ�������̏ꍇ */
    rewind( fp ); /* �L�[���[�h�t�@�C���̐擪�ɖ߂� */
    while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
        /* �L�[���[�h���擾���A�L�[���[�h���������s */
        if ( (*p == '\n') || (*p == '\r') )
            continue;
        len = strlen( p );
        while ( (p[len - 1] == '\n') || (p[len - 1] == '\r') ) {
            p[len - 1] = '\0';
            len--;
        }
        if ( (len == 0) || !(*p) )
            continue;

        if ( ( r = strstr( t, p ) ) != NULL ) {
            /* �����ΏۂɃL�[���[�h���܂܂��ꍇ */
            *r = '\0';
            /* ����}�b�`�������������O�̕����ɂ��L�[���[�h������\���� */
            /* ����̂ŁA�O�̕��������؂�o���ĒT�������s                   */
            if ( t && *t )
                searchKeyword( fp, gp, t, mode );

            /* ���������N���� */
            if ( mode == MODE_HTML )
                fprintf( gp, "<a class=\"hatena\" "
                         "href=\"http://d.hatena.ne.jp/keyword/%s\">%s</a>",
                         encodeURL( p ), p ); /* �����N�𐶐� */
            else
                fprintf( gp, "&lt;a class=\"hatena\" "
                  "href=\"http://d.hatena.ne.jp/keyword/%s\"&gt;%s&lt;/a&gt;",
                         encodeURL( p ), p ); /* �����N�𐶐� */

            /* �����Ώۂ̎c��̕����ɂ��āA����ɒT���𑱂��� */
            t = r + strlen( p );
            searchKeyword( fp, gp, t, mode );
            flag = 0;
            break;
        }
    }

    /* �L�[���[�h��������Ȃ������ꍇ�́A���̂܂܏o�� */
    if ( flag )
        fputs( t, gp );

    /* �̈��� */
    encodeURL( NULL );
    depth--;
}

#if 0
static void
makeAutoLink( FILE *fp, FILE *gp )
{
    char    *p, *q;
    char    buf[BUFSIZ];

    while ( ( p = fgets( buf, BUFSIZ - 1, fp ) ) != NULL ) {
        /* EUC-JP �ɕϊ� */
        if ( codeSet != CSET_EUCJP ) {
            switch ( codeSet ) {
            case CSET_SHIFTJIS:
                q = sjis2euc( p );
                break;
            case CSET_ISO2022JP:
                q = jis2euc( p );
                break;
            case CSET_UTF8:
                q = utf2euc( p );
                break;
            default:
                q = p;
                break;
            }

            if ( !q )
                continue;

            p = q;
        }

        searchKeyword( gp, stdout, p, MODE_HTML );
    }
}
#endif

static void
searchKeywordEx( FILE *fp, char *dst, const char *src, int mode )
{
    char    *p, *q;
    char    buf[BUFSIZ];
    FILE    *gp;
    char    tempfile[MAX_PATH];

    sprintf( tempfile, "%stempTemp.$$$", xmlrpc_p->dataDir );
    if ( ( gp = fopen( tempfile, "w" ) ) != NULL ) {
        /* EUC-JP �ɕϊ� */
        p = (char *)src;
        if ( codeSet != CSET_EUCJP ) {
            switch ( codeSet ) {
            case CSET_SHIFTJIS:
                q = sjis2euc( src );
                break;
            case CSET_ISO2022JP:
                q = jis2euc( src );
                break;
            case CSET_UTF8:
                q = utf2euc( src );
                break;
            default:
                q = (char *)src;
                break;
            }

            if ( q )
                p = q;
        }

        searchKeyword( fp, gp, p, mode );
        fclose( gp );

        dst[0] = '\0';
        if ( ( gp = fopen( tempfile, "r" ) ) != NULL ) {
            while ( ( p = fgets( buf, BUFSIZ - 1, gp ) ) != NULL )
                strcat( dst, p );
            fclose( gp );
        }

        unlink( tempfile );
    }
    else
        strcpy( dst, src );
}



/*
 *  �L�[���[�h�t�@�C�����擾
 */

static char *
getKeywordFilename()
{
    char        *filename = NULL;
    char        *dirname  = NULL;
    static char keywordFilename[MAX_PATH];

    keywordFilename[0] = '\0';
    if ( xmlrpc_p ) {
        if ( xmlrpc_p->dataDir[0] )
            dirname  = xmlrpc_p->dataDir;
        if ( xmlrpc_p->keywordList[0] )
            filename = xmlrpc_p->keywordList; 
    }
    if ( !dirname || !(dirname[0]) )
        dirname  = "./";
    if ( !filename || !(filename[0]) )
        filename = "keyword.lst";
    strcpy( keywordFilename, dirname  );
    strcat( keywordFilename, filename );

    return ( keywordFilename );
}


/*
 *  �L�[���[�h�t�@�C���t�H�[�}�b�g�ϊ�
 */
static int
changeFormat( const char *srcFile, const char *dstFile )
{
    FILE    *fp, *gp;
    char    buf[BUFSIZ];
    char    *p;
    int     ret = 0;

    if ( ( fp = fopen( srcFile, "r" ) ) != NULL ) {
        if ( ( gp = fopen( dstFile, "w" ) ) != NULL ) {
            while ( ( p = fgets( buf, BUFSIZ, fp ) ) != NULL ) {
                if ( (*p == '\r') || (*p == '\n') )
                    break;
            }
            clearerr( fp );
            while ( ( p = fgets( buf, BUFSIZ, fp ) ) != NULL ) {
                while ( *p ) {
                    if ( *p == '\\' ) {
                        p++;
                        if ( !(*p) )
                            break;
                        if ( *p == 's' )
                            fputc( ' ', gp );
                        else if ( !strncmp( p, "&amp\\;", 6 ) ) {
                            p += 5;
                            fputc( '&', gp );
                        }
                        else if ( !strncmp( p, "&gt\\;", 5 ) ) {
                            p += 4;
                            fputc( '>', gp );
                        }
                        else if ( !strncmp( p, "&lt\\;", 5 ) ) {
                            p += 4;
                            fputc( '<', gp );
                        }
                        else
                            fputc( *p, gp );
                    }
                    else if ( *p != '|' )
                        fputc( *p, gp );
                    else {
                        fputc( '\n', gp );
                        ret++;
                    }
                    p++;
                }
            }
            fputc( '\n', gp );
            ret++;
            fclose( gp );
        }

        fclose( fp );
    }

    return ( ret ); /* �L�[���[�h�� */
}



/*
 *  �͂Ăȃ_�C�A���[�L�[���[�h���X�g�擾
 */

int
getHatenaKeywordList()
{
    char        keywordFilename[MAX_PATH];
    char        originalFilename[MAX_PATH];
    int         needToGet = FALSE;
    struct stat s;
    int         ret = 0;

    strcpy( keywordFilename, getKeywordFilename() );
    strcpy( originalFilename, keywordFilename );
    strcat( originalFilename, ".orig" );

    if ( !stat( keywordFilename, &s ) ) {
        time_t  t = time( NULL );
        if ( s.st_mtime < t - 72 * 60 * 60 )
            needToGet = TRUE;
                /* �O��̎擾���� 72���Ԉȏ�o�߂��Ă���ꍇ�̂ݍĎ擾���� */
    }
    else
        needToGet = TRUE;
                /* �t�@�C�������݂��Ȃ��̂ŁA�擾���� */

    if ( needToGet == FALSE )
        return ( ret ); /* ������ �L�[���[�h���X�g�t�@�C�� ���g�p���� */

    /* �L�[���[�h���X�g���擾���� */
    ret = httpGetFile( HATENA_API_URL, originalFilename, TRUE );

    /* �擾�����L�[���[�h���X�g�����ɃL�[���[�h���X�g�t�@�C���𐶐����� */
    changeFormat( originalFilename, keywordFilename );
#ifndef _DEBUG
    unlink( originalFilename );
#endif

    return ( ret );
}


/*
 * �͂Ăȃ_�C�A���[�L�[���[�h�����N�ϊ�
 *    �w�蕶���񒆂̃L�[���[�h���u�͂ĂȃL�[���[�h�v�ɑ��݂��邩�ǂ������ׁA
 *    ���݂���ꍇ�́A�����N�𐶐�����
 *        Copyleft (c) 2004 by H. Tsujimura
 *        written by H. Tsujimura (tsupo@na.rim.or.jp)  05 Feb 2004
 */

char    *
stripScript( const char *src, char *dst )
{
    const char  *p = src;
    char        *q = dst;

    while ( *p ) {
        if ( *p == '<' ) {
            if ( !strncmp( p + 1, "script ", 7 ) ) {
                char    *r;

                p += 8;
                r = strstr( p, "</script>" );
                if ( r ) {
                    p = r + 9;
                    continue;
                }
            }
        }

        *q++ = *p++;
    }
    *q = NUL;

    return ( dst );
}

char    *
changeHatenaKeyword( const char *src, char *dst, int mode )
{
    FILE    *fp;
    char    keywordFilename[MAX_PATH];
    char    *p = (char *)malloc( (src && *src) ? strlen( src ) + 1
                                               : MAX_CONTENT_SIZE  );
    if ( !p )
        return ( NULL );
    stripScript( src, p );

    if ( (mode != MODE_RAW) && (mode != MODE_HTML) )
        mode = MODE_HTML;

    strcpy( keywordFilename, getKeywordFilename() );
    if ( ( fp = fopen( keywordFilename, "r" ) ) == NULL ) {
        getHatenaKeywordList();
        fp = fopen( keywordFilename, "r" );
    }
    if ( fp ) {
        char    *q = decodeURL( p );
        if ( q ) {
            char    *r = (char *)malloc( strlen( q ) + 1 );
            if ( r ) {
                strcpy( r, q );
                searchKeywordEx( fp, dst, r, mode );
                free( r );
            }
        }
        fclose( fp );
    }
    else
        strcpy( dst, p );

    free( p );

    return ( dst );
}


/* �͂Ăȃ_�C�A���[�L�[���[�h���������NAPI  2004.06.15 */
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

char    *
setKeywordLink( const char    *src,
                char          *dst,
                size_t        dstSize,
                int           score,
                unsigned long cname,
                const char    *target,
                const char    *keywordClass )
{
    int     ret = FALSE;
    char    *request;
    char    *response;
    char    *tmp = NULL;
    size_t  sz, len;

    if ( dstSize < strlen( src ) )
        return ( NULL );
    tmp = (char *)malloc( strlen( src ) * 6 + 1 );
    if ( !tmp )
        return ( NULL );
    encodeString( src, tmp );

    len = MAX_CONTENT_SIZE + strlen( tmp );
    request = (char *)malloc( len );
    if ( !request ) {
        free( tmp );
        return ( NULL );
    }
    memset( request, 0x00, len );

    sz = len * 16;
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        free( tmp );
        return ( response );
    }

    setTargetURL( HATENA_ENDPOINT_URL );
    if ( cname == CNAME_GENERAL ) {
	    sprintf( request,
                 XML_STATEMENT
             "<methodCall>\n<methodName>hatena.setKeywordLink</methodName>\n"
             "<params>\n<param>\n<value>\n<struct>\n"
             "<member>\n<name>body</name>\n<value>%s</value>\n</member>\n"
             "<member>\n<name>score</name>\n"
             "<value><i4>%d</i4></value>\n</member>\n"
             "<member>\n<name>a_target</name>\n<value>%s</value>\n</member>\n"
             "<member>\n<name>a_class</name>\n<value>%s</value>\n</member>\n"
             "</struct>\n</value>\n</param>\n</params>\n"
             "</methodCall>\n\n",
                 tmp,
                 score <  0 ?  0 :
                 score > 50 ? 50 :
                              score,
                 target,
                 keywordClass );
    }
    else {
        int len;

	    sprintf( request,
                 XML_STATEMENT
              "<methodCall>\n<methodName>hatena.setKeywordLink</methodName>\n"
              "<params>\n<param>\n<value>\n<struct>\n"
              "<member>\n<name>body</name>\n<value>%s</value>\n</member>\n"
              "<member>\n<name>score</name>\n"
              "<value><i4>%d</i4></value>\n</member>\n",
                 tmp,
                 score <  0 ?  0 :
                 score > 50 ? 50 :
                              score );

        strcat( request,
                "<member>\n<name>cname</name>\n<value>\n<array>\n<data>\n" );

        if ( (cname & CNAME_BOOK)   == CNAME_BOOK ) {
            strcat( request, "<value><string>book</string></value>\n" );
        }
        if ( (cname & CNAME_MUSIC)  == CNAME_MUSIC ) {
            strcat( request, "<value><string>music</string></value>\n" );
        }
        if ( (cname & CNAME_MOVIE)  == CNAME_MOVIE ) {
            strcat( request, "<value><string>movie</string></value>\n" );
        }
        if ( (cname & CNAME_WEB)    == CNAME_WEB ) {
            strcat( request, "<value><string>web</string></value>\n" );
        }
        if ( (cname & CNAME_ELEC)   == CNAME_ELEC ) {
            strcat( request, "<value><string>elec</string></value>\n" );
        }
        if ( (cname & CNAME_ANIMAL) == CNAME_ANIMAL ) {
            strcat( request, "<value><string>animal</string></value>\n" );
        }
        if ( (cname & CNAME_ANIME)  == CNAME_ANIME ) {
            strcat( request, "<value><string>anime</string></value>\n" );
        }
        if ( (cname & CNAME_FOOD)   == CNAME_FOOD ) {
            strcat( request, "<value><string>food</string></value>\n" );
        }
        if ( (cname & CNAME_SPORTS) == CNAME_SPORTS ) {
            strcat( request, "<value><string>sports</string></value>\n" );
        }
        if ( (cname & CNAME_GAME)   == CNAME_GAME ) {
            strcat( request, "<value><string>game</string></value>\n" );
        }
        if ( (cname & CNAME_COMIC)  == CNAME_COMIC ) {
            strcat( request, "<value><string>comic</string></value>\n" );
        }
        if ( (cname & CNAME_HATENA) == CNAME_HATENA ) {
            strcat( request, "<value><string>hatena</string></value>\n" );
        }
        if ( (cname & CNAME_CLUB)   == CNAME_CLUB ) {
            strcat( request, "<value><string>club</string></value>\n" );
        }

        strcat( request,
                "</data>\n</array>\n</value>\n</member>\n" );

        len = strlen( request );
        sprintf( request + len,
             "<member>\n<name>a_target</name>\n<value>%s</value>\n</member>\n"
             "<member>\n<name>a_class</name>\n<value>%s</value>\n</member>\n"
             "</struct>\n</value>\n</param>\n</params>\n"
             "</methodCall>\n\n",
                 target,
                 keywordClass );
    }

    dst[0] = NUL;
    setUpReceiveBuffer( response, sz );
    ret = httpPostEx( request, response );

    if ( (ret == 0) || (*response != NUL) ) {
        /* �ȉ��Ahttp://i.hatena.ne.jp/idea/23100 �̌��̎b��Ώ� */
        /* (�͂Ăȑ��̕s��������B�s�������΁A���̎b�菈�� */
        /* �͕s�v�ɂȂ�)                                         */
        const char  *word =
            "&lt;a class=&quot;hatena&quot; target=&quot;_blank&quot; "
            "href=&quot;http://d.hatena.ne.jp/keyword/&quot;&gt;&lt;/a&gt;";
        char    *p = strstr( response, word );
        if ( p ) {
            int len = strlen(word);
            while ( p ) {
                strcpy( p, p + len );
                p = strstr( response, word );
            }
        }
    }

    if ( (ret == 0) || (*response != NUL) ) {
        char    *p = response;
        char    *q = strstr( p, "<string>" ), *r;

        if ( q ) {
            q += 8;
            r = strstr( q, "</string>" );
            if ( r ) {
                size_t  len = min( dstSize - 1, (size_t)(r - q) );
                strncpy( dst, q, len == dstSize - 1 ? len - 1 : len );
                dst[len] = NUL;
                if ( len == dstSize - 1 ) {
                    char    *p = strrchr( dst, '>' );
                    if ( p )
                        *(p + 1) = NUL;
                }
                decodeString( dst );
            }
        }
    }

    free( response );
    free( request );
    free( tmp );

    return ( dst );
} 


/*
 *  �͂Ăȃu�b�N�}�[�N
 */

/*
 *  getASIN()
 *      URL �Ɋ܂܂�� ASIN �����o��
 *      (amazon, �͂Ă� �� URL ���Ώ�)
 */
static char *
getASIN(
        const char *url,    /* (I) ��͑Ώ� URL */
        char       *asin    /* (O) ASIN ������  */
    )
{
    char    *p, *q;

    asin[0] = NUL;
    p = strstr( url, "/ASIN/" );
    if ( !p )
        p = strstr( url, "/asin/" );    /*�u�͂Ăȁv�̏ꍇ���܂� */
    if ( !p ) {
        p = strstr( url, "/gp/product/" );
        if ( p ) {
            p += 6;
            if ( !strncmp( p + 6, "images/", 7 ) )
                p += 7;
        }
    }
    if ( p )
        p += 6;

    if ( !p && strstr( url, "amazon" ) ) {
        p = strstr( url, "/detail/" );
        if ( p ) {
            /* �C���X�^���g�X�g�A (���̃p�^�[���̏ꍇ�͕K���A���O�� */
            /* associate ID �����݂���)                             */
            if ( (*(p - 1) >= '0') && (*(p - 1) <= '9') )
                p += 8;
            else
                p = NULL;
        }

        if ( !p ) {
            /* �������� (2006�N8��24�����납��o�����n�߂��`��) */
            p = strstr( url, "/dp/" );
            if ( p )
                p += 4;
        }
        if ( !p ) {
            /* 
             *  /tg/�C�ӂ̕�����/-/XXX/ ��
             *  /tg/�C�ӂ̕�����/�C�ӂ̕�����/-/XXX/ �̏ꍇ
             */
            p = strstr( url, "/tg/" );
            q = strstr( url, "/-/"  );
            if ( p && q && (p < q) )
                p = q + 3;
            else
                p = NULL;
        }
    }

    if ( p ) {
        if ( !strncmp( p, "list/", 5 ) )
            p += 5;
        q = strchr( p, '/' );
        if ( q ) {
            strncpy( asin, p, q - p );
            asin[q - p] = NUL;
        }
        else if ( strlen( p ) > 10 ) {
            strncpy( asin, p, 10 );
            asin[10] = NUL;
        }
        else
            strcpy( asin, p );
    }

    return ( asin );
}

static char *
getRkm( char *rkm, const char *htmlSrcCode )
{
    char    *p, *q;

    rkm[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"rkm\" " );
    if ( p ) {
        p = strstr( p, "value=\"" );
        if ( p ) {
            p += 7;
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( rkm, p, q - p );
                rkm[q - p] = NUL;
            }
        }
    }
    else {
        p = strstr( htmlSrcCode, " name=\"rks\" " );
        if ( p ) {
            p = strstr( p, "value=\"" );
            if ( p ) {
                p += 7;
                q = strchr( p, '\"' );
                if ( q ) {
                    strncpy( rkm, p, q - p );
                    rkm[q - p] = NUL;
                }
            }
        }
    }

    return ( rkm );
}

static char *
getEid( char *eid, const char *htmlSrcCode )
{
    char    *p, *q;

    eid[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"eid\" " );
    if ( p ) {
        p = strstr( p, "value=\"" );
        if ( p ) {
            p += 7;
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( eid, p, q - p );
                eid[q - p] = NUL;
            }
        }
    }

    return ( eid );
}

static char *
getHref( char *href, const char *htmlSrcCode )
{
    char    *p, *q;

    href[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"url\" " );
    if ( p ) {
        p = strstr( p, "value=\"" );
        if ( p ) {
            p += 7;
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( href, p, q - p );
                href[q - p] = NUL;
            }
        }
    }

    return ( href );
}

static char *
getTitleText( char *title, const char *htmlSrcCode )
{
    char    *p, *q;

    title[0] = NUL;
    p = strstr( htmlSrcCode, " name=\"title\" " );
    if ( p ) {
        p = strstr( p, "value=\"" );
        if ( p ) {
            p += 7;
            q = strchr( p, '\"' );
            if ( q ) {
                strncpy( title, p, q - p );
                title[q - p] = NUL;
            }
        }
    }

    return ( title );
}


char    *
makeWSSE( const char *username, const char *password, char *buffer,
          int blogKind );

char    *
makeExtended( const char *tags, const char *summary, char *extended )
{
    const char  *p, *q;
    char        temp[MAX_DESCRIPTION_LEN];
    int         len = 0;

    extended[0] = NUL;
    if ( !tags || !(*tags) ) {
        if ( summary && *summary )
            strcpy( extended, summary );
        return ( extended );
    }

    p = tags;
    while ( *p ) {
        q = strchr( p, ' ' );
        if ( q ) {
            strncpy( temp, p, q - p );
            temp[q - p] = NUL;
            sprintf( extended + len, "[%s]", temp );
            p = q + 1;
            len = strlen( extended );
            continue;
        }

        sprintf( extended + len, "[%s]", p );
        break;
    }
    if ( summary && *summary )
        strcat( extended, summary );

    return ( extended );
}

char    *
getSummary( const char *extended, char *tags, char *summary )
{
    const char  *p;
    char        *r;

    *tags    = NUL;
    *summary = NUL;

    p = utf2sjis( extended );
    if ( !p ) {
        strcpy( summary, extended );
        p = utf2sjisEx( summary );
        if ( !p )
            return ( summary );
    }
    if ( *p != '[' ) {
        strcpy( summary, p );
        return ( summary );
    }

    p++;
    r = tags;
    while ( *p ) {
        /* �ۑ�: Shift_JIS �̏ꍇ�A������2�o�C�g�ڂ� '[' �� ']' ������ */
        /*       �ꍇ������A����̃R�[�h�̂܂܂ł͌듮�삷��          */
        while ( *p && (*p != ']') )
            *r++ = *p++;
        if ( (*p == NUL) || (*++p == NUL) )
            break;
        if ( *p != '[' )
            break;

        *r++ = ' ';
        p++;
    }
    *r = NUL;
    if ( p )
        strcpy( summary, p );
    else
        *summary = NUL;

    return ( summary );
}


static long
getPosts(
        const char      *xmlSrc,        /* (I) XML���� (Atom 0.3)       */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐� */
                                        /* (O) �擾�����u�b�N�}�[�N�̐� */
        HATENA_BOOKMARK *posts          /* (O) �擾�����u�b�N�}�[�N     */
    )
{
    const char  *p, *q, *r, *s, *t, *u;
    const char  *base;
    char        temp[MAX_DESCRIPTION_LEN];
    int         cnt;
    long        num = 0;

    /*
     * <?xml version="1.0" encoding="utf-8"?>
     * <feed version="0.3"
     *       xmlns="http://purl.org/atom/ns#"
     *       xml:lang="ja">
     *   <title>tsupo�̃u�b�N�}�[�N</title>
     *   <link rel="alternate" type="text/html" href="http://b.hatena.ne.jp/tsupo/" />
     *   <link rel="service.post" type="application/x.atom+xml" href="http://b.hatena.ne.jp/atom/post" title="tsupo�̃u�b�N�}�[�N" />
     *   <modified>2005-06-01T14:46:30+09:00</modified>
     *   <author>
     *     <name>tsupo</name>
     *   </author>
     *   <id>tag:hatena.ne.jp,2005:bookmark-tsupo</id>
     *   <generator url="http://b.hatena.ne.jp/" version="0.1">Hatena::Bookmark</generator>
     * 
     *   <entry>
     *     <title>�^�C�g���ύX����#003</title>
     *       <link rel="related" type="text/html" href="http://www.asahi.com/national/update/0531/TKY200505310127.html#test2" />
     *     <link rel="alternate" type="text/html" href="http://b.hatena.ne.jp/tsupo/20050601#275963" />
     *     <link rel="service.edit" type="application/x.atom+xml" href="http://b.hatena.ne.jp/atom/edit/275963" title="�^�C�g���ύX����#003" />
     *     <issued>2005-06-01T14:46:30+09:00</issued>
     *     <author>
     *       <name>tsupo</name>
     *     </author>
     *     <id>tag:hatena.ne.jp,2005:bookmark-tsupo-275963</id>
     *     <summary type="text/plain">�͂Ăȃu�b�N�}�[�N�� Atom API �ő��삵�Ă݂�e�X�g�B</summary>
     *   </entry>
     *   �c�c
     * </feed>
     *
     *
     * 2005�N7��5���ȍ~�A<dc:subject> ���g���� tag ��\������悤�ɂȂ���
     *
     * <entry>
     *  <title>Paj&#39;s Home: Cryptography: JavaScript MD5: sha1.js</title>
     *  <link rel="related" type="text/html" href="http://pajhome.org.uk/crypt/md5/sha1src.html" />
     *  <link rel="alternate" type="text/html" href="http://b.hatena.ne.jp/tsupo/20050715#148091" />
     *  <link rel="service.edit" type="application/x.atom+xml" href="http://b.hatena.ne.jp/atom/edit/148091" title="Paj&#39;s Home: Cryptography: JavaScript MD5: sha1.js" />
     *  <issued>2005-07-15T15:23:40+09:00</issued>
     *  <author>
     *   <name>tsupo</name>
     *  </author>
     *  <id>tag:hatena.ne.jp,2005:bookmark-tsupo-148091</id>
     *  <summary type="text/plain">A JavaScript implementation of the Secure Hash Algorithm, SHA-1</summary>
     *  <dc:subject>Javascript</dc:subject>
     *  <dc:subject>SHA-1</dc:subject>
     *  <dc:subject>library</dc:subject>
     * </entry>
     *
     *
     * 2008�N11��25���̃��j���[�A���ŁA�ȉ��̂悤�ȃt�H�[�}�b�g�ɕύX���ꂽ [�^�O��񂪌�������Ȃ�]
     *
     * <entry>
     *  <title>Twitter / mala: ����Ȃ킯�Ń��C�u�h�A�ɂ��܂���</title>
     *  <link type="text/html" rel="related" href="http://twitter.com/bulkneets/status/1026257962"/>
     *  <link type="text/html" rel="alternate" href="http://b.hatena.ne.jp/tsupo/20081127#bookmark-11017126"/>
     *  <link type="application/x.atom+xml" rel="service.edit" title="Twitter / mala: ����Ȃ킯�Ń��C�u�h�A�ɂ��܂���" href="http://b.hatena.ne.jp/atom/edit/11017126"/>
     *  <author>
     *    <name>tsupo</name>
     *  </author>
     *  <summary>20:55 ���s�ό����I���� (mala)</summary>
     *  <id>tag:hatena.ne.jp,2005:bookmark-tsupo-11017126</id>
     *  <issued>2008-11-27T21:57:50</issued>
     * </entry>
     *
     */
    p = xmlSrc;
    while ( ( q = strstr( p, "<entry>" ) ) != NULL ) {
        q += 7;
        u = strstr( p, "</entry>" );
        if ( !u )
            break;
        base = q;

        /* title */
        posts[num].title[0] = NUL;
        r = strstr( base, "<title" );
        if ( r && (r < u) ) {
            r += 6;
            s = strchr( r, '>' );
            if ( s ) {
                s++;
                while ( (*s == '\r') || (*s == '\n') )
                    s++;
                r = strstr( s, "</title>" );
                if ( r ) {
                    strncpy( temp, s, r - s );
                    temp[r - s] = NUL;
                    q = r + 8;
                    s = decodeURL( utf2sjisEx(temp) );
                    strcpy( posts[num].title, s ? s : temp );
                }
            }
        }

        /* href */
        posts[num].href[0] = NUL;
        r = strstr( base, "<link rel=\"related\"" );
        if ( !r ) {
            r = strstr( base, " rel=\"related\" href=\"" );
            if ( r )
                r -= 4;
        }
        if ( r && (r < u) ) {
            r += 19;
            s = strstr( r, "href=\"" );
            if ( s ) {
                s += 6;
                while ( (*s == '\r') || (*s == '\n') )
                    s++;
                r = strchr( s, '"' );
                if ( r ) {
                    strncpy( posts[num].href, s, r - s );
                    posts[num].href[r - s] = NUL;
                    q = r + 1;
                }
            }
        }

        /* entryID */
        posts[num].entryID[0] = NUL;
        r = strstr( base, "<link rel=\"service.edit\"" );
        if ( !r ) {
            r = strstr( base, " rel=\"service.edit\" title=\"" );
            if ( r )
                r += 4;
        }
        if ( r && (r < u) ) {
            r += 24;
            s = strstr( r, "/atom/edit/" );
            if ( !s ) {
                s = strstr( r, "atom/edit/" );
                if ( s )
                    s--;
            }
            if ( s ) {
                s += 11;
                r = strchr( s, '"' );
                if ( r ) {
                    strncpy( posts[num].entryID, s, r - s );
                    posts[num].entryID[r - s] = NUL;
                    q = r + 1;
                }
            }
        }

        /* issued */
        posts[num].yyyy = 0;
        posts[num].mm   = 0;
        posts[num].dd   = 0;
        posts[num].HH   = 0;
        posts[num].MM   = 0;
        posts[num].SS   = 0;
        r = strstr( base, "<issued" );
        if ( r && (r < u) ) {
            r += 7;
            s = strchr( r, '>' );
            if ( s ) {
                s++;
                r = strstr( s, "</issued>" );
                if ( r ) {
                    strncpy( temp, s, r - s );
                    temp[r - s] = NUL;
                    q = r + 9;
                    posts[num].yyyy = atol( temp );
                    posts[num].mm   = ((temp[5] -'0') * 10) + (temp[6] -'0');
                    posts[num].dd   = ((temp[8] -'0') * 10) + (temp[9] -'0');
                    posts[num].HH   = ((temp[11]-'0') * 10) + (temp[12]-'0');
                    posts[num].MM   = ((temp[14]-'0') * 10) + (temp[15]-'0');
                    posts[num].SS   = ((temp[17]-'0') * 10) + (temp[18]-'0');
                }
            }
        }

        /* summary */
        posts[num].summary[0] = NUL;
        r = strstr( base, "<summary" );
        if ( r && (r < u) ) {
            r += 8;
            s = strchr( r, '>' );
            if ( s ) {
                s++;
                while ( (*s == '\r') || (*s == '\n') )
                    s++;
                r = strstr( s, "</summary>" );
                if ( r ) {
                    strncpy( temp, s, r - s );
                    temp[r - s] = NUL;
                    q = r + 10;
                    t = utf2sjisEx(temp);
                    if ( t )
                        strcpy( posts[num].summary, t );
                }
            }
        }

        /* tags */
        posts[num].tags[0] = NUL;
        cnt = 0;
        do {
            r = strstr( base, "<dc:subject>" );
            if ( r && (r < u) ) {
                r += 12;
                s = strstr( r, "</dc:subject>" );
                if ( s ) {
                    strncpy( temp, r, s - r );
                    temp[s - r] = NUL;
                    q = s + 13;
                    t = utf2sjisEx(temp);
                    if ( t ) {
                        if ( cnt > 0 )
                            strcat( posts[num].tags, " " );
                        strcat( posts[num].tags, t );
                    }
                    cnt++;
                }
            }
            else
                break;
        } while ( cnt < 10 );    /* �͂Ăȃu�b�N�}�[�N�ł� tag ��10�܂� */

        num++;
        p = u + 8; /* </entry> */
    }
    *numOfPosts = num;

    return ( num );
}

static long
getPostsFromRSS(
        const char      *xmlSrc,        /* (I) XML���� (RSS 1.0)        */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐� */
                                        /* (O) �擾�����u�b�N�}�[�N�̐� */
        HATENA_BOOKMARK *posts          /* (O) �擾�����u�b�N�}�[�N     */
    )
{
    const char      *p, *q, *r, *s, *t, *u;
    char            temp[MAX_DESCRIPTION_LEN];
    int             cnt;
    long            num = 0;
    HATENA_BOOKMARK *hb;

    p = xmlSrc;
    while ( ( q = strstr( p, "<item rdf:about=\"" ) ) != NULL ) {
        q += 17;
        u = strstr( q, "</item>" );
        if ( !u )
            break;

        hb = &(posts[num]);

        /* href */
        hb->href[0] = NUL;
        r = strstr( q, "\">" );
        if ( r && (r < u) ) {
            strncpy( hb->href, q, r - q );
            hb->href[r - q] = NUL;
            q = r + 2;
            // �u�͂Ăȃu�b�N�}�[�N2�v�ł̓u�b�N�}�[�N�ւ̃����N��
            // �i�[�����悤�ɂȂ���
        }

        /* title */
        hb->title[0] = NUL;
        r = strstr( q, "<title>" );
        if ( r && (r < u) ) {
            r += 7;
            while ( (*r == '\r') || (*r == '\n') )
                r++;
            s = strstr( r, "</title>" );
            if ( s ) {
                strncpy( temp, r, s - r );
                temp[s - r] = NUL;
                q = s + 8;
                s = decodeURL( utf2sjisEx(temp) );
                strcpy( hb->title, s ? s : temp );
            }
        }

        /* link (for �͂Ăȃu�b�N�}�[�N2) */
        r = strstr( q, "<link>" );
        if ( r && (r < u) ) {
            r += 6;
            s = strstr( r, "</link>" );
            if ( s ) {
                strncpy( hb->href, r, s - r );
                hb->href[s - r] = NUL;
                q = s + 7;
            }
        }

        /* entryID (�͂Ăȃu�b�N�}�[�N�� RSS �t�B�[�h�o�[�W�����ɂ� entryID */
        /*          �Ɋւ����񂪊i�[����Ă��Ȃ�)                         */
        hb->entryID[0] = NUL;

        /* summary */
        hb->summary[0] = NUL;
        r = strstr( q, "<description>" );
        if ( r && (r < u) ) {
            r += 13;
            s = strstr( r, "</description>" );
            if ( s ) {
                strncpy( temp, r, s - r );
                temp[s - r] = NUL;
                q = s + 14;
                t = utf2sjisEx(temp);
                if ( t )
                    strcpy( hb->summary, t );
            }
        }

        /* issued */
        hb->yyyy = 0;
        hb->mm   = 0;
        hb->dd   = 0;
        hb->HH   = 0;
        hb->MM   = 0;
        hb->SS   = 0;
        r = strstr( q, "<dc:date>" );
        if ( r && (r < u) ) {
            r += 9;
            s = strstr( r, "</dc:date>" );
            if ( s ) {
                strncpy( temp, r, s - r );
                temp[s - r] = NUL;
                q = s + 10;
                hb->yyyy = atol( temp );
                hb->mm   = ((temp[5] -'0') * 10) + (temp[6] -'0');
                hb->dd   = ((temp[8] -'0') * 10) + (temp[9] -'0');
                hb->HH   = ((temp[11]-'0') * 10) + (temp[12]-'0');
                hb->MM   = ((temp[14]-'0') * 10) + (temp[15]-'0');
                hb->SS   = ((temp[17]-'0') * 10) + (temp[18]-'0');
            }
        }

        /* tags */
        hb->tags[0] = NUL;
        cnt = 0;
        do {
            r = strstr( q, "<dc:subject>" );
            if ( r && (r < u) ) {
                r += 12;
                s = strstr( r, "</dc:subject>" );
                if ( s ) {
                    strncpy( temp, r, s - r );
                    temp[s - r] = NUL;
                    q = s + 13;
                    t = utf2sjisEx(temp);
                    if ( t ) {
                        if ( cnt > 0 )
                            strcat( hb->tags, " " );
                        strcat( hb->tags, t );
                    }
                    cnt++;
                }
            }
            else
                break;
        } while ( cnt < 10 );    /* �͂Ăȃu�b�N�}�[�N�ł� tag ��10�܂� */

        num++;
        p = u + 7; /* </item> */
    }
    *numOfPosts = num;

    return ( num );
}


/* �V�K�u�b�N�}�[�N�̓��e (PostURI �ւ� POST) */

char    *
encodeAmpersand( const char *str )
{
    static char buf[MAX_URLLENGTH * 4];
    const char  *p;
    char        *q;

    p = str;
    q = strchr( p, '&' );
    if ( !q ) {
        strcpy( buf, p );
        return ( buf );
    }

    q = buf;
    while ( *p ) {
        *q++ = *p;
        if ( *p == '&' ) {
            *q++ = 'a';
            *q++ = 'm';
            *q++ = 'p';
            *q++ = ';';
        }
        p++;
    }
    *q = NUL;

    return ( buf );    
}

BOOL
postBookmarkOnHatena(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        const char *href,   /* (I) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        char       *title,  /* (O) �薼                                  */
        const char *summary,/* (I) �R�����g                              */
        const char *tags,   /* (I) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        char       *entryID /* (O) edit�p�G���g��ID                      */
    )
{
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    extended[MAX_DESCRIPTION_LEN * 2];
    char    *request;
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !href || !(*href) || !entryID )
        return ( ret );

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    memset( wsse,    0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/post", HATENA_B_ENDPOINT_URL );
    setTargetURL( url );

    /*
     * <entry xmlns="http://purl.org/atom/ns#">
     *  <title>dummy</title>
     *  <link rel="related" type="text/html" href="http://www.example.com/" />
     *  <summary type="text/plain">[tag1][tag2]�c[tagN]�R�����g</summary>
     * </entry>
     */
    memset( extended, 0x00, MAX_DESCRIPTION_LEN * 2 );
    makeExtended( tags, summary, extended );

    sprintf( request,
             "<entry xmlns=\"http://purl.org/atom/ns#\">\n"
             "<title>dummy</title>\n"
             "<link rel=\"related\" type=\"text/html\" href=\"%s\" />\n",
             encodeAmpersand(href) );
    if ( *extended ) {
        char    *p = sjis2utf(extended);
        sprintf( request + strlen(request),
                 "<summary type=\"text/plain\">%s</summary>\n",
                 encodeAmpersand( p ? p : extended ) );
    }
    sprintf( request + strlen(request),
             "</entry>" );

    setUpReceiveBuffer( response, sz );
    res = httpPostEx2( xmlrpc_p->webServer, xmlrpc_p->webPage,
                       request, response,
                       wsse );

    if ( response[0] != NUL ) {
        char    *p, *q;
        char    newExtended[MAX_DESCRIPTION_LEN * 2];
        BOOL    nesessaryToEdit = TRUE;

        /*
         * <?xml version="1.0" encoding="utf-8"?>
         * <entry xmlns="http://purl.org/atom/ns#">
         *  <title>Example Web Page</title>
         *  <link rel="related" type="text/html" href="http://www.example.com/" />
         *  <link rel="alternate" type="text/html" href="http://b.hatena.ne.jp/tsupo/20050531#275963" />
         *  <link rel="service.edit" type="application/x.atom+xml" href="http://b.hatena.ne.jp/atom/edit/275963" title="Example Web Page" />
         *  <author>
         *   <name>tsupo</name>
         *  </author>
         *  <generator url="http://b.hatena.ne.jp/" version="0.1">Hatena::Bookmark</generator>
         *  <issued>2005-05-31T15:49:07+09:00</issued>
         *  <id>tag:hatena.ne.jp,2005:bookmark-tsupo-275963</id>
         *  <summary type="text/plain">[tag1][tag2]�c[tagN]�R�����g</summary>
         * </entry>
         */
        entryID[0]     = NUL;
        title[0]       = NUL;
        newExtended[0] = NUL;
        p = strstr( response, "<link rel=\"service.edit\"" );
        if ( p ) {
            p += 24;
            q = strstr( p, "/atom/edit/" );
            if ( !q ) {
                q = strstr( p, "atom/edit/" );
                if ( q )
                    q--;
            }
            if ( q ) {
                q += 11;
                p = strchr( q, '"' );
                if ( p ) {
                    strncpy( entryID, q, p - q );
                    entryID[p - q] = NUL;
                    ret = TRUE;
                }
            }

            q = strstr( response, "<title>" );
            if ( q ) {
                char    temp[1024];

                q += 7;
                p = strstr( q, "</title>" );
                strncpy( temp, q, p - q );
                temp[p - q] = NUL;
                p = utf2sjis(temp);
                if ( !p )
                    p = utf2sjisEx(temp);
                if ( p )
                    strcpy( title, p );
            }

            q = strstr( response, "<summary " );
            if ( q ) {
                q += 9;
                p = strchr( q, '>' );
                if ( p ) {
                    p++;
                    q = strstr( p, "</summary>" );
                    if ( q ) {
                        strncpy( newExtended, p, q - p );
                        newExtended[q - p] = NUL;
                        p = sjis2utf( extended );
                        if ( !strcmp( newExtended, p ? p : extended ) )
                            nesessaryToEdit = FALSE;
                    }
                }
            }

            if ( nesessaryToEdit && title[0] && entryID[0] )
                ret = editBookmarkOnHatena( usrname, passwd, href,
                                            /*utf2sjisEx(title)*/ title,
                                            summary, tags, entryID );
        }
    }

    free( response );
    free( request );

    return ( ret );
}


/* ���e�����u�b�N�}�[�N�̎Q�� (EditURI �ւ� GET) */

BOOL
getBookmarkOnHatena(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        char       *href,   /* (O) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        char       *title,  /* (O) �薼                                  */
        char       *summary,/* (O) �R�����g                              */
        char       *tags,   /* (O) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        const char *entryID /* (I) edit�p�G���g��ID                      */
    )
{
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    extended[MAX_DESCRIPTION_LEN * 2];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !entryID || !(*entryID) || !href || !title || !summary || !tags )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/edit/%s", HATENA_B_ENDPOINT_URL, entryID );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     wsse );

    if ( response[0] != NUL ) {
        char    *p, *q;

        /* title   */
        p = strstr( response, "<title" );
        if ( p ) {
            p += 6;
            q = strchr( p, '>' );
            if ( q ) {
                q++;
                p = strchr( q, '<' );
                if ( p ) {
                    char    temp[BUFSIZ];
                    char    *r;

                    strncpy( temp, q, p - q );
                    temp[p - q] = NUL;
                    r = utf2sjis( temp );
                    if ( !r )
                        r = utf2sjisEx( temp );
                    strcpy( title, r ? r : temp );
                    ret = TRUE;
                }
            }
        }

        /* href    */
        p = strstr( response, "<link rel=\"related\"" );
        if ( p ) {
            p += 19;
            q = strstr( p, "href=\"" );
            if ( q ) {
                q += 6;
                p = strchr( q, '"' );
                if ( p ) {
                    strncpy( href, q, p - q );
                    href[p - q] = NUL;
                }
            }
        }

        /* summary */
        p = strstr( response, "<summary" );
        if ( p ) {
            p += 8;
            q = strchr( p, '>' );
            if ( q ) {
                q++;
                p = strchr( q, '<' );
                if ( p ) {
                    strncpy( extended, q, p - q );
                    extended[p - q] = NUL;
                    getSummary( extended, tags, summary );
                }
            }
        }

        /* tags */
        if ( tags[0] == NUL ) {
            char    temp[MAX_DESCRIPTION_LEN];
            char    *s, *t, *u;
            int     cnt = 0;

            do {
                q = strstr( p, "<dc:subject>" );
                u = strstr( p, "</entry>" );
                if ( q && u && (q < u) ) {
                    q += 12;
                    s = strstr( q, "</dc:subject>" );
                    if ( s ) {
                        strncpy( temp, q, s - q );
                        temp[s - q] = NUL;
                        p = s + 13;
                        t = utf2sjisEx(temp);
                        if ( t ) {
                            if ( cnt > 0 )
                                strcat( tags, " " );
                            strcat( tags, t );
                        }
                        cnt++;
                    }
                }
                else
                    break;
            } while ( cnt < 10 ); /* �͂Ăȃu�b�N�}�[�N�ł� tag ��10�܂� */
        }
    }

    free( response );

    return ( ret );
}

BOOL
getBookmarkOnHatenaWithURI(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        const char *href,   /* (I) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        char       *title,  /* (O) �薼                                  */
        char       *summary,/* (O) �R�����g                              */
        char       *tags,   /* (O) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        char       *entryID /* (O) edit�p�G���g��ID                      */
    )
{
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    extended[MAX_DESCRIPTION_LEN * 2];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !href || !(*href) || !href ||
        !title || !summary || !tags || !entryID )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/edit?url=%s", HATENA_B_ENDPOINT_URL, href );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     wsse );

    if ( response[0] != NUL ) {
        char    *p, *q;

        /* title   */
        p = strstr( response, "<title" );
        if ( p ) {
            p += 6;
            q = strchr( p, '>' );
            if ( q ) {
                char    *pp = sjis2utf("�͂Ăȃu�b�N�}�[�N - ");
                size_t  len = strlen(pp);
                q++;
                if ( !strncmp( q, pp, len ) )
                    q += len;
                p = strchr( q, '<' );
                if ( p ) {
                    char    temp[BUFSIZ];
                    char    *r;

                    strncpy( temp, q, p - q );
                    temp[p - q] = NUL;
                    r = utf2sjis( temp );
                    if ( !r )
                        r = utf2sjisEx( temp );
                    strcpy( title, r ? r : temp );
                    ret = TRUE;
                }
            }
        }

        /* id      */
        p = strstr( response, "<id>" );
        if ( p ) {
            p += 4;
            q = strstr( p, "</id>" );
            if ( q ) {
                char    temp[BUFSIZ];

                strncpy( temp, p, q - p );
                temp[q - p] = NUL;
                strcpy( entryID, strrchr( temp, '-' ) + 1 );
                p = q + 5;
            }
        }

        /* summary */
        p = strstr( response, "<summary" );
        if ( p ) {
            p += 8;
            q = strchr( p, '>' );
            if ( q ) {
                q++;
                p = strchr( q, '<' );
                if ( p ) {
                    strncpy( extended, q, p - q );
                    extended[p - q] = NUL;
                    getSummary( extended, tags, summary );
                }
            }
        }

        /* tags */
        if ( tags[0] == NUL ) {
            char    temp[MAX_DESCRIPTION_LEN];
            char    *s, *t, *u;
            int     cnt = 0;

            if ( !p )
                p = response;
            do {
                q = strstr( p, "<dc:subject>" );
                u = strstr( p, "</entry>" );
                if ( q && u && (q < u) ) {
                    q += 12;
                    s = strstr( q, "</dc:subject>" );
                    if ( s ) {
                        strncpy( temp, q, s - q );
                        temp[s - q] = NUL;
                        p = s + 13;
                        t = utf2sjisEx(temp);
                        if ( t ) {
                            if ( cnt > 0 )
                                strcat( tags, " " );
                            strcat( tags, t );
                        }
                        cnt++;
                    }
                }
                else
                    break;
            } while ( cnt < 10 ); /* �͂Ăȃu�b�N�}�[�N�ł� tag ��10�܂� */
        }
    }

    free( response );

    return ( ret );
}



/* ���e�����u�b�N�}�[�N�̃^�C�g���A�R�����g�̕ύX (EditURI �ւ� PUT) */
#ifdef  _MSC_VER
#pragma warning ( disable: 4100 )
#endif
BOOL
editBookmarkOnHatena(
        const char *usrname,/* (I) ���[�U��                              */
        const char *passwd, /* (I) �p�X���[�h                            */
        const char *href,   /* (I) �u�b�N�}�[�N�Ώ� Web �y�[�W URL       */
        const char *title,  /* (I) �薼                                  */
        const char *summary,/* (I) �R�����g                              */
        const char *tags,   /* (I) tag (�󔒕����ŋ�؂��ĕ���tag�w���) */
        const char *entryID /* (I) edit�p�G���g��ID                      */
    )
{
    /* ����: ���� API �ł� href �͕ύX�ł��Ȃ� */
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    extended[MAX_DESCRIPTION_LEN * 2];
    char    *request;
    char    *response;
    char    *p, *q;
    char    tmp1[8], tmp2[8];
    size_t  sz = MAX_CONTENT_SIZE;

    if ( /* !href || !(*href) || */
         !entryID || !(*entryID) ||
         !title   || !(*title)      )
        return ( ret );

    request = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request )
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );
    memset( wsse,    0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/edit/%s", HATENA_B_ENDPOINT_URL, entryID );
    setTargetURL( url );

    /*
     *  <entry xmlns="http://purl.org/atom/ns#">
     *      <title>New Title</title>
     *      <summary type="text/plain">[tag1][tag2]�c[tagN]�R�����g</summary>
     *  </entry>
     */
    memset( extended, 0x00, MAX_DESCRIPTION_LEN * 2 );
    makeExtended( tags, summary, extended );
    strcpy( tmp1, sjis2utf( "��" ) );
    strcpy( tmp2, sjis2utf( "��" ) );
    p = sjis2utf(title);
    while ( ( q = strstr( p, tmp1 ) ) != NULL ) {
        *q       = (unsigned char)0xC2;
        *(q + 1) = (unsigned char)0xBB;
        strcpy( q + 2, q + 3 );
    }
    while ( ( q = strstr( p, tmp2 ) ) != NULL ) {
        *q       = (unsigned char)0xC2;
        *(q + 1) = (unsigned char)0xAB;
        strcpy( q + 2, q + 3 );
    }
    while ( ( q = strstr( p, "&amp;raquo;" ) ) != NULL ) {
        *q       = (unsigned char)0xC2;
        *(q + 1) = (unsigned char)0xBB;
        strcpy( q + 2, q + 11 );
    }
    while ( ( q = strstr( p, "&amp;laquo;" ) ) != NULL ) {
        *q       = (unsigned char)0xC2;
        *(q + 1) = (unsigned char)0xBB;
        strcpy( q + 2, q + 11 );
    }
    sprintf( request,
             "<entry xmlns=\"http://purl.org/atom/ns#\">\n"
             "<title>%s</title>\n",
             p ? p : title );
    if ( *extended ) {
        p = sjis2utf(extended);
        sprintf( request + strlen( request ),
                 "<summary type=\"text/plain\">%s</summary>\n",
                 p ? p : extended );
    }
    sprintf( request + strlen( request ),
             "</entry>" );

    setUpReceiveBuffer( response, sz );
    res = httpPutEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     request, response,
                     wsse );

 /* if ( response[0] != NUL ) */
        ret = TRUE;

    free( response );
    free( request );

    return ( ret );
}
#ifdef  _MSC_VER
#pragma warning ( default: 4100 )
#endif

/* ���e�����u�b�N�}�[�N�̍폜 (EditURI �ւ� DELETE) */

BOOL
deleteBookmarkOnHatena(
        const char *usrname,/* (I) ���[�U��         */
        const char *passwd, /* (I) �p�X���[�h       */
        const char *entryID /* (I) edit�p�G���g��ID */
    )
{
    BOOL    ret = FALSE;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !entryID || !(*entryID) )
        return ( ret );

    response = (char *)malloc( sz );
    if ( !response )
        return ( ret );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/edit/%s", HATENA_B_ENDPOINT_URL, entryID );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpDeleteEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                        response, NULL, FALSE,
                        wsse );
    if ( *response ) {
        if ( !strstr( response, "403 Forbidden" ) )
            ret = TRUE;
    }

    free( response );

    return ( ret );
}


/* �ŋߓ��e�����u�b�N�}�[�N�̈ꗗ�̎擾 (FeedURI �ւ� GET) */

long
getRecentPostsOnHatena(
        const char      *usrname,       /* (I) ���[�U��                 */
        const char      *passwd,        /* (I) �p�X���[�h               */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐� */
                                        /* (O) �擾�����u�b�N�}�[�N�̐� */
        HATENA_BOOKMARK *posts          /* (O) �擾�����u�b�N�}�[�N     */
    )
{
    long    num = 0;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts || (*numOfPosts <= 0) || !posts )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( usrname, passwd, wsse, xmlrpc_p->blogKind );
    response[0] = NUL;

    sprintf( url, "%s/feed", HATENA_B_ENDPOINT_URL );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     wsse );

    if ( response[0] != NUL )
        num = getPosts( response, numOfPosts, posts );

    free( response );

    return ( num );
}


/* �w�胆�[�U�̍ŋߓ��e�����u�b�N�}�[�N�̈ꗗ�̎擾 (REST API) */
long
getRecentPostsOnHatenaUser(
        const char      *username,      /* (I) �擾�Ώۃ��[�U��(�͂Ă�ID)   */
        long            offset,         /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        HATENA_BOOKMARK *posts,         /* (O) �擾�����u�b�N�}�[�N         */
        BOOL            *more           /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         (offset < 0) || !more )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;

#ifdef  USE_ATOMFEED
    sprintf( url, "http://b.hatena.ne.jp/%s/atomfeed?of=%d",
             username, offset );
#else
    sprintf( url, "http://b.hatena.ne.jp/%s/rss?of=%d",
             username, offset );
#endif
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     NULL );

    if ( response[0] != NUL ) {
        const char  *p = response;

#ifdef  USE_ATOMFEED
        if (strstr(p, "<link rel=\"next\" type=\"application/atom+xml\""  )||
            strstr(p, "<link rel=\"next\" type=\"application/x.atom+xml\"")  )
            *more = TRUE;
        else
            *more = FALSE;

        num = getPosts( response, numOfPosts, posts );
#else
        /*
         * <opensearch:startIndex>401</opensearch:startIndex> 
         * <opensearch:itemsPerPage>20</opensearch:itemsPerPage> 
         * <opensearch:totalResults>13556</opensearch:totalResults> 
         */

        int     startIndex   = 0;
        int     itemsPerPage = 0;
        int     totalResults = 0;
        char    *q;

        q = strstr( p, "<opensearch:startIndex>" );
        if ( q )
            startIndex = atol( q + 23 );
        q = strstr( p, "<opensearch:itemsPerPage>" );
        if ( q )
            itemsPerPage = atol( q + 25 );
        q = strstr( p, "<opensearch:totalResults>" );
        if ( q )
            totalResults = atol( q + 25 );

        *more = FALSE;
        if ( totalResults > 0 ) {
            int rest = totalResults - startIndex;
            if ( rest > itemsPerPage )
                *more = TRUE;
        }

        num = getPostsFromRSS( response, numOfPosts, posts );
#endif
    }

    free( response );

    return ( num );
}

long
getRecentPostsOnHatenaUserWithTag(
        const char      *username,      /* (I) �擾�Ώۃ��[�U��(�͂Ă�ID)   */
        const char      *tag,           /* (I) �������� (tag)               */
        long            offset,         /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        HATENA_BOOKMARK *posts,         /* (O) �擾�����u�b�N�}�[�N         */
        BOOL            *more           /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    char    *target;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         !tag         || !(*tag)            ||
         (offset < 0) || !more )
        return ( num );

    target = sjis2utf( tag );
    if ( !target )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;

    sprintf( url, "http://b.hatena.ne.jp/%s/atomfeed?tag=%s&of=%d",
             username, target, offset );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     NULL );

    if ( response[0] != NUL ) {
        char    *p;

        p = response;
        if ( strstr( p, "<link rel=\"next\" type=\"application/atom+xml\"" ) )
            *more = TRUE;
        else
            *more = FALSE;

        num = getPosts( response, numOfPosts, posts );
    }

    free( response );

    return ( num );
}

long
getRecentPostsOnHatenaUserWithWord(
        const char      *username,      /* (I) �擾�Ώۃ��[�U��(�͂Ă�ID)   */
        const char      *word,          /* (I) �������� (�L�[���[�h)        */
        long            offset,         /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        HATENA_BOOKMARK *posts,         /* (O) �擾�����u�b�N�}�[�N         */
        BOOL            *more           /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    char    *target;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         !word        || !(*word)           ||
         (offset < 0) || !more )
        return ( num );

    target = sjis2utf( word );
    if ( !target )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;

    sprintf( url, "http://b.hatena.ne.jp/%s/atomfeed?word=%s&of=%d",
             username, target, offset );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     NULL );

    if ( response[0] != NUL ) {
        char    *p;

        p = response;
        if ( strstr( p, "<link rel=\"next\" type=\"application/atom+xml\"" ) )
            *more = TRUE;
        else
            *more = FALSE;

        num = getPosts( response, numOfPosts, posts );
    }

    free( response );

    return ( num );
}

long
getRecentPostsOnHatenaUserWithDate(
        const char      *username,      /* (I) �擾�Ώۃ��[�U��(�͂Ă�ID)   */
        const char      *date,          /* (I) �������� (���t,yyyymmdd�`��) */
        long            offset,         /* (I) �擾�J�n�u�b�N�}�[�N�ʒu     */
        long            *numOfPosts,    /* (I) �擾����u�b�N�}�[�N�̐�     */
                                        /* (O) �擾�����u�b�N�}�[�N�̐�     */
        HATENA_BOOKMARK *posts,         /* (O) �擾�����u�b�N�}�[�N         */
        BOOL            *more           /* (O) �擾�\�c���u�b�N�}�[�N�L�� */
    )
{
    long    num = 0;
    int     res;
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    if ( !numOfPosts  || (*numOfPosts <= 0) || !posts ||
         !date        || !(*date)           ||
         (offset < 0) || !more )
        return ( num );

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;

    sprintf( url, "http://b.hatena.ne.jp/%s/atomfeed?date=%s&of=%d",
             username, date, offset );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     NULL );

    if ( response[0] != NUL ) {
        char    *p;

        p = response;
#if 0
        if ( strstr( p, "<link rel=\"next\" type=\"application/atom+xml\"" ) )
            *more = TRUE;
        else
            *more = FALSE;
#else
        *more = FALSE;
#endif

        num = getPosts( response, numOfPosts, posts );
    }

    free( response );

    return ( num );
}


/* �u�b�N�}�[�N�ɕt�����^�O�̈ꊇ�u��
                    (REST API, �͂ĂȂ� login �ς݂̏�Ԃł���K�v����) */
BOOL
renameTagFromBookmarksOnHatena(
        const char *userName,   /* (I) ���[�U��   */
        const char *password,   /* (I) �p�X���[�h */
        const char *oldTag,     /* (I) �Â��^�O   */
        const char *newTag      /* (I) �V�����^�O */
    )
{
    BOOL    ret = FALSE;
    char    *cookie;
    char    *s;
    char    _oldTag[BUFSIZ];
    char    _newTag[BUFSIZ];

    if ( !oldTag || !(*oldTag) || !newTag || !(*newTag) )
        return ( ret );

    s = sjis2utf(oldTag);
    if ( !s )
        return ( ret );
    strcpy( _oldTag, encodeURL(s) );

    s = sjis2utf(newTag);
    if ( !s )
        return ( ret );
    strcpy( _newTag, encodeURL(s) );

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( ret );
    memset( cookie,  0x00, MAX_COOKIE_LEN );

    /* �͂ĂȂ� login */
    ret = loginHatenaBookmark( userName, password, cookie );
    if ( ret ) {
        char    *request;
        char    *response;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_CONTENT_SIZE * 4;

        ret = FALSE;

        request  = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request ) {
            free( cookie );
            return ( ret );
        }
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            free( cookie );
            return ( ret );
        }
        memset( request, 0x00, MAX_CONTENT_SIZE );

#ifdef  BEFORE_20081125
        /* http://b.hatena.ne.jp/���[�U��/�Â��^�O/?mode=edit ���擾 */
        sprintf( url, "http://b.hatena.ne.jp/%s/%s/?mode=edit",
                 userName, _oldTag );
#else
        /* http://b.hatena.ne.jp/���[�U��/tag?tag=�Â��^�O ���擾 */
        sprintf( url, "http://b.hatena.ne.jp/%s/tag?tag=%s",
                 userName, _oldTag );
#endif
        setUpReceiveBuffer( response, sz );
        httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
                                  NULL, NULL );

        if ( *response ) {
            char    rkm[MAX_KEYLENGTH];

            /* rkm �̒l���擾 */
            getRkm( rkm, response );

#ifdef  BEFORE_20081125
            /* �ꊇ�u�������s(http://b.hatena.ne.jp/���[�U��/�^�O/ �� POST) */
            sprintf( url, "http://b.hatena.ne.jp/%s/%s/", userName, _oldTag );
            setTargetURL( url );
            sprintf( request,
                     "mode=editenter&"
                     "rkm=%s&"
                     "oldtag=%s&"
                     "newtag=%s",
                     encodeURL(rkm), _oldTag, _newTag );
#else
            /* �ꊇ�u�������s                                         */
            /*      (http://b.hatena.ne.jp/���[�U��/tag.edit �� POST) */
            sprintf( url, "http://b.hatena.ne.jp/%s/tag.edit", userName );
            setTargetURL( url );
            sprintf( request,
                     "rks=%s&"
                     "tag=%s&"
                     "newtag=%s",
                     encodeURL(rkm), _oldTag, _newTag );
#endif
            setUpReceiveBuffer( response, sz );
            httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                                 "application/x-www-form-urlencoded",
                                 request, response, cookie,
                                 NULL, NULL );

            if ( *response ) {
                char    *p;

#ifdef  BEFORE_20081125
                p = strstr( response, "name=\"oldtag\" value=\"" );
#else
                p = strstr( response, "name=\"tag\" value=\"" );
#endif
                if ( p ) {
#ifdef  BEFORE_20081125
                    p += 21;
#else
                    p += 18;
#endif
                    if ( !strncmp( p, _newTag, strlen(_newTag) ) &&
                         (p[strlen(_newTag)] == '"' )               )
                        ret = TRUE;
                }
            }
        }

        free( response );
        free( request );
    }

    free( cookie );

    return ( ret );
}


/* �u�b�N�}�[�N�ɕt�����^�O�̍폜
                    (REST API, �͂ĂȂ� login �ς݂̏�Ԃł���K�v����) */
BOOL
removeTagFromBookmarksOnHatena(
        const char *userName,   /* (I) ���[�U��       */
        const char *password,   /* (I) �p�X���[�h     */
        const char *tag         /* (I) �폜�Ώۂ̃^�O */
    )
{
    BOOL    ret = FALSE;
    char    *cookie;
    char    *s;
    char    _tag[BUFSIZ];

    if ( !tag || !(*tag) )
        return ( ret );

    s = sjis2utf(tag);
    if ( !s )
        return ( ret );
    strcpy( _tag, encodeURL(s) );

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( ret );
    memset( cookie,  0x00, MAX_COOKIE_LEN );

    /* �͂ĂȂ� login */
    ret = loginHatenaBookmark( userName, password, cookie );
    if ( ret ) {
        char    *request;
        char    *response;
        char    url[MAX_URLLENGTH];
        size_t  sz = MAX_CONTENT_SIZE * 4;

        ret = FALSE;
        request  = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request )  {
            free( cookie );
            return ( ret );
        }
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            free( cookie );
            return ( ret );
        }
        memset( request, 0x00, MAX_CONTENT_SIZE );

#ifdef  BEFORE_20081125
        /* http://b.hatena.ne.jp/���[�U��/�^�O/?mode=edit ���擾 */
        sprintf( url, "http://b.hatena.ne.jp/%s/%s/?mode=edit",
                 userName, _tag );
#else
        /* http://b.hatena.ne.jp/���[�U��/tag?tag=�^�O ���擾 */
        sprintf( url, "http://b.hatena.ne.jp/%s/tag?tag=%s",
                 userName, _tag );
#endif
        setUpReceiveBuffer( response, sz );
        httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
                                  NULL, NULL );

        if ( *response ) {
            char    rkm[MAX_KEYLENGTH];

            /* rkm �̒l���擾 */
            getRkm( rkm, response );

#ifdef  BEFORE_20081125
            /* �폜�����s (http://b.hatena.ne.jp/���[�U��/�^�O/ �� POST) */
            sprintf( url, "http://b.hatena.ne.jp/%s/%s/", userName, _tag );
            setTargetURL( url );
            sprintf( request,
                     "mode=deleteenter&"
                     "rkm=%s&"
                     "oldtag=%s",
                     encodeURL(rkm), _tag );
#else
            /* �폜�����s                                               */
            /*      (http://b.hatena.ne.jp/���[�U��/tag.delete �� POST) */
            sprintf( url, "http://b.hatena.ne.jp/%s/tag.delete", userName );
            setTargetURL( url );
            sprintf( request,
                     "rks=%s&"
                     "tag=%s",
                     encodeURL(rkm), _tag );
#endif
            setUpReceiveBuffer( response, sz );
            httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                                 "application/x-www-form-urlencoded",
                                 request, response, cookie,
                                 NULL, NULL );
            if ( *response ) {
                char    target[BUFSIZ];

                sprintf( target, "/rss?tag=%s\"", _tag );
                if ( strstr( response, target ) )
                    ret = TRUE;
            }
        }

        free( response );
        free( request );
    }

    free( cookie );

    return ( ret );
}


/*
 *  �ǉ��@�\
 */

/* ���u�b�N�}�[�N���̎擾 (FeedURI �ւ� GET �œ��� XML����͂��邱�ƂŎ���) */

long
getNumberOfBookmarksOnHatena(
        const char *userName,   /* (I) ���[�U��   */
        const char *password    /* (I) �p�X���[�h */
    )
{
    long    num = 0;
    int     res;
    char    wsse[BUFSIZ];
    char    url[MAX_URLLENGTH];
    char    *response;
    size_t  sz = MAX_CONTENT_SIZE;

    response = (char *)malloc( sz );
    if ( !response )
        return ( num );
    memset( wsse, 0x00, BUFSIZ );

    xmlrpc_p->blogKind = BLOGKIND_HATENA;
    makeWSSE( userName, password, wsse, xmlrpc_p->blogKind );

    sprintf( url, "%s/feed", HATENA_B_ENDPOINT_URL );
    setTargetURL( url );
    setUpReceiveBuffer( response, sz );
    res = httpGetEx( xmlrpc_p->webServer, xmlrpc_p->webPage,
                     response, NULL, FALSE,
                     wsse );

    if ( response[0] != NUL ) {
        /* <openSearch:totalResults>1581</openSearch:totalResults> */
        char    *p = strstr( response, "<openSearch:totalResults>" );
        if ( p ) {
            p += 25;
            while ( *p == '0' )
                p++;
            if ( (*p >= '1') && (*p <= '9') )
                num = atol( p );
        }
    }

    free( response );

    return ( num );
}



/*
 *  �͂Ă�(�u�b�N�}�[�N)�� login
 */

BOOL
loginHatenaBookmark(
    const char *username,   // (I) �͂Ă�ID (�������̓��[���A�h���X)
    const char *password,   // (I) �p�X���[�h
    char       *cookie )    // (O) �N�b�L�[
{
    int     ret = FALSE, r;
    char    *request;
    char    *response;
    char    url[MAX_URLLENGTH];
    size_t  sz = MAX_CONTENT_SIZE * 2;

    if ( !cookie )
         return ( ret );

    if ( !username )
        username = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    request  = (char *)malloc( MAX_CONTENT_SIZE );
    if ( !request ) 
        return ( ret );
    response = (char *)malloc( sz );
    if ( !response ) {
        free( request );
        return ( ret );
    }
    memset( request, 0x00, MAX_CONTENT_SIZE );

    strcpy( url,
            "https://www.hatena.ne.jp/login?"
            "backurl=http%3A%2F%2Fb.hatena.ne.jp%2F" );
    setUpReceiveBuffer( response, sz );
    httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
                              NULL, NULL );

    strcpy( url, "https://www.hatena.ne.jp/login" );
    setTargetURL( url );
    sprintf( request,
             "name=%s&"
             "password=%s&"
             "persistent=1&"
             "location=http://b.hatena.ne.jp/",
             username, password );
    setUpReceiveBuffer( response, sz );
    r = httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                             "application/x-www-form-urlencoded",
                             request, response, cookie,
                             NULL, NULL );
    if ( r == -1 )
        ret = FALSE;        /* �T�[�o�Ƃ̒ʐM���s */
    else if ( *response ) {
        if ( strstr(response, sjis2utf("�p�X���[�h���F�؂���܂���")) ||
             strstr(response, sjis2utf("���O�C�����ł�"))                )
            ret = TRUE;     /* ���O�C������ */
        else {
            ret = FALSE;    /* ���O�C�����s */
            if ( strstr(response, "<meta http-equiv=\"R") ) {
                setUpReceiveBuffer( response, sz );
                http_getEx( "http://b.hatena.ne.jp/", response, cookie );
                if ( *response ) {
                    if ( strstr(response, sjis2utf("���O�A�E�g")) )
                        ret = TRUE;     /* ���O�C������ */
                }
            }
        }
    }

    free( response );
    free( request  );

    return ( ret );
}


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
    )
{
    BOOL    ret = FALSE;
    char    *cookie;
    char    extended[MAX_DESCRIPTION_LEN * 2];

    if ( !href || !(*href) || !entryID )
        return ( ret );

    entryID[0] = NUL;
    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( ret );
    memset( cookie,   0x00, MAX_COOKIE_LEN );
    memset( extended, 0x00, MAX_DESCRIPTION_LEN * 2 );
    makeExtended( tags, summary, extended );

    /* �͂ĂȂ� login */
    ret = loginHatenaBookmark( usrname, passwd, cookie );
    if ( ret ) {
        char    *request;
        char    *response;
        char    *p;
        char    url[BUFSIZ * 2];
        char    asin[32];
        size_t  sz = MAX_CONTENT_SIZE * 4;

        ret = FALSE;

        request  = (char *)malloc( MAX_CONTENT_SIZE );
        if ( !request ) {
            free( cookie );
            return ( ret );
        }
        response = (char *)malloc( sz );
        if ( !response ) {
            free( request );
            free( cookie );
            return ( ret );
        }
        memset( request, 0x00, MAX_CONTENT_SIZE );

        /* asin �̒l���擾 */
        getASIN( href, asin );

        /* �u�b�N�}�[�N���e�t�H�[�����擾 */
        p = sjis2utf(title);
#ifdef  BEFORE_20081125
        sprintf( url,
                 "http://b.hatena.ne.jp/add?"
                 "mode=confirm&"
                 "is_bm=1&"
                 "title=%s&",
                 encodeURL(p ? p : title) );
        sprintf( url + strlen(url),
                 "url=%s",
                 encodeURL(href) );
#else
        sprintf( url,
                 "http://b.hatena.ne.jp/%s/add.confirm?"
                 "url=%s",
                 usrname,
                 encodeURL(href) );
#endif
        setUpReceiveBuffer( response, sz );
        httpGetBufferWithSession( url, response, TRUE, NULL, NULL, cookie,
                                  NULL, NULL );
        if ( *response ) {
            char    rkm[MAX_KEYLENGTH];
            char    _href[BUFSIZ * 2];

            /* rkm �̒l���擾 */
            getRkm( rkm, response );
            getEid( entryID, response );
            getHref( _href, response );
            getTitleText( title, response );

            /* �u�b�N�}�[�N�𓊍e */
            memset( response, 0x00, MAX_CONTENT_SIZE * 4 );
#ifdef  BEFORE_20081125
            strcpy( url, "http://b.hatena.ne.jp/add" );
            setTargetURL( url );
            sprintf( request,
                     "mode=enter&" );
            if ( entryID[0] )
                sprintf( request + strlen(request),
                         "eid=%s&",
                         entryID );
            else
                sprintf( request + strlen(request),
                         "eid=&" );
            sprintf( request + strlen(request),
                     "url=%s&",
                     encodeURL( _href[0] ? _href : href ) );
            sprintf( request + strlen(request),
                     "rkm=%s&"
                     "is_bm=1&"
                     "force_url=1&"
                     "asin=%s&", 
                     encodeURL(rkm),
                     asin );
            sprintf( request + strlen(request),
                     "title=%s&",
                     encodeURL(title) ); // UTF-8
            if ( *extended ) {
                p = sjis2utf(extended);
                sprintf( request + strlen(request),
                         "comment=%s&",
                         encodeURL(p ? p : extended) );
            }
            else
                sprintf( request + strlen(request),
                         "comment=&" );
            sprintf( request + strlen(request),
                     "addasin=1&"
                     "commit=%s",
                     encodeURL(sjis2utf("�ǉ�����")) );
#else
            sprintf( url, "http://b.hatena.ne.jp/%s/add.edit", usrname );
            setTargetURL( url );
            sprintf( request,
                     "rks=%s&", 
                     encodeURL(rkm) );
            sprintf( request + strlen(request),
                     "url=%s&", 
                     encodeURL( _href[0] ? _href : href ) );
            if ( *extended ) {
                p = sjis2utf(extended);
                sprintf( request + strlen(request),
                         "comment=%s&",
                         encodeURL(p ? p : extended) );
            }
            else
                sprintf( request + strlen(request),
                         "comment=&" );
            sprintf( request + strlen(request),
                     "add_asin=1&"
                     "asin=%s&", 
                     asin );
#endif
            setUpReceiveBuffer( response, sz );
            httpPostWithSession( xmlrpc_p->webServer, xmlrpc_p->webPage,
                                 "application/x-www-form-urlencoded",
                                 request, response, cookie,
                                 NULL, NULL );

            if ( *response ) {
                if ( entryID[0] == NUL )
                    getEid( entryID, response );
                ret = TRUE;
            }
        }

        free( response );
        free( request );
    }

    free( cookie );

    return ( ret );
}


/*
 *  �͂Ăȃu�b�N�}�[�N���� RSS/Atom�t�B�[�h�`���� export �����t�@�C������
 *  �G���g������ǂݎ��
 */

#define HB_FEED_TYPE_UNKNOWN    0
#define HB_FEED_TYPE_RSS        1
#define HB_FEED_TYPE_ATOM       2

long
getPostsFromHatenaFeed(
    FILE            *fp,        /* (I) (RSS/Atom�t�B�[�h)�t�@�C���X�g���[�� */
    HATENA_BOOKMARK **posts,    /* (O) �擾�����u�b�N�}�[�N         */
    long            *numOfPosts /* (O) �擾�����u�b�N�}�[�N�̐�     */
  )
{
    size_t      fileSize = 0;
    long        num      = 0;
    char        buf[MAX_CONTENT_SIZE];
    char        *p, *q, *xmlSrc;
    int         feedType = HB_FEED_TYPE_UNKNOWN;
    struct stat s;

    if ( numOfPosts )
        *numOfPosts = 0;
    if ( !posts || !fp || !numOfPosts )
        return ( num );

    if ( !fstat( fileno( fp ), &s ) )
        fileSize = s.st_size;
    if ( fileSize == 0 )
        return ( num );

    xmlSrc = (char *)malloc( fileSize + BUFSIZ );
    if ( !xmlSrc )
        return ( num );

    q = xmlSrc;
    while ( ( p = fgets( buf, MAX_CONTENT_SIZE - 1, fp ) ) != NULL ) {
        if ( feedType == HB_FEED_TYPE_UNKNOWN ) {
            if ( strstr( p, "<feed version=\"0.3\"" ) )
                feedType = HB_FEED_TYPE_ATOM;
            else if ( strstr( p, "<rdf:RDF " ) )
                feedType = HB_FEED_TYPE_RSS;
        }
        strcpy( q, p );
        q += strlen( p );

        if ( feedType == HB_FEED_TYPE_ATOM ) {
            if ( strstr( p, "<entry>" ) )
                num++;
        }
        else if ( feedType == HB_FEED_TYPE_RSS ) {
            if ( strstr( p, "<item rdf:about=\"" ) )
                num++;
        }
    }

    if ( (num > 0) && (feedType != HB_FEED_TYPE_UNKNOWN) ) {
        *numOfPosts = num;
        *posts = (HATENA_BOOKMARK *)malloc(sizeof ( HATENA_BOOKMARK ) * num);
        num = 0;
        if ( *posts ) {
            if ( feedType == HB_FEED_TYPE_ATOM )
                num = getPosts( xmlSrc, numOfPosts, *posts );
            else
                num = getPostsFromRSS( xmlSrc, numOfPosts, *posts );
        }
    }
    free( xmlSrc );

    *numOfPosts = num;
    return ( num );
}

void
freePostsFromHatenaFeed( HATENA_BOOKMARK *posts )
{
    if ( posts )
        free( posts );
}


/* �^�O�ꗗ�̎擾 */
int
getListOfTagsOnHatena(
        const char *username,   /* (I) ���[�U��         */
        const char *password,   /* (I) �p�X���[�h       */
        long       *numOfTags,  /* (I) �擾����^�O�̐� */
                                /* (O) �擾�����^�O�̐� */
        TagList    *lp          /* (O) �^�O�ꗗ         */
    )
{
    int     num = 0;
    char    *cookie;
    int     ret;

    if ( !numOfTags || (*numOfTags <= 0) || !lp )
        return ( num );

    if ( !username )
        username = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    cookie = (char *)malloc( MAX_COOKIE_LEN );
    if ( !cookie )
        return ( num );
    memset( cookie, 0x00, MAX_COOKIE_LEN );

    /* �͂ĂȂ� login */
    ret = loginHatenaBookmark( username, password, cookie );
    if ( ret ) {
        char    url[MAX_URLLENGTH];
        char    *response;
        size_t  sz = MAX_CONTENT_SIZE * 16;

        response = (char *)malloc( sz );
        if ( !response ) {
            free( cookie );
            return ( num );
        }

#ifdef  BEFORE_20081125
        sprintf( url, "http://b.hatena.ne.jp/%s/tag", username );
#else
        /* ���j���[�A����́u�͂Ăȃu�b�N�}�[�N�v�ł́u�^�O�̕\�������Ȃ��v */
        /* �ݒ�ɂ��Ă���ƁA�^�O�ꗗ���擾����p���Ȃ�                     */
        sprintf( url, "http://b.hatena.ne.jp/%s/tag", username );// [�@�\����]

        strcpy( strchr( cookie, '\r' ),
                "; config_tab=config_table_design_button\r\n" );
#endif
        setUpReceiveBuffer( response, sz );
        http_getEx( url, response, cookie );

        if ( *response ) {
            char    *p, *q, *r;

            p = strstr( response, "<ul class=\"taglist\"" );
            if ( p ) {
                p += 19;

                do {
                    q = strstr( p, "\" class=\"tag-" );
                    if ( !q )
                        break;
                    q += 12;

                    r = strchr( q, '>' );
                    if ( !r )
                        break;

                    p = r + 1;
                    q = strstr( p, "</a>" );
                    if ( !q )
                        break;

                    strncpy( lp[num].tag, p, q - p );
                    lp[num].tag[q - p] = NUL;

                    num++;
                } while ( num < *numOfTags );
            }
        }

        free( response );
    }

    *numOfTags = num;
    free( cookie );

    return ( num );
}
