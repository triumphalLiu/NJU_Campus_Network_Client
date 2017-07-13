// Service.cpp : 实现文件
//

#include "stdafx.h"
#include "NJU.h"
#include "Service.h"
#include "afxdialogex.h"

extern char *serv1;
extern char *serv2;
extern status *new_status;
char *service_file_loc = "data\\service.nju";

// Service 对话框

IMPLEMENT_DYNAMIC(Service, CDialogEx)

Service::Service(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

Service::~Service()
{
}

void Service::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Service, CDialogEx)
	ON_BN_CLICKED(IDOK, &Service::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Service::OnBnClickedCancel)
END_MESSAGE_MAP()

// Service 消息处理程序


void Service::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == 1)
		save_password(serv1, service_file_loc);
	else if(((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == 1)
		save_password(serv2, service_file_loc);
	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == 0 && (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == 0))
	{
		AfxMessageBox(_T("请做出选择"));
		return;
	}
	WinExec("data\\changeservice.exe", SW_HIDE);
	if (change_check() == 1)
		AfxMessageBox(_T("修改成功"));
	else
		AfxMessageBox(_T("修改失败"));
	read_status();
	CDialogEx::OnOK();
}


void Service::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

/*

if (strcmp(serv1, new_status->service) == 0)
{
((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
}
else if (strcmp(serv2, new_status->service) == 0)
{
((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
}
else
{
((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
}
*/