#include "Artist.h"


namespace SongPrediction
{
	Artist::Artist(std::string name) : name(name), albums(), tracks()
	{
		
	}
	
	void Artist::addAlbum(Album* album)
	{
		albums.push_back(album);
	}
	
	void Artist::addTrack(Track* track)
	{
		tracks.push_back(track);
	}
}