#pragma once

#include <string>
#include <vector>


namespace SongPrediction
{
	class Artist;
	class Track;
	
	class Album
	{
		public:
		std::string name;
		
		Artist* artist;
		std::vector<Track*> tracks;
		
		
		Album(std::string name, Artist*);
		
		void addTrack(Track*);
	};
	
	
}