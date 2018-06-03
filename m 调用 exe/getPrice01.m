function c = getPrice01(futureCode)

% clear; clc; close all;

% futureCode = 'MA1801';

url = ['http://hq.sinajs.cn/list=', futureCode];

[KLineData, ~] = urlread(url);

pos = find(KLineData == '"');
KLineData = KLineData(pos(1)+1:pos(2)-1);
pos = find(KLineData == ',');

if ~isempty(pos)
    
    o = str2double(KLineData(pos(2)+1:pos(3)-1));
    h = str2double(KLineData(pos(3)+1:pos(4)-1));
    l = str2double(KLineData(pos(4)+1:pos(5)-1));
    c = str2double(KLineData(pos(8)+1:pos(9)-1));
    v = str2double(KLineData(pos(14)+1:pos(15)-1));
    
    % KLineData(pos(17)+1:pos(18)-1) % ÈÕÆÚ
    kData = [o,h,l,c,v];
    
end

end

