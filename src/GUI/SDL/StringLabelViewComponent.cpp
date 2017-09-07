#include <QUtils/GUI/SDL/StringLabelViewComponent.h>
#include <QUtils/GUI/Errors.h>


namespace QUtils::GUI::SDL
{
	SDLStringLabelViewComponent::SDLStringLabelViewComponent(const std::string id, bool touch, const std::string text, const std::string font, unsigned int fontSize) : SDLLabelViewComponent(id, touch, font, fontSize), _text(text)
	{
		
	}
	
	SDLStringLabelViewComponent::SDLStringLabelViewComponent(bool touch, const std::string text, const std::string font, unsigned int fontSize) : SDLLabelViewComponent(touch, font, fontSize), _text(text)
	{
		
	}
	
	SDLStringLabelViewComponent::SDLStringLabelViewComponent(const std::string id, const std::string text, const std::string font, unsigned int fontSize) : SDLLabelViewComponent(id, font, fontSize), _text(text)
	{
		
	}
	SDLStringLabelViewComponent::SDLStringLabelViewComponent(const std::string text, const std::string font, unsigned int fontSize) : SDLLabelViewComponent(font, fontSize), _text(text)
	{
		
	}
	
	SDLStringLabelViewComponent::~SDLStringLabelViewComponent()
	{
		
	}
		
	std::string SDLStringLabelViewComponent::text() const
	{
		return _text;
	}
	
	void SDLStringLabelViewComponent::text(const std::string value)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		_text = value;
		_changed = true;
	}
	
}