// DlgPropTransFichier.cpp : implementation file
//

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "DlgPropTransFichier.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPropTransFichier dialog


CDlgPropTransFichier::CDlgPropTransFichier(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPropTransFichier::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPropTransFichier)
	m_strPathAuto = _T("");
	m_bAutoSave = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgPropTransFichier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPropTransFichier)
	DDX_Text(pDX, IDC_EDIT_PARAMPATH, m_strPathAuto);
	DDX_Check(pDX, IDC_CHECK_AUTOSAVE, m_bAutoSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPropTransFichier, CDialog)
	//{{AFX_MSG_MAP(CDlgPropTransFichier)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPropTransFichier message handlers

void CDlgPropTransFichier::OnButtonBrowse() 
{
	UpdateData(TRUE);
	// Get the directory to add from the user
	char *Directory = new char[255];

	LPBROWSEINFO Settings	 = new BROWSEINFO;
	Settings->hwndOwner		 = m_hWnd;
	Settings->pidlRoot		 = NULL;
	Settings->pszDisplayName = Directory;
	Settings->lpszTitle		 = "Sauver sous...";
	Settings->ulFlags		 = BIF_RETURNONLYFSDIRS;
	Settings->lpfn			 = NULL;
	Settings->lParam		 = NULL;
	Settings->iImage		 = NULL;

	LPCITEMIDLIST FolderID = SHBrowseForFolder(Settings);
	delete Settings;

	if(FolderID)
	{
		SHGetPathFromIDList(FolderID, Directory);
		m_strPathAuto = Directory;
		//UpdateData(TRUE);
		UpdateData(FALSE);

	}

	delete [] Directory;	
}
