// Dlg_input.cpp: 实现文件
//

#include "pch.h"
#include "BinaryTree.h"
#include "afxdialogex.h"
#include "Dlg_input.h"
#include "BinaryTreeDlg.h"
#include <fstream>



// Dlg_input 对话框

IMPLEMENT_DYNAMIC(Dlg_input, CDialogEx)

Dlg_input::Dlg_input(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	ishint = false;
}

Dlg_input::~Dlg_input()
{
}

void Dlg_input::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_result);
}


BEGIN_MESSAGE_MAP(Dlg_input, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &Dlg_input::OnEnChangeEdit1)
//	ON_EN_ERRSPACE(IDC_EDIT1, &Dlg_input::ON_WM_INITDIALOG)
ON_BN_CLICKED(IDC_FILEOUT, &Dlg_input::OnBnClickedFileout)
END_MESSAGE_MAP()


// Dlg_input 消息处理程序

//void Dlg_input::ON_WM_INITDIALOG()
//{
	// TODO: 在此添加控件通知处理程序代码
	//CString   str = TEXT("123\r\n345 ");
	//GetDlgItem(IDC_EDIT1)->SetWindowText(str);
//}

void Dlg_input::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




BOOL Dlg_input::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CEdit* edit1 = (CEdit*)GetDlgItem(IDC_STATIC);
	CEdit* edit2 = (CEdit*)GetDlgItem(IDC_FILEOUT);
	if (ishint)
	{
		edit1->ShowWindow(TRUE);//显示该控件
	}
	else
	{
		edit2->ShowWindow(TRUE);//显示该控件
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(ChildData);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//BOOL Dlg_input::PreTranslateMessage(MSG* pMsg)
//{
	// TODO: 在此添加专用代码和/或调用基类  
//	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
//	{
		//将ESC键的消息替换为回车键的消息，这样，按ESC的时候  
		//也会和回车键一样去调用OnOK函数，而OnOK什么也不做，这样ESC也被屏蔽  
//		pMsg->wParam = VK_RETURN;
//	}
//	return CDialogEx::PreTranslateMessage(pMsg);
//}


void Dlg_input::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
	CBinaryTreeDlg* parent = (CBinaryTreeDlg*)GetParent();
	this->m_result.GetWindowText(ChildData);//获取当前子窗口编辑框中的值
	CDialogEx::EndDialog(0);
}


void Dlg_input::OnBnClickedFileout()
{
	// TODO: 在此添加控件通知处理程序代码
	ofstream outfile;
	string file_path = "output.txt";
	outfile.open(file_path.data());
	//assert(outfile.is_open());
	string out_str = CT2A(ChildData.GetString());
	outfile << out_str;
	outfile.close();
}
