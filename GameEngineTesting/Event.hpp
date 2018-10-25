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

		enum MouseButton
		{
			LEFT,
			MIDDLE,
			RIGHT,
			EXTRA1,
			EXTRA2
		};

		struct MouseButtonEvent
		{
			MouseButton code;
			// ctrl, alt, sys pressed etc
		};

		enum EventType
		{
			Close,			// Window requested to close
			KeyPressed,		// A keyboard key was pressed
			KeyReleased,	// A keyboard key was released
			MouseMoved,		// The mouse was moved
			MousePressed,	// A mouse button was pressed
			MouseReleased,	// A mouse button was released
			Resized,		// A resize event happend

			Count			// Keep last >> Number of available event types
		} type;

		union
		{
			ResizeEvent resize;
			KeyEvent key;

			struct Mouse
			{
				MouseMoveEvent move;
				MouseButtonEvent button;
			} mouse;
		};

		Event() {};

	};

}