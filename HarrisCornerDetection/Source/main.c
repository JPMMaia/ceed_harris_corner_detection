#include "MatrixFloat.h"
#include "Harris.h"

int main()
{
	{
		MatrixFloat inputImage;
		MatrixFloat_Load(&inputImage, L"Resources/HarrisInputImage.txt");

		MatrixFloat outputImage = Harris(&inputImage, 3);
		MatrixFloat_Shutdown(&outputImage);

		MatrixFloat_Shutdown(&inputImage);
	}

	return 0;
}