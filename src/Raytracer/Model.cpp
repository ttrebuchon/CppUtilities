#include <Raytracer/Model.h>
#include <Raytracer/Camera.h>
#include <Raytracer/Object.h>
#include <Raytracer/Light.h>
#include <Raytracer/Material.h>
#include <Raytracer/Texture.h>
#include <Exception/NotImplemented.h>
#include <Exception/Exception.h>

#include <algorithm>

namespace Util
{
namespace Raytracer
{
	UTIL_CUSTOM_EXCEPTION(ItemNotFoundException, Item not found in model);
	
	UTIL_CUSTOM_EXCEPTION(CameraNotSetException, Camera needs to be set before raytracing);
	
	Model::Model(std::string name, double maxDist, unsigned int aaSamples) : RaytracerItem(name), MAX_DIST(maxDist), AA_SAMPLES(aaSamples), cam(NULL)
	{
		
	}
	
	Model::Model(std::string name) : Model(name, 32, 3)
	{
		
	}
	
	Model::~Model()
	{
		
	}
	
	image_t Model::go(int x, int y)
	{
		image_t img = new pixel_t[x*y];
		this->go(img, x, y);
		return img;
	}
	
	void Model::go(image_t const img, const int x, const int y)
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
	
	std::shared_ptr<Camera> Model::initCamera(const double w, const double h, const vector_t viewpoint)
	{
		return cam = std::make_shared<Camera>(name() + "_Camera", w, h, viewpoint);
	}
	
	
	void Model::add(Object* obj)
	{add(obj->shared_from_this());}
	void Model::remove(Object* obj)
	{remove(obj->shared_from_this());}
	
	void Model::add(Material* mat)
	{add(mat->shared_from_this());}
	void Model::remove(Material* mat)
	{remove(mat->shared_from_this());}
	
	void Model::add(Texture* tex)
	{add(tex->shared_from_this());}
	void Model::remove(Texture* tex)
	{remove(tex->shared_from_this());}
	
	void Model::add(Light* lgt)
	{add(lgt->shared_from_this());}
	void Model::remove(Light* lgt)
	{remove(lgt->shared_from_this());}
	
	
	
	void Model::add(std::shared_ptr<Object> obj)
	{
		if (std::find(objs.begin(), objs.end(), obj) != objs.end())
		{
			return;
		}
		objs.push_back(obj);
	}
	
	void Model::add(std::shared_ptr<Material> mat)
	{
		if (std::find(mats.begin(), mats.end(), mat) != mats.end())
		{
			return;
		}
		mats.push_back(mat);
	}
	
	void Model::add(std::shared_ptr<Texture> tex)
	{
		if (std::find(texs.begin(), texs.end(), tex) != texs.end())
		{
			return;
		}
		texs.push_back(tex);
	}
	
	void Model::add(std::shared_ptr<Light> lgt)
	{
		if (std::find(lights.begin(), lights.end(), lgt) != lights.end())
		{
			return;
		}
		lights.push_back(lgt);
	}
	
	
	
	void Model::remove(std::shared_ptr<Object> obj)
	{
		typename std::vector<std::shared_ptr<Object>>::iterator i;
		if ((i = std::find(objs.begin(), objs.end(), obj)) == objs.end())
		{
			throw ItemNotFoundException();
		}
		objs.erase(i);
	}
	
	void Model::remove(std::shared_ptr<Material> mat)
	{
		typename std::vector<std::shared_ptr<Material>>::iterator i;
		if ((i = std::find(mats.begin(), mats.end(), mat)) == mats.end())
		{
			throw ItemNotFoundException();
		}
		mats.erase(i);
	}
	
	void Model::remove(std::shared_ptr<Texture> tex)
	{
		typename std::vector<std::shared_ptr<Texture>>::iterator i;
		if ((i = std::find(texs.begin(), texs.end(), tex)) == texs.end())
		{
			throw ItemNotFoundException();
		}
		texs.erase(i);
	}
	
	void Model::remove(std::shared_ptr<Light> lgt)
	{
		typename std::vector<std::shared_ptr<Light>>::iterator i;
		if ((i = std::find(lights.begin(), lights.end(), lgt)) == lights.end())
		{
			throw ItemNotFoundException();
		}
		lights.erase(i);
	}
	
	void Model::setCamera(const std::shared_ptr<Camera> cam)
	{
		this->cam = cam;
	}
	
	
	
	
	
	
	
	void Model::runRow(const int y)
	{
		for (int x = 0; x < cam->x(); x++)
		{
			runPixel(x, y);
		}
	}
	
	void Model::runPixel(const int x, const int y)
	{
		vector_t viewPt = cam->view();
		vector_t dir;
		
		dpixel_t pix;
		if (AA_SAMPLES > 1)
		{
		for (auto i = 0; i < AA_SAMPLES; i++)
		{
			dir = cam->dir(x, y, true);
			pix += trace(viewPt, dir, 0, NULL);
		}
		pix = pixScale(static_cast<double>(1)/AA_SAMPLES, pix);
		}
		else
		{
			dir = cam->dir(x, y, false);
			pix = trace(viewPt, dir, 0, NULL);
		}
		
		cam->setPixel(x, y, pix);
	}
	
	
	
	
	dpixel_t Model::trace(const vector_t& base, const vector_t& dir, double totDist, std::shared_ptr<Object> lastHit) const
	{
		dpixel_t pix;
		std::shared_ptr<Object> closest;
		double specref = 0;
		
		double dist = findClosestObj(base, dir, lastHit, &closest);
		if (closest != NULL)
		{
			dist = closest->hits(base, dir);
			pix = closest->ambient();
			pix = addIllumination(base, closest, pix);
		}
		if (dist > 0)
		{
			totDist += dist;
			pix = pixScale(1/totDist, pix);
			
			vector_t lastHitpt = closest->lastHit();
			
			double trans = closest->trans();
			if (trans > 0)
			{
				dpixel_t transBehind;
				dpixel_t transCol;
				transBehind = trace(lastHitpt, dir, totDist, closest);
				pix = pixScale(1 - trans, pix);
				transBehind = pixScale(trans, transBehind);
				
				dpixel_t diffuse = closest->diffuse();
				double largestComp = std::max(std::max(diffuse.R, diffuse.G), diffuse.B);
				diffuse = pixScale(trans / largestComp, diffuse);
				transBehind = transBehind*diffuse;
				pix = pix + transBehind;
				
			}
			if (totDist > MAX_DIST)
			{
				return pix;
			}
			
			specref = closest->specular();
			if (specref != 0)
			{
				dpixel_t spec_p;
				vector_t lastNorm = closest->lastNormal();
				
				vector_t refDir = dir.reflect(lastNorm);
				spec_p = trace(lastHitpt, refDir, totDist, closest);
				spec_p = pixScale(specref, spec_p);
				pix = pix + spec_p;
			}
			return pix;
		}
		else
		{
			return dpixel_t();
		}
		
		
	}
	
	double Model::findClosestObj(const vector_t& base, const vector_t& dir, std::shared_ptr<Object> lastHit, std::shared_ptr<Object>* closest) const
	{
		if (closest == NULL)
		{
			std::shared_ptr<Object> ptr;
			return findClosestObj(base, dir, lastHit, &ptr);
		}
		
		double tmpDist, minDist = -1;
		
		for (auto obj : objs)
		{
			if (obj == lastHit)
			{
				continue;
			}
			tmpDist = obj->hits(base, dir);
			if (tmpDist > 0)
			{
				if (tmpDist < minDist || minDist == -1)
				{
					*closest = obj;
					minDist = tmpDist;
				}
			}
		}
		return minDist;
		
	}
	
	dpixel_t Model::addIllumination(const vector_t& base, std::shared_ptr<Object> hitObj, const dpixel_t p) const
	{
		dpixel_t pix = p;
		for (auto light : lights)
		{
			light->illuminate(this, base, hitObj, pix);
		}
		return pix;
	}
	
	
	
	
	
	
	
	
	std::string Model::toString() const
	{
		throw NotImp();
	}
}
}