#include <QUtils/Drawing/SDL/Events/SysWMEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	SysWMEvent::SysWMEvent(const SDL_SysWMEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	SysWMEvent::SysWMEvent(const SDL_SysWMEvent& ev) : SysWMEvent(&ev)
	{}
	
	#else
	
	#endif
}