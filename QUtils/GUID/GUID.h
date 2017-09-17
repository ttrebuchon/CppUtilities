#pragma once

#ifdef QUTILS_HAS_BOOST

#define BOOST_UUID_NO_TYPE_TRAITS
#define QUTILS_GUID_ENABLED

#include <boost/uuid/uuid.hpp>

#endif

#include <string>

namespace QUtils
{
namespace GUID_NS
{
	
	class GUID
	{
		private:
		#ifdef QUTILS_HAS_BOOST
		boost::uuids::uuid uuid;
		
		GUID(const boost::uuids::uuid);
		#endif
		public:
		GUID();
		GUID(const GUID&);
		
		static GUID Create();
		
		bool is_nil() const;
		
		static GUID FromString(const std::string);
		
		
		friend std::ostream& operator<<(std::ostream&, GUID const&);
		friend std::istream& operator>>(std::istream&, GUID&);
		friend std::string to_string(GUID const& u);
		friend std::wstring to_wstring(GUID const& u);
		friend bool operator==(GUID const&, GUID const&);
		friend bool operator!=(GUID const&, GUID const&);
		friend bool operator<(GUID const&, GUID const&);
		friend bool operator>(GUID const&, GUID const&);
		friend bool operator<=(GUID const&, GUID const&);
		friend bool operator>=(GUID const&, GUID const&);
	};
	
	std::ostream& operator<<(std::ostream&, GUID const&);
	
	std::istream& operator>>(std::istream&, GUID&);
	
	std::string to_string(GUID const& u);
	std::wstring to_wstring(GUID const& u);
	
	
	bool operator==(GUID const&, GUID const&);
	bool operator!=(GUID const&, GUID const&);
	bool operator<(GUID const&, GUID const&);
	bool operator>(GUID const&, GUID const&);
	bool operator<=(GUID const&, GUID const&);
	bool operator>=(GUID const&, GUID const&);
	
}
using GUID = GUID_NS::GUID;
}