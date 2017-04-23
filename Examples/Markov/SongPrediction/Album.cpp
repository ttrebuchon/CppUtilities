#include "Album.h"


namespace SongPrediction
{
	Album::Album(std::string name, Artist* artist) : name(name), artist(artist), tracks()
	{
		
	}
	
	void Album::addTrack(Track* track)
	{
		tracks.push_back(track);
	}
}