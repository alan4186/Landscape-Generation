function filteredim = filterDisp( hsize, sigma,im,t )
%hsize: [x y], a large y will smooth virticle ridges
G=fspecial('gaussian',hsize,sigma);
filteredim=imfilter(im, G,'same');
figure;
surf(filteredim(300:1299,300:1299));
% surf(filteredim(1400:1600,1400:1600));
shading flat;view(0,90);
title(t)
%figure
%surf(filteredim(1:200,1:200));
%shading flat
%title '1-200'
colormap(jet);
end

