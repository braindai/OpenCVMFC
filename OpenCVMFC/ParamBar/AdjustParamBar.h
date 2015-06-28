#pragma once

#include "ParamBarBase.h"
#include "afxcmn.h"
// CAdjustParamBar �Ի���

class CAdjustParamBar : public CParamBarBase
{
	DECLARE_DYNAMIC(CAdjustParamBar)

public:
	CAdjustParamBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdjustParamBar();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAMBAR_ADJUST };
private:
	ULONG _lastTime;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL CreateExt(CWnd *pParentWnd = NULL);
	virtual BOOL RunImgProcess(Mat& workImg, const Mat& backImg);
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedMfcbuttonApply();
	CSliderCtrl m_slidContrast;
	CSliderCtrl m_slidBrightness;
	virtual BOOL OnInitDialog();
	virtual void ResetParam();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	virtual void OnOK();
};
