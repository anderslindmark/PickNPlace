#include "Image.h"
#include "log.h"

namespace camera {

Image::Image(int width, int height, Format format) {
	// TODO: Throw exception if format == FORMAT_UMKNOWN?
	init(width, height, format, formatBytesPerPixel(format));
}

Image::Image(int width, int height, int bytesPerPixel) {
	init(width, height, FORMAT_UNKNOWN, bytesPerPixel);
}

void Image::init(int width, int height, Format format, int bytesPerPixel) {
	LOG_TRACE("Image::Image()");
	_width = width;
	_height = height;
	_format = format;
	_bytesPerPixel = bytesPerPixel;
	_bufferSize = _width * _height * _bytesPerPixel;
	
	LOG_DEBUG("Image::init(): Allocating buffer " << _width << "x" << _height << "x" << _bytesPerPixel << " (" << _bufferSize << " bytes)");
	_buffer = new ImageBuffer[_bufferSize];
}

Image::~Image() {
	LOG_TRACE("Image::~Image()");
	
	LOG_DEBUG("Image::~Image(): Releasing buffer (" << _bufferSize << " bytes)");
	delete[] _buffer;
}

ImageBuffer *Image::getBufferAddress() const {
	LOG_TRACE("Image::getBufferAddress()");
	return _buffer;
}

int Image::getBufferSize() const {
	LOG_TRACE("Image::getBufferSize()");
	return _bufferSize;
}

Image::Format Image::getFormat() const {
	LOG_TRACE("Image::getBufferFormat()");
	return _format;
}

int Image::getWidth() const {
	LOG_TRACE("Image::getWidth()");
	return _width;
}

int Image::getHeight() const {
	LOG_TRACE("Image::getHeight()");
	return _height;
}

int Image::getBytesPerPixel() const {
	LOG_TRACE("Image::getBytesPerPixel()");
	return _bytesPerPixel;
}

int Image::formatBytesPerPixel(Format format) {
	LOG_TRACE("Image::formatBytesPerPixel()");
	switch(format) {
		case FORMAT_Y8: return 1;
		case FORMAT_RGB32: return 4;
		case FORMAT_RGB24: return 3;
		case FORMAT_RGB16: return 2;
		case FORMAT_RGB15: return 2;
		default: return 0;
	}
}

} // namespace camera
