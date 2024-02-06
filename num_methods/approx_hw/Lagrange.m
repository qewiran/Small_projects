% this function returns Lagrange interpolation polynomial coefficients based on
% function values (Y) at nodes (X)

function P = Lagrange(X, Y)
syms x
N = length(X);
L=0;
for i=1:N
    l_i=1;
    for j=1:N
        if j~=i
            l_i = l_i .* (x-X(j)) ./ (X(i)-X(j)) ;
        end%if
    end%for_j
    L = L + Y(i).*l_i;
end%for_i
P = sym2poly(L); 
end
