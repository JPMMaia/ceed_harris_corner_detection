#include "MatrixFloat.h"
#include "Harris.h"

#include <stdio.h>
#include <stdlib.h>

#define ROWS 168 //1024 //168
#define COLUMNS 300 // 768 //300

#define _Version0

int main()
{
	{
		printf("Begin\n");

		MatrixFloat inputImage;
		MatrixFloat_Initialize(&inputImage, COLUMNS, ROWS);
		printf("Initialized\n");

		//MatrixFloat_Load(&inputImage, L"Resources/HarrisInputImage.txt");

		MatrixFloat outputImage = Harris(&inputImage, 3);
		printf("Harris\n");

		MatrixFloat_Shutdown(&outputImage);

		MatrixFloat_Shutdown(&inputImage);

		printf("End\n");
	}

	return 0;
}
