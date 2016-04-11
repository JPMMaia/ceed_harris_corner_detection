sigma = 1;
g = fspecial('gaussian',max(1,fix(6*sigma)), sigma);
save -text CreateGaussianFilterOutputMatrix1.txt g;

sigma = 2;
g = fspecial('gaussian',max(1,fix(6*sigma)), sigma);
save -text CreateGaussianFilterOutputMatrix2.txt g;

sigma = 3;
g = fspecial('gaussian',max(1,fix(6*sigma)), sigma);
save -text CreateGaussianFilterOutputMatrix3.txt g;