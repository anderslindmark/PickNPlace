#include "Driver.h"
#include "log.h"
#include <sstream>

namespace camera 
{

Driver::Driver()
{
	LOG_TRACE("Driver::Driver()");
}

Driver::~Driver()
{
	LOG_TRACE("Driver::~Driver()");
}

std::string Driver::getVersionString()
{
	LOG_TRACE("Driver::getVersionString()");
	std::stringstream ss;
	ss << getName() << " v" << getVersionMajor() << "." << getVersionMinor();
	return ss.str();
}

} // namespace camera
