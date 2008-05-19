#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "Camera.h"
#include <vector>

namespace camera 
{

class Driver
{
	public:
		Driver();
		virtual ~Driver();
		
		///
		/// \brief Returns an identifier string for this driver. For example "MyDriver".
		///
		virtual std::string getIdentifier() = 0;
		
		///
		/// \brief Returns the readable name for this driver. For example "My driver".
		///
		virtual std::string getName() = 0;
		
		///
		/// \brief Returns the major version number.
		///
		virtual int getVersionMajor() = 0;
		
		///
		/// \brief Returns the minor version number.
		///
		virtual int getVersionMinor() = 0;
		
		///
		/// \brief Returns a full version string using getName and getVersion*. For example "My driver v1.2".
		///
		std::string getVersionString();
		
		///
		/// \brief Updates the drivers internal list of cameras. This method is typicaly called before listing cameras
		///
		virtual void updateCameraIdentifiers() = 0;
		
		///
		/// \brief Returns the number of cameras this driver have found
		///
		virtual int getCameraIdentifierCount() = 0;
		
		///
		/// \brief Returns a identifier string for camera with index index
		///
		virtual std::string getCameraIdentifier(int index) = 0;
		
		///
		/// \brief Create a Camera
		/// \return A pointer to the created camera.
		///
		virtual Camera *createCamera(const std::string &identifier) = 0;
};

} // namespace camera

#endif
