// ClipCxSrvDoc.cpp : implementation of the CClipCxSrvDoc class
//

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "DialogPort.h"
#include "ClipCxSrvDoc.h"
#include "lstnsock.h"
#include "ClientSocket.h"
#include "Clipboard.h"
#include "FClipCxSrvEtatCxView.h"
#include "Fichier.h"
#include "DlgPropTransFichier.h"
#include "Packet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvDoc

IMPLEMENT_DYNCREATE(CClipCxSrvDoc, CDocument)

BEGIN_MESSAGE_MAP(CClipCxSrvDoc, CDocument)
	//{{AFX_MSG_MAP(CClipCxSrvDoc)
	ON_COMMAND(ID_PARAMETRER, OnParametrer)
	ON_COMMAND(ID_PARAM_FICHIER, OnParamFichier)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvDoc construction/destruction

CClipCxSrvDoc::CClipCxSrvDoc()
{
	// TODO: add one-time construction code here
	m_pClipBoard = new CClipboard();
	m_bExistCx = FALSE;
	m_StrIpDistant = "";
	m_pClientSocket = NULL;
	m_pListenSocket = NULL;
	m_pView = NULL;
	m_bExistListenSock = NULL;
//	m_bIpasteLastData = TRUE;
	m_pFichier = NULL;
	m_lpbyteLastDibData =NULL;
	m_pathAutoSaveFic = "";
	m_pathmultiTransfert = "";
//	m_bTransfertEnCours = FALSE;
}

CClipCxSrvDoc::~CClipCxSrvDoc()
{
	delete m_pClipBoard;
	delete [] m_lpbyteLastDibData;
	m_pClipBoard = NULL;

}

BOOL CClipCxSrvDoc::OnNewDocument()
{

if (!CDocument::OnNewDocument())
		return FALSE;

	if(m_bExistCx)
		AbortCurrentCx();
	
	if(m_bExistListenSock)
		{
		m_pListenSocket->Close();
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		}


	RetreiveIniData();

	if(!m_bAutoCx)
	{
		CDialogPort Dialog;
		Dialog.m_nPort = m_uPort;

		if (Dialog.DoModal() != IDOK)
				return FALSE;
		else
		{

	
		m_bAutoCx = Dialog.m_bAutoCx;
		m_uPort = Dialog.m_nPort;
		
		SetIniData();
		}
	}

		m_pListenSocket = new CListeningSocket(this);
		if (m_pListenSocket->Create(m_uPort))
		{			
			if (m_pListenSocket->Listen())
			{
				m_bExistListenSock = TRUE;
				m_StrEtatCx.Format("ClipCxSrv en attente de connexion sur le port %d ", m_uPort);
				if(m_pView)
					m_pView->SendMessage(WM_PAINT);
				return TRUE;
			}
		}
	
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvDoc serialization

void CClipCxSrvDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here

	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvDoc diagnostics

#ifdef _DEBUG
void CClipCxSrvDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClipCxSrvDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClipCxSrvDoc commands

void CClipCxSrvDoc::ProcessPendingAccept()
{

AfxGetApp()->m_pMainWnd->ShowWindow(SW_NORMAL);
	//ToDo-->test-->cx entrante remplacer ?
CClientSocket * pClientSocket = new CClientSocket(this);

		if (m_pListenSocket->Accept(*pClientSocket/*,lpSockAddr*/))
		{
			pClientSocket->init();//doit etre aprés	accept
			CString StrAddr;// strask;
			CString& rStrAddr = StrAddr;
			UINT uint;
			UINT& ruint=uint;
			pClientSocket->GetPeerName(rStrAddr,ruint);
			

			if(m_bExistCx)
				{

				if (AfxMessageBox("demande de connexion de " + rStrAddr + "accepter ?",MB_OKCANCEL) == IDOK)
					{
					AbortCurrentCx();
					m_pClientSocket = pClientSocket;
					m_StrIpDistant = rStrAddr;
					m_StrEtatCx.Format("ClipCxSrv en connection avec le client %s via le port %d",m_StrIpDistant, m_uPort);
					m_pView->SendMessage(WM_PAINT);
					}
				else//(AfxMessageBox(rStrAddr,MB_YESNO) == IDOK)
					delete pClientSocket;
				}
			else//m_bExistCx
				{
				m_pClientSocket = pClientSocket;
				m_StrIpDistant = rStrAddr;
				m_bExistCx = TRUE;
				m_StrEtatCx.Format("ClipCxSrv en connection avec le client %s via le port %d",m_StrIpDistant, m_uPort);;
				if(m_pView)
				m_pView->SendMessage(WM_PAINT);
				}

		}else//m_pListenSocket->Accept
			{
			AfxMessageBox("Connexion refusé");	
			}
}


void CClipCxSrvDoc::AbortCurrentCx()
{
if(m_bExistCx)
	{	
		m_pClientSocket->Close();
		delete m_pClientSocket->m_pArchiveOut;
		m_pClientSocket->m_pArchiveOut = NULL;
		delete m_pClientSocket->m_pArchiveIn;
		m_pClientSocket->m_pArchiveIn = NULL;
		delete m_pClientSocket->m_pFile;
		m_pClientSocket->m_pFile = NULL;

		if (m_pClientSocket != NULL)
		{
			BYTE Buffer[50];
			m_pClientSocket->ShutDown();

			while(m_pClientSocket->Receive(Buffer,50) > 0);
		}

		delete m_pClientSocket;
		m_pClientSocket = NULL;
		m_bExistCx = FALSE;
		m_StrEtatCx.Format("ClipCxSrv en attente de connexion sur le port %d",m_uPort);
		if(m_pView)
		m_pView->SendMessage(WM_PAINT);
	 }
}

void CClipCxSrvDoc::RetreiveIniData()
{
	HKEY hkey;         // address of buffer for opened handle
	unsigned long dwDisp;   // address of disposition value buffer
// Load standard INI file options (including MRU)
	DWORD Status = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
					TEXT("Software\\JCSoft\\ClipCxSrv"),
					0,
					NULL,
					REG_OPTION_NON_VOLATILE, // special options flag 
					KEY_ALL_ACCESS, 
					NULL, 
					&hkey, 
					&dwDisp); 

unsigned char buffer[6]="";
unsigned long datatype;
unsigned long bufferlenght = sizeof(buffer);

	


Status = RegQueryValueEx(hkey,_T("portauto"),NULL, &datatype, buffer, &bufferlenght);

	if(Status)
		{
		strcpy((LPSTR)buffer, "700");
		RegSetValueEx(hkey,TEXT("portauto"),NULL,REG_SZ,buffer,sizeof(buffer));
		m_uPort = atoi((LPCSTR)buffer);
		}
	else
		m_uPort = atoi((LPCSTR)buffer);


Status = RegQueryValueEx(hkey,_T("autoconnect"),NULL, &datatype, buffer, &bufferlenght);

	if(Status)
		{
		unsigned char thide[2];
		thide[0] = '0';//par defaut autocx == 0;
		thide[1] ='\0';
		RegSetValueEx(hkey,TEXT("autoconnect"),NULL,REG_SZ,thide,1);
		buffer[0] = thide[0];
		}

	if(buffer[0] == '1')
		m_bAutoCx = TRUE;

	else
		m_bAutoCx = FALSE;

Status = RegQueryValueEx(hkey,_T("autosavefic"),NULL, &datatype, buffer, &bufferlenght);

	if(Status)
		{
		unsigned char thide[2];
		thide[0] = '0';//par defaut autocx == 0;
		thide[1] ='\0';
		RegSetValueEx(hkey,TEXT("autosavefic"),NULL,REG_SZ,thide,1);
		buffer[0] = thide[0];
		}

	if(buffer[0] == '1')
		m_bAutoSaveFic = TRUE;

	else
		m_bAutoSaveFic = FALSE;


unsigned char pathAutoSaveFic[_MAX_PATH]="d:\\donnees";
bufferlenght = sizeof(pathAutoSaveFic);
Status = RegQueryValueEx(hkey,_T("pathautosave"),NULL, &datatype, pathAutoSaveFic, &bufferlenght);

	if(Status)
		{
		RegSetValueEx(hkey,TEXT("pathautosave"),NULL,REG_SZ,pathAutoSaveFic,sizeof(pathAutoSaveFic));		
		}
	else
		m_pathAutoSaveFic = pathAutoSaveFic;

RegCloseKey(hkey);


}

void CClipCxSrvDoc::SetIniData()
{
	HKEY hkey;         // address of buffer for opened handle
	unsigned long dwDisp;   // address of disposition value buffer
// Load standard INI file options (including MRU)
	DWORD Status = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
					TEXT("Software\\JCSoft\\ClipCxSrv"),
					0,
					NULL,
					REG_OPTION_NON_VOLATILE, // special options flag 
					KEY_ALL_ACCESS, 
					NULL, 
					&hkey, 
					&dwDisp); 

	char bcx[2];
	itoa(m_bAutoCx,bcx,2);
	RegSetValueEx(hkey,TEXT("autoconnect"),NULL,REG_SZ,(const BYTE*)bcx,sizeof(bcx));

//	unsigned char ip[16];
//	strcpy((char *)ip,LPCSTR(m_strIpAddress));
//	RegSetValueEx(hkey,TEXT("ipauto"),NULL,REG_SZ,(const BYTE*)ip,sizeof(ip));

	char uport[6];
	itoa(m_uPort,uport,10);
	RegSetValueEx(hkey,TEXT("portauto"),NULL,REG_SZ,(const BYTE*)uport,sizeof(uport));

	RegCloseKey(hkey);
}

void CClipCxSrvDoc::OnParametrer() 
{

	UINT uPort;
	BOOL bAutoCx;

		// TODO: Add your command handler code here
	HKEY hkey;         // address of buffer for opened handle
	unsigned long dwDisp;   // address of disposition value buffer
// Load standard INI file options (including MRU)
	DWORD Status = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
					TEXT("Software\\JCSoft\\ClipCxSrv"),
					0,
					NULL,
					REG_OPTION_NON_VOLATILE, // special options flag 
					KEY_ALL_ACCESS, 
					NULL, 
					&hkey, 
					&dwDisp); 

unsigned char buffer[6]="";
unsigned long datatype;
unsigned long bufferlenght = sizeof(buffer);

	


Status = RegQueryValueEx(hkey,_T("portauto"),NULL, &datatype, buffer, &bufferlenght);

	if(Status)
		{
		unsigned char port[6]= "700\0";
		RegSetValueEx(hkey,TEXT("portauto"),NULL,REG_SZ,port,sizeof(port));
		uPort = atoi((LPCSTR)port);
		}
		else
			uPort = atoi((LPCSTR)buffer);


Status = RegQueryValueEx(hkey,_T("autoconnect"),NULL, &datatype, buffer, &bufferlenght);

	if(Status)
		{
		unsigned char thide[2];
		thide[0] = '0';//par defaut autocx == 0;
		thide[1] ='\0';
		RegSetValueEx(hkey,TEXT("autoconnect"),NULL,REG_SZ,thide,1);
		buffer[0] = thide[0];
		}

	if(buffer[0] == '1')
		bAutoCx = TRUE;

	else
		bAutoCx = FALSE;



		CDialogPort Dialog;

		Dialog.m_nPort = uPort;
		Dialog.m_bAutoCx = bAutoCx;

		if (IDOK != Dialog.DoModal())
				return ;


	char bcx[2];
	itoa(Dialog.m_bAutoCx,bcx,2);
	RegSetValueEx(hkey,TEXT("autoconnect"),NULL,REG_SZ,(const BYTE*)bcx,sizeof(bcx));

	char uport[6];
	itoa(Dialog.m_nPort,uport,10);
	RegSetValueEx(hkey,TEXT("portauto"),NULL,REG_SZ,(const BYTE*)uport,sizeof(uport));

	RegCloseKey(hkey);
	

}



void CClipCxSrvDoc::OnParamFichier() 
{
CDlgPropTransFichier dlg;
dlg.m_strPathAuto = m_pathAutoSaveFic;
dlg.m_bAutoSave = m_bAutoSaveFic;
if (dlg.DoModal() == IDOK)
	{
	m_pathAutoSaveFic = dlg.m_strPathAuto;
	m_bAutoSaveFic = dlg.m_bAutoSave;

		HKEY hkey;         // address of buffer for opened handle
		unsigned long dwDisp;   // address of disposition value buffer
	// Load standard INI file options (including MRU)
		DWORD Status = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
						TEXT("Software\\JCSoft\\ClipCxSrv"),
						0,
						NULL,
						REG_OPTION_NON_VOLATILE, // special options flag 
						KEY_ALL_ACCESS, 
						NULL, 
						&hkey, 
						&dwDisp); 

		char bcx[2];
		itoa(m_bAutoSaveFic,bcx,2);
		RegSetValueEx(hkey,TEXT("autosavefic"),NULL,REG_SZ,(const BYTE*)bcx,sizeof(bcx));

	//	unsigned char ip[16];
	//	strcpy((char *)ip,LPCSTR(m_strIpAddress));
	//	RegSetValueEx(hkey,TEXT("ipauto"),NULL,REG_SZ,(const BYTE*)ip,sizeof(ip));

		char path[_MAX_PATH]="" ;
		strcpy(path,m_pathAutoSaveFic);
		RegSetValueEx(hkey,TEXT("pathautosave"),NULL,REG_SZ,(const BYTE*)path,sizeof(path));

		RegCloseKey(hkey);
	}
	return;	// TODO: Add your command handler code here
}




void CClipCxSrvDoc::Envoisfichiers()
{
TCHAR pathfichier[_MAX_PATH];
memset(pathfichier,0,_MAX_PATH);

while(!m_plisteFichiers.IsEmpty())
			{
			strcpy(pathfichier,m_plisteFichiers.GetTail());
			m_plisteFichiers.RemoveTail();
				
			if(!m_pFichier)
				{
				m_pFichier = new CFichier(pathfichier, this);
					if(m_pFichier->OuvrirFichier()== FALSE)
					{
					delete m_pFichier;
					return ;
					}
				}
				else
				{
					delete m_pFichier;
					m_pFichier = new CFichier(pathfichier,this);
					m_pFichier->OuvrirFichier();
				}
		CPacketType * pPacket = new CPacketType(this);
		pPacket->m_iDataType = 8;
		m_pClientSocket->SendPacket(pPacket);
		delete pPacket;
		}
CPacketType * pPacket = new CPacketType(this);
pPacket->m_iDataType = 9;//transfert terminé.
m_pClientSocket->SendPacket(pPacket);
delete pPacket;
	
}

void CClipCxSrvDoc::TransfertAnnule()
{//cas 10 on annule le transfert
while(!m_plisteFichiers.IsEmpty())
		m_plisteFichiers.RemoveTail();

if(m_pFichier)
	{
	delete m_pFichier;
	m_pFichier = NULL;
	}
}
