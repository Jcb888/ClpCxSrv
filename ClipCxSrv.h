// ClipCxSrv.h : main header file for the CLIPCXSRV application
//

#if !defined(AFX_CLIPCXSRV_H__11A62625_89E0_11D7_BFF1_0010B5966E01__INCLUDED_)
#define AFX_CLIPCXSRV_H__11A62625_89E0_11D7_BFF1_0010B5966E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define MYWM_NOTIFYICON (WM_USER + 2)
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvApp:
// See ClipCxSrv.cpp for the implementation of this class
//

class CClipCxSrvApp : public CWinApp
{
public:
	NOTIFYICONDATA m_tnd;
	CClipCxSrvApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipCxSrvApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CClipCxSrvApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPCXSRV_H__11A62625_89E0_11D7_BFF1_0010B5966E01__INCLUDED_)
