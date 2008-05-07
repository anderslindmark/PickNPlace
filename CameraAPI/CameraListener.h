#ifndef __CAMERALISTENER_H__
#define __CAMERALISTENER_H__

#include <string>
#include "Camera.h"
#include "Image.h"

namespace camera 
{

class CameraListener 
{
	public:
		virtual void cameraNewImage(Camera *camera, Image *image) = 0;
		virtual void cameraError(Camera *camera, int errorCode, const std::string &errorMessage) = 0;
};

} // namespace camera

#endif
