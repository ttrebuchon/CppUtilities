#pragma once

#include "../Event.h"

struct SDL_TextEditingEvent;

namespace QUtils::Drawing::SDL
{
	struct TextEditingEvent : public Event
	{
		unsigned int windowID;
		char text[32];
		int start;
		int length;
		
		
		TextEditingEvent(const SDL_TextEditingEvent*);
		TextEditingEvent(const SDL_TextEditingEvent&);
	};
}