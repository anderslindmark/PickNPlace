#ifndef __CAMERAEXCEPTION_H__
#define __CAMERAEXCEPTION_H__

#include <stdexcept>

namespace camera 
{

class CameraException : public std::runtime_error
{
	public:
		CameraException(const std::string& message) : std::runtime_error(message) {}
};

} // namespace camera

#endif