#include <QUtils/Drawing/SDL/Events/KeyboardEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	KeyboardEvent::KeyboardEvent(const SDL_KeyboardEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	KeyboardEvent::KeyboardEvent(const SDL_KeyboardEvent& ev) : KeyboardEvent(&ev)
	{}
}
