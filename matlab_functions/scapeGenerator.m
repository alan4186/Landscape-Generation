function [scapen, in1, in2]= scapeGenerator( square ,sectionsize,scapesize,filename)

% create mask
mask1=square(1:sectionsize,1:round(sectionsize/10));
mask2=square(1:round(sectionsize/10),1:sectionsize);
mask2=transpose(mask2);
g1=zeros(scapesize);
g2=zeros(scapesize);
for h=1:sectionsize:scapesize
    for g=1:sectionsize:scapesize
        %generate gradients
        in1=zeros(sectionsize);
        for k=1:2
            for i=1:30
                z=zeros(sectionsize);
                posx=randi(sectionsize-round(sectionsize/10));

                z(:,posx:posx+round(sectionsize/10)-1)=mask2sectionB(mask1);
                angle=randi([-90 90],1,1);
                z=rot(z,angle);
                in1 = in1+z;
            end
            in1=rot90(in1);
        end
        g1(h:h+sectionsize-1,g:g+sectionsize-1)=in1;
        
        in2=zeros(sectionsize);
        for k=1:2
            for i=1:30
                z=zeros(sectionsize);
                posx=randi(sectionsize-round(sectionsize/10));
                z(:,posx:posx+round(sectionsize/10)-1)=mask2sectionB(mask2);
                angle=randi([-90 90],1,1);
                z=rot(z,angle);
                in2 = in2+z;
            end
            in2=rot90(in2);
        end
        g2(h:h+sectionsize-1,g:g+sectionsize-1)=in2;
    end
end
        

% 
% fprintf('inputs generated.\n');
% % normalize to -1 1
% g1=alannorm2d(g1)*2-1;
% g2=alannorm2d(g2)*2-1;
% % mean normalization
% g1=g1-mean(g1(:));
% g2=g2-mean(g2(:));
% % resize
% g1=imresize(g1,[length(g1)*3 length(g1)*3]);
% g2=imresize(g2,[length(g2)*3 length(g2)*3]);
% % integrate
% scape=intgrad2(g1,g2);
% fprintf('integration complete\n');
% scape=gfilter([5 5],3,scape);
% % mean normalization
% scape=scape-mean(scape(:));
% % normalize scape to -1 1
% scape=alannorm2d(scape)*2-1;
% % generate noise
% % noise=square(1:1010,1:1010);
% %noise=square(1:scapesize+10,1:scapesize+10);
% %noise=gfilter([10 10],3,rots(noise,90));
% %noise=gfilter([10 10],3, noise);
% % trim edges of filtered noise
% %noise=noise(6:1005,6:1005);
% % normalize noise to 0 1
% %noise=alannorm2d(noise);
% % scale noise to have range of 0.05 and normalize to -1 1
% %noise=noise*0.025;
% %noise=noise*2-1;
% % add noise to scape
% scapen=scape;%+noise;
% % convert to uint16
% scapen=alannorm2d(scapen)*65535;
% scapen=uint16(scapen);
% imwrite(scapen,filename);
% fprintf('file saved.\n');
scapen=-1;
end
% 
