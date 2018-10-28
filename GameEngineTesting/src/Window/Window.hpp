#pragma once
#include "WindowImpl.hpp"
#include "Event.hpp"

namespace hs
{

	class Window
	{
		hs::priv::WindowImpl* m_implementation = nullptr;

	public:
		typedef hs::priv::WindowImpl::Style Style;

		Window(uint32 width, uint32 height, String title, uint32 style);
		~Window();

		void create(uint32 width, uint32 height, String title, uint32 style);

		void close();
		
		bool isOpen();

		bool pollEvents(Event& e);
	};

}