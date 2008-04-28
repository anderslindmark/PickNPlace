#include "EuresysCamera.h"
#include "euresys/Include/MultiCam32.h"
#include "CameraException.h"
#include "EuresysDriver.h"
#include <sstream>
#include "log.h"

namespace camera {

namespace euresys {
void WINAPI surfaceAvailableCallback(PVOID context, PECEVENTINFO eventInfo)
{
	((EuresysCamera *) context)->surfaceAvailableCallback(eventInfo);
}

void WINAPI errorCallback(PVOID context, PECEVENTINFO eventInfo)
{
	((EuresysCamera *) context)->errorCallback(eventInfo);
}

} // namespace euresys

EuresysCamera::EuresysCamera(const std::string &identifier, int width, int height, Image::Format format, int numSurfaces)
{
	LOG_TRACE("EuresysCamera::EuresysCamera()");

	initialize(identifier);
	
	setParameters(width, height, format);
	
	createSurfaces(numSurfaces);
	
	registerCallbacks();

	stop();

	startAcquisition();
}

EuresysCamera::~EuresysCamera()
{
	LOG_TRACE("EuresysCamera::~EuresysCamera()");
	while(!m_images.empty())
	{
		delete m_images.back();
		m_images.pop_back();
	}
}

void EuresysCamera::start()
{
	LOG_TRACE("EuresysCamera::start()");
	MultiCamChannelSetParameterInt(m_channel, EC_PARAM_RepeatGrabCount, -1 );
	MultiCamChannelSetParameterInt(m_channel, EC_PARAM_ChannelState, CHANNEL_STATE_ACTIVE);
	m_running = true;
}

void EuresysCamera::stop()
{
	LOG_TRACE("EuresysCamera::stop()");
	MultiCamChannelSetParameterInt(m_channel, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);
	m_running = false;
}

bool EuresysCamera::isRunning()
{
	LOG_TRACE("EuresysCamera::isRunning()");
	return m_running;
}

void EuresysCamera::initialize(const std::string &identifier)
{
	LOG_TRACE("EuresysCamera::initialize()");
	std::string::size_type pos = identifier.find_first_of('.');
	if(pos == std::string::npos) {
		LOG_ERROR("EuresysCamera::initialize(): '" << identifier << "' is not a valid camera identifier");
		throw CameraException("Illegal Euresys camera identifier (no '.' found)");
	}
	
	std::string asmIdentification = std::string(identifier, 0, pos);
	
	int sourceId;
	std::stringstream ss;
	ss << std::string(identifier, pos + 1);
	ss >> sourceId;
	
	m_channel = MultiCamChannelCreate(NULL, asmIdentification.c_str(), sourceId);
	if(m_channel <= 0) {
		LOG_ERROR("EuresysCamera::initialize(): Failed to create channel " << asmIdentification << ", " << sourceId << " (" << m_channel << ")");
		throw CameraException("Failed to create camera");
	}
}

void EuresysCamera::setParameters(int width, int height, Image::Format format)
{
	LOG_TRACE("EuresysCamera::setParameters()");
	MultiCamChannelSetParameterInt(m_channel, EC_PARAM_TriggerMask, TRIGGERMASK_NONE);
	MultiCamChannelSetParameterInt(m_channel, EC_PARAM_AssemblerMask, ASMMASK__DELAY);
	MultiCamChannelSetParameterInt(m_channel, EC_PARAM_Standard, EC_STANDARD_PAL);
	MultiCamChannelSetParameterInt(m_channel, EC_PARAM_FieldMode, 2);
	MultiCamChannelSetParameterInt(m_channel, EC_PARAM_AcqColFmt, EuresysDriver::toEuresysFormat(format));
	if(width > 0)
	{
		MultiCamChannelSetParameterInt(m_channel, EC_PARAM_ImageSizeX, width);
	}
	if(height > 0)
	{
		MultiCamChannelSetParameterInt(m_channel, EC_PARAM_ImageSizeY, height);
	}
}

void EuresysCamera::createSurfaces(int numSurfaces)
{
	LOG_TRACE("EuresysCamera::createSurfaces()");
	int width;
	int height;
	int euresysFormat;
	Image::Format format;
	
	// Get parameters
	MultiCamChannelGetParameterInt(m_channel, EC_PARAM_ImageSizeX, &width);
	MultiCamChannelGetParameterInt(m_channel, EC_PARAM_ImageSizeY, &height);
	MultiCamChannelGetParameterInt(m_channel, EC_PARAM_AcqColFmt, &euresysFormat);
	format = EuresysDriver::fromEuresysFormat(euresysFormat);
	
	ECSURFACEINFO surfaceInfo;
	surfaceInfo.StructSize = sizeof(ECSURFACEINFO);
	surfaceInfo.Type = EC_SURFACE_TYPE_PC;
	surfaceInfo.UserAllocatedMemory = 0;
	
	for(int i = 0; i < numSurfaces; i++)
	{
		Image *image = new Image(width, height, format);
		m_images.push_back(image);
		surfaceInfo.Size = image->getBufferSize();
		surfaceInfo.Pitch = image->getWidth() * image->getBytesPerPixel();
		surfaceInfo.Address = image->getBufferAddress();
		
		ECHANDLE surface = MultiCamSurfaceCreate(&surfaceInfo);
		if(surface <= 0)
		{
			LOG_ERROR("EuresysCamera::createSurfaces(): Failed to create surface (" << surface << ")");
			throw CameraException("Failed to create surface");
		}
		
		// Save the handle in the image
		image->userData = (void *) surface;

		ECSTATUS status = MultiCamChannelAddSurface(m_channel, surface);
		if(status != EC_OK)
		{
			LOG_ERROR("EuresysCamera::createSurfaces(): Failed to add surface to channel (" << status << ")");
			throw CameraException("Failed to add surface");
		}
	}
}

void EuresysCamera::registerCallbacks()
{
	LOG_TRACE("EuresysCamera::registerCallbacks()");
	// Unmask signal
	MultiCamSignalMask(EC_SIGNAL_SURFACE_AVAILABLE, 1);
	
	ECSTATUS status = MultiCamSignalRegister(EC_SIGNAL_SURFACE_AVAILABLE, camera::euresys::surfaceAvailableCallback, this);
	if(status != EC_OK)
	{
		LOG_ERROR("EuresysCamera::registerCallbacks(): Failed to register callback (" << status << ")");
		throw CameraException("Failed to register callback");
	}
	
	status = MultiCamSignalRegister(EC_SIGNAL_ASM_ERROR, camera::euresys::errorCallback, this);
	if(status != EC_OK)
	{
		LOG_ERROR("EuresysCamera::registerCallbacks(): Failed to register callback (" << status << ")");
		throw CameraException("Failed to register callback");
	}
}

void EuresysCamera::startAcquisition()
{
	LOG_TRACE("EuresysCamera::startAcquisition()");
	ECSTATUS status = MultiCamSystemAcquisitionStart();
	if(status != EC_OK)
	{
		LOG_ERROR("EuresysCamera::registerCallbacks(): Failed to start acquisition (" << status << ")");
		throw CameraException("Failed to start acquisition");
	}
}

void EuresysCamera::surfaceAvailableCallback(PECEVENTINFO eventInfo)
{
	LOG_TRACE("EuresysCamera::surfaceAvailableCallback()");
	LOG_DEBUG("EuresysCamera::surfaceAvailableCallback(): " << eventInfo->Flags);
	
	// TODO: To something cool if eventInfo->Flags & EC_ERROR_NOSIG
	// TODO: Save eventInfo->TimeCode to the image

	// Find the image
	std::vector<Image *>::const_iterator iter;
	for(iter = m_images.begin(); iter != m_images.end(); iter++)
	{
		if((*iter)->userData == (void *) eventInfo->SurfaceID)
		{
			doNewImageCallback((*iter));
			return;
		}
	}

	// No image found
	LOG_ERROR("EuresysCamera::surfaceAvailableCallback(): No image with handle " << eventInfo->SurfaceID << " found");
}

void EuresysCamera::errorCallback(PECEVENTINFO eventInfo)
{
	LOG_TRACE("EuresysCamera::errorCallback()");
	LOG_DEBUG("EuresysCamera::errorCallback(): " << eventInfo->Flags);
	
	// TODO: Fix the callback

	doErrorCallback(eventInfo->Flags, "Internet?");
}

} // namespace camera
