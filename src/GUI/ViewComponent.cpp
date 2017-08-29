#include <QUtils/GUI/ViewComponent.h>
#include <QUtils/GUI/Errors.h>

namespace QUtils::GUI
{
	ViewComponent::ViewComponent() : _parent(nullptr), parent(_parent)
	{
		
	}
	
	ViewComponent::~ViewComponent()
	{
		
	}
	
	
	void ViewComponent::addToView(View* view)
	{
		if (_parent != NULL && _parent != view)
		{
			throw ParentChildException().Msg("This component is already a child of a different view");
		}
		_parent = view;
	}
	
	void ViewComponent::removeFromView()
	{
		if (_parent == NULL)
		{
			throw ParentChildException().Msg("This component cannot be removed from it's parent view because it has none");
		}
		_parent = NULL;
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