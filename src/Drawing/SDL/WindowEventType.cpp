#include <QUtils/Drawing/SDL/WindowEventType.h>
#include "IfSDL.h"
#include <map>

#ifdef DEBUG
#include <iostream>
#endif


namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	namespace Helpers
	{
		std::map<SDL_WindowEventID, WindowEventType> reverseMap(const std::map<WindowEventType, SDL_WindowEventID>& map)
		{
			std::map<SDL_WindowEventID, WindowEventType> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFTYPE(x, y) { WindowEventType::x, SDL_WINDOWEVENT_##y, }
	
	static std::map<WindowEventType, SDL_WindowEventID> types = {
		DEFTYPE(None, NONE),
		DEFTYPE(Shown, SHOWN),
		DEFTYPE(Hidden, HIDDEN),
		DEFTYPE(Exposed, EXPOSED),
		DEFTYPE(Moved, MOVED),
		DEFTYPE(Resized, RESIZED),
		DEFTYPE(SizeChanged, SIZE_CHANGED),
		DEFTYPE(Minimized, MINIMIZED),
		DEFTYPE(Maximized, MAXIMIZED),
		DEFTYPE(Restored, RESTORED),
		DEFTYPE(Enter, ENTER),
		DEFTYPE(Leave, LEAVE),
		DEFTYPE(FocusGained, FOCUS_GAINED),
		DEFTYPE(FocusLost, FOCUS_LOST),
		DEFTYPE(Close, CLOSE),
		#if SDL_VERSION_MIN(2,0,5)
		DEFTYPE(TakeFocus, TAKE_FOCUS),
		DEFTYPE(HitTest, HIT_TEST),
		#endif
	};
	
	static std::map<SDL_WindowEventID, WindowEventType> revTypes = Helpers::reverseMap(types);
	
	#endif
	
	int SDL_RawWindowEventType(WindowEventType access)
	{
		#ifdef QUTILS_HAS_SDL2
		#ifdef DEBUG
		try
		{
		#endif
		return types.at(access);
		#ifdef DEBUG
		}
		catch (std::exception& ex)
		{
			std::cout << "\nCould not find WindowEventID raw equivalent for " << (int)access << "\n";
			throw;
		}
		#endif
		#else
		throw NotAvail();
		#endif
	}
	
	WindowEventType SDL_EnumWindowEventType(int access)
	{
		#ifdef QUTILS_HAS_SDL2
		#ifdef DEBUG
		try
		{
		#endif
		return revTypes.at((SDL_WindowEventID)access);
		#ifdef DEBUG
		}
		catch (std::exception& ex)
		{
			std::cout << "\nCould not find WindowEventID enum equivalent for " << (int)access << "\n";
			std::cout << SDL_WINDOWEVENT_NONE << ", " << SDL_WINDOWEVENT_SHOWN << "\n";
			throw;
		}
		#endif
		#else
		throw NotAvail();
		#endif
	}
}