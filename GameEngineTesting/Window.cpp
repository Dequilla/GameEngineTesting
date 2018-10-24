#include "Window.hpp"

hs::Window::Window(uint32 width, uint32 height, String title, uint32 style)
{
	m_implementation = hs::priv::WindowImpl::create(width, height, title, style);
}

hs::Window::~Window()
{
	delete m_implementation;
}

bool hs::Window::pollEvents(Event& e)
{
	return m_implementation->popEvent(e);
}
