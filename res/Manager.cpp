#include "res/Manager.hpp"

#include <iostream>

#include "res/Data.hpp"
#include "res/Reference.hpp"

namespace res
{
	Manager::Manager() 
	   : log( "logs/res.txt" )
	{
	}
	
	Manager::~Manager() = default;
	
	Reference Manager::get( const std::string& filename )
	{
		auto it = resources.find( filename );
		if ( it == resources.end() )
		{
			it = resources.emplace( std::make_pair( filename, std::unique_ptr< Data >() ) ).first;
			it->second.reset( new Data( ( * this ), filename ) );
		}
		
		return Reference( it->second.get() );
	}
	
	Reference Manager::load( const std::string& filename )
	{
		// TODO: Use a logger instead
		Reference ref = get( filename );
		if ( !ref->load() )
		{
			log( "Failed to load resource '%s'.\n", filename );
		}
		
		return ref;
	}
	
	void Manager::reload()
	{
		for ( auto it = resources.begin(); it != resources.end(); ++it )
		{
			load( it->first );
		}
	}
}
