// SocketClient.cpp : implementation file
//

#include "stdafx.h"
#include "ClipCxClnt.h"
#include "SocketClient.h"
#include "ClipCxClntDoc.h"
#include "Packet.h"
#include "Clipboard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocketClient

CSocketClient::CSocketClient(CClipCxClntDoc * pDoc)
{
	m_pDoc = pDoc;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;

}

CSocketClient::~CSocketClient()
{//passage ok, mais erreur si mode debug.
//DEL delete m_pFile;
//DEL delete m_pArchiveIn;
//DEL delete m_pArchiveOut;

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocketClient, CSocket)
	//{{AFX_MSG_MAP(CSocketClient)
	ON_UPDATE_COMMAND_UI(ID_ABORT_CX, OnUpdateAbortCx)
	ON_COMMAND(ID_ABORT_CX, OnAbortCx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocketClient member functions

void CSocketClient::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
CSocket::OnReceive(nErrorCode);

if(!m_pDoc->m_bExistCx)
	return;

CPacketType data(m_pDoc);
	
	do 
		{
		data.Serialize(*m_pArchiveIn);
	
		}while (!m_pArchiveIn->IsBufferEmpty());

}

void CSocketClient::Init()
{
	m_pFile = new CSocketFile(m_pDoc->m_pSocket);
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);

	if (m_pFile == NULL || m_pArchiveIn == NULL ||m_pArchiveOut == NULL)
		AfxMessageBox("erreur init",MB_OK);

	m_pDoc->m_bExistCx = TRUE;
}

BOOL CSocketClient::SendPacket(CPacketType *pPacket)
{
//if(!m_pDoc->m_bExistCx)
//	return FALSE;

	if (m_pArchiveOut != NULL)
		{
			pPacket->Serialize(*m_pArchiveOut);
			m_pArchiveOut->Flush();
			return TRUE;
		}
return FALSE;
}




void CSocketClient::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pDoc->AbortCx();
	CSocket::OnClose(nErrorCode);
}


