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
		if (w < 0)
		{
			w = nativeWidth();
		}
		else
		{
			w = static_cast<int>(width()*w);
		}
		if (h < 0)
		{
			h = nativeHeight();
		}
		else
		{
			h = static_cast<int>(height()*h);
		}
		
		texture->blendMode(Drawing::SDL::BlendMode::Blend);
		ren->copy(texture, NULL, {x, y, w, h});
	}
	
	int SDLTextureViewComponent::nativeWidth() const
	{
		return texture->width();
	}
	
	int SDLTextureViewComponent::nativeHeight() const
	{
		return texture->height();
	}
	
	double SDLTextureViewComponent::opacity() const
	{
		return static_cast<double>(texture->alphaMod())/255;
	}
	
	void SDLTextureViewComponent::opacity(double value)
	{
		texture->alphaMod(value*255);
	}
}