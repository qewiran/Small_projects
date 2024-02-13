function [hue,saturation, value] = rgb2hue (r,g,b)
M = max (r, max(g,b));
m = min(r,min(g,b));
Chr = M - m;

if Chr==0
    hue=0;
end

switch M
    case r
        segment = (g-b)/Chr;
        if segment<0
            shift = 6; %360/6
        else
            shift = 0; %0/6
        end
        
    case g
        segment = (b-r)/Chr;
        shift = 2; %120/6
        
    case b
        segment = (r-g)/Chr;
        shift = 4; %240/6
end

hue = segment+shift;
hue = hue/6;

lightness = (M + m)/2;

if (M==0)
    saturation=0;
else
    saturation = Chr/M;
end

value = M;

