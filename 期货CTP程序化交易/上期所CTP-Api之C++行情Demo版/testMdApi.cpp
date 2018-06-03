// testTraderApi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "MdSpi.h"

// UserApi����
CThostFtdcMdApi* pUserApi;

//char  FRONT_ADDR[] = "tcp://180.168.146.187:10031";   // ǰ�õ�ַ       simnow����
//TThostFtdcBrokerIDType	BROKER_ID = "9999";		    // ���͹�˾����   simnow����
//TThostFtdcInvestorIDType INVESTOR_ID = "101024";		// ע�������������Լ���Ͷ���ߴ���
//TThostFtdcPasswordType  PASSWORD = "518888";			// ע�������������Լ����û�����

char  FRONT_ADDR[] = "tcp://116.228.171.216:41213";	    // ǰ�õ�ַ       �º��ڻ�-���� ���Գɹ�
TThostFtdcBrokerIDType	BROKER_ID = "6090";				// ���͹�˾����   �º��ڻ�-���� ���Գɹ�
TThostFtdcInvestorIDType INVESTOR_ID = "10501951";	    // ע���������Լ���Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD = "518888";			// ע���������Լ����û�����

/*
char  FRONT_ADDR[] = "tcp://61.152.165.100:41211";		// ǰ�õ�ַ       ��ó�ڻ�-���� ���Գɹ�
TThostFtdcBrokerIDType	BROKER_ID = "0187";				// ���͹�˾����   ��ó�ڻ�-���� ���Գɹ�
TThostFtdcInvestorIDType INVESTOR_ID = "28006311";	    // ע���������Լ���simnow����Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD = "518888";			// ע���������Լ���simnow�����û�����*/


char *ppInstrumentID[] = {"m1801", "rb1801"};			// ���鶩���б�ע�⣬�����ԼID���ʱ�ģ�ע����ʱ����޸�
int iInstrumentID = 2;									// ���鶩������


// ������
int iRequestID = 0;

void main(void)
{
	// ��ʼ��UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// ����UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// ע���¼���
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();

	pUserApi->Join();
//	pUserApi->Release();
}