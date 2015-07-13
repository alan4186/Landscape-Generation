function scapen = gradientscape( square ,filename)
in1=mask2tri(square(1:300,1:300));
in2=mask2tri(square(301:600,301:600));

% normalize to -1 1
in1=alannorm2d(in1)*2-1;
in2=alannorm2d(in2)*2-1;
% mean normalization
in1=in1-mean(in1(:));
in2=in2-mean(in2(:));
% resize
in1=imresize(in1,[1000 1000]);
in2=imresize(in2,[1000 1000]);
% integrate
scape=intgrad2(in1,in2);
% mean normalization
scape=scape-mean(scape(:));
% normalize scape to -1 1
scape=alannorm2d(scape)*2-1;
% generate noise
noise=square(1:1010,1:1010);
noise=gfilter([10 10],3,rots(noise,90));
noise=gfilter([10 10],3, noise);
% trim edges of filtered noise
noise=noise(6:1005,6:1005);
% normalize noise to 0 1
noise=alannorm2d(noise);
% scale noise to have range of 0.05 and normalize to -1 1
noise=noise*0.025
noise=noise*2-1;
range(noise(:))% to confirm range
% add noise to scape
scapen=scape+noise;
% convert to uint16
scapen=alannorm2d(scapen)*65535;
scapen=uint16(scapen);
imwrite(scapen,filename);
end

