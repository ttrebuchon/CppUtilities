#include <QUtils/Graphics/Images/GenericImage.h>

namespace QUtils
{
namespace Graphics
{
namespace Images
{
	GenericImage::~GenericImage()
	{
		delete[] map;
	}
	
	
	void GenericImage::setPixel(const unsigned int x, const unsigned int y, const GenericPixel nPix)
	{
		auto row = h - y - 1;
		auto col = x;
		auto pix = &map[w*row + col];
		*pix = nPix;
	}
	
	GenericPixel GenericImage::getPixel(const unsigned int x, const unsigned int y) const
	{
		auto row = h - y - 1;
		auto col = x;
		return map[w*row + col];
	}
}
}
}