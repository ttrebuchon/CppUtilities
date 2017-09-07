#pragma once

#include "../TextViewComponent.h"

#include "FontResource.h"

#include <string>

namespace QUtils::Drawing::SDL
{
	class Font;
	class Texture;
}

namespace QUtils::GUI::SDL
{
	class SDLLabelViewComponent : public TextViewComponent
	{
		private:
		int lastW, lastH;
		
		protected:
		std::string _text;
		std::shared_ptr<Drawing::SDL::Font> _font;
		Drawing::SDL::Texture* texture;
		Color _color;
		int _fontSize;
		std::string _fontName;
		double _wrapWidth;
		
		
		public:
		SDLLabelViewComponent(const std::string id, bool touch, const std::string text, const std::string font, unsigned int fontSize);
		SDLLabelViewComponent(bool touch, const std::string text, const std::string font, unsigned int fontSize);
		SDLLabelViewComponent(const std::string id, const std::string text, const std::string font, unsigned int fontSize);
		SDLLabelViewComponent(const std::string text, const std::string font, unsigned int fontSize);
		virtual ~SDLLabelViewComponent();
		
		virtual std::string text() const override;
		virtual void text(const std::string) override;
		
		virtual void update() override;
		virtual void render(RenderTarget*, int, int, int, int) override;
		
		virtual int nativeWidth() const override;
		virtual int nativeHeight() const override;
		
		virtual double wrapWidth() const override;
		virtual void wrapWidth(const double) override;
		
		virtual const Color color() const override
		{ return _color; }
		virtual void color(const Color& v) override
		{_color = v; _changed = true;}
		
		virtual void calcRelativeDimensions(double& width, double& height) const override;
	};
}