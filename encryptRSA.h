//  $Header: /comm/xmlRPC/encryptRSA.h 1     09/05/14 3:46 tsupo $
/*! @file
 *  @brief RSA による暗号化、復号を実行する
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
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 5     05/09/21 22:39 Tsujimura543
 * freeRSAkey() と freeRSAbuffer() を追加
 * 
 * 4     05/09/21 18:39 Tsujimura543
 * encodeByRSA() の第2引数を in のみから in,out に変更
 * 
 * 3     05/09/20 21:51 Tsujimura543
 * コメントを整理
 * 
 * 2     05/09/20 21:50 Tsujimura543
 * generateRSAkey() と recoveryRSAkey() のプロトタイプ宣言を本ライブラリ内
 * のみ見えるようにした
 * 
 * 1     05/09/20 21:42 Tsujimura543
 * 最初の版
 */

#ifndef __ENCRYPT_RSA_H__
#define __ENCRYPT_RSA_H__

/** \defgroup encryptRSA RSAによる暗号化・復号処理関連 */
/*@{*/
#ifdef  XMLRPC_EXPORTS
//! 鍵の生成
/**
 *  RSA鍵を生成します
 *  \param[out] rsaString   鍵対応文字列
 *  \return     RSA鍵
 *  \note   本関数は、本ライブラリ外からは直接参照することはできません。
 */
RSA *
generateRSAkey( unsigned char **rsaString );
#endif  /* XMLRPC_EXPORTS */

//! RSA による暗号化
/**
 *  RSA暗号化処理を実行します
 *  \param[in]      targetString    暗号化対象文字列(平文)
 *  \param[in,out]  rsaString       鍵対応文字列
 *  \param[out]     cryptedBuffer   暗号化されたバイナリ列
 *  \return     暗号化されたバイナリ列のサイズ(単位: バイト)
 *  \note     
 *      \li *rsaString が NULL もしくは **rsaString が NUL の場合、
 *         「鍵対応文字列」および「暗号化されたバイナリ列」
 *          (暗号化を実行した結果)
 *          を格納するための領域は本関数内で確保します。
 *          領域の解放は、本関数の呼び出し側で行なってください。
 *          なお、「鍵対応文字列」は復号時に使用します。
 *      \li **rsaString が非 NUL の場合、*rsaString 
 *          を元にRSA鍵を復元し、暗号化に使用します。
 *          既存・同一の鍵で複数の平文を個別に暗号化したい場合向けの機能です。
 */
int
encodeByRSA( const char    *targetString,
             unsigned char **rsaString,
             unsigned char **cryptedBuffer );

#ifdef  XMLRPC_EXPORTS
//! 鍵の復元
/**
 *  「鍵対応文字列」を元に、RSA鍵を復元します
 *  \param[in]  rsaString   鍵対応文字列
 *  \return     RSA鍵
 *  \note   本関数は、本ライブラリ外からは直接参照することはできません。
 */
RSA *
recoveryRSAkey( const unsigned char *rsaString );
#endif  /* XMLRPC_EXPORTS */

//! RSA による復号
/**
 *  RSA復号処理を実行します
 *  \param[out] targetString    復号結果文字列(平文)
 *  \param[in]  rsaString       鍵対応文字列
 *  \param[in]  cryptedBuffer   暗号化済みバイト列(復号対象)
 *  \param[in]  crypted_len     暗号化済みバイト列のサイズ
 *  \return     復号結果文字列のサイズ(単位: バイト)
 *  \note     「復号結果文字列」(復号を実行した結果)
 *            を格納するための領域は本関数で確保します。
 *            領域の解放は、本関数の呼び出し側で行なってください。
 */
int
decodeByRSA( char                **targetString,
             const unsigned char *rsaString,
             const unsigned char *cryptedBuffer,
             int                 crypted_len );

//! 「鍵対応文字列」の解放
/**
 *  「鍵対応文字列」格納領域を解放します
 *  \param[in]  rsaString   「鍵対応文字列」格納領域のアドレス
 *  \note   generateRSAkey() 内で確保した領域を解放するための関数です。
 */
void
freeRSAkey( unsigned char *rsaString );

//! 「暗号化結果」もしくは「復号結果」の解放
/**
 *  「暗号化結果」もしくは「復号結果」格納領域を解放します
 *  \param[in]  rsaString   「鍵対応文字列」格納領域のアドレス
 *  \note   recoveryRSAkey() もしくは decodeByRSA()
 *          内で確保した領域を解放するための関数です。
 */
void
freeRSAbuffer( char *buffer );
/*@}*/

#endif  /* __ENCRYPT_RSA_H__ */
