#include <QUtils/GUI/SDL/LabelViewComponent.h>
#include <QUtils/Drawing/SDL/Font.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/GUI/SDL/RenderTarget.h>
#include <QUtils/GUI/Errors.h>
#include <iostream>


namespace QUtils::GUI::SDL
{
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string id, bool touch, const std::string font, unsigned int fontSize) : TextViewComponent(id, touch), lastW(-1), lastH(-1), lastNativeW(-1), lastNativeH(-1), _textChanged(true), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::SDLLabelViewComponent(bool touch, const std::string font, unsigned int fontSize) : TextViewComponent(touch), lastW(-1), lastH(-1), _textChanged(true), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string id, const std::string font, unsigned int fontSize) : TextViewComponent(id), lastW(-1), lastH(-1), _textChanged(true), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1)
	{
		_changed = true;
	}
	SDLLabelViewComponent::SDLLabelViewComponent(const std::string font, unsigned int fontSize) : TextViewComponent(), lastW(-1), lastH(-1), _textChanged(true), _font(NULL), texture(NULL), _color({0, 0, 0, 255}), _fontSize(fontSize), _fontName(font), _wrapWidth(-1)
	{
		_changed = true;
	}
	
	SDLLabelViewComponent::~SDLLabelViewComponent()
	{
		
	}
		
	void SDLLabelViewComponent::update()
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
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
			lastNativeW = lastNativeH = -1;
			_textChanged = false;
		}
	}
	
	void SDLLabelViewComponent::render(RenderTarget* genericTarget, int x, int y, int w, int h)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
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
		if (w != lastW || h != lastH || texture == NULL || _textChanged)
		{
			lastW = w;
			lastH = h;
			if (texture != NULL)
			{
				delete texture;
				texture = NULL;
			}
			_textChanged = false;
			
			Drawing::SDL::Surface* surf = NULL;
			auto wrapW = wrapWidth();
			
			if (wrapW > 0)
			{
			
			surf = _font->surfaceBlendedWrapped(text(), (Drawing::SDL::Color)color(), wrapW);
			w = lastNativeW = surf->width();
			h = lastNativeH = surf->height();
			}
			else
			{
			surf = _font->surfaceBlended(text(), (Drawing::SDL::Color)color());
			lastNativeW = surf->width();
			lastNativeH = surf->height();
			}
			
			if (height() == -2)
			{
				h = (int)(static_cast<double>(surf->height())/surf->width()*w);
			}
			
			
			texture = surf->createTexture(ren);
			
			delete surf;
			
			
			
		}
		
		texture->alphaMod(static_cast<unsigned char>(255*opacity()));
		texture->blendMode(Drawing::SDL::BlendMode::Blend);
		ren->copy(texture, NULL, {x, y, w, h});
	}
	
	int SDLLabelViewComponent::nativeWidth() const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (lastNativeW < 0 || lastNativeH < 0)
		{
			updateNativeDims();
		}
		return lastNativeW;
	}
	
	int SDLLabelViewComponent::nativeHeight() const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (lastNativeW < 0 || lastNativeH < 0)
		{
			updateNativeDims();
		}
		return lastNativeH;
	}
	
	double SDLLabelViewComponent::wrapWidth() const
	{
		return _wrapWidth;
	}
	
	void SDLLabelViewComponent::wrapWidth(const double value)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (value != _wrapWidth)
		{
			_changed = true;
			_wrapWidth = value;
		}
	}
	
	void SDLLabelViewComponent::calcRelativeDimensions(double& outW, double& outH) const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		auto tmpW = width();
		auto tmpH = height();
		
		if (tmpW == -2 && tmpH == -2)
		{
			tmpW = tmpH = -1;
		}
		
		double nativeW, nativeH;
		
		if (tmpW < 0 || tmpH < 0)
		{
			if (lastNativeW < 0 || lastNativeH < 0)
			{
				updateNativeDims();
			}
			nativeW = lastNativeW;
			nativeH = lastNativeH;
		}
		
		if (tmpW >= 0)
		{
			outW = tmpW;
		}
		else if (tmpW == -1)
		{
			outW = nativeW/outW;
		}
		
		if (tmpH >= 0)
		{
			outH = tmpH;
		}
		else if (tmpH == -1)
		{
			outH = nativeH/outH;
		}
		
		
		
		if (tmpW == -2)
		{
			outW *= nativeW/nativeH;
		}
		
		if (tmpH == -2)
		{
			outH *= nativeH/nativeW;
		}
	}
	
	void SDLLabelViewComponent::updateNativeDims() const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (_font == NULL || changed())
		{
			const_cast<SDLLabelViewComponent*>(this)->update();
		}
		if (wrapWidth() <= 0)
		{
			_font->sizeText(text(), &lastNativeW, &lastNativeH);
		}
		else
		{
			auto surf = _font->surfaceBlendedWrapped(text(), (Drawing::SDL::Color)color(), wrapWidth());
			lastNativeH = surf->height();
			lastNativeW = surf->width();
			delete surf;
		}
	}
	
}