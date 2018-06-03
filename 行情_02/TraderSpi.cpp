#include <iostream>
using namespace std;

#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "MdSpi.h"

#include <time.h>
#include <windows.h>


#pragma warning(disable : 4996)

extern HANDLE g_hEvent;

// USER_API����
extern CThostFtdcMdApi* pUserApi;

// ���ò���
extern char FRONT_ADDR[];		// ǰ�õ�ַ
extern char BROKER_ID[];		// ���͹�˾����
extern char INVESTOR_ID[];		// Ͷ���ߴ���
extern char PASSWORD[];			// �û�����
extern char INSTRUMENT_ID[];	// ��Լ����

extern char *ppInstrumentID[];		
extern int iInstrumentID;									


extern TThostFtdcPriceType	LIMIT_PRICE;	// �۸�
extern TThostFtdcDirectionType	DIRECTION;	// ��������
extern TThostFtdcVolumeMultipleType Volume;

extern TThostFtdcOrderPriceTypeType PriceType;
extern TThostFtdcTimeConditionType TimeCondition;
extern TThostFtdcVolumeConditionType VolumeCondition;
extern int MinVolume;
extern TThostFtdcContingentConditionType ContingentCondition;
extern TThostFtdcForceCloseReasonType ForceCloseReason;
extern int IsAutoSuspend;
extern int UserForceClose;
extern TThostFtdcCombOffsetFlagType CombOffsetFlagType;
extern TThostFtdcCombHedgeFlagType CombHedgeFlag;

// ������
extern int iRequestID;

// �Ự����
TThostFtdcFrontIDType	FRONT_ID;	//ǰ�ñ��
TThostFtdcSessionIDType	SESSION_ID;	//�Ự���
TThostFtdcOrderRefType	ORDER_REF;	//��������
time_t lOrderTime;
time_t lOrderOkTime;
void CMdSpi::OnFrontConnected()
{
	cerr << "--->>> " << "OnFrontConnected" << endl;
	cerr<< "��������ѽ�������, ��ʼ��¼" <<endl; 
	///�û���¼����
	ReqUserLogin();
}


void CMdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.UserID, INVESTOR_ID);
	strcpy(req.Password, PASSWORD);
	int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
	cerr << "--->>> �����û���¼����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
							CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///��ȡ��ǰ������
		cerr << "--->>> ��ȡ��ǰ������ = " << pUserApi->GetTradingDay() << endl;
		// ����������
		SubscribeMarketData();	

	}
}

void CMdSpi::SubscribeMarketData()
{
	int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> �������鶩������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}

//void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << __FUNCTION__ << endl;
//}

using namespace std;
#include <iostream>
#include <fstream>
#include <string>

void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{

	//cerr << __FUNCTION__ << endl;
	cerr << pDepthMarketData->InstrumentID <<" ���¼�: " << pDepthMarketData->LastPrice << ";" << endl;
	cerr << pDepthMarketData->InstrumentID <<" ��ͣ��: " << pDepthMarketData->UpperLimitPrice << ";" << endl;
	cerr << pDepthMarketData->InstrumentID <<" ��ͣ��: " << pDepthMarketData->LowerLimitPrice << ";" << endl;


	//// string s = "D:\\" ;
	//string s = "..//..//" ; // wwy
	//s.append(pDepthMarketData->InstrumentID);
	//s.append(".csv");
	//ofstream outfile;
	//outfile.open(s, ios::app);
	//outfile << pDepthMarketData->InstrumentID<<","<< pDepthMarketData->UpdateTime
	//	<<"."<< pDepthMarketData->UpdateMillisec<<","<< pDepthMarketData->LastPrice
	//	<< "," << pDepthMarketData-> Volume << "," << pDepthMarketData-> BidPrice1 
	//	<< "," << pDepthMarketData-> BidVolume1 << "," << pDepthMarketData-> AskPrice1 
	//	<< "," << pDepthMarketData-> AskVolume1 << "," << pDepthMarketData-> OpenInterest
	//	<< "," << pDepthMarketData->Turnover<< endl;
	//outfile.close();

	static int nCount = 0; 	nCount = nCount+1;
	if (nCount == iInstrumentID)
	{ SetEvent(g_hEvent); } // �˳��߳�
}


bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}

//void CTraderSpi::ReqSettlementInfoConfirm()
//{
//	CThostFtdcSettlementInfoConfirmField req;
//	memset(&req, 0, sizeof(req));
//	strcpy(req.BrokerID, BROKER_ID);
//	strcpy(req.InvestorID, INVESTOR_ID);
//	int iResult = pUserApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
//	cerr << "--->>> Ͷ���߽�����ȷ��: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
//}
//
//void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
//											CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspSettlementInfoConfirm" << endl;
//
//	ReqQryInstrument();	
//	if (bIsLast && !IsErrorRspInfo(pRspInfo))
//	{
//		///�����ѯ��Լ
//		
//	}
//}
//
//void CTraderSpi::ReqQryInstrument()
//{
//	CThostFtdcQryInstrumentField req;
//	memset(&req, 0, sizeof(req));
//	strcpy(req.InstrumentID, INSTRUMENT_ID);
//	int iResult = pUserApi->ReqQryInstrument(&req, ++iRequestID);
//	cerr << "--->>> �����ѯ��Լ: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
//}
//
//void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, 
//									CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspQryInstrument" << endl;
//
//	if (bIsLast && !IsErrorRspInfo(pRspInfo))
//	{
//		///�����ѯ�˻��ʽ�
//		ReqQryTradingAccount();
//	}
//}
//
//void CTraderSpi::ReqQryTradingAccount()
//{
//	CThostFtdcQryTradingAccountField req;
//	memset(&req, 0, sizeof(req));
//	strcpy(req.BrokerID, BROKER_ID);
//	strcpy(req.InvestorID, INVESTOR_ID);
//	int iResult = pUserApi->ReqQryTradingAccount(&req, ++iRequestID);
//	cerr << "--->>> �����ѯ�ʽ��˻�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
//}
//
//void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, 
//										CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspQryTradingAccount" << endl;
//	cerr << "--->>> �˻��ʽ�: "<< pTradingAccount->Balance << ";" << endl;
//	if (bIsLast && !IsErrorRspInfo(pRspInfo))
//	{
//		///�����ѯͶ���ֲ߳�
//		ReqQryInvestorPosition();
//	}
//}
//
//void CTraderSpi::ReqQryInvestorPosition()
//{
//	CThostFtdcQryInvestorPositionField req;
//	memset(&req, 0, sizeof(req));
//	strcpy(req.BrokerID, BROKER_ID);
//	strcpy(req.InvestorID, INVESTOR_ID);
//	strcpy(req.InstrumentID, INSTRUMENT_ID);
//	int iResult = pUserApi->ReqQryInvestorPosition(&req, ++iRequestID);
//	cerr << "--->>> �����ѯͶ���ֲ߳�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
//}
//
//void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, 
//										  CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspQryInvestorPosition" << endl;
//	if (bIsLast && !IsErrorRspInfo(pRspInfo))
//	{
//		cerr << "--->>> �ֲ�����: " << pInvestorPosition->Position << ";" <<endl;
//		cerr << "--->>> �ֲַ���: " << pInvestorPosition->PosiDirection << ";" << endl;
//		SetEvent(g_hEvent);
//	}
//}


//void CTraderSpi::ReqOrderInsert()
//{
//	CThostFtdcInputOrderField req;
//	memset(&req, 0, sizeof(req));
//	///���͹�˾����
//	strcpy(req.BrokerID, BROKER_ID);
//	///Ͷ���ߴ���
//	strcpy(req.InvestorID, INVESTOR_ID);
//	///��Լ����
//	strcpy(req.InstrumentID, INSTRUMENT_ID);
//	///��������
//	strcpy(req.OrderRef, ORDER_REF);
//	///�û�����
//
////	TThostFtdcUserIDType	UserID;
//
//	///�����۸�����: �޼�
//	//req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
//	//req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
//	req.OrderPriceType = PriceType;
//
//	///��������: 
//	req.Direction = DIRECTION;
//
//	///��Ͽ�ƽ��־: ����/ƽ��
//	//req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
//	//req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
//	req.CombOffsetFlag[0] = CombOffsetFlagType[0];
//
//	///���Ͷ���ױ���־
//	/*req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;*/
//	req.CombHedgeFlag[0] = CombHedgeFlag[0];
//
//	///�۸�
//	req.LimitPrice = LIMIT_PRICE;
//
//	///����: 1
//	req.VolumeTotalOriginal = Volume;
//
//	///��Ч������: ������Ч
//	//req.TimeCondition = THOST_FTDC_TC_GFD;
//	//req.TimeCondition = THOST_FTDC_TC_IOC;
//	req.TimeCondition = TimeCondition;
//
//	///GTD����
////	TThostFtdcDateType	GTDDate;
//
//	///�ɽ�������: �κ�����
//	//req.VolumeCondition = THOST_FTDC_VC_AV;
//	req.VolumeCondition = VolumeCondition;
//
//	///��С�ɽ���: 1
//	//req.MinVolume = 1;
//	req.MinVolume = MinVolume;
//
//	///��������: ����
//	//req.ContingentCondition = THOST_FTDC_CC_Immediately;
//	req.ContingentCondition = ContingentCondition;
//
//	///ֹ���
////	TThostFtdcPriceType	StopPrice;
//
//	///ǿƽԭ��: ��ǿƽ
//	//req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
//	req.ForceCloseReason = ForceCloseReason;
//
//	///�Զ������־: ��
//	//req.IsAutoSuspend = 0;
//	req.IsAutoSuspend = IsAutoSuspend;
//
//	///ҵ��Ԫ
////	TThostFtdcBusinessUnitType	BusinessUnit;
//
//	///������
////	TThostFtdcRequestIDType	RequestID;
//
//	///�û�ǿ����־: ��
//	//req.UserForceClose = 0;
//	req.UserForceClose = UserForceClose;
//
//
//	lOrderTime=time(NULL);
//	int iResult = pUserApi->ReqOrderInsert(&req, ++iRequestID);
//	cerr << "--->>> ����¼������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
//}
//
//void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,
//								  CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspOrderInsert" << endl;
//	//IsErrorRspInfo(pRspInfo);
//}
//
////void CTraderSpi::ReqOrderAction(CThostFtdcOrderField *pOrder)
////{
////	static bool ORDER_ACTION_SENT = false;		//�Ƿ����˱���
////	if (ORDER_ACTION_SENT)
////		return;
////
////	CThostFtdcInputOrderActionField req;
////	memset(&req, 0, sizeof(req));
////	///���͹�˾����
////	strcpy(req.BrokerID, pOrder->BrokerID);
////	///Ͷ���ߴ���
////	strcpy(req.InvestorID, pOrder->InvestorID);
////	///������������
//////	TThostFtdcOrderActionRefType	OrderActionRef;
////	///��������
////	strcpy(req.OrderRef, pOrder->OrderRef);
////	///������
//////	TThostFtdcRequestIDType	RequestID;
////	///ǰ�ñ��
////	req.FrontID = FRONT_ID;
////	///�Ự���
////	req.SessionID = SESSION_ID;
////	///����������
//////	TThostFtdcExchangeIDType	ExchangeID;
////	///�������
//////	TThostFtdcOrderSysIDType	OrderSysID;
////	///������־
////	req.ActionFlag = THOST_FTDC_AF_Delete;
////	///�۸�
//////	TThostFtdcPriceType	LimitPrice;
////	///�����仯
//////	TThostFtdcVolumeType	VolumeChange;
////	///�û�����
//////	TThostFtdcUserIDType	UserID;
////	///��Լ����
////	strcpy(req.InstrumentID, pOrder->InstrumentID);
////	lOrderTime=time(NULL);
////	int iResult = pUserApi->ReqOrderAction(&req, ++iRequestID);
////	cerr << "--->>> ������������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
////	ORDER_ACTION_SENT = true;
////}
//
////void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction,
////								  CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
////{
////	cerr << "--->>> " << "OnRspOrderAction" << endl;
////	IsErrorRspInfo(pRspInfo);
////}
//
/////����֪ͨ
//void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
//{
//	cerr << "--->>> " << "OnRtnOrder"  << endl;
//	lOrderOkTime=time(NULL);
//	time_t lTime=lOrderOkTime-lOrderTime;
//	cerr << "--->>> ����������֪ͨ��ʱ��� = " << lTime << endl;
//	//if (IsMyOrder(pOrder))
//	//{
//	//	if (IsTradingOrder(pOrder))
//	//	{
//	//		//ReqOrderAction(pOrder);
//	//	}
//	//	else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
//	//		cout << "--->>> �����ɹ�" << endl;
//	//}
//
//	//static int nCount1 = 0;
//	//nCount1 = nCount1+1;
//	//cout << pOrder->OrderStatus << "����" << nCount1 << endl;
//	if (pOrder->OrderStatus == '0')
//	{
//		//static int nCount2 = 0;
//		//nCount2 = nCount2+1;
//		cout << "ȫ���ɽ�" << endl;
//	}
//}
//
/////�ɽ�֪ͨ
//void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
//{
//	cerr << "--->>> " << "OnRtnTrade"  << endl;
//	//static int nCount3 = 0;
//	//nCount3 = nCount3+1;
//	//cout << "OnRtnTrade" << nCount3 << endl;
//}


