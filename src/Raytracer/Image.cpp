#include <QUtils/Raytracer/Image.h>


namespace QUtils
{
namespace Raytracer
{
	void Image::BWConvert()
	{
		auto h = height();
		auto w = width();
		
		long long unsigned int total = 0;
		
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				auto p = getPixel(x, y);
				int tmp = (p.R + p.G + p.B)/3;
				total += tmp;
				p.R = tmp;
				p.G = tmp;
				p.B = tmp;
				setPixel(x, y, p);
			}
		}
	}
	
	void Image::diff(const Image* img)
	{
		auto h = height();
		auto w = width();
		
		if (img->width() != w || img->height() != h)
		{
			throw ImageDimensionMismatchException().Msg("Images must have the same dimensions");
		}
		
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				
				auto p1 = getPixel(x, y);
				auto p2 = img->getPixel(x, y);
				
				double r = static_cast<double>(p1.R) - p2.R;
				double g = static_cast<double>(p1.G) - p2.G;
				double b = static_cast<double>(p1.B) - p2.B;
				
				//Range for r, g, and b:
				//[-255, 255]
				
				r /= 2;
				g /= 2;
				b /= 2;
				
				//New Range:
				//[-127.5, 127.5]
				
				r += 128;
				g += 128;
				b += 128;
				
				//New Range:
				//[0.5, 255.5]
				
				//When casted to int:
				//[0, 255]
				
				pixel_t diff((int)r, (int)g, (int)b);
				
				setPixel(x, y, diff);
			}
		}
	}
}
}