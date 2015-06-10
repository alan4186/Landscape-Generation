function s = importTSPscores( file )
Xmap=dlmread(file,' ',[0 0 0 9]);
Ymap=dlmread(file,' ',[1 0 1 9]);
raw=dlmread(file,' ',2, 0);
square=reshape(raw(1:3625216),[1904 1904]);
square=reshape(raw(1:1900^2),[1900 1900]);
scape=genScape(square,square,1);
s=struct('Xmap',Xmap,'Ymap',Ymap,'raw',raw,'square',square);%,'scape',scape);
bucket=genBucket(s);
scape=genScape(bucket,square,1);
%scape=imresize(scape(100:end-100,100:end-100),[64 64]);
[s(:).scape]=deal(scape);
end

