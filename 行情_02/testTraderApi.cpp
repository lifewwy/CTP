// testTraderApi.cpp : �������̨Ӧ�ó������ڵ㡣

//#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
//#include "TraderSpi.h"

//#include "config.h"

#include <windows.h>
#include "ParaHandle.h"

#include <iostream>
using namespace std;

// UserApi����
CThostFtdcMdApi* pUserApi;

// ������
int iRequestID = 0;

HANDLE g_hEvent = CreateEvent(NULL, true, false, NULL);  

void main(int argc, char* argv[])  // matlab ���ݲ���
//void main(void)
{
	ParaHandle(argc, argv);

	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// ����UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// ע���¼���
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();
	

	//while (gExitFlag) 
	//	Sleep(100); 
	////����
	//WaitForSingleObject(g_hEvent);
	//WaitForSingleObject(g_hEvent,INFINITE);
	WaitForSingleObject(g_hEvent,20000);

	//Sleep(3000);
	//Sleep(200);

	
	//pUserApi->Join();          // �����̣߳�����ʱʹ�á�ʹ��ʱע�͵� pUserApi->Release(); 
	pUserApi->Release();         // ʵ��ʹ�ã�ʹ��ʱע�͵� pUserApi->Join(); 
}

