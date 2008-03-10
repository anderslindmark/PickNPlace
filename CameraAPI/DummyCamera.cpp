#include "DummyCamera.h"
#include "log.h"

namespace camera 
{

DummyCamera::DummyCamera(int width, int height) 
{
	LOG_TRACE("DummyCamera::DummyCamera()");
	
	_image = new Image(width, height, Image::FORMAT_RGB32);
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

Image *DummyCamera::getLastImage()
{
	LOG_TRACE("DummyCamera::getLastImage()");
	return _image;
}

void DummyCamera::start() 
{
	LOG_TRACE("DummyCamera::start()");
	_running = true;
	
	// Just draw something
	ImageBuffer *buffer = _image->getBufferAddress();
	int height = _image->getHeight();
	int width = _image->getWidth();
	ImageBuffer c;
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			// Using RGB24
			c = y^x % 256;
			*buffer = c; // Red
			buffer++;
			*buffer = c; // Green
			buffer++;
			*buffer = c; // Blue
			buffer++;
			buffer++;
		}
	}

	doNewImageCallback();
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