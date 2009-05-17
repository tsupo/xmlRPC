/*
 *  ftol2.c
 *      OpenSSL のスタティックライブラリを使うにあたって必要な処理
 *      (http://watcher.moe-nifty.com/memo/2005/09/openssl_098__wi_9fb8.html)
 *
 * History:
 * $Log: /comm/xmlRPC/misc/ftol2.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) ビルド環境のディレクトリ構造を整理
 * (2) VSSサーバ拠点を変更
 * 
 * 4     08/11/26 20:40 Tsujimura543
 * OpenSSL 0.9.8i 向けに _ftol2_sse() を用意 [暫定]
 * 
 * 3     07/12/20 15:20 Tsujimura543
 * Visual Studio 2005 によるコンパイルチェック結果を反映
 * 
 * 2     07/11/19 18:29 Tsujimura543
 * 動作確認完了
 * 
 * 1     07/11/19 18:27 Tsujimura543
 * OpenSSL 0.9.8g に切り替えるにあたって、_ftol2() を再び用意する必要が
 * 発生したため、xmlRPC.dll 内に _ftol2() を用意することで対応する
 * (OpenSSLのスタティックライブラリはビルドし直すことはせず、配布されて
 * いるものをそのまま使うことにする)
 */

// only for MSDEV 6.0
//#if (_MSC_VER == 1200) && (WINVER < 0x0500)
#if	_MSC_VER < 1400
# ifdef __cplusplus
extern "C" {
# endif
    long _ftol( double ); // defined by VC6 C libs
# ifdef cplusplus
}
# endif

# ifdef __cplusplus
extern "C" {
# endif
    long _ftol2( double dblSource )
    {
        return _ftol( dblSource );
    }

    long _ftol2_sse( double dblSource )
    {
        return _ftol( dblSource );
    }
# ifdef cplusplus
}
# endif
#else
#ifdef	_MSC_VER
#pragma warning (disable: 4206)
#endif
#endif
//#endif
