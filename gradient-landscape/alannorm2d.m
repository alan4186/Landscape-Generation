function  out  = alannorm2d( A )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
out=(((A-min(min(A)))./(max(max(A))-min(min(A)))));

end

