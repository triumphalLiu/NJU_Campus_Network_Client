
// NJUDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NJU.h"
#include "NJUDlg.h"
#include "afxdialogex.h"
#include "InputInfo_Dlg.h"
#include "Wait.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int now_status = 0; //未登录
char new_username[MAX_ID_LENGTH];
char new_password[MAX_PASSWORD_LENGTH]; 
status *new_status = new status;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CNJUDlg 对话框

CNJUDlg::CNJUDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NJU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNJUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNJUDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CNJUDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CNJUDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CNJUDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNJUDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT3, &CNJUDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &CNJUDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CNJUDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CNJUDlg 消息处理程序

BOOL CNJUDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if (!file_is_empty("username.txt"))
	{
		char *username = (char *)malloc(MAX_ID_LENGTH * sizeof(char));
		char *password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
		read_info(username, password);
		CString s1(username);
		CString s2(password);
		/*
		CEdit *p = (CEdit*)GetDlgItem(IDC_EDIT1);
		p->SetWindowText((LPCTSTR)s1);
		CEdit *p2 = (CEdit*)GetDlgItem(IDC_EDIT2);
		p2->SetWindowText((LPCTSTR)s2);
		*/
		Wait* Msgdlg = new Wait;
		Msgdlg->Create(IDD_DIALOG2, this);
		Msgdlg->UpdateData(FALSE);
		Msgdlg->ShowWindow(SW_SHOW);
		Msgdlg->RedrawWindow();
		login();
		Msgdlg->DestroyWindow();

		read_status(new_status);
		if (new_status->successful == 0)
		{
			now_status = 0;
			CString s_fail(_T("登录失败！"));
			CEdit *p_fail = (CEdit*)GetDlgItem(IDC_EDIT3);
			p_fail->SetWindowText((LPCTSTR)s_fail);
			GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT5)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT6)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT7)->SetWindowText(_T(""));
		}
		else
		{
			//AfxMessageBox(_T("123"));
			now_status = 1;
			CString s_succ(_T("登录成功！\r\n"));
			strcpy(new_username, username);
			strcpy(new_password, password);
			CEdit *p_succ = (CEdit*)GetDlgItem(IDC_EDIT3);
			p_succ->SetWindowText((LPCTSTR)s_succ);
			CString s_username(new_status->username);
			CEdit *p_name = (CEdit*)GetDlgItem(IDC_EDIT4);
			p_name->SetWindowText((LPCTSTR)s_username);
			CString s_num;
			s_num.Format(_T("%d"), new_status->device_amounts);
			CEdit *p_num = (CEdit*)GetDlgItem(IDC_EDIT7);
			p_num->SetWindowText((LPCTSTR)s_num);
			CString s_rest;
			s_rest.Format(_T("%.2f元"), new_status->account_balance);
			CEdit *p_rest = (CEdit*)GetDlgItem(IDC_EDIT5);
			p_rest->SetWindowText((LPCTSTR)s_rest);
			CString s_time;
			s_time.Format(_T("%d小时%d分钟"), new_status->hours, new_status->mins);
			CEdit *p_time = (CEdit*)GetDlgItem(IDC_EDIT6);
			p_time->SetWindowText((LPCTSTR)s_time);
		}
		CString s_butt;
		if (now_status == 0)
			s_butt.Format(_T("重新登录"));
		else
			s_butt.Format(_T("登出"));
		CEdit *p_butt = (CEdit*)GetDlgItem(IDC_BUTTON3);
		p_butt->SetWindowText((LPCTSTR)s_butt);
		free(username);
		free(password);
	}
	else
	{
		InputInfo_Dlg *p = new InputInfo_Dlg;
		p->Create(IDD_DIALOG1, this);
		p->ShowWindow(SW_SHOW);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNJUDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNJUDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNJUDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNJUDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CNJUDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CNJUDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CNJUDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CNJUDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CNJUDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	InputInfo_Dlg *p = new InputInfo_Dlg;
	p->Create(IDD_DIALOG1, this);
	p->ShowWindow(SW_SHOW);
}

void CNJUDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (now_status == 1) {
		Wait* Msgdlg = new Wait;
		Msgdlg->Create(IDD_DIALOG2, this);
		Msgdlg->UpdateData(FALSE);
		Msgdlg->ShowWindow(SW_SHOW);
		Msgdlg->RedrawWindow();
		logout();
		Msgdlg->DestroyWindow();
		clean_status();
		CString s_fail(_T("已退出登录！"));
		CEdit *p_fail = (CEdit*)GetDlgItem(IDC_EDIT3);
		p_fail->SetWindowText((LPCTSTR)s_fail);
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT5)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT6)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT7)->SetWindowText(_T(""));
	}
	else
	{

		Wait* Msgdlg = new Wait;
		Msgdlg->Create(IDD_DIALOG2, this);
		Msgdlg->UpdateData(FALSE);
		Msgdlg->ShowWindow(SW_SHOW);
		Msgdlg->RedrawWindow();
		login();
		Msgdlg->DestroyWindow();

		read_status(new_status);
		if (new_status->successful == 1) {
			CString s_succ(_T("登录成功！\r\n"));
			CEdit *p_succ = (CEdit*)GetDlgItem(IDC_EDIT3);
			p_succ->SetWindowText((LPCTSTR)s_succ);
			CString s_username(new_status->username);
			CEdit *p_name = (CEdit*)GetDlgItem(IDC_EDIT4);
			p_name->SetWindowText((LPCTSTR)s_username);
			CString s_num;
			s_num.Format(_T("%d"), new_status->device_amounts);
			CEdit *p_num = (CEdit*)GetDlgItem(IDC_EDIT7);
			p_num->SetWindowText((LPCTSTR)s_num);
			CString s_rest;
			s_rest.Format(_T("%.2f元"), new_status->account_balance);
			CEdit *p_rest = (CEdit*)GetDlgItem(IDC_EDIT5);
			p_rest->SetWindowText((LPCTSTR)s_rest);
			CString s_time;
			s_time.Format(_T("%d小时%d分钟"), new_status->hours, new_status->mins);
			CEdit *p_time = (CEdit*)GetDlgItem(IDC_EDIT6);
			p_time->SetWindowText((LPCTSTR)s_time);
		}
		else
		{
			CString s_succ(_T("登录失败！\r\n"));
			CEdit *p_succ = (CEdit*)GetDlgItem(IDC_EDIT3);
			p_succ->SetWindowText((LPCTSTR)s_succ);
		}
	}
	now_status = (new_status->successful == 1) ? 1 : 0;
	CString s_butt;
	if (now_status == 0)
		s_butt.Format(_T("重新登录"));
	else
		s_butt.Format(_T("登出"));
	CEdit *p_butt = (CEdit*)GetDlgItem(IDC_BUTTON3);
	p_butt->SetWindowText((LPCTSTR)s_butt);
}
