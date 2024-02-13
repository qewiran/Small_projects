function [h,s_hsl ,l]=hsv2hsl(h,s,v)
l = v - v*s/2;

if (l==0 || l==1)
    s_hsl = 0;
else
    s_hsl =(v-l)/min(1,1-l);
    
end
h = h;