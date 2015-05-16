#ifndef RES_TYPE_HPP
#define RES_TYPE_HPP

#include "res/Reference.hpp"

namespace sf
{
	class Font;
	class SoundBuffer;
	class Texture;
}

namespace res
{
	class Reference;
	
	sf::Font& font( Reference ref );
	sf::SoundBuffer& soundBuffer( Reference ref );
	sf::Texture& texture( Reference ref );
}

#endif // RES_TYPE_HPP
