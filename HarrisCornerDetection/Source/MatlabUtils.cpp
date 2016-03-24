#include "MatlabUtils.hpp"

void rotateVerticalHorizontal(double ** matrix, double ** resultMatrix, unsigned int rows, unsigned int columns) {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			resultMatrix[i][j] = matrix[rows - i - 1][columns - j - 1];
		}
	}
}

void convolve(double ** matrixA, double ** matrixK, double ** matrixB,unsigned int sizeA[2], unsigned int sizeK[2]) {
	double ** matrixH = new double*[sizeK[0]];
	for (unsigned int i = 0; i < sizeK[0]; ++i)
		matrixH[i] = new double[sizeK[1]];

	rotateVerticalHorizontal(matrixK, matrixH, sizeK[0], sizeK[1]);

	unsigned int center[2] = { (sizeK[0] + 1) / 2 ,(sizeK[1] + 1) / 2 };
	unsigned int left = center[1] - 1;
	unsigned int right = sizeK[1] - center[1];
	unsigned int top = center[0] - 1;
	unsigned int bottom = sizeK[0] - center[0];

	unsigned int sizeRep[2] = { sizeA[0] + top + bottom,sizeA[1] + left + right };

	double ** matrixRep = new double*[sizeRep[0]];
	for (unsigned int i = 0; i < sizeRep[0]; ++i)
		matrixRep[i] = new double[sizeRep[1]];

	for (unsigned int i = 0; i < sizeRep[0]; i++) {
		for (unsigned int j = 0; j < sizeRep[1]; j++) {
			matrixRep[i][j] = 0;
		}
	}

	for (unsigned int x = top; x < sizeA[0] + top; x++) {
		for (unsigned int y = left; y < sizeA[1] + left; y++) {
			matrixRep[x][y] = matrixA[x - top][y - left];
		}
	}

	for (unsigned int i = 0; i < sizeA[0]; i++) {
		for (unsigned int j = 0; j < sizeA[1]; j++) {
			matrixB[i][j] = 0;
		}
	}

	for (unsigned int x = 0; x < sizeA[0];x++) {
		for (unsigned int y = 0; y < sizeA[1];y++) {
			for (unsigned int i = 0; i < sizeK[0];i++) {
				for (unsigned int j = 0; j < sizeK[0];j++) {
					matrixB[x][y] = matrixB[x][y] + (matrixRep[i + x][j + y] * matrixH[i][j]);
				}
			}
		}
	}
}

int fix(double value) {
	return static_cast<int>(value);
}

double ** fspecial(double length, unsigned int sigma, unsigned int & rows, unsigned int & columns) {
	length -= 1;
	length = length / 2.0;

	double * pos = new double[length * 2 + 1];

	double ** f = new double*[length * 2 + 1];
	for (unsigned int i = 0; i < length * 2 + 1;i++) {
		f[i] = new double[length * 2 + 1];
		pos[i] = static_cast<double>(i) - length;
	}

	double sum = 0;
	for (unsigned int i = 0; i < length * 2 + 1; i++) {
		for (unsigned int j = 0; j < length * 2 + 1; j++) {
			f[i][j] = pos[i] * pos[i] + pos[j] * pos[j];
			f[i][j] = exp(-1 * f[i][j] / (2 * (sigma*sigma)));
			sum += f[i][j];
		}
	}
	
	
	for (rows = 0; rows < length * 2 + 1; rows++) {
		for (columns = 0; columns < length * 2 + 1; columns++) {
			f[rows][columns] /= sum;
		}
	}

	return f;
}