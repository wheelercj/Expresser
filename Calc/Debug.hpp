#pragma once
#include <fstream>
#include <string.h>

#define DEBUG_LEVEL 0

#if DEBUG_LEVEL == 0
	#define LOG(message); ;
#elif DEBUG_LEVEL == 1
	#define LOG(message); logError(__LINE__, __FILENAME__, message);
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif
#undef DEBUG_LEVEL

void logError(int line, const char* fileName, const std::string& message)
{
	std::ofstream logFile("debug_log.txt", std::ios::app);
	logFile << "\n- " << __TIME__ << " \"" << message << "\" from line " << line << " in file " << fileName;
	logFile.close();
}
