#pragma once

#include "../ViewComponent.h"



#include <QUtils/Drawing/SDL/Color.h>
#include "FontResource.h"

#include <string>

namespace QUtils::Drawing::SDL
{
	class Font;
	class Texture;
}

namespace QUtils::GUI::SDL
{
	class SDLLabelViewComponent : public ViewComponent
	{
		private:
		int lastW, lastH;
		
		protected:
		std::string _text;
		std::shared_ptr<Drawing::SDL::Font> _font;
		Drawing::SDL::Texture* texture;
		Drawing::SDL::Color _color;
		int _fontSize;
		std::string _fontName;
		
		public:
		SDLLabelViewComponent(const std::string id, bool touch, const std::string text, const std::string font, unsigned int fontSize);
		SDLLabelViewComponent(bool touch, const std::string text, const std::string font, unsigned int fontSize);
		SDLLabelViewComponent(const std::string id, const std::string text, const std::string font, unsigned int fontSize);
		SDLLabelViewComponent(const std::string text, const std::string font, unsigned int fontSize);
		virtual ~SDLLabelViewComponent();
		
		virtual std::string text() const;
		virtual void text(const std::string);
		
		virtual void update() override;
		virtual void render(RenderTarget*, int, int, int, int) override;
		virtual int nativeWidth() const override;
		virtual int nativeHeight() const override;
		
		virtual const Drawing::SDL::Color& color() const
		{ return _color; }
		virtual void color(const Drawing::SDL::Color v) {_color = v; _changed = true;}
	};
}