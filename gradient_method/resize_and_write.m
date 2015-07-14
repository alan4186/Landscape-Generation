function  resize_and_write( landscape, filename )
% resize_and_write
% resize the given landscape and write it to a .tif file that is readable
% by terragen

landscape=imresize(landscape,10);
landscape=norm2d(landscape)*65535;
landscape=uint16(landscape);
imwrite(landscape,filename);
end

