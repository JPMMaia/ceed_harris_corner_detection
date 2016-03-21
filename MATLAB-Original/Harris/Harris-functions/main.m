dx = [-1 0 1; -1 0 1; -1 0 1]; % Derivative masks
im = rand(16,16);

Ix = conv2(im, dx, 'same');    % Image derivatives

Iy = convolve(im, dx);  

Ix(1)
Iy(1)
