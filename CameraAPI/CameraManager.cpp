#include "log.h"
#include "CameraManager.h"
#include "CameraException.h"

namespace camera 
{

CameraManager *CameraManager::m_instance = NULL;

CameraManager::CameraManager()
{
	LOG_TRACE("CameraManger::CameraManager()");
}

CameraManager *CameraManager::getInstance()
{
	LOG_TRACE("CameraManger::getInstance()");
	
	// Not thread safe!
	if(m_instance == NULL)
	{
		m_instance = new CameraManager();
	}
	
	return m_instance;
}

void CameraManager::addDriver(Driver *driver)
{
	LOG_TRACE("CameraManager::addDriver");
	
	// Add the driver to the private list of drivers
	m_drivers.push_back(driver);
	
	LOG_DEBUG("Added driver " << driver->getVersionString());
}

void CameraManager::removeDriver(camera::Driver *driver)
{
	LOG_TRACE("CameraManager::removeDriver()");
	
	std::vector<Driver*>::const_iterator iter;
	for(iter = m_drivers.begin(); iter != m_drivers.end(); iter++)
	{
		if((*iter) == driver) {
			m_drivers.erase(iter);
			LOG_DEBUG("Removed driver " << driver->getVersionString());
		}
	}
}

int CameraManager::getDriverCount()
{
	LOG_TRACE("CameraManger::getDriverCount()");
	return m_drivers.size();
}

Driver *CameraManager::getDriver(int index)
{
	LOG_TRACE("CameraManger::getDriver()");
	return m_drivers.at(index);
}

Camera *CameraManager::createCamera(const std::string &driverIdentifier, const std::string &cameraIdentifier)
{
	LOG_TRACE("CameraManger::createCamera()");
	
	std::vector<Driver *>::const_iterator iter;
	for(iter = m_drivers.begin(); iter != m_drivers.end(); iter++)
	{
		// Search for a driver with a maching driver identifier
		if(driverIdentifier == (*iter)->getIdentifier())
		{
			// Create the camera
			return (*iter)->createCamera(cameraIdentifier);
		}
	}
	
	LOG_WARNING("No matching driver found (" << driverIdentifier << ")");
	throw CameraException("No matching driver found");
}

} // namespace camera
