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
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (comp != NULL)
		{
			comp->addToView(this);
		}
	}
	
	void View::removeChild(ViewComponent* comp)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (comp != NULL)
		{
			comp->removeFromView();
		}
	}
}