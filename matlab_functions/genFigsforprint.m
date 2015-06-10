function  genFigsforprint( s,name )
% save figures to print later
fig=figure;set(fig,'visible','on');
title(name);
subplot(1,2,1)
pcolor(s.scape(100:end-100,100:end-100))
shading flat;
colormap jet;
axis off;
pbaspect([1 1 1]);

subplot(1,2,2);

scatter(s.Xmap,s.Ymap,'k','filled');
axis([0 8 0 8]);
grid on;
pbaspect([1 1 1]);
labels = num2str((1:10)','%d');    %'
text(s.Xmap, s.Ymap, labels, 'horizontal','left', 'vertical','bottom')
title(name);


fig.PaperUnits = 'inches';
fig.PaperPosition = [0 0 6 3];
fig.PaperPositionMode = 'manual';
%print(name,'-dpng','-r0')
%saveas(fig,name,'png');
end

