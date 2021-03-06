#pragma once
#include "Version.h"

namespace QUtils::Drawing::SDL
{
	enum struct WindowFlags
	{
		Fullscreen = 1,
		FullscreenDesktop = 2,
		OpenGL = 4,
		Shown = 8,
		Hidden = 16,
		Borderless = 32,
		Resizable = 64,
		Minimized = 128,
		Maximized = 256,
		InputGrabbed = 512,
		InputFocus = 1024,
		MouseFocus = 2048,
		Foreign = 4096,
		AllowHighDPI = 8192,
		MouseCapture = 16384,
		#if SDL_VERSION_MIN(2, 0, 5)
		AlwaysOnTop = 32768,
		SkipTaskbar = 65536,
		Utility = 131072,
		Tooltip = 262144,
		PopupMenu = 524288
		#endif
	};
	
	inline WindowFlags operator|(WindowFlags a, WindowFlags b)
	{
		return static_cast<WindowFlags>(static_cast<int>(a) | static_cast<int>(b));
	}
	
	inline WindowFlags operator&(WindowFlags a, WindowFlags b)
	{
		return static_cast<WindowFlags>(static_cast<int>(a) & static_cast<int>(b));
	}
	
	unsigned int SDL_RawWindowFlags(WindowFlags);
}