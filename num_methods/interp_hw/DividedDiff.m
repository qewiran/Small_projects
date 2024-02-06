function D = DividedDiff(tbl_x)
syms x;
D =1;
    for x_i = tbl_x
        D = D * (x-x_i);
    end

end
