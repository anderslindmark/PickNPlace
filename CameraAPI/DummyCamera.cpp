#include "DummyCamera.h"
#include "log.h"

namespace camera 
{

DummyCamera::DummyCamera(int width, int height) 
{
	LOG_TRACE("DummyCamera::DummyCamera()");
	
	_image = new ImageBuffer(width, height, ImageBuffer::FORMAT_RGB24);
	
	// Set whole buffer to zero
	int bufferSize = _image->getBufferSize();
	unsigned char *p = _image->getBufferAddress();
	for(int i = 0; i < bufferSize; i++) 
	{
		*p = 0;
		p++;
	}
	
	_running = false;
}

DummyCamera::~DummyCamera() 
{
	LOG_TRACE("DummyCamera::~DummyCamera()");
	
	delete _image;
}

ImageBuffer *DummyCamera::getLastImage() 
{
	LOG_TRACE("DummyCamera::getLastImage()");
	return _image;
}

void DummyCamera::start() 
{
	LOG_TRACE("DummyCamera::start()");
	_running = true;
	
	// Just draw something
	Buffer *buffer = _image->getBufferAddress();
	int height = _image->getHeight();
	int width = _image->getWidth();
	for(int y = 0; y < height; y++) 
	{
		for(int x = 0; x < width; x++) 
		{
			// It should be 3 bytes per pixel
			*buffer = y^x % 256; // Red
			buffer++;
			*buffer = y^x % 256; // Green
			buffer++;
			*buffer = y^x % 256; // Blue
			buffer++;
		}
	}
}

void DummyCamera::stop()
{
	LOG_TRACE("DummyCamera::stop()");
	_running = false;
}

bool DummyCamera::isRunning()
{
	LOG_TRACE("DummyCamera::isRunning()");
	return _running;
}

} // namespace camera