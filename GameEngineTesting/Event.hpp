#pragma once

namespace hs
{

	struct Event
	{
	public:
		struct KeyEvent
		{

		};

		struct MouseMoveEvent
		{
		
		};

		enum EventType
		{
			Close,			// Window requested to close
			KeyPressed,		// A keyboard key was pressed
			KeyReleased,	// A keyboard key was released
			MouseMoved,		// The mouse was moved

			Count			// Keep last -- Number of available event types
		};
		EventType type;

		union
		{
			KeyEvent key;
			MouseMoveEvent mouseMove;
		};
	};

}