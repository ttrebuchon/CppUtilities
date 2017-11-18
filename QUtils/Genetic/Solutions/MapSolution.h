#pragma once

#include "../Solution.h"
#include <map>

namespace QUtils
{
namespace Genetic
{
	template <class Key, class T>
	class MapSolution : public Solution<std::map<Key, T>, T>
	{
		private:
		protected:
		std::map<Key, T> values;
		
		public:
		MapSolution(const std::map<Key, T> values);
		
		
		T& operator[](const Key i) { return at(i); }
		const T& operator[](const Key i) const { return at(i); }
		virtual T& at(const Key);
		virtual const T& at(const Key) const;
		
		virtual unsigned int size() const;
		
		
		virtual void randomize() override;
		
		virtual void mutate(const int magnitude = -1) override;
		
		virtual std::map<Key, T> get() const override;
		
		virtual std::shared_ptr<Solution<std::map<Key, T>, T>> clone() const override;
		
		virtual void modified() override;
		virtual T& set(const int index, const T) override;
		virtual T& set(const Key index, const T);
		
		T& atIndex(size_t);
		const T& atIndex(size_t) const;
		const Key keyAtIndex(const size_t) const;
		virtual T& at(const size_t i) override { return atIndex(i); }
		/*const T& at(const size_t i) const
		{ return atIndex(i); }*/
	};
	
}
}