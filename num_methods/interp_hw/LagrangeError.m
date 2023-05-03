function Err = LagrangeError(a, L, f, tbl_x, tbl_y)
t = -a:a/150:a;
E_val = abs(L(t,tbl_x,tbl_y)-f(t));
Err = max(E_val);
end