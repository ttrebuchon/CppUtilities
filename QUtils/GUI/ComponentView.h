#pragma once
#include "View.h"


namespace QUtils::GUI
{
	class ComponentView : public View
	{
		protected:
		ViewComponent* component;
		
		public:
		ComponentView(ViewComponent*);
		virtual ~ComponentView();
		
		
		virtual void update() override;
		
		virtual void removeChildren() override;
	};
}