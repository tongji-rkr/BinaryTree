
// BinaryTreeDlg.h: 头文件
//

#pragma once
#define LINK 1
#define THREAD -1
#define PREV 0
#define D 40
#define MAX_NODE_NUM 100
//#define BIAS 16
#include<iostream>
using namespace std;

struct Node
{
	Node()
	{
		lchild = rchild = -1;
		//val = 0;
		ltag = rtag = LINK;
		x = y = -1;
		isroot = true;
		dep = 0;
	}
	int lchild, rchild;
	int ltag, rtag;
	int x, y;
	bool isroot;
	int dep;
	//int val;
};
struct BinaryTree
{
private:
	int leafnode_num;
	int buffer;
public:
	Node* tree;
	bool isthread;
	int max_dep;
	int node_num;
	int TreeRoot;
	string traversal_order;
	BinaryTree();
	~BinaryTree();
	void build_fromstd(istream& in, int x0, int y0);
	void build_fromfile(string file_path, int x0, int y0);
	void get_maxdep(int s, int dep);
	int getnum();
	void setxy(int s, int x0, int y0, int dep);
	void preorder_traversal(int s);
	void inorder_traversal(int s);
	void postorder_traversal(int s);
	void preorder_thread(int root, int& prev);
	void preorder_thread_traversal(int root);
	void inorder_thread(int root, int& prev);
	void inorder_thread_traversal(int root);
	void postorder_thread(int root, int& prev);
	void postorder_thread_traversal(int root);
	void dethread();
	string get_result();
};


// CBinaryTreeDlg 对话框
class CBinaryTreeDlg : public CDialogEx
{
// 构造
public:
	CBinaryTreeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINARYTREE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_result2;
	string data;
	BinaryTree T;
private:
	CComboBox edit1;
	CComboBox edit2;
	int traversal_index;
	int thread_index;
	bool is_input;
public:
	afx_msg void OnBnClickedInput();
	afx_msg void OnBnClickedOrder1();
	afx_msg void OnBnClickedOrder3();
	afx_msg void OnBnClickedOrder2();
	afx_msg void OnBnClickedOrder4();
	afx_msg void OnBnClickedOutput();
	afx_msg void PrintBinaryTree(CDC* pDC, int s, bool is_delay = true, int delay_time = 200);
	afx_msg void PrintTheard(CDC* pDC, int s, bool is_delay = true, int delay_time = 200);
	afx_msg void BrushEllispe(CDC* pDC, int s, int RGB1, int RGB2, int RGB3, bool is_delay = true, int delaytime = 200);
};
