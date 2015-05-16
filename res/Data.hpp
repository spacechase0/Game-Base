#ifndef RES_DATA_HPP
#define RES_DATA_HPP

#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <util/TypeCompare.hpp>

namespace res
{
	class Manager;
	class ReloadNotify;
	
	class Data
	{
		public:
			~Data();
			
			bool isLoaded() const;
			bool load();
			
			std::string getName() const;
			const std::string& getData() const;
			
			void notify( ReloadNotify* notify );
			ReloadNotify* notifierForType( const std::type_info& type );
			
			Manager& getManager();
			const Manager& getManager() const;
		
		private:
			friend class Manager;
			friend class Reference;
			
			Data( Manager& theManager, const std::string& theFilename );
			
			Manager& manager;
			const std::string filename;
			std::unique_ptr< std::string > data;
			std::map< const std::type_info*, std::unique_ptr< ReloadNotify >, util::TypeCompare > toNotify;
			int refs = 0;
			
			class Type;
	};
}

#endif // RES_DATA_HPP


