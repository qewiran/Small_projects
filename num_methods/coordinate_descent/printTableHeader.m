function printTableHeader(methodName, fileId)

    if methodName == "dychotomy" || methodName == "goldenRatio"
        fprintf(fileId, "|№ |   a      |   b      |  x_1     |  x_2     | f(x_1)   | f(x_2)   |  b-a      |  calc     |\n");
    elseif methodName == "passiveSearch"
        fprintf(fileId, "|№ |  x_1      |  x_2      | f(x_1)    | f(x_2)    |  calc     |\n");
    elseif methodName == "Newton"
        fprintf(fileId, "|№ |  x_1     |  x_2     |  f(x_2)  |  df(x_2) | ddf(x_2) |  calc_df |  calc_ddf\n");
    else
        fprintf(fileId, "|№ |   a      |   b      |    c     | f(x_1)   | f(x_2)   |  b-a      |  calc     |\n");
    end

end
