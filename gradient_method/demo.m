function [ output_args ] = demo( cities,filename )
%demo: shows the gradient method
%   cities: a string of city coordinate formated for compute_scores()
%   filename: a file to save the final height map to.
compute_scores(cities,'tmt.txt');
ex=read_10_city_file('example_scores.txt');
[g1,g2]=Section_Generator(ex.square,1440,2520);
landscape=invGrad(1440,2520,g1,g2);
resize_and_write(landscape,'example_heightmap.tif');
end

