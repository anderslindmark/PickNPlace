#ifndef __CAMERAAPI_H__
#define __CAMERAAPI_H__

#include "Driver.h"
#include "CameraIdentifier.h"

#include <vector>

namespace camera {

/**
 * @todo Make class singleton?
 */
class CameraManager
{
	public:
		CameraManager();
		~CameraManager();
		
		void addDriver(Driver *driver);
		void deleteAllDrivers();
		int getCameraCount();
		CameraIdentifier getCameraIdentifier(int index) const;
		
	private:
		std::vector<Driver *> drivers;
		std::vector<CameraIdentifier> identifiers;
};

} // namespace camera

#endif
