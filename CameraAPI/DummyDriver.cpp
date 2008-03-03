#include "DummyDriver.h"
#include "log.h"
#include <sstream>

namespace camera {
namespace driver {

DummyDriver::DummyDriver()
{
	LOG_TRACE("DummyDriver::DummyDriver()");
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
		
		ss.str("");
		ss << "Dummy Camera " << i;
		ci.displayName = ss.str();
		
		identifiers.push_back(ci);
		LOG_TRACE("DummyDriver::getCameraIdentifiers(): Added " << ci.cameraIdentifier << " (" << ci.displayName << ")");
	}
	return identifers;
}

} // namespace driver
} // namespace camera
