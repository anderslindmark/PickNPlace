#include "DummyDriver.h"
#include "DummyCamera.h"
#include "log.h"
#include <sstream>

namespace camera 
{

DummyDriver::DummyDriver()
{
	LOG_TRACE("DummyDriver::DummyDriver()");
	
	m_width = 256;
	m_height = 256;
}

DummyDriver::~DummyDriver()
{
	LOG_TRACE("DummyDriver::~DummyDriver()");
}

void DummyDriver::updateCameraIdentifiers()
{
	LOG_TRACE("DummyDriver::updateCameraIdentifiers()");
}

int DummyDriver::getCameraIdentifierCount()
{
	LOG_TRACE("DummyDriver::getCameraIdentifierCount()");
	return 3;
}

std::string DummyDriver::getCameraIdentifier(int index)
{
		LOG_TRACE("DummyDriver::getCameraIdentifier()");
		
		std::stringstream ss;
		ss << "camera" << index;
		return ss.str();
}

Camera *DummyDriver::createCamera(const std::string &identifier) 
{
	LOG_TRACE("DummyDriver::createCamera()");
	LOG_DEBUG("DummyDriver::createCamera(): Creating camera " << identifier);
	return new DummyCamera(m_width, m_height);
}

void DummyDriver::setImageSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

} // namespace camera
