#include "Image.h"
#include <cmath>


namespace QUtils
{
namespace Graphics
{
	template <class Pixel>
	void Image<Pixel>::BWConvert()
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
	
	template <class Pixel>
	void Image<Pixel>::imgDiff(const Image* img)
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
				
				Pixel diff;
				diff.R = (int)r;
				diff.G = (int)g;
				diff.B = (int)b;
				
				setPixel(x, y, diff);
			}
		}
	}
	
	template <class Pixel>
	void Image<Pixel>::imgAbsDiff(const Image* img)
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
				
				r = fabs(r);
				g = fabs(g);
				b = fabs(b);
				
				//New Range:
				//[0, 255]
				
				Pixel diff;
				diff.R = (int)r;
				diff.G = (int)g;
				diff.B = (int)b;
				
				setPixel(x, y, diff);
			}
		}
	}
	
	
	
	
	template <class Pixel>
	int*** Image<Pixel>::diff(const Image* img) const
	{
		int*** mat = new int**[width()];
		for (int y = 0; y < height(); ++y)
		{
			mat[y] = new int*[width()];
			for (int x = 0; x < width(); ++x)
			{
				mat[y][x] = new int[3];
				
				for (int z = 0; z < 3; ++z)
				{
					mat[y][x][z] = 0;
				}
			}
		}
		
		for (int y = height()-1; y >= 0; --y)
		{
			for (int x = 0; x < width(); ++x)
			{
				Pixel p = getPixel(x, y);
				mat[y][x][0] = p.R;
				mat[y][x][1] = p.G;
				mat[y][x][2] = p.B;
				
				p = img->getPixel(x, y);
				
				mat[y][x][0] -= p.R;
				mat[y][x][1] -= p.G;
				mat[y][x][2] -= p.B;
			}
		}
		
		
		
		return mat;
	}
	
	template <class Pixel>
	int*** Image<Pixel>::absDiff(const Image* img) const
	{
		int*** mat = new int**[width()];
		for (int y = 0; y < height(); ++y)
		{
			mat[y] = new int*[width()];
			for (int x = 0; x < width(); ++x)
			{
				mat[y][x] = new int[3];
				
				for (int z = 0; z < 3; ++z)
				{
					mat[y][x][z] = 0;
				}
			}
		}
		
		for (int y = height()-1; y >= 0; --y)
		{
			for (int x = 0; x < width(); ++x)
			{
				Pixel p = getPixel(x, y);
				mat[y][x][0] = p.R;
				mat[y][x][1] = p.G;
				mat[y][x][2] = p.B;
				
				p = img->getPixel(x, y);
				
				mat[y][x][0] -= p.R;
				mat[y][x][1] -= p.G;
				mat[y][x][2] -= p.B;
				
				mat[y][x][0] = abs(mat[y][x][0]);
				mat[y][x][1] = abs(mat[y][x][1]);
				mat[y][x][2] = abs(mat[y][x][2]);
			}
		}
		
		
		
		return mat;
	}
}
}