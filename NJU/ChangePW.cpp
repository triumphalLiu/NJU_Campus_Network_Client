// ChangePW.cpp : 实现文件
//

#include "stdafx.h"
#include "NJU.h"
#include "ChangePW.h"
#include "afxdialogex.h"
#include "Wait.h"
extern char *pw_file_loc;
extern char *old_file_loc;
extern char new_password[MAX_PASSWORD_LENGTH];
// ChangePW 对话框

IMPLEMENT_DYNAMIC(ChangePW, CDialogEx)

ChangePW::ChangePW(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

ChangePW::~ChangePW()
{
}

void ChangePW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangePW, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChangePW::OnBnClickedButton1)
END_MESSAGE_MAP()


// ChangePW 消息处理程序


void ChangePW::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存原密码
	char *username = (char *)malloc(MAX_ID_LENGTH * sizeof(char));
	char *password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
	read_info(username, password);
	save_password(password, old_file_loc);
	//获取输入框内容并保存到pw.nju
	CString strTemp;
	GetDlgItemText(IDC_EDIT1, strTemp);
	char szTemp[128];
	memset(szTemp, 0, sizeof(szTemp));
	strcpy(szTemp, (char *)(strTemp.GetBuffer(strTemp.GetLength())));
	if (strTemp.IsEmpty())
	{
		AfxMessageBox(_T("密码不能为空！"));
		return;
	}

	char *save = (char *)malloc(sizeof(szTemp));
	strcpy(save, strTemp);
	save_password(save, pw_file_loc);

	//AfxMessageBox(strTemp);

	//打开等待框
	Wait* Msgdlg = new Wait;
	Msgdlg->Create(IDD_DIALOG2, this);
	Msgdlg->UpdateData(FALSE);
	Msgdlg->ShowWindow(SW_SHOW);
	Msgdlg->RedrawWindow();
	//修改密码
	WinExec("data\\changepw.exe", SW_HIDE);
	//是否成功
	int change_succ = change_check();
	
	if (change_succ == 1)
	{
		strcpy(new_password, szTemp); 
		CString str;
		str.Format(_T("修改成功!密码改为%s"),szTemp);
		AfxMessageBox(str);
	}
	else
	{
		save_password(password, pw_file_loc);//原密码写入
		CString str;
		str.Format(_T("修改失败!当前密码为%s"), password);
		AfxMessageBox(str);
	}
	
	Msgdlg->DestroyWindow();//销毁等待框
	EndDialog(0);//返回主界面
}