#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include "MdSpi.h"

//char *ppInstrumentID[] = {"m1801", "rb1801"};		    // ���鶩���б�ע�⣬�����ԼID���ʱ�ģ�ע����ʱ����޸�
char *ppInstrumentID[30];                           	// ���鶩���б�ע�⣬�����ԼID���ʱ�ģ�ע����ʱ����޸�
int iInstrumentID = 2;									// ���鶩������

//char  FRONT_ADDR[] = "tcp://61.152.165.100:41211";		// ǰ�õ�ַ       ��ó�ڻ�-���� ���Գɹ�
//TThostFtdcBrokerIDType	BROKER_ID = "0187";				// ���͹�˾����   ��ó�ڻ�-���� ���Գɹ�
//TThostFtdcInvestorIDType INVESTOR_ID = "28006311";	    // ע���������Լ���simnow����Ͷ���ߴ���
//TThostFtdcPasswordType  PASSWORD = "518888";			// ע���������Լ���simnow�����û�����

char  FRONT_ADDR[] = "tcp://180.168.146.187:10031";   // ǰ�õ�ַ       simnow����
TThostFtdcBrokerIDType	BROKER_ID = "9999";		    // ���͹�˾����   simnow����
TThostFtdcInvestorIDType INVESTOR_ID = "101024";		// ע�������������Լ���Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD = "518888";			// ע�������������Լ����û�����

// ��Լ���� ��ע����ʱ����ı��ԼID,����ʹ�ù�ʱ��Լ
//TThostFtdcInstrumentIDType INSTRUMENT_ID = "MA801";	 
//TThostFtdcInstrumentIDType INSTRUMENT_ID = "TA801";	 


// ��������
//TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Buy;	
//TThostFtdcDirectionType	DIRECTION = THOST_FTDC_D_Sell;	

// ����/ƽ��
//TThostFtdcCombOffsetFlagType CombOffsetFlagType = {THOST_FTDC_OF_Open};

// �۸�
//TThostFtdcPriceType	LIMIT_PRICE = 5400;				    

// ����
//TThostFtdcVolumeMultipleType Volume = 5;                

//TThostFtdcOrderPriceTypeType PriceType = THOST_FTDC_OPT_LimitPrice;

//TThostFtdcCombHedgeFlagType CombHedgeFlag = {THOST_FTDC_HF_Speculation};

//TThostFtdcTimeConditionType TimeCondition = THOST_FTDC_TC_GFD;

//TThostFtdcVolumeConditionType VolumeCondition = THOST_FTDC_VC_AV;

//TThostFtdcContingentConditionType ContingentCondition = THOST_FTDC_CC_Immediately;

//TThostFtdcForceCloseReasonType ForceCloseReason = THOST_FTDC_FCC_NotForceClose;

//int MinVolume = 1;
//int IsAutoSuspend = 0;
//int UserForceClose = 0;

//	TThostFtdcUserIDType	UserID;
///�����۸�����: �޼�
//req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
//req.OrderPriceType = THOST_FTDC_OPT_AnyPrice;

///��������: 
//req.Direction = DIRECTION;

///��Ͽ�ƽ��־: ����/ƽ��
//req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
//req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;

///���Ͷ���ױ���־
//req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;

///�۸�
//req.LimitPrice = LIMIT_PRICE;

///����: 1
//req.VolumeTotalOriginal = Volume;

///��Ч������: ������Ч
//req.TimeCondition = THOST_FTDC_TC_GFD;
//req.TimeCondition = THOST_FTDC_TC_IOC;

///GTD����
//	TThostFtdcDateType	GTDDate;

///�ɽ�������: �κ�����
//req.VolumeCondition = THOST_FTDC_VC_AV;

///��С�ɽ���: 1
//req.MinVolume = 1;

///��������: ����
//req.ContingentCondition = THOST_FTDC_CC_Immediately;

///ֹ���
//	TThostFtdcPriceType	StopPrice;

///ǿƽԭ��: ��ǿƽ
//req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;

///�Զ������־: ��
//req.IsAutoSuspend = 0;

///ҵ��Ԫ
//	TThostFtdcBusinessUnitType	BusinessUnit;
///������
//	TThostFtdcRequestIDType	RequestID;

///�û�ǿ����־: ��
//req.UserForceClose = 0;