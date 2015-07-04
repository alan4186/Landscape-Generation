function scape = invGrad(edgeX,edgeY, g1,g2 )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here


% format edgeX and edgeY
% for now edges are constrained to 0
% scape=zeros(length(edgeY),length(edgeX));
% scape(:,1)=edgeY;
% scape(1,:)=edgeX;
% scape(2:end,2:end)=mean([mean(edgeY), mean(edgeX)]);
src=zeros(edgeY,edgeX);
waveX=sin(2*pi/edgeX:2*pi/edgeX:2*pi);
waveY=sin(2*pi/edgeY:2*pi/edgeY:2*pi);
src(:,1)=waveY;
src(:,end)=waveY;
src(1,:)=waveX;
src(end,:)=waveX;
 src=src*5;

% create mask
%msk=ones(length(edgeY),length(edgeX));
msk=ones(edgeY,edgeX);
msk(1,:)=0;
msk(:,1)=0;
msk(end,:)=0;
msk(:,end)=0;

scape=PoissonJacobi(src,g1,g2,msk);



end

