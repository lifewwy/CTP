clear; clc; close all;

cmd = 'C:\Users\apple\Desktop\CTP\����_02\Bin\testTraderApi.exe '; 

%% �в�������
FRONT_ADDR = 'tcp://180.168.146.187:10031';
% FRONT_ADDR = 'tcp://180.168.146.187:10000';
BROKER_ID = '9999';
INVESTOR_ID = '101042';
PASSWORD = '518888';

% FRONT_ADDR = 'tcp://61.152.165.100:41201';	  
% BROKER_ID = '0187';			
% INVESTOR_ID = '28006311';	 
% PASSWORD = '518888';		

CONTRACT = ['m1801',' ', 'rb1801',' ', 'MA801',' ', 'TA801'];
nCONTRACT = '4';
x = [FRONT_ADDR,' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD,...
    ' ',nCONTRACT,' ',CONTRACT];

%% ���� exe ����
cmd = [cmd,x];

% [status, results] = system(cmd);
tic
[status, results] = dos(cmd); 
toc

results %#ok

% system('command')
% [status, results]=system('command')
% [status, results]=system('command','-echo')
% ��һ��ֱ�������������ʾ�����е���ʾ
% �ڶ���������óɹ���status�᷵��0�����ʧ�ܷ�������ֵ�����������û������ģ����������ַ�������results��
% �������͵ڶ���һ����ֻ�ǻ�ǿ�������������ʾ������Ϣ��
%% results ����











