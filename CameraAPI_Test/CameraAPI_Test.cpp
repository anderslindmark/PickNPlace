#include <iostream>
#include <string>
#include <sstream>
#include "CameraManager.h"
#include "DummyDriver.h"
#include "EuresysDriver.h"
#include "Camera.h"
#include "CameraListener.h"
#include "CameraException.h"
#include "BMP.h"
#include "Image.h"
#include "log.h"

class MyListener : public camera::CameraListener
{
	public:
		MyListener() : image(NULL) {}

		void cameraNewImage(camera::Camera *camera, camera::Image *image)
		{
			std::cout << "New image!" << std::endl;
			this->image = image;
		}

		void cameraError(camera::Camera *camera, int errorCode, const std::string &errorMessage)
		{
			std::cout << "Error! (#" << errorCode << ": " << errorMessage << ")" << std::endl;
		}
		
		camera::Image *image;
};


int main()
{
	std::cout << "Hello!" << std::endl;
	
	camera::CameraManager *cm = camera::CameraManager::getInstance();
	
	camera::DummyDriver dd;
	dd.setImageSize(500, 500);
	cm->addDriver(&dd);
	
	camera::EuresysDriver *ed;
	try
	{
		ed = new camera::EuresysDriver();
		cm->addDriver(ed);
	}
	catch(camera::CameraException &e)
	{
		std::cout << "Failed to add Euresys driver (" << e.what() << ")" << std::endl;
	}
	
	camera::Camera *c = NULL;
	MyListener cameraListener;
	std::string command;
	while(1)
	{
		std::cout << "Command: ";
		std::cin >> command;
		if(command == "exit")
		{
			break;
		}
		else if(command == "help")
		{
			std::cout << "Available commands:" << std::endl;
			std::cout << "    exit:                       Exit the program" << std::endl;
			std::cout << "    help:                       Show this help text" << std::endl;
			std::cout << "    camera <driver> <camera>:   Change the active camera" << std::endl;
			std::cout << "    start:                      Start the active camera" << std::endl;
			std::cout << "    stop:                       Stop the active camera" << std::endl;
			std::cout << "    save:                       Save the last image from the active camera" << std::endl;
			std::cout << std::endl;
			std::cout << "    Available cameras:" << std::endl;
			
			int driverCount = cm->getDriverCount();
			for(int i = 0; i < driverCount; i++)
			{
				camera::Driver *d = cm->getDriver(i);
				int identifierCount = d->getCameraIdentifierCount();
				for(int j = 0; j < identifierCount; j++)
				{
					std::cout << "        " << d->getIdentifier() << " " << d->getCameraIdentifier(j) << std::endl;
				}
			}
		}
		else if(command.substr(0, 6) == "camera")
		{
			if(c != NULL)
			{
				delete c;
				c = NULL;
			}

			try
			{
				std::string driverIdentifier, cameraIdentifier;
				std::cin >> driverIdentifier;
				std::cin >> cameraIdentifier;
				c = cm->createCamera(driverIdentifier, cameraIdentifier);
				c->setListener(&cameraListener);
			}
			catch(camera::CameraException &e)
			{
				std::cout << "Camera exception: " << e.what() << std::endl;
			}
			catch(...)
			{
				std::cout << "Unknown exception" << std::endl;
			}
		}
		else if(command == "start")
		{
			if(c == NULL)
			{
				std::cout << "No camera active" << std::endl;
			}
			else
			{
				c->start();
			}
		}
		else if(command == "stop")
		{
			if(c == NULL)
			{
				std::cout << "No camera active" << std::endl;
			}
			else
			{
				c->stop();
			}
		}
		else if(command == "save")
		{
			try
			{
				camera::util::saveBMP("test.bmp", cameraListener.image);
			}
			catch(std::runtime_error &e)
			{
				std::cout << "Runtime error: " << e.what() << std::endl;
			} catch(...)
			{
				std::cout << "Unknown exception" << std::endl;
			}
		}
		else
		{
			std::cout << "Unknown command. Try 'help'" << std::endl;
		}
	}
	
	delete ed;
	delete c;

	return 0;
}
