c_1 = length("Kirill");
c_2 = length("Evgenievich");
c_3 = length("Semyonov");

C = c_1 + c_2 + c_3;
A = -1;
B = 3;

f = @(x) exp(c_1 / 10 * x) + exp(c_2 / 10 * x) + exp(c_3 / 10 * x) - C * sin(x);

syms symF(t) dF(t) ddF(t) t;
symF(t) = exp(c_1 / 10 * t) + exp(c_2 / 10 * t) + exp(c_3 / 10 * t) - C * sin(t);
dF(t) = diff(symF(t));
ddF(t) = diff(dF(t));
df = matlabFunction(dF);
ddf = matlabFunction(ddF);

x = linspace(-1, 3);
plot(x, f(x));


fileId = fopen('passive_search.txt','w');
passiveSearch(f, -1, 3, fileId);
fclose(fileId);

fileId = fopen('dychotomy.txt','w');
dychotomy(f, -1, 3, fileId);
fclose(fileId);

fileId = fopen('golden_ratio.txt','w');
goldenRatio(f, -1, 3, fileId);
fclose(fileId);

fileId = fopen('Newton.txt','w');
Newton(f, df, ddf, (B + A) / 2, fileId);
fclose(fileId);

% disp("tangent")
% tangent(f, df, ddf, A, B);
