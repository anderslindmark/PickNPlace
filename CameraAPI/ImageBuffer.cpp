#include "ImageBuffer.h"
#include "log.h"

namespace camera {

ImageBuffer::ImageBuffer(int width, int height, Format format, int bytesPerPixel) {
	LOG_TRACE("ImageBuffer::ImageBuffer()");
	
	_width = width;
	_height = height;
	_format = format;
	_bytesPerPixel = bytesPerPixel == -1 ? formatBytesPerPixel(format) : bytesPerPixel;
	_bufferSize = _width * _height * _bytesPerPixel;
	
	LOG_DEBUG("ImageBuffer::ImageBuffer(): Allocating buffer " << _width << "x" << _height << "x" << _bytesPerPixel << " (" << _bufferSize << " bytes)");
	_buffer = new Buffer[_bufferSize];
}

ImageBuffer::~ImageBuffer() {
	LOG_TRACE("ImageBuffer::~ImageBuffer()");
	
	LOG_DEBUG("ImageBuffer::~ImageBuffer(): Releasing buffer (" << _bufferSize << " bytes)");
	delete[] _buffer;
}

Buffer *ImageBuffer::getBufferAddress() const {
	LOG_TRACE("ImageBuffer::getBufferAddress()");
	return _buffer;
}

int ImageBuffer::getBufferSize() const {
	LOG_TRACE("ImageBuffer::getBufferSize()");
	return _bufferSize;
}

ImageBuffer::Format ImageBuffer::getFormat() const {
	LOG_TRACE("ImageBuffer::getBufferFormat()");
	return _format;
}

int ImageBuffer::getWidth() const {
	LOG_TRACE("ImageBuffer::getWidth()");
	return _width;
}

int ImageBuffer::getHeight() const {
	LOG_TRACE("ImageBuffer::getHeight()");
	return _height;
}

int ImageBuffer::getBytesPerPixel() const {
	LOG_TRACE("ImageBuffer::getBytesPerPixel()");
	return _bytesPerPixel;
}

int ImageBuffer::formatBytesPerPixel(Format format) {
	LOG_TRACE("ImageBuffer::formatBytesPerPixel()");
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
