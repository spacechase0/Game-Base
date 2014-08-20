#include "Utility.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

void handleHighlight( const sf::Window& window, sf::Text& text )
{
	if ( text.getGlobalBounds().contains( sf::Vector2f( sf::Mouse::getPosition( window ) ) ) )
	{
		text.setColor( sf::Color( 128, 128, 128 ) );
	}
	else
	{
		text.setColor( sf::Color::White );
	}
}

std::string keyToString( sf::Keyboard::Key key )
{
	switch ( key )
	{
		#define key(a) case sf::Keyboard::a: return #a
		key( Unknown );
		key( A );
		key( B );
		key( C );
		key( D );
		key( E );
		key( F );
		key( G );
		key( H );
		key( I );
		key( J );
		key( K );
		key( L );
		key( M );
		key( N );
		key( O );
		key( P );
		key( Q );
		key( R );
		key( S );
		key( T );
		key( U );
		key( V );
		key( W );
		key( X );
		key( Y );
		key( Z );
		key( Num0 );
		key( Num1 );
		key( Num2 );
		key( Num3 );
		key( Num4 );
		key( Num5 );
		key( Num6 );
		key( Num7 );
		key( Num8 );
		key( Num9 );
		key( Escape );
		key( LControl );
		key( LShift );
		key( LAlt );
		key( LSystem );
		key( RControl );
		key( RShift );
		key( RAlt );
		key( RSystem );
		key( Menu );
		key( LBracket );
		key( RBracket );
		key( SemiColon );
		key( Comma );
		key( Period );
		key( Quote );
		key( Slash );
		key( BackSlash );
		key( Tilde );
		key( Equal );
		key( Dash );
		key( Space );
		key( Return );
		key( BackSpace );
		key( Tab );
		key( PageUp );
		key( PageDown );
		key( End );
		key( Home );
		key( Insert );
		key( Delete );
		key( Add );
		key( Subtract );
		key( Multiply );
		key( Divide );
		key( Left );
		key( Right );
		key( Up );
		key( Down );
		key( Numpad0 );
		key( Numpad1 );
		key( Numpad2 );
		key( Numpad3 );
		key( Numpad4 );
		key( Numpad5 );
		key( Numpad6 );
		key( Numpad7 );
		key( Numpad8 );
		key( Numpad9 );
		key( F1 );
		key( F2 );
		key( F3 );
		key( F4 );
		key( F5 );
		key( F6 );
		key( F7 );
		key( F8 );
		key( F9 );
		key( F10 );
		key( F11 );
		key( F12 );
		key( F13 );
		key( F14 );
		key( F15 );
		key( Pause );
		#undef key
	}
	
	return "???";
}
