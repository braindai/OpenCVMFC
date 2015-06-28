// DummyParamBar.cpp : 实现文件
//

#include "stdafx.h"
#include "..\OpenCVMFC.h"
#include "DummyParamBar.h"


// CDummyParamBar 对话框

IMPLEMENT_DYNAMIC(CDummyParamBar, CParamBarBase)

CDummyParamBar::CDummyParamBar(CWnd* pParent /*=NULL*/)
: CParamBarBase(CDummyParamBar::IDD, pParent)
{

}

CDummyParamBar::~CDummyParamBar()
{
}

void CDummyParamBar::DoDataExchange(CDataExchange* pDX)
{
	CParamBarBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDummyParamBar, CParamBarBase)
END_MESSAGE_MAP()


// CDummyParamBar 消息处理程序
BOOL  CDummyParamBar::CreateExt(CWnd *pParentWnd /*= NULL*/)
{
	return CParamBarBase::Create(CDummyParamBar::IDD, pParentWnd);
}
BOOL CDummyParamBar::RunImgProcess(Mat& workImg, const Mat& backImg)
{
	return TRUE;
}