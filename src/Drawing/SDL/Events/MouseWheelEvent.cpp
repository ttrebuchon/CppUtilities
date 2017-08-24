#include <QUtils/Drawing/SDL/Events/MouseWheelEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	MouseWheelEvent::MouseWheelEvent(const SDL_MouseWheelEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	MouseWheelEvent::MouseWheelEvent(const SDL_MouseWheelEvent& ev) : MouseWheelEvent(&ev)
	{}
}
