#pragma once

#include "ViewComponent.h"
#include "../View.h"


namespace QUtils::GUI::SDL
{
	class SDLView : public virtual View, public virtual SDLViewComponent
	{
		private:
		
		protected:
		
		public:
		SDLView(const std::string id, bool touch);
		SDLView(bool touch);
		SDLView(const std::string id);
		SDLView();
		virtual ~SDLView();
		
	};
}