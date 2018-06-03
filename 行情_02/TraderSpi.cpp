#include <iostream>
using namespace std;

#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "MdSpi.h"

#include <time.h>
#include <windows.h>


#pragma warning(disable : 4996)

extern HANDLE g_hEvent;

// USER_API参数
extern CThostFtdcMdApi* pUserApi;

// 配置参数
extern char FRONT_ADDR[];		// 前置地址
extern char BROKER_ID[];		// 经纪公司代码
extern char INVESTOR_ID[];		// 投资者代码
extern char PASSWORD[];			// 用户密码
extern char INSTRUMENT_ID[];	// 合约代码

extern char *ppInstrumentID[];		
extern int iInstrumentID;									


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
void CMdSpi::OnFrontConnected()
{
	cerr << "--->>> " << "OnFrontConnected" << endl;
	cerr<< "与服务器已建立连接, 开始登录" <<endl; 
	///用户登录请求
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
	cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
							CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		cerr << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay() << endl;
		// 请求订阅行情
		SubscribeMarketData();	

	}
}

void CMdSpi::SubscribeMarketData()
{
	int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
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
	cerr << pDepthMarketData->InstrumentID <<" 最新价: " << pDepthMarketData->LastPrice << ";" << endl;
	cerr << pDepthMarketData->InstrumentID <<" 涨停价: " << pDepthMarketData->UpperLimitPrice << ";" << endl;
	cerr << pDepthMarketData->InstrumentID <<" 跌停价: " << pDepthMarketData->LowerLimitPrice << ";" << endl;


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
	{ SetEvent(g_hEvent); } // 退出线程
}


bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
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
//	cerr << "--->>> 投资者结算结果确认: " << ((iResult == 0) ? "成功" : "失败") << endl;
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
//		///请求查询合约
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
//	cerr << "--->>> 请求查询合约: " << ((iResult == 0) ? "成功" : "失败") << endl;
//}
//
//void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, 
//									CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspQryInstrument" << endl;
//
//	if (bIsLast && !IsErrorRspInfo(pRspInfo))
//	{
//		///请求查询账户资金
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
//	cerr << "--->>> 请求查询资金账户: " << ((iResult == 0) ? "成功" : "失败") << endl;
//}
//
//void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, 
//										CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspQryTradingAccount" << endl;
//	cerr << "--->>> 账户资金: "<< pTradingAccount->Balance << ";" << endl;
//	if (bIsLast && !IsErrorRspInfo(pRspInfo))
//	{
//		///请求查询投资者持仓
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
//	cerr << "--->>> 请求查询投资者持仓: " << ((iResult == 0) ? "成功" : "失败") << endl;
//}
//
//void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, 
//										  CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
//{
//	cerr << "--->>> " << "OnRspQryInvestorPosition" << endl;
//	if (bIsLast && !IsErrorRspInfo(pRspInfo))
//	{
//		cerr << "--->>> 持仓手数: " << pInvestorPosition->Position << ";" <<endl;
//		cerr << "--->>> 持仓方向: " << pInvestorPosition->PosiDirection << ";" << endl;
//		SetEvent(g_hEvent);
//	}
//}


//void CTraderSpi::ReqOrderInsert()
//{
//	CThostFtdcInputOrderField req;
//	memset(&req, 0, sizeof(req));
//	///经纪公司代码
//	strcpy(req.BrokerID, BROKER_ID);
//	///投资者代码
//	strcpy(req.InvestorID, INVESTOR_ID);
//	///合约代码
//	strcpy(req.InstrumentID, INSTRUMENT_ID);
//	///报单引用
//	strcpy(req.OrderRef, ORDER_REF);
//	///用户代码
//
////	TThostFtdcUserIDType	UserID;
//
//	///报单价格条件: 限价
//	//req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
//	//req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;
//	req.OrderPriceType = PriceType;
//
//	///买卖方向: 
//	req.Direction = DIRECTION;
//
//	///组合开平标志: 开仓/平仓
//	//req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
//	//req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
//	req.CombOffsetFlag[0] = CombOffsetFlagType[0];
//
//	///组合投机套保标志
//	/*req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;*/
//	req.CombHedgeFlag[0] = CombHedgeFlag[0];
//
//	///价格
//	req.LimitPrice = LIMIT_PRICE;
//
//	///数量: 1
//	req.VolumeTotalOriginal = Volume;
//
//	///有效期类型: 当日有效
//	//req.TimeCondition = THOST_FTDC_TC_GFD;
//	//req.TimeCondition = THOST_FTDC_TC_IOC;
//	req.TimeCondition = TimeCondition;
//
//	///GTD日期
////	TThostFtdcDateType	GTDDate;
//
//	///成交量类型: 任何数量
//	//req.VolumeCondition = THOST_FTDC_VC_AV;
//	req.VolumeCondition = VolumeCondition;
//
//	///最小成交量: 1
//	//req.MinVolume = 1;
//	req.MinVolume = MinVolume;
//
//	///触发条件: 立即
//	//req.ContingentCondition = THOST_FTDC_CC_Immediately;
//	req.ContingentCondition = ContingentCondition;
//
//	///止损价
////	TThostFtdcPriceType	StopPrice;
//
//	///强平原因: 非强平
//	//req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
//	req.ForceCloseReason = ForceCloseReason;
//
//	///自动挂起标志: 否
//	//req.IsAutoSuspend = 0;
//	req.IsAutoSuspend = IsAutoSuspend;
//
//	///业务单元
////	TThostFtdcBusinessUnitType	BusinessUnit;
//
//	///请求编号
////	TThostFtdcRequestIDType	RequestID;
//
//	///用户强评标志: 否
//	//req.UserForceClose = 0;
//	req.UserForceClose = UserForceClose;
//
//
//	lOrderTime=time(NULL);
//	int iResult = pUserApi->ReqOrderInsert(&req, ++iRequestID);
//	cerr << "--->>> 报单录入请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
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
////	static bool ORDER_ACTION_SENT = false;		//是否发送了报单
////	if (ORDER_ACTION_SENT)
////		return;
////
////	CThostFtdcInputOrderActionField req;
////	memset(&req, 0, sizeof(req));
////	///经纪公司代码
////	strcpy(req.BrokerID, pOrder->BrokerID);
////	///投资者代码
////	strcpy(req.InvestorID, pOrder->InvestorID);
////	///报单操作引用
//////	TThostFtdcOrderActionRefType	OrderActionRef;
////	///报单引用
////	strcpy(req.OrderRef, pOrder->OrderRef);
////	///请求编号
//////	TThostFtdcRequestIDType	RequestID;
////	///前置编号
////	req.FrontID = FRONT_ID;
////	///会话编号
////	req.SessionID = SESSION_ID;
////	///交易所代码
//////	TThostFtdcExchangeIDType	ExchangeID;
////	///报单编号
//////	TThostFtdcOrderSysIDType	OrderSysID;
////	///操作标志
////	req.ActionFlag = THOST_FTDC_AF_Delete;
////	///价格
//////	TThostFtdcPriceType	LimitPrice;
////	///数量变化
//////	TThostFtdcVolumeType	VolumeChange;
////	///用户代码
//////	TThostFtdcUserIDType	UserID;
////	///合约代码
////	strcpy(req.InstrumentID, pOrder->InstrumentID);
////	lOrderTime=time(NULL);
////	int iResult = pUserApi->ReqOrderAction(&req, ++iRequestID);
////	cerr << "--->>> 报单操作请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
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
/////报单通知
//void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
//{
//	cerr << "--->>> " << "OnRtnOrder"  << endl;
//	lOrderOkTime=time(NULL);
//	time_t lTime=lOrderOkTime-lOrderTime;
//	cerr << "--->>> 报单到报单通知的时间差 = " << lTime << endl;
//	//if (IsMyOrder(pOrder))
//	//{
//	//	if (IsTradingOrder(pOrder))
//	//	{
//	//		//ReqOrderAction(pOrder);
//	//	}
//	//	else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
//	//		cout << "--->>> 撤单成功" << endl;
//	//}
//
//	//static int nCount1 = 0;
//	//nCount1 = nCount1+1;
//	//cout << pOrder->OrderStatus << "次数" << nCount1 << endl;
//	if (pOrder->OrderStatus == '0')
//	{
//		//static int nCount2 = 0;
//		//nCount2 = nCount2+1;
//		cout << "全部成交" << endl;
//	}
//}
//
/////成交通知
//void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
//{
//	cerr << "--->>> " << "OnRtnTrade"  << endl;
//	//static int nCount3 = 0;
//	//nCount3 = nCount3+1;
//	//cout << "OnRtnTrade" << nCount3 << endl;
//}


