#pragma once
#include "ParamBarBase.h"

// CTestParamBar �Ի���

class CTestParamBar : public CParamBarBase
{
	DECLARE_DYNAMIC(CTestParamBar)

public:
	CTestParamBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestParamBar();
	BOOL CreateExt(CWnd *pParentWnd = NULL);
// �Ի�������
	enum { IDD = IDD_DIALOG_PARAMBAR_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL RunImgProcess(Mat& workImg, const Mat& backImg);
	DECLARE_MESSAGE_MAP()
};
