function Err = PolyError(a, P, f)
    syms x
t = -a:a/150:a;
E_val = abs(polyval(P,t)-f(t));
Err = max(E_val);
end