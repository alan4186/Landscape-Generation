function scape = mask2tri( mask )
% mask is a square matrix to pull samples from
% xl any yl are the lengths of the output landscape to be generated
s=length(mask);
P=0.0005;
R=P*range(mask);
% normalize mask
mask=alannorm2d(mask);

%init scape
scape=zeros(length(mask));
scape=scape+(mean(mean(mask))*0.75);

% neighborhood: first row and col is all 0
% 0 0 0
% 0 X

l=length(mask);
for t=1:4
    c=1;%the coordinates of the first corner
    for i=1:(((l-1)/2)+1)%number of circles
        c=c+1;
    

        % do the top row
        for j=c:l-c+1
            %square(c,j)=num;
            nm=mean([scape(c-1,j-1:j+1) scape(c,j-1)]);
            %find point within R% of nm
            while 1
                x=randi(s);
                y=randi(s);
                if abs((mask(x,y)-nm))<R
                    break
                end
            end
            scape(c,j)=mask(x,y);
        end
    end
    scape=rot90(scape);
end

end



