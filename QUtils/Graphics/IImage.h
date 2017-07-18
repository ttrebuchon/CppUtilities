#pragma once
#include <QUtils/Exception/Exception.h>

namespace QUtils
{
namespace Graphics
{
	//QUTILS_CUSTOM_EXCEPTION(ImageDimensionMismatchException,);
	class IImage
	{
		private:
		
		protected:
		
		public:
		virtual ~IImage() {}
		
		virtual void setPixel(const unsigned int x, const unsigned int y, const unsigned char R, const unsigned char G, const unsigned char B) = 0;
		
		template <class Pixel>
		void setPixel(const unsigned int x, const unsigned int y, const Pixel p)
		{
			setPixel(x, y, p.R, p.G, p.B);
		}
		
		virtual void getPixel(const unsigned int x, const unsigned int y, unsigned char& R, unsigned char& G, unsigned char& B) const = 0;
		
		virtual unsigned int width() const = 0;
		virtual unsigned int height() const = 0;
		
		/*virtual void BWConvert();
		virtual void diff(const Image*);*/
		
		virtual IImage* clone() const = 0;
	};
}
}