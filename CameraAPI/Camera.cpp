#include "Camera.h"
#include "CameraException.h"
#include "log.h"

namespace camera {

Camera::Camera() {
	LOG_TRACE("Camera::Camera()");
	
	_listener = NULL;
}

Camera::~Camera() {
	LOG_TRACE("Camera::~Camera()");
}

void Camera::setListener(CameraListener *listener) {
	LOG_TRACE("Camera::setCallbackClass()");
	_listener = listener;
}

void Camera::doNewImageCallback() {
	LOG_TRACE("Camera::doNewImageCallback()");
	if(_listener != NULL) {
		_listener->cameraNewImage(this);
	}
}

void Camera::doErrorCallback(int errorCode, const std::string &errorMessage) {
	LOG_TRACE("Camera::doErrorCallback()");
	if(_listener != NULL) {
		_listener->cameraError(this, errorCode, errorMessage);
	}
}

} // namespace camera