function a = LSM(power, tbl_x, tbl_y)
syms x;
n=length(tbl_x);
m=power;
phi = sym(zeros(m,1));

for k=1:m+1
    phi(k)=x^(k-1);
end

Q = zeros(n,m);

for k=1:m+1
    for j=1:n
        Q(j,k)=double(subs(phi(k),x,tbl_x(j)));
    end
end

a = linsolve(transpose(Q)*Q, transpose(Q)*transpose(tbl_y));
a = flipud(a);                              