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
	((EuresysCamera *) context)->SurfaceAvailableCallback(eventInfo);
}

void WINAPI errorCallback(PVOID context, PECEVENTINFO eventInfo)
{
	((EuresysCamera *) context)->ErrorCallback(eventInfo);
}

} // namespace euresys

EuresysCamera::EuresysCamera(const std::string &identifier) {
	EuresysCamera(identifier, -1, -1, Image::FORMAT_RGB24, 1);
}

EuresysCamera::EuresysCamera(const std::string &identifier, int width, int height, Image::Format format, int numSurfaces)
{
	initialize(identifier);
	
	setParameters(width, height, format);
	
	createSurfaces(numSurfaces);
	
	startAcquisition();
}

EuresysCamera::~EuresysCamera()
{
	// TODO: Deallocate image buffers
}

void EuresysCamera::start()
{
	MultiCamChannelSetParameterInt(_channel, EC_PARAM_RepeatGrabCount, -1 );
	MultiCamChannelSetParameterInt(_channel, EC_PARAM_ChannelState, CHANNEL_STATE_ACTIVE);
	_running = true;
}

void EuresysCamera::stop()
{
	MultiCamChannelSetParameterInt(_channel, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);
	_running = false;
}

bool EuresysCamera::isRunning()
{
	return _running;
}

Image* EuresysCamera::getLastImage()
{
	// TODO: Return last image
	return NULL;
}

void EuresysCamera::initialize(const std::string &identifier)
{
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
	
	_channel = MultiCamChannelCreate(NULL, asmIdentification.c_str(), sourceId);
	if(_channel <= 0) {
		LOG_ERROR("EuresysCamera::initialize(): Failed to create channel " << asmIdentification << ", " << sourceId << " (" << _channel << ")");
		throw CameraException("Failed to create camera");
	}
}

void EuresysCamera::setParameters(int width, int height, Image::Format format)
{
	MultiCamChannelSetParameterInt(_channel, EC_PARAM_TriggerMask, TRIGGERMASK_NONE);
	MultiCamChannelSetParameterInt(_channel, EC_PARAM_AssemblerMask, ASMMASK__DELAY);
	MultiCamChannelSetParameterInt(_channel, EC_PARAM_Standard, EC_STANDARD_PAL);
	MultiCamChannelSetParameterInt(_channel, EC_PARAM_FieldMode, 2);
	MultiCamChannelSetParameterInt(_channel, EC_PARAM_AcqColFmt, EuresysDriver::toEuresysFormat(format));
	//MultiCamChannelSetParameterInt(_channel, EC_PARAM_ImageSizeX, width);
	//MultiCamChannelSetParameterInt(_channel, EC_PARAM_ImageSizeY, height);
}

void EuresysCamera::createSurfaces(int numSurfaces) {
	int width;
	int height;
	int euresysFormat;
	Image::Format format;
	
	// Get parameters
	MultiCamChannelGetParameterInt(_channel, EC_PARAM_ImageSizeX, &width);
	MultiCamChannelGetParameterInt(_channel, EC_PARAM_ImageSizeY, &height);
	MultiCamChannelGetParameterInt(_channel, EC_PARAM_AcqColFmt, &euresysFormat);
	format = EuresysDriver::fromEuresysFormat(euresysFormat);
	
	ECSURFACEINFO surfaceInfo;
	surfaceInfo.StructSize = sizeof(ECSURFACEINFO);
	surfaceInfo.Type = EC_SURFACE_TYPE_PC;
	surfaceInfo.UserAllocatedMemory = 0;
	
	for(int i = 0; i < numSurfaces; i++)
	{
		Image *image = new Image(width, height, format);
		surfaceInfo.Size = image->getBufferSize();
		surfaceInfo.Pitch = image->getWidth() * image->getBytesPerPixel();
		surfaceInfo.Address = image->getBufferAddress();
		
		ECHANDLE surface = MultiCamSurfaceCreate(&surfaceInfo);
		if(surface <= 0)
		{
			LOG_ERROR("EuresysCamera::createSurfaces(): Failed to create surface (" << surface << ")");
			throw CameraException("Failed to create surface");
		}
		
		ECSTATUS status = MultiCamChannelAddSurface(_channel, surface);
		if(status != EC_OK)
		{
			LOG_ERROR("EuresysCamera::createSurfaces(): Failed to add surface to channel (" << status << ")");
			throw CameraException("Failed to add surface");
		}
	}
}

void EuresysCamera::registerCallbacks()
{
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
	ECSTATUS status = MultiCamSystemAcquisitionStart();
	if(status != EC_OK)
	{
		LOG_ERROR("EuresysCamera::registerCallbacks(): Failed to start acquisition (" << status << ")");
		throw CameraException("Failed to start acquisition");
	}
}

void EuresysCamera::SurfaceAvailableCallback(PECEVENTINFO eventInfo)
{
	/*
	if (!m_bOnGoingRefresh)
	{
		for(int i=0;i<3;i++){
			if(pInfo->SurfaceID == (UINT32)m_hSurface[i]){
				ImgOper(IMG_INVERT, (EROIBW8*) m_pImage[i], (EROIBW8*) m_pTreatmentImage);
				i=3;
			}
		}
		RECT RectImageSize = { 0, 0, m_ImageSizeX-1 , m_ImageSizeY-1 };
		m_bOnGoingRefresh = TRUE;
		InvalidateRect(&RectImageSize, FALSE);
	}
	char pTexte [256] ;

	if ( pInfo->Flags & EC_ERROR_NOSIG )
	{
		m_bLive = FALSE ;

		sprintf(pTexte, "Event %d, Channel %03lx, Surface %08lx, Flags %08lx, TimeCode %03lx, Reserved %08lx.\n"
				, pInfo->EventID 
				, pInfo->ChannelID 
				, pInfo->SurfaceID 
				, pInfo->Flags 
				, pInfo->TimeCode 
				, pInfo->Reserved ) ;

		MessageBox(pTexte, "Surface State Processing", MB_SYSTEMMODAL | MB_ICONHAND | MB_OK);
	}
	*/
}
void EuresysCamera::ErrorCallback(PECEVENTINFO eventInfo)
{
	/*
	char pTexte [256] ;

	if ( pInfo->Flags & EC_ERROR_NOSIG )
	{
		sprintf(pTexte, "Event %d, Channel %03lx, Surface %08lx, Flags %08lx, TimeCode %03lx, Reserved %08lx.\n"
				, pInfo->EventID 
				, pInfo->ChannelID 
				, pInfo->SurfaceID 
				, pInfo->Flags 
				, pInfo->TimeCode 
				, pInfo->Reserved ) ;

		m_bLive = FALSE ;

		MessageBox(pTexte, "Error Signal Processing", MB_SYSTEMMODAL | MB_ICONHAND | MB_OK);
	}
	*/
}

} // namespace camera
