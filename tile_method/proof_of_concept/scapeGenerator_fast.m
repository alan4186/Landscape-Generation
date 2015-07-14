function [ g1, g2]= scapeGenerator_fast( square ,sectionsize)

% create mask
mask1=square(1:sectionsize,1:round(sectionsize/10));
mask2=square(1:round(sectionsize/10),1:sectionsize);
mask2=transpose(mask2);
%generate gradients
g1=zeros(sectionsize);
for k=1:2
    for i=1:30
        z=zeros(sectionsize);
        posx=randi(sectionsize-round(sectionsize/10));

        z(:,posx:posx+round(sectionsize/10)-1)=mask1;
        angle=randi([-90 90],1,1);
        z=rot(z,angle);
        g1 = g1+z;
    end
    g1=rot90(g1);
end

g2=zeros(sectionsize);
for k=1:2
    for i=1:30
        z=zeros(sectionsize);
        posx=randi(sectionsize-round(sectionsize/10));
        z(:,posx:posx+round(sectionsize/10)-1)=mask2;
        angle=randi([-90 90],1,1);
        z=rot(z,angle);
        g2 = g2+z;
    end
    g2=rot90(g2);
end

g1=norm2d(g1)*10-5;
g2=norm2d(g2)*10-5;
end
   

