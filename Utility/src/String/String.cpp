#include <String/String.h>
#include <Exception/NotImplemented.h>

#include <iostream>
#include <algorithm>


#ifdef __NS__
#define STR_VALUE(arg) #arg
#define __NS_NAME(name) STR_VALUE(name)
#define NS_NAME __NS_NAME(__NS__)
#endif


namespace Util
{
	//Constructors
	String::String(std::string str) : str(str)
	{
		
	}
	
	String::String(const char* c) : str(c)
	{
		
	}
	
	String::String() : String("")
	{
		
	}
	
	String::String(const String& s) : str(s.str)
	{
		
	}
	
	String::~String()
	{
	}
	
	
	
	
	//Methods
	size_t String::length() const noexcept
	{
		return str.length();
	}
	
	size_t String::size() const noexcept
	{
		return str.size();
	}
	
	const char* String::c_str() const
	{
		return str.c_str();
	}
	
	String String::toLower() const
	{
		std::string s;
		s = str;
		int len = s.length();
		for (int i = 0; i < len; i++)
		{
			s[i] = std::tolower(s[i]);
		}
		
		return String(s);
	}
	
	String String::toUpper() const
	{
		std::string s;
		s = str;
		int len = s.length();
		for (int i = 0; i < len; i++)
		{
			s[i] = std::toupper(s[i]);
		}
		
		return String(s);
	}
	
	String String::replace(std::string target, std::string replacement) const
	{
		std::string s = str;
		std::string first, second;
		size_t pos;
		while ((pos = s.find(target)) != std::string::npos)
		{
			first = s.substr(0, pos);
			second = s.substr(pos + target.length());
			s = first + second;
		}
		
		return String(s);
	}
	
	String String::substr(size_t start, size_t end) const
	{
		if (end != -1)
		{
			return String(str.substr(start, end));
		}
		else
		{
			return String(str.substr(start));
		}
	}
	
	bool String::empty() const
	{
		return str.empty();
	}
	
	char& String::at(int i)
	{
		return str.at(i);
	}
	
	size_t String::find(const std::string s, size_t start) const
	{
		return str.find(s, start);
	}
	
	bool String::contains(String s) const
	{
		return (str.find(s) != std::string::npos);
	}
	/*
	bool String::contains(std::string s) const
	{
		return (str.find(s) != std::string::npos);
	}*/
	
	bool String::startsWith(String s) const
	{
		register int len = s.length();
		if (length() < len)
		{
			return false;
		}
		for (register int i = 0; i < len; i++)
		{
			if (str[i] != s[i])
			{
				return false;
			}
		}
		return true;
	}
	/*
	bool String::startsWith(std::string s) const
	{
		register int len = s.length();
		if (length() < len)
		{
			return false;
		}
		for (register int i = 0; i < len; i++)
		{
			if (str[i] != s[i])
			{
				return false;
			}
		}
		return true;
	}*/
	
	bool String::endsWith(String s) const
	{
		register int len = s.length();
		register int thisLen = length();
		if (thisLen < len)
		{
			return false;
		}
		for (register auto i = 0; i < len; i++)
		{
			if (str[thisLen-i-1] != s[len-i-1])
			{
				return false;
			}
		}
		return true;
	}
	/*
	bool String::endsWith(std::string s) const
	{
		//return reverse().startsWith(s);
		register int len = s.length();
		register int thisLen = length();
		if (thisLen < len)
		{
			return false;
		}
		for (register auto i = 0; i < len; i++)
		{
			if (str[thisLen-i-1] != s[len-i-1])
			{
				return false;
			}
		}
		return true;
	}*/
	
	String String::removeWhitespaces() const
	{
		return this->replace(" ", "").replace("\t", "").replace("}n", "");
	}
	
	String String::trim() const
	{
		return removeWhitespaces();
	}
	
	std::vector<String> String::separateBy(std::string token) const
	{
		//throw NotImp();
		std::vector<String> v;
		String s = str;
		
		while (s.length() > 0)
		{
		auto index = s.find(token);
		v.push_back(s.substr(0, index));
		if (index != std::string::npos)
		{
			s = s.substr(index + token.length());
		}
		else
		{
			s = "";
		}
		
		}
		
		return v;
	}
	
	std::vector<String> String::split(std::string token) const
	{
		return separateBy(token);
	}
	
	String String::reverse() const
	{
		std::string s = str;
		std::reverse(s.begin(), s.end());
		return String(s);
	}
	
	int String::count(std::string s) const
	{
		register size_t index = 0;
		register auto count = -1;
		register auto thisLen = length();
		auto len = s.length();
		while (index < thisLen)
		{
			count++;
			index = find(s, index);
			if (index != std::string::npos)
			{
				index += len;
			}
			else
			{
				return count;
			}
		}
		
		return count;
	}
	
	String String::shuffle() const
	{
		std::string s = str;
		std::random_shuffle(s.begin(), s.end());
		return String(s);
	}
	
	double String::toDouble() const
	{
		return std::stod(str);
	}
	
	float String::toFloat() const
	{
		return std::stof(str);
	}
	
	int String::toInt() const
	{
		return std::stoi(str);
	}
	
	String String::insert(int pos, String nStr) const
	{
		return substr(0, pos) + nStr + substr(pos);
	}
	//End Member Functions
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//Iterators
	String::iterator::iterator(const char* c) : c(c)
	{
		
	}
	
	bool String::iterator::operator!=(const String::iterator it) const
	{
		return !(this->operator==(it));
	}
	
	bool String::iterator::operator==(const String::iterator it) const
	{
		return (c == it.c);
	}
	
	String::iterator& String::iterator::operator++()
	{
		if (*c == '\0')
		{
			#ifdef __NS__
			throw std::out_of_range(std::string(NS_NAME) + "::String::iterator: out of range");
			#else
			throw std::out_of_range("String::iterator: out of range");
			#endif
		}
		c++;
		return *this;
	}
	
	String::iterator String::iterator::operator++(int)
	{
		if (*c == '\0')
		{
			#ifdef __NS__
			throw std::out_of_range(std::string(NS_NAME) + "::String::iterator: out of range");
			#else
			throw std::out_of_range("String::iterator: out of range");
			#endif
		}
		String::iterator it(c);
		c++;
		return it;
	}
	
	char String::iterator::operator*() const
	{
		return *c;
	}
	
	String::iterator String::begin() const
	{
		return iterator(c_str());
	}
	
	String::iterator String::end() const
	{
		return iterator(&(c_str()[length()]));
	}
	//End Iterators
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//Operators
	String::operator std::string() const
	{
		return str;
	}
	
	
	String& String::operator+=(std::string s)
	{
		str += s;
		return *this;
	}
	
	String& String::operator+=(char c)
	{
		str += c;
		return *this;
	}
	
	String String::operator+(const String s) const
	{
		return str + s.str;
	}
	
	String String::operator+(const std::string s) const
	{
		return str + s;
	}
	
	bool String::operator==(std::string s) const
	{
		return (str == s);
	}
	
	bool String::operator==(const char* cs) const
	{
		return (strcmp(this->c_str(), cs) == 0);
	}
	
	bool String::operator!=(std::string s) const
	{
		return !(*this == s);
	}
	
	bool String::operator!=(const char* c) const
	{
		return !(*this == c);
	}
	
	String& String::operator=(std::string s)
	{
		str = s;
		return *this;
	}
	
	String& String::operator=(String& s)
	{
		str = s.str;
		return *this;
	}
	
	char& String::operator[](int i)
	{
		if (i >= length())
		{
			#ifdef __NS__
			throw std::out_of_range(std::string(NS_NAME) + "::String::[]: index out of range");
			#else
			throw std::out_of_range("String::[]: index out of range");
			#endif
		}
		return str[i];
	}
	
	template <>
	String& String::operator<<(const char* cs)
	{
		str += cs;
		return *this;
	}
	
	template <>
	String& String::operator<<(const String s)
	{
		str += s;
		return *this;
	}
	
	template <>
	String& String::operator<<(const double d)
	{
		str += std::to_string(d);
		return *this;
	}
	
	template <>
	String& String::operator<<(const int i)
	{
		str += std::to_string(i);
		return *this;
	}
	
	template <>
	String& String::operator<<(const char c)
	{
		str += c;
		return *this;
	}
	
	
	
	
	//Non-Member Functions
	String operator+(const char* c, String s)
	{
		return String(std::string(c) + (std::string)s);
	}
	
	std::ostream& operator<<(std::ostream& os, String s)
	{
		return (os << (std::string)s);
	}
}

namespace std
{
	std::istream& getline(std::istream& is, Util::String& s)
	{
		return getline(is, s.str);
	}
	
	std::istream& getline(std::istream& is, Util::String& s, char c)
	{
		return getline(is, s.str, c);
	}
	
	
}