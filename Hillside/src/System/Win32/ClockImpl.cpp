#include "ClockImpl.hpp"
#include <Windows.h>

hs::Time hs::priv::ClockImpl::getCurrentTime()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
}
