#pragma once
#include "ParamBarBase.h"

// CDummyParamBar �Ի���

class CDummyParamBar : public CParamBarBase
{
	DECLARE_DYNAMIC(CDummyParamBar)

public:
	CDummyParamBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDummyParamBar();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAMBAR_DUMMY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL CreateExt(CWnd *pParentWnd = NULL);
	virtual BOOL RunImgProcess(Mat& workImg, const Mat& backImg);
};
