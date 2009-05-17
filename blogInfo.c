/*
 *  blogInfo.c
 *      blog ���e�[�u��
 * History:
 * $Log: /comm/xmlRPC/blogInfo.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 15    09/03/20 22:25 Tsujimura543
 * �u�͂Ăȃ_�C�A���[�v�� Atom API �ɑΉ�
 * 
 * 14    09/03/16 14:04 Tsujimura543
 * �u�E�F�u���u���O (XML-RPC API)�v�֘A�A�ǉ�
 * 
 * 13    07/11/30 1:41 Tsujimura543
 * (1) ���v���O!�A�h���R���u���O�AJugem �����ɓ��ʂɗp�ӂ��Ă����������폜
 * (2) �A���[�o�u���O�����̓��ʏ������폜 (Atom API �֘A������)
 * 
 * 12    07/10/29 16:44 Tsujimura543
 * ���v���O! �� XML-RPC API �֘A�̒�`��ǉ�
 * 
 * 11    07/02/23 23:15 Tsujimura543
 * JUGEM �ƃh���R���u���O�� XML-RPC API �֘A�̒�`��ǉ�
 * 
 * 10    06/09/14 13:46 Tsujimura543
 * VOX �֘A�̋L�q��ǉ�
 * 
 * 9     06/03/15 21:57 Tsujimura543
 * livedoor Blog �̃G���h�|�C���g URL �� ATOMURL_LIVEDOOR_200507 �ɕύX
 * 
 * 8     06/02/20 23:22 Tsujimura543
 * �}�C�v���t�B�[���֘A�̋L�q���폜
 * 
 * 7     06/01/26 13:24 Tsujimura543
 * �A���[�o�u���O �� Atom API �ɑΉ�
 * 
 * 6     05/11/28 15:05 Tsujimura543
 * �R�R���O�t���[�Ή�
 * 
 * 5     05/07/19 11:17 Tsujimura543
 * So-net blog �Ή�
 * 
 * 4     04/09/28 13:54 Tsujimura543
 * �A���[�o�u���O�Ή�
 * 
 * 3     04/09/03 15:24 Tsujimura543
 * �}�C�v���t�B�[���Ή� [�b��]
 * 
 * 2     04/08/19 9:06 Tsujimura543
 * LOVELOG, TypePad Germany, blogger ��ǉ�
 * 
 * 1     04/07/07 15:45 Tsujimura543
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/blogInfo.c 1     09/05/14 3:46 tsupo $";
#endif


BLOGINFOTBL blogInfoTbl[] = {
    /*
     *  TypePad�n
     */
    {   /* �R�R���O */
        BLOGKIND_COCOLOG,
        CHARSET_UTF8,
        APIURL_COCOLOG,
        ATOMURL_COCOLOG
    },
    {   /* �R�R���O�t���[ */
        BLOGKIND_COCOLOGFREE,
        CHARSET_UTF8,
        APIURL_COCOLOGFREE,
        ATOMURL_COCOLOGFREE
    },
    {   /* �u���O�l */
        BLOGKIND_BLOGZINE,
        CHARSET_UTF8,
        APIURL_BLOGZINE,
        ATOMURL_BLOGZINE
    },
    {   /* TypePad */
        BLOGKIND_TYPEPAD,
        CHARSET_UTF8,
        APIURL_TYPEPAD,
        ATOMURL_TYPEPAD
    },
    {   /* TypePad Japan */
        BLOGKIND_TYPEPADJAPAN,
        CHARSET_UTF8,
        APIURL_TYPEPADJAPAN,
        ATOMURL_TYPEPADJAPAN
    },
    {   /* TypePad France */
        BLOGKIND_TYPEPADFRANCE,
        CHARSET_UTF8,
        APIURL_TYPEPADFRANCE,
        ATOMURL_TYPEPADFRANCE
    },
    {   /* TypePad Germany */
        BLOGKIND_TYPEPADGERMANY,
        CHARSET_UTF8,
        APIURL_TYPEPADGERMANY,
        ATOMURL_TYPEPADGERMANY
    },

    /*
     *  metaWeblog API �T�|�[�g blog
     */
    {   /* News-Handler */
        BLOGKIND_NEWSHANDLER,
        CHARSET_EUCJP,
        APIURL_NEWSHANDLER,
        ""
    },
    {   /* Seesaa BLOG */
        BLOGKIND_SEESAABLOG,
        CHARSET_SHIFTJIS,
        APIURL_SEESAABLOG,
        ""
    },

    /*
     *  MovableType API �T�|�[�g blog
     */
    {   /* �h���R���u���O (XML-RPC API) */
        BLOGKIND_DRECOMBLOG_X,
        CHARSET_SHIFTJIS,
        APIURL_DRECOMBLOG_X,
        ""
    },
    {   /* JUGEM (XML-RPC API) */
        BLOGKIND_JUGEM_X,
        CHARSET_EUCJP,
        APIURL_JUGEM_X,
        ""
    },
    {   /* ���v���O! (XML-RPC API) */
        BLOGKIND_YAPLOG_X,
        CHARSET_SHIFTJIS,
        APIURL_YAPLOG_X,
        ""
    },
    {   /* �E�F�u���u���O (XML-RPC API) */
        BLOGKIND_WEBRY_X,
        CHARSET_UTF8,
        APIURL_WEBRY_X,
        ""
    },

    /*
     *  Atom API �T�|�[�g blog
     */
    {   /* livedoor Blog */
        BLOGKIND_LIVEDOOR,
        CHARSET_EUCJP,
        "",
        ATOMURL_LIVEDOOR_200507
    },

    {   /* LOVELOG */
        BLOGKIND_LOVELOG,
        CHARSET_EUCJP,
        "",
        ATOMURL_LOVELOG
    },

    {   /* So-net blog */
        BLOGKIND_SONET,
        CHARSET_UTF8,
        "",
        ATOMURL_SONET
    },

    {   /* �A���[�o�u���O */
        BLOGKIND_AMEBLO,
        CHARSET_EUCJP,
        "",
        ATOMURL_AMEBLO
    },

    {   /* blogger */
        BLOGKIND_BLOGGER,
        CHARSET_UTF8,
        APIURL_BLOGGER,
        ATOMURL_BLOGGER
    },

    {   /* Vox */
        BLOGKIND_VOX,
        CHARSET_UTF8,
        "",
        ATOMURL_VOX
    },

    {   /* �͂Ăȃ_�C�A���[ */
        BLOGKIND_HATENADIARY,
        CHARSET_EUCJP,
        "",
        ATOMURL_HATENADIARY
    },

    /* �ȉ��� blog �́AXML-RPC API �� Atom API ���g�킸�Ablog �Ǘ���ʂ� */
    /* ���ڒʐM��������őΉ�                                            */
    {   /* excite�u���O */
        BLOGKIND_EXCITEBLOG,
        CHARSET_UTF8,
        NULL,
        NULL
    },

    { -1, -1, NULL, NULL }
};
