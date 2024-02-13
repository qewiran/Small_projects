function [h,s,l] = rgb2hsl(r,g,b);
[h,s,v] = rgb2hsv(r,g,b);
[h,s,l] = hsv2hsl(h,s,v);
end