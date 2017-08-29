#pragma once

#include "ViewComponent.h"

namespace QUtils::Drawing::SDL
{
	class Texture;
}

namespace QUtils::GUI::SDL
{
	class SDLTextureViewComponent : public SDLViewComponent
	{
		protected:
		Drawing::SDL::Texture* texture;
		public:
		
		SDLTextureViewComponent(Drawing::SDL::Texture*);
		virtual ~SDLTextureViewComponent();
		virtual void update()
		{}
		
	};
}