pkg load image

A = imread('Images/plane.jpg');
A = rgb2gray(A);
A = single(A);

radius = 3;
size = 2*radius+1;
result = ordfilt2(A, size^2, ones(size));

save -text OrderStatisticFilteringMatrixAInput.txt A;
save -text OrderStatisticFilteringMatrixAOutput.txt A;