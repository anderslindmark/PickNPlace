#ifndef __CAMERA_H__
#define __CAMERA_H__

namespace camera 
{
	class Camera;
}

#include "CameraListener.h"
#include "Image.h"
#include "Filter.h"

namespace camera 
{

///
/// \brief The base class for all cameras.
///
class Camera 
{
	public:
		Camera();
		virtual ~Camera();
		
		///
		/// \brief Start the image acquiring for this camera.
		///
		virtual void start() = 0;
		
		///
		/// \brief Stop the image acquiring for this camera.
		///
		virtual void stop() = 0;
		
		///
		/// \brief Check if this camera is started.
		///
		virtual bool isRunning() = 0;
		
		///
		/// \brief Get the last image this camera has acquired.
		/// \return The latest image. NULL if no image has been acquired yet.
		///
		Image* getLastImage();
		
		
		///
		/// \brief Set the listener of this camera. The listener is notified when a new image is available or when an error has occurred.
		///
		void setListener(CameraListener *listener);
		
		///
		/// \brief Add a filter to the camera.
		/// Filters are applied before the listener is notified.
		///
		void addFilter(Filter *filter);
		
		///
		/// \brief Remove a filter from the camera.
		///
		void removeFilter(Filter *filter);
		
	protected:
		///
		/// \brief Calling this method will apply all filters to the image and notify the listener that a new image is available.
		///
		void doNewImageCallback(Image *image);
		
		///
		/// \brief Calling this method will notify the listener that an error has occurred.
		///
		void doErrorCallback(int errorCode, const std::string &errorMessage);
		
	private:
		Image *m_lastImage;
		CameraListener *m_listener;
		FilterList m_filters;
};

} // namespace camera

#endif