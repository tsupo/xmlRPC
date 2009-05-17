/*
 *  cousagi.c
 *
 * History:
 * $Log: /comm/xmlRPC/cousagi.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 11    06/09/15 16:38 Tsujimura543
 * �\�[�X�R�[�h�𐮗�
 * 
 * 10    06/08/29 21:20 Tsujimura543
 * �V���� URL �Œ񋟂���邱�ƂɂȂ����u�L�����e�vAPI�̓���m�F�p��
 * �R�[�h���C��
 * 
 * 9     06/08/18 11:03 Tsujimura543
 * �VAPI�e�X�g��
 * 
 * 8     05/02/18 16:10 Tsujimura543
 * cousagi.yomiusa..net �� www.blogpet.net �ɕ�����u������悤�ɂ���
 * 
 * 7     05/02/18 15:39 Tsujimura543
 * �u���������v���uBlogPet�v�ֈڍs�����̂ɔ����C��
 * 
 * 6     04/11/04 16:18 Tsujimura543
 * setRequestForCousagi() ��ǉ����A�v���d���g�ݗ��ď��������ʉ�
 * 
 * 5     04/11/04 16:10 Tsujimura543
 * getNewWhisperOnCousagi() ��ǉ�
 * 
 * 4     04/08/31 15:57 Tsujimura543
 * http POST �Ŏg���d���i�[�̈�𓮓I�Ɋm�ۂ���悤�ɕύX
 * 
 * 3     04/07/16 14:09 Tsujimura543
 * �������� API �֘A�𐮗�
 * 
 * 2     04/07/07 11:57 Tsujimura543
 * RCS �ɂ��Ő��Ǘ����� VSS �ɂ��Ő��Ǘ��Ɉڍs
 */

#include "xmlRPC.h"

#ifndef	lint
static char	*rcs_id =
"$Header: /comm/xmlRPC/cousagi.c 1     09/05/14 3:46 tsupo $";
#endif


char    *regulerizeString( char *src );

/*
 * cousagi XML-RPC API
 *
 *  cousagi.getNewEntry 
 *    ���� 
 *      ���������ɐV�����L�����������܂� 
 *    ���� 
 *      String  username, // �������� �̃��[�U��(�A�J�E���g)
 *      String  password  // ��L���[�U�� login �p�p�X���[�h
 *
 *  cousagi.getNewPhrase 
 *    ���� 
 *      ���������ɐV�������������܂� 
 *    ���� 
 *      String  username, // �������� �̃��[�U��(�A�J�E���g)
 *      String  password  // ��L���[�U�� login �p�p�X���[�h
 *
 *  cousagi.getNewHaiku 
 *    ���� 
 *      ���������ɐV�����o����r�܂��܂� 
 *    ���� 
 *      String  username, // �������� �̃��[�U��(�A�J�E���g)
 *      String  password  // ��L���[�U�� login �p�p�X���[�h
 *
 *  cousagi.getNewWhisper 
 *    ���� 
 *      ���������ɐV�����Q�����Ԃ₩���܂� 
 *    ���� 
 *      String  username, // �������� �̃��[�U��(�A�J�E���g)
 *      String  password  // ��L���[�U�� login �p�p�X���[�h
 *
 *
 *  blogpet.getEntry
 *    ���� 
 *      BlogPet �ɐV�����L�����������܂� 
 *    ���� 
 *      String ���O�C��ID
 *      String ���O�C���p�X
 */

/* �v���d���̑g�ݗ��� */
char    *
setRequestForCousagi( const char *userName,     // (I) ���[�U��
                      const char *password,     // (I) �p�X���[�h
                      const char *serviceName,  // (I) �v���d����
                      char       *request       // (O) ���������v���d�� (XML)
                    )
{
	sprintf( request,
             XML_STATEMENT
             "<methodCall>\n<methodName>%s</methodName>\n"
             "<params>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "<param>\n<value><string>%s</string></value>\n</param>\n"
             "</params>\n"
             "</methodCall>\n\n",
             serviceName,
             userName, password );

    return ( request );
}


/* �L���̐��� */
int
getNewEntryOnCousagi( const char *userName, // (I) ���[�U��
                      const char *password, // (I) �p�X���[�h
                      char       *title,    // (O) ���������L���̑薼
                      char       *body )    // (O) ���������L���̖{��
{
    int     ret = 0, res;
    char    *buffer;
    char    *result;
    char    petName[BUFSIZ];
    char    profile[BUFSIZ];

    petName[0] = NUL;
    profile[0] = NUL;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( BUFSIZ * 2 );
    if ( !buffer )
        return ( ret );
    result = (char *)malloc( MAX_CONTENT_SIZE * 2 );
    if ( !result ) {
        free( buffer );
        return ( ret );
    }
    memset( buffer, 0x00, BUFSIZ * 2 );
    memset( result, 0x00, MAX_CONTENT_SIZE * 2 );

#ifdef  OLD_FASHIONED
    setTargetURL( APIURL_COUSAGI );
    setRequestForCousagi( userName, password, "cousagi.getNewEntry", buffer );
#else
    setTargetURL( "http://api.blogpet.net/api/api.php" );
    setRequestForCousagi( userName, password, "blogpet.getEntry", buffer );
#endif

    res = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, result );

    if ( (res == 0) || (result[0] != NUL) ) {
        /*
         * String   title
         * String   body
         */
        char    *p = result;
        char    *q = strstr( p, "<struct>" );
        char    *r, *s, *t;
        int     cnt = 0;

        if ( q ) {
            q += 8;
            while ( *q ) {
                r = strstr( q, "<name>Title</name>" );
                if ( !r )
                    r = strstr( q, "<name>title</name>" );
                if ( r ) {
                    s = strstr( r + 18, "<string>" );
                    if ( s ) {
                        s += 8;
                        t = strstr( s, "</string>" );
                        strncpy( title, s, t - s );
                        title[t - s] = NUL;
                        q = t + 9;
                        cnt++;
#ifdef  OLD_FASHIONED
                        if ( cnt >= 2 )
#else
                        if ( cnt >= 4 )
#endif
                            break;
                        continue;
                    }
                }

                r = strstr( q, "<name>Body</name>" );
                if ( !r )
                    r = strstr( q, "<name>body</name>" );
                if ( r ) {
                    s = strstr( r + 17, "<string>" );
                    if ( s ) {
                        s += 8;
                        t = strstr( s, "</string>" );

                        /* �Ȃ��� title �ɖ{���Abody �ɑ薼�������Ă���    */
                        /* (2006�N8��29������)���߁A�ȉ��̎b��Ώ������� */
                        if ( !strstr( title, "(BlogPet)" ) ) {
                            strcpy( body, title );

                            strncpy( title, s, t - s );
                            title[t - s] = NUL;
                        }
                        else {
                            strncpy( body, s, t - s );
                            body[t - s] = NUL;
                        }
                        decodeString( body );
                        regulerizeString( body );
                        q = t + 9;
                        cnt++;
#ifdef  OLD_FASHIONED
                        if ( cnt >= 2 )
#else
                        if ( cnt >= 4 )
#endif
                            break;
                        continue;
                    }
                }

#ifndef OLD_FASHIONED
                r = strstr( q, "<name>petname</name>" );
                if ( r ) {
                    s = strstr( r + 20, "<string>" );
                    if ( s ) {
                        s += 8;
                        t = strstr( s, "</string>" );
                        strncpy( petName, s, t - s );
                        petName[t - s] = NUL;
                     // decodeString( petName );
                        q = t + 9;
                        cnt++;
                        if ( cnt >= 4 )
                            break;
                        continue;
                    }
                }

                r = strstr( q, "<name>profile</name>" );
                if ( r ) {
                    s = strstr( r + 20, "<string>" );
                    if ( s ) {
                        s += 8;
                        t = strstr( s, "</string>" );
                        strncpy( profile, s, t - s );
                        profile[t - s] = NUL;
                     // decodeString( profile );
                        q = t + 9;
                        cnt++;
                        if ( cnt >= 4 )
                            break;
                        continue;
                    }
                }
#endif
                q++;
            }
        }

        ret = 1;
    }


    if ( body[0] && petName[0] && profile[0] ) {
        sprintf( body + strlen( body ),
                 "<p>%s ",
                 sjis2utf( "*���̃G���g����" ) );
        sprintf( body + strlen( body ),
                 "<a href=\"http://www.blogpet.net/\">BlogPet</a>"
                 " %s <a href=\"%s\">%s</a> ",
                 sjis2utf( "��" ), profile, petName );
        sprintf( body + strlen( body ),
                 "%s</p>",
                 sjis2utf( "�������܂����B" ) );
    }

    free( result );
    free( buffer );

    return ( ret );
}


/* �����̐��� */
int
getNewPhraseOnCousagi( const char *userName,    // (I) ���[�U��
                       const char *password,    // (I) �p�X���[�h
                       char       *response )   // (O) ������������
{
    int     ret = 0, res;
    char    *buffer;
    char    *result;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( BUFSIZ * 2 );
    if ( !buffer )
        return ( ret );
    result = (char *)malloc( BUFSIZ * 2 );
    if ( !result ) {
        free( buffer );
        return ( ret );
    }
    memset( buffer, 0x00, BUFSIZ * 2 );
    memset( result, 0x00, BUFSIZ * 2 );

    setTargetURL( APIURL_COUSAGI );
    setRequestForCousagi( userName, password, "cousagi.getNewPhrase", buffer);

    res = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, result );

    if ( (res == 0) || (result[0] != NUL) ) {
        /*
         * String   phrase
         */
        getSingleString( result, response );
        ret = 1;
    }

    free( result );
    free( buffer );

    return ( ret );
}


/* �o��̉r�� */
int
getNewHaikuOnCousagi( const char *userName, // (I) ���[�U��
                      const char *password, // (I) �p�X���[�h
                      char       *response )// (O) ���������o��
{
    int     ret = 0, res;
    char    *buffer;
    char    *result;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( BUFSIZ * 2 );
    if ( !buffer )
        return ( ret );
    result = (char *)malloc( BUFSIZ * 2 );
    if ( !result ) {
        free( buffer );
        return ( ret );
    }
    memset( buffer, 0x00, BUFSIZ * 2 );
    memset( result, 0x00, BUFSIZ * 2 );

    setTargetURL( APIURL_COUSAGI );
    setRequestForCousagi( userName, password, "cousagi.getNewHaiku", buffer );

    res = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, result );

    if ( (res == 0) || (result[0] != NUL) ) {
        /*
         * String   haiku
         */
        getSingleString( result, response );
        ret = 1;
    }

    free( result );
    free( buffer );

    return ( ret );
}


/* �Q���̐��� */
int
getNewWhisperOnCousagi( const char *userName,
                        const char *password,
                        char       *response )
{
    int     ret = 0, res;
    char    *buffer;
    char    *result;

    if ( !userName )
        userName = xmlrpc_p->userName;
    if ( !password )
        password = xmlrpc_p->password;

    buffer = (char *)malloc( BUFSIZ * 2 );
    if ( !buffer )
        return ( ret );
    result = (char *)malloc( BUFSIZ * 2 );
    if ( !result ) {
        free( buffer );
        return ( ret );
    }
    memset( buffer, 0x00, BUFSIZ * 2 );
    memset( result, 0x00, BUFSIZ * 2 );

    setTargetURL( APIURL_COUSAGI );
    setRequestForCousagi( userName, password, "cousagi.getNewWhisper",buffer);

    res = httpPost( xmlrpc_p->webServer, xmlrpc_p->webPage,
                    NULL,
                    buffer, result );

    if ( (res == 0) || (result[0] != NUL) ) {
        /*
         * String   whisper
         */
        getSingleString( result, response );
        ret = 1;
    }

    free( result );
    free( buffer );

    return ( ret );
}


/* XHTML valid �Ȍ`���ɂȂ�悤�^�O��t�� */
char    *
regulerizeString( char *src )   // (I/O) ���K��������������/���K���ς݂̕�����
{
    char    *tmp1;
    char    *tmp2;
    char    *p, *q;

    tmp1 = (char *)malloc( MAX_CONTENT_SIZE * 2 );
    if ( !tmp1 )
        return ( NULL );
    tmp2 = (char *)malloc( MAX_CONTENT_SIZE * 2 );
    if ( !tmp2 ) {
        free( tmp1 );
        return ( NULL );
    }
    memset( tmp1, 0x00, MAX_CONTENT_SIZE * 2 );
    memset( tmp2, 0x00, MAX_CONTENT_SIZE * 2 );

    sprintf( tmp1, "<p>%s</p>", src );

    p = tmp1;
    while ( ( ( q = strstr( p, "<blockquote>" ) ) != NULL ) ||
            ( ( q = strstr( p, "<BLOCKQUOTE>" ) ) != NULL )    ) {
        p = q;
        sprintf( tmp2, "</p><blockquote><p>%s", q + 12 );
        strcpy( q, tmp2 );
        p += 19;
        if ( ( ( q = strstr( p, "</blockquote>" ) ) != NULL ) ||
             ( ( q = strstr( p, "</BLOCKQUOTE>" ) ) != NULL )    ) {
            p = q;
            sprintf( tmp2, "</p></blockquote><p>%s", q + 13 );
            strcpy( q, tmp2 );
            p += 20;
        }
    }

    p = tmp1;
    while ( *p ) {
        if ( (*p == '\r') && (*(p + 1) == '\n') ) {
            sprintf( tmp2, "<br />%s", p + 2 );
            strcpy( p, tmp2 );
            p += 5;
        }
        else if ( (*p == '\r') || (*p == '\n') ) {
            sprintf( tmp2, "<br />%s", p + 1 );
            strcpy( p, tmp2 );
        }
        p++;
    }

    strcpy( src, tmp1 );

    free( tmp2 );
    free( tmp1 );

    return ( src );
}


/* ���������L���ɔo��𖄂ߍ��� (���܂�API) */
char    *
insertHaikuIntoEntry( char       *body,         // (I/O) �L���{��
                      const char *haiku,        // (I) �o��
                      const char *cousagiName,  // (I) BlogPet �̖��O
                      int        blogPetType )  // (I) BlogPet �̎��
{
    char    *tmp;
    char    *p, *q, *r;
    int     len = strlen( body ) + 
                    ((haiku && *haiku) ? strlen( haiku ) : 0) +
                    BUFSIZ;
    const char  *target1 =
    "*���̃G���g���́A<a href=\"http://cousagi.yomiusa.net/\">��������</a>��";
    const char  *target2 =
      "*���̃G���g���́A<a href=\"http://www.blogpet.net/\">BlogPet</a>��";

    tmp = (char *)malloc( len );
    if ( tmp ) {
        p = strstr( body, target1 );
        if ( !p )
            p = strstr( body, target2 );
        if ( p ) {
            if ( haiku && *haiku ) {
                memset( tmp, 0x00, len );
                strncpy( tmp, body, p - body );
                tmp[p - body] = '\0';
                sprintf( tmp + strlen( tmp ),
                         "</p><p>�����ň��A</p>"
                         "<blockquote><p>�u%s�v</p>"
                         "<cite>�\ %s %s�A�S�̔o��</cite>"
                         "</blockquote><p>%s",
                         haiku, 
                         blogPetTypeString( blogPetType ),
                         cousagiName, p );
                strcpy( body, tmp );
                p = strstr( body, target1 );
                if ( !p )
                    p = strstr( body, target2 );
            }
        }

        if ( p && !strncmp( p, target1, strlen( target1 ) ) ) {
            q = strchr( p, '"' );
            r = strchr( q + 1, '"' );
            strcpy( q + 1, "http://www.blogpet.net/" );
            strcat( q + 1, r );
            p = strstr( body, "*���̃G���g���́A" );
        }

        if ( p ) {
            q = strchr( p, '>' );
            r = strstr( p, "�u" );

            if ( q ) {
                q++;
                memset( tmp, 0x00, len );
                strncpy( tmp, body, q - body );
                tmp[q - body] = '\0';
                strcat( tmp, blogPetTypeString( blogPetType ) );

                q = strchr( q, '<' );
                if ( q && r && ( q < r ) ) {
                    r += 2;
                    len = strlen( tmp );
                    strncat( tmp, q, r - q );
                    tmp[len + (r - q)] = NUL;

                    strcat( tmp, cousagiName );

                    r = strstr( r, "�v" );
                    if ( r )
                        strcat( tmp, r );
                }
                else if ( q )
                    strcat( tmp, q );

                strcpy( body, tmp );
            }
        }

        free( tmp );
    }

    return ( body );
}


/*
 * Blog Pet ��ʂ𕶎���ŕԂ�
 */
char    *
blogPetTypeString( int blogPetType )
{
    char    *p;

    switch ( blogPetType ) {
    case BPTYPE_COUSAGI:
        p = "��������";
        break;
    case BPTYPE_CONEKO:
        p = "���˂�";
        break;
    case BPTYPE_COINU:
        p = "������";
        break;
    case BPTYPE_COPANDA:
        p = "���ς�";
        break;
    case BPTYPE_CONEZUMI:
        p = "���˂���";
        break;
    case BPTYPE_UNKNOWN:
    default:
        p = "Blog Pet";
        break;
    }

    return ( p );
}
