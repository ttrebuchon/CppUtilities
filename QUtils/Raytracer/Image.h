#pragma once
#include "Types.h"

namespace QUtils
{
namespace Raytracer
{
	class Image
	{
		private:
		
		protected:
		
		public:
		Image() {}
		virtual ~Image() {}
		
		virtual void setPixel(const unsigned int x, const unsigned int y, const pixel_t) = 0;
		
		virtual pixel_t getPixel(const unsigned int x, const unsigned int y) const = 0;
		
		virtual unsigned int width() const = 0;
		virtual unsigned int height() const = 0;
	};
}
}