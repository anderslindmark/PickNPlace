#include "Camera.h"
#include "CameraException.h"
#include "log.h"

namespace camera 
{

Camera::Camera() 
{
	LOG_TRACE("Camera::Camera()");
		
	m_listener = NULL;
	m_lastImage = NULL;
}

Camera::~Camera()
{
	LOG_TRACE("Camera::~Camera()");
}

Image *Camera::getLastImage()
{
	return m_lastImage;
}

void Camera::addFilter(Filter *filter)
{
	m_filters.push_back(filter);
}

void Camera::removeFilter(camera::Filter *filter)
{
	for(FilterList::const_iterator iter = m_filters.begin(); iter != m_filters.end(); iter++)
	{
		if((*iter) == filter)
			m_filters.erase(iter);
	}
}

void Camera::setListener(CameraListener *listener) 
{
	LOG_TRACE("Camera::setCallbackClass()");
	m_listener = listener;
}

void Camera::doNewImageCallback(Image *image)
{
	LOG_TRACE("Camera::doNewImageCallback()");
	
	// Apply all filters
	for(FilterList::const_iterator iter = m_filters.begin(); iter != m_filters.end(); iter++)
	{
		if((*iter)->getEnabled())
		{
			image = (*iter)->apply(image);
		}
	}
	
	m_lastImage = image;
	if(m_listener != NULL) 
	{
		m_listener->cameraNewImage(this, image);
	}
}

void Camera::doErrorCallback(int errorCode, const std::string &errorMessage)
{
	LOG_TRACE("Camera::doErrorCallback()");
	if(m_listener != NULL)
	{
		m_listener->cameraError(this, errorCode, errorMessage);
	}
}

} // namespace camera