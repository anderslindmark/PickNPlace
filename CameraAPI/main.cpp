#include <iostream>
#include "CameraManager.h"
#include "DummyDriver.h"
#include "Camera.h"
#include "BMP.h"

int main()
{
	std::cout << "Hello!" << std::endl;
	
	camera::CameraManager cm;
	camera::DummyDriver *dd = new camera::DummyDriver();
	dd->setImageSize(500, 500);
	cm.addDriver(dd);
	camera::CameraIdentifierList identifiers = cm.getCameraIdentifiers();
	
	std::cout << "Num cameras = " << identifiers.size() << std::endl;
	std::cout << "Creating camera..." << std::endl;
	
	camera::Camera *c = cm.createCamera(identifiers.at(0));
	c->start();
	std::cout << "Buffer size: " << c->getLastImage()->getWidth() << "x" << c->getLastImage()->getHeight() << " (" << c->getLastImage()->getBufferSize() << " bytes)" << std::endl;
	
	camera::util::saveBMP("test.bmp", c->getLastImage());
	
	delete c;
	delete dd;
}
