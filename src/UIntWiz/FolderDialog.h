// FolderDialog.h: interface for the CFolderDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDERDIALOG_H__346B941E_FB3A_4A8B_AC55_7FAF265F3414__INCLUDED_)
#define AFX_FOLDERDIALOG_H__346B941E_FB3A_4A8B_AC55_7FAF265F3414__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFolderDialog  
{	
public:
	CString GetPathName();
	CString m_strLabel;
	CString m_strFolderPath;
	int DoModal();
	HWND m_hWnd;
	
	
	CFolderDialog(CWnd* pParent=NULL, CString strLabel="");
	virtual ~CFolderDialog();
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	GetFolder(CString* strSelectedFolder, const char* lpszTitle,const HWND hwndOwner, const char* strRootFolder, const char* strStartFolder);
};

#endif // !defined(AFX_FOLDERDIALOG_H__346B941E_FB3A_4A8B_AC55_7FAF265F3414__INCLUDED_)
