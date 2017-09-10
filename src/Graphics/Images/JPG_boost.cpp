#include <QUtils/Graphics/Images/GenericPixel.h>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>

using namespace boost::gil;

namespace QUtils
{
namespace Graphics
{
namespace Images
{
namespace Internal
{
	bool saveJPEG(const std::string filename, const GenericPixel* map, const unsigned int w, const unsigned int h)
	{
		rgb8_image_t img(w, h);
		
		rgb8_view_t v = view(img);
		
		GenericPixel thisPix;
		
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
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
	
	bool loadJPEG(const std::string filename, GenericPixel** mapPtr, unsigned int& w, unsigned int& h)
	{
		GenericPixel* map = NULL;
		try
		{
			
			
			rgb8_image_t img;
			
			jpeg_read_image(filename, img);
			
			rgb8_view_t v = view(img);
			
			w = v.width();
			h = v.height();
			
			map = new GenericPixel[w*h];
			
			GenericPixel thisPix;
			
			for (int y = 0; y < h; y++)
			{
				for (int x = 0; x < w; x++)
				{
					
					auto& pix = v(x, y);
					thisPix = {pix[0], pix[1], pix[2]};
					
					map[w*y + x] = thisPix;
				}
			}
			*mapPtr = map;
		}
		catch (...)
		{
			if (map != NULL)
			{
				delete[] map;
				map = NULL;
			}
			w = h = 0;
			return false;
		}
		return true;
	}
}
}
}
}