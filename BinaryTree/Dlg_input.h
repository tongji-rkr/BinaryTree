#pragma once
#include "afxdialogex.h"


// Dlg_input 对话框

class Dlg_input : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_input)

public:
	Dlg_input(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_input();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
//	afx_msg void ON_WM_INITDIALOG();
	virtual BOOL OnInitDialog();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	CString ChildData;
	bool ishint;
private:
	CEdit m_result;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedFileout();
};
