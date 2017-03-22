// Wait.cpp : 实现文件
//

#include "stdafx.h"
#include "NJU.h"
#include "Wait.h"
#include "afxdialogex.h"


// Wait 对话框

IMPLEMENT_DYNAMIC(Wait, CDialogEx)

Wait::Wait(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Wait::~Wait()
{
}

void Wait::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Wait, CDialogEx)
END_MESSAGE_MAP()


// Wait 消息处理程序
