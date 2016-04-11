#include "FileStream.h"

#include <cassert>
#include <stdlib.h>

void FileStream_Open(struct FileStream* fileStream, const wchar_t* filenameW, const char* mode)
{
	char filename[512];
	wcstombs(filename, filenameW, 512);

	fileStream->Stream = fopen(filename, mode);

#ifdef _DEBUG
	assert(fileStream->Stream);
#endif
}
void FileStream_Close(const struct FileStream* fileStream)
{
	fclose(fileStream->Stream);
}

void FileStream_SkipUntil(const struct FileStream* fileStream, uint8_t byte)
{
	uint8_t c;
	do
		c = fgetc(fileStream->Stream);
	while (c != byte);
}

void FileStream_ReadUInt8(const struct FileStream* fileStream, uint8_t* element)
{
	uint32_t temp;
	fscanf(fileStream->Stream, "%d", &temp);
	*element = (uint8_t) temp;
}
void FileStream_ReadInt32(const struct FileStream* fileStream, int32_t* element)
{
	fscanf(fileStream->Stream, "%d", element);
}
void FileStream_ReadUInt32(const struct FileStream* fileStream, uint32_t* element)
{
	fscanf(fileStream->Stream, "%d", element);
}
