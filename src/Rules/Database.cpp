#include <QUtils/Rules/Database.h>

namespace QUtils
{
namespace Rules
{
	std::map<long long, std::vector<DBWrapper*>> DatabaseHandler::handles;
}
}