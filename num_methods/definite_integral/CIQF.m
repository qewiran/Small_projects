function J = CIQF (f, limits, n, m, method)
X = linspace (limits(1), limits(2),n+1);
J = 0;
for j = 2:n
    limits_curr = [X(j-1) X(j)];
    [A,X_nodes] = IQF(limits_curr, m, method);

    F_curr = arrayfun(f,X_nodes);
    J = J + dot(A, F_curr);
end

end
