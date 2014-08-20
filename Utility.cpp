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
