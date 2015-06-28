
// OpenCVMFCView.h : COpenCVMFCView ��Ľӿ�
//

#pragma once


class COpenCVMFCView : public CScrollView
{
protected: // �������л�����
	COpenCVMFCView();
	DECLARE_DYNCREATE(COpenCVMFCView)

	Mat  m_backImg;
	Mat  m_workImg;
	BOOL bImgLoaded;
	LPBITMAPINFO m_lpBmi;
	int m_dibFlag;
	double m_dRatio;
// ����
public:
	COpenCVMFCDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~COpenCVMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	afx_msg void OnImageAdjust();
	void SwitchParamBar(int nCmdID = 0);
protected:
	afx_msg LRESULT OnUserCmd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserImgviewUpdate(WPARAM wParam = TRUE, LPARAM lParam = 0);
};

#ifndef _DEBUG  // OpenCVMFCView.cpp �еĵ��԰汾
inline COpenCVMFCDoc* COpenCVMFCView::GetDocument() const
   { return reinterpret_cast<COpenCVMFCDoc*>(m_pDocument); }
#endif

