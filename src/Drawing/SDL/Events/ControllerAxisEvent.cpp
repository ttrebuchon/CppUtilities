#include <QUtils/Drawing/SDL/Events/ControllerAxisEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	ControllerAxisEvent::ControllerAxisEvent(const SDL_ControllerAxisEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(which);
		INIT_MEMBER(axis);
		INIT_MEMBER(value);
	}
	
	ControllerAxisEvent::ControllerAxisEvent(const SDL_ControllerAxisEvent& ev) : ControllerAxisEvent(&ev)
	{}
}