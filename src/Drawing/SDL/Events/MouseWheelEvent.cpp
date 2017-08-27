#include <QUtils/Drawing/SDL/Events/MouseWheelEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	MouseWheelEvent::MouseWheelEvent(const SDL_MouseWheelEvent* ev) : Event(ev->type, ev->timestamp)
	{
		INIT_MEMBER(windowID);
		INIT_MEMBER(which);
		INIT_MEMBER(x);
		INIT_MEMBER(y);
		INIT_MEMBER(direction);
	}
	
	MouseWheelEvent::MouseWheelEvent(const SDL_MouseWheelEvent& ev) : MouseWheelEvent(&ev)
	{}
}