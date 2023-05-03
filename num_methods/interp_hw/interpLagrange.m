clf;
syms x
fun = @(x) x.*log(x+1);

f1 = figure(1);
TL1 = tiledlayout(2,1);

nexttile;
title('5 nodes');
hold on;
grid on;

tbl1_x = -0.99:0.5:1.01;
tbl1_y = fun(tbl1_x);

og_plot = fplot(fun(x),[-1,1]);
og_plot.LineStyle = '--';

tbl1_plot = plot(tbl1_x,tbl1_y);
tbl1_plot.Marker='x';
tbl1_plot.MarkerSize = 10;
tbl1_plot.MarkerEdgeColor ='b';
tbl1_plot.Color= 'g';
tbl1_plot.LineWidth= 2;
tbl1_plot.MarkerEdgeColor = 'b';

Lagrange_plot1_eq = fplot(Lagrange(x, tbl1_x, tbl1_y),[-1, 1]);
Lagrange_plot1_eq.Color='k';
Lagrange_plot1_eq.LineWidth=2;

tbl1_cheb_x = ChebyshevNodes(tbl1_x);
tbl1_cheb_y = fun(tbl1_cheb_x);

Lagrange_plot1_cheb = fplot(Lagrange(x, tbl1_cheb_x, tbl1_cheb_y), [-1, 1]);
Lagrange_plot1_cheb.Color='r';
Lagrange_plot1_cheb.LineWidth=2;

legend('symbolic', 'linear', 'equal node distance', 'Chebyshev nodes')

err1 = LagrangeError(0.99, @Lagrange, fun, tbl1_x, tbl1_y)

nexttile;
hold on;
grid on;
title("9 nodes");

tbl2_x = -0.99:0.25:1.01;
length(tbl2_x)
tbl2_y = fun(tbl2_x);
n2 = length(tbl2_x);
fplot(fun(x),[-1,1], "LineStyle", '--');

tbl2_plot = plot(tbl2_x,tbl2_y);
tbl2_plot.Marker='x';
tbl2_plot.MarkerSize = 10;
tbl2_plot.Color= 'g';
tbl2_plot.LineWidth= 2;
tbl2_plot.MarkerEdgeColor = 'b';

Lagrange_plot2_eq = fplot(Lagrange(x, tbl2_x, tbl2_y),[-1, 1]);
Lagrange_plot2_eq.Color='k';
Lagrange_plot2_eq.LineWidth=2;

tbl2_cheb_x = ChebyshevNodes(tbl2_x);
tbl2_cheb_y = fun(tbl2_cheb_x);

Lagrange_plot2_cheb = fplot(Lagrange(x, tbl2_cheb_x, tbl2_cheb_y), [-1, 1]);
Lagrange_plot2_cheb.Color='r';
Lagrange_plot2_cheb.LineWidth=2;

legend('symbolic', 'linear', 'equal node distance', 'Chebyshev nodes')

err2 = LagrangeError(0.99, @Lagrange, fun, tbl2_x, tbl2_y)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

f2 = figure(2);

TL2 = tiledlayout(2,1);

nexttile;
title('5 nodes');
hold on;
grid on;

abs_fun = @(x) abs(x) .* x .* log(x+1);

tbl1_y_ = abs_fun(tbl1_x);

og_plot_ = fplot(abs_fun(x),[-1,1]);
og_plot_.LineStyle = '--';

tbl1_plot_ = plot(tbl1_x,tbl1_y_);
tbl1_plot_.Color= 'g';
tbl1_plot_.LineWidth= 2;
tbl1_plot_.Marker='x';
tbl1_plot_.MarkerSize = 10;
tbl1_plot_.MarkerEdgeColor = 'b';

Lagrange_plot1_eq_ = fplot(Lagrange(x, tbl1_x, tbl1_y_),[-1, 1]);
Lagrange_plot1_eq_.Color='k';
Lagrange_plot1_eq_.LineWidth=2;

tbl1_cheb_y_ = abs_fun(tbl1_cheb_x);

Lagrange_plot1_cheb_ = fplot(Lagrange(x, tbl1_cheb_x, tbl1_cheb_y_), [-1, 1]);
Lagrange_plot1_cheb_.Color='r';
Lagrange_plot1_cheb_.LineWidth=2;

legend('symbolic', 'linear', 'equal node distance', 'Chebyshev nodes')

err1_ = LagrangeError(0.99, @Lagrange, abs_fun, tbl1_x, tbl1_y_)


nexttile;
hold on;
grid on;
title("9 nodes");

tbl2_y_ = abs_fun(tbl2_x);
fplot(abs_fun(x),[-1,1], "LineStyle", '--');

tbl2_plot_ = plot(tbl2_x,tbl2_y_);
tbl2_plot_.Marker='x';
tbl2_plot_.MarkerSize = 10;
tbl2_plot_.MarkerEdgeColor = 'b';
tbl2_plot_.Color= 'g';
tbl2_plot_.LineWidth= 2;

Lagrange_plot2_eq_ = fplot(Lagrange(x, tbl2_x, tbl2_y_),[-1, 1]);
Lagrange_plot2_eq_.Color='k';
Lagrange_plot2_eq_.LineWidth=2;

tbl2_cheb_y_ = abs_fun(tbl2_cheb_x);

Lagrange_plot2_cheb_ = fplot(Lagrange(x, tbl2_cheb_x, tbl2_cheb_y_), [-1, 1]);
Lagrange_plot2_cheb_.Color='r';
Lagrange_plot2_cheb_.LineWidth=2;

legend('symbolic', 'linear', 'equal node distance', 'Chebyshev nodes')

err2_ = LagrangeError(0.99, @Lagrange, abs_fun, tbl2_x, tbl2_y_)

