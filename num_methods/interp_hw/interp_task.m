clf;
syms x
fun = @(x) x.*log(x+1);
f = x*log(x+1);
tbl_x = -0.99:0.5:1.01;
n = length(tbl_x)
tbl_y = fun(tbl_x);
dfun = diff(f);
dfun = matlabFunction(dfun);
tbl_dy = dfun(tbl_x);

H = Hermite(tbl_x, tbl_y, tbl_dy)
