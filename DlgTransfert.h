#if !defined(AFX_DLGTRANSFERT_H__A9C9BF59_D499_11D7_802E_0010B5966E01__INCLUDED_)
#define AFX_DLGTRANSFERT_H__A9C9BF59_D499_11D7_802E_0010B5966E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransfert.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTransfert dialog

class CDlgTransfert : public CDialog
{
// Construction
public:
	CDlgTransfert(CWnd* pParent = NULL);   // standard constructor
//	CDlgTransfert(CWnd* pParent = NULL,CString cstr = "sans nom"); 


// Dialog Data
	//{{AFX_DATA(CDlgTransfert)
	enum { IDD = IDD_PROPPAGE_TRANS };
	CProgressCtrl	m_Transfert;
	CString	m_strNameFic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransfert)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransfert)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSFERT_H__A9C9BF59_D499_11D7_802E_0010B5966E01__INCLUDED_)
