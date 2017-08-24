#pragma once
#include "../Event.h"
#include "../WindowEventType.h"

class SDL_WindowEvent;

namespace QUtils::Drawing::SDL
{
	class WindowEvent : public Event
	{
		private:
		
		public:
		unsigned int windowID;
		WindowEventType event;
		int data1;
		int data2;
		
		
		WindowEvent(const SDL_WindowEvent*);
		WindowEvent(const SDL_WindowEvent&);
	};
}