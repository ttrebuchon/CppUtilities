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
		std::lock_guard<std::recursive_mutex> lock(this_m);
		removeChildren();
	}
	
	void SDLAbsoluteTextureView::updateTexture()
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
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
		std::lock_guard<std::recursive_mutex> lock(this_m);
		while (children.size() > 0)
		{
			removeChild(std::get<0>(children.front()));
			
		}
		_changed = true;
	}
	
	bool SDLAbsoluteTextureView::changed() const
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
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
		std::lock_guard<std::recursive_mutex> lock(this_m);
		this->View::addChild(comp);
		children.emplace_back(comp, x, y);
		comp->width(w);
		comp->height(h);
		_changed = true;
	}
	
	void SDLAbsoluteTextureView::removeChild(ViewComponent* comp)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
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
		onFingerDown += [&](auto win, auto timestamp, auto touchId, auto fingerId, auto x, auto y, auto pressure)
		{
			std::lock_guard<std::recursive_mutex> lock(this_m);
			for (int i = static_cast<int>(children.size())-1; i >= 0; --i)
			{
				const auto& child = std::get<0>(children.at(i));
				
				double cw = texW;
				double ch = texH;
				child->calcRelativeDims(cw, ch);
				
				if (x >= std::get<1>(children[i]) && y >= std::get<2>(children[i]))
				{
					if (x <= std::get<1>(children[i]) + cw && y <= std::get<2>(children[i]) + ch)
					{
						child->onFingerDown(win, timestamp, touchId, fingerId, x - std::get<1>(children[i]), y - std::get<2>(children[i]), pressure);
						return;
					}
				}
			}
		};
		
		
		onFingerUp += [&](auto win, auto timestamp, auto touchId, auto fingerId, auto x, auto y, auto pressure)
		{
			std::lock_guard<std::recursive_mutex> lock(this_m);
			
			for (int i = static_cast<int>(children.size())-1; i >= 0; --i)
			{
				const auto& child = std::get<0>(children.at(i));
				
				double cw = texW;
				double ch = texH;
				child->calcRelativeDims(cw, ch);
				
				if (x >= std::get<1>(children[i]) && y >= std::get<2>(children[i]))
				{
					if (x <= std::get<1>(children[i]) + cw && y <= std::get<2>(children[i]) + ch)
					{
						child->onFingerUp(win, timestamp, touchId, fingerId, x - std::get<1>(children[i]), y - std::get<2>(children[i]), pressure);
						return;
					}
				}
			}
		};
		
		onFingerMotion += [&](auto win, auto timestamp, auto touchId, auto fingerId, auto x, auto y, auto dx, auto dy, double rdx, double rdy, auto pressure)
		{
			std::lock_guard<std::recursive_mutex> lock(this_m);
			for (int i = static_cast<int>(children.size())-1; i >= 0; --i)
			{
				const auto& child = std::get<0>(children.at(i));
				
				double cw = texW;
				double ch = texH;
				child->calcRelativeDims(cw, ch);
				
				if (x >= std::get<1>(children[i]) && y >= std::get<2>(children[i]))
				{
					if (x <= std::get<1>(children[i]) + cw && y <= std::get<2>(children[i]) + ch)
					{
						child->onFingerMotion(win, timestamp, touchId, fingerId, x - std::get<1>(children[i]), y - std::get<2>(children[i]), dx, dy, rdx/cw, rdy/ch, pressure);
						return;
					}
				}
			}
		};
	}
}