function [ output_args ] = gengroupedfig( files,r,out )
% create  a figure for each group
for i = 1:6
    
    
    numing=sum(out(i,:));
    if numing~=0
        figure('Name',strcat('group ',num2str(i)));
    currentplot=0;
    for j=1:35
        if out(i,j)==1
        currentplot=currentplot+1;
        subplot(2,numing,currentplot);
        scatter(r.(genvarname(files{j})).Xmap,r.(genvarname(files{j})).Ymap);
        axis([0 8 0 8]);
        pbaspect([1 1 1]);
        title(files{j});
        
        subplot(2,numing,currentplot+numing);
        pcolor(r.(genvarname(files{j})).scape);
        shading flat;
        colormap gray;
        pbaspect([1 1 1]);
        end
    end
    end
    
end


end

