function [LastPrice, UpperLimitPrice,LowerLimitPrice]... 
    = GetMarketData(FRONT_ADDR_MD,BROKER_ID,...
    INVESTOR_ID,PASSWORD,CONTRACT_cell) %#ok

% clear; clc; close all;
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


%% �����ѯ
cmd = 'C:\Users\apple\Desktop\CTP\����_02\Bin\testTraderApi.exe '; 

% CONTRACT_cell = {'m1801', 'rb1801', 'MA801','TA801'};

nContract = length(CONTRACT_cell);
nCONTRACT = num2str(nContract);
CONTRACT = [];
for i = 1:nContract
    CONTRACT = [CONTRACT,' ',CONTRACT_cell{i}]; %#ok
end


x = [FRONT_ADDR_MD,' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD,...
    ' ',nCONTRACT,' ',CONTRACT];

cmd = [cmd,x];

tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>���óɹ���');
end

% results %#ok

for i=1:nContract
    pos1 = strfind(results ,[CONTRACT_cell{i},' ���¼�: ']);
    pos2 = strfind(results ,[CONTRACT_cell{i},' ��ͣ��: ']);
    pos3 = strfind(results ,[CONTRACT_cell{i},' ��ͣ��: ']);
    vv1 = results(pos1(end):pos1(end)+20);
    vv2 = results(pos2(end):pos2(end)+20);
    vv3 = results(pos3(end):pos3(end)+20);
    p1 = str2double(vv1(find(vv1==':')+1 : find(vv1==';')-1));
    p2 = str2double(vv2(find(vv2==':')+1 : find(vv2==';')-1));
    p3 = str2double(vv3(find(vv3==':')+1 : find(vv3==';')-1));
    eval(['LastPrice.' CONTRACT_cell{i} ' = ' num2str(p1) ';']);
    eval(['UpperLimitPrice.' CONTRACT_cell{i} ' = ' num2str(p2) ';']);
    eval(['LowerLimitPrice.' CONTRACT_cell{i} ' = ' num2str(p3) ';']);
end
% LastPrice 
% UpperLimitPrice
% LowerLimitPrice

end













