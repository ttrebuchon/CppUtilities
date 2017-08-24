#include <QUtils/Drawing/SDL/Events/QuitEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	QuitEvent::QuitEvent(const SDL_QuitEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	QuitEvent::QuitEvent(const SDL_QuitEvent& ev) : QuitEvent(&ev)
	{}
}
