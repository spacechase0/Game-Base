#include "InputBinding.hpp"

#include <functional>
#include <util/Logger.hpp>
#include <util/String.hpp>

InputBinding::InputBinding( sf::Keyboard::Key theKey )
   : type( Keyboard ),
     key( theKey ),
     state( 0 ),
     prevState( 0 )
{
}

InputBinding::InputBinding( sf::Mouse::Button theMouseButton )
   : type( MouseButton ),
     mouseButton( theMouseButton ),
     state( 0 ),
     prevState( 0 )
{
}

InputBinding::InputBinding( int joystickId, sf::Joystick::Axis axis, int dir )
   : type( JoystickAxis ),
     joystickAxis{ joystickId, axis, dir },
     state( 0 ),
     prevState( 0 )
{
}

InputBinding::InputBinding( int joystickId, int button )
   : type( JoystickButton ),
     joystickButton{ joystickId, button },
     state( 0 ),
     prevState( 0 )
{
}

bool InputBinding::isActive() const
{
	return state > 0;
}

bool InputBinding::wasActive() const
{
	return prevState > 0;
}

float InputBinding::getState() const
{
	return state;
}

float InputBinding::getLastState() const
{
	return prevState;
}

std::string InputBinding::write() const
{
	std::string out = util::toString( type ) + ",";
	switch ( type )
	{
		case Keyboard: out += util::toString( key ); break;
		case MouseButton: out += util::toString( mouseButton ); break;
		case JoystickAxis:
			out += util::toString( joystickAxis.id ) + ",";
			out += util::toString( joystickAxis.axis ) + ",";
			out += util::toString( joystickAxis.dir );
			break;
		case JoystickButton:
			out += util::toString( joystickButton.id ) + ",";
			out += util::toString( joystickButton.button );
			break;
	}
	
	return out;
}

InputBinding InputBinding::read( const std::string& str )
{
	std::vector< std::string > tokens = util::tokenize( str );
	int typeInt = util::fromString< int >( tokens[ 0 ] );
	Type type = static_cast< Type >( typeInt );
	
	if ( type == Keyboard )
	{
		int keyInt = util::fromString< int >( tokens[ 1 ] );
		return InputBinding( static_cast< sf::Keyboard::Key >( keyInt ) );
	}
	else if ( type == MouseButton )
	{
		int mouseInt = util::fromString< int >( tokens[ 1 ] );
		return InputBinding( static_cast< sf::Mouse::Button >( mouseInt ) );
	}
	else if ( type == JoystickAxis )
	{
		int id = util::fromString< int >( tokens[ 1 ] );
		int axisInt = util::fromString< int >( tokens[ 2 ] );
		int dir = util::fromString< int >( tokens[ 3 ] );
		return InputBinding( id, static_cast< sf::Joystick::Axis >( axisInt ), dir );
	}
	else if ( type == JoystickButton )
	{
		int id = util::fromString< int >( tokens[ 1 ] );
		int button = util::fromString< int >( tokens[ 2 ] );
		return InputBinding( id, button );
	}
	
	// This should never happen... right?
	return InputBinding( sf::Keyboard::Unknown );
}

void InputBinding::update()
{
	prevState = state;
	state = check();
}

float InputBinding::check() const
{
	switch ( type )
	{
		case Keyboard:
			return sf::Keyboard::isKeyPressed( key ) ? 1 : 0;
			
		case MouseButton:
			return sf::Mouse::isButtonPressed( mouseButton ) ? 1 : 0;
		
		case JoystickAxis:
			{
				if ( !sf::Joystick::isConnected( joystickAxis.id ) )
				{
					return 0;
				}
				
				float value = sf::Joystick::getAxisPosition( joystickAxis.id, joystickAxis.axis );
					 if ( joystickAxis.dir < 0 ) return -value / 100;
				else if ( joystickAxis.dir > 0 ) return value / 100;
				
				return 0;
			}
		
		case JoystickButton:
			{
				if ( !sf::Joystick::isConnected( joystickAxis.id ) )
				{
					return 0;
				}
				
				return sf::Joystick::isButtonPressed( joystickButton.id, joystickButton.button ) ? 1 : 0;
			}
	}
	
	return 0;
}
