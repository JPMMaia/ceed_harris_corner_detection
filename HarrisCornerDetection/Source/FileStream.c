#include "FileStream.h"

#include <assert.h>
#include <stdlib.h>

void FileStream_Open(FileStream* fileStream, const wchar_t* filenameW, const char* mode)
{
	char filename[512];
	wcstombs(filename, filenameW, 512);

	fileStream->Stream = fopen(filename, mode);

#ifdef _DEBUG
	assert(fileStream->Stream);
#endif
}
void FileStream_Close(const FileStream* fileStream)
{
	fclose(fileStream->Stream);
}

void FileStream_SkipUntil(const FileStream* fileStream, uint8_t byte)
{
	uint8_t c;
	do
		c = fgetc(fileStream->Stream);
	while (c != byte);
}

void FileStream_ReadUInt8(const FileStream* fileStream, uint8_t* element)
{
	uint32_t temp;
	fscanf(fileStream->Stream, "%d", (int*)&temp);
	*element = (uint8_t) temp;
}
void FileStream_ReadInt32(const FileStream* fileStream, int32_t* element)
{
	fscanf(fileStream->Stream, "%d", (int*)element);
}
void FileStream_ReadUInt32(const FileStream* fileStream, uint32_t* element)
{
	fscanf(fileStream->Stream, "%d", (int*)element);
}
void FileStream_ReadFloat(const FileStream* fileStream, float* element)
{
	fscanf(fileStream->Stream, "%f", element);
}
