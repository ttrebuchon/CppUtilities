#include <QUtils/String/String.h>
#include <QUtils/Exception/NotImplemented.h>

#include <iostream>
#include <algorithm>
#include <cstring>


#ifdef __NS__
#define STR_VALUE(arg) #arg
#define __NS_NAME(name) STR_VALUE(name)
#define NS_NAME __NS_NAME(__NS__)
#endif


namespace QUtils
{
	//Static Methods
	void String::Replace(std::string& str, const std::string target, const std::string replacement)
	{
		std::string s = "";
		//String str = this->str;
		size_t pos;
		while (str.length() > 0)
		{
			pos = str.find(target);
			if (pos == std::string::npos)
			{
				s += str;
				break;
			}
			s += str.substr(0, pos);
			str = str.substr(pos+target.length());
			s += replacement;
		}
		
		str = s;
	}
	
	void String::Replace(String& str, const std::string target, const std::string replacement)
	{
		String::Replace(str.str, target, replacement);
	}
	
	void String::Trim(std::string& str)
	{
		TrimStart(str);
		TrimEnd(str);
	}
	
	void String::Trim(String& str)
	{
		String::Trim(str.str);
	}
	
	void String::TrimStart(std::string& str)
	{
		int i;
		for (i = 0; i < str.length(); ++i)
		{
			if (str[i] != ' ' && str[i] != '\t')
			{
				break;
			}
		}
		if (i > 0)
		{
			str = str.substr(i);
		}
	}
	
	void String::TrimStart(String& str)
	{
		String::TrimStart(str.str);
	}
	
	void String::TrimEnd(std::string& str)
	{
		int i;
		for (i = str.length()-1; i >= 0; --i)
		{
			if (str[i] != ' ' && str[i] != '\t')
			{
				break;
			}
		}
		if (i < str.length()-1)
		{
			str = str.substr(0, i);
		}
	}
	
	void String::TrimEnd(String& str)
	{
		String::TrimEnd(str.str);
	}
	
	
	
	
	
	
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
		String s = *this;
		String::Replace(s, target, replacement);
		return s;
	}
	
	String String::substr(size_t start, size_t length) const
	{
		return String(str.substr(start, length));
	}
	
	String String::substr(size_t start) const
	{
		return String(str.substr(start));
	}
	
	String String::substring(size_t start, size_t end) const
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
		String s = *this;
		String::Trim(s);
		return s;
	}
	
	String String::trimStart() const
	{
		String s = *this;
		String::TrimStart(s);
		return s;
	}
	
	String String::trimEnd() const
	{
		String s = *this;
		String::TrimEnd(s);
		return s;
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
	
	String operator+(const String s1, const String s2)
	{
		return s1.str + s2.str;
	}
	
	String operator+(const String s1, const std::string s2)
	{
		return s1.str + s2;
	}

	String operator+(const String s1, const char* s2)
	{
		return s1.str + s2;
	}
	
	bool operator==(const String s1, const std::string s2)
	{
		return (s1.str == s2);
	}
	
	bool operator==(const String s1, const char* s2)
	{
		return (strcmp(s1.c_str(), s2) == 0);
	}
	
	bool operator!=(const String s1, const std::string s2)
	{
		return s1.str != s2;
	}
	
	bool operator!=(const String str, const char* s2)
	{
		return str.str != s2;
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

	String operator+(std::string c, String s)
	{
		return String(c + (std::string)s);
	}
	
	std::ostream& operator<<(std::ostream& os, String s)
	{
		return (os << (std::string)s);
	}
}

namespace std
{
	std::istream& getline(std::istream& is, QUtils::String& s)
	{
		return getline(is, s.str);
	}
	
	std::istream& getline(std::istream& is, QUtils::String& s, char c)
	{
		return getline(is, s.str, c);
	}
	
	
}