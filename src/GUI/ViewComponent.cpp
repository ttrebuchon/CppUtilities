#include <QUtils/GUI/ViewComponent.h>
#include <QUtils/GUI/View.h>
#include <QUtils/GUI/Errors.h>

namespace QUtils::GUI
{
	ViewComponent::ViewComponent() : _parent(nullptr), _window(nullptr), _w(1), _h(1), _changed(false), parent(_parent), window(_window)
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
	}
	
	void ViewComponent::removeFromView()
	{
		if (_parent == NULL)
		{
			throw ParentChildException().Msg("This component cannot be removed from it's parent view because it has none");
		}
		_parent = NULL;
		setWindow(NULL);
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
	}
	
	void ViewComponent::height(double h)
	{
		_h = h;
	}
}