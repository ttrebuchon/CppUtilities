#include <Raytracer/Camera.h>
#include <Exception/NullPointer.h>

namespace Util
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
		pixel_t scaled(npix.R, npix.G, npix.B);
		
		img->pix[dims[0]*y + x] = scaled;
	}
	
	pixel_t Camera::getPixel(int x, int y) const
	{
		return img->pix[dims[0]*y + x];
	}
	
	
	
	
	vector_t Camera::dir(int x, int y) const
	{
		vector_t v;
		v.x = ((double)x / (this->x() - 1))*viewpointDims[0];
		v.y = ((double)y / (this->y() - 1))*viewpointDims[1];
		v.z = 0;
		return (v - viewpoint).unit();
	}
	
	void Camera::setImgDims(const int x, const int y)
	{
		dims[0] = x;
		dims[1] = y;
	}
	
	void Camera::setImg(image_t* img)
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