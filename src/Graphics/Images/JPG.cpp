#include <QUtils/Graphics/Images/JPG.h>

namespace QUtils
{
namespace Graphics
{
namespace Images
{
	namespace Internal
	{
		bool saveJPEG(const std::string filename, const GenericPixel* map, const unsigned int w, const unsigned int h);
		bool loadJPEG(const std::string filename, GenericPixel** mapPtr, unsigned int& w, unsigned int& h);
	}
	
	
	JPGImage::~JPGImage()
	{
		
	}
	
	bool JPGImage::save(const std::string filename) const
	{
		return Internal::saveJPEG(filename, map, this->w, this->h);
	}
	
	bool JPGImage::load(const std::string filename)
	{
		if (map != NULL)
		{
			delete[] map;
			map = NULL;
		}
		return Internal::loadJPEG(filename, &map, w, h);
	}
	
	JPGImage* JPGImage::clone() const
	{
		auto w = width();
		auto h = height();
		auto newImg = new JPGImage(w, h);
		
		for (auto it = 0; it < w*h; ++it)
		{
			newImg->map[it] = map[it];
		}
		
		return newImg;
	}
}
}
}