#ifndef __EURESYSCAMERA_H__
#define __EURESYSCAMERA_H__

#include "Camera.h"
#include "euresys/Include/MultiCam32.h"
#include "CameraIdentifier.h"

namespace camera {

class EuresysCamera : public Camera {
	public:
		EuresysCamera(const std::string &identifier, int width = -1, int height = -1, Image::Format format = Image::FORMAT_RGB24, int numSurfaces = 3);
		~EuresysCamera();
		
		void start();
		void stop();
		bool isRunning();
		Image* getLastImage();
		
		void surfaceAvailableCallback(PECEVENTINFO eventInfo);
		void errorCallback(PECEVENTINFO eventInfo);
		
	private:
		void initialize(const std::string &identifier);
		void setParameters(int width, int height, Image::Format format);
		void createSurfaces(int numSurfacess);
		void registerCallbacks();
		void startAcquisition();
		
		bool _running;
		ECHANDLE _channel;
		std::vector<Image *> images;
		Image *lastImage;
};

} // namespace camera

#endif