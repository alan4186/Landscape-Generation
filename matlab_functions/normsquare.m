function out = normsquare( s )
si=size(s);
sl=reshape(s,[1,si(1)*si(2)]);
sl=mapminmax(sl);
out=reshape(sl,[si(1),si(2)]);


end

