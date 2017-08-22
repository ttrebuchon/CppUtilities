#pragma once
#include "EventType.h"

union SDL_Event;

namespace QUtils::Drawing::SDL
{
	class Event
	{
		private:
		
		public:
		Event(EventType type) : type(type)
		{}
		const EventType type;
		
		static Event* pollEvent();
		static bool pollEvent(SDL_Event*);
	};
}