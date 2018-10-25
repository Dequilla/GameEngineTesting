#include "Window.hpp"

hs::Window::Window(uint32 width, uint32 height, String title, uint32 style)
{
	create(width, height, title, style);
}

hs::Window::~Window()
{
	close();
}

void hs::Window::create(uint32 width, uint32 height, String title, uint32 style)
{
	// Close any previous window
	close(); 

	m_implementation = hs::priv::WindowImpl::create(width, height, title, style);
}

void hs::Window::close()
{
	delete m_implementation;
	m_implementation = nullptr;
}

bool hs::Window::isOpen()
{
	return (m_implementation != nullptr);
}

bool hs::Window::pollEvents(Event& e)
{
	if(this->m_implementation != nullptr)
		return m_implementation->popEvent(e);
	return false;
}
