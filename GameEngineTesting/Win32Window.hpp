#pragma once
#include <Windows.h>
#include <unordered_map>

#include "WindowImpl.hpp"

namespace hs
{
	namespace priv
	{
		class Win32Window : public WindowImpl
		{
		public:
			const wchar_t* className = L"Hillside_Window";

			Win32Window(uint32 width, uint32 height, String title, uint32 style);
			~Win32Window();

		public:
			void setPosition(uint32 x, uint32 y);
			void setSize(uint32 width, uint32 height);
			void setTitle(String title);

			WindowHandle getSystemHandle();

		protected:
			void processEvents();

		private:
			HINSTANCE m_systemHandle;
			HWND m_windowHandle;

			void switchToFullscreen(uint32 width, uint32 height);

			static std::unordered_map<HWND, Win32Window*> m_windowsCreated;
			static Win32Window* getWindowFromhandle(HWND winHandle);

			bool registerWindowClass();

			void processEvent(UINT msg, WPARAM wParam, LPARAM lParam);

			static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
		};

		
	}

}