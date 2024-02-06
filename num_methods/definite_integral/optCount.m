function nodesCount_opt = optCount(f, limits, nodesCount_init, method, I)
epsilon = 10 ^ (-6);
L = 2;
R = 1; m0 = 0; m1 = 1;
n = length(nodesCount_init);

nodesCount = nodesCount_init; S = zeros(1, n);

while ((R > epsilon) && (abs(m1 - m0) > 1/10))
    m0 = m1;
    nodesCount = (nodesCount-1) .* L+1;
    for j = 1:n
        S(j) = CIQF(f, [limits(1) limits(2)], nodesCount(j),3, method);
    end

    m1 = -log(abs((S(3) - S(2)) / (S(2) - S(1)))) / log(L);
    R = abs(S(3) - S(2)) / (L ^ (m1) - 1);
    
    disp("values: ");
    disp([nodesCount(2), R, S(2)-I, m1, m0]);
   
    
end

nodesCount_opt = nodesCount(2);


