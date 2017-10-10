#include <QUtils/Network/Service/Message.h>

namespace QUtils { namespace Network {
	void to_json(nlohmann::json& j, const Message& msg)
	{
		j["priority"] = msg.priority();
		j["timestamp"] = msg.time().time_since_epoch().count();
		msg.serialize(j["content"]);
	}
	void from_json(const nlohmann::json& j, Message& msg);
}
}