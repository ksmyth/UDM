@echo off

setlocal

set _UDM_PATH=%~dp0..
set _VC=%1%
shift
set _UDM_BUILD=%1%
shift

rem Set environment
call "%_UDM_PATH%\scripts\%_VC%-env.bat"
if ERRORLEVEL 1 echo Environment not set & exit /b

pushd %_UDM_PATH%\Build\Win32\%_VC%\%_UDM_BUILD%\Gen
zip -r %_UDM_PATH%\model-files-%_VC%-%_UDM_BUILD%.zip . -i *_udm.xml -i *_udm.udm
popd

pushd %_UDM_PATH%
zip -r %_UDM_PATH%\model-files-%_VC%-%_UDM_BUILD%.zip judm -i *_udm.xml -i *_udm.udm -x judm/build/*
popd

pushd %_UDM_PATH%
zip -r %_UDM_PATH%\model-files-%_VC%-%_UDM_BUILD%.zip tests -i *_udm.xml -i *_udm.udm
popd

pushd %_UDM_PATH%
zip -r %_UDM_PATH%\model-files-%_VC%-%_UDM_BUILD%.zip samples -i *_udm.xml -i *_udm.udm
popd

exit /b
