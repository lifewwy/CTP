#include <iostream>
using namespace std;

#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include "TraderSpi.h"
#include <time.h>
#include <windows.h>

#pragma warning(disable : 4996)

extern HANDLE g_hEvent;

// USER_API参数
extern CThostFtdcTraderApi* pUserApi;

// 配置参数
extern char FRONT_ADDR[];		// 前置地址
extern char BROKER_ID[];		// 经纪公司代码
extern char INVESTOR_ID[];		// 投资者代码
extern char PASSWORD[];			// 用户密码
extern char INSTRUMENT_ID[];	// 合约代码


extern TThostFtdcPriceType	LIMIT_PRICE;	// 价格
extern TThostFtdcDirectionType	DIRECTION;	// 买卖方向
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

// 请求编号
extern int iRequestID;

// 会话参数
TThostFtdcFrontIDType	FRONT_ID;	//前置编号
TThostFtdcSessionIDType	SESSION_ID;	//会话编号
TThostFtdcOrderRefType	ORDER_REF;	//报单引用
time_t lOrderTime;
time_t lOrderOkTime;
void CTraderSpi::OnFrontConnected()
{
	cerr << "--->>> " << "OnFrontConnected" << endl;
	cerr<< "与服务器已建立连接, 开始登录" <<endl; 
	///用户登录请求
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
	cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspUserLogin" << endl;
	//if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		// 保存会话参数
		FRONT_ID = pRspUserLogin->FrontID;
		SESSION_ID = pRspUserLogin->SessionID;
		int iNextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
		iNextOrderRef++;
		sprintf(ORDER_REF, "%d", iNextOrderRef);
		//获取当前交易日
		cerr << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay() << endl;
		//投资者结算结果确认
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
	cerr << "--->>> 投资者结算结果确认: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
											CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspSettlementInfoConfirm" << endl;

	//if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///请求查询合约
		//ReqQryInstrument();

		///报单录入请求
		
	}

	ReqOrderInsert();
}


void CTraderSpi::ReqOrderInsert()
{
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, BROKER_ID);
	///投资者代码
	strcpy(req.InvestorID, INVESTOR_ID);
	///合约代码
	strcpy(req.InstrumentID, INSTRUMENT_ID);
	///报单引用
	strcpy(req.OrderRef, ORDER_REF);
	///用户代码

//	TThostFtdcUserIDType	UserID;

	///报单价格条件: 限价
	//req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	//req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
	req.OrderPriceType = PriceType;

	///买卖方向: 
	req.Direction = DIRECTION;

	///组合开平标志: 开仓/平仓
	//req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	//req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
	req.CombOffsetFlag[0] = CombOffsetFlagType[0];

	///组合投机套保标志
	/*req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;*/
	req.CombHedgeFlag[0] = CombHedgeFlag[0];

	///价格
	req.LimitPrice = LIMIT_PRICE;

	///数量: 1
	req.VolumeTotalOriginal = Volume;

	///有效期类型: 当日有效
	//req.TimeCondition = THOST_FTDC_TC_GFD;
	//req.TimeCondition = THOST_FTDC_TC_IOC;
	req.TimeCondition = TimeCondition;

	///GTD日期
//	TThostFtdcDateType	GTDDate;

	///成交量类型: 任何数量
	//req.VolumeCondition = THOST_FTDC_VC_AV;
	req.VolumeCondition = VolumeCondition;

	///最小成交量: 1
	//req.MinVolume = 1;
	req.MinVolume = MinVolume;

	///触发条件: 立即
	//req.ContingentCondition = THOST_FTDC_CC_Immediately;
	req.ContingentCondition = ContingentCondition;

	///止损价
//	TThostFtdcPriceType	StopPrice;

	///强平原因: 非强平
	//req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	req.ForceCloseReason = ForceCloseReason;

	///自动挂起标志: 否
	//req.IsAutoSuspend = 0;
	req.IsAutoSuspend = IsAutoSuspend;

	///业务单元
//	TThostFtdcBusinessUnitType	BusinessUnit;

	///请求编号
//	TThostFtdcRequestIDType	RequestID;

	///用户强评标志: 否
	//req.UserForceClose = 0;
	req.UserForceClose = UserForceClose;


	lOrderTime=time(NULL);
	int iResult = pUserApi->ReqOrderInsert(&req, ++iRequestID);
	cerr << "--->>> 报单录入请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,
								  CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspOrderInsert" << endl;
	//IsErrorRspInfo(pRspInfo);
}

//void CTraderSpi::ReqOrderAction(CThostFtdcOrderField *pOrder)
//{
//	static bool ORDER_ACTION_SENT = false;		//是否发送了报单
//	if (ORDER_ACTION_SENT)
//		return;
//
//	CThostFtdcInputOrderActionField req;
//	memset(&req, 0, sizeof(req));
//	///经纪公司代码
//	strcpy(req.BrokerID, pOrder->BrokerID);
//	///投资者代码
//	strcpy(req.InvestorID, pOrder->InvestorID);
//	///报单操作引用
////	TThostFtdcOrderActionRefType	OrderActionRef;
//	///报单引用
//	strcpy(req.OrderRef, pOrder->OrderRef);
//	///请求编号
////	TThostFtdcRequestIDType	RequestID;
//	///前置编号
//	req.FrontID = FRONT_ID;
//	///会话编号
//	req.SessionID = SESSION_ID;
//	///交易所代码
////	TThostFtdcExchangeIDType	ExchangeID;
//	///报单编号
////	TThostFtdcOrderSysIDType	OrderSysID;
//	///操作标志
//	req.ActionFlag = THOST_FTDC_AF_Delete;
//	///价格
////	TThostFtdcPriceType	LimitPrice;
//	///数量变化
////	TThostFtdcVolumeType	VolumeChange;
//	///用户代码
////	TThostFtdcUserIDType	UserID;
//	///合约代码
//	strcpy(req.InstrumentID, pOrder->InstrumentID);
//	lOrderTime=time(NULL);
//	int iResult = pUserApi->ReqOrderAction(&req, ++iRequestID);
//	cerr << "--->>> 报单操作请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
//	ORDER_ACTION_SENT = true;
//}

//void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction,
//								  CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspOrderAction" << endl;
//	IsErrorRspInfo(pRspInfo);
//}

///报单通知
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	cerr << "--->>> " << "OnRtnOrder"  << endl;
	lOrderOkTime=time(NULL);
	time_t lTime=lOrderOkTime-lOrderTime;
	cerr << "--->>> 报单到报单通知的时间差 = " << lTime << endl;
	//if (IsMyOrder(pOrder))
	//{
	//	if (IsTradingOrder(pOrder))
	//	{
	//		//ReqOrderAction(pOrder);
	//	}
	//	else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
	//		cout << "--->>> 撤单成功" << endl;
	//}

	//static int nCount1 = 0;
	//nCount1 = nCount1+1;
	//cout << pOrder->OrderStatus << "次数" << nCount1 << endl;
	if (pOrder->OrderStatus == THOST_FTDC_OST_AllTraded)
	{
		//static int nCount2 = 0;
		//nCount2 = nCount2+1;
		cout << "全部成交" << endl;
		Sleep(500);
		SetEvent(g_hEvent);

	}
}

///成交通知
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	cerr << "--->>> " << "OnRtnTrade"  << endl;
	cerr << "--->>>成交价格 " << pTrade->Price  << endl;
	cerr << "--->>>成交手数 " << pTrade->Volume  << endl;

	//SetEvent(g_hEvent);

	//pTrade->Price;  // 成交价格
	//pTrade->Volume; // 成交手数

	static int TotalTradedValume = 0;
	TotalTradedValume = TotalTradedValume + pTrade->Volume;
	cerr << "总成交手数 " << TotalTradedValume  << endl;
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
//	// 如果ErrorID != 0, 说明收到了错误的响应
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
