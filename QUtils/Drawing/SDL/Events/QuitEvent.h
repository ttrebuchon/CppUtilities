#pragma once

#include "../Event.h"

struct SDL_QuitEvent;

namespace QUtils::Drawing::SDL
{
	struct QuitEvent : public Event
	{
		QuitEvent(const SDL_QuitEvent*);
		QuitEvent(const SDL_QuitEvent&);
	};
}