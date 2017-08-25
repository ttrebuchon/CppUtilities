#include <QUtils/Drawing/SDL/Event.h>
#include <QUtils/Drawing/SDL/Errors.h>
#include <QUtils/Drawing/SDL/Events/Events.h>
#include <QUtils/Drawing/SDL/EventEnumMappings.h>
#include "IfSDL.h"
#include <QUtils/Exception/NotImplemented.h>


using namespace QUtils::Drawing::SDL::EventMappings;

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
	
	Event* Event::PollEvent()
	{
		SDL_Event ev;
		if (!PollEvent(&ev))
		{
			return NULL;
		}
		return FromSDLEvent(&ev);
	}
	
	bool Event::PollEvent(SDL_Event* ev)
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
		SDL_Event ev;
		WaitEvent(&ev);
		return FromSDLEvent(&ev);
	}
	
	void Event::WaitEventTimeout(SDL_Event* ev, int t)
	{
		SDL_WaitEventTimeout(ev, t);
	}
	
	Event* Event::WaitEventTimeout(int t)
	{
		SDL_Event ev;
		WaitEventTimeout(&ev, t);
		return FromSDLEvent(&ev);
	}
	
	Event* Event::FromSDLEvent(SDL_Event* ev)
	{
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
	}
}