#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <functional>

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
		class Word;
		class Number;
		class Symbol;
		class Punctuation;
		class Sentence;
		
		/*template <typename Key>
		using Token_Set = std::unordered_set<std::shared_ptr<Key>, std::hash<std::shared_ptr<Key>>, std::function<bool(const std::shared_ptr<Key>, const std::shared_ptr<Key>)>>;*/
		
		template <typename Key>
		using Token_Set = std::unordered_set<std::shared_ptr<Key>>;
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	class Analyzer
	{
		private:
		std::string _contents;
		std::vector<std::shared_ptr<Internal::Token>> _tokens;
		Internal::Token_Set<Internal::Word> _words;
		Internal::Token_Set<Internal::Number> _numbers;
		Internal::Token_Set<Internal::Symbol> _symbols;
		Internal::Token_Set<Internal::Punctuation> _punctuation;
		Internal::Token_Set<Internal::Sentence> _sentences;
		Internal::Token_Set<Internal::Token> _distinctTokens;
		
		
		
		void parseToken(const std::string);
		
		
		
		protected:
		Analyzer();
		
		public:
		Analyzer(std::ifstream& file);
		Analyzer(const std::string& contents);
		Analyzer(const std::vector<std::string>& lines);
		
		
		const std::string& contents;
		const std::vector<std::shared_ptr<Internal::Token>>& tokens;
		const Internal::Token_Set<Internal::Word>& words;
		const Internal::Token_Set<Internal::Number>& numbers;
		const Internal::Token_Set<Internal::Symbol>& symbols;
		const Internal::Token_Set<Internal::Punctuation>& punctuation;
		const Internal::Token_Set<Internal::Sentence>& sentences;
		const Internal::Token_Set<Internal::Token>& distinctTokens;
		
		
		
		void parse();
		
		std::shared_ptr<Markov::Markov<std::shared_ptr<Internal::Token>>> markov(bool separateBySentence = true) const;
		
		std::vector<std::shared_ptr<const Internal::Token>> expand() const;
		
	};
}
}