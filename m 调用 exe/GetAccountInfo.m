function balance = GetAccountInfo(FRONT_ADDR_TD,BROKER_ID,...
    INVESTOR_ID,PASSWORD)

% clear; clc; close all;

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


%% 交易账户查询
cmd = 'C:\Users\apple\Desktop\CTP\交易账户查询_01\Bin\testTraderApi.exe ';

x = [FRONT_ADDR_TD,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD];

cmd = [cmd,x];
tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>调用成功！');
end

% 结果分析
pos = strfind(results ,'账户资金');
vv = results(pos:pos+22);
balance = str2double(vv(find(vv==':')+1 : find(vv==';')-1));
fprintf(1,['账户资金:' num2str(balance) '\n' ]);

% 写 csv 文件
pos = strfind(results ,'持仓合约');
nn = length(pos);
fid = fopen(['C:\D\future\m\跟踪开仓-记录资金-图像识别-4\记录资金\持仓', '.csv'], 'wt');
for k = 1:nn+1
    if k == 1
        fprintf(fid, '%s,', '');
        fprintf(fid, '%s,', '合约号');
        fprintf(fid, '%s,', '多/空');
        fprintf(fid, '%s\n', '总仓');
    else
        vv = results(pos(k-1):pos(k-1)+40);
        pos1 = find(vv==':');
        pos2 = find(vv==';');
        contract = vv(pos1(1)+1:pos2(1)-1);
        hands = vv(pos1(2)+1:pos2(2)-1);
        direction = vv(pos1(3)+1:pos2(3)-1);
        fprintf(fid, '%s,', '');
        fprintf(fid, '%s,', contract);
        if str2double(direction)==2
            fprintf(fid, '%s,', '多');% 2多头，3空头
        end
        if str2double(direction)==3
            fprintf(fid, '%s,', '空');% 2多头，3空头
        end
        fprintf(fid, '%s\n', hands);
    end
end
fclose(fid);
% disp('---------------> 持仓文件更新成功！------------->')
disp('持仓文件更新成功！')

end

% % 当日可交易合约查询
% pos = strfind(results ,'合约号:');
% contract = cell(length(pos),1);
% for i = 1:length(pos)
%     vv = results(pos(i):pos(i)+15);
%     contract(i) = {vv(find(vv==':')+1 : find(vv==';')-1)};
% end
% contract = sortrows(contract);














