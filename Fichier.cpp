// Fichier.cpp: implementation of the CFichier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "Fichier.h"
#include "Packet.h"
#include "ClipCxSrvDoc.h"
#include "ClientSocket.h"
#include "Dlgtransfert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CFichier,CObject)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFichier::CFichier()
{

}

CFichier::CFichier(TCHAR * path,CClipCxSrvDoc * pDoc)
{
	m_pDoc = pDoc;
	memset(m_drive,0,_MAX_DRIVE);
	memset(m_dir,0,_MAX_DIR);
	memset(m_fname,0,_MAX_FNAME);
	memset(m_ext,0,_MAX_EXT);
	memset(m_pathname,0,_MAX_PATH);

strcat(m_pathname,path);
_tsplitpath(m_pathname,m_drive, m_dir,m_fname, m_ext);
m_strNameExt.Format("%s%s",m_fname,m_ext);

m_pdatecreation=(FILETIME *) malloc(sizeof(FILETIME));
m_pdatederacces=(FILETIME *) malloc(sizeof(FILETIME));
m_pdatederecrit=(FILETIME *) malloc(sizeof(FILETIME));

}

CFichier::~CFichier()
{
delete m_pdatecreation;
delete m_pdatederacces;
delete m_pdatederecrit;
}

void CFichier::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	ar << m_dwTailleFichier;
	ar << m_pdatecreation->dwHighDateTime;
	ar << m_pdatecreation->dwLowDateTime;
	ar << m_pdatederacces->dwHighDateTime;
	ar << m_pdatederacces->dwLowDateTime;
	ar << m_pdatederecrit->dwHighDateTime;
	ar << m_pdatederecrit->dwLowDateTime;
	
	
	LPBYTE data = (LPBYTE) new char[m_dwTailleFichier];
	m_file.Read(data,m_dwTailleFichier);
	unsigned int i;
	for(i=0;i < m_dwTailleFichier;i++) 
		{
		ar << data[i]; 
		}

	delete [] data;
	}
	else
	{
	CDlgTransfert dlg;
	dlg.m_strNameFic = m_strNameExt;
	dlg.Create(IDD_PROPPAGE_TRANS,NULL);


	ar >> m_dwTailleFichier;
	ar >> m_pdatecreation->dwHighDateTime;
	ar >> m_pdatecreation->dwLowDateTime;
	ar >> m_pdatederacces->dwHighDateTime;
	ar >> m_pdatederacces->dwLowDateTime;
	ar >> m_pdatederecrit->dwHighDateTime;
	ar >> m_pdatederecrit->dwLowDateTime;

	dlg.m_Transfert.SetRange32(0,(int)m_dwTailleFichier);
	dlg.ShowWindow(SW_SHOWNORMAL);
	//dlg.UpdateData();

	LPBYTE data = (LPBYTE) new char[m_dwTailleFichier];
	unsigned int i;
	for(i=0;i < m_dwTailleFichier;i++) 
		{
		ar >> data[i];
		dlg.m_Transfert.SetPos(i);
		}
	m_file.Write(data,m_dwTailleFichier);
	dlg.DestroyWindow();
	delete []data;
	}

}

DWORD CFichier::SetTailleFichier()
{
return m_file.GetLength();
}

BOOL CFichier::OuvrirFichier()
{
if(m_file.Open(m_pathname, CFile::modeRead | CFile::typeBinary)==0)
	{
	AfxMessageBox("Impossible d'ouvrir le fichier");
	return FALSE;
	}
m_dwTailleFichier = m_file.GetLength();


GetFileTime((void *)m_file.m_hFile,m_pdatecreation,m_pdatederacces,m_pdatederecrit);

return TRUE;
}

BOOL CFichier::SauverFichier()
{
if(m_file.Open(m_pathname, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)==0)
	{
	AfxMessageBox("impossible de créer le fichier");
	return FALSE;
	}
return TRUE;

}

void CFichier::FichierFermer()
{
SetFileTime((void *)m_file.m_hFile,m_pdatecreation,m_pdatederacces,m_pdatederecrit);
m_file.Close();
}

BOOL CFichier::AccepterEtSauverSous()
{
if(!m_pDoc->m_bAutoSaveFic)
	{

	strcat(m_pathname,LPCSTR(m_strNameExt));

	OPENFILENAME ofn; // common dialog box structure

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = AfxGetApp()->m_pMainWnd->m_hWnd;
	ofn.lpstrFile = m_pathname;//à l'ouverture le nom du fichier proposé
	ofn.nMaxFile = sizeof(m_pathname);
	ofn.lpstrFilter = "Tout\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = m_fname;//contient nom + extension choisit aprés
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "d:\\donnees";
	ofn.Flags = OFN_CREATEPROMPT |OFN_EXPLORER |OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = "Veuillez choisir le nom et l'emplacement";
	// Display the Open dialog box.

	if(GetSaveFileName(&ofn) > 0)
		if(SauverFichier())
			{
			CPacketType * pPacketRet = new CPacketType(m_pDoc);
			pPacketRet->m_iDataType = 3;
			m_pDoc->m_pClientSocket->SendPacket(pPacketRet);
			delete pPacketRet;
			return TRUE;
			}

	return FALSE;
}
else //autosave
	{
	CreerPathautosave();

	if(SauverFichier())
		{
		CPacketType * pPacketRet = new CPacketType(m_pDoc);
		pPacketRet->m_iDataType = 3;
		m_pDoc->m_pClientSocket->SendPacket(pPacketRet);
		delete pPacketRet;
		return TRUE;
		}
	
	}
return FALSE;
}

void CFichier::CreerPathautosave()
{
	strcat(m_pathname, LPCSTR(m_pDoc->m_pathAutoSaveFic));
	strcat(m_pathname,"\\");
	strcat(m_pathname,LPCSTR( m_strNameExt));

}

void CFichier::InitialiseMultiPath()
{
	// Get the directory to add from the user

	char *Directory = new char[255];
	LPBROWSEINFO Settings	 = new BROWSEINFO;
	Settings->hwndOwner		 = AfxGetApp()->m_pMainWnd->m_hWnd;
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
		m_pDoc->m_pathmultiTransfert = Directory;

	}
	else
	{
	CPacketType * pPacket = new CPacketType(m_pDoc);
	pPacket->m_iDataType = 10;//annulation du transfert
	m_pDoc->m_pClientSocket->SendPacket(pPacket);
	delete pPacket;

	}
	
	delete [] Directory;
//prevoir si refus
}

void CFichier::CreerPathMultiSave()
{
	strcat(m_pathname, LPCSTR(m_pDoc->m_pathmultiTransfert));
	strcat(m_pathname,"\\");
	strcat(m_pathname,LPCSTR( m_strNameExt));

}
