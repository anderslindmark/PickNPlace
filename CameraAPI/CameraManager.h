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
		void updateCameraIdentifiers();
		const CameraIdentifierList& getCameraIdentifiers();
		Camera *createCamera(CameraIdentifier identifier);
		
	private:
		DriverList drivers;
		CameraIdentifierList identifiers;
};

} // namespace camera

#endif
