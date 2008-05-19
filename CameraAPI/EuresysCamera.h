#ifndef __EURESYSCAMERA_H__
#define __EURESYSCAMERA_H__

#include "Camera.h"
#include "euresys/Include/MultiCam32.h"

namespace camera {

class EuresysCamera : public Camera {
	public:
		///
		/// \brief Create a new euresys camera
		/// \param identifier Possible identifiers: <ul><li>#<BoardID> (position in the boardList array), "#0"</li><li>@<BoardType>_<SerialNumber>, "@PICOLO_000731"</li><li>&<InternalName>, "&MyPicoloPro"</li><li>%<PciPosition>, "%9"</li></ul>
		/// \param width The width of the output image from the camera. Both width and height have to be set for this to take effect.
		/// \param height The height of the output image from the camera. Both width and height have to be set for this to take effect.
		/// \param format The pixel format of the output image from the camera.
		/// \param numSurfaces The number of surfaces (memory spaces) the hardware can write the captured image to. The surfaces are cycled so the more surfaces you have, the longer time it takes for the image in one surface to be overwritten. Use more surfaces if the time to process the image data can sometimes be longer than the time to campure the next frame from the camera.
		///
		EuresysCamera(const std::string &identifier, int width = -1, int height = -1, Image::Format format = Image::FORMAT_RGB32, int numSurfaces = 1);
		~EuresysCamera();
		
		void start();
		void stop();
		bool isRunning();
		
		///
		/// \brief This method is called by the driver when a new image is available.
		///
		void surfaceAvailableCallback(PECEVENTINFO eventInfo);
		
		///
		/// \brief This method is called by the driver when a error has occurred.
		///
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