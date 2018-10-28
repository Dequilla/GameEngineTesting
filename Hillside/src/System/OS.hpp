#pragma once

#ifdef _WIN32
#define HILLSIDE_OS_WINDOWS
#elif __linux__
#define HILLSIDE_OS_LINUX
#endif

#ifdef HILLSIDE_OS_WINDOWS
	#ifdef HILLSIDE_EXPORTS 
		#define HILLSIDE_API __declspec(dllexport)
	#else
		#define HILLSIDE_API __declspec(dllimport)
	#endif
#endif