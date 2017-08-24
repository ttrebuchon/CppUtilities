#include <QUtils/Drawing/SDL/Events/JoyButtonEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	JoyButtonEvent::JoyButtonEvent(const SDL_JoyButtonEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	JoyButtonEvent::JoyButtonEvent(const SDL_JoyButtonEvent& ev) : JoyButtonEvent(&ev)
	{}
}
