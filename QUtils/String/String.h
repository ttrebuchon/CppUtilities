#pragma once

#include <string>
#include <vector>

namespace Util
{
	class String;
}

namespace std
{
	std::istream& getline(std::istream&, Util::String&);
	std::istream& getline(std::istream&, Util::String&, char);
}

namespace Util
{
	class String
	{
		private:
		std::string str;
		
		protected:
		
		public:
		String(std::string);
		String(const char*);
		String();
		String(const String&);
		~String();
		
		
		
		//Methods
		size_t length() const noexcept;
		size_t size() const noexcept;
		const char* c_str() const;
		String toLower() const;
		String toUpper() const;
		String replace(std::string target, std::string replacement) const;
		String substr(size_t start, size_t end = -1) const;
		bool empty() const;
		char& at(int);
		size_t find(const std::string, size_t start = 0) const;
		bool contains(String) const;
		//bool contains(std::string) const;
		bool startsWith(String) const;
		//bool startsWith(std::string) const;
		bool endsWith(String) const;
		//bool endsWith(std::string) const;
		String removeWhitespaces() const;
		String trim() const;
		std::vector<String> separateBy(std::string token) const;
		std::vector<String> split(std::string token) const;
		String reverse() const;
		int count(const std::string) const; //Number of times token appears in string
		String shuffle() const; //Randomly reorder characters
		double toDouble() const;
		float toFloat() const;
		int toInt() const;
		
		String insert(int pos, String) const;
		String padLeft(int totLen, char c = ' ');
		String padRight(int totLen, char c = ' ');
		
		
		//Iterators
		class iterator
		{
			private:
			const char* c;
			
			iterator(const char*);
			
			public:
			
			bool operator!=(const iterator) const;
			bool operator==(const iterator) const; 
			
			iterator& operator++();
			iterator operator++(int);
			
			char operator*() const;
			
			friend String;
		};
		iterator begin() const;
		iterator end() const;
		
		
		
		
		//Operators
		operator std::string() const;
		String& operator+=(std::string);
		String& operator+=(char);
		String operator+(const String) const;
		String operator+(const std::string) const;
		String operator+(const char*) const;
		bool operator==(std::string) const;
		bool operator==(const char*) const;
		bool operator!=(std::string) const;
		bool operator!=(const char*) const;
		String& operator=(std::string);
		String& operator=(String&);
		char& operator[](int);
		
		template <typename T>
		String& operator<<(T);
		
		
		//Friends
		friend std::istream& std::getline(std::istream&, String&);
		friend std::istream& std::getline(std::istream&, String&, char);
	};
	
	template <>
	String& String::operator<<(const char*);
	template <>
	String& String::operator<<(const String);
	template <>
	String& String::operator<<(const double);
	template <>
	String& String::operator<<(const int);
	template <>
	String& String::operator<<(const char);
	
	
	template <typename T>
	String& String::operator<<(T t)
	{
		//str += std::to_string(t);
		str += (std::stringstream() << t).str();
		return *this;
	}
	
	
	//Non-Member Functions
	String operator+(const char* c, String s);
	String operator+(std::string c, String s);
	std::ostream& operator<<(std::ostream&, String);
	
}