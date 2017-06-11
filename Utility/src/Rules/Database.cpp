#include <Rules/Database.h>

namespace Util
{
namespace Rules
{
	std::map<long long, std::vector<DBWrapper*>> DatabaseHandler::handles;
}
}