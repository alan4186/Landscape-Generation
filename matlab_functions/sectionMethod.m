function [scape,g1,g2]= figs( raw )
raw=reshape(raw,[(factorial(10)/factorial(7))*2,factorial(7)/2]);

[g1,g2]=Copy_of_scapeGenerator_fast(raw,1440,2520);
scape=invGrad(1440,2520,g1,g2);
surf(scape);
shading flat;
view(0,90);
scape=norm2d(scape)*65535;scape=uint16(scape);
scape=imresize(scape,10);
% imwrite(scape,name);

end

