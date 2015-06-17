
// OpenCVMFCView.cpp : COpenCVMFCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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
	ON_COMMAND(ID_VIEW_ZOOMIN, &COpenCVMFCView::OnViewZoomIn)
	ON_COMMAND(ID_VIEW_ZOOMOUT, &COpenCVMFCView::OnViewZoomOut)
ON_WM_MOUSEWHEEL()
ON_COMMAND(ID_IMAGE_INVERT, &COpenCVMFCView::OnImageInvert)
ON_COMMAND(ID_FLIP_H, &COpenCVMFCView::OnFlipH)
ON_COMMAND(ID_FLIP_V, &COpenCVMFCView::OnFlipV)
ON_COMMAND(ID_FLIP, &COpenCVMFCView::OnFlip)
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// COpenCVMFCView ����/����

COpenCVMFCView::COpenCVMFCView()
{
	// TODO:  �ڴ˴���ӹ������
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// COpenCVMFCView ����

void COpenCVMFCView::OnDraw(CDC* pDC)
{
	COpenCVMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

	if (!bImgLoaded)    {               //  �д�������ͼ��  
		if (!pDoc->m_Img.empty()) {           //  ��δ��ʾ  
			m_workImg = pDoc->m_Img.clone();         //  ���Ƶ�����λͼ 
			m_dibFlag = 1;
//			m_ImageType = m_workImg.type;
//			m_SaveFlag = m_ImageType;
//			pDoc->m_Display = 1;
			bImgLoaded = TRUE;
		}
	}

	if (m_dibFlag) {                        //  DIB �ṹ�ı�  
		if (m_lpBmi)
			free(m_lpBmi);
		m_lpBmi = CtreateMapInfo(m_workImg,m_dibFlag);
		m_dibFlag = 0;

		CSize  sizeTotal;
		sizeTotal = CSize((int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows));
		SetScrollSizes(MM_TEXT, sizeTotal);  //  ���ù�����  
	}



	//������һ�����û�м�������ͷ��صĻ���벻���ģ��������ﻹ�ǰ����ӽ���     

	//char *pBits;
	//if (m_CaptFlag == 1) pBits = m_Frame->imageData;
	//else if (workImg)  pBits = workImg->imageData;

	if (!m_workImg.empty()) {                          //  ˢ�´��ڻ���  
		StretchDIBits(pDC->m_hDC, 0, 0,(int)(m_dRatio*m_workImg.cols),(int)(m_dRatio*m_workImg.rows), 0, 0, m_workImg.cols, m_workImg.rows, m_workImg.data, m_lpBmi, DIB_RGB_COLORS, SRCCOPY);
	}
}

// COpenCVMFCView ��ӡ


void COpenCVMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenCVMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COpenCVMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COpenCVMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
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


// COpenCVMFCView ���

#ifdef _DEBUG
void COpenCVMFCView::AssertValid() const
{
	CView::AssertValid();
}

void COpenCVMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenCVMFCDoc* COpenCVMFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenCVMFCDoc)));
	return (COpenCVMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenCVMFCView ��Ϣ�������


void COpenCVMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
}


void COpenCVMFCView::OnImgApply()
{
	// TODO:  �ڴ���������������
	COpenCVMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_Img = m_workImg.clone();
	pDoc->SetModifiedFlag();
}

void COpenCVMFCView::OnImgRefresh()
{
	// TODO:  �ڴ���������������
	bImgLoaded = FALSE;
	Invalidate();
}

void COpenCVMFCView::OnMenuTest()
{
	if (m_workImg.empty())
		return;
	CV_Assert(m_workImg.depth() != sizeof(uchar));
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
	cv::Mat I = m_workImg.clone();
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
	
	// ����ʲô ...
	t = 1000*((double)getTickCount() - t) / getTickFrequency();
		cs.Format(_T("%.3lf"), t);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarTime,cs);
	m_workImg = J;
	Invalidate();
}

void COpenCVMFCView::OnColorToGray()
{
	// TODO:  �ڴ���������������
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
	// TODO:  �ڴ���������������
	if (m_workImg.empty())
		return;
	m_dRatio = 1.0;
	CSize  sizeTotal;
	sizeTotal = CSize((int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows));
	SetScrollSizes(MM_TEXT, sizeTotal);  //  ���ù�����  
	Invalidate();
}

void COpenCVMFCView::OnViewZoomIn()
{
	// TODO:  �ڴ���������������
	if (m_dRatio < 0.125)
		return;
	m_dRatio /= 2;	
	CSize  sizeTotal;
	sizeTotal = CSize((int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows));
	SetScrollSizes(MM_TEXT, sizeTotal);  //  ���ù�����  
	Invalidate();
}

void COpenCVMFCView::OnViewZoomOut()
{
	// TODO:  �ڴ���������������
	if (m_dRatio > 8.0)
		return;
	m_dRatio *= 2;
	CSize  sizeTotal;
	sizeTotal = CSize((int)(m_dRatio*m_workImg.cols), (int)(m_dRatio*m_workImg.rows));
	SetScrollSizes(MM_TEXT, sizeTotal);  //  ���ù�����  
	Invalidate();
}


BOOL COpenCVMFCView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ���������������
	if (m_workImg.empty())
		return;
	bitwise_not(m_workImg, m_workImg);
	Invalidate();
}


void COpenCVMFCView::OnFlipH()
{
	// TODO:  �ڴ���������������
	if (m_workImg.empty())
		return;
	flip(m_workImg,m_workImg,1);
	Invalidate();
}


void COpenCVMFCView::OnFlipV()
{
	// TODO:  �ڴ���������������
	if (m_workImg.empty())
		return;
	flip(m_workImg, m_workImg,0);
	Invalidate();
}


void COpenCVMFCView::OnFlip()
{
	// TODO:  �ڴ���������������
	if (m_workImg.empty())
		return;
	flip(m_workImg, m_workImg, -1);
	Invalidate();	
}


void COpenCVMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ


	CString cs;
	CPoint pt = GetScrollPosition();
	cs.Format(_T("%d,%d"), (int)((point.x + pt.x)/m_dRatio),(int)((point.y + pt.y)/m_dRatio));

	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneText(nStatusBarPos, cs);
	CScrollView::OnMouseMove(nFlags, point);
}
