#include <QUtils/GUI/View.h>


namespace QUtils::GUI
{
	View::View(const std::string id, bool touch) : ViewComponent(id, touch)
	{
		
	}
	
	View::View(bool touch) : ViewComponent(touch)
	{
		
	}
	
	View::View(const std::string id) : ViewComponent(id)
	{
		
	}
	
	View::View() : ViewComponent()
	{
		
	}
	
	View::~View()
	{
		
	}
	
	void View::addChild(ViewComponent* comp)
	{
		comp->addToView(this);
	}
	
	void View::removeChild(ViewComponent* comp)
	{
		if (comp != NULL)
		{
			comp->removeFromView();
		}
	}
}