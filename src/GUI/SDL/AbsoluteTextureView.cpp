#include <QUtils/GUI/SDL/AbsoluteTextureView.h>

#include <iostream>


namespace QUtils::GUI::SDL
{
	SDLAbsoluteTextureView::SDLAbsoluteTextureView(int w, int h) : SDLTextureView(w, h), children()
	{
		
	}
	
	SDLAbsoluteTextureView::~SDLAbsoluteTextureView()
	{
		
	}
	
	void SDLAbsoluteTextureView::updateTexture()
	{
		for (auto child : children)
		{
			std::get<0>(child)->update();
		}
		for (auto child : children)
		{
			std::get<0>(child)->render(this, std::get<1>(child)*texW, std::get<2>(child)*texH, texW, texH);
		}
	}
	
	
	void SDLAbsoluteTextureView::removeChildren()
	{
		children.clear();
		_changed = true;
	}
	
	bool SDLAbsoluteTextureView::changed() const
	{
		if (_changed)
		{
			return true;
		}
		
		for (const auto& child : children)
		{
			if (std::get<0>(child)->changed())
			{
				((SDLAbsoluteTextureView*)this)->_changed = true;
				return true;
			}
		}
		
		return false;
	}
	
	
	void SDLAbsoluteTextureView::addChild(ViewComponent* comp, double x, double y, double w, double h)
	{
		this->View::addChild(comp);
		children.emplace_back(comp, x, y);
		comp->width(w);
		comp->height(h);
		_changed = true;
	}
}