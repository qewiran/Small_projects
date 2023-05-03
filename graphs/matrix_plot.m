A = (diag([1:8])*ones(8))'-(diag([1:8])*ones(8))

bar3(abs(mod((triu(A)+triu(A)'),2))+1);