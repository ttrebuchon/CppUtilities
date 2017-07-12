#pragma once

#include "Image.h"

namespace QUtils
{
namespace Raytracer
{
	template <class Pixel>
	class BitmapImg : public Image
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
		
		virtual void setPixel(const unsigned int x, const unsigned int y, const pixel_t nPix) override
		{
			int row = h - y - 1;
			int col = x;
			auto pix = &array[w*row + col];
			pix->R = nPix.R;
			pix->G = nPix.G;
			pix->B = nPix.B;
			
		}
		
		virtual pixel_t getPixel(const unsigned int x, const unsigned int y) const override
		{
			int row = h - y - 1;
			int col = x;
			auto pix = &array[w*row + col];
			pixel_t gPix;
			gPix.R = pix->R;
			gPix.G = pix->G;
			gPix.B = pix->B;
			return gPix;
		}
		
		virtual unsigned int width() const override { return w; }
		virtual unsigned int height() const override { return h; }
	};
}
}