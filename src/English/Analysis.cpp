#include <QUtils/English/Analysis.h>
#include <QUtils/English/Analysis/Analysis.h>
#include <QUtils/String/String.h>
#include <QUtils/Markov/Markov.h>
#include <iostream>
#include <map>

namespace QUtils
{
namespace English
{
	
	
	
	
	Analyzer::Analyzer(std::ifstream& file) : _contents(), _tokens(), contents(_contents), tokens(_tokens)
	{
		file.seekg(0, std::ios::end);
		_contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&_contents[0], _contents.size());
	}
	
	Analyzer::Analyzer(const std::string& contents) : _contents(contents), _tokens(), contents(_contents), tokens(_tokens)
	{}
	
	Analyzer::Analyzer(const std::vector<std::string>& lines) : _contents(lines.at(0)), _tokens(), contents(_contents), tokens(_tokens)
	{
		for (auto it = lines.begin()+1; it != lines.end(); ++it)
		{
			_contents += "\n" + *it;
		}
	}
	
	void Analyzer::parse()
	{
		QUtils::String _cont = _contents;
		_cont = _cont.replace("\r\n", "\n");
		_contents = _cont;
		std::string tmp;
		enum Last_t
		{
			Letter = 0,
			Number = 1,
			Whitespace = 2,
			Punc = 3,
			Symbol = 4,
		};
		Last_t last;
		//char last_c;
		for (char c : contents)
		{
			if (tmp == "")
			{
				
				if (isLetter(c))
				{
					last = Letter;
				}
				else if (isNumber(c))
				{
					last = Number;
				}
				else if (isPunctuation(c))
				{
					last = Punc;
				}
				else if (isWhitespace(c))
				{
					last = Whitespace;
				}
				else if (isSymbol(c))
				{
					last = Symbol;
				}
				else if (isUnparseable(c))
				{
					continue;
				}
				tmp = c;
				//last_c = c;
				continue;
			}
			
			
			
			if (isLetter(c))
			{
				switch (last)
				{
					case Letter:
					case Number:
					tmp += c;
					break;
					
					default:
					_tokens.push_back(parseToken(tmp));
					tmp = c;
				}
				last = Letter;
			}
			else if (isNumber(c))
			{
				
				switch (last)
				{
					case Letter:
					case Number:
					case Punc:
					tmp += c;
					break;
					
					default:
					_tokens.push_back(parseToken(tmp));
					tmp = c;
					
				}
				last = Number;
			}
			else if (isPunctuation(c))
			{
				switch (last)
				{
					case Letter:
					if (c == '\'')
					{
						tmp += c;
						//last_c = c;
						continue;
					}
					else
					{
						_tokens.push_back(parseToken(tmp));
						tmp = c;
					}
					break;
					
					case Number:
					tmp += c;
					break;
					
					
					default:
					_tokens.push_back(parseToken(tmp));
					tmp = c;
				}
				last = Punc;
			}
			else if (isWhitespace(c))
			{
				switch (last)
				{
					case Whitespace:
					tmp += c;
					break;
					
					default:
					_tokens.push_back(parseToken(tmp));
					tmp = c;
				}
				last = Whitespace;
			}
			else if (isSymbol(c))
			{
				switch (last)
				{
					default:
					_tokens.push_back(parseToken(tmp));
					tmp = c;
				}
				last = Symbol;
			}
			else if (isUnparseable(c))
			{
				continue;
			}
			else
			{
				std::cerr << "'" << c << "' #" << (int)c << "\n";
				continue;
				throw std::exception();
			}
			
			//last_c = c;
		}
		
		auto clearNulls = [](auto& tokens)
		{
			decltype(tokens.begin()) it;
			while ((it = std::find(tokens.begin(), tokens.end(), (std::shared_ptr<Internal::Token>)NULL)) != tokens.end())
			{
				tokens.erase(it);
			}
		};
		
		auto simplifyTokens = [clearNulls](auto& tokens)
		{
		clearNulls(tokens);
		
		std::map<int, std::vector<std::shared_ptr<Internal::Token>>> hashTable;
		
		int checksum;
		std::string text;
		for (auto i = 0; i < tokens.size(); i++)
		{
			auto token = tokens[i];
			text = token->text();
			checksum = 0;
			for (char c : text)
			{
				checksum += c;
			}
			checksum = checksum % 1000;
			
			bool found = false;
			for (auto storedT : hashTable[checksum])
			{
				if (token->text() == storedT->text())
				{
					tokens[i] = storedT;
					found = true;
					break;
				}
			}
			if (!found)
			{
				hashTable[checksum].push_back(token);
			}
		}
		
		};
		
		
		
		
		simplifyTokens(_tokens);
		auto onlyExcAndQuest = [](const std::string str) -> bool
		{
			for (auto c : str)
			{
				if (!(c == '!' || c == '?'))
				{
					return false;
				}
			}
			return true;
		};
		bool lastWasPunc = false;
		if (_tokens.size() > 0)
		{
			lastWasPunc = (_tokens[0]->type() == "punctuation");
		}
		int lastIndex = 0;
		for (int i = 1; i < _tokens.size(); i++)
		{
			if (_tokens[i] == NULL)
			{
				continue;
			}
			if (_tokens[i]->type() == "punctuation")
			{
				if (lastWasPunc)
				{
					if (onlyExcAndQuest(_tokens[i]->text()) && onlyExcAndQuest(_tokens[lastIndex]->text()))
					{
						_tokens[lastIndex] = std::make_shared<Internal::Punctuation>(_tokens[lastIndex]->text() + _tokens[i]->text());
						_tokens[i] = NULL;
						continue;
					}
				}
				else
				{
					lastWasPunc = true;
				}
			}
			else
			{
				lastWasPunc = false;
			}
			lastIndex = i;
		}
		
		simplifyTokens(_tokens);
		
		
		std::vector<int> sentenceEndIndexes;
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i] == NULL)
			{
				continue;
			}
			if (tokens[i]->type() != "punctuation")
			{
				continue;
			}
			
			for (auto c : tokens[i]->text())
			{
				if (endsSentence(c))
				{
					sentenceEndIndexes.push_back(i);
					break;
				}
			}
		}
		
		
		
		std::cerr << "Sentence enders: " << sentenceEndIndexes.size() << "\n";
	}
	
	
	
	
	std::shared_ptr<Markov::Markov<std::shared_ptr<Internal::Token>>> Analyzer::markov(bool separateBySentence) const
	{
		std::shared_ptr<Markov::Markov<std::shared_ptr<Internal::Token>>> MC = std::make_shared<Markov::Markov<std::shared_ptr<Internal::Token>>>();
		MC->equals = [] (auto a, auto b) -> bool { return (a == b); };
		
		if (separateBySentence)
		{
			
		}
		else
		{
			MC->AddTrainChain(tokens);
		}
		return MC;
	}
	
	
	
	
	std::shared_ptr<Internal::Token> parseToken(const std::string text)
	{
		bool letters = false;
		bool numbers = false;
		bool punctuation = false;
		bool whitespaces = false;
		bool symbols = false;
		
		for (char c : text)
		{
			letters |= isLetter(c);
			numbers |= isNumber(c);
			punctuation |= isPunctuation(c);
			whitespaces |= isWhitespace(c);
			symbols |= isSymbol(c);
		}
		
		if (!(letters || numbers || punctuation || whitespaces || symbols))
		{
			std::cerr << "Indeterminate: \"" << text << "\"\n";
			for (auto c : text)
			{
				std::cerr << "#" << (int)c << "\tSym: " << isSymbol(c) << "\n";
			}
			throw std::exception();
		}
		
		
		if (whitespaces)
		{
			if (letters || numbers || punctuation || symbols)
			{
				std::cerr << "\"" << text << "\"\n";
				for (char c : text)
				{
					std::cerr << "#" << (int)c << "\n";
				}
				throw std::exception();
			}
			else
			{
				return std::make_shared<Internal::Whitespace>(text);
			}
		}
		else if (symbols)
		{
			return std::make_shared<Internal::Symbol>(text);
		}
		else if (letters)
		{
			return std::make_shared<Internal::Word>(text);
		}
		else if (punctuation)
		{
			if (numbers)
			{
				return std::make_shared<Internal::Number>(text);
			}
			else
			{
				return std::make_shared<Internal::Punctuation>(text);
			}
		}
		else if (numbers)
		{
			return std::make_shared<Internal::Number>(text);
		}
		else
		{
			throw std::exception();
		}
	}
}
}