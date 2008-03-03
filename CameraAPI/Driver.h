#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "CameraIdentifier.h"
#include <vector>

namespace camera {
namespace driver {

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
		/// \brief Returns a list of camera identifiers
		///
		virtual const CameraIdentifierList getCameraIdentifiers() = 0;
};

typedef std::vector<Driver *> DriverList;

} // namespace driver
} // namespace camera

#endif
