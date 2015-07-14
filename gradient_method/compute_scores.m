function  compute_scores( city_coordinates, file_name )
% comoute_scores: writes all scores of a 10 city TSP to a file
%   city_coordinates: a string that is 20 charachters long
%                       the first 10 char are the x coords of cities 1-10
%                       the last 10 chare are the y coords of ciries 1-10
%   file_name: the file name of the file to write to with the extention
unix(strcat('./JohnsonTrotter -n 10 -o',file_name,' -c ',city_coordinates));

end

