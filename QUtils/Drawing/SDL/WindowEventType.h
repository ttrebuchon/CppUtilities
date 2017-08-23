#pragma once

namespace QUtils::Drawing::SDL
{
	enum WindowEventType
	{
		WindowHidden,
		WindowExposed,
		WindowMoved,
		WindowResized,
		WindowSizeChanged,
		WindowMinimized,
		WindowMaximized,
		WindowRestored,
		WindowEnter,
		WindowLeave,
		WindowFocusGained,
		WindowFocusLost,
		WindowClose,
		#ifdef SDL_2_0_5
		WindowTakeFocus,
		WindowHitTest,
		#endif
	};
	
	int SDL_RawWindowEventType(WindowEventType);
	WindowEventType SDL_EnumWindowEventType(int);
	
	
}