#include <QUtils/Drawing/SDL/WindowEventType.h>
#include "IfSDL.h"
#include <map>


namespace QUtils::Drawing::SDL
{
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
		#ifdef SDL_2_0_5
		DEFTYPE(TakeFocus, TAKE_FOCUS),
		DEFTYPE(HitTest, HIT_TEST),
		#endif
	};
	
	static std::map<SDL_WindowEventID, WindowEventType> revTypes = Helpers::reverseMap(types);
	
	
	
	int SDL_RawWindowEventType(WindowEventType access)
	{
		return types.at(access);
	}
	
	WindowEventType SDL_EnumWindowEventType(int access)
	{
		return revTypes.at((SDL_WindowEventID)access);
	}
}