#pragma once


CString GetAppPath();
int roiCreateBMPHeader(const int nWidth, const int nHeight, const int colorbits, unsigned char * pBMPHeader);
void ConvertCharToCString(char str_in[],CString&);
char* ConvertCStringToChar(CString& cstring);
char* ConvertTStringToChar(const TCHAR* tchar);