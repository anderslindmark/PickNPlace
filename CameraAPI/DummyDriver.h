#ifndef __DUMMYDRIVER_H__
#define __DUMMYDRIVER_H__

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
		
		void updateCameraIdentifiers();
		int getCameraIdentifierCount();
		std::string getCameraIdentifier(int index);
		Camera *createCamera(const std::string &identifier);
		
		///
		/// \brief Set the size of the images the DummyCamera should produce.
		/// This has to be called before creating the DummyCamera
		///
		void setImageSize(int width, int height);
		
	private:
		int m_width;
		int m_height;
};

} // namespace camera

#endif // __DUMMYDRIVER_H__

