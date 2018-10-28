#pragma once

namespace hs
{

	struct HILLSIDE_API Event
	{
	public:
		struct SizeEvent
		{
			uint32 width;
			uint32 height;
		};

		struct KeyEvent
		{
		};

		struct MouseMoveEvent
		{
			int32 x;
			int32 y;
		};

		struct MouseWheelEvent
		{
			int32 x;
			int32 y;
			float delta;
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
			int32 x;
			int32 y;
		};

		enum EventType
		{
			Close,			// Window requested to close
			KeyPressed,		// A keyboard key was pressed
			KeyReleased,	// A keyboard key was released
			MouseMoved,		// The mouse was moved
			MouseWheel,		// Mouse wheel was rotated/moved
			MousePressed,	// A mouse button was pressed
			MouseReleased,	// A mouse button was released
			Resized,		// A resize event happend

			Count			// Keep last >> Number of available event types
		} type;

		union
		{
			SizeEvent size;
			KeyEvent key;
			MouseMoveEvent mouseMove;
			MouseWheelEvent mouseWheel;
			MouseButtonEvent mouseButton;
		};

		Event() {};

	};

}