#pragma once

namespace hs
{

	struct Event
	{
	public:
		struct ResizeEvent
		{
			bool isBeingResized = false;
			
			uint32 width = 0;
			uint32 height = 0; 
		};

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
			Resized,		// A resize event happend

			Count			// Keep last -- Number of available event types
		};
		EventType type;

		union
		{
			ResizeEvent resize;
			KeyEvent key;
			MouseMoveEvent mouseMove;
		};

		Event() {};
	};

}