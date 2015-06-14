
// OpenCVMFCView.h : COpenCVMFCView ��Ľӿ�
//

#pragma once


class COpenCVMFCView : public CScrollView
{
protected: // �������л�����
	COpenCVMFCView();
	DECLARE_DYNCREATE(COpenCVMFCView)

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
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();

};

#ifndef _DEBUG  // OpenCVMFCView.cpp �еĵ��԰汾
inline COpenCVMFCDoc* COpenCVMFCView::GetDocument() const
   { return reinterpret_cast<COpenCVMFCDoc*>(m_pDocument); }
#endif

