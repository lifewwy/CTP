clear; clc; close all;

cmd = 'C:\Users\apple\Desktop\CTP\�����˻���ѯ_01\Bin\testTraderApi.exe ';

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

FRONT_ADDR = 'tcp://180.168.146.187:10030';
% FRONT_ADDR = 'tcp://180.168.146.187:10000';
BROKER_ID = '9999';
INVESTOR_ID = '101042';
PASSWORD = '518888';

% FRONT_ADDR = 'tcp://61.152.165.100:41201';	  
% FRONT_ADDR = 'tcp://61.152.165.100:41211';
% BROKER_ID = '0187';			
% INVESTOR_ID = '28006311';	 
% PASSWORD = '518888';		

x = [FRONT_ADDR,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD,' ',Contract];

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

% cell2mat(strfind(ResultsCell,'�ֲ�����'));


pos = strfind(results ,'�˻��ʽ�');
vv = results(pos:pos+50);
banance = str2double(vv(find(vv==':')+1 : find(vv==';')-1)) %#ok

pos = strfind(results ,'�ֲ�����');
vv = results(pos:pos+50);
hands = str2double(vv(find(vv==':')+1 : find(vv==';')-1));

% �ֲַ���0�ղ� 2��ͷ��3��ͷ
pos = strfind(results ,'�ֲַ���');
vv = results(pos:pos+50);
direction = str2double(vv(find(vv==':')+1 : find(vv==';')-1));

position =  [hands, direction]  %#ok










