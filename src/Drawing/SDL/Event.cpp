#include <QUtils/Drawing/SDL/Event.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include <QUtils/Drawing/SDL/Events/Events.h>
#include <map>
#include "IfSDL.h"
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils::Drawing::SDL
{
	Event::~Event()
	{
		
	}
	
	std::string Event::eventName() const
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_EventTypeName(this->type);
		#else
		throw NotAvail();
		#endif
	}
	
	
	
	
	
	
	namespace Helpers
	{
		template <class F>
		int EventWatch(void* data, SDL_Event* ev)
		{
			return (*(F*)data)(ev);
		}
		
		static unsigned int EventWatchersCounter = 1;
		static std::map<unsigned int, std::tuple<int(*)(void*, SDL_Event*), void*>> EventWatchers;
	}
	
	
	
	void Event::AddEventWatch(int (filter)(void*, SDL_Event*), void* userData)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_AddEventWatch(filter, userData);
		#else
		throw NotAvail();
		#endif
	}
	
	unsigned int Event::AddEventWatch(std::function<int(SDL_Event*)> filter)
	{
		#ifdef QUTILS_HAS_SDL2
		typedef std::function<int(SDL_Event*)> Func_t;
		auto lambda = new Func_t(filter);
		SDL_AddEventWatch(Helpers::EventWatch<Func_t>, (void*)lambda);
		unsigned int index;
		Helpers::EventWatchers[index = Helpers::EventWatchersCounter++] = std::make_tuple(Helpers::EventWatch<Func_t>, (void*)lambda);
		return index;
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::AppendEventFilter(std::function<int(SDL_Event*)> filter)
	{
		#ifdef QUTILS_HAS_SDL2
		std::function<int(SDL_Event*)> oldFilter;
		bool hasOldFilter = GetEventFilter(&oldFilter);
			
		if (!hasOldFilter)
		{
			SetEventFilter(filter);
		}
		else
		{
			SetEventFilter(std::function<int(SDL_Event*)>([oldFilter, filter](SDL_Event* ev) -> int
			{
				auto r1 = oldFilter(ev);
				auto r2 = filter(ev);
				return r1 & r2;
			}));
		}
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::DelEventWatch(int (filter)(void*, SDL_Event*), void* userData)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_DelEventWatch(filter, userData);
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::DelEventWatch(unsigned int index)
	{
		#ifdef QUTILS_HAS_SDL2
		if (index >= Helpers::EventWatchersCounter)
		{
			throw SDLErrorException().Function(__func__).Line(__LINE__).Msg("Index (" + std::to_string(index) + ") is out of bounds [Current Counter: " + std::to_string(Helpers::EventWatchersCounter) + "]");
		}
		auto funcTuple = Helpers::EventWatchers.at(index);
		Helpers::EventWatchers.erase(index);
		SDL_DelEventWatch(std::get<0>(funcTuple), std::get<1>(funcTuple));
		#else
		throw NotAvail();
		#endif
	}
	
	
	unsigned char Event::EventState(EventType type, int state)
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_EventState(SDL_RawEventType(type), state);
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::FilterEvents(int (filter)(void*, SDL_Event*), void* userData)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_FilterEvents(filter, userData);
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::FilterEvents(std::function<int(SDL_Event*)> filter)
	{
		#ifdef QUTILS_HAS_SDL2
		typedef std::function<int(SDL_Event*)> Func_t;
		SDL_FilterEvents(Helpers::EventWatch<Func_t>, (void*)&filter);
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::FlushEvent(EventType type)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_FlushEvent(SDL_RawEventType(type));
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::FlushEvents(EventType min, EventType max)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_FlushEvents(SDL_RawEventType(min), SDL_RawEventType(max));
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::FlushEvents(unsigned int min, unsigned int max)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_FlushEvents(min, max);
		#else
		throw NotAvail();
		#endif
	}
	
	bool Event::GetEventFilter(int (**filter)(void*, SDL_Event*), void** userData)
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetEventFilter(filter, userData) == SDL_TRUE;
		#else
		throw NotAvail();
		#endif
	}
	
	bool Event::GetEventFilter(std::function<int(SDL_Event*)>* filter)
	{
		#ifdef QUTILS_HAS_SDL2
		void* data;
		typedef int (Filter_t)(void*, SDL_Event*);
		Filter_t* filterPtr;
		if (SDL_GetEventFilter(&filterPtr, &data) == SDL_TRUE)
		{
			if (filter != NULL)
			{
				*filter = std::function<int(SDL_Event*)>([=](SDL_Event* ev) -> int
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
		#else
		throw NotAvail();
		#endif
	}
	
	unsigned char Event::GetEventState(EventType type)
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_GetEventState(SDL_RawEventType(type));
		#else
		throw NotAvail();
		#endif
	}
	
	bool Event::HasEvent(EventType type)
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_HasEvent(SDL_RawEventType(type));
		#else
		throw NotAvail();
		#endif
	}
	
	bool Event::HasEvents(EventType min, EventType max)
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_HasEvents(SDL_RawEventType(min), SDL_RawEventType(max));
		#else
		throw NotAvail();
		#endif
	}
	
	/*int Event::PeepEvents(SDL_Event*, int numevents, EventAction, EventType min, EventType max)
	{
		
	}*/ 
	
	void Event::PumpEvents()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_PumpEvents();
		#else
		throw NotAvail();
		#endif
	}
	
	bool Event::PushEvent(SDL_Event* ev)
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_PushEvent(ev);
		#else
		throw NotAvail();
		#endif
	}
	
	bool Event::PushEvent(Event*)
	{
		#ifdef QUTILS_HAS_SDL2
		throw NotImp();
		#else
		throw NotAvail();
		#endif
	}
	
	Event* Event::PollEvent()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Event ev;
		if (!PollEvent(&ev))
		{
			return NULL;
		}
		return FromSDLEvent(&ev);
		#else
		throw NotAvail();
		#endif
	}
	
	bool Event::PollEvent(SDL_Event* ev)
	{
		#ifdef QUTILS_HAS_SDL2
		return (SDL_PollEvent(ev) == 1);
		#else
		throw NotAvail();
		#endif
	}
	
	bool Event::QuitRequested()
	{
		#ifdef QUTILS_HAS_SDL2
		return SDL_QuitRequested();
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::RecordGesture(int i)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_CHECKERROR(SDL_RecordGesture(i), 0);
		#else
		throw NotAvail();
		#endif
	}
	
	EventType Event::RegisterEvents(int x)
	{
		#ifdef QUTILS_HAS_SDL2
		return (EventType)SDL_RegisterEvents(x);
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::SetEventFilter(int (filter)(void*, SDL_Event*), void* userData)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_SetEventFilter(filter, userData);
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::SetEventFilter(std::function<int(SDL_Event*)> filter)
	{
		#ifdef QUTILS_HAS_SDL2
		typedef std::function<int(SDL_Event*)> Func_t;
		auto lambda = new Func_t(filter);
		SDL_SetEventFilter(Helpers::EventWatch<Func_t>, (void*)lambda);
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::WaitEvent(SDL_Event* ev)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_WaitEvent(ev);
		#else
		throw NotAvail();
		#endif
	}
	
	Event* Event::WaitEvent()
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Event ev;
		WaitEvent(&ev);
		return FromSDLEvent(&ev);
		#else
		throw NotAvail();
		#endif
	}
	
	void Event::WaitEventTimeout(SDL_Event* ev, int t)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_WaitEventTimeout(ev, t);
		#else
		throw NotAvail();
		#endif
	}
	
	Event* Event::WaitEventTimeout(int t)
	{
		#ifdef QUTILS_HAS_SDL2
		SDL_Event ev;
		WaitEventTimeout(&ev, t);
		return FromSDLEvent(&ev);
		#else
		throw NotAvail();
		#endif
	}
	
	Event* Event::FromSDLEvent(SDL_Event* ev)
	{
		#ifdef QUTILS_HAS_SDL2
		EventType type = SDL_EnumEventType(ev->type);
		switch (type)
		{
			case EventType::Quit:
			return new QuitEvent(ev->quit);
			
			case EventType::WindowEvent:
			return new WindowEvent(ev->window);
			
			case EventType::SysWMEvent:
			return new SysWMEvent(ev->syswm);
			
			case EventType::KeyDown:
			case EventType::KeyUp:
			/*{
				const EventType v = EventType::KeyDown;
				typedef typename Event_t<v>::type Type;
				return new Type(Enum_t<Type>::get(ev));
			}*/
			return new KeyboardEvent(ev->key);
			
			case EventType::TextEditing:
			return new TextEditingEvent(ev->edit);
			
			case EventType::TextInput:
			return new TextInputEvent(ev->text);
			
			case EventType::MouseMotion:
			return new MouseMotionEvent(ev->motion);
			
			case EventType::MouseButtonDown:
			case EventType::MouseButtonUp:
			return new MouseButtonEvent(ev->button);
			
			case EventType::MouseWheel:
			return new MouseWheelEvent(ev->wheel);
			
			case EventType::JoyAxisMotion:
			return new JoyAxisEvent(ev->jaxis);
			
			case EventType::JoyBallMotion:
			return new JoyBallEvent(ev->jball);
			
			case EventType::JoyHatMotion:
			return new JoyHatEvent(ev->jhat);
			
			case EventType::JoyButtonDown:
			case EventType::JoyButtonUp:
			return new JoyButtonEvent(ev->jbutton);
			
			case EventType::JoyDeviceAdded:
			case EventType::JoyDeviceRemoved:
			return new JoyDeviceEvent(ev->jdevice);
			
			case EventType::ControllerAxisMotion:
			return new ControllerAxisEvent(ev->caxis);
			
			case EventType::ControllerButtonDown:
			case EventType::ControllerButtonUp:
			return new ControllerButtonEvent(ev->cbutton);
			
			case EventType::ControllerDeviceAdded:
			case EventType::ControllerDeviceRemoved:
			case EventType::ControllerDeviceRemapped:
			return new ControllerDeviceEvent(ev->cdevice);
			
			case EventType::FingerDown:
			case EventType::FingerUp:
			case EventType::FingerMotion:
			return new TouchFingerEvent(ev->tfinger);
			
			case EventType::DollarGesture:
			case EventType::DollarRecord:
			return new DollarGestureEvent(ev->dgesture);
			
			case EventType::MultiGesture:
			return new MultiGestureEvent(ev->mgesture);
			
			case EventType::ClipboardUpdate:
			throw NotImp();
			return NULL;
			
			case EventType::DropFile:
			#if SDL_VERSION_MIN(2,0,5)
			case EventType::DropText:
			case EventType::DropBegin:
			case EventType::DropComplete:
			#endif
			return new DropEvent(ev->drop);
			
			case EventType::AudioDeviceAdded:
			case EventType::AudioDeviceRemoved:
			return new AudioDeviceEvent(ev->adevice);
			
			case EventType::UserEvent:
			return new UserEvent(ev->user);
			
			default:
			break;
		}
		throw NotImp();
		#else
		throw NotAvail();
		#endif
	}
}