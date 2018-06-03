clear; clc; close all;

%% 登录配置
% SimNow 1   交易阶段(服务时间)：与实际生产环境保持一致
FRONT_ADDR_MD = 'tcp://180.168.146.187:10010';
FRONT_ADDR_TD = 'tcp://180.168.146.187:10000';
BROKER_ID = '9999';
INVESTOR_ID = '101042';
PASSWORD = '518888';

% SimNow 2
%  交易阶段(服务时间)：交易日，16：00～次日09：00；非交易日，16：00～次日15：00。
% 账户、钱、仓跟第一套环境上一个交易日保持一致。
% FRONT_ADDR_MD = 'tcp://180.168.146.187:10031';
% FRONT_ADDR_TD = 'tcp://180.168.146.187:10030';
% BROKER_ID = '9999';
% INVESTOR_ID = '101042';
% PASSWORD = '518888';

% 快期-国贸期货
% FRONT_ADDR_TD = 'tcp://61.152.165.100:41201';
% FRONT_ADDR_MD = 'tcp://61.152.165.100:41211';
% BROKER_ID = '0187';			
% INVESTOR_ID = '28006311';	 
% PASSWORD = '518888';

% 快期-新湖期货
% FRONT_ADDR_TD = 'tcp://116.228.171.216:41205';
% FRONT_ADDR_MD = 'tcp://116.228.171.216:41213';
% BROKER_ID = '6090';			
% INVESTOR_ID = '10501951';	 
% PASSWORD = '202031';
%% 登录测试
FLG = LoginTest(FRONT_ADDR_TD,BROKER_ID,...
    INVESTOR_ID,PASSWORD);

%% 当日可交易合约查询
% % Contract = 'MA801';
% % Contract = 'TA801';
% Contract = 'ALL';
% TradableContract = GetTradableContracts(FRONT_ADDR_TD,BROKER_ID,...
%     INVESTOR_ID,PASSWORD,Contract);

%% 交易账户查询
balance = GetAccountInfo(FRONT_ADDR_TD,BROKER_ID,...
    INVESTOR_ID,PASSWORD);

%% 行情数据查询
CONTRACT_cell = {'m1801', 'rb1801', 'MA801','TA801'};
[LastPrice, UpperLimitPrice,LowerLimitPrice]...
    = GetMarketData(FRONT_ADDR_MD,BROKER_ID,...
    INVESTOR_ID,PASSWORD,CONTRACT_cell) ;
%% 下单 1
% Contract = 'MA801';
Contract = 'TA801';

Sell_Buy = '0'; % 买
% Sell_Buy = '1'; % 卖

% Open_Close = '0'; % 开仓
Open_Close = '1'; % 平仓

Volume = '1';

if (strcmp( Sell_Buy , '0' ) && ...
        strcmp( Open_Close , '0' ))|| ...
        (strcmp( Sell_Buy , '1' )&& ...
        strcmp( Sell_Buy , '1' ))
    % 加价保证成交  
    LimitPrice = num2str(eval(['UpperLimitPrice.',Contract]));
else
    % 减价保证成交
    LimitPrice = num2str(eval(['LowerLimitPrice.',Contract]));
end
Doneflg = PlanceOrder(Contract,Sell_Buy,Open_Close,...
    LimitPrice,Volume,FRONT_ADDR_TD,...
    BROKER_ID, INVESTOR_ID,PASSWORD);
%% 下单 2
clc
Contract = 'TA801';

Sell_Buy = '0'; % 买
% Sell_Buy = '1'; % 卖

Open_Close = '0'; % 开仓
% Open_Close = '1'; % 平仓

Volume = '1';

[Doneflg,results] = PlanceOrder1(Contract,Sell_Buy,Open_Close,...
    Volume,FRONT_ADDR_TD,FRONT_ADDR_MD,...
    BROKER_ID, INVESTOR_ID,PASSWORD);

pos1 = strfind(results,'[ErrorMsg]');
vv = results(pos1(end):pos1(end)+60);
pos2 = find(vv==']');
ErrorMsg = vv(1:pos2(3));












