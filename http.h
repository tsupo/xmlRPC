/*
 *  http.h
 *
 * History:
 * $Log: /comm/xmlRPC/http.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 9     08/12/02 21:07 Tsujimura543
 * �R�����g���̒Ԃ�~�X�𔭌��A�C��
 * 
 * 8     07/09/14 22:39 Tsujimura543
 * MAX_URLLENGTH_MAX �̒�`�� xmlRPC.h �Ɉړ�
 * 
 * 7     06/09/26 18:50 Tsujimura543
 * MAX_URLLENGTH_MAX �̒�`�� http.c ���� http.h �ֈڂ�
 * 
 * 6     05/10/18 18:46 Tsujimura543
 * _httpExecute() �̈����ǉ��ɔ����e��ύX�����{
 * 
 * 5     05/06/28 15:22 Tsujimura543
 * _httpPost() �� BASIC�F�ؑΉ���
 * 
 * 4     05/05/31 22:50 Tsujimura543
 * _httpExecute() �̃v���g�^�C�v�錾���C��
 * 
 * 3     05/05/24 14:43 Tsujimura543
 * BASIC�F�؂ɑΉ�
 * 
 * 2     04/11/24 15:48 Tsujimura543
 * http �֘A���ʊ֐��𐮗�
 * 
 * 1     04/11/24 15:29 Tsujimura543
 * _httpExecute() �̃v���g�^�C�v�錾���w�b�_�t�@�C���Ɉړ�
 */

#ifndef __HTTP_H__
#define __HTTP_H__

/* HTTP���N�G�X�g���s�����{�� */
int
_httpExecute( const char *method,
              const char *webServer, const char *webPage,
              const char *mimeType,/* �� �K�v�Ȃ̂� POST, PUT �̂� */
              const char *sndBody, /* �� �K�v�Ȃ̂� POST, PUT �̂� */
              const char *userName,/* �� �K�v�Ȃ̂� BASIC�F�؎g�p���̂� */
              const char *password,/* �� �K�v�Ȃ̂� BASIC�F�؎g�p���̂� */
              char *rcvBody, FILE *output, int printHead,
              const char *wsse, char *p3p, char *cookie,
              char *webServerRedirected,    /* for TypeKey */
              char *cookieRedirected,       /* for TypeKey */
              int stackCount );

int
_httpGet( const char *webServer, const char *webPage,
          const char *userName,/* �� �K�v�Ȃ̂� BASIC�F�؎g�p���̂� */
          const char *password,/* �� �K�v�Ȃ̂� BASIC�F�؎g�p���̂� */
          char *rcvBody, FILE *output, int printHead,
          const char *wsse, char *p3p, char *cookie,
          char *webServerRedirected, char *cookieRedirected );

int
_httpDelete( const char *webServer, const char *webPage,
             const char *userName,/* �� �K�v�Ȃ̂� BASIC�F�؎g�p���̂� */
             const char *password,/* �� �K�v�Ȃ̂� BASIC�F�؎g�p���̂� */
             char *rcvBody, FILE *output, int printHead,
             const char *wsse );

int
_httpPost( const char *webServer, const char *webPage,
           const char *userName,/* �� �K�v�Ȃ̂� BASIC�F�؎g�p���̂� */
           const char *password,/* �� �K�v�Ȃ̂� BASIC�F�؎g�p���̂� */
           const char *mimeType,
           const char *sndBody, char *rcvBody,
           const char *wsse,    char *cookie,
           char *webServerRedirected, char *cookieRedirected );

#endif  /* __HTTP_H__ */
