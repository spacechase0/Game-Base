#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace sf
{
	class Text;
	class Window;
}

void handleHighlight( const sf::Window& window, sf::Text& text );
std::string keyToString( sf::Keyboard::Key key );

std::string getWritablePathFor( const std::string& file );

#endif // UTILITY_HPP
