#pragma once
#include "../Config.hpp"

#ifdef HILLSIDE_OS_WINDOWS
#include <Windows.h>
#elif HILLSIDE_OS_LINUX

#endif

namespace hs
{

	class HILLSIDE_API WindowHandle
	{
	#ifdef HILLSIDE_OS_WINDOWS
			HWND m_windowHandle;
	#elif HILLSIDE_OS_LINUX

	#endif

	public:
	#ifdef HILLSIDE_OS_WINDOWS
			WindowHandle(HWND handle);
			HWND get();
	#elif HILLSIDE_OS_LINUX

	#endif
	};

}