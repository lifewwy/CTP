clear; clc; close all;

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
FRONT_ADDR_MD = 'tcp://180.168.146.187:10031';
FRONT_ADDR_TD = 'tcp://180.168.146.187:10030';
BROKER_ID = '9999';
INVESTOR_ID = '101042';
PASSWORD = '518888';

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


%% �����˻���ѯ
cmd = 'C:\Users\apple\Desktop\CTP\�����˻���ѯ_01\Bin\testTraderApi.exe ';
% Contract = 'MA801';
Contract = 'TA801';
% Contract = 'ALL';

x = [FRONT_ADDR_TD,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD,' ',Contract];

cmd = [cmd,x];
tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>���óɹ���');
end

% �������
pos = strfind(results ,'�˻��ʽ�');
vv = results(pos:pos+16);
banance = str2double(vv(find(vv==':')+1 : find(vv==';')-1));
fprintf(2,['�˻��ʽ�:' num2str(banance) '\n' ]);

% д csv �ļ�
pos = strfind(results ,'�ֲֺ�Լ');
nn = length(pos);
fid = fopen(['�ֲ�', '.csv'], 'wt');
for k = 1:nn+1
    if k == 1
        fprintf(fid, '%s,', '');
        fprintf(fid, '%s,', '��Լ��');
        fprintf(fid, '%s,', '��/��');
        fprintf(fid, '%s\n', '�ܲ�');
    else
        vv = results(pos(1):pos(1)+40);
        pos1 = find(vv==':');
        pos2 = find(vv==';');
        contract = vv(pos1(1)+1:pos2(1)-1);
        hands = vv(pos1(2)+1:pos2(2)-1);
        direction = vv(pos1(3)+1:pos2(3)-1);
        fprintf(fid, '%s,', '');
        fprintf(fid, '%s,', contract);
        fprintf(fid, '%s,', direction);
        fprintf(fid, '%s\n', hands);
    end
end
fclose(fid);
disp('---------------> �ֲ��ļ����³ɹ���------------->')

% ���տɽ��׺�Լ��ѯ
pos = strfind(results ,'��Լ��:');
contract = cell(length(pos),1);
for i = 1:length(pos)
    vv = results(pos(i):pos(i)+15);
    contract(i) = {vv(find(vv==':')+1 : find(vv==';')-1)};
end
contract = sortrows(contract);
%% �������ݲ�ѯ
cmd = 'C:\Users\apple\Desktop\CTP\����_02\Bin\testTraderApi.exe '; 

CONTRACT_cell = {'m1801', 'rb1801', 'MA801','TA801'};
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

%% ����
cmd = 'C:\Users\apple\Desktop\CTP\����_03\Bin\testTraderApi.exe ';

% Contract = 'MA801';
Contract = 'TA801';

Sell_Buy = '0'; % ��
% Sell_Buy = '1'; % ��

Open_Close = '0'; % ����
% Open_Close = '1'; % ƽ��

Volume = '1';

% LimitPrice = '2800';
if (strcmp( Sell_Buy , '0' ) && ...
        strcmp( Open_Close , '0' ))|| ...
        (strcmp( Sell_Buy , '1' )&& ...
        strcmp( Sell_Buy , '1' ))
    % �Ӽ۱�֤�ɽ�  
    LimitPrice = num2str(eval(['UpperLimitPrice.',Contract]));
else
    % ���۱�֤�ɽ�
    LimitPrice = num2str(eval(['LowerLimitPrice.',Contract]));
end

x = [Contract,' ',Sell_Buy,' ',Open_Close,...
    ' ',LimitPrice,' ',Volume,' ',FRONT_ADDR_TD,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD];

cmd = [cmd,x];

tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>���óɹ���');
end

if ~isempty(strfind(results ,'ȫ���ɽ�'))
    disp('ȫ���ɽ�');
end














