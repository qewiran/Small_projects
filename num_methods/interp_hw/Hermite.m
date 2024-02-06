function H = Hermite (tbl_x, tbl_y, tbl_dy)
n=length(tbl_x);
P = [];
F = [transpose(tbl_y); transpose(tbl_dy)];
for j=1:n
    X = zeros(1, 2*n);
    for k=1:2*n
        X(1,k) = tbl_x(j)^(k-1);
    end
    P = [P;X];
end

for j=1:n
    dX = zeros(1,2*n);
    for k=2:2*n
        dX(1,k) = (k-1)* tbl_x(j)^(k-2);
    end
    P = [P;dX];
end
H= linsolve(P,F);
H = flipud(H);
H = double(H);
end