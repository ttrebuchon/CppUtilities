#include <QUtils/GUI/SDL/LabelViewComponent.h>
#include <QUtils/Drawing/SDL/Font.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/GUI/SDL/RenderTarget.h>
#include <QUtils/GUI/Errors.h>
#include <iostream>


namespace QUtils::GUI::SDL
{
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string text, const std::string font, unsigned int fontSize) : SDLViewComponent(), lastW(-1), lastH(-1), _text(text), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::~SDLLabelViewComponent()
	{
		
	}
		
	std::string SDLLabelViewComponent::text() const
	{
		return _text;
	}
	
	void SDLLabelViewComponent::text(const std::string value)
	{
		_text = value;
		_changed = true;
	}
		
	void SDLLabelViewComponent::update()
	{
		if (changed())
		{
			_font = SDLFontResourceLoader::get(_fontName, _fontSize);
			if (texture != NULL)
			{
				delete texture;
				texture = NULL;
			}
			_changed = false;
		}
	}
	
	void SDLLabelViewComponent::render(RenderTarget* genericTarget, int x, int y, int w, int h)
	{
		auto sdlTarget = dynamic_cast<SDLRenderTarget*>(genericTarget);
		if (sdlTarget == NULL)
		{
			throw IncompatibleGUI_TypeException().Msg("RenderTarget isn't an SDLRenderTarget").File(__FILE__).Function(__func__);
		}
		auto ren = sdlTarget->getRenderer();
		
		calcRenderDimensions(w, h);
		
		if (w != lastW || h != lastH || texture == NULL)
		{
			if (texture != NULL)
			{
				delete texture;
				texture = NULL;
			}
			
			auto surf = _font->surfaceBlendedWrapped(text(), color(), w);
			texture = surf->createTexture(ren);
			
			
			lastW = w;
			lastH = h;
		}
		
		texture->alphaMod(static_cast<unsigned char>(255*opacity()));
		texture->blendMode(Drawing::SDL::BlendMode::Blend);
		ren->copy(texture, NULL, {x, y, w, h});
	}
	
	int SDLLabelViewComponent::nativeWidth() const
	{
		int w;
		if (_font == NULL)
		{
			const_cast<SDLLabelViewComponent*>(this)->update();
		}
		_font->sizeText(_text, &w, NULL);
		return w;
	}
	
	int SDLLabelViewComponent::nativeHeight() const
	{
		int h;
		if (_font == NULL)
		{
			const_cast<SDLLabelViewComponent*>(this)->update();
		}
		_font->sizeText(_text, NULL, &h);
		return h;
	}
	
}