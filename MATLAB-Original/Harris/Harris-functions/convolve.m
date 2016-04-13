% http://stackoverflow.com/questions/14864315/alternative-to-conv2-in-matlab

function B = convolve(A, B);
    
    [rowsA columnsA] = size(A);
    [rowsB columnsB] = size(B);
    
    rotatedB = rot90(B, 2);
    center = floor((size(rotatedB)+1)/2);
    left = center(2) - 1;
    right = columnsB - center(2);
    top = center(1) - 1;
    bottom = rowsB - center(1);
  
    C = zeros(rowsA + top + bottom, columnsA + left + right);

    for x = 1 + top : rowsA + top
        for y = 1 + left : columnsA + left
            C(x,y) = A(x - top, y - left);
        end
    end
    
    B = zeros(rowsA , columnsA);
    for x = 1 : rowsA
        for y = 1 : columnsA
            for i = 1 : rowsB
                for j = 1 : columnsB
                    q = x - 1;
                    w = y -1;
                    B(x, y) = B(x, y) + (C(i + q, j + w) * rotatedB(i, j));
                end
            end
        end
    end

