#include "../Tests.h"
#include <English/English.h>
#include <algorithm>


bool Testing::English()
{
	auto english = new Utils::English::Language(Utils::English::Lang::English);
	english->load();
	dout << "Words: " << english->count() << std::endl;
	
	auto& WBT = english->WordsByType();
	for (auto POS : WBT)
	{
		dout << "Checking POS " << POS.first << std::endl;
		std::vector<std::string> words;
		for (auto word : POS.second)
		{
			words.push_back(word.first);
			assert_ex(word.first != "");
		}
		
		std::sort(words.begin(), words.end());
		
		std::vector<std::string> allWords;
		for (auto word : POS.second)
		{
			allWords.push_back(word.first);
			assert_ex(word.first[0] != ' ');
			for (auto syn : word.second->synonyms)
			{
				allWords.push_back(syn->word);
				assert_ex(syn->word[0] != ' ');
			}
		}
		
		std::sort(allWords.begin(), allWords.end());
		auto newEnd = std::unique(allWords.begin(), allWords.end());
		allWords.resize(newEnd - allWords.begin());
		dout << "allWords size: " << allWords.size() << std::endl;
	}
	
	return true;
}