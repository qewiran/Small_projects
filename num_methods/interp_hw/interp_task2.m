

f2 = figure(2);

clf;

TL2 = tiledlayout(2,1);
nexttile;
title('5 nodes');
hold on;
grid on;

abs_fun = @(x) abs(x) .* x .* log(x+1);

tbl1_y_ = abs_fun(tbl1_x);
Lagrange_1_ = Lagrange(tbl1_x, tbl1_y_);

og_plot_ = fplot(abs_fun(x),[-1,1]);
og_plot_.LineStyle = '--';

tbl1_plot_ = plot(tbl1_x,tbl1_y_);
tbl1_plot_.Color= 'g';
tbl1_plot_.LineWidth= 2;
tbl1_plot_.Marker='x';
tbl1_plot_.MarkerSize = 10;
tbl1_plot_.MarkerEdgeColor = 'b';

Lagrange_plot1_eq_ = fplot(poly2sym(Lagrange_1_),[-1, 1]);
Lagrange_plot1_eq_.Color='k';
Lagrange_plot1_eq_.LineWidth=2;

tbl1_cheb_y_ = abs_fun(tbl1_cheb_x);
tbl1_cheb_plot_ = plot(tbl1_cheb_x, tbl1_cheb_y_,'o', 'MarkerSize', 8, ...
'HandleVisibility','off');

Lagrange_cheb_1_ = Lagrange(tbl1_cheb_x, tbl1_cheb_y_);

Lagrange_plot1_cheb_ = fplot(poly2sym(Lagrange_cheb_1_), [-1, 1]);
Lagrange_plot1_cheb_.Color='r';
Lagrange_plot1_cheb_.LineWidth=2;

legend('symbolic', 'linear', 'equal node distance', 'Chebyshev nodes');

err1_ = PolyError(0.99, Lagrange_1_, abs_fun)
err1_cheb1_ = PolyError(0.99,Lagrange_cheb_1_, abs_fun);


nexttile;
hold on;
grid on;
title("9 nodes");

tbl2_y_ = abs_fun(tbl2_x);
Lagrange_2_ = Lagrange(tbl2_x, tbl2_y);

fplot(abs_fun(x),[-1,1], "LineStyle", '--');

tbl2_plot_ = plot(tbl2_x,tbl2_y_);
tbl2_plot_.Marker='x';
tbl2_plot_.MarkerSize = 10;
tbl2_plot_.MarkerEdgeColor = 'b';
tbl2_plot_.Color= 'g';
tbl2_plot_.LineWidth= 2;

Lagrange_plot2_eq_ = fplot(poly2sym(Lagrange_2_),[-1, 1]);
Lagrange_plot2_eq_.Color='k';
Lagrange_plot2_eq_.LineWidth=2;

tbl2_cheb_y_ = abs_fun(tbl2_cheb_x);
tbl2_cheb_plot_ = plot(tbl2_cheb_x, tbl2_cheb_y_, ...
    'HandleVisibility','off','Marker', 'o', 'MarkerSize', 8);

Lagrange_cheb_2_ = Lagrange(tbl2_cheb_x, tbl2_cheb_y_);

Lagrange_plot2_cheb_ = fplot(poly2sym(Lagrange_cheb_2_), [-1, 1]);
Lagrange_plot2_cheb_.Color='r';
Lagrange_plot2_cheb_.LineWidth=2;

legend('symbolic','linear' ,'equal node distance', 'Chebyshev nodes');

err2_ = PolyError(0.99, Lagrange_2_, abs_fun)
err2_cheb2_ = PolyError(0.99,Lagrange_cheb_2_, abs_fun);

