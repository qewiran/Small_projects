syms x
fun = @(x) x.*log(x+1);
f = x*log(x+1);

tbl_x = -0.99:1.01;
tbl_y = fun(tbl_x);
dfun = diff(f);
dfun = matlabFunction(dfun);
tbl_dy = dfun(tbl_x);

tbl_cheb_x = ChebyshevNodes(tbl_x);
tbl_cheb_y = fun(tbl_cheb_x);
tbl_cheb_dy = dfun(tbl_cheb_x);

Hermite_poly = Hermite(tbl_x,tbl_y,tbl_dy);
Hermite_poly_ = Hermite(tbl_cheb_x, tbl_cheb_y,tbl_cheb_dy);

d2fun = diff(sym(dfun));
d2fun = matlabFunction(d2fun);

tbl_d2y=d2fun(tbl_x);
tbl_cheb_d2y = d2fun(tbl_cheb_x);

Hermite2_poly = Hermite2(tbl_x, tbl_y, tbl_dy,tbl_d2y);
Hermite2_poly_ = Hermite2(tbl_cheb_x, tbl_cheb_y, tbl_cheb_dy,tbl_cheb_d2y);


figure(3);
clf;
hold on;

og_plot = fplot(fun(x),[-1 1]);
og_plot.LineStyle = '--';

tbl_plot = plot(tbl_x, tbl_y, 'or', 'HandleVisibility', 'off');

tbl_cheb_plot = plot (tbl_cheb_x, tbl_cheb_y, 'ob',  'HandleVisibility', 'off');

Hermite_cheb_nodes_plot = fplot(poly2sym(Hermite_poly_),[-1 1], 'b','LineWidth',2);

Hermite_eq_nodes_plot = fplot(poly2sym(Hermite_poly), [-1 1], 'r','LineWidth',2);

legend('true function','Chebyshev nodes', 'equal distance nodes');

dH = polyder(Hermite_poly);
dH_ = polyder(Hermite_poly_);

error_eq = PolyError(0.99, Hermite_poly, fun)
error_cheb = PolyError(0.99, Hermite_poly_, fun)
error_diff_eq = PolyError(0.99, dH, dfun)
error_diff_cheb = PolyError(0.99, dH_, dfun)

figure(4);
clf;
hold on;
og_plot = fplot(fun(x),[-1 1]);
og_plot.LineStyle = '--';

tbl1_plot = plot(tbl_x, tbl_y, 'or', 'HandleVisibility', 'off');

tbl1_cheb_plot = plot (tbl_cheb_x, tbl_cheb_y, 'ob',  'HandleVisibility', 'off');

Hermite2_cheb_nodes_plot = fplot(poly2sym(Hermite2_poly_),[-1 1], 'b','LineWidth',2);

Hermite2_eq_nodes_plot = fplot(poly2sym(Hermite2_poly), [-1 1], 'r','LineWidth',2);

legend('true function','Chebyshev nodes', 'equal distance nodes');

dH2 = polyder(Hermite2_poly);
dH2_ = polyder(Hermite2_poly_);

d2H2=polyder(dH2);
d2H2_=polyder(dH2_);

error2_eq = PolyError(0.99, Hermite2_poly, fun)
error2_cheb = PolyError(0.99, Hermite2_poly_, fun)
error2_diff_eq = PolyError(0.99, dH2, dfun)
error2_diff_cheb = PolyError(0.99, dH2_, dfun)
error2_diff2_eq = PolyError(0.99, d2H2, dfun)
error2_diff2_cheb = PolyError(0.99, d2H2_, dfun)




