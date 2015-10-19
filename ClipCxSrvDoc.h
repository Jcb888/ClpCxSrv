// ClipCxSrvDoc.h : interface of the CClipCxSrvDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPCXSRVDOC_H__11A6262B_89E0_11D7_BFF1_0010B5966E01__INCLUDED_)
#define AFX_CLIPCXSRVDOC_H__11A6262B_89E0_11D7_BFF1_0010B5966E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListeningSocket;
class CClientSocket;
class CClipboard;
class FClipCxSrvEtatCxView;
class CFichier;
class CDib;
#include <afxtempl.h>
class CClipCxSrvDoc : public CDocument
{
protected: // create from serialization only
	CClipCxSrvDoc();
	DECLARE_DYNCREATE(CClipCxSrvDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipCxSrvDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void TransfertAnnule();
	void Envoisfichiers();
//	void InitialiseMultiPath();
//	BOOL m_bTransfertEnCours;
	BOOL m_bAutoSaveFic;
	CDib * m_pDibToSend;
	LPBYTE m_lpbyteLastDibData;
	DWORD m_dwlasteDibSize;
	CString m_strlastReceivetext;
	CFichier * m_pFichier;
//	BOOL m_bIpasteLastData;
	CString m_StrEtatCx;
	FClipCxSrvEtatCxView * m_pView;
	void SetIniData();
	BOOL m_bAutoCx;
	UINT m_uPort;
	void RetreiveIniData();
	CString m_StrIpDistant;
	void AbortCurrentCx();
//	CString m_LastReceiveData;
	BOOL m_bExistCx;
	CClipboard * m_pClipBoard;
	CString m_pathAutoSaveFic;
	CString m_pathmultiTransfert;
	CList<CString,CString> m_plisteFichiers;

	
	virtual	void Serialize(CArchive& ar);
//	CString m_StringReceive;
	CClientSocket * m_pClientSocket;
	CListeningSocket* m_pListenSocket;
	void ProcessPendingAccept();
	virtual ~CClipCxSrvDoc();
	

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL m_bExistListenSock;
	//{{AFX_MSG(CClipCxSrvDoc)
	afx_msg void OnParametrer();
	afx_msg void OnParamFichier();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPCXSRVDOC_H__11A6262B_89E0_11D7_BFF1_0010B5966E01__INCLUDED_)
