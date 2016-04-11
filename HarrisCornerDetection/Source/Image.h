#pragma once

#include <stdint.h>

struct Image
{
	size_t Width;
	size_t Height;
	uint8_t* Data;
};

#ifdef __cplusplus
extern "C"
{
#endif

	void Image_Initialize(struct Image* image, size_t width, size_t height);
	void Image_Shutdown(struct Image* image);
	uint8_t Image_Get(const struct Image* image, size_t i, size_t j);
	void Image_Load(struct Image* image, const wchar_t* filename);

#ifdef __cplusplus
}
#endif