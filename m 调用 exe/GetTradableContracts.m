function contract = GetTradableContracts(FRONT_ADDR_TD,BROKER_ID,...
    INVESTOR_ID,PASSWORD,Contract)

%% 查询当日可交易的合约号
cmd = 'C:\Users\apple\Desktop\CTP\交易账户查询_01\Bin\testTraderApi.exe ';
% Contract = 'MA801';
% Contract = 'TA801';
% Contract = 'ALL';

x = [FRONT_ADDR_TD,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD,' ',Contract];

cmd = [cmd,x];
tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>调用成功！');
end

% 当日可交易合约查询
pos = strfind(results ,'合约号:');
contract = cell(length(pos),1);
for i = 1:length(pos)
    vv = results(pos(i):pos(i)+20);
    contract(i) = {vv(find(vv==':')+2 : find(vv==';')-1)};
end
contract = sortrows(contract);

end













