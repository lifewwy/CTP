// testTraderApi.cpp : 定义控制台应用程序的入口点。

//#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
//#include "TraderSpi.h"

//#include "config.h"

#include <windows.h>
#include "ParaHandle.h"

#include <iostream>
using namespace std;

// UserApi对象
CThostFtdcMdApi* pUserApi;

// 请求编号
int iRequestID = 0;

HANDLE g_hEvent = CreateEvent(NULL, true, false, NULL);  

void main(int argc, char* argv[])  // matlab 传递参数
//void main(void)
{
	ParaHandle(argc, argv);

	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();
	

	//while (gExitFlag) 
	//	Sleep(100); 
	////或者
	//WaitForSingleObject(g_hEvent);
	//WaitForSingleObject(g_hEvent,INFINITE);
	WaitForSingleObject(g_hEvent,20000);

	//Sleep(3000);
	//Sleep(200);

	
	//pUserApi->Join();          // 阻塞线程，调试时使用。使用时注释掉 pUserApi->Release(); 
	pUserApi->Release();         // 实际使用，使用时注释掉 pUserApi->Join(); 
}

