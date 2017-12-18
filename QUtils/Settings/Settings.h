#pragma once
#include <memory>
#include <json/json.hpp>


namespace QUtils { namespace __Settings {
	
	template <class X = void>
	class _Settings
	{
		static_assert(std::is_same<X, void>::value, "");
		
		private:
		mutable nlohmann::json* doc;
		std::string filename;
		mutable bool changed;
		
		_Settings(const std::string fname);
		
		void open() const;
		
		public:
		static std::shared_ptr<_Settings> Default;
		
		~_Settings();
		
		std::string get(const std::string key) const;
		void set(const std::string key, const std::string value);
		template <class T>
		T get(const std::string key) const;
		template <class T>
		void set(const std::string key, const T value);
		void remove(const std::string);
		
		void save() const;
		void reload();
		
		friend std::shared_ptr<_Settings<>> _settingsInit();
	};
	
	std::shared_ptr<_Settings<>> _settingsInit();
	
	template <>
	std::shared_ptr<_Settings<>> _Settings<>::Default = _settingsInit();
	
	
	
	std::shared_ptr<_Settings<>> _settingsInit()
	{
		static bool initted = false;
		if (initted)
		{
			throw std::exception();
		}
		initted = true;
		return std::shared_ptr<_Settings<>>(new _Settings<>("Settings.json"));
	}
	
}

typedef __Settings::_Settings<> Settings;
}

#include "Settings.hpp"