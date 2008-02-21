#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "CameraIdentifier.h"
#include <vector>

namespace camera {

class Driver
{
	public:
		Driver();
		virtual ~Driver();
		
		virtual std::string getIdentifier() = 0;
		virtual std::string getName() = 0;
		virtual int getVersionMajor() = 0;
		virtual int getVersionMinor() = 0;
		std::string getVersionString();
		
		virtual std::vector<CameraIdentifier> getCameraIdentifiers() = 0;
		
	private:
		
};

} // namespace camera

#endif
