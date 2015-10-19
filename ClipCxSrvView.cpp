// ClipCxSrvView.cpp : implementation of the CClipCxSrvView class
//

#include "stdafx.h"
#include "ClipCxSrv.h"

#include "ClipCxSrvDoc.h"
#include "ClipCxSrvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvView

IMPLEMENT_DYNCREATE(CClipCxSrvView, CView)

BEGIN_MESSAGE_MAP(CClipCxSrvView, CView)
	//{{AFX_MSG_MAP(CClipCxSrvView)
	ON_COMMAND(ID_TRANSFER_FILE, OnTransferFile)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvView construction/destruction

CClipCxSrvView::CClipCxSrvView()
{
	// TODO: add construction code here

}

CClipCxSrvView::~CClipCxSrvView()
{
}

BOOL CClipCxSrvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvView drawing

void CClipCxSrvView::OnDraw(CDC* pDC)
{
	CClipCxSrvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->SetBkColor(RGB(127,127,127));
	pDC->UpdateColors();
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvView printing

BOOL CClipCxSrvView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CClipCxSrvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CClipCxSrvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvView diagnostics

#ifdef _DEBUG
void CClipCxSrvView::AssertValid() const
{
	CView::AssertValid();
}

void CClipCxSrvView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClipCxSrvDoc* CClipCxSrvView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClipCxSrvDoc)));
	return (CClipCxSrvDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvView message handlers

