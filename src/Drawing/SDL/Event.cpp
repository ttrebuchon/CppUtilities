#include <QUtils/Drawing/SDL/Event.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include "IfSDL.h"
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils::Drawing::SDL
{
	namespace Helpers
	{
		template <class F>
		int EventWatch(void* data, SDL_Event* ev)
		{
			return (*(F*)data)(ev);
		}
	}
	
	
	
	void AddEventWatch(int (filter)(void*, SDL_Event*), void* userData)
	{
		SDL_AddEventWatch(filter, userData);
	}
	
	void Event::AddEventWatch(std::function<int(SDL_Event*)> filter)
	{
		typedef std::function<int(SDL_Event*)> Func_t;
		SDL_AddEventWatch(Helpers::EventWatch<Func_t>, (void*)(new Func_t(filter)));
	}
	
	
	unsigned char Event::EventState(EventType type, int state)
	{
		return SDL_EventState(SDL_RawEventType(type), state);
	}
	
	void Event::FilterEvents(int (filter)(void*, SDL_Event*), void* userData)
	{
		SDL_FilterEvents(filter, userData);
	}
	
	void Event::FilterEvents(std::function<int(SDL_Event*)> filter)
	{
		typedef std::function<int(SDL_Event*)> Func_t;
		SDL_FilterEvents(Helpers::EventWatch<Func_t>, (void*)&filter);
	}
	
	void Event::FlushEvent(EventType type)
	{
		SDL_FlushEvent(SDL_RawEventType(type));
	}
	
	void Event::FlushEvents(EventType min, EventType max)
	{
		SDL_FlushEvents(SDL_RawEventType(min), SDL_RawEventType(max));
	}
	
	bool Event::GetEventFilter(int (**filter)(void*, SDL_Event*), void** userData)
	{
		return SDL_GetEventFilter(filter, userData) == SDL_TRUE;
	}
	
	bool Event::GetEventFilter(std::function<int(void*, SDL_Event*)>* filter, void** data)
	{
		
		typedef int (Filter_t)(void*, SDL_Event*);
		Filter_t* filterPtr;
		if (SDL_GetEventFilter(&filterPtr, data) == SDL_TRUE)
		{
			if (filter != NULL)
			{
				*filter = std::function<int(void*, SDL_Event*)>([=](void* data, SDL_Event* ev) -> int
				{
					return (*filterPtr)(data, ev);
				});
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	
	unsigned char Event::GetEventState(EventType type)
	{
		return SDL_GetEventState(SDL_RawEventType(type));
	}
	
	bool Event::HasEvent(EventType type)
	{
		return SDL_HasEvent(SDL_RawEventType(type));
	}
	
	bool Event::HasEvents(EventType min, EventType max)
	{
		return SDL_HasEvents(SDL_RawEventType(min), SDL_RawEventType(max));
	}
	
	/*int Event::PeepEvents(SDL_Event*, int numevents, EventAction, EventType min, EventType max)
	{
		
	}*/ 
	
	void Event::PumpEvents()
	{
		SDL_PumpEvents();
	}
	
	bool Event::PushEvent(SDL_Event* ev)
	{
		return SDL_PushEvent(ev);
	}
	
	bool Event::PushEvent(Event*)
	{
		throw NotImp();
	}
	
	Event* Event::pollEvent()
	{
		throw NotImp();
	}
	
	bool Event::pollEvent(SDL_Event* ev)
	{
		return (SDL_PollEvent(ev) == 1);
	}
	
	bool Event::QuitRequested()
	{
		return SDL_QuitRequested();
	}
	
	void Event::RecordGesture(int i)
	{
		SDL_CHECKERROR(SDL_RecordGesture(i), 0);
	}
	
	EventType Event::RegisterEvents(int x)
	{
		return (EventType)SDL_RegisterEvents(x);
	}
	
	
	void Event::SetEventFilter(int (filter)(void*, SDL_Event*), void* userData)
	{
		throw NotImp();
	}
	
	void Event::SetEventFilter(std::function<int(SDL_Event*)> filter)
	{
		throw NotImp();
	}
	
	void Event::WaitEvent(SDL_Event* ev)
	{
		SDL_WaitEvent(ev);
	}
	
	Event* Event::WaitEvent()
	{
		throw NotImp();
	}
	
	void Event::WaitEventTimeout(SDL_Event* ev, int t)
	{
		SDL_WaitEventTimeout(ev, t);
	}
	
	Event* Event::WaitEventTimeout(int)
	{
		throw NotImp();
	}
	
	Event* Event::FromSDLEvent(SDL_Event*)
	{
		throw NotImp();
	}
}