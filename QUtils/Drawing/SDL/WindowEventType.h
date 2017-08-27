#pragma once
#include "Version.h"

namespace QUtils::Drawing::SDL
{
	enum struct WindowEventType : unsigned char
	{
		None = 0,
		Shown = 1,
		Hidden = 2,
		Exposed = 3,
		Moved = 4,
		Resized = 5,
		SizeChanged = 6,
		Minimized = 7,
		Maximized = 8,
		Restored = 9,
		Enter = 10,
		Leave = 11,
		FocusGained = 12,
		FocusLost = 13,
		Close = 14,
		#if SDL_VERSION_MIN(2, 0, 5)
		TakeFocus = 15,
		HitTest = 16,
		#endif
	};
	
	int SDL_RawWindowEventType(WindowEventType);
	WindowEventType SDL_EnumWindowEventType(int);
	
	
}