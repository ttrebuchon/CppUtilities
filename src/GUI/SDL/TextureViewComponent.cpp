#include <QUtils/GUI/SDL/TextureViewComponent.h>
#include <QUtils/GUI/SDL/AppWindow.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/GUI/Errors.h>

#include <iostream>


namespace QUtils::GUI::SDL
{
	SDLTextureViewComponent::SDLTextureViewComponent(const std::string id, bool touch, Drawing::SDL::Texture* tex) : ViewComponent(id, touch), texture(tex)
	{
		
	}
	
	SDLTextureViewComponent::SDLTextureViewComponent(bool touch, Drawing::SDL::Texture* tex) : ViewComponent(touch), texture(tex)
	{
		
	}
	
	SDLTextureViewComponent::SDLTextureViewComponent(const std::string id, Drawing::SDL::Texture* tex) : ViewComponent(id), texture(tex)
	{
		
	}
	
	SDLTextureViewComponent::SDLTextureViewComponent(Drawing::SDL::Texture* tex) : ViewComponent(), texture(tex)
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
		
		calcRenderDimensions(w, h);
		
		auto oldAMod = texture->alphaMod();
		auto oldMode = texture->blendMode();
		texture->alphaMod(static_cast<unsigned char>(opacity()*255));
		texture->blendMode(Drawing::SDL::BlendMode::Blend);
		ren->copy(texture, NULL, {x, y, w, h});
		texture->alphaMod(oldAMod);
		texture->blendMode(oldMode);
	}
	
	int SDLTextureViewComponent::nativeWidth() const
	{
		return texture->width();
	}
	
	int SDLTextureViewComponent::nativeHeight() const
	{
		return texture->height();
	}
}