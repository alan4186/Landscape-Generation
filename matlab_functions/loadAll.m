function out = loadAll(files)
out=struct;
for f=1:length(files)
    s=files{f}(1:end-4)
    [out(:).(genvarname(s))]=deal(importTSPscores(char(files{f})));
end
end

