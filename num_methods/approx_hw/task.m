syms x sym_f(x);

f = @(x) exp(x) .* (x-2) .^2;
sym_f(x) = exp(x)*(x-2)^2;

figure(1);
clf;
hold on;
% исходная функция
og_plot = fplot(sym_f, [-1 1]);
og_plot.LineStyle = '--';

%% МНК по равноотстоящим
tbl_x = -1:1/2:1;
tbl_y = f(tbl_x);
n = length(tbl_x);

p1 = LSM(3, tbl_x, tbl_y);

p1_plot = fplot(poly2sym(p1),[-1 1] );
p1_plot.LineWidth = 2;
p1_plot.Color = 'g';

tbl_x2 = -1:1/100:1;
tbl_y2 = f(tbl_x2);

p1_ = LSM(3,tbl_x2, tbl_y2);

p1_plot_ = fplot(poly2sym(p1_),[-1 1] );
p1_plot_.LineWidth = 2;
p1_plot_.Color = [0 0.6 0.5];

%% МНК по чебышёвским

tbl_x_cheb=ChebyshevNodes(tbl_x);
tbl_y_cheb= f(tbl_x_cheb);
p1_cheb = LSM(3,tbl_x_cheb, tbl_y_cheb);
p1_plot = fplot(poly2sym(p1_cheb),[-1 1] );
p1_plot.LineWidth = 2;
p1_plot.Color = 'b';

%% с погрешностью
ep = rand(1,ceil(n/2), "double");
eps_len = length(ep);
tbl_y_eps = tbl_y;
for k=1:n
    if k<=eps_len
        tbl_y_eps(k) = tbl_y_eps(k) * ( 1 - 0.05*ep(k)); % 5% погрешность
    else
        tbl_y_eps(k) = tbl_y_eps(k) * ( 1 + 0.05*ep(n-k+1));
    end
end

p2 = LSM(3,tbl_x, tbl_y_eps);

p2_plot = fplot(poly2sym(p2), [-1 1]);
p2_plot.LineWidth = 2;
p2_plot.Color = 'k';

%% 3n значений

Y = [tbl_y_eps tbl_y tbl_y_eps*1.05];
X = [tbl_x tbl_x tbl_x];

p3 = LSM(3,X,Y);
p3_plot = fplot(poly2sym(p3), [-1 1]);
p3_plot.LineWidth = 1;
p3_plot.Color = [0 1 1];

%% сравнение с лагранжевым ИП
L = Lagrange(tbl_x,tbl_y);

L_plot = fplot(poly2sym(L),[-1 1]);
L_plot.Color = 'm';
L_plot.LineWidth=2;
L_plot.LineStyle='--';

L_= Lagrange(tbl_x, tbl_y_eps);

L_plot = fplot(poly2sym(L_),[-1 1]);
L_plot.Color = [0.8 0 0.1];
L_plot.LineWidth=2;
L_plot.LineStyle='-.';

%% с помощью многочленов Лежандра

syms l(x) k Q

Q=sym(0);
for k=0:3
    if k==0
        Q = int(sym_f(x),[-1 1])/2;
    else
        l(x) = 1/(factorial(k)*2^k)*diff((x^2-1)^k,k);
        Q = Q + int(sym_f(x)*l(x), -1, 1) / int(l(x)^2,-1,1)*l(x);
    end
end
disp("Legendre polynomial coeff-s ");
disp(double(sym2poly(Q)));
Lgndr_plot = fplot(Q,[-1 1]);
Lgndr_plot.LineWidth=2;
Lgndr_plot.Color='y';

legend('$e^x(x-2)^2$', 'LSM $h=1/2$', 'LSM $h=1/100$','LSM Chebyshev','LSM w/ error', ...
'3nx3n', 'Lagrange', 'Lagrange w/ error', 'Legendre poly',...
 'Interpreter', 'Latex')