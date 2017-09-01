#include <QUtils/GUI/Clickable.h>


namespace QUtils::GUI
{
	Clickable::Clickable(bool touch) : onFingerDown(touch), onFingerUp(touch), onFingerMotion(touch), onMouseButtonDown(!touch), onMouseButtonUp(!touch), onMouseMotion(!touch), onMouseWheel(!touch)
	{
		
	}
	
	Clickable::Clickable() : onFingerDown(), onFingerUp(), onFingerMotion(), onMouseButtonDown(), onMouseButtonUp(), onMouseMotion(), onMouseWheel()
	{
		
	}
	
	void Clickable::relayEvents(std::function<Clickable*(Clickable*)> accessor)
	{
		#define FORWARD(x) x += [&, accessor](auto... args) \
		{ \
			auto ptr = accessor(this); \
			if (ptr != NULL) \
			{ \
				ptr->x(args...); \
			} \
		}
		
		FORWARD(onFingerDown);
		FORWARD(onFingerUp);
		FORWARD(onFingerMotion);
		FORWARD(onMouseButtonDown);
		FORWARD(onMouseButtonUp);
		FORWARD(onMouseMotion);
		FORWARD(onMouseWheel);
		
		
		#undef FORWARD
	}
}