function FLG = LoginTest(FRONT_ADDR_TD,BROKER_ID,...
    INVESTOR_ID,PASSWORD)

% clear; clc; close all;

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
% FRONT_ADDR_MD = 'tcp://180.168.146.187:10031';
% FRONT_ADDR_TD = 'tcp://180.168.146.187:10030';
% BROKER_ID = '9999';
% INVESTOR_ID = '101042';
% PASSWORD = '518888';

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
cmd = 'C:\Users\apple\Desktop\CTP\��¼����_01\Bin\testTraderApi.exe ';

x = [FRONT_ADDR_TD,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD];

cmd = [cmd,x];
tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>���óɹ���');
end

% �������
pos = strfind(results ,'��¼�ɹ�');
if ~isempty(pos)
    fprintf(1,'��¼�ɹ�!\n');
    FLG = '��¼�ɹ�';
else
    fprintf(2,'δ��¼�ɹ�!\n');
    FLG = 'δ��¼�ɹ�';
end


end













