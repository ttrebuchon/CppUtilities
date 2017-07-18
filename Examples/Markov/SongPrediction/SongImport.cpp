#include "SongImport.h"

#include "Collection.h"
#include "Track.h"
#include "Album.h"
#include "Artist.h"

#include "NotImpEx.h"
#include <QUtils/DebugOut/DebugOut.h>
#include <tinyxml2.h>
#include <assert.h>

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

namespace SongPrediction
{
	Importer::Importer() : col(new Collection()), doc(NULL), imported()
	{
		
	}
	
	void Importer::open(std::string filename)
	{
		doc = new XMLDocument();
		doc->LoadFile(filename.c_str());
	}
	
	void Importer::import()
	{
		assert(!doc->NoChildren());
		auto content = doc->FirstChildElement("content");
		
		assert(!content->NoChildren());
		auto tracks = content->FirstChildElement("tracks");
		
		
		assert(!tracks->NoChildren());
		auto track = tracks->FirstChildElement();
		auto last = tracks->LastChildElement();
		while (track != last)
		{
			parseTrack(track);
			track = track->NextSiblingElement();
		}
		parseTrack(last);
		
		
		auto lists = content->FirstChildElement("playlists");
		assert(!lists->NoChildren());
		auto list = lists->FirstChildElement();
		auto lastL = lists->LastChildElement();
		while (list != lastL)
		{
			parseList(list);
			list = list->NextSiblingElement();
		}
		parseList(lastL);
		
	}
	
	void Importer::close()
	{
		delete doc;
		doc = NULL;
	}
	
	Collection* Importer::collection()
	{
		return col;
	}
	
	
	void Importer::parseTrack(XMLElement* track)
	{
		std::string name, album, artist, id;
		
		auto nameN = track->FirstChildElement("name");
		auto albumN = track->FirstChildElement("album");
		auto artistN = track->FirstChildElement("artist");
		auto idN = track->FirstChildElement("id");
		
		name = nameN->GetText();
		album = albumN->GetText();
		artist = artistN->GetText();
		id = idN->GetText();
		
		
		
		imported[id] = col->addTrack(name, album, artist);
	}
	
	void Importer::parseList(XMLElement* list)
	{
		std::vector<Track*> tracks;
		std::string artist, name;
		Track* t;
		
		assert(!list->NoChildren());
		auto last = list->LastChildElement();
		auto track = list->FirstChildElement();
		while (track != NULL)
		{
			std::string id = track->FirstChildElement("id")->GetText();
			if (imported.count(id) > 0)
			{
			t = NULL;
			t = imported[id];
			tracks.push_back(t);
			}
			/*
			name = track->FirstChildElement("name")->GetText();
			artist = track->FirstChildElement("artist")->GetText();
			t = NULL;
			if (col->artists.count(artist) > 0)
			{
				for (auto tr : col->artists[artist]->tracks)
				{
					if (tr->name == name)
					{
						t = tr;
						break;
					}
				}
				if (t != NULL)
				{
					tracks.push_back(t);
				}
			}
			*/
			if (track == last)
			{
				track = NULL;
			}
			else
			{
				track = track->NextSiblingElement();
			}
		}
		
		if (tracks.size() > 0)
		{
			col->addPlaylist(tracks);
		}
	}
}