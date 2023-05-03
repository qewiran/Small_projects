function xc = dichotomy(xl, xr, f)
    eps = 1e-2;

    while xr - xl > eps
        hold on;
        plot([xl xr], [f(xl) f(xr)], 'ro');
        plot([xl xr], [0 f(xl)], 'k');
        plot([xl xr], [0 f(xr)], 'k');
        plot([xl xr], [0 0], 'r');
        xc = (xl + xr) / 2;

        if f(xl) * f(xr) > 0
            xr = xc;
        elseif f(xl) * f(xr) < 0
            xl = xc;
        end
        pause(0.5);
    end
end
