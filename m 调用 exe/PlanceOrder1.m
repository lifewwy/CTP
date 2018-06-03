function [Doneflg,results] = PlanceOrder1(Contract,Sell_Buy,Open_Close,...
    Volume,FRONT_ADDR_TD,FRONT_ADDR_MD,...
    BROKER_ID, INVESTOR_ID,PASSWORD)

% Contract = 'TA801';

% Sell_Buy = '0'; % ��
% Sell_Buy = '1'; % ��

% Open_Close = '0'; % ����
% Open_Close = '1'; % ƽ��

% Volume = '1';

%% �����ѯ
CONTRACT_cell = {Contract};
[LastPrice, UpperLimitPrice,LowerLimitPrice]...
    = GetMarketData(FRONT_ADDR_MD,BROKER_ID,...
    INVESTOR_ID,PASSWORD,CONTRACT_cell); %#ok

%% ����
cmd = 'C:\Users\apple\Desktop\CTP\����_03\Bin\testTraderApi.exe ';
% LimitPrice = '2800';

if strcmp( Sell_Buy , '0' )
    % �Ӽ۱�֤�ɽ�  
    LimitPrice = num2str(eval(['UpperLimitPrice.',Contract]));
else
    % ���۱�֤�ɽ�
    LimitPrice = num2str(eval(['LowerLimitPrice.',Contract]));
end

% LimitPrice = num2str(eval(['LowerLimitPrice.',Contract]))
% LimitPrice = num2str(eval(['UpperLimitPrice.',Contract]))

% if (strcmp( Sell_Buy , '0' ) && ...
%         strcmp( Open_Close , '0' ))|| ...
%         (strcmp( Sell_Buy , '1' )&& ...
%         strcmp( Open_Close , '1' ))
%     % �Ӽ۱�֤�ɽ�  
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
    disp('>>>>>>>>>>���óɹ���');
end

% results

if ~isempty(strfind(results ,'ȫ���ɽ�'))
    disp('ȫ���ɽ�');
    Doneflg = 1;
else 
    Doneflg = 0;
end

end

%% ��¼����
% SimNow 1   ���׽׶�(����ʱ��)����ʵ��������������һ��
% FRONT_ADDR_MD = 'tcp://180.168.146.187:10010';
% FRONT_ADDR_TD = 'tcp://180.168.146.187:10000';
% BROKER_ID = '9999';
% INVESTOR_ID = '101042';
% PASSWORD = '518888';

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















