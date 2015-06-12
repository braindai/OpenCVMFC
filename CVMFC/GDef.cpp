#include "stdafx.h"
#include "GDef.h"




CString GetAppPath()
{

	CString m_FilePath;
	GetModuleFileName(NULL,m_FilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	m_FilePath.ReleaseBuffer();
	int m_iPosIndex;
	m_iPosIndex = m_FilePath.ReverseFind('\\');
	m_FilePath = m_FilePath.Left(m_iPosIndex);
	return m_FilePath;

}
int roiCreateBMPHeader(const int nWidth, const int nHeight, const int colorbits, unsigned char * pBMPHeader)
{
	LPBITMAPINFO LPBMPINFO;
	LPBMPINFO = (LPBITMAPINFO) pBMPHeader;
	RGBQUAD mypalette[256];
	int i = 0;
	LPBMPINFO->bmiHeader.biSize = 40;
	LPBMPINFO->bmiHeader.biWidth = nWidth;
	//#if defined UNDER_CE
	//    LPBMPINFO->bmiHeader.biHeight = abs(nHeight);
	//#else
	LPBMPINFO->bmiHeader.biHeight = -abs(nHeight);
	//#endif
	LPBMPINFO->bmiHeader.biPlanes = 1;
	LPBMPINFO->bmiHeader.biBitCount = (unsigned char) colorbits;
	LPBMPINFO->bmiHeader.biCompression = 0;
	//	LPBMPINFO->bmiHeader.biSizeImage = (LPBMPINFO->bmiHeader.biWidth*LPBMPINFO->bmiHeader.biBitCount+31)/32*4*abs(LPBMPINFO->bmiHeader.biHeight);
	LPBMPINFO->bmiHeader.biSizeImage = nWidth*nHeight;
	LPBMPINFO->bmiHeader.biXPelsPerMeter = 0xdece;
	LPBMPINFO->bmiHeader.biYPelsPerMeter = 0xded8;
	LPBMPINFO->bmiHeader.biClrUsed = 0;
	LPBMPINFO->bmiHeader.biClrImportant = 0;

	if (colorbits == 8)
	{
		for (i=0; i<256; i++)
		{
			mypalette[i].rgbBlue=(unsigned char)i;
			mypalette[i].rgbGreen=(unsigned char)i;
			mypalette[i].rgbRed=(unsigned char)i;
			LPBMPINFO->bmiColors[i]=mypalette[i];
		}
	}
	return 0;
}
void ConvertCharToCString(char str_in[],CString& cstring)
{
#ifdef UNICODE
	size_t newsize;
	mbstowcs_s(&newsize,NULL,0,str_in,_TRUNCATE);
	wchar_t* sTmp = new wchar_t[newsize];
	size_t convertedCharsw = 0;
	mbstowcs_s(&convertedCharsw, sTmp, newsize, str_in, _TRUNCATE);
	cstring.Format(_T("%s"),sTmp);
	delete[] sTmp;
#else
	cstring.Format(_T("%s"),msg);
#endif
}

//should "delete[] str_out" outside
char* ConvertCStringToChar(CString& cstring)
{
#ifdef UNICODE
		//char filename[PATH_MAX];
		int newsizew = (cstring.GetLength()+1)*2;
		char* str_out = new char[newsizew];
		size_t convertedCharsw = 0;
		wcstombs_s(&convertedCharsw, str_out, newsizew, cstring, _TRUNCATE);

#else
		int newsizew = cstring.GetLength()+1;
		char str_out = new char[newsizew];
		strcpy(str_out,cstring);
		str_out[newsizew-1] = 0;
#endif
		return str_out;
}

char* ConvertTStringToChar(const TCHAR* tchar)
{

	int newsizew = _tcslen(tchar)+1;
	char* str_out = new char[newsizew];
#ifdef UNICODE
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, str_out, newsizew, tchar, _TRUNCATE);	
#else
	_tcscpy(str_out,tchar);
#endif
	str_out[newsizew - 1] = 0;
	return str_out;
}
