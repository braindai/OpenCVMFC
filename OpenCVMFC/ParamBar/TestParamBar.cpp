// E:\DXQ\Documents\Visual Studio 2013\Projects\OpenCVMFC\OpenCVMFC\ParamBar\TestParamBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\OpenCVMFC.h"
#include "TestParamBar.h"


// CTestParamBar �Ի���

IMPLEMENT_DYNAMIC(CTestParamBar, CParamBarBase)

CTestParamBar::CTestParamBar(CWnd* pParent /*=NULL*/)
: CParamBarBase(CTestParamBar::IDD, pParent)
{

}

CTestParamBar::~CTestParamBar()
{

}

void CTestParamBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestParamBar, CParamBarBase)
END_MESSAGE_MAP()

BOOL CTestParamBar::CreateExt(CWnd *pParentWnd/* = NULL*/)
{
	if (!CParamBarBase::Create(CTestParamBar::IDD, pParentWnd))
		return FALSE;
	//	ResetParam();
	return TRUE;
}
// CTestParamBar ��Ϣ�������
BOOL CTestParamBar::RunImgProcess(Mat& workImg, const Mat& backImg)
{
	return TRUE;
}