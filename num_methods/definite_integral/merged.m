function Mu = calculateMu(limits, n, method)
    if (method == "NC")
        Mu = ones(n,1);
    else 
        Mu = ones(2*n,1);
    end
    % delta_b = ( limits(2) - 1/10 );
    % delta_a = ( limits(1) - 1/10 );
    
    syms x p(x);
    p(x) = (x-1/10)^(-1/5);
    
    Mu(1) = integral( matlabFunction(x*p(x)),limits(1), limits(2));
    Mu(2) = integral( matlabFunction(x^2*p(x)),limits(1), limits(2));
    Mu(3) = integral( matlabFunction(x^3*p(x)),limits(1), limits(2));
    
    
    % Mu(1) = 5/4 * (delta_b^(4/5)-delta_a^(4/5));
    % Mu(2) = 5/9 * (delta_b^(9/5)-delta_a^(9/5)) + 1/8 * (delta_b^(4/5)-delta_a^(4/5));
    % Mu(3) = 5/14 * (delta_b^(14/5)-delta_a^(14/5)) + 1/9 * (delta_b^(9/5)-delta_a^(9/5)) + 1/80 * (delta_b^(4/5)-delta_a^(4/5));
    
    if method=="G"
        Mu(1) = integral( matlabFunction(x^4*p(x)),limits(1), limits(2));
        Mu(2) = integral( matlabFunction(x^5*p(x)),limits(1), limits(2));
        Mu(3) = integral( matlabFunction(x^6*p(x)),limits(1), limits(2));
        % Mu(4) = 5/19 * (delta_b^(19/5)-delta_a^(19/5)) + 3/28 * (delta_b^(14/5)-delta_a^(14/5)) + 1/60 * (delta_b^(9/5)-delta_a^(9/5)) + 1/800 * (delta_b^(4/5)-delta_a^(4/5));
        % Mu(5) = 5/24 * (delta_b^(24/5)-delta_a^(24/5)) + 2/19 * (delta_b^(19/5)-delta_a^(19/5)) + 3/140 * (delta_b^(14/5)-delta_a^(14/5)) + 1/450 * (delta_b^(9/5)-delta_a^(9/5)) + 1/8000 * (delta_b^(4/5)-delta_a^(4/5));
        % Mu(6) = 5/29 * (delta_b^(29/5)-delta_a^(29/5)) + 5/48 * (delta_b^(24/5)-delta_a^(24/5)) + 1/38 * (delta_b^(19/5)-delta_a^(19/5)) + 1/280 * (delta_b^(14/5)-delta_a^(14/5)) + 1/3600 * (delta_b^(9/5)-delta_a^(9/5)) + 1/80000 * (delta_b^(4/5)-delta_a^(4/5));
    end
end

function A = IQF(limits, n, method)

    Mu = calculateMu(limits, n, method);
    X_nodes = zeros(n,n);
    if (method == "G")
        M = zeros(n,n);
        for j=1:n
            for k=1:n
                M(j,k) = Mu(j+k-1);
            end
        end
        M
        nodePoly = linsolve(M,-Mu(n+1:end))
        X_temp = roots([1; nodePoly])
        for k = 1:n
            X_nodes(k, :) = X_temp .^ (k - 1);
        end
        X_nodes
        A = linsolve(X_nodes, Mu(1:3));
    else
        X_temp = linspace(limits(1), limits(2), n);
      
        for k = 1:n
            X_nodes(k, :) = X_temp .^ (k - 1);
        end
    end
   
end


function J = CIQF (f, limits, n, m, method)
    X = linspace (limits(1), limits(2),n);
    J = 0;
    for j = 2:n
        limits_curr = [X(j-1) X(j)];
        A_curr = IQF(limits_curr, m, method);
        F_curr = arrayfun(f, linspace(limits_curr(1), limits_curr(2), m));
        J = J + dot(A_curr, F_curr);
    end
    
end
    
function nodesCount_opt = optCount(f, limits, nodesCount_init, method, I)
        epsilon = 10 ^ (-6);
        L = 2;
        R = 1; m0 = 0; m1 = 1;
        n = length(nodesCount_init);
        
        nodesCount = nodesCount_init; S = zeros(1, n);
        
        while (R > epsilon) || (abs(m1 - m0) > 1/10)
            m0 = m1;
            
            for j = 1:n
                S(j) = CIQF(f, [limits(1) limits(2)], nodesCount(j),3, method);
            end
        
            m1 = -log(abs((S(3) - S(2)) / (S(2) - S(1)))) / log(L);
            R = abs(S(3) - S(2)) / (L ^ (m1) - 1);
            
            disp("values: ");
            disp([nodesCount(2), R, S(2), m1, m0]);
            nodesCount = nodesCount .* L;
            
        end
        
        nodesCount_opt = nodesCount(2);   
end
        
function TASK()
f = @(x) 5/2*cos(2*x)*exp(2/3*x) + 4*sin(7/2*x)*exp(-3*x)+3*x;
p = @(x) (x-1/10)^(-1/5);
n = 3;
a_b = [0.1 2.3];
I = 3.578861536040539915439859609644293194417;

% Ньютон-Котс метод:

% 1) простая ИКФ по трем узлам
% J_3n = dot(arrayfun(f,X), IQF(a_b,n, "NC"));

% 2) составная ИКФ по шести узлам 
% J = CIQF(f, a_b, 6, 3, "NC");

% 3) выбор оптимального числа узлов
% k_opt = optCount(f,a_b,[2 3 5], "NC", I);

% Гаусс метод:

% 1) простая ИКФ по трем узлам
J_3n = dot(arrayfun(f,X), IQF([a_b(1) 1/2*(a_b(1) + a_b(2))],n, "G"))+dot(arrayfun(f,X), IQF([1/2*(a_b(1) + a_b(2)) a_b(2)],n, "G"))

% 2) составная ИКФ по шести узлам 
% J = CIQF(f, a_b, 6, 3, "G")

% 3) выбор оптимального числа узлов
% k_opt = optCount(f, a_b,[2 3 5], "G", I)
end