function L = Lagrange(x, X, Y)
N = length(X);
L=0;

for i=1:N
    l_i=1;
    for j=1:N
        if j~=i
            l_i = l_i .* (x-X(j)) / (X(i)-X(j)) ;
        end%if
    end%for
    L = L + Y(i).*l_i;
end%for
end
