#if !defined(AFX_FCLIPCXSRVETATCXVIEW_H__0BA42F2F_A664_11D7_BFFD_0010B5966E01__INCLUDED_)
#define AFX_FCLIPCXSRVETATCXVIEW_H__0BA42F2F_A664_11D7_BFFD_0010B5966E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FClipCxSrvEtatCxView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FClipCxSrvEtatCxView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "ClipCxSrvDoc.h"	// Added by ClassView

class FClipCxSrvEtatCxView : public CFormView
{
protected:
	FClipCxSrvEtatCxView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(FClipCxSrvEtatCxView)

// Form Data
public:
	//{{AFX_DATA(FClipCxSrvEtatCxView)
	enum { IDD = IDD_FCLIPCXSRVETATCXVIEW_FORM };
	CString	m_StrIPDistant;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CClipCxSrvDoc * m_pDoc;
	void MyUpdateData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FClipCxSrvEtatCxView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~FClipCxSrvEtatCxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(FClipCxSrvEtatCxView)
	afx_msg void OnDeconnecter();
	afx_msg void OnUpdateDeconnecter(CCmdUI* pCmdUI);
//	afx_msg void OnTransferFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FCLIPCXSRVETATCXVIEW_H__0BA42F2F_A664_11D7_BFFD_0010B5966E01__INCLUDED_)
