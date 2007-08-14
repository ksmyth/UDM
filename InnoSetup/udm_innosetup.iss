; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

; Requires Inno Setup Preprocessor by Alex Yackimoff
#pragma option -v+
#pragma verboselevel 9

#define UDMPATH "C:\Projects\udm_ns2"
#define UDM3rdPartyPATH "C:\Projects\udm_ns_3rdparty"
#define GREATPATH "C:\Projects\GReAT"
#define UDMDLL "UdmDll_3_1_1.dll"
#define UDMDLLD "UdmDll_3_1_1D.dll"
#define UDMVER "3.1.1"
#define GMEVER "6.11.9"
#define OutputFileBase "Udm_setup"

[Setup]
AppName=UDM {#UDMVER}
APPVerName=UDM
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
AppCopyright=Copyright (C) 2000-2006 ISIS, Vanderbilt University

[Languages]
Name: english; MessagesFile: compiler:Default.isl

[Types]
Name: Full; Description: Full(C++ and Java); Flags: iscustom
Name: Typical; Description: Typical(C++); Flags: iscustom

[Components]
Name: Core; Description: Core UDM; Types: Typical Full; Flags: fixed
Name: C; Description: C++ UDM; Types: Typical Full; Flags: fixed
Name: Java; Description: Java UDM; Types: Full; Flags: fixed
Name: System; Description: Register Environment Variables System-Wide (recommended); Types: Typical Full;

[Files]
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
;Udm Root folder
Source: {#UDMPATH}\readme.txt; DestDir: {app}; Components: Core; Flags: ignoreversion
; Udm_3rdparty_files
Source: {#UDM3rdPartyPath}\ant-1.6.2\*; DestDir: {app}\3rdparty\ant-1.6.2; Excludes: *.scc; Components: Java; Flags: ignoreversion recursesubdirs createallsubdirs
Source: {#UDM3rdPartyPath}\junit\*; DestDir: {app}\3rdparty\junit; Excludes: *.scc; Components: Java; Flags: ignoreversion recursesubdirs createallsubdirs
Source: {#UDM3rdPartyPath}\mpc\*; DestDir: {app}\3rdparty\mpc; Excludes: clone_build_tree.exe, mnwc.exe, prj_install.exe, *.scc; Components: C; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\mpc\config\*; DestDir: {app}\3rdparty\mpc\config; Excludes: *.scc; Components: C; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\mpc\templates\*; DestDir: {app}\3rdparty\mpc\templates; Excludes: *.scc; Components: C; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_8_0\license.txt; DestDir: {app}\3rdparty\xalan-c_1_8_0; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_8_0\bin\*; DestDir: {app}\3rdparty\xalan-c_1_8_0\bin; Excludes: *.scc; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xalan-c_1_8_0\lib\*; DestDir: {app}\3rdparty\xalan-c_1_8_0\lib; Excludes: *.scc; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xerces-c_2_5_0\license.txt; DestDir: {app}\3rdparty\xerces-c_2_5_0; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xerces-c_2_5_0\bin\*; DestDir: {app}\3rdparty\xerces-c_2_5_0\bin; Excludes: *.scc; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\xerces-c_2_5_0\lib\*; DestDir: {app}\3rdparty\xerces-c_2_5_0\lib; Excludes: *.scc; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\zlib\license.txt; DestDir: {app}\3rdparty\zlib; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\zlib\zlib.lib; DestDir: {app}\3rdparty\zlib; Components: Core; Flags: ignoreversion
Source: {#UDM3rdPartyPath}\zlib\zlibD.lib; DestDir: {app}\3rdparty\zlib; Components: Core; Flags: ignoreversion
;Udm bin folder
Source: {#UDM3rdPartyPath}\xerces-c_2_5_0\bin\xerces-c_2_5_0.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion deleteafterinstall
Source: {#UDMPATH}\bin\{#UDMDLL}; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\{#UDMDLLD}; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\GmeOclExprChecker.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion regserver
Source: {#UDMPATH}\bin\UML2XML.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion regserver
Source: {#GREATPATH}\bin\MetaGME2Uml.dll; DestDir: {app}\bin; Components: Core; Flags: ignoreversion regserver
Source: {#UDMPATH}\bin\Udm.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\UdmBackendDump.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\UdmCopy.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\UdmOclPat.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\UdmToXmi.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\UdmViz.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\UIntWiz.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\XmiToUdm.exe; DestDir: {app}\bin; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\bin\judm.jar; DestDir: {app}\bin; Components: Java; Flags: ignoreversion
Source: {#UDMPATH}\bin\UdmSwig.dll; DestDir: {app}\bin; Components: Java; Flags: ignoreversion
;Udm Doc folder
Source: {#UDMPATH}\doc\UDMAPI.pdf; DestDir: {app}\doc; Flags: ignoreversion; Components: Core
Source: {#UDMPATH}\doc\UdmInterpreterWizard.pdf; DestDir: {app}\doc; Flags: ignoreversion; Components: Core
Source: {#UDMPATH}\judm\build\build_win\judm\apidoc\*; DestDir: {app}\doc\apidoc; Excludes: *.scc; Flags: recursesubdirs createallsubdirs ignoreversion; Components: Java
;Udm etc folder
Source: {#UDMPATH}\etc\MPCGen.exe; DestDir: {app}\etc; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\etc\StrResGen.exe; DestDir: {app}\etc; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\etc\CreateUdmXml.vbs; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\compileUdmAPI.bat; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\CreateMGA.vbs; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\Uml.xsd; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\UdmProject.xme; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
Source: {#UDMPATH}\etc\UdmProject.xml; DestDir: {app}\etc; Components: Core; Flags: ignoreversion
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
Source: {#UDMPATH}\include\UdmBase.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\Uml_export.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UdmXmi.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\cint_string.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UdmUtil.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\ErrHand.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UdmGme.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UdmProject.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UdmDom.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UdmOcl.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UdmCintSwig.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UdmStatic.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\UmlExt.h; DestDir: {app}\include; Flags: ignoreversion
Source: {#UDMPATH}\include\Uml.h; DestDir: {app}\include; Flags: ignoreversion
;Udm lib folder
Source: {#UDMPATH}\lib\GOCLD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmDll.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmDllD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmXmi.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmXmiD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\File2Code.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\File2CodeD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmUtil.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\Uml.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UmlD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmDom.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmUtilD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmPOI.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\JavaAPIGen.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmPOID.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\JavaAPIGenD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmOcl.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmGme.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmDomD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\GOCL.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmGmeD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmOclD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmBase.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmBaseD.lib; DestDir: {app}\lib; Flags: ignoreversion
Source: {#UDMPATH}\lib\UdmDllD.lib; DestDir: {app}\lib; Flags: ignoreversion
;Udm Samples folder
Source: {#UDMPATH}\samples\LampDiagramGME.xme; DestDir: {app}\samples\C++; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\LampDiagramUML.xme; DestDir: {app}\samples\C++; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\CreateLampModel\CreateLampModel.rc; DestDir: {app}\samples\C++\CreateLampModel; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\CreateLampModel\CreateLampModel.vcproj; DestDir: {app}\samples\C++\CreateLampModel; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\CreateLampModel\CreateLampModel.cpp; DestDir: {app}\samples\C++\CreateLampModel; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\cross_links\cross_links.cpp; DestDir: {app}\samples\C++\cross_links; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\cross_links\cross_links.vcproj; DestDir: {app}\samples\C++\cross_links; Components: C; Flags: ignoreversion
Source: {#UDMPATH}\samples\cross_links\CL.xme; DestDir: {app}\samples\C++\cross_links; Components: C; Flags: ignoreversion
;Source: {#UDMPATH}\samples\Java\GeneTF\*; DestDir: {app}\samples\Java\GeneTF; Excludes: *.scc; Components: Java; Flags: ignoreversion recursesubdirs createallsubdirs
;Source: {#UDMPATH}\samples\Java\GeneTRE\*; DestDir: {app}\samples\Java\GeneTRE; Excludes: *.scc; Components: Java; Flags: ignoreversion recursesubdirs createallsubdirs
;Source: {#UDMPATH}\samples\Java\SBML2Ex\*; DestDir: {app}\samples\Java\SBML2Ex; Excludes: *.scc; Components: Java; Flags: ignoreversion recursesubdirs createallsubdirs

[Dirs]
Name: {app}\include; Components: C
Name: {app}\lib; Components: C

[Messages]
SelectComponentsLabel2=Select the setup type that best suits your needs. Click Next when you are ready to continue.

[Registry]
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: UDM_PATH; ValueData: {app}; Flags: uninsdeletevalue deletevalue; Components: not System
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: UDM_3RDPARTY_PATH; ValueData: {app}\3rdparty; Flags: uninsdeletevalue deletevalue; Components: not System
Root: HKLM; Subkey: SYSTEM\CurrentControlSet\Control\Session Manager\Environment; ValueType: string; ValueName: UDM_PATH; ValueData: {app}; Flags: uninsdeletevalue deletevalue; Components: System
Root: HKLM; Subkey: SYSTEM\CurrentControlSet\Control\Session Manager\Environment; ValueType: string; ValueName: UDM_3RDPARTY_PATH; ValueData: {app}\3rdparty; Flags: uninsdeletevalue deletevalue; Components: System

[Code]
var
  InstallSystemWide: Boolean;
function InitializeSetup(): Boolean;
var
  GME_Path : String;
  oGME :  Variant;
begin
  GME_Path := GetEnv('GME_ROOT');
  if GME_Path = '' then begin
    MsgBox('Unable to locate GME r{#GMEVER}.  Please install GME r{#GMEVER} first.', mbError, MB_OK);
    Result := False;
  end else begin
	oGME := CreateOleObject('GME.Application');
	if oGME.Version = '{#GMEVER}' then begin
		Result := True;
	end else begin
		MsgBox('Udm {#UDMVER} needs GME r{#GMEVER}. The current GME version is '+oGME.Version+'.'#13#13'Please install GME r{#GMEVER} first.', mbError, MB_OK);
		Result := False;
	end;
  end;
end;
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
		ModPath('PATH', path+'\3rdparty\xerces-c_2_5_0\bin');
		ModPath('PATH', path+'\3rdparty\xalan-c_1_8_0\bin');
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
		ModPath('PATH', path+'\3rdparty\xerces-c_2_5_0\bin');
		ModPath('PATH', path+'\3rdparty\xalan-c_1_8_0\bin');
		ModPath('CLASSPATH', '.');
	end;
end;

function NextButtonClick(CurPageID: Integer): Boolean;
var
  MyComponents : String;
  MyCompLen : Integer;
begin
  if CurPageID = wpSelectComponents then begin
    MyComponents := WizardSelectedComponents(false);
    MyCompLen := length(MyComponents);
    if MyComponents[MyCompLen] = 'm' then begin
      InstallSystemWide := true;
    end else begin
      InstallSystemWide := false;
    end;
  end;
  Result := True;
end;
