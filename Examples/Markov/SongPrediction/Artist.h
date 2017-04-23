#pragma once

#include <string>
#include <vector>
namespace SongPrediction
{
	class Album;
	class Track;
	
	class Artist
	{
		public:
		std::string name;
		
		std::vector<Album*> albums;
		std::vector<Track*> tracks;
		
		
		Artist(std::string name);
		
		void addAlbum(Album*);
		void addTrack(Track*);
		
	};
	
}