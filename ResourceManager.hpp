#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <memory>
#include <SFML/System/Mutex.hpp>
#include <string>

namespace sf
{
	class Texture;
	class SoundBuffer;
	class Font;
}

class ResourceManager
{
	public:
		bool loadTexture( const std::string& filename );
		bool loadSoundBuffer( const std::string& filename );
		bool loadFont( const std::string& filename );
		
		std::shared_ptr< sf::Texture > getTexture( const std::string& filename, bool loadIfNotLoaded = true );
		std::shared_ptr< sf::SoundBuffer > getSoundBuffer( const std::string& filename, bool loadIfNotLoaded = true );
		std::shared_ptr< sf::Font > getFont( const std::string& filename, bool loadIfNotLoaded = true );
		
		void unloadTexture( const std::string& filename );
		void unloadSoundBuffer( const std::string& filename );
		void unloadFont( const std::string& filename );
		void unloadAll();
	
	private:
		sf::Mutex texMutex;
		sf::Mutex soundMutex;
		sf::Mutex fontMutex;
		
		std::map< std::string, std::shared_ptr< sf::Texture > > textures;
		std::map< std::string, std::shared_ptr< sf::SoundBuffer > > soundBuffers;
		std::map< std::string, std::shared_ptr< sf::Font > > fonts;
};

#endif // RESOURCEMANAGER_HPP
