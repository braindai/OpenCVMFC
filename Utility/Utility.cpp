
#include "stdafx.h"
#include "../Utility/Utility.h"

namespace Utility_DXQ{

	StringCov::StringCov() :m_char(NULL), m_wchar(NULL)
	{
	}
	StringCov::~StringCov()
	{
		Release();
	}
	char* StringCov::WcharToChar(const wchar_t* wp)
	{
		Release();
		int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
		m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		return m_char;
	}
	wchar_t* StringCov::CharToWchar(const char* c)
	{
		Release();
		int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
		m_wchar = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_wchar, len);
		m_wchar[len] = '\0';
		return m_wchar;
	}
	void StringCov::Release()
	{
		if (m_char)
		{
			delete m_char;
			m_char = NULL;
		}
		if (m_wchar)
		{
			delete m_wchar;
			m_wchar = NULL;
		}
	}
	char* StringCov::StringToChar(const string& s)
	{
		return const_cast<char*>(s.c_str());
	}
	char* StringCov::WstringToChar(const std::wstring &ws)
	{
		const wchar_t* wp = ws.c_str();
		return WcharToChar(wp);
	}
	wchar_t* StringCov::WstringToWchar(const std::wstring &ws)
	{
		return const_cast<wchar_t*>(ws.c_str());
	}
	wchar_t* StringCov::StringToWchar(const string& s)
	{
		const char* p = s.c_str();
		return CharToWchar(p);
	}
	string StringCov::WstringToString(const std::wstring &ws)
	{
		string s;
		char* p = WstringToChar(ws);
		s.append(p);
		return s;
	}
	wstring StringCov::StringToWstring(const std::string &s)
	{
		wstring ws;
		wchar_t* wp = StringToWchar(s);
		ws.append(wp);
		return ws;
	}
#ifdef USE_MFC
	string StringCov::CStringToString(CString& cs)
	{
		string s;
#ifdef _UNICODE
		char *p = WcharToChar(cs.GetBuffer());
		s.assign(p);
#else
		s.assign(cs.GetBuffer());
#endif
		cs.ReleaseBuffer();
		return s;
	}
	wstring StringCov::CStringToWstring(CString& cs)
	{
		wstring ws;
#ifdef _UNICODE
		ws.assign(cs.GetBuffer());
#else
		char *wp = charToWChar(cs.GetBuffer());
		ws.assign(wp);	
#endif
		cs.ReleaseBuffer();
		return ws;
	}
	CString StringCov::StringToCString(const string& s)
	{
		CString cs;
#ifdef _UNICODE
		wchar_t* wp = StringToWchar(s);
		cs.Format(L"%s", wp);
#else	
		cs.Format("%s",s.c_str());
#endif
		return cs;
	}
	CString StringCov::WstringToCString(const wstring& ws)
	{
		CString cs;
#ifdef _UNICODE
		cs.Format(L"%s", ws.c_str());
#else
		char* p=WstringToChar(ws);
		cs.Format("%s",p);
#endif
		return cs;
	}
#endif
	LPBITMAPINFO CtreateMapInfo(Mat workImg, int flag)
	{                                           //  建立位图信息
		BITMAPINFOHEADER BIH = { 40, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0 };
		LPBITMAPINFO lpBmi;
		int      wid, hei, bits, colors, i;

		wid = workImg.cols;
		hei = workImg.rows;
		bits = 8*workImg.elemSize();

		if (bits > 8) colors = 0;
		else colors = 1 << bits;

		lpBmi = (LPBITMAPINFO)malloc(40 + 4 * colors);
		BIH.biWidth = wid;
		BIH.biHeight = -hei;
		BIH.biBitCount = (BYTE)bits;
		memcpy(lpBmi, &BIH, 40);                  //  复制位图信息头
		RGBQUAD VgaColorTab[256] = {0};
		if (bits == 8) {                          //  256 色位图
			if (flag == 1) {                      //  设置灰阶调色板
				for (i = 0; i < 256; i++) {
					VgaColorTab[i].rgbRed = VgaColorTab[i].rgbGreen =
						VgaColorTab[i].rgbBlue = (BYTE)i;
				}
				memcpy(lpBmi->bmiColors, VgaColorTab, 1024);
			}
			else if (flag == 2) {                 //  设置默认调色板
				memcpy(lpBmi->bmiColors, VgaDefPal, 1024);
			}
			else if (flag == 3) {                 //  设置自定义调色板
				memcpy(lpBmi->bmiColors, VgaColorTab, 1024);
			}
		}
		return(lpBmi);
	}
}


