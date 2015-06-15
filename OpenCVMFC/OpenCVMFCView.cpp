
// OpenCVMFCView.cpp : COpenCVMFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenCVMFC.h"
#endif
#include "MainFrm.h"
#include "OpenCVMFCDoc.h"
#include "OpenCVMFCView.h"
#include "../Utility/Utility.h"
using namespace Utility_DXQ;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenCVMFCView

IMPLEMENT_DYNCREATE(COpenCVMFCView, CScrollView)

BEGIN_MESSAGE_MAP(COpenCVMFCView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenCVMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_IMG_APPLY, &COpenCVMFCView::OnImgApply)
	ON_COMMAND(ID_IMG_REFRESH, &COpenCVMFCView::OnImgRefresh)
	ON_COMMAND(ID_Menu_TEST, &COpenCVMFCView::OnMenuTest)
	ON_COMMAND(ID_COLOR_TO_GRAY, &COpenCVMFCView::OnColorToGray)
	ON_COMMAND(ID_VIEW_ORIGIN, &COpenCVMFCView::OnViewOrigin)
	ON_COMMAND(ID_VIEW_ZOOMIN, &COpenCVMFCView::OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, &COpenCVMFCView::OnViewZoomout)
//	ON_WM_MOUSEHWHEEL()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// COpenCVMFCView 构造/析构

COpenCVMFCView::COpenCVMFCView()
{
	// TODO:  在此处添加构造代码
	bImgLoaded = FALSE;
	m_lpBmi = NULL;
	m_dibFlag = 0;
	m_dRatio = 1.0;

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 200;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
}

COpenCVMFCView::~COpenCVMFCView()
{
	if (m_lpBmi)
		delete m_lpBmi;
}

BOOL COpenCVMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COpenCVMFCView 绘制

void COpenCVMFCView::OnDraw(CDC* pDC)
{
	COpenCVMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码

	if (!bImgLoaded)    {               //  有磁盘输入图像  
		if (!pDoc->m_Img.empty()) {           //  尚未显示  
			m_workImg = pDoc->m_Img.clone();         //  复制到工作位图 
			m_dibFlag = 1;
//			m_ImageType = m_workImg.type;
//			m_SaveFlag = m_ImageType;
//			pDoc->m_Display = 1;
			bImgLoaded = TRUE;
		}
	}

	if (m_dibFlag) {                        //  DIB 结构改变  
		if (m_lpBmi)
			free(m_lpBmi);
		m_lpBmi = CtreateMapInfo(m_workImg,m_dibFlag);
		m_dibFlag = 0;

		CSize  sizeTotal;
		sizeTotal = CSize((int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows));
		SetScrollSizes(MM_TEXT, sizeTotal);  //  设置滚动条  
	}



	//下面这一段如果没有加入摄像头相关的会编译不过的，所以这里还是把它加进来     

	//char *pBits;
	//if (m_CaptFlag == 1) pBits = m_Frame->imageData;
	//else if (workImg)  pBits = workImg->imageData;

	if (!m_workImg.empty()) {                          //  刷新窗口画面  
		StretchDIBits(pDC->m_hDC, 0, 0,(int)(m_dRatio*m_workImg.cols),(int)(m_dRatio*m_workImg.rows), 0, 0, m_workImg.cols, m_workImg.rows, m_workImg.data, m_lpBmi, DIB_RGB_COLORS, SRCCOPY);
	}
}

// COpenCVMFCView 打印


void COpenCVMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenCVMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpenCVMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void COpenCVMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void COpenCVMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenCVMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenCVMFCView 诊断

#ifdef _DEBUG
void COpenCVMFCView::AssertValid() const
{
	CView::AssertValid();
}

void COpenCVMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenCVMFCDoc* COpenCVMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenCVMFCDoc)));
	return (COpenCVMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenCVMFCView 消息处理程序


void COpenCVMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
}



void COpenCVMFCView::OnImgApply()
{
	// TODO:  在此添加命令处理程序代码
	COpenCVMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Img = m_workImg.clone();
	pDoc->SetModifiedFlag();
}


void COpenCVMFCView::OnImgRefresh()
{
	// TODO:  在此添加命令处理程序代码
	bImgLoaded = FALSE;
	Invalidate();
}


void COpenCVMFCView::OnMenuTest()
{
	// TODO:  在此添加命令处理程序代码
	//Invalidate();
	double t = (double)getTickCount();
	// 做点什么 ...
	Sleep(100);
	t = 1000*((double)getTickCount() - t) / getTickFrequency();
	CString cs;
	cs.Format(_T("%.3lf"), t);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarTime,cs);
	//test
}


void COpenCVMFCView::OnColorToGray()
{
	// TODO:  在此添加命令处理程序代码
	if (m_workImg.empty())
		return;
	Mat img8u(m_workImg.rows,m_workImg.cols, CV_8UC1);
	cvtColor(m_workImg, img8u, CV_RGB2GRAY);
	m_workImg = img8u;
	m_dibFlag = 1;
	Invalidate();
}


void COpenCVMFCView::OnViewOrigin()
{
	// TODO:  在此添加命令处理程序代码
	if (m_workImg.empty())
		return;
	m_dRatio = 1.0;
	CSize  sizeTotal;
	sizeTotal = CSize((int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows));
	SetScrollSizes(MM_TEXT, sizeTotal);  //  设置滚动条  
	Invalidate();
}


void COpenCVMFCView::OnViewZoomin()
{
	// TODO:  在此添加命令处理程序代码
	if (m_dRatio < 0.125)
		return;
	m_dRatio /= 2;	
	CSize  sizeTotal;
	sizeTotal = CSize((int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows));
	SetScrollSizes(MM_TEXT, sizeTotal);  //  设置滚动条  
	Invalidate();
}


void COpenCVMFCView::OnViewZoomout()
{
	// TODO:  在此添加命令处理程序代码
	if (m_dRatio > 8.0)
		return;
	m_dRatio *= 2;
	CSize  sizeTotal;
	sizeTotal = CSize((int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows));
	SetScrollSizes(MM_TEXT, sizeTotal);  //  设置滚动条  
	Invalidate();
}


//void COpenCVMFCView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// 此功能要求 Windows Vista 或更高版本。
//	// _WIN32_WINNT 符号必须 >= 0x0600。
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//
//	CScrollView::OnMouseHWheel(nFlags, zDelta, pt);
//}


BOOL COpenCVMFCView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nFlags == MK_CONTROL)
		if (zDelta < 0)
			OnViewZoomin();
		else if (zDelta > 0)
			OnViewZoomout();
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}
