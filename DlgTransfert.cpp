// DlgTransfert.cpp : implementation file
//

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "DlgTransfert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTransfert dialog


CDlgTransfert::CDlgTransfert(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransfert::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransfert)
	m_strNameFic = _T("");
	//}}AFX_DATA_INIT
}

//CDlgTransfert(CWnd* pParent,CString cstr)
//	: CDialog(CDlgTransfert::IDD, pParent)
//	{
//	m_strNameFic = cstr;
//	}

void CDlgTransfert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransfert)
	DDX_Control(pDX, IDC_PROGRESS1, m_Transfert);
	DDX_Text(pDX, IDC_EDIT_NOMFICTRANS, m_strNameFic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransfert, CDialog)
	//{{AFX_MSG_MAP(CDlgTransfert)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransfert message handlers
