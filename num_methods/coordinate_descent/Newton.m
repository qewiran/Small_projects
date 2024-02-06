function x1 = Newton(f, df, ddf, point, fileId)
    x2 = point;
    x1 = point +1e-3;
    countOperDf1 = 1;
    countOperDf2 = 0;
    countIter = 0;

    printTableHeader("Newton", fileId);

    while (abs(x2 - x1) > 0.0005)
        x1 = x2;
        countIter = countIter + 1;
        countOperDf2 = countOperDf2 + 1;
        countOperDf1 = countOperDf1 + 1;
        x2 = x1 - df(x1) / ddf(x1);
        printTableRow(fileId, countIter, x1, x2, f(x2), df(x2), ddf(x2), countOperDf1, countOperDf2);
    end

end
