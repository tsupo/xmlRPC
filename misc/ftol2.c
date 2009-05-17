/*
 *  ftol2.c
 *      OpenSSL �̃X�^�e�B�b�N���C�u�������g���ɂ������ĕK�v�ȏ���
 *      (http://watcher.moe-nifty.com/memo/2005/09/openssl_098__wi_9fb8.html)
 *
 * History:
 * $Log: /comm/xmlRPC/misc/ftol2.c $
 * 
 * 1     09/05/14 3:46 tsupo
 * (1) �r���h���̃f�B���N�g���\���𐮗�
 * (2) VSS�T�[�o���_��ύX
 * 
 * 4     08/11/26 20:40 Tsujimura543
 * OpenSSL 0.9.8i ������ _ftol2_sse() ��p�� [�b��]
 * 
 * 3     07/12/20 15:20 Tsujimura543
 * Visual Studio 2005 �ɂ��R���p�C���`�F�b�N���ʂ𔽉f
 * 
 * 2     07/11/19 18:29 Tsujimura543
 * ����m�F����
 * 
 * 1     07/11/19 18:27 Tsujimura543
 * OpenSSL 0.9.8g �ɐ؂�ւ���ɂ������āA_ftol2() ���Ăїp�ӂ���K�v��
 * �����������߁AxmlRPC.dll ���� _ftol2() ��p�ӂ��邱�ƂőΉ�����
 * (OpenSSL�̃X�^�e�B�b�N���C�u�����̓r���h���������Ƃ͂����A�z�z�����
 * ������̂����̂܂܎g�����Ƃɂ���)
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
