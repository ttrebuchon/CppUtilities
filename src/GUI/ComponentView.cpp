#include <QUtils/GUI/ComponentView.h>
#include <QUtils/GUI/Errors.h>


namespace QUtils::GUI
{
	ComponentView::ComponentView(ViewComponent* comp) : View(), component(comp)
	{
		if (component == nullptr)
		{
			throw ParentChildException().Msg("Cannot instantiate ComponentView with NULL child");
		}
		this->addChild(comp);
	}
	
	ComponentView::~ComponentView()
	{
		
	}
	
	void ComponentView::update()
	{
		component->update();
	}
	
	void ComponentView::removeChildren()
	{
		if (component == nullptr)
		{
			throw ParentChildException().Msg("Cannot remove child from ComponentView because view has no child");
		}
	}
}