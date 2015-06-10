function [ inp, tar ] = genData( filename )
s=importTSPscores(filename);
% create input outputs for net
inp=[s.Xmap s.Ymap];
%normalize inputs from range 0:8
inp=inp./8.0;
inp=transpose(inp);
 
 
B=genBucket(s);
size(B);
A=genScape(B,B,0);
A=A(100:end-50,100:end-50);%crop edges
mn=min(min(A));
mx=max(max(A));
r=mx-mn;
t=mn+0.85*r;

A=A-t;
peaks=A>0;
%G=fspecial('gaussian',[25 25],100);
%peaks=imfilter(peaks,G,'same');

fig=figure;set(fig,'visible','off');
[c, ~]=contour(peaks,1);
lines=getcontourlines(c);
[~,numM]=size(lines);

if numM>100
    numM=10;
else if numM<=0
        numM=1; 
    else
        numM=round(numM/10);
    end
end
tar=zeros(10,1);

tar(numM,1)=1;

end

