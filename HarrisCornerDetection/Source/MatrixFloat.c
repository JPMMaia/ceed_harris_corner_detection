#include "MatrixFloat.h"
#include "FileStream.h"

#include <assert.h>
#include <stdlib.h>

void MatrixFloat_Initialize(MatrixFloat* image, size_t width, size_t height)
{
	image->Width = width;
	image->Height = height;
	image->Data = malloc(width * height * sizeof(float));
}

void MatrixFloat_Shutdown(MatrixFloat* image)
{
	if(image->Data)
		free(image->Data);

	image->Height = 0;
	image->Width = 0;
}

float MatrixFloat_Get(const MatrixFloat* image, size_t i, size_t j)
{
#ifdef _DEBUG
	assert(i >= 0 && i < image->Height && j >= 0 && j < image->Width);
#endif

	return image->Data[i * image->Width + j];
}

void MatrixFloat_Set(const MatrixFloat* image, size_t i, size_t j, float value)
{
#ifdef _DEBUG
	assert(i >= 0 && i < image->Height && j >= 0 && j < image->Width);
#endif

	image->Data[i * image->Width + j] = value;

}

void MatrixFloat_Load(MatrixFloat* image, const wchar_t* filenameW)
{
	FileStream fileStream;
	FileStream_Open(&fileStream, filenameW, "r");

	// Read header:
	uint32_t rows, columns;
	{
		// Skip the first 3 lines:
		for (size_t i = 0; i < 3; ++i)
		{
			FileStream_SkipUntil(&fileStream, '\n');
		}

		// Read rows:
		FileStream_SkipUntil(&fileStream, ':');
		FileStream_ReadUInt32(&fileStream, &rows);

		// Read columns:
		FileStream_SkipUntil(&fileStream, ':');
		FileStream_ReadUInt32(&fileStream, &columns);

		FileStream_SkipUntil(&fileStream, '\n');
	}

	// Initialize image:
	MatrixFloat_Initialize(image, columns, rows);

	// Read content:
	{
		for (uint32_t i = 0; i < rows; ++i)
		{
			for (uint32_t j = 0; j < columns; ++j)
			{
				FileStream_ReadFloat(&fileStream, &image->Data[i * columns + j]);
			}
		}
	}
	
	FileStream_Close(&fileStream);
}
