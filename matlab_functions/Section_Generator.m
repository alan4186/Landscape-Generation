function [ g1, g2]= scapeGenerator_fast( square ,row, col)
rng default;
len=100;
width=20;
% create mask
% mask1=square(1:len,1:width);
% mask2=square(1:width,1:len);
% mask2=transpose(mask2);
%generate gradients
g1=zeros(row,col);
g2=zeros(row,col);
for k=1:25:col-25
% for k=1:50:col-25
    k
    for i=1:25:row-100
%     for i=1:50:row-100
        mask1=square(i:i+len-1,k:k+width-1);
        mask2=square(i:i+len-1,k:k+width-1);
        for q=1:1
%         for q=1:5
            z=zeros(row,col);
            y=zeros(row,col);
            posx=randi([k,k+10]);
            posy=randi([i, i+10]);
            posx2=randi([k,k+10]);
            posy2=randi([i, i+10]);
            z(posy:posy+len-1,posx:posx+width-1)=mask1;
            y(posy2:posy2+len-1,posx2:posx2+width-1)=mask2;
            angle=randi([-90 90],1,1);
            angle2=randi([-90 90],1,1);
            z=rot(z,angle);
            y=rot(y,angle2);
            g1 = g1+z;
            g2= g1+y;
            
        end
    end
%      g1=rot90(g1);
end


% for k=1:2
%     for i=1:200
%         z=zeros(sectionsize);
%         posx=randi(sectionsize-round(sectionsize/10));
%         posy=randi(sectionsize-round(sectionsize/10));
%         z(posy:posy+round(sectionsize/10)-1,posx:posx+round(sectionsize/10)-1)=mask2;        angle=randi([-90 90],1,1);
%         z=rot(z,angle);
%         g2 = g2+z;
%     end
%     g2=rot90(g2);
% end

g1=norm2d(g1)*10-5;
g2=norm2d(g2)*10-5;
end
   

