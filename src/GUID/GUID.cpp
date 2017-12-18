#include <QUtils/GUID/GUID.h>
#include <QUtils/Exception/NotAvailable.h>
#include <iostream>
#include <QUtils/Multi/Lockable.h>


#ifdef QUTILS_HAS_BOOST

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/functional/hash.hpp>

#endif

namespace QUtils
{
namespace GUID_NS
{
	#define NOT_AVAIL_MSG "The GUID module requires boost/uuid"
	
	
	#ifdef QUTILS_HAS_BOOST
	
	#ifdef __GNUC__
	#define TLS __thread
	#else
	#define TLS thread_local
	#endif
	
	namespace Internal
	{
		class MT_Generator : public QUtils::Multi::Lockable
		{
			public:
			boost::uuids::random_generator generator;
			boost::uuids::string_generator str_generator;
			
			auto operator()()
			{
				std::lock_guard<MT_Generator> lock(*this);
				return generator();
			}
			
			auto operator()(const std::string str)
			{
				std::lock_guard<MT_Generator> lock(*this);
				return str_generator(str);
			}
		};
	}
	
	/*TLS boost::uuids::random_generator guid_generator;*/
	static Internal::MT_Generator guid_generator;
	
	
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
		/*static TLS boost::mt19937 inner;
		static TLS boost::uuids::random_generator guid_generator(inner);*/
		//boost::uuids::random_generator gen;
		return GUID(guid_generator());
		//return GUID(gen());
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
	
	GUID GUID::FromString(const std::string value)
	{
	#ifdef QUTILS_HAS_BOOST
		static TLS boost::uuids::string_generator gen;
		GUID guid;
		guid.uuid = gen(value);
		return guid;
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	
	GUID& GUID::operator=(const GUID& value)
	{
	#ifdef QUTILS_HAS_BOOST
		this->uuid = value.uuid;
	#endif
		return *this;
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
	
	
	void to_json(nlohmann::json& j, const GUID& guid)
	{
	#ifdef QUTILS_HAS_BOOST
		j = to_string(guid);
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
	void from_json(const nlohmann::json& j, GUID& guid)
	{
	#ifdef QUTILS_HAS_BOOST
		guid = GUID::FromString(j.get<std::string>());
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
	
}
}


namespace std
{
	std::size_t hash<QUtils::GUID>::operator()(const QUtils::GUID id) const
	{
	#ifdef QUTILS_HAS_BOOST
		boost::hash<boost::uuids::uuid> uuid_hasher;
		return uuid_hasher(id.uuid);
	#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
	#endif
	}
}