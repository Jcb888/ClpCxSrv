#if !defined(AFX_DLGPROPTRANSFICHIER_H__FA670B38_A58F_46DD_A033_29B821A8681D__INCLUDED_)
#define AFX_DLGPROPTRANSFICHIER_H__FA670B38_A58F_46DD_A033_29B821A8681D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPropTransFichier.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPropTransFichier dialog

class CDlgPropTransFichier : public CDialog
{
// Construction
public:
	CDlgPropTransFichier(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPropTransFichier)
	enum { IDD = IDD_DIALOG_PTRANSFIC };
	CString	m_strPathAuto;
	BOOL	m_bAutoSave;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPropTransFichier)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPropTransFichier)
	afx_msg void OnButtonBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPTRANSFICHIER_H__FA670B38_A58F_46DD_A033_29B821A8681D__INCLUDED_)
