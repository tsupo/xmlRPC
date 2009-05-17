//  $Header: /comm/xmlRPC/multipart.h 1     09/05/14 3:46 tsupo $
/*! @file
 *  @brief multipart/form-data を扱うための関数群
 *  @author tsujimura543
 *  @date $Date: 09/05/14 3:46 $
 *  @version $Revision: 1 $
 *  @note
 * History:
 * $Log: /comm/xmlRPC/multipart.h $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     07/12/06 1:14 Tsujimura543
 * makeMultiPartItem() の引数を追加
 * 
 * 4     05/09/08 15:28 Tsujimura543
 * さらにコメントを修正 (グループ化)
 * 
 * 3     05/09/08 15:10 Tsujimura543
 * コメントを修正、追加
 * 
 * 2     05/09/08 14:38 Tsujimura543
 * コメントを doxygen 向けに書き直し
 * 
 * 1     04/09/07 10:41 Tsujimura543
 * myprofile.c から multipart 関連の共通関数を分離
 */

#ifndef __MULTIPART_H__
#define __MULTIPART_H__

/** \defgroup multipart multipart/form-data 関連 */
/*@{*/
//! multipart 区切り子の生成
/**
 *  multipart を構成する各 part を区切る文字列(区切り子)を生成します。
 *  \return multipart 区切り子
 *  \note   本関数は、本ライブラリ外からは直接参照することはできません。
 */
char    *getMultiPartID( void );

//! multipart を構成する part の生成
/** \param[in] separator        multipart 区切り子
 *  \param[in] itemType         引数の型
 *  \param[in] itemName         引数の名前
 *  \param[in] itemValueInteger
 *      引数の値
 *      (整数値、itemType が \ref MULITIPART_ITEM_TYPE_INTEGER のときのみ有効)
 *  \param[in] itemValueString
 *      引数の値
 *      (文字列、itemType が \ref MULITIPART_ITEM_TYPE_STRING のときのみ有効)
 *  \return 生成した part (文字列)
 *  \note   本関数は、本ライブラリ外からは直接参照することはできません。
 */
char    *
makeMultiPartItem( const char *separator,
                   int        itemType,
                   const char *itemName,
                   long       itemValueInteger,
                   const char *itemValueString,
                   size_t     *sz );
/*@}*/

/** \defgroup multipartType part の種別
 *  \ingroup multipart
 */
/*@{*/
#define MULITIPART_ITEM_TYPE_INTEGER    0       //!< 整数
#define MULITIPART_ITEM_TYPE_STRING     1       //!< 文字列
#define MULITIPART_ITEM_TYPE_FILE       2       //!< ファイル
#define MULITIPART_ITEM_TYPE_BUFFERFREE 0xFF
                                //!< makeMultiPartItem() 内作業領域解放指示
/*@}*/

#endif  /* __MULTIPART_H__ */
