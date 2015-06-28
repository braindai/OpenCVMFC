#pragma once
#include "ParamBarBase.h"

// CDummyParamBar 对话框

class CDummyParamBar : public CParamBarBase
{
	DECLARE_DYNAMIC(CDummyParamBar)

public:
	CDummyParamBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDummyParamBar();

// 对话框数据
	enum { IDD = IDD_DIALOG_PARAMBAR_DUMMY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL CreateExt(CWnd *pParentWnd = NULL);
	virtual BOOL RunImgProcess(Mat& workImg, const Mat& backImg);
};
