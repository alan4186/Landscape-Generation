function out = genScapes( A,B,scaleFactor )
% generate noise matrix
noise=gfilter([5 5],3,rots(B,90));
noise=gfilter([5 5],3,noise);
normNoise=mapminmax(noise);

% generate base landscape matrix
scape=gfilter([40 40],300,rots(A,90));
scape=gfilter([40 40],300,scape);
% leave base landscape scaled to whatever height the soln are

% mix noixe and the base landscape
out=scape+scaleFactor*normNoise;

% figure;
% surf(out(100:end-100,100:end-100));
% shading flat;
% view(0,90);
% colormap(jet);
end

