#pragma once
#include "Version.h"
#include "EventType.h"
#include <functional>

union SDL_Event;

namespace QUtils::Drawing::SDL
{
	namespace Helpers
	{
		template <class F, class = void>
		struct InvokeWhichEventType
		{
			static void call(const F f)
			{
				
			}
		};
	}
	
	class Event
	{
		private:
		
		public:
		Event(EventType type, unsigned int timestamp) : type(type), timestamp(timestamp)
		{}
		Event(int type, unsigned int timestamp) : type(SDL_EnumEventType(type)), timestamp(timestamp)
		{}
		virtual ~Event();
		const EventType type;
		unsigned int timestamp;
		
		virtual std::string eventName() const;
		
		
		static void AddEventWatch(int (filter)(void*, SDL_Event*), void* userData);
		static unsigned int AddEventWatch(std::function<int(SDL_Event*)> filter);
		
		template <class F, class Obj>
		inline static unsigned int AddEventWatch(const F f, Obj* userData)
		{
			return AddEventWatch(std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
			{
				return f(userData, ev);
			}));
		}
		
		inline static unsigned int AddEventWatch(std::function<int(Event*)> filter)
		{
			return AddEventWatch(std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
			{
				auto ev2 = Event::FromSDLEvent(ev);
				auto ret = filter(ev2);
				delete ev2;
				return ret;
			}));
		}
		
		inline static void AppendEventFilter(int (filter)(void*, SDL_Event*), void* userData)
		{
			std::function<int(SDL_Event*)> oldFilter;
			bool hasOldFilter = GetEventFilter(&oldFilter);
			
			if (!hasOldFilter)
			{
				SetEventFilter(filter, userData);
			}
			else
			{
				SetEventFilter(std::function<int(SDL_Event*)>([oldFilter, filter, userData](SDL_Event* ev) -> int
				{
					auto r1 = oldFilter(ev);
					auto r2 = filter(userData, ev);
					return r1 & r2;
				}));
			}
		}
		
		static void AppendEventFilter(std::function<int(SDL_Event*)> filter);
		
		template <class F, class Obj>
		inline static void AppendEventFilter(const F f, Obj* userData)
		{
			AppendEventFilter(std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
			{
				return f(userData, ev);
			}));
		}
		
		inline static void AppendEventFilter(std::function<int(Event*)> filter)
		{
			AppendEventFilter(std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
			{
				auto ev2 = Event::FromSDLEvent(ev);
				auto ret = filter(ev2);
				delete ev2;
				return ret;
			}));
		}
		
		static void DelEventWatch(int (filter)(void*, SDL_Event*), void* userData);
		static void DelEventWatch(unsigned int index);
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
		static void FlushEvents(unsigned int min, unsigned int max);
		
		static bool GetEventFilter(int (**filter)(void*, SDL_Event*), void** userData);
		static bool GetEventFilter(std::function<int(SDL_Event*)>*);
		
		static unsigned char GetEventState(EventType);
		
		static bool HasEvent(EventType);
		static bool HasEvents(EventType min, EventType max);
		
		//static int PeepEvents(SDL_Event*, int numevents, EventAction, EventType min, EventType max);
		static void PumpEvents();
		static bool PushEvent(SDL_Event*);
		static bool PushEvent(Event*);
		static Event* PollEvent();
		static bool PollEvent(SDL_Event*);
		static bool QuitRequested();
		static void RecordGesture(/*SDL_TouchID*/int);
		static EventType RegisterEvents(int);
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
		inline static void SetEventFilter(std::function<int(Event*)> filter)
		{
			SetEventFilter(std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
			{
				auto ev2 = Event::FromSDLEvent(ev);
				auto ret = filter(ev2);
				delete ev2;
				return ret;
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
		
		static Event* FromSDLEvent(SDL_Event*);
		
		
	};
}