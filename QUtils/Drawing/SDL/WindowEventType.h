#pragma once
#include "Version.h"

namespace QUtils::Drawing::SDL
{
	enum struct WindowEventType : unsigned char
	{
		None = 0,
		Shown,
		Hidden,
		Exposed,
		Moved,
		Resized,
		SizeChanged,
		Minimized,
		Maximized,
		Restored,
		Enter,
		Leave,
		FocusGained,
		FocusLost,
		Close,
		#if SDL_VERSION_MIN(2, 0, 5)
		TakeFocus,
		HitTest,
		#endif
	};
	
	int SDL_RawWindowEventType(WindowEventType);
	WindowEventType SDL_EnumWindowEventType(int);
	
	
}