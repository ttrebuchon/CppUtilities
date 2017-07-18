#pragma once
#include "../Image.h"
#include "GenericPixel.h"


namespace QUtils
{
namespace Graphics
{
namespace Images
{
	class GenericImage : public Image<GenericPixel>
	{
		protected:
		unsigned int w;
		unsigned int h;
		GenericPixel* map;
		
		
		public:
		GenericImage(const unsigned int w, const unsigned int h) : Image(), w(w), h(h), map(new GenericPixel[h*w])
		{}
		
		virtual ~GenericImage();
		
		virtual void setPixel(const unsigned int x, const unsigned int y, const GenericPixel) override;
		
		virtual GenericPixel getPixel(const unsigned int x, const unsigned int y) const override;
		
		virtual unsigned int width() const override { return w; }
		virtual unsigned int height() const override { return h; }
		
		virtual bool save(const std::string filename) const = 0;
		
		virtual bool load(const std::string filename) = 0;
		
		virtual Image* clone() const = 0;
	};
}
}
}