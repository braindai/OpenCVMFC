
// OpenCVMFCDoc.cpp : COpenCVMFCDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "OpenCVMFC.h"
#endif

#include "OpenCVMFCDoc.h"
#include <propkey.h>
#include "../Utility/Utility.h"
using namespace Utility_DXQ;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COpenCVMFCDoc

IMPLEMENT_DYNCREATE(COpenCVMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenCVMFCDoc, CDocument)
END_MESSAGE_MAP()


// COpenCVMFCDoc ����/����

COpenCVMFCDoc::COpenCVMFCDoc()
{
	// TODO:  �ڴ����һ���Թ������	
}

COpenCVMFCDoc::~COpenCVMFCDoc()
{

}

BOOL COpenCVMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	m_Img.create(480, 640, CV_8UC(1));
	return TRUE;
}




// COpenCVMFCDoc ���л�

void COpenCVMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void COpenCVMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void COpenCVMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void COpenCVMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COpenCVMFCDoc ���

#ifdef _DEBUG
void COpenCVMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenCVMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COpenCVMFCDoc ����


BOOL COpenCVMFCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	//if (!CDocument::OnOpenDocument(lpszPathName))
	//	return FALSE;

	// TODO:  �ڴ������ר�õĴ�������

#ifdef _DEBUG
	if (IsModified())
		TRACE(traceAppMsg, 0, "Warning: OnOpenDocument replaces an unsaved document.\n");
#endif

	ENSURE(lpszPathName);
	DeleteContents();
	StringCov sCov;
	CString cs(lpszPathName);
	m_Img = imread(sCov.CStringToString(cs));
	if (m_Img.empty())
	{
		AfxMessageBox(_T("open failed!"));
		return FALSE;
	}
	return TRUE;
}


BOOL COpenCVMFCDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO:  �ڴ����ר�ô����/����û���
	// TODO:  �ڴ������ר�õĴ�������
	ENSURE(lpszPathName);
	StringCov sCov;
	CString cs(lpszPathName);
	bool bSaveSuccessFlag;
	try 
	{
		bSaveSuccessFlag = imwrite(sCov.CStringToString(cs), m_Img);
	}
	catch (CException &e)
	{
//		TRACE(e.GetErrorMessage());
		bSaveSuccessFlag = false;
	}
	if (bSaveSuccessFlag)
	{
		SetModifiedFlag(FALSE);     // back to unmodified
		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("save failed!"));
		return FALSE;
	}	
//	return CDocument::OnSaveDocument(lpszPathName);
}
