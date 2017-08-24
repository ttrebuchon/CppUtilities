#pragma once

namespace QUtils::Drawing::SDL
{
	enum struct WindowEventType
	{
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
		#ifdef SDL_2_0_5
		TakeFocus,
		HitTest,
		#endif
	};
	
	int SDL_RawWindowEventType(WindowEventType);
	WindowEventType SDL_EnumWindowEventType(int);
	
	
}