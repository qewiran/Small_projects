clf;
f = @(x) x ^ 2 * sin(x) + log(abs(x));
xl = -8;
xr = -4;
fplot(f,[-10 10]);
figure(1);
m = dichotomy(xl, xr, f);
disp(m);
