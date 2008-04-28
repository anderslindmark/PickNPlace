#ifndef __EURESYSCAMERA_H__
#define __EURESYSCAMERA_H__

#include "Camera.h"
#include "euresys/Include/MultiCam32.h"
#include "CameraIdentifier.h"

namespace camera {

class EuresysCamera : public Camera {
	public:
		EuresysCamera(const std::string &identifier, int width = -1, int height = -1, Image::Format format = Image::FORMAT_RGB32, int numSurfaces = 1);
		~EuresysCamera();
		
		void start();
		void stop();
		bool isRunning();
		
		void surfaceAvailableCallback(PECEVENTINFO eventInfo);
		void errorCallback(PECEVENTINFO eventInfo);
		
	private:
		void initialize(const std::string &identifier);
		void setParameters(int width, int height, Image::Format format);
		void createSurfaces(int numSurfacess);
		void registerCallbacks();
		void startAcquisition();
		
		bool m_running;
		ECHANDLE m_channel;
		std::vector<Image *> m_images;
};

} // namespace camera

#endif