#include "MatrixFloat.h"
#include "Harris.h"

#define ROWS 168
#define COLUMNS 300

int main()
{
	{
		MatrixFloat inputImage;
		MatrixFloat_Initialize(&inputImage, COLUMNS, ROWS);

		//MatrixFloat_Load(&inputImage, L"Resources/HarrisInputImage.txt");

		MatrixFloat outputImage = Harris(&inputImage, 3);

		MatrixFloat_Shutdown(&outputImage);

		MatrixFloat_Shutdown(&inputImage);
	}

	return 0;
}