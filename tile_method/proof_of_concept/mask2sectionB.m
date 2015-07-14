function [scape, mask] = mask2sectionB( mask )
% mask is a matrix to pull samples from
s=size(mask);
P=0.01;
R=P*range(mask(:));
% normalize mask
mask=alannorm2d(mask);

%init scape
scape=zeros(s(1),s(2));
scape=scape+mean(mask(:));

% neighborhood: first row and col is all 0
% 0 0 0
% 0 X
mask=reshape(mask,[1,s(1)*s(2)]);
l=length(mask);
for j=2:s(2)-1
    for i=2:s(1)
        nm=mean([scape(i-1,j-1:j+1) scape(i,j-1)]);
        %find point within R% of nm
        count=0;
        while 1
            x=randi(l);

            if abs((mask(x)-nm))<R
                break
            end
            count=count+1;
            if count>10000
                R=R+(R*0.01);
            end
        end
        scape(i,j)=mask(x);
        mask(x)=[];
        l=l-1;
    end
end

end

