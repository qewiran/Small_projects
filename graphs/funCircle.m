function funCircle(power, center, depth)

    t = [0:pi / 36:pi];

    if (power < depth)
        offset = 2 ^ (-power);
        radius = 2 ^ power;
        p1 = plot(cos(t) / radius + center + offset, sin(t) / radius);
        p2 = plot(cos(t) / radius - center - offset, sin(t) / radius);
        p1.Color = [offset 0 1];
        p2.Color = [offset 1 0];
        funCircle(power + 1, center + offset, depth);
        funCircle(power + 1, center - offset, depth);
    end %if

end %function
