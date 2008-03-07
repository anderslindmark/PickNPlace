#include <iostream>
#include <string>
#include "CameraManager.h"
#include "DummyDriver.h"
#include "EuresysDriver.h"
#include "Camera.h"
#include "CameraException.h"
#include "BMP.h"
#include "log.h"

int main()
{
	std::cout << "Hello!" << std::endl;
	
	camera::CameraManager cm;
	
	camera::DummyDriver dd;
	dd.setImageSize(500, 500);
	cm.addDriver(&dd);
	
	try
	{
		camera::EuresysDriver ed;
		cm.addDriver(&ed);
	}
	catch(camera::CameraException &e)
	{
		LOG_ERROR("Failed to add Euresys driver (" << e.what() << ")");
	}
	
	camera::CameraIdentifierList identifiers = cm.getCameraIdentifiers();
	std::cout << "Available cameras:" << std::endl;
	int i = 0;
	for(camera::CameraIdentifierList::const_iterator iter = identifiers.begin(); iter != identifiers.end(); iter++)
	{
		std::cout << "  #" << i << ": " << (*iter).encode() << std::endl;
		i++;
	}
	
	std::cout << "Creating camera #0..." << std::endl;
	camera::Camera *c = cm.createCamera(identifiers.at(0));
	c->start();
	camera::util::saveBMP("test.bmp", c->getLastImage());
	delete c;
}
