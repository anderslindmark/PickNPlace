#ifndef __CAMERAIDENTIFIER_H__
#define __CAMERAIDENTIFIER_H__

#include <string>
#include <vector>

namespace camera {

struct CameraIdentifier
{
	std::string displayName;
	std::string driverIdentifier;
	std::string cameraIdentifier;
};

typedef std::vector<CameraIdentifier> CameraIdentifierList;

} // namespace camera

#endif