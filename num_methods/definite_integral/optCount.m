function nodesCount_opt = optCount(f, limits, nodesCount_init, method, I)
epsilon = 10 ^ (-6);
L = 2;
R = 1; m_prev = 0; m_curr = 1;
n = length(nodesCount_init);

nodesCount = nodesCount_init; S = zeros(1, n);
iterations = 0;
while ((R > epsilon) || (abs(m_curr - m_prev) > 1/10)) && iterations<6
    iterations = iterations + 1;

    m_prev = m_curr;
    nodesCount = (nodesCount-1) .* L+1;
    
    for j = 1:n
        S(j) = CIQF(f, [limits(1) limits(2)], nodesCount(j),3, method);
    end
    
    m_curr = -log(abs((S(3) - S(2)) / (S(2) - S(1)))) / log(L);
    R = abs(S(3) - S(2)) / (L ^ (m_curr) - 1);
    
    difference = S(2)-I;
    disp( [nodesCount(2),"R : " + R, "S(2) - I: " + difference, "m_curr: " +  m_curr, "m_pr " +  m_prev]);
    
    
end

nodesCount_opt = nodesCount(2);



