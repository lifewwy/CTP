// testTraderApi.cpp : 定义控制台应用程序的入口点。

//#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
//#include "TraderSpi.h"

#include "config.h"
#include <windows.h>

#include <iostream>
using namespace std;

// UserApi对象
CThostFtdcTraderApi* pUserApi;

// 请求编号
int iRequestID = 0;


//void main(int argc, char* r[])  // matlab 传递参数
void main(void)  // matlab 传递参数
{
	//char q = *r[1];
	//cout << "-------"<< q << "-------"  << endl;

	// 初始化UserApi
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类

	//pUserApi->SubscribePublicTopic(TERT_RESTART);					// 注册公有流
	//pUserApi->SubscribePrivateTopic(TERT_RESTART);				// 注册私有流

	pUserApi->SubscribePublicTopic(TERT_QUICK);					    // 注册公有流
	pUserApi->SubscribePrivateTopic(TERT_QUICK);					// 注册私有流

	pUserApi->RegisterFront(FRONT_ADDR);							// connect

	pUserApi->Init();


	Sleep(1000);
	Sleep(200);

	
	pUserApi->Join();          // 阻塞线程，调试时使用。使用时注释掉 pUserApi->Release(); 
	//pUserApi->Release();         // 实际使用，使用时注释掉 pUserApi->Join(); 
}