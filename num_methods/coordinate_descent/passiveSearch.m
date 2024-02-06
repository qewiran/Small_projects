function min = passiveSearch(f, A, B, fileId)
    countOper = 0;
    countIter = 0;
    step = 1e-3;
    min = A;
    currPos = A;
    fPrev = f(A) + 1;
    fVal = f(A);
    printTableHeader("passiveSearch", fileId);

    while fPrev > fVal && currPos < B
        fPrev = fVal;
        currPos = currPos + step;
        fVal = f(currPos);
        countIter = countIter + 1;
        countOper = countOper + 1;
        printTableRow(fileId,countIter, currPos, currPos + step, fPrev, fVal, countIter);
    end

end
