#pragma once
#include "NJU.h"

// InputInfo_Dlg 对话框

class InputInfo_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(InputInfo_Dlg)

public:
	InputInfo_Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InputInfo_Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit2();
	afx_msg void On32772();
	afx_msg void On32783();
	afx_msg void On32784();
};
