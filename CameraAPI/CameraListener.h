#ifndef __CAMERALISTENER_H__
#define __CAMERALISTENER_H__

#include <string>
#include "Camera.h"
#include "Image.h"

namespace camera 
{

///
/// \brief Classes that inherit this abstract class and implements the virtual methods can be used as camera listeners.
/// \see Camera::setListener()
///		
class CameraListener 
{
	public:
		///
		/// \brief This method is called when a new image is available in the camera.
		/// \param camera The camera that produced the new image.
		/// \param image The new image. This is the same image as you get when calling camera->getLastImage()
		///
		virtual void cameraNewImage(Camera *camera, Image *image) = 0;
		
		///
		/// \brief This method is called when an error has occurred in the camera.
		/// \param camera The camera that produced the error.
		/// \param errorCode The error code.
		/// \param errorMessage The error message.
		///
		virtual void cameraError(Camera *camera, int errorCode, const std::string &errorMessage) = 0;
};

} // namespace camera

#endif
