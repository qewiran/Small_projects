clc; clf;
[x, y] = ginput(12);

x = x .* 4;
y = y .* 4;

figure(1);
hold on;
plot(x, y, 'ko');

p11 = polyfit(x, y, 11);
t = 0:0.05:max(x) + 0.1;
f11 = polyval(p11, t);

plot(t, f11, 'Color', 'magenta', 'LineWidth', 2);

p11_inv = p11 .^ (-1);

sym_pol = poly2sym(p11);
sym_inv = poly2sym(p11_inv);
handle = matlabFunction(sym_pol);
inv_handle = matlabFunction(sym_inv);
[x_min, y_min] = fminsearch(handle, 1);
[x_max, y_max] = fminsearch(inv_handle, 1);

%plot ([x_max y_max], [x_min y_min], 'y*');

hold off;
