function D = FiniteDiff(power, num, tbl_y)
n = length(tbl_y);
if power > n
    return;
end
if power == 0
    D = tbl_y(num);
else
    D = FiniteDiff(power-1, num+1, tbl_y) - FiniteDiff(power-1,num, tbl_y);
end
