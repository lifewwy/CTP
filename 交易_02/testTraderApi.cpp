// testTraderApi.cpp : �������̨Ӧ�ó������ڵ㡣

//#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
//#include "TraderSpi.h"

#include "config.h"
#include <windows.h>

#include <iostream>
using namespace std;

// UserApi����
CThostFtdcTraderApi* pUserApi;

// ������
int iRequestID = 0;


//void main(int argc, char* r[])  // matlab ���ݲ���
void main(void)  // matlab ���ݲ���
{
	//char q = *r[1];
	//cout << "-------"<< q << "-------"  << endl;

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


	Sleep(1000);
	Sleep(200);

	
	pUserApi->Join();          // �����̣߳�����ʱʹ�á�ʹ��ʱע�͵� pUserApi->Release(); 
	//pUserApi->Release();         // ʵ��ʹ�ã�ʹ��ʱע�͵� pUserApi->Join(); 
}