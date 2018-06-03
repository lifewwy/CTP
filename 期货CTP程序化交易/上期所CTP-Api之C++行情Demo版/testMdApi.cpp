// testTraderApi.cpp : 定义控制台应用程序的入口点。
//

#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "MdSpi.h"

// UserApi对象
CThostFtdcMdApi* pUserApi;

//char  FRONT_ADDR[] = "tcp://180.168.146.187:10031";   // 前置地址       simnow仿真
//TThostFtdcBrokerIDType	BROKER_ID = "9999";		    // 经纪公司代码   simnow仿真
//TThostFtdcInvestorIDType INVESTOR_ID = "101024";		// 注意这里输入你自己的投资者代码
//TThostFtdcPasswordType  PASSWORD = "518888";			// 注意这里输入你自己的用户密码

char  FRONT_ADDR[] = "tcp://116.228.171.216:41213";	    // 前置地址       新湖期货-快期 测试成功
TThostFtdcBrokerIDType	BROKER_ID = "6090";				// 经纪公司代码   新湖期货-快期 测试成功
TThostFtdcInvestorIDType INVESTOR_ID = "10501951";	    // 注意输入你自己的投资者代码
TThostFtdcPasswordType  PASSWORD = "518888";			// 注意输入你自己的用户密码

/*
char  FRONT_ADDR[] = "tcp://61.152.165.100:41211";		// 前置地址       国贸期货-快期 测试成功
TThostFtdcBrokerIDType	BROKER_ID = "0187";				// 经纪公司代码   国贸期货-快期 测试成功
TThostFtdcInvestorIDType INVESTOR_ID = "28006311";	    // 注意输入你自己的simnow仿真投资者代码
TThostFtdcPasswordType  PASSWORD = "518888";			// 注意输入你自己的simnow仿真用户密码*/


char *ppInstrumentID[] = {"m1801", "rb1801"};			// 行情订阅列表，注意，这个合约ID会过时的，注意与时俱进修改
int iInstrumentID = 2;									// 行情订阅数量


// 请求编号
int iRequestID = 0;

void main(void)
{
	// 初始化UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();

	pUserApi->Join();
//	pUserApi->Release();
}