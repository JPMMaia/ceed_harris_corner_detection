% HARRIS - Harris corner detector
% Usage:  [cim, r, c] = harris(im, sigma, thresh, radius, disp)
% Arguments:
% 	im - image to be processed.
% 	sigma - standard deviation of smoothing Gaussian. Typical values to use might be 1-3.
%	thresh - threshold (optional). Try a value ~1000.
%  radius - radius of region considered in non-maximal suppression (optional). Typical values to use might be 1-3.
% 	disp - optional flag (0 or 1) indicating whether you want to display corners overlayed on the original image. This can be useful for parameter tuning.
% Returns:
% 	cim - binary image marking corners.
% 	r - row coordinates of corner points.
%	c - column coordinates of corner points.
%
%   http://slazebni.cs.illinois.edu/spring16/harris.m

function [cim, r, c] = harris(im, sigma, thresh, radius)
    
    dx = [-1 0 1; -1 0 1; -1 0 1]; % Derivative masks
    dy = [-1 -1 -1; 0 0 0; 1 1 1]; % dy = dx';
    Ix = conv2(im, dx, 'same');    % Image derivatives
    Iy = conv2(im, dy, 'same'); 
    if sigma == 1  % g = fspecial('gaussian',max(1,fix(6*sigma)), sigma); 
        g = [0.0003    0.0023    0.0062    0.0062    0.0023    0.0003;
    0.0023    0.0168    0.0458    0.0458    0.0168    0.0023;
    0.0062    0.0458    0.1244    0.1244    0.0458    0.0062;
    0.0062    0.0458    0.1244    0.1244    0.0458    0.0062;
    0.0023    0.0168    0.0458    0.0458    0.0168    0.0023;
    0.0003    0.0023    0.0062    0.0062    0.0023    0.0003]
    else if sigma == 2
            g = [0.0002    0.0001    0.0000;
    0.0007    0.0003    0.0001;
    0.0019    0.0007    0.0002;
    0.0040    0.0015    0.0004;
    0.0065    0.0024    0.0007;
    0.0084    0.0031    0.0009;
    0.0084    0.0031    0.0009;
    0.0065    0.0024    0.0007;
    0.0040    0.0015    0.0004;
    0.0019    0.0007    0.0002;
    0.0007    0.0003    0.0001;
    0.0002    0.0001    0.0000]
        else if sigma == 3
            end
    
    
    Ix2 = conv2(Ix.^2, g, 'same'); % Smoothed squared image derivatives
    Iy2 = conv2(Iy.^2, g, 'same');
    Ixy = conv2(Ix.*Iy, g, 'same');
    
    cim = (Ix2.*Iy2 - Ixy.^2)./(Ix2 + Iy2 + eps); % Harris corner measure
	
    sze = 2*radius+1;                   % Size of mask.
    mx = ordfilt2(cim,sze^2,ones(sze)); % Grey-scale dilate.
    cim = (cim==mx)&(cim>thresh);       % Find maxima.
	
    [r,c] = find(cim);                  % Find row,col coords.
end

