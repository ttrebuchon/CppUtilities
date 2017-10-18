#pragma once

#include <QUtils/Enum/Flags.h>

namespace QUtils { namespace Graph {
	
	enum struct NodeDetails
	{
		None = 0,
		BackLinked = 1,
	};
	
	
	QUTILS_FLAG_ENUM_OPS(NodeDetails);
}
}