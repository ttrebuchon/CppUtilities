#include <QUtils/Reddit/Account.h>
#include <QUtils/Reddit/RedditSys.h>

#include <QUtils/Debug/DAssert.h>
#include <QUtils/Exception/NotImplemented.h>

#include "Macro.h"

namespace QUtils { namespace Reddit {
	
	Account::Account(RedditSystem* sys, json_ptr&& j) : Thing(sys, (json_ptr&&)j), Created()
	{
		
	}
	
	#define PROPERTY(TYPE, NAME) CLASS_PROPERTY(Account, TYPE, NAME)
	
	PROPERTY(int, comment_karma)
	PROPERTY(bool, has_mail)
	PROPERTY(bool, has_mod_mail)
	PROPERTY(bool, has_verified_email)
	PROPERTY(int, inbox_count)
	PROPERTY(bool, is_friend)
	PROPERTY(bool, is_gold)
	PROPERTY(bool, is_mod)
	PROPERTY(int, link_karma)
	PROPERTY(bool, over_18)
	
	
	
	
	
	
}
}