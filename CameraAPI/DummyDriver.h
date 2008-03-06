#ifndef __DUMMYDRIVER_H__
#define __DYMMYDRIVER_H__

#include "Driver.h"

namespace camera 
{

class DummyDriver : public Driver
{
	public:
		DummyDriver();
		~DummyDriver();
		
		std::string getName() { return "Dummy Driver"; }
		int getVersionMajor() { return 1; }
		int getVersionMinor() { return 0; }
		std::string getIdentifier() { return "dummy"; }
		
		CameraIdentifierList getCameraIdentifiers();
		Camera *createCamera(CameraIdentifier identifier);
		
		void setImageSize(int width, int height);
		
	private:
		int _width;
		int _height;
};

} // namespace camera

#endif