# Microsoft Developer Studio Project File - Name="UIntWiz" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=UINTWIZ - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UIntWiz.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UIntWiz.mak" CFG="UINTWIZ - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UIntWiz - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "UIntWiz - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/MoBIES/InterpreterWizard/Uintwiz", RKLAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UIntWiz - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 zlib.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build
InputPath=.\Release\UIntWiz.exe
SOURCE="$(InputPath)"

"UdmInterpreter.zip" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	../../3rdparty/Info-zip/zip.exe -r UdmInterpreter.zip res/UdmInterpreter

# End Custom Build

!ELSEIF  "$(CFG)" == "UIntWiz - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 zlib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UIntWiz - Win32 Release"
# Name "UIntWiz - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Complete.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Generator.cpp
# End Source File
# Begin Source File

SOURCE=.\Int1.cpp
# End Source File
# Begin Source File

SOURCE=.\Int2.cpp
# End Source File
# Begin Source File

SOURCE=.\Interior3.cpp
# End Source File
# Begin Source File

SOURCE=.\Interior4.cpp
# End Source File
# Begin Source File

SOURCE=.\IntroPg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UIntWiz.rc
# End Source File
# Begin Source File

SOURCE=.\Wizard97.cpp
# End Source File
# Begin Source File

SOURCE=.\WizSheet.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\Complete.h
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.h
# End Source File
# Begin Source File

SOURCE=.\Generator.h
# End Source File
# Begin Source File

SOURCE=.\Int1.h
# End Source File
# Begin Source File

SOURCE=.\Int2.h
# End Source File
# Begin Source File

SOURCE=.\Interior3.h
# End Source File
# Begin Source File

SOURCE=.\Interior4.h
# End Source File
# Begin Source File

SOURCE=.\IntroPg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Wizard97.h
# End Source File
# Begin Source File

SOURCE=.\WizSheet.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Baner16.bmp
# End Source File
# Begin Source File

SOURCE=.\Baner256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\completi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Resources.txt

!IF  "$(CFG)" == "UIntWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "UIntWiz - Win32 Debug"

# Begin Custom Build
InputPath=.\res\Resources.txt

"UdmInterpreter.zip" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd res 
	..\..\..\3rdParty\Info-zip\zip.exe -r UdmInterpreter.zip UdmInterpreter 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\thanktext.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UdmInterpreter.zip
# End Source File
# Begin Source File

SOURCE=.\res\UIntWiz.rc2
# End Source File
# Begin Source File

SOURCE=.\Water16.bmp
# End Source File
# Begin Source File

SOURCE=.\Water256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\welcometext.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wizardicon.ico
# End Source File
# Begin Source File

SOURCE=.\res\wizardiconsmall.ico
# End Source File
# Begin Source File

SOURCE=.\res\wizardleft.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wizardtop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wizico.ico
# End Source File
# End Group
# End Target
# End Project
