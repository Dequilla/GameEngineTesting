#pragma once
#include "WindowImpl.hpp"
#include "Event.hpp"

namespace hs
{

	class HILLSIDE_API Window
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

		void setPosition(uint32 x, uint32 y);
		void setSize(uint32 width, uint32 height);
		void setTitle(String title);

		uint32 getWidth();
		uint32 getHeight();
		int32 getPosX();
		int32 getPosY();
	};

}