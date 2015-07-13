function filteredim = gfilter( hsize, sigma,im )
%hsize: [x y], a large y will smooth virticle ridges
G=fspecial('gaussian',hsize,sigma);
filteredim=imfilter(im, G,'same');
end
