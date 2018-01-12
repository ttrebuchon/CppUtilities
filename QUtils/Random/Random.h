#pragma once
#include <random>
#include <limits>

namespace QUtils {
namespace Random_Internal {
	
	
	//Static Class
	template <class T>
	class Random final
	{
		private:
		typedef std::default_random_engine REngine;
		static REngine engine;
		static std::uniform_real_distribution<T> dist;
		constexpr static T _max = std::numeric_limits<T>::max();
		constexpr static T _min = std::numeric_limits<T>::min();
		
		public:
		typedef T result_type;
		Random() = delete;
		
		static T Get()
		{
			return dist(engine);
		}
		
		static void Seed(const T seed)
		{
			engine.seed(seed);
		}
		
		static T RandomSeed()
		{
			T seed = std::random_device()();
			Seed(seed);
			return seed;
		}
		
		static constexpr T Min()
		{
			return _min;
		}
		
		static constexpr T Max()
		{
			return _max;
		}
		
		template <class G>
		static G GetAs()
		{
			static std::uniform_real_distribution<G> d(std::numeric_limits<G>::min(), std::numeric_limits<G>::max());
			
			return d(engine);
		}
		
	};
	
	template <class T>
	typename Random<T>::REngine Random<T>::engine;
	
	template <class T>
	std::uniform_real_distribution<T> Random<T>::dist(Random<T>::Min(), Random<T>::Max());
}
using Random = Random_Internal::Random<double>;
}