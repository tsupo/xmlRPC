//  $Header: /comm/xmlRPC/multipart.h 1     09/05/14 3:46 tsupo $
/*! @file
 *  @brief multipart/form-data ���������߂̊֐��Q
 *  @author tsujimura543
 *  @date $Date: 09/05/14 3:46 $
 *  @version $Revision: 1 $
 *  @note
 * History:
 * $Log: /comm/xmlRPC/multipart.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 5     07/12/06 1:14 Tsujimura543
 * makeMultiPartItem() �̈�����ǉ�
 * 
 * 4     05/09/08 15:28 Tsujimura543
 * ����ɃR�����g���C�� (�O���[�v��)
 * 
 * 3     05/09/08 15:10 Tsujimura543
 * �R�����g���C���A�ǉ�
 * 
 * 2     05/09/08 14:38 Tsujimura543
 * �R�����g�� doxygen �����ɏ�������
 * 
 * 1     04/09/07 10:41 Tsujimura543
 * myprofile.c ���� multipart �֘A�̋��ʊ֐��𕪗�
 */

#ifndef __MULTIPART_H__
#define __MULTIPART_H__

/** \defgroup multipart multipart/form-data �֘A */
/*@{*/
//! multipart ��؂�q�̐���
/**
 *  multipart ���\������e part ����؂镶����(��؂�q)�𐶐����܂��B
 *  \return multipart ��؂�q
 *  \note   �{�֐��́A�{���C�u�����O����͒��ڎQ�Ƃ��邱�Ƃ͂ł��܂���B
 */
char    *getMultiPartID( void );

//! multipart ���\������ part �̐���
/** \param[in] separator        multipart ��؂�q
 *  \param[in] itemType         �����̌^
 *  \param[in] itemName         �����̖��O
 *  \param[in] itemValueInteger
 *      �����̒l
 *      (�����l�AitemType �� \ref MULITIPART_ITEM_TYPE_INTEGER �̂Ƃ��̂ݗL��)
 *  \param[in] itemValueString
 *      �����̒l
 *      (������AitemType �� \ref MULITIPART_ITEM_TYPE_STRING �̂Ƃ��̂ݗL��)
 *  \return �������� part (������)
 *  \note   �{�֐��́A�{���C�u�����O����͒��ڎQ�Ƃ��邱�Ƃ͂ł��܂���B
 */
char    *
makeMultiPartItem( const char *separator,
                   int        itemType,
                   const char *itemName,
                   long       itemValueInteger,
                   const char *itemValueString,
                   size_t     *sz );
/*@}*/

/** \defgroup multipartType part �̎��
 *  \ingroup multipart
 */
/*@{*/
#define MULITIPART_ITEM_TYPE_INTEGER    0       //!< ����
#define MULITIPART_ITEM_TYPE_STRING     1       //!< ������
#define MULITIPART_ITEM_TYPE_FILE       2       //!< �t�@�C��
#define MULITIPART_ITEM_TYPE_BUFFERFREE 0xFF
                                //!< makeMultiPartItem() ����Ɨ̈����w��
/*@}*/

#endif  /* __MULTIPART_H__ */
