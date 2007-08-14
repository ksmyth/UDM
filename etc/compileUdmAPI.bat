call vcvars32.bat

echo generate MPC file
%UDM_PATH%/etc/mpcgen.exe %1 %2

echo call MPC
%UDM_PATH%/3rdparty/mpc/mpc %1.mpc -static -type vc71

echo compile project
devenv /build RELEASE %1.vcproj
devenv /build DEBUG %1.vcproj