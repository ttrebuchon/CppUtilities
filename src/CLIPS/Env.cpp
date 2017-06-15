#include <CLIPS/Env.h>
#include <CLIPS/Fact.h>
#include <CLIPS/Value.h>
#include <sstream>
#include <iostream>


namespace Util
{
namespace Clips
{
	std::string FactToString(struct ::fact* fPtr);

	std::vector<std::string> MFToString(struct ::multifield* mfPtr)
	{
		
		long len = mfPtr->multifieldLength;
		long index = -1;
		std::vector<std::string> v(len);

		while (++index < len)
		{
			auto type = mfPtr->theFields[index].type;
			
			switch (type)
			{
				case String:
				case Instance_Name:
				case Symbol:
					v.push_back(static_cast<std::string>(DOToString(mfPtr->theFields[index])));
					break;
				case Float:
					v.push_back(std::to_string(DOToDouble(mfPtr->theFields[index])));
					break;
				case Integer:
					v.push_back(std::to_string(DOToLong(mfPtr->theFields[index])));
					break;

				case Fact_Address:{
					struct ::fact* fPtr = ((struct ::fact*)DOToPointer(mfPtr->theFields[index]));
					v.push_back(FactToString(fPtr));}
					break;

				case Multifield:{
					auto subVec = MFToString((struct ::multifield*)mfPtr->theFields[index].value);
					for (auto str : subVec)
					{
						if (str != "")
						{
							v.push_back(str);
						}
						
					}}
					break;
			}
		}
		return v;

	}


	std::string FactToString(struct ::fact* fPtr)
	{
		struct ::multifield* mfPtr = &(fPtr->theProposition);
		std::string str = "";
		
		for (auto item : MFToString(mfPtr))
		{
			if (item != "")
			{
				str = str + " " + item;
			}
			
		}
		
		if (str.length() > 0)
		{
			str = str.substr(1);
		}
		auto contents = fPtr->whichDeftemplate->header.name->contents;
		return std::string("(") + std::string(contents != NULL ? contents : "NULL") + " (" + str + "))";

	}


	std::map<void*, int> Environment::use_counts;


	Environment::Environment() : env(CreateEnvironment()), _facts()
	{
		use_counts[env]++;
	}


	Environment::~Environment()
	{
		use_counts[env]--;
		if (use_counts[env] <= 0)
		{
			use_counts.erase(env);
			_facts.clear();
			DestroyEnvironment(env);
		}
	}
	
	
	void Environment::clear()
	{
		EnvClear(env);
	}
	
	
	void Environment::reset()
	{
		EnvReset(env);
	}
	
	bool Environment::build(const std::string str)
	{
		return EnvBuild(env, str.c_str());
	}
	
	std::vector<std::string> Environment::facts() const
	{
		DATA_OBJECT factlist;
		EnvGetFactList(env, &factlist, NULL);
		
		std::vector<std::string> vec;
		if (GetType(factlist) == MULTIFIELD)
		{
			auto end = GetDOEnd(factlist);
			void* multifieldPtr = GetValue(factlist);
			
			char factBuffer[1024+1];


			for (auto i = GetDOBegin(factlist); i <= end; i++)
			{
				EnvGetFactPPForm(env, factBuffer, 1024, GetMFValue(multifieldPtr, i));
				vec.push_back(std::string(factBuffer));
			}
		}
		return vec;
	}
	
	
	std::shared_ptr<Fact> Environment::assert_f(const std::string str)
	{
		void* rfact = EnvAssertString(env, const_cast<char*>(str.c_str()));
		if (!rfact)
		{
			return NULL;
		}

		struct ::fact* f = EnvCreateFact(env, rfact);
		return _facts[f->factIndex] = std::make_shared<Fact>(env, f);
		return NULL;

	}

	

	int Environment::run(int runlimit)
	{
		int executed = EnvRun(env, runlimit);
		return executed;
	}


	bool Environment::watch(const std::string str)
	{
		return EnvWatch(env, const_cast<char*>(str.c_str()));
	}
	
	Environment& Environment::operator=(const Environment& env)
	{
		if (this->env != NULL)
		{
			use_counts[this->env]--;
			if (use_counts[this->env] <= 0)
			{
				DestroyEnvironment(this->env);
				this->env = NULL;
			}
		}
		this->env = env.env;
		use_counts[this->env]++;
		return *this;
	}

	std::vector<std::string> Environment::evaluate(const std::string expression)
	{
		DATA_OBJECT obj;
		int status = EnvEval(env, static_cast<const char*>(expression.c_str()), &obj);
		std::vector<std::string> results;
		if (status)
		{
			switch (GetType(obj))
			{
				
				case String:
				case Instance_Name:
				case Symbol:
					results.push_back(static_cast<std::string>(DOToString(obj)));
					break;
				case Float:
					results.push_back(std::to_string(DOToDouble(obj)));
					break;
				case Integer:
					results.push_back(std::to_string(DOToLong(obj)));
					break;
				case Fact_Address:

					{struct ::fact* fPtr = ((struct ::fact*)DOToPointer(obj));
					results.push_back(FactToString(fPtr));}
					break;

				case Rvoid:

					break;


				case Multifield:
					{
						struct ::multifield* ptr = ((struct ::multifield*)DOToPointer(obj));
						for (auto res : MFToString(ptr))
						{
							if (res == "")
							{
								continue;
							}
							results.push_back(res);
						}
					}
					break;

				default:
					std::cerr << "Unhandled type case: " << GetType(obj) << std::endl;
					break;
			}
		}
		return results;
	}

}
}