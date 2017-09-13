#include <QUtils/Drawing/SDL/Events/JoyBallEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	JoyBallEvent::JoyBallEvent(const SDL_JoyBallEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	JoyBallEvent::JoyBallEvent(const SDL_JoyBallEvent& ev) : JoyBallEvent(&ev)
	{}
	
	#else
	
	#endif
}