pkg load image

im = imread('Images/plane.jpg');
im=rgb2gray(im);
im=single(im);

dx = [-1 0 1; -1 0 1; -1 0 1];
Ix = conv2(im, dx, 'same');

save -text Convolve2DSameInputImage.txt im;
save -text Convolve2DSameOutputImage.txt Ix;