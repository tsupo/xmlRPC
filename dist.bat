echo off

REM batch file for distribution of xmlRPC.dll
REM $Header: /comm/xmlRPC/dist.bat 1     09/05/14 3:46 tsupo $

chmod -R +w dist

rm -Rf dist\src

mkdir dist\src
mkdir dist\src\misc
mkdir dist\src\lib

copy *.c   dist\src
copy *.h   dist\src
copy *.def dist\src
copy *.rc  dist\src

copy misc\*.c   dist\src\misc
copy misc\*.h   dist\src\misc
copy misc\*.asm dist\src\misc

copy release\*.lib dist\src\lib

copy release\*.dll dist

rm -f dist\src\apiKey.h
