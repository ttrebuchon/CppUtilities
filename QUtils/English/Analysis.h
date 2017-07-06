#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>

namespace QUtils
{

namespace Markov
{
template <class T>
class Markov;
}


namespace English
{
	namespace Internal
	{
		class Token;
	};
	
	inline bool isLetterOrNumber(const char c)
	{
		return (((int)c >= 48 && (int)c <= 57) || ((int)c >= 65 && (int)c <= 90) || ((int)c >= 97 && (int)c <= 122) || ((int)c >= 128 && (int)c <= 154) || (c >= 160 && c <= 165));
	}
	
	inline bool isLetter(const char c)
	{
		return (((int)c >= 65 && (int)c <= 90) || ((int)c >= 97 && (int)c <= 122) || ((int)c >= 128 && (int)c <= 154) || (c >= 160 && c <= 165));
	}
	
	inline bool isNumber(const char c)
	{
		return ((int)c >= 48 && (int)c <= 57);
	}
	
	inline bool isCapital(const char c)
	{
		return ((int)c >= 65 && (int)c <= 90);
	}
	
	inline bool isPunctuation(const char c)
	{
		return (c == '!' || c == '"' || c == '\'' || c == '(' || c == ')' || c == ',' || c == '-' || c == '.' || c == '/' || c == '\\' || c == ':' || c == ';' || c == '[' || c == ']'|| c == '?');
	}
	
	inline bool endsSentence(const char c)
	{
		return (c == '.' || c == '!' || c == '?');
	}
	
	inline bool isWhitespace(const char c)
	{
		return ((c == ' ') || (c == '\n') || (c == '\t'));
	}
	
	inline bool isSymbol(const char c)
	{
		return (c == '#' || c == '%' || c == '&' || c == '*' || c == '+' || c == '=' || c == '<' || c == '>' || c == '@' || c == '$' || ((int)c == 156) || ((int)c == 157) || c == 227 || c == '_');
	}
	
	inline bool isUnparseable(char c)
	{
		return ((((int)c >= 174) && ((int)c <= 226)) || c == 166 || c == 169 || (c >= 228 && c <= 254));
	}
	
	
	std::shared_ptr<Internal::Token> parseToken(const std::string);
	
	
	class Analyzer
	{
		private:
		std::string _contents;
		std::vector<std::shared_ptr<Internal::Token>> _tokens;
		
		protected:
		
		public:
		Analyzer(std::ifstream& file);
		Analyzer(const std::string& contents);
		Analyzer(const std::vector<std::string>& lines);
		
		
		const std::string& contents;
		const std::vector<std::shared_ptr<Internal::Token>>& tokens;
		
		void parse();
		
		std::shared_ptr<Markov::Markov<std::shared_ptr<Internal::Token>>> markov(bool separateBySentence = true) const;
		
	};
}
}