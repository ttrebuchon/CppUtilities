#include <QUtils/GUI/SDL/ViewComponent.h>

namespace QUtils::GUI::SDL
{
	SDLViewComponent::SDLViewComponent(const std::string id, bool touch) : ViewComponent(id, touch)
	{
		
	}
	
	SDLViewComponent::SDLViewComponent(bool touch) : ViewComponent(touch)
	{
		
	}
	
	SDLViewComponent::SDLViewComponent(const std::string id) : ViewComponent(id)
	{
		
	}
	
	SDLViewComponent::SDLViewComponent() : ViewComponent()
	{
		
	}
	SDLViewComponent::~SDLViewComponent()
	{
		
	}
}