#include <QUtils/Multi/Lockable.h>

namespace QUtils
{
namespace Multi
{
	Lockable::Lockable() : mut()
	{
		
	}
	
	
	bool Lockable::try_lock()
	{
		return mut.try_lock();
	}
	
	void Lockable::lock()
	{
		return mut.lock();
	}
	
	void Lockable::unlock()
	{
		return mut.unlock();
	}
	
	
}
}