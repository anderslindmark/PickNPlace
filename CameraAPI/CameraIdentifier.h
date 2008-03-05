#ifndef __CAMERAIDENTIFIER_H__
#define __CAMERAIDENTIFIER_H__

#include <string>
#include <vector>

namespace camera {

class CameraIdentifier
{
	public:
		CameraIdentifier() {};
		CameraIdentifier(const std::string &str);
		
		void decode(const std::string &str);
		std::string encode() const;
		
		std::string driverIdentifier;
		std::string cameraIdentifier;
};

typedef std::vector<CameraIdentifier> CameraIdentifierList;

} // namespace camera

#endif