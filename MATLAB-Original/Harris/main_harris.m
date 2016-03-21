

%im = imread('Harris_Detector_Original_Image.jpg');
im = imread('plane.jpg');
%im = imread('corner.png');
im=rgb2gray(im);

figure;
imshow(im);

im=single(im);

sigma=1;
thresh=1000;
radius=3;
[cim, r, c] = harris(im, sigma, thresh, radius);

figure;
imshow(cim);

%imout = im;
%imout(cim == 1) = 255;
%figure;
%imshow(imout);