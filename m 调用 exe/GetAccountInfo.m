function balance = GetAccountInfo(FRONT_ADDR_TD,BROKER_ID,...
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
cmd = 'C:\Users\apple\Desktop\CTP\�����˻���ѯ_01\Bin\testTraderApi.exe ';

x = [FRONT_ADDR_TD,...
    ' ',BROKER_ID,' ',INVESTOR_ID,' ',PASSWORD];

cmd = [cmd,x];
tic; [status, results] = dos(cmd); toc
if status==0
    disp('>>>>>>>>>>���óɹ���');
end

% �������
pos = strfind(results ,'�˻��ʽ�');
vv = results(pos:pos+22);
balance = str2double(vv(find(vv==':')+1 : find(vv==';')-1));
fprintf(1,['�˻��ʽ�:' num2str(balance) '\n' ]);

% д csv �ļ�
pos = strfind(results ,'�ֲֺ�Լ');
nn = length(pos);
fid = fopen(['C:\D\future\m\���ٿ���-��¼�ʽ�-ͼ��ʶ��-4\��¼�ʽ�\�ֲ�', '.csv'], 'wt');
for k = 1:nn+1
    if k == 1
        fprintf(fid, '%s,', '');
        fprintf(fid, '%s,', '��Լ��');
        fprintf(fid, '%s,', '��/��');
        fprintf(fid, '%s\n', '�ܲ�');
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
            fprintf(fid, '%s,', '��');% 2��ͷ��3��ͷ
        end
        if str2double(direction)==3
            fprintf(fid, '%s,', '��');% 2��ͷ��3��ͷ
        end
        fprintf(fid, '%s\n', hands);
    end
end
fclose(fid);
% disp('---------------> �ֲ��ļ����³ɹ���------------->')
disp('�ֲ��ļ����³ɹ���')

end

% % ���տɽ��׺�Լ��ѯ
% pos = strfind(results ,'��Լ��:');
% contract = cell(length(pos),1);
% for i = 1:length(pos)
%     vv = results(pos(i):pos(i)+15);
%     contract(i) = {vv(find(vv==':')+1 : find(vv==';')-1)};
% end
% contract = sortrows(contract);














