#include "CameraIdentifier.h"
#include "CameraException.h"

namespace camera 
{

CameraIdentifier::CameraIdentifier(const std::string &str) 
{
	decode(str);
}

void CameraIdentifier::decode(const std::string &str) 
{
	std::string::size_type pos = str.find_first_of('.');
	if(pos == std::string::npos)
		throw CameraException("Illegal identifier string (no '.' found)");
	
	driverIdentifier = std::string(str, 0, pos);
	cameraIdentifier = std::string(str, pos + 1);
}

std::string CameraIdentifier::encode() const 
{
	std::string s(driverIdentifier);
	s.append(".");
	s.append(cameraIdentifier);
	return s;
}

} // namespace camera