#pragma once
#include "WindowImpl.hpp"
#include "Event.hpp"

// The class used by the user to create a platform specific window without dealing with platform specific code

namespace hs
{

	class Window
	{
		hs::priv::WindowImpl* m_implementation;

	public:
		Window(uint32 width, uint32 height, String title, uint32 style);
		~Window();

		bool pollEvents(Event& e);
	};

}