#include "MatrixFloat.h"
#include "Harris.h"
#include "Profiler.h"

#include <iostream>

using namespace CEED;
using namespace std;

int main()
{
	{
		MatrixFloat inputImage;
		MatrixFloat_Load(&inputImage, L"Resources/HarrisInputImage.txt");

		Profiler profiler;
		profiler.Start();
		MatrixFloat outputImage = Harris(&inputImage, 3);
		profiler.End();

		cout << "Elapsed Nanoseconds: " << profiler.ElapsedTime<double, std::nano>().count() << endl;

		MatrixFloat_Shutdown(&outputImage);

		MatrixFloat_Shutdown(&inputImage);
	}

	return 0;
}