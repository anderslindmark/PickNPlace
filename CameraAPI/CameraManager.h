#ifndef __CAMERAAPI_H__
#define __CAMERAAPI_H__

#include "Driver.h"

#include <vector>

namespace camera 
{

///
/// \brief This is a singleton class that keeps all drivers in one place and helps to select the right driver when creating a new camera.
///
class CameraManager
{
	public:
		///
		/// \brief Get the one and only instance of this singleton class by calling this method.
		///
		static CameraManager *getInstance();
		
		
		///
		/// \brief Add a driver to the CameraManager. The driver is then available when creating cameras with the createCamera method.
		/// \param driver The driver to be added.
		///
		void addDriver(Driver *driver);
		
		///
		/// \brief Remove a driver from the CameraManager.
		/// \param driver The driver to be removed.
		///
		void removeDriver(Driver *driver);
		
		///
		/// \brief Get the curent number of drivers in the CameraManager.
		///
		int getDriverCount();
		
		///
		/// \brief Get a driver
		/// \param index The index of the driver. 0 <= index <= getDriverCount() - 1
		///
		Driver *getDriver(int index);
		
		
		///
		/// \brief Create a camera.
		/// This method searches the available drivers for a matching driverIdentifier and then calls createCamera on than driver.
		/// If no matching driver is found a CameraException is thrown.
		/// \param driverIdentifier Specify which driver to use.
		/// \param cameraIdentifier This identifier will be sent to the matching driver's createCamera method.
		/// \see Driver::createCamera()
		Camera *createCamera(const std::string &driverIdentifier, const std::string &cameraIdentifier);
		
	protected:
		CameraManager();
		
	private:
		static CameraManager *m_instance;  ///< The singleton instance
		std::vector<Driver *> m_drivers;
};

} // namespace camera

#endif
