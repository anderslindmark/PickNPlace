#ifndef __CAMERALISTENER_H__
#define __CAMERALISTENER_H__

#include <string>
#include "Camera.h"
#include "ImageBuffer.h"

namespace camera {

//typedef void (*CameraCallbackFunction)(void *context, Camera *camera);

class CameraListener {
	public:
		virtual void cameraNewImage(Camera *camera) = 0;
		virtual void cameraError(Camera *camera, int errorCode, const std::string &errorMessage) = 0;
};

} // namespace camera

#endif
