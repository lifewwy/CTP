#include <iostream>
using namespace std;

#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include "TraderSpi.h"
#include <time.h>

#pragma warning(disable : 4996)

// USER_API����
extern CThostFtdcTraderApi* pUserApi;

// ���ò���
extern char FRONT_ADDR[];		// ǰ�õ�ַ
extern char BROKER_ID[];		// ���͹�˾����
extern char INVESTOR_ID[];		// Ͷ���ߴ���
extern char PASSWORD[];			// �û�����
extern char INSTRUMENT_ID[];	// ��Լ����
extern TThostFtdcPriceType	LIMIT_PRICE;	// �۸�
extern TThostFtdcDirectionType	DIRECTION;	// ��������
extern TThostFtdcVolumeMultipleType Volume;

// ������
extern int iRequestID;

// �Ự����
TThostFtdcFrontIDType	FRONT_ID;	//ǰ�ñ��
TThostFtdcSessionIDType	SESSION_ID;	//�Ự���
TThostFtdcOrderRefType	ORDER_REF;	//��������
time_t lOrderTime;
time_t lOrderOkTime;
void CTraderSpi::OnFrontConnected()
{
	cerr << "--->>> " << "OnFrontConnected" << endl;
	cerr<< "��������ѽ�������, ��ʼ��¼" <<endl; 
	///�û���¼����
	ReqUserLogin();
}

void CTraderSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.UserID, INVESTOR_ID);
	strcpy(req.Password, PASSWORD);
	int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
	cerr << "--->>> �����û���¼����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspUserLogin" << endl;
	//if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		// ����Ự����
		FRONT_ID = pRspUserLogin->FrontID;
		SESSION_ID = pRspUserLogin->SessionID;
		int iNextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
		iNextOrderRef++;
		sprintf(ORDER_REF, "%d", iNextOrderRef);
		//��ȡ��ǰ������
		cerr << "--->>> ��ȡ��ǰ������ = " << pUserApi->GetTradingDay() << endl;
		//Ͷ���߽�����ȷ��
		ReqSettlementInfoConfirm();
	}
}

void CTraderSpi::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.InvestorID, INVESTOR_ID);
	int iResult = pUserApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
	cerr << "--->>> Ͷ���߽�����ȷ��: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
											CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspSettlementInfoConfirm" << endl;

	//if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///�����ѯ��Լ
		//ReqQryInstrument();

		///����¼������
		
	}

	ReqOrderInsert();
}


void CTraderSpi::ReqOrderInsert()
{
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///���͹�˾����
	strcpy(req.BrokerID, BROKER_ID);
	///Ͷ���ߴ���
	strcpy(req.InvestorID, INVESTOR_ID);
	///��Լ����
	strcpy(req.InstrumentID, INSTRUMENT_ID);
	///��������
	strcpy(req.OrderRef, ORDER_REF);
	///�û�����
//	TThostFtdcUserIDType	UserID;
	///�����۸�����: �޼�
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	//req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
	///��������: 
	req.Direction = DIRECTION;
	///��Ͽ�ƽ��־: ����/ƽ��
	req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	//req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
	///���Ͷ���ױ���־
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	///�۸�
	req.LimitPrice = LIMIT_PRICE;
	///����: 1
	req.VolumeTotalOriginal = Volume;
	///��Ч������: ������Ч
	req.TimeCondition = THOST_FTDC_TC_GFD;
	//req.TimeCondition = THOST_FTDC_TC_IOC;
	///GTD����
//	TThostFtdcDateType	GTDDate;
	///�ɽ�������: �κ�����
	req.VolumeCondition = THOST_FTDC_VC_AV;
	///��С�ɽ���: 1
	req.MinVolume = 1;
	///��������: ����
	req.ContingentCondition = THOST_FTDC_CC_Immediately;
	///ֹ���
//	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��: ��ǿƽ
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///�Զ������־: ��
	req.IsAutoSuspend = 0;
	///ҵ��Ԫ
//	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
//	TThostFtdcRequestIDType	RequestID;
	///�û�ǿ����־: ��
	req.UserForceClose = 0;

	lOrderTime=time(NULL);
	int iResult = pUserApi->ReqOrderInsert(&req, ++iRequestID);
	cerr << "--->>> ����¼������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,
								  CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspOrderInsert" << endl;
	//IsErrorRspInfo(pRspInfo);
}

//void CTraderSpi::ReqOrderAction(CThostFtdcOrderField *pOrder)
//{
//	static bool ORDER_ACTION_SENT = false;		//�Ƿ����˱���
//	if (ORDER_ACTION_SENT)
//		return;
//
//	CThostFtdcInputOrderActionField req;
//	memset(&req, 0, sizeof(req));
//	///���͹�˾����
//	strcpy(req.BrokerID, pOrder->BrokerID);
//	///Ͷ���ߴ���
//	strcpy(req.InvestorID, pOrder->InvestorID);
//	///������������
////	TThostFtdcOrderActionRefType	OrderActionRef;
//	///��������
//	strcpy(req.OrderRef, pOrder->OrderRef);
//	///������
////	TThostFtdcRequestIDType	RequestID;
//	///ǰ�ñ��
//	req.FrontID = FRONT_ID;
//	///�Ự���
//	req.SessionID = SESSION_ID;
//	///����������
////	TThostFtdcExchangeIDType	ExchangeID;
//	///�������
////	TThostFtdcOrderSysIDType	OrderSysID;
//	///������־
//	req.ActionFlag = THOST_FTDC_AF_Delete;
//	///�۸�
////	TThostFtdcPriceType	LimitPrice;
//	///�����仯
////	TThostFtdcVolumeType	VolumeChange;
//	///�û�����
////	TThostFtdcUserIDType	UserID;
//	///��Լ����
//	strcpy(req.InstrumentID, pOrder->InstrumentID);
//	lOrderTime=time(NULL);
//	int iResult = pUserApi->ReqOrderAction(&req, ++iRequestID);
//	cerr << "--->>> ������������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
//	ORDER_ACTION_SENT = true;
//}

//void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction,
//								  CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspOrderAction" << endl;
//	IsErrorRspInfo(pRspInfo);
//}

///����֪ͨ
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	cerr << "--->>> " << "OnRtnOrder"  << endl;
	lOrderOkTime=time(NULL);
	time_t lTime=lOrderOkTime-lOrderTime;
	cerr << "--->>> ����������֪ͨ��ʱ��� = " << lTime << endl;
	//if (IsMyOrder(pOrder))
	//{
	//	if (IsTradingOrder(pOrder))
	//	{
	//		//ReqOrderAction(pOrder);
	//	}
	//	else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
	//		cout << "--->>> �����ɹ�" << endl;
	//}

	static int nCount1 = 0;
	nCount1 = nCount1+1;
	cout << pOrder->OrderStatus << "����" << nCount1 << endl;
	if (pOrder->OrderStatus == '0')
	{
		static int nCount2 = 0;
		nCount2 = nCount2+1;
		cout << "ȫ���ɽ�" << nCount2 << endl;
	}
}

///�ɽ�֪ͨ
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	cerr << "--->>> " << "OnRtnTrade"  << endl;
	static int nCount3 = 0;
	nCount3 = nCount3+1;
	cout << "OnRtnTrade" << nCount3 << endl;
}

//void CTraderSpi:: OnFrontDisconnected(int nReason)
//{
//	cerr << "--->>> " << "OnFrontDisconnected" << endl;
//	cerr << "--->>> Reason = " << nReason << endl;
//}
		
//void CTraderSpi::OnHeartBeatWarning(int nTimeLapse)
//{
//	cerr << "--->>> " << "OnHeartBeatWarning" << endl;
//	cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
//}

//void CTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspError" << endl;
//	//IsErrorRspInfo(pRspInfo);
//}

//bool CTraderSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
//{
//	// ���ErrorID != 0, ˵���յ��˴������Ӧ
//	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
//	if (bResult)
//		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
//	return bResult;
//}

//bool CTraderSpi::IsMyOrder(CThostFtdcOrderField *pOrder)
//{
//	return ((pOrder->FrontID == FRONT_ID) &&
//			(pOrder->SessionID == SESSION_ID) &&
//			(strcmp(pOrder->OrderRef, ORDER_REF) == 0));
//}

//bool CTraderSpi::IsTradingOrder(CThostFtdcOrderField *pOrder)
//{
//	return ((pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing) &&
//			(pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
//			(pOrder->OrderStatus != THOST_FTDC_OST_AllTraded));
//}
