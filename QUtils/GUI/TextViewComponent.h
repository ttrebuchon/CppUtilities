#pragma once

#include "ViewComponent.h"

#include "Color.h"


namespace QUtils::GUI
{
	class TextViewComponent : public ViewComponent
	{
		
		
		protected:
		
		
		
		public:
		TextViewComponent(const std::string id, bool touch);
		TextViewComponent(bool touch);
		TextViewComponent(const std::string id);
		TextViewComponent();
		virtual ~TextViewComponent();
		
		
		
		virtual std::string text() const = 0;
		virtual void text(const std::string) = 0;
		
		
		virtual const Color color() const = 0;
		inline void color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char alpha)
		{ color({r, g, b, alpha}); }
		virtual void color(const Color& v) = 0;
		
		virtual double wrapWidth() const = 0;
		virtual void wrapWidth(const double) = 0;
		
		virtual void calcRenderDimensions(int& width, int& height) override;
	};
}