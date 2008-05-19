#ifndef __DUMMYCAMERA_H__
#define __DYMMYCAMERA_H__

#include "Camera.h"

namespace camera 
{

class DummyCamera : public Camera 
{
	public:
		///
		/// \brief Create a new dummy camera.
		/// \param width The width of the output image.
		/// \param height The height of the output image.
		///
		DummyCamera(int width, int height);
		~DummyCamera();
		
		///
		/// \brief Render a dummy image and call the cameraNewImage on the camera listener.
		///
		void start();
		void stop();
		bool isRunning();
		
	private:
		bool m_running;
		Image *m_image;
};

} // namespace camera

#endif