
// TestCtp01Dlg.h : 头文件
//

#pragma once


// CTestCtp01Dlg 对话框
class CTestCtp01Dlg : public CDialogEx
{
// 构造
public:
	CTestCtp01Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTCTP01_DIALOG };

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
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedExit();
protected:
	TCHAR use_pwd[128];
	TCHAR user_name[128];
};
