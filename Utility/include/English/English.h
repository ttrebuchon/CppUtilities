#pragma once
#include <string>
#include <vector>
#include <map>

namespace Util
{
namespace English
{
	enum PartOfSpeech
	{
		Noun = 0,
		Verb = 1,
		Adjective = 2,
	};
	
	
	enum Lang
	{
		English = 0,
	};
	
	static const std::map<Lang, std::string>& FileTable()
	{
		static std::map<Lang, std::string> table;
		if (table.size() == 0)
		{
			table = std::map<Lang, std::string>{
				{English, "english-core-wordnet.txt"},
			};
		}
		
		return table;
	};
	
	class Word
	{
		private:
		std::string word;
		std::string definition;
		std::vector<Word*> synonyms;
		PartOfSpeech type;
		
		public:
		Word(std::string name, PartOfSpeech);
		
		
		
	};
	
	
	class Language
	{
		private:
		static Language* english;
		
		std::map<std::string, Word*> words;
		std::string filename;
		
		public:
		Language(Lang = English);
		
		
		bool load();
		
	};
	
	
}
}