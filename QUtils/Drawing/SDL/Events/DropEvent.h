#pragma once

#include "../Event.h"
#include <string>

struct SDL_DropEvent;

namespace QUtils::Drawing::SDL
{
	struct DropEvent : public Event
	{
		std::string file;
		unsigned int windowID;
		
		
		
		
		DropEvent(const SDL_DropEvent*);
		DropEvent(const SDL_DropEvent&);
	};
}