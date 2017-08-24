#include <QUtils/Drawing/SDL/Events/MouseMotionEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	MouseMotionEvent::MouseMotionEvent(const SDL_MouseMotionEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	MouseMotionEvent::MouseMotionEvent(const SDL_MouseMotionEvent& ev) : MouseMotionEvent(&ev)
	{}
}
