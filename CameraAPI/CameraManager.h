#ifndef __CAMERAAPI_H__
#define __CAMERAAPI_H__

#include "Driver.h"

#include <vector>

namespace camera 
{

class CameraManager
{
	public:
		static CameraManager *getInstance();
		
		void addDriver(Driver *driver);
		void removeDriver(Driver *driver);
		int getDriverCount();
		Driver *getDriver(int index);
		
		Camera *createCamera(const std::string &driverIdentifier, const std::string &cameraIdentifier);
		
	protected:
		CameraManager();
		
	private:
		static CameraManager *m_instance;
		std::vector<Driver *> m_drivers;
};

} // namespace camera

#endif
