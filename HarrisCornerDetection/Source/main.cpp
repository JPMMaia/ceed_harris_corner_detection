/*
 * Main.cpp
 *
 *  Created on: 15/03/2016
 *      Author: Diogo Eiras
 */

#include "IO.h"
#include "MatlabUtils.hpp"
#include <cmath>
#include <float.h>

int main(int argc, char ** args) {

	double ** img = new double*[3];
	double ** dx = new double*[3];
	double ** dy = new double*[3];
	for (unsigned int i = 0; i < 3; ++i){
		img[i] = new double[3];
		dx[i] = new double[3];
		dy[i] = new double[3];
	}

	img[0][0] = 1;
	img[0][1] = 2;
	img[0][2] = 3;
	img[1][0] = 4;
	img[1][1] = 5;
	img[1][2] = 6;
	img[2][0] = 7;
	img[2][1] = 8;
	img[2][2] = 9;


	unsigned int sizeImg[2] = { 3,3 };
	unsigned int sizeD[2] = { 3,3 };

	double sigma = 1;

	/*
	Convolve start
	*/

	double ** ix = new double*[sizeImg[0]];
	double ** iy = new double*[sizeImg[0]];
	double ** ix2 = new double*[sizeImg[0]];
	double ** iy2 = new double*[sizeImg[0]];
	double ** ixy = new double*[sizeImg[0]];
	for (unsigned int i = 0; i < sizeImg[0]; ++i){
		ix[i] = new double[sizeImg[1]];
		iy[i] = new double[sizeImg[1]];
		ix2[i] = new double[sizeImg[1]];
		iy2[i] = new double[sizeImg[1]];
		ixy[i] = new double[sizeImg[1]];
	}

	convolve(img, dx, ix, sizeImg, sizeD);
	convolve(img, dx, iy, sizeImg, sizeD);

	for (unsigned int i = 0; i < sizeD[0]; i++) {
		for (unsigned int j = 0; j < sizeD[1]; j++) {
			ix2[i][j] = ix[i][j] * ix[i][j];
			iy2[i][j] = iy[i][j] * iy[i][j];
			ixy[i][j] = ix[i][j] * iy[i][j];
		}
	}
	/*
	Convolve end
	*/


	double length = 1;

	if (6 * sigma > length)
		length = 6 * sigma;


	/*
	Fspecial start
	*/

	unsigned int sizeG[2];

	double ** g = fspecial(length, sigma, sizeG[0], sizeG[1]);


	/*
	Fspecial end
	*/


	printf_s("%.20f\n", DBL_EPSILON);
	system("pause");

	return 0;
}
