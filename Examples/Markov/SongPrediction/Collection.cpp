#include "Collection.h"
#include "Track.h"
#include "Album.h"
#include "Artist.h"
#include "Playlist.h"


namespace SongPrediction
{
	Collection::Collection() : artists(), albums(), tracks()
	{
		
	}
	
	
	Artist* Collection::addArtist(std::string name)
	{
		if (artists.count(name) > 0)
		{
			return artists[name];
		}
		
		Artist* artist = new Artist(name);
		artists[name] = artist;
		return artist;
	}
	
	Album* Collection::addAlbum(std::string name, std::string artistN)
	{
		if (artists.count(artistN) <= 0)
		{
			addArtist(artistN);
		}
		
		
		auto artist = artists[artistN];
		
		if (albums.count(name) <= 0)
		{
			albums[name] = std::vector<Album*>();
		}
		else
		{
			for (auto exAlbum : albums[name])
			{
				if (exAlbum->artist == artist)
				{
					return exAlbum;
				}
			}
			
		}
		Album* album = new Album(name, artist);
		albums[name].push_back(album);
		artist->addAlbum(album);
		return album;
	}
	
	Track* Collection::addTrack(std::string name, std::string albumN, std::string artistN)
	{
		if (albums.count(albumN) <= 0)
		{
			addAlbum(albumN, artistN);
		}
		
		if (tracks.count(name) <= 0)
		{
			tracks[name] = std::vector<Track*>();
		}
		
		if (artists.count(artistN) <= 0)
		{
			addArtist(artistN);
		}
		
		auto artist = artists[artistN];
		Album* album = NULL;
		findAlb:
		for (auto alb : artist->albums)
		{
			if (alb->name == albumN)
			{
				album = alb;
				break;
			}
		}
		if (album == NULL)
		{
			addAlbum(albumN, artistN);
			goto findAlb;
		}
		
		for (auto track : album->tracks)
		{
			if (track->name == name)
			{
				return track;
			}
		}
		
		Track* track = new Track(name, album, artist);
		tracks[name].push_back(track);
		
		artist->addTrack(track);
		album->addTrack(track);
		return track;
	}
	
	void Collection::addPlaylist(std::vector<Track*>& vec)
	{
		playlists.push_back(vec);
	}
	
	std::vector<Playlist> Collection::lists()
	{
		std::vector<Playlist> vec;
		for (auto list : playlists)
		{
			vec.push_back(Playlist(list));
		}
		return vec;
	}
}