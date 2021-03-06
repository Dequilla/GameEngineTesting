#pragma once
#include <Windows.h>
#include <unordered_map>

#include "../WindowImpl.hpp"
#include "../Keyboard.hpp"

namespace hs
{
	namespace priv
	{
		class HILLSIDE_API Win32Window : public WindowImpl
		{
		public:
			const wchar_t* className = L"Hillside_Window";

			Win32Window(uint32 width, uint32 height, String title, uint32 style);
			~Win32Window();

		public:
			void setPosition(uint32 x, uint32 y);
			void setSize(uint32 width, uint32 height);
			void setTitle(String title);

			uint32 getWidth();
			uint32 getHeight();
			int32 getPosX();
			int32 getPosY();

			WindowHandle getSystemHandle();

		protected:
			void processEvents();

		private:
			HINSTANCE m_systemHandle;
			HWND m_windowHandle;

			void switchToFullscreen(uint32 width, uint32 height);

			static std::unordered_map<HWND, Win32Window*> m_windowsCreated;
			static Win32Window* getWindowFromHandle(HWND winHandle);

			static bool m_windowClassRegistered;
			bool registerWindowClass();

			void processEvent(UINT msg, WPARAM wParam, LPARAM lParam);

			static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

			Keyboard::Key translateVirtualKeycode(WPARAM key, LPARAM lParam);
		};

		
	}

}