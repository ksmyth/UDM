@echo off

: Read UDM_3RDPARTY_PATH and JDK_PATH from script with local settings
if exist "%~dp0"vc9-env-local.bat call "%~dp0"vc9-env-local.bat

if not defined UDM_3RDPARTY_PATH echo Set UDM_3RDPARTY_PATH & exit /b 1
if not defined JDK_PATH echo Set JDK_PATH & exit /b 1
if not defined GME_ROOT echo Set GME_ROOT & exit /b 1

if defined UDM_PATH goto :udm_path_set

rem Determine UDM_PATH
pushd %CD%
rem cd to the parent directory of this script
cd /d %~dp0..
set UDM_PATH=%CD%
popd

:udm_path_set

set PATH=%UDM_3RDPARTY_PATH%\xerces-c_2_8_0\bin;^
%UDM_3RDPARTY_PATH%\xalan-c_1_11_0\bin;^
%UDM_3RDPARTY_PATH%\cppunit-1.12.1\bin;^
%UDM_3RDPARTY_PATH%\info-zip;^
%UDM_3RDPARTY_PATH%\sed;^
%UDM_3RDPARTY_PATH%\swigwin-2.0.0;^
%UDM_3RDPARTY_PATH%\ant-1.6.2\bin;^
%PATH%

set INCLUDE=%UDM_3RDPARTY_PATH%\xerces-c_2_8_0\include;^
%UDM_3RDPARTY_PATH%\Xalan-C_1_11_0\include;^
%UDM_3RDPARTY_PATH%\antlr-2.7.7\lib\cpp;^
%UDM_3RDPARTY_PATH%\zlib;^
%UDM_3RDPARTY_PATH%\zlib\contrib\minizip;^
%UDM_3RDPARTY_PATH%\cppunit-1.12.1\include;^
%UDM_3RDPARTY_PATH%\boost_1_36_0;^
%JDK_PATH%\include\win32;^
%JDK_PATH%\include;^
%GME_ROOT%\Interfaces;^
%GME_ROOT%\Gme\Interfaces;^
%INCLUDE%

set LIB=%UDM_3RDPARTY_PATH%\Xalan-C_1_11_0\lib;^
%UDM_3RDPARTY_PATH%\xerces-c_2_8_0\lib;^
%UDM_3RDPARTY_PATH%\zlib;^
%UDM_3RDPARTY_PATH%\antlr-2.7.7\lib;^
%UDM_3RDPARTY_PATH%\cppunit-1.12.1\lib;^
%JDK_PATH%\lib;^
%LIB%

set JAVA_HOME=%JDK_PATH%

set _CLASSPATH=%UDM_3RDPARTY_PATH%\junit\junit.jar;^
%UDM_3RDPARTY_PATH%\antlr-2.7.7\antlr.jar
if defined CLASSPATH (set CLASSPATH=%_CLASSPATH%;%CLASSPATH%) else (set CLASSPATH=%_CLASSPATH%)

set ANT_HOME=%UDM_3RDPARTY_PATH%\ant-1.6.2
