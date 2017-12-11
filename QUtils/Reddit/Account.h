#pragma once
#include <string>

#include "ForwardDecs.h"
#include "Created.h"

namespace QUtils { namespace Reddit {
	
	
	class Account : public Created
	{
		private:
		
		protected:
		Account(RedditSystem* sys, json_ptr&&);
		
		public:
		constexpr static Reddit::Kind Kind = Reddit::Kind::t2;
		
		int comment_karma() const;
		bool has_mail() const;
		bool has_mod_mail() const;
		bool has_verified_email() const;
		int inbox_count() const;
		bool is_friend() const;
		bool is_gold() const;
		bool is_mod() const;
		int link_karma() const;
		bool over_18() const;
		
		virtual typename Reddit::Kind kind() const override
		{
			return Kind;
		}
		
		friend class RedditSystem;
	};
	
	
	
}
}