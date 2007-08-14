// Generator.cpp: implementation of the CGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wizard97.h"
#include <fstream.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



// The only generator
CGenerator Generator;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenerator::CGenerator()
{

}

CGenerator::~CGenerator()
{

}

void CGenerator::Generate()
{
	UnzipSources();
	GenerateComponentConfig();
	GenerateUdmConfig();
	CopyUdmMetaFiles();
	
	GenerateUdmApp();

	GenerateProjectFile();

}

BOOL CGenerator::UnzipSources()
{
	// Laoding resource containing the zip files (source files for code generation)
	HRSRC hResInfo = ::FindResource(NULL, MAKEINTRESOURCE(IDR_SOURCES), "ARCHIVE");
	if(!hResInfo) 
	{
		AfxMessageBox("Error finding resource (source files)");
		return FALSE;
	}
	HGLOBAL hResource = ::LoadResource(NULL,hResInfo);
	LPVOID lpRes;
	if(!hResource || !(lpRes = ::LockResource(hResource))) 
	{
		AfxMessageBox("Error loading resource (source files)");
		return FALSE;
	}

	// Setting up start and end pointers to the resource
	char *pResStart = (char *)lpRes;
	char *pResEnd = pResStart + ::SizeofResource(NULL,hResInfo);


	//Setting up memfile parameters for zlib
	char szMemFileName[40];
	sprintf(szMemFileName, "(beg:0x%x,end:0x%x)", pResStart,pResEnd);

    ofstream myFile ("c:\\udminterpreter.zip", ios::out | ios::binary);
    myFile.write ((char *)lpRes, ::SizeofResource(NULL,hResInfo));
	myFile.close();

	if(UnZip(szMemFileName, m_strDestinationPath) )return FALSE;


	return TRUE;
}




void CGenerator::FileFilter(CString strFileName,bool & bSkip,bool&bReadOnly, bool bIsDir)
{
	if(!m_UdmData.m_bIncludeUdm)
	{
		CString strUdmPathFilter="UdmInterpreter\\UDM";
		strUdmPathFilter.MakeLower();
		strFileName.MakeLower();
		if(strFileName.Find(strUdmPathFilter)!=-1)
		{
			bSkip=true;
		}
	}
}




#include "direct.h"
#include <io.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "unzip.h"

#define DIM(x) (sizeof(x)/sizeof((x)[0]))


int CGenerator::UnZip(const char * szMemFileName, const char *szPath) 
{ 
	// Return value: -1 on error, 0 otherwise
	int nRetVal;

	// Statistic counters
	int nFiles = 0, nDirs = 0, nSkips = 0;

	// File name
	char szFileName[_MAX_PATH+1];
	szFileName[0] = '\0';
	int nFileNum = 0;

	// Error message buffer
	char szErrMessage[200];

	// Handle of the memory zip file
	unzFile zipFile = NULL;

	try 
	{
		// Opening zip file				
	    //zipFile = unzOpen(szMemFileName);
		zipFile = unzOpen("c:\\udminterpreter.zip");
		if(zipFile == NULL) 
		{
			throw "Cannot open input file. The application file must be corrupt.";
		}
		
		// Setting or creating the destination directory (folder)
		if(!::SetCurrentDirectory(szPath)) 
		{
			::CreateDirectory(szPath,NULL);
		}

		if(!::SetCurrentDirectory(szPath)) 
		{
			throw("Cannot access destination folder.");
		}

		if(unzGoToFirstFile(zipFile) != UNZ_OK) 
		{
			throw "Cannot locate first file. The application file must be corrupt.";
		}

		// Unzipping files		
		int nStatus;
		do 
		{
			nFileNum++;
			unz_file_info ufiFileInfo;
			nStatus = unzGetCurrentFileInfo(zipFile, &ufiFileInfo, szFileName, sizeof(szFileName), NULL, 0, NULL, 0);
			if(nStatus != UNZ_OK) 
			{
				throw "Error accessing file info. The application file must be corrupt.";
			}

			nStatus = unzOpenCurrentFile(zipFile);
			if(nStatus != UNZ_OK) 
			{
				throw "Error opening file in archive. The application file must be corrupt.";
			}

			// Replacing / to \ in the szFileName
			char * szPos;
			while(szPos = strchr(szFileName,'/')) 
			{
				*szPos = '\\';
			}

			// Chechking if it is a directory (folder)
			bool bIsDir = false;
			if(szFileName[strlen(szFileName)-1] == '\\') 
			{
				szFileName[strlen(szFileName)-1] = '\0';
				// It is a directory
				bIsDir = true;
				
			}

			bool bSkip = false;
			bool bReadOnly=false;

/****************************************************************/ 
/* Filtering files	- set bSkip and bReadOnly					*/
			FileFilter(szFileName,bSkip,bReadOnly,bIsDir);
/****************************************************************/
								
			if(!bSkip) 
			{
				/*** Checking existence and permissions ***/

				// Checking permissions
				struct stat statBuffer;
				if(_access( szFileName, 2) == EACCES) 
				{
					throw "No permission to write to file";
				}

				if(!stat(szFileName, &statBuffer)) 
				{
					if(bIsDir) 
					{
						if(!(statBuffer.st_mode & _S_IFDIR)) 
						{
							throw "Cannot extract a directory on a non-dir file"; 
						}
						bSkip = true;
					}
					else 
					{
						if(!(statBuffer.st_mode & _S_IFREG))  
						{
							throw "File exists and not a regular file";
						}
						else 
						{
							if(unlink(szFileName)) 
							{
								throw "Cannot remove original file";
							}
						}
					}	
				}
			}

			if(bSkip) 
			{
				nSkips++;
			}
			else if(bIsDir) // It is a directory
			{   
				if(_mkdir(szFileName))
				{
					throw "Error creating directory";
				}
				nDirs++;
			}	
			else /*** Copying process ***/
			{
				// Open file system file
				FILE *fNewFile = fopen(szFileName, "wb");
				if(fNewFile == NULL) 
				{
					throw "Cannot open output file in OS filesystem";
				}

				// Copying file from memory zip file to file system file
				char szWriteBuffer[8192];
				while((nStatus = unzReadCurrentFile(zipFile, szWriteBuffer, sizeof(szWriteBuffer))) > 0) 
				{
					if(fwrite(szWriteBuffer, nStatus, 1, fNewFile) != 1) 
					{
						throw "Error writing to filesystem file";
					}
				} 

				// Status check - Error reading archive
				if(nStatus < 0) 
				{
					throw "Error reading file in archive";
				}

				// Close file system file
				if(fclose(fNewFile))
				{
					throw "Error closing filesystem file";
				}
				
				nFiles++;
				if(bReadOnly) chmod(szFileName,_S_IREAD);
			}

			// Close zip file in memory
			nStatus = unzCloseCurrentFile(zipFile);
			if(nStatus != UNZ_OK) 
			{
				throw "Error closing file in archive";
			}
			szFileName[0] = '\0';

		} while((nStatus = unzGoToNextFile(zipFile)) == UNZ_OK); // Extract next zip file
		
				
		if(nStatus != UNZ_END_OF_LIST_OF_FILE) 
		{
			throw "Error reading file. The application file must be corrupt.";
		}
		nRetVal=0;
	}
	catch( char *szException) 
	{		
		sprintf(szErrMessage, "Error: %s [at archive item %s (#%d)]\n", szException, szFileName, nFileNum);
		AfxMessageBox(szErrMessage);
		nRetVal= -1;
	}

	// Closing zip file in the memory
	if( zipFile) 
	{
		unzClose(zipFile);
	}
	
#ifdef _DEBUG
	// Display statistics
	sprintf(szErrMessage, "%d files and %d folders extracted, %d skipped.", nFiles, nDirs, nSkips);
	AfxMessageBox(szErrMessage);
#endif

	DeleteFile("c:\\udminterpreter.zip");
	return nRetVal;

}



BOOL CGenerator::GenerateComponentConfig()
{

	// Getting current time
	CTime Time=CTime::GetCurrentTime();
	CString strTime = Time.Format( "%A, %B %d, %Y %H:%M:%S" );

	
	CString strUUIDExploded = "0x"+m_ComponentData.m_strClassUUID;
	strUUIDExploded.Insert(36,"-");
	strUUIDExploded.Insert(34,"-");
	strUUIDExploded.Insert(32,"-");
	strUUIDExploded.Insert(30,"-");
	strUUIDExploded.Insert(28,"-");
	strUUIDExploded.Insert(23,"-");
	strUUIDExploded.Replace("-",", 0x");

	CString strFileName=m_strDestinationPath+_INTERPRETER_CODE_PATH+"ComponentConfig.h";

	FILE *fCompCfgFile = fopen(strFileName, "wt");
	
	if(fCompCfgFile==NULL) return FALSE;

	// Printing header
	fprintf(fCompCfgFile, 
				"// Component configuration file automatically generated as %s\n"
				"// by UDM Interpreter Wizard on %s\n\n",
				"ComponentConfig.h", strTime);

	fprintf(fCompCfgFile, "#define RAWCOMPONENT\n\n"); 

	// UUIDs TypeLib,ProgID, ComponentName...
	fprintf(fCompCfgFile, 
				"// COM UUID-s, names and ProgID\n\n"
				"#define TYPELIB_UUID \"%s\"\n"
				"#define TYPELIB_NAME \"%s\"\n"
				"#define COCLASS_UUID \"%s\"\n"
				"#define COCLASS_NAME \"%s\"\n"
				"#define COCLASS_PROGID \"%s\"\n\n\n"
				"// This name will appear in the popup window for interpreter selection.\n"
				"#define COMPONENT_NAME \"%s\"\n\n\n"
				"#define TOOLTIP_TEXT \"%s\"\n\n\n"
				"// This #define determines the interpreter type:\n",
				 m_ComponentData.m_strTypeLibUUID, 
				 m_ComponentData.m_strTypeLibName,
				 m_ComponentData.m_strClassUUID, 
				 m_ComponentData.m_strClassName, 
				 m_ComponentData.m_strProgID, 
				 m_ComponentData.m_strComponentName,
				 m_ComponentData.m_strToolTip);

	// This is an interpreter
	fprintf(fCompCfgFile, "#define GME_INTERPRETER\n");

	// Paradigm support
	if(m_ComponentData.m_bParadigmIndependent) 
	{
		fprintf(fCompCfgFile, "#define PARADIGM_INDEPENDENT\n");
	}
	else
	{
		fprintf(fCompCfgFile, 
				"// The name of the paradigm(s). The GME will use this component\n"
				"// for this paradigm. Separate the names of paradigms by commas.\n"
				"#define PARADIGMS \"%s\"\n",
				m_ComponentData.m_strParadigmName);
	}

	// GME Interface path
	m_ComponentData.m_strInterfacePath.Replace("\\\\","/");
	m_ComponentData.m_strInterfacePath.Replace("\\","/");
	fprintf(fCompCfgFile, 
	 "\n\n// This is the location of the GME interfaces file (Mga.idl, Meta.idl, etc)\n"
	 "#define GME_INTERFACES_BASE %s\n\n\n", m_ComponentData.m_strInterfacePath);

	// Icon on GME Toolbar
	if(m_ComponentData.m_bIconInGME) 
	{
		fprintf(fCompCfgFile, "#define BON_ICON_SUPPORT\n\n");
	}
	else
	{
		fprintf(fCompCfgFile, "// not defined: #define BON_ICON_SUPPORT\n\n");
	}

	// Fragment UUID - a la Arpad Bakay
	fprintf(fCompCfgFile, "// Just to please the whims of those Microsoft jerks:\n");
	int n = 1;
	for(char *a = strtok((LPSTR)(LPCSTR)strUUIDExploded,","); a; a = strtok(NULL, ",")) 
	{
		fprintf(fCompCfgFile, "#define COCLASS_UUID_EXPLODED%d %s\n", n++, a);
	}

	fclose(fCompCfgFile);
	return TRUE;
}




BOOL CGenerator::GenerateUdmConfig()
{
	// Getting current time
	CTime Time=CTime::GetCurrentTime();
	CString strTime = Time.Format( "%A, %B %d, %Y %H:%M:%S" );

	CString strFileName=m_strDestinationPath+_INTERPRETER_CODE_PATH+"UdmConfig.h";

	FILE *fUdmCfgFile = fopen(strFileName, "wt");
	
	if(fUdmCfgFile==NULL) return FALSE;

	// Printing header
	fprintf(fUdmCfgFile, 
				"// Component configuration file automatically generated as %s\n"
				"// by UDM Interpreter Wizard on %s\n\n",
				"UdmConfig.h", strTime);


	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"#ifndef UDM_CONFIG_H\n");
	fprintf(fUdmCfgFile,"#define UDM_CONFIG_H\n");
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"\n");

	bool bUseDom=(m_UdmData.m_nDataNetworkType==DATA_NETWORK_TYPE_XML&&
				  m_UdmData.m_nMetaLoading==META_LOADING_DYNAMIC)||
				 (m_UdmData.m_bUserSelect&&
				  m_UdmData.m_nDataNetworkType==DATA_NETWORK_TYPE_XML);

	if(bUseDom)
	{
		fprintf(fUdmCfgFile,"#define _USE_DOM\n");
	}
	else
	{
		fprintf(fUdmCfgFile,"//#define _USE_DOM\n");
	}
	
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"\n");

	// Include header file
	CString strHeaderFileName=m_UdmData.m_strHeaderPath.Right(m_UdmData.m_strHeaderPath.GetLength()-m_UdmData.m_strHeaderPath.ReverseFind('\\')-1);

	if(m_UdmData.m_nMetaLoading==META_LOADING_CODE)
	{
		fprintf(fUdmCfgFile,"#include\"%s\"\n",strHeaderFileName);
	}
	fprintf(fUdmCfgFile,"#include<string> // STL\n");
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"// Udm Libraries \n");

	/* 
	Commented by Ananth:
	fprintf(fUdmCfgFile,"#ifdef _DEBUG\n");
	

	if(m_UdmData.m_bIncludeUdm)
	{
		fprintf(fUdmCfgFile,"	#define UDM_BASE_PATH	\"..\\\\Udm\\\\Lib\\\\Udm\\\\Udmbase_D.lib\"\n");
		fprintf(fUdmCfgFile,"	#define UDM_DOM_PATH	\"..\\\\Udm\\\\Lib\\\\Udm\\\\UdmDom_D.lib\"\n");
		fprintf(fUdmCfgFile,"	#define UDM_XERCES_PATH	\"..\\\\Udm\\\\Lib\\\\xerces\\\\xerces-c_1D.lib\"\n");
		fprintf(fUdmCfgFile,"	#define UDM_GME_PATH	\"..\\\\Udm\\\\Lib\\\\Udm\\\\UdmGme_D.lib\"\n");
		fprintf(fUdmCfgFile,"	#define UDM_UTIL_PATH	\"..\\\\Udm\\\\Lib\\\\Udm\\\\UdmUtil_D.lib\"\n");
		fprintf(fUdmCfgFile,"#else\n");
		fprintf(fUdmCfgFile,"	#define UDM_BASE_PATH	\"..\\\\Udm\\\\Lib\\\\Udm\\\\Udmbase.lib\"\n");
		fprintf(fUdmCfgFile,"	#define UDM_DOM_PATH	\"..\\\\Udm\\\\Lib\\\\Udm\\\\UdmDom.lib\"\n");
		fprintf(fUdmCfgFile,"	#define UDM_XERCES_PATH	\"..\\\\Udm\\\\Lib\\\\xerces\\\\xerces-c_1.lib\"\n");
		fprintf(fUdmCfgFile,"	#define UDM_GME_PATH	\"..\\\\Udm\\\\Lib\\\\Udm\\\\UdmGme.lib\"\n");
		fprintf(fUdmCfgFile,"	#define UDM_UTIL_PATH	\"..\\\\Udm\\\\Lib\\\\Udm\\\\UdmUtil.lib\"\n");
	}
	else
	{
		CString strUdmPath=m_UdmData.m_strUdmPath;
		strUdmPath.Replace("\\","\\\\");

		CString strLibPath=strUdmPath+"\\\\Lib\\\\Udm\\\\";
		CString strXercesPath=strUdmPath+"\\\\Lib\\\\xerces\\\\";
		
		fprintf(fUdmCfgFile,"	#define UDM_BASE_PATH	\"%sUdmbase_D.lib\"\n",strLibPath);
		fprintf(fUdmCfgFile,"	#define UDM_DOM_PATH	\"%sUdmDom_D.lib\"\n",strLibPath);
		fprintf(fUdmCfgFile,"	#define UDM_XERCES_PATH	\"%sxerces-c_1D.lib\"\n",strXercesPath);
		fprintf(fUdmCfgFile,"	#define UDM_GME_PATH	\"%sUdmGme_D.lib\"\n",strLibPath);
		fprintf(fUdmCfgFile,"	#define UDM_UTIL_PATH	\"%sUdmUtil_D.lib\"\n",strLibPath);
		fprintf(fUdmCfgFile,"#else\n");
		fprintf(fUdmCfgFile,"	#define UDM_BASE_PATH	\"%sUdmbase.lib\"\n",strLibPath);
		fprintf(fUdmCfgFile,"	#define UDM_DOM_PATH	\"%sUdmDom.lib\"\n",strLibPath);
		fprintf(fUdmCfgFile,"	#define UDM_XERCES_PATH	\"%sxerces-c_1.lib\"\n",strXercesPath);
		fprintf(fUdmCfgFile,"	#define UDM_GME_PATH	\"%sUdmGme.lib\"\n",strLibPath);
		fprintf(fUdmCfgFile,"	#define UDM_UTIL_PATH	\"%sUdmUtil.lib\"\n",strLibPath);
	}
	fprintf(fUdmCfgFile,"#endif\n");
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"// Adding library search entries to the object file for linker\n");
	fprintf(fUdmCfgFile,"#pragma comment( lib,UDM_BASE_PATH)\n\n");
	fprintf(fUdmCfgFile,"#ifdef _USE_DOM\n");
	fprintf(fUdmCfgFile,"#pragma comment( lib,UDM_XERCES_PATH)\n");
	fprintf(fUdmCfgFile,"#pragma comment( lib,UDM_DOM_PATH)\n");
	fprintf(fUdmCfgFile,"#endif\n\n");
	fprintf(fUdmCfgFile,"#pragma comment( lib,UDM_GME_PATH)\n");
	fprintf(fUdmCfgFile,"#pragma comment( lib,UDM_UTIL_PATH)\n");
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"\n");
	End comment by Ananth
	*/
	if(m_UdmData.m_nMetaLoading==META_LOADING_DYNAMIC)
	{
		fprintf(fUdmCfgFile,"#define _DYNAMIC_META\n");
		if(m_UdmData.m_nDataNetworkType==DATA_NETWORK_TYPE_XML)
		{
			fprintf(fUdmCfgFile,"#define _DYNAMIC_META_DOM\n");
		}
		else
		{
			fprintf(fUdmCfgFile,"#define _DYNAMIC_META_STATIC\n");
		}
	}
	else
	{
		fprintf(fUdmCfgFile,"#define META_NAMESPACE %s\n",strHeaderFileName.Left(strHeaderFileName.GetLength()-2));
	}

	if(m_UdmData.m_nMGAAccess==ACCESS_MEMORY)
	{
		fprintf(fUdmCfgFile,"#define _ACCESS_MEMORY\n");
	}
	else
	{
		fprintf(fUdmCfgFile,"//#define _ACCESS_MEMORY\n");
	}

	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"struct _config\n");
	fprintf(fUdmCfgFile,"{\n");
	fprintf(fUdmCfgFile,"	// Global settings\n");
	
	fprintf(fUdmCfgFile,"	std::string metaPath;\n");
	
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"};\n");
	fprintf(fUdmCfgFile,"extern _config config;\n");
	fprintf(fUdmCfgFile,"\n");
	fprintf(fUdmCfgFile,"#endif /* UDM_CONFIG_H */\n");


	fclose(fUdmCfgFile);
	return TRUE;
}





bool CGenerator::CopyUdmMetaFiles()
{
	if(m_UdmData.m_nMetaLoading!=META_LOADING_CODE) return false;

	bool bRet=true;
	// Include header file
	CString strHeaderFileName=m_UdmData.m_strHeaderPath.Right(m_UdmData.m_strHeaderPath.GetLength()-m_UdmData.m_strHeaderPath.ReverseFind('\\')-1);
	CString strCppFileName=m_UdmData.m_strCppPath.Right(m_UdmData.m_strCppPath.GetLength()-m_UdmData.m_strCppPath.ReverseFind('\\')-1);

	CString strHeaderFilePath=m_strDestinationPath+_INTERPRETER_CODE_PATH+strHeaderFileName;
	CString strCppFilePath=m_strDestinationPath+_INTERPRETER_CODE_PATH+strCppFileName;

	if(!::CopyFile(m_UdmData.m_strHeaderPath,strHeaderFilePath,FALSE))
	{
		CString strMessage;
		strMessage.Format("Udm Interpreter Wizard could not open file %s.",strHeaderFilePath);
		AfxMessageBox(strMessage,MB_ICONEXCLAMATION);
		bRet=false;
	}
	if(!::CopyFile(m_UdmData.m_strCppPath,strCppFilePath,FALSE))
	{
		CString strMessage;
		strMessage.Format("Udm Interpreter Wizard could not open file %s.",strCppFilePath);
		AfxMessageBox(strMessage,MB_ICONEXCLAMATION);
		bRet=false;
	}

	return bRet;
}



bool CGenerator::GenerateProjectFile()
{

	CString strFileName=m_strDestinationPath+_INTERPRETER_CODE_PATH+"Component.dsp";
	CString strUdmHeaderPath=m_UdmData.m_strUdmPath+"\\Include\\Udm";
	CString strSTLHeaderPath=m_UdmData.m_strUdmPath+"\\Include\\Stl";	
	
	CString strGMEPath;
	char l_strSingleVal[255];
	if(GetEnvironmentVariable("GME_ROOT", l_strSingleVal,255)) {
		strGMEPath=l_strSingleVal;
	}	
	CString strGMEBONPath = strGMEPath + "\\SDK\\BON";

	CString strHeaderFileName=m_UdmData.m_strHeaderPath.Right(m_UdmData.m_strHeaderPath.GetLength()-m_UdmData.m_strHeaderPath.ReverseFind('\\')-1);
	CString strCppFileName=m_UdmData.m_strCppPath.Right(m_UdmData.m_strCppPath.GetLength()-m_UdmData.m_strCppPath.ReverseFind('\\')-1);

	FILE* fDspFile=fopen(strFileName,"wt");
	if(fDspFile==NULL)
	{
		CString strMessage;
		strMessage.Format("Udm Interpreter Wizard could not generate project file %s.",strFileName);
		AfxMessageBox(strMessage);
		return false;
	}

	fprintf(fDspFile,"# Microsoft Developer Studio Project File - Name=\"Component\" - Package Owner=<4>\n");
	fprintf(fDspFile,"# Microsoft Developer Studio Generated Build File, Format Version 6.00\n");
	fprintf(fDspFile,"# ** DO NOT EDIT **\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# TARGTYPE \"Win32 (x86) Dynamic-Link Library\" 0x0102\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"CFG=Component - Win32 Debug\n");
	fprintf(fDspFile,"!MESSAGE This is not a valid makefile. To build this project using NMAKE,\n");
	fprintf(fDspFile,"!MESSAGE use the Export Makefile command and run\n");
	fprintf(fDspFile,"!MESSAGE \n");
	fprintf(fDspFile,"!MESSAGE NMAKE /f \"Component.mak\".\n");
	fprintf(fDspFile,"!MESSAGE \n");
	fprintf(fDspFile,"!MESSAGE You can specify a configuration when running NMAKE\n");
	fprintf(fDspFile,"!MESSAGE by defining the macro CFG on the command line. For example:\n");
	fprintf(fDspFile,"!MESSAGE \n");
	fprintf(fDspFile,"!MESSAGE NMAKE /f \"Component.mak\" CFG=\"Component - Win32 Debug\"\n");
	fprintf(fDspFile,"!MESSAGE \n");
	fprintf(fDspFile,"!MESSAGE Possible choices for configuration are:\n");
	fprintf(fDspFile,"!MESSAGE \n");
	fprintf(fDspFile,"!MESSAGE \"Component - Win32 Debug\" (based on \"Win32 (x86) Dynamic-Link Library\")\n");
	fprintf(fDspFile,"!MESSAGE \"Component - Win32 Release MinSize\" (based on \"Win32 (x86) Dynamic-Link Library\")\n");
	fprintf(fDspFile,"!MESSAGE \"Component - Win32 Release MinDependency\" (based on \"Win32 (x86) Dynamic-Link Library\")\n");
	fprintf(fDspFile,"!MESSAGE \n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# Begin Project\n");
	fprintf(fDspFile,"# PROP AllowPerConfigDependencies 0\n");
	fprintf(fDspFile,"# PROP Scc_ProjName \"\"\n");
	fprintf(fDspFile,"# PROP Scc_LocalPath \"\"\n");
	fprintf(fDspFile,"CPP=cl.exe\n");
	fprintf(fDspFile,"MTL=midl.exe\n");
	fprintf(fDspFile,"RSC=rc.exe\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"!IF  \"$(CFG)\" == \"Component - Win32 Debug\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP BASE Use_MFC 2\n");
	fprintf(fDspFile,"# PROP BASE Use_Debug_Libraries 1\n");
	fprintf(fDspFile,"# PROP BASE Output_Dir \"Debug\"\n");
	fprintf(fDspFile,"# PROP BASE Intermediate_Dir \"Debug\"\n");
	fprintf(fDspFile,"# PROP BASE Target_Dir \"\"\n");
	fprintf(fDspFile,"# PROP Use_MFC 2\n");
	fprintf(fDspFile,"# PROP Use_Debug_Libraries 1\n");
	fprintf(fDspFile,"# PROP Output_Dir \"Debug\"\n");
	fprintf(fDspFile,"# PROP Intermediate_Dir \"Debug\"\n");
	fprintf(fDspFile,"# PROP Ignore_Export_Lib 0\n");
	fprintf(fDspFile,"# PROP Target_Dir \"\"\n");
	fprintf(fDspFile,"# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D \"WIN32\" /D \"_DEBUG\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /Yu\"stdafx.h\" /FD /GZ /c\n");

	/*
	Commented by Ananth
	if(m_UdmData.m_bIncludeUdm)
	{
		fprintf(fDspFile,"# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I \"..\\Udm\\Include\\Udm\" /I \"..\\Udm\\Include\\Stl\" /D \"_DEBUG\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /FR /FD /GZ /c\n");
	}
	else
	{
		fprintf(fDspFile,"# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I \"%s\" /I \"%s\" /D \"_DEBUG\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /FR /FD /GZ /c\n",strUdmHeaderPath,strSTLHeaderPath);
	}
	End comment by Ananth
	*/
	//Added by Ananth
	fprintf(fDspFile,"# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I \".\\\\\" /I \".\\\" /I \"%s\" /I \"%s\\include\" /I \"%s\\3rdParty\\stl\" /D \"_DEBUG\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /D \"GME_INTERPRETER_USED\" /D \"UML_CLASS_DIAGRAM\" /FR /FD /GZ /Zm200 /c\n",strGMEBONPath,m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	//End add by Ananth

	/* Commented by Ananth
	fprintf(fDspFile,"# SUBTRACT CPP /YX /Yc /Yu\n");
	*/
	fprintf(fDspFile,"# ADD BASE MTL /nologo /D \"_DEBUG\" /mktyplib203 /win32\n");
	fprintf(fDspFile,"# ADD BASE RSC /l 0x409 /d \"_DEBUG\" /d \"_AFXDLL\"\n");
	fprintf(fDspFile,"# ADD RSC /l 0x409 /d \"_DEBUG\" /d \"_AFXDLL\"\n");
	fprintf(fDspFile,"BSC32=bscmake.exe\n");
	fprintf(fDspFile,"# ADD BASE BSC32 /nologo\n");
	fprintf(fDspFile,"# ADD BSC32 /nologo\n");
	fprintf(fDspFile,"LINK32=link.exe\n");
	fprintf(fDspFile,"# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept\n");
	/*
	Commented by Ananth
	fprintf(fDspFile,"# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept\n");
	End comment by Ananth
	*/
	//Added by Ananth
	fprintf(fDspFile,"# ADD LINK32 xerces-c_2D.lib ZlibD.lib UdmBase_D.lib UdmDom_D.lib UdmUtil_D.lib UdmGme_D.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:\"%s\\lib\" /libpath:\"%s\\3rdParty\\zlib\" /libpath:\"%s\\3rdparty\xerces\xerces-c_2_5_0-windows_nt-msvc_60\lib\"\n",m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	fprintf(fDspFile,"# SUBTRACT LINK32 /pdb:none\n");
	//End add by Ananth
	fprintf(fDspFile,"# Begin Custom Build - Performing registration\n");
	fprintf(fDspFile,"OutDir=.\\Debug\n");
	fprintf(fDspFile,"TargetPath=.\\Debug\\Component.dll\n");
	fprintf(fDspFile,"InputPath=.\\Debug\\Component.dll\n");
	fprintf(fDspFile,"SOURCE=\"$(InputPath)\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"$(OutDir)\\regsvr32.trg\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"	regsvr32 /s /c \"$(TargetPath)\" \n");
	fprintf(fDspFile,"	echo regsvr32 exec. time > \"$(OutDir)\\regsvr32.trg\" \n");
	fprintf(fDspFile,"	\n");
	fprintf(fDspFile,"# End Custom Build\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"!ELSEIF  \"$(CFG)\" == \"Component - Win32 Release MinSize\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP BASE Use_MFC 2\n");
	fprintf(fDspFile,"# PROP BASE Use_Debug_Libraries 0\n");
	fprintf(fDspFile,"# PROP BASE Output_Dir \"ReleaseMinSize\"\n");
	fprintf(fDspFile,"# PROP BASE Intermediate_Dir \"ReleaseMinSize\"\n");
	fprintf(fDspFile,"# PROP BASE Ignore_Export_Lib 0\n");
	fprintf(fDspFile,"# PROP BASE Target_Dir \"\"\n");
	fprintf(fDspFile,"# PROP Use_MFC 2\n");
	fprintf(fDspFile,"# PROP Use_Debug_Libraries 0\n");
	fprintf(fDspFile,"# PROP Output_Dir \"ReleaseMinSize\"\n");
	fprintf(fDspFile,"# PROP Intermediate_Dir \"ReleaseMinSize\"\n");
	fprintf(fDspFile,"# PROP Ignore_Export_Lib 0\n");
	fprintf(fDspFile,"# PROP Target_Dir \"\"\n");	
	/*Commented by Ananth
	fprintf(fDspFile,"# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /Yu\"stdafx.h\" /FD /c\n");

	if(m_UdmData.m_bIncludeUdm)
	{
		fprintf(fDspFile,"# ADD CPP /nologo /MD /W3 /GX /O1 /I \"..\\Udm\\Include\\Udm\" /I \"..\\Udm\\Include\\Stl\" /D \"NDEBUG\" /D \"_ATL_DLL\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /FD /c\n");
	}
	else
	{
		fprintf(fDspFile,"# ADD CPP /nologo /MD /W3 /GX /O1 /I \"%s\" /I \"%s\" /D \"NDEBUG\" /D \"_ATL_DLL\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /FD /c\n",strUdmHeaderPath,strSTLHeaderPath);
	}
	*/
	//Added by Ananth
	fprintf(fDspFile,"# ADD BASE CPP /nologo /MD /W3 /GX /O1 /I \".\\\\\" /I \".\\\" /I \"%s/\" /I \"%s\\include\" /I \"%s\\3rdParty\\stl\" /D \"NDEBUG\" /D \"_ATL_DLL\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /D \"GME_INTERPRETER_USED\" /D \"UML_CLASS_DIAGRAM\" /FR /FD /Zm200 /c\n",strGMEBONPath,m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	//
	/*Commented by Ananth
	fprintf(fDspFile,"# SUBTRACT CPP /YX /Yc /Yu\n");
	fprintf(fDspFile,"# ADD BASE MTL /nologo /D \"NDEBUG\" /mktyplib203 /win32\n");
	*/
	//Added by Ananth
	fprintf(fDspFile,"# ADD CPP /nologo /MD /W3 /GX /O1 /I \".\\\\\" /I \".\\\" /I \"%s\" /I \"%s\\include\" /I \"%s\\3rdParty\\stl\" /D \"NDEBUG\" /D \"_ATL_DLL\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /D \"GME_INTERPRETER_USED\" /D \"UML_CLASS_DIAGRAM\" /FR /FD /Zm200 /c\n",strGMEBONPath,m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	//end
	fprintf(fDspFile,"# ADD BASE RSC /l 0x409 /d \"NDEBUG\" /d \"_AFXDLL\"\n");
	fprintf(fDspFile,"# ADD RSC /l 0x409 /d \"NDEBUG\" /d \"_AFXDLL\"\n");
	fprintf(fDspFile,"BSC32=bscmake.exe\n");
	fprintf(fDspFile,"# ADD BASE BSC32 /nologo\n");
	fprintf(fDspFile,"# ADD BSC32 /nologo\n");
	fprintf(fDspFile,"LINK32=link.exe\n");
	/*Commented by Ananth
	fprintf(fDspFile,"# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386\n");
	fprintf(fDspFile,"# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386\n");
	*/
	//Added by Ananth
	fprintf(fDspFile,"# ADD BASE LINK32 xerces-c_2.lib Zlib.lib /nologo /subsystem:windows /dll /machine:I386 /out:\"Release/Component.dll\" /libpath:\"%s\\3rdParty\\zlib\" /libpath:\"%s\\3rdparty\xerces\xerces-c_2_5_0-windows_nt-msvc_60\lib\"\n",m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	fprintf(fDspFile,"# ADD LINK32 xerces-c_2.lib Zlib.lib UdmBase.lib UdmDom.lib UdmUtil.lib UdmGme.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:\"%s\\lib\" /libpath:\"%s\\3rdParty\\zlib\" /libpath:\"%s\\3rdparty\xerces\xerces-c_2_5_0-windows_nt-msvc_60\lib\"\n",m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	//end
	fprintf(fDspFile,"# Begin Custom Build - Performing registration\n");
	fprintf(fDspFile,"OutDir=.\\ReleaseMinSize\n");
	fprintf(fDspFile,"TargetPath=.\\ReleaseMinSize\\Component.dll\n");
	fprintf(fDspFile,"InputPath=.\\ReleaseMinSize\\Component.dll\n");
	fprintf(fDspFile,"SOURCE=\"$(InputPath)\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"$(OutDir)\\regsvr32.trg\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"	regsvr32 /s /c \"$(TargetPath)\" \n");
	fprintf(fDspFile,"	echo regsvr32 exec. time > \"$(OutDir)\\regsvr32.trg\" \n");
	fprintf(fDspFile,"	\n");
	fprintf(fDspFile,"# End Custom Build\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"!ELSEIF  \"$(CFG)\" == \"Component - Win32 Release MinDependency\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP BASE Use_MFC 2\n");
	fprintf(fDspFile,"# PROP BASE Use_Debug_Libraries 0\n");
	fprintf(fDspFile,"# PROP BASE Output_Dir \"ReleaseMinDependency\"\n");
	fprintf(fDspFile,"# PROP BASE Intermediate_Dir \"ReleaseMinDependency\"\n");
	fprintf(fDspFile,"# PROP BASE Target_Dir \"\"\n");
	fprintf(fDspFile,"# PROP Use_MFC 2\n");
	fprintf(fDspFile,"# PROP Use_Debug_Libraries 0\n");
	fprintf(fDspFile,"# PROP Output_Dir \"ReleaseMinDependency\"\n");
	fprintf(fDspFile,"# PROP Intermediate_Dir \"ReleaseMinDependency\"\n");
	fprintf(fDspFile,"# PROP Ignore_Export_Lib 0\n");
	fprintf(fDspFile,"# PROP Target_Dir \"\"\n");
	fprintf(fDspFile,"# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /FD /c\n");
	/*Commented by Ananth	
	fprintf(fDspFile,"# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /Yu\"stdafx.h\" /FD /c\n");
	if(m_UdmData.m_bIncludeUdm)
	{
		fprintf(fDspFile,"# ADD CPP /nologo /MD /W3 /GX /O1 /I \"..\\Udm\\Include\\Udm\" /I \"..\\Udm\\Include\\Stl\" /D \"NDEBUG\" /D \"_ATL_STATIC_REGISTRY\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /Yu\"stdafx.h\" /FD /c\n");
	}
	else
	{
		fprintf(fDspFile,"# ADD CPP /nologo /MD /W3 /GX /O1 /I \"%s\" /I \"%s\" /D \"NDEBUG\" /D \"_ATL_STATIC_REGISTRY\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /Yu\"stdafx.h\" /FD /c\n", strUdmHeaderPath,strSTLHeaderPath);
	}
	*/
	//Added by Ananth
	//fprintf(fDspFile,"# ADD CPP /nologo /MD /W3 /GX /O1 /I \"%s\\include\" /I \"%s\\3rdParty\\stl\" /D \"NDEBUG\" /D \"_ATL_STATIC_REGISTRY\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /Yu\"stdafx.h\" /FD /c\n",m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	fprintf(fDspFile,"# ADD CPP /nologo /MD /W3 /GX /O1 /I \".\\\" /I \"%s\" /I \"%s\\include\" /I \"%s\\3rdParty\\stl\" /D \"NDEBUG\" /D \"_ATL_STATIC_REGISTRY\" /D \"WIN32\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /FD /c\n",strGMEBONPath,m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	//end
	fprintf(fDspFile,"# ADD BASE MTL /nologo /D \"NDEBUG\" /mktyplib203 /win32\n");
	fprintf(fDspFile,"# ADD BASE RSC /l 0x409 /d \"NDEBUG\" /d \"_AFXDLL\"\n");
	fprintf(fDspFile,"# ADD RSC /l 0x409 /d \"NDEBUG\" /d \"_AFXDLL\"\n");
	fprintf(fDspFile,"BSC32=bscmake.exe\n");
	fprintf(fDspFile,"# ADD BASE BSC32 /nologo\n");
	fprintf(fDspFile,"# ADD BSC32 /nologo\n");
	fprintf(fDspFile,"LINK32=link.exe\n");
	fprintf(fDspFile,"# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386\n");
	fprintf(fDspFile,"# ADD LINK32 xerces-c_2.lib zlib.lib UdmBase.lib UdmGme.lib UdmUtil.lib UdmDom.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:\"%s\\Lib,%s\\3rdparty\xerces\xerces-c_2_5_0-windows_nt-msvc_60\lib,%s\\3rdparty\\zlib\"\n",m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath,m_UdmData.m_strUdmPath);
	/*Commented by Ananth
	fprintf(fDspFile,"# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /libpath:\"..\\Udm\\Lib\\Udm ..\\Udm\\Lib\\xerces\"\n");
	*/
	fprintf(fDspFile,"# Begin Custom Build - Performing registration\n");
	fprintf(fDspFile,"OutDir=.\\ReleaseMinDependency\n");
	fprintf(fDspFile,"TargetPath=.\\ReleaseMinDependency\\Component.dll\n");
	fprintf(fDspFile,"InputPath=.\\ReleaseMinDependency\\Component.dll\n");
	fprintf(fDspFile,"SOURCE=\"$(InputPath)\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"$(OutDir)\\regsvr32.trg\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"	regsvr32 /s /c \"$(TargetPath)\" \n");
	fprintf(fDspFile,"	echo regsvr32 exec. time > \"$(OutDir)\\regsvr32.trg\" \n");
	fprintf(fDspFile,"	\n");
	fprintf(fDspFile,"# End Custom Build\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"!ENDIF \n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# Begin Target\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# Name \"Component - Win32 Debug\"\n");
	fprintf(fDspFile,"# Name \"Component - Win32 Release MinSize\"\n");
	fprintf(fDspFile,"# Name \"Component - Win32 Release MinDependency\"\n");
	fprintf(fDspFile,"# Begin Group \"Source Files\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP Default_Filter \"cpp;c;cxx;rc;def;r;odl;idl;hpj;bat\"\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=\"%s\\ComHelp.cpp\"\n", strGMEBONPath);
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\Component.def\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\Component.rc\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=\"%s\\ComponentDll.cpp\"\n", strGMEBONPath);
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\ComponentLib.idl\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"!IF  \"$(CFG)\" == \"Component - Win32 Debug\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP Ignore_Default_Tool 1\n");
	fprintf(fDspFile,"# Begin Custom Build - MIDL $(InputPath))\n");
	fprintf(fDspFile,"InputPath=.\\ComponentLib.idl\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"BuildCmds= \\\n");
	fprintf(fDspFile,"	midl /server none /client none ComponentLib.idl\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib.tlb\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib.h\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib_i.c\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"# End Custom Build\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"!ELSEIF  \"$(CFG)\" == \"Component - Win32 Release MinSize\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP Ignore_Default_Tool 1\n");
	fprintf(fDspFile,"# Begin Custom Build - MIDL $(InputPath))\n");
	fprintf(fDspFile,"InputPath=.\\ComponentLib.idl\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"BuildCmds= \\\n");
	fprintf(fDspFile,"	midl /server none /client none ComponentLib.idl\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib.tlb\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib.h\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib_i.c\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"# End Custom Build\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"!ELSEIF  \"$(CFG)\" == \"Component - Win32 Release MinDependency\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP Ignore_Default_Tool 1\n");
	fprintf(fDspFile,"# Begin Custom Build - MIDL $(InputPath))\n");
	fprintf(fDspFile,"InputPath=.\\ComponentLib.idl\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"BuildCmds= \\\n");
	fprintf(fDspFile,"	midl /server none /client none ComponentLib.idl\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib.tlb\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib.h\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"\"ComponentLib_i.c\" : $(SOURCE) \"$(INTDIR)\" \"$(OUTDIR)\"\n");
	fprintf(fDspFile,"   $(BuildCmds)\n");
	fprintf(fDspFile,"# End Custom Build\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"!ENDIF \n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=\"%s\\ComponentObj.cpp\"\n", strGMEBONPath);
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");

	if(m_UdmData.m_nMetaLoading==META_LOADING_CODE)
	{
		// Adding cpp file to project
		fprintf(fDspFile,"SOURCE=.\\%s\n",strCppFileName);
		fprintf(fDspFile,"# End Source File\n");
		fprintf(fDspFile,"# Begin Source File\n");
		fprintf(fDspFile,"\n");
	}

	fprintf(fDspFile,"SOURCE=.\\RawComponent.cpp\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\StdAfx.cpp\n");
	fprintf(fDspFile,"# ADD CPP /Yc\"stdafx.h\"\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\UdmApp.cpp\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# End Group\n");
	fprintf(fDspFile,"# Begin Group \"Header Files\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP Default_Filter \"h;hpp;hxx;hm;inl\"\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\ComponentConfig.h\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	
	if(m_UdmData.m_nMetaLoading==META_LOADING_CODE)
	{
		// Adding header to the project
		fprintf(fDspFile,"SOURCE=.\\%s\n",strHeaderFileName);	
		fprintf(fDspFile,"# End Source File\n");
		fprintf(fDspFile,"# Begin Source File\n");
		fprintf(fDspFile,"\n");
	}

	fprintf(fDspFile,"SOURCE=.\\RawComponent.h\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\Resource.h\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\StdAfx.h\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\UdmApp.h\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\UdmConfig.h\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# End Group\n");
	fprintf(fDspFile,"# Begin Group \"Resource Files\"\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"# PROP Default_Filter \"ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe\"\n");
	fprintf(fDspFile,"# Begin Source File\n");
	fprintf(fDspFile,"\n");
	fprintf(fDspFile,"SOURCE=.\\CompIcon.ico\n");
	fprintf(fDspFile,"# End Source File\n");
	fprintf(fDspFile,"# End Group\n");
	fprintf(fDspFile,"# End Target\n");
	fprintf(fDspFile,"# End Project\n");

	// Close file
	fclose(fDspFile);

	return true;
}

bool CGenerator::GenerateUdmApp()
{

		// Getting current time
	CTime Time=CTime::GetCurrentTime();
	CString strTime = Time.Format( "%A, %B %d, %Y %H:%M:%S" );


	CString strFileName=m_strDestinationPath+_INTERPRETER_CODE_PATH+"UdmApp.cpp";

	FILE* fUdmAppFile=fopen(strFileName,"wt");
	if(fUdmAppFile==NULL)
	{
		CString strMessage;
		strMessage.Format("Udm Interpreter Wizard could not generate code file %s.",strFileName);
		AfxMessageBox(strMessage);
		return false;
	}


	// Printing header
	fprintf(fUdmAppFile, 
				"// UdmApp.cpp: implementation of the CUdmApp class.\n"
				"// This file was automatically generated as %s\n"
				"// by UDM Interpreter Wizard on %s\n\n",
				"UdmApp.cpp", strTime);

	
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"#include \"stdafx.h\"\n");
	fprintf(fUdmAppFile,"#include \"UdmApp.h\"\n");
	fprintf(fUdmAppFile,"#include \"UdmConfig.h\"\n");

	if(m_UdmData.m_bUserSelect)
	{
		fprintf(fUdmAppFile,"#include <afxdlgs.h> // For CFileDialog\n");
	}
	
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"/*********************************************************************************/\n");
	fprintf(fUdmAppFile,"/* Initialization function. The framework calls it before preparing the backend. */\n");
	fprintf(fUdmAppFile,"/* Initialize here the settings in the config global object.					  */\n");
	fprintf(fUdmAppFile,"/* Return 0 if successful.														  */\n");
	fprintf(fUdmAppFile,"/*********************************************************************************/\n");
	fprintf(fUdmAppFile,"int CUdmApp::Initialize()\n");
	fprintf(fUdmAppFile,"{\n");

	// To be strict: m_UdmData.m_nMetaLoading==META_LOADING_DYNAMIC && !m_UdmData.m_bUserSelect
	// But now we can add default value to a user specified meta path
	if(m_UdmData.m_nMetaLoading==META_LOADING_DYNAMIC) 
	{
		fprintf(fUdmAppFile,"	std::string metaPath=\"%s\";\n\n",m_UdmData.m_strBackendPath);
	}

	if(m_UdmData.m_bUserSelect)
	{
		if(m_UdmData.m_nDataNetworkType==DATA_NETWORK_TYPE_XML)
		{
			fprintf(fUdmAppFile,"	static char szFilterXML[] = \"XML Backend Files (*.xml)|*.xml|All Files (*.*)|*.*||\";\n");
			fprintf(fUdmAppFile,"	CFileDialog dlgDOM(TRUE,\"xml\",NULL,OFN_FILEMUSTEXIST,szFilterXML,NULL);\n");
			fprintf(fUdmAppFile,"\n");
			fprintf(fUdmAppFile,"	if(dlgDOM.DoModal()==IDOK)\n");
			fprintf(fUdmAppFile,"	{\n");
			fprintf(fUdmAppFile,"		config.metaPath=dlgDOM.GetPathName();\n");
			fprintf(fUdmAppFile,"	}\n");
			fprintf(fUdmAppFile,"	else\n");
			fprintf(fUdmAppFile,"	{\n");
			fprintf(fUdmAppFile,"		// If cancel pressed exit\n");
			fprintf(fUdmAppFile,"		return -1;\n");
			fprintf(fUdmAppFile,"	}\n");
		}	
		if(m_UdmData.m_nDataNetworkType==DATA_NETWORK_TYPE_STATIC)
		{
			fprintf(fUdmAppFile,"	static char szFilterMem[] = \"Static Memory Backend Files (*.mem)|*.mem|All Files (*.*)|*.*||\";\n");
			fprintf(fUdmAppFile,"	CFileDialog dlgStatic(TRUE,\"mem\",NULL,OFN_FILEMUSTEXIST,szFilterMem,NULL);\n");
			fprintf(fUdmAppFile,"\n");
			fprintf(fUdmAppFile,"	if(dlgStatic.DoModal()==IDOK)\n");
			fprintf(fUdmAppFile,"	{\n");
			fprintf(fUdmAppFile,"		config.metaPath=dlgStatic.GetPathName();\n");
			fprintf(fUdmAppFile,"	}\n");
			fprintf(fUdmAppFile,"	else\n");
			fprintf(fUdmAppFile,"	{\n");
			fprintf(fUdmAppFile,"		// If cancel pressed exit\n");
			fprintf(fUdmAppFile,"		return -1;\n");
			fprintf(fUdmAppFile,"	}\n");

		}	
	}
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"	// TODO: Your initialization code comes here...\n");
	fprintf(fUdmAppFile,"	return 0;\n");
	fprintf(fUdmAppFile,"}\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"/* \n");
	fprintf(fUdmAppFile,"Remarks to CUdmApp::UdmMain(...):\n");
	fprintf(fUdmAppFile,"0.	The p_backend points to an already open backend, and the framework \n");
	fprintf(fUdmAppFile,"	closes it automatically. DO NOT OPEN OR CLOSE IT!\n");
	fprintf(fUdmAppFile,"	To commit changes use p_backend->CommitEditSequence().\n");
	fprintf(fUdmAppFile,"	To abort changes use p_backend->AbortEditSequence().\n");
	fprintf(fUdmAppFile,"	To save changes to a different file use p_backend->SaveAs() or p_backend->CloseAs().\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"1.	Focus is the currently open model.\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"2.	The possible values for param (from GME DecoratorLib.h component_startmode_enum):\n");
	fprintf(fUdmAppFile,"	GME_MAIN_START			=   0,\n");
	fprintf(fUdmAppFile,"	GME_BROWSER_START		=   1,\n");
	fprintf(fUdmAppFile,"	GME_CONTEXT_START		=   2,\n");
	fprintf(fUdmAppFile,"	GME_EMBEDDED_START		=   3,\n");
	fprintf(fUdmAppFile,"	GME_MENU_START			=  16,\n");
	fprintf(fUdmAppFile,"	GME_BGCONTEXT_START		=  18,\n");
	fprintf(fUdmAppFile,"	GME_ICON_START			=  32,\n");
	fprintf(fUdmAppFile,"	METAMODEL_CHECK_SYNTAX	= 101\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile," 3. The framework catches all the exceptions and reports the error in a message box,\n");
	fprintf(fUdmAppFile,"	clean up and close the transactions aborting the changes. You can override this \n");
	fprintf(fUdmAppFile,"	behavior by catching udm_exception. Use udm_exception::what() to form an error \n");
	fprintf(fUdmAppFile,"	message.\n");
	fprintf(fUdmAppFile,"*/\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"/***********************************************/\n");
	fprintf(fUdmAppFile,"/* Main entry point for Udm-based Interpreter  */\n");
	fprintf(fUdmAppFile,"/***********************************************/\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"void CUdmApp::UdmMain(\n");
	fprintf(fUdmAppFile,"					 Udm::DataNetwork* p_backend,		// Backend pointer(already open!)\n");
	fprintf(fUdmAppFile,"					 Udm::Object focusObject,			// Focus object\n");
	fprintf(fUdmAppFile,"					 set<Udm::Object> selectedObjects,	// Selected objects\n");
	fprintf(fUdmAppFile,"					 long param)						// Parameters\n");
	fprintf(fUdmAppFile,"{	\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"	// TODO: Your Code Comes Here...\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"/************************** Demo Code - Delete It *********************/\n");
	fprintf(fUdmAppFile,"	// Welcome\n");
	fprintf(fUdmAppFile,"	AfxMessageBox(\"Hello Udm-based Interpreter World!\");\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"#ifdef _DEBUG\n");
	fprintf(fUdmAppFile,"	// Displaying the name of the root object meta\n");
	fprintf(fUdmAppFile,"	Udm::Object rootObject=p_backend->GetRootObject();\n");
	fprintf(fUdmAppFile,"	string rootObjectName(\"Root Object's Class Name: \");\n");
	fprintf(fUdmAppFile,"	rootObjectName+=ExtractName(rootObject.type());\n");
	fprintf(fUdmAppFile,"	AfxMessageBox(rootObjectName.c_str());\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"	// Displaying the focus object\n");
	fprintf(fUdmAppFile,"	string focusObjectName(\"Focus Object Name: \");\n");
	fprintf(fUdmAppFile,"	focusObjectName+=ExtractName(focusObject);\n");
	fprintf(fUdmAppFile,"	AfxMessageBox(focusObjectName.c_str());\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"	// Displaying selected objects\n");
	fprintf(fUdmAppFile,"	string selObjNames(\"Selected Objects:\\r\\n\");\n");
	fprintf(fUdmAppFile,"	// Iterate set\n");
	fprintf(fUdmAppFile,"	for(set<Udm::Object>::iterator i=selectedObjects.begin();\n");
	fprintf(fUdmAppFile,"													i!=selectedObjects.end();i++)\n");
	fprintf(fUdmAppFile,"	{\n");
	fprintf(fUdmAppFile,"		selObjNames+=ExtractName(*i);\n");
	fprintf(fUdmAppFile,"		selObjNames+=\"\\r\\n\";\n");
	fprintf(fUdmAppFile,"	}\n");
	fprintf(fUdmAppFile,"	AfxMessageBox(selObjNames.c_str());	\n");
	fprintf(fUdmAppFile,"#endif\n");
	fprintf(fUdmAppFile,"/****************************** Demo Code End *************************/\n");
	fprintf(fUdmAppFile,"													\n");
	fprintf(fUdmAppFile,"}\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"#ifdef _DEBUG\n");
	fprintf(fUdmAppFile,"/*****************************************************/\n");
	fprintf(fUdmAppFile,"/* Debug time helper function. If the object has an  */\n");
	fprintf(fUdmAppFile,"/* attribute called \"name\", this function retreives  */\n");
	fprintf(fUdmAppFile,"/* it to help you to find it in the model during the */\n");
	fprintf(fUdmAppFile,"/* application development.	Usualy every GME Object	 */\n");
	fprintf(fUdmAppFile,"/* has a \"name\" attribute. If an object hapens not	 */\n");
	fprintf(fUdmAppFile,"/* to have it,function retreives <no name specified>.*/\n");
	fprintf(fUdmAppFile,"/*****************************************************/\n");
	fprintf(fUdmAppFile,"string CUdmApp::ExtractName(Udm::Object ob)\n");
	fprintf(fUdmAppFile,"{\n");
	fprintf(fUdmAppFile,"	Uml::Class cls= ob.type();				\n");
	fprintf(fUdmAppFile,"	set<Uml::Attribute> attrs=cls.attributes();		\n");
	fprintf(fUdmAppFile,"	\n");
	fprintf(fUdmAppFile,"	// Adding parent attributes\n");
	fprintf(fUdmAppFile,"	set<Uml::Attribute> aattrs=Uml::AncestorAttributes(cls);\n");
	fprintf(fUdmAppFile,"	attrs.insert(aattrs.begin(),aattrs.end());\n");
	fprintf(fUdmAppFile,"\n");
	fprintf(fUdmAppFile,"	for(set<Uml::Attribute>::iterator ai = attrs.begin();ai != attrs.end(); ai++) \n");
	fprintf(fUdmAppFile,"	{\n");
	fprintf(fUdmAppFile,"		if(string(ai->type())==\"String\")\n");
	fprintf(fUdmAppFile,"		{\n");
	fprintf(fUdmAppFile,"			string str=ai->name();\n");
	fprintf(fUdmAppFile,"			if(str==\"name\")\n");
	fprintf(fUdmAppFile,"			{\n");
	fprintf(fUdmAppFile,"				string value=ob.getStringAttr(*ai);\n");
	fprintf(fUdmAppFile,"				if(value.empty())value=\"<empty string>\";\n");
	fprintf(fUdmAppFile,"				return value;\n");
	fprintf(fUdmAppFile,"			}			\n");
	fprintf(fUdmAppFile,"		}				\n");
	fprintf(fUdmAppFile,"	}	\n");
	fprintf(fUdmAppFile,"	return string(\"<no name specified>\");\n");
	fprintf(fUdmAppFile,"}\n");
	fprintf(fUdmAppFile,"#endif\n");

	fclose(fUdmAppFile);

	return true;

}
