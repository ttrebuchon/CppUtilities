#pragma once


namespace QUtils { namespace World {
	
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
	
	
}
}