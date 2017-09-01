#include <QUtils/GUI/ViewComponent.h>
#include <QUtils/GUI/View.h>
#include <QUtils/GUI/Errors.h>
#include <algorithm>

namespace QUtils::GUI
{
	int ViewComponent::idCounter = 1;
	
	
	ViewComponent::ViewComponent(const std::string id, bool touch) : Clickable(touch), _id(id), _parent(nullptr), _window(nullptr), _w(1), _h(1), _opacity(1), _changed(false), id(_id), parent(_parent), window(_window)
	{
		
	}
	
	ViewComponent::ViewComponent(bool touch) : ViewComponent(std::to_string(idCounter++), touch)
	{
		
	}
	
	ViewComponent::ViewComponent(const std::string id) : Clickable(), _id(id), _parent(nullptr), _window(nullptr), _w(1), _h(1), _opacity(1), _changed(false), id(_id), parent(_parent), window(_window)
	{
		
	}
	
	ViewComponent::ViewComponent() : ViewComponent(std::to_string(idCounter++))
	{
		
	}
	
	ViewComponent::~ViewComponent()
	{
		
	}
	
	
	void ViewComponent::addToView(View* view)
	{
		if (_parent != NULL/* && _parent != view*/)
		{
			throw ParentChildException().Msg("This component is already a child of a view");
		}
		_parent = view;
		setWindow(view->window);
		_changed = true;
	}
	
	void ViewComponent::removeFromView()
	{
		if (_parent == NULL)
		{
			throw ParentChildException().Msg("This component cannot be removed from it's parent view because it has none");
		}
		_parent = NULL;
		setWindow(NULL);
		_changed = true;
	}
	
	void ViewComponent::calcRenderDimensions(int& w, int& h)
	{
		auto tmpW = width();
		auto tmpH = height();
		
		if (tmpW == -2 && tmpH == -2)
		{
			tmpW = tmpH = -1;
		}
		
		if (tmpW >= 0)
		{
			w = static_cast<int>(tmpW*w);
		}
		else if (tmpW == -1)
		{
			w = nativeWidth();
		}
		
		
		if (tmpH >= 0)
		{
			h = static_cast<int>(tmpH*h);
		}
		else if (tmpH == -1)
		{
			h = nativeHeight();
		}
		
		if (tmpW == -2)
		{
			w = (static_cast<double>(nativeWidth())/nativeHeight())*h;
		}
		
		if (tmpH == -2)
		{
			h = (static_cast<double>(nativeHeight())/nativeWidth())*w;
		}
		
		
	}
	
	
	double ViewComponent::width() const
	{
		return _w;
	}
	
	double ViewComponent::height() const
	{
		return _h;
	}
	
	
	void ViewComponent::width(double w)
	{
		_w = w;
		_changed = true;
	}
	
	void ViewComponent::height(double h)
	{
		_h = h;
		_changed = true;
	}
	
	double ViewComponent::opacity() const
	{
		return std::max<double>(std::min<double>(1, _opacity), 0);
	}
	
	void ViewComponent::opacity(double value)
	{
		_opacity = std::max<double>(std::min<double>(1, value), 0);
		_changed = true;
	}
}