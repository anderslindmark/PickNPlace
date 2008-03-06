#ifndef __CAMERA_H__
#define __CAMERA_H__

namespace camera 
{
	class Camera;
}

#include "CameraListener.h"
#include "ImageBuffer.h"

namespace camera 
{

class Camera 
{
	public:
		Camera();
		virtual ~Camera();
		
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual bool isRunning() = 0;
		virtual ImageBuffer* getLastImage() = 0;
		
		//void setBufferAvailableCallback(void *context, CameraCallbackFunction callbackFunction);
		//void setErrorCallback(void *context, CameraCallbackFunction callbackFunction);
		void setListener(CameraListener *listener);
		
	protected:
		void doNewImageCallback();
		void doErrorCallback(int errorCode, const std::string &errorMessage);
		
	private:
		//CameraCallbackFunction _bufferAvailableCallbackFunc;
		//void *_bufferAvailableCallbackContext;
		//CameraCallbackFunction _errorCallbackFunc;
		//void *_errorCallbackContext;
		
		CameraListener *_listener;
};

} // namespace camera

#endif