function [h,s_hsv,v] = hsl2hsv(h,s,l)
h=h;
v = l + s*min(l,1-l);
if v==0
    s_hsv = 0 ;
else 
    s_hsv=2*(1-l/v);
end
end