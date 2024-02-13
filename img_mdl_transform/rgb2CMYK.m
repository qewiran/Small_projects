function [c,m,y,k] = rgb2cmyk(r,g,b)

k = 1-max(r,max(g,b))
c = 1-r-k;
m = 1-g-k;
y = 1-b-k;

out= [c,m,y,k]/(1-k);
c = out(1); m = out(2); y = out(3); 

end