#ifndef __DUMMYCAMERA_H__
#define __DYMMYCAMERA_H__

#include "Camera.h"

namespace camera {

class DummyCamera : public Camera {
	public:
		DummyCamera(int width, int height);
		~DummyCamera();
		
		void start();
		void stop();
		bool isRunning();
		ImageBuffer* getLastImage();
		
	private:
		bool _running;
		ImageBuffer *_image;
};

} // namespace camera

#endif