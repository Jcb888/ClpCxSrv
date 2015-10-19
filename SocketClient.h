#if !defined(AFX_SOCKETCLIENT_H__B6D89E21_8B59_11D7_BFF3_0010B5966E01__INCLUDED_)
#define AFX_SOCKETCLIENT_H__B6D89E21_8B59_11D7_BFF3_0010B5966E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SocketClient.h : header file
//


class CClipCxClntDoc;
class CPacketType;
/////////////////////////////////////////////////////////////////////////////
// CSocketClient command target

class CSocketClient : public CSocket
{
// Attributes
public:

// Operations
public:
	CSocketClient(CClipCxClntDoc * pDoc);
	virtual ~CSocketClient();

// Overrides
public:
	BOOL SendPacket(CPacketType * pPacket);
	void Init();
	CSocketFile * m_pFile;
	CArchive * m_pArchiveOut;
	CArchive * m_pArchiveIn;
	CClipCxClntDoc * m_pDoc;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketClient)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSocketClient)
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKETCLIENT_H__B6D89E21_8B59_11D7_BFF3_0010B5966E01__INCLUDED_)
