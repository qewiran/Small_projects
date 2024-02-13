function [r,g,b] = hsv2RGB(h,s,v)
c = v*s;
x = c*(1-abs(mod(h,2)-1));
m = v-c;

if h<=1/6
    [r_,g_,b_] = [c,x,0];
end