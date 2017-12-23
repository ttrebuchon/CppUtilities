#pragma once
#include "Settings.h"
#include <fstream>


namespace QUtils { namespace __Settings {
	
	using namespace nlohmann;
	
	template <class X>
	_Settings<X>::_Settings(const std::string fname) : doc(NULL), filename(fname), changed(false)
	{
		
	}
	
	
	template <class X>
	_Settings<X>::~_Settings()
	{
		if (doc != NULL)
		{
			if (changed)
			{
				save();
			}
			delete doc;
		}
	}
	
	template <class X>
	void _Settings<X>::open() const
	{
		doc = new json();
		{
		std::ifstream in(filename);
		if (in)
		{
			in >> *doc;
			changed = false;
		}
		else
		{
			changed = true;
		}
		}
	}
	
	template <class X>
	std::string _Settings<X>::get(const std::string key) const
	{
		if (!doc)
		{
			open();
		}
		if (doc->count(key) > 0)
		{
			try
			{
				return doc->at(key).get<std::string>();
			}
			catch (...)
			{
				return doc->at(key).dump();
			}
		}
		return "";
	}
	
	template <class X>
	void _Settings<X>::set(const std::string key, const std::string value)
	{
		this->set<std::string>(key, value);
	}
	
	template <class X>
	template <class T>
	T _Settings<X>::get(const std::string key) const
	{
		if (!doc)
		{
			open();
		}
		if (doc->count(key) > 0)
		{
			return doc->at(key).get<T>();
		}
		return T();
	}
	
	template <class X>
	template <class T>
	void _Settings<X>::set(const std::string key, const T value)
	{
		if (!doc)
		{
			open();
		}
		(*doc)[key] = value;
		changed = true;
	}
	
	template <class X>
	void _Settings<X>::save() const
	{
		if (changed)
		{
			std::ofstream out(filename);
			out << doc->dump(4);
			out.close();
			changed = false;
		}
	}
	
	template <class X>
	void _Settings<X>::reload()
	{
		std::ifstream in(filename);
		if (in)
		{
			in >> *doc;
			changed = false;
		}
		else
		{
			changed = true;
			*doc = json();
		}
	}
}
}