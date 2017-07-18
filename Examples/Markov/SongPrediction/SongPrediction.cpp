#include <iostream>
#include <QUtils/Markov/Markov.h>


#include "SongImport.h"
#include "Collection.h"
#include "Track.h"
#include "Album.h"
#include "Artist.h"
#include "Playlist.h"

#include <ctime>

#include <fstream>
#include <sstream>
#include <vector>

//#define GENERATE

int main()
{
	#ifdef SEED
	srand(time(NULL));
	#endif
	
	#ifdef GENERATE
	
	std::ofstream out;
	out.open("Test.xml");
	out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
	out << "<content>" << std::endl;
	out << "<tracks>\n\n" << std::endl;
	
	
	int maxcount = 1000;
	int count = ((double)rand())/RAND_MAX*maxcount;
	std::cout << "Count: " << count << std::endl;
	std::vector<std::string> tracksV;
	
	
	
	int track_max=20, track_min = 5;
	int album_max=10, album_min=1;
	int artist_count = 5;
	
	for (int i = 0; i < artist_count; i++)
	{
		int albums = (rand() % (album_max - album_min + 1)) + album_min;
		for (int a = 0; a < albums; a++)
		{
			int tracks = (rand() % (track_max - track_min + 1)) + track_min;
			for (int t = 0; t < tracks; t++)
			{
				out << "<track>\n<name>Track" << t << "</name>\n";
				out << "<album>" << "Album" << a << "</album>\n";
				out << "<artist>Artist" << i << "</artist>\n";
				out << "<id>" << i << "_" << a << "_" << t << "</id>\n";
				out << "</track>\n" << std::endl;
				tracksV.push_back((std::stringstream() << i << "_" << a << "_" << t).str());
			}
		}
	}
	out << "\n\n</tracks>\n\n" << std::endl;
	out << "<playlists>\n\n" << std::endl;
	
	std::cout << "Generated tracks." << std::endl;
	
	
	
	out << "<playlist>\n" << std::endl;
	for (int i = 0; i < maxcount; i++)
	{
		if (rand() % 10 == 0)
		{
			out << "\n</playlist>\n" << std::endl;
			out << "<playlist>\n" << std::endl;
		}
		out << "<track><id>" << tracksV[rand()%tracksV.size()] << "</id></track>" << std::endl;
	}
	out << "\n</playlist>" << std::endl;
	out << "\n\n</playlists>" << std::endl;
	out << "</content>" << std::endl;
	out.close();
	std::cout << "Done." << std::endl;
	
	//return 0;
	#endif
	
	
	
	
	
	
	
	
	
	
	
	
	QUtils::Markov::Markov<SongPrediction::Track*> MC;
	MC.equals = [](SongPrediction::Track* t1, SongPrediction::Track* t2) { return t1 == t2; };
	
	std::vector<SongPrediction::Playlist> playlists;
	
	std::string filename = "Test.xml";
	//TODO: Get data file
	
	SongPrediction::Importer importer;
	importer.open(filename);
	importer.import();
	importer.close();
	std::cout << "Imported." << std::endl;
	
	SongPrediction::Collection* col = importer.collection();
	playlists = col->lists();
	
	for (auto pl : playlists)
	{
		MC.AddTrainChain(pl.byTrack());
	}
	
	std::cout << "Training data added." << std::endl;
	
	
	auto plVec = MC.GenerateChain();
	std::cout << "Generated." << std::endl;
	SongPrediction::Playlist generated(*plVec);
	std::cout << "Length: " << generated.byTrack().size() << "\n" << std::endl;
	
	for (auto tr : generated.byTrack())
	{
		std::cout << tr->name << " - " << tr->album->name << " - " << tr->artist->name << std::endl;
	}
	
	std::cout << "\n\nFinished." << std::endl;
}