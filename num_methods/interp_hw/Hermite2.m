function H = Hermite2 (tbl_x, tbl_y, tbl_dy, tbl_d2y)
    n=length(tbl_x);
    P = [];
    F = [transpose(tbl_y); transpose(tbl_dy); transpose(tbl_d2y)];
    for j=1:n
        X = zeros(1, 3*n);
        for k=1:3*n
            X(1,k) = tbl_x(j)^(k-1);
        end
        P = [P;X];
    end
    
    for j=1:n
        dX = zeros(1,3*n);
        for k=2:3*n
            dX(1,k) = (k-1)* tbl_x(j)^(k-2);
        end
        P = [P;dX];
    end
    for j=1:n
        d2X = zeros(1,3*n);
        for k=3:3*n
            d2X(1,k) = (k-1)*(k-2)* tbl_x(j)^(k-3);
        end
        P = [P;d2X];
    end
    H= linsolve(P,F);
    H = flipud(H);
    H = double(H);
    end