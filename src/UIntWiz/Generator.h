// Generator.h: interface for the CGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATOR_H__053AD83E_F06E_4D1B_80A0_A3529F6BAFE7__INCLUDED_)
#define AFX_GENERATOR_H__053AD83E_F06E_4D1B_80A0_A3529F6BAFE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#define ACCESS_DIRECT_MGA	0
#define ACCESS_MEMORY		1

#define META_LOADING_CODE		0
#define META_LOADING_DYNAMIC	1

#define DATA_NETWORK_TYPE_STATIC	0
#define DATA_NETWORK_TYPE_XML		1


#define _INTERPRETER_CODE_PATH "\\UdmInterpreter\\Component\\"

class CGenerator  
{
public:
	bool GenerateUdmApp();
	bool CopyUdmMetaFiles();
	bool GenerateProjectFile();
	BOOL GenerateUdmConfig();
	BOOL GenerateComponentConfig();	
	void FileFilter(CString strFileName,bool & bSkip,bool&bReadOnly,bool bIsDir);	
	BOOL UnzipSources();
	int UnZip(const char * szMemFileName, const char *szPath);
	void Generate();
	CGenerator();
	virtual ~CGenerator();

	
	CString m_strDestinationPath;

	struct CComponentData
	{
		CString	m_strInterfacePath;
		CString	m_strClassName;
		CString	m_strComponentName;
		CString m_strToolTip;
		BOOL	m_bParadigmIndependent;
		CString	m_strParadigmName;
		CString	m_strProgID;
		CString	m_strTypeLibName;
		CString	m_strClassUUID;
		CString	m_strTypeLibUUID;
		BOOL	m_bIconInGME;
	}m_ComponentData;

	struct CUdmData
	{
		int	m_nMGAAccess;
		int	m_nMetaLoading;

		CString	m_strBackendPath;
		CString	m_strUdmPath;
		BOOL	m_bIncludeUdm;
		BOOL	m_bUserSelect;
		int		m_nDataNetworkType;
		CString	m_strCppPath;
		CString	m_strHeaderPath;

	}m_UdmData;

};

#endif // !defined(AFX_GENERATOR_H__053AD83E_F06E_4D1B_80A0_A3529F6BAFE7__INCLUDED_)
