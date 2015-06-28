
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
	ON_COMMAND(ID_MENU_TEST, &COpenCVMFCView::OnMenuTest)
	ON_COMMAND(ID_COLOR_TO_GRAY, &COpenCVMFCView::OnColorToGray)
	ON_COMMAND(ID_VIEW_ORIGIN, &COpenCVMFCView::OnViewOrigin)
	ON_COMMAND(ID_VIEW_ZOOMIN, &COpenCVMFCView::OnViewZoomIn)
	ON_COMMAND(ID_VIEW_ZOOMOUT, &COpenCVMFCView::OnViewZoomOut)
ON_WM_MOUSEWHEEL()
ON_COMMAND(ID_IMAGE_INVERT, &COpenCVMFCView::OnImageInvert)
ON_COMMAND(ID_FLIP_H, &COpenCVMFCView::OnFlipH)
ON_COMMAND(ID_FLIP_V, &COpenCVMFCView::OnFlipV)
ON_COMMAND(ID_FLIP, &COpenCVMFCView::OnFlip)
ON_WM_MOUSEMOVE()
ON_COMMAND(ID_IMAGE_ADJUST, &COpenCVMFCView::OnImageAdjust)
ON_MESSAGE(WM_USER_IMGPROC_CMD, &COpenCVMFCView::OnUserCmd)
ON_MESSAGE(WM_USER_IMGVIEW_UPDATE, &COpenCVMFCView::OnUserImgviewUpdate)
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
			m_backImg = pDoc->m_Img.clone();         //  复制到工作位图 
			m_workImg = m_backImg.clone();
			m_dibFlag = 1;
//			m_ImageType = m_backImg.type;
//			m_SaveFlag = m_ImageType;
//			pDoc->m_Display = 1;
			bImgLoaded = TRUE;
		}
	}

	if (m_dibFlag) {                        //  DIB 结构改变  
		if (m_lpBmi)
			free(m_lpBmi);
		m_lpBmi = CtreateMapInfo(m_backImg,m_dibFlag);
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
		StretchDIBits(pDC->m_hDC, 0, 0, (int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows), 0, 0, m_workImg.cols, m_workImg.rows, m_workImg.data, m_lpBmi, DIB_RGB_COLORS, SRCCOPY);
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
	m_backImg = m_workImg.clone();
	pDoc->m_Img = m_backImg.clone();
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
	SwitchParamBar(ID_MENU_TEST);
	if (m_backImg.empty())
		return;
	CV_Assert(m_backImg.depth() != sizeof(uchar));
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] =(i/10)*10;

	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for (int i = 0; i < 256; i++)
		p[i] = table[i];

	Mat J;
	int times=1;
	CString cs;
	cs = _T("start test......");
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarSeparator, cs);
	cv::Mat I = m_backImg.clone();
	double t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
	{
		//
		//int channels = I.channels();
		//int nRows = I.rows * channels;
		//int nCols = I.cols;

		//if (I.isContinuous())
		//{
		//	nCols *= nRows;
		//	nRows = 1;
		//}
		//int k, j;
		//uchar* p;
		//for (k = 0; k < nRows; ++k)
		//{
		//	p = I.ptr<uchar>(k);
		//	for (j = 0; j < nCols; ++j)
		//	{
		//		p[j] = table[p[j]];
		//		p[j] = (p[j] / 10) * 10;
		//	}
		//}	

		LUT(I, lookUpTable, J);

	}
	
	// 做点什么 ...
	t = 1000*((double)getTickCount() - t) / getTickFrequency();
		cs.Format(_T("%.3lf"), t);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarTime,cs);
	m_backImg = J;
	m_workImg = m_backImg.clone();
	Invalidate();
}

void COpenCVMFCView::OnColorToGray()
{
	// TODO:  在此添加命令处理程序代码
	if (m_workImg.empty())
		return;
	m_backImg = m_workImg.clone();
	if (m_workImg.channels() != 3)
	{
		((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarSeparator, _T("非RGB图像！"));
		return;
	}
	Mat img8u(m_workImg.rows, m_workImg.cols, CV_8UC1);
	cvtColor(m_workImg, img8u, CV_RGB2GRAY);
	m_workImg = img8u;
	m_dibFlag = 1;
//	m_workImg = m_backImg.clone();
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

void COpenCVMFCView::OnViewZoomIn()
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

void COpenCVMFCView::OnViewZoomOut()
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

BOOL COpenCVMFCView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nFlags == MK_CONTROL)
	{
	
		if (zDelta < 0)
		{
			OnViewZoomIn();
		}
		else if (zDelta > 0)
		{
			OnViewZoomOut();
		}

	}
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void COpenCVMFCView::OnImageInvert()
{
	// TODO:  在此添加命令处理程序代码
	SwitchParamBar();
	if (m_backImg.empty())
		return;
	m_backImg = m_workImg.clone();
	bitwise_not(m_workImg, m_workImg);
//	m_workImg = m_backImg.clone();
	Invalidate();
}

void COpenCVMFCView::OnFlipH()
{
	// TODO:  在此添加命令处理程序代码
	SwitchParamBar();
	if (m_workImg.empty())
		return;
	m_backImg = m_workImg.clone();
	flip(m_workImg, m_workImg, 1);
	Invalidate();
}

void COpenCVMFCView::OnFlipV()
{
	// TODO:  在此添加命令处理程序代码
	SwitchParamBar();
	if (m_workImg.empty())
		return;
	m_backImg = m_workImg.clone();
	flip(m_workImg, m_workImg, 0);
	Invalidate();
}

void COpenCVMFCView::OnFlip()
{
	// TODO:  在此添加命令处理程序代码
	SwitchParamBar();
	if (m_workImg.empty())
		return;
	m_backImg = m_workImg.clone();
	flip(m_workImg, m_workImg, -1);
	Invalidate();	
}

void COpenCVMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值


	CString cs;
	CPoint pt = GetScrollPosition();
	int col = (int)((point.x + pt.x) / m_dRatio);
	int row = (int)((point.y + pt.y) / m_dRatio);
	if (row < 0)
		row = 0;
	else if (row >= m_workImg.rows)
		row = m_workImg.rows - 1;
	if (col < 0)
		col = 0;
	else if (col >= m_workImg.cols)
		col = m_workImg.cols - 1;
	
	cs.Format(_T("%d,%d"), row, col);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarPos, cs);

	if (m_workImg.depth() != CV_8U)
		return;
	const int channels = m_workImg.channels();
	try{
		switch (channels)
		{
		case 1:
			cs.Format(_T("%3d,000,000"), m_workImg.at<uchar>(row, col));
			((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarValue, cs);
			break;
		case 3:
			cs.Format(_T("%3d,%3d,%3d"), m_workImg.at<Vec3b>(row, col)[0],
				m_workImg.at<Vec3b>(row, col)[1],
				m_workImg.at<Vec3b>(row, col)[2]);
			((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarValue, cs);
			break;
		}
	}
	catch (cv::Exception &/*e*/)
	{
		cs = _T("error");
		((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarValue, cs);
	}
}

void COpenCVMFCView::OnImageAdjust()
{
	// TODO:  在此添加命令处理程序代码
	SwitchParamBar(ID_IMAGE_ADJUST);
	m_backImg = m_workImg.clone();
}

void COpenCVMFCView::SwitchParamBar(int nCmdID /*=0*/)
{
	((CMainFrame*)AfxGetMainWnd())->m_wndParamBar.SwitchBar(nCmdID);
}
afx_msg LRESULT COpenCVMFCView::OnUserCmd(WPARAM wParam, LPARAM lParam)
{
	CParamBarBase* pbar = (CParamBarBase*)lParam;
	if (pbar->RunImgProcess(m_workImg, m_backImg))
		if (wParam == TRUE)
			Invalidate();
	return 0;
}


afx_msg LRESULT COpenCVMFCView::OnUserImgviewUpdate(WPARAM wParam, LPARAM/* lParam*/)
{
	BOOL bDir = (BOOL)wParam;
	if (bDir)
		m_backImg = m_workImg.clone();
	else
	{
		m_workImg = m_backImg.clone();
		Invalidate();
	}	
	return 0;
}
