#pragma once
#include "Types.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <memory>

#include <QUtils/Exception/Exception.h>

namespace QUtils
{
namespace Graphics
{
	template <class Pixel>
	class Image;
}
namespace Raytracer
{
	UTIL_CUSTOM_EXCEPTION(ItemNotFoundException, Item not found in model);
	UTIL_CUSTOM_EXCEPTION(CameraNotSetException, Camera needs to be set before raytracing);
	
	class Camera;
	class Object;
	class Material;
	class Texture;
	class Light;
	
	class Model : public std::enable_shared_from_this<Model>, public RaytracerItem
	{
		private:
		double MAX_DIST;
		unsigned int AA_SAMPLES;
		std::shared_ptr<Camera> cam;
		std::vector<std::shared_ptr<Object>> objs;
		std::vector<std::shared_ptr<Material>> mats;
		std::vector<std::shared_ptr<Texture>> texs;
		std::vector<std::shared_ptr<Light>> lights;
		
		
		
		public:
		Model(std::string name, double maxDist, unsigned int AAsamples);
		Model(std::string name);
		virtual ~Model();
		
		Graphics::Image<pixel_t>* go(int x, int y);
		
		template <class Pixel>
		void go(Graphics::Image<Pixel>* const img, const int x, const int y)
		{
			if (cam == NULL)
		{
			throw CameraNotSetException();
		}
		
		cam->setImgDims(x, y);
		cam->setImg(img);
		for (int i = 0; i < y; i++)
		{
			this->runRow(i);
		}
		}
		
		std::shared_ptr<Camera> initCamera(const double w, const double h, const vector_t viewpoint);
		
		
		
		void add(Object*);
		void add(std::shared_ptr<Object>);
		void remove(Object*);
		void remove(std::shared_ptr<Object>);
		
		void add(Material*);
		void add(std::shared_ptr<Material>);
		void remove(Material*);
		void remove(std::shared_ptr<Material>);
		
		void add(Texture*);
		void add(std::shared_ptr<Texture>);
		void remove(Texture*);
		void remove(std::shared_ptr<Texture>);
		
		void add(Light*);
		void add(std::shared_ptr<Light>);
		void remove(Light*);
		void remove(std::shared_ptr<Light>);
		
		std::shared_ptr<Camera> getCamera() const { return cam; }
		
		void setCamera(const std::shared_ptr<Camera>);
		
		
		virtual void runRow(const int y);
		virtual void runPixel(const int x, const int y);
		
		virtual dpixel_t trace(const vector_t& base, const vector_t& dir, double totDist, std::shared_ptr<Object> lastHit) const;
		
		double findClosestObj(const vector_t& base, const vector_t& dir, std::shared_ptr<Object> lastHit, std::shared_ptr<Object>* closest) const;
		
		dpixel_t addIllumination(const vector_t& base, std::shared_ptr<Object>, const dpixel_t) const;
		
		virtual std::string toString() const;
		
	};
}
}