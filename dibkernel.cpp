/*---------------------------------------------------------------------------------
	dibkernel.cpp, version 1.0, June 1997
	René Dencker Eriksen (http://www.imada.ou.dk/~edr) and
	Hans-Martin Brændmose Jensen (http://www.mip.ou.dk/~hansm)
---------------------------------------------------------------------------------*/

#include "stdafx.h"		//standard precompiled headers
#include "dibkernel.h"

//default color table for 8 bit color depth
const BYTE def256pal_r[256] = {0,128,0,128,0,128,0,192,192,166,64,96,128,160,192,
	224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,
	192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,
	160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,
	128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,
	96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,
	64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,
	32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,
	224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,
	192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,
	160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,128,160,192,224,0,32,64,96,
	128,160,255,160,128,255,0,255,0,255,0,255};
const BYTE def256pal_g[256] = {0,0,128,128,0,0,128,192,220,202,32,32,32,32,32,32,
	64,64,64,64,64,64,64,64,96,96,96,96,96,96,96,96,128,128,128,128,128,128,128,
	128,160,160,160,160,160,160,160,160,192,192,192,192,192,192,192,192,224,224,
	224,224,224,224,224,224,0,0,0,0,0,0,0,0,32,32,32,32,32,32,32,32,64,64,64,64,
	64,64,64,64,96,96,96,96,96,96,96,96,128,128,128,128,128,128,128,128,160,160,
	160,160,160,160,160,160,192,192,192,192,192,192,192,192,224,224,224,224,224,
	224,224,224,0,0,0,0,0,0,0,0,32,32,32,32,32,32,32,32,64,64,64,64,64,64,64,64,
	96,96,96,96,96,96,96,96,128,128,128,128,128,128,128,128,160,160,160,160,160,
	160,160,160,192,192,192,192,192,192,192,192,224,224,224,224,224,224,224,224,
	0,0,0,0,0,0,0,0,32,32,32,32,32,32,32,32,64,64,64,64,64,64,64,64,96,96,96,96,
	96,96,96,96,128,128,128,128,128,128,128,128,160,160,160,160,160,160,160,160,
	192,192,192,192,192,192,251,160,128,0,255,255,0,0,255,255};
const BYTE def256pal_b[256] = {0,0,0,0,128,128,128,192,192,240,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,240,164,128,
	0,0,0,255,255,255,255};

IMPLEMENT_DYNCREATE(CDib,CObject);

CDib::CDib()
{
	m_pntOrigo = CPoint(0,0);	//default origo
	m_lpBMIH = NULL;
	m_lpImage = NULL;
	m_hPalette = NULL;
	Empty();
}

CDib::CDib(CSize size, int nBitCount, BOOL bInitialize)
{
	m_pntOrigo = CPoint(0,0);	//default origo
	m_hPalette = NULL;
	m_lpBMIH = NULL;
	m_lpImage = NULL;
	Empty();
	ComputePaletteSize(nBitCount);
	m_lpBMIH = (LPBITMAPINFOHEADER) new 
		char[sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*m_nColorTableEntries];
	m_lpBMIH->biSize = sizeof(BITMAPINFOHEADER);
	m_lpBMIH->biWidth = size.cx;
	m_lpBMIH->biHeight = size.cy;
	m_lpBMIH->biPlanes = 1;
	m_lpBMIH->biBitCount = nBitCount;
	m_lpBMIH->biCompression = BI_RGB;
	m_lpBMIH->biSizeImage = 0;
	m_lpBMIH->biXPelsPerMeter = 0;
	m_lpBMIH->biYPelsPerMeter = 0;
	m_lpBMIH->biClrUsed = m_nColorTableEntries;
	m_lpBMIH->biClrImportant = m_nColorTableEntries;
	ComputeMetrics();
	m_lpImage=(LPBYTE) new char[m_dwSizeImage];
	if (bInitialize) {
		//make default palette from def256pal_x constants
		int i;
		switch (nBitCount) {
			case 1:
				SetPaletteEntry(0,0);					//black
				SetPaletteEntry(1,RGB(255,255,255));	//white
				break;
			case 8:
				for (i=0; i<=255; i++) {
					SetPaletteEntry(i,RGB(def256pal_r[i],def256pal_g[i],def256pal_b[i]));
				}
				break;
			case 24:
				break;
		}
		memset(m_lpImage, 0, m_dwSizeImage); //initialize image bits to zero
	}
	MakePalette();
}

CDib::CDib(const CDib& dib,CRect rect)
//copy area of interest from dib
{
    int headerSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*dib.m_nColorTableEntries;
    //copy header
    m_lpBMIH = (LPBITMAPINFOHEADER) new char[headerSize];
    memcpy(m_lpBMIH,dib.m_lpBMIH,headerSize);
	//correct size
	m_lpBMIH->biWidth=rect.Width();
	m_lpBMIH->biHeight=rect.Height();
	m_lpBMIH->biSizeImage = 0;
    //compute member variables
    ComputeMetrics();
    ComputePaletteSize(dib.m_lpBMIH->biBitCount);
    MakePalette();
	m_pntOrigo = CPoint(0,0);	//default origo
    //copy bits
    m_lpImage = (LPBYTE)new char[m_dwSizeImage];
	for(int y=rect.top; y<=rect.bottom; y++){
		for(int x=rect.left; x<=rect.right; x++){
			SetPixel(CPoint(x-rect.left,y-rect.top),dib.GetPixel(CPoint(x,y)));
		}
	}
}

CDib& CDib::operator=(const CDib& dib)
{
	ASSERT(this != &dib); //beware of dib=dib

	if (dib.m_lpBMIH) {
		Empty(); //clear left operand (dib we are coping to)
		int headerSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*dib.m_nColorTableEntries;
		//copy header
		m_lpBMIH = (LPBITMAPINFOHEADER) new char[headerSize];
		memcpy(m_lpBMIH,dib.m_lpBMIH,headerSize);
		//copy member variables
		ComputeMetrics();
		ComputePaletteSize(dib.m_lpBMIH->biBitCount);
		MakePalette();
		m_pntOrigo = dib.m_pntOrigo;
		//copy bits
		m_lpImage = (LPBYTE)new char[dib.m_dwSizeImage];
		memcpy(m_lpImage,dib.m_lpImage,dib.m_dwSizeImage);
	}
	return *this;
}

CDib::~CDib()
{
	Empty(); //clean up memory
}

CSize CDib::GetDimensions()
{	
	if(m_lpBMIH == NULL) return CSize(0, 0);
	return CSize((int) m_lpBMIH->biWidth, (int) m_lpBMIH->biHeight);
}

BOOL CDib::Draw(CDC* pDC,CRect rcDest,CPoint pntSrc)
/*-----------------------------------------------------------------------------
pDC:	Device context pointer to do output to.
rcDest:	Rectangle on DC to do output to.
pntSrc:	Coordinate of the lower-left corner of the DIB to output into rcDest.
-----------------------------------------------------------------------------*/
{
	/* Check for valid DIB handle */
	if ((m_lpBMIH == NULL) /*|| (m_hPalette == NULL)*/) return FALSE;

	BOOL     bSuccess=FALSE; //Success/fail flag
	HPALETTE hOldPal=NULL; //Previous palette (our DIB's palette is m_hPalette)
	CSize	 dibsize = GetDimensions(); //Get DIB's dimensions

	// Select as background since we have already realized in forground if needed
	hOldPal = ::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	if (pDC->IsPrinting())   // printer DC
	{
		// get size of printer page (in pixels)
		int cxPage = pDC->GetDeviceCaps(HORZRES);
		int cyPage = pDC->GetDeviceCaps(VERTRES);
		// get printer pixels per inch
		int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
		int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

		// Best Fit case -- create a rectangle which preserves
		// the DIB's aspect ratio, and fills the page horizontally.
		//
		// The formula in the "->bottom" field below calculates the Y
		// position of the printed bitmap, based on the size of the
		// bitmap, the width of the page, and the relative size of
		// a printed pixel (cyInch / cxInch).
		rcDest.top = rcDest.left = 0;
		rcDest.bottom = (int)(((double)dibsize.cy*cxPage*cyInch)
				/((double)dibsize.cx*cxInch));
		rcDest.right = cxPage;
	}
	/* Make sure to use the stretching mode best for color pictures */
	::SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
	/* Determine whether to call StretchDIBits or SetDIBitsToDevice */
	if (dibsize == rcDest.Size()) {
		bSuccess = ::SetDIBitsToDevice(
			pDC->GetSafeHdc(),		//handle of device context
			rcDest.left,			//x-coordinate of upper-left corner of dest. rect.
			rcDest.top,				//y-coordinate of upper-left corner of dest. rect.
			rcDest.Width(),			//source rectangle width
			rcDest.Height(),		//source rectangle height
			pntSrc.x,				//x-coordinate of lower-left corner of source rect.
			pntSrc.y,				//y-coordinate of lower-left corner of source rect.
			0,						//first scan line in array
			rcDest.Height(),		//number of scan lines
			m_lpImage,				//address of array with DIB bits
			(LPBITMAPINFO)m_lpBMIH,	//address of structure with bitmap info.
			DIB_RGB_COLORS);		//RGB or palette indices
	}
	else {
		bSuccess = ::StretchDIBits(
			pDC->GetSafeHdc(),		//handle of device context
			rcDest.left,			//x-coordinate of upper-left corner of dest. rect.
			rcDest.top,				//y-coordinate of upper-left corner of dest. rect.
			rcDest.Width(),			//width of destination rectangle
			rcDest.Height(),		//height of destination rectangle
			pntSrc.x,				//x-coordinate of upper-left corner of source rect.
			pntSrc.y,				//y-coordinate of upper-left corner of source rect.
			m_lpBMIH->biWidth,		//width of source rectangle
			m_lpBMIH->biHeight,		//height of source rectangle
			m_lpImage,				//address of bitmap bits
			(LPBITMAPINFO)m_lpBMIH,	//address of bitmap data
			DIB_RGB_COLORS,			//usage
			SRCCOPY);				//raster operation code
	}
	/* Reselect old palette */
	if (hOldPal != NULL)
	{
		::SelectPalette(pDC->GetSafeHdc(), hOldPal, TRUE);
	}
    return bSuccess;
}

BOOL CDib::MakePalette()
{
	// makes a logical palette (m_hPalette) from the DIB's color table
	// this palette will be selected and realized prior to drawing the DIB
	if(m_nColorTableEntries == 0) return FALSE;
	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);
	LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) +
		m_nColorTableEntries * sizeof(PALETTEENTRY)];
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = m_nColorTableEntries;
	LPRGBQUAD pDibQuad = (LPRGBQUAD) m_lpvColorTable;
	for(int i = 0; i < m_nColorTableEntries; i++) {
		pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
		pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
		pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
		pDibQuad++;
	}
	m_hPalette = ::CreatePalette(pLogPal);
	delete pLogPal;
	return TRUE;
}	

BOOL CDib::Read(CFile* pFile) //CFile ptr passed by the documents serialize function
{
	// 1. read file header to get size of info hdr + color table
	// 2. read info hdr (to get image size) and color table
	// 3. read image

	Empty();
	int nCount, nSize;
	BITMAPFILEHEADER bmfh;
	TRY {
		nCount = pFile->Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		if(nCount != sizeof(BITMAPFILEHEADER)) {
			AfxMessageBox("Error reading header");
			return FALSE;
		}
		if(bmfh.bfType != 0x4d42) { // 'BM'
			AfxMessageBox("Invalid bitmap file");
			return FALSE;
		}
		nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		m_lpBMIH = (LPBITMAPINFOHEADER) new char[nSize];
		nCount = pFile->Read(m_lpBMIH, nSize); // info hdr & color table
		ComputeMetrics(); //sets m_dwSizeImage etc.
		m_lpImage = (LPBYTE) new char[m_dwSizeImage];
		nCount = pFile->Read(m_lpImage, m_dwSizeImage); // image only
	}
	CATCH (CException, e) {
		AfxMessageBox("Error reading file (exception thrown)");
		return FALSE;
	}
	END_CATCH
	ComputePaletteSize(m_lpBMIH->biBitCount);
	MakePalette();
	m_FileInfo.FileName=pFile->GetFileName();
	m_FileInfo.FilePath=pFile->GetFilePath();
	return TRUE;
}

BOOL CDib::Write(CFile* pFile) //CFile ptr passed by the documents serialize function
{
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42;  // 'BM'
	int nSize =  sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*m_nColorTableEntries;
	bmfh.bfSize = nSize+sizeof(BITMAPFILEHEADER);
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+
			sizeof(RGBQUAD)*m_nColorTableEntries;
	TRY {
		pFile->Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		pFile->Write((LPVOID) m_lpBMIH,nSize);
		pFile->Write((LPVOID) m_lpImage,m_dwSizeImage);
	}
	CATCH (CException, e) {
		AfxMessageBox("Write error");
		return FALSE;
	}
	END_CATCH
	m_FileInfo.FileName=pFile->GetFileName();
	m_FileInfo.FilePath=pFile->GetFilePath();
	return TRUE;
}

void CDib::Serialize(CArchive& ar)
{
//	CObject::Serialize(ar);	//always call base class Serialize
//	ar.Flush();
	if(ar.IsStoring()) {
		ar << m_nColorTableEntries;
		ar << m_dwSizeImage;
		ar << m_lpBMIH->biBitCount;
		ar << m_lpBMIH->biClrImportant;
		ar << m_lpBMIH->biClrUsed;
		ar << m_lpBMIH->biCompression;
		ar << m_lpBMIH->biHeight;
		ar << m_lpBMIH->biPlanes;
		ar << m_lpBMIH->biSize;
		ar << m_lpBMIH->biSizeImage;
		ar << m_lpBMIH->biWidth;
		ar << m_lpBMIH->biXPelsPerMeter;
		ar << m_lpBMIH->biYPelsPerMeter;
		ar << m_nByteWidth;
		ar << m_nColorTableEntries;
		//ar << m_pntOrigo.x;
		//ar << m_pntOrigo.y;

		unsigned int i;
		for(i=0;i< m_dwSizeImage ; i++)
			ar << m_lpImage[i];

	}
	else {
		ar >> m_nColorTableEntries;

		if(m_lpBMIH)
			delete m_lpBMIH;

		m_lpBMIH = (LPBITMAPINFOHEADER) new char[sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*m_nColorTableEntries];

		ar >> m_dwSizeImage;

		if(m_lpImage)
			delete m_lpImage;
	
		m_lpImage=(LPBYTE) new char[m_dwSizeImage];


		ar >> m_lpBMIH->biBitCount;
		ar >> m_lpBMIH->biClrImportant;
		ar >> m_lpBMIH->biClrUsed;
		ar >> m_lpBMIH->biCompression;
		ar >> m_lpBMIH->biHeight;
		ar >> m_lpBMIH->biPlanes;
		ar >> m_lpBMIH->biSize;
		ar >> m_lpBMIH->biSizeImage;
		ar >> m_lpBMIH->biWidth;
		ar >> m_lpBMIH->biXPelsPerMeter;
		ar >> m_lpBMIH->biYPelsPerMeter;
		ar >> m_nByteWidth;
		ar >> m_nColorTableEntries;
		
		

		unsigned int i;
		for(i=0;i< m_dwSizeImage ; i++)
			ar >> m_lpImage[i];

	}
}

int CDib::GetSizeImage()
{
	return m_dwSizeImage;
}

int CDib::GetSizeHeader()
{
	return sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*m_nColorTableEntries;
}

DWORD CDib::GetPixel(CPoint pnt) const
{
	CPoint pntReal = pnt+m_pntOrigo;
	register BYTE* adr;

	if ((pntReal.x>=0)&&(pntReal.x<m_lpBMIH->biWidth)&&
		(pntReal.y>=0)&&(pntReal.y<m_lpBMIH->biHeight))
		switch(m_lpBMIH->biBitCount) {
		case 1:
			adr = m_lpImage+(m_lpBMIH->biHeight-pntReal.y-1)*m_nByteWidth+(pntReal.x>>3);
			return (((*adr)&(0x80>>(pntReal.x&0x7)))!=0);
		case 8:
			adr = m_lpImage+(m_lpBMIH->biHeight-pntReal.y-1)*m_nByteWidth+pntReal.x;
			return (*adr)&0xff;
		case 24:
			adr = m_lpImage+(m_lpBMIH->biHeight-pntReal.y-1)*m_nByteWidth
				+pntReal.x+pntReal.x+pntReal.x;
			return ((*(DWORD*)adr)&0xffffff);
		default:
			AfxMessageBox("GetPixel: only implemented for 1,8 and 24 bit per pixels");
			return DIBERROR;
		}
	return DIBERROR;
}
	
DWORD CDib::SetPixel(CPoint pnt, DWORD color)
{
	CPoint pntReal = pnt + m_pntOrigo;
	register unsigned int pixnum;
	register BYTE* adr;

	if((pntReal.x>=0)&&(pntReal.x<m_lpBMIH->biWidth)&&
		(pntReal.y>=0)&&(pntReal.y<m_lpBMIH->biHeight))
		switch(m_lpBMIH->biBitCount) {
		case 1:
			adr = m_lpImage+(m_lpBMIH->biHeight-pntReal.y-1)*m_nByteWidth+(pntReal.x>>3);
			pixnum = pntReal.x & 0x7;
			color ? (*adr |= (0x80>>pixnum)) : (*adr &= (0xff7f>>pixnum));
			break;
		case 8:
			adr = m_lpImage+(m_lpBMIH->biHeight-pntReal.y-1)*m_nByteWidth+pntReal.x;
			*adr = (BYTE)color;
			break;
		case 24:
			adr = m_lpImage+(m_lpBMIH->biHeight-pntReal.y-1)*m_nByteWidth
				+pntReal.x+pntReal.x+pntReal.x;
			*((DWORD*)adr) = ((*((DWORD*)adr)) & 0xff000000) | (color & 0x00ffffff);
			break;
		default:
			AfxMessageBox("SetPixel: only implemented for 1,8 and 24 bit per pixels");
			return DIBERROR;
		}
	return DIBERROR;
}

void CDib::Empty()
{
	// this is supposed to clean up whatever is in the DIB
	if(m_lpBMIH != NULL) {
		delete [] m_lpBMIH;
	}
	if(m_lpImage != NULL){
		delete [] m_lpImage;
	}
	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);
	m_lpBMIH = NULL;
	m_lpImage = NULL;
	m_lpvColorTable = NULL;
	m_nColorTableEntries = 0;
	m_dwSizeImage = 0;
	m_hPalette = NULL;
}

void CDib::SetOrigo(CPoint pntOrigo)
{
	m_pntOrigo = pntOrigo;
}

BOOL CDib::SetPaletteEntry(BYTE bEntry, DWORD dwValue)
{
	switch (m_lpBMIH->biBitCount) {
		case 1:
			if (bEntry>1){
				AfxMessageBox("SetPaletteEntry: palette entry out of range");
				ASSERT(FALSE);
				return FALSE;
			}
			*((DWORD*)((BYTE*)m_lpvColorTable+bEntry*sizeof(RGBQUAD)))=dwValue;
			return TRUE;
		case 8:
			*((DWORD*)((BYTE*)m_lpvColorTable+bEntry*sizeof(RGBQUAD))) =dwValue;
			return TRUE;
		case 24:
			AfxMessageBox("SetPaletteEntry: image with 24 bits per pixel has no palette");
			ASSERT(FALSE);
			return FALSE;
		default:
			AfxMessageBox("CDib only supports 1, 8 and 24 bits per pixel régler votre affichage");
			ASSERT(FALSE);
			return FALSE;
		}
}

DWORD CDib::GetPaletteEntry(BYTE bEntry)
{
	switch (m_lpBMIH->biBitCount) {
		case 1:
			if (bEntry>1){
				AfxMessageBox("GetPaletteEntry: palette entry out of range");
				ASSERT(FALSE);
				return DIBERROR;
			}
			return *((DWORD*)((BYTE*)m_lpvColorTable+bEntry*sizeof(RGBQUAD)));
		case 8:
			return *((DWORD*)((BYTE*)m_lpvColorTable+bEntry*sizeof(RGBQUAD)));
		case 24:
			AfxMessageBox("GetPaletteEntry: image with 24 bits per pixel has no palette");
			ASSERT(FALSE);
			return DIBERROR;
		default:
			AfxMessageBox("CDib only supports 1, 8 and 24 bits per pixel régler votre affichage");
			ASSERT(FALSE);
			return DIBERROR;
		}
}

//***********************************************
//         private helper functions
//***********************************************

void CDib::ComputePaletteSize(int nBitCount)
{
	if(m_lpBMIH==NULL || m_lpBMIH->biClrUsed == 0) {
		switch(nBitCount) {
			case 1:
				m_nColorTableEntries = 2;
				break;
			case 4:
				m_nColorTableEntries = 16;
				break;
			case 8:
				m_nColorTableEntries = 256;
				break;
			case 24:
				m_nColorTableEntries = 0;
				break;
			default:
				AfxMessageBox("bitmap supporte seulement 1, 8 et 24 (votre écran doit être configuré)");
				ASSERT(FALSE);
		}
	}
	else {
		m_nColorTableEntries = m_lpBMIH->biClrUsed;
	}
	ASSERT(m_nColorTableEntries <= 256); 
}

void CDib::ComputeMetrics()
{
	m_dwSizeImage = m_lpBMIH->biSizeImage;
	if(m_dwSizeImage == 0) {
		DWORD dwBytes = ((DWORD) m_lpBMIH->biWidth * m_lpBMIH->biBitCount) / 32;
		if(((DWORD) m_lpBMIH->biWidth * m_lpBMIH->biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;
		m_dwSizeImage = dwBytes * m_lpBMIH->biHeight; // no compression
	}
	m_lpvColorTable = (LPBYTE) m_lpBMIH + sizeof(BITMAPINFOHEADER);
	m_nByteWidth = (((m_lpBMIH->biWidth)*(m_lpBMIH->biBitCount) + 31) / 32 * 4);
}

BOOL CDib::CopyToClipboard()
{
	//Before calling CopyToClipboard, an application must open the clipboard
	//  by using the OpenClipboard function.

	if (m_lpBMIH==NULL)	return FALSE;

	// Clean clipboard of contents, and copy the DIB.
	HGLOBAL h = ::GlobalAlloc(GHND,GetSizeHeader()+GetSizeImage());
	if (h != NULL) {
		void* lp = ::GlobalLock(h);
		//copy header and palette
		memcpy(lp,m_lpBMIH,GetSizeHeader());
		//copy image bits
		memcpy((LPBYTE)lp+GetSizeHeader(),m_lpImage,GetSizeImage());
		::GlobalUnlock(h);
		EmptyClipboard();
		SetClipboardData(CF_DIB,h);
		CloseClipboard();
		return TRUE;
	}
	return FALSE;
}

BOOL CDib::PasteFromClipboard()
{
	//Before calling PasteFromClipboard, an application must open the clipboard
	//  by using the OpenClipboard function.

	HGLOBAL hNewDIB = (HGLOBAL)::GetClipboardData(CF_DIB);
	if (hNewDIB != NULL) {
		Empty();	//free the old DIB
		LPBITMAPINFOHEADER lpNewBMIH = m_lpBMIH = (LPBITMAPINFOHEADER)::GlobalLock(hNewDIB);
		ComputePaletteSize(lpNewBMIH->biBitCount);
		int headersize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*m_nColorTableEntries;

		m_lpBMIH = (LPBITMAPINFOHEADER) new char[headersize];
	    //copy header and palette
		memcpy(m_lpBMIH,lpNewBMIH,headersize);
		ComputeMetrics();
		MakePalette();

		m_lpImage=(LPBYTE) new char[m_dwSizeImage];
		//copy image bits
		memcpy(m_lpImage,(LPBYTE)lpNewBMIH+headersize,m_dwSizeImage);
		
		::GlobalUnlock(hNewDIB);
		m_pntOrigo = CPoint(0,0);	//default origo

		CloseClipboard();	//enable other windows to access the clipboard
		return TRUE;
	}
	return FALSE;
}
