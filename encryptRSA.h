//  $Header: /comm/xmlRPC/encryptRSA.h 1     09/05/14 3:46 tsupo $
/*! @file
 *  @brief RSA �ɂ��Í����A���������s����
 *  @author tsujimura543
 *  @date $Date: 09/05/14 3:46 $
 *  @version $Revision: 1 $
 *  @attention
 *      \li Copyright (c) 2005 by H.Tsujimura
 *      \li written by H.Tsujimura
 *      \li mailto: tsupo@na.rim.or.jp
 *
 *  @note
 * History:
 * $Log: /comm/xmlRPC/encryptRSA.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     05/09/21 22:39 Tsujimura543
 * freeRSAkey() �� freeRSAbuffer() ��ǉ�
 * 
 * 4     05/09/21 18:39 Tsujimura543
 * encodeByRSA() �̑�2������ in �݂̂��� in,out �ɕύX
 * 
 * 3     05/09/20 21:51 Tsujimura543
 * �R�����g�𐮗�
 * 
 * 2     05/09/20 21:50 Tsujimura543
 * generateRSAkey() �� recoveryRSAkey() �̃v���g�^�C�v�錾��{���C�u������
 * �̂݌�����悤�ɂ���
 * 
 * 1     05/09/20 21:42 Tsujimura543
 * �ŏ��̔�
 */

#ifndef __ENCRYPT_RSA_H__
#define __ENCRYPT_RSA_H__

/** \defgroup encryptRSA RSA�ɂ��Í����E���������֘A */
/*@{*/
#ifdef  XMLRPC_EXPORTS
//! ���̐���
/**
 *  RSA���𐶐����܂�
 *  \param[out] rsaString   ���Ή�������
 *  \return     RSA��
 *  \note   �{�֐��́A�{���C�u�����O����͒��ڎQ�Ƃ��邱�Ƃ͂ł��܂���B
 */
RSA *
generateRSAkey( unsigned char **rsaString );
#endif  /* XMLRPC_EXPORTS */

//! RSA �ɂ��Í���
/**
 *  RSA�Í������������s���܂�
 *  \param[in]      targetString    �Í����Ώە�����(����)
 *  \param[in,out]  rsaString       ���Ή�������
 *  \param[out]     cryptedBuffer   �Í������ꂽ�o�C�i����
 *  \return     �Í������ꂽ�o�C�i����̃T�C�Y(�P��: �o�C�g)
 *  \note     
 *      \li *rsaString �� NULL �������� **rsaString �� NUL �̏ꍇ�A
 *         �u���Ή�������v����сu�Í������ꂽ�o�C�i����v
 *          (�Í��������s��������)
 *          ���i�[���邽�߂̗̈�͖{�֐����Ŋm�ۂ��܂��B
 *          �̈�̉���́A�{�֐��̌Ăяo�����ōs�Ȃ��Ă��������B
 *          �Ȃ��A�u���Ή�������v�͕������Ɏg�p���܂��B
 *      \li **rsaString ���� NUL �̏ꍇ�A*rsaString 
 *          ������RSA���𕜌����A�Í����Ɏg�p���܂��B
 *          �����E����̌��ŕ����̕������ʂɈÍ����������ꍇ�����̋@�\�ł��B
 */
int
encodeByRSA( const char    *targetString,
             unsigned char **rsaString,
             unsigned char **cryptedBuffer );

#ifdef  XMLRPC_EXPORTS
//! ���̕���
/**
 *  �u���Ή�������v�����ɁARSA���𕜌����܂�
 *  \param[in]  rsaString   ���Ή�������
 *  \return     RSA��
 *  \note   �{�֐��́A�{���C�u�����O����͒��ڎQ�Ƃ��邱�Ƃ͂ł��܂���B
 */
RSA *
recoveryRSAkey( const unsigned char *rsaString );
#endif  /* XMLRPC_EXPORTS */

//! RSA �ɂ�镜��
/**
 *  RSA�������������s���܂�
 *  \param[out] targetString    �������ʕ�����(����)
 *  \param[in]  rsaString       ���Ή�������
 *  \param[in]  cryptedBuffer   �Í����ς݃o�C�g��(�����Ώ�)
 *  \param[in]  crypted_len     �Í����ς݃o�C�g��̃T�C�Y
 *  \return     �������ʕ�����̃T�C�Y(�P��: �o�C�g)
 *  \note     �u�������ʕ�����v(���������s��������)
 *            ���i�[���邽�߂̗̈�͖{�֐��Ŋm�ۂ��܂��B
 *            �̈�̉���́A�{�֐��̌Ăяo�����ōs�Ȃ��Ă��������B
 */
int
decodeByRSA( char                **targetString,
             const unsigned char *rsaString,
             const unsigned char *cryptedBuffer,
             int                 crypted_len );

//! �u���Ή�������v�̉��
/**
 *  �u���Ή�������v�i�[�̈��������܂�
 *  \param[in]  rsaString   �u���Ή�������v�i�[�̈�̃A�h���X
 *  \note   generateRSAkey() ���Ŋm�ۂ����̈��������邽�߂̊֐��ł��B
 */
void
freeRSAkey( unsigned char *rsaString );

//! �u�Í������ʁv�������́u�������ʁv�̉��
/**
 *  �u�Í������ʁv�������́u�������ʁv�i�[�̈��������܂�
 *  \param[in]  rsaString   �u���Ή�������v�i�[�̈�̃A�h���X
 *  \note   recoveryRSAkey() �������� decodeByRSA()
 *          ���Ŋm�ۂ����̈��������邽�߂̊֐��ł��B
 */
void
freeRSAbuffer( char *buffer );
/*@}*/

#endif  /* __ENCRYPT_RSA_H__ */
