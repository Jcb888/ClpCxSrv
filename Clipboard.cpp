// Clipboard.cpp: implementation of the CClipboard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ClipCxSrv.h"
#include "Clipboard.h"
//#include "ClipCxSrvDoc.h"

//#include "Packet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CClipboard,CObject);

CClipboard::CClipboard()
{

}

CClipboard::~CClipboard()
{

}

void CClipboard::MyGetClipboardData()
{

if (::OpenClipboard(NULL)) 
	{
	HANDLE hClipboardData;
	hClipboardData = GetClipboardData(CF_TEXT);
	char *pchData = (char*)GlobalLock(hClipboardData);
	m_StrData = pchData;
	GlobalUnlock(hClipboardData);
	CloseClipboard();
	}

}


BOOL CClipboard::MySetClipboardData()
{

if (::OpenClipboard(NULL))

  {
   EmptyClipboard();

   HGLOBAL hClipboardData;
   hClipboardData = GlobalAlloc(GMEM_DDESHARE, 
                                m_StrData.GetLength()+1);
   char * pchData;
   pchData = (char*)GlobalLock(hClipboardData);
		  
   strcpy(pchData, LPCSTR(m_StrData));
		  
   GlobalUnlock(hClipboardData);
		  
   SetClipboardData(CF_TEXT,hClipboardData);
		  
   CloseClipboard();

 
   return TRUE;
  }
return FALSE;
}

void CClipboard::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_StrData;

	}
	else
	{
		ar >> m_StrData;
		// TODO: add loading code here
	}
}
