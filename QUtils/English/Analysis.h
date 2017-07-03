#pragma once
#include <string>
#include <fstream>
#include <vector>

namespace QUtils
{
namespace English
{
	
	inline bool isLetterOrNumber(char c)
	{
		return (((int)c >= 48 && (int)c <= 57) || ((int)c >= 65 && (int)c <= 90) || ((int)c >= 97 && (int)c <= 122));
	}
	
	inline bool isLetter(char c)
	{
		return (((int)c >= 65 && (int)c <= 90) || ((int)c >= 97 && (int)c <= 122));
	}
	
	inline bool isNumber(char c)
	{
		return ((int)c >= 48 && (int)c <= 57);
	}
	
	inline bool isCapital(char c)
	{
		return ((int)c >= 65 && (int)c <= 90);
	}
	
	inline bool isPunctuation(char c)
	{
		return (c == '!' || c == '"' || c == '\'' || c == '(' || c == ')' || c == ',' || c == '-' || c == '.' || c == '/' || c == '?' || c == ' ');
	}
	
	inline bool isSpace(char c)
	{
		return (c == ' ');
	}
	
	
	
	class Analyzer
	{
		private:
		std::string _contents;
		
		protected:
		
		public:
		Analyzer(std::ifstream& file);
		Analyzer(const std::string& contents);
		Analyzer(const std::vector<std::string>& lines);
		
		
		const std::string& contents;
		
	};
}
}