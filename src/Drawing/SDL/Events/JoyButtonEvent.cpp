#include <QUtils/Drawing/SDL/Events/JoyButtonEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	JoyButtonEvent::JoyButtonEvent(const SDL_JoyButtonEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	JoyButtonEvent::JoyButtonEvent(const SDL_JoyButtonEvent& ev) : JoyButtonEvent(&ev)
	{}
	#else
	JoyButtonEvent::JoyButtonEvent(const SDL_JoyButtonEvent* ev) : Event(-1, 0)
	{
		throw NotAvail();
	}
	
	JoyButtonEvent::JoyButtonEvent(const SDL_JoyButtonEvent& ev) : JoyButtonEvent(&ev)
	{
		
	}
	
	#endif
}