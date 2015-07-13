function  doitall(s )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
cd ~/Documents/Landscape-Generation/resources_for_paper

mkdir cluster/Methodology/Gradient/
[scape,g1,g2]=figs(s.cluster.raw);
imwrite(scape,'cluster/Methodology/Gradient/landscape.tif');
imwrite(g1,'cluster/Methodology/Gradient/gradient1.tif');
imwrite(g2,'cluster/Methodology/Gradient/gradient2.tif');

mkdir football/Methodology/Gradient/
[scape,g1,g2]=figs(s.footbal.raw);
imwrite(scape,'football/Methodology/Gradient/landscape.tif');
imwrite(g1,'football/Methodology/Gradient/gradient1.tif');
imwrite(g2,'football/Methodology/Gradient/gradient2.tif');

mkdir four_corners/Methodology/Gradient/
[scape,g1,g2]=figs(s.four_courners.raw);
imwrite(scape,'four_corners/Methodology/Gradient/landscape.tif');
imwrite(g1,'four_corners/Methodology/Gradient/gradient1.tif');
imwrite(g2,'four_corners/Methodology/Gradient/gradient2.tif');

mkdir nested_triangles/Methodology/Gradient/
[scape,g1,g2]=figs(s.nestedTriangles.raw);
imwrite(scape,'nested_triangles/Methodology/Gradient/landscape.tif');
imwrite(g1,'nested_triangles/Methodology/Gradient/gradient1.tif');
imwrite(g2,'nested_triangles/Methodology/Gradient/gradient2.tif');

mkdir random/Methodology/Gradient/
[scape,g1,g2]=figs(s.random.raw);
imwrite(scape,'random/Methodology/Gradient/landscape.tif');
imwrite(g1,'random/Methodology/Gradient/gradient1.tif');
imwrite(g2,'random/Methodology/Gradient/gradient2.tif');

mkdir two_corners/Methodology/Gradient/
[scape,g1,g2]=figs(s.two_corners.raw);
imwrite(scape,'two_corners/Methodology/Gradient/landscape.tif');
imwrite(g1,'two_corners/Methodology/Gradient/gradient1.tif');
imwrite(g2,'two_corners/Methodology/Gradient/gradient2.tif');

mkdir two_lines/Methodology/Gradient/
[scape,g1,g2]=figs(s.twoLines.raw);
imwrite(scape,'two_lines/Methodology/Gradient/landscape.tif');
imwrite(g1,'two_lines/Methodology/Gradient/gradient1.tif');
imwrite(g2,'two_lines/Methodology/Gradient/gradient2.tif');
end

