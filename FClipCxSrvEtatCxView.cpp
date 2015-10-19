// FClipCxSrvEtatCxView.cpp : implementation file
//

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "FClipCxSrvEtatCxView.h"
#include "ClipCxSrvDoc.h"
#include "Packet.h"
#include "ClientSocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FClipCxSrvEtatCxView

IMPLEMENT_DYNCREATE(FClipCxSrvEtatCxView, CFormView)

FClipCxSrvEtatCxView::FClipCxSrvEtatCxView()
	: CFormView(FClipCxSrvEtatCxView::IDD)
{

	//{{AFX_DATA_INIT(FClipCxSrvEtatCxView)
	m_StrIPDistant = _T("ClipCxSrv running");
	//}}AFX_DATA_INIT


}

FClipCxSrvEtatCxView::~FClipCxSrvEtatCxView()
{
}

void FClipCxSrvEtatCxView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FClipCxSrvEtatCxView)
	DDX_Text(pDX, IDC_EDIT_ETATCX, m_StrIPDistant);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FClipCxSrvEtatCxView, CFormView)
	//{{AFX_MSG_MAP(FClipCxSrvEtatCxView)
	ON_COMMAND(ID_DECONNECTER, OnDeconnecter)
	ON_UPDATE_COMMAND_UI(ID_DECONNECTER, OnUpdateDeconnecter)
//	ON_COMMAND(ID_TRANSFER_FILE, OnTransferFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FClipCxSrvEtatCxView diagnostics

#ifdef _DEBUG
void FClipCxSrvEtatCxView::AssertValid() const
{
	CFormView::AssertValid();
}

void FClipCxSrvEtatCxView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// FClipCxSrvEtatCxView message handlers

void FClipCxSrvEtatCxView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	ResizeParentToFit();
	m_pDoc =(CClipCxSrvDoc *) GetDocument();
}

void FClipCxSrvEtatCxView::MyUpdateData()
{
	

}


void FClipCxSrvEtatCxView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class


m_StrIPDistant = m_pDoc->m_StrEtatCx;
UpdateData(FALSE);
m_pDoc->m_pView = this;

}
void FClipCxSrvEtatCxView::OnDeconnecter() 
{
	// TODO: Add your command handler code here

m_pDoc->AbortCurrentCx();
m_StrIPDistant = m_pDoc->m_StrEtatCx;
UpdateData(FALSE);
SendMessage(WM_PAINT);
}

void FClipCxSrvEtatCxView::OnUpdateDeconnecter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	
	if(!m_pDoc->m_bExistCx)
		pCmdUI->Enable(FALSE);
}

