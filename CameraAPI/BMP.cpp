#include "BMP.h"
#include <fstream>
#include <stdexcept>
#include "log.h"

namespace camera 
{
namespace util 
{

/*
struct BITMAPFILEHEADER 
{ 
	unsigned short	bfType;
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
};

struct BITMAPINFOHEADER 
{
	unsigned long	biSize; 
	long			biWidth; 
	long			biHeight; 
	unsigned short	biPlanes; 
	unsigned short	biBitCount; 
	unsigned long	biCompression; 
	unsigned long	biSizeImage; 
	long			biXPelsPerMeter; 
	long			biYPelsPerMeter; 
	unsigned long	biClrUsed; 
	unsigned long	biClrImportant; 
};
*/

// Because the datatype char (1 byte) and short (2 bytes) is saved as a long (4 bytes) all char have been removed and all short have been replaced
struct BMPHeader 
{ 
	unsigned long	bfSize;
	unsigned long	bfReserved1And2;
	unsigned long	bfOffBits;
};

struct BMPInfoHeader 
{
	unsigned long	biSize;
	long			biWidth;
	long			biHeight;
	unsigned long	biPlanesAndBitCount;
	unsigned long	biCompression;
	unsigned long	biSizeImage;
	long			biXPelsPerMeter;
	long			biYPelsPerMeter;
	unsigned long	biClrUsed;
	unsigned long	biClrImportant;
};


Image *loadBMP(const char *filename)
{
	LOG_TRACE("loadBMP()");
	LOG_ERROR("loadBMP not implemented! Returning NULL");
	return NULL;
}

void saveBMP(const char *filename, const Image *image)
{
	LOG_TRACE("saveBMP()");
	if(image == NULL)
	{
		LOG_ERROR("saveBMP: image is NULL ");
		throw std::runtime_error("image is NULL");
	}
	if(image->getFormat() != Image::FORMAT_RGB32)
	{
		LOG_ERROR("saveBMP: Trying to save ImageBuffer with format " << image->getFormat());
		throw std::runtime_error("The only supported format is RGB32");
	}
	
	int width = image->getWidth();
	int height = image->getHeight();
	
	std::ofstream file(filename, std::ios_base::out | std::ios_base::binary);
	
	BMPHeader header;
	header.bfSize = 54 + image->getBufferSize(); // TODO: Check
	header.bfReserved1And2 = 0;
	header.bfOffBits = 54; // TODO: Check
	
	BMPInfoHeader infoHeader;
	infoHeader.biSize = 40;
	infoHeader.biWidth = image->getWidth();
	infoHeader.biHeight = image->getHeight();
	infoHeader.biPlanesAndBitCount = (24 << 16) | 1;
	infoHeader.biCompression = 0; // Compression is bad :P
	infoHeader.biSizeImage = 0; // Can be 0 only if we do not use compression
	infoHeader.biXPelsPerMeter = 0;
	infoHeader.biYPelsPerMeter = 0;
	infoHeader.biClrUsed = 0;
	infoHeader.biClrImportant = 0;
	
	file.put('B');
	file.put('M');
	file.write((char *) &header, sizeof(BMPHeader));
	file.write((char *) &infoHeader, sizeof(BMPInfoHeader));
	
	camera::ImageBuffer *buffer = image->getBufferAddress();
	int linePadding = width % 4;
	
	// Start with the bottom left pixel (WHY MICROSOFT? WHY?!)
	buffer += 4 * (width * height - width);
	for(int y = 0; y < height; y++) 
	{
		for(int x = 0; x < width; x++) 
		{
			file.put(*(buffer)); // B
			file.put(*(buffer + 1)); // G
			file.put(*(buffer + 2)); // R
			// Move to next pixel
			buffer += 4;
		}

		// Every line must be n * 4 bytes
		for(int i = 0; i < linePadding; i++) 
		{
			file.put('\0');
		}

		// Move up one line
		buffer -= 4 * 2 * width;
	}
		
	file.close();
}

} // namespace util
} // namespace camera