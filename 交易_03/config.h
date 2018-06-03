#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include "TraderSpi.h"

//char  FRONT_ADDR[] = "tcp://180.168.146.187:10000";   // 前置地址
char  FRONT_ADDR[] = "tcp://180.168.146.187:10030";   // 前置地址
TThostFtdcBrokerIDType	BROKER_ID = "9999";		    // 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "101042";	    // 注意输入你自己的simnow仿真投资者代码
TThostFtdcPasswordType  PASSWORD = "518888";			// 注意输入你自己的simnow仿真用户密码

//char  FRONT_ADDR[] = "tcp://61.152.165.100:41201";	    // 前置地址       国贸期货-快期 测试成功
//TThostFtdcBrokerIDType	BROKER_ID = "0187";				// 经纪公司代码   国贸期货-快期 测试成功
//TThostFtdcInvestorIDType INVESTOR_ID = "28006311";	    // 注意输入你自己的投资者代码
//TThostFtdcPasswordType  PASSWORD = "518888";			// 注意输入你自己的用户密码


//char  FRONT_ADDR[] = "tcp://116.228.171.216:41205";		// 前置地址      新湖期货-快期 测试成功
//TThostFtdcBrokerIDType	BROKER_ID = "6090";				// 经纪公司代码  新湖期货-快期 测试成功 
//TThostFtdcInvestorIDType INVESTOR_ID = "10501951";	    // 注意输入你自己的投资者代码
//TThostFtdcPasswordType  PASSWORD = "202031";			// 注意输入你自己的用户密码


// 合约代码 ，注意与时俱进改变合约ID,避免使用过时合约
//TThostFtdcInstrumentIDType INSTRUMENT_ID = "MA801";	 
TThostFtdcInstrumentIDType INSTRUMENT_ID = "TA801";


// 买卖方向
TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Buy;	
//TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	

// 开仓/平仓
TThostFtdcCombOffsetFlagType CombOffsetFlagType = {THOST_FTDC_OF_Open};

// 价格
//TThostFtdcPriceType	LIMIT_PRICE = 2900;		
TThostFtdcPriceType	LIMIT_PRICE = 5450;

// 手数
TThostFtdcVolumeMultipleType Volume = 1;                

TThostFtdcOrderPriceTypeType PriceType = THOST_FTDC_OPT_LimitPrice;

TThostFtdcCombHedgeFlagType CombHedgeFlag = {THOST_FTDC_HF_Speculation};

TThostFtdcTimeConditionType TimeCondition = THOST_FTDC_TC_GFD;

TThostFtdcVolumeConditionType VolumeCondition = THOST_FTDC_VC_AV;

TThostFtdcContingentConditionType ContingentCondition = THOST_FTDC_CC_Immediately;

TThostFtdcForceCloseReasonType ForceCloseReason = THOST_FTDC_FCC_NotForceClose;

int MinVolume = 1;
int IsAutoSuspend = 0;
int UserForceClose = 0;

//	TThostFtdcUserIDType	UserID;
///报单价格条件: 限价
//req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
//req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;

///买卖方向: 
//req.Direction = DIRECTION;

///组合开平标志: 开仓/平仓
//req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
//req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;

///组合投机套保标志
//req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;

///价格
//req.LimitPrice = LIMIT_PRICE;

///数量: 1
//req.VolumeTotalOriginal = Volume;

///有效期类型: 当日有效
//req.TimeCondition = THOST_FTDC_TC_GFD;
//req.TimeCondition = THOST_FTDC_TC_IOC;

///GTD日期
//	TThostFtdcDateType	GTDDate;

///成交量类型: 任何数量
//req.VolumeCondition = THOST_FTDC_VC_AV;

///最小成交量: 1
//req.MinVolume = 1;

///触发条件: 立即
//req.ContingentCondition = THOST_FTDC_CC_Immediately;

///止损价
//	TThostFtdcPriceType	StopPrice;

///强平原因: 非强平
//req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;

///自动挂起标志: 否
//req.IsAutoSuspend = 0;

///业务单元
//	TThostFtdcBusinessUnitType	BusinessUnit;
///请求编号
//	TThostFtdcRequestIDType	RequestID;

///用户强评标志: 否
//req.UserForceClose = 0;