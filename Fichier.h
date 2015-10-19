// Fichier.h: interface for the CFichier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FICHIER_H__59DFF4F9_75A5_4701_A03C_88A801524606__INCLUDED_)
#define AFX_FICHIER_H__59DFF4F9_75A5_4701_A03C_88A801524606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CClipCxSrvDoc;
class CFichier : public CObject  
{
DECLARE_DYNCREATE(CFichier)
public:
	void CreerPathMultiSave();
	void CreerPathautosave();
	void InitialiseMultiPath();
	CClipCxSrvDoc * m_pDoc;
	CString m_strNameExt;
	BOOL AccepterEtSauverSous();
	void FichierFermer();
	BOOL SauverFichier();
	BOOL OuvrirFichier();
	DWORD SetTailleFichier();
	CFichier();
	CFichier(TCHAR * path,CClipCxSrvDoc * pDoc);
	virtual ~CFichier();
	void Serialize(CArchive& ar);
	
	TCHAR m_pathname[_MAX_PATH];
	TCHAR m_drive[_MAX_DRIVE];
	TCHAR m_dir[_MAX_DIR];
	TCHAR m_fname[_MAX_FNAME];
	TCHAR m_ext[_MAX_EXT];
	CFile m_file;
	DWORD m_dwTailleFichier;

	LPFILETIME m_pdatecreation;
	LPFILETIME m_pdatederacces;
	LPFILETIME m_pdatederecrit;


};

#endif // !defined(AFX_FICHIER_H__59DFF4F9_75A5_4701_A03C_88A801524606__INCLUDED_)
