function contract = GetTradableContracts(FRONT_ADDR_TD,BROKER_ID,...
    INVESTOR_ID,PASSWORD,Contract)

%% ��ѯ���տɽ��׵ĺ�Լ��
cmd = 'C:\Users\apple\Desktop\CTP\�����˻���ѯ_01\Bin\testTraderApi.exe ';
% Contract = 'MA801';
% Contract = 'TA801';
% Contract = 'ALL';

x = [FRONT_ADDR_TD,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD,' ',Contract];

cmd = [cmd,x];
tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>���óɹ���');
end

% ���տɽ��׺�Լ��ѯ
pos = strfind(results ,'��Լ��:');
contract = cell(length(pos),1);
for i = 1:length(pos)
    vv = results(pos(i):pos(i)+20);
    contract(i) = {vv(find(vv==':')+2 : find(vv==';')-1)};
end
contract = sortrows(contract);

end













