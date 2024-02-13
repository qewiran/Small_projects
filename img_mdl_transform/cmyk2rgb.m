function [r,g,b] = cmyk2rgb(c,m,y,k)
r = (1-c)*(1-k); g = (1-m)*(1-k); b = (1-y)*(1-k);
end