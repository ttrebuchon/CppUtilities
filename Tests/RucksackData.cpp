#include <vector>
#include <tuple>
namespace RucksackData
{

	//[(Size, Value)]
	const std::vector<std::tuple<double, double>>& items()
	{
		return data;
	}
}