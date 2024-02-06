function Mu = calculateMu(limits, n, method)
if (method == "NC")
    Mu = ones(n,1);
else 
    Mu = ones(2*n,1);
end
delta_b = ( limits(2) - 1/10 );
delta_a = ( limits(1) - 1/10 );

% syms x p(x);
% p(x) = (x-1/10)^(-1/5);

% Mu(1) = integral( matlabFunction(p(x)),limits(1), limits(2));
% Mu(2) = integral( matlabFunction(x*p(x)),limits(1), limits(2));
% Mu(3) = integral( matlabFunction(x^2*p(x)),limits(1), limits(2));


Mu(1) = 5/4 * (delta_b^(4/5)-delta_a^(4/5));
Mu(2) = 5/9 * (delta_b^(9/5)-delta_a^(9/5)) + 1/8 * (delta_b^(4/5)-delta_a^(4/5));
Mu(3) = 5/14 * (delta_b^(14/5)-delta_a^(14/5)) + 1/9 * (delta_b^(9/5)-delta_a^(9/5)) + 1/80 * (delta_b^(4/5)-delta_a^(4/5));

if method=="G"
    % Mu(4) = integral( matlabFunction(x^3*p(x)),limits(1), limits(2));
    % Mu(5) = integral( matlabFunction(x^4*p(x)),limits(1), limits(2));
    % Mu(6) = integral( matlabFunction(x^5*p(x)),limits(1), limits(2));
    Mu(4) = 5/19 * (delta_b^(19/5)-delta_a^(19/5)) + 3/28 * (delta_b^(14/5)-delta_a^(14/5)) + 1/60 * (delta_b^(9/5)-delta_a^(9/5)) + 1/800 * (delta_b^(4/5)-delta_a^(4/5));
    Mu(5) = 5/24 * (delta_b^(24/5)-delta_a^(24/5)) + 2/19 * (delta_b^(19/5)-delta_a^(19/5)) + 3/140 * (delta_b^(14/5)-delta_a^(14/5)) + 1/450 * (delta_b^(9/5)-delta_a^(9/5)) + 1/8000 * (delta_b^(4/5)-delta_a^(4/5));
    Mu(6) = 5/29 * (delta_b^(29/5)-delta_a^(29/5)) + 5/48 * (delta_b^(24/5)-delta_a^(24/5)) + 1/38 * (delta_b^(19/5)-delta_a^(19/5)) + 1/280 * (delta_b^(14/5)-delta_a^(14/5)) + 1/3600 * (delta_b^(9/5)-delta_a^(9/5)) + 1/80000 * (delta_b^(4/5)-delta_a^(4/5));
end
end