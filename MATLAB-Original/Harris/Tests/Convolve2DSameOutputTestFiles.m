pkg load image

im = imread('Images/plane.jpg');
im=rgb2gray(im);
im=single(im);

dx = [-1 0 1; -1 0 1; -1 0 1];
Ix = conv2(im, dx, 'same');

save -text Convolve2DSameInputImage.txt im;
save -text Convolve2DSameOutputImage.txt Ix;

A = [
		0 1 2 3 4;
		5 6 7 8 9;
		10 11 12 13 14;
		15 16 17 18 19;
	];
B = [
		20 21 22 23 24;
		25 26 27 28 29;
		30 31 32 33 34;
		35 36 37 38 39;
	];
C = [-1 0 1; -1 0 1; -1 0 1];

AConvA = conv2(A, A, 'same');
AConvB = conv2(A, B, 'same');
BConvA = conv2(A, B, 'same');
AConvC = conv2(A, C, 'same');
CConvA = conv2(C, A, 'same');

save -text Convolve2DSameAConvA.txt AConvA;
save -text Convolve2DSameAConvB.txt AConvB;
save -text Convolve2DSameBConvA.txt BConvA;
save -text Convolve2DSameBConvA.txt BConvA;
save -text Convolve2DSameAConvC.txt AConvC;
save -text Convolve2DSameCConvA.txt CConvA;