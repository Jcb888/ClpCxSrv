// ClipCxSrvView.h : interface of the CClipCxSrvView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPCXSRVVIEW_H__11A6262D_89E0_11D7_BFF1_0010B5966E01__INCLUDED_)
#define AFX_CLIPCXSRVVIEW_H__11A6262D_89E0_11D7_BFF1_0010B5966E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClipCxSrvView : public CView
{
protected: // create from serialization only
	CClipCxSrvView();
	DECLARE_DYNCREATE(CClipCxSrvView)

// Attributes
public:
	CClipCxSrvDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipCxSrvView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClipCxSrvView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClipCxSrvView)
	afx_msg void OnTransferFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ClipCxSrvView.cpp
inline CClipCxSrvDoc* CClipCxSrvView::GetDocument()
   { return (CClipCxSrvDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPCXSRVVIEW_H__11A6262D_89E0_11D7_BFF1_0010B5966E01__INCLUDED_)
