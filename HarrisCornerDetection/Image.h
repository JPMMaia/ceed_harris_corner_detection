#pragma once

#include <stdint.h>

struct Image
{
	size_t Width;
	size_t Height;
	uint8_t* Data;
};

uint8_t Image_Get(const struct Image* image, size_t i, size_t j);
void Image_Load(const struct Image* image, const wchar_t* filename);