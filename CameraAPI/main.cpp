#include <iostream>
#include "CameraManager.h"
#include "DummyDriver.h"

int main()
{
	std::cout << "Hello!" << std::endl;
	
	camera::CameraManager cm;
	cm.addDriver(new camera::driver::DummyDriver());
	camera::CameraIdentifierList identifiers = cm.getCameraIdentifiers();
	
	std::cout << "Num cameras = " << identifiers.size() << std::endl;
}
