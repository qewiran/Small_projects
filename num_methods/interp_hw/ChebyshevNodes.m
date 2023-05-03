function X_c = ChebyshevNodes(X)
n = length(X);
X_c = zeros(n);
b = X(n);
a = X(1);
for i=1:n
    X_c(i)= 1/2 * ((b-a) * cos((2*i+1) * pi / (2*n+2) ) + (b+a));
end
end
