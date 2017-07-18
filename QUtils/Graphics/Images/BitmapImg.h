#pragma once

#include "../Image.h"

namespace QUtils
{
namespace Graphics
{
	template <class Pixel>
	class BitmapImg : public Image<Pixel>
	{
		protected:
		const unsigned int w;
		const unsigned int h;
		Pixel* const array;
		
		public:
		BitmapImg(const unsigned int x, const unsigned int y) : w(x), h(y), array(new Pixel[x*y])
		{
			
		}
		virtual ~BitmapImg()
		{
			delete[] array;
		}
		
		operator Pixel*() const
		{
			return array;
		}
		
		virtual void setPixel(const unsigned int x, const unsigned int y, const unsigned char R, const unsigned char G, const unsigned char B) override
		{
			int row = h - y - 1;
			int col = x;
			auto pix = &array[w*row + col];
			pix->R = R;
			pix->G = G;
			pix->B = B;
			
		}
		
		virtual Pixel getPixel(const unsigned int x, const unsigned int y) const override
		{
			int row = h - y - 1;
			int col = x;
			auto pix = &array[w*row + col];
			/*pixel_t gPix;
			gPix.R = pix->R;
			gPix.G = pix->G;
			gPix.B = pix->B;
			return gPix;*/
			return *pix;
		}
		
		virtual unsigned int width() const override { return w; }
		virtual unsigned int height() const override { return h; }
		
		virtual BitmapImg<Pixel>* clone() const override
		{
			BitmapImg<Pixel>* newImg = new BitmapImg<Pixel>(w, h);
			for (int y = 0; y < h; ++y)
			{
				for (int x = 0; x < w; ++x)
				{
					auto p = getPixel(x, y);
					newImg->Image<Pixel>::setPixel(x, y, p);
				}
			}
			return newImg;
		}
	};
}
}