#include "Options.hpp"

#include <SFML/Audio/Listener.hpp>
#include <util/IniFile.hpp>
#include <util/Logger.hpp>

Options::Options()
{
	// Add controls here, such as:
	// controls.push_back( std::make_pair( "Up", InputBinding( sf::Keyboard::W ) ) );
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
		if ( config[ "Controls" ].find( it->first ) == config[ "Controls" ].end() ) continue;
		it->second = InputBinding::read( config[ "Controls" ][ it->first ] );
	}
}

const InputBinding& Options::getInputBinding( const std::string& str ) const
{
	for ( auto it = controls.begin(); it != controls.end(); ++it )
	{
		if ( it->first == str )
		{
			return it->second;
		}
	}
	
	throw std::invalid_argument( "'" + str + "' is not an existing control." );
}

InputBinding& Options::getInputBinding( const std::string& str )
{
	for ( auto it = controls.begin(); it != controls.end(); ++it )
	{
		if ( it->first == str )
		{
			return it->second;
		}
	}
	
	throw std::invalid_argument( "'" + str + "' is not an existing control." );
}

std::vector< std::string > Options::getControlList() const
{
	std::vector< std::string > controlList;
	controlList.reserve( controls.size() );
	for ( auto it = controls.begin(); it != controls.end(); ++it )
	{
		controlList.push_back( it->first );
	}
	
	return controlList;
}

void Options::updateInput()
{
	for ( auto it = controls.begin(); it != controls.end(); ++it )
	{
		it->second.update();
	}
}
