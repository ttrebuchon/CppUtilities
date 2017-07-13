#include <QUtils/Raytracer/Images/JPG.h>
#include <QUtils/Exception/NotImplemented.h>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>

using namespace boost::gil;

namespace QUtils
{
namespace Raytracer
{
namespace Images
{
	JPGImage::~JPGImage()
	{
		
	}
	
	bool JPGImage::save(const std::string filename) const
	{
		rgb8_image_t img(this->w, this->h);
		
		rgb8_view_t v = view(img);
		
		pixel_t thisPix;
		
		for (int y = 0; y < this->h; y++)
		{
			for (int x = 0; x < this->w; x++)
			{
				thisPix = map[w*y + x];
				auto& pix = v(x, y);
				
				pix[0] = thisPix.R;
				pix[1] = thisPix.G;
				pix[2] = thisPix.B;
			}
		}
		try
		{
			jpeg_write_view(filename, v);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	
	bool JPGImage::load(const std::string filename)
	{
		throw NotImp();
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