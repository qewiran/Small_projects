function S = GlobalSpline(tbl_x, tbl_y)

n=length(tbl_x);
h = tbl_x(2)-tbl_x(1);

delta = zeros(1,n-1);
lambda = zeros(1,n-1);
b = zeros(1,n-1);
c = zeros(1,n);
d = zeros(1,n-1);

for k=3:n
    delta(k-1)= -1 / (4+delta(k-2));
    lambda(k-1) = (3/h^2*FiniteDiff(2,k-2,tbl_y) - lambda(k-2)) / (4+ delta(k-2));
end

for k=n:-1:2
    c(k-1)=delta(k-1)+lambda(k-1);
end

a = tbl_y(1:n);
a(1)=0;

for k=2:n
    b(k) = FiniteDiff(1, k-1, tbl_y) / h + h/3 * (2*c(k) + c(k-1));
    d(k) = (c(k) - c(k-1)) / (3*h);
end

syms x p;
S = [a; b; c; d];
S = flipud(S);

for k=2:n
    buff = poly2sym(S(:, k), p);
    buff_ = subs(buff,p,x-tbl_x(k));
    S(:,k)=double(sym2poly(buff_));
end


