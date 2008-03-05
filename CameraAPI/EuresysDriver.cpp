#include "EuresysDriver.h"
#include "CameraException.h"
#include "log.h"
#include <sstream>
#include "euresys/Include/MultiCam32.h"

namespace camera {

EuresysDriver::EuresysDriver()
{
	LOG_TRACE("EuresysDriver::EuresysDriver()");
	
	LOG_DEBUG("Initializing driver");
	ECSTATUS status = MultiCamSystemInitialize();
	if(status != EC_OK)
	{
		throw CameraException("Failed to initialize driver");
	}
}

EuresysDriver::~EuresysDriver()
{
	LOG_TRACE("EuresysDriver::~EuresysDriver()");
}

std::vector<CameraIdentifier> EuresysDriver::getCameraIdentifiers() {
	LOG_TRACE("EuresysDriver::getIdentifiers()");
	
	ECBOARDINFO boardList[MAX_CAMERAS_PER_BOARD];
	unsigned int boardCount;
	ECSTATUS status = MultiCamSystemGetBoardInfo(boardList, MAX_CAMERAS_PER_BOARD, &boardCount);
	if(status != EC_OK)
	{
		throw CameraException("Failed to get board info");
	}
	
	LOG_DEBUG("Found " << boardCount << " boards:");
	std::vector<CameraIdentifier> identifiers;
	for(unsigned int i = 0; i < boardCount; i++)
	{
		LOG_DEBUG("    #" << i << ": name = " << boardList[i].InternalName << ", sn = " << boardList[i].SerialNumber << ", pci = " << boardList[i].PciPosition << ", firmware = " << boardList[i].FirmwareRevision);
		for(unsigned int j = 0; j < boardList[i].SourceCount; j++)
		{
			CameraIdentifier identifier;
			
			std::stringstream ss;
			ss << boardList[i].SerialNumber << "." << i;
			identifier.cameraIdentifier = ss.str();
			
			identifier.driverIdentifier = getIdentifier();
			
			identifiers.push_back(identifier);
			LOG_DEBUG("        Added identifier " << identifier.encode());
		}
	}
	return identifiers;
}

} // namespace camera
