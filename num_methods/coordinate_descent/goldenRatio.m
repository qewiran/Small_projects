function mid = goldenRatio(f, A, B, fileId)
    fracL = (3 - sqrt(5)) / 2;
    fracR = (sqrt(5) - 1) / 2;
    a = A;
    b = B;
    c = fracL * (b - a) + a;
    d = fracR * (b - a) + a;
    countOper = 2;
    countIter = 0;
    left = 0;
    right = 0;
    f_d = f(d);
    f_c = f(c);
    printTableHeader("goldenRatio", fileId);

    while (b - a) / 2 > 0.0005
        countIter = countIter + 1;

        if left
            f_d = f_c;
            f_c = f(c);
            countOper = countOper + 1;
        elseif right
            f_c = f_d;
            f_d = f(d);
            countOper = countOper + 1;
        end

        if f_c < f_d
            b = d;
            d = c;
            c = fracL * (b - a) + a;
            left = true;
            right = false;

        else
            a = c;
            c = d;
            d = fracR * (b - a) + a;
            right = true;
            left = false;
        end

        printTableRow(fileId, countIter, a, b, c, d, f(c), f(d), (b - a) / 2, countOper);

    end

    mid = (a + b) / 2;

end
