function [eval, err] = IQFerr(p, X)
    M_n = 26
    n = length(X);
    syms omega(x) x;
    omega(x) = 1;

    for k = 1:n
        omega(x) = omega(x) * (x - X(k));
    end

    eval = M_n / factorial(n) * int(abs(p * omega), x, a_b(1), a_b(2));
    err = -1;

end
