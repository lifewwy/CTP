clear; clc; close all;

cmd = 'C:\Users\apple\Desktop\CTP\����_03\Bin\testTraderApi.exe ';

% cmd = 'C:\Users\apple\Desktop\CTP\����Demo�� 02\Bin\testTraderApi.exe &';
% �������ͨ����� & ��ѡ����ʵ�ִ�Ӧ�ó������������matlab��Ȼ��ִ��matlab
% �ĺ�����������ȴ�Ӧ�ó���
% system(cmd); 

% �޲�������
% [status, results] = system(cmd); 
% [status, results] = dos(cmd); 

%% �в�������
Contract = 'MA801';
% Contract = 'TA801';

Sell_Buy = '0'; % ��
% Sell_Buy = '1'; % ��

Open_Close = '0'; % ����
% Open_Close = '1'; % ƽ��

LimitPrice = '2800re';

Volume = '1';

FRONT_ADDR = 'tcp://180.168.146.187:10030';
% FRONT_ADDR = 'tcp://180.168.146.187:10000';
BROKER_ID = '9999';
INVESTOR_ID = '101042';
PASSWORD = '518888';

% FRONT_ADDR = 'tcp://61.152.165.100:41201';	  
% BROKER_ID = '0187';			
% INVESTOR_ID = '28006311';	 
% PASSWORD = '518888';		

x = [Contract,' ',Sell_Buy,' ',Open_Close,...
    ' ',LimitPrice,' ',Volume,' ',FRONT_ADDR,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD];

%% ���� exe ����
cmd = [cmd,x];

% [status, results] = system(cmd);
tic
[status, results] = dos(cmd); 
toc

% results %#ok

% system('command')
% [status, results]=system('command')
% [status, results]=system('command','-echo')
% ��һ��ֱ�������������ʾ�����е���ʾ
% �ڶ���������óɹ���status�᷵��0�����ʧ�ܷ�������ֵ�����������û������ģ����������ַ�������results��
% �������͵ڶ���һ����ֻ�ǻ�ǿ�������������ʾ������Ϣ��
%% results ����
% save results results;
% clc;
% load results; 

% tic
% pos1 = find(results == results(74));
% ResultsCell = cell(length(pos1)-1,1);
% for i = 1:length(pos1)-1
%     if i==1
%         ResultsCell(i,1) = {results(1:pos1(1)-1)};
%     else
%         ResultsCell(i,1) = {results(pos1(i)+1:pos1(i+1)-1)};
%     end
% end
% toc

% �ɽ����
% sum(strcmp(ResultsCell,'ȫ���ɽ�'))

if ~isempty(strfind(results ,'ȫ���ɽ�'))
    disp('ȫ���ɽ�');
end












