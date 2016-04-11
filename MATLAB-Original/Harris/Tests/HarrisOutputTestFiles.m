pkg load image

im = imread('Images/plane.jpg');
im=rgb2gray(im);
im=single(im);

sigma=1;
thresh=1000;
radius=3;
[cim, r, c] = harris(im, sigma, thresh, radius);

save -text HarrisInputImage.txt im;
save -text HarrisOutputImage.txt cim;