#ifndef _Utility_DXQ_
#define _Utility_DXQ_

#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

namespace Utility_DXQ{

	//---------------------------------------------------------
	//  VGA 256色默认调色板数据

	static RGBQUAD VgaDefPal[256] = {
		{ 0x00, 0x00, 0x00, 0x00 }, { 0xa8, 0x00, 0x00, 0x00 }, { 0x00, 0xa8, 0x00, 0x00 }, { 0xa8, 0xa8, 0x00, 0x00 },
		{ 0x00, 0x00, 0xa8, 0x00 }, { 0xa8, 0x00, 0xa8, 0x00 }, { 0x00, 0x54, 0xa8, 0x00 }, { 0xa8, 0xa8, 0xa8, 0x00 },
		{ 0x54, 0x54, 0x54, 0x00 }, { 0xfc, 0x54, 0x54, 0x00 }, { 0x54, 0xfc, 0x54, 0x00 }, { 0xfc, 0xfc, 0x54, 0x00 },
		{ 0x54, 0x54, 0xfc, 0x00 }, { 0xfc, 0x54, 0xfc, 0x00 }, { 0x54, 0xfc, 0xfc, 0x00 }, { 0xfc, 0xfc, 0xfc, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00 }, { 0x14, 0x14, 0x14, 0x00 }, { 0x20, 0x20, 0x20, 0x00 }, { 0x2c, 0x2c, 0x2c, 0x00 },
		{ 0x38, 0x38, 0x38, 0x00 }, { 0x44, 0x44, 0x44, 0x00 }, { 0x50, 0x50, 0x50, 0x00 }, { 0x60, 0x60, 0x60, 0x00 },
		{ 0x70, 0x70, 0x70, 0x00 }, { 0x80, 0x80, 0x80, 0x00 }, { 0x90, 0x90, 0x90, 0x00 }, { 0xa0, 0xa0, 0xa0, 0x00 },
		{ 0xb4, 0xb4, 0xb4, 0x00 }, { 0xc8, 0xc8, 0xc8, 0x00 }, { 0xe0, 0xe0, 0xe0, 0x00 }, { 0xfc, 0xfc, 0xfc, 0x00 },
		{ 0xfc, 0x00, 0x00, 0x00 }, { 0xfc, 0x00, 0x40, 0x00 }, { 0xfc, 0x00, 0x7c, 0x00 }, { 0xfc, 0x00, 0xbc, 0x00 },
		{ 0xfc, 0x00, 0xfc, 0x00 }, { 0xbc, 0x00, 0xfc, 0x00 }, { 0x7c, 0x00, 0xfc, 0x00 }, { 0x40, 0x00, 0xfc, 0x00 },
		{ 0x00, 0x00, 0xfc, 0x00 }, { 0x00, 0x40, 0xfc, 0x00 }, { 0x00, 0x7c, 0xfc, 0x00 }, { 0x00, 0xbc, 0xfc, 0x00 },
		{ 0x00, 0xfc, 0xfc, 0x00 }, { 0x00, 0xfc, 0xbc, 0x00 }, { 0x00, 0xfc, 0x7c, 0x00 }, { 0x00, 0xfc, 0x40, 0x00 },
		{ 0x00, 0xfc, 0x00, 0x00 }, { 0x40, 0xfc, 0x00, 0x00 }, { 0x7c, 0xfc, 0x00, 0x00 }, { 0xbc, 0xfc, 0x00, 0x00 },
		{ 0xfc, 0xfc, 0x00, 0x00 }, { 0xfc, 0xbc, 0x00, 0x00 }, { 0xfc, 0x7c, 0x00, 0x00 }, { 0xfc, 0x40, 0x00, 0x00 },
		{ 0xfc, 0x7c, 0x7c, 0x00 }, { 0xfc, 0x7c, 0x9c, 0x00 }, { 0xfc, 0x7c, 0xbc, 0x00 }, { 0xfc, 0x7c, 0xdc, 0x00 },
		{ 0xfc, 0x7c, 0xfc, 0x00 }, { 0xdc, 0x7c, 0xfc, 0x00 }, { 0xbc, 0x7c, 0xfc, 0x00 }, { 0x9c, 0x7c, 0xfc, 0x00 },
		{ 0x7c, 0x7c, 0xfc, 0x00 }, { 0x7c, 0x9c, 0xfc, 0x00 }, { 0x7c, 0xbc, 0xfc, 0x00 }, { 0x7c, 0xdc, 0xfc, 0x00 },
		{ 0x7c, 0xfc, 0xfc, 0x00 }, { 0x7c, 0xfc, 0xdc, 0x00 }, { 0x7c, 0xfc, 0xbc, 0x00 }, { 0x7c, 0xfc, 0x9c, 0x00 },
		{ 0x7c, 0xfc, 0x7c, 0x00 }, { 0x9c, 0xfc, 0x7c, 0x00 }, { 0xbc, 0xfc, 0x7c, 0x00 }, { 0xdc, 0xfc, 0x7c, 0x00 },
		{ 0xfc, 0xfc, 0x7c, 0x00 }, { 0xfc, 0xdc, 0x7c, 0x00 }, { 0xfc, 0xbc, 0x7c, 0x00 }, { 0xfc, 0x9c, 0x7c, 0x00 },
		{ 0xfc, 0xb4, 0xb4, 0x00 }, { 0xfc, 0xb4, 0xc4, 0x00 }, { 0xfc, 0xb4, 0xd8, 0x00 }, { 0xfc, 0xb4, 0xe8, 0x00 },
		{ 0xfc, 0xb4, 0xfc, 0x00 }, { 0xe8, 0xb4, 0xfc, 0x00 }, { 0xd8, 0xb4, 0xfc, 0x00 }, { 0xc4, 0xb4, 0xfc, 0x00 },
		{ 0xb4, 0xb4, 0xfc, 0x00 }, { 0xb4, 0xc4, 0xfc, 0x00 }, { 0xb4, 0xd8, 0xfc, 0x00 }, { 0xb4, 0xe8, 0xfc, 0x00 },
		{ 0xb4, 0xfc, 0xfc, 0x00 }, { 0xb4, 0xfc, 0xe8, 0x00 }, { 0xb4, 0xfc, 0xd8, 0x00 }, { 0xb4, 0xfc, 0xc4, 0x00 },
		{ 0xb4, 0xfc, 0xb4, 0x00 }, { 0xc4, 0xfc, 0xb4, 0x00 }, { 0xd8, 0xfc, 0xb4, 0x00 }, { 0xe8, 0xfc, 0xb4, 0x00 },
		{ 0xfc, 0xfc, 0xb4, 0x00 }, { 0xfc, 0xe8, 0xb4, 0x00 }, { 0xfc, 0xd8, 0xb4, 0x00 }, { 0xfc, 0xc4, 0xb4, 0x00 },
		{ 0x70, 0x00, 0x00, 0x00 }, { 0x70, 0x00, 0x1c, 0x00 }, { 0x70, 0x00, 0x38, 0x00 }, { 0x70, 0x00, 0x54, 0x00 },
		{ 0x70, 0x00, 0x70, 0x00 }, { 0x54, 0x00, 0x70, 0x00 }, { 0x38, 0x00, 0x70, 0x00 }, { 0x1c, 0x00, 0x70, 0x00 },
		{ 0x00, 0x00, 0x70, 0x00 }, { 0x00, 0x1c, 0x70, 0x00 }, { 0x00, 0x38, 0x70, 0x00 }, { 0x00, 0x54, 0x70, 0x00 },
		{ 0x00, 0x70, 0x70, 0x00 }, { 0x00, 0x70, 0x54, 0x00 }, { 0x00, 0x70, 0x38, 0x00 }, { 0x00, 0x70, 0x1c, 0x00 },
		{ 0x00, 0x70, 0x00, 0x00 }, { 0x1c, 0x70, 0x00, 0x00 }, { 0x38, 0x70, 0x00, 0x00 }, { 0x54, 0x70, 0x00, 0x00 },
		{ 0x70, 0x70, 0x00, 0x00 }, { 0x70, 0x54, 0x00, 0x00 }, { 0x70, 0x38, 0x00, 0x00 }, { 0x70, 0x1c, 0x00, 0x00 },
		{ 0x70, 0x38, 0x38, 0x00 }, { 0x70, 0x38, 0x44, 0x00 }, { 0x70, 0x38, 0x54, 0x00 }, { 0x70, 0x38, 0x60, 0x00 },
		{ 0x70, 0x38, 0x70, 0x00 }, { 0x60, 0x38, 0x70, 0x00 }, { 0x54, 0x38, 0x70, 0x00 }, { 0x44, 0x38, 0x70, 0x00 },
		{ 0x38, 0x38, 0x70, 0x00 }, { 0x38, 0x44, 0x70, 0x00 }, { 0x38, 0x54, 0x70, 0x00 }, { 0x38, 0x60, 0x70, 0x00 },
		{ 0x38, 0x70, 0x70, 0x00 }, { 0x38, 0x70, 0x60, 0x00 }, { 0x38, 0x70, 0x54, 0x00 }, { 0x38, 0x70, 0x44, 0x00 },
		{ 0x38, 0x70, 0x38, 0x00 }, { 0x44, 0x70, 0x38, 0x00 }, { 0x54, 0x70, 0x38, 0x00 }, { 0x60, 0x70, 0x38, 0x00 },
		{ 0x70, 0x70, 0x38, 0x00 }, { 0x70, 0x60, 0x38, 0x00 }, { 0x70, 0x54, 0x38, 0x00 }, { 0x70, 0x44, 0x38, 0x00 },
		{ 0x70, 0x50, 0x50, 0x00 }, { 0x70, 0x50, 0x58, 0x00 }, { 0x70, 0x50, 0x60, 0x00 }, { 0x70, 0x50, 0x68, 0x00 },
		{ 0x70, 0x50, 0x70, 0x00 }, { 0x68, 0x50, 0x70, 0x00 }, { 0x60, 0x50, 0x70, 0x00 }, { 0x58, 0x50, 0x70, 0x00 },
		{ 0x50, 0x50, 0x70, 0x00 }, { 0x50, 0x58, 0x70, 0x00 }, { 0x50, 0x60, 0x70, 0x00 }, { 0x50, 0x68, 0x70, 0x00 },
		{ 0x50, 0x70, 0x70, 0x00 }, { 0x50, 0x70, 0x68, 0x00 }, { 0x50, 0x70, 0x60, 0x00 }, { 0x50, 0x70, 0x58, 0x00 },
		{ 0x50, 0x70, 0x50, 0x00 }, { 0x58, 0x70, 0x50, 0x00 }, { 0x60, 0x70, 0x50, 0x00 }, { 0x68, 0x70, 0x50, 0x00 },
		{ 0x70, 0x70, 0x50, 0x00 }, { 0x70, 0x68, 0x50, 0x00 }, { 0x70, 0x60, 0x50, 0x00 }, { 0x70, 0x58, 0x50, 0x00 },
		{ 0x40, 0x00, 0x00, 0x00 }, { 0x40, 0x00, 0x10, 0x00 }, { 0x40, 0x00, 0x20, 0x00 }, { 0x40, 0x00, 0x30, 0x00 },
		{ 0x40, 0x00, 0x40, 0x00 }, { 0x30, 0x00, 0x40, 0x00 }, { 0x20, 0x00, 0x40, 0x00 }, { 0x10, 0x00, 0x40, 0x00 },
		{ 0x00, 0x00, 0x40, 0x00 }, { 0x00, 0x10, 0x40, 0x00 }, { 0x00, 0x20, 0x40, 0x00 }, { 0x00, 0x30, 0x40, 0x00 },
		{ 0x00, 0x40, 0x40, 0x00 }, { 0x00, 0x40, 0x30, 0x00 }, { 0x00, 0x40, 0x20, 0x00 }, { 0x00, 0x40, 0x10, 0x00 },
		{ 0x00, 0x40, 0x00, 0x00 }, { 0x10, 0x40, 0x00, 0x00 }, { 0x20, 0x40, 0x00, 0x00 }, { 0x30, 0x40, 0x00, 0x00 },
		{ 0x40, 0x40, 0x00, 0x00 }, { 0x40, 0x30, 0x00, 0x00 }, { 0x40, 0x20, 0x00, 0x00 }, { 0x40, 0x10, 0x00, 0x00 },
		{ 0x40, 0x20, 0x20, 0x00 }, { 0x40, 0x20, 0x28, 0x00 }, { 0x40, 0x20, 0x30, 0x00 }, { 0x40, 0x20, 0x38, 0x00 },
		{ 0x40, 0x20, 0x40, 0x00 }, { 0x38, 0x20, 0x40, 0x00 }, { 0x30, 0x20, 0x40, 0x00 }, { 0x28, 0x20, 0x40, 0x00 },
		{ 0x20, 0x20, 0x40, 0x00 }, { 0x20, 0x28, 0x40, 0x00 }, { 0x20, 0x30, 0x40, 0x00 }, { 0x20, 0x38, 0x40, 0x00 },
		{ 0x20, 0x40, 0x40, 0x00 }, { 0x20, 0x40, 0x38, 0x00 }, { 0x20, 0x40, 0x30, 0x00 }, { 0x20, 0x40, 0x28, 0x00 },
		{ 0x20, 0x40, 0x20, 0x00 }, { 0x28, 0x40, 0x20, 0x00 }, { 0x30, 0x40, 0x20, 0x00 }, { 0x38, 0x40, 0x20, 0x00 },
		{ 0x40, 0x40, 0x20, 0x00 }, { 0x40, 0x38, 0x20, 0x00 }, { 0x40, 0x30, 0x20, 0x00 }, { 0x40, 0x28, 0x20, 0x00 },
		{ 0x40, 0x2c, 0x2c, 0x00 }, { 0x40, 0x2c, 0x30, 0x00 }, { 0x40, 0x2c, 0x34, 0x00 }, { 0x40, 0x2c, 0x3c, 0x00 },
		{ 0x40, 0x2c, 0x40, 0x00 }, { 0x3c, 0x2c, 0x40, 0x00 }, { 0x34, 0x2c, 0x40, 0x00 }, { 0x30, 0x2c, 0x40, 0x00 },
		{ 0x2c, 0x2c, 0x40, 0x00 }, { 0x2c, 0x30, 0x40, 0x00 }, { 0x2c, 0x34, 0x40, 0x00 }, { 0x2c, 0x3c, 0x40, 0x00 },
		{ 0x2c, 0x40, 0x40, 0x00 }, { 0x2c, 0x40, 0x3c, 0x00 }, { 0x2c, 0x40, 0x34, 0x00 }, { 0x2c, 0x40, 0x30, 0x00 },
		{ 0x2c, 0x40, 0x2c, 0x00 }, { 0x30, 0x40, 0x2c, 0x00 }, { 0x34, 0x40, 0x2c, 0x00 }, { 0x3c, 0x40, 0x2c, 0x00 },
		{ 0x40, 0x40, 0x2c, 0x00 }, { 0x40, 0x3c, 0x2c, 0x00 }, { 0x40, 0x34, 0x2c, 0x00 }, { 0x40, 0x30, 0x2c, 0x00 },
		{ 0xa8, 0xa8, 0xa8, 0x00 }, { 0x54, 0xfc, 0xfc, 0x00 }, { 0xfc, 0x54, 0xfc, 0x00 }, { 0xfc, 0xfc, 0x54, 0x00 },
		{ 0xfc, 0x54, 0x54, 0x00 }, { 0x54, 0xfc, 0x54, 0x00 }, { 0x54, 0x54, 0xfc, 0x00 }, { 0xfc, 0xfc, 0xfc, 0x00 }
	};

using namespace std;
#define USE_MFC
class StringCov
{
public:
	StringCov();
	virtual~ StringCov();
	char* WcharToChar(const wchar_t* wp);
	char* StringToChar(const string& s);
	char* WstringToChar(const wstring& ws);
	wchar_t* CharToWchar(const char* c);
	wchar_t* WstringToWchar(const wstring& ws);
	wchar_t* StringToWchar(const string& s);
	wstring StringToWstring(const string& s);
	string WstringToString(const wstring& ws);
#ifdef USE_MFC
	string CStringToString( CString& cs);
	wstring CStringToWstring( CString& cs);
	CString StringToCString(const string& s);
	CString WstringToCString(const wstring& ws);
#endif
	void Release();
private:
	char* m_char;
	wchar_t* m_wchar;
};
LPBITMAPINFO CtreateMapInfo(Mat workImg, int flag);

//int ParseCmdString(string s,); // 解析命令字符串




}
#endif;  //_Utility_DXQ_