#include <QUtils/GUI/SDL/TextureViewComponent.h>


namespace QUtils::GUI::SDL
{
	SDLTextureViewComponent::SDLTextureViewComponent(Drawing::SDL::Texture* tex) : SDLViewComponent(), texture(tex)
	{
		
	}
	
	SDLTextureViewComponent::~SDLTextureViewComponent()
	{
		
	}
}