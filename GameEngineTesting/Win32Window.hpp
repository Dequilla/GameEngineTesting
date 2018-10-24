#pragma once
#include <Windows.h>
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
			void setStyle(uint32 style);
			void setVisible(bool visibile);

			WindowHandle getSystemHandle();

		protected:
			void processEvents();

		private:
			HINSTANCE m_systemHandle;
			HWND m_windowHandle;

			bool registerWindowClass();

			static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
		};

		
	}

}