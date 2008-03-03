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

void CameraManager::addDriver(driver::Driver *driver)
{
	LOG_TRACE("CameraManager::addDriver");
	
	// Add the driver to our list of drivers
	drivers.push_back(driver);
	
	// Get the list of camera identifiers
	CameraIdentifierList ids = driver->getCameraIdentifiers();
	
	// ... and copy it to the local list
	identifiers.insert(identifiers.end(), ids.begin(), ids.end());
	
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

void CameraManager::updateCameraIdentifiers()
{
	LOG_TRACE("CameraManager::updateCameraIdentifiers()");
	// Clear the list of identifiers
	identifiers.clear();
	
	// Loop through all drivers
	driver::DriverList::const_iterator iter;
	for(iter = drivers.begin(); iter != drivers.end(); iter++)
	{
		// Get a list of camera identifiers...
		CameraIdentifierList ids = (*iter)->getCameraIdentifiers();
		
		// ... and copy it to the local list
		identifiers.insert(identifiers.end(), ids.begin(), ids.end());
	}
}

const CameraIdentifierList& CameraManager::getCameraIdentifiers()
{
	LOG_TRACE("CameraManger::getCameraIdentifiers()");
	return identifiers;
}

//Camera CameraManager::createCamera(CameraIdentifier identifier)
//{
//	LOG_TRACE("CameraManger::createCamera()");
//}

} // namespace camera
