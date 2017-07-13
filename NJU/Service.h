#pragma once


// Service 对话框

class Service : public CDialogEx
{
	DECLARE_DYNAMIC(Service)

public:
	Service(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Service();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
