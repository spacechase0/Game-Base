#ifndef RES_MANAGER_HPP
#define RES_MANAGER_HPP

#include <map>
#include <memory>
#include <SFML/System/Mutex.hpp>
#include <string>
#include <util/Logger.hpp>

namespace res
{
	class Data;
	class Reference;
	
	class Manager
	{
		public:
			Manager();
			~Manager();
			
			Reference get( const std::string& filename );
			Reference load( const std::string& filename );
			
			void reload();
			
			mutable util::Logger log;
		
		private:
			std::map< std::string, std::unique_ptr< Data > > resources;
	};
}

#endif // RES_MANAGER_HPP

