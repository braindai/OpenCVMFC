#ifndef _Utility_DXQ_
#define _Utility_DXQ_

#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

#define USE_MFC

//#ifdef USE_MFC
//#include <afx.h>
//#else
//
//#endif

namespace Utility_DXQ{
using namespace std;
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
}
#endif;  //_Utility_DXQ_