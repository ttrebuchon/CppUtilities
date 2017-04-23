#pragma once

#include <vector>

namespace SongPrediction
{
	class Track;
	class Artist;
	class Album;
	
	class Playlist
	{
		private:
		std::vector<Track*> list;
		
		public:
		
		Playlist(std::vector<Track*>);
		
		std::vector<Track*> byTrack();
		std::vector<Album*> byAlbum();
		std::vector<Artist*> byArtist();
	};
}