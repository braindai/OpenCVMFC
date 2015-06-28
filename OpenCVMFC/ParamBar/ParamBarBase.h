#pragma once


// CParamBarBase ¶Ô»°¿ò

class CParamBarBase : public CDialogEx
{
	DECLARE_DYNAMIC(CParamBarBase)

public:
	CParamBarBase(UINT nIDTemplate, CWnd *pParent = NULL);
	CParamBarBase(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void ResetParam();
	virtual BOOL CreateExt(CWnd *pParentWnd = NULL) = 0;
	virtual BOOL RunImgProcess(Mat& workImg, const Mat& backImg) = 0;
	int m_nCmdID;
	virtual void OnOK(){ return; };
	virtual void OnCancel(){ return; };	
	void SendMsgToView(int msgID, CParamBarBase* pOwner, BOOL bRedraw = FALSE);
};
