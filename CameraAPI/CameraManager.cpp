#include "log.h"
#include "CameraManager.h"
#include "CameraException.h"

namespace camera 
{

CameraManager::CameraManager()
{
	LOG_TRACE("CameraManger::CameraManager()");
}

CameraManager::~CameraManager()
{
	LOG_TRACE("CameraManger::~CameraManager()");
}

void CameraManager::addDriver(Driver *driver)
{
	LOG_TRACE("CameraManager::addDriver");
	
	// Add the driver to our list of drivers
	m_drivers.push_back(driver);
	
	// Get the list of camera identifiers
	CameraIdentifierList ids = driver->getCameraIdentifiers();
	
	// ... and copy it to the local list
	m_identifiers.insert(m_identifiers.end(), ids.begin(), ids.end());
	
	LOG_DEBUG("Added driver " << driver->getVersionString());
}

void CameraManager::removeDriver(camera::Driver *driver) {
	for(DriverList::const_iterator iter = m_drivers.begin(); iter != m_drivers.end(); iter++)
	{
		if((*iter) == driver)
			m_drivers.erase(iter);
	}
	
	updateCameraIdentifiers();
}

void CameraManager::updateCameraIdentifiers()
{
	LOG_TRACE("CameraManager::updateCameraIdentifiers()");
	// Clear the list of identifiers
	m_identifiers.clear();
	
	// Loop through all drivers
	DriverList::const_iterator iter;
	for(iter = m_drivers.begin(); iter != m_drivers.end(); iter++)
	{
		// Get a list of camera identifiers...
		CameraIdentifierList ids = (*iter)->getCameraIdentifiers();
		
		// ... and copy it to the local list
		m_identifiers.insert(m_identifiers.end(), ids.begin(), ids.end());
	}
}

const CameraIdentifierList& CameraManager::getCameraIdentifiers()
{
	LOG_TRACE("CameraManger::getCameraIdentifiers()");
	return m_identifiers;
}

Camera *CameraManager::createCamera(CameraIdentifier identifier)
{
	LOG_TRACE("CameraManger::createCamera()");
	DriverList::const_iterator iter;
	for(iter = m_drivers.begin(); iter != m_drivers.end(); iter++)
	{
		if(identifier.driverIdentifier == (*iter)->getIdentifier())
		{
			return (*iter)->createCamera(identifier.cameraIdentifier);
		}
	}
	
	throw CameraException("No matching driver found");
}

} // namespace camera
