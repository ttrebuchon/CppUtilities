#pragma once
#include <string>
#include <vector>
#include <map>

namespace QUtils
{
namespace English
{
	enum PartOfSpeech
	{
		Noun = 0,
		Verb = 1,
		Adjective = 2,
		Adverb = 3,
	};
	
	
	enum Lang
	{
		English = 0,
	};
	
	struct FileTable
	{
	static std::string File(const Lang l)
	{
		switch (l)
		{
			case English:
			return "Data/th_en_US_new";
			
			default:
			return "";
		}
	}
	};
	
	class Word
	{
		private:
		
		std::string definition;
		
		
		public:
		Word(std::string name, PartOfSpeech);
		const std::string word;
		std::vector<Word*> synonyms;
		const PartOfSpeech type;
		
	};
	
	
	class Language
	{
		private:
		static Language* english;
		
		std::map<std::string, std::vector<Word*>> words;
		std::map<PartOfSpeech, std::map<std::string, Word*>> wordsByType;
		std::string filename;
		
		public:
		Language(Lang = English);
		
		
		bool load();
		
		long long count() const;
		
		const std::map<std::string, std::vector<Word*>>& Words() const;
		
		const std::map<PartOfSpeech, std::map<std::string, Word*>>& WordsByType() const;
		
	};
	
	
}
}