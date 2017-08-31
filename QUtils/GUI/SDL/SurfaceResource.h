#pragma once

#include "../Resource.h"

namespace QUtils::Drawing::SDL
{
	class Surface;
}


namespace QUtils::GUI::SDL
{
	class SDLSurfaceResourceLoader : public ResourceLoader<Drawing::SDL::Surface>
	{
		private:
		typedef ResourceLoader<Drawing::SDL::Surface> Base;
		
		protected:
		std::shared_ptr<Drawing::SDL::Surface> surface;
		
		Resource<Drawing::SDL::Surface>* load()
		{
			return new Resource<Drawing::SDL::Surface>(name, surface);
		}
		
		
		public:
		
		SDLSurfaceResourceLoader(const std::string name, Drawing::SDL::Surface* surface) : Base(name), surface(surface)
		{
			
		}
		
		
	};
}