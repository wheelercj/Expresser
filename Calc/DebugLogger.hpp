#pragma once
#include <fstream>
#include <string.h>

#define DEBUG_LEVEL 0

#if DEBUG_LEVEL == 0
	#define CLEAR_LOG(); ;
	#define LOG(message) message
#elif DEBUG_LEVEL == 1
	#define CLEAR_LOG(); clearDebugLog();
	#define LOG(message) log_error(__LINE__, __FILENAME__, message)
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif
#undef DEBUG_LEVEL

inline std::string log_error(int line, const char* file_name, const std::string& message)
{
	std::ofstream log_file("debug_log.txt", std::ios::app);
	log_file << "\n- " << __TIME__ << " \"" << message << "\" from line " << line << " in file " << file_name;
	log_file.close();
	return message;
}

inline void clear_debug_log()
{
	std::ofstream log_file("debug_log.txt", std::ios::trunc);
	log_file.close();
}
