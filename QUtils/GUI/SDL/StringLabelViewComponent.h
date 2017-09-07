#pragma once

#include "LabelViewComponent.h"

namespace QUtils::GUI::SDL
{
	class SDLStringLabelViewComponent : public SDLLabelViewComponent
	{
		
		protected:
		std::string _text;
		
		public:
		SDLStringLabelViewComponent(const std::string id, bool touch, const std::string text, const std::string font, unsigned int fontSize);
		SDLStringLabelViewComponent(bool touch, const std::string text, const std::string font, unsigned int fontSize);
		SDLStringLabelViewComponent(const std::string id, const std::string text, const std::string font, unsigned int fontSize);
		SDLStringLabelViewComponent(const std::string text, const std::string font, unsigned int fontSize);
		virtual ~SDLStringLabelViewComponent();
		
		virtual std::string text() const override;
		virtual void text(const std::string) override;
		
	};
}