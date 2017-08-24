#pragma once

#include "../Event.h"

struct SDL_UserEvent;

namespace QUtils::Drawing::SDL
{
	struct UserEvent : public Event
	{
		unsigned int windowID;
		int code;
		void* data1;
		void* data2;
		
		
		UserEvent(const SDL_UserEvent*);
		UserEvent(const SDL_UserEvent&);
	};
}