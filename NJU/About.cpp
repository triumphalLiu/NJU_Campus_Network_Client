// About.cpp : 实现文件
//

#include "stdafx.h"
#include "NJU.h"
#include "About.h"
#include "afxdialogex.h"


// About 对话框

IMPLEMENT_DYNAMIC(About, CDialogEx)

About::About(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

About::~About()
{
}

void About::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(About, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &About::OnBnClickedCancel)
END_MESSAGE_MAP()


// About 消息处理程序


void About::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
