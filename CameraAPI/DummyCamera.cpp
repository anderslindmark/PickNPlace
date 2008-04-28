#include "DummyCamera.h"
#include "log.h"

namespace camera 
{

DummyCamera::DummyCamera(int width, int height) 
{
	LOG_TRACE("DummyCamera::DummyCamera()");
	
	m_image = new Image(width, height, Image::FORMAT_RGB32);
	// Set whole buffer to zero
	int bufferSize = m_image->getBufferSize();
	unsigned char *p = m_image->getBufferAddress();
	for(int i = 0; i < bufferSize; i++) 
	{
		*p = 0;
		p++;
	}
	
	m_running = false;
}

DummyCamera::~DummyCamera() 
{
	LOG_TRACE("DummyCamera::~DummyCamera()");
	
	delete m_image;
}

void DummyCamera::start() 
{
	LOG_TRACE("DummyCamera::start()");
	m_running = true;
	
	// Just draw something
	ImageBuffer *buffer = m_image->getBufferAddress();
	int height = m_image->getHeight();
	int width = m_image->getWidth();
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

	doNewImageCallback(m_image);
}

void DummyCamera::stop()
{
	LOG_TRACE("DummyCamera::stop()");
	m_running = false;
}

bool DummyCamera::isRunning()
{
	LOG_TRACE("DummyCamera::isRunning()");
	return m_running;
}

} // namespace camera