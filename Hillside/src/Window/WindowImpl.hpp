#pragma once
#include <queue>

#include "../System/NonCopyable.hpp"
#include "../System/String.hpp"
#include "../System/Types.hpp"
#include "../System/OS.hpp"

#include "WindowHandle.hpp"
#include "Event.hpp"

namespace hs
{

	namespace priv
	{

		class HILLSIDE_API WindowImpl : NonCopyable
		{
		public:
			enum Style
			{
				WINDOW_HIDE			= 0x01,
				WINDOW_SHOW			= 0x02,
				WINDOW_FULLSCREEN	= 0x04
			};

			// Don't forget to delete it!
			static WindowImpl* create(uint32 width, uint32 height, String title, uint32 style);

			virtual ~WindowImpl();

		public:
			virtual void setPosition(uint32 x, uint32 y) = 0;
			virtual void setSize(uint32 width, uint32 height) = 0;
			virtual void setTitle(String title) = 0;

			virtual WindowHandle getSystemHandle() = 0;

		public:
			bool popEvent(Event& e);
			void pushEvent(const Event& e);

		protected:
			virtual void processEvents() = 0;

			std::queue<Event> m_events;
		};

	}

}