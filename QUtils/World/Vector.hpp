#pragma once
#include "Vector.h"


namespace QUtils { namespace World {
	
	
	
	template <class T>
	template <class G>
	constexpr typename Meta::Types<T, G>::Dot Vector<T>::dot(const Vector<G> r) const
	{
		return x*r.x + y*r.y + z*r.z;
	}
	
	template <class T>
	template <class G>
	constexpr Vector<typename Meta::Types<T, G>::Cross> Vector<T>::cross(const Vector<G> r) const
	{
		typedef typename Meta::Types<T, G>::Cross R;
		return Vector<R>(
			y*r.z - z*r.y,
			z*r.x - x*r.z,
			x*r.y - y*r.x
		);
	}
	
	template <class T>
	constexpr typename Meta::Types<T, T>::Magnitude Vector<T>::magnitude() const
	{
		return sqrt(x*x + y*y + z*z);
	}
	
	template <class T>
	constexpr Vector<typename Meta::Types<T, T>::Unit> Vector<T>::unit() const
	{
		return *this / magnitude();
	}
}
}