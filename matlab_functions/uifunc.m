function uifunc(cities,name )
unix(strcat('./JT3 -n 10 -o tmp.txt -c ',cities));
tmp=importTSPscores('tmp.txt');
genFigsforprint(tmp,name);
delete('tmp.txt');
saveas(gcf,name);
end

