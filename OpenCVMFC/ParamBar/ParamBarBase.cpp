// E:\DXQ\Documents\Visual Studio 2013\Projects\OpenCVMFC\OpenCVMFC\ParamBar\ParamBarBase.cpp : 实现文件
//

#include "stdafx.h"
#include "ParamBarBase.h"
#include "afxdialogex.h"


// CParamBarBase 对话框

IMPLEMENT_DYNAMIC(CParamBarBase, CDialogEx)

CParamBarBase::CParamBarBase(UINT nIDTemplate, CWnd *pParent/* = NULL*/) :CDialogEx(nIDTemplate, pParent)
{
	m_nCmdID = 0;
}
CParamBarBase::CParamBarBase(LPCTSTR lpszTemplateName, CWnd *pParentWnd/* = NULL*/) : CDialogEx(lpszTemplateName, pParentWnd)
{
	m_nCmdID = 0;
}

BEGIN_MESSAGE_MAP(CParamBarBase, CDialogEx)
END_MESSAGE_MAP()
void CParamBarBase::ResetParam()
{

}
// CParamBarBase 消息处理程序


void CParamBarBase::SendMsgToView(int msgID, CParamBarBase* pOwner, BOOL bRedraw)
{
	((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveFrame()->GetActiveView()->SendMessage(msgID, bRedraw, (LPARAM)pOwner);
}
