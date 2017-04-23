#pragma once

#include <string>

namespace SongPrediction
{
	class Album;
	class Artist;
	
	class Track
	{
		public:
		std::string name;
		Album* album;
		Artist* artist;
		
		
		Track(std::string title, Album*, Artist*);
		
		
	};
	
	
}