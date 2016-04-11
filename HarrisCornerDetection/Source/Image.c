#include "Image.h"
#include "FileStream.h"

#include <assert.h>
#include <stdlib.h>

void Image_Initialize(struct Image* image, size_t width, size_t height)
{
	image->Width = width;
	image->Height = height;
	image->Data = (uint8_t*) malloc(width * height * sizeof(uint8_t));
}

void Image_Shutdown(struct Image* image)
{
	if(image->Data)
		free(image->Data);

	image->Height = 0;
	image->Width = 0;
}

uint8_t Image_Get(const struct Image* image, size_t i, size_t j)
{
#ifdef _DEBUG
	assert(i >= 0 && i < image->Height && j >= 0 && j < image->Width);
#endif

	return image->Data[i * image->Width + j];
}
void Image_Load(struct Image* image, const wchar_t* filenameW)
{
	struct FileStream fileStream;
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
	Image_Initialize(image, columns, rows);

	// Read content:
	{
		for (uint32_t i = 0; i < rows; ++i)
		{
			for (uint32_t j = 0; j < columns; ++j)
			{
				FileStream_ReadUInt8(&fileStream, &image->Data[i * columns + j]);
			}
		}
	}
	
	FileStream_Close(&fileStream);
}