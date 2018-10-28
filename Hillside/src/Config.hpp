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

namespace hs
{

	typedef char byte;

	typedef char int8;
	typedef short int16;
	typedef int int32;
	typedef long long int64;

	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;

}
