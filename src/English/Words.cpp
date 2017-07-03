#include <QUtils/English/Words.h>
#include <fstream>
#include <string>
#include <queue>

namespace Util
{
namespace English
{
	Word::Word(std::string name, PartOfSpeech pos) : definition(), word(name), synonyms(), type(pos)
	{
		
	}
	
	
	
	
	
	
	Language::Language(Lang lang) : words(), wordsByType(), filename(FileTable::File(lang))
	{
		
	}
	
	bool Language::load()
	{
		std::ifstream idxFile(filename + ".idx");
		
		std::queue<std::string> lines;
		std::string sizeLine;
		std::string tmp;
		//unsigned long size;
		std::ifstream dataFile;
		size_t strIndex;
		std::string name;
		unsigned short dupCount;
		std::string POSstr;
		PartOfSpeech POS;
		Word* word = NULL;
		std::string synonym;
		Word* synonymPtr = NULL;
		
		
		//Throwaway read to seek to the second line, with the size
		getline(idxFile, sizeLine);
		getline(idxFile, sizeLine);
		idxFile.close();
		
		//size = std::stoul(sizeLine);
		
		
		
		
		dataFile.open(filename + ".dat");
		//Throwaway read to handle ISO format line
		getline(dataFile, tmp);
		
		
		while (getline(dataFile, tmp))
		{
			
			
			strIndex = tmp.find('|');
			if (strIndex == std::string::npos)
			{
				throw std::exception();
			}
			name = tmp.substr(0, strIndex);
			dupCount = std::stoi(tmp.substr(strIndex+1));
			
			for (short i = 0; i < dupCount; i++)
			{
				if (!getline(dataFile, tmp))
				{
					//TODO
					throw std::exception();
				}
				
				
				if ((strIndex = tmp.find(')')) == std::string::npos)
				{
					//TODO
					throw std::exception();
				}
				
				POSstr = tmp.substr(1, strIndex-1);
				
				if (POSstr == "noun")
				{
					POS = Noun;
				}
				else if (POSstr == "verb")
				{
					POS = Verb;
				}
				else if (POSstr == "adv")
				{
					POS = Adverb;
				}
				else if (POSstr == "adj")
				{
					POS = Adjective;
				}
				else
				{
					//TODO
					throw std::exception();
				}
				if ((word = this->wordsByType[POS][name]) == NULL)
				{
					word = this->wordsByType[POS][name] = new Word(name, POS);
					this->words[name].push_back(word);
				}
				
				tmp = tmp.substr(strIndex+2);
				
				while ((strIndex = tmp.find('|')) != std::string::npos)
				{
					synonym = tmp.substr(0, strIndex);
					
					tmp = tmp.substr(strIndex+1);
				}
				while (tmp[0] == ' ')
				{
					tmp = tmp.substr(1);
					if (tmp.length() == 0)
					{
						break;
					}
					
				}
				if (tmp.length() == 0)
				{
					continue;
				}
				synonym = tmp;
				
				if ((synonymPtr = this->wordsByType[POS][synonym]) == NULL)
				{
					words[synonym].push_back(
						synonymPtr = wordsByType[POS][synonym] = new Word(synonym, POS)
					);
				}
				word->synonyms.push_back(synonymPtr);
				
			}
			
			
			
			
		}
		
		
		dataFile.close();
		return true;
	}
	
	
	
	long long Language::count() const
	{
		long long sum = 0;
		for (auto POS : wordsByType)
		{
			sum += POS.second.size();
		}
		return sum;
	}
	
	
	const std::map<std::string, std::vector<Word*>>& Language::Words() const
	{
		return words;
	}
	
	const std::map<PartOfSpeech, std::map<std::string, Word*>>& Language::WordsByType() const
	{
		return wordsByType;
	}
	
}
}