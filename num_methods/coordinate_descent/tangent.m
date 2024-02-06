function tan = tangent(f, df, ddf, A, B)
    countOper = 2;
    countOperDf = 2;
    countIter = 0;
    printTableHeader("tangent");
    b = B;
    a = A;
    f_a = f(a);
    df_a = df(a);
    f_b = f(b);
    df_b = ddf(b);
    tan = b - a;

    while (b - a) > 0.0005
        countIter = countIter + 1;
        countOperDf = countOperDf + 1;
        c = (f_b - f_a + a * df_a - b * df_b) / (df_a - df_b);
        countOper = countOper + 1;

        if (df(c) <= 0)
            a = c;
            f_a = f(c);
            df_a = df(c);
        else
            b = c;
            f_b = f(c);
            df_b = df(c);
        end

        tan = b - a;
        printTableRow(countIter, a, c, f(c), df(c), f_a, df_a, b, df_b, countOper, countOperDf, tan);
    end
