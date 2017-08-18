#pragma once

#include <string>

namespace QUtils::Network
{
	
	
	std::string getPage(const std::string url);
	
	bool savePage(const std::string url, const std::string path);
	
	bool savePage(const std::string url, const std::string path, bool includeLinks);
}