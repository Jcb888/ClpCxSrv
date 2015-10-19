// Packet.h: interface for the CPacketType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__B3ECF286_E2D7_4E2A_8FA9_39942A571586__INCLUDED_)
#define AFX_PACKET_H__B3ECF286_E2D7_4E2A_8FA9_39942A571586__INCLUDED_

#include "dibkernel.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClipCxSrvDoc;
class CPacketType : public CObject  
{

public:
	CPacketType();
	DECLARE_DYNCREATE(CPacketType)
	CClipCxSrvDoc * m_pDoc;
	int m_iDataType;
	virtual void Serialize(CArchive& arsock);
	CPacketType(CClipCxSrvDoc * pDoc);
	

	virtual ~CPacketType();


};

#endif // !defined(AFX_PACKET_H__B3ECF286_E2D7_4E2A_8FA9_39942A571586__INCLUDED_)
