// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "ClientSocket.h"
#include "ClipCxSrvDoc.h"
#include "packet.h"
#include "clipboard.h"
//#include <strstrea.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket(CClipCxSrvDoc * pDoc)
{
	m_pDoc = pDoc;

}

CClientSocket::~CClientSocket()
{
	delete m_pFile;
	delete m_pArchiveIn ;
	delete m_pArchiveOut;

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions


void CClientSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
//if(!m_pDoc->m_bExistCx)
//	return;

CPacketType data(m_pDoc);
	
CSocket::OnReceive(nErrorCode);


	do 
		{
		data.Serialize(*m_pArchiveIn);
	
		}while (!m_pArchiveIn->IsBufferEmpty());


}


BOOL CClientSocket::SendPacket(CPacketType * pPacket)
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

void CClientSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pDoc->AbortCurrentCx();
	CSocket::OnClose(nErrorCode);
}

void CClientSocket::init()
{
	m_pFile = new CSocketFile(this);
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);

}


