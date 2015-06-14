
// OpenCVMFCDoc.cpp : COpenCVMFCDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// COpenCVMFCDoc 构造/析构

COpenCVMFCDoc::COpenCVMFCDoc()
{
	// TODO:  在此添加一次性构造代码	
}

COpenCVMFCDoc::~COpenCVMFCDoc()
{

}

BOOL COpenCVMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	m_Img.create(480, 640, CV_8UC(1));
	return TRUE;
}




// COpenCVMFCDoc 序列化

void COpenCVMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void COpenCVMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void COpenCVMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// COpenCVMFCDoc 诊断

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


// COpenCVMFCDoc 命令


BOOL COpenCVMFCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	//if (!CDocument::OnOpenDocument(lpszPathName))
	//	return FALSE;

	// TODO:  在此添加您专用的创建代码

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
	// TODO:  在此添加专用代码和/或调用基类
	// TODO:  在此添加您专用的创建代码
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
