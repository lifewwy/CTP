#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include "TraderSpi.h"

//char  FRONT_ADDR[] = "tcp://180.168.146.187:10000";   // ǰ�õ�ַ
char  FRONT_ADDR[] = "tcp://180.168.146.187:10030";   // ǰ�õ�ַ
TThostFtdcBrokerIDType	BROKER_ID = "9999";		    // ���͹�˾����
TThostFtdcInvestorIDType INVESTOR_ID = "101042";	    // ע���������Լ���simnow����Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD = "518888";			// ע���������Լ���simnow�����û�����

//char  FRONT_ADDR[] = "tcp://61.152.165.100:41201";	    // ǰ�õ�ַ       ��ó�ڻ�-���� ���Գɹ�
//TThostFtdcBrokerIDType	BROKER_ID = "0187";				// ���͹�˾����   ��ó�ڻ�-���� ���Գɹ�
//TThostFtdcInvestorIDType INVESTOR_ID = "28006311";	    // ע���������Լ���Ͷ���ߴ���
//TThostFtdcPasswordType  PASSWORD = "518888";			// ע���������Լ����û�����

/*
char  FRONT_ADDR[] = "tcp://116.228.171.216:41205";		// ǰ�õ�ַ      �º��ڻ�-���� ���Գɹ�
TThostFtdcBrokerIDType	BROKER_ID = "6090";				// ���͹�˾����  �º��ڻ�-���� ���Գɹ� 
TThostFtdcInvestorIDType INVESTOR_ID = "10501951";	    // ע���������Լ���Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD = "202031";			// ע���������Լ����û�����
*/

TThostFtdcInstrumentIDType INSTRUMENT_ID = "MA801";	    // ��Լ���� ��ע����ʱ����ı��ԼID,����ʹ�ù�ʱ��Լ
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Buy;	// ��������
//TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	// ��������
TThostFtdcPriceType	LIMIT_PRICE = 2900;				    // �۸�
TThostFtdcVolumeMultipleType Volume = 10;                // ����