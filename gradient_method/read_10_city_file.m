function s = read_10_city_file( file )
Xmap=dlmread(file,' ',[0 0 0 9]);
Ymap=dlmread(file,' ',[1 0 1 9]);
raw=dlmread(file,' ',2, 0);
square=reshape(raw,[(factorial(10)/factorial(7))*2,factorial(7)/2]);
s=struct('Xmap',Xmap,'Ymap',Ymap,'raw',raw,'square',square);

end

