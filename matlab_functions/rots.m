function out = rots( a,n )
out=zeros(length(a));
nn=n/37.5;
for i=1:length(a)
    % previoisly stable
    out(i,:)=circshift(a(i,:),[0 int64(nn*(i+length(a)/2)*sin(i))]);
    
    % for testing:
    %out(i,:)=circshift(a(i,:),[0 int64(nn*i)]); 

end
end

% /function out = rotate( a,n )
% out=zeros(100);
% n=n/37.5;
% for i=1:100
%     
%     out(i,:)=circshift(a(i,:),[0 int64(i*n)]); 
% end
% for i=1:100
%     out(i,:)=smooth(out(i,:));
% end
% for i=1:100
%     out(:,i)=smooth(out(:,i));
% end
% end

