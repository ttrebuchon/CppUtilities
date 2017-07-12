#include <QUtils/Raytracer/Images/GenericImage.h>

namespace QUtils
{
namespace Raytracer
{
namespace Images
{
	GenericImage::~GenericImage()
	{
		delete[] map;
	}
	
	
	void GenericImage::setPixel(const unsigned int x, const unsigned int y, const pixel_t nPix)
	{
		auto row = h - y - 1;
		auto col = x;
		auto pix = &map[w*row + col];
		*pix = nPix;
	}
	
	pixel_t GenericImage::getPixel(const unsigned int x, const unsigned int y) const
	{
		auto row = h - y - 1;
		auto col = x;
		return map[w*row + col];
	}
}
}
}