#include <QUtils/Drawing/SDL/Events/JoyDeviceEvent.h>
#include "../IfSDL.h"

#define INIT_MEMBER(x) this->x = ev->x

namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	JoyDeviceEvent::JoyDeviceEvent(const SDL_JoyDeviceEvent* ev) : Event(ev->type, ev->timestamp)
	{
		
	}
	
	JoyDeviceEvent::JoyDeviceEvent(const SDL_JoyDeviceEvent& ev) : JoyDeviceEvent(&ev)
	{}
	
	#else
	
	#endif
}