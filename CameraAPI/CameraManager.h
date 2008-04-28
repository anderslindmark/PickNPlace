#ifndef __CAMERAAPI_H__
#define __CAMERAAPI_H__

#include "Driver.h"
#include "CameraIdentifier.h"

#include <vector>

namespace camera 
{

class CameraManager
{
	public:
		static CameraManager *getInstance();
		
		void addDriver(Driver *driver);
		void removeDriver(Driver *driver);
		void updateCameraIdentifiers();
		const CameraIdentifierList& getCameraIdentifiers();
		Camera *createCamera(CameraIdentifier identifier);
		
	protected:
		CameraManager();
		
	private:
		static CameraManager *m_instance;
		
		DriverList m_drivers;
		CameraIdentifierList m_identifiers;
};

} // namespace camera

#endif
