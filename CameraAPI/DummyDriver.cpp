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

CameraIdentifierList DummyDriver::getCameraIdentifiers()
{
	LOG_TRACE("DummyDriver::getCameraIdentifiers()");
	
	// Clear the list of identifiers
	CameraIdentifierList identifiers;
	
	CameraIdentifier ci;
	ci.driverIdentifier = getIdentifier();
	std::stringstream ss;
	for(int i = 0; i < 3; i++)
	{
		ss.str("");
		ss << "camera" << i;
		ci.cameraIdentifier = ss.str();
		
		identifiers.push_back(ci);
		LOG_TRACE("DummyDriver::getCameraIdentifiers(): Added " << ci.encode());
	}
	return identifiers;
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
