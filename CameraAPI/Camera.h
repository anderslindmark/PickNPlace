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

class Camera 
{
	public:
		Camera();
		virtual ~Camera();
		
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual bool isRunning() = 0;
		Image* getLastImage();
		
		void setListener(CameraListener *listener);
		
		void addFilter(Filter *filter);
		void removeFilter(Filter *filter);
		
	protected:
		void doNewImageCallback(Image *image);
		void doErrorCallback(int errorCode, const std::string &errorMessage);
		
	private:
		Image *m_lastImage;
		CameraListener *m_listener;
		FilterList m_filters;
};

} // namespace camera

#endif