function [Doneflg,results] = PlanceOrder1(Contract,Sell_Buy,Open_Close,...
    Volume,FRONT_ADDR_TD,FRONT_ADDR_MD,...
    BROKER_ID, INVESTOR_ID,PASSWORD)

% Contract = 'TA801';

% Sell_Buy = '0'; % 买
% Sell_Buy = '1'; % 卖

% Open_Close = '0'; % 开仓
% Open_Close = '1'; % 平仓

% Volume = '1';

%% 行情查询
CONTRACT_cell = {Contract};
[LastPrice, UpperLimitPrice,LowerLimitPrice]...
    = GetMarketData(FRONT_ADDR_MD,BROKER_ID,...
    INVESTOR_ID,PASSWORD,CONTRACT_cell); %#ok

%% 交易
cmd = 'C:\Users\apple\Desktop\CTP\交易_03\Bin\testTraderApi.exe ';
% LimitPrice = '2800';

if strcmp( Sell_Buy , '0' )
    % 加价保证成交  
    LimitPrice = num2str(eval(['UpperLimitPrice.',Contract]));
else
    % 减价保证成交
    LimitPrice = num2str(eval(['LowerLimitPrice.',Contract]));
end

% LimitPrice = num2str(eval(['LowerLimitPrice.',Contract]))
% LimitPrice = num2str(eval(['UpperLimitPrice.',Contract]))

% if (strcmp( Sell_Buy , '0' ) && ...
%         strcmp( Open_Close , '0' ))|| ...
%         (strcmp( Sell_Buy , '1' )&& ...
%         strcmp( Open_Close , '1' ))
%     % 加价保证成交  
%     LimitPrice = num2str(eval(['UpperLimitPrice.',Contract]));
% else
%     LimitPrice = num2str(eval(['LowerLimitPrice.',Contract]));
% end

x = [Contract,' ',Sell_Buy,' ',Open_Close,...
    ' ',LimitPrice,' ',Volume,' ',FRONT_ADDR_TD,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD];

cmd = [cmd,x];

tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>调用成功！');
end

% results

if ~isempty(strfind(results ,'全部成交'))
    disp('全部成交');
    Doneflg = 1;
else 
    Doneflg = 0;
end

end

%% 登录配置
% SimNow 1   交易阶段(服务时间)：与实际生产环境保持一致
% FRONT_ADDR_MD = 'tcp://180.168.146.187:10010';
% FRONT_ADDR_TD = 'tcp://180.168.146.187:10000';
% BROKER_ID = '9999';
% INVESTOR_ID = '101042';
% PASSWORD = '518888';

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















