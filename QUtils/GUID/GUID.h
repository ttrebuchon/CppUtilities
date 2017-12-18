#pragma once

#ifdef QUTILS_HAS_BOOST

#define BOOST_UUID_NO_TYPE_TRAITS
#define QUTILS_GUID_ENABLED

#include <boost/uuid/uuid.hpp>

#endif

#include <string>


#include <json/json.hpp>

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
		
		#else
		char data[16];
		#endif
		public:
		GUID();
		GUID(const GUID&);
		
		static GUID Create();
		
		bool is_nil() const;
		
		static GUID FromString(const std::string);
		
		GUID& operator=(const GUID&);
		
		
		friend class std::hash<GUID>;
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
	
	void to_json(nlohmann::json&, const GUID&);
	void from_json(const nlohmann::json&, GUID&);
	
	static_assert(sizeof(GUID) == 16, "");
	
}
using GUID = GUID_NS::GUID;
}



namespace std
{
	template <>
	class hash<QUtils::GUID>
	{
		public:
		std::size_t operator()(const QUtils::GUID id) const;
	};
}