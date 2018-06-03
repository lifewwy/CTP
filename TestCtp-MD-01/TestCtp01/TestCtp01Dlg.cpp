
// TestCtp01Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestCtp01.h"
#include "TestCtp01Dlg.h"
#include "afxdialogex.h"

#include <ThostFtdcMdApi.h>
#include <ThostFtdcUserApiStruct.h>
#include <ThostFtdcTraderApi.h>
#include <ThostFtdcUserApiDataType.h>

#include "MdSpi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// UserApi对象
CThostFtdcMdApi* pUserApi;

//char  FRONT_ADDR[] = "tcp://180.168.146.187:10031";   // 前置地址       simnow仿真
//TThostFtdcBrokerIDType	BROKER_ID = "9999";		    // 经纪公司代码   simnow仿真
//TThostFtdcInvestorIDType INVESTOR_ID = "101024";		// 注意这里输入你自己的投资者代码
//TThostFtdcPasswordType  PASSWORD = "518888";			// 注意这里输入你自己的用户密码

//char  FRONT_ADDR[] = "tcp://116.228.171.216:41213";	    // 前置地址       新湖期货-快期 测试成功
//TThostFtdcBrokerIDType	BROKER_ID = "6090";				// 经纪公司代码   新湖期货-快期 测试成功
//TThostFtdcInvestorIDType INVESTOR_ID = "10501951";	    // 注意输入你自己的投资者代码
//TThostFtdcPasswordType  PASSWORD = "202031";			// 注意输入你自己的用户密码


char  FRONT_ADDR[] = "tcp://61.152.165.100:41211";		// 前置地址       国贸期货-快期 测试成功
TThostFtdcBrokerIDType	BROKER_ID = "0187";				// 经纪公司代码   国贸期货-快期 测试成功
TThostFtdcInvestorIDType INVESTOR_ID = "28006311";	    // 注意输入你自己的simnow仿真投资者代码
TThostFtdcPasswordType  PASSWORD = "518888";			// 注意输入你自己的simnow仿真用户密码


char *ppInstrumentID[] = {"m1801", "rb1801"};			// 行情订阅列表，注意，这个合约ID会过时的，注意与时俱进修改
int iInstrumentID = 2;									// 行情订阅数量

// 请求编号
int iRequestID = 0;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestCtp01Dlg 对话框



CTestCtp01Dlg::CTestCtp01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestCtp01Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCtp01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestCtp01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestCtp01Dlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CTestCtp01Dlg 消息处理程序

BOOL CTestCtp01Dlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestCtp01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestCtp01Dlg::OnPaint()
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
HCURSOR CTestCtp01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestCtp01Dlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	// 初始化UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();

	pUserApi->Join();
	//	pUserApi->Release();

	TRACE("DDDDDDDDDDD");

}
