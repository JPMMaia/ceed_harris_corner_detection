#pragma once

#include <stdint.h>

typedef struct _MatrixFloat
{
	size_t Width;
	size_t Height;
	float* Data;
} MatrixFloat;

#ifdef __cplusplus
extern "C"
{
#endif

	void MatrixFloat_Initialize(MatrixFloat* image, size_t width, size_t height);
	void MatrixFloat_Shutdown(MatrixFloat* image);
	float MatrixFloat_Get(const MatrixFloat* image, size_t i, size_t j);
	void MatrixFloat_Set(const MatrixFloat* image, size_t i, size_t j, float value);
	void MatrixFloat_Load(MatrixFloat* image, const wchar_t* filename);

#ifdef __cplusplus
}
#endif