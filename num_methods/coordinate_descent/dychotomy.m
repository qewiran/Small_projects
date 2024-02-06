function point = dychotomy(f, A, B, fileId)
    countOper = 0;
    countIter = 0;
   
    a = A;
    b = B;
    
    printTableHeader("dychotomy", fileId);
    point = (b - a) / 2;
   
    while point > 0.0005
        countIter = countIter + 1;
        mid = (a + b) / 2;
        c = mid -2.5e-4;
        d = mid +2.5e-4;
        
        printTableRow(fileId, countIter, a, b, c, d, f(c), f(d), (b - a) / 2, countOper);
        
        if (f(c) < f(d))
            b = d;
        else
            a = c;
        end
        
        point = (b - a) / 2;
        countOper = countOper + 2;
    end
end
