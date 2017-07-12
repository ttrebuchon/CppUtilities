#pragma once
#include "Types.h"
#include <string>
#include <vector>
#include <memory>

namespace Util
{
namespace Raytracer
{
	class Camera;
	class Object;
	class Material;
	class Texture;
	class Light;
	class Image;
	template <class T>
	class BitmapImg;
	
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
		
		BitmapImg<pixel_t>* go(int x, int y);
		virtual void go(Image* const, const int x, const int y);
		
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