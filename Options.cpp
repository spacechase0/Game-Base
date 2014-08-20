#include "Options.hpp"

#include <SFML/Audio/Listener.hpp>
#include <util/IniFile.hpp>
#include <util/Logger.hpp>

Options::Options()
{
	// Add controls here.
}

void Options::save( const std::string& filename )
{
	util::IniFile config;
	config[ "General" ][ "Volume" ] = util::toString( sf::Listener::getGlobalVolume() );
	for ( auto it = controls.begin(); it != controls.end(); ++it )
	{
		config[ "Controls" ][ it->first ] = it->second.write();
	}
	
	config.saveToFile( filename );
}

void Options::load( const std::string& filename )
{
	util::IniFile config;
	if ( !config.loadFromFile( filename ) )
	{
		log( "Failed to load config file." );
		return;
	}
	
	sf::Listener::setGlobalVolume( util::fromString< float >( config[ "General" ][ "Volume" ] ) );
	for ( auto it = controls.begin(); it != controls.end(); ++it )
	{
		it->second = InputBinding::read( config[ "Controls" ][ it->first ] );
	}
}
