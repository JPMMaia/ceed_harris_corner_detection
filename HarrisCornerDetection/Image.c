#include "Image.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t Image_Get(const struct Image* image, size_t i, size_t j)
{
	assert(i >= 0 && i < image->Width && j >= 0 && j < image->Height);

	return image->Data[i * image->Width + j];
}
void Image_Load(const struct Image* image, const wchar_t* filenameW)
{
	char filename[512];
	wcstombs(filename, filenameW, 512);

	FILE* file = fopen(filename, "r");

	fclose(file);
}