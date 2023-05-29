
// BinaryTreeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "BinaryTree.h"
#include "BinaryTreeDlg.h"
#include "afxdialogex.h"
#include "Dlg_input.h"
#include<iostream>
#include<fstream>
#include<assert.h>
#include<sstream>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BinaryTree::BinaryTree()
{
	tree = NULL;
	node_num = leafnode_num = buffer = 0;
	isthread = false;
	traversal_order = "";
	TreeRoot = -1;
	max_dep = 0;
}
BinaryTree::~BinaryTree()
{
	delete[]tree;
}
void BinaryTree::build_fromstd(istream& in,int x0,int y0)
{
	int lc = 0, rc = 0;
	in >> node_num;
	buffer = node_num + 1;//点从1开始
	tree = new Node[buffer];
	int x = x0, y = y0;
	for (int i = 1; i <= node_num; i++)
	{
		in >> lc >> rc;// >> tree[i].val;
		tree[i].lchild = lc;
		tree[i].rchild = rc;
		if (lc != -1)tree[lc].isroot = false;
		if (rc != -1)tree[rc].isroot = false;
		if (lc == -1 && rc == -1)
		{
			leafnode_num++;
		}
	}
	for (int i = 1; i <= node_num; i++)
	{
		if (tree[i].isroot)
		{
			TreeRoot = i;
			break;
		}
	}
	get_maxdep(TreeRoot, 1);
	setxy(TreeRoot, x0, y0, 1);
	return;
}
void BinaryTree::build_fromfile(string file_path, int x0, int y0)
{
	ifstream infile;
	infile.open(file_path.data());
	assert(infile.is_open());
	build_fromstd(infile, x0, y0);
	infile.close();
	return;
}
void BinaryTree::get_maxdep(int s,int dep)
{
	if (s == -1)return;
	tree[s].dep = dep;
	max_dep = max(max_dep, dep);
	get_maxdep(tree[s].lchild, dep + 1);
	get_maxdep(tree[s].rchild, dep + 1);
}
int BinaryTree::getnum()
{
	return leafnode_num;
}
void BinaryTree::setxy(int s, int x0, int y0,int dep)
{
	tree[s].x = x0, tree[s].y = y0;
	if (tree[s].lchild != -1)
		setxy(tree[s].lchild, x0 - (D * max_dep) / dep, y0 + 90, dep + 1);
	if (tree[s].rchild != -1)
		setxy(tree[s].rchild, x0 + (D * max_dep) / dep, y0 + 90, dep + 1);
}
void BinaryTree::preorder_traversal(int s)
{
	int p = tree[s].lchild, r = tree[s].rchild;
	traversal_order += (s+'0');
	if (p != -1)preorder_traversal(p);
	if (r != -1)preorder_traversal(r);
}
void BinaryTree::inorder_traversal(int s)
{
	int p = tree[s].lchild, r = tree[s].rchild;
	if (p != -1)inorder_traversal(p);
	traversal_order += (s + '0');
	if (r != -1)inorder_traversal(r);
}
void BinaryTree::postorder_traversal(int s)
{
	int p = tree[s].lchild, r = tree[s].rchild;
	if (p != -1)postorder_traversal(p);
	if (r != -1)postorder_traversal(r);
	traversal_order += (s + '0');
}
void BinaryTree::preorder_thread(int root, int& prev)
{
	if (tree[root].lchild == -1)
	{
		tree[root].lchild = prev;
		tree[root].ltag = THREAD;
	}
	if (prev > 0 && tree[prev].rchild == -1)
	{
		tree[prev].rchild = root;
		tree[prev].rtag = THREAD;
	}
	prev = root;
	if (tree[root].ltag == LINK && tree[root].lchild > 0)
	{
		preorder_thread(tree[root].lchild, prev);
	}
	if (tree[root].rtag == LINK && tree[root].rchild > 0)
	{
		preorder_thread(tree[root].rchild, prev);
	}
}
void BinaryTree::preorder_thread_traversal(int root)
{
	int cur = root;
	while (cur != -1)
	{
		while (tree[cur].ltag == LINK)
		{
			traversal_order += (cur + '0');
			cur = tree[cur].lchild;
		}
		traversal_order += (cur + '0');
		cur = tree[cur].rchild;
	}
	cout << endl;
}
void BinaryTree::inorder_thread(int root, int& prev)
{

	if (tree[root].lchild > 0)
		inorder_thread(tree[root].lchild, prev);
	if (tree[root].lchild == -1)
	{
		tree[root].lchild = prev;
		tree[root].ltag = THREAD;
	}
	if (prev > 0 && tree[prev].rchild == -1)
	{
		tree[prev].rchild = root;
		tree[prev].rtag = THREAD;

	}
	prev = root;
	if (tree[root].rchild > 0)
		inorder_thread(tree[root].rchild, prev);
}
void BinaryTree::inorder_thread_traversal(int root)
{
	int cur = root;
	while (cur != -1)
	{
		while (tree[cur].ltag == LINK)
		{
			cur = tree[cur].lchild;
		}
		traversal_order += (cur + '0');
		while (tree[cur].rtag == THREAD)
		{
			cur = tree[cur].rchild;
			traversal_order += (cur + '0');
		}
		cur = tree[cur].rchild;
	}
	cout << endl;
}
void BinaryTree::postorder_thread(int root, int& prev)
{
	if (tree[root].lchild >0)
		postorder_thread(tree[root].lchild, prev);
	if (tree[root].rchild >0)
		postorder_thread(tree[root].rchild,prev);
	if (tree[root].lchild == -1)
	{
		tree[root].lchild = prev;
		tree[root].ltag = THREAD;
	}
	if (prev > 0 && tree[prev].rchild == -1)
	{
		tree[prev].rchild = root;
		tree[prev].rtag = THREAD;

	}
	prev = root;
}
void BinaryTree::postorder_thread_traversal(int root)
{
	int cur = root, prev = 0;
	int parent[MAX_NODE_NUM];
	parent[root] = -1;
	while (cur != -1)
	{
		while (tree[cur].lchild != prev)
		{
			parent[tree[cur].lchild] = cur;
			cur = tree[cur].lchild;
		}
		while (cur>0 && tree[cur].rtag == THREAD)
		{
			traversal_order += (cur + '0');
			prev = cur;
			cur = tree[cur].rchild;
		}
		//判断此时cur是不是指向了根节点
		if (cur == root)
		{
			traversal_order += (cur + '0');
			return;
		}
		while (cur>0 && tree[cur].rchild == prev)
		{
			traversal_order += (cur + '0');
			prev = cur;
			cur = parent[cur];  //往上一级走
		}
		//这里不能用NULL判断，而是用Rtag
		if (cur > 0 && tree[cur].rtag == LINK)
		{
			parent[tree[cur].rchild] = cur;
			cur = tree[cur].rchild;
		}
	}
	cout << endl;
}
void BinaryTree::dethread()
{
	for (int i = 0; i <= node_num; i++)
	{
		if (tree[i].ltag == THREAD)
		{
			tree[i].ltag = LINK;
			tree[i].lchild = -1;
		}
		if (tree[i].rtag == THREAD)
		{
			tree[i].rtag = LINK;
			tree[i].rchild = -1;
		}
	}
}


string BinaryTree::get_result()
{
	string output = "";
	output += (node_num + '0');
	output += "\r\n";
	for (int i = 1; i <= node_num; i++)
	{
		output += tree[i].ltag == LINK ? "LINK" : "THREAD";
		output += " ";
		output += (tree[i].lchild + '0');
		output += " ";
		output += tree[i].rtag == LINK ? "LINK" : "THREAD";
		output += " ";
		output += (tree[i].rchild + '0');
		output += "\r\n";
	}
	return output;
}
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


// CBinaryTreeDlg 对话框



CBinaryTreeDlg::CBinaryTreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BINARYTREE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinaryTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPTION1, edit1);
	DDX_Control(pDX, IDC_OPTION2, edit2);
	DDX_Control(pDX, IDC_EDIT1, m_result2);
}

BEGIN_MESSAGE_MAP(CBinaryTreeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INPUT, &CBinaryTreeDlg::OnBnClickedInput)
	ON_BN_CLICKED(IDC_ORDER1, &CBinaryTreeDlg::OnBnClickedOrder1)
	ON_BN_CLICKED(IDC_ORDER3, &CBinaryTreeDlg::OnBnClickedOrder3)
	ON_BN_CLICKED(IDC_ORDER2, &CBinaryTreeDlg::OnBnClickedOrder2)
	ON_BN_CLICKED(IDC_ORDER4, &CBinaryTreeDlg::OnBnClickedOrder4)
	ON_BN_CLICKED(IDC_OUTPUT, &CBinaryTreeDlg::OnBnClickedOutput)
END_MESSAGE_MAP()


// CBinaryTreeDlg 消息处理程序

BOOL CBinaryTreeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	is_input = false;
	traversal_index = thread_index = 0;

	edit1.AddString(TEXT("请选择遍历方式"));
	edit1.AddString(TEXT("前序遍历"));
	edit1.AddString(TEXT("中序遍历"));
	edit1.AddString(TEXT("后序遍历"));
	edit1.SetCurSel(0);

	edit2.AddString(TEXT("请选择线索化方式"));
	edit2.AddString(TEXT("前序线索化"));
	edit2.AddString(TEXT("中序线索化"));
	edit2.AddString(TEXT("后序线索化"));
	edit2.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBinaryTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBinaryTreeDlg::OnPaint()
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
HCURSOR CBinaryTreeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBinaryTreeDlg::PrintBinaryTree(CDC* pDC, int s,bool is_delay,int delay_time)
{
	// TODO: 在此处添加实现代码.
	if (s == -1) return;
	pDC->Ellipse(T.tree[s].x - 20, T.tree[s].y - 20, T.tree[s].x + 30, T.tree[s].y + 30);
	if(is_delay)Sleep(delay_time);
	CString str;
	str.Format(_T("%c"), s + '0');
	pDC->TextOutW(T.tree[s].x, T.tree[s].y, str);
	if (is_delay)Sleep(delay_time);
	int lc = T.tree[s].lchild, rc = T.tree[s].rchild;
	if (lc != -1)
	{
		PrintBinaryTree(pDC, lc);
		if (is_delay)Sleep(delay_time);
		pDC->MoveTo(T.tree[s].x - 16, T.tree[s].y + 16);
		pDC->LineTo(T.tree[lc].x + 16, T.tree[lc].y - 16);
	}
	if (rc != -1)
	{
		PrintBinaryTree(pDC, rc);
		if (is_delay)Sleep(delay_time);
		pDC->MoveTo(T.tree[s].x + 21, T.tree[s].y + 21);
		pDC->LineTo(T.tree[rc].x - 15, T.tree[rc].y - 15);
	}
}


void CBinaryTreeDlg::PrintTheard(CDC* pDC, int s, bool is_delay, int delay_time)
{
	CPen pen1(PS_DASH, 1, RGB(255, 0, 0));
	pDC->SelectObject(&pen1);
	for (int i = 1; i <= T.node_num; i++)
	{
		if (T.tree[i].ltag == THREAD && T.tree[i].lchild >0)
		{
			int x1 = T.tree[i].x - (D * T.max_dep) / T.tree[i].dep;
			int y1 = T.tree[i].y + 90;
			pDC->Ellipse(x1 - 20, y1 - 20, x1 + 30, y1 + 30);
			if (is_delay)Sleep(delay_time);
			CString str;
			str.Format(_T("%c"), T.tree[i].lchild + '0');
			pDC->TextOutW(x1, y1, str);
			if (is_delay)Sleep(delay_time);
			pDC->MoveTo(T.tree[i].x - 16, T.tree[i].y + 16);
			pDC->LineTo(x1 + 16, y1 - 16);
			if (is_delay)Sleep(delay_time);
		}
	}
	CPen pen2(PS_DASH, 1, RGB(0, 0, 255));
	pDC->SelectObject(&pen2);
	for (int i = 1; i <= T.node_num; i++)
	{
		if (T.tree[i].rtag == THREAD && T.tree[i].rchild >0)
		{
			int x1 = T.tree[i].x + (D * T.max_dep) / T.tree[i].dep;
			int y1 = T.tree[i].y + 90;
			pDC->Ellipse(x1 - 20, y1 - 20, x1 + 30, y1 + 30);
			if (is_delay)Sleep(delay_time);
			CString str;
			str.Format(_T("%c"), T.tree[i].rchild + '0');
			pDC->TextOutW(x1, y1, str);
			if (is_delay)Sleep(delay_time);
			pDC->MoveTo(T.tree[i].x + 21, T.tree[i].y + 21);
			pDC->LineTo(x1 - 15, y1 - 15);
			if (is_delay)Sleep(delay_time);
		}
	}
}


void CBinaryTreeDlg::BrushEllispe(CDC* pDC, int s, int RGB1, int RGB2, int RGB3, bool is_delay, int delay_time)
{
	CBrush brush(RGB(RGB1, RGB2, RGB3));//根据自己需要填充颜色
	CBrush* oldbrush;
	oldbrush = pDC->SelectObject(&brush);//选新的画刷
	pDC->Ellipse(T.tree[s].x - 20, T.tree[s].y - 20, T.tree[s].x + 30, T.tree[s].y + 30);
	if (is_delay)Sleep(delay_time);
	CString str;
	str.Format(_T("%c"), s + '0');
	pDC->TextOutW(T.tree[s].x, T.tree[s].y, str);
	if (is_delay)Sleep(delay_time / 2);
	pDC->SelectObject(oldbrush);//将原来的画刷选回去
	pDC->Ellipse(T.tree[s].x - 20, T.tree[s].y - 20, T.tree[s].x + 30, T.tree[s].y + 30);
	if (is_delay)Sleep(delay_time);
	str.Format(_T("%c"), s + '0');
	pDC->TextOutW(T.tree[s].x, T.tree[s].y, str);
	if (is_delay)Sleep(delay_time / 2);
}


void CBinaryTreeDlg::OnBnClickedInput()
{
	// TODO: 在此添加控件通知处理程序代码
	Dlg_input dlg1;
	dlg1.ChildData = TEXT("8\r\n2 4\r\n-1 3\r\n-1 -1\r\n5 8\r\n-1 6\r\n-1 7\r\n-1 -1\r\n-1 -1");
	dlg1.ishint = true;
	dlg1.DoModal();
	SetDlgItemText(IDC_EDIT1, dlg1.ChildData);
	data = CT2A(dlg1.ChildData.GetString());
	stringstream ss;
	ss << data;
	CRect rect;
	CWnd* pWin = GetDlgItem(IDC_STATIC);
	pWin->GetClientRect(rect);
	int x = rect.Width();
	int y = rect.Height();
	T.build_fromstd(ss, x / 2, 75);
	is_input = true;
	CDC* pDC = pWin->GetDC();
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	pDC->SelectObject(&pen);
	PrintBinaryTree(pDC, T.TreeRoot, false);
}


void CBinaryTreeDlg::OnBnClickedOrder1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!is_input)
		MessageBox(_T("请先输入结点信息！"));
	else
	{
		CString m_str, m_order;
		CRect rect;
		CWnd* pWin = GetDlgItem(IDC_STATIC);
		pWin->GetClientRect(rect);
		int x = rect.Width();
		int y = rect.Height();
		is_input = true;
		CDC* pDC = pWin->GetDC();
		CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
		pDC->SelectObject(&pen);
		traversal_index = ((CComboBox*)GetDlgItem(IDC_OPTION1))->GetCurSel();
		if (T.isthread)
			T.dethread();
		T.traversal_order = "";
		switch (traversal_index)
		{
			case 0:MessageBox(_T("请选择遍历方式！")); break;
			case 1:T.preorder_traversal(T.TreeRoot); break;
			case 2:T.inorder_traversal(T.TreeRoot); break;
			case 3:T.postorder_traversal(T.TreeRoot); break;
		}
		((CComboBox*)GetDlgItem(IDC_OPTION1))->GetLBText(traversal_index, m_str);
		for (auto& c : T.traversal_order)
		{
			int s = c - '0';
			BrushEllispe(pDC, s, 255, 255, 0);
		}
		m_order = T.traversal_order.c_str();
		m_str += _T("的结果为:\r\n") + m_order;
		SetDlgItemText(IDC_EDIT1, m_str);
		MessageBox(m_str);
		int prev = PREV;
		if (T.isthread)
		{
			if (thread_index == 1)
				T.preorder_thread(T.TreeRoot, prev);
			else
				T.inorder_thread(T.TreeRoot, prev);
		}
	}

}


void CBinaryTreeDlg::OnBnClickedOrder2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!is_input)
		MessageBox(_T("请先输入结点信息！"));
	else
	{
		CString m_leafnodenum;
		m_leafnodenum.Format(_T("二叉树叶子结点个数为：%d"), T.getnum());
		MessageBox(m_leafnodenum);
	}
}



void CBinaryTreeDlg::OnBnClickedOrder3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!is_input)
		MessageBox(_T("请先输入结点信息！"));
	else
	{
		CString m_str;
		CRect rect;
		CWnd* pWin = GetDlgItem(IDC_STATIC);
		pWin->GetClientRect(rect);
		int x = rect.Width();
		int y = rect.Height();
		is_input = true;
		CDC* pDC = pWin->GetDC();
		CPen pen0(PS_SOLID, 3, RGB(0, 0, 0));
		pDC->SelectObject(&pen0);
		thread_index = ((CComboBox*)GetDlgItem(IDC_OPTION2))->GetCurSel();
		if (T.isthread)
		{
			CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC);
			CRect IRect;
			pStatic->GetClientRect(&IRect);
			pStatic->GetDC()->FillSolidRect(IRect.left, IRect.top, IRect.Width(), IRect.Height(), RGB(240, 240, 240));
			T.dethread();
			PrintBinaryTree(pDC, T.TreeRoot, 0);
			T.isthread = false;
		}
		int prev = PREV;
		switch (thread_index)
		{
			case 0:MessageBox(_T("请选择线索化方式！")); break;
			case 1:T.preorder_thread(T.TreeRoot, prev); break;
			case 2:T.inorder_thread(T.TreeRoot, prev); break;
			case 3:T.postorder_thread(T.TreeRoot, prev); break;
		}
		//((CComboBox*)GetDlgItem(IDC_OPTION2))->GetLBText(traversal_index, m_str);
		PrintTheard(pDC, T.TreeRoot);
		T.isthread = true;
	}
}


void CBinaryTreeDlg::OnBnClickedOrder4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!is_input)
		MessageBox(_T("请先输入结点信息！"));
	else
	{
		CString m_str,m_order;
		int index;
		index = ((CComboBox*)GetDlgItem(IDC_OPTION2))->GetCurSel();
		if (index != thread_index)
		{
			MessageBox(_T("选择的线索化方式改变，请重新生成线索化二叉树！！"));
		}
		else
		{
			T.traversal_order = "";
			switch (thread_index)
			{
				case 0:break;
				case 1:T.preorder_thread_traversal(T.TreeRoot); break;
				case 2:T.inorder_thread_traversal(T.TreeRoot); break;
				case 3:T.postorder_thread_traversal(T.TreeRoot); break;
			}
			m_str = T.traversal_order.c_str();
			SetDlgItemText(IDC_EDIT1, m_str);
			((CComboBox*)GetDlgItem(IDC_OPTION2))->GetLBText(traversal_index, m_str);
			CRect rect;
			CWnd* pWin = GetDlgItem(IDC_STATIC);
			pWin->GetClientRect(rect);
			int x = rect.Width();
			int y = rect.Height();
			is_input = true;
			CDC* pDC = pWin->GetDC();
			CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
			pDC->SelectObject(&pen);
			for (auto& c : T.traversal_order)
			{
				int s = c - '0';
				BrushEllispe(pDC, s, 255, 255, 0);
			}
			m_order = T.traversal_order.c_str();
			m_str += _T("遍历的结果为:\r\n") + m_order;
			SetDlgItemText(IDC_EDIT1, m_str);
			MessageBox(m_str);
		}
		
	}
}


void CBinaryTreeDlg::OnBnClickedOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!is_input)
		MessageBox(_T("请先输入结点信息！"));
	else
	{
		if (!T.isthread)
			MessageBox(_T("请先对二叉树进行线索化！"));
		else
		{
			Dlg_input dlg2;
			string output = T.get_result();
			dlg2.ChildData = output.c_str();
			dlg2.DoModal();
		}
	}
}
