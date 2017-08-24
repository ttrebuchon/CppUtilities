#pragma once

#include "../Event.h"
#include <string>

struct SDL_DropEvent;

namespace QUtils::Drawing::SDL
{
	struct DropEvent : public Event
	{
		std::string file;
		#if SDL_VERSION_MIN(2,0,5)
		unsigned int windowID;
		#endif
		
		
		
		
		DropEvent(const SDL_DropEvent*);
		DropEvent(const SDL_DropEvent&);
	};
}