#include "WindowImpl.hpp"

#ifdef HILLSIDE_OS_WINDOWS
	#include "Win32Window.hpp"
	typedef hs::priv::Win32Window WindowType;
#endif

hs::priv::WindowImpl* hs::priv::WindowImpl::create(uint32 width, uint32 height, String title, uint32 style)
{
	return new WindowType(width, height, title, style);
}

hs::priv::WindowImpl::~WindowImpl()
{
	// Nothing needed to be done
}

bool hs::priv::WindowImpl::popEvent(Event& e)
{
	if (m_events.empty())
	{
		// Check for new events
		processEvents(); // Runs WndProc etc
	}

	if (!m_events.empty())
	{
		e = m_events.front();
		m_events.pop();

		return true; // Had events
	}

	return false; // Didn't have events
}

void hs::priv::WindowImpl::pushEvent(const Event& e)
{
	m_events.push(e);
}
