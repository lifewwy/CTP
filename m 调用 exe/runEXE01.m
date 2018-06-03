clear; clc; close all;

cmd = 'C:\Users\apple\Desktop\CTP\交易_03\Bin\testTraderApi.exe ';

% cmd = 'C:\Users\apple\Desktop\CTP\交易Demo版 02\Bin\testTraderApi.exe &';
% 这里可以通过添加 & 的选项来实现打开应用程序后立即返回matlab，然后执行matlab
% 的后续命令，而不等待应用程序。
% system(cmd); 

% 无参数调用
% [status, results] = system(cmd); 
% [status, results] = dos(cmd); 

%% 有参数调用
Contract = 'MA801';
% Contract = 'TA801';

Sell_Buy = '0'; % 买
% Sell_Buy = '1'; % 卖

Open_Close = '0'; % 开仓
% Open_Close = '1'; % 平仓

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

%% 调用 exe 程序
cmd = [cmd,x];

% [status, results] = system(cmd);
tic
[status, results] = dos(cmd); 
toc

% results %#ok

% system('command')
% [status, results]=system('command')
% [status, results]=system('command','-echo')
% 第一个直接在命令窗口中显示运行中的提示
% 第二个如果调用成功，status会返回0，如果失败返回其它值，在命令窗口是没有输出的，但是所有字符保存在results中
% 第三个和第二个一样，只是还强制在命令窗口中显示运行信息。
%% results 分析
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

% 成交情况
% sum(strcmp(ResultsCell,'全部成交'))

if ~isempty(strfind(results ,'全部成交'))
    disp('全部成交');
end












