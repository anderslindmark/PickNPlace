#include "Image.h"
#include "CameraException.h"
#include "log.h"

namespace camera {

int Image::formatBytesPerPixel(Format format)
{
	LOG_TRACE("Image::formatBytesPerPixel()");
	switch(format)
	{
		case FORMAT_Y8: return 1;
		case FORMAT_RGB32: return 4;
		case FORMAT_RGB24: return 3;
		case FORMAT_RGB16: return 2;
		case FORMAT_RGB15: return 2;
		default: return 0;
	}
}

Image::Image(int width, int height, Format format)
{
	LOG_TRACE("Image::Image()");
	if(format == FORMAT_UNKNOWN)
	{
		LOG_WARNING("Image::Image(): Can not create image with unknown format and unknown bytes per bixel");
		throw CameraException("Can not create image with unknown format and unknown bytes per bixel");
	}
	
	m_buffer = NULL;
	reallocate(width, height, format);
}

Image::Image(int width, int height, int bytesPerPixel)
{
	LOG_TRACE("Image::Image()");
	
	m_buffer = NULL;
	reallocate(width, height, bytesPerPixel);
}

Image::~Image()
{
	LOG_TRACE("Image::~Image()");
	
	LOG_DEBUG("Image::~Image(): Releasing buffer (" << m_bufferSize << " bytes)");
	free(m_buffer);
}

void Image::reallocate(int width, int height)
{
	LOG_TRACE("Image::reallocate()");
	m_width = width;
	m_height = height;
	m_bufferSize = m_width * m_height * m_bytesPerPixel;
	
	LOG_DEBUG("Image::reallocate(): Allocating buffer " << m_width << "x" << m_height << "x" << m_bytesPerPixel << " (" << m_bufferSize << " bytes)");
	m_buffer = (ImageBuffer *) realloc(m_buffer, m_bufferSize);
	if(m_buffer == NULL)
	{
		LOG_ERROR("Image::reallocate(): Failed to allocate memory for image (" << m_bufferSize << " bytes)");
		throw CameraException("Failed to allocate memory for image");
	}
}

void Image::reallocate(int width, int height, Format format)
{
	m_format = format;
	m_bytesPerPixel = formatBytesPerPixel(format);
	reallocate(width, height);
}

void Image::reallocate(int width, int height, int bytesPerPixel)
{
	m_format = FORMAT_UNKNOWN;
	m_bytesPerPixel = bytesPerPixel;
	reallocate(width, height);
}

ImageBuffer *Image::getBufferAddress() const
{
	LOG_TRACE("Image::getBufferAddress()");
	return m_buffer;
}

int Image::getBufferSize() const
{
	LOG_TRACE("Image::getBufferSize()");
	return m_bufferSize;
}

Image::Format Image::getFormat() const
{
	LOG_TRACE("Image::getBufferFormat()");
	return m_format;
}

int Image::getWidth() const
{
	LOG_TRACE("Image::getWidth()");
	return m_width;
}

int Image::getHeight() const
{
	LOG_TRACE("Image::getHeight()");
	return m_height;
}

int Image::getBytesPerPixel() const
{
	LOG_TRACE("Image::getBytesPerPixel()");
	return m_bytesPerPixel;
}

} // namespace camera
