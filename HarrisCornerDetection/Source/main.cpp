/*#include "MatrixFloat.h"
#include "Harris.h"
#include "Profiler.h"

#include <iostream>

#ifdef _EMBEDED
#define ROWS 168
#define COLUMNS 300
#endif

#ifndef _EMBEDED
using namespace CEED;
using namespace std;
#endif

int main()
{
	{
		MatrixFloat inputImage;
#ifdef _EMBEDED
		MatrixFloat_Initialize(&inputImage, COLUMNS, ROWS);
#endif

#ifndef _EMBEDED
		MatrixFloat_Load(&inputImage, L"Resources/HarrisInputImage.txt");

		Profiler profiler;
		profiler.Start();
#endif

		MatrixFloat outputImage = Harris(&inputImage, 3);

#ifndef _EMBEDED
		profiler.End();

		cout << "Elapsed Nanoseconds: " << profiler.ElapsedTime<double, std::nano>().count() << endl;
#endif

		MatrixFloat_Shutdown(&outputImage);

		MatrixFloat_Shutdown(&inputImage);
	}

	return 0;
}*/