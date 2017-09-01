#include <QUtils/GUI/SDL/AbsoluteTextureView.h>
#include <QUtils/GUI/Errors.h>

#include <iostream>


namespace QUtils::GUI::SDL
{
	SDLAbsoluteTextureView::SDLAbsoluteTextureView(const std::string id, bool touch, int w, int h) : SDLTextureView(id, touch, w, h), children()
	{
		registerEvents();
	}
	
	SDLAbsoluteTextureView::SDLAbsoluteTextureView(bool touch, int w, int h) : SDLTextureView(touch, w, h), children()
	{
		registerEvents();
	}
	
	SDLAbsoluteTextureView::SDLAbsoluteTextureView(const std::string id, int w, int h) : SDLTextureView(id, w, h), children()
	{
		registerEvents();
	}
	
	SDLAbsoluteTextureView::SDLAbsoluteTextureView(int w, int h) : SDLTextureView(w, h), children()
	{
		registerEvents();
	}
	
	SDLAbsoluteTextureView::~SDLAbsoluteTextureView()
	{
		removeChildren();
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
	
	void SDLAbsoluteTextureView::removeChild(ViewComponent* comp)
	{
		this->View::removeChild(comp);
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			if (std::get<0>(*it) == comp)
			{
				children.erase(it);
				_changed = true;
				return;
			}
		}
		
		throw ParentChildException().Msg("Child " + comp->id + " could not be found under parent " + this->id).Line(__LINE__).Function(__func__).File(__FILE__);
	}
	
	
	
	void SDLAbsoluteTextureView::registerEvents()
	{
		onFingerDown += [&](auto win, auto timestamp, auto touchId, auto fingerId, auto x, auto y, auto dx, auto dy, auto pressure)
		{
			
			auto rdx = static_cast<double>(dx)/texW;
			auto rdy = static_cast<double>(dy)/texH;
			
			for (int i = static_cast<int>(children.size())-1; i >= 0; --i)
			{
				const auto& child = std::get<0>(children.at(i));
				double cw = child->width();
				double ch = child->height();
				
				if (ch == -2 && cw == -2)
				{
					ch = cw = -1;
				}
				
				if (cw == -1)
				{
					cw = child->nativeWidth();
				}
				if (ch == -1)
				{
					ch = child->nativeHeight();
				}
				
				if (cw == -2)
				{
					cw = static_cast<double>(child->nativeWidth())/child->nativeHeight()*ch;
				}
				if (ch == -2)
				{
					ch = static_cast<double>(child->nativeHeight())/child->nativeWidth()*cw;
				}
				
				if (x >= std::get<1>(children[i]) && y >= std::get<2>(children[i]))
				{
					if (x <= std::get<1>(children[i]) + cw && y <= std::get<2>(children[i]) + ch)
					{
						child->onFingerDown(win, timestamp, touchId, fingerId, x - std::get<1>(children[i]), y - std::get<2>(children[i]), rdx, rdy, pressure);
						return;
					}
				}
			}
		};
	}
}