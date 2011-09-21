@echo off

if /i not "%1"=="VC9" goto :usage
if /i not "%2"=="Debug" if /i not "%2"=="Release" goto :usage

rem Run ant
cmd /c "call "%~dp0_%~nx0" %*"

exit /b

:usage
echo Runs ant on judm, with the specified UDM build
echo Usage: %0 ^<VC9^> ^<Debug^|Release^> ^<parameters to ant^>
exit /b
