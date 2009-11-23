# Microsoft Developer Studio Project File - Name="xmlRPC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=xmlRPC - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "xmlRPC.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "xmlRPC.mak" CFG="xmlRPC - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "xmlRPC - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "xmlRPC - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/comm/xmlRPC", RCBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xmlRPC - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XMLRPC_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\openssl-0.9.8l\inc32" /I "..\..\libiconv-1.13.1\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XMLRPC_EXPORTS" /D "SUPPORT_FOR_WIN95" /D "USE_APIS" /FD /c
# SUBTRACT CPP /Fr /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 libeay32.lib ssleay32.lib iconv.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.277 /dll /machine:I386 /libpath:"..\..\openssl-0.9.8l\out32" /libpath:"..\..\libiconv-1.13.1\windows\release"
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "xmlRPC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XMLRPC_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /I "..\..\openssl-0.9.8l\inc32" /I "..\..\libiconv-1.13.1\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XMLRPC_EXPORTS" /D "SUPPORT_FOR_WIN95" /D "USE_APIS" /FR /FD /GZ /c
# SUBTRACT CPP /u /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libeay32d.lib ssleay32d.lib iconv.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.277 /dll /incremental:no /map /debug /machine:I386 /pdbtype:sept /libpath:"..\..\openssl-0.9.8l\out32_debug" /libpath:"..\..\libiconv-1.13.1\windows\debug"

!ENDIF 

# Begin Target

# Name "xmlRPC - Win32 Release"
# Name "xmlRPC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\misc\alloca_probe_16.asm

!IF  "$(CFG)" == "xmlRPC - Win32 Release"

# Begin Custom Build
TargetDir=.\Release
InputPath=.\misc\alloca_probe_16.asm
InputName=alloca_probe_16

"$(TargetDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Zi /Fo"$(TargetDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "xmlRPC - Win32 Debug"

# Begin Custom Build
TargetDir=.\Debug
InputPath=.\misc\alloca_probe_16.asm
InputName=alloca_probe_16

"$(TargetDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Zi /Fo"$(TargetDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\amazon.c
# End Source File
# Begin Source File

SOURCE=.\atomApi.c
# End Source File
# Begin Source File

SOURCE=.\blogInfo.c
# End Source File
# Begin Source File

SOURCE=.\bluedot.c
# End Source File
# Begin Source File

SOURCE=.\bulkfeed.c
# End Source File
# Begin Source File

SOURCE=.\misc\changeCode.c
# ADD CPP /I "."
# End Source File
# Begin Source File

SOURCE=.\misc\changeCode2.c
# ADD CPP /I "."
# End Source File
# Begin Source File

SOURCE=.\cocolog.c
# End Source File
# Begin Source File

SOURCE=.\codeTbl.c
# End Source File
# Begin Source File

SOURCE=.\console.c
# End Source File
# Begin Source File

SOURCE=.\cookie.c
# End Source File
# Begin Source File

SOURCE=.\cousagi.c
# End Source File
# Begin Source File

SOURCE=.\misc\decodeURL.c
# End Source File
# Begin Source File

SOURCE=.\delicious.c
# End Source File
# Begin Source File

SOURCE=.\deliciousApi.c
# End Source File
# Begin Source File

SOURCE=.\misc\encodeURL.c
# ADD CPP /I "."
# End Source File
# Begin Source File

SOURCE=.\encryptRSA.c
# End Source File
# Begin Source File

SOURCE=.\misc\ftol2.c
# End Source File
# Begin Source File

SOURCE=.\hatenaApi.c
# End Source File
# Begin Source File

SOURCE=.\http.c
# End Source File
# Begin Source File

SOURCE=.\httpGet.c
# End Source File
# Begin Source File

SOURCE=.\httpPost.c
# End Source File
# Begin Source File

SOURCE=.\https.c
# End Source File
# Begin Source File

SOURCE=.\isbn.c
# End Source File
# Begin Source File

SOURCE=.\md5.c
# End Source File
# Begin Source File

SOURCE=.\misc.c
# End Source File
# Begin Source File

SOURCE=.\multipart.c
# End Source File
# Begin Source File

SOURCE=.\rakuten.c
# End Source File
# Begin Source File

SOURCE=.\misc\setSigInfo.c
# End Source File
# Begin Source File

SOURCE=.\sha1.c
# End Source File
# Begin Source File

SOURCE=.\misc\strncmpi.c
# End Source File
# Begin Source File

SOURCE=.\misc\ulldvrm.asm

!IF  "$(CFG)" == "xmlRPC - Win32 Release"

# Begin Custom Build
TargetDir=.\Release
InputPath=.\misc\ulldvrm.asm
InputName=ulldvrm

"$(TargetDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Fo"$(TargetDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "xmlRPC - Win32 Debug"

# Begin Custom Build
TargetDir=.\Debug
InputPath=.\misc\ulldvrm.asm
InputName=ulldvrm

"$(TargetDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Zi /Fo"$(TargetDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\winsock.c
# End Source File
# Begin Source File

SOURCE=.\xmlRPC.c
# End Source File
# Begin Source File

SOURCE=.\xmlRPC.def
# End Source File
# Begin Source File

SOURCE=.\xmlRPCapi.c
# End Source File
# Begin Source File

SOURCE=.\xmlRPCutil.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\amazon.h
# End Source File
# Begin Source File

SOURCE=.\apiKey.h
# End Source File
# Begin Source File

SOURCE=.\atomApi.h
# End Source File
# Begin Source File

SOURCE=.\bluedot.h
# End Source File
# Begin Source File

SOURCE=.\codeTbl.h
# End Source File
# Begin Source File

SOURCE=.\delicious.h
# End Source File
# Begin Source File

SOURCE=.\deliciousApi.h
# End Source File
# Begin Source File

SOURCE=.\encryptRSA.h
# End Source File
# Begin Source File

SOURCE=.\hatenaApi.h
# End Source File
# Begin Source File

SOURCE=.\http.h
# End Source File
# Begin Source File

SOURCE=.\misc\kanjidata.h
# End Source File
# Begin Source File

SOURCE=.\md5.h
# End Source File
# Begin Source File

SOURCE=.\multipart.h
# End Source File
# Begin Source File

SOURCE=.\rakuten.h
# End Source File
# Begin Source File

SOURCE=.\sha1.h
# End Source File
# Begin Source File

SOURCE=.\stdint.h
# End Source File
# Begin Source File

SOURCE=.\xmlRPC.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\xmlRPC.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\dist.bat
# End Source File
# End Target
# End Project
