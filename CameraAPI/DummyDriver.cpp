#include "DummyDriver.h"
#include "DummyCamera.h"
#include "log.h"
#include <sstream>

namespace camera {

DummyDriver::DummyDriver()
{
	LOG_TRACE("DummyDriver::DummyDriver()");
	
	_width = 256;
	_height = 256;
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

Camera *DummyDriver::createCamera(CameraIdentifier identifier) {
	LOG_TRACE("DummyDriver::createCamera()");
	LOG_DEBUG("DummyDriver::createCamera(): Creating camera " << identifier.encode());
	return new DummyCamera(_width, _height);
}

void DummyDriver::setImageSize(int width, int height) {
	_width = width;
	_height = height;
}

} // namespace camera
