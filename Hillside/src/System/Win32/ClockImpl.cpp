#include "ClockImpl.hpp"
#include <Windows.h>

hs::Time hs::priv::ClockImpl::getCurrentTime()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	double freq = static_cast<double>(frequency.QuadPart) / 1000000.0;
	int64 microseconds = static_cast<int64>((static_cast<double>(time.QuadPart) / freq));

	return hs::Time(microseconds);
}
