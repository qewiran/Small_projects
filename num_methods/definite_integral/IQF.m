function [coeffs,nodes] = IQF(limits, n, method)
Mu = calculateMu(limits, n, method);
X_pwrs = zeros(n,n);
if (method == "G")
    M = zeros(n,n);
    for j=1:n
        for k=1:n
            M(j,k) = Mu(j+k-1);
        end
    end
    nodePoly = linsolve(M,-Mu(n+1:end));
    nodePoly = flip(nodePoly);
    nodes = roots([1; (nodePoly)]);
    
else
    nodes = linspace(limits(1), limits(2), n);
end
for k = 1:n
    
    X_pwrs(k, :) = nodes .^ (k - 1);
end
coeffs = linsolve(X_pwrs, Mu(1:3));

end
