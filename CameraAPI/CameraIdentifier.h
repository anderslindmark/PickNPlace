#ifndef __CAMERAIDENTIFIER_H__
#define __CAMERAIDENTIFIER_H__

#include <string>

namespace camera {

struct CameraIdentifier
{
	std::string displayName;
	std::string driverIdentifier;
	std::string cameraIdentifier;
};

} // namespace camera

#endif