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
		auto h = height();
		auto w = width();
		if (texW <= 100 || texH <= 100)
		{
			throw std::exception();
		}
		for (auto child : children)
		{
			std::get<0>(child)->render(this, std::get<1>(child)*texW, std::get<2>(child)*texH, std::get<3>(child)*texW, std::get<4>(child)*texH);
			std::cout << "(" << std::get<1>(child)*texW << ", " << std::get<2>(child)*texH << ", " << std::get<3>(child)*texW << ", " << std::get<4>(child)*texH << ")\n";
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
		children.emplace_back(comp, x, y, w, h);
		_changed = true;
	}
}