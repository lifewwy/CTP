clear; clc; close all;

cmd = 'C:\Users\apple\Desktop\CTP\交易账户查询_01\Bin\testTraderApi.exe ';

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

% cell2mat(strfind(ResultsCell,'持仓手数'));


pos = strfind(results ,'账户资金');
vv = results(pos:pos+50);
banance = str2double(vv(find(vv==':')+1 : find(vv==';')-1)) %#ok

pos = strfind(results ,'持仓手数');
vv = results(pos:pos+50);
hands = str2double(vv(find(vv==':')+1 : find(vv==';')-1));

% 持仓方向：0空仓 2多头，3空头
pos = strfind(results ,'持仓方向');
vv = results(pos:pos+50);
direction = str2double(vv(find(vv==':')+1 : find(vv==';')-1));

position =  [hands, direction]  %#ok










