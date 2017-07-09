#include <QUtils/English/Analysis.h>
#include <QUtils/English/Analysis/Analysis.h>
#include <QUtils/English/Analysis/TokenType.h>
#include <QUtils/String/String.h>
#include <QUtils/Markov/Markov.h>
#include <QUtils/Exception/Exception.h>
#include <iostream>
#include <map>
#include <queue>

namespace QUtils
{
namespace English
{
	namespace Internal
	{
		template <class Key>
		bool Token_Set_Eq(const Key k1, const Key k2)
		{
			return (k1->text() == k2->text());
		}
		
		
		template <class Key>
		auto init_token_set()
		{
			return Token_Set<Key>();
			//return Token_Set<Key>(0, std::hash<std::shared_ptr<Key>>(), Token_Set_Eq<std::shared_ptr<Key>>);
		}
	}
	
	QUTILS_CUSTOM_EXCEPTION(AnalyzerParseException, "Can't parse text");
	
	
	
	Analyzer::Analyzer() : 
	_contents(),
	_tokens(),
	 _words(Internal::init_token_set<Internal::Word>()),
	 _numbers(Internal::init_token_set<Internal::Number>()),
	 _symbols(Internal::init_token_set<Internal::Symbol>()),
	 _punctuation(Internal::init_token_set<Internal::Punctuation>()),
	 _sentences(Internal::init_token_set<Internal::Sentence>()),
	 _distinctTokens(Internal::init_token_set<Internal::Token>()),
	 contents(_contents),
	 tokens(_tokens),
	 words(_words),
	 numbers(_numbers),
	 symbols(_symbols),
	 punctuation(_punctuation),
	 sentences(_sentences),
	 distinctTokens(_distinctTokens)
	{
		
	}
	
	Analyzer::Analyzer(std::ifstream& file) : Analyzer()
	{
		file.seekg(0, std::ios::end);
		_contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&_contents[0], _contents.size());
	}
	
	Analyzer::Analyzer(const std::string& contents) : Analyzer()
	{
		_contents = contents;
	}
	
	Analyzer::Analyzer(const std::vector<std::string>& lines) : Analyzer()
	{
		if (lines.size() > 0)
		{
		_contents = lines.at(0);
		for (auto it = lines.begin()+1; it != lines.end(); ++it)
		{
			_contents += "\n" + *it;
		}
		}
	}
	
	void Analyzer::parse()
	{
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
		char last_c;
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
				last_c = c;
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
					parseToken(tmp);
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
					parseToken(tmp);
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
						last_c = c;
						continue;
					}
					else
					{
						parseToken(tmp);
						tmp = c;
					}
					break;
					
					case Number:
					if (c == ',' || c == '.')
					{
						tmp += c;
						break;
					}
					
					case Punc:
					if (c == '.' && last_c == '.')
					{
						tmp += c;
						break;
					}
					
					
					default:
					parseToken(tmp);
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
					parseToken(tmp);
					tmp = c;
				}
				last = Whitespace;
			}
			else if (isSymbol(c))
			{
				switch (last)
				{
					default:
					parseToken(tmp);
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
			
			last_c = c;
		}
		}
		
		auto clearNulls = [](auto& tokens)
		{
			//bool reachedEnd = false;
			int j;
			for (int i = 0; i < tokens.size(); i++)
			{
				if (tokens[i] == NULL)
				{
					for (j = i+1; j < tokens.size(); j++)
					{
						if (tokens[j] != NULL)
						{
							tokens[i] = tokens[j];
							tokens[j] = NULL;
							break;
						}
					}
					if (j == tokens.size())
					{
						tokens.erase(tokens.begin()+i, tokens.end());
						break;
					}
				}
				
			}
			
		};
		
		auto simplifyTokens = [clearNulls](auto& tokens)
		{
		clearNulls(tokens);
		
		std::map<int, std::vector<typename std::remove_reference<decltype(tokens[0])>::type>> hashTable;
		
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
		
		
		
		
		
		
		
		
		
		
		
		//Combine adjacent exclamation and question marks
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
			lastWasPunc = (_tokens[0]->type() == Punctuation);
		}
		int lastIndex = 0;
		for (int i = 1; i < _tokens.size(); i++)
		{
			if (_tokens[i] == NULL)
			{
				continue;
			}
			if (_tokens[i]->type() == Punctuation)
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
		
		
		
		//Insert tokens into categories
		{
			_words.clear();
			_punctuation.clear();
			_symbols.clear();
			_numbers.clear();
			
			for (auto token : tokens)
			{
				switch (token->type())
				{
					case Word:
					_words.insert(std::dynamic_pointer_cast<Internal::Word>(token));
					break;
					
					case Number:
					_numbers.insert(std::dynamic_pointer_cast<Internal::Number>(token));
					break;
					
					case Symbol:
					_symbols.insert(std::dynamic_pointer_cast<Internal::Symbol>(token));
					break;
					
					case Punctuation:
					_punctuation.insert(std::dynamic_pointer_cast<Internal::Punctuation>(token));
					break;
					
					case Whitespace:
					break;
					
					default:
					std::cerr << "Unknown token type of \"" << token->text() << "\"!\n";
					throw std::exception();
				}
			}
			
		}
		
		
		
		//Parse parentheses/brackets
		{
			bool openChar[2] = {false, false};
			std::function<int(const int, bool*, const char)> parsePB;
			
			parsePB = [&](const int index, bool* openChar, const char target) -> int
			{
				std::string text;
				for (int i = index+1; i < tokens.size(); i++)
				{
					if (tokens[i]->type() == Punctuation)
					{
						text = tokens[i]->text();
						if (text == "(")
						{
							bool alreadyTrue = openChar[0];
							openChar[0] = true;
							i = parsePB(i, openChar, ')');
							openChar[0] = alreadyTrue;
						}
						else if (text == "[")
						{
							bool alreadyTrue = openChar[1];
							openChar[1] = true;
							i = parsePB(i, openChar, ']');
							openChar[1] = alreadyTrue;
						}
						else if (text == ")")
						{
							if (openChar[0])
							{
								if (target != ')')
								{
									return i-1;
								}
								std::vector<std::shared_ptr<Internal::Token>> segment(tokens.begin()+index+1, tokens.begin()+i-1);
								clearNulls(segment);
								auto ptr = std::make_shared<Internal::Parentheses>(std::dynamic_pointer_cast<Internal::Punctuation>(tokens[index]), segment, std::dynamic_pointer_cast<Internal::Punctuation>(tokens[i]));
								_tokens[index] = ptr;
								for (int j = index+1; j <= i; j++)
								{
									_tokens[j] = NULL;
								}
								return i+1;
							}
						}
						else if (text == "]")
						{
							if (openChar[1])
							{
								if (target != ']')
								{
									return i-1;
								}
								std::vector<std::shared_ptr<Internal::Token>> segment(tokens.begin()+index+1, tokens.begin()+i-1);
								clearNulls(segment);
								auto ptr = std::make_shared<Internal::Parentheses>(std::dynamic_pointer_cast<Internal::Punctuation>(tokens[index]), segment, std::dynamic_pointer_cast<Internal::Punctuation>(tokens[i]));
								_tokens[index] = ptr;
								for (int j = index+1; j <= i; j++)
								{
									_tokens[j] = NULL;
								}
								return i+1;
							}
						}
					}
				}
				return tokens.size();
			};
			
			
			
			
			
			
			std::string text;
			for (int i = 0; i < tokens.size(); i++)
			{
				
				if (tokens[i]->type() == Punctuation)
				{
					text = tokens[i]->text();
					if (text == "(")
					{
						openChar[0] = true;
						i = parsePB(i, openChar, ')');
						openChar[0] = false;
					}
					else if (text == "[")
					{
						openChar[1] = true;
						i = parsePB(i, openChar, ']');
						openChar[1] = false;
					}
				}
			}
			
		}
		
		simplifyTokens(_tokens);
		
		
		
		
		
		
		
		//Parse into sentences
		{
			std::queue<int> sentenceStartIndexes;
			std::queue<int> sentenceEndIndexes;
			for (int i = 0; i < tokens.size(); i++)
			{
				if (tokens[i] == NULL)
				{
					continue;
				}
				if (tokens[i]->type() == Punctuation)
				{
					for (auto c : tokens[i]->text())
					{
						if (endsSentence(c))
						{
							sentenceEndIndexes.push(i);
							break;
						}
					}
				}
				else if (tokens[i]->type() == Word)
				{
					if (isCapital(tokens[i]->text()[0]))
					{
						sentenceStartIndexes.push(i);
					}
				}
			}
		
		
			int startIndex = -1;
			int endIndex = -1;
			while (sentenceStartIndexes.size() > 0)
			{
				while (sentenceEndIndexes.front() < sentenceStartIndexes.front() && sentenceEndIndexes.size() > 1)
				{
					sentenceEndIndexes.pop();
					if (sentenceEndIndexes.size() == 0)
					{
						break;
					}
				}
				if (sentenceEndIndexes.size() == 0)
				{
					break;
				}
				startIndex = sentenceStartIndexes.front();
				endIndex = sentenceEndIndexes.front();
				
				std::vector<std::shared_ptr<Internal::Token>> segment(tokens.begin()+startIndex, tokens.begin() + endIndex);
				auto ptr = std::make_shared<Internal::Sentence>(segment, std::dynamic_pointer_cast<Internal::Punctuation>(tokens[endIndex]));
				_tokens[startIndex] = ptr;
				for (int j = startIndex+1; j <= endIndex; j++)
				{
					_tokens[j] = NULL;
				}
				while ((sentenceStartIndexes.size() > 0 ? (sentenceStartIndexes.front() < endIndex) : false))
				{
					sentenceStartIndexes.pop();
				}
			}
		}
		
		simplifyTokens(_tokens);
		
		
		//Insert sentences into category
		{
			_sentences.clear();
			
			for (auto token : tokens)
			{
				if (token->type() == Sentence)
				{
					_sentences.insert(std::dynamic_pointer_cast<Internal::Sentence>(token));
				}
			}
		}
		
		
		//DEBUG
		{
		std::unordered_set<std::string> strs;
		std::string text;
		for (auto w : words)
		{
			text = w->text();
			if (strs.count(text) > 0)
			{
				std::cerr << "Duplicate found: " << text << "\n";
				throw std::exception();
			}
			strs.insert(text);
		}
		}
		
		//DEBUG
		{
		std::unordered_set<std::string> strs;
		std::string text;
		for (auto w : sentences)
		{
			text = w->text();
			if (strs.count(text) > 0)
			{
				std::cerr << "Duplicate found: \"" << text << "\"\n";
				throw std::exception();
			}
			strs.insert(text);
		}
		}
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
	
	
	std::vector<std::shared_ptr<const Internal::Token>> Analyzer::expand() const
	{
		std::vector<std::shared_ptr<const Internal::Token>> eTokens;
		
		std::function<void(const std::shared_ptr<const Internal::Token>)> getTokens;
		
		getTokens = [&getTokens, &eTokens] (const std::shared_ptr<const Internal::Token> token)
		{
			auto subs = token->expand();
			if (subs.size() > 1)
			{
				for (auto subToken : subs)
				{
					getTokens(subToken);
				}
			}
			else
			{
				eTokens.push_back(subs[0]);
			}
		};
		
		for (auto token : tokens)
		{
			getTokens(token);
		}
		
		
		return eTokens;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void Analyzer::parseToken(const std::string text)
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
				_tokens.push_back(std::make_shared<Internal::Whitespace>(text));
			}
		}
		else if (symbols)
		{
			_tokens.push_back(std::make_shared<Internal::Symbol>(text));
		}
		else if (letters)
		{
			auto ptr = std::make_shared<Internal::Word>(text);
			_tokens.push_back(ptr);
			//_words.insert(ptr);
		}
		else if (punctuation)
		{
			if (numbers)
			{
				_tokens.push_back(std::make_shared<Internal::Number>(text));
			}
			else
			{
				_tokens.push_back(std::make_shared<Internal::Punctuation>(text));
			}
		}
		else if (numbers)
		{
			_tokens.push_back(std::make_shared<Internal::Number>(text));
		}
		else
		{
			throw AnalyzerParseException().Msg("\"" + text + "\"");
		}
	}
}
}