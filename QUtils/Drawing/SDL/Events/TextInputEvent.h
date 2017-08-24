#pragma once

#include "../Event.h"

struct SDL_TextInputEvent;

namespace QUtils::Drawing::SDL
{
	struct TextInputEvent : public Event
	{
		unsigned int windowID;
		char text[32];
		
		
		
		
		TextInputEvent(const SDL_TextInputEvent*);
		TextInputEvent(const SDL_TextInputEvent&);
	};
}