#include "Playlist.h"
#include "Track.h"

namespace SongPrediction
{
	Playlist::Playlist(std::vector<Track*> tracks) : list(tracks)
	{
		
	}
	
	
	std::vector<Track*> Playlist::byTrack()
	{
		return list;
	}
	
	std::vector<Album*> Playlist::byAlbum()
	{
		std::vector<Album*> albums;
		for (Track* track : list)
		{
			albums.push_back(track->album);
		}
		return albums;
	}
	
	std::vector<Artist*> Playlist::byArtist()
	{
		std::vector<Artist*> artists;
		for (Track* track : list)
		{
			artists.push_back(track->artist);
		}
		return artists;
	}
}