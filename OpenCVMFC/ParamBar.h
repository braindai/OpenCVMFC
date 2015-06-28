#pragma once

#include "ParamBar\ParamBarBase.h"

// CParamBar

class CParamBar : public CDockablePane
{
	DECLARE_DYNAMIC(CParamBar)

public:
	CParamBar();
	virtual ~CParamBar();

protected:
	DECLARE_MESSAGE_MAP()
	int m_nCurBarIndex;
	CArray<CParamBarBase*, CParamBarBase*> m_pBars;
	CDialogEx*	pDlg;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 创建参数栏
	BOOL CreateBars();
	void SwitchBar(int nCmdID);
};


