#pragma once

#include <memory>
#include <type_traits>
#include <string>
#include <iostream>
#include <map>

namespace QUtils::GUI
{
	class AppWindow;
	
	template <class R, class... Keys>
	class Resource
	{
		private:
		std::shared_ptr<R> ptr;
		
		
		protected:
		
		
		public:
		const std::string name;
		
		Resource(const std::string name, std::shared_ptr<R> ptr) : ptr(ptr), name(name)
		{
			
		}
		
		
		virtual ~Resource()
		{
			
		}
		
		virtual std::shared_ptr<R> get()
		{
			return ptr;
		}
		
	};
	
	
	template <class R, class... Keys>
	class ResourceLoader
	{
		private:
		static std::map<std::tuple<std::string, Keys...>, Resource<R, Keys...>*> resources;
		
		static std::map<std::string, ResourceLoader<R, Keys...>*> loaders;
		
		
		
		protected:
		
		virtual Resource<R, Keys...>* load(Keys... keys) = 0;
		
		public:
		const std::string name;
		
		ResourceLoader(const std::string name) : name(name)
		{}
		
		virtual ~ResourceLoader()
		{
			
		}
		
		
		static std::shared_ptr<R> get(const std::string name, Keys... keys)
		{
			auto tup = std::tuple<std::string, Keys...>(name, keys...);
			auto ptr = resources[tup];
			if (ptr == NULL)
			{
				auto loader = loaders[name];
				if (loader == NULL)
				{
					//TODO
					std::cout << "LOADER FOR \"" << name << "\" IS NULL\n";
					throw std::exception();
				}
				ptr = (resources[tup] = loader->load(keys...));
			}
			return ptr->get();
		}
		
		void assign()
		{
			if (loaders[name] != NULL)
			{
				delete loaders[name];
			}
			loaders[name] = this;
		}
		
	};
	
	template <class R, class... Keys>
	std::map<std::tuple<std::string, Keys...>, Resource<R, Keys...>*> ResourceLoader<R, Keys...>::resources;
	
	template <class R, class... Keys>
	std::map<std::string, ResourceLoader<R, Keys...>*> ResourceLoader<R, Keys...>::loaders;
}