#include <QUtils/Drawing/SDL/WindowFlags.h>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	unsigned int SDL_RawWindowFlags(WindowFlags flags)
	{
		unsigned int rFlags = 0;
		
		if ((flags & Fullscreen) > 0)
		{
			rFlags |= SDL_WINDOW_FULLSCREEN;
		}
		
		if ((flags & FullscreenDesktop) > 0)
		{
			rFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		
		if ((flags & OpenGL) > 0)
		{
			rFlags |= SDL_WINDOW_OPENGL;
		}
		
		if ((flags & Shown) > 0)
		{
			rFlags |= SDL_WINDOW_SHOWN;
		}
		
		if ((flags & Hidden) > 0)
		{
			rFlags |= SDL_WINDOW_HIDDEN;
		}
		
		if ((flags & Borderless) > 0)
		{
			rFlags |= SDL_WINDOW_BORDERLESS;
		}
		
		if ((flags & Resizable) > 0)
		{
			rFlags |= SDL_WINDOW_RESIZABLE;
		}
		
		if ((flags & Minimized) > 0)
		{
			rFlags |= SDL_WINDOW_MINIMIZED;
		}
		
		if ((flags & Maximized) > 0)
		{
			rFlags |= SDL_WINDOW_MAXIMIZED;
		}
		
		if ((flags & InputGrabbed) > 0)
		{
			rFlags |= SDL_WINDOW_INPUT_GRABBED;
		}
		
		if ((flags & InputFocus) > 0)
		{
			rFlags |= SDL_WINDOW_INPUT_FOCUS;
		}
		
		if ((flags & MouseFocus) > 0)
		{
			rFlags |= SDL_WINDOW_MOUSE_FOCUS;
		}
		
		if ((flags & Foreign) > 0)
		{
			rFlags |= SDL_WINDOW_FOREIGN;
		}
		
		if ((flags & AllowHighDPI) > 0)
		{
			rFlags |= SDL_WINDOW_ALLOW_HIGHDPI;
		}
		
		if ((flags & MouseCapture) > 0)
		{
			rFlags |= SDL_WINDOW_MOUSE_CAPTURE;
		}
		
		#ifdef SDL_WINDOW_ALWAYS_ON_TOP
		if ((flags & AlwaysOnTop) > 0)
		{
			rFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
		}
		#endif
		
		#ifdef SDL_WINDOW_SKIP_TASKBAR
		if ((flags & SkipTaskbar) > 0)
		{
			rFlags |= SDL_WINDOW_SKIP_TASKBAR;
		#endif
		
		#ifdef SDL_WINDOW_UTILITY
		if ((flags & Utility) > 0)
		{
			rFlags |= SDL_WINDOW_UTILITY;
		}
		#endif
		
		#ifdef SDL_WINDOW_TOOLTIP
		if ((flags & Tooltip) > 0)
		{
			rFlags |= SDL_WINDOW_TOOLTIP;
		}
		#endif
		
		#ifdef SDL_WINDOW_POPUP_MENU
		if ((flags & PopupMenu) > 0)
		{
			rFlags |= SDL_WINDOW_POPUP_MENU;
		}
		#endif
		
		
		return rFlags;
	}
}