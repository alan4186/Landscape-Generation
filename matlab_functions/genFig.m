function out = genFig( structure,name )
A=structure.square(100:end-100,100:end-100);
b=genBucket(structure);
bs=genScape(b,b,1);
%as=genScapes(A,A,1);%genScapes uses sine in the roatate function
%as=as(100:end-100,100:end-100);
figure('Name',strcat(name,''));

% plot bucket version
subplot(1,2,2);
pcolor(bs(100:end-100,100:end-100));
shading flat;
colormap(jet);
pbaspect([1 1 1]);
title 'bucket'
% plot pcolor  rotate with sine version
% subplot(1,3,3);
% pcolor(as);
% shading flat;
% colormap(jet);
% pbaspect([1 1 1]);
% axis('off')
% title 'rot 90'
% plot city map
subplot(1,2,1)
scatter(structure.Xmap,structure.Ymap,'fill','r');
title 'City Map'
xlabel('x axis')
ylabel('y axis')
pbaspect([1 1 1])
axis([0 8 0 8]);
%savefig(strcat(name,'.fig'));



end

