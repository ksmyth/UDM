@echo off

rem set JDK_PATH=c:\Program Files\Java\jdk1.6.0_16
rem set UMD_3RDPARTY_PATH=C:\Documents and Settings\kevin\My Documents\UDM\3rdparty_VS2008

pushd %CD%
cd /d %~dp0
pushd %CD%
cd ..\..\..\..
set UDM_PATH=%CD%
popd
popd

if not exist "%UDM_3RDPARTY_PATH%" echo Set UDM_3RDPARTY_PATH & goto :eof
if not exist "%JDK_PATH%" echo Set JDK_PATH & goto :eof
if not exist "%GME_ROOT%" echo Set GME_ROOT & goto :eof

set PATH=%UDM_3RDPARTY_PATH%\xerces-c_2_8_0\bin;%UDM_3RDPARTY_PATH%\xalan-c_1_11_0\bin;%UDM_3RDPARTY_PATH%\cppunit-1.12.1\bin;%UDM_3RDPARTY_PATH%\info-zip;%UDM_3RDPARTY_PATH%\sed;%UDM_3RDPARTY_PATH%\swigwin-1.3.36;%PATH%
set INCLUDE=%UDM_3RDPARTY_PATH%\xerces-c_2_8_0\include;%UDM_3RDPARTY_PATH%\Xalan-C_1_11_0\include;%UDM_3RDPARTY_PATH%\antlr-2.7.7\lib\cpp;%UDM_3RDPARTY_PATH%\zlib;%UDM_3RDPARTY_PATH%\zlib\contrib\minizip;%UDM_3RDPARTY_PATH%\cppunit-1.12.1\include;%UDM_3RDPARTY_PATH%\boost-1.34.1;%JDK_PATH%\include\win32;%JDK_PATH%\include;%GME_ROOT%\Include;%GME_ROOT%\Gme\Include;%GME_ROOT%\Interfaces;%GME_ROOT%\Gme\Interfaces
set LIB=%UDM_3RDPARTY_PATH%\Xalan-C_1_11_0\lib;%UDM_3RDPARTY_PATH%\xerces-c_2_8_0\lib;%UDM_3RDPARTY_PATH%\zlib;%UDM_3RDPARTY_PATH%\antlr-2.7.7\lib;%UDM_3RDPARTY_PATH%\cppunit-1.12.1\lib;%UDM_3RDPARTY_PATH%\boost-1.34.1\lib;%JDK_PATH%\lib
set CLASSPATH=%UDM_3RDPARTY_PATH%\antlr-2.7.7\antlr.jar;%CLASSPATH%
