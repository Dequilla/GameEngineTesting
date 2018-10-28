#include "WindowHandle.hpp"

hs::WindowHandle::WindowHandle(HWND handle)
{
	m_windowHandle = handle;
}

HWND hs::WindowHandle::get()
{
	return m_windowHandle;
}
