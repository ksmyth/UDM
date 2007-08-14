# Microsoft Developer Studio Project File - Name="GOCL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=GOCL - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GOCL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GOCL.mak" CFG="GOCL - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GOCL - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GOCL - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GOCL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\stl" /I ".\ANTLRBase" /I "..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "OCL_USING_STL_NAMESPACE" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\GOCL.lib" /nodefaultlib

!ELSEIF  "$(CFG)" == "GOCL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\ANTLRBase" /I "..\Include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "OCL_USING_STL_NAMESPACE" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\GOCL_D.lib" /nodefaultlib

!ENDIF 

# Begin Target

# Name "GOCL - Win32 Release"
# Name "GOCL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ANTLRBase\AParser.cpp
# End Source File
# Begin Source File

SOURCE=.\ANTLRBase\ATokenBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\ANTLRBase\DLexerBase.cpp
# End Source File
# Begin Source File

SOURCE=.\ocl.cpp
# End Source File
# Begin Source File

SOURCE=.\ocl.g

!IF  "$(CFG)" == "GOCL - Win32 Release"

# Begin Custom Build
InputPath=.\ocl.g

BuildCmds= \
	.\ANTLRBase\antlr -CC -ft OCLTokens.h -fl OCLParser.dlg -mrhoist off $(InputPath) \
	.\ANTLRBase\dlg -C2 -i -CC -cl OCLLexer OCLParser.dlg \
	

"OCLLexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OCLLexer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OCLParser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OCLParser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ocl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OCLTokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "GOCL - Win32 Debug"

# Begin Custom Build
InputPath=.\ocl.g

BuildCmds= \
	.\ANTLRBase\antlr -CC -ft OCLTokens.h -fl OCLParser.dlg -mrhoist off $(InputPath) \
	.\ANTLRBase\dlg -C2 -i -CC -cl OCLLexer OCLParser.dlg \
	

"OCLLexer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OCLLexer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OCLParser.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OCLParser.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"ocl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OCLTokens.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OCLCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\OclConstraint.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLContext.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLException.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLFeatureImplementation.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLObject.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLObjectExBasic.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLParserStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLRefCount.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLSignature.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLTree.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLType.cpp
# End Source File
# Begin Source File

SOURCE=.\OCLTypeExBasic.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Include\OCLCommon.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLConfig.h
# End Source File
# Begin Source File

SOURCE=..\Include\OclConstraint.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLContext.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLException.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLFactory.h
# End Source File
# Begin Source File

SOURCE=..\Include\\OCLFeature.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLFeatureImplementation.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLFormalParameter.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLLexer.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLObject.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLObjectExBasic.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLParser.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLParserStatic.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLRefCount.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLSignature.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLTokens.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLTree.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLType.h
# End Source File
# Begin Source File

SOURCE=..\Include\OCLTypeExBasic.h
# End Source File
# End Group
# End Target
# End Project
