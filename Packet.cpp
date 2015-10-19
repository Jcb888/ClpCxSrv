// Packet.cpp: implementation of the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClipCxSrv.h"
#include "Packet.h"
#include "ClipCxSrvDoc.h"
#include "Clipboard.h"
#include "Fichier.h"
#include <strstrea.h>
#include "ClientSocket.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CPacketType, CObject)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPacketType::CPacketType(CClipCxSrvDoc * pDoc)
{
m_iDataType = 255;
//m_StrData = "";
m_pDoc = pDoc;
}
CPacketType::CPacketType()
{
m_iDataType = 255;
//m_StrData = "";
}

CPacketType::~CPacketType()
{

}

void CPacketType::Serialize(CArchive &arsock)
{


if (arsock.IsStoring())
	{
	
	arsock << m_iDataType;

	switch (m_iDataType)
		{
		case 0 :
			{
			m_pDoc->m_pClipBoard->Serialize(arsock);
			break;
			}
		case 1 :
			{
			//::OpenClipboard(NULL);
			m_pDoc->m_pDibToSend->Serialize(arsock);
			break;
			}
		case 2 ://envois nom + demande d'acceptation
			{
			arsock << m_pDoc->m_pFichier->m_strNameExt;

			break;
			}
		case 3 ://fichier accepter et ouvert
			{
			break;
			}
		case 4 :
			{
			m_pDoc->m_pFichier->Serialize(arsock);
			m_pDoc->m_pFichier->m_file.Close();
			delete m_pDoc->m_pFichier;
			m_pDoc->m_pFichier = NULL;
			break;
			}
		case 5://fichier refuse ou annulé
			{
			break;
			}
		case 6://demande d'envois multicopie
			{
			break;
			}
		case 7://
			{
			break;
			}
		case 8://envois des fichier depuis le CList
			{
			arsock << m_pDoc->m_pFichier->m_strNameExt;
			m_pDoc->m_pFichier->Serialize(arsock);
			m_pDoc->m_pFichier->m_file.Close();
			delete m_pDoc->m_pFichier;
			m_pDoc->m_pFichier = NULL;
			break;
			}
		case 9 ://trnasfert terminé
			{
			break;
			}
		case 10 : // annulation du transfert
			{
			break;
			}
		case 255 :
			{
			AfxMessageBox("tentative d'envois Packet non initialisé");
			m_pDoc->AbortCurrentCx();
			break;
			}
		default :
			{
			AfxMessageBox("demande d'envois d'un type inconnue");
			m_pDoc->AbortCurrentCx();
			}
		}
	}

else{
	arsock >> m_iDataType;

	switch (m_iDataType)
		{
		case 0 :
			{
			m_pDoc->m_pClipBoard->Serialize(arsock);
//			m_pDoc->m_bIpasteLastData = TRUE;
			m_pDoc->m_strlastReceivetext = m_pDoc->m_pClipBoard->m_StrData;
			m_pDoc->m_pClipBoard->MySetClipboardData();
			break;
			}
		case 1 :
			{
			CDib dib;
			dib.Serialize(arsock);
//			m_pDoc->m_bIpasteLastData = TRUE;
			::OpenClipboard(NULL);
			dib.CopyToClipboard();
			m_pDoc->m_dwlasteDibSize = dib.m_dwSizeImage;
			if(m_pDoc->m_lpbyteLastDibData != NULL)
				{
				delete m_pDoc->m_lpbyteLastDibData;
				m_pDoc->m_lpbyteLastDibData = NULL;
				}
			m_pDoc->m_lpbyteLastDibData =(LPBYTE) new char[dib.m_dwSizeImage];
			unsigned int i;
			for(i=0;i< dib.m_dwSizeImage ; i++)
				m_pDoc->m_lpbyteLastDibData[i] = dib.m_lpImage[i];
			break;
			}
		case 2 :
			{
			m_pDoc->m_pFichier = new CFichier("",m_pDoc);
			arsock >> m_pDoc->m_pFichier->m_strNameExt;
			if(!m_pDoc->m_pFichier->AccepterEtSauverSous())
				{
				delete m_pDoc->m_pFichier;
				m_pDoc->m_pFichier = NULL;
				CPacketType * pPacket = new CPacketType(m_pDoc);
				pPacket->m_iDataType = 5;
				m_pDoc->m_pClientSocket->SendPacket(pPacket);
				delete pPacket;
				}
			break;
			}
		case 3 :
			{
			CPacketType * pPacket = new CPacketType(m_pDoc);
			pPacket->m_iDataType = 4;
			m_pDoc->m_pClientSocket->SendPacket(pPacket);
			delete pPacket;
			break;
			}
		case 4 :
			{
			m_pDoc->m_pFichier->Serialize(arsock);
			m_pDoc->m_pFichier->FichierFermer();
			delete m_pDoc->m_pFichier;
			m_pDoc->m_pFichier = NULL;
			//m_pDoc->m_bTransfertEnCours = FALSE;
			break;
			}
		case 5 :
			{			
			m_pDoc->m_pFichier->m_file.Close();
			delete m_pDoc->m_pFichier;
			m_pDoc->m_pFichier = NULL;
			//m_pDoc->m_bTransfertEnCours = FALSE;
			break;
			}
		case 6://reception demande initialisation multicopie
			{
			m_pDoc->m_pFichier = new CFichier("",m_pDoc);
			//arsock >> m_pDoc->m_pFichier->m_strNameExt;
			if(m_pDoc->m_bAutoSaveFic)
				m_pDoc->m_pFichier->CreerPathautosave();

			else
				if(m_pDoc->m_pathmultiTransfert=="")
					m_pDoc->m_pFichier->InitialiseMultiPath();

			//m_pDoc->m_pFichier->SauverFichier();
			//m_pDoc->m_pFichier->Serialize(arsock);
			//m_pDoc->m_pFichier->FichierFermer();
			//delete m_pDoc->m_pFichier;
			//m_pDoc->m_pFichier = NULL;
			CPacketType * pPacket = new CPacketType(m_pDoc);
			pPacket->m_iDataType = 7;
			m_pDoc->m_pClientSocket->SendPacket(pPacket);
			delete pPacket;
			delete m_pDoc->m_pFichier;
			m_pDoc->m_pFichier = NULL;
			break;
			}
		case 7 ://reception path multicopi pret
			{
			m_pDoc->Envoisfichiers();
			//m_pDoc->m_pathmultiTransfert="";
			break;
			}
		case 8 ://reception des fichiers depuis le Clist
			{
			m_pDoc->m_pFichier = new CFichier("",m_pDoc);
			arsock >> m_pDoc->m_pFichier->m_strNameExt;
			m_pDoc->m_pFichier->CreerPathMultiSave();
			m_pDoc->m_pFichier->SauverFichier();
			m_pDoc->m_pFichier->Serialize(arsock);
			m_pDoc->m_pFichier->FichierFermer();
			delete m_pDoc->m_pFichier;
			m_pDoc->m_pFichier = NULL;
			break;
			}
		case 9://multi transfert terminé.
			{
			m_pDoc->m_pathmultiTransfert="";
			break;
			}
		case 10 :
			{
			m_pDoc->TransfertAnnule();
			break;
			}
		case 255 :
			{
			AfxMessageBox("reception d'un packet non initialisé");
			m_pDoc->AbortCurrentCx();
			break;
			}
		default :
			{
			AfxMessageBox("Erreur de réception Cx terminée");
			m_pDoc->AbortCurrentCx();
			}
		}
	}
}

