#include <iostream>
#include <string>
#include <sstream>
#include "CameraManager.h"
#include "DummyDriver.h"
#include "Camera.h"
#include "CameraListener.h"
#include "CameraException.h"
#include "BarrelCorrection.h"
#include "BMP.h"
#include "Image.h"
#include "log.h"

#ifdef USE_EURESYS
	#include "EuresysDriver.h"
#endif

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
	std::cout << "Welcome to the camera API test!" << std::endl;
	
	camera::CameraManager *cameraManager = camera::CameraManager::getInstance();
	
	camera::DummyDriver dummyDriver;
	dummyDriver.setImageSize(768, 576);
	cameraManager->addDriver(&dummyDriver);
	
	int distortedRectangle[8][2] = {
		{31, 60},
		{350, 30},
		{732, 17},
		{30, 288},
		{741, 288},
		{37, 513},
		{355, 542},
		{731, 550}
	};
	camera::BarrelCorrection *barrelCorrection = new camera::BarrelCorrection(distortedRectangle);
	//barrelCorrection->setOutputSize(768, 576);
	
#ifdef USE_EURESYS
	camera::EuresysDriver *euresysDriver;
	try
	{
		euresysDriver = new camera::EuresysDriver();
		cameraManager->addDriver(euresysDriver);
	}
	catch(camera::CameraException &e)
	{
		std::cout << "Failed to add Euresys driver (" << e.what() << ")" << std::endl;
	}
#endif
	camera::Camera *camera = NULL;
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
			std::cout << "    barrel:                     Toggle barrel correction" << std::endl;
			std::cout << "    start:                      Start the active camera" << std::endl;
			std::cout << "    stop:                       Stop the active camera" << std::endl;
			std::cout << "    save:                       Save the last image from the active camera" << std::endl;
			std::cout << std::endl;
			std::cout << "    Available cameras:" << std::endl;
			
			int driverCount = cameraManager->getDriverCount();
			for(int i = 0; i < driverCount; i++)
			{
				camera::Driver *d = cameraManager->getDriver(i);
				int identifierCount = d->getCameraIdentifierCount();
				for(int j = 0; j < identifierCount; j++)
				{
					std::cout << "        " << d->getIdentifier() << " " << d->getCameraIdentifier(j) << std::endl;
				}
			}
		}
		else if(command == "camera")
		{
			if(camera != NULL)
			{
				delete camera;
				camera = NULL;
			}

			try
			{
				std::string driverIdentifier, cameraIdentifier;
				std::cin >> driverIdentifier;
				std::cin >> cameraIdentifier;
				camera = cameraManager->createCamera(driverIdentifier, cameraIdentifier);
				camera->setListener(&cameraListener);
				camera->addFilter(barrelCorrection);
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
		else if(command == "barrel")
		{
			barrelCorrection->setEnabled(!barrelCorrection->getEnabled());
			std::cout << "Barrel correction filter is " << (barrelCorrection->getEnabled() ? "enabled" : "disabled") << std::endl;
		}
		else if(command == "start")
		{
			if(camera == NULL)
			{
				std::cout << "No camera active" << std::endl;
			}
			else
			{
				camera->start();
			}
		}
		else if(command == "stop")
		{
			if(camera == NULL)
			{
				std::cout << "No camera active" << std::endl;
			}
			else
			{
				camera->stop();
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
	
#ifdef USE_EURESYS
	delete euresysDriver;
#endif
	delete camera;
	delete barrelCorrection;

	return 0;
}
