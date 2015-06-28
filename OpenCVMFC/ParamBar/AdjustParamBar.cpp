// E:\DXQ\Documents\Visual Studio 2013\Projects\OpenCVMFC\OpenCVMFC\ParamBar\AdjustParamBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\OpenCVMFC.h"
#include "AdjustParamBar.h"
#include "afxdialogex.h"


// CAdjustParamBar �Ի���

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


// CAdjustParamBar ��Ϣ�������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ResetParam();
	SendMsgToView(WM_USER_IMGPROC_CMD, this, TRUE);
}

void CAdjustParamBar::OnBnClickedMfcbuttonApply()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
BOOL CAdjustParamBar::OnInitDialog()
{
	CParamBarBase::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_slidBrightness.SetRange(-255,255,TRUE);
	m_slidContrast.SetRange(-50, 50, TRUE);

	ResetParam();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
void CAdjustParamBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ����ר�ô����/����û���
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
