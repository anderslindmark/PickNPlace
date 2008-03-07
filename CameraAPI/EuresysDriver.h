#ifndef __EURESYSDRIVER_H__
#define __EURESYSDRIVER_H__

#include "Driver.h"
#include "Image.h"

namespace camera 
{

class EuresysDriver : public Driver
{
	public:
		static const int MAX_BOARD_COUNT = 8;
		
		EuresysDriver();
		~EuresysDriver();
		
		std::string getName() { return "Euresys MultiCam for Picolo"; }
		int getVersionMajor() { return 0; }
		int getVersionMinor() { return 1; }
		std::string getIdentifier() { return "multicamforpicolo"; }
		
		CameraIdentifierList getCameraIdentifiers();
		Camera *createCamera(CameraIdentifier identifier);
		
		static Image::Format fromEuresysFormat(int format);
		static int toEuresysFormat(Image::Format format);
	private:
		std::vector<CameraIdentifier> identifiers;
};

} // namespace camera

#endif
