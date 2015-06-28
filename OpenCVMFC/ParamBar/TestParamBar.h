#pragma once
#include "ParamBarBase.h"

// CTestParamBar 对话框

class CTestParamBar : public CParamBarBase
{
	DECLARE_DYNAMIC(CTestParamBar)

public:
	CTestParamBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestParamBar();
	BOOL CreateExt(CWnd *pParentWnd = NULL);
// 对话框数据
	enum { IDD = IDD_DIALOG_PARAMBAR_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL RunImgProcess(Mat& workImg, const Mat& backImg);
	DECLARE_MESSAGE_MAP()
};
