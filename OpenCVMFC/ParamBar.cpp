// ParamPane.cpp : 实现文件
//

#include "stdafx.h"
#include "OpenCVMFC.h"
#include "ParamBar.h"
#include "ParamBar\AdjustParamBar.h"
#include "ParamBar\TestParamBar.h"
#include "ParamBar\DummyParamBar.h"


// CParamPane

IMPLEMENT_DYNAMIC(CParamBar, CDockablePane)

CParamBar::CParamBar()
{
	
	pDlg = NULL;
}

CParamBar::~CParamBar()
{
	for (int i = 0; i < m_pBars.GetCount(); i++)
		delete m_pBars[i];
}


BEGIN_MESSAGE_MAP(CParamBar, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CParamPane 消息处理程序

int CParamBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!CreateBars())
		return -1;
	m_nCurBarIndex = 0;
	m_pBars[m_nCurBarIndex]->ShowWindow(SW_SHOW);
	return 0;
}


void CParamBar::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (m_pBars[m_nCurBarIndex]->GetSafeHwnd())
	{
	       CRect rct;
	       GetClientRect(rct);
		   m_pBars[m_nCurBarIndex]->MoveWindow(rct);
	 }
}



// 创建参数栏
BOOL CParamBar::CreateBars()
{
	CDummyParamBar* pDummyDlg = new CDummyParamBar();
	if (!pDummyDlg->CreateExt(this))
	{
		TRACE(_T("Create Dummy ParamBar Failed"));
		return FALSE;
	}
	pDummyDlg->m_nCmdID = 0;
	m_pBars.Add((CParamBarBase*)pDummyDlg);

	CAdjustParamBar* pAdjustDlg = new CAdjustParamBar();
	if (!pAdjustDlg->CreateExt(this))
	{
		TRACE(_T("Create Adjust ParamBar Failed"));
		return FALSE;
	}
	pAdjustDlg->m_nCmdID = ID_IMAGE_ADJUST;
	m_pBars.Add((CParamBarBase*)pAdjustDlg);

	CTestParamBar* pTestDlg = new CTestParamBar();
	if (!pTestDlg->CreateExt( this))
	{
		TRACE(_T("Create Test ParamBar Failed"));
		return FALSE;
	}
	pTestDlg->m_nCmdID = ID_MENU_TEST;
	m_pBars.Add((CParamBarBase*)pTestDlg);
	return TRUE;
}


void CParamBar::SwitchBar(int nCmdID)
{
	if (m_pBars[m_nCurBarIndex]->m_nCmdID == nCmdID)
		return;
	for (int i = 0; i < m_pBars.GetCount(); i++)
	{
		if (m_pBars[i]->m_nCmdID == nCmdID)
		{
			m_pBars[m_nCurBarIndex]->ShowWindow(SW_HIDE);
			m_nCurBarIndex = i;
			m_pBars[m_nCurBarIndex]->ShowWindow(SW_SHOW);
			if (m_pBars[m_nCurBarIndex]->GetSafeHwnd())
			{
				CRect rct;
				GetClientRect(rct);
				m_pBars[m_nCurBarIndex]->MoveWindow(rct);
			}
			break;
		}
	}
}
