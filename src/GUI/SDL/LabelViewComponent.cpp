#include <QUtils/GUI/SDL/LabelViewComponent.h>
#include <QUtils/Drawing/SDL/Font.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/GUI/SDL/RenderTarget.h>
#include <QUtils/GUI/Errors.h>
#include <iostream>


namespace QUtils::GUI::SDL
{
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string id, bool touch, const std::string text, const std::string font, unsigned int fontSize) : TextViewComponent(id, touch), lastW(-1), lastH(-1), _text(text), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::SDLLabelViewComponent(bool touch, const std::string text, const std::string font, unsigned int fontSize) : TextViewComponent(touch), lastW(-1), lastH(-1), _text(text), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string id, const std::string text, const std::string font, unsigned int fontSize) : TextViewComponent(id), lastW(-1), lastH(-1), _text(text), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1)
	{
		_changed = true;
	}
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string text, const std::string font, unsigned int fontSize) : TextViewComponent(), lastW(-1), lastH(-1), _text(text), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1)
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
			onUpdate(this);
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
		
		int tmpW = w;
		int tmpH = h;
		calcRenderDimensions(tmpW, tmpH);
		w = tmpW;
		h = tmpH;
		if (w != lastW || h != lastH || texture == NULL)
		{
			if (texture != NULL)
			{
				delete texture;
				texture = NULL;
			}
			
			Drawing::SDL::Surface* surf = NULL;
			auto wrapW = wrapWidth();
			
			//surf = _font->surfaceBlendedWrapped(text(), (Drawing::SDL::Color)color(), wrapW*w);
			surf = _font->surfaceBlended(text(), (Drawing::SDL::Color)color());
			if (height() == -2)
			{
				h = (int)(static_cast<double>(surf->height())/surf->width()*w);
			}
			
			
			texture = surf->createTexture(ren);
			
			delete surf;
			
			
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
	
	double SDLLabelViewComponent::wrapWidth() const
	{
		return _wrapWidth;
	}
	
	void SDLLabelViewComponent::wrapWidth(const double value)
	{
		if (value != _wrapWidth)
		{
			_changed = true;
			_wrapWidth = value;
		}
	}
	
}