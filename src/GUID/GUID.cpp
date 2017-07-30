#include <QUtils/GUID/GUID.h>
#include <QUtils/Exception/NotAvailable.h>
#include <iostream>


#ifdef QUTILS_HAS_BOOST

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#endif

namespace QUtils
{
namespace GUID_NS
{
	#define NOT_AVAIL_MSG "The GUID module requires boost/uuid"
	
	
	#ifdef QUTILS_HAS_BOOST
	
	boost::uuids::random_generator guid_generator;
	
	GUID::GUID(const boost::uuids::uuid id) : uuid(id)
	{}
	#endif
	
	
	GUID::GUID()
	#ifdef QUTILS_HAS_BOOST
	 : uuid()
	#endif
	{	
	}
	
	GUID::GUID(const GUID& id)
	#ifdef QUTILS_HAS_BOOST
	 : uuid(id.uuid)
	 #endif
	{}
	
	
	GUID GUID::Create()
	{
	#ifdef QUTILS_HAS_BOOST
		return GUID(guid_generator());
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	
	bool GUID::is_nil() const
	{
	#ifdef QUTILS_HAS_BOOST
		return uuid.is_nil();
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	
	
	
	
	
	std::ostream& operator<<(std::ostream& out, GUID const& id)
	{
	#ifdef QUTILS_HAS_BOOST
		return (out << id.uuid);
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	std::istream& operator>>(std::istream& in, GUID& id)
	{
	#ifdef QUTILS_HAS_BOOST
		return (in >> id.uuid);
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	std::string to_string(GUID const& id)
	{
	#ifdef QUTILS_HAS_BOOST
		return to_string(id.uuid);
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	std::wstring to_wstring(GUID const& id)
	{
	#ifdef QUTILS_HAS_BOOST
		return to_wstring(id.uuid);
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	
	
	bool operator==(GUID const& lhs, GUID const& rhs)
	{
	#ifdef QUTILS_HAS_BOOST
		return lhs.uuid == rhs.uuid;
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	bool operator!=(GUID const& lhs, GUID const& rhs)
	{
	#ifdef QUTILS_HAS_BOOST
		return lhs.uuid != rhs.uuid;
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	bool operator<(GUID const& lhs, GUID const& rhs)
	{
	#ifdef QUTILS_HAS_BOOST
		return lhs.uuid < rhs.uuid;
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	bool operator>(GUID const& lhs, GUID const& rhs)
	{
	#ifdef QUTILS_HAS_BOOST
		return lhs.uuid > rhs.uuid;
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	bool operator<=(GUID const& lhs, GUID const& rhs)
	{
	#ifdef QUTILS_HAS_BOOST
		return lhs.uuid <= rhs.uuid;
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	bool operator>=(GUID const& lhs, GUID const& rhs)
	{
	#ifdef QUTILS_HAS_BOOST
		return lhs.uuid >= rhs.uuid;
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
}
}