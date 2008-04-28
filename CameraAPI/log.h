#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>

//#define LOGGING

#ifdef LOGGING
	//#define LOG_TRACE(message) std::clog << "[TRACE] " << __FILE__ << ":" << __LINE__ << " >> " << message << std::endl;
	#define LOG_TRACE(message) std::clog << "[TRACE] " << message << std::endl;
	#define LOG_DEBUG(message) std::clog << "[DEBUG] " << message << std::endl;
	#define LOG_MESSAGE(message) std::clog << "[MESSAGE] " << message << std::endl;
	#define LOG_ERROR(message) std::clog << "[ERROR] " << message << std::endl;
#else
	#define LOG_TRACE(message)
	#define LOG_DEBUG(message)
	#define LOG_MESSAGE(message)
	#define LOG_ERROR(message)
#endif

#endif