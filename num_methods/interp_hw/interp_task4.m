syms x
fun = @(x) x.*log(x+1);
f = x*log(x+1);

tbl_x = -0.99:2/3:1.01;
tbl_y = fun(tbl_x);
dfun = diff(f);
dfun = matlabFunction(dfun);
tbl_dy = dfun(tbl_x);
n=length(tbl_x);
[S31_1, S31_2, S31_3] = HermiteSpline(n,1,tbl_x,tbl_y,tbl_dy)

figure(1);
clf;
hold on;

og_plot = fplot(fun,[-1 1]);
sp_10 = plot(tbl_x,tbl_y);
sp_10.Marker='x';
sp_10.MarkerSize = 10;
sp_10.MarkerEdgeColor ='b';
sp_10.Color= 'g';
sp_10.LineWidth= 2;

sp_31_1 = fplot(poly2sym(S31_1),[-1 -0.3235]);
sp_31_1.Color='r';
sp_31_1.LineWidth=2;

sp_31_2 = fplot(poly2sym(S31_2),[-0.3235 0.343]);
sp_31_2.Color='b';
sp_31_2.LineWidth=2;

sp_31_3 = fplot(poly2sym(S31_3),[0.343 1]);
sp_31_3.Color='b';
sp_31_3.LineWidth=2;

% H = Hermite(tbl_x,tbl_y,tbl_dy);

% H_plot = fplot(poly2sym(H), [-1 1]);

S = GlobalSpline(tbl_x, tbl_y);

S_1 = S(:,2);
S_2 = S(:,3);
S_3 = S(:,4);

s1_g_plot = fplot(poly2sym(S_1),[-1 -0.3235]);
s1_g_plot.LineWidth=2;
s1_g_plot.Color='k';
s2_g_plot = fplot(poly2sym(S_2),[-0.3235 0.343]);
s2_g_plot.LineWidth =2;
s2_g_plot.Color ='m';
s3_g_plot = fplot(poly2sym(S_3),[0.343 1]);
s3_g_plot.LineWidth =2;
s3_g_plot.Color ='m';


% legend('x*ln(x+1)','S_{10}', 'S_{31} (01)', 'S_{31}(12)', 'S_{32}(01)', 'S_{32}(12)');

figure(2);

clf;
hold on;
tbl_x = -0.99:1.01;
tbl_y = fun(tbl_x);
dfun = diff(f);
dfun = matlabFunction(dfun);
tbl_dy = dfun(tbl_x);
n=length(tbl_x);
[S31_1, S31_2] = HermiteSpline(n,1,tbl_x,tbl_y,tbl_dy)

og_plot = fplot(fun,[-1 1]);
sp_10 = plot(tbl_x,tbl_y);
sp_10.Marker='x';
sp_10.MarkerSize = 10;
sp_10.MarkerEdgeColor ='b';
sp_10.Color= 'g';
sp_10.LineWidth= 2;

sp_31_1 = fplot(poly2sym(S31_1),[-1 0.01]);
sp_31_1.Color='r';
sp_31_1.LineWidth=2;

sp_31_2 = fplot(poly2sym(S31_2),[0.01 1]);
sp_31_2.Color='b';
sp_31_2.LineWidth=2;

S = GlobalSpline(tbl_x, tbl_y);

S_1 = S(:,2);
S_2 = S(:,3);

s1_g_plot = fplot(poly2sym(S_1),[-1 0.01]);
s1_g_plot.LineWidth=2;
s1_g_plot.Color='k';
s2_g_plot = fplot(poly2sym(S_2),[0.01 1]);
s2_g_plot.LineWidth =2;
s2_g_plot.Color ='m';
