
// OpenCVMFCView.h : COpenCVMFCView 类的接口
//

#pragma once


class COpenCVMFCView : public CScrollView
{
protected: // 仅从序列化创建
	COpenCVMFCView();
	DECLARE_DYNCREATE(COpenCVMFCView)

	Mat  m_workImg;
	BOOL bImgLoaded;
	LPBITMAPINFO m_lpBmi;
	int m_dibFlag;
	double m_dRatio;
// 特性
public:
	COpenCVMFCDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~COpenCVMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnImgApply();
	afx_msg void OnImgRefresh();
	afx_msg void OnMenuTest();
	afx_msg void OnColorToGray();
	afx_msg void OnViewOrigin();
	afx_msg void OnViewZoomIn();
	afx_msg void OnViewZoomOut();

//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnImageInvert();
	afx_msg void OnFlipH();
	afx_msg void OnFlipV();
	afx_msg void OnFlip();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // OpenCVMFCView.cpp 中的调试版本
inline COpenCVMFCDoc* COpenCVMFCView::GetDocument() const
   { return reinterpret_cast<COpenCVMFCDoc*>(m_pDocument); }
#endif

