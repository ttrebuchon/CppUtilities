#pragma once

#include <string>
#include <map>
#include <vector>

namespace SongPrediction
{
	class Track;
	class Album;
	class Artist;
	class Playlist;
	
	class Collection
	{
		private:
		
		public:
		std::map<std::string, Artist*> artists;
		std::map<std::string, std::vector<Album*>> albums;
		std::map<std::string, std::vector<Track*>> tracks;
		
		std::vector<std::vector<Track*>> playlists;
		
		Collection();
		
		Artist* addArtist(std::string name);
		Album* addAlbum(std::string name, std::string artist);
		Track* addTrack(std::string name, std::string album, std::string artist);
		void addPlaylist(std::vector<Track*>& vec);
		
		std::vector<Playlist> lists();
	};
	
}