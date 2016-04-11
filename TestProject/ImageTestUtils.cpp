#include "stdafx.h"
#include "ImageTestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool operator==(const Image& image1, const Image& image2)
{
	if (image1.Width != image2.Width || image1.Height != image2.Height)
		return false;

	for (size_t i = 0; i < image1.Height; ++i)
	{
		for (size_t j = 0; j < image1.Width; ++j)
		{
			if (Image_Get(&image1, i, j) != Image_Get(&image2, i, j))
				return false;
		}
	}

	return true;
}
