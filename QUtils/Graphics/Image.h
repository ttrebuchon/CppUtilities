#pragma once
#include "IImage.h"
#include <QUtils/Exception/Exception.h>

namespace QUtils
{
namespace Graphics
{
	QUTILS_CUSTOM_EXCEPTION(ImageDimensionMismatchException,);
	
	template <class Pixel>
	class Image : public IImage
	{
		private:
		
		protected:
		
		public:
		/*Image() {}*/
		virtual ~Image() {}
		
		virtual void setPixel(const unsigned int x, const unsigned int y, const Pixel p)
		{
			IImage::setPixel<Pixel>(x, y, p);
		}
		
		virtual void setPixel(const unsigned int x, const unsigned int y, const unsigned char R, const unsigned char G, const unsigned char B) override
		{
			Pixel p;
			p.R = R;
			p.G = G;
			p.B = B;
			setPixel(x, y, p);
		}
		
		
		virtual void getPixel(const unsigned int x, const unsigned int y, unsigned char& R, unsigned char& G, unsigned char& B) const override
		{
			Pixel p = getPixel(x, y);
			R = p.R;
			G = p.G;
			B = p.B;
		}
		
		virtual Pixel getPixel(const unsigned int x, const unsigned int y) const = 0;
		
		virtual unsigned int width() const = 0;
		virtual unsigned int height() const = 0;
		
		virtual void BWConvert();
		virtual void imgDiff(const Image*);
		virtual void imgAbsDiff(const Image*);
		
		virtual Image* clone() const = 0;
		virtual int*** diff(const Image*) const;
		virtual int*** absDiff(const Image*) const;
	};
}
}

#include "Image.hpp"