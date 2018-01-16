#pragma once
#include <math.h>


namespace QUtils { namespace World {
	
	namespace Meta
	{
		template <class T, class G>
		struct Types
		{
			typedef decltype(std::declval<T>()*std::declval<G>() + std::declval<T>()*std::declval<G>()) Dot;
			typedef decltype(std::declval<T>()*std::declval<G>() - std::declval<T>()*std::declval<G>()) Cross;
			typedef decltype(sqrt(std::declval<T>()*std::declval<T>() + std::declval<T>()*std::declval<T>())) Magnitude;
			typedef decltype(std::declval<T>()/std::declval<Magnitude>()) Unit;
		};
	}
	
	
	
	template <class T>
	struct Vector
	{
		T x, y, z;
		
		constexpr Vector() : x(), y(), z()
		{}
		
		constexpr Vector(const T x, const T y, const T z) : 
		x(x),
		y(y),
		z(z)
		{}
		
		template <class G>
		constexpr typename Meta::Types<T, G>::Dot dot(const Vector<G>) const;
		
		template <class G>
		constexpr Vector<typename Meta::Types<T, G>::Cross> cross(const Vector<G>) const;
		
		constexpr typename Meta::Types<T, T>::Magnitude magnitude() const;
		inline constexpr typename Meta::Types<T, T>::Magnitude value() const
		{
			return magnitude();
		}
		
		constexpr Vector<typename Meta::Types<T, T>::Unit> unit() const;
		
		template <class G>
		constexpr operator Vector<G>() const;
	};
	
	template <class T>
	std::string to_string(const Vector<T> vec)
	{
		using std::to_string;
		
		
		return "<" +
		to_string(vec.x) +
		", " +
		to_string(vec.y) +
		", " + 
		to_string(vec.z) +
		">";
	}
	
	template <class T, class G>
	Vector<T>& operator+=(Vector<T>& l, const Vector<G> r)
	{
		l.x += r.x;
		l.y += r.y;
		l.z += r.z;
		return l;
	}
	
	template <class T, class G>
	constexpr Vector<decltype(T() + G())> operator+(const Vector<T> l, const Vector<G> r)
	{
		return Vector<decltype(T() + G())>(
		l.x + r.x,
		l.y + r.y,
		l.z + r.z
		);
	}
	
	template <class T, class G>
	Vector<T>& operator-=(Vector<T>& l, const Vector<G> r)
	{
		l.x -= r.x;
		l.y -= r.y;
		l.z -= r.z;
		return l;
	}
	
	template <class T, class G>
	constexpr Vector<decltype(T() - G())> operator-(const Vector<T> l, const Vector<G> r)
	{
		return Vector<decltype(T() - G())>(
		l.x - r.x,
		l.y - r.y,
		l.z - r.z
		);
	}
	
	template <class T, class G>
	constexpr Vector<decltype(T() * G())> operator*(const Vector<T> l, const G r)
	{
		return Vector<decltype(T() * G())>(
		l.x * r,
		l.y * r,
		l.z * r
		);
	}
	
	template <class T, class G>
	constexpr Vector<decltype(T() * G())> operator*(const G l, const Vector<T> r)
	{
		return Vector<decltype(T() * G())>(
		l * r.x,
		l * r.y,
		l * r.z
		);
	}
	
	template <class T, class G>
	Vector<T>& operator*=(Vector<T>& l, const G r)
	{
		l.x *= r;
		l.y *= r;
		l.z *= r;
		return l;
	}
	
	template <class T, class G>
	constexpr auto operator*(const Vector<T> l, const Vector<G> r)
	{
		return l.dot(r);
	}
	
	template <class T, class G>
	constexpr Vector<decltype(T() / G())> operator/(const Vector<T> l, const G r)
	{
		return Vector<decltype(T() / G())>(
		l.x / r,
		l.y / r,
		l.z / r
		);
	}
	
	template <class T, class G>
	constexpr bool operator==(const Vector<T> l, const Vector<G> r)
	{
		return 
		(l.x == r.x) &&
		(l.y == r.y) &&
		(l.z == r.z);
	}
	
	template <class T, class G>
	constexpr bool operator!=(const Vector<T> l, const Vector<G> r)
	{
		return 
		(l.x != r.x) ||
		(l.y != r.y) ||
		(l.z != r.z);
	}
	
	
	/*template <class G>
	struct Vector<Vector<G>>
	{
		private:
		typedef Vector<G> T;
		
		public:
		T x, y, z;
		
		constexpr Vector() : x(), y(), z()
		{}
		
		constexpr Vector(const T x, const T y, const T z) : 
		x(x),
		y(y),
		z(z)
		{}
		
	};*/
}
}
#include "Vector.hpp"