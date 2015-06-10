function numMountains = countmountains( struct )
% find peaks
A=struct.scape(100:end-100,100:end-100);
mn=min(min(A));
mx=max(max(A));
r=mx-mn;
t=mn+0.80*r;

A=A-t;
peaks=A>0;
G=fspecial('gaussian',[25 25],100);
peaks=imfilter(peaks,G,'same');
% for i=1:length(peaks)-50
%     for j=1:length(peaks)-50
%         if sum(peaks(i:i+50,j))>20 || sum(peaks(i,j:j+50))>20
%             peaks(i,j)=1;
%         else
%             peaks(i,j)=0;
%         end
%     end
% end
%figure; pcolor(peaks);shading flat;

fig=figure;set(fig,'visible','on');
[c, ~]=contour(peaks,1);
lines=getcontourlines(c);
[~,numMountains]=size(lines);
end

