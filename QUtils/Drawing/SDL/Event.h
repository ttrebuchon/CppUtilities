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
		Event(int type) : type(SDL_EnumEventType(type))
		{}
		const EventType type;
		
		static Event* pollEvent();
		static bool pollEvent(SDL_Event*);
	};
}