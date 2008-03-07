#ifndef __EURESYSCAMERA_H__
#define __EURESYSCAMERA_H__

#include "Camera.h"
#include "euresys/Include/MultiCam32.h"
#include "CameraIdentifier.h"

namespace camera {

class EuresysCamera : public Camera {
	public:
		EuresysCamera(const std::string &identifier);
		EuresysCamera(const std::string &identifier, int width, int height, Image::Format format, int numSurfaces);
		~EuresysCamera();
		
		void start();
		void stop();
		bool isRunning();
		Image* getLastImage();
		
		void SurfaceAvailableCallback(PECEVENTINFO eventInfo);
		void ErrorCallback(PECEVENTINFO eventInfo);
		
	private:
		void initialize(const std::string &identifier);
		void setParameters(int width, int height, Image::Format format);
		void createSurfaces(int numSurfacess);
		void registerCallbacks();
		void startAcquisition();
		
		bool _running;
		ECHANDLE _channel;
		//Image *_image;
};

} // namespace camera

#endif