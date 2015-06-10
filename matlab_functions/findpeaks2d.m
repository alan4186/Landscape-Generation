function peaks = findpeaks2d( struct )
A=struct.scape(100:end-100,100:end-100);
peaks=zeros(length(A));
mn=min(min(A));
mx=max(max(A));
r=mx-mn;
t=mn+0.80*r;

A=A-t;
peaks=A>0;

% for i=1:length(A)
%     [~ ,thispeaks]=findpeaks(A(i,:),'MinPeakHeight',t);
%     
%     for j=1:length(thispeaks)
%         peaks(thispeaks(j), i)=1;
%     end
% end
% for i=1:1701-25
%     for j=1:1701-25
%         if sum(peaks(i,j:j+25))~=0
%             peaks(i,j)=1;
%         end
%         if sum(peaks(j:j+25,i))~=0
%             peaks(i,j)=1;
%         end
%         
%     end
% end

    


end

