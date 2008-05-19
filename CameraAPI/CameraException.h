#ifndef __CAMERAEXCEPTION_H__
#define __CAMERAEXCEPTION_H__

#include <stdexcept>

namespace camera 
{

///
/// \brief This exception will be thrown by the camera API
///
class CameraException : public std::runtime_error
{
	public:
		CameraException(const std::string& message) : std::runtime_error(message) {}
};

} // namespace camera

#endif