#pragma once

#include "../ViewComponent.h"

namespace QUtils::GUI::SDL
{
	class SDLViewComponent : public virtual ViewComponent
	{
		private:
		
		protected:
		
		public:
		SDLViewComponent(const std::string id, bool touch);
		SDLViewComponent(bool touch);
		SDLViewComponent(const std::string id);
		SDLViewComponent();
		virtual ~SDLViewComponent();
		
	};
}