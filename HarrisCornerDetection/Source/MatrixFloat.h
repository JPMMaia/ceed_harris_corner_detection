#pragma once

#include <stdint.h>
#include <stddef.h>

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

	void MatrixFloat_Initialize(MatrixFloat* matrix, size_t width, size_t height);
	void MatrixFloat_Shutdown(MatrixFloat* matrix);
	float MatrixFloat_Get(const MatrixFloat* matrix, size_t i, size_t j);
	void MatrixFloat_Set(const MatrixFloat* matrix, size_t i, size_t j, float value);
	void MatrixFloat_Load(MatrixFloat* destination, const wchar_t* filename);
	void MatrixFloat_Copy(MatrixFloat* destination, const MatrixFloat* source);
	void MatrixFloat_ForEach(MatrixFloat* destination, const MatrixFloat* matrix, float compute(float value));
	void MatrixFloat_ExecuteElementByElement(MatrixFloat* destination, const MatrixFloat* matrix1, const MatrixFloat* matrix2, float compute(float value1, float value2));
	void MatrixFloat_Fill(MatrixFloat* matrix, float value);

#ifdef __cplusplus
}
#endif