#pragma once

#include "../Event.h"

struct SDL_SysWMEvent;
struct SDL_SysWMmsg;

namespace QUtils::Drawing::SDL
{
	struct SysWMEvent : public Event
	{
		SDL_SysWMmsg* msg;
		
		
		
		
		
		SysWMEvent(const SDL_SysWMEvent*);
		SysWMEvent(const SDL_SysWMEvent&);
	};
}