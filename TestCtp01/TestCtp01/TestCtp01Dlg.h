
// TestCtp01Dlg.h : ͷ�ļ�
//

#pragma once


// CTestCtp01Dlg �Ի���
class CTestCtp01Dlg : public CDialogEx
{
// ����
public:
	CTestCtp01Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTCTP01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
