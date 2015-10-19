// DialogPort.cpp : implementation file
//

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "DialogPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogPort dialog


CDialogPort::CDialogPort(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPort::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPort)
	m_nPort = 700;
	m_bAutoCx = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPort)
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDV_MinMaxUInt(pDX, m_nPort, 700, 36500);
	DDX_Check(pDX, IDC_CHECK1, m_bAutoCx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPort, CDialog)
	//{{AFX_MSG_MAP(CDialogPort)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPort message handlers
