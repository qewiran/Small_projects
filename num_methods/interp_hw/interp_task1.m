
f1 = figure(1);
clf;

TL1 = tiledlayout(2,1);

nexttile;
title('5 nodes');
hold on;
grid on;

tbl1_x = -0.99:0.5:1.01;
tbl1_y = fun(tbl1_x);

Lagrange_1 = Lagrange(tbl1_x, tbl1_y);

og_plot = fplot(fun(x),[-1,1]);
og_plot.LineStyle = '--';

tbl1_plot = plot(tbl1_x,tbl1_y);
tbl1_plot.Marker='x';
tbl1_plot.MarkerSize = 10;
tbl1_plot.MarkerEdgeColor ='b';
tbl1_plot.Color= 'g';
tbl1_plot.LineWidth= 2;

Lagrange_plot1_eq = fplot(poly2sym(Lagrange_1),[-1, 1]);
Lagrange_plot1_eq.Color='k';
Lagrange_plot1_eq.LineWidth=2;

% Chebyshev nodes part

tbl1_cheb_x = ChebyshevNodes(tbl1_x);
tbl1_cheb_y = fun(tbl1_cheb_x);

tbl1_cheb_plot = plot(tbl1_cheb_x, tbl1_cheb_y, 'o', 'MarkerSize', 8, ...
    'HandleVisibility','off');
Lagrange_cheb_1 = Lagrange(tbl1_cheb_x, tbl1_cheb_y);

Lagrange_plot1_cheb = fplot(poly2sym(Lagrange_cheb_1), [-1, 1]);
Lagrange_plot1_cheb.Color='r';
Lagrange_plot1_cheb.LineWidth=2;

legend('symbolic', 'linear', 'equal node distance', 'Chebyshev nodes');

err1 = PolyError(0.99, Lagrange_1, fun)

nexttile; % more nodes
hold on;
grid on;
title("9 nodes");

tbl2_x = -0.99:0.25:1.01;
tbl2_y = fun(tbl2_x);

Lagrange_2 = Lagrange(tbl2_x, tbl2_y);

fplot(fun(x),[-1,1], "LineStyle", '--');

tbl2_plot = plot(tbl2_x,tbl2_y);
tbl2_plot.Marker='x';
tbl2_plot.MarkerSize = 10;
tbl2_plot.Color= 'g';
tbl2_plot.LineWidth= 2;
tbl2_plot.MarkerEdgeColor = 'b';

Lagrange_plot2_eq = fplot(poly2sym(Lagrange_2),[-1, 1]);
Lagrange_plot2_eq.Color='k';
Lagrange_plot2_eq.LineWidth=2;

% Chebyshev nodes part

tbl2_cheb_x = ChebyshevNodes(tbl2_x);
tbl2_cheb_y = fun(tbl2_cheb_x);

tbl2_cheb_plot = plot(tbl2_cheb_x, tbl2_cheb_y,'o', 'MarkerSize', 8,...
    'HandleVisibility','off');

Lagrange_2_cheb = Lagrange(tbl2_cheb_x, tbl2_cheb_y);

Lagrange_plot2_cheb = fplot(poly2sym(Lagrange_2_cheb), [-1, 1]);
Lagrange_plot2_cheb.Color='r';
Lagrange_plot2_cheb.LineWidth=2;

legend('symbolic', 'linear', 'equal node distance', 'Chebyshev nodes');

err2 = PolyError(0.99, Lagrange_2, fun)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%