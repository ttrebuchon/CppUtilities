#include <QUtils/Drawing/SDL/WindowFlags.h>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	unsigned int SDL_RawWindowFlags(WindowFlags flags)
	{
		#ifdef QUTILS_HAS_SDL2
		unsigned int rFlags = 0;
		
		if ((int)(flags & WindowFlags::Fullscreen) > 0)
		{
			rFlags |= SDL_WINDOW_FULLSCREEN;
		}
		
		if ((int)(flags & WindowFlags::FullscreenDesktop) > 0)
		{
			rFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		
		if ((int)(flags & WindowFlags::OpenGL) > 0)
		{
			rFlags |= SDL_WINDOW_OPENGL;
		}
		
		if ((int)(flags & WindowFlags::Shown) > 0)
		{
			rFlags |= SDL_WINDOW_SHOWN;
		}
		
		if ((int)(flags & WindowFlags::Hidden) > 0)
		{
			rFlags |= SDL_WINDOW_HIDDEN;
		}
		
		if ((int)(flags & WindowFlags::Borderless) > 0)
		{
			rFlags |= SDL_WINDOW_BORDERLESS;
		}
		
		if ((int)(flags & WindowFlags::Resizable) > 0)
		{
			rFlags |= SDL_WINDOW_RESIZABLE;
		}
		
		if ((int)(flags & WindowFlags::Minimized) > 0)
		{
			rFlags |= SDL_WINDOW_MINIMIZED;
		}
		
		if ((int)(flags & WindowFlags::Maximized) > 0)
		{
			rFlags |= SDL_WINDOW_MAXIMIZED;
		}
		
		if ((int)(flags & WindowFlags::InputGrabbed) > 0)
		{
			rFlags |= SDL_WINDOW_INPUT_GRABBED;
		}
		
		if ((int)(flags & WindowFlags::InputFocus) > 0)
		{
			rFlags |= SDL_WINDOW_INPUT_FOCUS;
		}
		
		if ((int)(flags & WindowFlags::MouseFocus) > 0)
		{
			rFlags |= SDL_WINDOW_MOUSE_FOCUS;
		}
		
		if ((int)(flags & WindowFlags::Foreign) > 0)
		{
			rFlags |= SDL_WINDOW_FOREIGN;
		}
		
		if ((int)(flags & WindowFlags::AllowHighDPI) > 0)
		{
			rFlags |= SDL_WINDOW_ALLOW_HIGHDPI;
		}
		
		if ((int)(flags & WindowFlags::MouseCapture) > 0)
		{
			rFlags |= SDL_WINDOW_MOUSE_CAPTURE;
		}
		
		#if SDL_VERSION_MIN(2, 0, 5)
		if ((int)(flags & WindowFlags::AlwaysOnTop) > 0)
		{
			rFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
		}
		#endif
		
		#if SDL_VERSION_MIN(2, 0, 5)
		if ((int)(flags & WindowFlags::SkipTaskbar) > 0)
		{
			rFlags |= SDL_WINDOW_SKIP_TASKBAR;
		#endif
		
		#if SDL_VERSION_MIN(2, 0, 5)
		if ((int)(flags & WindowFlags::Utility) > 0)
		{
			rFlags |= SDL_WINDOW_UTILITY;
		}
		#endif
		
		#if SDL_VERSION_MIN(2, 0, 5)
		if ((int)(flags & WindowFlags::Tooltip) > 0)
		{
			rFlags |= SDL_WINDOW_TOOLTIP;
		}
		#endif
		
		#if SDL_VERSION_MIN(2, 0, 5)
		if ((int)(flags & WindowFlags::PopupMenu) > 0)
		{
			rFlags |= SDL_WINDOW_POPUP_MENU;
		}
		#endif
		
		
		return rFlags;
		
		#else
		throw NotAvail();
		#endif
	}
}