//#ifndef INCLUDED_SONG_IMPORT_H
//#define INCLUDED_SONG_IMPORT_H
#pragma once

#include <string>
#include <map>

namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

namespace SongPrediction
{
	class Collection;
	class Track;
	
	class Importer
	{
		private:
		Collection* col;
		tinyxml2::XMLDocument* doc;
		std::map<std::string, Track*> imported;
		
		void parseTrack(tinyxml2::XMLElement*);
		void parseList(tinyxml2::XMLElement*);
		
		public:
		Importer();
		
		void open(std::string file);
		void import();
		void close();
		
		Collection* collection();
		
	};
	
}


//#endif