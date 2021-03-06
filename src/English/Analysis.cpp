#include <QUtils/English/Analysis.h>
#include <QUtils/English/Analysis/Analysis.h>
#include <QUtils/English/Analysis/TokenType.h>
#include <QUtils/String/String.h>
#include <QUtils/Markov/Markov.h>
#include <QUtils/Exception/Exception.h>
#include <QUtils/Exception/NotImplemented.h>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <array>
#include <tuple>
#include <math.h>

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
	QUTILS_CUSTOM_EXCEPTION(AnalyzerFileException, "Invalid file stream");
	
	
	
	Analyzer::Analyzer() : 
	_contents(),
	_tokens(),
	 _words(Internal::init_token_set<Internal::Word>()),
	 _numbers(Internal::init_token_set<Internal::Number>()),
	 _symbols(Internal::init_token_set<Internal::Symbol>()),
	 _punctuation(Internal::init_token_set<Internal::Punctuation>()),
	 _sentences(Internal::init_token_set<Internal::Sentence>()),
	 _distinctTokens(Internal::init_token_set<Internal::Token>()),
	 _subTokens(),
	 _tokenIndexes(),
	 _equivalents(),
	 _tokensByText(),
	 _clusteringRatings(),
	 contents(_contents),
	 tokens(_tokens),
	 words(_words),
	 numbers(_numbers),
	 symbols(_symbols),
	 punctuation(_punctuation),
	 sentences(_sentences),
	 distinctTokens(_distinctTokens),
	 subTokens(_subTokens),
	 tokenIndexes(_tokenIndexes),
	 equivalents(_equivalents),
	 clusteringRatings(_clusteringRatings)
	{
		
	}
	
	Analyzer::Analyzer(std::ifstream& file) : Analyzer()
	{
		if (!file.is_open())
		{
			throw AnalyzerFileException();
		}
		file.seekg(0, std::ios::end);
		if (file.tellg() < 0)
		{
			throw AnalyzerFileException();
		}
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
		sanitize(_contents);
		std::string tmp;
		enum Last_t
		{
			Letter = 0,
			Number = 1,
			Whitespace = 2,
			Punc = 3,
			Symbol = 4,
		};
		Last_t last = Whitespace;
		char last_c = '\0';
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
		
		auto& _dTokens = this->_distinctTokens;
		
		auto simplifyTokens = [clearNulls, &_dTokens](auto& tokens, bool addDistinct = true)
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
				if (addDistinct)
				{
				_dTokens.insert(token);
				}
			}
		}
		
		};
		
		
		
		
		
		
		
		
		
		
		
		//Combine adjacent exclamation and question marks
		simplifyTokens(_tokens, false);
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
				
				auto uCopy = token->clone();
				uCopy->toLowerCase();
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
				
				clearNulls(segment);
				
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
		
		{
			std::vector<std::shared_ptr<Internal::Token>> nTokens;
			for (auto token : tokens)
			{
				if (token != NULL)
				{
					nTokens.push_back(token);
				}
			}
			this->_tokens = nTokens;
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
		
		
		//Index the tokens
		{
			auto& m = this->_tokenIndexes;
			int fullIndex = 0;
			for (int i = 0; i < this->tokens.size(); i++)
			{
				m[this->tokens[i]].push_back(fullIndex);
				auto subM = this->tokens[i]->indexes();
				int inc = 0;
				for (auto pair : subM)
				{
					for (auto subIndex : pair.second)
					{
						m[pair.first].push_back(subIndex+fullIndex);
						if (subIndex > inc)
						{
							inc = subIndex;
						}
					}
				}
				++inc;
				fullIndex += inc;
			}
		}
		
		
		//Map tokens by text
		{
			for (auto token : distinctTokens)
			{
				_tokensByText[token->text()] = token;
			}
		}
		
	}
	
	
	
	
	void Analyzer::calcSubtokens()
	{
		_subTokens.clear();
		std::queue<std::shared_ptr<Internal::Token>> waiting;
		std::unordered_set<std::shared_ptr<Internal::Token>> processed;
		for (auto token : tokens)
		{
			if (processed.count(token) <= 0)
			{
				waiting.push(token);
				processed.insert(token);
			}
		}
		
		while (waiting.size() > 0)
		{
			auto next = waiting.front();
			auto subs = next->subTokens();
			for (auto sub : subs)
			{
				_subTokens[sub].insert(next);
				
				if (processed.count(sub) <= 0)
				{
					waiting.push(sub);
					processed.insert(sub);
				}
			}
			waiting.pop();
		}
		
	}
	
	
	
	void Analyzer::calcEquivalents()
	{
		_equivalents.clear();
		std::map<std::string, std::set<std::shared_ptr<Internal::Token>>> values;
		std::map<std::shared_ptr<Internal::Token>, std::string> lowerStrs;
		
		for (auto token : distinctTokens)
		{
			if (lowerStrs.count(token) > 0)
			{
				throw std::exception();
			}
			std::string text = QUtils::String(token->text());
			lowerStrs[token] = text;
			values[text].insert(token);
		}
		
		for (auto pair : values)
		{
			for (auto token : pair.second)
			{
				_equivalents[token] = pair.second;
				_equivalents[token].erase(token);
			}
		}
	}
	
	
	void Analyzer::calcDistances()
	{
		std::set<std::shared_ptr<Internal::Token>> processed;
		std::map<std::shared_ptr<Internal::Token>, std::vector<int>> indexes;
		
		for (auto word : words)
		{
			if (processed.count(word) > 0)
			{
				continue;
			}
			auto wIndexes = _tokenIndexes[word];
			for (auto i : wIndexes)
			{
				indexes[word].push_back(i);
			}
			processed.insert(word);
			for (auto eq : equivalents.at(word))
			{
				wIndexes = _tokenIndexes[eq];
			for (auto i : wIndexes)
			{
				indexes[word].push_back(i);
			}
			processed.insert(eq);
			}
		}
		
		//Formula: N/n*sqrt(sum(i, sum(j, 1/(Index(i) - Index(j))^2)))
		
		for (auto pair : indexes)
		{
			auto ptr = std::make_shared<std::vector<std::pair<int, long double>>>();
			
			
			auto word = std::dynamic_pointer_cast<Internal::Word>(pair.first);
			_clusteringRatings[word] = ptr;
			
			for (auto eq : _equivalents[pair.first])
			{
				word = std::dynamic_pointer_cast<Internal::Word>(eq);
				_clusteringRatings[word] = ptr;
				
			}
			
			
			word = std::dynamic_pointer_cast<Internal::Word>(pair.first);
			
			long double val;
			for (auto i = 0; i < pair.second.size(); ++i)
			{
				val = 0;
				auto index = pair.second[i];
				
				for (auto j = 0; j < pair.second.size(); ++j)
				{
					if (index == pair.second[j])
					{
						continue;
					}
					val += sqrt(static_cast<long double>(1)/((index - pair.second[j])*(index - pair.second[j])));
				}
				int occurrences = this->_tokenIndexes.at(pair.first).size();
				
				for (auto eq : equivalents.at(pair.first))
				{
					occurrences += _tokenIndexes.at(eq).size();
				}
				
				val *= static_cast<long double>(1)/occurrences;
				ptr->emplace_back(index, val);
			}
		}
		
		//throw NotImp();
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
	
	
	
	std::shared_ptr<const Internal::Token> Analyzer::getToken(std::string text) const
	{
		if (_tokensByText.count(text) > 0)
		{
			return _tokensByText.at(text);
		}
		return NULL;
	}
	
	std::shared_ptr<Internal::Token> Analyzer::getToken(std::string text)
	{
		if (_tokensByText.count(text) > 0)
		{
			return _tokensByText.at(text);
		}
		return NULL;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	void Analyzer::parseToken(const std::string text)
	{
		if (text == "")
		{
			return;
		}
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
	
	unsigned int Analyzer::sanitize(std::string& str)
	{
		unsigned int count = 0;
		
		std::tuple<std::string, std::string> bads[] = { std::make_tuple("‘", "'"), std::make_tuple("’", "'"), std::make_tuple("“", "\""), std::make_tuple("”", "\""), std::make_tuple("\r\n", "\n")};
		
		decltype(str.find("")) it = 0;
		for (auto bad : bads)
		{
			it = 0;
			while ((it = str.find(std::get<0>(bad), it)) != std::string::npos)
			{
				str.replace(it, std::get<0>(bad).length(), std::get<1>(bad));
				count++;
			}
		}
		
		
		
		return count;
	}
}
}