; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

; Requires Inno Setup Preprocessor by Alex Yackimoff
#pragma option -v+
#pragma verboselevel 9

#define GMEVER "10.8.18"

#define UDMPATH GetEnv('UDM_PATH')
#define UDM3rdPartyPATH GetEnv('UDM_3RDPARTY_PATH')
#define GREATPATH GetEnv('GREAT_PATH')

#define UDMDLL "UdmDll_3_2.dll"
#define UDMDLLD "UdmDll_3_2D.dll"
#define UDMDLLVS10 "UdmDll_3_2_VS10.dll"
#define UDMDLLDVS10 "UdmDll_3_2_VS10D.dll"

#define UDMVER GetEnv('UDM_VERSION')
#if UDMVER == ""
#define UDMVER "3.2.7"
#endif
#define OutputFileBase "Udm_setup"

[Setup]
AppID=ISIS UDM
AppName=UDM {#UDMVER}
APPVerName=ISIS UDM v{#UDMVER}
AppVersion={#UDMVER}
AppPublisher=ISIS, Vanderbilt University
AppPublisherURL=http://www.escherinstitute.org/Plone/tools/suites/mic/udm
AppSupportURL=http://www.escherinstitute.org/Plone/tools/suites/mic/udm
AppUpdatesURL=http://www.escherinstitute.org/Plone/tools/suites/mic/udm
DefaultDirName={pf}\ISIS\UDM
DefaultGroupName=UDM
LicenseFile={#UDMPATH}\license.txt
InfoBeforeFile={#UDMPATH}\releaseinfo.txt
OutputDir={#UDMPATH}\InnoSetup
OutputBaseFilename={#OutputFileBase}
Compression=lzma
SolidCompression=yes
ChangesEnvironment=true
AppCopyright=Copyright (C) 2001-2011 ISIS, Vanderbilt University

[Languages]
Name: english; MessagesFile: compiler:Default.isl

[Types]
Name: Full; Description: Full; Flags: iscustom
Name: Typical; Description: Typical

[Components]
Name: Core; Description: Core UDM; Types: Typical Full; Flags: fixed
Name: C; Description: C++ UDM; Types: Typical Full; Flags: fixed
Name: Clibs; Descriptions: C++ UDM Static Libraries (deprecated); Types: Typical Full
Name: Java; Description: Java UDM; Types: Full Typical
Name: Python; Description: Python UDM; Types: Full Typical
Name: CS; Description: C# UDM; Types: Full Typical
Name: System; Description: Register Environment Variables System-Wide (recommended); Types: Typical Full
Name: Full3rdParty; Description: Full 3rdParty Package (deprecated); Types: Full

[Files]
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
;Udm Root folder
Source: {#UDMPATH}\releaseinfo.txt; DestDir: {app}; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\license.txt; DestDir: {app}; Components: Core
; Udm_3rdparty_files
Source: {#UDM3rdPartyPath}\mpc\*; DestDir: {app}\3rdparty\mpc; Excludes: clone_build_tree.exe, mnwc.exe, prj_install.exe, .svn; Components: C Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\mpc\config\*; DestDir: {app}\3rdparty\mpc\config; Excludes: .svn; Components: C Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\mpc\devtools\*; DestDir: {app}\3rdparty\mpc\devtools; Excludes: .svn; Components: C Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\mpc\docs\*; DestDir: {app}\3rdparty\mpc\docs; Excludes: .svn; Components: C Full3rdParty; Flags: ignoreversion recursesubdirs
Source: {#UDM3rdPartyPath}\mpc\history\*; DestDir: {app}\3rdparty\mpc\history; Excludes: .svn; Components: C Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\mpc\modules\*; DestDir: {app}\3rdparty\mpc\modules; Excludes: .svn; Components: C Full3rdParty; Flags: ignoreversion recursesubdirs
Source: {#UDM3rdPartyPath}\mpc\templates\*; DestDir: {app}\3rdparty\mpc\templates; Excludes: .svn; Components: C Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_11_0\bin\*; DestDir: {app}\3rdparty\xalan-c_1_11_0\bin; Excludes: ".svn,*.pdb"; Components: Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_11_0\include\*; DestDir: {app}\3rdparty\xalan-c_1_11_0\include; Excludes: .svn; Components: Full3rdParty; Flags: ignoreversion recursesubdirs createallsubdirs
Source: {#UDM3rdPartyPath}\xalan-c_1_11_0\lib\*; DestDir: {app}\3rdparty\xalan-c_1_11_0\lib; Excludes: .svn; Components: Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xerces-c_2_8_0\bin\*; DestDir: {app}\3rdparty\xerces-c_2_8_0\bin; Excludes: ".svn,*.pdb"; Components: Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xerces-c_2_8_0\include\*; DestDir: {app}\3rdparty\xerces-c_2_8_0\include; Excludes: .svn; Components: Full3rdParty; Flags: ignoreversion recursesubdirs createallsubdirs
Source: {#UDM3rdPartyPath}\xerces-c_2_8_0\lib\*; DestDir: {app}\3rdparty\xerces-c_2_8_0\lib; Excludes: .svn; Components: Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\zlib\license.txt; DestDir: {app}\3rdparty\zlib; Components: Core Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\zlib\zlib.lib; DestDir: {app}\3rdparty\zlib; Components: Full3rdParty; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\zlib\zlibD.lib; DestDir: {app}\3rdparty\zlib; Components: Full3rdParty; Flags: ignoreversion
;Udm bin folder
Source: {#UDM3rdPartyPath}\xerces-c_2_8_0\bin\xerces-c_2_8.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xerces-c_2_8_0\bin\xerces-c_2_8D.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_11_0\bin\Xalan-C_1_11.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_11_0\bin\Xalan-C_1_11D.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_11_0\bin\XalanMessages_1_11.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_11_0\bin\XalanMessages_1_11D.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\{#UDMDLL}; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Debug\{#UDMDLLD}; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\GmeOclExprChecker.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion regserver
Source: {#UDMPATH}\Build\Win32\VC9\Release\UML2XML.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion regserver
Source: {#GREATPATH}\bin_vs9\MetaGME2Uml.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion regserver
Source: {#UDMPATH}\Build\Win32\VC9\Release\Udm.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmBackendDump.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmCopy.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmOclPat.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmToXmi.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmViz.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
;Source: {#UDMPATH}\Build\Win32\VC9\Release\UIntWiz.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\XmiToUdm.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmSwig.dll; DestDir: {app}\bin; Components: Java; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC10\Release\{#UDMDLLVS10}; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC10\Debug\{#UDMDLLDVS10}; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC10\Release\UdmCli.dll; DestDir: {app}\bin; StrongAssemblyName: "UdmCli, Version=3.2.7.0, Culture=neutral, PublicKeyToken=9b61694741cb5693, ProcessorArchitecture=x86"; Flags: "gacinstall sharedfile uninsnosharedfileprompt"; Components: CS
Source: {#UDMPATH}\Build\Win32\VC10\Release\UdmCliBridge.dll; DestDir: {app}\bin; Components: CS; Flags: ignoreversion
Source: {#UDMPATH}\src\UdmCliGen\dist\UdmCliGen.exe; DestDir: {app}\bin; Components: CS; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC10\Release\udm.pyd; DestDir: {app}\bin; Components: Python CS; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC10\Debug\udmd.pyd; DestDir: {app}\bin; Components: Python; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC10\Release27\udm27.pyd; DestDir: {app}\bin; Components: Python; Flags: ignoreversion
Source: {#UDMPATH}\bin\boost_python-vc100-mt-1_44.dll; DestDir: {app}\bin; Components: Python CS; Flags: ignoreversion
Source: {#UDMPATH}\judm\build\build_win\judm\judm.jar; DestDir: {app}\bin; Components: Java; Flags: ignoreversion
;Udm Doc folder
Source: {#UDMPATH}\doc\UDMAPI.pdf; DestDir: {app}\doc; Flags: ignoreversion; Components: Core
Source: {#UDMPATH}\doc\UdmInterpreterWizard.pdf; DestDir: {app}\doc; Flags: ignoreversion; Components: Core
Source: {#UDMPATH}\judm\build\build_win\judm\apidoc\*; DestDir: {app}\doc\apidoc; Excludes: .svn; Flags: recursesubdirs createallsubdirs ignoreversion; Components: Java
;Udm etc folder
Source: {#UDMPATH}\etc\MPCGen.exe; DestDir: {app}\etc; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\etc\StrResGen.exe; DestDir: {app}\etc; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\etc\CreateUdmXml.vbs; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\compileUdmAPI.bat; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\CreateMGA.vbs; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\CreateXmp.vbs; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\Uml.xsd; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\UdmProject.xme; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\UdmProject_udm.xml; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\UdmProject.xsd; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\Uml.xml; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\Xme2UdmXml.bat; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\UmlInUml.xme; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\UmlMeta.xme; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\JAVA\judmAPI.bat; DestDir: {app}\etc\Java; Components: Java; Flags: ignoreversion
Source: {#UDMPATH}\etc\JAVA\.classpath; DestDir: {app}\etc\Java; Components: Java; Flags: ignoreversion
Source: {#UDMPATH}\etc\JAVA\.project; DestDir: {app}\etc\Java; Components: Java; Flags: ignoreversion
Source: {#UDMPATH}\etc\JAVA\build.xml; DestDir: {app}\etc\Java; Components: Java; Flags: ignoreversion
Source: {#UDMPATH}\etc\JAVA\eclipseAPI.bat; DestDir: {app}\etc\Java; Components: Java; Flags: ignoreversion
;Udm include folder
Source: {#UDMPATH}\include\UdmBase.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\Uml_export.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmXmi.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\cint_string.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmUtil.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\ErrHand.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmGme.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmProject.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmDom.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmOcl.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmCintSwig.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmStatic.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UmlExt.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\Uml.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
Source: {#UDMPATH}\include\UdmMPL.h; DestDir: {app}\include; Flags: ignoreversion; Components: C
;Udm lib folder
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmDll.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC10\Release\UdmDll_VS10.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UdmDllD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC10\Debug\UdmDll_VS10D.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\Build\Win32\VC9\Debug\GOCLD.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UdmXmiD.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UdmUtilD.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UmlD.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UdmPOID.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UdmDomD.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UdmGmeD.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UdmOclD.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Debug\UdmBaseD.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\GOCL.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmXmi.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmUtil.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\Uml.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmPOI.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmDom.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmGme.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmOcl.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
Source: {#UDMPATH}\Build\Win32\VC9\Release\UdmBase.lib; DestDir: {app}\lib; Flags: ignoreversion; Components: CLibs
;Udm Interpreter Wizard Script folder
Source: {#UDMPATH}\src\UIntWizVS\*; DestDir: {app}\UdmIntWizard; Excludes: setup80.*,*.ncb,*.suo,*.user,.svn; Flags: ignoreversion recursesubdirs createallsubdirs; Components: C
;Udm Samples folder/C++
Source: {#UDMPATH}\Projects\Win32\VC9\samples\samples-paths-installer.vsprops; DestDir: {app}\samples\C++; DestName: "samples-paths.vsprops"; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\Projects\Win32\VC9\samples\CreateLampModel\CreateLampModel.vcproj; DestDir: {app}\samples\C++\CreateLampModel; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\CreateLampModel\LampDiagramGME.xme; DestDir: {app}\samples\C++\CreateLampModel; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\CreateLampModel\LampDiagramUML.xme; DestDir: {app}\samples\C++\CreateLampModel; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\CreateLampModel\CreateLampModel.rc; DestDir: {app}\samples\C++\CreateLampModel; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\CreateLampModel\CreateLampModel.cpp; DestDir: {app}\samples\C++\CreateLampModel; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\Projects\Win32\VC9\samples\cross_links\cross_links.vcproj; DestDir: {app}\samples\C++\cross_links; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\cross_links\cross_links.cpp; DestDir: {app}\samples\C++\cross_links; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\cross_links\CL.xme; DestDir: {app}\samples\C++\cross_links; Components: C; Flags: ignoreversion
;Udm Samples folder/java
Source: {#UDMPATH}\judm\build\build_win\GeneTF\*; DestDir: {app}\samples\java\GeneTF; Excludes: "\apidoc\*,\classes\*,"; Components: Java; Flags: recursesubdirs createallsubdirs ignoreversion
Source: {#UDMPATH}\judm\build\build_win\GeneTRE\*; DestDir: {app}\samples\java\GeneTRE; Excludes: "\apidoc\*,\classes\*,"; Components: Java; Flags: recursesubdirs createallsubdirs ignoreversion
Source: {#UDMPATH}\judm\build\build_win\SBML2Ex\*; DestDir: {app}\samples\java\SBML2Ex; Excludes: "\apidoc\*,\classes\*,"; Components: Java; Flags: recursesubdirs createallsubdirs ignoreversion
; Python samples
Source: {#UDMPATH}\tests\test_UdmPython\UdmPythonTestMeta.xme; DestDir: {app}\samples\python\UdmPythonTest; Components: Python
Source: {#UDMPATH}\tests\test_UdmPython\UdmPythonTestMeta.xml; DestDir: {app}\samples\python\UdmPythonTest; Components: Python
Source: {#UDMPATH}\tests\test_UdmPython\UdmPythonTestMeta.xmp; DestDir: {app}\samples\python\UdmPythonTest; Components: Python
Source: {#UDMPATH}\tests\test_UdmPython\UdmPythonTestModel.xme; DestDir: {app}\samples\python\UdmPythonTest; Components: Python
Source: {#UDMPATH}\tests\test_UdmPython\udm_python_test.py; DestDir: {app}\samples\python\UdmPythonTest; Components: Python

[Messages]
SelectComponentsLabel2=Select the setup type that best suits your needs. Click Next when you are ready to continue.

[Registry]
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: UDM_PATH; ValueData: {app}; Flags: uninsdeletevalue deletevalue; Components: not System
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: UDM_3RDPARTY_PATH; ValueData: {app}\3rdparty; Flags: uninsdeletevalue deletevalue; Components: not System
Root: HKLM; Subkey: SYSTEM\CurrentControlSet\Control\Session Manager\Environment; ValueType: string; ValueName: UDM_PATH; ValueData: {app}; Flags: uninsdeletevalue deletevalue; Components: System
Root: HKLM; Subkey: SYSTEM\CurrentControlSet\Control\Session Manager\Environment; ValueType: string; ValueName: UDM_3RDPARTY_PATH; ValueData: {app}\3rdparty; Flags: uninsdeletevalue deletevalue; Components: System
Root: HKLM; Subkey: SOFTWARE\Microsoft\.NETFramework\v2.0.50727\AssemblyFoldersEx\UdmCli; ValueType: string; ValueData: "C:\Windows\assembly\GAC_32\UdmCli\3.2.7.0__9b61694741cb5693"; Flags: uninsdeletevalue deletevalue


[Run]
Filename: {app}\UdmIntWizard\setup90.bat; Flags: skipifdoesntexist postinstall runhidden; Description: Install Udm-based Interpreter project wizard for visual studio 2008; Components: C

[Code]
var
  InstallSystemWide: Boolean;

function InitializeUninstall(): Boolean;
begin
  //Need to know if this was a system wide install or not
  InstallSystemWide := RegValueExists(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'UDM_PATH');
  Result := True;
end;

Procedure ModPath(const ValueName, pathdir: String);
var
	oldpath:	String;
	newpath:	String;
	pathArr:	TArrayOfString;
	i:			Integer;
begin
	// Modify WinNT path
	if UsingWinNT() = true then begin

		// Get current path, split into an array
		if InstallSystemWide then begin
		  RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', ValueName, oldpath);
		end else begin
		  RegQueryStringValue(HKEY_CURRENT_USER, 'Environment', ValueName, oldpath);
    end;
		if oldpath <> '' then
			oldpath := oldpath + ';';
		i := 0;
		while (Pos(';', oldpath) > 0) do begin
			SetArrayLength(pathArr, i+1);
			pathArr[i] := Copy(oldpath, 0, Pos(';', oldpath)-1);
			oldpath := Copy(oldpath, Pos(';', oldpath)+1, Length(oldpath));
			i := i + 1;

			// Check if current directory matches app dir
			if pathdir = pathArr[i-1] then begin
				// if uninstalling, remove dir from path
				if IsUninstaller() = true then begin
					continue;
				// if installing, abort because dir was already in path
				end else begin
					exit;
				end;
			end;

			// Add current directory to new path
			if i = 1 then begin
				newpath := pathArr[i-1];
			end else begin
				newpath := newpath + ';' + pathArr[i-1];
			end;
		end;

		if IsUninstaller() = false then begin
			if newpath <> '' then begin
				newpath := newpath + ';' + pathdir;
			end else begin
				newpath := pathdir;
			end;
		end;

		// Write new path
		if InstallSystemWide then begin
		  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', ValueName, newpath);
		end else begin
		  RegWriteStringValue(HKEY_CURRENT_USER, 'Environment', ValueName, newpath);
    end;
	end;
end;

procedure CurStepChanged(CurStep: TSetupStep);
var
	path : String;
begin
	if CurStep = ssInstall then begin
		path := ExpandConstant('{app}');
//		RegWriteStringValue(HKEY_CURRENT_USER, 'Environment', 'UDM_PATH', path);
//		RegWriteStringValue(HKEY_CURRENT_USER, 'Environment', 'UDM_3RDPARTY_PATH', path+'3rdparty');
		ModPath('PATH', path+'\bin');
		ModPath('PATH', path+'\etc');
		ModPath('CLASSPATH', '.');
	end;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
	path : String;
begin
	if CurUninstallStep = usUninstall then begin
		path := ExpandConstant('{app}');
		ModPath('PATH', path+'\bin');
		ModPath('PATH', path+'\etc');
		ModPath('CLASSPATH', '.');
	end;
end;

function CheckVersions(): Boolean;
var
  gme_path : String;
  oGME :  Variant;
begin
  Result := True;
#ifdef GMEVER
  gme_path := GetEnv('GME_ROOT');
  /////////////////////////////////////////////////////////
  // CASE #1: No GME installed
  /////////////////////////////////////////////////////////
  if gme_path = '' then begin
    MsgBox('Unable to locate GME r{#GMEVER}.  Please install GME r{#GMEVER} first.', mbError, MB_OK);
    Result := False;
  /////////////////////////////////////////////////////////
  // ELSE: wrong GME installed
  ////////////////////////////////////////////////////////
  end else begin
    oGME := CreateOleObject('GME.Application');
	  if oGME.Version <> '{#GMEVER}' then begin
	  	Result := MsgBox('This version of UDM ({#UDMVER}) is recommended for use with GME {#GMEVER}. The currently installed GME version is '+oGME.Version+'.'#13#13+'Are you sure you wish to continue with the installation?', mbConfirmation, MB_YESNO) = idYes;
  	end
    IDispatchInvoke(oGME, False, 'Exit', []);
  end;
#endif
end;

function NextButtonClick(CurPageID: Integer): Boolean;
var
  MyComponents : String;
  MyCompLen : Integer;
begin
  Result := True;
  if CurPageID = wpSelectComponents then begin
    MyComponents := WizardSelectedComponents(false);
    MyCompLen := length(MyComponents);
    if Pos('system', MyComponents) <> 0 then begin
      InstallSystemWide := true;
    end else begin
      InstallSystemWide := false;
    end;
  end;
  if (CurPageID = wpInfoBefore) and not WizardSilent() then begin
    Result := CheckVersions();
  end;
end;

