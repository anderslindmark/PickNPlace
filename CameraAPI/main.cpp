#include <iostream>
#include "CameraManager.h"
#include "EuresysDriver.h"

int main()
{
	std::cout << "Hello!" << std::endl;
	
	camera::CameraManager cm;
	std::cout << "Num cameras = " << cm.getCameraCount() << std::endl;
	
	cm.addDriver(new camera::EuresysDriver());
}
