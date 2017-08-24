#include <QUtils/Drawing/SDL/Events/ControllerButtonEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	ControllerButtonEvent::ControllerButtonEvent(const SDL_ControllerButtonEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(which);
		INIT_MEMBER(button);
		INIT_MEMBER(state);
	}
	
	ControllerButtonEvent::ControllerButtonEvent(const SDL_ControllerButtonEvent& ev) : ControllerButtonEvent(&ev)
	{}
}