#ifndef __EURESYSDRIVER_H__
#define __EURESYSDRIVER_H__

#include "Driver.h"

namespace camera {

class EuresysDriver : public Driver
{
	public:
		static const int MAX_CAMERAS_PER_BOARD = 16;
		
		EuresysDriver();
		~EuresysDriver();
		
		std::string getName() { return "Euresys MultiCam for Picolo"; }
		int getVersionMajor() { return 0; }
		int getVersionMinor() { return 1; }
		std::string getIdentifier() { return "multicamforpicolo"; }
		
		std::vector<CameraIdentifier> getCameraIdentifiers();
	private:
		
};

} // namespace camera

#endif
