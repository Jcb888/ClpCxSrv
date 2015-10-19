// Clipboard.h: interface for the CClipboard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPBOARD_H__9826133A_445B_4AAB_9C3A_06C161A08018__INCLUDED_)
#define AFX_CLIPBOARD_H__9826133A_445B_4AAB_9C3A_06C161A08018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//class CPacket;
class CClipCxSrvDoc;

class CClipboard : public CObject  
{

	
public:
	CClipboard();
	DECLARE_DYNCREATE(CClipboard)
	void Serialize(CArchive& ar);
	CString m_StrData;
	BOOL MySetClipboardData();
	void MyGetClipboardData();
	virtual ~CClipboard();

};

#endif // !defined(AFX_CLIPBOARD_H__9826133A_445B_4AAB_9C3A_06C161A08018__INCLUDED_)
