#ifndef __CAMERAAPI_H__
#define __CAMERAAPI_H__

#include "Driver.h"
#include "CameraIdentifier.h"

#include <vector>

namespace camera 
{

// TODO: Make class singleton?
class CameraManager
{
	public:
		CameraManager();
		~CameraManager();
		
		void addDriver(Driver *driver);
		void removeDriver(Driver *driver);
		void updateCameraIdentifiers();
		const CameraIdentifierList& getCameraIdentifiers();
		Camera *createCamera(CameraIdentifier identifier);
		
	private:
		DriverList m_drivers;
		CameraIdentifierList m_identifiers;
};

} // namespace camera

#endif
