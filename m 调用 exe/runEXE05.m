clear; clc; close all;

%% ��¼����
% SimNow 1   ���׽׶�(����ʱ��)����ʵ��������������һ��
FRONT_ADDR_MD = 'tcp://180.168.146.187:10010';
FRONT_ADDR_TD = 'tcp://180.168.146.187:10000';
BROKER_ID = '9999';
INVESTOR_ID = '101042';
PASSWORD = '518888';

% SimNow 2
%  ���׽׶�(����ʱ��)�������գ�16��00������09��00���ǽ����գ�16��00������15��00��
% �˻���Ǯ���ָ���һ�׻�����һ�������ձ���һ�¡�
% FRONT_ADDR_MD = 'tcp://180.168.146.187:10031';
% FRONT_ADDR_TD = 'tcp://180.168.146.187:10030';
% BROKER_ID = '9999';
% INVESTOR_ID = '101042';
% PASSWORD = '518888';

% ����-��ó�ڻ�
% FRONT_ADDR_TD = 'tcp://61.152.165.100:41201';
% FRONT_ADDR_MD = 'tcp://61.152.165.100:41211';
% BROKER_ID = '0187';			
% INVESTOR_ID = '28006311';	 
% PASSWORD = '518888';

% ����-�º��ڻ�
% FRONT_ADDR_TD = 'tcp://116.228.171.216:41205';
% FRONT_ADDR_MD = 'tcp://116.228.171.216:41213';
% BROKER_ID = '6090';			
% INVESTOR_ID = '10501951';	 
% PASSWORD = '202031';
%% ��¼����
FLG = LoginTest(FRONT_ADDR_TD,BROKER_ID,...
    INVESTOR_ID,PASSWORD);

%% ���տɽ��׺�Լ��ѯ
% % Contract = 'MA801';
% % Contract = 'TA801';
% Contract = 'ALL';
% TradableContract = GetTradableContracts(FRONT_ADDR_TD,BROKER_ID,...
%     INVESTOR_ID,PASSWORD,Contract);

%% �����˻���ѯ
balance = GetAccountInfo(FRONT_ADDR_TD,BROKER_ID,...
    INVESTOR_ID,PASSWORD);

%% �������ݲ�ѯ
CONTRACT_cell = {'m1801', 'rb1801', 'MA801','TA801'};
[LastPrice, UpperLimitPrice,LowerLimitPrice]...
    = GetMarketData(FRONT_ADDR_MD,BROKER_ID,...
    INVESTOR_ID,PASSWORD,CONTRACT_cell) ;
%% �µ� 1
% Contract = 'MA801';
Contract = 'TA801';

Sell_Buy = '0'; % ��
% Sell_Buy = '1'; % ��

% Open_Close = '0'; % ����
Open_Close = '1'; % ƽ��

Volume = '1';

if (strcmp( Sell_Buy , '0' ) && ...
        strcmp( Open_Close , '0' ))|| ...
        (strcmp( Sell_Buy , '1' )&& ...
        strcmp( Sell_Buy , '1' ))
    % �Ӽ۱�֤�ɽ�  
    LimitPrice = num2str(eval(['UpperLimitPrice.',Contract]));
else
    % ���۱�֤�ɽ�
    LimitPrice = num2str(eval(['LowerLimitPrice.',Contract]));
end
Doneflg = PlanceOrder(Contract,Sell_Buy,Open_Close,...
    LimitPrice,Volume,FRONT_ADDR_TD,...
    BROKER_ID, INVESTOR_ID,PASSWORD);
%% �µ� 2
clc
Contract = 'TA801';

Sell_Buy = '0'; % ��
% Sell_Buy = '1'; % ��

Open_Close = '0'; % ����
% Open_Close = '1'; % ƽ��

Volume = '1';

[Doneflg,results] = PlanceOrder1(Contract,Sell_Buy,Open_Close,...
    Volume,FRONT_ADDR_TD,FRONT_ADDR_MD,...
    BROKER_ID, INVESTOR_ID,PASSWORD);

pos1 = strfind(results,'[ErrorMsg]');
vv = results(pos1(end):pos1(end)+60);
pos2 = find(vv==']');
ErrorMsg = vv(1:pos2(3));












