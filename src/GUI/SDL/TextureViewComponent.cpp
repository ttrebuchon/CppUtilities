#include <QUtils/GUI/SDL/TextureViewComponent.h>
#include <QUtils/GUI/SDL/AppWindow.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/GUI/Errors.h>

#include <iostream>


namespace QUtils::GUI::SDL
{
	SDLTextureViewComponent::SDLTextureViewComponent(Drawing::SDL::Texture* tex) : SDLViewComponent(), texture(tex)
	{
		
	}
	
	SDLTextureViewComponent::~SDLTextureViewComponent()
	{
		
	}
	
	void SDLTextureViewComponent::render(RenderTarget* genericTarget, int x, int y, int w, int h)
	{
		auto sdlTarget = dynamic_cast<SDLRenderTarget*>(genericTarget);
		if (sdlTarget == NULL)
		{
			throw IncompatibleGUI_TypeException().Msg("RenderTarget isn't an SDLRenderTarget").File(__FILE__).Function(__func__);
		}
		
		auto ren = sdlTarget->getRenderer();
		ren->copy(texture, NULL, {x, y, w, h});
		std::cout << "\t(" << x << ", " << y << ", " << w << ", " << h << ")\n";
	}
	
	void SDLTextureViewComponent::render(RenderTarget* target, int x, int y)
	{
		render(target, x, y, width(), height());
	}
	
	void SDLTextureViewComponent::render(RenderTarget* target)
	{
		render(target, 0, 0, width(), height());
	}
	
	double SDLTextureViewComponent::width() const
	{
		return texture->width();
	}
	
	double SDLTextureViewComponent::height() const
	{
		return texture->height();
	}
}