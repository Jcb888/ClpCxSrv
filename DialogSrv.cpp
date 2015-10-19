// DialogSrv.cpp : implementation file
//

#include "stdafx.h"
#include "ClipCxClnt.h"
#include "DialogSrv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSrv dialog


CDialogSrv::CDialogSrv(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSrv::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSrv)
	m_StrIpSrv = _T("");
	m_nPort = 0;
	m_bDlgAutoCx = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogSrv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSrv)
	DDX_Text(pDX, IDC_EDIT_SRV, m_StrIpSrv);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Check(pDX, IDC_CHECK_AUTO, m_bDlgAutoCx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSrv, CDialog)
	//{{AFX_MSG_MAP(CDialogSrv)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSrv message handlers
