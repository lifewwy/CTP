clear; clc; close all;

cmd = 'C:\Users\apple\Desktop\CTP\行情_02\Bin\testTraderApi.exe '; 

%% 有参数调用
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

%% 调用 exe 程序
cmd = [cmd,x];

% [status, results] = system(cmd);
tic
[status, results] = dos(cmd); 
toc

results %#ok

% system('command')
% [status, results]=system('command')
% [status, results]=system('command','-echo')
% 第一个直接在命令窗口中显示运行中的提示
% 第二个如果调用成功，status会返回0，如果失败返回其它值，在命令窗口是没有输出的，但是所有字符保存在results中
% 第三个和第二个一样，只是还强制在命令窗口中显示运行信息。
%% results 分析











