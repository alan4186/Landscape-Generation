function  prof_of_concept(  )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

% set status to 1
statusID=fopen('.status.txt','w');
fprintf(statusID,'%d',1);
fclose(statusID);

f='.spacescores.txt';
figure;
g=dlmread(f);
size(g)
tic;
while 1
    statusID=fopen('.status.txt','r');
    status=fscanf(statusID,'%u');
    fclose(statusID);
    if status==0
        % read data
        g=dlmread(f);
        % use the decimal part of the first score as seed
        sd=g(1,1)
        integ=floor(sd);
        fract=uint32((sd-integ)*100000);
        rng(fract);
        % compute landscape
%         [~,g1,g2]=scapeGenerator(g,100,10,'deleteme.txt');
        [g1,g2]=scapeGenerator_fast(g,100);
        scape=invGrad(100,100,g1,g2);
        toc;
        surf(scape);
%         view(0,90);
        
        % wait for more input 
        inp=input('ASWD:\n','s');
        while (inp~='a')&&(inp~='s')&&(inp~='d')&&(inp~='w')
            inp=input('ASWD:err\n','s');

        end
        tic;
        inpID=fopen('.inp.txt','w');
        fprintf(inpID,'%c',inp);
        fclose(inpID);
        % alert c that new inp is ready
        statusID=fopen('.status.txt','w');
        fprintf(statusID,'%d',1);
        fclose(statusID);
        fprintf('status: 1\n');
    end %if
    
end

end

