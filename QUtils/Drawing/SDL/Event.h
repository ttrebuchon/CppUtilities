#pragma once
#include "EventType.h"
#include <functional>

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
		
		
		static void AddEventWatch(int (filter)(void*, SDL_Event*), void* userData);
		static void AddEventWatch(std::function<int(SDL_Event*)> filter);
		
		template <class F, class Obj>
		inline static void AddEventWatch(const F f, Obj* userData)
		{
			AddEventWatch(std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
			{
				return f(userData, ev);
			}));
		}
		
		
		static unsigned char EventState(EventType, int state);
		
		static void FilterEvents(int (filter)(void*, SDL_Event*), void* userData);
		static void FilterEvents(std::function<int(SDL_Event*)> filter);
		
		template <class F, class Obj>
		inline static void FilterEvents(const F f, Obj* userData)
		{
			FilterEvents(std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
			{
				return f(userData, ev);
			}));
		}
		
		static void FlushEvent(EventType);
		static void FlushEvents(EventType min, EventType max);
		
		static bool GetEventFilter(int (*filter)(void*, SDL_Event*), void** userData);
		static bool GetEventFilter(std::function<int(void*, SDL_Event*)>*, void**);
		
		static unsigned char GetEventState(EventType);
		
		static bool HasEvent(EventType);
		static bool HasEvents(EventType min, EventType max);
		
		//static int PeepEvents(SDL_Event*, int numevents, EventAction, EventType min, EventType max);
		static void PumpEvents();
		static bool PushEvent(SDL_Event*);
		static bool PushEvent(Event*);
		static Event* pollEvent();
		static bool pollEvent(SDL_Event*);
		static bool QuitRequested();
		static void RecordGesture(/*SDL_TouchID*/int);
		EventType RegisterEvents(int);
		
		
		static void SetEventFilter(int (filter)(void*, SDL_Event*), void* userData);
		static void SetEventFilter(std::function<int(SDL_Event*)> filter);
		
		template <class F, class Obj>
		inline static void SetEventFilter(const F f, Obj* userData)
		{
			SetEventFilter(std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
			{
				return f(userData, ev);
			}));
		}
		
		static void WaitEvent(SDL_Event*);
		static Event* WaitEvent();
		inline static void WaitEvent(SDL_Event* ptr, int t)
		{
			WaitEventTimeout(ptr, t);
		}
		inline static Event* WaitEvent(int t)
		{
			return WaitEventTimeout(t);
		}
		static void WaitEventTimeout(SDL_Event*, int);
		static Event* WaitEventTimeout(int);
		
		
	};
}