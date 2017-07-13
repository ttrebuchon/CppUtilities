#include <QUtils/Raytracer/Camera.h>
#include <QUtils/Exception/NullPointer.h>
#include <QUtils/Raytracer/Image.h>

namespace QUtils
{
namespace Raytracer
{
	Camera::Camera(std::string name, double w, double h, vector_t viewpoint) : RaytracerItem(name), dims(),  viewpointDims(), viewpoint(viewpoint), img(NULL)
	{
		viewpointDims[0] = w;
		viewpointDims[1] = h;
	}
	
	void Camera::setPixel(int x, int y, const dpixel_t pix)
	{
		if (img == NULL)
		{
			throw NullPointerException();
		}
		auto npix = pixScale(255, pix);
		npix.R += 0.5;
		npix.G += 0.5;
		npix.B += 0.5;
		npix = clamp(npix);
		pixel_t scaled(npix.R, npix.G, npix.B);
		
		this->img->setPixel(x, y, scaled);
		
		/*int row = dims[1] - y - 1;
		int col = x;
		img[dims[0]*row + col] = scaled;*/
		
		
	}
	
	pixel_t Camera::getPixel(int x, int y) const
	{
		/*int row = dims[1] - y - 1;
		int col = x;
		return img[dims[0]*row + col];*/
		return img->getPixel(x, y);
	}
	
	
	void jitter(double& in)
	{
		double r = random();
		r /= 0x7fffffff;
		r -= 0.5;
		in += r;
	}
	
	vector_t Camera::dir(int x, int y, bool AA) const
	{
		double dx = x;
		double dy = y;
		
		
		if (AA)
		{
			jitter(dx);
			jitter(dy);
		}
		
		
		vector_t v;
		v.x = (dx / (this->x() - 1))*viewpointDims[0];
		v.y = (dy / (this->y() - 1))*viewpointDims[1];
		v.z = 0;
		return (v - viewpoint).unit();
	}
	
	void Camera::setImgDims(const int x, const int y)
	{
		dims[0] = x;
		dims[1] = y;
	}
	
	void Camera::setImg(Image* img)
	{
		this->img = img;
	}
	
	std::string Camera::toString() const
	{
		std::stringstream ss;
		ss << "Camera: " << name();
		ss << "\nPosition: " << viewpoint;
		ss << "\nWorld Dims: (" << viewpointDims[0] << ", " << viewpointDims[1] << ")\n";
		ss << "Image Dims: " << dims[0] << ", " << dims[1] << ")";
		
		return ss.str();
	}
	
	
}
}