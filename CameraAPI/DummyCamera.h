#ifndef __DUMMYCAMERA_H__
#define __DYMMYCAMERA_H__

#include "Camera.h"

namespace camera 
{

class DummyCamera : public Camera 
{
	public:
		DummyCamera(int width, int height);
		~DummyCamera();
		
		void start();
		void stop();
		bool isRunning();
		
	private:
		bool m_running;
		Image *m_image;
};

} // namespace camera

#endif