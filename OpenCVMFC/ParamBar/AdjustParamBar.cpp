// E:\DXQ\Documents\Visual Studio 2013\Projects\OpenCVMFC\OpenCVMFC\ParamBar\AdjustParamBar.cpp : 实现文件
//

#include "stdafx.h"
#include "..\OpenCVMFC.h"
#include "AdjustParamBar.h"
#include "afxdialogex.h"


// CAdjustParamBar 对话框

IMPLEMENT_DYNAMIC(CAdjustParamBar, CParamBarBase)

CAdjustParamBar::CAdjustParamBar(CWnd* pParent /*=NULL*/)
: CParamBarBase(CAdjustParamBar::IDD, pParent)
{
	_lastTime = GetTickCount();
}

CAdjustParamBar::~CAdjustParamBar()
{

}

void CAdjustParamBar::DoDataExchange(CDataExchange* pDX)
{
	CParamBarBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_slidContrast);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_slidBrightness);
}


BEGIN_MESSAGE_MAP(CAdjustParamBar, CParamBarBase)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CAdjustParamBar::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CAdjustParamBar::OnBnClickedMfcbuttonApply)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CAdjustParamBar 消息处理程序
BOOL CAdjustParamBar::CreateExt(CWnd *pParentWnd/* = NULL*/)
{
	if (!CParamBarBase::Create(CAdjustParamBar::IDD, pParentWnd))
		return FALSE;
	return TRUE;
}
BOOL CAdjustParamBar::RunImgProcess(Mat& workImg, const Mat& backImg)
{
	CString cs;
	double alpha, beta;
	GetDlgItemText(IDC_EDIT_CONTRAST, cs);
	alpha = _ttof(cs);
	GetDlgItemText(IDC_EDIT_BRIGHTNESS, cs);
	beta = _ttof(cs);
	backImg.convertTo(workImg, -1, alpha, beta);
	return TRUE;
}
void CAdjustParamBar::OnBnClickedButtonReset()
{
	// TODO:  在此添加控件通知处理程序代码
	ResetParam();
	SendMsgToView(WM_USER_IMGPROC_CMD, this, TRUE);
}

void CAdjustParamBar::OnBnClickedMfcbuttonApply()
{
	// TODO:  在此添加控件通知处理程序代码
}
BOOL CAdjustParamBar::OnInitDialog()
{
	CParamBarBase::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_slidBrightness.SetRange(-255,255,TRUE);
	m_slidContrast.SetRange(-50, 50, TRUE);

	ResetParam();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
void CAdjustParamBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString cs;
	
	double tempa = (double)m_slidContrast.GetPos();
	tempa = tempa >= 0 ? 1 + tempa / 50 * 4 : 1 + tempa / 50 * 4 / 5;
	cs.Format(_T("%.2lf"), tempa);
	SetDlgItemText(IDC_EDIT_CONTRAST, cs);

	double tempb = (double)m_slidBrightness.GetPos();
	cs.Format(_T("%.0lf"),tempb);
	SetDlgItemText(IDC_EDIT_BRIGHTNESS, cs);
	
//	ULONG passTime = GetTickCount() - _lastTime;
//	if (passTime > 200)
//	{
	SendMsgToView(WM_USER_IMGPROC_CMD, this, TRUE);
//		_lastTime = GetTickCount();
//	}
	
//	CParamBarBase::OnHScroll(nSBCode, nPos, pScrollBar);
}
void CAdjustParamBar::ResetParam()
{
	m_slidContrast.SetPos(0);
	m_slidBrightness.SetPos(0);
	UpdateData(FALSE);
	SetDlgItemText(IDC_EDIT_CONTRAST,_T("1.0"));
	SetDlgItemText(IDC_EDIT_BRIGHTNESS,_T("0"));
}

void CAdjustParamBar::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CString cs;
	double alpha, beta;
	GetDlgItemText(IDC_EDIT_CONTRAST, cs);
	alpha = _ttof(cs);
	alpha = alpha >= 1 ? (alpha - 1) * 50 / 4 : (alpha - 1) * 50 * 5 / 4;
	m_slidContrast.SetPos((int)alpha);

	GetDlgItemText(IDC_EDIT_BRIGHTNESS, cs);
	beta = _ttof(cs);
	m_slidBrightness.SetPos((int)beta);	

	SendMsgToView(WM_USER_IMGPROC_CMD, this, TRUE);
//	CParamBarBase::OnOK();
}
