#include "res/Data.hpp"

#include <fstream>

#include "res/ReloadNotify.hpp"

namespace res
{
	Data::~Data()
	{
	}
	
	bool Data::isLoaded() const
	{
		return data.get();
	}
	
	bool Data::load()
	{
		// TODO: Use manager access
		std::ifstream file( filename, std::ios::in | std::ios::binary );
		if ( !file )
		{
			return false;
		}
		
		file.seekg( 0, std::ios::end );
		std::unique_ptr< std::string > newData( new std::string() );
		newData->resize( file.tellg() );
		
		file.seekg( 0, std::ios::beg );
		file.read( &( * newData )[ 0 ], newData->size() );
		if ( !file.good() )
		{
			return false;
		}
		
		data = std::move( newData );
		for ( auto it = toNotify.begin(); it != toNotify.end(); ++it )
		{
			it->second->onLoad( * this );
		}
		
		return true;
	}

	std::string Data::getName() const
	{
		return filename;
	}
	
	const std::string& Data::getData() const
	{
		return ( * data );
	}
	
	void Data::notify( ReloadNotify* notify )
	{
		const std::type_info& type = typeid( * notify );
		toNotify[ &type ].reset( notify );
	}
	
	ReloadNotify* Data::notifierForType( const std::type_info& type )
	{
		for ( auto it = toNotify.begin(); it != toNotify.end(); ++it )
		{
			if ( ( * it->first ) == type )
			{
				return it->second.get();
			}
		}
		
		return NULL;
	}
	
	Manager& Data::getManager()
	{
		return manager;
	}
	
	const Manager& Data::getManager() const
	{
		return manager;
	}

	Data::Data( Manager& theManager, const std::string& theFilename )
	   : manager( theManager ),
	     filename( theFilename )
	{
	}
}
