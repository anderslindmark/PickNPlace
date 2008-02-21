#include "log.h"
#include "CameraManager.h"

namespace camera {

CameraManager::CameraManager()
{
	LOG_TRACE("CameraManger::CameraManager()");
}

CameraManager::~CameraManager()
{
	LOG_TRACE("CameraManger::~CameraManager()");
	deleteAllDrivers();
}

void CameraManager::addDriver(Driver *driver)
{
	LOG_TRACE("CameraManager::addDriver");
	drivers.push_back(driver);
	
	LOG_DEBUG("Added driver " << driver->getVersionString());
}

void CameraManager::deleteAllDrivers()
{
	LOG_TRACE("CameraManager::deleteAllDrivers()");
	while(!drivers.empty())
	{
		delete drivers.back();
		drivers.pop_back();
	}
}

int CameraManager::getCameraCount()
{
	LOG_TRACE("CameraManger::getCameraCount()");
	return identifiers.size();
}

} // namespace camera
