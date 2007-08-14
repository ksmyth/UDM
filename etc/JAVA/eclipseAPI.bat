cls

@echo off

rem if "%3"=="" goto usage

chdir > d
set /p curr_dir=<"d"

echo Generate domain-specific %1 jUdm source ...
%UDM_PATH%\bin\udm.exe %2 -java %3
echo Done

echo Generate the domain-specific %1 eclipse project ...
%UDM_3RDPARTY_PATH%\ant-1.6.2\bin\ant -f %UDM_PATH%\etc\java\etc\build.xml -Dbasedir=%curr_dir% -Ddspackage=%1 -quiet eclipse
echo Done

goto end

:usage
echo .
echo eclipseApi: Wrong parameter!
echo Usage:   %%UDM_PATH%%\etc\java\eclipseAPI [eclipse_project_name] [UML_meta_model] [UDM_parameters]
echo Example: %%UDM_PATH%%\etc\java\eclipseAPI SBML2Ex SBML2Ex_udm.xml "-i jigcell -q jigcell -e"
goto end
:end