#include "../Tests_Helpers.h"

#include <QUtils/Serialization/Serialization.h>

//#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <sstream>

DEF_TEST(BoostBased_Serialization)
{
	{
	std::stringstream ar_buf;
	{
		boost::archive::text_oarchive ar(ar_buf);
		ar << 4;
		ar << 5;
		ar << 6;
		ar << 7;
		ar & 8;
		
		ar << std::string("Some Text to Archive!");
		
		ar << std::string("Some More Text to \n_Archive!");
		
		ar << std::string("820");
		
	}
	
	dout << "Archive Contents:\n{ ";
	dout << ar_buf.str();
	dout << " }\n";
	
	{
		boost::archive::text_iarchive ar(ar_buf);
		int x;
		ar >> x;
		assert_ex(x == 4);
		ar >> x;
		assert_ex(x == 5);
		ar >> x;
		assert_ex(x == 6);
		ar >> x;
		assert_ex(x == 7);
		ar >> x;
		assert_ex(x == 8);
		
		std::string y;
		ar >> y;
		dout << "'" << y << "'\n";
		ar >> y;
		dout << "'" << y << "'\n";
		
		ar >> y;
		assert_ex(std::stoi(y) == 820);
	}
	
	}
	
	
	{
		std::stringstream ar_buf;
		int x = 40, y = 50, z = 80;
		{
			boost::archive::xml_oarchive ar(ar_buf);
			
			ar << BOOST_SERIALIZATION_NVP(x);
			ar << BOOST_SERIALIZATION_NVP(y);
			ar << BOOST_SERIALIZATION_NVP(z);
		}
		
		x = y = z = 0;
		
		dout << "Archive Contents:\n{ ";
		dout << ar_buf.str();
		dout << " }\n";
		
		{
			boost::archive::xml_iarchive ar(ar_buf);
			
			ar >> BOOST_SERIALIZATION_NVP(x);
			ar >> BOOST_SERIALIZATION_NVP(y);
			ar >> BOOST_SERIALIZATION_NVP(z);
			
			assert_ex(x == 40);
			assert_ex(y == 50);
			assert_ex(z == 80);
		}
		
		
	}
	
	return true;
}