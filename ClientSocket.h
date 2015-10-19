#if !defined(AFX_CLIENTSOCKET_H__739E73F7_89FA_11D7_BFF1_0010B5966E01__INCLUDED_)
#define AFX_CLIENTSOCKET_H__739E73F7_89FA_11D7_BFF1_0010B5966E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target
class CClipCxSrvDoc;
class CPacketType;

class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	BOOL SendPacket(CPacketType * pPacket);
	CClientSocket(CClipCxSrvDoc * pDoc);
	virtual ~CClientSocket();

// Overrides
public:
	void init();
	CSocketFile * m_pFile;
	CArchive * m_pArchiveOut;
	CArchive * m_pArchiveIn;
	CClipCxSrvDoc * m_pDoc;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:

private:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__739E73F7_89FA_11D7_BFF1_0010B5966E01__INCLUDED_)
