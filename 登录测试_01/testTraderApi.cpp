// testTraderApi.cpp : �������̨Ӧ�ó������ڵ㡣

//#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
//#include "TraderSpi.h"

//#include "config.h"

#include <windows.h>
#include "ParaHandle.h"

#include <iostream>
using namespace std;

// UserApi����
CThostFtdcTraderApi* pUserApi;

// ������
int iRequestID = 0;

HANDLE g_hEvent = CreateEvent(NULL, true, false, NULL);  
void main(int argc, char* argv[])  // matlab ���ݲ���
//void main(void)
{
	ParaHandle(argc, argv);
	
	// ��ʼ��UserApi
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// ����UserApi
	CTraderSpi* pUserSpi = new CTraderSpi();
	pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// ע���¼���

	//pUserApi->SubscribePublicTopic(TERT_RESTART);					// ע�ṫ����
	//pUserApi->SubscribePrivateTopic(TERT_RESTART);				// ע��˽����

	pUserApi->SubscribePublicTopic(TERT_QUICK);					    // ע�ṫ����
	pUserApi->SubscribePrivateTopic(TERT_QUICK);					// ע��˽����

	pUserApi->RegisterFront(FRONT_ADDR);							// connect

	pUserApi->Init();

	//while (gExitFlag) 
	//	Sleep(100); 
	////����
	//WaitForSingleObject(g_hEvent);
	//WaitForSingleObject(g_hEvent,INFINITE);
	WaitForSingleObject(g_hEvent,5000);

	//Sleep(3000);
	//Sleep(200);

	
	//pUserApi->Join();          // �����̣߳�����ʱʹ�á�ʹ��ʱע�͵� pUserApi->Release(); 
	pUserApi->Release();         // ʵ��ʹ�ã�ʹ��ʱע�͵� pUserApi->Join(); 
}

