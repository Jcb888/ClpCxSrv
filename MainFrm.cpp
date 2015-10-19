// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "ClipCxSrvDoc.h"
#include "ClientSocket.h"
#include "Clipboard.h"
#include "MainFrm.h"
#include "Packet.h"
#include "Fichier.h"
//#include <iostream.h>
//#include "windows.h"
#include "Shlwapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_DRAWCLIPBOARD()
	ON_WM_SIZE()
	ON_COMMAND(ID_CONTEXT_OUVRIR, OnContextOuvrir)
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
m_pDoc = NULL;	
m_bMultiCopy = FALSE;
m_bIGetLasteData = FALSE;
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnDrawClipboard() 
{

CFrameWnd::OnDrawClipboard();


if(!m_pDoc)
	{
	CClipCxSrvDoc* pDoc = (CClipCxSrvDoc*)GetActiveDocument();
	m_pDoc = pDoc;
	}

if(!m_pDoc->m_bExistCx)
	return;

if(m_bIGetLasteData)
	{
	m_bIGetLasteData =	FALSE;//annule l'appel genere par nous meme
	return;
	}

int type = 255;

//pPacket->m_StrData = *pDoc->m_pClipboard->MyGetClipboardData();


if(::IsClipboardFormatAvailable(CF_TEXT))
	{
	m_pDoc->m_pClipBoard->MyGetClipboardData();
	if(m_pDoc->m_pClipBoard->m_StrData == m_pDoc->m_strlastReceivetext)
		return;

	type = 0;
	}


if(::IsClipboardFormatAvailable(CF_DIB))
	{
	if(::OpenClipboard(this->m_hWnd))
		{
		type = 1;
		m_pDoc->m_pDibToSend = new CDib;
		unsigned int IsDibDifferent = FALSE;
		
		m_pDoc->m_pDibToSend->PasteFromClipboard();

		if(m_pDoc->m_pDibToSend->m_dwSizeImage == m_pDoc->m_dwlasteDibSize)
			{
			 for(unsigned int i=0;i< m_pDoc->m_pDibToSend->m_dwSizeImage ; i++)
				 if(m_pDoc->m_pDibToSend->m_lpImage[i] != m_pDoc->m_lpbyteLastDibData[i])
					 {	
					 IsDibDifferent = TRUE;
					 break;
					 }
			}
		else
			IsDibDifferent = TRUE;

		if(IsDibDifferent == FALSE)
			return;
		}
	}


if((type == 0)||(type == 1))
	{
	m_bIGetLasteData =  TRUE;
	CPacketType * pPacket = new CPacketType(m_pDoc);
	pPacket->m_iDataType = type;
	m_pDoc->m_pClientSocket->SendPacket(pPacket);
	delete pPacket;
	}
	
// TODO: Add your message handler code here

}


LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{//////////////////
	if(message == MYWM_NOTIFYICON){
			
		switch (lParam){

			case WM_LBUTTONDBLCLK:
				switch (wParam)	{
					case IDR_MAINFRAME:
						
						ShowWindow(SW_NORMAL);
						SetForegroundWindow();
						SetFocus();

						return TRUE;
						break;
	
								}

			case WM_RBUTTONDOWN :
				switch (wParam)	{
					case IDR_MAINFRAME:
						CMenu menu;
						POINT* pPoint = new POINT;

						menu.LoadMenu(IDR_MENU_CONTEXT);
						::GetCursorPos(pPoint);
						SetForegroundWindow();//antibug
						menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pPoint->x,pPoint->y,this,NULL);
						PostMessage(WM_NULL,0,0);//antibug
						break;		
								}


			break;
		}
	}	
	

//////////////////
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	
	
	if(nType == SIZE_MINIMIZED)
		ShowWindow(SW_HIDE);
	else
		CFrameWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	
}

void CMainFrame::OnContextOuvrir() 
{
	// TODO: Add your command handler code here
ShowWindow(SW_NORMAL);	
}




BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	//TODO  free CString
	//todo verif Cx -->try ? catch


	TCHAR pathfichier[_MAX_PATH];
	memset(pathfichier,0,_MAX_PATH);
	strcat(pathfichier,LPCTSTR(pCopyDataStruct->lpData));//,pCopyDataStruct->cbData);
	
	if(m_pDoc == NULL)
	{
	CClipCxSrvDoc* pDoc = (CClipCxSrvDoc*)GetActiveDocument();
	m_pDoc = pDoc;
	}

	if(((pathfichier[0]=='1')||(m_bMultiCopy == TRUE))&&(pathfichier[0]!='2'))//debut ou en cours multi
		{
		if(m_bMultiCopy == FALSE)//si debut
			{
			m_bMultiCopy = TRUE;
			return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
			}
		m_pDoc->m_plisteFichiers.AddTail(pathfichier);
		return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);

		}

	if(pathfichier[0]== '2')//signal fin d'envois multifichiers (Cfile remplit)
		{
		if(!m_pDoc->m_bExistCx)
			{
			AfxMessageBox("Pas de Connexion Active");
			while(!m_pDoc->m_plisteFichiers.IsEmpty())
				m_pDoc->m_plisteFichiers.RemoveTail();

			return	FALSE;
			}


		
		CPacketType * pPacket = new CPacketType(m_pDoc);
		pPacket->m_iDataType = 6;
		m_pDoc->m_pClientSocket->SendPacket(pPacket);
		delete pPacket;
		m_bMultiCopy = FALSE;
		return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
		}


		if(!m_pDoc->m_bExistCx)
			{
			AfxMessageBox("Pas de Connexion Active");
			return	FALSE;
			}

	//si on arrive ici copie de fichier unique
	if(!m_pDoc->m_pFichier)
		{


		m_pDoc->m_pFichier = new CFichier(pathfichier, m_pDoc);
			if(m_pDoc->m_pFichier->OuvrirFichier()== FALSE)
			{
			delete m_pDoc->m_pFichier;
			return FALSE;
			}
		}
	else
	{
		delete m_pDoc->m_pFichier;
		m_pDoc->m_pFichier = new CFichier(pathfichier,m_pDoc);
		m_pDoc->m_pFichier->OuvrirFichier();
	}
	
	CPacketType * pPacket = new CPacketType(m_pDoc);
	pPacket->m_iDataType = 2;
	m_pDoc->m_pClientSocket->SendPacket(pPacket);
	delete pPacket;

	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}




