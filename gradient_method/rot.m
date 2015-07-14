function out = rot( a,n )
s=size(a);
out=zeros(s(1),s(2));
nn=n/37.5;
for i=1:s(1)
    % previoisly stable
    %out(i,:)=circshift(a(i,:),[0 int64(nn*(i+length(a)/2)*sin(i))]);
    
    % for testing:
    out(i,:)=circshift(a(i,:),[0 int64(nn*i)]); 

end
end

