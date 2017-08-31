#include <QUtils/GUI/View.h>


namespace QUtils::GUI
{
	View::View()
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
		comp->removeFromView();
	}
}