/*---------------------------------------------------------------------------------
	dibkernel.h, version 1.0, June 1997
	René Dencker Eriksen (http://www.imada.ou.dk/~edr) and
	Hans-Martin Brændmose Jensen (http://www.mip.ou.dk/~hansm)
---------------------------------------------------------------------------------*/

#ifndef _CDIBKERNEL_H
#define _CDIBKERNEL_H

#define DIBERROR 0xffffffff			//define constants
#define BLACK    0x0				//for 1 bit pictures only
#define WHITE    0x1				//for 1 bit pictures only

class CDib : public CObject
{
	DECLARE_DYNCREATE(CDib)

public: //attributes
	struct strFileInfo{
		CString FilePath;				//path+filename+extension
		CString FileName;				//     filename+extension
	}m_FileInfo;
	LPBITMAPINFOHEADER m_lpBMIH;		//ptr to BITMAPINFOHEADER structure
private: //attributes
	LPVOID  m_lpvColorTable;			//ptr to DIB palette
	CPoint m_pntOrigo;					//GetPixel and SetPixel origo
						//address of DIB bits
	int m_nByteWidth;					//width of image (incl. zeropadding)
					//size of image (incl. zeropadding)
	int m_nColorTableEntries;			//number of palette entries
	HPALETTE m_hPalette;				//system palette handle
public: //methods
	CDib();								//default constructor
	CDib(CSize size, int nBitCount,BOOL bInitialize=TRUE);
										//constructor for empty DIB
	CDib(const CDib& dib,CRect rect);	//copies rect from given DIB to new DIB
	~CDib();							//destructor
	CDib& operator =(const CDib& dib);	//overloading of assignment operator
	int GetSizeImage();					//image bits in bytes (incl. zeropad.)
	int GetSizeHeader();				//size of bitmapinfoheader+colortable
	CSize GetDimensions();				//dimensions of image in pixels
	BOOL CDib::Draw(CDC* pDC,CRect rcDest, CPoint pntSrc=0); 
										//draw DIB, ment to be called from OnDraw
	BOOL Read(CFile* pFile);			//reads BMP (DIB) from file
	BOOL Write(CFile* pFile);			//writes BMP (DIB) to file
	void Serialize(CArchive& ar);		//serializes the CDib object
	void Empty();						//clear image and deallocate memory
	DWORD GetPixel(CPoint pnt) const;	//get pixel value
	DWORD SetPixel(CPoint pnt, DWORD color); //set pixel value
	void SetOrigo(CPoint pntOrigo);		//set origo for GetPixel and SetPixel
	DWORD GetPaletteEntry(BYTE bEntry);	//retrieves a palette entry
	BOOL SetPaletteEntry(BYTE bEntry, DWORD dwValue); //sets a palette entry
	BOOL CopyToClipboard();				//cpy to clipbrd - use OpenClipboard() first
	BOOL PasteFromClipboard();			//pst from clpbrd - use OpenClipboard() first
	DWORD m_dwSizeImage;	
	LPBYTE  m_lpImage;
	//to convert RGB-value to DWORD use the RGB(BYTE r,BYTE g,BYTE b) macro
	//to get Red, Green, Blue component use GetBValue(rgb), GetGValue(rgb),
	//  GetRValue(rgb) or PALETTEINDEX(i) macros
private: //methods
	BOOL MakePalette();
	void ComputePaletteSize(int nBitCount);
	void ComputeMetrics();
};

#endif //_CDIBKERNEL_H