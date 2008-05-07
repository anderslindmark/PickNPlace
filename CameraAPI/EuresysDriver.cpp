#include "EuresysDriver.h"
#include "euresys/Include/MultiCam32.h"
#include "CameraException.h"
#include "EuresysCamera.h"
#include <sstream>
#include "log.h"

namespace camera 
{

EuresysDriver::EuresysDriver()
{
	LOG_TRACE("EuresysDriver::EuresysDriver()");
	
	LOG_TRACE("EuresysDriver::EuresysDriver(): Initializing driver");
	ECSTATUS status = MultiCamSystemInitialize();
	if(status != EC_OK)
	{
		LOG_ERROR("EuresysDriver::EuresysDriver(): Failed to initialize driver");
		throw CameraException("Failed to initialize driver");
	}
	
	LOG_TRACE("EuresysDriver::EuresysDriver(): Get board info");
	ECBOARDINFO boardList[MAX_BOARD_COUNT];
	unsigned int boardCount;
	status = MultiCamSystemGetBoardInfo(boardList, MAX_BOARD_COUNT, &boardCount);
	if(status != EC_OK)
	{
		LOG_ERROR("EuresysDriver::EuresysDriver(): Failed to get board info");
		throw CameraException("Failed to get board info");
	}
	
	LOG_TRACE("EuresysDriver::EuresysDriver(): Found " << boardCount << " boards");
	for(unsigned int i = 0; i < boardCount; i++)
	{
		LOG_TRACE("EuresysDriver::EuresysDriver():   #" << i << ": name = " << boardList[i].InternalName << ", sn = " << boardList[i].SerialNumber << ", pci = " << boardList[i].PciPosition << ", firmware = " << boardList[i].FirmwareRevision);
		for(unsigned int j = 0; j < boardList[i].SourceCount; j++)
		{
			// Possible camera identifiers:
			//   #<BoardID> (position in the boardList array), "#0"
			//   @<BoardType>_<SerialNumber>, "@PICOLO_000731"
			//   &<InternalName>, "&MyPicoloPro"
			//   %<PciPosition>, "%9"
			std::stringstream ss;
			ss << "#" << i << "." << j;
			m_identifiers.push_back(ss.str());
			
			LOG_TRACE("EuresysDriver::EuresysDriver():    Added  identifier " << ss.str());
		}
	}
}

EuresysDriver::~EuresysDriver()
{
	LOG_TRACE("EuresysDriver::~EuresysDriver()");
}

void EuresysDriver::updateCameraIdentifiers()
{
	LOG_TRACE("EuresysDriver::~updateCameraIdentifiers()");
}

int EuresysDriver::getCameraIdentifierCount()
{
	LOG_TRACE("EuresysDriver::getIdentifierCount()");
	return m_identifiers.size();
}

std::string EuresysDriver::getCameraIdentifier(int index)
{
	LOG_TRACE("EuresysDriver::getIdentifier()");
	return m_identifiers.at(index);
}

Camera *EuresysDriver::createCamera(const std::string &identifier)
{
	LOG_TRACE("EuresysDriver::createCamera()");
	return new EuresysCamera(identifier);
}

Image::Format EuresysDriver::fromEuresysFormat(int format)
{
	// We have been clever and used the same enum order
	return (Image::Format) format;
}

int EuresysDriver::toEuresysFormat(Image::Format format)
{
	// We have been clever and used the same enum order
	return (int) format;
}

} // namespace camera
